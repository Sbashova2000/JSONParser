#include "objectValue.h"




objectValue::~objectValue()
{
	clear();
}


void objectValue::serialize(std::ostream& out, int depth)
{
	depth++; 
	out << "{" << std::endl;
	for (std::pair < std::string, Value* > item : map) 
	{
		for (int i = 0; i < depth; i++)
		{
			out << "	"; 
		}

		out << '"' << item.first << '"' << " : "; 
		item.second->serialize(out, depth);
		out << std::endl;
	}

	for (int i = 0; i < depth; i++)
	{
		out << "	"; 
	}
	out << "}";

}

void objectValue::clear()
{
	for (std::pair < std::string, Value* > item : map)
	{	
		delete item.second; 
	}
	map.clear();  
}