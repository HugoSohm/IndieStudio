/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Game.hpp
*/

#ifndef OOP_INDIE_STUDIO_2018_GAME_HPP
#define OOP_INDIE_STUDIO_2018_GAME_HPP

#include "GameStat.hpp"


class Game : public GameStat {

public:
    //CTOR
    explicit Game(irr::IrrlichtDevice *window);

    //DTOR
    ~Game() override = default;

    void run(irr::IrrlichtDevice *window) override;
    void loadButtons(irr::IrrlichtDevice *window) override;
    void loadTextures(irr::IrrlichtDevice *window) override;

private:
    std::map<std::string, irr::video::ITexture *> _textures;
    std::map<std::string, irr::gui::IGUIButton *> _buttons;

};


#endif //OOP_INDIE_STUDIO_2018_GAME_HPP