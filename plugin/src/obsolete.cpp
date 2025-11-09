#include <hyprland/src/plugins/PluginAPI.hpp>
#include <hyprland/src/helpers/Color.hpp>
#include <string>

// Global plugin handle, required by the API
inline HANDLE PHANDLE = nullptr;

// I DON'T KNOW HOW TO DO CPP ERROR HANDLING
void err_notif(std::string msg) {
    msg = "[hyprkool] " + msg;
    std::cerr << msg << std::endl;
    HyprlandAPI::addNotification(PHANDLE, msg, CHyprColor{1.0, 0.2, 0.2, 1.0}, 5000);
}
void throw_err_notif(std::string msg) {
    err_notif(msg);
    throw std::runtime_error(msg);
}

// Do NOT change this function.
APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    // This is a safety check to prevent crashes from mismatched header versions.
    const std::string HASH = __hyprland_api_get_hash();
    if (HASH != GIT_COMMIT_HASH) {
        // throwing is allowed in init function
        throw_err_notif("Mismatched headers! Can't proceed.");
    }

    // Send the notification to the user.
    HyprlandAPI::addNotification(
        PHANDLE,
        "[hyprkool] This plugin is obsolete and can be safely uninstalled. "
        "Directional workspace animations are now handled by Hyprland directly (v0.51.1+).",
        CHyprColor{1, 1, 0, 1}, // Yellow for warning
        15000               // 15 seconds duration
    );

    // Return a description that also indicates the plugin is obsolete.
    return {"hyprkool", "Grid workspaces for hyprland (this plugin is now obsolete)", "thrombe", VERSION};
}

APICALL EXPORT void PLUGIN_EXIT() {
    // Nothing to clean up.
}
