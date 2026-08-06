; Object keys
(pair
  key: (_) @string.special.key)

; String values
(string) @string
(multiline_string) @string
(pair value: (unquoted_string) @string)
(array (unquoted_string) @string)
(document (unquoted_string) @string)

; Numbers
(number) @number

; Boolean and null literals
[
  (null)
  (true)
  (false)
] @constant.builtin

; Escape sequences inside strings
(escape_sequence) @string.escape

; Comments (HJSON supports #, //, and /* */ comments)
(comment) @comment

; Structural punctuation
["{" "}"] @punctuation.bracket
["[" "]"] @punctuation.bracket
[":"] @punctuation.delimiter
