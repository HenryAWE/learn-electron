// Author: HenryAWE
// License: The 3-clause BSD License

#include <memory>
#include <SDL.h>
#include <physfs.h>
#include "app.hpp"
#include "sys/init.hpp"


int SDL_main(int argc, char* argv[])
{
    awe::Prepare(argv[0]);
    awe::InitSDL();
    awe::InitPhysfs(argv[0]);
    PHYSFS_mount(
        std::filesystem::current_path().u8string().c_str(),
        "app",
        true
    );

    auto& app = awe::App::GetInstance();
    app.CreateWindow();

    app.Mainloop();

    app.Quit();

    awe::QuitPhysfs();
    awe::QuitSDL();
    return 0;
}
