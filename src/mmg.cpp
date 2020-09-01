#include "mmg.hpp"
#include <iostream>

void run(int argc, char *argv[])
{
    auto world = ECS->Container();

    std::string filename;
    if(argc >= 2) filename = argv[1];
    else filename = "TOWN.ZZT";

    uint8_t board = 0;
    if(argc == 3) board = std::atoi(argv[2]);

    Json::Value zzt_config;
    zzt_config["filename"] = filename;
    zzt_config["board"] = board;
    world->System(SystemLoader::Create("@metaverse-systems/zzt_engine_system", &zzt_config));

    world->Start(1000000 / 30);

    while(ECS->IsRunning())
    {
        usleep(100000);
    }
}

int main(int argc, char *argv[])
{
    try
    {
        run(argc, argv);
    }
    catch(std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
