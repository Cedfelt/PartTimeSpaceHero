

#include "FishObject.hpp"
#include "BabyTurfelObject.hpp"
#include "CoinObject.hpp"


bool FishObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!EnemyObject::init())
  {
    return false;
  }
  
  
  this->schedule(schedule_selector(FishObject::AIUpdate), 0.8);
  addGravityToObject(true);
  setElastic(0.f);
  plingSFX = SoundFx::create();
  plingSFX->loadEffect("small_explosion.aif", 0, 1, false);
  addChild(plingSFX);
  dmg = 1;
  
  // Start Speed
  setVelocityX(-speed);
  setPrevDir(GO_LEFT);
  objectSprite = cocos2d::Sprite::create();
  objectSprite->setPosition(12, 0);// Aling sprite in Hitbox
  objectSprite->setAnchorPoint(Point(0.5, 0));
  addChild(objectSprite);
  objectSprite->setScaleX(-1);
  addGravityToObject(false);
  return true;
}

void FishObject::colideWith(GameObject* oterhObj, const uint32_t otherType) {
  simpleWalkerHurt(oterhObj,otherType);
}

void FishObject::AIUpdate(const float delta) {
  genericWalkAi(delta);
}

void FishObject::deadState() {
  HP = 0;
  plingSFX->play(0.3f);
  setAnimation("fish_dead");
  this->bWallCollisions = false;
  setVelocityY(70);
  this->unschedule(schedule_selector(FishObject::AIUpdate));
  this->unschedule(schedule_selector(FishObject::update));
  removeWhenBelowZero();
  addGravityToObject(true);
  dropCoin(3);
}

bool FishObject::setupAnimation() {
  // SETUP ANIMATIONS
  
  spriteFrameCache = spriteFrameCache->getInstance();
  animationCache = animationCache->getInstance();
  spriteFrameCache->addSpriteFramesWithFile("fish.plist");
  addAnimation("fish", "fish_idle", 1, 4, 0.25f);
  addAnimation("fish", "fish_dead", 3, 3, 1.f);
  return true;
}
