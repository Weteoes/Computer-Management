// Mouse_event.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include <string>
#include <iostream>
#include <Windows.h>

//Weteoes
std::string One = "Weteoes";
std::string Two_one = "0";
std::string Two_two = "1";
int main(int Weteoes_i,char* Weteoes_text[])
{
	if (Weteoes_i > 0) {
		int x = (int)Weteoes_text[3], y = (int)Weteoes_text[4];
		std::cout << "arg:" << Weteoes_text[1] << std::endl;
		if (Weteoes_text[1] == One) {
			std::cout << "yes" << std::endl;
			if (Weteoes_text[2] == Two_one) {
				while (1) {
					Sleep(1000);
					POINT a;
					GetCursorPos(&a);
					std::cout << "当前鼠标坐标" << " x:" << a.x << " y:" << a.y << std::endl;
				}
			}
			else if (Weteoes_text[2] == Two_two) {
				SetCursorPos(x, y);
				mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, NULL);  
			}
		}
	}
    return 0;
}

