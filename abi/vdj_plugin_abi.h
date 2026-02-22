/**
 * VirtualDJ Rust SDK - C ABI Layer
 * 
 * This header defines the C ABI interface that bridges C++ plugin classes
 * to Rust through FFI. All functions and types here use C linkage and are
 * designed to be called from Rust code.
 */

#ifndef VDJ_PLUGIN_ABI_H
#define VDJ_PLUGIN_ABI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

/* ============================================================================
   Basic Types and Constants
   ============================================================================ */

typedef int32_t HRESULT;
typedef uint32_t DWORD;
typedef uint32_t ULONG;

#define S_OK            0x00000000L
#define S_FALSE         0x00000001L
#define E_NOTIMPL       0x80004001L
#define E_FAIL          0x80004005L

/* Plugin parameter types */
#define VDJPARAM_BUTTON             0
#define VDJPARAM_SLIDER             1
#define VDJPARAM_SWITCH             2
#define VDJPARAM_STRING             3
#define VDJPARAM_CUSTOM             4
#define VDJPARAM_RADIO              5
#define VDJPARAM_COMMAND            6
#define VDJPARAM_COLORFX            7
#define VDJPARAM_BEATS              8
#define VDJPARAM_BEATS_RELATIVE     9
#define VDJPARAM_POSITION           10
#define VDJPARAM_RELEASEFX          11
#define VDJPARAM_TRANSITIONFX       12

/* Plugin flags */
#define VDJFLAG_NODOCK              0x1
#define VDJFLAG_PROCESSAFTERSTOP    0x2
#define VDJFLAG_PROCESSFIRST        0x4
#define VDJFLAG_PROCESSLAST         0x8
#define VDJFLAG_EXTENSION1          0x10
#define VDJFLAG_SETPREVIEW          0x20
#define VDJFLAG_POSITION_NOSLIP     0x40
#define VDJFLAG_ALWAYSPREFADER      0x80
#define VDJFLAG_ALWAYSPOSTFADER     0x100
#define VDJFLAG_EPHEMERAL           0x200

/* Video-specific flags */
#define VDJFLAG_VIDEO_MASTERONLY           0x10000
#define VDJFLAG_VIDEO_VISUALISATION        0x20000
#define VDJFLAG_VIDEO_OVERLAY              0x40000
#define VDJFLAG_VIDEO_HASRESIZE            0x80000
#define VDJFLAG_VIDEO_NOAUTOACTIVE         0x200000
#define VDJFLAG_VIDEO_OUTPUTRESOLUTION     0x400000
#define VDJFLAG_VIDEO_OUTPUTASPECTRATIO    0x800000
#define VDJFLAG_VIDEO_FORRECORDING         0x1000000
#define VDJFLAG_VIDEOTRANSITION_CONTINOUS  0x100000

/* Video engines */
typedef enum {
    VdjVideoEngineAny = 0,
    VdjVideoEngineDirectX9 = 1,
    VdjVideoEngineOpenGL = 2,
    VdjVideoEngineDirectX11 = 3,
    VdjVideoEngineOpenGLES2 = 4,
    VdjVideoEngineMetal = 5,
    VdjVideoEngineAnyPtr = 6,
} EVdjVideoEngine;

/* ============================================================================
   Opaque Plugin Handles
   ============================================================================ */

typedef struct VdjPlugin VdjPlugin;
typedef struct VdjPluginDsp VdjPluginDsp;
typedef struct VdjPluginBufferDsp VdjPluginBufferDsp;
typedef struct VdjPluginPositionDsp VdjPluginPositionDsp;
typedef struct VdjPluginVideoFx VdjPluginVideoFx;
typedef struct VdjPluginVideoTransition VdjPluginVideoTransition;
typedef struct VdjPluginVideoTransitionMultiDeck VdjPluginVideoTransitionMultiDeck;
typedef struct VdjPluginOnlineSource VdjPluginOnlineSource;

/* ============================================================================
   Callback Structures
   ============================================================================ */

/**
 * Callbacks provided by VirtualDJ to the plugin
 */
typedef struct {
    HRESULT (*send_command)(VdjPlugin *plugin, const char *command);
    HRESULT (*get_info)(VdjPlugin *plugin, const char *command, double *result);
    HRESULT (*get_string_info)(VdjPlugin *plugin, const char *command, char *result, int size);
    HRESULT (*declare_parameter)(VdjPlugin *plugin, void *parameter, int type, int id, 
                                 const char *name, const char *short_name, float default_value);
    HRESULT (*get_song_buffer)(VdjPlugin *plugin, int pos, int nb, int16_t **buffer);
} VdjCallbacks;

/**
 * Mouse and input callbacks for video plugins
 */
typedef struct {
    int (*on_mouse_move)(VdjPlugin *plugin, int x, int y, int buttons, int key_modifiers);
    int (*on_mouse_down)(VdjPlugin *plugin, int x, int y, int buttons, int key_modifiers);
    int (*on_mouse_up)(VdjPlugin *plugin, int x, int y, int buttons, int key_modifiers);
    void (*on_key)(VdjPlugin *plugin, const char *ch, int vkey, int modifiers, int flag, int scancode);
} VdjVideoMouseCallbacks;

/**
 * Video-specific callbacks
 */
typedef struct {
    HRESULT (*draw_deck)(VdjPlugin *plugin);
    HRESULT (*get_device)(VdjPlugin *plugin, EVdjVideoEngine engine, void **device);
    HRESULT (*get_texture)(VdjPlugin *plugin, EVdjVideoEngine engine, void **texture, void **vertices);
} VdjVideoCallbacks;

/* ============================================================================
   Plugin Info Structure
   ============================================================================ */

typedef struct {
    const char *plugin_name;
    const char *author;
    const char *description;
    const char *version;
    void *bitmap;  /* Platform-specific bitmap */
    DWORD flags;
} VdjPluginInfo;

/* ============================================================================
   Core Plugin Functions
   ============================================================================ */

/**
 * Create a new plugin instance
 */
VdjPlugin* vdj_plugin_create(void);

/**
 * Destroy a plugin instance
 */
void vdj_plugin_release(VdjPlugin *plugin);

/**
 * Initialize the plugin with callbacks from VirtualDJ
 */
HRESULT vdj_plugin_init(VdjPlugin *plugin, const VdjCallbacks *callbacks);

/**
 * Called when plugin is loaded
 */
HRESULT vdj_plugin_on_load(VdjPlugin *plugin);

/**
 * Get plugin info (name, author, description, etc)
 */
HRESULT vdj_plugin_get_info(VdjPlugin *plugin, VdjPluginInfo *info);

/**
 * Called when a parameter is changed
 */
HRESULT vdj_plugin_on_parameter(VdjPlugin *plugin, int id);

/**
 * Get string representation of a parameter
 */
HRESULT vdj_plugin_on_get_parameter_string(VdjPlugin *plugin, int id, char *out_param, int out_param_size);

/* ============================================================================
   DSP Plugin Functions
   ============================================================================ */

/**
 * Create a new DSP plugin instance
 */
VdjPluginDsp* vdj_plugin_dsp_create(void);

/**
 * Destroy a DSP plugin instance
 */
void vdj_plugin_dsp_release(VdjPluginDsp *plugin);

/**
 * Initialize DSP plugin with callbacks
 */
HRESULT vdj_plugin_dsp_init(VdjPluginDsp *plugin, const VdjCallbacks *callbacks);

/**
 * Called when DSP plugin starts
 */
HRESULT vdj_plugin_dsp_on_start(VdjPluginDsp *plugin);

/**
 * Called when DSP plugin stops
 */
HRESULT vdj_plugin_dsp_on_stop(VdjPluginDsp *plugin);

/**
 * Process audio samples
 */
HRESULT vdj_plugin_dsp_on_process_samples(VdjPluginDsp *plugin, float *buffer, int nb);

/**
 * Get DSP plugin info
 */
HRESULT vdj_plugin_dsp_get_info(VdjPluginDsp *plugin, VdjPluginInfo *info);

/**
 * Get DSP sample rate
 */
int vdj_plugin_dsp_get_sample_rate(VdjPluginDsp *plugin);

/**
 * Get DSP song BPM
 */
int vdj_plugin_dsp_get_song_bpm(VdjPluginDsp *plugin);

/**
 * Get DSP song position in beats
 */
double vdj_plugin_dsp_get_song_pos_beats(VdjPluginDsp *plugin);

/* ============================================================================
   Buffer DSP Plugin Functions
   ============================================================================ */

VdjPluginBufferDsp* vdj_plugin_buffer_dsp_create(void);
void vdj_plugin_buffer_dsp_release(VdjPluginBufferDsp *plugin);
HRESULT vdj_plugin_buffer_dsp_init(VdjPluginBufferDsp *plugin, const VdjCallbacks *callbacks);
HRESULT vdj_plugin_buffer_dsp_on_start(VdjPluginBufferDsp *plugin);
HRESULT vdj_plugin_buffer_dsp_on_stop(VdjPluginBufferDsp *plugin);
int16_t* vdj_plugin_buffer_dsp_on_get_song_buffer(VdjPluginBufferDsp *plugin, int song_pos, int nb);
HRESULT vdj_plugin_buffer_dsp_get_song_buffer(VdjPluginBufferDsp *plugin, int pos, int nb, int16_t **buffer);
int vdj_plugin_buffer_dsp_get_sample_rate(VdjPluginBufferDsp *plugin);
int vdj_plugin_buffer_dsp_get_song_bpm(VdjPluginBufferDsp *plugin);
int vdj_plugin_buffer_dsp_get_song_pos(VdjPluginBufferDsp *plugin);
double vdj_plugin_buffer_dsp_get_song_pos_beats(VdjPluginBufferDsp *plugin);

/* ============================================================================
   Position DSP Plugin Functions
   ============================================================================ */

VdjPluginPositionDsp* vdj_plugin_position_dsp_create(void);
void vdj_plugin_position_dsp_release(VdjPluginPositionDsp *plugin);
HRESULT vdj_plugin_position_dsp_init(VdjPluginPositionDsp *plugin, const VdjCallbacks *callbacks);
HRESULT vdj_plugin_position_dsp_on_start(VdjPluginPositionDsp *plugin);
HRESULT vdj_plugin_position_dsp_on_stop(VdjPluginPositionDsp *plugin);
HRESULT vdj_plugin_position_dsp_on_transform_position(VdjPluginPositionDsp *plugin, 
                                                      double *song_pos, double *video_pos, 
                                                      float *volume, float *src_volume);
HRESULT vdj_plugin_position_dsp_on_process_samples(VdjPluginPositionDsp *plugin, float *buffer, int nb);
int vdj_plugin_position_dsp_get_sample_rate(VdjPluginPositionDsp *plugin);
int vdj_plugin_position_dsp_get_song_bpm(VdjPluginPositionDsp *plugin);
int vdj_plugin_position_dsp_get_song_pos(VdjPluginPositionDsp *plugin);
double vdj_plugin_position_dsp_get_song_pos_beats(VdjPluginPositionDsp *plugin);

/* ============================================================================
   Video FX Plugin Functions
   ============================================================================ */

VdjPluginVideoFx* vdj_plugin_video_fx_create(void);
void vdj_plugin_video_fx_release(VdjPluginVideoFx *plugin);
HRESULT vdj_plugin_video_fx_init(VdjPluginVideoFx *plugin, const VdjCallbacks *callbacks, 
                                 const VdjVideoCallbacks *video_callbacks);
HRESULT vdj_plugin_video_fx_on_start(VdjPluginVideoFx *plugin);
HRESULT vdj_plugin_video_fx_on_stop(VdjPluginVideoFx *plugin);
HRESULT vdj_plugin_video_fx_on_draw(VdjPluginVideoFx *plugin);
HRESULT vdj_plugin_video_fx_on_device_init(VdjPluginVideoFx *plugin);
HRESULT vdj_plugin_video_fx_on_device_close(VdjPluginVideoFx *plugin);
HRESULT vdj_plugin_video_fx_on_audio_samples(VdjPluginVideoFx *plugin, float *buffer, int nb);
int vdj_plugin_video_fx_get_width(VdjPluginVideoFx *plugin);
int vdj_plugin_video_fx_get_height(VdjPluginVideoFx *plugin);
int vdj_plugin_video_fx_get_sample_rate(VdjPluginVideoFx *plugin);
int vdj_plugin_video_fx_get_song_bpm(VdjPluginVideoFx *plugin);
double vdj_plugin_video_fx_get_song_pos_beats(VdjPluginVideoFx *plugin);

/* ============================================================================
   Video Transition Plugin Functions
   ============================================================================ */

VdjPluginVideoTransition* vdj_plugin_video_transition_create(void);
void vdj_plugin_video_transition_release(VdjPluginVideoTransition *plugin);
HRESULT vdj_plugin_video_transition_init(VdjPluginVideoTransition *plugin, const VdjCallbacks *callbacks,
                                        const VdjVideoCallbacks *video_callbacks);
HRESULT vdj_plugin_video_transition_on_draw(VdjPluginVideoTransition *plugin, float crossfader);
HRESULT vdj_plugin_video_transition_on_device_init(VdjPluginVideoTransition *plugin);
HRESULT vdj_plugin_video_transition_on_device_close(VdjPluginVideoTransition *plugin);
int vdj_plugin_video_transition_get_width(VdjPluginVideoTransition *plugin);
int vdj_plugin_video_transition_get_height(VdjPluginVideoTransition *plugin);
int vdj_plugin_video_transition_get_sample_rate(VdjPluginVideoTransition *plugin);
int vdj_plugin_video_transition_get_song_bpm(VdjPluginVideoTransition *plugin);
double vdj_plugin_video_transition_get_song_pos_beats(VdjPluginVideoTransition *plugin);

/* ============================================================================
   Online Source Plugin Functions
   ============================================================================ */

VdjPluginOnlineSource* vdj_plugin_online_source_create(void);
void vdj_plugin_online_source_release(VdjPluginOnlineSource *plugin);
HRESULT vdj_plugin_online_source_init(VdjPluginOnlineSource *plugin, const VdjCallbacks *callbacks);
HRESULT vdj_plugin_online_source_is_logged(VdjPluginOnlineSource *plugin);
HRESULT vdj_plugin_online_source_on_login(VdjPluginOnlineSource *plugin);
HRESULT vdj_plugin_online_source_on_logout(VdjPluginOnlineSource *plugin);
HRESULT vdj_plugin_online_source_on_search(VdjPluginOnlineSource *plugin, const char *search, void *tracks_list);
HRESULT vdj_plugin_online_source_on_search_cancel(VdjPluginOnlineSource *plugin);

#ifdef __cplusplus
}
#endif

#endif /* VDJ_PLUGIN_ABI_H */
