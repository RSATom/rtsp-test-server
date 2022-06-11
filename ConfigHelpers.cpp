#include "ConfigHelpers.h"

#include <glib.h>


std::deque<std::string> ConfigDirs()
{
    std::deque<std::string> dirs;

#ifdef SNAPCRAFT_BUILD
    if(const gchar* data = g_getenv("SNAP"))
        dirs.push_back(std::string(data) + "/etc");

    if(const gchar* common = g_getenv("SNAP_COMMON"))
        dirs.push_back(common);
#else
    const gchar * const *systemConfigDirs = g_get_system_config_dirs();
    while(*systemConfigDirs) {
        dirs.push_back(*systemConfigDirs);
        ++systemConfigDirs;
    }

    const gchar* configDir = g_get_user_config_dir();
    if(configDir)
        dirs.push_back(configDir);
#endif

    return dirs;
}

std::string FullPath(const std::string& configDir, const std::string& path)
{
    std::string fullPath;
    if(!g_path_is_absolute(path.c_str())) {
        gchar* tmpPath =
            g_build_filename(configDir.c_str(), path.c_str(), NULL);
        fullPath = tmpPath;
        g_free(tmpPath);
    } else
        fullPath = path;

    return fullPath;
}
