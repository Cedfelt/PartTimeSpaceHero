//
//  Player.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once
#include "GameObject.hpp"
#include "PlayerInput.hpp"


using namespace cocos2d;
class PlayerObject : public GameObject {
public:
  void resetPlayerSaveData();
  virtual bool init();
  bool setupAnimation();
  CREATE_FUNC(PlayerObject);
  void setupPlayer(const float x,const float y);
  void playerUpdate(const float delta);
  PlayerInput* playerInput;
  float getFuel(void);
  float playerLookAhead;
  virtual void setItem(PlayerItem_ID id);
  virtual bool isSafe();
  void resetItems();
  uint32_t gear_mask_exclusive; // 0x ff ff ff ff
  uint32_t gear_mask_unlimited; // 0x ff ff ff ff
private:
  
  
  enum GEAR_MASK{
    E_GEAR_SLOT1 = 0xf,
    E_GEAR_QUANTITY1 = 0xf0,
    
    E_GEAR_SLOT2 = 0xf00,
    E_GEAR_QUANTITY2 = 0xf000,
    
    E_GEAR_SLOT3 = 0xf0000,
    E_GEAR_QUANTITY3 = 0xf00000,
    
    E_GEAR_SLOT4 = 0xf000000,
    E_GEAR_QUANTITY4 = 0xf0000000,
  };
  
  enum SLOT_BITS{
    E_SLOT_POS_1 = 0x1,
    E_SLOT_POS_2 = 0x2,
    E_SLOT_POS_3 = 0x4,
    E_SLOT_POS_4 = 0x8,
  };
  
  
  
  void playerWalkUpdate(float delta);
  void walkAtDir(MovementDirectionX dir, std::string animName);
  void fallAtDir(MovementDirectionX dir, std::string animName);
  bool flyAtDir(MovementDirectionX dir, std::string animName);
  void playerFallUpdate(float delta);
  bool playerFlyUpdate(float delta);
  bool hurt(const int dmg, const Vec2 force);
  bool flying = false;
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  const float jumpStength = 200 * SPEED_MOD;
  SoundFx* jetpack1;
  SoundFx* playerCrySFX;
  SoundFx* weaponSFX;
  SoundFx* rechargedSFX;
  float fuel;
  float consumeRate;
  float currentConsumeRate;
  
  float lastFuel;
  
  std::vector<std::string> animationStrings;
  enum {
    IdleR,
    IdleL,
    WalkR,
    WalkL,
    FlyR,
    FlyL,
    AscendR,
    AscendL,
    FallR,
    FallL,
    ItemR,
    ItemL,
    Item2R,
    Item2L,
    AnimationCount
  };

  bool rifle_item(float);
  bool playerDashUpdate(float delta);
  bool no_item(float delta);
  
  
  bool (PlayerObject::*pItem)(float);

  };
