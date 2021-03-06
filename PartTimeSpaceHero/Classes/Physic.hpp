//
//  GameObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once
#include "cocos2d.h"
#include "GameObject.hpp"
#include "MapObject.hpp"
#include <stdio.h>
using namespace cocos2d;
class Physic : public cocos2d::Node {
public:
  virtual bool init();
  CREATE_FUNC(Physic);
  void moveGameObjects(cocos2d::Vector<GameObject*>* gameObjects,MapObject* mapObject,float delta);
  void movePlatform(cocos2d::Vector<GameObject*>* gameObjects, MapObject* mapObject, float delta);
  void colideGameObjects(cocos2d::Vector<GameObject*>* gameObjects);
  void gameObjectCollision(GameObject*  goA,GameObject* goB);
  cocos2d::Vector<GameObject*>* platforms;
private:
  bool isBlockedPlatform(GameObject* obj,const Rect* hitBox, MapObject* map,const uint32_t mask,const float delta);
  bool isBlocked(GameObject* obj, const Rect* hitBox, MapObject* map, const uint32_t mask);
  void rightRamp(GameObject* obj,const uint32_t xPre,const uint32_t yPre, MapObject* mapObject,const uint32_t collision_mask);
  void leftRamp(GameObject* obj,const uint32_t xPre,const uint32_t yPre, MapObject* mapObject,const uint32_t collision_mask);
};


