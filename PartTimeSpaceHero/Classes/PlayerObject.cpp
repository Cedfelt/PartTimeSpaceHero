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
  addAnimation("PTSH_WEP", "DashRWep", 18, 21, 0.15f);
  addAnimation("PTSH_WEP", "DashLWep", 18, 21, 0.15f);
  addAnimation("PTSH_WEP", "DieRWep", 22, 25, 0.15f);
  addAnimation("PTSH_WEP", "DieLWep", 22, 25, 0.15f);
  addAnimation("PTSH_WEP", "PlayerShootRWep", 26, 29, 0.06f);
  addAnimation("PTSH_WEP", "PlayerShootLWep", 26, 29, 0.06f);


  // Strings
  animationStrings.push_back("IdleRWep");
  animationStrings.push_back("IdleLWep");
  animationStrings.push_back("WalkRWep");
  animationStrings.push_back("WalkLWep");
  animationStrings.push_back("FlyRWep");
  animationStrings.push_back("FlyLWep");
  animationStrings.push_back("AscendRWep");
  animationStrings.push_back("AscendLWep");
  animationStrings.push_back("FallRWep");
  animationStrings.push_back("FallLWep");
  animationStrings.push_back("DashRWep");
  animationStrings.push_back("DashLWep");
  animationStrings.push_back("DieRWep");
  animationStrings.push_back("DieLWep");
  animationStrings.push_back("PlayerShootRWep");
  animationStrings.push_back("PlayerShootLWep");

  objectSprite = cocos2d::Sprite::create();
  objectSprite->setAnchorPoint(cocos2d::Point(0.5, 0.25));
  objectSprite->setPosition(8, -64);// Aling sprite in Hitbox
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
  setItem(E_RIFLE_ITEM);
  /*setItem(E_DASH_ITEM);*/
  return true;
}

const float ground_deacceleration = 0.85;
const float ground_acceleration = 5;

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
  }
  else if (id == E_DASH_ITEM) {
    pItem = &PlayerObject::playerDashUpdate;
  }


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
      if (movement_status == GO_ON_GROUND || platform) {
        setVelocityY(jumpStength);
        flying = true;
        return true;
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
      if (movement_status == GO_ON_GROUND) {
        flying = false;
        consumeRate = currentConsumeRate;
      }

    }
  }
  if (playerInput->isLeft()) {
    if (playerInput->getSwipeL() > upp_threshold &&fuel > 0) {
      throtling++;
      consumeRate = -currentConsumeRate;
      if (movement_status == GO_ON_GROUND && !flying) {
        addToVelocityY(jumpStength);
        flying = true;
        return true;
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
    flying = false;
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
bool dashingRight = false;
bool dashingLeft = false;
float dashLeftCnt = 0;
float dashRightCnt = 0;
float dashSpeed = 300;
const float dashTime = 2.0f;
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
    if (dashRightCnt > 0.5*dashTime) {
      setVelocityX(0);
      setAnimation(animationStrings.at(DashR));
    }
    else {
      dash_stage++;
      jetpack1->play(0.4, 0.7f);
      setVelocityX(dashSpeed);
      fuel += consumeRate;
      if (fuel < 0) {
        fuel = 0;
      }
      setAnimation(animationStrings.at(DieR));
    }
    if (dash_stage == 1) {
      jetpack1->stop();
    }
    dashRightCnt -= delta;
    return true;
  }
  if (dashLeftCnt > 0) {
    setVelocityY(0);
    if (dashLeftCnt > 0.5*dashTime) {
      setVelocityX(0);
      setAnimation(animationStrings.at(DashL));
    }
    else {
      dash_stage++;
      setVelocityX(-dashSpeed);
      fuel += consumeRate;
      if (fuel < 0) {
        fuel = 0;
      }
      setAnimation(animationStrings.at(DieL));
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
    setAnimationOnce(animationStrings.at(PlayerShootR));
    //setVelocityX(0);
    setPrevDir(GO_RIGHT);
    auto babyTurf = SimpleBullet::create();
    babyTurf->setupHitbox(0.1f, 1.0f, 16, 16, 16, 16, false);
    babyTurf->setObjectPositionX(getPositionX() + 10);
    babyTurf->setObjectPositionY(getPositionY() + 2);
    babyTurf->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Player);
    babyTurf->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
    babyTurf->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Enemy);
    addToGameObjects.pushBack(babyTurf);
    bPlayerShoot = true;
    babyTurf->setVelocityX(200);
    weaponSFX->play(0.4f);
  }
  if (playerInput->isDoubleLeft() && !bPlayerShoot) {
    objectSprite->setScaleX(-1);
    //setVelocityX(0);
    setAnimationOnce(animationStrings.at(PlayerShootL));
    bPlayerShoot = true;
    setPrevDir(GO_LEFT);
    auto babyTurf = SimpleBullet::create();
    babyTurf->setupHitbox(0.1f, 1.0f, 16, 16, 16, 16, false);
    babyTurf->setObjectPositionX(getPositionX() - 20);
    babyTurf->setObjectPositionY(getPositionY() + 2);
    babyTurf->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Player);
    babyTurf->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
    babyTurf->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Enemy);
    addToGameObjects.pushBack(babyTurf);
    bPlayerShoot = true;
    babyTurf->setVelocityX(-200);
    weaponSFX->play(0.4f);
  }
  if (bPlayerShoot) {
    if (getPrevDir() == GO_RIGHT) {
      if (setAnimationOnce(animationStrings.at(PlayerShootR))) {
        bPlayerShoot = false;
        return false;
      }
    }
    else if (getPrevDir() == GO_LEFT) {
      if (setAnimationOnce(animationStrings.at(PlayerShootL)))
      {
        bPlayerShoot = false;
        return false;
      }

    }
    return true;
  }
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
    if (p->getMinY() + 20 > r->getMaxY()) {
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