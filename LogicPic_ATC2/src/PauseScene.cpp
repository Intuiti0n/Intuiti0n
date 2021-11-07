#include "PauseScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* PauseMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = PauseMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PauseMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto resumeItem =
		MenuItemImage::create("C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/resume.png",
		"C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/resume-clicked.png",
		CC_CALLBACK_1(PauseMenu::Resume, this));
	auto retryItem =
		MenuItemImage::create("C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/retry.png",
		"C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/retry-clicked.png",
		CC_CALLBACK_1(PauseMenu::Retry, this));
	auto mainMenuItem =
		MenuItemImage::create("C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/menu.png",
		"C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/menu-clicked.png",
		CC_CALLBACK_1(PauseMenu::GoToMainMenuScene, this));
	auto menu = Menu::create(resumeItem, retryItem, mainMenuItem,
		NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height /6);
	this->addChild(menu);

	auto backgroundSprite = Sprite::create
		("C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/background.png");
	backgroundSprite->setPosition(Point((visibleSize.width / 2) +
		origin.x, (visibleSize.height / 2) + origin.y));
	this->addChild(backgroundSprite, -1);

    return true;
}

void PauseMenu::Resume(cocos2d::Ref *pSender)
{
	Director::getInstance()->popScene();
}
void PauseMenu::GoToMainMenuScene(cocos2d::Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}
void PauseMenu::Retry(cocos2d::Ref *pSender)
{
	auto scene = GameScreen::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}