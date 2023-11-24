#include"workerManager.h"

WorkerManager::WorkerManager()
{
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		this->m_WorkerNum = 0;
		this->m_WorkerArray = NULL;
		this->isEmpty = true;
		ifs.close();
		return;
	}
	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->m_WorkerNum = 0;
		this->m_WorkerArray = NULL;
		this->isEmpty = true;
		ifs.close();
		return;
	}
	//读取现有文件
	int num = this->get_Num();
	this->m_WorkerNum = num;
	this->m_WorkerArray = new Worker * [this->m_WorkerNum];
	this->initalize();
}

void WorkerManager::Show_Meau()
{
	cout << "-------------------------------------\n";
	cout << "-------------------------------------\n";
	cout << "--------欢迎使用职工管理系统！-------\n";
	cout << "------------0.退出管理系统-----------\n";
	cout << "------------1.添加职工信息-----------\n";
	cout << "------------2.显示职工信息-----------\n";
	cout << "------------3.删除离职职工-----------\n";
	cout << "------------4.修改职工信息-----------\n";
	cout << "------------5.查找职工信息-----------\n";
	cout << "------------6.按照工号排序-----------\n";
	cout << "------------7.清空所有文档-----------\n";
	cout << "-------------------------------------\n";
	cout << "-------------------------------------\n";
	cout << endl;
}

WorkerManager::~WorkerManager()
{
	if (this->m_WorkerArray != NULL)
	{
		for (int i = 0; i < this->m_WorkerNum; i++)
		{
			if (this->m_WorkerArray[i] != NULL)
			{
				delete this->m_WorkerArray[i];
				this->m_WorkerArray[i] = NULL;
			}
		}
		delete[]this->m_WorkerArray;
		this->m_WorkerArray = NULL;
	}
}

void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::AddWorker()
{
	cout << "请输入添加数量！" << endl;
	int AddNum = 0;
	cin >> AddNum;
	if (AddNum > 0)
	{
		//计算新空间大小
		int newSize = this->m_WorkerNum + AddNum;
		//开辟新空间
		Worker** newspace = new Worker * [newSize];
		//将原有数组拷贝
		if (this->m_WorkerArray != NULL)
		{
			for (int i = 0; i < this->m_WorkerNum; i++)
			{
				newspace[i] = this->m_WorkerArray[i];
			}
		}
		//批量添加
		for (int i = 0; i < AddNum; i++)
		{
			int id;
			string name;
			int Dselect;
			cout << "请输入第" << i + 1 << "个新职工编号： " << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名： " << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "个新职工岗位： " << endl;
			cout << "1.普通职工\n" << "2.经理\n" << "3.老板\n";
			cin >> Dselect;

			Worker* worker = NULL;
			switch (Dselect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			newspace[this->m_WorkerNum + i] = worker;
		}
		delete[] this->m_WorkerArray;
		this->m_WorkerArray = newspace;
		this->m_WorkerNum = newSize;
		cout << "添加成功！" << endl;
		this->Save();
		this->isEmpty = false;
	}
	else
	{
		cout << "输入有误！"<< endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_WorkerNum; i++)
	{
		ofs << this->m_WorkerArray[i]->m_ID << " "
			<< this->m_WorkerArray[i]->m_Name << " "
			<< this->m_WorkerArray[i]->m_DeptID << endl;
	}
	ofs.close();
}

int WorkerManager::get_Num()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int ID;
	string name;
	int dID;
	int num = 0;
	while (ifs >> ID && ifs >> name && ifs >> dID)
	{
		num++;
	}
	ifs.close();
	return num;
}

void WorkerManager::initalize()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int ID;
	string name;
	int dID;
	int index = 0;
	while (ifs >> ID && ifs >> name && ifs >> dID)
	{
		Worker* worker = NULL;
		if (dID == 1)
		{
			worker = new Employee(ID, name, dID);
		}
		if (dID == 2)
		{
			worker = new Manager(ID, name, dID);
		}
		if (dID == 3)
		{
			worker = new Boss(ID, name, dID);
		}
		this->m_WorkerArray[index] = worker;
		index++;
	}
}

void WorkerManager::Show_Worker()
{
	if (this->isEmpty)
	{
		cout << "列表为空！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		for (int i = 0; i < this->m_WorkerNum; i++)
		{
			this->m_WorkerArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::isExist(int ID)
{
	int index = -1;
	for (int i = 0; i < this->m_WorkerNum; i++)
	{
		if (this->m_WorkerArray[i]->m_ID == ID)
		{
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::Delete_Worker()
{
	if (this->isEmpty)
	{
		cout << "列表为空！" << endl;
	}
	else
	{
		cout << "请输入工号！" << endl;
		int ID;
		cin >> ID;
		if (this->isExist(ID) != -1)
		{
			for (int i = this->isExist(ID); i < this->m_WorkerNum - 1; i++)
			{
				this->m_WorkerArray[i] = this->m_WorkerArray[i + 1];
			}
			this->m_WorkerNum--;
			this->Save();
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "未查此人！" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Change_Worker()
{
	if (this->isEmpty)
	{
		cout << "列表为空！" << endl;
	}
	else
	{
		cout << "请输入工号" << endl;
		int ID;
		cin >> ID;
		if (this->isExist(ID) != -1)
		{
			int index = this->isExist(ID);
			cout << "匹配成功： " << endl;
			this->m_WorkerArray[index]->showInfo();
			delete this->m_WorkerArray[index];
			int newID = 0;
			string newName;
			int dID = 0;
			cout << "请输入新工号： " << endl;
			cin >> newID;
			cout << "请输入新姓名： " << endl;
			cin >> newName;
			cout << "请输入岗位：" << endl;
			cin >> dID;
			Worker* worker = NULL;
			switch (dID)
			{
			case 1:
				worker = new Employee(newID, newName, dID);
				break;
			case 2:
				worker = new Manager(newID, newName, dID);
				break;
			case 3:
				worker = new Boss(newID, newName, dID);
			default:
				break;
			}
			this->m_WorkerArray[index] = worker;
			cout << "修改成功！" << endl;
			this->Save();
		}
		else
		{
			cout << "查无此人！" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Find_Worker()
{
	if (this->isEmpty)
	{
		cout << "列表为空！" << endl;
	}
	else
	{
		cout << "请输入工号！" << endl;
		int ID;
		cin >> ID;
		int index = this->isExist(ID);
		if (index != -1)
		{
			cout << "查找成功，信息如下：" << endl;
			this->m_WorkerArray[index]->showInfo();
		}
		else
		{
			cout << "查无此人！" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Worker()
{
	if (this->isEmpty)
	{
		cout << "列表为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_WorkerNum; i++)
		{
			for (int j = 0; j < this->m_WorkerNum - 1 - i; j++)
			{
				Worker* temp;
				if (this->m_WorkerArray[j]->m_ID > this->m_WorkerArray[j + 1]->m_ID)
				{
					temp = this->m_WorkerArray[j];
					this->m_WorkerArray[j] = this->m_WorkerArray[j + 1];
					this->m_WorkerArray[j + 1] = temp;
				}
			}
		}
		this->Save();
		cout << "排序完成！" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::CLEAN()
{
	cout << "确定清空？您将会失去所有信息！" << endl;
	cout << "1.确定" << endl << "2.取消" << endl;
	int choice = 0;
	cin >> choice;
	if (choice == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_WorkerArray != NULL)
		{
			for (int i = 0; i < this->m_WorkerNum; i++)
			{
				if (this->m_WorkerArray[i] != NULL)
				{
					delete this->m_WorkerArray[i];
					this->m_WorkerArray[i] = NULL;
				}
			}
			delete[]this->m_WorkerArray;
			this->m_WorkerArray = NULL;
			this->m_WorkerNum = 0;
			this->isEmpty = true;
		}
		cout << "清空完成！" << endl;
	}
	system("pause");
	system("cls");
}
