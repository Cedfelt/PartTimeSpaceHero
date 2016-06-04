//
//  MapObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "MapObject.hpp"
#include "GlobalPList.hpp"
#include "PlayerObject.hpp"



bool MapObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!Node::init()){return false;}
  setAnchorPoint(Point(0,0));
  map = TMXTiledMap::create(getMapUrl());
  map->setAnchorPoint(Point(0,0));
  addChild(map);
  mapWidth = map->getMapSize().width;
  mapHeight = map->getMapSize().height;
  tileSize = map->getTileSize().width;
  
  mapData = MapData::create();
  addChild(mapData);
  mapData->setupAttributes(map);
  
  setupBackgroundLayers();
  
  return true;
}

void MapObject::setupAttributes() {
  
}

uint32_t MapObject::attributeAt(const uint32_t x, const uint32_t y) {
  if (x < TILES_COUNT_X&&y < TILES_COUNT_Y) {
    return mapData->attributes[x][y];
  }
  return MapData::BLOCKED;
}

void MapObject::setupBackgroundLayers(){
  std::string bgs = "background";
  int bg_cnt = 1;
  TMXLayer *bg = map->getLayer((bgs + std::to_string(bg_cnt)));
  
  int cnt = 0;// Make the scala an atribute of the layer!!!
  while (bg != NULL) {
    if(cnt == 0)
      bg->setScale(2);
    cnt++;
    background_layers.pushBack(bg);
    bg = map->getLayer((bgs + std::to_string(bg_cnt)));
    bg_cnt++;
  }
}

void MapObject::moveBackgroundLayers(){
  for (int i = 0; i < background_layers.size();i++) {
    auto layer_grp = background_layers.at(i)->getProperties();
    float bg_speed = layer_grp["BACKGROUND_SPEED"].asFloat();
    if (bg_speed == 0) {
      bg_speed = 1;
    }
    background_layers.at(i)->setPosition(bg_speed*map->convertToNodeSpace(Point(0, 0.)));
  }
}



uint32_t MapObject::getMapWidthInTiles(){
  return mapWidth;
}

uint32_t MapObject::getMapHeightInTiles(){
  return mapHeight;
}

uint32_t MapObject::getMapTileSize(){
  return tileSize;
}




