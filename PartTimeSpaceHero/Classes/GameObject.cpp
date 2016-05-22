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
  addGravityToObject(true);
  setElastic(0);
  colided = false;
  remove_object = false;
  resolution_scale = getScaleFactor();
  return true;
}

void GameObject::setupHitbox(float aDensity, float aRestitution, const float w, const float h,const float box, const float boy, const bool draw) {
  setPosition(0, 0);
  hitBox.setRect(0, 0, w, h);
  if (draw) {
    cocos2d::Vec2 rectangle[4];
    rectangle[0] = cocos2d::Vec2(0 , 0);
    rectangle[1] = cocos2d::Vec2(w, 0);
    rectangle[2] = cocos2d::Vec2(w, h);
    rectangle[3] = cocos2d::Vec2(0, h);
    drawPolygon(rectangle, 4, cocos2d::Color4F::RED, 1, cocos2d::Color4F::BLUE);
  }

  auto physicsBody = PhysicsBody::createBox(Size(w, h), PhysicsMaterial(aDensity, aRestitution, 0.0f));
  physicsBody->setPositionOffset(Vec2(box,boy));
  physicsBody->setDynamic(true);
  setPhysicsBody(physicsBody);
    
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

void GameObject::colideWith(GameObject *otherGo){
}

void GameObject::interActWithPlayer(GameObject* player){

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
  //Rect r = Rect(0, 0, 0, 0);
  return &hitBox;
}

void GameObject::setPrevDir(int32_t prev_dir){
  prevDirection = prev_dir;
}
int32_t GameObject::getPrevDir(){
  return prevDirection;
}

void GameObject::setObjectPositionX(const float x){
  modelPositionX = x;
  hitBox.origin.x = int(modelPositionX);
  setPositionX(int(modelPositionX));
}

float GameObject::getObjectPositionX(){
  return modelPositionX;
}

void GameObject::setObjectPositionY(const float y){
  modelPositionY = y;
  hitBox.origin.y = int(modelPositionY);
  setPositionY(int(modelPositionY));
}

float GameObject::getObjectPositionY(){
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