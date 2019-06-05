#ifndef _UNITITEM_H_
#define _UNITITEM_H_

#include "Util.h"
#define ITEM_SPEED_BOMD 2
#define ITEM_SPEED_BUTTET 1

//������
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

	bool _bRight;   //�ڶ�����
	int _swing;    //ƫ��ֵ
	float _center; //���ĵ�
};

#endif