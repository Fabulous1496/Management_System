#pragma once
#include<iostream>
# include<string>
#include"Worker.h"
using namespace std;

class Manager :public Worker
{
public:
	//构造函数
	Manager(int ID, string name, int dID);
	//显示个人信息
	virtual void showInfo();
	//获取岗位名称
	virtual string getDeptName();

};