#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Util.h"

//�л���
class Enemy : public Sprite
{
public:
	Enemy();
	~Enemy();
	//�л�������
	enum Type { BIG, MID, SML, COUNT };

	//��ȡ�л����ٶ�
	int getEnemySpeed()const;
	//�жϵл��Ƿ������
	bool isOutOfWindow();
	//�л����˺�
	void hurt(int);
	//�жϵл��Ƿ�����
	bool isDead();
	//�л���ը
	void bomb();
	//��ȡѪ��
	int getEnemyBlood()const;

	//�л�ֵ����
	int score();

	//��ȡ����
	Type type()const;

	static Enemy* create(Type type);
	
	virtual bool init()override;

private:
	//���Ŷ���
	void playDeadAnimation(float dt);

	Type _type;			//�л�����
	int  _speed;		//�л��ٶ�
	int  _hp;           //�л�Ѫ��
	int  _deadPictureIdx;  //�л�����ʱͼƬ����
};

#endif
