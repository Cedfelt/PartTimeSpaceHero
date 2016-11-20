//
//  WorldObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "MapObject.hpp"
#include "PlayerObject.hpp"
#include "GameObject.hpp"
#include "Physic.hpp"
#include "GoalObject.hpp"
#include "SaveData.hpp"
#include "WaterTiles.hpp"
#include "DialogObject.hpp"
#include "CameraObject.hpp"


class WorldObject : public cocos2d::Node
{
public:
  // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
  virtual bool init();
  cocos2d::Vector<GameObject*>* getGameObjects();
  CREATE_FUNC(WorldObject);
  // implement the "static create()" method manually
  PlayerObject* player;
   void finishLevel();
  cocos2d::Vector<DialogObject*>* dialogObjects;
  int bg_color;
  void setupWorld();
  CameraObject* camera;
private:
  bool goOnScreen(GameObject *obj);
  void updateOffScreenRect();
  cocos2d::Rect screen;
  float outside_screen;
  cocos2d::DrawNode *screen_draw;
  bool view_of_screen_rect = false;
  
  MapObject* mapObject;
  cocos2d::Vector<GameObject*> gameObjects;
  cocos2d::Vector<GameObject*> plattis;
  void spawnObjects(cocos2d::Vector<GameObject*>* gameObjects);
  void setViewPointCenter(const cocos2d::Point position);
  void updateWorld(float delta);
  bool onContactBegan(PhysicsContact &contact);
  GoalObject* obj;
  Physic* physic;
  
  // Crate
  bool createSpawned = false;
  bool giveObject = false;
  int playerSafe = 0;
  int flyCnt = 0;
  bool finish_scene(float delta);
  float finish_time = 5.f;
  bool death_scene(float delta);
  float dead_time = 5.f;
  WaterTiles* water;
};

