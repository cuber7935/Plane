#include "Util.h"


Util::Util()
{
}

Util::~Util()
{
}

Sprite * Util::addSprite(const char * fileName, Node * parent, Vec2 pos)
{
	Sprite* sprite = Sprite::create(fileName);
	if (!sprite)
	{
		log("create sprite fail");
		return nullptr;
	}		
	parent->addChild(sprite, 0);
	sprite->setPosition(pos);
	return sprite;
}

Scene * Util::createScene(Layer* layer)
{
	Scene* scene = Scene::create();
	scene->addChild(layer);
	return scene;
}

void Util::move(Node * node, Vec2 delta)
{
	node->setPosition(node->getPosition() + delta);
}

void Util::moveX(Node * node, float deltaX)
{
	node->setPositionX(node->getPositionX() + deltaX);
}

void Util::moveY(Node * node, float deltaY)
{
	node->setPositionY(node->getPositionY() + deltaY);
}

void Util::addTouch(Node * node, 
	EventListenerTouchOneByOne::ccTouchBeganCallback began, 
	EventListenerTouchOneByOne::ccTouchCallback ended, 
	EventListenerTouchOneByOne::ccTouchCallback moved,
	EventListenerTouchOneByOne::ccTouchCallback cancelled, 
	bool bSelect)
{
	auto ev = EventListenerTouchOneByOne::create();
	ev->setSwallowTouches(bSelect);
	
	ev->onTouchBegan = began;
	if(ended)
		ev->onTouchEnded = ended;
	if(moved)
		ev->onTouchMoved = moved;
	if(cancelled)
		ev->onTouchCancelled = cancelled;

	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ev, node);
}
