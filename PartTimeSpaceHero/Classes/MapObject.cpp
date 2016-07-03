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
  setupLiquidLayers();
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
    if(cnt == 0){
      bg->setScale(1);
    }
    cnt++;
    background_layers.pushBack(bg);
    bg_cnt++;
    bg = map->getLayer((bgs + std::to_string(bg_cnt)));
    
  }
}
float animation_speed = 0.2f;
float animation_speed_total;
int liquidIndex = 0;
int layers;
float timeCnt = 0;
void MapObject::setupLiquidLayers(){
  layers = 4;
  animation_speed_total = animation_speed*layers;
  
  std::string bgs = "liquid";
  int bg_cnt = 1;
  TMXLayer *liq = map->getLayer((bgs + std::to_string(bg_cnt)));
  while (liq != NULL) {
    liquid_layers.pushBack(liq);
    liq->setGlobalZOrder(5);
    bg_cnt++;
    liq = map->getLayer((bgs + std::to_string(bg_cnt)));
    
    
  }
}



void MapObject::moveBackgroundLayers(){
  for (int i = 0; i < background_layers.size();i++) {
    auto layer_grp = background_layers.at(i)->getProperties();
    float bg_speed = layer_grp["BACKGROUND_SPEED"].asFloat();
    if (bg_speed == 0) {
      bg_speed = 1;
    }
    auto v = bg_speed*map->convertToNodeSpace(Point(0.0, 0.0));
    v.x = int(v.x);
    v.y = int(v.y);
    background_layers.at(i)->setPosition(v);
  }
}

int a = 0;
void MapObject::updateLiquids(const float delta){
  timeCnt+=delta;
  if(timeCnt>=animation_speed_total){
    timeCnt = 0;
    //liquid_layers.at(1)->setVisible(a);
    a++;
    if( a>1){
      a = 0;
    }
  }
  //cocos2d::log("%u",liquidIndex);
  liquidIndex = (int)(timeCnt/animation_speed);
  for (int i = 0; i < liquid_layers.size();i++) {
    if(i == liquidIndex)
      liquid_layers.at(i)->setVisible(true);
    else{
      liquid_layers.at(i)->setVisible(false);
    }
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




