#include "AppDelegate.h"
#include "TitleScreen.hpp"
#include "GlobalPList.hpp"
#include "DB32.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

//#define IPAD_RETINA

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
    setup_colorcollection();



  
    auto director = Director::getInstance();
#ifdef WIN32
  const uint32_t res_x = 1136;
  const uint32_t res_y = 640;
#else //if IPHONE5
  const uint32_t res_x = director->getWinSizeInPixels().width;
  const uint32_t res_y = director->getWinSizeInPixels().height;
#endif
    auto glview = director->getOpenGLView();
    if (!glview) {
        glview = GLViewImpl::createWithRect("SpaceGame", Rect(0, 0, res_x , res_y ));
        director->setOpenGLView(glview);
    }
    
    setScaleFactor(scale);
    
    director->getOpenGLView()->setDesignResolutionSize(res_x, res_y, ResolutionPolicy::SHOW_ALL);
    
    director->setProjection(Director::Projection::_2D);
    
    // turn on display FPS
    director->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    FileUtils::getInstance()->addSearchPath("res");
    FileUtils::getInstance()->addSearchPath("res/sound/music");
    FileUtils::getInstance()->addSearchPath("res/sound/sfx");
  FileUtils::getInstance()->addSearchPath("res/graphics/map_files");
  FileUtils::getInstance()->addSearchPath("res/graphics/sprites");
  FileUtils::getInstance()->addSearchPath("res/graphics/gui");
  FileUtils::getInstance()->addSearchPath("Classes/gameobjects");
  
  
  //auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
  //audio->stopBackgroundMusic();
  //audio->playBackgroundMusic("title_theme.mp3", true);
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("title_theme.mp3");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("78.mp3");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("theme.mp3");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("adventure.mp3");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("alone in space2.mp3");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Corp_Waltz.mp3");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Dawn.aif");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("echo.mp3");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Hope.mp3");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("on_a_mission.mp3");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Space_Adventure.mp3");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("finished.mp3");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("death.mp3");
  //CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("too_quiet_in_here.aif");
  

    // create a scene. it's an autorelease object
    auto scene = TitleScreen::createScene();

    // run
    director->runWithScene(scene);
  
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    //CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
     //CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
