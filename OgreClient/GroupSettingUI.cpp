#include "stdafx.h"
#include "GroupsettingUI.h"


BaseUI::CGroupSettingUI::CGroupSettingUI()
{
}

BaseUI::CGroupSettingUI::~CGroupSettingUI()
{
}
//加载资源
bool BaseUI::CGroupSettingUI::LoadUI()
{
	MyGUI::ResourceManager::getInstance().load("duiwushezhi.xml");

	initialise("GroupSetting.layout");  //加载资源


	assignWidget(m_BtnOk,"BTN_OK");
	assignWidget(m_BtnClose,"BTN_Close");
	assignWidget(m_CmbGroupType,"CMB_GroupType");
	assignWidget(m_CmbDeclaration,"CMB_Declaration");
	assignWidget(m_CmbDestination,"CMB_Destination");
	assignWidget(m_ChkSearchable,"CHK_Searchable");
	assignWidget(m_BtnCha,"BTN_Cha");

	m_CmbGroupType->addItem(MyGUI::UString(L"无").asUTF8());
	m_CmbGroupType->addItem(MyGUI::UString(L"副本").asUTF8());
	m_CmbGroupType->addItem(MyGUI::UString(L"任务").asUTF8());
	m_CmbGroupType->addItem(MyGUI::UString(L"活动").asUTF8());
	m_CmbGroupType->setIndexSelected(0);


	m_CmbDeclaration->addItem(MyGUI::UString(L"一起副本吧").asUTF8());
	m_CmbDeclaration->addItem(MyGUI::UString(L"一起组队吧！").asUTF8());
	m_CmbDeclaration->addItem(MyGUI::UString(L"一起下副本吧！").asUTF8());
	m_CmbDeclaration->addItem(MyGUI::UString(L"一起来PK吧！").asUTF8());
	m_CmbDeclaration->addItem(MyGUI::UString(L"有参加活动的没？！").asUTF8());
	m_CmbDeclaration->addItem(MyGUI::UString(L"任务过不去了！").asUTF8());
	m_CmbDeclaration->setIndexSelected(0);

	m_CmbDestination->addItem(MyGUI::UString(L"无").asUTF8());
	m_CmbDestination->addItem(MyGUI::UString(L"Test1").asUTF8());
	m_CmbDestination->addItem(MyGUI::UString(L"Test2").asUTF8());
	m_CmbDestination->addItem(MyGUI::UString(L"Test3").asUTF8());
	m_CmbDestination->setIndexSelected(0);

	m_BtnOk->eventMouseButtonClick += MyGUI::newDelegate(this, &CGroupSettingUI::notifyOkButtonClick);
	m_BtnClose->eventMouseButtonClick += MyGUI::newDelegate(this, &CGroupSettingUI::notifyCloseButtonClick);
	m_BtnCha->eventMouseButtonClick += MyGUI::newDelegate(this, &CGroupSettingUI::notifyCloseButtonClick);
	m_ChkSearchable->eventMouseButtonClick += MyGUI::newDelegate(this, &CGroupSettingUI::notifySearchChkButtonClick);

	return true;
}

//设置是否显示
bool BaseUI::CGroupSettingUI::Show(bool bShow)
{
	if(bShow)
	{
		MyGUI::InputManager::getInstance().addWidgetModal(mMainWidget);
		MyGUI::LayerManager::getInstance().upLayerItem(mMainWidget);
	}
	else
	{
		MyGUI::InputManager::getInstance().removeWidgetModal(mMainWidget);
	}

	mMainWidget->setVisible(bShow);
	return true;
}

//设置窗口位置
bool BaseUI::CGroupSettingUI::SetPosition(int x, int y)
{
	mMainWidget->setPosition(x,y);
	return false;
}

MyGUI::IntPoint BaseUI::CGroupSettingUI::GetPosition()
{
	return mMainWidget->getPosition();
}

//窗口是否显示
bool BaseUI::CGroupSettingUI::IsShow()
{
	return mMainWidget->getVisible();
}

void BaseUI::CGroupSettingUI::notifyOkButtonClick(MyGUI::Widget* _sender)
{
	OnOkButtonClick();
}

void BaseUI::CGroupSettingUI::notifyCloseButtonClick(MyGUI::Widget* _sender)
{
	Show(false);

	OnCloseButtonClick();
}

void BaseUI::CGroupSettingUI::notifySearchChkButtonClick( MyGUI::Widget* _sender )
{
	m_ChkSearchable->setStateSelected(!m_ChkSearchable->getStateSelected());
}