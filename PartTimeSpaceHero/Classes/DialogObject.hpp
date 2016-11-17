//
//  DialogObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 20/07/16.
//
//

#pragma once
#include "cocos2d.h"
#include "SoundFx.hpp"

using namespace cocos2d;
class DialogObject : public Node {
public:
  virtual bool init();
  CREATE_FUNC(DialogObject);
  SoundFx* pling;
  Label* dialogLabel;
  void playDialog();
  void update(const float delta);
  void updateLineByLine(const float delta);
  std::vector<std::string> dialogText;
  std::vector<float> dialogTime;
  float cnt;
  void addLine(const std::string line,const float time);
  bool dialogShowed;
  bool started;
  bool lineShowed = true;
  std::string nextLine;
  float dialog_pause_timer;
  std::string outputLine;
  float printRate = 0.1f;
  int inx = 0;
  float holdCnt = 0;
  float holdTime = 3;
  bool endLevelWhenDone;
  int presentation;
  
  typedef enum tDialogType{
    E_CHAR_BY_CHAR,
    E_LINE_BY_LINE
  }dialogType;
private:
};
