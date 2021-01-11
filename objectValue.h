#pragma once
#include "Value.h"

class objectValue : public Value
{
public:
	
	~objectValue();
	objectValue() { type = "object"; };
	void serialize(std::ostream&, int depth);
	void clear();

	std::unordered_map <std::string, Value*> map; 
private:
	objectValue(const objectValue&);
	objectValue& operator=(const objectValue&);

};
