//
//  GameObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once
#include "cocos2d.h"
#include <stdio.h>
using namespace cocos2d;
class GameObject : public cocos2d::DrawNode {
public:
  void setPrevDir(int32_t prevDir);
  int32_t getPrevDir();
  int32_t getMovementStatus();
  virtual bool init();
  void addAnimation(std::string fileName,std::string animation_name,int start,int end,float animSpeed);
  void setAnimation(std::string anim);
  CREATE_FUNC(GameObject);
  void setupHitbox(const float x, const float y, const float w, const float h,const bool draw);
  void addToVelocityX(float velX);
  void setVelocityX(float velX);
  float getVelocityX();
  void addToVelocityY(float velY);
  void setVelocityY(float velY);
  float getVelocityY();
  void setSpeed(float s);
  float getSpeed();
  void setObjectPositionX(const float x);
  void setObjectPositionY(const float y);
  float getObjectPositionX();
  float getObjectPositionY();
  Rect* getHitbox();
  cocos2d::SpriteFrameCache *spriteFrameCache;
  cocos2d::AnimationCache *animationCache;
  Sprite* objectSprite;
  Rect hitBox;
  enum{
    GO_LEFT,
    GO_RIGHT,
    GO_UP,
    GO_DOWN,
    GO_STILL
  };
  
  enum{
    GO_ON_GROUND,
    GO_IN_AIR_UP,
    GO_IN_AIR_DOWN
  };
    
private:
  int32_t goMovementStatus;
  std::string prevAnimation;
  float speed;
  float velocityX;
  float velocityY;
  float resolution_scale;
  int32_t prevDirection;
  float modelPositionX;
  float modelPositionY;
};


