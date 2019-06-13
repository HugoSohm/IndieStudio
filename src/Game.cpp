/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Game.cpp
*/

#include "Game.hpp"

void Game::run(irr::IrrlichtDevice *window)
{
    if (this->_map.empty())
        return;
    window->getVideoDriver()->draw2DImage(this->_textures["gameBackground"], irr::core::position2d<irr::s32>(0, 0),
          irr::core::rect<irr::s32>(0, 0, 1920, 1080), nullptr, irr::video::SColor(255, 255, 255, 255), true);
}

void Game::loadTextures(irr::IrrlichtDevice *window)
{
    this->_textures.insert(std::pair<std::string, irr::video::ITexture *>(std::string("RedBricks"),
          window->getVideoDriver()->getTexture("./assets/blocks/RedBricks.bmp")));
    this->_textures.insert(std::pair<std::string, irr::video::ITexture *>(std::string("WoodenFloor"),
          window->getVideoDriver()->getTexture("./assets/blocks/WoodenFloor.bmp")));
    this->_textures.insert(std::pair<std::string, irr::video::ITexture *>(std::string("gameBackground"),
          window->getVideoDriver()->getTexture("./assets/images/gameBackground.jpg")));
    this->_textures.insert(std::pair<std::string, irr::video::ITexture *>(std::string("grass"),
          window->getVideoDriver()->getTexture("./assets/images/grass.jpg")));
}

void Game::loadButtons(irr::IrrlichtDevice *window)
{
    (void)window;
}

void Game::player1MoveRight()
{
    irr::core::vector3df nodePosition = this->_nodes[0]->getPosition();
    irr::core::vector3df nodeRotation = this->_nodes[0]->getRotation();

    nodeRotation.Z = 90;
    nodePosition.X += this->_frameDeltaTime * 5.f;
    this->_nodes[0]->setFrameLoop(140, 160);
    this->_nodes[0]->setRotation(nodeRotation);
    this->_nodes[0]->setPosition(nodePosition);
}

void Game::player1MoveLeft()
{
    irr::core::vector3df nodePosition = this->_nodes[0]->getPosition();
    irr::core::vector3df nodeRotation = this->_nodes[0]->getRotation();

    nodeRotation.Z = 270;
    nodePosition.X -= this->_frameDeltaTime * 5.f;
    this->_nodes[0]->setFrameLoop(140, 160);
    this->_nodes[0]->setRotation(nodeRotation);
    this->_nodes[0]->setPosition(nodePosition);
}

void Game::player1MoveUp()
{
    irr::core::vector3df nodePosition = this->_nodes[0]->getPosition();
    irr::core::vector3df nodeRotation = this->_nodes[0]->getRotation();

    nodeRotation.Z = 180;
    nodePosition.Y += this->_frameDeltaTime * 5.f;
    this->_nodes[0]->setFrameLoop(140, 160);
    this->_nodes[0]->setRotation(nodeRotation);
    this->_nodes[0]->setPosition(nodePosition);
}

void Game::player1MoveDown()
{
    irr::core::vector3df nodePosition = this->_nodes[0]->getPosition();
    irr::core::vector3df nodeRotation = this->_nodes[0]->getRotation();

    nodeRotation.Z = 0;
    nodePosition.Y -= this->_frameDeltaTime * 5.f;
    this->_nodes[0]->setFrameLoop(140, 160);
    this->_nodes[0]->setRotation(nodeRotation);
    this->_nodes[0]->setPosition(nodePosition);
}

int Game::generateMap()
{
    FILE* file = nullptr;
    int i = 0;
    int j = 0;
    int n = 0;

    file = fopen("map.txt", "w");
    if (!file)
        return -1;
    fputs("AAAAAAAAAAAAAAAAAAA\n", file);
    while (j < 17) {
        fputs("A", file);
        i = 0;
        while (i < 17) {
            n = rand();
            if ((i == 0 && j == 0) || (i == 0 && j == 16) || (i == 16 && j == 0) || (i == 16 && j == 16))
                fputs("x", file);
            else if ((i == 1 && j == 0) || (i == 0 && j == 1))
                fputs("x", file);
            else if ((i == 15 && j == 0) || (i == 16 && j == 1))
                fputs("x", file);
            else if ((i == 1 && j == 16) || (i == 0 && j == 15))
                fputs("x", file);
            else if ((i == 15 && j == 16) || (i == 16 && j == 15))
                fputs("x", file);
            else if (i % 2 != 0 && j % 2 != 0)
                fputs("A", file);
            else if (n % 2 == 0)
                fputs("T", file);
            else
                fputs("x", file);
            i++;
        }
        fputs("A\n", file);
        j++;
    }
    fputs("AAAAAAAAAAAAAAAAAAA", file);
    return 1;
}

bool Game::getMap(const std::string& fileName)
{
    std::ifstream in(fileName.c_str());
    std::string str;
    std::vector<char> tmp;

    if (!in) {
        std::cerr << "Loading map failed: " << fileName << std::endl;
        return false;
    }

    while (std::getline(in, str)) {
        if(str.empty())
            continue;
        for (auto it : str) {
            tmp.push_back(it);
        }
        this->_map.push_back(tmp);
        tmp.clear();
    }
    in.close();
    return true;
}

std::vector<std::vector<irr::scene::ISceneNode *>> Game::getCubes()
{
    return this->_cubes;
}

std::vector<std::vector<irr::scene::ISceneNode *>> Game::getFloor()
{
    return this->_floor;
}

std::vector<irr::scene::IAnimatedMesh *> Game::getPlayers()
{
    return this->_players;
}

std::vector<irr::scene::IAnimatedMeshSceneNode *> Game::getNodes()
{
    return this->_nodes;
}

void Game::createBlocks(irr::IrrlichtDevice *window)
{
    int x = 0;
    int y = 0;
    std::vector<irr::scene::ISceneNode *> tmp;
    std::vector<irr::scene::ISceneNode *> floorTmp;

    this->loadTextures(window);
    for (auto &it : this->_map) {
        for (auto &it2 : it) {
            if (it2 == 'A' || it2 == 'T') {
                tmp.push_back(window->getSceneManager()->addCubeSceneNode(2.0f, nullptr, -1,
                      irr::core::vector3df(x * 2, - y * 2, 0.0f),
                      irr::core::vector3df(0.0f, 0.0f, 0.0f)));
                if (it2 == 'A')
                    tmp.back()->setMaterialTexture(0, this->_textures["RedBricks"]);
                else
                    tmp.back()->setMaterialTexture(0, this->_textures["WoodenFloor"]);
                tmp.back()->setMaterialFlag(irr::video::EMF_LIGHTING, true);
            } else {
                tmp.push_back(nullptr);
            }

            floorTmp.push_back(window->getSceneManager()->addCubeSceneNode(2.0f, nullptr, -1,
                  irr::core::vector3df(x * 2, - y * 2, 2.0f),
                  irr::core::vector3df(0.0f, 0.0f, 0.0f)));
            floorTmp.back()->setMaterialTexture(0, this->_textures["grass"]);
            floorTmp.back()->setMaterialFlag(irr::video::EMF_LIGHTING, true);

    x++;
    }
    x = 0;
    this->_cubes.push_back(tmp);
            this->_floor.push_back(floorTmp);
            tmp.clear();
            floorTmp.clear();
    y++;
    }
}

void Game::createPlayers(irr::IrrlichtDevice *window)
{
    for (int i = 0; i < 4; i++) {
        this->_players.push_back(nullptr);
        this->_nodes.push_back(nullptr);
        this->_players[i] = window->getSceneManager()->getMesh("assets/models/Bomberman.b3d");
/*
        window->getSceneManager()->getMeshManipulator()->scale(this->_players[i], irr::core::vector3df(1, 1, 1));
*/
        this->_nodes[i] = window->getSceneManager()->addAnimatedMeshSceneNode(this->_players[i]);
        if (this->_nodes[i]) {
            this->_nodes[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            this->_nodes[i]->setMaterialTexture(0, window->getVideoDriver()->getTexture("assets/models/Bomberman.png"));
            this->_nodes[i]->setRotation(irr::core::vector3df(-90, 0, 0));
        }
    }
    this->_nodes[0]->setPosition(irr::core::vector3df(2,-2,0));
    this->_nodes[1]->setPosition(irr::core::vector3df(34,-34,0));
    this->_nodes[2]->setPosition(irr::core::vector3df(2,-34,0));
    this->_nodes[3]->setPosition(irr::core::vector3df(34,-2,0));
}

Game::Game(irr::IrrlichtDevice *window) : _textures()
{
    if (!this->getMap("assets/map/map.txt"))
        return;
    this->_frameDeltaTime = 0.030;
    this->createBlocks(window);
    this->createPlayers(window);
    window->getSceneManager()->addLightSceneNode(nullptr, irr::core::vector3df(19, 0, -30),
                                                 irr::video::SColorf(1.0f, 1.0f, 1.0f));
    window->getSceneManager()->addLightSceneNode(nullptr, irr::core::vector3df(19, -38, -30),
                                                 irr::video::SColorf(1.0f, 1.0f, 1.0f));
    window->getSceneManager()->addCameraSceneNode(nullptr, irr::core::vector3df(19, -40, -38),
          irr::core::vector3df(19, -19, 0));
}