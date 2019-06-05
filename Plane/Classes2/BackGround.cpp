#include "BackGround.h"


BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

bool BackGround::init(bool bScorll)
{
	if (!Layer::init())
		return false;

	_spBgA = Util::addSprite("plane/background.png", this, Vec2(winSize.width / 2, winSize.height / 2));
	if (bScorll)
	{
		_spBgB = Util::addSprite("plane/background.png", this, Vec2(winSize.width / 2, winSize.height / 2 + winSize.height));
		//ʹ�ü�ʱ�� ʹ����ͼ�ƶ�����
		scheduleUpdate();
	}

	return true;
}

void BackGround::update(float dt)
{
	float off = 300 * dt;
	Util::moveY(_spBgA, -off);
	Util::moveY(_spBgB, -off);

	if (_spBgA->getPositionY() < -winSize.height / 2)
	{
		//�ص�����
		_spBgA->setPositionY(_spBgB->getPositionY() + winSize.height);
	}
	if (_spBgB->getPositionY() < -winSize.height / 2)
	{
		//�ص�����
		_spBgB->setPositionY(_spBgA->getPositionY() + winSize.height);
	}
}

BackGround * BackGround::create(bool bScorll)
{
	BackGround* bg = new BackGround;
	bg->init(bScorll);
	bg->autorelease();
	return bg;
}
