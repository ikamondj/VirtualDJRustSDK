//! Integration tests for VirtualDJ Plugin SDK
//!
//! These tests verify that the SDK components compile and link correctly.

use virtualdj_plugin_sdk::ffi;

#[test]
fn test_constants_defined() {
    // Verify that all important constants are defined
    assert_eq!(ffi::S_OK, 0);
    assert!(ffi::E_NOTIMPL != 0);
    assert!(ffi::E_FAIL != 0);
}

#[test]
fn test_parameter_types_defined() {
    // Verify parameter type constants
    assert_eq!(ffi::VDJPARAM_BUTTON, 0);
    assert_eq!(ffi::VDJPARAM_SLIDER, 1);
    assert_eq!(ffi::VDJPARAM_SWITCH, 2);
    assert_eq!(ffi::VDJPARAM_STRING, 3);
}

#[test]
fn test_video_engine_enum() {
    // Verify video engine enum values
    assert_eq!(ffi::EVdjVideoEngine::VdjVideoEngineAny as i32, 0);
    assert_eq!(ffi::EVdjVideoEngine::VdjVideoEngineDirectX9 as i32, 1);
    assert_eq!(ffi::EVdjVideoEngine::VdjVideoEngineOpenGL as i32, 2);
}

#[test]
fn test_error_type_conversion() {
    use virtualdj_plugin_sdk::PluginError;
    
    let err: PluginError = ffi::E_FAIL.into();
    assert_eq!(err, PluginError::Fail);
    
    let ok: PluginError = ffi::S_OK.into();
    assert_eq!(ok, PluginError::Ok);
}

#[test]
fn test_plugin_info_creation() {
    use virtualdj_plugin_sdk::PluginInfo;
    
    let info = PluginInfo {
        name: "Test Plugin".to_string(),
        author: "Test Author".to_string(),
        description: "A test plugin".to_string(),
        version: "1.0.0".to_string(),
        flags: 0,
    };
    
    assert_eq!(info.name, "Test Plugin");
    assert_eq!(info.author, "Test Author");
    assert_eq!(info.version, "1.0.0");
}

#[test]
fn test_result_type() {
    use virtualdj_plugin_sdk::{Result, PluginError};
    
    let success: Result<i32> = Ok(42);
    assert!(success.is_ok());
    
    let failure: Result<i32> = Err(PluginError::Fail);
    assert!(failure.is_err());
}
