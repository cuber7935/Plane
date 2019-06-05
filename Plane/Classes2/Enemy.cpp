#include "Enemy.h"


Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

int Enemy::getEnemySpeed() const
{
	return _speed;
}

bool Enemy::isOutOfWindow()
{
	Rect rc = this->getBoundingBox();
	return rc.getMaxY() < 0;
}

int Enemy::score()
{
	static int s[] = { 1000, 300, 100 };

	return s[_type];
}

Enemy::Type Enemy::type() const
{
	return _type;
}

Enemy * Enemy::create(Type type)
{
	Enemy* enemy = new Enemy;
	enemy->_type = type;
	enemy->init();
	enemy->autorelease();
	return enemy;
}

bool Enemy::init()
{
	static const char* fileEnemy[] = { "plane/Enemy3.png", "plane/Enemy2.png", "plane/Enemy1.png" };
	if (!Sprite::initWithFile(fileEnemy[_type]))
		return false;

	static int speed[] = { 1, 3, 5 };
	_speed = speed[_type];

	static int hp[] = {100, 30, 10};
	_hp = hp[_type];

	return true;
}

//敌机受伤害
void Enemy::hurt(int hp)
{
	_hp -= hp;
}
//判断敌机是否死亡
bool Enemy::isDead()
{
	return _hp <= 0;
}
//敌机爆炸
void Enemy::bomb()
{
	//启动定时器播放动画
	schedule(schedule_selector(Enemy::playDeadAnimation), 0.08f);
	this->_deadPictureIdx = 1;
	//播放声音

}

int Enemy::getEnemyBlood() const
{
	return _hp;
}

void Enemy::playDeadAnimation(float dt)
{
	char buf[128] = {0};
	const char* format = "plane/enemy%d_down%d.png";   // ?????????
	sprintf(buf, format, 3 - _type, _deadPictureIdx++);

	if (FileUtils::getInstance()->isFileExist(buf))
	{
		setTexture(buf);
	}
	else
	{
		this->removeFromParent();
	}
}