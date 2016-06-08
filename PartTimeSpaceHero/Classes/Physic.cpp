//
//  GameScene.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "Physic.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GlobalPList.hpp"
#include "MapData.hpp"

USING_NS_CC;

# define GRAVITY -90.0
# define MAX_FALLSPEED -750.0

// on "init" you need to initialize your instance
bool Physic::init() {
  if (!Node::init()) { return false; }
  return true;
}

int dir_sign(const float num) {
  if (num < 0) {
    return 1;
  }
  return -1;
}

float round_and(float f) {
  return floorf(f + 0.5f);
}
enum collision_bits {
  E_CB_NONE = 0,
  E_CB_BLOCKED = 1,
  EB_CB_ONE_WAY_UP = 2
};

void Physic::movePlatforms(cocos2d::Vector<GameObject*>* gameObjects, MapObject* mapObject, const float delta) {
  const size_t obj_cnt = gameObjects->size();
  for (int i = 0;i < obj_cnt;i++) {

    GameObject* obj = gameObjects->at(i);
    obj->lastX = obj->getObjectPositionX();
    obj->lastY = obj->getObjectPositionY();
    uint32_t collision_mask = E_CB_BLOCKED;
    if (obj->getVelocityY() <= 0) {
      collision_mask |= EB_CB_ONE_WAY_UP;
    }

    if (obj->remove_object || obj->skipMove) {
      continue;
    }
    if (obj->isAffectedByGravity()) {
      obj->addToVelocityY(delta*GRAVITY);// GRAVITY
      if (obj->getVelocityY() < MAX_FALLSPEED) {
        obj->setVelocityY(MAX_FALLSPEED);
      }
    }

    // COLLISION Y-AXIS
    obj->setObjectPositionY((obj->getObjectPositionY() + (obj->getVelocityY()*delta + obj->moveY)));
    if (isBlockedPlatform(obj, obj->getHitbox(), mapObject, collision_mask, delta)) {
      const int sign = dir_sign(obj->getVelocityY());
      obj->setObjectPositionY((int)(obj->getObjectPositionY() + sign));
      while (isBlockedPlatform(obj, obj->getHitbox(), mapObject, collision_mask, delta)) {
        obj->setObjectPositionY((int)(obj->getObjectPositionY() + sign));
      }
      // BLOCKED Y
      const float newVel = obj->getVelocityY() * obj->getElastic();
      obj->setVelocityY(newVel* -1);
    }

    // COLLISION X-AXIS
    obj->setObjectPositionX((obj->getObjectPositionX() + (delta*obj->getVelocityX() + obj->moveX)));
    if (isBlockedPlatform(obj, obj->getHitbox(), mapObject, collision_mask, delta)) {
      const int sign = dir_sign(obj->getVelocityX());
      obj->setObjectPositionX(int(obj->getObjectPositionX() + sign));
      while (isBlockedPlatform(obj, obj->getHitbox(), mapObject, collision_mask, delta)) {
        obj->setObjectPositionX(int(obj->getObjectPositionX() + sign));
      }
      // BLOCKED X
      const float newVel = obj->getVelocityX() * obj->getElastic();
      obj->setVelocityX(newVel * -1);
    }
    obj->moveX = 0;
    obj->moveY = 0;
  }

}

void Physic::moveGameObjects(cocos2d::Vector<GameObject*>* gameObjects, MapObject* mapObject, const float delta) {
  const size_t obj_cnt = gameObjects->size();
  for (int i = 0;i < obj_cnt;i++) {

    GameObject* obj = gameObjects->at(i);
    obj->lastX = obj->getObjectPositionX();
    obj->lastY = obj->getObjectPositionY();
    uint32_t collision_mask = E_CB_BLOCKED;
    if (obj->getVelocityY() <= 0) {
      collision_mask |= EB_CB_ONE_WAY_UP;
    }

    if (obj->remove_object || obj->skipMove) {
      continue;
    }
    if (obj->isAffectedByGravity()) {
      obj->addToVelocityY(delta*GRAVITY);// GRAVITY
      if (obj->getVelocityY() < MAX_FALLSPEED) {
        obj->setVelocityY(MAX_FALLSPEED);
      }
    }

    // COLLISION Y-AXIS
    obj->setObjectPositionY((obj->getObjectPositionY() + (obj->getVelocityY()*delta + obj->moveY)));
    if (isBlocked(obj, obj->getHitbox(), mapObject, collision_mask, delta)) {
      const int sign = dir_sign(obj->getVelocityY());
      obj->setObjectPositionY((int)(obj->getObjectPositionY() + sign));
      while (isBlocked(obj, obj->getHitbox(), mapObject, collision_mask, delta)) {
        obj->setObjectPositionY((int)(obj->getObjectPositionY() + sign));
      }
      // BLOCKED Y
      const float newVel = obj->getVelocityY() * obj->getElastic();
      obj->setVelocityY(newVel* -1);
    }

    // COLLISION X-AXIS
    obj->setObjectPositionX((obj->getObjectPositionX() + (delta*obj->getVelocityX() + obj->moveX)));
    if (isBlocked(obj, obj->getHitbox(), mapObject, collision_mask,  delta)) {
      const int sign = dir_sign(obj->getVelocityX());
      obj->setObjectPositionX(int(obj->getObjectPositionX() + sign));
      while (isBlocked(obj, obj->getHitbox(), mapObject, collision_mask, delta)) {
        obj->setObjectPositionX(int(obj->getObjectPositionX() + sign));
      }
      // BLOCKED X
      const float newVel = obj->getVelocityX() * obj->getElastic();
      obj->setVelocityX(newVel * -1);
    }
    obj->moveX = 0;
    obj->moveY = 0;
  }

}


uint32_t print = 0;
bool Physic::isBlocked(GameObject* obj, const Rect* hitBox, MapObject* map, const uint32_t mask, const float delta) {
  Rect tile_rect;
  const size_t ts = 8;
  const uint32_t x_min = ((int)(hitBox->getMinX()) / (ts));
  const uint32_t x_max = ((int)(hitBox->getMaxX()) / (ts));
  const uint32_t y_min = ((int)(hitBox->getMinY()) / (ts));
  const uint32_t y_max = ((int)(hitBox->getMaxY()) / (ts));
  const uint32_t xRange = x_min + x_max - x_min + 1;
  const uint32_t yRange = y_min + y_max - y_min + 1;
  const uint32_t mapWidth = map->getMapWidthInTiles();
  const uint32_t mapHeight = map->getMapWidthInTiles();
  // Out of bounds
  if (x_min > mapWidth || x_max > mapWidth) {
    return true;
  }
  if (y_min > mapHeight || y_max > mapHeight) {
    return true;
  }

  for (uint32_t xx = x_min; xx < xRange;xx++) {
    for (uint32_t yy = y_min; yy < yRange;yy++) {

      uint32_t attribute = map->attributeAt(xx, yy);
      if (attribute == MapData::CLEAR) {
        continue;
      }
      else if (attribute == MapData::BLOCKED) {
        tile_rect.setRect(xx*ts, yy*ts, ts, ts);
      }
      else if (attribute == MapData::ONE_WAY_UP) {
        if ((mask & EB_CB_ONE_WAY_UP) && yy*ts < hitBox->getMinY())
          tile_rect.setRect(xx*ts, yy*ts, ts, ts);
        else
          continue;
      }

      bool cond1 = hitBox->intersectsRect(tile_rect);
      if (cond1) {
        return true;
      }
    }
  }
  for (int i = 0;i < platforms->size();i++)
  {
    auto a = platforms->at(i)->getHitbox();
    tile_rect.setRect(a->getMinX(), a->getMinY(), a->getMaxX() - a->getMinX(), a->getMaxY() - a->getMinY());
    if (hitBox->intersectsRect(tile_rect)) {
      return true;
    }
  }
  return false;
}

bool Physic::isBlockedPlatform(GameObject* obj, const Rect* hitBox, MapObject* map, const uint32_t mask, const float delta) {
  Rect tile_rect;
  const size_t ts = 8;
  const uint32_t x_min = ((int)(hitBox->getMinX()) / (ts));
  const uint32_t x_max = ((int)(hitBox->getMaxX()) / (ts));
  const uint32_t y_min = ((int)(hitBox->getMinY()) / (ts));
  const uint32_t y_max = ((int)(hitBox->getMaxY()) / (ts));
  const uint32_t xRange = x_min + x_max - x_min + 1;
  const uint32_t yRange = y_min + y_max - y_min + 1;
  const uint32_t mapWidth = map->getMapWidthInTiles();
  const uint32_t mapHeight = map->getMapWidthInTiles();
  // Out of bounds
  if (x_min > mapWidth || x_max > mapWidth) {
    return true;
  }
  if (y_min > mapHeight || y_max > mapHeight) {
    return true;
  }

  for (uint32_t xx = x_min; xx < xRange;xx++) {
    for (uint32_t yy = y_min; yy < yRange;yy++) {

      uint32_t attribute = map->attributeAt(xx, yy);
      if (attribute == MapData::CLEAR) {
        continue;
      }
      else if (attribute == MapData::BLOCKED) {
        tile_rect.setRect(xx*ts, yy*ts, ts, ts);
      }
      else if (attribute == MapData::ONE_WAY_UP) {
        if ((mask & EB_CB_ONE_WAY_UP) && yy*ts < hitBox->getMinY())
          tile_rect.setRect(xx*ts, yy*ts, ts, ts);
        else
          continue;
      }

      bool cond1 = hitBox->intersectsRect(tile_rect);
      if (cond1) {
        return true;
      }
    }
  }


  return false;
}


void Physic::colideGameObjects(cocos2d::Vector<GameObject*>* gameObjects) {

}

void Physic::gameObjectCollision(GameObject*  goA, GameObject* goB) {

  /*nodeA->addToVelocityX(nodeB->getVelocityX());
  nodeA->addToVelocityY(nodeB->getVelocityY());
  nodeB->addToVelocityX(nodeA->getVelocityX());
  nodeB->addToVelocityY(nodeA->getVelocityY());*/
  const float aMass = goA->getPhysicsBody()->getMass() *0.01 * (!goA->remove_object) *goA->solid;
  const float bMass = goB->getPhysicsBody()->getMass() *0.01 * (!goB->remove_object) *goA->solid;
  const Vec2 repA = Vec2(goB->getVelocityX(), goB->getVelocityY());
  const Vec2 repB = Vec2(goA->getVelocityX(), goA->getVelocityY());

  //WE DONT WANT COLLISION WITH REMOVED OBJECTS, EG COINS
  if ((aMass != 0.0f) && !goB->remove_object&&!goA->staticBoody) {
    goA->setVelocityX(repA.x * bMass / aMass);
    goA->setVelocityY(repA.y * bMass / aMass);
  }

  if ((bMass != 0.0f) && !goA->remove_object&&!goA->staticBoody) {
    goB->setVelocityX(repB.x  * aMass / bMass);
    goB->setVelocityY(repB.y * aMass / bMass);
  }

  //nodeA->removeFromParent();
  //nodeB->removeFromParent();
  //return true;
}

