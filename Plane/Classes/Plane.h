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

	//������Դ
	void loadSpriteFrameCache();

	//��ӹ�������
	void addScorllBlackGround();

	//���Ӣ��
	void addZero();

	//��������
	void addTouchEvent();

	//���ӵл�
	void addEnemy();
	void genMin(float dt);
	void genMid(float dt);
	void genMax(float dt);
	void genEnemy(int type);

	//�����ӵ�
	void bullets(float dt);

	//��ײ���
	void collision(float dt);

	//��ȡ�л���Ϣ
	EnemyData* GetUserData(Sprite*);

	//��ȡ����
	Animate* getAnimationByType(int type);
	//���ŵл���������
	void enemyDeadAnimation(Sprite*);

	//�Ʒְ�
	void createScore();
	void setScore(int score);
	//��ȡ�Ʒְ��ϵ�����
	int getScore()const;

	//��Ϸ����
	void gameover();

	//�ύ���ݵ�������
	void commitServer(int score);
	//����ص�����
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