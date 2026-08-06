#include "tree_sitter/parser.h"
#include <stdbool.h>
#include <wctype.h>

enum TokenType {
  UNQUOTED_KEY,
  UNQUOTED_VALUE_OBJECT,
  UNQUOTED_VALUE_ARRAY,
};

void *tree_sitter_hjson_external_scanner_create(void) { return NULL; }
void tree_sitter_hjson_external_scanner_destroy(void *payload) {}
unsigned tree_sitter_hjson_external_scanner_serialize(void *payload, char *buffer) { return 0; }
void tree_sitter_hjson_external_scanner_deserialize(void *payload, const char *buffer, unsigned length) {}

static bool is_forbidden_start(int32_t c) {
  return c == 0 || c == '{' || c == '}' || c == '[' || c == ']' ||
         c == '"' || c == '\'' || c == ':' || c == ',' || c == '#' ||
         c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

// Looks ahead (without affecting the token boundary) to see whether a ':'
// appears on the current line before a newline/EOF/closing bracket/comment.
// Consumes lexer input as a side effect (the caller only uses the boolean
// result; the actual token boundary is controlled separately via mark_end).
static bool peek_colon_follows(TSLexer *lexer) {
  for (;;) {
    int32_t c = lexer->lookahead;
    if (c == 0 || c == '\n' || c == '}' || c == ']' || c == '#') return false;
    if (c == '/') {
      lexer->advance(lexer, false);
      int32_t next = lexer->lookahead;
      if (next == '/' || next == '*') return false;
      continue;
    }
    if (c == ':') return true;
    lexer->advance(lexer, false);
  }
}

// Checks whether the character at the lexer's current position starts a
// comment ('#', '//' or '/*'). May advance the lexer by one character (past
// a lone '/') as a side effect when checking for '//'/'/*'; the caller must
// account for that consumed character when the result is false.
static bool peek_is_comment_start(TSLexer *lexer, bool *consumed_slash) {
  *consumed_slash = false;
  int32_t c = lexer->lookahead;
  if (c == '#') return true;
  if (c == '/') {
    lexer->advance(lexer, false);
    *consumed_slash = true;
    int32_t next = lexer->lookahead;
    return next == '/' || next == '*';
  }
  return false;
}

static void skip_leading_whitespace(TSLexer *lexer) {
  // Skip whitespace/newlines ourselves (marked as skipped trivia) instead
  // of relying on the grammar's `extras`: when this scanner is consulted at
  // a position that turns out not to produce a token, tree-sitter's
  // generic "unrecognized character" recovery consumes one raw byte
  // instead of retrying the extras regex, which can corrupt subsequent
  // scans. Doing the skipping inside the scanner avoids that entirely.
  while (lexer->lookahead == ' ' || lexer->lookahead == '\t' ||
         lexer->lookahead == '\n' || lexer->lookahead == '\r') {
    lexer->advance(lexer, true);
  }
}

static bool scan_key(TSLexer *lexer) {
  skip_leading_whitespace(lexer);
  if (is_forbidden_start(lexer->lookahead)) return false;

  bool consumed_any = false;
  for (;;) {
    int32_t c = lexer->lookahead;
    if (c == 0 || c == '\n') return false; // no ':' found on this line
    if (c == ':') {
      if (!consumed_any) return false;
      lexer->result_symbol = UNQUOTED_KEY;
      return true;
    }
    bool is_ws = (c == ' ' || c == '\t' || c == '\r');
    lexer->advance(lexer, false);
    consumed_any = true;
    if (!is_ws) lexer->mark_end(lexer);
  }
}

static bool scan_value(TSLexer *lexer, bool in_array) {
  skip_leading_whitespace(lexer);
  if (is_forbidden_start(lexer->lookahead)) return false;

  bool consumed_any = false;
  for (;;) {
    int32_t c = lexer->lookahead;
    if (c == 0 || c == '\n' || c == '}' || c == ']') break;
    bool consumed_slash = false;
    if (peek_is_comment_start(lexer, &consumed_slash)) break;
    if (consumed_slash) {
      // The '/' was not actually a comment start; include it in the value.
      consumed_any = true;
      lexer->mark_end(lexer);
      continue;
    }

    if (c == ',') {
      if (in_array) break;
      // Object-value mode: a comma only terminates the value when it is
      // actually separating this property from another one later on the
      // same line (i.e. a ':' appears before the next hard stop). Plain
      // prose commas (no following ':') are kept as part of the value.
      lexer->advance(lexer, false);
      if (peek_colon_follows(lexer)) break;
      consumed_any = true;
      lexer->mark_end(lexer);
      continue;
    }

    bool is_ws = (c == ' ' || c == '\t' || c == '\r');
    lexer->advance(lexer, false);
    consumed_any = true;
    if (!is_ws) lexer->mark_end(lexer);
  }

  if (!consumed_any) return false;
  lexer->result_symbol = in_array ? UNQUOTED_VALUE_ARRAY : UNQUOTED_VALUE_OBJECT;
  return true;
}

bool tree_sitter_hjson_external_scanner_scan(void *payload, TSLexer *lexer, const bool *valid_symbols) {
  if (valid_symbols[UNQUOTED_KEY]) {
    if (scan_key(lexer)) return true;
  }
  if (valid_symbols[UNQUOTED_VALUE_OBJECT]) {
    if (scan_value(lexer, false)) return true;
  }
  if (valid_symbols[UNQUOTED_VALUE_ARRAY]) {
    if (scan_value(lexer, true)) return true;
  }
  return false;
}
