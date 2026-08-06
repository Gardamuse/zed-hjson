#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 65
#define LARGE_STATE_COUNT 11
#define SYMBOL_COUNT 33
#define ALIAS_COUNT 0
#define TOKEN_COUNT 19
#define EXTERNAL_TOKEN_COUNT 3
#define FIELD_COUNT 2
#define MAX_ALIAS_SEQUENCE_LENGTH 3
#define PRODUCTION_ID_COUNT 3

enum ts_symbol_identifiers {
  anon_sym_LBRACE = 1,
  anon_sym_RBRACE = 2,
  anon_sym_COLON = 3,
  anon_sym_LBRACK = 4,
  anon_sym_RBRACK = 5,
  anon_sym_DQUOTE = 6,
  anon_sym_SQUOTE_SQUOTE_SQUOTE = 7,
  aux_sym_multiline_string_token1 = 8,
  sym_string_content = 9,
  sym_escape_sequence = 10,
  sym_number = 11,
  sym_true = 12,
  sym_false = 13,
  sym_null = 14,
  sym_comment = 15,
  sym__unquoted_key = 16,
  sym__unquoted_value_object = 17,
  sym__unquoted_value_array = 18,
  sym_document = 19,
  sym__value = 20,
  sym__array_value = 21,
  sym_object = 22,
  sym_pair = 23,
  sym__pair_value = 24,
  sym_unquoted_key = 25,
  sym_array = 26,
  sym_string = 27,
  sym_multiline_string = 28,
  aux_sym__string_content = 29,
  aux_sym_document_repeat1 = 30,
  aux_sym_document_repeat2 = 31,
  aux_sym_array_repeat1 = 32,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_COLON] = ":",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_DQUOTE] = "\"",
  [anon_sym_SQUOTE_SQUOTE_SQUOTE] = "'''",
  [aux_sym_multiline_string_token1] = "multiline_string_token1",
  [sym_string_content] = "string_content",
  [sym_escape_sequence] = "escape_sequence",
  [sym_number] = "number",
  [sym_true] = "true",
  [sym_false] = "false",
  [sym_null] = "null",
  [sym_comment] = "comment",
  [sym__unquoted_key] = "_unquoted_key",
  [sym__unquoted_value_object] = "unquoted_string",
  [sym__unquoted_value_array] = "unquoted_string",
  [sym_document] = "document",
  [sym__value] = "_value",
  [sym__array_value] = "_array_value",
  [sym_object] = "object",
  [sym_pair] = "pair",
  [sym__pair_value] = "_pair_value",
  [sym_unquoted_key] = "unquoted_key",
  [sym_array] = "array",
  [sym_string] = "string",
  [sym_multiline_string] = "multiline_string",
  [aux_sym__string_content] = "_string_content",
  [aux_sym_document_repeat1] = "document_repeat1",
  [aux_sym_document_repeat2] = "document_repeat2",
  [aux_sym_array_repeat1] = "array_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [anon_sym_SQUOTE_SQUOTE_SQUOTE] = anon_sym_SQUOTE_SQUOTE_SQUOTE,
  [aux_sym_multiline_string_token1] = aux_sym_multiline_string_token1,
  [sym_string_content] = sym_string_content,
  [sym_escape_sequence] = sym_escape_sequence,
  [sym_number] = sym_number,
  [sym_true] = sym_true,
  [sym_false] = sym_false,
  [sym_null] = sym_null,
  [sym_comment] = sym_comment,
  [sym__unquoted_key] = sym__unquoted_key,
  [sym__unquoted_value_object] = sym__unquoted_value_object,
  [sym__unquoted_value_array] = sym__unquoted_value_object,
  [sym_document] = sym_document,
  [sym__value] = sym__value,
  [sym__array_value] = sym__array_value,
  [sym_object] = sym_object,
  [sym_pair] = sym_pair,
  [sym__pair_value] = sym__pair_value,
  [sym_unquoted_key] = sym_unquoted_key,
  [sym_array] = sym_array,
  [sym_string] = sym_string,
  [sym_multiline_string] = sym_multiline_string,
  [aux_sym__string_content] = aux_sym__string_content,
  [aux_sym_document_repeat1] = aux_sym_document_repeat1,
  [aux_sym_document_repeat2] = aux_sym_document_repeat2,
  [aux_sym_array_repeat1] = aux_sym_array_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SQUOTE_SQUOTE_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_multiline_string_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_string_content] = {
    .visible = true,
    .named = true,
  },
  [sym_escape_sequence] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_true] = {
    .visible = true,
    .named = true,
  },
  [sym_false] = {
    .visible = true,
    .named = true,
  },
  [sym_null] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym__unquoted_key] = {
    .visible = false,
    .named = true,
  },
  [sym__unquoted_value_object] = {
    .visible = true,
    .named = true,
  },
  [sym__unquoted_value_array] = {
    .visible = true,
    .named = true,
  },
  [sym_document] = {
    .visible = true,
    .named = true,
  },
  [sym__value] = {
    .visible = false,
    .named = true,
    .supertype = true,
  },
  [sym__array_value] = {
    .visible = false,
    .named = true,
  },
  [sym_object] = {
    .visible = true,
    .named = true,
  },
  [sym_pair] = {
    .visible = true,
    .named = true,
  },
  [sym__pair_value] = {
    .visible = false,
    .named = true,
  },
  [sym_unquoted_key] = {
    .visible = true,
    .named = true,
  },
  [sym_array] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_multiline_string] = {
    .visible = true,
    .named = true,
  },
  [aux_sym__string_content] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_document_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_document_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_array_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_key = 1,
  field_value = 2,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_key] = "key",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [2] = {.index = 0, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_key, 0},
    {field_value, 2},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
  [1] = {
    [0] = sym_object,
  },
};

static const uint16_t ts_non_terminal_alias_map[] = {
  aux_sym_document_repeat1, 2,
    aux_sym_document_repeat1,
    sym_object,
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 4,
  [6] = 6,
  [7] = 7,
  [8] = 6,
  [9] = 4,
  [10] = 6,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 15,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 19,
  [23] = 20,
  [24] = 14,
  [25] = 13,
  [26] = 21,
  [27] = 18,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 29,
  [32] = 32,
  [33] = 29,
  [34] = 32,
  [35] = 32,
  [36] = 18,
  [37] = 37,
  [38] = 20,
  [39] = 37,
  [40] = 40,
  [41] = 21,
  [42] = 15,
  [43] = 43,
  [44] = 19,
  [45] = 14,
  [46] = 13,
  [47] = 47,
  [48] = 48,
  [49] = 40,
  [50] = 37,
  [51] = 40,
  [52] = 37,
  [53] = 40,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 14,
  [58] = 54,
  [59] = 59,
  [60] = 54,
  [61] = 61,
  [62] = 13,
  [63] = 56,
  [64] = 56,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(27);
      ADVANCE_MAP(
        '"', 33,
        '#', 57,
        '\'', 6,
        '-', 12,
        '/', 8,
        '0', 47,
        ':', 30,
        '[', 31,
        '\\', 23,
        ']', 32,
        'f', 13,
        'n', 22,
        't', 19,
        '{', 28,
        '}', 29,
      );
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == ',') SKIP(26);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(48);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(2);
      if (lookahead == '"') ADVANCE(33);
      if (lookahead == '#') ADVANCE(45);
      if (lookahead == '/') ADVANCE(42);
      if (lookahead == '\\') ADVANCE(23);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == ',') ADVANCE(41);
      if (lookahead != 0) ADVANCE(45);
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(33);
      if (lookahead == '#') ADVANCE(57);
      if (lookahead == '/') ADVANCE(8);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == ',') SKIP(2);
      END_STATE();
    case 3:
      if (lookahead == '\'') ADVANCE(10);
      if (lookahead == '*') ADVANCE(39);
      if (lookahead != 0) ADVANCE(40);
      END_STATE();
    case 4:
      if (lookahead == '\'') ADVANCE(34);
      END_STATE();
    case 5:
      if (lookahead == '\'') ADVANCE(25);
      if (lookahead != 0) ADVANCE(38);
      END_STATE();
    case 6:
      if (lookahead == '\'') ADVANCE(4);
      END_STATE();
    case 7:
      if (lookahead == '\'') ADVANCE(3);
      if (lookahead == '*') ADVANCE(39);
      if (lookahead != 0) ADVANCE(40);
      END_STATE();
    case 8:
      if (lookahead == '*') ADVANCE(10);
      if (lookahead == '/') ADVANCE(57);
      END_STATE();
    case 9:
      if (lookahead == '*') ADVANCE(9);
      if (lookahead == '/') ADVANCE(54);
      if (lookahead != 0) ADVANCE(10);
      END_STATE();
    case 10:
      if (lookahead == '*') ADVANCE(9);
      if (lookahead != 0) ADVANCE(10);
      END_STATE();
    case 11:
      if (lookahead == '-') ADVANCE(24);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(50);
      END_STATE();
    case 12:
      if (lookahead == '0') ADVANCE(47);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(48);
      END_STATE();
    case 13:
      if (lookahead == 'a') ADVANCE(16);
      END_STATE();
    case 14:
      if (lookahead == 'e') ADVANCE(51);
      END_STATE();
    case 15:
      if (lookahead == 'e') ADVANCE(52);
      END_STATE();
    case 16:
      if (lookahead == 'l') ADVANCE(20);
      END_STATE();
    case 17:
      if (lookahead == 'l') ADVANCE(53);
      END_STATE();
    case 18:
      if (lookahead == 'l') ADVANCE(17);
      END_STATE();
    case 19:
      if (lookahead == 'r') ADVANCE(21);
      END_STATE();
    case 20:
      if (lookahead == 's') ADVANCE(15);
      END_STATE();
    case 21:
      if (lookahead == 'u') ADVANCE(14);
      END_STATE();
    case 22:
      if (lookahead == 'u') ADVANCE(18);
      END_STATE();
    case 23:
      ADVANCE_MAP(
        '"', 46,
        '/', 46,
        '\\', 46,
        'b', 46,
        'f', 46,
        'n', 46,
        'r', 46,
        't', 46,
        'u', 46,
      );
      END_STATE();
    case 24:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(50);
      END_STATE();
    case 25:
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(38);
      END_STATE();
    case 26:
      if (eof) ADVANCE(27);
      ADVANCE_MAP(
        '"', 33,
        '#', 57,
        '\'', 6,
        '-', 12,
        '/', 8,
        '0', 47,
        ':', 30,
        '[', 31,
        ']', 32,
        'f', 13,
        'n', 22,
        't', 19,
        '{', 28,
        '}', 29,
      );
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == ',') SKIP(26);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(48);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_SQUOTE_SQUOTE_SQUOTE);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(aux_sym_multiline_string_token1);
      if (lookahead == '\n') ADVANCE(38);
      if (lookahead == '\'') ADVANCE(56);
      if (lookahead != 0) ADVANCE(35);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(aux_sym_multiline_string_token1);
      if (lookahead == '#') ADVANCE(35);
      if (lookahead == '\'') ADVANCE(5);
      if (lookahead == '/') ADVANCE(37);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == ',') ADVANCE(36);
      if (lookahead != 0) ADVANCE(38);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(aux_sym_multiline_string_token1);
      if (lookahead == '\'') ADVANCE(5);
      if (lookahead == '*') ADVANCE(40);
      if (lookahead == '/') ADVANCE(35);
      if (lookahead != 0) ADVANCE(38);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(aux_sym_multiline_string_token1);
      if (lookahead == '\'') ADVANCE(5);
      if (lookahead != 0) ADVANCE(38);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(aux_sym_multiline_string_token1);
      if (lookahead == '\'') ADVANCE(7);
      if (lookahead == '*') ADVANCE(39);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead != 0) ADVANCE(40);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(aux_sym_multiline_string_token1);
      if (lookahead == '\'') ADVANCE(7);
      if (lookahead == '*') ADVANCE(39);
      if (lookahead != 0) ADVANCE(40);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == '#') ADVANCE(45);
      if (lookahead == '/') ADVANCE(42);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == ',') ADVANCE(41);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '#' &&
          lookahead != '\\') ADVANCE(45);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == '*') ADVANCE(44);
      if (lookahead == '/') ADVANCE(45);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(45);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == '*') ADVANCE(43);
      if (lookahead == '/') ADVANCE(45);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(44);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == '*') ADVANCE(43);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(44);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(45);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(49);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(11);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(49);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(11);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(48);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(11);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(49);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(50);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(sym_true);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(sym_false);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(sym_null);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\n') ADVANCE(38);
      if (lookahead == '\'') ADVANCE(57);
      if (lookahead != 0) ADVANCE(35);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\n') ADVANCE(38);
      if (lookahead == '\'') ADVANCE(55);
      if (lookahead != 0) ADVANCE(35);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(57);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0, .external_lex_state = 1},
  [1] = {.lex_state = 0, .external_lex_state = 2},
  [2] = {.lex_state = 0, .external_lex_state = 3},
  [3] = {.lex_state = 0, .external_lex_state = 4},
  [4] = {.lex_state = 0, .external_lex_state = 3},
  [5] = {.lex_state = 0, .external_lex_state = 3},
  [6] = {.lex_state = 0, .external_lex_state = 3},
  [7] = {.lex_state = 0, .external_lex_state = 4},
  [8] = {.lex_state = 0, .external_lex_state = 3},
  [9] = {.lex_state = 0, .external_lex_state = 3},
  [10] = {.lex_state = 0, .external_lex_state = 3},
  [11] = {.lex_state = 0, .external_lex_state = 4},
  [12] = {.lex_state = 0, .external_lex_state = 4},
  [13] = {.lex_state = 0, .external_lex_state = 4},
  [14] = {.lex_state = 0, .external_lex_state = 4},
  [15] = {.lex_state = 0, .external_lex_state = 4},
  [16] = {.lex_state = 0, .external_lex_state = 4},
  [17] = {.lex_state = 0, .external_lex_state = 3},
  [18] = {.lex_state = 0, .external_lex_state = 3},
  [19] = {.lex_state = 0, .external_lex_state = 4},
  [20] = {.lex_state = 0, .external_lex_state = 3},
  [21] = {.lex_state = 0, .external_lex_state = 3},
  [22] = {.lex_state = 0, .external_lex_state = 3},
  [23] = {.lex_state = 0, .external_lex_state = 4},
  [24] = {.lex_state = 0, .external_lex_state = 3},
  [25] = {.lex_state = 0, .external_lex_state = 3},
  [26] = {.lex_state = 0, .external_lex_state = 4},
  [27] = {.lex_state = 0, .external_lex_state = 4},
  [28] = {.lex_state = 0, .external_lex_state = 5},
  [29] = {.lex_state = 0, .external_lex_state = 5},
  [30] = {.lex_state = 0, .external_lex_state = 5},
  [31] = {.lex_state = 0, .external_lex_state = 5},
  [32] = {.lex_state = 0, .external_lex_state = 5},
  [33] = {.lex_state = 0, .external_lex_state = 5},
  [34] = {.lex_state = 0, .external_lex_state = 5},
  [35] = {.lex_state = 0, .external_lex_state = 5},
  [36] = {.lex_state = 0, .external_lex_state = 5},
  [37] = {.lex_state = 1},
  [38] = {.lex_state = 0, .external_lex_state = 5},
  [39] = {.lex_state = 1},
  [40] = {.lex_state = 1},
  [41] = {.lex_state = 0, .external_lex_state = 5},
  [42] = {.lex_state = 0, .external_lex_state = 5},
  [43] = {.lex_state = 1},
  [44] = {.lex_state = 0, .external_lex_state = 5},
  [45] = {.lex_state = 0, .external_lex_state = 5},
  [46] = {.lex_state = 0, .external_lex_state = 5},
  [47] = {.lex_state = 0, .external_lex_state = 5},
  [48] = {.lex_state = 0, .external_lex_state = 5},
  [49] = {.lex_state = 1},
  [50] = {.lex_state = 1},
  [51] = {.lex_state = 1},
  [52] = {.lex_state = 1},
  [53] = {.lex_state = 1},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 36},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 0},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 36},
  [64] = {.lex_state = 36},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_SQUOTE_SQUOTE_SQUOTE] = ACTIONS(1),
    [sym_escape_sequence] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [sym_true] = ACTIONS(1),
    [sym_false] = ACTIONS(1),
    [sym_null] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
    [sym__unquoted_key] = ACTIONS(1),
    [sym__unquoted_value_object] = ACTIONS(1),
    [sym__unquoted_value_array] = ACTIONS(1),
  },
  [1] = {
    [sym_document] = STATE(59),
    [sym__value] = STATE(3),
    [sym_object] = STATE(16),
    [sym_pair] = STATE(48),
    [sym_unquoted_key] = STATE(61),
    [sym_array] = STATE(16),
    [sym_string] = STATE(12),
    [sym_multiline_string] = STATE(16),
    [aux_sym_document_repeat1] = STATE(30),
    [aux_sym_document_repeat2] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_LBRACE] = ACTIONS(7),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_DQUOTE] = ACTIONS(11),
    [anon_sym_SQUOTE_SQUOTE_SQUOTE] = ACTIONS(13),
    [sym_number] = ACTIONS(15),
    [sym_true] = ACTIONS(15),
    [sym_false] = ACTIONS(15),
    [sym_null] = ACTIONS(15),
    [sym_comment] = ACTIONS(3),
    [sym__unquoted_key] = ACTIONS(17),
    [sym__unquoted_value_object] = ACTIONS(15),
  },
  [2] = {
    [sym__array_value] = STATE(2),
    [sym_object] = STATE(2),
    [sym_array] = STATE(2),
    [sym_string] = STATE(2),
    [sym_multiline_string] = STATE(2),
    [aux_sym_array_repeat1] = STATE(2),
    [anon_sym_LBRACE] = ACTIONS(19),
    [anon_sym_LBRACK] = ACTIONS(22),
    [anon_sym_RBRACK] = ACTIONS(25),
    [anon_sym_DQUOTE] = ACTIONS(27),
    [anon_sym_SQUOTE_SQUOTE_SQUOTE] = ACTIONS(30),
    [sym_number] = ACTIONS(33),
    [sym_true] = ACTIONS(33),
    [sym_false] = ACTIONS(33),
    [sym_null] = ACTIONS(33),
    [sym_comment] = ACTIONS(3),
    [sym__unquoted_value_array] = ACTIONS(33),
  },
  [3] = {
    [sym__value] = STATE(7),
    [sym_object] = STATE(16),
    [sym_array] = STATE(16),
    [sym_string] = STATE(16),
    [sym_multiline_string] = STATE(16),
    [aux_sym_document_repeat2] = STATE(7),
    [ts_builtin_sym_end] = ACTIONS(36),
    [anon_sym_LBRACE] = ACTIONS(7),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_DQUOTE] = ACTIONS(11),
    [anon_sym_SQUOTE_SQUOTE_SQUOTE] = ACTIONS(13),
    [sym_number] = ACTIONS(15),
    [sym_true] = ACTIONS(15),
    [sym_false] = ACTIONS(15),
    [sym_null] = ACTIONS(15),
    [sym_comment] = ACTIONS(3),
    [sym__unquoted_value_object] = ACTIONS(15),
  },
  [4] = {
    [sym__array_value] = STATE(2),
    [sym_object] = STATE(2),
    [sym_array] = STATE(2),
    [sym_string] = STATE(2),
    [sym_multiline_string] = STATE(2),
    [aux_sym_array_repeat1] = STATE(2),
    [anon_sym_LBRACE] = ACTIONS(38),
    [anon_sym_LBRACK] = ACTIONS(40),
    [anon_sym_RBRACK] = ACTIONS(42),
    [anon_sym_DQUOTE] = ACTIONS(44),
    [anon_sym_SQUOTE_SQUOTE_SQUOTE] = ACTIONS(46),
    [sym_number] = ACTIONS(48),
    [sym_true] = ACTIONS(48),
    [sym_false] = ACTIONS(48),
    [sym_null] = ACTIONS(48),
    [sym_comment] = ACTIONS(3),
    [sym__unquoted_value_array] = ACTIONS(48),
  },
  [5] = {
    [sym__array_value] = STATE(2),
    [sym_object] = STATE(2),
    [sym_array] = STATE(2),
    [sym_string] = STATE(2),
    [sym_multiline_string] = STATE(2),
    [aux_sym_array_repeat1] = STATE(2),
    [anon_sym_LBRACE] = ACTIONS(38),
    [anon_sym_LBRACK] = ACTIONS(40),
    [anon_sym_RBRACK] = ACTIONS(50),
    [anon_sym_DQUOTE] = ACTIONS(44),
    [anon_sym_SQUOTE_SQUOTE_SQUOTE] = ACTIONS(46),
    [sym_number] = ACTIONS(48),
    [sym_true] = ACTIONS(48),
    [sym_false] = ACTIONS(48),
    [sym_null] = ACTIONS(48),
    [sym_comment] = ACTIONS(3),
    [sym__unquoted_value_array] = ACTIONS(48),
  },
  [6] = {
    [sym__array_value] = STATE(4),
    [sym_object] = STATE(4),
    [sym_array] = STATE(4),
    [sym_string] = STATE(4),
    [sym_multiline_string] = STATE(4),
    [aux_sym_array_repeat1] = STATE(4),
    [anon_sym_LBRACE] = ACTIONS(38),
    [anon_sym_LBRACK] = ACTIONS(40),
    [anon_sym_RBRACK] = ACTIONS(52),
    [anon_sym_DQUOTE] = ACTIONS(44),
    [anon_sym_SQUOTE_SQUOTE_SQUOTE] = ACTIONS(46),
    [sym_number] = ACTIONS(54),
    [sym_true] = ACTIONS(54),
    [sym_false] = ACTIONS(54),
    [sym_null] = ACTIONS(54),
    [sym_comment] = ACTIONS(3),
    [sym__unquoted_value_array] = ACTIONS(54),
  },
  [7] = {
    [sym__value] = STATE(7),
    [sym_object] = STATE(16),
    [sym_array] = STATE(16),
    [sym_string] = STATE(16),
    [sym_multiline_string] = STATE(16),
    [aux_sym_document_repeat2] = STATE(7),
    [ts_builtin_sym_end] = ACTIONS(56),
    [anon_sym_LBRACE] = ACTIONS(58),
    [anon_sym_LBRACK] = ACTIONS(61),
    [anon_sym_DQUOTE] = ACTIONS(64),
    [anon_sym_SQUOTE_SQUOTE_SQUOTE] = ACTIONS(67),
    [sym_number] = ACTIONS(70),
    [sym_true] = ACTIONS(70),
    [sym_false] = ACTIONS(70),
    [sym_null] = ACTIONS(70),
    [sym_comment] = ACTIONS(3),
    [sym__unquoted_value_object] = ACTIONS(70),
  },
  [8] = {
    [sym__array_value] = STATE(9),
    [sym_object] = STATE(9),
    [sym_array] = STATE(9),
    [sym_string] = STATE(9),
    [sym_multiline_string] = STATE(9),
    [aux_sym_array_repeat1] = STATE(9),
    [anon_sym_LBRACE] = ACTIONS(38),
    [anon_sym_LBRACK] = ACTIONS(40),
    [anon_sym_RBRACK] = ACTIONS(73),
    [anon_sym_DQUOTE] = ACTIONS(44),
    [anon_sym_SQUOTE_SQUOTE_SQUOTE] = ACTIONS(46),
    [sym_number] = ACTIONS(75),
    [sym_true] = ACTIONS(75),
    [sym_false] = ACTIONS(75),
    [sym_null] = ACTIONS(75),
    [sym_comment] = ACTIONS(3),
    [sym__unquoted_value_array] = ACTIONS(75),
  },
  [9] = {
    [sym__array_value] = STATE(2),
    [sym_object] = STATE(2),
    [sym_array] = STATE(2),
    [sym_string] = STATE(2),
    [sym_multiline_string] = STATE(2),
    [aux_sym_array_repeat1] = STATE(2),
    [anon_sym_LBRACE] = ACTIONS(38),
    [anon_sym_LBRACK] = ACTIONS(40),
    [anon_sym_RBRACK] = ACTIONS(77),
    [anon_sym_DQUOTE] = ACTIONS(44),
    [anon_sym_SQUOTE_SQUOTE_SQUOTE] = ACTIONS(46),
    [sym_number] = ACTIONS(48),
    [sym_true] = ACTIONS(48),
    [sym_false] = ACTIONS(48),
    [sym_null] = ACTIONS(48),
    [sym_comment] = ACTIONS(3),
    [sym__unquoted_value_array] = ACTIONS(48),
  },
  [10] = {
    [sym__array_value] = STATE(5),
    [sym_object] = STATE(5),
    [sym_array] = STATE(5),
    [sym_string] = STATE(5),
    [sym_multiline_string] = STATE(5),
    [aux_sym_array_repeat1] = STATE(5),
    [anon_sym_LBRACE] = ACTIONS(38),
    [anon_sym_LBRACK] = ACTIONS(40),
    [anon_sym_RBRACK] = ACTIONS(79),
    [anon_sym_DQUOTE] = ACTIONS(44),
    [anon_sym_SQUOTE_SQUOTE_SQUOTE] = ACTIONS(46),
    [sym_number] = ACTIONS(81),
    [sym_true] = ACTIONS(81),
    [sym_false] = ACTIONS(81),
    [sym_null] = ACTIONS(81),
    [sym_comment] = ACTIONS(3),
    [sym__unquoted_value_array] = ACTIONS(81),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(83), 1,
      anon_sym_LBRACE,
    ACTIONS(85), 1,
      anon_sym_LBRACK,
    ACTIONS(87), 1,
      anon_sym_DQUOTE,
    ACTIONS(89), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
    ACTIONS(91), 5,
      sym__unquoted_value_object,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(47), 5,
      sym_object,
      sym__pair_value,
      sym_array,
      sym_string,
      sym_multiline_string,
  [30] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(95), 1,
      anon_sym_COLON,
    ACTIONS(93), 10,
      sym__unquoted_value_object,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [49] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 11,
      sym__unquoted_value_object,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_COLON,
      anon_sym_LBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [66] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(99), 11,
      sym__unquoted_value_object,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_COLON,
      anon_sym_LBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [83] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(101), 10,
      sym__unquoted_value_object,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [99] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 10,
      sym__unquoted_value_object,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [115] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(101), 10,
      sym__unquoted_value_array,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [131] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 10,
      sym__unquoted_value_array,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [147] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(105), 10,
      sym__unquoted_value_object,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [163] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 10,
      sym__unquoted_value_array,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [179] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(109), 10,
      sym__unquoted_value_array,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [195] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(105), 10,
      sym__unquoted_value_array,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [211] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 10,
      sym__unquoted_value_object,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [227] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(99), 10,
      sym__unquoted_value_array,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [243] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 10,
      sym__unquoted_value_array,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [259] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(109), 10,
      sym__unquoted_value_object,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [275] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 10,
      sym__unquoted_value_object,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_LBRACK,
      anon_sym_DQUOTE,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
  [291] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(113), 1,
      anon_sym_DQUOTE,
    ACTIONS(116), 1,
      sym__unquoted_key,
    STATE(28), 1,
      aux_sym_document_repeat1,
    STATE(48), 1,
      sym_pair,
    ACTIONS(111), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
    STATE(61), 2,
      sym_unquoted_key,
      sym_string,
  [315] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      sym__unquoted_key,
    ACTIONS(119), 1,
      anon_sym_RBRACE,
    ACTIONS(121), 1,
      anon_sym_DQUOTE,
    STATE(34), 1,
      aux_sym_document_repeat1,
    STATE(48), 1,
      sym_pair,
    STATE(61), 2,
      sym_unquoted_key,
      sym_string,
  [338] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      sym__unquoted_key,
    ACTIONS(121), 1,
      anon_sym_DQUOTE,
    ACTIONS(123), 1,
      ts_builtin_sym_end,
    STATE(28), 1,
      aux_sym_document_repeat1,
    STATE(48), 1,
      sym_pair,
    STATE(61), 2,
      sym_unquoted_key,
      sym_string,
  [361] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      sym__unquoted_key,
    ACTIONS(121), 1,
      anon_sym_DQUOTE,
    ACTIONS(125), 1,
      anon_sym_RBRACE,
    STATE(32), 1,
      aux_sym_document_repeat1,
    STATE(48), 1,
      sym_pair,
    STATE(61), 2,
      sym_unquoted_key,
      sym_string,
  [384] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      sym__unquoted_key,
    ACTIONS(121), 1,
      anon_sym_DQUOTE,
    ACTIONS(127), 1,
      anon_sym_RBRACE,
    STATE(28), 1,
      aux_sym_document_repeat1,
    STATE(48), 1,
      sym_pair,
    STATE(61), 2,
      sym_unquoted_key,
      sym_string,
  [407] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      sym__unquoted_key,
    ACTIONS(121), 1,
      anon_sym_DQUOTE,
    ACTIONS(129), 1,
      anon_sym_RBRACE,
    STATE(35), 1,
      aux_sym_document_repeat1,
    STATE(48), 1,
      sym_pair,
    STATE(61), 2,
      sym_unquoted_key,
      sym_string,
  [430] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      sym__unquoted_key,
    ACTIONS(121), 1,
      anon_sym_DQUOTE,
    ACTIONS(131), 1,
      anon_sym_RBRACE,
    STATE(28), 1,
      aux_sym_document_repeat1,
    STATE(48), 1,
      sym_pair,
    STATE(61), 2,
      sym_unquoted_key,
      sym_string,
  [453] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      sym__unquoted_key,
    ACTIONS(121), 1,
      anon_sym_DQUOTE,
    ACTIONS(133), 1,
      anon_sym_RBRACE,
    STATE(28), 1,
      aux_sym_document_repeat1,
    STATE(48), 1,
      sym_pair,
    STATE(61), 2,
      sym_unquoted_key,
      sym_string,
  [476] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 4,
      sym__unquoted_key,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_DQUOTE,
  [486] = 4,
    ACTIONS(135), 1,
      anon_sym_DQUOTE,
    ACTIONS(139), 1,
      sym_comment,
    STATE(49), 1,
      aux_sym__string_content,
    ACTIONS(137), 2,
      sym_string_content,
      sym_escape_sequence,
  [500] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 4,
      sym__unquoted_key,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_DQUOTE,
  [510] = 4,
    ACTIONS(139), 1,
      sym_comment,
    ACTIONS(141), 1,
      anon_sym_DQUOTE,
    STATE(40), 1,
      aux_sym__string_content,
    ACTIONS(143), 2,
      sym_string_content,
      sym_escape_sequence,
  [524] = 4,
    ACTIONS(139), 1,
      sym_comment,
    ACTIONS(145), 1,
      anon_sym_DQUOTE,
    STATE(43), 1,
      aux_sym__string_content,
    ACTIONS(147), 2,
      sym_string_content,
      sym_escape_sequence,
  [538] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(109), 4,
      sym__unquoted_key,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_DQUOTE,
  [548] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(101), 4,
      sym__unquoted_key,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_DQUOTE,
  [558] = 4,
    ACTIONS(139), 1,
      sym_comment,
    ACTIONS(149), 1,
      anon_sym_DQUOTE,
    STATE(43), 1,
      aux_sym__string_content,
    ACTIONS(151), 2,
      sym_string_content,
      sym_escape_sequence,
  [572] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(105), 4,
      sym__unquoted_key,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_DQUOTE,
  [582] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(99), 4,
      sym__unquoted_key,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_DQUOTE,
  [592] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 4,
      sym__unquoted_key,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_DQUOTE,
  [602] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(154), 4,
      sym__unquoted_key,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_DQUOTE,
  [612] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(156), 4,
      sym__unquoted_key,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_DQUOTE,
  [622] = 4,
    ACTIONS(139), 1,
      sym_comment,
    ACTIONS(158), 1,
      anon_sym_DQUOTE,
    STATE(43), 1,
      aux_sym__string_content,
    ACTIONS(147), 2,
      sym_string_content,
      sym_escape_sequence,
  [636] = 4,
    ACTIONS(139), 1,
      sym_comment,
    ACTIONS(160), 1,
      anon_sym_DQUOTE,
    STATE(51), 1,
      aux_sym__string_content,
    ACTIONS(162), 2,
      sym_string_content,
      sym_escape_sequence,
  [650] = 4,
    ACTIONS(139), 1,
      sym_comment,
    ACTIONS(164), 1,
      anon_sym_DQUOTE,
    STATE(43), 1,
      aux_sym__string_content,
    ACTIONS(147), 2,
      sym_string_content,
      sym_escape_sequence,
  [664] = 4,
    ACTIONS(139), 1,
      sym_comment,
    ACTIONS(166), 1,
      anon_sym_DQUOTE,
    STATE(53), 1,
      aux_sym__string_content,
    ACTIONS(168), 2,
      sym_string_content,
      sym_escape_sequence,
  [678] = 4,
    ACTIONS(139), 1,
      sym_comment,
    ACTIONS(170), 1,
      anon_sym_DQUOTE,
    STATE(43), 1,
      aux_sym__string_content,
    ACTIONS(147), 2,
      sym_string_content,
      sym_escape_sequence,
  [692] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(172), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
  [699] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(174), 1,
      anon_sym_COLON,
  [706] = 2,
    ACTIONS(139), 1,
      sym_comment,
    ACTIONS(176), 1,
      aux_sym_multiline_string_token1,
  [713] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(99), 1,
      anon_sym_COLON,
  [720] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(178), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
  [727] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(180), 1,
      ts_builtin_sym_end,
  [734] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(182), 1,
      anon_sym_SQUOTE_SQUOTE_SQUOTE,
  [741] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(95), 1,
      anon_sym_COLON,
  [748] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 1,
      anon_sym_COLON,
  [755] = 2,
    ACTIONS(139), 1,
      sym_comment,
    ACTIONS(184), 1,
      aux_sym_multiline_string_token1,
  [762] = 2,
    ACTIONS(139), 1,
      sym_comment,
    ACTIONS(186), 1,
      aux_sym_multiline_string_token1,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(11)] = 0,
  [SMALL_STATE(12)] = 30,
  [SMALL_STATE(13)] = 49,
  [SMALL_STATE(14)] = 66,
  [SMALL_STATE(15)] = 83,
  [SMALL_STATE(16)] = 99,
  [SMALL_STATE(17)] = 115,
  [SMALL_STATE(18)] = 131,
  [SMALL_STATE(19)] = 147,
  [SMALL_STATE(20)] = 163,
  [SMALL_STATE(21)] = 179,
  [SMALL_STATE(22)] = 195,
  [SMALL_STATE(23)] = 211,
  [SMALL_STATE(24)] = 227,
  [SMALL_STATE(25)] = 243,
  [SMALL_STATE(26)] = 259,
  [SMALL_STATE(27)] = 275,
  [SMALL_STATE(28)] = 291,
  [SMALL_STATE(29)] = 315,
  [SMALL_STATE(30)] = 338,
  [SMALL_STATE(31)] = 361,
  [SMALL_STATE(32)] = 384,
  [SMALL_STATE(33)] = 407,
  [SMALL_STATE(34)] = 430,
  [SMALL_STATE(35)] = 453,
  [SMALL_STATE(36)] = 476,
  [SMALL_STATE(37)] = 486,
  [SMALL_STATE(38)] = 500,
  [SMALL_STATE(39)] = 510,
  [SMALL_STATE(40)] = 524,
  [SMALL_STATE(41)] = 538,
  [SMALL_STATE(42)] = 548,
  [SMALL_STATE(43)] = 558,
  [SMALL_STATE(44)] = 572,
  [SMALL_STATE(45)] = 582,
  [SMALL_STATE(46)] = 592,
  [SMALL_STATE(47)] = 602,
  [SMALL_STATE(48)] = 612,
  [SMALL_STATE(49)] = 622,
  [SMALL_STATE(50)] = 636,
  [SMALL_STATE(51)] = 650,
  [SMALL_STATE(52)] = 664,
  [SMALL_STATE(53)] = 678,
  [SMALL_STATE(54)] = 692,
  [SMALL_STATE(55)] = 699,
  [SMALL_STATE(56)] = 706,
  [SMALL_STATE(57)] = 713,
  [SMALL_STATE(58)] = 720,
  [SMALL_STATE(59)] = 727,
  [SMALL_STATE(60)] = 734,
  [SMALL_STATE(61)] = 741,
  [SMALL_STATE(62)] = 748,
  [SMALL_STATE(63)] = 755,
  [SMALL_STATE(64)] = 762,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_document, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [19] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0), SHIFT_REPEAT(31),
  [22] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0), SHIFT_REPEAT(8),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0),
  [27] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0), SHIFT_REPEAT(50),
  [30] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0), SHIFT_REPEAT(63),
  [33] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0), SHIFT_REPEAT(2),
  [36] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_document, 1, 0, 0),
  [38] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [40] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [42] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [44] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [46] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [48] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [50] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [52] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [56] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_document_repeat2, 2, 0, 0),
  [58] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat2, 2, 0, 0), SHIFT_REPEAT(29),
  [61] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat2, 2, 0, 0), SHIFT_REPEAT(6),
  [64] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat2, 2, 0, 0), SHIFT_REPEAT(39),
  [67] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat2, 2, 0, 0), SHIFT_REPEAT(56),
  [70] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat2, 2, 0, 0), SHIFT_REPEAT(16),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [75] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [77] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [79] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [81] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [83] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [85] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [87] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__value, 1, 0, 0),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3, 0, 0),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 2, 0, 0),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 3, 0, 0),
  [103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 2, 0, 0),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_multiline_string, 3, 0, 0),
  [107] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 2, 0, 0),
  [109] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 3, 0, 0),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0),
  [113] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(37),
  [116] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(55),
  [119] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_document, 1, 0, 1),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [127] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [129] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [131] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [133] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [135] = {.entry = {.count = 1, .reusable = false}}, SHIFT(57),
  [137] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [139] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [141] = {.entry = {.count = 1, .reusable = false}}, SHIFT(14),
  [143] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [145] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [147] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [149] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__string_content, 2, 0, 0),
  [151] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__string_content, 2, 0, 0), SHIFT_REPEAT(43),
  [154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pair, 3, 0, 2),
  [156] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 1, 0, 0),
  [158] = {.entry = {.count = 1, .reusable = false}}, SHIFT(62),
  [160] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [162] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [164] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [166] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [168] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [170] = {.entry = {.count = 1, .reusable = false}}, SHIFT(46),
  [172] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [174] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unquoted_key, 1, 0, 0),
  [176] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [180] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [182] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [184] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [186] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
};

enum ts_external_scanner_symbol_identifiers {
  ts_external_token__unquoted_key = 0,
  ts_external_token__unquoted_value_object = 1,
  ts_external_token__unquoted_value_array = 2,
};

static const TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {
  [ts_external_token__unquoted_key] = sym__unquoted_key,
  [ts_external_token__unquoted_value_object] = sym__unquoted_value_object,
  [ts_external_token__unquoted_value_array] = sym__unquoted_value_array,
};

static const bool ts_external_scanner_states[6][EXTERNAL_TOKEN_COUNT] = {
  [1] = {
    [ts_external_token__unquoted_key] = true,
    [ts_external_token__unquoted_value_object] = true,
    [ts_external_token__unquoted_value_array] = true,
  },
  [2] = {
    [ts_external_token__unquoted_key] = true,
    [ts_external_token__unquoted_value_object] = true,
  },
  [3] = {
    [ts_external_token__unquoted_value_array] = true,
  },
  [4] = {
    [ts_external_token__unquoted_value_object] = true,
  },
  [5] = {
    [ts_external_token__unquoted_key] = true,
  },
};

#ifdef __cplusplus
extern "C" {
#endif
void *tree_sitter_hjson_external_scanner_create(void);
void tree_sitter_hjson_external_scanner_destroy(void *);
bool tree_sitter_hjson_external_scanner_scan(void *, TSLexer *, const bool *);
unsigned tree_sitter_hjson_external_scanner_serialize(void *, char *);
void tree_sitter_hjson_external_scanner_deserialize(void *, const char *, unsigned);

#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_hjson(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .external_scanner = {
      &ts_external_scanner_states[0][0],
      ts_external_scanner_symbol_map,
      tree_sitter_hjson_external_scanner_create,
      tree_sitter_hjson_external_scanner_destroy,
      tree_sitter_hjson_external_scanner_scan,
      tree_sitter_hjson_external_scanner_serialize,
      tree_sitter_hjson_external_scanner_deserialize,
    },
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
