/**
 * VirtualDJ Rust SDK - C++ Shim Implementation
 * 
 * This file implements the C ABI interface as wrappers around the C++ classes
 * from the VirtualDJ SDK. It bridges the gap between C++ and C/Rust FFI.
 */

#include "../abi/vdj_plugin_abi.h"
#include "../header_ref/vdjPlugin8.h"
#include "../header_ref/vdjDsp8.h"
#include "../header_ref/vdjVideo8.h"
#include "../header_ref/vdjOnlineSource.h"

#include <cstring>
#include <memory>

/* ============================================================================
   Internal Plugin Wrapper Classes
   ============================================================================ */

/**
 * Wrapper around IVdjPlugin8 that stores Rust callbacks
 */
struct VdjPluginWrapper : public IVdjPlugin8 {
    HRESULT VDJ_API OnLoad() override { return S_OK; }
    
    HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8 *info) override { 
        if (info) {
            info->PluginName = "RustPlugin";
            info->Author = "Rust Developer";
            info->Description = "A plugin written in Rust";
            info->Version = "1.0";
            info->Bitmap = nullptr;
            info->Flags = 0;
        }
        return S_OK; 
    }
    
    HRESULT VDJ_API OnParameter(int id) override { return S_OK; }
    
    HRESULT VDJ_API OnGetParameterString(int id, char *outParam, int outParamSize) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnGetUserInterface(TVdjPluginInterface8 *pluginInterface) override { 
        return E_NOTIMPL; 
    }
};

/**
 * Wrapper around IVdjPluginDsp8
 */
struct VdjPluginDspWrapper : public IVdjPluginDsp8 {
    HRESULT VDJ_API OnLoad() override { return S_OK; }
    
    HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8 *info) override { 
        if (info) {
            info->PluginName = "RustDspPlugin";
            info->Author = "Rust Developer";
            info->Description = "A DSP plugin written in Rust";
            info->Version = "1.0";
            info->Bitmap = nullptr;
            info->Flags = 0;
        }
        return S_OK; 
    }
    
    HRESULT VDJ_API OnParameter(int id) override { return S_OK; }
    
    HRESULT VDJ_API OnGetParameterString(int id, char *outParam, int outParamSize) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnGetUserInterface(TVdjPluginInterface8 *pluginInterface) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnStart() override { return S_OK; }
    
    HRESULT VDJ_API OnStop() override { return S_OK; }
    
    HRESULT VDJ_API OnProcessSamples(float *buffer, int nb) override { return S_OK; }
};

/**
 * Wrapper around IVdjPluginBufferDsp8
 */
struct VdjPluginBufferDspWrapper : public IVdjPluginBufferDsp8 {
    HRESULT VDJ_API OnLoad() override { return S_OK; }
    
    HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8 *info) override { 
        if (info) {
            info->PluginName = "RustBufferDspPlugin";
            info->Author = "Rust Developer";
            info->Description = "A buffer DSP plugin written in Rust";
            info->Version = "1.0";
            info->Bitmap = nullptr;
            info->Flags = 0;
        }
        return S_OK; 
    }
    
    HRESULT VDJ_API OnParameter(int id) override { return S_OK; }
    
    HRESULT VDJ_API OnGetParameterString(int id, char *outParam, int outParamSize) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnGetUserInterface(TVdjPluginInterface8 *pluginInterface) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnStart() override { return S_OK; }
    
    HRESULT VDJ_API OnStop() override { return S_OK; }
    
    short* VDJ_API OnGetSongBuffer(int songPos, int nb) override { return nullptr; }
};

/**
 * Wrapper around IVdjPluginPositionDsp8
 */
struct VdjPluginPositionDspWrapper : public IVdjPluginPositionDsp8 {
    HRESULT VDJ_API OnLoad() override { return S_OK; }
    
    HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8 *info) override { 
        if (info) {
            info->PluginName = "RustPositionDspPlugin";
            info->Author = "Rust Developer";
            info->Description = "A position DSP plugin written in Rust";
            info->Version = "1.0";
            info->Bitmap = nullptr;
            info->Flags = 0;
        }
        return S_OK; 
    }
    
    HRESULT VDJ_API OnParameter(int id) override { return S_OK; }
    
    HRESULT VDJ_API OnGetParameterString(int id, char *outParam, int outParamSize) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnGetUserInterface(TVdjPluginInterface8 *pluginInterface) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnStart() override { return S_OK; }
    
    HRESULT VDJ_API OnStop() override { return S_OK; }
    
    HRESULT VDJ_API OnTransformPosition(double *songPos, double *videoPos, float *volume, float *srcVolume) override { 
        return S_OK; 
    }
    
    HRESULT VDJ_API OnProcessSamples(float *buffer, int nb) override { return S_OK; }
};

/**
 * Wrapper around IVdjPluginVideoFx8
 */
struct VdjPluginVideoFxWrapper : public IVdjPluginVideoFx8 {
    HRESULT VDJ_API OnLoad() override { return S_OK; }
    
    HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8 *info) override { 
        if (info) {
            info->PluginName = "RustVideoFxPlugin";
            info->Author = "Rust Developer";
            info->Description = "A video FX plugin written in Rust";
            info->Version = "1.0";
            info->Bitmap = nullptr;
            info->Flags = 0;
        }
        return S_OK; 
    }
    
    HRESULT VDJ_API OnParameter(int id) override { return S_OK; }
    
    HRESULT VDJ_API OnGetParameterString(int id, char *outParam, int outParamSize) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnGetUserInterface(TVdjPluginInterface8 *pluginInterface) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnStart() override { return S_OK; }
    
    HRESULT VDJ_API OnStop() override { return S_OK; }
    
    HRESULT VDJ_API OnDraw() override { return S_OK; }
    
    HRESULT VDJ_API OnDeviceInit() override { return S_OK; }
    
    HRESULT VDJ_API OnDeviceClose() override { return S_OK; }
    
    HRESULT VDJ_API OnAudioSamples(float *buffer, int nb) override { return E_NOTIMPL; }
};

/**
 * Wrapper around IVdjPluginVideoTransition8
 */
struct VdjPluginVideoTransitionWrapper : public IVdjPluginVideoTransition8 {
    HRESULT VDJ_API OnLoad() override { return S_OK; }
    
    HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8 *info) override { 
        if (info) {
            info->PluginName = "RustVideoTransitionPlugin";
            info->Author = "Rust Developer";
            info->Description = "A video transition plugin written in Rust";
            info->Version = "1.0";
            info->Bitmap = nullptr;
            info->Flags = 0;
        }
        return S_OK; 
    }
    
    HRESULT VDJ_API OnParameter(int id) override { return S_OK; }
    
    HRESULT VDJ_API OnGetParameterString(int id, char *outParam, int outParamSize) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnGetUserInterface(TVdjPluginInterface8 *pluginInterface) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnDraw(float crossfader) override { return S_OK; }
    
    HRESULT VDJ_API OnDeviceInit() override { return S_OK; }
    
    HRESULT VDJ_API OnDeviceClose() override { return S_OK; }
};

/**
 * Wrapper around IVdjPluginOnlineSource
 */
struct VdjPluginOnlineSourceWrapper : public IVdjPluginOnlineSource {
    HRESULT VDJ_API OnLoad() override { return S_OK; }
    
    HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8 *info) override { 
        if (info) {
            info->PluginName = "RustOnlineSourcePlugin";
            info->Author = "Rust Developer";
            info->Description = "An online source plugin written in Rust";
            info->Version = "1.0";
            info->Bitmap = nullptr;
            info->Flags = 0;
        }
        return S_OK; 
    }
    
    HRESULT VDJ_API OnParameter(int id) override { return S_OK; }
    
    HRESULT VDJ_API OnGetParameterString(int id, char *outParam, int outParamSize) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnGetUserInterface(TVdjPluginInterface8 *pluginInterface) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API IsLogged() override { return E_NOTIMPL; }
    
    HRESULT VDJ_API OnLogin() override { return E_NOTIMPL; }
    
    HRESULT VDJ_API OnLogout() override { return E_NOTIMPL; }
    
    HRESULT VDJ_API OnOAuth(const char* access_token, size_t access_token_expire, 
                    const char* refresh_token, const char* code, 
                    const char* errorMessage) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnSearch(const char *search, IVdjTracksList *tracksList) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnSearchCancel() override { return E_NOTIMPL; }
    
    HRESULT VDJ_API GetStreamUrl(const char *uniqueId, IVdjString& url, IVdjString& errorMessage) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API GetFolderList(IVdjSubfoldersList *subfoldersList) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API GetFolder(const char *folderUniqueId, IVdjTracksList *tracksList) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API GetContextMenu(const char *uniqueId, IVdjContextMenu *contextMenu) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnContextMenu(const char *uniqueId, size_t menuIndex) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API GetFolderContextMenu(const char *folderUniqueId, IVdjContextMenu *contextMenu) override { 
        return E_NOTIMPL; 
    }
    
    HRESULT VDJ_API OnFolderContextMenu(const char *folderUniqueId, size_t menuIndex) override { 
        return E_NOTIMPL; 
    }
};

/* ============================================================================
   Core Plugin C ABI Functions
   ============================================================================ */

extern "C" {

VdjPlugin* vdj_plugin_create(void) {
    return reinterpret_cast<VdjPlugin*>(new VdjPluginWrapper());
}

void vdj_plugin_release(VdjPlugin *plugin) {
    if (plugin) {
        IVdjPlugin8 *p = reinterpret_cast<IVdjPlugin8*>(plugin);
        delete p;
    }
}

HRESULT vdj_plugin_init(VdjPlugin *plugin, const VdjCallbacks *callbacks) {
    if (!plugin || !callbacks) return E_FAIL;
    
    IVdjPlugin8 *p = reinterpret_cast<IVdjPlugin8*>(plugin);
    
    // Create a simple IVdjCallbacks8 adapter
    struct CallbacksAdapter : public IVdjCallbacks8 {
        const VdjCallbacks *c_callbacks;
        VdjPlugin *plugin;
        
        HRESULT SendCommand(const char *command) override {
            return c_callbacks->send_command(plugin, command);
        }
        HRESULT GetInfo(const char *command, double *result) override {
            return c_callbacks->get_info(plugin, command, result);
        }
        HRESULT GetStringInfo(const char *command, void *result, int size) override {
            return c_callbacks->get_string_info(plugin, command, (char*)result, size);
        }
        HRESULT DeclareParameter(void *parameter, int type, int id, const char *name, 
                                const char *shortName, float defaultvalue) override {
            return c_callbacks->declare_parameter(plugin, parameter, type, id, name, shortName, defaultvalue);
        }
        HRESULT GetSongBuffer(int pos, int nb, short **buffer) override {
            return c_callbacks->get_song_buffer(plugin, pos, nb, buffer);
        }
    };
    
    CallbacksAdapter *adapter = new CallbacksAdapter();
    adapter->c_callbacks = callbacks;
    adapter->plugin = plugin;
    p->cb = adapter;
    
    return p->OnLoad();
}

HRESULT vdj_plugin_on_load(VdjPlugin *plugin) {
    if (!plugin) return E_FAIL;
    IVdjPlugin8 *p = reinterpret_cast<IVdjPlugin8*>(plugin);
    return p->OnLoad();
}

HRESULT vdj_plugin_get_info(VdjPlugin *plugin, VdjPluginInfo *info) {
    if (!plugin || !info) return E_FAIL;
    IVdjPlugin8 *p = reinterpret_cast<IVdjPlugin8*>(plugin);
    
    TVdjPluginInfo8 cpp_info = {};
    HRESULT hr = p->OnGetPluginInfo(&cpp_info);
    
    info->plugin_name = cpp_info.PluginName;
    info->author = cpp_info.Author;
    info->description = cpp_info.Description;
    info->version = cpp_info.Version;
    info->bitmap = cpp_info.Bitmap;
    info->flags = cpp_info.Flags;
    
    return hr;
}

HRESULT vdj_plugin_on_parameter(VdjPlugin *plugin, int id) {
    if (!plugin) return E_FAIL;
    IVdjPlugin8 *p = reinterpret_cast<IVdjPlugin8*>(plugin);
    return p->OnParameter(id);
}

HRESULT vdj_plugin_on_get_parameter_string(VdjPlugin *plugin, int id, char *out_param, int out_param_size) {
    if (!plugin) return E_FAIL;
    IVdjPlugin8 *p = reinterpret_cast<IVdjPlugin8*>(plugin);
    return p->OnGetParameterString(id, out_param, out_param_size);
}

/* ============================================================================
   DSP Plugin C ABI Functions
   ============================================================================ */

VdjPluginDsp* vdj_plugin_dsp_create(void) {
    return reinterpret_cast<VdjPluginDsp*>(new VdjPluginDspWrapper());
}

void vdj_plugin_dsp_release(VdjPluginDsp *plugin) {
    if (plugin) {
        IVdjPluginDsp8 *p = reinterpret_cast<IVdjPluginDsp8*>(plugin);
        delete p;
    }
}

HRESULT vdj_plugin_dsp_init(VdjPluginDsp *plugin, const VdjCallbacks *callbacks) {
    if (!plugin || !callbacks) return E_FAIL;
    
    IVdjPluginDsp8 *p = reinterpret_cast<IVdjPluginDsp8*>(plugin);
    
    struct CallbacksAdapter : public IVdjCallbacks8 {
        const VdjCallbacks *c_callbacks;
        VdjPlugin *plugin;
        
        HRESULT SendCommand(const char *command) override {
            return c_callbacks->send_command(plugin, command);
        }
        HRESULT GetInfo(const char *command, double *result) override {
            return c_callbacks->get_info(plugin, command, result);
        }
        HRESULT GetStringInfo(const char *command, void *result, int size) override {
            return c_callbacks->get_string_info(plugin, command, (char*)result, size);
        }
        HRESULT DeclareParameter(void *parameter, int type, int id, const char *name, 
                                const char *shortName, float defaultvalue) override {
            return c_callbacks->declare_parameter(plugin, parameter, type, id, name, shortName, defaultvalue);
        }
        HRESULT GetSongBuffer(int pos, int nb, short **buffer) override {
            return c_callbacks->get_song_buffer(plugin, pos, nb, buffer);
        }
    };
    
    CallbacksAdapter *adapter = new CallbacksAdapter();
    adapter->c_callbacks = callbacks;
    adapter->plugin = reinterpret_cast<VdjPlugin*>(plugin);
    p->cb = adapter;
    
    return S_OK;
}

HRESULT vdj_plugin_dsp_on_start(VdjPluginDsp *plugin) {
    if (!plugin) return E_FAIL;
    IVdjPluginDsp8 *p = reinterpret_cast<IVdjPluginDsp8*>(plugin);
    return p->OnStart();
}

HRESULT vdj_plugin_dsp_on_stop(VdjPluginDsp *plugin) {
    if (!plugin) return E_FAIL;
    IVdjPluginDsp8 *p = reinterpret_cast<IVdjPluginDsp8*>(plugin);
    return p->OnStop();
}

HRESULT vdj_plugin_dsp_on_process_samples(VdjPluginDsp *plugin, float *buffer, int nb) {
    if (!plugin) return E_FAIL;
    IVdjPluginDsp8 *p = reinterpret_cast<IVdjPluginDsp8*>(plugin);
    return p->OnProcessSamples(buffer, nb);
}

HRESULT vdj_plugin_dsp_get_info(VdjPluginDsp *plugin, VdjPluginInfo *info) {
    if (!plugin || !info) return E_FAIL;
    IVdjPluginDsp8 *p = reinterpret_cast<IVdjPluginDsp8*>(plugin);
    
    TVdjPluginInfo8 cpp_info = {};
    HRESULT hr = p->OnGetPluginInfo(&cpp_info);
    
    info->plugin_name = cpp_info.PluginName;
    info->author = cpp_info.Author;
    info->description = cpp_info.Description;
    info->version = cpp_info.Version;
    info->bitmap = cpp_info.Bitmap;
    info->flags = cpp_info.Flags;
    
    return hr;
}

int vdj_plugin_dsp_get_sample_rate(VdjPluginDsp *plugin) {
    if (!plugin) return 0;
    IVdjPluginDsp8 *p = reinterpret_cast<IVdjPluginDsp8*>(plugin);
    return p->SampleRate;
}

int vdj_plugin_dsp_get_song_bpm(VdjPluginDsp *plugin) {
    if (!plugin) return 0;
    IVdjPluginDsp8 *p = reinterpret_cast<IVdjPluginDsp8*>(plugin);
    return p->SongBpm;
}

double vdj_plugin_dsp_get_song_pos_beats(VdjPluginDsp *plugin) {
    if (!plugin) return 0.0;
    IVdjPluginDsp8 *p = reinterpret_cast<IVdjPluginDsp8*>(plugin);
    return p->SongPosBeats;
}

/* ============================================================================
   Buffer DSP Plugin C ABI Functions
   ============================================================================ */

VdjPluginBufferDsp* vdj_plugin_buffer_dsp_create(void) {
    return reinterpret_cast<VdjPluginBufferDsp*>(new VdjPluginBufferDspWrapper());
}

void vdj_plugin_buffer_dsp_release(VdjPluginBufferDsp *plugin) {
    if (plugin) {
        IVdjPluginBufferDsp8 *p = reinterpret_cast<IVdjPluginBufferDsp8*>(plugin);
        delete p;
    }
}

HRESULT vdj_plugin_buffer_dsp_init(VdjPluginBufferDsp *plugin, const VdjCallbacks *callbacks) {
    if (!plugin || !callbacks) return E_FAIL;
    
    IVdjPluginBufferDsp8 *p = reinterpret_cast<IVdjPluginBufferDsp8*>(plugin);
    
    struct CallbacksAdapter : public IVdjCallbacks8 {
        const VdjCallbacks *c_callbacks;
        VdjPlugin *plugin;
        
        HRESULT SendCommand(const char *command) override {
            return c_callbacks->send_command(plugin, command);
        }
        HRESULT GetInfo(const char *command, double *result) override {
            return c_callbacks->get_info(plugin, command, result);
        }
        HRESULT GetStringInfo(const char *command, void *result, int size) override {
            return c_callbacks->get_string_info(plugin, command, (char*)result, size);
        }
        HRESULT DeclareParameter(void *parameter, int type, int id, const char *name, 
                                const char *shortName, float defaultvalue) override {
            return c_callbacks->declare_parameter(plugin, parameter, type, id, name, shortName, defaultvalue);
        }
        HRESULT GetSongBuffer(int pos, int nb, short **buffer) override {
            return c_callbacks->get_song_buffer(plugin, pos, nb, buffer);
        }
    };
    
    CallbacksAdapter *adapter = new CallbacksAdapter();
    adapter->c_callbacks = callbacks;
    adapter->plugin = reinterpret_cast<VdjPlugin*>(plugin);
    p->cb = adapter;
    
    return S_OK;
}

HRESULT vdj_plugin_buffer_dsp_on_start(VdjPluginBufferDsp *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginBufferDsp8*>(plugin)->OnStart();
}

HRESULT vdj_plugin_buffer_dsp_on_stop(VdjPluginBufferDsp *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginBufferDsp8*>(plugin)->OnStop();
}

int16_t* vdj_plugin_buffer_dsp_on_get_song_buffer(VdjPluginBufferDsp *plugin, int song_pos, int nb) {
    if (!plugin) return nullptr;
    return reinterpret_cast<IVdjPluginBufferDsp8*>(plugin)->OnGetSongBuffer(song_pos, nb);
}

HRESULT vdj_plugin_buffer_dsp_get_song_buffer(VdjPluginBufferDsp *plugin, int pos, int nb, int16_t **buffer) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginBufferDsp8*>(plugin)->GetSongBuffer(pos, nb, buffer);
}

int vdj_plugin_buffer_dsp_get_sample_rate(VdjPluginBufferDsp *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginBufferDsp8*>(plugin)->SampleRate;
}

int vdj_plugin_buffer_dsp_get_song_bpm(VdjPluginBufferDsp *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginBufferDsp8*>(plugin)->SongBpm;
}

int vdj_plugin_buffer_dsp_get_song_pos(VdjPluginBufferDsp *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginBufferDsp8*>(plugin)->SongPos;
}

double vdj_plugin_buffer_dsp_get_song_pos_beats(VdjPluginBufferDsp *plugin) {
    if (!plugin) return 0.0;
    return reinterpret_cast<IVdjPluginBufferDsp8*>(plugin)->SongPosBeats;
}

/* ============================================================================
   Position DSP Plugin C ABI Functions
   ============================================================================ */

VdjPluginPositionDsp* vdj_plugin_position_dsp_create(void) {
    return reinterpret_cast<VdjPluginPositionDsp*>(new VdjPluginPositionDspWrapper());
}

void vdj_plugin_position_dsp_release(VdjPluginPositionDsp *plugin) {
    if (plugin) {
        IVdjPluginPositionDsp8 *p = reinterpret_cast<IVdjPluginPositionDsp8*>(plugin);
        delete p;
    }
}

HRESULT vdj_plugin_position_dsp_init(VdjPluginPositionDsp *plugin, const VdjCallbacks *callbacks) {
    if (!plugin || !callbacks) return E_FAIL;
    
    IVdjPluginPositionDsp8 *p = reinterpret_cast<IVdjPluginPositionDsp8*>(plugin);
    
    struct CallbacksAdapter : public IVdjCallbacks8 {
        const VdjCallbacks *c_callbacks;
        VdjPlugin *plugin;
        
        HRESULT SendCommand(const char *command) override {
            return c_callbacks->send_command(plugin, command);
        }
        HRESULT GetInfo(const char *command, double *result) override {
            return c_callbacks->get_info(plugin, command, result);
        }
        HRESULT GetStringInfo(const char *command, void *result, int size) override {
            return c_callbacks->get_string_info(plugin, command, (char*)result, size);
        }
        HRESULT DeclareParameter(void *parameter, int type, int id, const char *name, 
                                const char *shortName, float defaultvalue) override {
            return c_callbacks->declare_parameter(plugin, parameter, type, id, name, shortName, defaultvalue);
        }
        HRESULT GetSongBuffer(int pos, int nb, short **buffer) override {
            return c_callbacks->get_song_buffer(plugin, pos, nb, buffer);
        }
    };
    
    CallbacksAdapter *adapter = new CallbacksAdapter();
    adapter->c_callbacks = callbacks;
    adapter->plugin = reinterpret_cast<VdjPlugin*>(plugin);
    p->cb = adapter;
    
    return S_OK;
}

HRESULT vdj_plugin_position_dsp_on_start(VdjPluginPositionDsp *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginPositionDsp8*>(plugin)->OnStart();
}

HRESULT vdj_plugin_position_dsp_on_stop(VdjPluginPositionDsp *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginPositionDsp8*>(plugin)->OnStop();
}

HRESULT vdj_plugin_position_dsp_on_transform_position(VdjPluginPositionDsp *plugin, 
                                                      double *song_pos, double *video_pos, 
                                                      float *volume, float *src_volume) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginPositionDsp8*>(plugin)->OnTransformPosition(song_pos, video_pos, volume, src_volume);
}

HRESULT vdj_plugin_position_dsp_on_process_samples(VdjPluginPositionDsp *plugin, float *buffer, int nb) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginPositionDsp8*>(plugin)->OnProcessSamples(buffer, nb);
}

int vdj_plugin_position_dsp_get_sample_rate(VdjPluginPositionDsp *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginPositionDsp8*>(plugin)->SampleRate;
}

int vdj_plugin_position_dsp_get_song_bpm(VdjPluginPositionDsp *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginPositionDsp8*>(plugin)->SongBpm;
}

int vdj_plugin_position_dsp_get_song_pos(VdjPluginPositionDsp *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginPositionDsp8*>(plugin)->SongPos;
}

double vdj_plugin_position_dsp_get_song_pos_beats(VdjPluginPositionDsp *plugin) {
    if (!plugin) return 0.0;
    return reinterpret_cast<IVdjPluginPositionDsp8*>(plugin)->SongPosBeats;
}

/* ============================================================================
   Video FX Plugin C ABI Functions
   ============================================================================ */

VdjPluginVideoFx* vdj_plugin_video_fx_create(void) {
    return reinterpret_cast<VdjPluginVideoFx*>(new VdjPluginVideoFxWrapper());
}

void vdj_plugin_video_fx_release(VdjPluginVideoFx *plugin) {
    if (plugin) {
        IVdjPluginVideoFx8 *p = reinterpret_cast<IVdjPluginVideoFx8*>(plugin);
        delete p;
    }
}

HRESULT vdj_plugin_video_fx_init(VdjPluginVideoFx *plugin, const VdjCallbacks *callbacks, 
                                 const VdjVideoCallbacks *video_callbacks) {
    if (!plugin || !callbacks || !video_callbacks) return E_FAIL;
    
    IVdjPluginVideoFx8 *p = reinterpret_cast<IVdjPluginVideoFx8*>(plugin);
    
    struct CallbacksAdapter : public IVdjCallbacks8 {
        const VdjCallbacks *c_callbacks;
        VdjPlugin *plugin;
        
        HRESULT SendCommand(const char *command) override {
            return c_callbacks->send_command(plugin, command);
        }
        HRESULT GetInfo(const char *command, double *result) override {
            return c_callbacks->get_info(plugin, command, result);
        }
        HRESULT GetStringInfo(const char *command, void *result, int size) override {
            return c_callbacks->get_string_info(plugin, command, (char*)result, size);
        }
        HRESULT DeclareParameter(void *parameter, int type, int id, const char *name, 
                                const char *shortName, float defaultvalue) override {
            return c_callbacks->declare_parameter(plugin, parameter, type, id, name, shortName, defaultvalue);
        }
        HRESULT GetSongBuffer(int pos, int nb, short **buffer) override {
            return c_callbacks->get_song_buffer(plugin, pos, nb, buffer);
        }
    };
    
    CallbacksAdapter *adapter = new CallbacksAdapter();
    adapter->c_callbacks = callbacks;
    adapter->plugin = reinterpret_cast<VdjPlugin*>(plugin);
    p->cb = adapter;
    
    struct VideoCallbacksAdapter : public IVdjVideoCallbacks8 {
        const VdjVideoCallbacks *c_callbacks;
        VdjPlugin *plugin;
        
        HRESULT DrawDeck() override {
            return c_callbacks->draw_deck(plugin);
        }
        HRESULT GetDevice(EVdjVideoEngine engine, void **device) override {
            return c_callbacks->get_device(plugin, engine, device);
        }
        HRESULT GetTexture(EVdjVideoEngine engine, void **texture, TVertex **vertices) override {
            return c_callbacks->get_texture(plugin, engine, texture, vertices);
        }
    };
    
    VideoCallbacksAdapter *video_adapter = new VideoCallbacksAdapter();
    video_adapter->c_callbacks = video_callbacks;
    video_adapter->plugin = reinterpret_cast<VdjPlugin*>(plugin);
    p->vcb = video_adapter;
    
    return S_OK;
}

HRESULT vdj_plugin_video_fx_on_start(VdjPluginVideoFx *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginVideoFx8*>(plugin)->OnStart();
}

HRESULT vdj_plugin_video_fx_on_stop(VdjPluginVideoFx *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginVideoFx8*>(plugin)->OnStop();
}

HRESULT vdj_plugin_video_fx_on_draw(VdjPluginVideoFx *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginVideoFx8*>(plugin)->OnDraw();
}

HRESULT vdj_plugin_video_fx_on_device_init(VdjPluginVideoFx *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginVideoFx8*>(plugin)->OnDeviceInit();
}

HRESULT vdj_plugin_video_fx_on_device_close(VdjPluginVideoFx *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginVideoFx8*>(plugin)->OnDeviceClose();
}

HRESULT vdj_plugin_video_fx_on_audio_samples(VdjPluginVideoFx *plugin, float *buffer, int nb) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginVideoFx8*>(plugin)->OnAudioSamples(buffer, nb);
}

int vdj_plugin_video_fx_get_width(VdjPluginVideoFx *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginVideoFx8*>(plugin)->width;
}

int vdj_plugin_video_fx_get_height(VdjPluginVideoFx *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginVideoFx8*>(plugin)->height;
}

int vdj_plugin_video_fx_get_sample_rate(VdjPluginVideoFx *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginVideoFx8*>(plugin)->SampleRate;
}

int vdj_plugin_video_fx_get_song_bpm(VdjPluginVideoFx *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginVideoFx8*>(plugin)->SongBpm;
}

double vdj_plugin_video_fx_get_song_pos_beats(VdjPluginVideoFx *plugin) {
    if (!plugin) return 0.0;
    return reinterpret_cast<IVdjPluginVideoFx8*>(plugin)->SongPosBeats;
}

/* ============================================================================
   Video Transition Plugin C ABI Functions
   ============================================================================ */

VdjPluginVideoTransition* vdj_plugin_video_transition_create(void) {
    return reinterpret_cast<VdjPluginVideoTransition*>(new VdjPluginVideoTransitionWrapper());
}

void vdj_plugin_video_transition_release(VdjPluginVideoTransition *plugin) {
    if (plugin) {
        IVdjPluginVideoTransition8 *p = reinterpret_cast<IVdjPluginVideoTransition8*>(plugin);
        delete p;
    }
}

HRESULT vdj_plugin_video_transition_init(VdjPluginVideoTransition *plugin, const VdjCallbacks *callbacks,
                                        const VdjVideoCallbacks *video_callbacks) {
    if (!plugin || !callbacks || !video_callbacks) return E_FAIL;
    
    IVdjPluginVideoTransition8 *p = reinterpret_cast<IVdjPluginVideoTransition8*>(plugin);
    
    struct CallbacksAdapter : public IVdjCallbacks8 {
        const VdjCallbacks *c_callbacks;
        VdjPlugin *plugin;
        
        HRESULT SendCommand(const char *command) override {
            return c_callbacks->send_command(plugin, command);
        }
        HRESULT GetInfo(const char *command, double *result) override {
            return c_callbacks->get_info(plugin, command, result);
        }
        HRESULT GetStringInfo(const char *command, void *result, int size) override {
            return c_callbacks->get_string_info(plugin, command, (char*)result, size);
        }
        HRESULT DeclareParameter(void *parameter, int type, int id, const char *name, 
                                const char *shortName, float defaultvalue) override {
            return c_callbacks->declare_parameter(plugin, parameter, type, id, name, shortName, defaultvalue);
        }
        HRESULT GetSongBuffer(int pos, int nb, short **buffer) override {
            return c_callbacks->get_song_buffer(plugin, pos, nb, buffer);
        }
    };
    
    CallbacksAdapter *adapter = new CallbacksAdapter();
    adapter->c_callbacks = callbacks;
    adapter->plugin = reinterpret_cast<VdjPlugin*>(plugin);
    p->cb = adapter;
    
    // Note: Video transition has different callback setup
    // This is simplified for now
    
    return S_OK;
}

HRESULT vdj_plugin_video_transition_on_draw(VdjPluginVideoTransition *plugin, float crossfader) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginVideoTransition8*>(plugin)->OnDraw(crossfader);
}

HRESULT vdj_plugin_video_transition_on_device_init(VdjPluginVideoTransition *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginVideoTransition8*>(plugin)->OnDeviceInit();
}

HRESULT vdj_plugin_video_transition_on_device_close(VdjPluginVideoTransition *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginVideoTransition8*>(plugin)->OnDeviceClose();
}

int vdj_plugin_video_transition_get_width(VdjPluginVideoTransition *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginVideoTransition8*>(plugin)->width;
}

int vdj_plugin_video_transition_get_height(VdjPluginVideoTransition *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginVideoTransition8*>(plugin)->height;
}

int vdj_plugin_video_transition_get_sample_rate(VdjPluginVideoTransition *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginVideoTransition8*>(plugin)->SampleRate;
}

int vdj_plugin_video_transition_get_song_bpm(VdjPluginVideoTransition *plugin) {
    if (!plugin) return 0;
    return reinterpret_cast<IVdjPluginVideoTransition8*>(plugin)->SongBpm;
}

double vdj_plugin_video_transition_get_song_pos_beats(VdjPluginVideoTransition *plugin) {
    if (!plugin) return 0.0;
    return reinterpret_cast<IVdjPluginVideoTransition8*>(plugin)->SongPosBeats;
}

/* ============================================================================
   Online Source Plugin C ABI Functions
   ============================================================================ */

VdjPluginOnlineSource* vdj_plugin_online_source_create(void) {
    return reinterpret_cast<VdjPluginOnlineSource*>(new VdjPluginOnlineSourceWrapper());
}

void vdj_plugin_online_source_release(VdjPluginOnlineSource *plugin) {
    if (plugin) {
        IVdjPluginOnlineSource *p = reinterpret_cast<IVdjPluginOnlineSource*>(plugin);
        delete p;
    }
}

HRESULT vdj_plugin_online_source_init(VdjPluginOnlineSource *plugin, const VdjCallbacks *callbacks) {
    if (!plugin || !callbacks) return E_FAIL;
    
    IVdjPluginOnlineSource *p = reinterpret_cast<IVdjPluginOnlineSource*>(plugin);
    
    struct CallbacksAdapter : public IVdjCallbacks8 {
        const VdjCallbacks *c_callbacks;
        VdjPlugin *plugin;
        
        HRESULT SendCommand(const char *command) override {
            return c_callbacks->send_command(plugin, command);
        }
        HRESULT GetInfo(const char *command, double *result) override {
            return c_callbacks->get_info(plugin, command, result);
        }
        HRESULT GetStringInfo(const char *command, void *result, int size) override {
            return c_callbacks->get_string_info(plugin, command, (char*)result, size);
        }
        HRESULT DeclareParameter(void *parameter, int type, int id, const char *name, 
                                const char *shortName, float defaultvalue) override {
            return c_callbacks->declare_parameter(plugin, parameter, type, id, name, shortName, defaultvalue);
        }
        HRESULT GetSongBuffer(int pos, int nb, short **buffer) override {
            return c_callbacks->get_song_buffer(plugin, pos, nb, buffer);
        }
    };
    
    CallbacksAdapter *adapter = new CallbacksAdapter();
    adapter->c_callbacks = callbacks;
    adapter->plugin = reinterpret_cast<VdjPlugin*>(plugin);
    p->cb = adapter;
    
    return S_OK;
}

HRESULT vdj_plugin_online_source_is_logged(VdjPluginOnlineSource *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginOnlineSource*>(plugin)->IsLogged();
}

HRESULT vdj_plugin_online_source_on_login(VdjPluginOnlineSource *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginOnlineSource*>(plugin)->OnLogin();
}

HRESULT vdj_plugin_online_source_on_logout(VdjPluginOnlineSource *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginOnlineSource*>(plugin)->OnLogout();
}

HRESULT vdj_plugin_online_source_on_search(VdjPluginOnlineSource *plugin, const char *search, void *tracks_list) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginOnlineSource*>(plugin)->OnSearch(search, (IVdjTracksList*)tracks_list);
}

HRESULT vdj_plugin_online_source_on_search_cancel(VdjPluginOnlineSource *plugin) {
    if (!plugin) return E_FAIL;
    return reinterpret_cast<IVdjPluginOnlineSource*>(plugin)->OnSearchCancel();
}

} // extern "C"
