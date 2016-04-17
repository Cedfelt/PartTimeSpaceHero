//
//  GameObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//
#include "GameObject.hpp"
#include "GlobalPList.hpp"

bool GameObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!DrawNode::init())
  {
    return false;
  }
  resolution_scale = getScaleFactor();
  return true;
}

void GameObject::setupHitbox(const float x, const float y, const float w, const float h, const bool draw) {
  setPosition(x, y);
  hitBox.setRect(x, y, w, h);
  if (draw) {
    cocos2d::Vec2 rectangle[4];
    rectangle[0] = cocos2d::Vec2(0, 0);
    rectangle[1] = cocos2d::Vec2(w, 0);
    rectangle[2] = cocos2d::Vec2(w, h);
    rectangle[3] = cocos2d::Vec2(0, h);
    drawPolygon(rectangle, 4, cocos2d::Color4F::RED, 1, cocos2d::Color4F::BLUE);
  }
}

void GameObject::addAnimation(std::string fileName,std::string animation_name,int start,int end,float animSpeed){
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames(end-start);
    std::string fileFormat = "%i.png";
    std::string fileName_update = fileName+fileFormat;
    
    for(int i = start;i<=end;i++){
        auto name = cocos2d::String::createWithFormat(fileName_update.c_str(), i);
        auto frame = spriteFrameCache->getSpriteFrameByName(name->getCString());
        frame->getTexture()->setAliasTexParameters();
        animFrames.pushBack(frame);
    }
    animationCache->addAnimation(cocos2d::Animation::createWithSpriteFrames(animFrames,animSpeed), animation_name);
}

void GameObject::setAnimation(std::string anim){
  if(prevAnimation!=anim){
    objectSprite->stopAllActions();
    objectSprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animationCache->getAnimation(anim))));
  }
  prevAnimation = anim;
}

int32_t GameObject::getMovementStatus(){
  if(velocityY==0){
    return GO_ON_GROUND;
  }
  else if(velocityY<0){
    return GO_IN_AIR_DOWN;
  }
  else if(velocityY>0){
    return GO_IN_AIR_UP;
  }
  CC_ASSERT(false); // MISSING A STATUS
  return GO_ON_GROUND;
}

void GameObject::addToVelocityX(const float velX){
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

Rect* GameObject::getHitbox(){
  return &hitBox;
}

void GameObject::setPrevDir(int32_t prev_dir){
  prevDirection = prev_dir;
}
int32_t GameObject::getPrevDir(){
  return prevDirection;
}
float x2;
void GameObject::setObjectPositionX(const float x){
  x2 = x;
  hitBox.origin.x = int(x2);
  setPositionX(int(x2));
}

float GameObject::getObjectPositionX(){
  return x2;
}
void GameObject::setObjectPositionY(const float y){
  hitBox.origin.y = y;
  setPositionY(y);
}

void GameObject::setSpeed(float s) {
  speed = s;
}

float GameObject::getSpeed() {
  return speed;
}