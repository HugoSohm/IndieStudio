/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player.hpp
*/

#ifndef OOP_INDIE_STUDIO_2018_PLAYER_HPP
#define OOP_INDIE_STUDIO_2018_PLAYER_HPP

#include <irrlicht.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <zconf.h>
#include <map>

class Player {

public:
    //CTOR
    Player(irr::IrrlichtDevice *window, const irr::core::vector3df&, bool IA,
           std::vector<std::vector<irr::scene::ISceneNode *>> cubes, std::vector<std::vector<char>> map);

    //DTOR
    ~Player() = default;

    void MoveRight();
    void MoveLeft();
    void MoveUp();
    void MoveDown();
    void action();
    void Animate(int, int);
    void ia_core();
    void ia_start();
    void ia_careful();
    void ia_rand_direction();
    void ia_put_bomb();
    void ia_to_bonus();
    void ia_offensive();
    void ia_deffensive();
    void ia_move_right();
    void ia_move_up();
    void ia_move_down();
    void ia_move_left();

    //Getters
    irr::scene::IAnimatedMeshSceneNode *getNode();
    bool getIsWalking();
    clock_t getTimer();
    std::pair<bool, irr::scene::ISceneNode *> getBombCube();
    bool isIA();
    bool getIsAlive();
    std::map<std::string, bool> getBonuses();

    //Setters
    void setIsWalking(bool res);
    void setBonuses(const std::string& name);
    void setBombCube(std::pair<bool, irr::scene::ISceneNode *> cube);
    void setTimer();
    void setIsAlive(bool);
    void setMap(std::vector<std::vector<char>> map);

    enum direction_e {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

private:
    irr::scene::IAnimatedMesh *_playerMesh;
    irr::video::ITexture *_bombTexture;
    std::pair<bool, irr::scene::ISceneNode *> _bombCube;
    direction_e _direction;
    irr::scene::IAnimatedMeshSceneNode * _playerNode;
    irr::f32 _frameDeltaTime;
    irr::IrrlichtDevice *_window;
    std::vector<std::vector<irr::scene::ISceneNode *>> _cubes;
    std::vector<std::vector<char>> _map;
    bool _isWalking = false;
    bool _IA;
    bool _isAlive;
    clock_t _bombTimer;
    float _correction = 0.3;
    std::map<std::string, bool> _bonuses;
};


#endif //OOP_INDIE_STUDIO_2018_PLAYER_HPP