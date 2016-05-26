//
//  GoalObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 21/05/16.
//
//

#include "GUI.hpp"

float bar_length = 4;
bool GUI::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }

  this->schedule(schedule_selector(GUI::update));
  setAnchorPoint(Point(0, 5.1f));

  //addGravityToObject(false);
  setElastic(0);
  // SETUP ANIMATIONS
  auto director = Director::getInstance();
  const float xPos = director->getWinSize().width / 10;
  const float yPos = director->getWinSize().height*0.95f;
  setObjectPositionX(xPos);
  setObjectPositionY(yPos);
  setPosition(getPositionX() - 32 * bar_length / 2, getPositionY());
  addGravityToObject(false);

  Sprite* barBack = Sprite::create("fule_bar.png");
  barBack->setScaleX(bar_length);
  barBack->setAnchorPoint(Point(0.0f, 1.f));
  barBack->getTexture()->setAliasTexParameters();
  barBack->setColor(Color3B(0, 0, 0));
  addChild(barBack, 1);

  objectSprite = cocos2d::Sprite::create("fule_bar.png");
  objectSprite->setScaleX(bar_length);
  objectSprite->setAnchorPoint(Point(0.0f, 1.f));
  objectSprite->getTexture()->setAliasTexParameters();
  addChild(objectSprite, 2);

  Label* fuelLabel = Label::createWithTTF("FUEL", "fonts/arial.ttf", 25);
  fuelLabel->setAnchorPoint(Point(0.0f, 1.f));
  fuelLabel->setPositionX(18 * bar_length / 2.0f);
  fuelLabel->setPositionY(-2);
  addChild(fuelLabel, 3);

  for (int i = 0;i < 3;i++) {
    heartSprite[i] = Sprite::create("heart.png");
    heartSprite[i]->setPositionY((-64));
    heartSprite[i]->setPositionX((43*i));
    heartSprite[i]->setAnchorPoint(Point(0.0f, 1.f));
    heartSprite[i]->getTexture()->setAliasTexParameters();
    heartSprite[i]->setScale(getScale() * 2);
    //heartSprite->setColor(Color3B(0, 0, 0));
    addChild(heartSprite[i], 1);
  }

  // Hearts

  return true;
}

void GUI::update(const float delta) {
  objectSprite->setScaleX(bar_length*player->getFuel());
}

void GUI::colideWith(GameObject* oterhObj) {
  colided = true;
}