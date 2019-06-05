#include "Hero.h"


Hero::Hero()
{
}

Hero::~Hero()
{
}

//ʵ�ֶ�̬
void Hero::changeTexture(float dt)
{
	if (isDead())
		return;

	static bool bChange = false;
	bChange = !bChange;
	if (bChange)
	{
		this->setTexture("plane/Player2.png");
	}
	else
	{
		this->setTexture("plane/Player1.png");
	}
}

void Hero::hurt(int hp)
{
	_hp -= hp;
}

bool Hero::isDead()
{
	return _hp <= 0;
}

void Hero::bomb()
{
	//�ص��ɻ�����Ч��
	//unschedule(schedule_selector(Hero::playDeadAnimation));
	
	//������ʱ�����Ŷ���
	schedule(schedule_selector(Hero::playDeadAnimation), 0.08f);
	this->_deadPictureIdx = 1;
	//��������
}

void Hero::playDeadAnimation(float dt)
{
	char buf[128] = { 0 };
	const char* format = "plane/hero%d.png";   //?????????
	sprintf(buf, format, _deadPictureIdx++);

	if (FileUtils::getInstance()->isFileExist(buf))
	{
		setTexture(buf);
	}
	else
	{
		//_gameOver();
		_gameOver->gameOver();
	}
}

bool Hero::init()
{
	if(!Sprite::initWithFile("plane/Player1.png"))
		return false;

	//���Ӽ�ʱ��
	schedule(schedule_selector(Hero::changeTexture), 0.08f);

	//��Ӵ���
	Util::addTouch(this, CC_CALLBACK_2(Hero::TouchBegan, this), nullptr, CC_CALLBACK_2(Hero::TouchMoved, this), nullptr, false);

	_hp = 100;

	return true;
}

bool Hero::TouchBegan(Touch * touch, Event * ev)
{
	return true;
}

void Hero::TouchMoved(Touch * touch, Event * ev)
{
	//���ң����¶�����
	Util::move(ev->getCurrentTarget(), touch->getDelta());
	//ֻ�������ƶ�
	//Util::moveX(ev->getCurrentTarget(), touch->getDelta().x);
}

