#include "AppDelegate.h"
#include "MainMenu.hpp"
#include "GlobalPList.hpp"
#include "SimpleAudioEngine.h"


USING_NS_CC;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
  
    // initialize director
    const uint32_t scale = 2;
  
#ifdef IPAD_AIR
  uint32_t res_x = 2048;
  uint32_t res_y = 1536;
#else //if IPHONE5
  uint32_t res_x = 1136;
  uint32_t res_y = 640;
#endif
  
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
        glview = GLViewImpl::createWithRect("SpaceGame", Rect(0, 0, res_x , res_y ));
        director->setOpenGLView(glview);
    }
    
    setScaleFactor(scale);
    
    director->getOpenGLView()->setDesignResolutionSize(res_x, res_y, ResolutionPolicy::SHOW_ALL);
    
    director->setProjection(Director::Projection::_2D);
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto scene = MainMenu::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
     CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
