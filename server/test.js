#!/usr/bin/env node
'use strict';

// Lightweight, dependency-free test suite for the bundled Hjson parser
// (`parser.js`) and stringifier (`formatter.js`). Run with:
//
//   node server/test.js
//
// Exits with a non-zero status code if any assertion fails.

const assert = require('assert');
const fs = require('fs');
const path = require('path');
const { parse } = require('./parser');
const { stringify } = require('./formatter');

const FIXTURE_PATH = path.join(__dirname, 'test-fixtures', 'sample.hjson');

let passed = 0;
let failed = 0;

function test(name, fn) {
  try {
    fn();
    passed++;
    console.log('  ok - ' + name);
  } catch (e) {
    failed++;
    console.error('  FAIL - ' + name);
    console.error('    ' + (e && e.stack ? e.stack : e));
  }
}

// ---------------------------------------------------------------------------
// Parser tests
// ---------------------------------------------------------------------------

test('parses a simple object with quoteless values', () => {
  const value = parse('name: Test\nage: 42\n');
  assert.deepStrictEqual(value, { name: 'Test', age: 42 });
});

test('parses booleans and null', () => {
  const value = parse('a: true\nb: false\nc: null\n');
  assert.deepStrictEqual(value, { a: true, b: false, c: null });
});

test('parses numbers (int, float, exponent, negative)', () => {
  const value = parse('a: 1\nb: -2\nc: 1.5\nd: 1e3\ne: -1.5e-2\n');
  assert.deepStrictEqual(value, { a: 1, b: -2, c: 1.5, d: 1000, e: -0.015 });
});

test('parses nested objects and arrays', () => {
  const value = parse('outer: {\n  inner: [1, 2, 3]\n}\n');
  assert.deepStrictEqual(value, { outer: { inner: [1, 2, 3] } });
});

test('parses quoted string values', () => {
  const value = parse('key: "hello world"\n');
  assert.deepStrictEqual(value, { key: 'hello world' });
});

test('parses quoted string escapes', () => {
  const value = parse('key: "line1\\nline2\\ttab"\n');
  assert.deepStrictEqual(value, { key: 'line1\nline2\ttab' });
});

test('parses line comments (# and //)', () => {
  const value = parse('a: 1 # comment\nb: 2 // another comment\n');
  assert.deepStrictEqual(value, { a: 1, b: 2 });
});

test('parses block comments', () => {
  const value = parse('a: 1\n/* this is\n a block comment */\nb: 2\n');
  assert.deepStrictEqual(value, { a: 1, b: 2 });
});

test('parses multiline (triple-quoted) strings', () => {
  const value = parse('key:\n  \'\'\'\n  line1\n  line2\n  \'\'\'\n');
  assert.deepStrictEqual(value, { key: 'line1\nline2' });
});

test('parses unquoted keys containing internal spaces', () => {
  const value = parse('display name: Some Value\n');
  assert.deepStrictEqual(value, { 'display name': 'Some Value' });
});

test('parses unquoted keys with internal spaces inside nested objects', () => {
  const value = parse('outer: {\n  my key: 1\n}\n');
  assert.deepStrictEqual(value, { outer: { 'my key': 1 } });
});

test('parses quoted keys', () => {
  const value = parse('"my key": 1\n');
  assert.deepStrictEqual(value, { 'my key': 1 });
});

test('parses an unquoted object value containing commas as ordinary punctuation', () => {
  const value = parse('description: A jittery clerk agreed, but he lost his nerve, and bolted.\nother: 1\n');
  assert.deepStrictEqual(value, {
    description: 'A jittery clerk agreed, but he lost his nerve, and bolted.',
    other: 1,
  });
});

test('still terminates array quoteless elements early at a comma', () => {
  const value = parse('list: [one, two, three]\n');
  assert.deepStrictEqual(value, { list: ['one', 'two', 'three'] });
});

test('still splits a single-line object with multiple comma-separated properties', () => {
  const value = parse('stats: {intelligence: -6, libido: 3}\n');
  assert.deepStrictEqual(value, { stats: { intelligence: -6, libido: 3 } });
});

test('parses a braceless root object', () => {
  const value = parse('a: 1\nb: 2\n');
  assert.deepStrictEqual(value, { a: 1, b: 2 });
});

test('parses top-level arrays', () => {
  const value = parse('[1, 2, 3]');
  assert.deepStrictEqual(value, [1, 2, 3]);
});

test('parses empty objects and arrays', () => {
  const value = parse('a: {}\nb: []\n');
  assert.deepStrictEqual(value, { a: {}, b: [] });
});

test('throws a ParseError with a line number on invalid input', () => {
  assert.throws(() => parse('{\n  a\n}\n'), /at line \d+/);
});

// ---------------------------------------------------------------------------
// Formatter tests
// ---------------------------------------------------------------------------

test('stringify quotes strings by default', () => {
  const out = stringify({ name: 'Test' });
  assert.strictEqual(out, 'name: "Test"\n');
});

test('stringify can disable quoting via options', () => {
  const out = stringify({ name: 'Test' }, { quotes: false });
  assert.strictEqual(out, 'name: Test\n');
});

test('stringify emits multiline blocks for newline-containing strings even when quoting', () => {
  const out = stringify({ key: 'line1\nline2' }, { quotes: true });
  assert.ok(out.includes("'''"), 'expected a multiline block, got: ' + out);
  assert.ok(!out.includes('\\n'), 'should not escape the newline as \\n when quoting');
});

test('stringify quotes keys that need it, leaves ordinary keys bare', () => {
  const out = stringify({ ordinary: 1, 'needs quotes:': 2 }, { quotes: false });
  assert.ok(out.includes('ordinary: 1'));
  assert.ok(out.includes('"needs quotes:": 2'));
});

test('stringify renders nested objects and arrays', () => {
  const out = stringify({ outer: { inner: [1, 2, 3] } }, { quotes: false });
  assert.ok(out.includes('outer:'));
  assert.ok(out.includes('inner:'));
  assert.ok(out.includes('1'));
});

test('stringify handles booleans, numbers, and null', () => {
  const out = stringify({ a: true, b: false, c: null, d: 1.5 }, { quotes: false });
  assert.ok(out.includes('a: true'));
  assert.ok(out.includes('b: false'));
  assert.ok(out.includes('c: null'));
  assert.ok(out.includes('d: 1.5'));
});

// ---------------------------------------------------------------------------
// Parser + formatter round-trip tests
// ---------------------------------------------------------------------------

test('round-trips a mixed document through parse -> stringify -> parse', () => {
  const text = [
    'name: Test',
    'display name: Some Value',
    'nested: {',
    '  my key: 1',
    '  list: [1, 2, 3]',
    '}',
    '',
  ].join('\n');

  const value1 = parse(text);
  const formatted = stringify(value1, { quotes: true });
  const value2 = parse(formatted);

  assert.deepStrictEqual(value1, value2);
  assert.deepStrictEqual(value1, {
    name: 'Test',
    'display name': 'Some Value',
    nested: { 'my key': 1, list: [1, 2, 3] },
  });
});

test('round-trip preserves both quoting and multiline formatting simultaneously', () => {
  const value = { title: 'Hello', body: 'line1\nline2' };
  const formatted = stringify(value, { quotes: true });

  // Quoted single-line string.
  assert.ok(formatted.includes('"Hello"'));
  // Multiline block for the newline-containing value, not an escaped string.
  assert.ok(formatted.includes("'''"));
  assert.ok(!formatted.includes('"line1\\nline2"'));

  const reparsed = parse(formatted);
  assert.deepStrictEqual(reparsed, value);
});

// ---------------------------------------------------------------------------
// Fixture-file test: exercises many features together in one realistic file
// ---------------------------------------------------------------------------

test('parses the sample.hjson fixture covering many features at once', () => {
  const text = fs.readFileSync(FIXTURE_PATH, 'utf8');
  const value = parse(text);

  assert.deepStrictEqual(value, [
    {
      name: 'Test Project',
      'display name': 'My Cool Project',
      version: '1.0.0',
      enabled: true,
      disabled: false,
      missing: null,
      count: 42,
      negative: -7,
      pi: 3.14159,
      exp: 1500,
      server: {
        host: 'localhost',
        port: 8080,
        'quoted key': 'value',
        'nested flag': true,
      },
      list: [1, 2, 3, 'four', 'five'],
      'empty object': {},
      'empty array': [],
      description: 'This is a multiline\nstring value that spans\nseveral lines.',
      quoted: 'a string with "escapes" and a\ttab',
      // The following two values are quoted strings that contain raw,
      // literal newlines within the quotes.
      realNewline: 'A quoted string with a\n    real newline in it',
      realNewline2: 'A quoted string with two\n\n    real newlines in it',
      // These two are quoteless values that continue onto following lines
      // without using the ''' multiline syntax. The parser leniently merges
      // such continuation lines into a single multi-line string value (see
      // `parseLiteralOrQuotelessString` in `server/parser.js`), and the
      // formatter re-emits them using proper ''' multiline blocks.
      unquotedStringWithNewline: 'An unquoted string with\na newline in it.',
      unquotedStringWithNewline2: 'An unquoted string with\n\ntwo newlines in it.',
    },
  ]);
});

test('round-trips the sample.hjson fixture through stringify -> parse', () => {
  const text = fs.readFileSync(FIXTURE_PATH, 'utf8');
  const value1 = parse(text);
  const formatted = stringify(value1, { quotes: true });
  const value2 = parse(formatted);

  assert.deepStrictEqual(value1, value2);
  // Quoting is on, so plain string values should be quoted in the output.
  assert.ok(formatted.includes('"Test Project"'));
  // The multiline description should still be emitted as a block, not an
  // escaped quoted string, even with quoting enabled.
  assert.ok(formatted.includes("'''"));
});

// ---------------------------------------------------------------------------

console.log('\n' + passed + ' passed, ' + failed + ' failed');
if (failed > 0) {
  process.exit(1);
}
