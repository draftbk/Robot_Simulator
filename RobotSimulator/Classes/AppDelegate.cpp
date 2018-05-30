#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include <fstream>
#include <iostream>
#include <windows.h>  
#include  <direct.h>  
#include <string.h>
#include  <stdio.h>  
#include <vector>
#include <list>   
using namespace std;


// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

//设置窗口大小
static cocos2d::Size designResolutionSize = cocos2d::Size(600, 788);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
	//读取config-更改界面大小
	//通过(FileUtils)这个工具获取和写入文件
	auto fu = FileUtils::getInstance();
	Data config_d = fu->getDataFromFile(fu->fullPathForFilename("../TestRobot/Config.txt"));
	unsigned char* config_tmp = config_d.getBytes();
	int config_number = config_d.getSize();
	vector<string> configs;
	string config_temp = "";
	for (int i = 0; i < config_number; ++i){
		char mid = (*config_tmp);
		if (mid == '0' || mid == '1' || mid == '2' || mid == '3' || mid == '4' || mid == '5' || mid == '6' || mid == '7' || mid == '8' || mid == '9' || mid == ','){
			config_temp = config_temp + mid;
		}
		else{
			if (config_temp.size() > 0){
				configs.push_back(config_temp);
				config_temp = "";
			}
		}
		++config_tmp;
	}
	configs.push_back(config_temp);
	int	DESIGNRESOLUTIONSIZE = atoi(configs[5].c_str());


	//根据map比例来决定大小
	Data d = fu->getDataFromFile(fu->fullPathForFilename("../TestRobot/InitMap.txt"));
	unsigned char* tmp = d.getBytes();
	int number = d.getSize();
	vector<string> results;
	string temp = "";
	for (int i = 0; i < number; ++i){
		char mid = (*tmp);
		if (mid == '0' || mid == '1' || mid == '2' || mid == '3' || mid == '4' || mid == '5' || mid == '6' || mid == '7' || mid == '8' || mid == '9' || mid == ','){
			temp = temp + mid;
		}
		else{
			if (temp.size() > 0){
				results.push_back(temp);
				temp = "";
			}
		}
		++tmp;
	}
	results.push_back(temp);
	//读取行列
	string str = results[0].c_str();
	string c = ",";
	vector<string> v;

	while (str.find(c) != -1)
	{
		v.push_back(str.substr(0, str.find(c)));
		str = str.substr(str.find(c) + 1, str.size());
	}
	v.push_back(str);
	//画栅格
	int w = atoi(v[1].c_str());
	int h = atoi(v[0].c_str());
	designResolutionSize = cocos2d::Size(DESIGNRESOLUTIONSIZE, DESIGNRESOLUTIONSIZE*h*1.0/w);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("RobotSimulator", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("RobotSimulator");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
