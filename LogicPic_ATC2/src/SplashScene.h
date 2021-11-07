#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"
#include "MainMenuScene.h"
USING_NS_CC;

class Splash : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(Splash);

	//DELAY, DEPOIS IR PARA MAINMENU SCENE
	void GoToMainMenuScene(Ref *pSender);
	// function in the splash layer class
	void Splash::RunMainMenu(float dt) {
		// tell CCDirector to run main menu
		auto scene = MainMenu::createScene();
		//Director::getInstance()->popScene();
		Director::getInstance()->replaceScene(scene);
	}

};

#endif // __MAINMENU_SCENE_H__