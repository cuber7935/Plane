#include "GameCtl.h"


GameCtl::GameCtl()
{
}

GameCtl::~GameCtl()
{
}

bool GameCtl::init()
{
	if(!Layer::init())
		return false;

	createPlane();
	createScoreBoard();
	createGameCtl();

	_bombCount = 0;
	
	_bomb = Sprite::create("plane/boom.png");
	addChild(_bomb);
	_bomb->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_bomb->setPosition(10, 10);
	_bomb->setVisible(false);

	_bombed = false;
	_bMissle = false;               
	_bFireMissile = false;

	Director::getInstance()->pause();

	//添加触摸
	Util::addTouch(this, CC_CALLBACK_2(GameCtl::TouchBegan, this), nullptr, CC_CALLBACK_2(GameCtl::TouchMoved, this), nullptr, false);

	return true;
}

void GameCtl::createPlane()
{
	_hero = Hero::create();
	this->addChild(_hero);
	_hero->setPosition(winSize.width / 2, _hero->getBoundingBox().size.height);

	//启动子弹控制定时器
	schedule(schedule_selector(GameCtl::bulletCtl));

	//导弹控制定时器
	schedule(schedule_selector(GameCtl::missleCtl), 0.1f);
}

void GameCtl::createScoreBoard()
{
	this->_score = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30);
	this->_score->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	this->_score->setPosition(0, winSize.height);
	this->addChild(_score, 0);
	_playScore = 0;
}

void GameCtl::setScoreBoard(int score)
{
	int cur = atoi(_score->getString().c_str());
	cur += score;
	_playScore += score;
	char buf[128] = {0};
	sprintf(buf, "%d", cur);
	_score->setString(buf);
	
}

void GameCtl::createGameCtl()
{
	Menu* menu = Menu::create();
	this->addChild(menu);

	const char* buf[] = {
		"plane/btn-play-selected.png",
		"plane/btn-play-normal.png",
	};

	for (int i = 0; i < 2; i++)
	{
		_items[i] = MenuItemImage::create(buf[i], buf[i]);
		menu->addChild(_items[i]);
		_items[i]->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
		_items[i]->setPosition(winSize.width/2, winSize.height/2);
		_items[i]->setTag(i);
		_items[i]->setCallback(CC_CALLBACK_1(GameCtl::gameCtlCallBack, this));	
	}

	_items[PAUSE]->setVisible(false);
}

void GameCtl::gameCtlCallBack(Ref * sender)
{
	MenuItem* item = (MenuItem*)sender;
	int tag = item->getTag();
	_items[tag]->setVisible(false);
	_items[1 - tag]->setVisible(true);

	if (tag == START)
		Director::getInstance()->resume();
	else
		Director::getInstance()->pause();
}

int GameCtl::getScore() const
{
	return _playScore;
}

void GameCtl::bulletCtl(float dt)
{
	//移动子弹
	for (auto it = _bullets.begin(); it != _bullets.end();)
	{
		Sprite* sprite = *it;
		Util::moveY(sprite, sprite->getBoundingBox().size.height + 2);

		//判断字段是否飞出窗口外
		if (sprite->getPositionY() > winSize.height)
		{
			sprite->removeFromParent();
			it = _bullets.erase(it);
		}
		else
		{
			it++;
		}
	}
	//获取飞机的位置
	Vec2 point = _hero->getPosition();
	point.y += _hero->getBoundingBox().size.height/ 2;
	//产生子弹
	Sprite* bullet = Util::addSprite("plane/Bullet.png", this, point);
	_bullets.pushBack(bullet);

}

void GameCtl::missleCtl(float dt)
{
	if(this->_bMissle)
		this->_bFireMissile = true;
}

void GameCtl::addBomb()
{
	this->_bombCount++;
	this->_bomb->setVisible(true);
}

void GameCtl::delBomb()
{
	this->_bombCount--;
	if (this->_bombCount <= 0)
		this->_bomb->setVisible(false);
}

void GameCtl::setMissle()
{
	this->_bMissle = true;
}

bool GameCtl::TouchBegan(Touch * touch, Event * ev)
{
	if (this->_bombCount > 0)
	{
		if (this->_bomb->getBoundingBox().containsPoint(touch->getLocation()))
		{
			this->_bombed = true;
		}
		this->delBomb();
	}
	return true;;
}

void GameCtl::TouchMoved(Touch * touch, Event * ev)
{
}

