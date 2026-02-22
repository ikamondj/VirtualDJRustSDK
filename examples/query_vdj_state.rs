//! VirtualDJ State Query Example
//! 
//! This example demonstrates how to use the PluginContext to safely query
//! VirtualDJ state information like track titles, positions, and BPM values,
//! similar to the UdpSender.cpp example.

use virtualdj_plugin_sdk::{PluginBase, PluginContext, PluginInfo, Result};

/// A plugin that demonstrates querying VirtualDJ state
pub struct StateQueryPlugin {
    // In a real plugin, you would store the PluginContext here
    // for use in your plugin callbacks
}

impl StateQueryPlugin {
    pub fn new() -> Self {
        StateQueryPlugin {}
    }

    /// Example method showing how to query various VirtualDJ state values
    /// This mirrors the pattern used in UdpSender.cpp
    pub fn query_deck_info(&self, context: &PluginContext, deck: i32) -> Result<()> {
        // Get track title (like GetInfoText("deck 1 get_title") in C++)
        let title = context.get_info_string(&format!("deck {} get_title", deck))?;
        println!("Deck {} title: {}", deck, title);

        // Get position as a double (like GetInfoDouble("deck 1 get_position") in C++)
        let position = context.get_info_double(&format!("deck {} get_position", deck))?;
        println!("Deck {} position: {}", deck, position);

        // Check if deck is audible
        let audible = context.get_info_string(&format!("deck {} is_audible", deck))?;
        println!("Deck {} is audible: {}", deck, audible);

        Ok(())
    }

    /// Example showing how to iterate through cues and query their properties
    pub fn query_deck_cues(&self, context: &PluginContext, deck: i32) -> Result<()> {
        // Get track title
        let title = context.get_info_string(&format!("deck {} get_title", deck))?;
        
        // Get current position
        let cursor_percent = context.get_info_double(&format!("deck {} get_position", deck))?;
        
        println!("\nQuerying cues for deck {} ({})", deck, title);
        println!("Current position: {:.2}%", cursor_percent * 100.0);

        // Check cues 1-8 (you can extend to 128 like in the C++ version)
        for cue in 1..=8 {
            // Check if cue exists
            let has_cue = context.get_info_string(&format!("deck {} has_cue {}", deck, cue))?;
            
            if has_cue.to_lowercase() != "on" {
                continue;
            }

            // Get cue name
            let cue_name = context.get_info_string(&format!("deck {} cue_name {}", deck, cue))?;
            
            // Get cue position
            let cue_pos = context.get_info_double(&format!("deck {} cue_pos {}", deck, cue))?;
            
            if cue_pos >= 0.0 {
                println!("  Cue {}: {} (position: {:.2}%)", cue, cue_name, cue_pos * 100.0);
            }
        }

        Ok(())
    }

    /// Example showing how to send commands (like SendCommand in C++)
    pub fn send_example_command(&self, context: &PluginContext) -> Result<()> {
        // Play deck 1
        context.send_command("deck 1 play")?;
        println!("Sent: deck 1 play");

        // You can also use the parsed information to make decisions
        let active_deck_str = context.get_info_string("get_activedeck")?;
        let active_deck: i32 = active_deck_str.parse().unwrap_or(1);
        println!("Active deck: {}", active_deck);

        Ok(())
    }
}

impl PluginBase for StateQueryPlugin {
    fn on_load(&mut self) -> Result<()> {
        println!("State Query Plugin loaded!");
        Ok(())
    }

    fn get_info(&self) -> PluginInfo {
        PluginInfo {
            name: "VDJ State Query Example".to_string(),
            author: "VirtualDJ SDK".to_string(),
            description: "Demonstrates querying VirtualDJ state safely".to_string(),
            version: "1.0.0".to_string(),
            flags: 0,
        }
    }

    fn on_parameter(&mut self, _id: i32) -> Result<()> {
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_state_query_plugin_creation() {
        let plugin = StateQueryPlugin::new();
        let info = plugin.get_info();
        assert_eq!(info.name, "VDJ State Query Example");
    }
}
