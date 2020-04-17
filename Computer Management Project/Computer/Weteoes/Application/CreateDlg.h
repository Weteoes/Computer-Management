#pragma once
#include <pch.h>

#ifndef CreateDlgClass_H
#define CreateDlgClass_H
class CreateDlgClass {
public:
	void browser(string url, bool minimize = false);
	void login();
	void main(bool minimize = false);
};
#endif