#ifndef _LAYER_SCORE_H_
#define _LAYER_SCORE_H_

#include "BackGround.h"

class LayerScore : public Layer
{
public:
	LayerScore();
	~LayerScore();
	static LayerScore* create(int score);

	virtual bool init()override;

	int _score;
};

#endif
