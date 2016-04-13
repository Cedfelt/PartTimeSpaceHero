//
//  Player.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once
#include "GameObject.hpp"
#include "PlayerInput.hpp"

using namespace cocos2d;
class PlayerObject : public GameObject {
public:
    virtual bool init();
    CREATE_FUNC(PlayerObject);
    void setupPlayer(const float x,const float y);
    void playerUpdate(const float delta);
    PlayerInput* playerInput;
private:
};
