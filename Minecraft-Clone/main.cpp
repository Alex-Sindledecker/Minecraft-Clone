#include "Application/Application.h"

int main(int argc, char* argv[])
{
    Application& app = Application::get();

    app.init();
    app.run();
    app.deinit();

    return 0;
}