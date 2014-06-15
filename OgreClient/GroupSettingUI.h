
//////////////////////////////////////////////////////////////////////////
/*
右击自己的头像弹出右击菜单
*/
//////////////////////////////////////////////////////////////////////////
#ifndef _DEF_GROUP_SETTING_UI_H_
#define _DEF_GROUP_SETTING_UI_H_

#include "BaseLayout/BaseLayout.h"
namespace BaseUI
{
	class CGroupSettingUI:
		public wraps::BaseLayout
	{
	public:
		CGroupSettingUI();
		~CGroupSettingUI();

		//加载资源
		bool LoadUI();
		//设置是否显示
		bool Show(bool bShow);
		//窗口是否显示
		bool IsShow();
		//设置窗口位置
		bool SetPosition(int x, int y);

		MyGUI::IntPoint GetPosition();

	public:
		virtual void OnOkButtonClick(){return ;}
		virtual void OnCloseButtonClick(){return ;}
	public:
		void notifyOkButtonClick(MyGUI::Widget* _sender);
		void notifyCloseButtonClick(MyGUI::Widget* _sender);
		void notifySearchChkButtonClick(MyGUI::Widget* _sender);

		MyGUI::ButtonPtr m_BtnOk;
		MyGUI::ButtonPtr m_BtnClose;
		MyGUI::ComboBoxPtr m_CmbGroupType;
		MyGUI::ComboBoxPtr m_CmbDeclaration;
		MyGUI::ComboBoxPtr m_CmbDestination;
		MyGUI::ButtonPtr  m_ChkSearchable;
		MyGUI::ButtonPtr  m_BtnCha;
	};
}


#endif