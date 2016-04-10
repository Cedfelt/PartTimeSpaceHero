//
//  PlayerInput.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "PlayerInput.hpp"
#include "ui/CocosGUI.h"

bool PlayerInput::init(){

    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(PlayerInput::onTouchBegan, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(PlayerInput::onTouchEnded, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(PlayerInput::onTouchMoved, this);
    touchListener->onTouchesCancelled = CC_CALLBACK_2(PlayerInput::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}
void PlayerInput::onTouchBegan(const std::vector<Touch*>& touch, Event* event)
{
    cocos2d::log("touch Began");
}

void PlayerInput::onTouchEnded(const std::vector<Touch*>& touches, Event*)
{
    cocos2d::log("touch Ended");
}

void PlayerInput::onTouchMoved(const std::vector<Touch*>& touch, Event* event)
{
    cocos2d::log("touch moved");
}

void PlayerInput::onTouchCancelled(const std::vector<Touch*>&, Event*)
{
    cocos2d::log("touch cancelled");
}