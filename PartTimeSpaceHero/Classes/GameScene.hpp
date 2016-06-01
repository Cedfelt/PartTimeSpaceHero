//
//  GameScene.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once

#include "cocos2d.h"
#include "WorldObject.hpp"
#include "Physic.hpp"
#include "GameScene.hpp"
#include "GUI.hpp"

using namespace cocos2d;


class GameScene : public cocos2d::Layer
{
public:
  // there's no 'id' in cpp, so we recommend returning the class instance pointer
  static cocos2d::Scene* createScene();
  // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
  virtual bool init();
  // implement the "static create()" method manually
  
  CREATE_FUNC(GameScene);
  void mainGameLoop(float delta);
  GUI* gui;
private:
  float counter;
  WorldObject* worldObject;
};


