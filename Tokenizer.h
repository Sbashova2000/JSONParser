#pragma once
#include <string>
#include <iostream>
#include "stringValue.h"
#include "numberValue.h"



class Tokenizer
{
public:

	struct Token
	{
		enum TokenType{number, string, doubleColon,comma, open_bracket, close_bracket, error,endOfFile,open_array_bracket}; 
		TokenType type;
		std::string name;
		Value* val;
	};

	Tokenizer(std::istream&);

	Token nextToken(bool isArray);
	int getPosition();

private:
	std::istream& in;
	void clearWhiteSpace();
};

