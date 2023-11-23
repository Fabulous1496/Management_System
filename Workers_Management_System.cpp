#include<iostream>
#include<string>
#include<fstream>
#include"workerManager.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"
using namespace std;


int main()
{
	WorkerManager wm;
	int choice = 0;
	while (1)
	{
		wm.Show_Meau();
		cout << "请选择功能！" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:     //退出系统
			wm.ExitSystem();
			break;
		case 1:     //增加职工
			wm.AddWorker();
			break;
		case 2:		//显示职工
			wm.Show_Worker();
			break;
		case 3:		//删除员工
			wm.Delete_Worker();
			break;
		case 4:		//修改职工
			wm.Change_Worker();
			break;
		case 5:		//查找职工
			wm.Find_Worker();
			break;
		case 6:		//排序职工
			wm.Sort_Worker();
			break;
		case 7:		//清空所有
			wm.CLEAN();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	system("pause");
	return 0;
}