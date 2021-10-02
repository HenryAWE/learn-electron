// Author: HenryAWE
// License: The 3-clause BSD License

#include "init.hpp"
#include <SDL.h>
#include <filesystem>
#include <stdexcept>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#endif
#include <physfs.h>


namespace awe
{
    void InitSDL()
    {
        constexpr int required_subsystems =
            SDL_INIT_AUDIO |
            SDL_INIT_VIDEO;

        if(SDL_Init(required_subsystems) < 0)
        {
            throw std::runtime_error(SDL_GetError());
        }

        SDL_version sdl_ver;
        SDL_VERSION(&sdl_ver);
        // runtime version, may be different from the compile-time version
        SDL_version sdl_ver_rt;
        SDL_GetVersion(&sdl_ver_rt);
        SDL_LogInfo(
            SDL_LOG_CATEGORY_APPLICATION,
            "SDL version: %d.%d.%d\n"
            "SDL version (runtime): %d.%d.%d",
            sdl_ver.major, sdl_ver.major, sdl_ver.patch,
            sdl_ver_rt.major, sdl_ver_rt.major, sdl_ver_rt.patch
        );
    }

    void QuitSDL() noexcept
    {
        SDL_Quit();
    }

    void InitPhysfs(const char* argv0)
    {
        if(PHYSFS_init(argv0) == 0)
        {
            throw std::runtime_error(PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        }

        PHYSFS_Version physfs_ver;
        PHYSFS_VERSION(&physfs_ver);
        // runtime version, may be different from the compile-time version
        PHYSFS_Version physfs_ver_rt;
        PHYSFS_getLinkedVersion(&physfs_ver_rt);
        SDL_LogInfo(
            SDL_LOG_CATEGORY_APPLICATION,
            "PhysicsFS version: %d.%d.%d\n"
            "PhysicsFS version (runtime): %d.%d.%d",
            physfs_ver.major, physfs_ver.major, physfs_ver.patch,
            physfs_ver_rt.major, physfs_ver_rt.major, physfs_ver_rt.patch
        );
    }
    void QuitPhysfs() noexcept
    {
        PHYSFS_deinit();
    }

    void Prepare(const char* argv0)
    {
#ifdef _WIN32
        (void)argv0;

        wchar_t buf[MAX_PATH];
        ::GetModuleFileNameW(nullptr, buf, MAX_PATH);

        using namespace std::filesystem;
        std::error_code ec;
        current_path(path(buf).parent_path(), ec);
        if(ec)
        {
            SDL_LogError(
                SDL_LOG_CATEGORY_APPLICATION,
                "Set program execution path failed: %s",
                ec.message().c_str()
            );
        }
#elif defined(__LINUX__)
        std::error_code ec;
        current_path(std::filesystem::path(argv0).parent_path(), ec);
        if(ec)
        {
            SDL_LogError(
                SDL_LOG_CATEGORY_APPLICATION,
                "Set program execution path failed: %s",
                ec.message().c_str()
            );
        }
#else
#error "Unimplemented OS-depended code"
#endif
    }
}
