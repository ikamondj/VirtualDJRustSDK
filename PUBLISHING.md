/** 
 * VirtualDJ Plugin SDK - Publishing Guide
 */

# Publishing to crates.io

This project uses GitHub Actions to automatically test, build, version, and publish to crates.io.

## Prerequisites

### 1. Create a crates.io account
- Visit https://crates.io
- Click "Login with GitHub"
- Authorize the application

### 2. Generate API token
- Go to https://crates.io/me (after logging in)
- Click "API Tokens"
- Create a new token (recommended: name it "github-actions")
- Copy the token

### 3. Add secret to GitHub repository
- Go to your repository: https://github.com/ikamondj/VirtualDJRustSDK
- Settings → Secrets and variables → Actions
- Click "New repository secret"
- Name: `CARGO_REGISTRY_TOKEN`
- Value: Paste your API token
- Click "Add secret"

## Verify your Cargo.toml

Ensure your `Cargo.toml` includes:

```toml
[package]
name = "virtualdj-plugin-sdk"
version = "0.1.0"
edition = "2021"
authors = ["Thomas Landman"]
description = "Rust bindings for the VirtualDJ Plugin SDK"
license = "MIT OR Apache-2.0"
repository = "https://github.com/ikamondj/VirtualDJRustSDK"
readme = "README.md"
keywords = ["virtualdj", "plugin", "sdk", "audio", "dj"]
categories = ["multimedia::audio"]
```

All of these are required for publishing.

## How the workflow works

1. **Trigger** - Push to `master` or `main` branch (only if relevant files changed)
2. **Test** - Run all tests (`cargo test`)
3. **Build** - Build release version (`cargo build --release`)
4. **Version** - Auto-increment patch version (0.1.0 → 0.1.1)
5. **Publish** - Upload to crates.io
6. **Tag** - Create git tag and commit version bump

The workflow file is at `.github/workflows/publish.yml`

## Manual publishing (if needed)

If you need to publish manually:

1. Update version in `Cargo.toml`
2. Run tests locally:
   ```bash
   cargo test
   ```
3. Publish:
   ```bash
   cargo publish
   ```

## Viewing published versions

Once published, your crate will be available at:
https://crates.io/crates/virtualdj-plugin-sdk

## Troubleshooting

### Workflow fails with "unauthorized"
- Verify `CARGO_REGISTRY_TOKEN` secret is set correctly
- Token should start with `crates_`

### "crate name already taken"
- The name must be unique on crates.io
- If needed, change to something like `virtualdj-plugin-sdk-yourname`

### Version already published
- Each version can only be published once
- The workflow auto-increments patch versions to avoid this
- To re-publish, either wait for auto-increment or manually change version

## Version bumping strategy

The workflow currently bumps the patch version (0.1.0 → 0.1.1).

To manually bump major/minor:
1. Edit `Cargo.toml` to your desired version
2. Commit and push to master
3. The workflow will use your version

## See also

- [Cargo Book - Publishing](https://doc.rust-lang.org/cargo/reference/publishing.html)
- [crates.io Documentation](https://doc.rust-lang.org/cargo/reference/publishing.html)
- [GitHub Actions Secrets](https://docs.github.com/en/actions/security-guides/encrypted-secrets)
