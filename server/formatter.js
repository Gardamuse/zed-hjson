'use strict';

// A small, self-contained Hjson stringifier written for this extension.
//
// It exists because the upstream `hjson-js` library has a bug where enabling
// the `quotes` stringify option (used to force-quote string values) silently
// implies `multiline: "off"`, which means strings containing real newlines or
// `\n` escapes never get converted to `'''...'''` multiline blocks. This
// formatter re-implements Hjson stringification so both behaviors can be
// active at the same time: strings are quoted by default *and* strings that
// contain a newline are automatically emitted as multiline blocks.

const NEEDS_QUOTES_RE = /^\s|\s$|^"|^'|^#|^\/\*|^\/\/|^\{|^\[|,|:|\}|\]|^$/;
const NEEDS_ESCAPE_RE = /[\\"\u0000-\u001f\u007f-\u009f\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/;
const NEEDS_ESCAPE_ML_RE = /[\\\u0000-\u0009\u000b-\u001f\u007f-\u009f\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/;
const STARTS_WITH_KEYWORD_RE = /^(true|false|null)\s*$/;
const NEEDS_QUOTES_NAME_RE = /[,\{\[\}\]\s:#"']|\/\/|\/\*/;

function isDigit(c) {
  return c >= '0' && c <= '9';
}

function quoteForString(value) {
  // Escape a plain (non-multiline) string as a JSON-style double-quoted string.
  let result = '"';
  for (const ch of value) {
    if (ch === '"' || ch === '\\') {
      result += '\\' + ch;
    } else if (ch === '\n') {
      result += '\\n';
    } else if (ch === '\r') {
      result += '\\r';
    } else if (ch === '\t') {
      result += '\\t';
    } else if (ch < ' ') {
      result += '\\u' + ch.charCodeAt(0).toString(16).padStart(4, '0');
    } else {
      result += ch;
    }
  }
  return result + '"';
}

function quoteForMultiline(value, indent) {
  const lines = value.split('\n');
  let result = "'''\n";
  for (const line of lines) {
    result += line.length > 0 ? indent + line + '\n' : '\n';
  }
  result += indent + "'''";
  return result;
}

function canUseUnquoted(value) {
  if (value.length === 0) return false;
  if (NEEDS_QUOTES_RE.test(value)) return false;
  if (STARTS_WITH_KEYWORD_RE.test(value)) return false;
  if (isDigit(value[0]) || value[0] === '-') {
    // Looks like it could be parsed back as a number; keep it quoted to be safe.
    if (/^-?\d+(\.\d+)?([eE][+-]?\d+)?$/.test(value)) return false;
  }
  return !NEEDS_ESCAPE_RE.test(value);
}

/**
 * Formats a string value for Hjson output.
 *
 * @param {string} value - the raw string value.
 * @param {string} indent - the indentation to use for continuation lines.
 * @param {{quotes: boolean}} options
 */
function formatStringValue(value, indent, options) {
  if (value.indexOf('\n') !== -1 && !NEEDS_ESCAPE_ML_RE.test(value.replace(/\n/g, ''))) {
    // Any value containing a real newline is always emitted as a multiline
    // block, regardless of the `quotes` option — this is the behavior that
    // `hjson-js` fails to provide when `quotes` is set.
    return quoteForMultiline(value, indent);
  }

  if (options.quotes || !canUseUnquoted(value)) {
    return quoteForString(value);
  }

  return value;
}

function formatKey(key) {
  if (key.length === 0 || NEEDS_QUOTES_NAME_RE.test(key) || STARTS_WITH_KEYWORD_RE.test(key) || isDigit(key[0])) {
    return quoteForString(key);
  }
  return key;
}

function formatValue(value, indentLevel, options) {
  const indent = options.indentString.repeat(indentLevel);
  const childIndent = options.indentString.repeat(indentLevel + 1);

  if (value === null || value === undefined) {
    return 'null';
  }
  if (typeof value === 'boolean' || typeof value === 'number') {
    return String(value);
  }
  if (typeof value === 'string') {
    return formatStringValue(value, childIndent, options);
  }
  if (Array.isArray(value)) {
    if (value.length === 0) return '[]';
    let out = '[\n';
    for (const item of value) {
      out += childIndent + formatValue(item, indentLevel + 1, options) + '\n';
    }
    out += indent + ']';
    return out;
  }
  if (typeof value === 'object') {
    const keys = Object.keys(value);
    if (keys.length === 0) return '{}';
    let out = '{\n';
    for (const key of keys) {
      out += childIndent + formatKey(key) + ': ' + formatValue(value[key], indentLevel + 1, options) + '\n';
    }
    out += indent + '}';
    return out;
  }
  return 'null';
}

/**
 * Stringifies a parsed value as Hjson text.
 *
 * @param {*} value - the value returned by `Hjson.parse`.
 * @param {{quotes?: boolean, indent?: number}} [userOptions]
 * @returns {string}
 */
function stringify(value, userOptions) {
  const options = {
    quotes: userOptions && userOptions.quotes !== undefined ? userOptions.quotes : true,
    indentString: ' '.repeat((userOptions && userOptions.indent) || 2),
  };

  if (value === null || value === undefined || typeof value !== 'object') {
    return formatValue(value, 0, options) + '\n';
  }

  // Top-level object/array: Hjson omits the outer braces for the root object.
  if (!Array.isArray(value)) {
    const keys = Object.keys(value);
    if (keys.length === 0) return '{}\n';
    let out = '';
    for (const key of keys) {
      out += formatKey(key) + ': ' + formatValue(value[key], 0, options) + '\n';
    }
    return out;
  }

  return formatValue(value, 0, options) + '\n';
}

module.exports = { stringify };
