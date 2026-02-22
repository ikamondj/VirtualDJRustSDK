//! VirtualDJ Rust SDK - FFI Bindings
//! 
//! Raw FFI bindings to the C ABI layer. These are low-level unsafe wrappers
//! around the C ABI functions. Use the safe API in the parent module for higher-level access.

#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

use std::ffi::c_void;

/* ============================================================================
   Types and Constants
   ============================================================================ */

pub type HRESULT = i32;
pub type DWORD = u32;
pub type ULONG = u32;

pub const S_OK: HRESULT = 0x00000000;
pub const S_FALSE: HRESULT = 0x00000001;
pub const E_NOTIMPL: HRESULT = 0x80004001u32 as i32;
pub const E_FAIL: HRESULT = 0x80004005u32 as i32;

/* Plugin parameter types */
pub const VDJPARAM_BUTTON: i32 = 0;
pub const VDJPARAM_SLIDER: i32 = 1;
pub const VDJPARAM_SWITCH: i32 = 2;
pub const VDJPARAM_STRING: i32 = 3;
pub const VDJPARAM_CUSTOM: i32 = 4;
pub const VDJPARAM_RADIO: i32 = 5;
pub const VDJPARAM_COMMAND: i32 = 6;
pub const VDJPARAM_COLORFX: i32 = 7;
pub const VDJPARAM_BEATS: i32 = 8;
pub const VDJPARAM_BEATS_RELATIVE: i32 = 9;
pub const VDJPARAM_POSITION: i32 = 10;
pub const VDJPARAM_RELEASEFX: i32 = 11;
pub const VDJPARAM_TRANSITIONFX: i32 = 12;

/* Plugin flags */
pub const VDJFLAG_NODOCK: DWORD = 0x1;
pub const VDJFLAG_PROCESSAFTERSTOP: DWORD = 0x2;
pub const VDJFLAG_PROCESSFIRST: DWORD = 0x4;
pub const VDJFLAG_PROCESSLAST: DWORD = 0x8;
pub const VDJFLAG_EXTENSION1: DWORD = 0x10;
pub const VDJFLAG_SETPREVIEW: DWORD = 0x20;
pub const VDJFLAG_POSITION_NOSLIP: DWORD = 0x40;
pub const VDJFLAG_ALWAYSPREFADER: DWORD = 0x80;
pub const VDJFLAG_ALWAYSPOSTFADER: DWORD = 0x100;
pub const VDJFLAG_EPHEMERAL: DWORD = 0x200;

/* Video-specific flags */
pub const VDJFLAG_VIDEO_MASTERONLY: DWORD = 0x10000;
pub const VDJFLAG_VIDEO_VISUALISATION: DWORD = 0x20000;
pub const VDJFLAG_VIDEO_OVERLAY: DWORD = 0x40000;
pub const VDJFLAG_VIDEO_HASRESIZE: DWORD = 0x80000;
pub const VDJFLAG_VIDEO_NOAUTOACTIVE: DWORD = 0x200000;
pub const VDJFLAG_VIDEO_OUTPUTRESOLUTION: DWORD = 0x400000;
pub const VDJFLAG_VIDEO_OUTPUTASPECTRATIO: DWORD = 0x800000;
pub const VDJFLAG_VIDEO_FORRECORDING: DWORD = 0x1000000;
pub const VDJFLAG_VIDEOTRANSITION_CONTINOUS: DWORD = 0x100000;

/* Video engines */
#[repr(C)]
#[derive(Clone, Copy, Debug)]
pub enum EVdjVideoEngine {
    VdjVideoEngineAny = 0,
    VdjVideoEngineDirectX9 = 1,
    VdjVideoEngineOpenGL = 2,
    VdjVideoEngineDirectX11 = 3,
    VdjVideoEngineOpenGLES2 = 4,
    VdjVideoEngineMetal = 5,
    VdjVideoEngineAnyPtr = 6,
}

/* ============================================================================
   Opaque Plugin Handles
   ============================================================================ */

#[repr(C)]
pub struct VdjPlugin {
    _priv: [u8; 0],
}

#[repr(C)]
pub struct VdjPluginDsp {
    _priv: [u8; 0],
}

#[repr(C)]
pub struct VdjPluginBufferDsp {
    _priv: [u8; 0],
}

#[repr(C)]
pub struct VdjPluginPositionDsp {
    _priv: [u8; 0],
}

#[repr(C)]
pub struct VdjPluginVideoFx {
    _priv: [u8; 0],
}

#[repr(C)]
pub struct VdjPluginVideoTransition {
    _priv: [u8; 0],
}

#[repr(C)]
pub struct VdjPluginVideoTransitionMultiDeck {
    _priv: [u8; 0],
}

#[repr(C)]
pub struct VdjPluginOnlineSource {
    _priv: [u8; 0],
}

/* ============================================================================
   Callback Structures
   ============================================================================ */

#[repr(C)]
pub struct VdjCallbacks {
    pub send_command: extern "C" fn(*mut VdjPlugin, *const u8) -> HRESULT,
    pub get_info: extern "C" fn(*mut VdjPlugin, *const u8, *mut f64) -> HRESULT,
    pub get_string_info: extern "C" fn(*mut VdjPlugin, *const u8, *mut u8, i32) -> HRESULT,
    pub declare_parameter: extern "C" fn(*mut VdjPlugin, *mut c_void, i32, i32, *const u8, *const u8, f32) -> HRESULT,
    pub get_song_buffer: extern "C" fn(*mut VdjPlugin, i32, i32, *mut *mut i16) -> HRESULT,
}

#[repr(C)]
pub struct VdjVideoMouseCallbacks {
    pub on_mouse_move: extern "C" fn(*mut VdjPlugin, i32, i32, i32, i32) -> i32,
    pub on_mouse_down: extern "C" fn(*mut VdjPlugin, i32, i32, i32, i32) -> i32,
    pub on_mouse_up: extern "C" fn(*mut VdjPlugin, i32, i32, i32, i32) -> i32,
    pub on_key: extern "C" fn(*mut VdjPlugin, *const u8, i32, i32, i32, i32),
}

#[repr(C)]
pub struct VdjVideoCallbacks {
    pub draw_deck: extern "C" fn(*mut VdjPlugin) -> HRESULT,
    pub get_device: extern "C" fn(*mut VdjPlugin, EVdjVideoEngine, *mut *mut c_void) -> HRESULT,
    pub get_texture: extern "C" fn(*mut VdjPlugin, EVdjVideoEngine, *mut *mut c_void, *mut *mut c_void) -> HRESULT,
}

/* ============================================================================
   Plugin Info Structure
   ============================================================================ */

#[repr(C)]
pub struct VdjPluginInfo {
    pub plugin_name: *const u8,
    pub author: *const u8,
    pub description: *const u8,
    pub version: *const u8,
    pub bitmap: *mut c_void,
    pub flags: DWORD,
}

/* ============================================================================
   Core Plugin FFI Functions
   ============================================================================ */

extern "C" {
    pub fn vdj_plugin_create() -> *mut VdjPlugin;
    pub fn vdj_plugin_release(plugin: *mut VdjPlugin);
    pub fn vdj_plugin_init(plugin: *mut VdjPlugin, callbacks: *const VdjCallbacks) -> HRESULT;
    pub fn vdj_plugin_on_load(plugin: *mut VdjPlugin) -> HRESULT;
    pub fn vdj_plugin_get_info(plugin: *mut VdjPlugin, info: *mut VdjPluginInfo) -> HRESULT;
    pub fn vdj_plugin_on_parameter(plugin: *mut VdjPlugin, id: i32) -> HRESULT;
    pub fn vdj_plugin_on_get_parameter_string(plugin: *mut VdjPlugin, id: i32, out_param: *mut u8, out_param_size: i32) -> HRESULT;
}

/* ============================================================================
   DSP Plugin FFI Functions
   ============================================================================ */

extern "C" {
    pub fn vdj_plugin_dsp_create() -> *mut VdjPluginDsp;
    pub fn vdj_plugin_dsp_release(plugin: *mut VdjPluginDsp);
    pub fn vdj_plugin_dsp_init(plugin: *mut VdjPluginDsp, callbacks: *const VdjCallbacks) -> HRESULT;
    pub fn vdj_plugin_dsp_on_start(plugin: *mut VdjPluginDsp) -> HRESULT;
    pub fn vdj_plugin_dsp_on_stop(plugin: *mut VdjPluginDsp) -> HRESULT;
    pub fn vdj_plugin_dsp_on_process_samples(plugin: *mut VdjPluginDsp, buffer: *mut f32, nb: i32) -> HRESULT;
    pub fn vdj_plugin_dsp_get_info(plugin: *mut VdjPluginDsp, info: *mut VdjPluginInfo) -> HRESULT;
    pub fn vdj_plugin_dsp_get_sample_rate(plugin: *mut VdjPluginDsp) -> i32;
    pub fn vdj_plugin_dsp_get_song_bpm(plugin: *mut VdjPluginDsp) -> i32;
    pub fn vdj_plugin_dsp_get_song_pos_beats(plugin: *mut VdjPluginDsp) -> f64;
}

/* ============================================================================
   Buffer DSP Plugin FFI Functions
   ============================================================================ */

extern "C" {
    pub fn vdj_plugin_buffer_dsp_create() -> *mut VdjPluginBufferDsp;
    pub fn vdj_plugin_buffer_dsp_release(plugin: *mut VdjPluginBufferDsp);
    pub fn vdj_plugin_buffer_dsp_init(plugin: *mut VdjPluginBufferDsp, callbacks: *const VdjCallbacks) -> HRESULT;
    pub fn vdj_plugin_buffer_dsp_on_start(plugin: *mut VdjPluginBufferDsp) -> HRESULT;
    pub fn vdj_plugin_buffer_dsp_on_stop(plugin: *mut VdjPluginBufferDsp) -> HRESULT;
    pub fn vdj_plugin_buffer_dsp_on_get_song_buffer(plugin: *mut VdjPluginBufferDsp, song_pos: i32, nb: i32) -> *mut i16;
    pub fn vdj_plugin_buffer_dsp_get_song_buffer(plugin: *mut VdjPluginBufferDsp, pos: i32, nb: i32, buffer: *mut *mut i16) -> HRESULT;
    pub fn vdj_plugin_buffer_dsp_get_sample_rate(plugin: *mut VdjPluginBufferDsp) -> i32;
    pub fn vdj_plugin_buffer_dsp_get_song_bpm(plugin: *mut VdjPluginBufferDsp) -> i32;
    pub fn vdj_plugin_buffer_dsp_get_song_pos(plugin: *mut VdjPluginBufferDsp) -> i32;
    pub fn vdj_plugin_buffer_dsp_get_song_pos_beats(plugin: *mut VdjPluginBufferDsp) -> f64;
}

/* ============================================================================
   Position DSP Plugin FFI Functions
   ============================================================================ */

extern "C" {
    pub fn vdj_plugin_position_dsp_create() -> *mut VdjPluginPositionDsp;
    pub fn vdj_plugin_position_dsp_release(plugin: *mut VdjPluginPositionDsp);
    pub fn vdj_plugin_position_dsp_init(plugin: *mut VdjPluginPositionDsp, callbacks: *const VdjCallbacks) -> HRESULT;
    pub fn vdj_plugin_position_dsp_on_start(plugin: *mut VdjPluginPositionDsp) -> HRESULT;
    pub fn vdj_plugin_position_dsp_on_stop(plugin: *mut VdjPluginPositionDsp) -> HRESULT;
    pub fn vdj_plugin_position_dsp_on_transform_position(plugin: *mut VdjPluginPositionDsp, song_pos: *mut f64, video_pos: *mut f64, volume: *mut f32, src_volume: *mut f32) -> HRESULT;
    pub fn vdj_plugin_position_dsp_on_process_samples(plugin: *mut VdjPluginPositionDsp, buffer: *mut f32, nb: i32) -> HRESULT;
    pub fn vdj_plugin_position_dsp_get_sample_rate(plugin: *mut VdjPluginPositionDsp) -> i32;
    pub fn vdj_plugin_position_dsp_get_song_bpm(plugin: *mut VdjPluginPositionDsp) -> i32;
    pub fn vdj_plugin_position_dsp_get_song_pos(plugin: *mut VdjPluginPositionDsp) -> i32;
    pub fn vdj_plugin_position_dsp_get_song_pos_beats(plugin: *mut VdjPluginPositionDsp) -> f64;
}

/* ============================================================================
   Video FX Plugin FFI Functions
   ============================================================================ */

extern "C" {
    pub fn vdj_plugin_video_fx_create() -> *mut VdjPluginVideoFx;
    pub fn vdj_plugin_video_fx_release(plugin: *mut VdjPluginVideoFx);
    pub fn vdj_plugin_video_fx_init(plugin: *mut VdjPluginVideoFx, callbacks: *const VdjCallbacks, video_callbacks: *const VdjVideoCallbacks) -> HRESULT;
    pub fn vdj_plugin_video_fx_on_start(plugin: *mut VdjPluginVideoFx) -> HRESULT;
    pub fn vdj_plugin_video_fx_on_stop(plugin: *mut VdjPluginVideoFx) -> HRESULT;
    pub fn vdj_plugin_video_fx_on_draw(plugin: *mut VdjPluginVideoFx) -> HRESULT;
    pub fn vdj_plugin_video_fx_on_device_init(plugin: *mut VdjPluginVideoFx) -> HRESULT;
    pub fn vdj_plugin_video_fx_on_device_close(plugin: *mut VdjPluginVideoFx) -> HRESULT;
    pub fn vdj_plugin_video_fx_on_audio_samples(plugin: *mut VdjPluginVideoFx, buffer: *mut f32, nb: i32) -> HRESULT;
    pub fn vdj_plugin_video_fx_get_width(plugin: *mut VdjPluginVideoFx) -> i32;
    pub fn vdj_plugin_video_fx_get_height(plugin: *mut VdjPluginVideoFx) -> i32;
    pub fn vdj_plugin_video_fx_get_sample_rate(plugin: *mut VdjPluginVideoFx) -> i32;
    pub fn vdj_plugin_video_fx_get_song_bpm(plugin: *mut VdjPluginVideoFx) -> i32;
    pub fn vdj_plugin_video_fx_get_song_pos_beats(plugin: *mut VdjPluginVideoFx) -> f64;
}

/* ============================================================================
   Video Transition Plugin FFI Functions
   ============================================================================ */

extern "C" {
    pub fn vdj_plugin_video_transition_create() -> *mut VdjPluginVideoTransition;
    pub fn vdj_plugin_video_transition_release(plugin: *mut VdjPluginVideoTransition);
    pub fn vdj_plugin_video_transition_init(plugin: *mut VdjPluginVideoTransition, callbacks: *const VdjCallbacks, video_callbacks: *const VdjVideoCallbacks) -> HRESULT;
    pub fn vdj_plugin_video_transition_on_draw(plugin: *mut VdjPluginVideoTransition, crossfader: f32) -> HRESULT;
    pub fn vdj_plugin_video_transition_on_device_init(plugin: *mut VdjPluginVideoTransition) -> HRESULT;
    pub fn vdj_plugin_video_transition_on_device_close(plugin: *mut VdjPluginVideoTransition) -> HRESULT;
    pub fn vdj_plugin_video_transition_get_width(plugin: *mut VdjPluginVideoTransition) -> i32;
    pub fn vdj_plugin_video_transition_get_height(plugin: *mut VdjPluginVideoTransition) -> i32;
    pub fn vdj_plugin_video_transition_get_sample_rate(plugin: *mut VdjPluginVideoTransition) -> i32;
    pub fn vdj_plugin_video_transition_get_song_bpm(plugin: *mut VdjPluginVideoTransition) -> i32;
    pub fn vdj_plugin_video_transition_get_song_pos_beats(plugin: *mut VdjPluginVideoTransition) -> f64;
}

/* ============================================================================
   Online Source Plugin FFI Functions
   ============================================================================ */

extern "C" {
    pub fn vdj_plugin_online_source_create() -> *mut VdjPluginOnlineSource;
    pub fn vdj_plugin_online_source_release(plugin: *mut VdjPluginOnlineSource);
    pub fn vdj_plugin_online_source_init(plugin: *mut VdjPluginOnlineSource, callbacks: *const VdjCallbacks) -> HRESULT;
    pub fn vdj_plugin_online_source_is_logged(plugin: *mut VdjPluginOnlineSource) -> HRESULT;
    pub fn vdj_plugin_online_source_on_login(plugin: *mut VdjPluginOnlineSource) -> HRESULT;
    pub fn vdj_plugin_online_source_on_logout(plugin: *mut VdjPluginOnlineSource) -> HRESULT;
    pub fn vdj_plugin_online_source_on_search(plugin: *mut VdjPluginOnlineSource, search: *const u8, tracks_list: *mut c_void) -> HRESULT;
    pub fn vdj_plugin_online_source_on_search_cancel(plugin: *mut VdjPluginOnlineSource) -> HRESULT;
}
