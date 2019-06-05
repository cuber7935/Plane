#include "LayerScore.h"

LayerScore::LayerScore()
{
}


LayerScore::~LayerScore()
{
}

LayerScore* LayerScore::create(int score)
{
	LayerScore* ps = new LayerScore;
	ps->_score = score;
	ps->init();
	ps->autorelease();	
	return ps;
}

bool LayerScore::init()
{
	if(!Layer::init())
		return false;

	BackGround* bg = BackGround::create(false);
	this->addChild(bg);

	char buf[128] = {0};
	sprintf(buf, "your are score: %d", _score);

	Label* label = Label::createWithTTF(buf, "fonts/Marker Felt.ttf", 30);
	this->addChild(label);
	label->setPosition(winSize.width / 2, winSize.height / 2);

	return true;
}
