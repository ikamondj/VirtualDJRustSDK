# VirtualDJ Rust SDK

A complete Rust binding for the VirtualDJ Plugin SDK, enabling developers to write VirtualDJ plugins entirely in Rust while maintaining full compatibility with the C++ ABI.

## Architecture

This SDK consists of three layers:

```
┌─────────────────────────────────────────────┐
│  User Rust Plugin (Pure Rust)               │
│  - Implements plugin traits                 │
│  - No C++ knowledge required                │
└────────────────┬────────────────────────────┘
                 │ (Safe abstraction)
┌────────────────▼────────────────────────────┐
│  Rust Safe API (rs_core/lib.rs)             │
│  - Trait definitions (DspPlugin, etc)       │
│  - Error handling (PluginError)             │
│  - High-level abstractions                  │
└────────────────┬────────────────────────────┘
                 │ (FFI bindings)
┌────────────────▼────────────────────────────┐
│  Rust FFI Layer (rs_core/ffi.rs)            │
│  - Raw C function declarations              │
│  - Direct mapping to C ABI                  │
└────────────────┬────────────────────────────┘
                 │ (C linkage)
┌────────────────▼────────────────────────────┐
│  C ABI Layer (abi/vdj_plugin_abi.h)         │
│  - C-compatible function signatures         │
│  - Opaque handles (VdjPlugin, etc)          │
│  - Callback structures                      │
└────────────────┬────────────────────────────┘
                 │ (C++ implementation)
┌────────────────▼────────────────────────────┐
│  C++ Shim Layer (vdj_plugin_shim/*.cpp)     │
│  - Wraps C++ classes from VirtualDJ SDK     │
│  - Implements C ABI functions               │
│  - Bridges C++ and C/FFI worlds             │
└────────────────┬────────────────────────────┘
                 │ (C++ classes)
┌────────────────▼────────────────────────────┐
│  VirtualDJ C++ SDK Headers (header_ref/)    │
│  - IVdjPlugin8 (base plugin interface)      │
│  - IVdjPluginDsp8 (audio effects)           │
│  - IVdjPluginVideoFx8 (video effects)       │
│  - IVdjPluginOnlineSource (online sources)  │
└─────────────────────────────────────────────┘
```

## How It Works

1. **User writes Rust code** implementing trait methods (e.g., `DspPlugin::on_process_samples`)
2. **Safe API trait** provides default implementations and type safety
3. **Rust FFI bindings** call into C ABI functions (extern "C" declarations)
4. **C ABI layer** defines function signatures that work with C calling conventions
5. **C++ shim** implements those C functions by wrapping the C++ classes from VirtualDJ
6. **VirtualDJ C++ SDK** provides the actual plugin infrastructure

## Building

```bash
cargo build --release
```

The build script (`build.rs`) automatically:
- Compiles the C++ shim layer using the `cc` crate
- Links the compiled C++ code with your Rust code
- Monitors file changes for incremental builds

## Creating a Plugin

### 1. Basic DSP Plugin Template

```rust
use virtualdj_plugin_sdk::{DspPlugin, PluginBase, PluginInfo, Result};

pub struct MyEffect {
    // Your plugin state here
}

impl PluginBase for MyEffect {
    fn on_load(&mut self) -> Result<()> {
        Ok(())
    }

    fn get_info(&self) -> PluginInfo {
        PluginInfo {
            name: "My Effect".to_string(),
            author: "Your Name".to_string(),
            description: "My awesome effect".to_string(),
            version: "1.0.0".to_string(),
            flags: 0,
        }
    }
}

impl DspPlugin for MyEffect {
    fn on_process_samples(&mut self, buffer: &mut [f32]) -> Result<()> {
        // Process audio here
        for sample in buffer.iter_mut() {
            *sample *= 0.5; // Example: reduce volume
        }
        Ok(())
    }
}
```

### 2. Available Plugin Types

- **`DspPlugin`** - Real-time audio effects
- **`BufferDspPlugin`** - Buffer manipulation (e.g., time-stretching)
- **`PositionDspPlugin`** - Position/playback control
- **`VideoFxPlugin`** - Video effects
- **`VideoTransitionPlugin`** - Video transitions
- **`OnlineSourcePlugin`** - Online music sources/streaming

## Key Features

✅ **100% Rust** - Write plugins in pure Rust, no C++ needed  
✅ **Type Safe** - Leverages Rust's type system for safety  
✅ **Error Handling** - Rust's `Result` type for error propagation  
✅ **ABI Compatible** - Fully compatible with VirtualDJ's C++ ABI  
✅ **Zero Overhead** - Direct FFI calls, minimal abstraction cost  
✅ **Cross-Platform** - Works with Windows, macOS implementations  

## Project Structure

```
VirtualDJRustSDK/
├── abi/
│   └── vdj_plugin_abi.h          # C ABI interface definitions
├── header_ref/
│   ├── vdjPlugin8.h              # VirtualDJ base plugin header
│   ├── vdjDsp8.h                 # DSP plugin header
│   ├── vdjVideo8.h               # Video plugin header
│   └── vdjOnlineSource.h          # Online source plugin header
├── vdj_plugin_shim/
│   └── basic_plugin_shim.cpp      # C++ shim implementation
├── rs_core/
│   ├── lib.rs                     # Safe Rust API and trait definitions
│   └── ffi.rs                     # Raw FFI bindings to C ABI
├── examples/
│   └── simple_dsp.rs              # Example DSP plugin
├── build.rs                        # Build script for C++ compilation
├── Cargo.toml                      # Rust package manifest
└── README.md                       # This file
```

## Development Workflow

### 1. Create a new plugin library

```bash
cargo new --lib my-virtualdj-plugin
cd my-virtualdj-plugin
```

### 2. Add SDK as a dependency

```toml
# Cargo.toml
[dependencies]
virtualdj-plugin-sdk = { path = "../VirtualDJRustSDK" }
```

### 3. Implement the plugin trait

```rust
use virtualdj_plugin_sdk::DspPlugin;

pub struct MyPlugin { }

impl DspPlugin for MyPlugin {
    fn on_process_samples(&mut self, buffer: &mut [f32]) -> Result<()> {
        todo!()
    }
}
```

### 4. Build your plugin

```bash
cargo build --release
```

## Error Handling

The SDK provides a `PluginError` type for error handling:

```rust
use virtualdj_plugin_sdk::{Result, PluginError};

fn my_function() -> Result<String> {
    if some_error_condition {
        Err(PluginError::Fail)
    } else {
        Ok("Success".to_string())
    }
}
```

## FFI Bindings Reference

The low-level FFI bindings are available in `rs_core::ffi` for advanced use cases:

```rust
use virtualdj_plugin_sdk::ffi::*;

// Direct C function calls
unsafe {
    let plugin = vdj_plugin_dsp_create();
    vdj_plugin_dsp_release(plugin);
}
```

**Note:** Direct FFI usage requires `unsafe` blocks and is not recommended for typical use.

## Constants and Flags

Common plugin flags and parameter types are available:

```rust
use virtualdj_plugin_sdk::ffi::*;

// Plugin flags
const VDJFLAG_PROCESSFIRST: u32 = 0x4;
const VDJFLAG_PROCESSLAST: u32 = 0x8;

// Parameter types
const VDJPARAM_SLIDER: i32 = 1;
const VDJPARAM_BUTTON: i32 = 0;
```

## Testing

The SDK includes test support for plugin logic:

```rust
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_plugin() {
        let mut plugin = MyPlugin::new();
        assert!(plugin.on_load().is_ok());
    }
}
```

Run tests with:

```bash
cargo test
```

## Performance Considerations

- **Buffer Processing**: Buffers are passed as `&mut [f32]` slices for zero-copy access
- **Sample Rates**: Typically 44.1kHz or 48kHz (access via `sample_rate()` method)
- **Stereo Format**: Audio samples are interleaved (L, R, L, R, ...)
- **Real-time**: Minimize allocations in `on_process_samples()` for best performance

## Troubleshooting

### Compilation errors with C++

Ensure you have:
- A C++ compiler installed (MSVC on Windows)
- The `cc` crate dependency (automatically downloaded)

### Symbol resolution errors

The C++ shim must be properly compiled. Check that `vdj_plugin_shim/basic_plugin_shim.cpp` includes all necessary VirtualDJ headers.

## Contributing

Contributions are welcome! Areas for improvement:
- Additional plugin type examples
- Performance optimizations
- Cross-platform testing
- Extended trait methods

## License

This project is provided under the MIT or Apache 2.0 license.

## References

- [VirtualDJ Developer Documentation](https://www.virtualdj.com/)
- [Rust FFI Book](https://doc.rust-lang.org/nomicon/ffi.html)
- [Rust Type System](https://doc.rust-lang.org/book/ch03-02-data-types.html)
