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
#include "SoundFx.hpp"
#include "MapData.hpp"
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
  void setupHitbox(const float x, const float y, const float w, const float h, const float box, const float boy, const bool draw);
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
  bool isAffectedByGravity(void);
  void addGravityToObject(const bool bGrav);
  virtual void imuneUpdate(const float delta);
  virtual void setImune();
  virtual bool isImune();
  float getElastic(void);
  void setElastic(const float bGrav);
  float getObjectPositionX();
  float getObjectPositionY();
  virtual void colideWith(GameObject* otherGo);
  virtual void interActWithPlayer(GameObject* player);
  virtual bool hurt(const int dmg, const Vec2 force);
  bool colided;
  bool remove_object;
  float imuneTime;
  float imuneCnt;
  float solid;
  int32_t dmg;
  bool skipMove;
  float softXMax;
  float softXMin;
  GameObject* target;
  cocos2d::Vector<GameObject*> addToGameObjects;
  int32_t HP;
  bool staticBoody;
  bool platform;
  MapData* mapData;
  Vec2 extraMove;
  
  float moveX;
  float moveY;

  float lastX;
  float lastY;
  float deltaX;
  float deltaY;
  
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
  uint32_t isBlocked(uint32_t x,uint32_t y);
  float maxSpeedX;
  float maxSpeedYUpp;
  float maxSpeedYDown;
  float modelPositionX;
  float modelPositionY;
private:
  int32_t goMovementStatus;
  std::string prevAnimation;
  float speed;
  float velocityX;
  float velocityY;
  float resolution_scale;
  int32_t prevDirection;
  
  bool affectedByGravity;
 
  float elastic;
};

enum class PhysicsCategory {
  None = 0,
  Player = (1 << 0),    // 1
  PlayerPickups = (1 << 1), // 2
  Goal = (1 << 2),
  Hazard = (1 << 3),
  Enemy = (1 << 4),
  All = 0xff // 3
};

enum MovementDirectionX {
  LEFT =-1,
  RIGHT = 1,
};

enum MovementDirectionY {
  UP = 1,
  DOWN = -1
};
