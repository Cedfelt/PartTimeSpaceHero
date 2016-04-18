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

# define GRAVITY -100.0
# define MAX_FALLSPEED -200.0

// on "init" you need to initialize your instance
bool Physic::init(){
  if (!Node::init()) { return false; }
  return true;
}

int dir_sign(const float num){
  if (num<0){
    return 1;
  }
  return -1;
}

float round_and(float f){
  return floorf(f+0.5f);
}

void Physic::moveGameObjects(cocos2d::Vector<GameObject*>* gameObjects,MapObject* mapObject,const float delta) {
  const size_t obj_cnt = gameObjects->size();
  for (int i = 0;i < obj_cnt;i++) {
    
    GameObject* obj = gameObjects->at(i);
    obj->addToVelocityY(delta*GRAVITY);// GRAVITY
    if(obj->getVelocityY()<MAX_FALLSPEED){
      obj->setVelocityY(MAX_FALLSPEED);
    }
    
    
    // COLLISION Y-AXIS
    obj->setObjectPositionY((obj->getObjectPositionY()+obj->getVelocityY()*delta));
    if(isBlocked(obj->getHitbox(),mapObject)){
      const int sign = dir_sign(obj->getVelocityY());
      obj->setObjectPositionY((int)(obj->getObjectPositionY()+sign));
      while(isBlocked(obj->getHitbox(),mapObject)){
        obj->setObjectPositionY((int)(obj->getObjectPositionY()+sign));
      }
      obj->setVelocityY(0);
    }
    
    // COLLISION X-AXIS
    obj->setObjectPositionX((obj->getObjectPositionX() + delta*obj->getVelocityX()));
    if(isBlocked(obj->getHitbox(),mapObject)){
      const int sign = dir_sign(obj->getVelocityX());
      obj->setObjectPositionX(int(obj->getObjectPositionX()+sign));
      while(isBlocked(obj->getHitbox(),mapObject)){
        obj->setObjectPositionX(int(obj->getObjectPositionX()+sign));
      }
      
      
      obj->setVelocityX(0);
    }
  }
}

bool Physic::isBlocked(Rect* hitBox, MapObject* map){
  Rect tile_rect;
  const size_t ts = 8;
  const uint32_t x_min = ((int)(hitBox->getMinX())/(ts));
  const uint32_t x_max = ((int)(hitBox->getMaxX())/(ts));
  const uint32_t y_min = ((int)(hitBox->getMinY())/(ts));
  const uint32_t y_max = ((int)(hitBox->getMaxY())/(ts));
  const uint32_t xRange = x_min + x_max-x_min+1;
  const uint32_t yRange = y_min + y_max-y_min+1;
  const uint32_t mapWidth = map->getMapWidthInTiles();
  const uint32_t mapHeight = map->getMapWidthInTiles();
  // Out of bounds
  if(x_min>mapWidth||x_max>mapWidth){
    return true;
  }
  if(y_min>mapHeight||y_max>mapHeight){
    return true;
  }
  
  for(uint32_t xx = x_min; xx<xRange;xx++){
    for(uint32_t yy = y_min; yy<yRange;yy++){
      
      uint32_t attribute = map->attributeAt(xx, yy);
      if(attribute==MapObject::CLEAR){
        continue;
      }
      else if (attribute==MapObject::BLOCKED){
        tile_rect.setRect(xx*ts,yy*ts,ts,ts);
      }
      
      bool cond1 = hitBox->intersectsRect(tile_rect);
      if(cond1){
        return true;
      }
    }
  }
  return false;
}

void Physic::colideGameObjects(cocos2d::Vector<GameObject*>* gameObjects) {

}

