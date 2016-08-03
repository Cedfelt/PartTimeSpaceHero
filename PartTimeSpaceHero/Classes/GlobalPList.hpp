//
//  GlobalPList.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#ifndef GlobalPList_hpp
#define GlobalPList_hpp

#include <stdio.h>
#include "cocos2d.h"


bool setScaleFactor(const size_t scale);
size_t getScaleFactor();

bool setMapUrl(const std::string level);
std::string getMapUrl();

void setDebuggDraw(bool debugDraw);
bool getDebuggDraw();

void setNewGame(bool first);
bool getNewGame();

void setPlayerGear(uint32_t gear_mask);
uint32_t getPayerGear();

void setPlayerMoney(uint32_t money);
uint32_t getPayerMoney();

#endif /* GlobalPList_hpp */
