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

//��ײ���
void Game::collision(float dt)
{
	//�ж�Ӣ���Ƿ�����
	if (_gameCtl->_hero->isDead())
		return;

	if (_gameCtl->_bFireMissile)
	{
		_gameCtl->_bFireMissile = false;

		_compAi->fireMissile(_gameCtl->_hero);
	}


	if (_gameCtl->_bombed)
	{
		//�ɵ����ел�
		_gameCtl->_bombed = false;
		while (_compAi->_enemys.size())
		{
			Enemy* enemy = _compAi->_enemys.back();
			_compAi->_enemys.popBack();

			enemy->bomb();
			//�ӷ�
			_gameCtl->setScoreBoard(enemy->score());
		}
		return;
	}

	//��ȡӢ�۵ľ��δ�С
	Rect reHero = _gameCtl->_hero->getBoundingBox();

	//�������е���
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

	//�������ел�
	for (auto itEnemy = _compAi->_enemys.begin(); itEnemy != _compAi->_enemys.end();)
	{
		//��ȡ�л�
		Enemy* enemy = *itEnemy;
		//��ȡ�л��ľ��δ�С
		Rect rc = enemy->getBoundingBox();

		//�ж��Ƿ���ײ�Ѿ�
		if (rc.intersectsRect(reHero))
		{
			//�о��ɻ�����
			itEnemy = _compAi->_enemys.erase(itEnemy);
			//��ը
			enemy->bomb();
			//�ӷ�
			_gameCtl->setScoreBoard(enemy->score());

			//�Ҿ����˺�
			_gameCtl->_hero->hurt(enemy->getEnemyBlood());
			//�ж��Ҿ��Ƿ�����
			if (_gameCtl->_hero->isDead())
			{
				//���Ŷ���
				_gameCtl->_hero->bomb();
				return;
			}
			//����Ҿ�û����������һ����ײ���
			continue;
		}

		//���������ӵ�
		for (auto itBullet = _gameCtl->_bullets.begin(); itBullet != _gameCtl->_bullets.end();)
		{
			//��ȡ�ӵ���λ��
			Sprite* bullet = *itBullet;
			Vec2 pos = bullet->getPosition();
			//�����ӵ���ʱ������ײ��ⶨʱ������˳�򲻶������ӵ����ܻ�û��Ⱦ����
			pos.y -= 23;

			//�ж��ӵ���л��Ƿ���ײ
			if (rc.containsPoint(pos))
			{
				//�ȴ����ӵ�
				//�Ƴ��ӵ�
				bullet->removeFromParent();
				//��������Ҳ�Ƴ�
				itBullet = _gameCtl->_bullets.erase(itBullet);

				//�л����˺�
				enemy->hurt(1);
				//�жϵл��Ƿ�����
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

		//�ٴ��жϵл��Ƿ�����
		if (enemy->isDead())
		{
			if (enemy->type() == Enemy::SML)
			{
				_compAi->createItemRand(0.8f);
			}
			//�ӷ�
			_gameCtl->setScoreBoard(enemy->score());
			//�Ƴ��л�
			itEnemy = _compAi->_enemys.erase(itEnemy);
			//�л���ը
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
	//�����л�����
	Scene* scene = Util::createScene(LayerScore::create(_gameCtl->getScore()));
	TransitionJumpZoom* zoom = TransitionJumpZoom::create(0.1f, scene);
	Director::getInstance()->replaceScene(zoom);
}
