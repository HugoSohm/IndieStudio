/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include <random>
#include <utility>

Player::Player(irr::IrrlichtDevice *window, const irr::core::vector3df& position, bool IA,
               std::vector<std::vector<irr::scene::ISceneNode *>> cubes, std::vector<std::vector<char>> map)
{
    this->_bombTexture = window->getVideoDriver()->getTexture("./assets/blocks/tnt.jpg");
    this->_cubes = std::move(cubes);
    this->_map = std::move(map);
    this->_bombCube = std::pair<bool, irr::scene::ISceneNode *>(false, nullptr);
    this->_bombTimer = 0;
    this->_direction = Player::DOWN;
    this->_window = window;
    this->_frameDeltaTime = 0.020;
    this->_IA = IA;
    this->_placement = NONE;
    this->_isAlive = true;
    this->_playerMesh = window->getSceneManager()->getMesh("assets/models/Bomberman.b3d");
    this->_playerNode = window->getSceneManager()->addAnimatedMeshSceneNode(this->_playerMesh);
    if (this->_playerNode) {
        this->_playerNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        this->_playerNode->setMaterialTexture(0, window->getVideoDriver()->getTexture("assets/models/Bomberman.png"));
        this->_playerNode->setRotation(irr::core::vector3df(-90, 0, 0));
    }
    this->_playerNode->setPosition(position);
    this->_bonuses.insert(std::pair<std::string, bool>(std::string("BombUp"), false));
    this->_bonuses.insert(std::pair<std::string, bool>(std::string("SpeedUp"), false));
    this->_bonuses.insert(std::pair<std::string, bool>(std::string("FireUp"), false));
    this->_bonuses.insert(std::pair<std::string, bool>(std::string("WallPass"), false));
}

std::map<std::string, bool> Player::getBonuses()
{
    return this->_bonuses;
}

irr::scene::IAnimatedMeshSceneNode * Player::getNode()
{
    return this->_playerNode;
}
bool Player::isIA()
{
    return this->_IA;
}

bool Player::getIsWalking()
{
    return this->_isWalking;
}

clock_t Player::getTimer()
{
    return this->_bombTimer;
}

std::pair<bool, irr::scene::ISceneNode *> Player::getBombCube()
{
    return this->_bombCube;
}

void Player::setIsWalking(bool res)
{
    this->_isWalking = res;
}

void Player::setBombCube(std::pair<bool, irr::scene::ISceneNode *> cube)
{
    this->_bombCube = cube;
}

void Player::setTimer()
{
    this->_bombTimer = clock();
}

bool Player::getIsAlive()
{
    return this->_isAlive;
}

void Player::setIsAlive(bool is)
{
    this->_isAlive = is;
}

void Player::setMap(std::vector<std::vector<char>> map)
{
    this->_map = std::move(map);
}

void Player::setBonuses(const std::string& name)
{
    this->_bonuses[name] = true;
}
void Player::MoveRight()
{
    irr::core::vector3df nodePosition = this->_playerNode->getPosition();
    irr::core::vector3df nodeRotation = this->_playerNode->getRotation();

    if (!this->_isAlive)
        return;
    nodeRotation.Z = 90;
    if (!this->_bonuses["SpeedUp"])
        nodePosition.X += this->_frameDeltaTime * 5.f;
    else
        nodePosition.X += this->_frameDeltaTime * 10.f;
    if ((this->_map[static_cast<int>(-round(nodePosition.Y) / 2)][static_cast<int>(round(nodePosition.X + this->_correction) / 2)] == 'A' ||
        this->_map[static_cast<int>(-round(nodePosition.Y) / 2)][static_cast<int>(round(nodePosition.X + this->_correction) / 2)] == 'T') &&
            !this->_bonuses["WallPass"])
        return;
    this->_playerNode->setRotation(nodeRotation);
    this->_playerNode->setPosition(nodePosition);
    this->_isWalking = true;
}

void Player::MoveLeft()
{
    irr::core::vector3df nodePosition = this->_playerNode->getPosition();
    irr::core::vector3df nodeRotation = this->_playerNode->getRotation();

    if (!this->_isAlive)
        return;
    nodeRotation.Z = 270;
    if (!this->_bonuses["SpeedUp"])
        nodePosition.X -= this->_frameDeltaTime * 5.f;
    else
        nodePosition.X -= this->_frameDeltaTime * 10.f;
    if ((this->_map[static_cast<int>(-round(nodePosition.Y) / 2)][static_cast<int>(round(nodePosition.X) / 2)] == 'A' ||
        this->_map[static_cast<int>(-round(nodePosition.Y) / 2)][static_cast<int>(round(nodePosition.X) / 2)] == 'T') &&
            !this->_bonuses["WallPass"])
        return;
    this->_playerNode->setRotation(nodeRotation);
    this->_playerNode->setPosition(nodePosition);
    this->_direction = Player::LEFT;
    this->_isWalking = true;
}

void Player::MoveUp()
{
    irr::core::vector3df nodePosition = this->_playerNode->getPosition();
    irr::core::vector3df nodeRotation = this->_playerNode->getRotation();

    if (!this->_isAlive)
        return;
    nodeRotation.Z = 180;
    if (!this->_bonuses["SpeedUp"])
        nodePosition.Y += this->_frameDeltaTime * 5.f;
    else
        nodePosition.Y += this->_frameDeltaTime * 10.f;
    if ((this->_map[static_cast<int>(-round(nodePosition.Y) / 2)][static_cast<int>(round(nodePosition.X) / 2)] == 'A' ||
        this->_map[static_cast<int>(-round(nodePosition.Y) / 2)][static_cast<int>(round(nodePosition.X) / 2)] == 'T') &&
        !this->_bonuses["WallPass"])
        return;
    this->_playerNode->setRotation(nodeRotation);
    this->_playerNode->setPosition(nodePosition);
    this->_direction = Player::UP;
    this->_isWalking = true;
}

void Player::MoveDown()
{
    irr::core::vector3df nodePosition = this->_playerNode->getPosition();
    irr::core::vector3df nodeRotation = this->_playerNode->getRotation();

    if (!this->_isAlive)
        return;
    nodeRotation.Z = 0;
    if (!this->_bonuses["SpeedUp"])
        nodePosition.Y -= this->_frameDeltaTime * 5.f;
    else
        nodePosition.Y -= this->_frameDeltaTime * 10.f;
    if ((this->_map[static_cast<int>(-round(nodePosition.Y - this->_correction) / 2)][static_cast<int>(round(nodePosition.X) / 2)] == 'A' ||
        this->_map[static_cast<int>(-round(nodePosition.Y - this->_correction) / 2 )][static_cast<int>(round(nodePosition.X) / 2)] == 'T')
        && !this->_bonuses["WallPass"])
        return;
    this->_playerNode->setRotation(nodeRotation);
    this->_playerNode->setPosition(nodePosition);
    this->_direction = Player::DOWN;
    this->_isWalking = true;
}

int roundTo2(float nb)
{
    int r = static_cast<int>(round(nb));

    if (fmod(r, 2) == 0)
        return r;
    return r - 1;
}

void Player::action()
{
    irr::core::vector3df nodePosition = this->_playerNode->getPosition();
    irr::core::vector3df intNodePosition;

    if (!this->_isAlive)
        return;
    if (this->_bombCube.second)
        return;
    intNodePosition.X = roundTo2(nodePosition.X);
    intNodePosition.Y = roundTo2(nodePosition.Y);
    intNodePosition.Z = roundTo2(nodePosition.Z);
    if (this->_map[static_cast<int>(-round(intNodePosition.Y) / 2)][static_cast<int>(round(intNodePosition.X) / 2)] == 'A' ||
        this->_map[static_cast<int>(-round(intNodePosition.Y) / 2)][static_cast<int>(round(intNodePosition.X) / 2)] == 'T')
        return;    this->_bombCube.second = this->_window->getSceneManager()->addCubeSceneNode(2.0f, nullptr, -1,
        intNodePosition,
        irr::core::vector3df(0.0f, 0.0f, 0.0f));
    this->_bombCube.second->setMaterialTexture(0, this->_bombTexture);
    this->_bombCube.second->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    this->_bombCube.first = true;
    _bombTimer = clock();
}

void Player::Animate(int firstFrame, int lastFrame)
{
    this->_playerNode->setFrameLoop(firstFrame, lastFrame);
}

// Direction key map
/*if (this->_map[- static_cast<int>(nodePosition.Y)/2 - 1][static_cast<int>(nodePosition.X)/2] == 'x') {
    this->MoveUp();
} else if (this->_map[- static_cast<int>(nodePosition.Y)/2][static_cast<int>(nodePosition.X)/2 + 1] == 'x') {
    this->MoveRight();
} else if (this->_map[- static_cast<int>(nodePosition.Y)/2 + 1][static_cast<int>(nodePosition.X)/2] == 'x') {
    this->MoveDown();
} else if (this->_map[- static_cast<int>(nodePosition.Y)/2][static_cast<int>(nodePosition.X)/2 - 1] == 'x') {
    this->MoveLeft();
}*/

void Player::ia_move_left()
{
    irr::core::vector3df nodePosition = this->_playerNode->getPosition();
    irr::core::vector3df nodeRotation = this->_playerNode->getRotation();

    if (this->_map[- static_cast<int>(nodePosition.Y/2)][static_cast<int>(nodePosition.X/2) - 1] == 'x') {
        float tmp = nodePosition.X;
            nodeRotation.Z = 270;
            nodePosition.X -= 2;
            if (!this->_isWalking)
                this->_playerNode->setFrameLoop(140, 160);
            if (this->_map[static_cast<int>(-round(nodePosition.Y) / 2)][static_cast<int>(round(nodePosition.X) / 2)] ==
                'A' ||
                this->_map[static_cast<int>(-round(nodePosition.Y) / 2)][static_cast<int>(round(nodePosition.X) / 2)] ==
                'T')
                return;
            this->_playerNode->setRotation(nodeRotation);
            this->_playerNode->setPosition(nodePosition);
            this->_direction = Player::LEFT;
            this->_isWalking = true;
        nodePosition = this->_playerNode->getPosition();
        if ((static_cast<int>(nodePosition.X/2) - 2) < 0)
            return;
    }
}

void Player::ia_move_right()
{
    irr::core::vector3df nodePosition = this->_playerNode->getPosition();
    irr::core::vector3df nodeRotation = this->_playerNode->getRotation();

    if (this->_map[- static_cast<int>(nodePosition.Y/2)][static_cast<int>(nodePosition.X/2) + 1] == 'x') {
        float tmp = nodePosition.X;
            nodeRotation.Z = 90;
            nodePosition.X += 2;
            if (!this->_isWalking)
                this->_playerNode->setFrameLoop(140, 160);
            if (this->_map[static_cast<int>(-round(nodePosition.Y) / 2)][static_cast<int>(
                    round(nodePosition.X + this->_correction) / 2)] == 'A' ||
                this->_map[static_cast<int>(-round(nodePosition.Y) / 2)][static_cast<int>(
                        round(nodePosition.X + this->_correction) / 2)] == 'T')
                return;
            this->_playerNode->setRotation(nodeRotation);
            this->_playerNode->setPosition(nodePosition);
            this->_direction = Player::RIGHT;
            this->_isWalking = true;
        nodePosition = this->_playerNode->getPosition();
        if ((static_cast<int>(nodePosition.X/2) + 2) < 19)
            return;
    }
}

void Player::ia_move_up()
{
    irr::core::vector3df nodePosition = this->_playerNode->getPosition();
    irr::core::vector3df nodeRotation = this->_playerNode->getRotation();

    if (this->_map[- static_cast<int>(nodePosition.Y/2) - 1][static_cast<int>(nodePosition.X/2)] == 'x') {
        float tmp = nodePosition.Y;
            nodeRotation.Z = 180;
            nodePosition.Y += 2;
            if (!this->_isWalking)
                this->_playerNode->setFrameLoop(140, 160);
            if (this->_map[static_cast<int>(-round(nodePosition.Y) / 2)][static_cast<int>(round(nodePosition.X) / 2)] ==
                'A' ||
                this->_map[static_cast<int>(-round(nodePosition.Y) / 2)][static_cast<int>(round(nodePosition.X) / 2)] ==
                'T')
                return;
            this->_playerNode->setRotation(nodeRotation);
            this->_playerNode->setPosition(nodePosition);
            this->_direction = Player::UP;
            this->_isWalking = true;
        nodePosition = this->_playerNode->getPosition();
        if ((static_cast<int>(nodePosition.Y/2) - 2) < 0)
            return;
    }
}

void Player::ia_move_down()
{
    irr::core::vector3df nodePosition = this->_playerNode->getPosition();
    irr::core::vector3df nodeRotation = this->_playerNode->getRotation();

    if (this->_map[- static_cast<int>(nodePosition.Y/2) + 1][static_cast<int>(nodePosition.X/2)] == 'x') {
        float tmp = nodePosition.Y;
            nodeRotation.Z = 0;
            nodePosition.Y -= 2;
            if (!this->_isWalking)
                this->_playerNode->setFrameLoop(140, 160);
            if (this->_map[static_cast<int>(-round(nodePosition.Y - this->_correction) / 2)][static_cast<int>(
                    round(nodePosition.X) / 2)] == 'A' ||
                this->_map[static_cast<int>(-round(nodePosition.Y - this->_correction) / 2 )][static_cast<int>(
                        round(nodePosition.X) / 2)] == 'T')
                return;
            this->_playerNode->setRotation(nodeRotation);
            this->_playerNode->setPosition(nodePosition);
            this->_direction = Player::DOWN;
            this->_isWalking = true;
        nodePosition = this->_playerNode->getPosition();
        if ((- static_cast<int>(nodePosition.Y/2) + 2) == 19)
            return;
    }
}

void Player::ia_deffensive()
{
    irr::core::vector3df nodePosition = this->_playerNode->getPosition();

    if (this->getBombCube().second == NULL && this->_placement == NONE) {
        if ((nodePosition.X / 2 == 1.00 && nodePosition.Y / 2 == -1.00)) {
            for (int i = 0; i <= 19; i++)
                ia_move_right();
            for (int i = 0; i <= 19; i++)
                ia_move_up();
            this->action();
            for (int i = 0; i <= 19; i++)
                ia_move_down();
            for (int i = 0; i <= 19; i++)
                ia_move_left();
            for (int i = 0; i <= 19; i++)
                ia_move_down();
            for (int i = 0; i <= 19; i++)
                ia_move_left();
            this->_placement = UP_G;
        }
        if ((nodePosition.X / 2 == 1.00 && nodePosition.Y / 2 == -17.00)) {
            for (int i = 0; i <= 19; i++)
                ia_move_left();
            for (int i = 0; i <= 19; i++)
                ia_move_up();
            this->action();
            for (int i = 0; i <= 19; i++)
                ia_move_down();
            for (int i = 0; i <= 19; i++)
                ia_move_right();
            for (int i = 0; i <= 19; i++)
                ia_move_down();
            for (int i = 0; i <= 19; i++)
                ia_move_right();
            this->_placement = DOWN_G;
        }
        if ((nodePosition.X / 2 == 17.00 && nodePosition.Y / 2 == -1.00)) {
            for (int i = 0; i <= 19; i++)
                ia_move_right();
            for (int i = 0; i <= 19; i++)
                ia_move_down();
            this->action();
            for (int i = 0; i <= 19; i++)
                ia_move_up();
            for (int i = 0; i <= 19; i++)
                ia_move_left();
            for (int i = 0; i <= 19; i++)
                ia_move_up();
            for (int i = 0; i <= 19; i++)
                ia_move_left();
            this->_placement = UP_D;
        }
        if ((nodePosition.X / 2 == 17.00 && nodePosition.Y / 2 == -17.00)) {
            for (int i = 0; i <= 19; i++)
                ia_move_right();
            for (int i = 0; i <= 19; i++)
                ia_move_up();
            this->action();
            for (int i = 0; i <= 19; i++)
                ia_move_down();
            for (int i = 0; i <= 19; i++)
                ia_move_left();
            for (int i = 0; i <= 19; i++)
                ia_move_down();
            for (int i = 0; i <= 19; i++)
                ia_move_left();
            this->_placement = DOWN_D;
        }
    }
}

void Player::ia_core() {
    irr::core::vector3df nodePosition = this->_playerNode->getPosition();
    irr::core::vector3df nodeRotation = this->_playerNode->getRotation();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 2);
    auto n = dis(gen);

    ia_deffensive();

    if (this->getBombCube().second == NULL) {
        if (this->_placement == UP_G) {
            if (this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) + 1] == 'x') {
                ia_move_right();
            } else if (this->_map[-static_cast<int>(nodePosition.Y / 2) - 1][static_cast<int>(nodePosition.X / 2)] ==
                       'x') {
                ia_move_up();
                this->_direction = BOOM;
            } else if (this->_direction == BOOM) {
                this->action();
                ia_move_down();
                ia_move_left();
                this->_direction = BOOMOK;
            }
            if (this->_direction == BOOMOK) {
                if (this->_map[-static_cast<int>(nodePosition.Y / 2) + 1][static_cast<int>(nodePosition.X / 2)] ==
                    'x') {
                    ia_move_down();
                } else if (
                        this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) - 1] ==
                        'x') {
                    ia_move_left();
                    this->_direction = UP;
                }
            }
        }
        if (this->_placement == DOWN_G) {
            if (this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) - 1] == 'x') {
                ia_move_left();
            } else if (this->_map[-static_cast<int>(nodePosition.Y / 2) - 1][static_cast<int>(nodePosition.X / 2)] ==
                       'x') {
                ia_move_up();
                this->_direction = BOOM;
            } else if (this->_direction == BOOM) {
                this->action();
                ia_move_down();
                ia_move_right();
                this->_direction = BOOMOK;
            }
            if (this->_direction == BOOMOK) {
                if (this->_map[-static_cast<int>(nodePosition.Y / 2) + 1][static_cast<int>(nodePosition.X / 2)] ==
                    'x') {
                    ia_move_down();
                } else if (
                        this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) + 1] ==
                        'x') {
                    ia_move_right();
                    this->_direction = UP;
                }
            }
        }
        if (this->_placement == UP_D) {
            if (this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) + 1] == 'x') {
                ia_move_right();
            } else if (this->_map[-static_cast<int>(nodePosition.Y / 2) + 1][static_cast<int>(nodePosition.X / 2)] ==
                       'x') {
                ia_move_down();
                this->_direction = BOOM;
            } else if (this->_direction == BOOM) {
                this->action();
                ia_move_up();
                ia_move_left();
                this->_direction = BOOMOK;
            }
            if (this->_direction == BOOMOK) {
                if (this->_map[-static_cast<int>(nodePosition.Y / 2) - 1][static_cast<int>(nodePosition.X / 2)] ==
                    'x') {
                    ia_move_up();
                } else if (
                        this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) - 1] ==
                        'x') {
                    ia_move_left();
                    this->_direction = UP;
                }
            }
        }
        if (this->_placement == DOWN_D) {
            if (this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) + 1] == 'x') {
                ia_move_right();
            } else if (this->_map[-static_cast<int>(nodePosition.Y / 2) - 1][static_cast<int>(nodePosition.X / 2)] ==
                       'x') {
                ia_move_up();
                this->_direction = BOOM;
            } else if (this->_direction == BOOM) {
                this->action();
                ia_move_down();
                ia_move_left();
                this->_direction = BOOMOK;
            }
            if (this->_direction == BOOMOK) {
                if (this->_map[-static_cast<int>(nodePosition.Y / 2) + 1][static_cast<int>(nodePosition.X / 2)] ==
                    'x') {
                    ia_move_down();
                } else if (
                        this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) - 1] ==
                        'x') {
                    ia_move_left();
                    this->_direction = UP;
                }
            }
        }
    }
}

/*    if (n == 1) {
        ia_offensive();
    } else if (n == 2) {
        ia_deffensive();
    }*/

/*
void Player::ia_offensive()
{
    irr::core::vector3df nodePosition = this->_playerNode->getPosition();
    irr::core::vector3df nodeRotation = this->_playerNode->getRotation();

    if (this->getBombCube().second != NULL) {
        irr::core::vector3df bombPosition = this->getBombCube().second->getPosition();
        if ((static_cast<int>(bombPosition.X / 2) != static_cast<int>(nodePosition.X / 2)
             || static_cast<int>(bombPosition.X / 2) != static_cast<int>(nodePosition.X / 2) + 1
             || static_cast<int>(bombPosition.X / 2) != static_cast<int>(nodePosition.X / 2) - 1)
            && (static_cast<int>(bombPosition.Y / 2) != static_cast<int>(nodePosition.Y / 2)
                || static_cast<int>(bombPosition.Y / 2) != static_cast<int>(nodePosition.Y / 2) + 1
                || static_cast<int>(bombPosition.Y / 2) != static_cast<int>(nodePosition.Y / 2) - 1)) {
            return;
        } else {
            if ((this->_map[-static_cast<int>(nodePosition.Y / 2) + 1][static_cast<int>(nodePosition.X / 2)] == 'x'
                 && static_cast<int>(bombPosition.X / 2) == static_cast<int>(nodePosition.X / 2) + 1 && static_cast<int>(bombPosition.Y / 2) == static_cast<int>(nodePosition.Y / 2))
                || (this->_map[-static_cast<int>(nodePosition.Y / 2) + 1][static_cast<int>(nodePosition.X / 2)] == 'x'
                    && static_cast<int>(bombPosition.X / 2) + 1 == static_cast<int>(nodePosition.X / 2) + 1 && static_cast<int>(bombPosition.Y / 2) == static_cast<int>(nodePosition.Y / 2))
                || (this->_map[-static_cast<int>(nodePosition.Y / 2) + 1][static_cast<int>(nodePosition.X / 2)] == 'x'
                    && static_cast<int>(bombPosition.X / 2) - 1 == static_cast<int>(nodePosition.X / 2) + 1 && static_cast<int>(bombPosition.Y / 2) == static_cast<int>(nodePosition.Y / 2))
                || (this->_map[-static_cast<int>(nodePosition.Y / 2) + 1][static_cast<int>(nodePosition.X / 2)] == 'x'
                    && static_cast<int>(bombPosition.X / 2) == static_cast<int>(nodePosition.X / 2) + 1 && static_cast<int>(bombPosition.Y / 2) + 1 == static_cast<int>(nodePosition.Y / 2))
                || (this->_map[-static_cast<int>(nodePosition.Y / 2) + 1][static_cast<int>(nodePosition.X / 2)] == 'x'
                    && static_cast<int>(bombPosition.X / 2) == static_cast<int>(nodePosition.X / 2) + 1 && static_cast<int>(bombPosition.Y / 2) - 1 == static_cast<int>(nodePosition.Y / 2))) {
                ia_move_down();
                nodePosition = this->_playerNode->getPosition();
                nodeRotation = this->_playerNode->getRotation();
            }
            else if ((this->_map[-static_cast<int>(nodePosition.Y / 2) - 1][static_cast<int>(nodePosition.X / 2)] == 'x'
                      && static_cast<int>(bombPosition.X / 2) == static_cast<int>(nodePosition.X / 2) - 1 && static_cast<int>(bombPosition.Y / 2) == static_cast<int>(nodePosition.Y / 2))
                     || (this->_map[-static_cast<int>(nodePosition.Y / 2) - 1][static_cast<int>(nodePosition.X / 2)] == 'x'
                         && static_cast<int>(bombPosition.X / 2) + 1 == static_cast<int>(nodePosition.X / 2) - 1 && static_cast<int>(bombPosition.Y / 2) == static_cast<int>(nodePosition.Y / 2))
                     || (this->_map[-static_cast<int>(nodePosition.Y / 2) - 1][static_cast<int>(nodePosition.X / 2)] == 'x'
                         && static_cast<int>(bombPosition.X / 2) - 1 == static_cast<int>(nodePosition.X / 2) - 1 && static_cast<int>(bombPosition.Y / 2) == static_cast<int>(nodePosition.Y / 2))
                     || (this->_map[-static_cast<int>(nodePosition.Y / 2) - 1][static_cast<int>(nodePosition.X / 2)] == 'x'
                         && static_cast<int>(bombPosition.X / 2) == static_cast<int>(nodePosition.X / 2) - 1 && static_cast<int>(bombPosition.Y / 2) + 1 == static_cast<int>(nodePosition.Y / 2))
                     || (this->_map[-static_cast<int>(nodePosition.Y / 2) - 1][static_cast<int>(nodePosition.X / 2)] == 'x'
                         && static_cast<int>(bombPosition.X / 2) == static_cast<int>(nodePosition.X / 2) - 1 && static_cast<int>(bombPosition.Y / 2) - 1 == static_cast<int>(nodePosition.Y / 2))) {
                printf("%s\n", "up\n");
                ia_move_up();
                nodePosition = this->_playerNode->getPosition();
                nodeRotation = this->_playerNode->getRotation();
            }
            else if ((this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) - 1] == 'x'
                      && static_cast<int>(bombPosition.X / 2) == static_cast<int>(nodePosition.X / 2) && static_cast<int>(bombPosition.Y / 2) == static_cast<int>(nodePosition.Y / 2) - 1)
                     || (this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) - 1] == 'x'
                         && static_cast<int>(bombPosition.X / 2) - 1 == static_cast<int>(nodePosition.X / 2) && static_cast<int>(bombPosition.Y / 2) == static_cast<int>(nodePosition.Y / 2) - 1)
                     || (this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) - 1] == 'x'
                         && static_cast<int>(bombPosition.X / 2) + 1 == static_cast<int>(nodePosition.X / 2) && static_cast<int>(bombPosition.Y / 2) == static_cast<int>(nodePosition.Y / 2) - 1)
                     || (this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) - 1] == 'x'
                         && static_cast<int>(bombPosition.X / 2) == static_cast<int>(nodePosition.X / 2) && static_cast<int>(bombPosition.Y / 2) + 1 == static_cast<int>(nodePosition.Y / 2) - 1)
                     || (this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) - 1] == 'x'
                         && static_cast<int>(bombPosition.X / 2) == static_cast<int>(nodePosition.X / 2) && static_cast<int>(bombPosition.Y / 2) - 1 == static_cast<int>(nodePosition.Y / 2) - 1)) {
                ia_move_left();
                nodePosition = this->_playerNode->getPosition();
                nodeRotation = this->_playerNode->getRotation();
            }
            else if ((this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) + 1] == 'x'
                      && static_cast<int>(bombPosition.X / 2) == static_cast<int>(nodePosition.X / 2) && static_cast<int>(bombPosition.Y / 2) == static_cast<int>(nodePosition.Y / 2) + 1)
                     || (this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) + 1] == 'x'
                         && static_cast<int>(bombPosition.X / 2) - 1 == static_cast<int>(nodePosition.X / 2) && static_cast<int>(bombPosition.Y / 2) == static_cast<int>(nodePosition.Y / 2) + 1)
                     || (this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) + 1] == 'x'
                         && static_cast<int>(bombPosition.X / 2) + 1 == static_cast<int>(nodePosition.X / 2) && static_cast<int>(bombPosition.Y / 2) == static_cast<int>(nodePosition.Y / 2) + 1)
                     || (this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) + 1] == 'x'
                         && static_cast<int>(bombPosition.X / 2) == static_cast<int>(nodePosition.X / 2) && static_cast<int>(bombPosition.Y / 2) - 1 == static_cast<int>(nodePosition.Y / 2) + 1)
                     || (this->_map[-static_cast<int>(nodePosition.Y / 2)][static_cast<int>(nodePosition.X / 2) + 1] == 'x'
                         && static_cast<int>(bombPosition.X / 2) == static_cast<int>(nodePosition.X / 2) && static_cast<int>(bombPosition.Y / 2) + 1 == static_cast<int>(nodePosition.Y / 2) + 1)) {
                ia_move_right();
                nodePosition = this->_playerNode->getPosition();
                nodeRotation = this->_playerNode->getRotation();
            } else
                ia_start();
        }
    } else {
        ia_start();
    }
}

void Player::ia_start()
{
    int a = rand() % 4;
    irr::core::vector3df nodePosition = this->_playerNode->getPosition();
    irr::core::vector3df nodeRotation = this->_playerNode->getRotation();

    if (a == 0) {
           if (this->_map[- static_cast<int>(nodePosition.Y/2) - 1][static_cast<int>(nodePosition.X/2)] == 'x') {
               ia_move_up();
               nodePosition = this->_playerNode->getPosition();
               nodeRotation = this->_playerNode->getRotation();
               if ((this->_map[- static_cast<int>(nodePosition.Y/2) + 1][static_cast<int>(nodePosition.X/2)] == 'T')
                   || (this->_map[- static_cast<int>(nodePosition.Y/2) - 1][static_cast<int>(nodePosition.X/2)] == 'T')
                   || (this->_map[- static_cast<int>(nodePosition.Y/2)][static_cast<int>(nodePosition.X/2) + 1] == 'T')
                   || (this->_map[- static_cast<int>(nodePosition.Y/2)][static_cast<int>(nodePosition.X/2) - 1] == 'T')) {
                   this->action();
               }
           }
       } else if (a == 1) {
           if (this->_map[- static_cast<int>(nodePosition.Y/2)][static_cast<int>(nodePosition.X/2) + 1] == 'x') {
               ia_move_right();
               nodePosition = this->_playerNode->getPosition();
               nodeRotation = this->_playerNode->getRotation();
               if ((this->_map[- static_cast<int>(nodePosition.Y/2) + 1][static_cast<int>(nodePosition.X/2)] == 'T')
                   || (this->_map[- static_cast<int>(nodePosition.Y/2) - 1][static_cast<int>(nodePosition.X/2)] == 'T')
                   || (this->_map[- static_cast<int>(nodePosition.Y/2)][static_cast<int>(nodePosition.X/2) + 1] == 'T')
                   || (this->_map[- static_cast<int>(nodePosition.Y/2)][static_cast<int>(nodePosition.X/2) - 1] == 'T')) {
                   this->action();
               }
           }
       } else if (a == 2) {
           if (this->_map[- static_cast<int>(nodePosition.Y/2)][static_cast<int>(nodePosition.X/2) - 1] == 'x') {
               ia_move_left();
               nodePosition = this->_playerNode->getPosition();
               nodeRotation = this->_playerNode->getRotation();
               if ((this->_map[- static_cast<int>(nodePosition.Y/2) + 1][static_cast<int>(nodePosition.X/2)] == 'T')
                   || (this->_map[- static_cast<int>(nodePosition.Y/2) - 1][static_cast<int>(nodePosition.X/2)] == 'T')
                   || (this->_map[- static_cast<int>(nodePosition.Y/2)][static_cast<int>(nodePosition.X/2) + 1] == 'T')
                   || (this->_map[- static_cast<int>(nodePosition.Y/2)][static_cast<int>(nodePosition.X/2) - 1] == 'T')) {
                   this->action();
               }
           }
       } else if (a == 3) {
           if (this->_map[- static_cast<int>(nodePosition.Y/2) + 1][static_cast<int>(nodePosition.X/2)] == 'x') {
               ia_move_down();
               nodePosition = this->_playerNode->getPosition();
               nodeRotation = this->_playerNode->getRotation();
               if ((this->_map[- static_cast<int>(nodePosition.Y/2) + 1][static_cast<int>(nodePosition.X/2)] == 'T')
                   || (this->_map[- static_cast<int>(nodePosition.Y/2) - 1][static_cast<int>(nodePosition.X/2)] == 'T')
                   || (this->_map[- static_cast<int>(nodePosition.Y/2)][static_cast<int>(nodePosition.X/2) + 1] == 'T')
                   || (this->_map[- static_cast<int>(nodePosition.Y/2)][static_cast<int>(nodePosition.X/2) - 1] == 'T')) {
                   this->action();
               }
           }
       }
}*/