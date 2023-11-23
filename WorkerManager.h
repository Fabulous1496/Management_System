#pragma once    //防止头文件重复包含
#include<iostream>
#include<fstream>
#include"Worker.h"
#include"Boss.h"
#include"Employee.h"
#include"Manager.h"
#define FILENAME "empFile.txt"
using namespace std;

class WorkerManager
{
public:
	//构造函数
	WorkerManager();
	//析构函数
	~WorkerManager();
	//显示菜单
	void Show_Meau();
	//退出系统
	void ExitSystem();
	//记录职工人数
	int m_WorkerNum;
	//职工数组指针
	Worker** m_WorkerArray;
	//批量添加职工
	void AddWorker();
	//保存文件
	void Save();
	//判断文件是否为空
	bool isEmpty;
	//统计职工人数
	int get_Num();
	//从文件中初始化职工列表
	void initalize();
	//显示职工
	void Show_Worker();
	//判断职工是否存在
	int isExist(int ID);
	//删除职工
	void Delete_Worker();
	//修改职工
	void Change_Worker();
	//查找员工
	void Find_Worker();
	//按工号升序排序
	void Sort_Worker();
	//清空文件
	void CLEAN();
};
