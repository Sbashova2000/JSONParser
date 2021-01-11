#pragma once
#include "Value.h"


class stringValue : public  Value
{
public:
	
	~stringValue();
	stringValue(std::string _data) : data(_data) { type = "string"; };
	void serialize(std::ostream&, int depth);
	void clear();

private:
	std::string data;
};