#include "Missilie.h"


Missilie::Missilie()
{
}

Missilie::~Missilie()
{
	_target->release();
}

Missilie * Missilie::create(Enemy * target)
{
	Missilie* missilie = new Missilie;
	target->retain();
	missilie->_target = target;
	missilie->init();
	missilie->autorelease();
	return missilie;
}

bool Missilie::init()
{
	if (!Sprite::initWithFile("plane/hole_effect.png"))
		return false;

	return true;
}
