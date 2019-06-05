#ifndef _UNITITEM_H_
#define _UNITITEM_H_

#include "Util.h"
#define ITEM_SPEED_BOMD 2
#define ITEM_SPEED_BUTTET 1

//道具类
class UnitItem : public Sprite
{
public:
	UnitItem();
	~UnitItem();

	enum Type{ BOMD, BULLET, COUNT};

	static UnitItem* create(Type type);

	void move();

	bool isOutOfWindow();

	virtual bool init()override;

	Type _type;
	int _speed;

	bool _bRight;   //摆动方向
	int _swing;    //偏移值
	float _center; //中心点
};

#endif