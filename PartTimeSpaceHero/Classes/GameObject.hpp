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
#include "DialogObject.hpp"

#define SPEED_MOD 1


using namespace cocos2d;
class GameObject : public cocos2d::DrawNode {
public:
  GameObject();
  ~ GameObject();
  cocos2d::Vector<DialogObject*>* dialogObjects;
  enum{
    GO_ON_GROUND,
    GO_IN_AIR_UP,
    GO_IN_AIR_DOWN
  };
  virtual bool setupAnimation();
  uint32_t getObjectType();
  void setPrevDir(int32_t prevDir);
  int32_t getPrevDir();
  int32_t getMovementStatus();
  virtual bool init();
  void addAnimation(std::string fileName,std::string animation_name,int start,int end,float animSpeed);
  void setAnimation(std::string anim);
  bool setAnimationOnce(std::string anim);
  uint32_t getCurrentAnimationFrameIndex();
  Repeat* r;
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
  virtual bool isSafe();
  virtual void removeWhenBelowZero();
  
  void addCoins(uint32_t coinsToAdd);
  uint32_t getCoins();
  uint32_t coins;
  void setCoins(uint32_t coinsSet);

  float getElastic(void);
  void setElastic(const float bGrav);
  float getObjectPositionX();
  float getObjectPositionY();
  virtual void colideWith(GameObject* otherGo,const uint32_t otherType);
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
  virtual void deadState();
  float moveX;
  float moveY;

  float lastX;
  float lastY;
  float deltaX;
  float deltaY;
  
  Rect* getHitbox();
  Sprite* objectSprite;
  Rect hitBox;
  enum{
    GO_LEFT = 0x1,
    GO_RIGHT = 0x2,
    GO_UP = 0x4,
    GO_DOWN = 0x8,
    GO_STILL = 10,
  };
  int obstacle_mask;
  Rect objectZone;
  bool isPlayerInZone();
  void walkAtDir(float speed, int dir);
  void approachPlayer(const float delta);
  
  virtual void dissconect();
  virtual void reconect();
  bool dissconeted;
  uint32_t zoneEffectStatus;
  
  uint32_t isBlocked(uint32_t x,uint32_t y);
  float maxSpeedX;
  float maxSpeedYUpp;
  float maxSpeedYDown;
  float modelPositionX;
  float modelPositionY;

  enum PlayerItem_ID {
    E_NO_ITEM,
    E_RIFLE_ITEM = 1,
    E_DASH_ITEM = 2,
    E_SUPORT_ITEM = 4,
  };
  
#define NUMBER_OF_ITEMS 3
  
  std::string item_descriptions[10] ={
    "NO_ITEM",
    "Plasma Rifle",
    "Dash",
    "Suportive Droid",
    
  
  };
  
  uint32_t itemLevel;
  bool checkForWallCollisions();
  virtual void setItem(PlayerItem_ID id);
  bool bWallCollisions;

  void setTurnAtEdges(bool bState);
  void setStupidWalk(bool bState);
  void setStayInZone(bool bState);
  void flash(int times, float interval);
  
  void flash_sprite(float delta);
protected:
  virtual void removeWhenBelowZeroUpdate(const float delta);
  void dropCoin(int nrOfCoins);
  int32_t goMovementStatus;
  std::string prevAnimation;
  float speed;
  float velocityX;
  float velocityY;
  float resolution_scale;
  int32_t prevDirection;
  
  bool bTurnAtEdges;
  bool bStayInZone;
  bool bStupidWalk;
  
  bool affectedByGravity;
  float elastic;

  
  
  
};



enum class PhysicsCategory {
  None = 0,
  Player = (1 << 0),// 1
  PlayerPickups = (1 << 1), // 2
  Goal = (1 << 2),
  Hazard = (1 << 3),
  Enemy = (1 << 4),
  PlayerProjectile = (1 << 5),
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



enum E_Z_LEVELS {
  E_Z_LEVEL1 = -5,
  E_Z_LEVEL2,
  E_Z_LEVEL3,
  E_Z_LEVEL_ONE_BEHIND_PLAYER,
  E_Z_LEVEL_PLAYER,
  E_Z_LEVEL6,
  E_Z_LEVEL7,
  E_Z_LEVEL8,
  E_Z_LEVEL9,
  E_Z_LEVEL10,
};

