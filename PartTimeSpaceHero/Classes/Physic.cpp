//
//  GameScene.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "Physic.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GlobalPList.hpp"

USING_NS_CC;

// on "init" you need to initialize your instance
bool Physic::init(){
  if (!Node::init()) { return false; }
  return true;
}

void Physic::moveGameObjects(cocos2d::Vector<GameObject*>* gameObjects,const float delta) {
  const size_t obj_cnt = gameObjects->size();
  for (int i = 0;i < obj_cnt;i++) {
    GameObject* obj = gameObjects->at(i);
    const float movementY = delta*(gravity + obj->getVelocityY());
    obj->setPositionY(obj->getPositionY() + movementY);
    const float movementX = delta*obj->getVelocityX();
    obj->setPositionX(obj->getPositionX() + movementX);
  }
}

void Physic::colideGameObjects(cocos2d::Vector<GameObject*>* gameObjects) {

}

