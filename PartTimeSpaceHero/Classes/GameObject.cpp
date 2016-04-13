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
  if (draw) {
    cocos2d::Vec2 rectangle[4];
    const float hitBoxWidth = 32;
    const float hitBoxHeight = 32;
    rectangle[0] = cocos2d::Vec2(0, 0);
    rectangle[1] = cocos2d::Vec2(w, 0);
    rectangle[2] = cocos2d::Vec2(w, h);
    rectangle[3] = cocos2d::Vec2(0, h);
    drawPolygon(rectangle, 4, cocos2d::Color4F::RED, 1, cocos2d::Color4F::BLUE);
  }
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

void GameObject::setSpeed(float s) {
  speed = s;
}

float GameObject::getSpeed() {
  return speed;
}