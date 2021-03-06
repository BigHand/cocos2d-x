#include "testBasic.h"
#include "controller.h"

BackToMainMenuLayer::BackToMainMenuLayer()
{
    //add the menu item for back to main menu
    CCLabelTTF* label = CCLabelTTF::labelWithString("MainMenu", "Arial", 20);
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(BackToMainMenuLayer::MainMenuCallback));

    CCMenu* pMenu =CCMenu::menuWithItems(pMenuItem, NULL);
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( CCPointMake( s.width - 50, 25) );

    addChild(pMenu, 1);
}

void BackToMainMenuLayer::MainMenuCallback(CCObject* pSender)
{
    CCScene* pScene = CCScene::node();
    CCLayer* pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

TestScene::TestScene()
{
    CCScene::init();
    CCLayer* pLayer = new BackToMainMenuLayer();
    pLayer->autorelease();

    addChild(pLayer, 1000);
}
