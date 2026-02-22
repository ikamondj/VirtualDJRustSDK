# Changelog

All notable changes to the VirtualDJ Rust SDK will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.1.0] - 2026-02-21

### Added
- Initial release of VirtualDJ Rust SDK
- C ABI layer (`abi/vdj_plugin_abi.h`) for bridging Rust and VirtualDJ C++ SDK
- C++ shim implementation (`vdj_plugin_shim/basic_plugin_shim.cpp`)
- Raw FFI bindings (`rs_core/ffi.rs`)
- Safe Rust API with trait definitions:
  - `DspPlugin` - Real-time audio effects
  - `BufferDspPlugin` - Buffer manipulation
  - `PositionDspPlugin` - Position/playback control
  - `VideoFxPlugin` - Video effects
  - `VideoTransitionPlugin` - Video transitions
  - `OnlineSourcePlugin` - Online music sources
- Error handling with `PluginError` and `Result<T>` types
- Comprehensive integration tests
- Example DSP plugin (Simple Gain effect)
- GitHub Actions workflow for automated testing and publishing to crates.io
- Automatic version bumping and tagging
- Full documentation (README, CONTRIBUTING, PUBLISHING guides)

### Features
- 100% pure Rust plugin development (no C++ knowledge required)
- Type-safe abstractions over C++ ABI
- Automatic C++ compilation via `cc` crate
- Cross-platform support (Windows, macOS, Linux)
- Zero-cost abstractions with minimal FFI overhead
- Comprehensive test coverage

### Documentation
- README.md with architecture overview and usage guide
- CONTRIBUTING.md for contributor guidelines
- PUBLISHING.md for crates.io publishing setup
- Inline code documentation and examples
- Integration tests demonstrating API usage

---

## Future Releases

### Planned for v0.2.0
- Advanced parameter system with full callback support
- Video plugin infrastructure improvements
- Online source plugin helpers
- More comprehensive examples
- Performance optimizations

### Planned for v0.3.0
- GUI plugin support
- Advanced error handling and diagnostics
- Plugin lifecycle management improvements
- Logging and tracing infrastructure

---

[0.1.0]: https://github.com/ikamondj/VirtualDJRustSDK/releases/tag/v0.1.0
