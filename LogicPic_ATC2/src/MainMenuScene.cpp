#include "MainMenuScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto menuTitle = MenuItemImage::create("title.png", //so para testar o diretorio das imagens
		"C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/title.png");
	auto playItem = MenuItemImage::create("C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/play.png",
		"C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/play-clicked.png",
		CC_CALLBACK_1(MainMenu::GoToGameScene, this));
	auto menu = Menu::create(menuTitle, playItem, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	this->addChild(menu);

	auto backgroundSprite = Sprite::create
		("C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/background.png");
	backgroundSprite->setPosition(Point((visibleSize.width / 2) +
		origin.x, (visibleSize.height / 2) + origin.y));
	this->addChild(backgroundSprite, -1);

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/sporting.mp3");
    return true;
}

void MainMenu::GoToGameScene(Ref *pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->
		playEffect("C:/Users/Daniel/Downloads/atc2/programas/cocos2d-x-3.10/projects/LogicPic/Resources/sporting.mp3");
	auto scene = GameScreen::createScene();
	//Director::getInstance()->replaceScene(scene);
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
	//Director::getInstance()->replaceScene(TransitionFlipX::create(3, scene));
	//Director::getInstance()->replaceScene(TransitionZoomFlipY::create(3, scene));
	//Director::getInstance()->replaceScene (TransitionPageTurn::create(3, scene, false));
}

