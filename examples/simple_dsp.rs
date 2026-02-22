//! Simple DSP Plugin Example
//! 
//! This example demonstrates how to create a basic DSP (audio effect) plugin
//! using the VirtualDJ Rust SDK. This is meant to be a template for developers
//! who want to write audio effects in Rust.

use virtualdj_plugin_sdk::{DspPlugin, PluginBase, PluginInfo, Result};

/// A simple gain/volume control DSP plugin
pub struct GainPlugin {
    gain: f32,
    sample_rate: i32,
}

impl GainPlugin {
    pub fn new() -> Self {
        GainPlugin {
            gain: 1.0,
            sample_rate: 44100,
        }
    }
}

impl PluginBase for GainPlugin {
    fn on_load(&mut self) -> Result<()> {
        println!("Gain plugin loaded!");
        Ok(())
    }

    fn get_info(&self) -> PluginInfo {
        PluginInfo {
            name: "Simple Gain".to_string(),
            author: "Your Name".to_string(),
            description: "A simple volume gain effect".to_string(),
            version: "1.0.0".to_string(),
            flags: 0,
        }
    }

    fn on_parameter(&mut self, id: i32) -> Result<()> {
        println!("Parameter {} changed", id);
        Ok(())
    }
}

impl DspPlugin for GainPlugin {
    fn on_start(&mut self) -> Result<()> {
        println!("Gain plugin started");
        Ok(())
    }

    fn on_stop(&mut self) -> Result<()> {
        println!("Gain plugin stopped");
        Ok(())
    }

    fn on_process_samples(&mut self, buffer: &mut [f32]) -> Result<()> {
        // Apply gain to all samples (stereo buffer is interleaved)
        for sample in buffer.iter_mut() {
            *sample *= self.gain;
            // Clamp to prevent clipping
            if *sample > 1.0 {
                *sample = 1.0;
            } else if *sample < -1.0 {
                *sample = -1.0;
            }
        }
        Ok(())
    }

    fn sample_rate(&self) -> i32 {
        self.sample_rate
    }

    fn song_bpm(&self) -> i32 {
        120
    }

    fn song_pos_beats(&self) -> f64 {
        0.0
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_plugin_creation() {
        let mut plugin = GainPlugin::new();
        assert!(plugin.on_load().is_ok());
        assert_eq!(plugin.gain, 1.0);
    }

    #[test]
    fn test_gain_processing() {
        let mut plugin = GainPlugin::new();
        plugin.gain = 0.5;
        
        let mut samples = vec![1.0, -1.0, 0.5, -0.5, 2.0, -2.0];
        assert!(plugin.on_process_samples(&mut samples).is_ok());
        
        // Check that samples were scaled
        assert_eq!(samples[0], 0.5);
        assert_eq!(samples[1], -0.5);
        assert_eq!(samples[4], 1.0); // Clipped from 1.0
        assert_eq!(samples[5], -1.0); // Clipped from -1.0
    }
}
