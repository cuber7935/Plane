#include "Game.h"
#include "LayerScore.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::init()
{
	if (!Layer::init())
		return false;

	_backGrd = BackGround::create(true);
	this->addChild(_backGrd);

	_gameCtl = GameCtl::create();
	this->addChild(_gameCtl);

	//_gameCtl->_hero->_gameOver = std::bind(&Game::gameOver, this);
	_gameCtl->_hero->_gameOver = this;

	_compAi = ComputerAi::create();
	this->addChild(_compAi);

	//
	schedule(schedule_selector(Game::collision));

	return true;
}

//碰撞检测
void Game::collision(float dt)
{
	//判断英雄是否死亡
	if (_gameCtl->_hero->isDead())
		return;

	if (_gameCtl->_bFireMissile)
	{
		_gameCtl->_bFireMissile = false;

		_compAi->fireMissile(_gameCtl->_hero);
	}


	if (_gameCtl->_bombed)
	{
		//干掉所有敌机
		_gameCtl->_bombed = false;
		while (_compAi->_enemys.size())
		{
			Enemy* enemy = _compAi->_enemys.back();
			_compAi->_enemys.popBack();

			enemy->bomb();
			//加分
			_gameCtl->setScoreBoard(enemy->score());
		}
		return;
	}

	//获取英雄的矩形大小
	Rect reHero = _gameCtl->_hero->getBoundingBox();

	//遍历所有道具
	for (auto it = _compAi->_items.begin(); it != _compAi->_items.end();)
	{
		UnitItem* item = *it;
		if (item->getBoundingBox().intersectsRect(reHero))
		{
			if (item->_type == UnitItem::BOMD)
			{
				_gameCtl->addBomb();
			}
			else
			{
				_gameCtl->setMissle();
			}
			item->removeFromParent();
			it = _compAi->_items.erase(it);
		}
		else
		{
			it++;
		}
	}

	//遍历所有敌机
	for (auto itEnemy = _compAi->_enemys.begin(); itEnemy != _compAi->_enemys.end();)
	{
		//获取敌机
		Enemy* enemy = *itEnemy;
		//获取敌机的矩形大小
		Rect rc = enemy->getBoundingBox();

		//判断是否碰撞友军
		if (rc.intersectsRect(reHero))
		{
			//敌军飞机死亡
			itEnemy = _compAi->_enemys.erase(itEnemy);
			//爆炸
			enemy->bomb();
			//加分
			_gameCtl->setScoreBoard(enemy->score());

			//我军受伤害
			_gameCtl->_hero->hurt(enemy->getEnemyBlood());
			//判断我军是否死亡
			if (_gameCtl->_hero->isDead())
			{
				//播放动画
				_gameCtl->_hero->bomb();
				return;
			}
			//如果我军没死，继续下一次碰撞检测
			continue;
		}

		//遍历所有子弹
		for (auto itBullet = _gameCtl->_bullets.begin(); itBullet != _gameCtl->_bullets.end();)
		{
			//获取子弹的位置
			Sprite* bullet = *itBullet;
			Vec2 pos = bullet->getPosition();
			//由于子弹定时器与碰撞检测定时器调用顺序不定，故子弹可能还没渲染出来
			pos.y -= 23;

			//判断子弹与敌机是否碰撞
			if (rc.containsPoint(pos))
			{
				//先处理子弹
				//移除子弹
				bullet->removeFromParent();
				//从容器中也移除
				itBullet = _gameCtl->_bullets.erase(itBullet);

				//敌机受伤害
				enemy->hurt(1);
				//判断敌机是否死亡
				if (enemy->isDead())
					break;
				else
					continue;
			}
			else
			{
				itBullet++;
			}
		}

		//再此判断敌机是否死亡
		if (enemy->isDead())
		{
			if (enemy->type() == Enemy::SML)
			{
				_compAi->createItemRand(0.8f);
			}
			//加分
			_gameCtl->setScoreBoard(enemy->score());
			//移除敌机
			itEnemy = _compAi->_enemys.erase(itEnemy);
			//敌机爆炸
			enemy->bomb();
		}
		else 
		{
			itEnemy++;
		}
	}
}

void Game::gameOver()
{
	//动画切换场景
	Scene* scene = Util::createScene(LayerScore::create(_gameCtl->getScore()));
	TransitionJumpZoom* zoom = TransitionJumpZoom::create(0.1f, scene);
	Director::getInstance()->replaceScene(zoom);
}
