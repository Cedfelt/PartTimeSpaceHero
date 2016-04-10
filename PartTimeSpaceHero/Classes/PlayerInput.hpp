//
//  PlayerInput.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#ifndef PlayerInput_hpp
#define PlayerInput_hpp

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class PlayerInput : public Node {
public:
    void setup_controlls();
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(PlayerInput);
private:
    virtual void onTouchBegan(const std::vector<Touch*>&, Event*);
    virtual void onTouchEnded(const std::vector<Touch*>&, Event*);
    virtual void onTouchMoved(const std::vector<Touch*>&, Event*);
    virtual void onTouchCancelled(const std::vector<Touch*>&, Event*);
};

#endif /* PlayerInput_hpp */
