'use strict';

// A small, self-contained Hjson parser written for this extension, so that
// the bundled language server has no runtime dependency on the `hjson` npm
// package (or any other third-party Hjson implementation). It supports the
// subset of the Hjson grammar commonly used in practice: objects, arrays,
// quoted/quoteless strings, multiline `'''...'''` strings, numbers,
// booleans, null, `#`/`//` line comments, `/* */` block comments, and
// optional commas.

class ParseError extends Error {
  constructor(message, pos, line) {
    super(message + ' at line ' + line);
    this.pos = pos;
    this.line = line;
  }
}

class Parser {
  constructor(text) {
    this.text = text;
    this.pos = 0;
    this.len = text.length;
  }

  peek() {
    return this.text[this.pos];
  }

  line() {
    let l = 1;
    for (let i = 0; i < this.pos; i++) {
      if (this.text[i] === '\n') l++;
    }
    return l;
  }

  error(message) {
    throw new ParseError(message, this.pos, this.line());
  }

  isWhitespace(ch) {
    return ch === ' ' || ch === '\t' || ch === '\r' || ch === '\n';
  }

  skipWhitespaceAndComments() {
    while (this.pos < this.len) {
      const ch = this.text[this.pos];
      if (this.isWhitespace(ch)) {
        this.pos++;
      } else if (ch === '#') {
        while (this.pos < this.len && this.text[this.pos] !== '\n') this.pos++;
      } else if (ch === '/' && this.text[this.pos + 1] === '/') {
        while (this.pos < this.len && this.text[this.pos] !== '\n') this.pos++;
      } else if (ch === '/' && this.text[this.pos + 1] === '*') {
        this.pos += 2;
        const end = this.text.indexOf('*/', this.pos);
        this.pos = end === -1 ? this.len : end + 2;
      } else {
        break;
      }
    }
  }

  skipCommasAndWhitespace() {
    while (this.pos < this.len) {
      const before = this.pos;
      this.skipWhitespaceAndComments();
      if (this.text[this.pos] === ',') {
        this.pos++;
      }
      if (this.pos === before) break;
    }
  }

  parseRoot() {
    this.skipWhitespaceAndComments();
    // Root may be a braceless object.
    const saved = this.pos;
    if (this.peek() !== '{' && this.peek() !== '[') {
      try {
        const obj = this.parseObjectBody(true);
        this.skipWhitespaceAndComments();
        if (this.pos >= this.len) return obj;
      } catch (e) {
        // fall through to try a plain value
      }
      this.pos = saved;
    }
    const value = this.parseValue(false);
    this.skipWhitespaceAndComments();
    return value;
  }

  parseValue(inArray) {
    this.skipWhitespaceAndComments();
    const ch = this.peek();
    if (ch === '{') return this.parseObject();
    if (ch === '[') return this.parseArray();
    if (ch === '"') return this.parseQuotedString();
    if (ch === "'" && this.text[this.pos + 1] === "'" && this.text[this.pos + 2] === "'") {
      return this.parseMultilineString();
    }
    return this.parseLiteralOrQuotelessString(inArray);
  }

  parseObject() {
    if (this.peek() !== '{') this.error('Expected {');
    this.pos++;
    const obj = this.parseObjectBody(false);
    this.skipWhitespaceAndComments();
    if (this.peek() !== '}') this.error('Expected }');
    this.pos++;
    return obj;
  }

  parseObjectBody(braceless) {
    const obj = {};
    while (true) {
      this.skipCommasAndWhitespace();
      if (this.pos >= this.len) break;
      if (!braceless && this.peek() === '}') break;

      const key = this.parseKey();
      this.skipWhitespaceAndComments();
      if (this.peek() !== ':') this.error("Expected ':' after key");
      this.pos++;
      const value = this.parseValue(false);
      obj[key] = value;
      this.skipWhitespaceAndComments();
    }
    return obj;
  }

  parseKey() {
    this.skipWhitespaceAndComments();
    if (this.peek() === '"') return this.parseQuotedString();
    let start = this.pos;
    // Unlike values, unquoted keys may contain internal whitespace (e.g.
    // `my key: value`); they only terminate at ':' or the start of a
    // structural character/comment. Trailing whitespace is trimmed below.
    while (
      this.pos < this.len &&
      this.text[this.pos] !== ':' &&
      this.text[this.pos] !== '\n' &&
      this.text[this.pos] !== '{' &&
      this.text[this.pos] !== '}' &&
      this.text[this.pos] !== '[' &&
      this.text[this.pos] !== ']' &&
      this.text[this.pos] !== ',' &&
      this.findLineCommentStart(this.text.slice(this.pos, this.pos + 2)) !== 0
    ) {
      this.pos++;
    }
    if (this.pos === start) this.error('Expected key');
    return this.text.slice(start, this.pos).replace(/[ \t\r]+$/, '');
  }

  parseArray() {
    if (this.peek() !== '[') this.error('Expected [');
    this.pos++;
    const arr = [];
    while (true) {
      this.skipCommasAndWhitespace();
      if (this.pos >= this.len) this.error('Unterminated array');
      if (this.peek() === ']') break;
      arr.push(this.parseValue(true));
      this.skipWhitespaceAndComments();
    }
    this.pos++; // consume ']'
    return arr;
  }

  parseQuotedString() {
    this.pos++; // consume opening quote
    let result = '';
    while (this.pos < this.len && this.text[this.pos] !== '"') {
      const ch = this.text[this.pos];
      if (ch === '\\') {
        this.pos++;
        const esc = this.text[this.pos];
        switch (esc) {
          case 'n': result += '\n'; break;
          case 't': result += '\t'; break;
          case 'r': result += '\r'; break;
          case 'b': result += '\b'; break;
          case 'f': result += '\f'; break;
          case '"': result += '"'; break;
          case '\\': result += '\\'; break;
          case '/': result += '/'; break;
          case 'u': {
            const hex = this.text.slice(this.pos + 1, this.pos + 5);
            result += String.fromCharCode(parseInt(hex, 16));
            this.pos += 4;
            break;
          }
          default:
            result += esc;
        }
        this.pos++;
      } else {
        result += ch;
        this.pos++;
      }
    }
    this.pos++; // consume closing quote
    return result;
  }

  parseMultilineString() {
    this.pos += 3; // consume '''
    // Skip to end of the opening line.
    if (this.text[this.pos] === '\n') {
      this.pos++;
    } else {
      while (this.pos < this.len && this.text[this.pos] !== '\n') this.pos++;
      if (this.text[this.pos] === '\n') this.pos++;
    }

    const startOfContent = this.pos;
    const end = this.text.indexOf("'''", this.pos);
    if (end === -1) this.error('Unterminated multiline string');

    let content = this.text.slice(startOfContent, end);
    this.pos = end + 3;

    // Strip a trailing newline immediately before the closing quotes and
    // de-indent based on the indentation of the closing quotes line.
    const lines = content.split('\n');
    if (lines.length > 0 && lines[lines.length - 1].trim() === '') {
      lines.pop();
    }

    // Determine indent from the line containing the closing quotes.
    let indent = '';
    const closingLineStart = this.text.lastIndexOf('\n', end - 1) + 1;
    indent = this.text.slice(closingLineStart, end);
    if (/^[ \t]*$/.test(indent) === false) indent = '';

    if (indent.length > 0) {
      for (let i = 0; i < lines.length; i++) {
        if (lines[i].startsWith(indent)) {
          lines[i] = lines[i].slice(indent.length);
        }
      }
    }

    return lines.join('\n');
  }

  parseLiteralOrQuotelessString(inArray) {
    const start = this.pos;
    let lineEnd = this.text.indexOf('\n', this.pos);
    if (lineEnd === -1) lineEnd = this.len;
    const rawLine = this.text.slice(this.pos, lineEnd);

    // A quoteless string normally runs to the end of the line (trimmed), but
    // also terminates early at a top-level ']' or '}' so that single-line
    // arrays/objects using quoteless values still work (e.g. `[1, 2, three]`
    // or `{allure: 3}`), and at a line comment.
    let stop = rawLine.length;
    const bracketIdx = rawLine.search(/[\]\}]/);
    if (bracketIdx !== -1) stop = Math.min(stop, bracketIdx);
    const commentIdx = this.findLineCommentStart(rawLine);
    if (commentIdx !== -1) stop = Math.min(stop, commentIdx);

    // A top-level ',' terminates the value too, but only when it's actually
    // separating this property from another one later on the same line
    // (array elements, e.g. `[1, 2, three]`, or a single-line object with
    // multiple properties, e.g. `{intelligence: -6, libido: 3}`). We detect
    // "another property follows" by checking for a ':' after the comma and
    // before the next hard stop. Plain sentence commas inside natural-
    // language values (e.g. `description: A jittery clerk agreed, but he's
    // losing his nerve.`) have no such trailing ':', so they are left alone
    // — otherwise the remainder of the sentence would be misinterpreted as
    // a bogus key on the same line.
    if (inArray) {
      const commaIdx = rawLine.indexOf(',');
      if (commaIdx !== -1) stop = Math.min(stop, commaIdx);
    } else {
      let searchFrom = 0;
      while (true) {
        const commaIdx = rawLine.indexOf(',', searchFrom);
        if (commaIdx === -1 || commaIdx >= stop) break;
        if (rawLine.slice(commaIdx + 1, stop).indexOf(':') !== -1) {
          stop = commaIdx;
          break;
        }
        searchFrom = commaIdx + 1;
      }
    }

    let value = rawLine.slice(0, stop);
    // Trim trailing whitespace only; leading whitespace was already skipped.
    value = value.replace(/[ \t\r]+$/, '');

    this.pos = start + stop;

    // Strict Hjson requires quoteless strings to end at the line break, so a
    // continuation line with no ':'/closing bracket/comment would normally
    // be a syntax error (it looks like a malformed key). In practice this
    // usually means the author intended a multi-line value without using the
    // ''' syntax, so we're lenient here: as long as the value ran naturally
    // to the end of its line (no early ',', ']', '}' or comment terminator),
    // keep absorbing subsequent lines as part of the same value until we hit
    // a real key line (contains a top-level ':'), a closing bracket, a
    // comment-only line, or the end of input. Blank lines in between are
    // preserved as embedded blank lines rather than treated as separators.
    if (stop === rawLine.length && !inArray) {
      let pendingBlankLines = 0;
      while (this.pos < this.len && this.text[this.pos] === '\n') {
        const nextLineStart = this.pos + 1;
        const info = this.lineInfoAt(nextLineStart);
        if (info.isBlank) {
          pendingBlankLines++;
          this.pos = info.lineEnd;
          continue;
        }
        if (info.isClosing || info.hasColon || info.isCommentOnly) {
          break;
        }
        value += '\n'.repeat(pendingBlankLines + 1) + info.trimmedContent;
        pendingBlankLines = 0;
        this.pos = info.lineEnd;
      }
    }

    return this.coerceLiteral(value);
  }

  /**
   * Inspects the line starting at `pos` (assumed to be right after a
   * newline) without moving the parser's own position.
   */
  lineInfoAt(pos) {
    let lineEnd = this.text.indexOf('\n', pos);
    if (lineEnd === -1) lineEnd = this.len;
    const raw = this.text.slice(pos, lineEnd);
    const trimmed = raw.trim();
    if (trimmed === '') {
      return { isBlank: true, lineEnd };
    }
    const commentIdx = this.findLineCommentStart(raw);
    const beforeComment = commentIdx === -1 ? raw : raw.slice(0, commentIdx);
    // A block comment (`/* ... */`) can start or continue on this line even
    // though `findLineCommentStart` only recognizes '#'/'//'; treat any line
    // that begins with a comment marker of any kind as non-continuation so
    // we never swallow comments into a merged quoteless value.
    const isCommentOnly = beforeComment.trim() === '' || /^(\/\*|\*\/)/.test(trimmed);
    const isClosing = /^[}\]]/.test(trimmed);
    const hasColon = beforeComment.indexOf(':') !== -1;
    return {
      isBlank: false,
      isCommentOnly,
      isClosing,
      hasColon,
      lineEnd,
      trimmedContent: raw.replace(/^[ \t]+/, '').replace(/[ \t\r]+$/, ''),
    };
  }

  findLineCommentStart(line) {
    const hashIdx = line.indexOf('#');
    const slashIdx = line.indexOf('//');
    if (hashIdx === -1 && slashIdx === -1) return -1;
    if (hashIdx === -1) return slashIdx;
    if (slashIdx === -1) return hashIdx;
    return Math.min(hashIdx, slashIdx);
  }

  coerceLiteral(value) {
    const trimmed = value.trim();
    if (trimmed === 'true') return true;
    if (trimmed === 'false') return false;
    if (trimmed === 'null') return null;
    if (/^-?\d+$/.test(trimmed)) return parseInt(trimmed, 10);
    if (/^-?\d+\.\d+([eE][+-]?\d+)?$/.test(trimmed) || /^-?\d+[eE][+-]?\d+$/.test(trimmed)) {
      return parseFloat(trimmed);
    }
    return value;
  }
}

/**
 * Parses Hjson text into a plain JavaScript value.
 *
 * @param {string} text
 * @returns {*}
 */
function parse(text) {
  const parser = new Parser(text);
  return parser.parseRoot();
}

module.exports = { parse, ParseError };
