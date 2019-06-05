#include "ComputerAi.h"

ComputerAi::ComputerAi()
{
}

ComputerAi::~ComputerAi()
{
}

void ComputerAi::enemyMove(float dt)
{
	//移动导弹
	for (auto it = _missiles.begin(); it != _missiles.end();)
	{
		Missilie* missile = *it;
		Rect rc = missile->getBoundingBox();

		Enemy* enemy = missile->_target;

		Vec2 veMissile = missile->getPosition();
		Vec2 veEnemy = enemy->getPosition();
		Vec2 delta = veEnemy - veMissile;

		float angle = delta.getAngle();   //获取两点之间的角度
		float y = sinf(angle) * 5;
		float x = cosf(angle) * 5;

		Util::move(missile, Vec2(x, y));
		missile->setRotation(90 - CC_RADIANS_TO_DEGREES(angle));

		if (rc.intersectsRect(enemy->getBoundingBox()))
		{
			if (!enemy->isDead())
			{
				enemy->hurt(1);
				if (enemy->isDead())
				{
					enemy->bomb();
					this->_enemys.eraseObject(enemy);
				}
			}
			missile->removeFromParent();
			it = _missiles.erase(it);
		}
		else
		{
			it++;
		}
	}

	//遍历容器
	for (auto it = _enemys.begin(); it!= _enemys.end();)
	{
		Enemy* enemy = *it;
		Util::moveY(enemy, -enemy->getEnemySpeed());

		if (enemy->isOutOfWindow())
		{
			it = _enemys.erase(it);
			enemy->removeFromParent();
		}
		else
		{
			it++;
		}
	}

	//移动道具
	for (auto it = _items.begin(); it != _items.end();)
	{
		UnitItem* item = *it;
		item->move();

		if (item->isOutOfWindow())
		{
			it = _items.erase(it);
			item->removeFromParent();
		}
		else
		{
			it++;
		}
	}
}

void ComputerAi::fireMissile(Sprite * hero)
{
	if (this->_enemys.size() == 0)
		return;

	//创建导弹
	Missilie* miss = Missilie::create(this->_enemys.at(0));
	addChild(miss);
	miss->setPosition(hero->getPosition());
	Util::moveY(miss, hero->getBoundingBox().size.height / 2);
	_missiles.pushBack(miss);
}

bool ComputerAi::init()
{
	if (!Layer::init())
		return false;

	//创建敌机
	schedule(schedule_selector(ComputerAi::createBigEnemy), INTERVAL_BIG);
	schedule(schedule_selector(ComputerAi::createMidEnemy), INTERVAL_MID);
	schedule(schedule_selector(ComputerAi::createSmlEnemy), INTERVAL_SML);
	
	//敌机移动
	schedule(schedule_selector(ComputerAi::enemyMove));

	return true;
}

void ComputerAi::createBigEnemy(float  dt)
{
	this->createEnemy(Enemy::BIG);
}
void ComputerAi::createMidEnemy(float  dt)
{
	this->createEnemy(Enemy::MID);
}
void ComputerAi::createSmlEnemy(float  dt)
{
	this->createEnemy(Enemy::SML);
}

void ComputerAi::createEnemy(Enemy::Type type)
{
	Enemy* enemy = Enemy::create(type);
	this->addChild(enemy, 0);

	this->setRandPos(enemy);
	_enemys.pushBack(enemy);
}

void ComputerAi::createItemRand(float rate)
{
	//随机出现不同道具
	if (CCRANDOM_0_1() < rate)
	{
		UnitItem::Type type;
		if (CCRANDOM_0_1() < 0.5)
		{
			type = UnitItem::BOMD;
		}
		else
		{
			type = UnitItem::BULLET;
		}

		UnitItem* item = UnitItem::create(type);
		this->addChild(item);
		_items.pushBack(item);

		this->setRandPos(item);
		item->_center = item->getPositionX();
	}
}

void ComputerAi::setRandPos(Sprite * sp)
{
	Rect rc = sp->getBoundingBox();
	int x = CCRANDOM_0_1()* (winSize.width - rc.size.width) + rc.size.width / 2;
	int y = winSize.height + rc.size.height / 2;

	sp->setPosition(Vec2(x, y));
}
