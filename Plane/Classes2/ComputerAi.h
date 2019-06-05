#ifndef _COMPUTER_AI_H_
#define _COMPUTER_AI_H_

#include "Missilie.h"
#include "UnitItem.h"
#define INTERVAL_SML 1
#define INTERVAL_MID 3
#define INTERVAL_BIG 10

/*	
	1.产生敌机
	2.移动敌机，判断是否飞出窗口外（回收敌机）
	3.将敌机放入容器，方便碰撞检测
*/
class ComputerAi : public Layer
{
public:
	ComputerAi();
	~ComputerAi();

	//创建敌机
	void createBigEnemy(float  dt);
	void createMidEnemy(float  dt);
	void createSmlEnemy(float  dt);
	void createEnemy(Enemy::Type type);

	//随机创建道具
	void createItemRand(float rate);
	//设置随机位置
	void setRandPos(Sprite* sp);

	//敌机移动
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