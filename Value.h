#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>


//���������� ���������

struct Value
{
	virtual void serialize(std::ostream&, int depth) = 0;        
	virtual void clear() = 0;
	std::string type; 
	virtual ~Value() {};
};







