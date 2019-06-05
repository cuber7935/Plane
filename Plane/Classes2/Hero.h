#ifndef _HERO_H_
#define _HERO_H_

#include "Util.h"

//���ô��麯����� ͷ�ļ��ظ�����������ѭ��
class GameDelegate
{
public:
	virtual void gameOver() = 0;
};

//Ҳ����ʹ��std::bind����������Ǹ�����

class Hero : public Sprite
{
public:
	Hero();
	~Hero();

	void changeTexture(float dt);
	
	//���˺�
	void hurt(int);
	//�Ƿ�����
	bool isDead();
	//���Ŷ���
	void bomb();

	void playDeadAnimation(float dt);

	virtual bool init()override;
	CREATE_FUNC(Hero);

	bool TouchBegan(Touch* touch, Event* ev);
	void TouchMoved(Touch* touch, Event* ev);

	//std::function<void()> _gameOver;
	GameDelegate* _gameOver;
private:
	int _hp;   //Ӣ��Ѫ��
	int _deadPictureIdx;
};

#endif
