#include "Plane.h"

#define winSize Director::getInstance()->getWinSize()

bool PlaneX::init()
{
	if(!Layer::init())
		return false;

	//loadSpriteFrameCache();
	addScorllBlackGround();

	createScore();

	//碰撞检测
	//schedule(schedule_selector(PlaneX::collision));

	return true;
}

//1.加载精灵帧缓存
void PlaneX::loadSpriteFrameCache()
{
	_cache = SpriteFrameCache::getInstance();
	_cache->addSpriteFramesWithFile("PFBoom.plist");
	_cache->addSpriteFramesWithFile("chooselevel.plist");

}
//2.添加滚动背景
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
//3.添加英雄
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
//4.增加触摸处理
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
//5.增加敌机
void PlaneX::addEnemy()
{
	schedule(schedule_selector(PlaneX::genMin), 1.0f);    //小飞机
	schedule(schedule_selector(PlaneX::genMid), 3.0f);    //中飞机
	schedule(schedule_selector(PlaneX::genMax), 7.0f);    //大飞机
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
	_enemys.pushBack(enemy);   //便于碰撞检测

	_data = new EnemyData;
	_data->_type = type;
	_data->_hp = hp[type];
	_data->_socre = score[type];
	enemy->setUserData(_data);
}
//6.发射子弹
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
//7.碰撞检测
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
				//子弹消灭
				(*it)->setVisible(false);
				it2 = _bullets.erase(it2);
				//敌机少血
				data->_hp--;
				if (data->_hp <= 0)
				{
					//敌机死亡
					setScore(data->_socre);
					break;
				}
			}
			it2++;
		}
		if (data->_hp <= 0)
		{
			(*it)->stopAllActions();
			//播放动画
			enemyDeadAnimation((*it));
		}	
		it++;
	}
}
//获取敌机信息
EnemyData * PlaneX::GetUserData(Sprite * sp)
{
	return (EnemyData*)sp->getUserData();
}
//获取动画
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
//播放敌机死亡动画
void PlaneX::enemyDeadAnimation(Sprite * sp)
{
	stopAllActions();
	//获取动画
	Animate* mate = getAnimationByType(GetUserData(sp)->_type);
	RemoveSelf* self = RemoveSelf::create();

	sp->runAction(Sequence::create(mate, self, NULL));
	delete GetUserData(sp);
}
//创建计分板
void PlaneX::createScore()
{
	_label = Label::createWithSystemFont("0", "fonts/Arial.ttf", 20);
	this->addChild(_label);
	_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_label->setPosition(0, winSize.height);
}
//设置计分板
void PlaneX::setScore(int score)
{
	char buf[128] = {0};
	sprintf(buf, "%d", getScore()+score);
	_label->setString(buf);
}
//获取计分板上的数据
int PlaneX::getScore()const
{
	return atoi(_label->getString().c_str());
}

//游戏结束
void PlaneX::gameover()
{
	//保存成绩
	int score = getScore();
	
	//释放资源
	unscheduleAllCallbacks();
	removeAllChildren();
	_bullets.clear();
	_enemys.clear();
	_eventDispatcher->removeEventListenersForTarget(this);

	//再次添加背景
	addScorllBlackGround();

	//提交成绩到服务器
	commitServer(score);
}

//提交数据到服务器
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
//请求回调函数
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
