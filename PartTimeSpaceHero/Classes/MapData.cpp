//
//  MapData.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 03/06/16.
//
//

#include "MapData.hpp"
#include "GlobalPList.hpp"

bool MapData::init() {
  //////////////////////////////
  // 1. super init first
  if (!Node::init())
  {
    return false;
  }
  return true;
}

void MapData::setupAttributes(cocos2d::TMXTiledMap* map) {
  cocos2d::TMXLayer *tempLayer;
  tempLayer = map->getLayer("walls");
  const size_t mh = map->getMapSize().height-1;
  const size_t mw = map->getMapSize().width-1;
  if(!tempLayer){
    cocos2d::log("NO 'walls' -layer");
    return;
  }
  for(int x = 0;x<mw;x++){
    for(int y = 0;y<mh;y++){
      int gid = tempLayer->getTileGIDAt(cocos2d::Point(x, mh - (y)));
      if(gid>0){
        attributes[x][y] = BLOCKED;
      }
      else{
        attributes[x][y] = CLEAR;
      }
    }
  }
}
