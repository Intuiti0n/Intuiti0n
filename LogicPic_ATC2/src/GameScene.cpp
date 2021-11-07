#include "GameScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto pauseItem =
		MenuItemImage::create("C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/pause.png",
		"C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/pause-clicked.png",
		CC_CALLBACK_1(GameScreen::GoToPauseScene, this));
	pauseItem->setPosition(Point(pauseItem->getContentSize().width -
		(pauseItem->getContentSize().width / 4) + origin.x,
		visibleSize.height - pauseItem->getContentSize().height +
		(pauseItem->getContentSize().width / 4) + origin.y));
	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	auto backgroundSprite = Sprite::create
		("C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/background.png");
	backgroundSprite->setPosition(Point((visibleSize.width / 2) +
		origin.x, (visibleSize.height / 2) + origin.y));
	this->addChild(backgroundSprite, -1);

    return true;
}

void GameScreen::GoToPauseScene(cocos2d::Ref *pSender)
{
	auto scene = PauseMenu::createScene();
	Director::getInstance()->pushScene(scene);
}
void GameScreen::GoToGameOverScene(cocos2d::Ref *pSender)
{
	auto scene = GameOver::createScene();
	Director::getInstance()->replaceScene(scene);
}

