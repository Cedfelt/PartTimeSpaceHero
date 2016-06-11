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
#include "MapData.hpp"
using namespace cocos2d;

class MapObject : public cocos2d::Node
{
public:
  // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
  virtual bool init();
  void spawnObjects(cocos2d::Vector<GameObject*> gameObjects);
  uint32_t attributeAt(const uint32_t x, const uint32_t y);
  uint32_t getMapWidthInTiles();
  uint32_t getMapHeightInTiles();
  uint32_t getMapTileSize();
  void setupBackgroundLayers();
  void moveBackgroundLayers();
  MapData* mapData;
  // implement the "static create()" method manually
  CREATE_FUNC(MapObject);
  TMXTiledMap* map;
  void setupForegroundLayers();
  void setupLiquidLayers();
  void updateLiquids(const float delta);
private:
  void setupAttributes();
  uint32_t mapWidth;
  uint32_t mapHeight;
  uint32_t tileSize;
  cocos2d::Vector<cocos2d::TMXLayer*> background_layers;
  cocos2d::Vector<cocos2d::TMXLayer*> liquid_layers;

};
