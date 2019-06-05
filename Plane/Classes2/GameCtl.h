#ifndef _GAME_CTL_H_
#define _GAME_CTL_H_

#include "Hero.h"

class GameCtl: public Layer
{
public:
	GameCtl();
	~GameCtl();
	enum {START, PAUSE};

	virtual bool init()override;

	//创建飞机精灵
	void createPlane();
	//创建记分牌
	void createScoreBoard();
	//设置记分
	void setScoreBoard(int score);
	//游戏控制
	void createGameCtl();
	//回调函数
	void gameCtlCallBack(Ref* sender);
	//获取分数
	int getScore()const;

	//子弹控制回调 函数
	void bulletCtl(float dt);
	//导弹控制回调函数
	void missleCtl(float dt);

	//增加炸弹
	void addBomb();
	//减少炸弹
	void delBomb();

	//设置跟踪导弹标记
	void setMissle();

	//回调函数
	bool TouchBegan(Touch* touch, Event* ev);
	void TouchMoved(Touch* touch, Event* ev);

	CREATE_FUNC(GameCtl);
private:
	int  _playScore;
	Label*    _score;     //计分标签
	MenuItem* _items[2];  //暂停和开始
public:
	Hero*     _hero;             //战机
	Vector<Sprite*> _bullets;    //用于存放子弹的容器，方便后面碰撞检测
	int _bombCount;              //炸弹数量
	Sprite* _bomb;               //炸弹精灵
	bool _bMissle;               //跟踪导弹标记
	bool _bombed;                //炸弹被点
	bool _bFireMissile;
};

#endif