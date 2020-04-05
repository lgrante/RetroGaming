#include "Main.hpp"
#include "Core.hpp"

int main(int argc, char **argv)
{
    Core core;

    if (argc != 2) {
        std::cout << "./arcade [libray_name].so" << std::endl;
        return 84;
    }
    core.setModule(std::string(argv[1]));
    core.launch(std::string(argv[1]));
    return 0;
}