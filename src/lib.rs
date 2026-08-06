use std::fs;
use std::path::Path;

use zed_extension_api::{self as zed, Command, LanguageServerId, Result, Worktree};

struct HjsonExtension;

impl HjsonExtension {
    /// Path (relative to the extension's sandboxed working directory) of the
    /// bundled language server script that provides `textDocument/formatting`
    /// for HJSON. See `server/index.js` for the implementation.
    const SERVER_SCRIPT: &'static str = "server/index.js";
    const PARSER_SCRIPT: &'static str = "server/parser.js";
    const FORMATTER_SCRIPT: &'static str = "server/formatter.js";

    // The extension's WASM host only ever gives the extension access to its
    // own private "work" directory (e.g.
    // `~/.local/share/zed/extensions/work/hjson/`) when resolving relative
    // paths for `Command`/`make_file_executable`. Zed does NOT automatically
    // copy arbitrary bundled source files (like these `server/*.js` scripts)
    // from this project into that sandboxed directory — only manifest-declared
    // assets (grammars, the compiled wasm) end up there. So we embed the
    // scripts at compile time and write them out into that working directory
    // ourselves before ever trying to spawn/mark them executable.
    const SERVER_SCRIPT_CONTENTS: &'static str = include_str!("../server/index.js");
    const PARSER_SCRIPT_CONTENTS: &'static str = include_str!("../server/parser.js");
    const FORMATTER_SCRIPT_CONTENTS: &'static str = include_str!("../server/formatter.js");

    fn write_bundled_server_files() -> Result<()> {
        if let Some(parent) = Path::new(Self::SERVER_SCRIPT).parent() {
            fs::create_dir_all(parent)
                .map_err(|e| format!("failed to create {:?}: {}", parent, e))?;
        }

        for (path, contents) in [
            (Self::SERVER_SCRIPT, Self::SERVER_SCRIPT_CONTENTS),
            (Self::PARSER_SCRIPT, Self::PARSER_SCRIPT_CONTENTS),
            (Self::FORMATTER_SCRIPT, Self::FORMATTER_SCRIPT_CONTENTS),
        ] {
            fs::write(path, contents).map_err(|e| format!("failed to write {}: {}", path, e))?;
        }

        Ok(())
    }
}

impl zed::Extension for HjsonExtension {
    fn new() -> Self {
        Self
    }

    fn language_server_command(
        &mut self,
        _language_server_id: &LanguageServerId,
        _worktree: &Worktree,
    ) -> Result<Command> {
        // Make sure the bundled server scripts actually exist in the
        // extension's sandboxed working directory before we try to spawn or
        // chmod them (see the comment on `write_bundled_server_files`).
        Self::write_bundled_server_files()?;

        // Zed spawns this command with its working directory set to the
        // worktree being edited, not this extension's own installation
        // directory. Passing `server/index.js` as a relative *argument* to
        // `node` therefore fails (`MODULE_NOT_FOUND`), because relative args
        // are never resolved by Zed — only the `command` field is (Zed
        // rewrites a relative `command` into an absolute path rooted at the
        // extension's directory). So we make the script itself the command
        // (relying on its `#!/usr/bin/env node` shebang) and mark it
        // executable, instead of invoking `node` with a relative script arg.
        zed::make_file_executable(Self::SERVER_SCRIPT)?;

        Ok(Command {
            command: Self::SERVER_SCRIPT.to_string(),
            args: Vec::new(),
            env: Default::default(),
        })
    }
}

zed::register_extension!(HjsonExtension);
