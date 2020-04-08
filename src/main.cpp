#include "Main.hpp"
#include "Core.hpp"

int main(int argc, char **argv)
{
    Core core;

    if (argc != 2) {
        std::cout << "./arcade [libray_name].so" << std::endl;
        return 84;
    }
    try {
        core.setModule(std::string(argv[1]));
        core.launch(std::string(argv[1]));
    } catch(const ArcadeException &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    return 0;
}