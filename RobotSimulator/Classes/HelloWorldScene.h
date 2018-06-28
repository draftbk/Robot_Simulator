#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	//Ïß³Ì
	void HelloWorld::readingThread(int w, int h, int s_width, int s_height, int SPEED, int PERIOD, int PERIODNUMBER, int OPENBULLETSCREEN, 
		int BulletCOLOR_1, int BulletCOLOR_2, int BulletCOLOR_3, int BulletPosition_1, int BulletPosition_2);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void update(float) override;
};

#endif // __HELLOWORLD_SCENE_H__
