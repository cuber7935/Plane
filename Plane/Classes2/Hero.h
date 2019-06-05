#ifndef _HERO_H_
#define _HERO_H_

#include "Util.h"

//利用纯虚函数解决 头文件重复包含陷入死循环
class GameDelegate
{
public:
	virtual void gameOver() = 0;
};

//也可以使用std::bind来解决上面那个问题

class Hero : public Sprite
{
public:
	Hero();
	~Hero();

	void changeTexture(float dt);
	
	//受伤害
	void hurt(int);
	//是否死亡
	bool isDead();
	//播放动画
	void bomb();

	void playDeadAnimation(float dt);

	virtual bool init()override;
	CREATE_FUNC(Hero);

	bool TouchBegan(Touch* touch, Event* ev);
	void TouchMoved(Touch* touch, Event* ev);

	//std::function<void()> _gameOver;
	GameDelegate* _gameOver;
private:
	int _hp;   //英雄血量
	int _deadPictureIdx;
};

#endif
