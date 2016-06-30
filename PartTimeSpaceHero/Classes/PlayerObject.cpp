//
//  Player.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "PlayerObject.hpp"
#include "Simple_Bullet.hpp"


bool PlayerObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  playerInput = PlayerInput::create();
  setSpeed(100.f);
  addChild(playerInput);
  this->schedule(schedule_selector(PlayerObject::playerUpdate));

  HP = 3;
  playerLookAhead = 0;
  // SETUP ANIMATIONS
  spriteFrameCache = spriteFrameCache->getInstance();
  animationCache = animationCache->getInstance();


  ///////////////////////////
  // Normal

  /////////////////////////

  //Animations
  //-

//  spriteFrameCache->addSpriteFramesWithFile("mech.plist");
//  const float animSpeed = 0.180;
//  addAnimation("mech", "IdleR", 2, 2, animSpeed);
//  addAnimation("mech", "IdleL", 2, 2, animSpeed);
//  addAnimation("mech", "WalkR", 1, 4, animSpeed);
//  addAnimation("mech", "WalkL", 1, 4, animSpeed);
//  addAnimation("mech", "FlyR", 1, 1, animSpeed);
//  addAnimation("mech", "FlyL", 3, 3, animSpeed);
//  addAnimation("mech", "AscendR", 1, 1, animSpeed);
//  addAnimation("mech", "AscendL", 3, 3, animSpeed);
//  addAnimation("mech", "FallR", 1, 1, animSpeed);
//  addAnimation("mech", "FallL", 3, 3, animSpeed);
//  addAnimation("mech", "DashChargeR", 1, 4, animSpeed);
//  addAnimation("mech", "DashChargeL", 1, 4, animSpeed);
//  addAnimation("mech", "DashR", 1, 4, animSpeed);
//  addAnimation("mech", "DashL", 1, 4, animSpeed);


  spriteFrameCache->addSpriteFramesWithFile("ptsh.plist");
  addAnimation("PTSH", "IdleR", 1, 4, 0.2f);
  addAnimation("PTSH", "IdleL", 1, 4, 0.2f);
  addAnimation("PTSH", "WalkR", 5, 8, 0.15f);
  addAnimation("PTSH", "WalkL", 5, 8, 0.15f);
  addAnimation("PTSH", "FlyR", 9, 12, 0.2f);
  addAnimation("PTSH", "FlyL", 9, 12, 0.2f);
  addAnimation("PTSH", "AscendR", 13, 13, 0.2f);
  addAnimation("PTSH", "AscendL", 13, 13, 0.2f);
  addAnimation("PTSH", "FallR", 14, 17, 0.2f);
  addAnimation("PTSH", "FallL", 14, 17, 0.2f);
  addAnimation("PTSH", "DashChargeR", 18, 21, 0.15f);
  addAnimation("PTSH", "DashChargeL", 18, 21, 0.15f);
  addAnimation("PTSH", "DashR", 22, 25, 0.15f);
  addAnimation("PTSH", "DashL", 22, 25, 0.15f);
  

  // Strings
  //-


  //////////////////////////
  // Weapon
  /////////////////////////

  //Animations
  spriteFrameCache->addSpriteFramesWithFile("ptshwep.plist");
  addAnimation("PTSH_WEP", "IdleRWep", 1, 4, 0.2f);
  addAnimation("PTSH_WEP", "IdleLWep", 1, 4, 0.2f);
  addAnimation("PTSH_WEP", "WalkRWep", 5, 8, 0.15f);
  addAnimation("PTSH_WEP", "WalkLWep", 5, 8, 0.15f);
  addAnimation("PTSH_WEP", "FlyRWep", 9, 12, 0.2f);
  addAnimation("PTSH_WEP", "FlyLWep", 9, 12, 0.2f);
  addAnimation("PTSH_WEP", "AscendRWep", 13, 13, 0.2f);
  addAnimation("PTSH_WEP", "AscendLWep", 13, 13, 0.2f);
  addAnimation("PTSH_WEP", "FallRWep", 14, 17, 0.2f);
  addAnimation("PTSH_WEP", "FallLWep", 14, 17, 0.2f);
  addAnimation("PTSH_WEP", "PlayerShootRWep", 26, 29, 0.06f);
  addAnimation("PTSH_WEP", "PlayerShootLWep", 26, 29, 0.06f);


  // Strings
  animationStrings.push_back("IdleR");
  animationStrings.push_back("IdleL");
  animationStrings.push_back("WalkR");
  animationStrings.push_back("WalkL");
  animationStrings.push_back("FlyR");
  animationStrings.push_back("FlyL");
  animationStrings.push_back("AscendR");
  animationStrings.push_back("AscendL");
  animationStrings.push_back("FallR");
  animationStrings.push_back("FallL");
  animationStrings.push_back("ItemR");
  animationStrings.push_back("ItemL");
  animationStrings.push_back("Item2R");
  animationStrings.push_back("Item2L");

  objectSprite = cocos2d::Sprite::create();
  objectSprite->setAnchorPoint(cocos2d::Point(0.5, 0.25));
  objectSprite->setPosition(8, -128);// Aling sprite in Hitbox
  setAnimation(animationStrings.at((WalkR)));
  //addChild(objectSprite);


  // soundfx
  jetpack1 = SoundFx::create();
  jetpack1->loadEffect("jet_pack_hum.aif", 0, 1, true);
  addChild(jetpack1);

  weaponSFX = SoundFx::create();
  weaponSFX->loadEffect("weapon.aif", 0, 1, false);
  addChild(weaponSFX);

  playerCrySFX = SoundFx::create();
  playerCrySFX->loadEffect("Cry.aif", 0, 1, false);
  addChild(playerCrySFX);



  fuel = 1.0f;
  consumeRate = currentConsumeRate;
  currentConsumeRate = 0.0075f;
  objectSprite->retain();

  // ITEM POINTERS
  setItem(E_NO_ITEM);
  /*setItem(E_DASH_ITEM);*/
  return true;
}

const float ground_deacceleration = 0.87;
const float ground_acceleration = 10;

void PlayerObject::walkAtDir(MovementDirectionX dir, std::string animName) {
  setAnimation(animName);
  addToVelocityX(dir*ground_acceleration);
  if (std::abs(getVelocityX()) > std::abs(dir*getSpeed())) {
    setVelocityX(dir*getSpeed());
  }
}

void PlayerObject::setItem(PlayerItem_ID id) {
  if (id == E_RIFLE_ITEM) {
    pItem = &PlayerObject::rifle_item; // note: <pt2Member> may also legally point to &DoMore
    animationStrings.at(IdleR) = ("IdleRWep");
    animationStrings.at(IdleL) = ("IdleLWep");
    animationStrings.at(WalkR) = ("WalkRWep");
    animationStrings.at(WalkL) = ("WalkLWep");
    animationStrings.at(FlyR) = ("FlyRWep");
    animationStrings.at(FlyL) = ("FlyLWep");
    animationStrings.at(AscendR) = ("AscendRWep");
    animationStrings.at(AscendL) = ("AscendLWep");
    animationStrings.at(FallR) = ("FallRWep");
    animationStrings.at(FallL) = ("FallLWep");
    animationStrings.at(ItemR) = ("PlayerShootRWep");
    animationStrings.at(ItemL) = ("PlayerShootLWep");
  }
  else if (id == E_DASH_ITEM) {
    pItem = &PlayerObject::playerDashUpdate;
    animationStrings.at(IdleR) = ("IdleR");
    animationStrings.at(IdleL) = ("IdleL");
    animationStrings.at(WalkR) = ("WalkR");
    animationStrings.at(WalkL) = ("WalkL");
    animationStrings.at(FlyR) = ("FlyR");
    animationStrings.at(FlyL) = ("FlyL");
    animationStrings.at(AscendR) = ("AscendR");
    animationStrings.at(AscendL) = ("AscendL");
    animationStrings.at(FallR) = ("FallR");
    animationStrings.at(FallL) = ("FallL");
    animationStrings.at(ItemR) = ("DashChargeR");
    animationStrings.at(ItemL) = ("DashChargeL");
    animationStrings.at(Item2R) = ("DashR");
    animationStrings.at(Item2L) = ("DashL");
  }
  else if (id == E_NO_ITEM) {
    pItem = &PlayerObject::no_item;
    animationStrings.at(IdleR) = ("IdleR");
    animationStrings.at(IdleL) = ("IdleL");
    animationStrings.at(WalkR) = ("WalkR");
    animationStrings.at(WalkL) = ("WalkL");
    animationStrings.at(FlyR) = ("FlyR");
    animationStrings.at(FlyL) = ("FlyL");
    animationStrings.at(AscendR) = ("AscendR");
    animationStrings.at(AscendL) = ("AscendL");
    animationStrings.at(FallR) = ("FallR");
    animationStrings.at(FallL) = ("FallL");
  }
  else {
    assert(false); // The Requested item dont exsist
  }
}
bool dashingRight = false;
bool dashingLeft = false;
bool PlayerObject::isSafe() {
  if (getVelocityY() != 0) {
    return false;
  }
  if (platform) {
    return false;
  }
  if (dashingLeft||dashingRight) {
    return false;
  }
  return true;
}

void PlayerObject::playerWalkUpdate(float delta) {
  if (getMovementStatus() != GO_ON_GROUND) {
    return; // Flying
  }
  if (playerInput->isLeft()) {
    walkAtDir(LEFT, animationStrings.at(WalkL));

  }
  else if (playerInput->isRight()) {
    walkAtDir(RIGHT, animationStrings.at(WalkR));
  }
  else {
    setVelocityX(getVelocityX()*ground_deacceleration);

    if (getPrevDir() == GO_RIGHT) {
      setAnimation(animationStrings.at(IdleR));
    }
    else {
      setAnimation(animationStrings.at(IdleL));
    }

  }
}

void PlayerObject::fallAtDir(MovementDirectionX dir, std::string animName) {
  const float playerFallSpeed = 0.75;
  setAnimation(animName);
  addToVelocityX(dir*playerFallSpeed);
}

void PlayerObject::playerFallUpdate(float delta) {
  if (getMovementStatus() == GO_IN_AIR_DOWN) {
    if (getPrevDir() == GO_LEFT) {
      fallAtDir(LEFT, animationStrings.at(FallL));
    }
    else if (getPrevDir() == GO_RIGHT) {
      fallAtDir(RIGHT, animationStrings.at(FallR));
    }
  }
}

float PlayerObject::getFuel() {
  return fuel;
}

bool PlayerObject::flyAtDir(MovementDirectionX dir, std::string animName) {
  const float playerFallSpeed = 0.1f;
  setAnimation(animName);
  addToVelocityX(dir*playerFallSpeed);
  return true;
}

bool PlayerObject::playerFlyUpdate(float delta) {
  const float jetPackFlySpeed = 1.7f;
  const float maxSpeed = getSpeed();
  const float uppSpeed = 2.2f;
  const float maxRiseSpeed = 100;
  float upp_threshold;
  int throtling = 0;
  bool module_active = false;
  if (flying) {
    upp_threshold = 0.0f;
    consumeRate = 0.0f;
  }
  else {
    upp_threshold = 2.1f;
    consumeRate = 0.00f;;
  }
  const float movement_status = getMovementStatus();
  if (playerInput->isRight()) {
    if (playerInput->getSwipeR() > upp_threshold &&fuel > 0) {
      consumeRate = -currentConsumeRate;
      throtling++;
      module_active = true;
      if (movement_status == GO_ON_GROUND ) {
        if(!flying ){
          setVelocityY(jumpStength);
          flying = true;
          return true;
        }
        else{
          playerInput->resetAnalog();
          flying = false;
          return false;
        }
      }
      if (getVelocityY() < maxRiseSpeed)
        addToVelocityY(playerInput->getSwipeR()*uppSpeed);
      setAnimation(animationStrings.at(FlyR));
      if (getVelocityX() < maxSpeed) {
        addToVelocityX(jetPackFlySpeed);
      }
      module_active = true;
    }
    else {
      

    }
  }
  
  if (playerInput->isLeft()) {
    if (playerInput->getSwipeL() > upp_threshold &&fuel > 0) {
      throtling++;
      consumeRate = -currentConsumeRate;
      if (movement_status == GO_ON_GROUND ) {
        if(!flying){
          setVelocityY(jumpStength);
          flying = true;
          return true;
        }
        else{
          flying = false;
          playerInput->resetAnalog();
          return false;
        }
      }
      if (getVelocityY() < maxRiseSpeed)
        addToVelocityY(playerInput->getSwipeL()*uppSpeed);
      setAnimation(animationStrings.at(FlyL));
      if (getVelocityX() > -maxSpeed) {
        addToVelocityX(-jetPackFlySpeed);
      }
      module_active = true;
    }
    else {

    }
  }
  
  if (movement_status == GO_ON_GROUND) {
    consumeRate = currentConsumeRate;
  }
  if (throtling) {
    jetpack1->play(0.2f);
  }
  else {
    jetpack1->stop();
    if (getVelocityY() > 0)
      setAnimation(animationStrings.at(AscendR));

  }
  fuel += consumeRate;
  if (fuel > 1) {
    fuel = 1;
  }
  if (fuel < 0) {
    fuel = 0;
  }
  
  return module_active;
}

float dashLeftCnt = 0;
float dashRightCnt = 0;
float dashSpeed = 300;
const float dashTime = 0.6f;
const float chargePart = 0.75f;
int dash_stage = 0;

bool PlayerObject::playerDashUpdate(float delta) {
  consumeRate = -currentConsumeRate*0.5f;
  if (fuel <= 0) {
    jetpack1->stop();
    dashRightCnt = 0;
    dashLeftCnt = 0;
    dashingLeft = false;
    dashingRight = false;
    addGravityToObject(true);
    return false;
  }
  if (playerInput->isDoubleRight() && !dashingRight) {
    addGravityToObject(false);
    objectSprite->setScaleX(1);
    dashRightCnt = dashTime;
    dashLeftCnt = 0;
    jetpack1->play(0.2, 1.7f);
  }
  if (playerInput->isDoubleLeft() && !dashingLeft) {
    objectSprite->setScaleX(-1);
    addGravityToObject(false);
    dashLeftCnt = dashTime;
    dashRightCnt = 0;
    jetpack1->play(0.2, 1.7f);
  }
  if (dashRightCnt > 0) {

    setVelocityY(0);
    if (dashRightCnt > chargePart*dashTime) {
      setVelocityX(0);
      setAnimation(animationStrings.at(ItemR));
    }
    else {
      dash_stage++;
      jetpack1->play(0.4, 0.7f);
      setVelocityX(dashSpeed);
      fuel += consumeRate;
      if (fuel < 0) {
        fuel = 0;
      }
      setAnimation(animationStrings.at(Item2R));
    }
    if (dash_stage == 1) {
      jetpack1->stop();
    }
    dashRightCnt -= delta;
    return true;
  }
  if (dashLeftCnt > 0) {
    setVelocityY(0);
    if (dashLeftCnt > chargePart*dashTime) {
      setVelocityX(0);
      setAnimation(animationStrings.at(ItemL));
    }
    else {
      dash_stage++;
      setVelocityX(-dashSpeed);
      fuel += consumeRate;
      if (fuel < 0) {
        fuel = 0;
      }
      setAnimation(animationStrings.at(Item2L));
      jetpack1->play(0.4, 0.7f);
    }
    if (dash_stage == 1) {
      jetpack1->stop();
    }
    dashLeftCnt -= delta;
    return true;
  }
  if (dash_stage > 0) {
    jetpack1->stop();
  }
  dash_stage = 0;
  addGravityToObject(true);
  return false;
}

bool bPlayerShoot = false;
bool PlayerObject::rifle_item(float delta) {
  if (playerInput->isDoubleRight() && !bPlayerShoot) {
    objectSprite->setScaleX(1);
    setAnimationOnce(animationStrings.at(ItemR));
    //setVelocityX(0);
    setPrevDir(GO_RIGHT);
    auto babyTurf = SimpleBullet::create();
    babyTurf->setupHitbox(0.1f, 1.0f, 16, 16, 16, 16, false);
    babyTurf->setObjectPositionX(getPositionX() + 10);
    babyTurf->setObjectPositionY(getPositionY() + 2);
    babyTurf->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::PlayerProjectile);
    babyTurf->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
    babyTurf->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Enemy | (int)PhysicsCategory::PlayerPickups);
    addToGameObjects.pushBack(babyTurf);
    bPlayerShoot = true;
    babyTurf->setVelocityX(200);
    weaponSFX->play(0.4f);
  }
  if (playerInput->isDoubleLeft() && !bPlayerShoot) {
    objectSprite->setScaleX(-1);
    setAnimationOnce(animationStrings.at(ItemR));
    //setVelocityX(0);
    setPrevDir(GO_RIGHT);
    auto babyTurf = SimpleBullet::create();
    babyTurf->setupHitbox(0.1f, 1.0f, 16, 16, 16, 16, false);
    babyTurf->setObjectPositionX(getPositionX() - 20);
    babyTurf->setObjectPositionY(getPositionY() + 2);
    babyTurf->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::PlayerProjectile);
    babyTurf->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
    babyTurf->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Enemy | (int)PhysicsCategory::PlayerPickups);
    addToGameObjects.pushBack(babyTurf);
    bPlayerShoot = true;
    babyTurf->setVelocityX(-200);
    weaponSFX->play(0.4f);
  }
  if (bPlayerShoot) {
    if (getPrevDir() == GO_RIGHT) {
      if (setAnimationOnce(animationStrings.at(ItemR))) {
        bPlayerShoot = false;
        return false;
      }
    }
    else if (getPrevDir() == GO_LEFT) {
      if (setAnimationOnce(animationStrings.at(ItemL)))
      {
        bPlayerShoot = false;
        return false;
      }

    }
    return true;
  }
  return false;
}

bool PlayerObject::no_item(float delta) {
  return false;
}


void PlayerObject::playerUpdate(const float delta) {
  solid = true;
  objectSprite->setPosition(cocos2d::Point((modelPositionX)+4, (modelPositionY)));
  // Update priority

  if ((*this.*pItem)(delta)) {
    return;
  }
  solid = false;// Not Dashing

  if (playerInput->isLeft()) {
    objectSprite->setScaleX(-1);
    if (playerLookAhead > -71)
      playerLookAhead -= 0.2;

  }
  if (playerInput->isRight()) {
    objectSprite->setScaleX(1);
    if (playerLookAhead<71)
      playerLookAhead += 0.2;
  }

  if (!playerFlyUpdate(delta)) {
    playerFallUpdate(delta);
    playerWalkUpdate(delta);
  }

  if (std::abs(this->getVelocityX()) > getSpeed()) {
    setVelocityX(getVelocityX()*0.99f);
  }

  if (playerInput->isLeft()) {
    setPrevDir(GO_LEFT);
  }
  else if (playerInput->isRight()) {
    setPrevDir(GO_RIGHT);
  }
}

bool PlayerObject::hurt(const int dmg, const Vec2 force) {
  if (!isImune()) {
    if (dmg > 0) {
      setImune();
      HP -= dmg;
      playerCrySFX->play(0.3f);
    }



    setVelocityX(force.x);
    setVelocityY(force.y);
    this->unschedule(CC_SCHEDULE_SELECTOR(GameObject::imuneUpdate));
    this->schedule(CC_SCHEDULE_SELECTOR(GameObject::imuneUpdate));
    if (HP <= 0) {
      HP = 0;
    }
    return true;
  }

  return false;
}

void PlayerObject::colideWith(GameObject* otherObj, const uint32_t otherType) {
  if (otherType&(uint32_t)PhysicsCategory::Enemy) {
    auto p = getHitbox();
    auto r = otherObj->getHitbox();
    if (getVelocityY()<0 || (p->getMinX() > r->getMidX())) {
      // Above Enemy
      setVelocityY(getVelocityY()*-0.9f);
      otherObj->hurt(1, Vec2(0, 0));
    }
  }
}

void PlayerObject::setupPlayer(const float x, const float y) {
  setObjectPositionX(x);
  setObjectPositionY(y);
}