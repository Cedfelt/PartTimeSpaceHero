//
//  GlobalPList.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "GlobalPList.hpp"

bool setScaleFactor(const size_t scale){
    CC_ASSERT(scale!=0);
    cocos2d::UserDefault::getInstance()->setIntegerForKey("scale_factor", (int)scale);
    return true;
}

size_t getScaleFactor(){
    const size_t scale = cocos2d::UserDefault::getInstance()->getIntegerForKey("scale_factor");
    CC_ASSERT(scale!=0);
    return scale;
}


const char map_url_code [25] = "map_url";
bool setMapUrl(const std::string mapUrl) {
  cocos2d::UserDefault::getInstance()->setStringForKey(map_url_code, mapUrl);
  cocos2d::UserDefault::getInstance()->flush();
  
  return true;
}

std::string getMapUrl() {
  std::string mapUrl = cocos2d::UserDefault::getInstance()->getStringForKey(map_url_code);
  return mapUrl;
}

