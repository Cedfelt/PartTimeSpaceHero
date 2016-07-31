//
//  DialogObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 20/07/16.
//
//

#include "DialogObject.hpp"
#include "GlobalPList.hpp"
bool DialogObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!Node::init())
  {
    return false;
  }
  
  dialogShowed = false;
  
  started = false;
  
  Size visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  const size_t scale = getScaleFactor();
  dialogLabel = Label::createWithTTF("", "fonts/PressStart2P.ttf", 15*scale);
  dialogLabel->setPosition(Vec2(visibleSize.width / 2 - scale * 20,1.5f * 15*scale));
  cnt = 0;
  addChild(dialogLabel);
  setAnchorPoint(Vec2(0.5f,0.0));
  dialogLabel->setAnchorPoint(Vec2(0.5, 0));
  endLevelWhenDone = false;
  presentation = E_CHAR_BY_CHAR;
  holdCnt = -1;
  return true;
  
}


void DialogObject::update(const float delta) {
  if(holdCnt>0){
    holdCnt-=delta;
    return;
  }
  
  if(dialogText.size()<=0&&lineShowed){
    dialogShowed = true;
    if(endLevelWhenDone){
      
    }
  }
  else if(lineShowed){
    lineShowed = false;
    nextLine = dialogText.at(0);
    dialogText.erase(dialogText.begin());
    inx = 0;
    const float diaTime = dialogTime.at(0);
    dialogTime.erase(dialogTime.begin());
    cnt = 0;
  }
  else if(cnt <=0){
    inx++;
    cnt = printRate;
    if(inx<=nextLine.size()){
      outputLine = nextLine.substr(0,inx);
      cnt = printRate;
      dialogLabel->setString(outputLine);
      
    }
    else{
      lineShowed = true;
      holdCnt = holdTime;
    }
    
  }
  
  cnt-=delta;
}
 

void DialogObject::updateLineByLine(const float delta){
  if(dialogText.size()>0 && cnt <=0){
    const std::string nextLine = dialogText.at(0);
    dialogText.erase(dialogText.begin());
    dialogLabel->setString(nextLine);
    
    const float diaTime = dialogTime.at(0);
    dialogTime.erase(dialogTime.begin());
    cnt = diaTime;
  }
  else if(dialogText.size()<=0 && cnt <=0){
    dialogShowed = true;
  }
  cnt-=delta;
  

}

void DialogObject::addLine(const std::string line,const float time){
  dialogText.push_back(line);
  dialogTime.push_back(time);
}

void DialogObject::playDialog(){
  if(!started){
    started = true;
    if(presentation == E_CHAR_BY_CHAR){
      this->schedule(schedule_selector(DialogObject::update));
    }
    if(presentation == E_LINE_BY_LINE){
      this->schedule(schedule_selector(DialogObject::updateLineByLine));
    }
  }
}
