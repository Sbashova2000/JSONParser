#pragma once
#include "Value.h"


class arrayValue : public Value
{
public:
	
	
	~arrayValue();
	arrayValue() { type = "array"; };
	void serialize(std::ostream&, int depth);
	void clear();

	std::vector<Value*> array;
	
private:
	arrayValue(const arrayValue&);
	arrayValue& operator=(const arrayValue&);

};