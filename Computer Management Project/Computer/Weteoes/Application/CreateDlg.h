#pragma once
#include <pch.h>

#ifndef CreateDlgClass_H
#define CreateDlgClass_H
class CreateDlgClass {
public:
	void Browser(string url, bool minimize = false);
	void Login();
	void Main(bool minimize = false);
};
#endif