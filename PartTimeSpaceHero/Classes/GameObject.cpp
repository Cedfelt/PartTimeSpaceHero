//
//  GameObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//
#include "GameObject.hpp"
#include "GlobalPList.hpp"
#include "CoinObject.hpp"

bool GameObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!DrawNode::init())
  {
    return false;
  }
  addGravityToObject(true);
  setElastic(0);
  colided = false;
  remove_object = false;
  resolution_scale = getScaleFactor();
  HP = 1;
  imuneTime = 1;
  imuneCnt = 0;
  platform = false;
  solid = 1;
  staticBoody = false;
  bWallCollisions = true;
  speed = 50.0f;
  return true;
}

void GameObject::imuneUpdate(const float delta) {
  if (imuneCnt > 0) {
    imuneCnt -= delta;
    if (imuneCnt <= 0) {
      imuneCnt = 0;
      this->unschedule(CC_SCHEDULE_SELECTOR(GameObject::imuneUpdate));
    }
  }
}

bool GameObject::isImune() {
  return imuneCnt > 0;
}

void GameObject::setImune() {
  imuneCnt = imuneTime;
}

void GameObject::setupHitbox(float aDensity, float aRestitution, const float w, const float h, const float box, const float boy, const bool draw) {
  hitBox.setRect(0, 0, w, h);
  if (getDebuggDraw()) {
    cocos2d::Vec2 rectangle[4];
    rectangle[0] = cocos2d::Vec2(0, 0);
    rectangle[1] = cocos2d::Vec2(w, 0);
    rectangle[2] = cocos2d::Vec2(w, h);
    rectangle[3] = cocos2d::Vec2(0, h);
    drawPolygon(rectangle, 4, cocos2d::Color4F::RED, 1, cocos2d::Color4F::BLUE);
  }

  auto physicsBody = PhysicsBody::createBox(Size(w, h), PhysicsMaterial(aDensity, aRestitution, 0.0f));
  physicsBody->setPositionOffset(Vec2(box, boy));
  physicsBody->setDynamic(true);
  setPhysicsBody(physicsBody);

}

void GameObject::addAnimation(std::string fileName, std::string animation_name, int start, int end, float animSpeed) {
  cocos2d::Vector<cocos2d::SpriteFrame*> animFrames(end - start);
  std::string fileFormat = "%i.png";
  std::string fileName_update = fileName + fileFormat;

  for (int i = start;i <= end;i++) {
    auto name = cocos2d::String::createWithFormat(fileName_update.c_str(), i);
    auto frame = spriteFrameCache->getSpriteFrameByName(name->getCString());
    frame->getTexture()->setAliasTexParameters();
    animFrames.pushBack(frame);
  }
  animationCache->addAnimation(cocos2d::Animation::createWithSpriteFrames(animFrames, animSpeed), animation_name);
}

void GameObject::colideWith(GameObject *otherGo, const uint32_t otherType) {
}

void GameObject::setAnimation(std::string anim) {
  if (prevAnimation != anim) {
    objectSprite->stopAllActions();
    objectSprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animationCache->getAnimation(anim))));
  }
  prevAnimation = anim;
}

bool GameObject::setAnimationOnce(std::string anim) {
  if (prevAnimation != anim) {
    objectSprite->stopAllActions();
    r = cocos2d::Repeat::create(cocos2d::Animate::create(animationCache->getAnimation(anim)), 1);
    objectSprite->runAction(r);
  }
  prevAnimation = anim;
  return objectSprite->getNumberOfRunningActions() == 0;
}

bool GameObject::checkForWallCollisions() {
  return bWallCollisions;
}

uint32_t GameObject::getCurrentAnimationFrameIndex() {
  return 0;
}

int32_t GameObject::getMovementStatus() {
  if (velocityY == 0 || platform) {
    return GO_ON_GROUND;
  }
  else if (velocityY < 0) {
    return GO_IN_AIR_DOWN;
  }
  else if (velocityY > 0) {
    return GO_IN_AIR_UP;
  }
  CC_ASSERT(false); // MISSING A STATUS
  return GO_ON_GROUND;
}

void GameObject::addToVelocityX(const float velX) {
  velocityX += velX;
}
void GameObject::setVelocityX(const float velX) {
  velocityX = velX;
}
float GameObject::getVelocityX() {
  return velocityX;
}
void GameObject::addToVelocityY(const float velY) {
  velocityY += velY;
}
void GameObject::setVelocityY(const float velY) {
  velocityY = velY;
}
float GameObject::getVelocityY() {
  return velocityY;
}

Rect* GameObject::getHitbox() {
  //Rect r = Rect(0, 0, 0, 0);
  return &hitBox;
}

void GameObject::setPrevDir(int32_t prev_dir) {
  prevDirection = prev_dir;
}
int32_t GameObject::getPrevDir() {
  return prevDirection;
}

uint32_t GameObject::getObjectType() {
  return getPhysicsBody()->getCategoryBitmask();
}

bool GameObject::hurt(const int dmg, const Vec2 force) {
  if (!isImune()) {
    setImune();
    HP -= dmg;
    addToVelocityX(force.x);
    addToVelocityY(force.y);
    this->unschedule(CC_SCHEDULE_SELECTOR(GameObject::imuneUpdate));
    this->schedule(CC_SCHEDULE_SELECTOR(GameObject::imuneUpdate));
    if (HP <= 0) {
      HP = 0;
      deadState();
    }
    return true;
  }
  return false;
}

void GameObject::deadState() {
  this->remove_object = true;
}

void GameObject::removeWhenBelowZeroUpdate(const float delta) {
  if (getHitbox()->getMaxY() < 0) {
    this->remove_object = true;
  }
}

void GameObject::removeWhenBelowZero() {
  this->schedule(schedule_selector(GameObject::removeWhenBelowZeroUpdate), 1);
}

uint32_t GameObject::isBlocked(uint32_t x, uint32_t y) {
  if (x < TILES_COUNT_X&&y < TILES_COUNT_Y) {
    return mapData->attributes[x][y] != MapData::CLEAR;
  }
  return true;
}

void GameObject::setObjectPositionX(const float x) {
  modelPositionX = x;
  hitBox.origin.x = (modelPositionX);
  setPositionX(x);
}

float GameObject::getObjectPositionX() {
  return modelPositionX;
}

void GameObject::addCoins(uint32_t coinsToAdd) {
  coins += coinsToAdd;
}

void GameObject::setCoins(uint32_t coinsSet) {
  coins = coinsSet;
}

uint32_t GameObject::getCoins() {
  return coins;
}

void GameObject::setObjectPositionY(const float y) {

  modelPositionY = y;
  hitBox.origin.y = int(modelPositionY);
  setPositionY(y);
}

bool GameObject::isSafe() {
  return true;
}

float GameObject::getObjectPositionY() {
  return modelPositionY;
}

void GameObject::setSpeed(float s) {
  speed = s;
}

float GameObject::getSpeed() {
  return speed;
}

bool GameObject::isAffectedByGravity(void) {
  return affectedByGravity;
}
void GameObject::addGravityToObject(const bool bGrav) {
  affectedByGravity = bGrav;
}

float GameObject::getElastic(void) {
  return elastic;
}
void GameObject::setElastic(const float fElastic) {
  elastic = fElastic;
}

void GameObject::setTurnAtEdges(const bool bState) {
  bTurnAtEdges = bState;
}
void GameObject::setStupidWalk(const bool bState) {
  bStupidWalk = bState;
}
void GameObject::setStayInZone(const bool bState) {
  bStayInZone = bState;
}

void GameObject::dropCoin(int nrOfCoins) {
  for (int i = 0;i < nrOfCoins;i++) {
    auto coin = CoinObject::create();
    coin->setupHitbox(0.1f, 1.0f, 16, 16, 16, 16, false);
    coin->setObjectPositionX(getPositionX());
    coin->setObjectPositionY(getHitbox()->getMidY());
    coin->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::PlayerPickups);
    coin->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
    coin->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player | (int)PhysicsCategory::Hazard);
    coin->setVelocityX(cocos2d::random(-25, 25));
    coin->setVelocityY(cocos2d::random(10, 50));
    coin->addGravityToObject(true);
    coin->setElastic(1);
    addToGameObjects.pushBack(coin);
  }
}

void GameObject::flash(int times, float interval){
  this->schedule(CC_SCHEDULE_SELECTOR(GameObject::flash_sprite),interval,times,0);
}

void GameObject::flash_sprite(float delta){
  cocos2d::Color3B c = objectSprite->getColor();
  if(c !=c.RED){
    objectSprite->setColor(c.RED);
  }
  else{
    objectSprite->setColor(c.WHITE);
  }
}

void GameObject::setItem(PlayerItem_ID id) {

}

bool GameObject::setupAnimation() {
  return false;
}