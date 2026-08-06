/**
 * @file HJSON grammar for tree-sitter
 * A superset of JSON allowing unquoted keys, unquoted (quoteless) string
 * values, multiline ('''...''') strings, and #/// and /* *\/ comments.
 */

module.exports = grammar({
  name: 'hjson',

  extras: $ => [
    /[ \t\r\n]/,
    $.comment,
    ',',
  ],

  externals: $ => [
    $._unquoted_key,
    $._unquoted_value_object,
    $._unquoted_value_array,
  ],

  supertypes: $ => [
    $._value,
  ],

  rules: {
    document: $ => choice(
      alias(repeat1($.pair), $.object),
      repeat($._value),
    ),

    _value: $ => choice(
      $.object,
      $.array,
      $.number,
      $.string,
      $.multiline_string,
      $.true,
      $.false,
      $.null,
      alias($._unquoted_value_object, $.unquoted_string),
    ),

    // Value used inside an array element position: unquoted values here stop
    // at the first top-level comma.
    _array_value: $ => choice(
      $.object,
      $.array,
      $.number,
      $.string,
      $.multiline_string,
      $.true,
      $.false,
      $.null,
      alias($._unquoted_value_array, $.unquoted_string),
    ),

    object: $ => seq('{', repeat($.pair), '}'),

    pair: $ => seq(
      field('key', choice($.string, $.unquoted_key)),
      ':',
      field('value', $._pair_value),
    ),

    _pair_value: $ => choice(
      $.object,
      $.array,
      $.number,
      $.string,
      $.multiline_string,
      $.true,
      $.false,
      $.null,
      alias($._unquoted_value_object, $.unquoted_string),
    ),

    unquoted_key: $ => $._unquoted_key,

    array: $ => seq('[', repeat($._array_value), ']'),

    string: $ => choice(
      seq('"', '"'),
      seq('"', $._string_content, '"'),
    ),

    multiline_string: $ => seq(
      "'''",
      /[^']*(''?[^']+)*/,
      "'''",
    ),

    _string_content: $ => repeat1(choice(
      $.string_content,
      $.escape_sequence,
    )),

    string_content: _ => token.immediate(prec(1, /[^\\"\n]+/)),

    escape_sequence: _ => token.immediate(seq(
      '\\',
      /(\"|\\|\/|b|f|n|r|t|u)/,
    )),

    number: _ => {
      const decimalDigits = /\d+/;
      const signedInteger = seq(optional('-'), decimalDigits);
      const exponentPart = seq(choice('e', 'E'), signedInteger);

      const decimalIntegerLiteral = seq(
        optional('-'),
        choice(
          '0',
          seq(/[1-9]/, optional(decimalDigits)),
        ),
      );

      const decimalLiteral = choice(
        seq(decimalIntegerLiteral, '.', optional(decimalDigits), optional(exponentPart)),
        seq(decimalIntegerLiteral, optional(exponentPart)),
      );

      return token(decimalLiteral);
    },

    true: _ => 'true',

    false: _ => 'false',

    null: _ => 'null',

    comment: _ => token(choice(
      seq('#', /.*/),
      seq('//', /.*/),
      seq(
        '/*',
        /[^*]*\*+([^/*][^*]*\*+)*/,
        '/',
      ),
    )),
  },
});

