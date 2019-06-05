#ifndef _UTIL_H_
#define _UTIL_H_

#include "cocos2d.h"
USING_NS_CC;

#define winSize Director::getInstance()->getWinSize()

class Util
{
public:
	Util();
	~Util();
	//创建精灵
	static Sprite* addSprite(const char* fileName, Node* parent, Vec2 pos);
	//创建场景
	static Scene* createScene(Layer* layer);
	//移动
	static void move(Node* node, Vec2 delta);
	static void moveX(Node* node, float deltaX);
	static void moveY(Node* node, float deltaY);

	//添加触摸
	static void addTouch(Node* node,
		EventListenerTouchOneByOne::ccTouchBeganCallback began,
		EventListenerTouchOneByOne::ccTouchCallback ended = nullptr,
		EventListenerTouchOneByOne::ccTouchCallback moved = nullptr,
		EventListenerTouchOneByOne::ccTouchCallback cancelled = nullptr,
		bool bSelect = false);

};

#endif