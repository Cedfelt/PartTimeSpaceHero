//
//  RifleBoss.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 18/07/16.
//
//

#pragma once
#include "EnemyObject.hpp"
#include "SoundFx.hpp"

using namespace cocos2d;
class RifleBoos : public EnemyObject {
public:
  virtual bool init();
  bool setupAnimation();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(RifleBoos);
  SoundFx* plingSFX;
  Rect bossArea;
  int playerHp;
  int lastHP;
  int shootCnt =0;
  bool shotFired;
  void AIUpdate(const float delta);
  virtual void deadState();
  bool isPlayerInBossArea();
  bool isFacingPlayer();
  void shootAtPlayer();
  void walkAtDir(float speed, int dir);
  void approachPlayer(const float delta);
  void escapeFromPlayer(const float delta);
  
private:
};
