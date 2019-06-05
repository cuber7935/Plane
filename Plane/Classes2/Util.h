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
	//��������
	static Sprite* addSprite(const char* fileName, Node* parent, Vec2 pos);
	//��������
	static Scene* createScene(Layer* layer);
	//�ƶ�
	static void move(Node* node, Vec2 delta);
	static void moveX(Node* node, float deltaX);
	static void moveY(Node* node, float deltaY);

	//��Ӵ���
	static void addTouch(Node* node,
		EventListenerTouchOneByOne::ccTouchBeganCallback began,
		EventListenerTouchOneByOne::ccTouchCallback ended = nullptr,
		EventListenerTouchOneByOne::ccTouchCallback moved = nullptr,
		EventListenerTouchOneByOne::ccTouchCallback cancelled = nullptr,
		bool bSelect = false);

};

#endif