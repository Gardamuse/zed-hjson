# HJSON for Zed

A [Zed](https://zed.dev) extension that provides language support for [HJSON](https://hjson.github.io/) — the Human JSON format.

## Features

- **Syntax highlighting** — keys, strings, numbers, booleans, nulls, escape sequences, and comments (`#`, `//`, `/* */`)
- **Bracket matching** — automatic matching of `{}` and `[]`
- **Auto-indentation** — smart indentation inside objects and arrays
- **Auto-formatting** — formats `.hjson` files using the `hjson` CLI tool

## Requirements

For auto-formatting, install the `hjson` CLI tool:

```sh
npm install -g hjson
```

## Installation

Search for **HJSON** in Zed's extension panel (`zed: extensions`) and install it.

## Usage

Files with the `.hjson` extension are automatically detected. Use `editor: format` (`Alt+Shift+F` / `Option+Shift+F`) to format the current file.

## Grammar

This extension uses the [tree-sitter-json](https://github.com/tree-sitter/tree-sitter-json) grammar. Since HJSON is a superset of JSON, the JSON grammar covers the structural syntax. HJSON-specific features (comments, multiline strings, unquoted keys) are handled at the tokenizer level by the grammar's comment nodes.

## License

MIT
