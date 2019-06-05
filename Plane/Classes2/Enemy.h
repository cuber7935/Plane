#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Util.h"

//敌机类
class Enemy : public Sprite
{
public:
	Enemy();
	~Enemy();
	//敌机的种类
	enum Type { BIG, MID, SML, COUNT };

	//获取敌机的速度
	int getEnemySpeed()const;
	//判断敌机是否出窗口
	bool isOutOfWindow();
	//敌机受伤害
	void hurt(int);
	//判断敌机是否死亡
	bool isDead();
	//敌机爆炸
	void bomb();
	//获取血量
	int getEnemyBlood()const;

	//敌机值分数
	int score();

	//获取类型
	Type type()const;

	static Enemy* create(Type type);
	
	virtual bool init()override;

private:
	//播放动画
	void playDeadAnimation(float dt);

	Type _type;			//敌机类型
	int  _speed;		//敌机速度
	int  _hp;           //敌机血量
	int  _deadPictureIdx;  //敌机死亡时图片索引
};

#endif
