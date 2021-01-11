#include "stringValue.h"


stringValue::~stringValue()
{
	clear();
}

//Тази функция се използва, за да може данните(низовете) да се запишат във файл
void stringValue::serialize(std::ostream& out, int depth)
{
	out << '"' << data << '"' << ",";
}

void stringValue::clear()
{
	data = "";
	delete this;
}