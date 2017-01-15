//
//  CaveMonsters.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 15/01/17.
//
//

#pragma once
#include "EnemyObject.hpp"
#include "SoundFx.hpp"
typedef enum tMONSTER_ID
{
  FIRE_MONSTER,
  BLOB_MONSTER,
  FLYING_EYE_MOSTER
}MONSTER_ID;

using namespace cocos2d;
class CaveMonsters : public EnemyObject {
public:
  virtual bool init();
  bool setupAnimation(int monster_type);
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(CaveMonsters);
  SoundFx* plingSFX;
  void FireMon_AIUpdate(const float delta);
  void BlobMon_AIUpdate(const float delta);
  void EyeMon_AIUpdate(const float delta);
  void ShootXDir(const float delta);
  virtual void deadState();
  MONSTER_ID monster_id;
  
  void setupMonsterType(MONSTER_ID id);
protected:
  enum {
    PATROL,
    AIM,
    SHOOT,
    AIM_DOWN,
    DEAD
  };
  float AI_TIMER;
private:
  
};
