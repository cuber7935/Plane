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

	//�����ɻ�����
	void createPlane();
	//�����Ƿ���
	void createScoreBoard();
	//���üǷ�
	void setScoreBoard(int score);
	//��Ϸ����
	void createGameCtl();
	//�ص�����
	void gameCtlCallBack(Ref* sender);
	//��ȡ����
	int getScore()const;

	//�ӵ����ƻص� ����
	void bulletCtl(float dt);
	//�������ƻص�����
	void missleCtl(float dt);

	//����ը��
	void addBomb();
	//����ը��
	void delBomb();

	//���ø��ٵ������
	void setMissle();

	//�ص�����
	bool TouchBegan(Touch* touch, Event* ev);
	void TouchMoved(Touch* touch, Event* ev);

	CREATE_FUNC(GameCtl);
private:
	int  _playScore;
	Label*    _score;     //�Ʒֱ�ǩ
	MenuItem* _items[2];  //��ͣ�Ϳ�ʼ
public:
	Hero*     _hero;             //ս��
	Vector<Sprite*> _bullets;    //���ڴ���ӵ������������������ײ���
	int _bombCount;              //ը������
	Sprite* _bomb;               //ը������
	bool _bMissle;               //���ٵ������
	bool _bombed;                //ը������
	bool _bFireMissile;
};

#endif