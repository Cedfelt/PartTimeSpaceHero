//
//  MapObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "GameObject.hpp"
using namespace cocos2d;

class MapObject : public cocos2d::Node
{
public:
  // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
  enum{
    BLOCKED,
    WATER,
    CLEAR,
    DESTRUCTABLE
  };
  virtual bool init();
  void spawnObjects(cocos2d::Vector<GameObject*> gameObjects);
  uint32_t attributeAt(const uint32_t x, const uint32_t y);
  uint32_t getMapWidthInTiles();
  uint32_t getMapHeightInTiles();
  uint32_t getMapTileSize();
  void setupBackgroundLayers();
  void moveBackgroundLayers();
  // implement the "static create()" method manually
  CREATE_FUNC(MapObject);
  TMXTiledMap* map;
private:
  void setupAttributes();
  uint32_t mapWidth;
  uint32_t mapHeight;
  uint32_t tileSize;
  cocos2d::Vector<cocos2d::TMXLayer*> background_layers;
#define BLOCK_SIZE 1000
  uint32_t attributes[BLOCK_SIZE][BLOCK_SIZE];
};
