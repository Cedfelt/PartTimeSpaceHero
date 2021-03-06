//
//  Player.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once
#include "GameObject.hpp"
#include "SoundFx.hpp"


using namespace cocos2d;
class EnemyObject : public GameObject {
public:
  virtual bool init();
  CREATE_FUNC(EnemyObject);
  bool setupAnimation();
protected:
  // Walk functions
  virtual void stupidWalk(const float delta);
  virtual void turnAtEdge(const float delta);
  virtual void walkInZone(const float delta);
  virtual void simpleWalkerHurt(GameObject* player, const uint32_t otherType);
  void genericWalkAi(const float delta);
  void faceTarget(const float delta);
  float fSimpleHurtForce;
  int fDMG;
  int AI_STATE_VAR = 0;
};
