//
//  MapObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "MapObject.hpp"
#include "GlobalPList.hpp"

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
  setupAttributes();
  setupBackgroundLayers();
  
  return true;
}

void MapObject::setupAttributes() {
  TMXLayer *tempLayer;
  tempLayer = map->getLayer("walls");
  const size_t mh = mapHeight-1;
  const size_t mw = mapWidth-1;
  if(!tempLayer){
    log("NO 'walls' -layer");
    return;
  }
  for(int x = 0;x<mw;x++){
    for(int y = 0;y<mh;y++){
      int gid = tempLayer->getTileGIDAt(Point(x, mh - (y)));
      if(gid>0){
        attributes[x][y] = BLOCKED;
      }
      else{
        attributes[x][y] = CLEAR;
      }
    }
  }
}

uint32_t MapObject::attributeAt(const uint32_t x, const uint32_t y) {
  if (x < BLOCK_SIZE&&y < BLOCK_SIZE) {
    return attributes[x][y];
  }
  return BLOCKED;
}

void MapObject::setupBackgroundLayers(){
  std::string bgs = "background";
  int bg_cnt = 1;
  TMXLayer *bg = map->getLayer((bgs + std::to_string(bg_cnt)));
  
  while (bg != NULL) {
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
      bg_speed = 0.8;
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



