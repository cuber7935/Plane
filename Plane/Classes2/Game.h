#ifndef _GAME_H_
#define _GAME_H_

#include "Util.h"
#include "BackGround.h"
#include "GameCtl.h"
#include "ComputerAi.h"

class Game: public Layer, public GameDelegate
{
public:
	Game();
	~Game();
	virtual bool init()override;

	//Åö×²¼ì²â
	void collision(float dt);

	//ÓÎÏ·½áÊø
	virtual void gameOver()override;

	CREATE_FUNC(Game);
private:
	BackGround*  _backGrd;
	GameCtl*     _gameCtl;
	ComputerAi*  _compAi;
};

#endif