#ifndef _COMPUTER_AI_H_
#define _COMPUTER_AI_H_

#include "Missilie.h"
#include "UnitItem.h"
#define INTERVAL_SML 1
#define INTERVAL_MID 3
#define INTERVAL_BIG 10

/*	
	1.�����л�
	2.�ƶ��л����ж��Ƿ�ɳ������⣨���յл���
	3.���л�����������������ײ���
*/
class ComputerAi : public Layer
{
public:
	ComputerAi();
	~ComputerAi();

	//�����л�
	void createBigEnemy(float  dt);
	void createMidEnemy(float  dt);
	void createSmlEnemy(float  dt);
	void createEnemy(Enemy::Type type);

	//�����������
	void createItemRand(float rate);
	//�������λ��
	void setRandPos(Sprite* sp);

	//�л��ƶ�
	void enemyMove(float dt); 
	
	void fireMissile(Sprite* hero);


	virtual bool init()override;

	CREATE_FUNC(ComputerAi);
public:
	Vector<Enemy*> _enemys;
	Vector<UnitItem*> _items;
	Vector<Missilie*> _missiles;
};

#endif