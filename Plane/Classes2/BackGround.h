#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "Util.h"

class BackGround : public Layer
{
public:
	BackGround();
	~BackGround();

	virtual void update(float dt)override;

	static BackGround* create(bool bScorll); 
	
	bool init(bool bScorll = true);

private:
	Sprite* _spBgA;
	Sprite* _spBgB;
};

#endif