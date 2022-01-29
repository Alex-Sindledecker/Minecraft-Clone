#include "Application/Application.h"

#include "Utils/Timer.h"

#include <iostream>

int main(int argc, char* argv[])
{
    Application& app = Application::get();

    double time = utils::getElapsedTime<utils::Milliseconds>([&]() {
        app.init();
        app.run();
        app.deinit();
    });

    std::cout << "Total elapsed time: " << utils::millisecondsToSeconds(time) << "s" << std::endl;

    return 0;
}