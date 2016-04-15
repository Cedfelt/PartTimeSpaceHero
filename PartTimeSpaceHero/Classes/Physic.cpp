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
    obj->addToVelocityY(gravity);
    obj->setPositionY(obj->getPositionY() + obj->getVelocityY()*delta);
    // While Blocked Move Backwards
    
    obj->setPositionX(obj->getPositionX() + delta*obj->getVelocityX());
    // While Blocked Move Backwards
  }
}

void Physic::colideGameObjects(cocos2d::Vector<GameObject*>* gameObjects) {

}

