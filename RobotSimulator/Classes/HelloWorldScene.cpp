#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <fstream>
#include <iostream>
#include <windows.h>  
#include  <direct.h>  
#include <string.h>
#include  <stdio.h>  
#include <vector>
#include <list>   
using namespace std;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
//////////////////////////////
// 1. super init first
if (!Scene::init())
{
	return false;
}

auto visibleSize = Director::getInstance()->getVisibleSize();
Vec2 origin = Director::getInstance()->getVisibleOrigin();

/////////////////////////////
// 2. add a menu item with "X" image, which is clicked to quit the program
//    you may modify it.

// add a "close" icon to exit the progress. it's an autorelease object
auto closeItem = MenuItemImage::create(
	"CloseNormal.png",
	"CloseSelected.png",
	CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

if (closeItem == nullptr ||
	closeItem->getContentSize().width <= 0 ||
	closeItem->getContentSize().height <= 0)
{
	problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
}
else
{
	float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
	float y = origin.y + closeItem->getContentSize().height / 2;
	closeItem->setPosition(Vec2(x, y));
}

// create menu, it's an autorelease object
auto menu = Menu::create(closeItem, NULL);
menu->setPosition(Vec2::ZERO);
this->addChild(menu, 1);

/////////////////////////////
// 3. add your codes below...

//画背景
auto red = LayerColor::create(Color4B(242, 239, 230, 255), visibleSize.width, visibleSize.height);
this->addChild(red, 0);
//划线
auto s = Director::getInstance()->getWinSize();
auto draw = DrawNode::create();
this->addChild(draw, 0);
int w, h;

//通过(FileUtils)这个工具获取和写入文件--读map文件
auto fu = FileUtils::getInstance();
//读取文件,将读取到的数据传给d
Data d = fu->getDataFromFile(fu->fullPathForFilename("../../../map.txt"));
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
w = atoi(v[1].c_str());
h = atoi(v[0].c_str());
for (int i = 0; i <= w; i++){
	draw->drawSegment(Vec2(s.width*i / w, 0), Vec2(s.width*i / w, s.height), 1, Color4F(Color4B(59, 32, 12, 255)));
}
for (int i = 0; i <= h; i++){
	draw->drawSegment(Vec2(0, s.height*i / h), Vec2(s.width, s.height*i / h), 1, Color4F(Color4B(59, 32, 12, 255)));
}
//画障碍
for(int i = 1; i <= h; i++){
	string str = results[i].c_str();
	string c = ",";
	vector<string> v;
	while (str.find(c) != -1)
	{
		v.push_back(str.substr(0, str.find(c)));
		str = str.substr(str.find(c) + 1, str.size());
	}
	v.push_back(str);
	log("%s", ".................");
	for (int j = 0; j < w; j++){
		log("%i", atoi(v[j].c_str()));
		if (atoi(v[j].c_str()) == 1){
			Vec2 points[] = { Vec2(s.width*(j) / w, s.height*(i - 1) / h), Vec2(s.width*(j) / w, s.height*i / h),
				Vec2(s.width*(j+1) / w, s.height*i  / h), Vec2(s.width*(j + 1) / w, s.height*(i-1) / h) };
			draw->drawPolygon(points, sizeof(points) / sizeof(points[0]), Color4F(Color4B(222, 129, 0, 255)), 1, Color4F(Color4B(59, 32, 12, 255)));
			//ccDrawSolidRect(Vec2(s.width*j / w, s.height*(i-1) / w), Vec2(s.width*(j+1) / w, s.height*i/w), Color4F(Color4B(59, 32, 12, 255)));
		}
	}
}

//读取robot
Data robot_d = fu->getDataFromFile(fu->fullPathForFilename("../../../robot.txt"));
unsigned char* robot_tmp = robot_d.getBytes();
int robot_number = robot_d.getSize();
vector<string> robots;
string robot_temp = "";
for (int i = 0; i < robot_number; ++i){
	char mid = (*robot_tmp);
	if (mid == '0' || mid == '1' || mid == '2' || mid == '3' || mid == '4' || mid == '5' || mid == '6' || mid == '7' || mid == '8' || mid == '9' || mid == ','){
		robot_temp = robot_temp + mid;
	}
	else{
		if (robot_temp.size() > 0){
			robots.push_back(robot_temp);
			robot_temp = "";
		}
	}
	++robot_tmp;
}
robots.push_back(robot_temp);
//画robot
float r = s.width /(2* w);
float pic = 256.0;
int robotNumber = atoi(robots[0].c_str());
Vector<Sprite*> robotSprites;
for (int i = 1; i <= robotNumber; i++){
	string robotStr = robots[i].c_str();
	string r_c = ",";
	vector<string> r_v;
	while (robotStr.find(r_c) != -1)
	{
		r_v.push_back(robotStr.substr(0, robotStr.find(r_c)));
		robotStr = robotStr.substr(robotStr.find(r_c) + 1, robotStr.size());
	}
	r_v.push_back(robotStr);
	auto mySprite = Sprite::create("robot.png");
	mySprite->setTag(i);
	mySprite->setScale(3*r/pic);
	mySprite->setPosition(Vec2(s.width*(atoi(r_v[2].c_str())) / w-r, s.height*(atoi(r_v[1].c_str())) / h-r));
	this->addChild(mySprite);
	robotSprites.pushBack(mySprite);
	log("%s", ".................");
}

//开启robot刷新线程
std::thread t1(&HelloWorld::readingThread, this, w, h,  s.width,s.height);
//把线程和主线程分离开
t1.detach();
return true;
}

void HelloWorld::readingThread(int w, int h, int s_width, int s_height)
{
	//通过(FileUtils)这个工具获取和写入文件--读map文件
	auto fu = FileUtils::getInstance();
	this->getChildByTag(1);
	for (int i = 0; i < 1000; i++){
		Sleep(1000);
		//读取robot
		Data robot_d = fu->getDataFromFile(fu->fullPathForFilename("../../../TestRobot/Robot_Current_Position.txt"));
		unsigned char* robot_tmp = robot_d.getBytes();
		int robot_number = robot_d.getSize();
		vector<string> robots;
		string robot_temp = "";
		for (int i = 0; i < robot_number; ++i){
			char mid = (*robot_tmp);
			if (mid == '0' || mid == '1' || mid == '2' || mid == '3' || mid == '4' || mid == '5' || mid == '6' || mid == '7' || mid == '8' || mid == '9' || mid == ','){
				robot_temp = robot_temp + mid;
			}
			else{
				if (robot_temp.size() > 0){
					robots.push_back(robot_temp);
					robot_temp = "";
				}
			}
			++robot_tmp;
		}
		robots.push_back(robot_temp);
		//画robot
		float r = s_width / (2 * w);
		float pic = 256.0;
		int robotNumber = atoi(robots[0].c_str());
		Vector<Sprite*> robotSprites;
		for (int i = 1; i <= robotNumber; i++){
			string robotStr = robots[i].c_str();
			string r_c = ",";
			vector<string> r_v;
			while (robotStr.find(r_c) != -1)
			{
				r_v.push_back(robotStr.substr(0, robotStr.find(r_c)));
				robotStr = robotStr.substr(robotStr.find(r_c) + 1, robotStr.size());
			}
			r_v.push_back(robotStr);
			auto moveTo = MoveTo::create(1, Vec2(s_width*(atoi(r_v[2].c_str())) / w - r, s_height*(atoi(r_v[1].c_str())) / h - r));
			this->getChildByTag(i)->runAction(moveTo);
		}
		
	}
	
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
