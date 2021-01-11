#include "numberValue.h"



numberValue::~numberValue()
{
	clear();
}

void numberValue::serialize(std::ostream& out, int depth)
{
	out << data << ",";
}

void numberValue::clear()
{
	data = 0;
}