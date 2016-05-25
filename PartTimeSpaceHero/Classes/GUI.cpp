//
//  GoalObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 21/05/16.
//
//

#include "GUI.hpp"

float bar_length = 10;
bool GUI::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  this->schedule(schedule_selector(GUI::update));
  setAnchorPoint(Point(0,5.1f));
  
  //addGravityToObject(false);
  setElastic(0);
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create("fule_bar.png");
  objectSprite->setScaleX(bar_length);
  auto director = Director::getInstance();
  const float xPos = director->getWinSize().width/2;
  const float yPos = director->getWinSize().height;
  setObjectPositionX(xPos);
  setObjectPositionY(yPos);
  objectSprite->setAnchorPoint(Point(0.0f, 1.f));
  setPosition(getPositionX()-32*bar_length /2, getPositionY());// Aling sprite in GUI
  objectSprite->getTexture()->setAliasTexParameters();
  
  addChild(objectSprite);
  addGravityToObject(false);
  return true;
}

void GUI::update(const float delta) {
  objectSprite->setScaleX(bar_length*player->getFuel());
}

void GUI::colideWith(GameObject* oterhObj){
  colided = true;
}