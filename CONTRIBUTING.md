# Contributing to VirtualDJ Rust SDK

Thank you for your interest in contributing! This document provides guidelines for contributing to the project.

## Code of Conduct

Be respectful and inclusive. We are committed to providing a welcoming environment for all contributors.

## Getting Started

### Prerequisites
- Rust 1.70+ (install from https://rustup.rs/)
- A C++ compiler (MSVC on Windows, Clang on macOS, GCC on Linux)
- Git

### Setup
```bash
git clone https://github.com/ikamondj/VirtualDJRustSDK.git
cd VirtualDJRustSDK
cargo build
cargo test
```

## Development Workflow

### 1. Create a branch
```bash
git checkout -b feature/your-feature-name
```

### 2. Make your changes
- Keep commits small and focused
- Write clear commit messages
- Add tests for new functionality

### 3. Test your changes
```bash
cargo test --all
cargo build --release
cargo clippy  # Check for common mistakes
cargo fmt     # Format code
```

### 4. Push and create a pull request
```bash
git push origin feature/your-feature-name
```

## Types of Contributions

### Bug Reports
- Check if the bug is already reported
- Provide a minimal reproducible example
- Include your environment details

### Feature Requests
- Check if already requested
- Explain the use case
- Describe the expected behavior

### Code Contributions
- Follow the existing code style
- Add tests for new features
- Update documentation
- Ensure all tests pass

### Documentation
- Fix typos and unclear explanations
- Add examples and use cases
- Clarify complex sections

## Code Style

### Formatting
```bash
cargo fmt
```

### Linting
```bash
cargo clippy
```

### Testing
```bash
# Run all tests
cargo test

# Run specific test
cargo test test_name

# Run with logging
RUST_LOG=debug cargo test -- --nocapture
```

## Project Structure

```
├── rs_core/
│   ├── lib.rs      - Safe Rust API and traits
│   └── ffi.rs      - Raw FFI bindings
├── vdj_plugin_shim/
│   └── basic_plugin_shim.cpp  - C++ implementation
├── abi/
│   └── vdj_plugin_abi.h       - C ABI interface
├── examples/
│   └── simple_dsp.rs          - Example plugin
├── tests/
│   └── integration_tests.rs   - Integration tests
├── build.rs        - Build script
└── Cargo.toml      - Package manifest
```

## Key Files to Know

- **rs_core/lib.rs** - High-level Rust API (traits like `DspPlugin`)
- **rs_core/ffi.rs** - Low-level FFI bindings (raw C functions)
- **vdj_plugin_shim/basic_plugin_shim.cpp** - C++ wrapper implementation
- **abi/vdj_plugin_abi.h** - C ABI function declarations

## Commit Message Guidelines

Use clear, descriptive commit messages:

```
feat: add support for position DSP plugins
fix: correct audio sample clipping in gain effect
docs: update README with plugin template
test: add integration tests for DSP pipeline
chore: update dependencies
```

## Pull Request Process

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add/update tests
5. Ensure all tests pass: `cargo test`
6. Format code: `cargo fmt`
7. Check with clippy: `cargo clippy`
8. Push to your fork
9. Create a pull request with a clear description

## Reporting Issues

When reporting issues, include:
- OS and Rust version (`rustc --version`)
- Minimal reproducible example
- Expected vs actual behavior
- Any error messages

## Getting Help

- **GitHub Issues** - Bug reports and feature requests
- **GitHub Discussions** - General questions
- **Rust Community** - https://www.rust-lang.org/community

## Maintainers

- Thomas Landman (@ikamondj)

## License

By contributing, you agree that your contributions will be licensed under the project's license (MIT OR Apache-2.0).

---

Thank you for contributing to the VirtualDJ Rust SDK! 🎵
