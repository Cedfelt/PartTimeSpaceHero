//
//  WorldObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "MapObject.hpp"
#include "PlayerObject.hpp"
#include "GameObject.hpp"
#include "Physic.hpp"
#include "GoalObject.hpp"
#include "SaveData.hpp"

class WorldObject : public cocos2d::Node
{
public:
  // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
  virtual bool init();
  cocos2d::Vector<GameObject*>* getGameObjects();
  CREATE_FUNC(WorldObject);
  // implement the "static create()" method manually
  PlayerObject* player;
private:
  MapObject* mapObject;
  cocos2d::Vector<GameObject*> gameObjects;
  void spawnObjects(cocos2d::Vector<GameObject*>* gameObjects);
  void setViewPointCenter(const cocos2d::Point position);
  void updateWorld(float delta);
  bool onContactBegan(PhysicsContact &contact);
  GoalObject* obj;
  Physic* physic;
};

