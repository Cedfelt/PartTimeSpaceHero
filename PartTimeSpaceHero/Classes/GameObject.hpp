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
  virtual bool init();
    void addAnimation(std::string fileName,std::string animation_name,int start,int end,float animSpeed);
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
    cocos2d::SpriteFrameCache *spriteFrameCache;
    cocos2d::AnimationCache *animationCache;
    Sprite* objectSprite;
    
private:
    
  float speed;
  float velocityX;
  float velocityY;
  float resolution_scale;
};


