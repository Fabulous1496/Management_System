#include"Manager.h"
Manager::Manager(int ID, string name, int dID)
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_DeptID = dID;
}

void Manager::showInfo()
{
	cout <<"职工编号： " << this->m_ID
		<< "\t职工姓名： " << this->m_Name
		<< "\t岗位： " << this->getDeptName()
		<< "\t职责：完成老板交代的任务" << endl;
}

string Manager::getDeptName()
{
	return string("经理");
}