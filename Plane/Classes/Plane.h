#ifndef _PLANE_H_
#define _PLANE_H_

#include "cocos2d.h"
#include "network/HttpClient.h"
USING_NS_CC;
using namespace network;

static const char* Type[] = {
	"Enemy1.png",
	"Enemy2.png",
	"Enemy3.png"
};

struct EnemyData {
	int _hp;
	int _type;
	int _socre;
};

static const int hp[] = {10, 40, 100};
static const int score[] = {10, 20, 50};

class PlaneX : public Layer
{
public:
	bool init();
	CREATE_FUNC(PlaneX);

	//加载资源
	void loadSpriteFrameCache();

	//添加滚动背景
	void addScorllBlackGround();

	//添加英雄
	void addZero();

	//触摸处理
	void addTouchEvent();

	//增加敌机
	void addEnemy();
	void genMin(float dt);
	void genMid(float dt);
	void genMax(float dt);
	void genEnemy(int type);

	//发射子弹
	void bullets(float dt);

	//碰撞检测
	void collision(float dt);

	//获取敌机信息
	EnemyData* GetUserData(Sprite*);

	//获取动画
	Animate* getAnimationByType(int type);
	//播放敌机死亡动画
	void enemyDeadAnimation(Sprite*);

	//计分板
	void createScore();
	void setScore(int score);
	//获取计分板上的数据
	int getScore()const;

	//游戏结束
	void gameover();

	//提交数据到服务器
	void commitServer(int score);
	//请求回调函数
	void httpCallBack(HttpClient* client, HttpResponse* response);

protected:
	SpriteFrameCache*  _cache = nullptr;
	Sprite*            _zero = nullptr;
	Vector<Sprite*>    _enemys;
	Vector<Sprite*>    _bullets;
	EnemyData*         _data = nullptr;
	Label*			   _label = nullptr; 
	Menu*			   _menu = nullptr;
};


#endif