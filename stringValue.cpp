#include "stringValue.h"


stringValue::~stringValue()
{
	clear();
}

//���� ������� �� ��������, �� �� ���� �������(��������) �� �� ������� ��� ����
void stringValue::serialize(std::ostream& out, int depth)
{
	out << '"' << data << '"' << ",";
}

void stringValue::clear()
{
	data = "";
	delete this;
}