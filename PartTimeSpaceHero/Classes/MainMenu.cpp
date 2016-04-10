//
//  MainMenu.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "MainMenu.hpp"

MainMenu::MainMenu() {
    cocos2d::Director::getInstance()->getTextureCache()->removeAllTextures();
    ///////////////////////////////
    // SCHEDULE UPDATE FUNCTION
    this->schedule(schedule_selector(SpaceGameLayer::super_update));
}