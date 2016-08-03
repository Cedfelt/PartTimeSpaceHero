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

void setDebuggDraw(const bool debugDraw){
  cocos2d::UserDefault::getInstance()->setBoolForKey("debugDraw", debugDraw);
}

bool getDebuggDraw(){
  return cocos2d::UserDefault::getInstance()->getBoolForKey("debugDraw");
}

void setNewGame(bool first) {
  cocos2d::UserDefault::getInstance()->setBoolForKey("NEW_GAME", first);
  cocos2d::UserDefault::getInstance()->flush();
}
bool getNewGame() {
  bool newGame = cocos2d::UserDefault::getInstance()->getBoolForKey("NEW_GAME");
  cocos2d::UserDefault::getInstance()->flush();
  return newGame;
}

void setPlayerGear(uint32_t gear_mask) {
  cocos2d::UserDefault::getInstance()->setIntegerForKey("PLAYER_GEAR", gear_mask);
  cocos2d::UserDefault::getInstance()->flush();
}
uint32_t getPayerGear() {
  uint32_t gear_mask = cocos2d::UserDefault::getInstance()->getIntegerForKey("PLAYER_GEAR");
  cocos2d::UserDefault::getInstance()->flush();
  return gear_mask;
}

void setPlayerMoney(uint32_t money) {
  cocos2d::UserDefault::getInstance()->setIntegerForKey("PLAYER_MONEY", money);
  cocos2d::UserDefault::getInstance()->flush();
}
uint32_t getPayerMoney() {
  uint32_t money = cocos2d::UserDefault::getInstance()->getIntegerForKey("PLAYER_MONEY");
  cocos2d::UserDefault::getInstance()->flush();
  return money;
}