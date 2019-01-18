#include "MyData.h"


MyData::MyData(int number) {
	this->number = number;
	this->name.Format(_T("Number : %d"), number);
}

int MyData::GetNumber() {
	return number;
}

CString MyData::GetName() {
	return name;
}

void MyData::SetName(CString name) {
	this->name = name;
}