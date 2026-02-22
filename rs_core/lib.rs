//! VirtualDJ Rust SDK - Safe API Bindings
//! 
//! This module provides a high-level, safe Rust API for developing VirtualDJ plugins.
//! It wraps the low-level FFI bindings with proper error handling and memory safety.

pub mod ffi;

use std::ffi::{CStr, CString};
use std::fmt;

/// VirtualDJ plugin error type
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum PluginError {
    /// Operation succeeded
    Ok,
    /// General failure
    Fail,
    /// Not implemented
    NotImplemented,
    /// Null pointer error
    NullPointer,
}

impl fmt::Display for PluginError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            PluginError::Ok => write!(f, "Success"),
            PluginError::Fail => write!(f, "General failure"),
            PluginError::NotImplemented => write!(f, "Not implemented"),
            PluginError::NullPointer => write!(f, "Null pointer"),
        }
    }
}

impl std::error::Error for PluginError {}

impl From<ffi::HRESULT> for PluginError {
    fn from(hr: ffi::HRESULT) -> Self {
        match hr {
            ffi::S_OK => PluginError::Ok,
            ffi::E_NOTIMPL => PluginError::NotImplemented,
            ffi::E_FAIL => PluginError::Fail,
            _ => PluginError::Fail,
        }
    }
}

/// Result type for plugin operations
pub type Result<T> = std::result::Result<T, PluginError>;

/// Plugin context that provides access to VirtualDJ API functions
/// 
/// This struct holds the plugin pointer and callbacks, allowing safe access to
/// VirtualDJ state information like track metadata, position, BPM, etc.
/// 
/// # Example
/// 
/// ```ignore
/// let context = PluginContext::new(plugin_ptr, &callbacks);
/// let title = context.get_info_string("deck 1 get_title")?;
/// let position = context.get_info_double("deck 1 get_position")?;
/// ```
pub struct PluginContext {
    plugin: *mut ffi::VdjPlugin,
    callbacks: *const ffi::VdjCallbacks,
}

impl PluginContext {
    /// Create a new plugin context
    /// 
    /// # Arguments
    /// * `plugin` - Pointer to the VdjPlugin struct
    /// * `callbacks` - Reference to the VdjCallbacks struct
    /// 
    /// # Safety
    /// The plugin pointer must be valid and the callbacks must remain valid
    /// for the lifetime of this context.
    pub fn new(plugin: *mut ffi::VdjPlugin, callbacks: &ffi::VdjCallbacks) -> Self {
        PluginContext {
            plugin,
            callbacks: callbacks as *const ffi::VdjCallbacks,
        }
    }

    /// Query VirtualDJ for a double/numeric value
    /// 
    /// # Arguments
    /// * `command` - The VDJ script command (e.g., "deck 1 get_position")
    /// 
    /// # Returns
    /// A Result containing the numeric value, or an error if the command fails
    pub fn get_info_double(&self, command: &str) -> Result<f64> {
        if self.plugin.is_null() || self.callbacks.is_null() {
            return Err(PluginError::NullPointer);
        }

        let c_command = std::ffi::CString::new(command)
            .map_err(|_| PluginError::Fail)?;
        
        let mut result: f64 = 0.0;
        
        let hr = unsafe {
            ((*self.callbacks).get_info)(
                self.plugin,
                c_command.as_ptr() as *const u8,
                &mut result as *mut f64,
            )
        };

        if hr == ffi::S_OK {
            Ok(result)
        } else {
            Err(PluginError::from(hr))
        }
    }

    /// Query VirtualDJ for a string value
    /// 
    /// # Arguments
    /// * `command` - The VDJ script command (e.g., "deck 1 get_title")
    /// 
    /// # Returns
    /// A Result containing the string value, or an error if the command fails
    pub fn get_info_string(&self, command: &str) -> Result<String> {
        if self.plugin.is_null() || self.callbacks.is_null() {
            return Err(PluginError::NullPointer);
        }

        let c_command = std::ffi::CString::new(command)
            .map_err(|_| PluginError::Fail)?;
        
        let mut output: [u8; 1024] = [0; 1024];
        
        let hr = unsafe {
            ((*self.callbacks).get_string_info)(
                self.plugin,
                c_command.as_ptr() as *const u8,
                output.as_mut_ptr(),
                output.len() as i32,
            )
        };

        if hr == ffi::S_OK {
            let c_str = unsafe { CStr::from_ptr(output.as_ptr() as *const i8) };
            Ok(c_str.to_string_lossy().into_owned())
        } else {
            Err(PluginError::from(hr))
        }
    }

    /// Send a command to VirtualDJ
    /// 
    /// # Arguments
    /// * `command` - The VDJ script command (e.g., "deck 1 play")
    /// 
    /// # Returns
    /// Ok(()) if successful, or an error if the command fails
    pub fn send_command(&self, command: &str) -> Result<()> {
        if self.plugin.is_null() || self.callbacks.is_null() {
            return Err(PluginError::NullPointer);
        }

        let c_command = std::ffi::CString::new(command)
            .map_err(|_| PluginError::Fail)?;
        
        let hr = unsafe {
            ((*self.callbacks).send_command)(
                self.plugin,
                c_command.as_ptr() as *const u8,
            )
        };

        if hr == ffi::S_OK {
            Ok(())
        } else {
            Err(PluginError::from(hr))
        }
    }
}

/// Plugin information
#[derive(Debug, Clone)]
pub struct PluginInfo {
    pub name: String,
    pub author: String,
    pub description: String,
    pub version: String,
    pub flags: u32,
}

impl PluginInfo {
    fn from_ffi(ffi_info: &ffi::VdjPluginInfo) -> Result<Self> {
        let name = unsafe { CStr::from_ptr(ffi_info.plugin_name as *const i8) }
            .to_string_lossy()
            .into_owned();
        let author = unsafe { CStr::from_ptr(ffi_info.author as *const i8) }
            .to_string_lossy()
            .into_owned();
        let description = unsafe { CStr::from_ptr(ffi_info.description as *const i8) }
            .to_string_lossy()
            .into_owned();
        let version = unsafe { CStr::from_ptr(ffi_info.version as *const i8) }
            .to_string_lossy()
            .into_owned();

        Ok(PluginInfo {
            name,
            author,
            description,
            version,
            flags: ffi_info.flags,
        })
    }
}

/// Base plugin trait that all plugin types implement
pub trait PluginBase {
    /// Called when the plugin is loaded
    fn on_load(&mut self) -> Result<()> {
        Ok(())
    }

    /// Get plugin information
    fn get_info(&self) -> PluginInfo {
        PluginInfo {
            name: "VirtualDJ Plugin".to_string(),
            author: "Plugin Developer".to_string(),
            description: "A VirtualDJ plugin".to_string(),
            version: "1.0.0".to_string(),
            flags: 0,
        }
    }

    /// Called when a parameter is changed
    fn on_parameter(&mut self, id: i32) -> Result<()> {
        Ok(())
    }

    /// Get string representation of a parameter
    fn on_get_parameter_string(&self, id: i32) -> Result<String> {
        Err(PluginError::NotImplemented)
    }
}

/// DSP plugin trait for audio effect plugins
pub trait DspPlugin: PluginBase {
    /// Called when the DSP plugin starts
    fn on_start(&mut self) -> Result<()> {
        Ok(())
    }

    /// Called when the DSP plugin stops
    fn on_stop(&mut self) -> Result<()> {
        Ok(())
    }

    /// Process audio samples (stereo, so buffer is 2*nb samples)
    fn on_process_samples(&mut self, buffer: &mut [f32]) -> Result<()>;

    /// Get the sample rate
    fn sample_rate(&self) -> i32 {
        44100
    }

    /// Get the song BPM
    fn song_bpm(&self) -> i32 {
        120
    }

    /// Get the song position in beats
    fn song_pos_beats(&self) -> f64 {
        0.0
    }
}

/// Buffer DSP plugin trait for buffer manipulation
pub trait BufferDspPlugin: PluginBase {
    /// Called when the plugin starts
    fn on_start(&mut self) -> Result<()> {
        Ok(())
    }

    /// Called when the plugin stops
    fn on_stop(&mut self) -> Result<()> {
        Ok(())
    }

    /// Get song buffer at the specified position
    fn on_get_song_buffer(&mut self, song_pos: i32, nb: i32) -> Option<&[i16]>;

    /// Get the sample rate
    fn sample_rate(&self) -> i32 {
        44100
    }

    /// Get the song BPM
    fn song_bpm(&self) -> i32 {
        120
    }

    /// Get the song position in samples
    fn song_pos(&self) -> i32 {
        0
    }

    /// Get the song position in beats
    fn song_pos_beats(&self) -> f64 {
        0.0
    }
}

/// Position DSP plugin trait for position manipulation
pub trait PositionDspPlugin: PluginBase {
    /// Called when the plugin starts
    fn on_start(&mut self) -> Result<()> {
        Ok(())
    }

    /// Called when the plugin stops
    fn on_stop(&mut self) -> Result<()> {
        Ok(())
    }

    /// Transform position (can modify songPos, videoPos, volume)
    fn on_transform_position(
        &mut self,
        song_pos: &mut f64,
        video_pos: &mut f64,
        volume: &mut f32,
        src_volume: &mut f32,
    ) -> Result<()>;

    /// Process audio samples
    fn on_process_samples(&mut self, buffer: &mut [f32]) -> Result<()> {
        Ok(())
    }

    /// Get the sample rate
    fn sample_rate(&self) -> i32 {
        44100
    }

    /// Get the song BPM
    fn song_bpm(&self) -> i32 {
        120
    }

    /// Get the song position in samples
    fn song_pos(&self) -> i32 {
        0
    }

    /// Get the song position in beats
    fn song_pos_beats(&self) -> f64 {
        0.0
    }
}

/// Video FX plugin trait
pub trait VideoFxPlugin: PluginBase {
    /// Called when the plugin starts
    fn on_start(&mut self) -> Result<()> {
        Ok(())
    }

    /// Called when the plugin stops
    fn on_stop(&mut self) -> Result<()> {
        Ok(())
    }

    /// Draw the video frame
    fn on_draw(&mut self) -> Result<()>;

    /// Called when graphics device is initialized
    fn on_device_init(&mut self) -> Result<()> {
        Ok(())
    }

    /// Called when graphics device is closed
    fn on_device_close(&mut self) -> Result<()> {
        Ok(())
    }

    /// Process audio samples for visualization
    fn on_audio_samples(&mut self, buffer: &[f32]) -> Result<()> {
        Ok(())
    }

    /// Get video width
    fn width(&self) -> i32 {
        1920
    }

    /// Get video height
    fn height(&self) -> i32 {
        1080
    }

    /// Get the sample rate
    fn sample_rate(&self) -> i32 {
        44100
    }

    /// Get the song BPM
    fn song_bpm(&self) -> i32 {
        120
    }

    /// Get the song position in beats
    fn song_pos_beats(&self) -> f64 {
        0.0
    }
}

/// Video transition plugin trait
pub trait VideoTransitionPlugin: PluginBase {
    /// Draw the video transition
    fn on_draw(&mut self, crossfader: f32) -> Result<()>;

    /// Called when graphics device is initialized
    fn on_device_init(&mut self) -> Result<()> {
        Ok(())
    }

    /// Called when graphics device is closed
    fn on_device_close(&mut self) -> Result<()> {
        Ok(())
    }

    /// Get video width
    fn width(&self) -> i32 {
        1920
    }

    /// Get video height
    fn height(&self) -> i32 {
        1080
    }

    /// Get the sample rate
    fn sample_rate(&self) -> i32 {
        44100
    }

    /// Get the song BPM
    fn song_bpm(&self) -> i32 {
        120
    }

    /// Get the song position in beats
    fn song_pos_beats(&self) -> f64 {
        0.0
    }
}

/// Online source plugin trait
pub trait OnlineSourcePlugin: PluginBase {
    /// Check if user is logged in
    fn is_logged(&self) -> Result<bool> {
        Ok(false)
    }

    /// Handle login
    fn on_login(&mut self) -> Result<()> {
        Ok(())
    }

    /// Handle logout
    fn on_logout(&mut self) -> Result<()> {
        Ok(())
    }

    /// Search for tracks
    fn on_search(&mut self, search: &str) -> Result<Vec<SearchResult>> {
        Ok(Vec::new())
    }

    /// Cancel ongoing search
    fn on_search_cancel(&mut self) -> Result<()> {
        Ok(())
    }
}

/// Search result for online sources
#[derive(Debug, Clone)]
pub struct SearchResult {
    pub unique_id: String,
    pub title: String,
    pub artist: String,
    pub genre: Option<String>,
    pub bpm: Option<f32>,
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_error_conversion() {
        let err: PluginError = ffi::E_FAIL.into();
        assert_eq!(err, PluginError::Fail);
    }
}
