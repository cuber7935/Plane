#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "Enemy.h"

class Missilie : public Sprite
{
public:
	Missilie();
	~Missilie();

	static Missilie* create(Enemy* target);

	virtual bool init()override;

	Enemy* _target;
};

#endif