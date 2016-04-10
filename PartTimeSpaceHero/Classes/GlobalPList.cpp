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

