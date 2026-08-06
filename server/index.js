#!/usr/bin/env node
'use strict';

// Minimal Language Server Protocol server providing `textDocument/formatting`
// for HJSON documents. It is spawned by the Zed extension (see `src/lib.rs`)
// and communicates over stdio using the standard LSP framing
// (`Content-Length` headers).
//
// Both parsing (`parser.js`) and stringification (`formatter.js`) are
// implemented from scratch in this extension, replacing the previously used
// `hjson` npm package. That library has a bug where enabling the `quotes`
// stringify option silently disables multiline `'''...'''` block output,
// which this custom formatter fixes by supporting both at once (see README
// for details).

const { parse } = require('./parser');
const { stringify } = require('./formatter');

const documents = new Map();

let buffer = Buffer.alloc(0);

process.stdin.on('data', (chunk) => {
  buffer = Buffer.concat([buffer, chunk]);
  processBuffer();
});

function processBuffer() {
  while (true) {
    const headerEnd = buffer.indexOf('\r\n\r\n');
    if (headerEnd === -1) return;

    const header = buffer.slice(0, headerEnd).toString('utf8');
    const match = /Content-Length: (\d+)/i.exec(header);
    if (!match) {
      // Malformed header; drop it to avoid getting stuck.
      buffer = buffer.slice(headerEnd + 4);
      continue;
    }

    const contentLength = parseInt(match[1], 10);
    const bodyStart = headerEnd + 4;
    if (buffer.length < bodyStart + contentLength) return;

    const body = buffer.slice(bodyStart, bodyStart + contentLength).toString('utf8');
    buffer = buffer.slice(bodyStart + contentLength);

    let message;
    try {
      message = JSON.parse(body);
    } catch (e) {
      continue;
    }
    handleMessage(message);
  }
}

function send(message) {
  const json = JSON.stringify(message);
  const header = 'Content-Length: ' + Buffer.byteLength(json, 'utf8') + '\r\n\r\n';
  process.stdout.write(header + json);
}

function respond(id, result) {
  send({ jsonrpc: '2.0', id, result });
}

function respondError(id, code, msg) {
  send({ jsonrpc: '2.0', id, error: { code, message: msg } });
}

function handleMessage(message) {
  const { id, method, params } = message;

  switch (method) {
    case 'initialize':
      respond(id, {
        capabilities: {
          textDocumentSync: 1, // Full document sync.
          documentFormattingProvider: true,
        },
        serverInfo: { name: 'hjson-language-server', version: '1.0.0' },
      });
      break;

    case 'initialized':
    case '$/setTrace':
      // Notifications; nothing to do.
      break;

    case 'shutdown':
      respond(id, null);
      break;

    case 'exit':
      process.exit(0);
      break;

    case 'textDocument/didOpen':
      documents.set(params.textDocument.uri, params.textDocument.text);
      break;

    case 'textDocument/didChange':
      if (params.contentChanges && params.contentChanges.length > 0) {
        // We only support full document sync, so the last change is the
        // full new text.
        const lastChange = params.contentChanges[params.contentChanges.length - 1];
        documents.set(params.textDocument.uri, lastChange.text);
      }
      break;

    case 'textDocument/didClose':
      documents.delete(params.textDocument.uri);
      break;

    case 'textDocument/formatting':
      handleFormatting(id, params);
      break;

    default:
      if (id !== undefined) {
        respondError(id, -32601, 'Method not found: ' + method);
      }
      break;
  }
}

function handleFormatting(id, params) {
  const uri = params.textDocument.uri;
  const text = documents.get(uri);

  if (text === undefined) {
    respondError(id, -32602, 'Document not open: ' + uri);
    return;
  }

  try {
    const value = parse(text);
    const formatted = stringify(value, { quotes: true, indent: 2 });

    if (formatted === text) {
      respond(id, []);
      return;
    }

    const lines = text.split('\n');
    const lastLine = lines[lines.length - 1];

    respond(id, [
      {
        range: {
          start: { line: 0, character: 0 },
          end: { line: lines.length - 1, character: lastLine.length },
        },
        newText: formatted,
      },
    ]);
  } catch (e) {
    respondError(id, -32000, 'Failed to format document: ' + e.message);
  }
}
