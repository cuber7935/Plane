#include "UnitItem.h"


UnitItem::UnitItem()
{
}

UnitItem::~UnitItem()
{
}

UnitItem * UnitItem::create(Type type)
{
	UnitItem* item = new UnitItem;
	item->_type = type;
	item->init();
	item->autorelease();
	return item;
}

void UnitItem::move()
{
	Util::moveY(this, -_speed);
	if (_bRight)
	{
		Util::moveX(this, 0.5f);
		if (this->getPositionX() > (_center + _swing))
			_bRight = false;
	}
	else
	{
		Util::moveX(this, -0.5f);
		if (this->getPositionX() < (_center - _swing))
			_bRight = true;
	}
}

bool UnitItem::init()
{
	const char* item[] = { "plane/sprite-0-2,png","plane/sprite-1-2.png" };
		//"boom.png"
	if (!Sprite::initWithFile(item[_type]))
		return false;
	
	if(_type == UnitItem::BOMD)
		_speed = ITEM_SPEED_BOMD;
	else
		_speed = ITEM_SPEED_BUTTET;
	
	_swing = 20;
	_bRight = true;
	
	return true;
}

bool UnitItem::isOutOfWindow()
{
	Rect rc = this->getBoundingBox();
	return rc.getMaxY() < 0;
}