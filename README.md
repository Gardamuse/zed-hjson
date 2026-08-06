# HJSON for Zed

A [Zed](https://zed.dev) extension that provides language support for [HJSON](https://hjson.github.io/) — the Human JSON format.

## Features

- **Syntax highlighting** — keys, strings, numbers, booleans, nulls, escape sequences, and comments (`#`, `//`, `/* */`)
- **Bracket matching** — automatic matching of `{}` and `[]`
- **Auto-indentation** — smart indentation inside objects and arrays
- **Auto-formatting** — formats `.hjson` files using a built-in language server bundled with this extension (no external CLI to install), quoting strings and auto-detecting multiline strings by default

## Requirements

Auto-formatting is powered by a small Node.js-based language server that ships with this extension. Zed runs it automatically using its own bundled Node runtime, so no extra installation is required.

## Installation

Search for **HJSON** in Zed's extension panel (`zed: extensions`) and install it.

## Usage

Files with the `.hjson` extension are automatically detected. Use `editor: format` (`Alt+Shift+F` / `Option+Shift+F`) to format the current file.

### Auto-format on save

To enable auto-formatting on save, add the following to your Zed `settings.json` (`zed: open settings`):

```json
{
  "languages": {
    "HJSON": {
      "format_on_save": "on",
      "formatter": "language_server"
    }
  }
}
```

The `"formatter": "language_server"` line is **required** — without it, Zed does not know to use this extension's bundled language server for formatting, and `format_on_save`/`editor: format` will effectively do nothing (which looks like formatting "not working" or strings never getting quoted, even though the language server itself is correct).

If you already had a `"formatter": { "external": { "command": "hjson", ... } }` block from an older version of this README (which called the now-removed external `hjson` CLI), remove it and replace it with `"formatter": "language_server"` as shown above — leaving the old external formatter configured will keep invoking the old, buggy `hjson` CLI instead of this extension's built-in formatter, which is why quoting may still appear not to work after upgrading/reinstalling.

### Formatting behavior

This extension ships its own Hjson parser and formatter (see `server/parser.js` and `server/formatter.js`) instead of relying on the `hjson` npm package, which had a bug where quoting strings silently disabled multiline block output. The built-in formatter always applies both of the following at once:

- **Quoted strings by default** — ordinary string values are wrapped in `"..."`.
- **Automatic multiline blocks** — any string value containing a real newline or a `\n` escape is emitted as a `'''...'''` multiline block instead of a quoted, escaped string, regardless of the quoting setting above.

There are currently no user-facing settings to change this behavior; it reflects the defaults previously recommended for the external `hjson` CLI, but without the quoting/multiline conflict that CLI had.

- **Lenient multi-line quoteless values** — strict Hjson requires an unquoted (quoteless) value to end at the line break, so continuing it onto the next line without `'''` is technically invalid syntax. This parser is lenient about it: if a quoteless value runs naturally to the end of its line, any following lines (including blank ones, which are preserved as embedded blank lines) are merged into that same value until a real `key: value` line, a closing `}`/`]`, or a comment is reached. The formatter then re-emits the merged, newline-containing value using a proper `'''...'''` multiline block, effectively auto-fixing this style of input into valid Hjson. This merging only applies to object values — array elements are never merged, since they are naturally newline-separated without colons. Quoted strings behave the same as before: a real newline typed directly inside `"..."` is kept as part of that single quoted value (and, since it contains a newline, is likewise re-emitted as a `'''...'''` block on format).

## Building from source (first-time setup)

If you're developing this extension or installing it as a dev extension, the Rust/WASM crate needs to be compiled once with a working toolchain:

1. **Install a C linker/toolchain** (needed by build scripts of some dependencies, even though the final target is WASM):
   ```sh
   # Debian/Ubuntu
   sudo apt-get update && sudo apt-get install -y build-essential

   # Fedora
   sudo dnf groupinstall -y "Development Tools"

   # macOS
   xcode-select --install

   # Arch
   sudo pacman -S base-devel
   ```

2. **Install Rust and the `wasm32-wasip2` target**:
   ```sh
   # If you don't have Rust yet:
   curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

   # Add the WASI Preview 2 target
   rustup target add wasm32-wasip2
   ```
   Note: `wasm32-wasip2` requires a reasonably recent Rust toolchain (stable ≥ 1.78 or so). If `rustup target add wasm32-wasip2` fails saying the target is unknown, run `rustup update stable` first.

3. **Build the extension** from the project root:
   ```sh
   cargo build --release --target wasm32-wasip2
   ```

4. **Verify the output artifact**:
   ```sh
   ls -la target/wasm32-wasip2/release/*.wasm
   ```
   You should see a `.wasm` file (named after the crate, e.g. `zed_hjson.wasm`), which is what Zed loads for the extension.

5. **Test the extension in a real Zed installation**:
   - Open Zed, go to `zed: extensions` → "Install Dev Extension" and point it at this project's root directory (Zed will pick up `extension.toml` and build/load the WASM automatically using its own toolchain, so this step also serves as an independent way to validate the build if you don't want to invoke `cargo` manually).
   - Alternatively, if you prefer to rely on Zed's own bundled Rust/WASI toolchain instead of your local one, just installing it as a dev extension is sufficient — Zed will invoke the equivalent of `cargo build --release --target wasm32-wasip2` internally when loading a dev extension.

**Note:** The extension now spawns `server/index.js` directly (using its `#!/usr/bin/env node` shebang) instead of passing it as a relative argument to `node`. This fixes a bug where the language server crashed with `Cannot find module '.../server/index.js'` because Zed runs the process with its working directory set to whichever project you have open, not this extension's own directory — a relative `node` argument was never resolved against the extension path, only the `command` field is. If you're upgrading from an older build, reinstall/rebuild the dev extension in Zed to pick up this fix.

**Note:** The extension's WASM sandbox only ever has write access to its own private "work" directory (e.g. `~/.local/share/zed/extensions/work/hjson/`), and Zed does **not** automatically copy this project's `server/*.js` files into it — only manifest-declared assets (grammars, the compiled `.wasm`) end up there. This previously caused `setting permissions for path ".../work/hjson/server/index.js": No such file or directory`. The fix: the three server scripts are now embedded into the compiled extension at build time (via `include_str!`) and written out to that working directory at runtime, right before the language server is spawned. If you're upgrading from an older build, reinstall/rebuild the dev extension in Zed to pick up this fix.

**Note:** Fixed a parser bug where formatting failed with `Expected ':' after key at line N` for files containing unquoted keys with internal spaces (e.g. `my key: value`), which is valid Hjson. The bundled parser (`server/parser.js`) previously stopped reading a key at the first whitespace character instead of only at `:`; it now correctly reads the full key up to the colon (or a structural/comment character), matching standard Hjson key parsing. If you're upgrading from an older build, reinstall/rebuild the dev extension in Zed to pick up this fix.

**Note:** Fixed another parser bug also surfacing as `Expected ':' after key at line N`: an unquoted (quoteless) object value containing a comma as ordinary sentence punctuation (e.g. `description: A jittery clerk agreed, but he's losing his nerve.`) was truncated at the first comma, leaving the rest of the sentence to be misparsed as a bogus key. The parser now only treats a comma as ending the value when it's actually separating properties/elements — i.e. for array elements, or for a single-line object property when a `:` appears later on the same line (e.g. `{intelligence: -6, libido: 3}`); a comma with no following `:` on the line (plain prose) is left as part of the value. If you're upgrading from an older build, reinstall/rebuild the dev extension in Zed to pick up this fix.

If you hit further errors after installing build-essential:
- `error: linker cc not found` persisting → check `which cc gcc`; if still missing, your `PATH` may not include `/usr/bin` in the shell used by `cargo`.
- `error: target wasm32-wasip2 not found` → your Rust toolchain is too old; run `rustup update` then retry `rustup target add wasm32-wasip2`.
- `zed_extension_api` version mismatches → double-check the `Cargo.toml` dependency version against what's currently expected by the Zed extension API docs/examples, since this API evolves between Zed releases.

## Testing the parser/formatter

The bundled Hjson parser and stringifier (`server/parser.js`, `server/formatter.js`) have a dependency-free Node.js test suite in `server/test.js`, covering parsing (objects, arrays, quoted/quoteless values, multiline strings, comments, keys with internal spaces), stringification (quoting, multiline blocks, key quoting), and parse → stringify → parse round-trips. It also includes a dedicated fixture file, `server/test-fixtures/sample.hjson`, combining many of these features (comments, nested objects/arrays, quoted/unquoted keys, multiline strings, escapes, numbers, booleans, null, empty collections, quoted strings with raw embedded newlines, and quoteless values that continue across lines without `'''`) in a single realistic document, which is parsed and round-tripped as part of the suite. Run it with:

```sh
node server/test.js
```

It exits with a non-zero status if any assertion fails, so it can be wired into CI.

## Grammar

This extension ships its own real HJSON tree-sitter grammar, hosted in its own standalone repository, [hjson-tree-sitter](https://github.com/Gardamuse/hjson-tree-sitter), instead of reusing the plain [tree-sitter-json](https://github.com/tree-sitter/tree-sitter-json) grammar. The old approach previously caused two visible highlighting bugs: a comma inside a `'''...'''` multiline string would break coloring for the rest of the value, and keys like `fail`/`success` would lose their key highlighting unless the preceding line ended with a comma — both were symptoms of tree-sitter's JSON grammar not actually understanding HJSON constructs (unquoted keys/values, multiline blocks) and falling back to error recovery around them.

The new grammar natively supports objects/arrays, quoted and unquoted (`unquoted_key`/`unquoted_string`) keys and values, `'''...'''` multiline strings, numbers/booleans/null, and `#`/`//`/`/* */` comments, with commas treated as optional separators (as in real Hjson) that are consumed directly by the scanner/extras and never appear as a node in the syntax tree. It's referenced in `extension.toml` via `[grammars.hjson]` (`repository`/`rev` pointing at the `hjson-tree-sitter` repository), and `languages/hjson/config.toml` sets `grammar = "hjson"` to match. `languages/hjson/brackets.scm` and `indents.scm` already queried the node types this grammar produces without changes, but `highlights.scm` needed a small fix (see note below).

If you're upgrading from an older build that used the plain JSON grammar (or the earlier `hjson-grammar` branch hosted directly on this repository), reinstall/rebuild the dev extension in Zed (uninstall + "Install Dev Extension" again, then fully restart Zed) — Zed needs network access the first time to fetch the grammar from the [hjson-tree-sitter](https://github.com/Gardamuse/hjson-tree-sitter) repository/rev.

**Note:** Fixed a bug where the extension failed to load entirely right after switching to the new grammar, with the log showing `Error loading highlights query ... Invalid node type ","`. The new grammar treats commas as optional separators consumed directly by its external scanner/extras rule, so no `,` node is ever produced in the syntax tree — unlike the old JSON grammar, which did emit a `,` token. `highlights.scm`'s punctuation query still referenced `","` from that old grammar, which is now an invalid node type and made Zed refuse to load the `HJSON` language at all. The query was updated to only match `":"` for `@punctuation.delimiter`. If you're upgrading from an older build, reinstall/rebuild the dev extension in Zed to pick up this fix.

**Note:** Fixed `Failed to install dev extension: failed to compile grammar 'hjson'` after moving the grammar to its own repository (`hjson-tree-sitter`). When installed as a dev extension, Zed checks out the grammar directly into this project's own `grammars/hjson/` directory; that directory was left over from the previous `[grammars.hjson]` `repository` value (the old `hjson-grammar` branch of `zed-hjson` itself), and Zed refuses to reuse an existing grammar directory that isn't a git clone of the *current* `repository` URL, causing the compile step to fail outright. The stale `grammars/hjson/` (and `grammars/hjson.wasm`) directory has been removed, and a `.gitignore` was added for `/grammars`, `/extension.wasm`, and `/target` so these local build artifacts never get committed or become stale again. If you hit this error, delete the `grammars/hjson` directory (and `grammars/hjson.wasm`, if present) in this project, then reinstall/rebuild the dev extension in Zed.

## License

MIT
