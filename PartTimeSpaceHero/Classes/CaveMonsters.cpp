//
//  CaveMonsters.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 15/01/17.
//
//

#include "CaveMonsters.hpp"
#include "BabyTurfelObject.hpp"
#include "CoinObject.hpp"
#include "Simple_Bullet.hpp"
#include "SpecialFX.hpp"

bool CaveMonsters::init() {
  //////////////////////////////
  // 1. super init first
  if (!EnemyObject::init())
  {
    return false;
  }
  addGravityToObject(true);
  setElastic(0.f);
  plingSFX = SoundFx::create();
  plingSFX->loadEffect("small_explosion.aif", 0, 1, false);
  addChild(plingSFX);
  dmg = 1;
  
  
  
  
  
  return true;
}

void CaveMonsters::setupMonsterType(MONSTER_ID id){
  
  // Start Speed
  setVelocityX(-speed);
  setPrevDir(GO_LEFT);
  setupAnimation(id);
  objectSprite = cocos2d::Sprite::create();
  monster_id = id;
  
  if(id == FIRE_MONSTER){
    HP = 3;
    setAnimation("fireMon_walk");
    this->schedule(schedule_selector(CaveMonsters::FireMon_AIUpdate), 0.4);
    objectSprite->setPosition(8, 0);// Aling sprite in Hitbox
    objectSprite->setAnchorPoint(Point(0.5, 0));
  }
  else if(id == BLOB_MONSTER){
    HP = 2;
    setAnimation("blobMon_walk");
    this->schedule(schedule_selector(CaveMonsters::BlobMon_AIUpdate), 0.4);
    objectSprite->setPosition(8, 0);// Aling sprite in Hitbox
    objectSprite->setAnchorPoint(Point(0.5, 0));
    speed = speed * 0.5f;
  }
  else if(id == FLYING_EYE_MOSTER){
    HP = 1;
    setAnimation("eyeMon_walk");
    addGravityToObject(false);
    this->schedule(schedule_selector(CaveMonsters::EyeMon_AIUpdate), 0.4);
    objectSprite->setPosition(8, 0);// Aling sprite in Hitbox
    objectSprite->setAnchorPoint(Point(0.5, 0));
    
  }
  addChild(objectSprite);
  objectSprite->setScaleX(-1);
  
  }

void CaveMonsters::colideWith(GameObject* oterhObj, const uint32_t otherType) {
  if(AI_STATE_VAR == DEAD){
    return;
  }
  simpleWalkerHurt(oterhObj,otherType);
}



void CaveMonsters::FireMon_AIUpdate(const float delta) {
  
  if(AI_STATE_VAR == PATROL){
    genericWalkAi(delta);
    setAnimation("fireMon_walk");
    if(isPlayerInZone() && target->HP > 0 && isFacingTarget()){
      AI_STATE_VAR = AIM;
      AI_TIMER = 1.f;
      return;
    }
  }
  else if(AI_STATE_VAR == AIM){
    setVelocityX(0);
    setAnimation("fireMon_aim");
    faceTarget(delta);
    if(AI_TIMER>0){
      AI_TIMER-= delta;
      return;
    }
    else{
      AI_STATE_VAR = SHOOT;
      return;
    }
  }
  else if(AI_STATE_VAR == SHOOT){
    ShootXDir(delta);
    AI_STATE_VAR = AIM_DOWN;
    AI_TIMER = 1.f;
    return;
  }
  else if(AI_STATE_VAR == AIM_DOWN){
    if(AI_TIMER>0){
      AI_TIMER-= delta;
      return;
    }
    else{
      AI_STATE_VAR = PATROL;
      return;
    }
  }
  
  else if(AI_STATE_VAR == HAUNT){
    approachPlayer(0);
    if(std::abs(target->getObjectPositionY() - getObjectPositionY())<15){
      AI_STATE_VAR = AIM;
    }
  }
  else if(AI_STATE_VAR == DEAD){
    setVelocityX(getVelocityX()*0.2f);
  }
  
}

void CaveMonsters::BlobMon_AIUpdate(const float delta) {
  genericWalkAi(delta);
}

void CaveMonsters::EyeMon_AIUpdate(const float delta) {
  genericWalkAi(delta);
}


void CaveMonsters::ShootXDir(const float delta) {
  auto babyTurf = SimpleBullet::create();
  float bullet_x_offset;
  babyTurf->setup(E_SIMPLE_BULLET);
  babyTurf->setupHitbox(0.1f, 1.0f, 16, 16, 16, 16, false);
  babyTurf->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Enemy);
  babyTurf->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
  babyTurf->getPhysicsBody()->setContactTestBitmask( (int)PhysicsCategory::Player | (int)PhysicsCategory::Hazard);
  addToGameObjects.pushBack(babyTurf);
  if(getPrevDir() == GO_RIGHT){
    babyTurf->setVelocityX(200);
    bullet_x_offset = 12;
  }
  else {
    babyTurf->setVelocityX(-200);
    bullet_x_offset = -6;
  }
  babyTurf->setObjectPositionX(getPositionX() + bullet_x_offset);
  babyTurf->setObjectPositionY(getPositionY() + 4);
  //weaponSFX->play(0.4f);
}


void CaveMonsters::deadState() {
  HP = 0;
  plingSFX->play(0.3f);
  dropCoin(3);
  SpecialFX *poof = SpecialFX::create();
  poof->setObjectPositionX(getObjectPositionX());
  poof->setObjectPositionY(getObjectPositionY());
  poof->setupFXType(POOF_FX);
  addToGameObjects.pushBack(poof);
  remove_object = true;
  return;
  
  addGravityToObject(true);
  
  if(monster_id == FIRE_MONSTER)
    setAnimation("fireMon_dead");
  else if(monster_id == BLOB_MONSTER)
    setAnimation("blobMon_dead");
  else if(monster_id == FLYING_EYE_MOSTER)
    setAnimation("eyeMon_dead");
  
  setVelocityY(70);
  bWallCollisions = false;
  this->unschedule(schedule_selector(CaveMonsters::update));
  removeWhenBelowZero();
  AI_STATE_VAR = DEAD;
  
}

void CaveMonsters::hurtNotification(){
  if(monster_id == FIRE_MONSTER){
    approachPlayer(0);
    AI_STATE_VAR = HAUNT;
  }
  else if(monster_id == BLOB_MONSTER){}
  else if(monster_id == FLYING_EYE_MOSTER){}
}

bool CaveMonsters::setupAnimation(int monster_type) {
  // SETUP ANIMATIONS
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cave_monsters.plist");
  
  if(monster_type == FIRE_MONSTER){
    addAnimation("cave_monsters", "fireMon_walk", 4, 6, 0.2f);
    addAnimation("cave_monsters", "fireMon_dead", 6, 6, 0.2f);
    addAnimation("cave_monsters", "fireMon_aim", 7, 7, 0.2f);
  }
  else if(monster_type == BLOB_MONSTER){
    addAnimation("cave_monsters", "blobMon_walk", 1, 3, 0.250f);
    addAnimation("cave_monsters", "blobMon_dead", 1, 1, 0.250f);
  }
  else if(monster_type == FLYING_EYE_MOSTER){
    addAnimation("cave_monsters", "eyeMon_walk", 8, 10, 0.150f);
    addAnimation("cave_monsters", "eyeMon_dead", 8, 10, 0.100f);
  }
  return true;
}
