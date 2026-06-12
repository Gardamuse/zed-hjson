; Object keys
(pair
  key: (_) @string.special.key)

; String values
(string) @string

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
["," ":"] @punctuation.delimiter
