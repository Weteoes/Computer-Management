#include <pch.h>
#include <Weteoes/Application/Dlg.h>
#include <Weteoes/Application/Icon.h>
#include <Weteoes/Application/AppConfig.h>
#include <atltypes.h>

HWND DlgClass::Dlg_HWND;
HINSTANCE DlgClass::Dlg_HINSTANCE;
DlgClass::Dlg DlgClass::Dlg_ = { 0,0,300,400 }; //��¼��������

void DlgClass::Dlg_Close() { 
	Dlg_Icon_Remove();
	exit(0x40);
}
void DlgClass::Dlg_Mini() {
	if (!AppConfigClass::IsLogin) { //��û��½
		ShowWindow(Dlg_HWND, SW_MINIMIZE);
	}
	else { //�Ѿ���¼
		Dlg_SetNowRect(); //�������ڵĴ�����Ϣ

		//�ƶ�����λ��
		int nFullWidth = GetSystemMetrics(SM_CXSCREEN), //��ȡ��Ļ��С
			nFullHeight = GetSystemMetrics(SM_CYSCREEN);
		SetWindowPos(Dlg_HWND, NULL, nFullWidth, nFullHeight, 0, 0, SWP_NOSIZE);  //����0����,�Ƶ������,��Ȼ�������Ӱ

		ShowWindow(Dlg_HWND, SW_HIDE);
	}
}
#include <Weteoes/Application/App.h>
void DlgClass::Dlg_Show(bool first) {
	if (!first) { //���Ǵ��ڴ�������õ�
		if (!AppConfigClass::IsLogin) { //��û��½
			ShowWindow(Dlg_HWND, SW_RESTORE);
		}
		else { //�Ѿ���¼
			Dlg a = Dlg_GetRect(); //��ȡ����Ĵ�����Ϣ
			SetWindowPos(Dlg_HWND, NULL, a.x, a.y, 0, 0, SWP_NOSIZE);  //����0����,�Ƶ������
			ShowWindow(Dlg_HWND, SW_SHOW);
		}
	}
	else { //���ڴ��������
		AppClass().Start_SRW(0); // ����UI����
	}
}
void DlgClass::Dlg_Icon_Add() {
	IconClass().Icon_Add(Dlg_HWND, Dlg_HINSTANCE); // ���޸�
}
void DlgClass::Dlg_Icon_Remove() { 
	IconClass().Icon_Remove();
}
void DlgClass::Dlg_SetNowRect(bool SetWH) {
	CRect DlgCRect;
	GetWindowRect(Dlg_HWND, &DlgCRect); //��ȡ����Ļ�е�����
	Dlg_.x = DlgCRect.left;
	Dlg_.y = DlgCRect.top;
	if (SetWH) { //���ÿ��
		Dlg_.width = DlgCRect.right - DlgCRect.left;
		Dlg_.height = DlgCRect.bottom - DlgCRect.top;
	}
}
DlgClass::Dlg DlgClass::Dlg_GetRect() {
	Dlg a;
	if (Dlg_.x == 0 || Dlg_.y == 0) { //������ֵ
		int width = GetSystemMetrics(SM_CXSCREEN),
			height = GetSystemMetrics(SM_CYSCREEN); //��ȡ��Ļ�ֱ���
		a.x = (width - Dlg_.width) / 2;
		a.y = (height - Dlg_.height) / 2 - 20;
	}
	else {
		a.x = Dlg_.x;
		a.y = Dlg_.y;
	}
	Dlg_.width == 0 ? a.width = 300 : a.width = Dlg_.width;
	Dlg_.height == 0 ? a.height = 400 : a.height = Dlg_.height;
	return a;
}