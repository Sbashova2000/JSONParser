#pragma once
#include "Value.h"

class numberValue : public Value
{
public:
	
	~numberValue();
	numberValue(double _data) : data(_data) { type = "number"; };
	void serialize(std::ostream&, int depth);
	void clear();

private:
	double data;
};
