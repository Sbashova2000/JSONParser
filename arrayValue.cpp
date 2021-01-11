#include "arrayValue.h"




arrayValue::~arrayValue()
{
	clear();
}

void arrayValue::serialize(std::ostream& out, int depth)
{
	out << '[' << std::endl;
	for (int i = 0; i < array.size(); i++)
	{
		for (int j = 0; j < depth+1; j++)
		{
			out << "	";
		}
		array[i]->serialize(out, depth+1);
		out << std::endl;
		
	}
	for (int j = 0; j < depth; j++)
	{
		out << "	";
	}
	out << ']' << std::endl;

}
void arrayValue::clear()
{
	for (int i = 0; i < array.size(); i++)
	{
		delete array[i];
	}
	array.clear();
}
