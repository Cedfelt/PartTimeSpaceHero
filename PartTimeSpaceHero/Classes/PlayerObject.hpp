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
  virtual bool init();
  CREATE_FUNC(PlayerObject);
  void setupPlayer(const float x,const float y);
  void playerUpdate(const float delta);
  PlayerInput* playerInput;
  float getFuel(void);
  float playerLookAhead;

private:
  void playerWalkUpdate(float delta);
  void walkAtDir(MovementDirectionX dir, std::string animName);
  void fallAtDir(MovementDirectionX dir, std::string animName);
  bool flyAtDir(MovementDirectionX dir, std::string animName);
  void playerFallUpdate(float delta);
  bool playerFlyUpdate(float delta);
  bool hurt(const int dmg, const Vec2 force);
  bool playerDashUpdate(float delta);
  bool playerShoot(float delta);
  bool flying = false;
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  const float jumpStength = 90;
  SoundFx* jetpack1;
  SoundFx* playerCrySFX;
  SoundFx* weaponSFX;
  float fuel;
  float consumeRate;
  float currentConsumeRate;
  
  
};
