#pragma once
#include<iostream>
#include<string>
using namespace std;

class Worker
{
public:

	//显示个人信息
	virtual void showInfo() = 0;
	//获取岗位名称
	virtual string getDeptName() = 0;

	int m_ID;		//工号
	string m_Name;		//姓名
	int m_DeptID;		//部门
};