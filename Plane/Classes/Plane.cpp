#include "Plane.h"

#define winSize Director::getInstance()->getWinSize()

bool PlaneX::init()
{
	if(!Layer::init())
		return false;

	//loadSpriteFrameCache();
	addScorllBlackGround();

	createScore();

	//��ײ���
	//schedule(schedule_selector(PlaneX::collision));

	return true;
}

//1.���ؾ���֡����
void PlaneX::loadSpriteFrameCache()
{
	_cache = SpriteFrameCache::getInstance();
	_cache->addSpriteFramesWithFile("PFBoom.plist");
	_cache->addSpriteFramesWithFile("chooselevel.plist");

}
//2.��ӹ�������
void PlaneX::addScorllBlackGround()
{
	Sprite* sp = Sprite::create("background.png");
	Sprite* sp2 = Sprite::create("background.png");

	sp->setPosition(winSize.width/2, winSize.height/2);
	sp2->setPosition(winSize.width / 2, sp->getPositionY()+ winSize.height);

	Node* bg = Node::create();
	bg->addChild(sp);
	bg->addChild(sp2);
	this->addChild(bg);

	MoveBy* by = MoveBy::create(5.0f, Vec2(0, -winSize.height));
	Place* pl = Place::create(Vec2(0, 0));
	Sequence* seq = Sequence::createWithTwoActions(pl, by);

	bg->runAction(RepeatForever::create(seq));
}
//3.���Ӣ��
void PlaneX::addZero()
{
	_zero = Sprite::create("Player4.png");
	this->addChild(_zero);
	Vector<SpriteFrame*> frames;
	for (int i = 0; i < 2; i++)
	{
#if 0
		char buf[128] = {0};
		sprintf(buf, "zero%d", i);
		SpriteFrame* frame = _cache->getSpriteFrameByName(buf);
		frames.pushBack(frame);
#endif
	
	}
	Animation* ani = Animation::createWithSpriteFrames(frames);
	Animate*   mate = Animate::create(ani);
	_zero->runAction(RepeatForever::create(mate));
	_zero->setPosition(winSize.width / 2, _zero->getBoundingBox().size.height);

	schedule(schedule_selector(PlaneX::bullets));
}
//4.���Ӵ�������
void PlaneX::addTouchEvent()
{
	auto ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = [&](Touch* touch, Event*) {
		return true;
	};
	ev->onTouchMoved = [=](Touch* touch, Event*) {
		_zero->setPosition(_zero->getPosition()+touch->getDelta());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
}
//5.���ӵл�
void PlaneX::addEnemy()
{
	schedule(schedule_selector(PlaneX::genMin), 1.0f);    //С�ɻ�
	schedule(schedule_selector(PlaneX::genMid), 3.0f);    //�зɻ�
	schedule(schedule_selector(PlaneX::genMax), 7.0f);    //��ɻ�
}
void PlaneX::genMin(float dt)
{
	genEnemy(0);
}
void PlaneX::genMid(float dt)
{
	genEnemy(1);
}
void PlaneX::genMax(float dt)
{
	genEnemy(2);
}
void PlaneX::genEnemy(int type)
{
	Sprite* enemy = Sprite::createWithSpriteFrameName(Type[type]);
	this->addChild(enemy);
	enemy->setPosition(winSize.width*CCRANDOM_0_1(), winSize.height+enemy->getBoundingBox().size.height/2);
	auto to = MoveTo::create(6.0f, Vec2(enemy->getPositionX(), enemy->getBoundingBox().size.height / 2));
	RemoveSelf* self = RemoveSelf::create();
	
	enemy->runAction(Sequence::create(to, self, NULL));
	_enemys.pushBack(enemy);   //������ײ���

	_data = new EnemyData;
	_data->_type = type;
	_data->_hp = hp[type];
	_data->_socre = score[type];
	enemy->setUserData(_data);
}
//6.�����ӵ�
void PlaneX::bullets(float dt)
{
	Sprite* bullet = Sprite::createWithSpriteFrameName("Bullet,png");
	this->addChild(bullet);
	bullet->setPosition(_zero->getPositionX(), _zero->getPositionY()+bullet->getBoundingBox().size.height/2);
	_bullets.pushBack(bullet);

	auto by = MoveBy::create(winSize.width/1320, Vec2(0, winSize.height));
	RemoveSelf* self = RemoveSelf::create();
	bullet->runAction(Sequence::createWithTwoActions(by, self));
	
}
//7.��ײ���
void PlaneX::collision(float dt)
{
	Rect rc = _zero->getBoundingBox();
	for (auto it = _enemys.begin(); it != _enemys.end();)
	{
		Rect rcEmy = (*it)->getBoundingBox();
		EnemyData* data = GetUserData(*it);
		if (rcEmy.intersectsRect(rc))
		{
			gameover();
			return;
		}
		for (auto it2 = _bullets.begin(); it2 != _bullets.end();)
		{
			if ((*it2)->getReferenceCount() == 1)
			{
				it2 = _bullets.erase(it2);
				continue;
			}
			if (rcEmy.containsPoint((*it2)->getPosition()))
			{
				//�ӵ�����
				(*it)->setVisible(false);
				it2 = _bullets.erase(it2);
				//�л���Ѫ
				data->_hp--;
				if (data->_hp <= 0)
				{
					//�л�����
					setScore(data->_socre);
					break;
				}
			}
			it2++;
		}
		if (data->_hp <= 0)
		{
			(*it)->stopAllActions();
			//���Ŷ���
			enemyDeadAnimation((*it));
		}	
		it++;
	}
}
//��ȡ�л���Ϣ
EnemyData * PlaneX::GetUserData(Sprite * sp)
{
	return (EnemyData*)sp->getUserData();
}
//��ȡ����
Animate * PlaneX::getAnimationByType(int type)
{
	Vector<SpriteFrame*> frames;
	for (int i = 1; ; i++)
	{
		char buf[128] = { 0 };
		sprintf(buf, "enemy%d_down%d.png", type+1, i);
		SpriteFrame* frame = _cache->getSpriteFrameByName(buf);
		if (!frame)
			break;
		frames.pushBack(frame);
	}
	Animation* ani = Animation::createWithSpriteFrames(frames);
	Animate* mate = Animate::create(ani);

	return mate;
}
//���ŵл���������
void PlaneX::enemyDeadAnimation(Sprite * sp)
{
	stopAllActions();
	//��ȡ����
	Animate* mate = getAnimationByType(GetUserData(sp)->_type);
	RemoveSelf* self = RemoveSelf::create();

	sp->runAction(Sequence::create(mate, self, NULL));
	delete GetUserData(sp);
}
//�����Ʒְ�
void PlaneX::createScore()
{
	_label = Label::createWithSystemFont("0", "fonts/Arial.ttf", 20);
	this->addChild(_label);
	_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_label->setPosition(0, winSize.height);
}
//���üƷְ�
void PlaneX::setScore(int score)
{
	char buf[128] = {0};
	sprintf(buf, "%d", getScore()+score);
	_label->setString(buf);
}
//��ȡ�Ʒְ��ϵ�����
int PlaneX::getScore()const
{
	return atoi(_label->getString().c_str());
}

//��Ϸ����
void PlaneX::gameover()
{
	//����ɼ�
	int score = getScore();
	
	//�ͷ���Դ
	unscheduleAllCallbacks();
	removeAllChildren();
	_bullets.clear();
	_enemys.clear();
	_eventDispatcher->removeEventListenersForTarget(this);

	//�ٴ���ӱ���
	addScorllBlackGround();

	//�ύ�ɼ���������
	commitServer(score);
}

//�ύ���ݵ�������
void PlaneX::commitServer(int score)
{
	char buf[1024] = {0};
	sprintf(buf, "%d", score);

	HttpClient* http = HttpClient::getInstance();
	
	HttpRequest* req = new HttpRequest;
	req->setRequestType(HttpRequest::Type::POST);
	req->setUrl("http://192.168.1.12/cgi-bin/a.out");
	req->setRequestData(buf, strlen(buf) + 1);
	req->setResponseCallback(CC_CALLBACK_2(PlaneX::httpCallBack, this));

	http->send(req);
	req->release();
}
//����ص�����
void PlaneX::httpCallBack(HttpClient * client, HttpResponse * response)
{
	char* data = const_cast<char*>(response->getResponseDataString());
	if (_menu)
		_menu->removeFromParent();

	_menu = Menu::create();
	this->addChild(_menu);
	_menu->setLocalZOrder(10);

	//char* p = strdup(data);  
	//free(p);
	char* score = strtok(data, "|");
	while (score)
	{
		auto item = MenuItemFont::create(score);
		item->setEnabled(false);
		_menu->addChild(item);
		score = strtok(NULL, "|");
	}
	_menu->alignItemsHorizontally();
}
