#pragma once
#include "objectValue.h"
#include "arrayValue.h"
#include "Tokenizer.h"
#include <string>
#include <fstream>



class Json
{
public:
	Json();                                                         
	~Json();
	bool validate(std::string name);
	bool read(Tokenizer&, objectValue*); 
	void print(std::vector<std::string>& key);
	void changeObject(std::vector<std::string>& key, std::string& valueName);
	void createObject(std::vector<std::string>& key,  std::string& valueName);  
	void deleteElement(std::vector<std::string>& key);
	void replaceElement(std::vector<std::string> & keyFrom, std::vector<std::string>& keyTo);

	void open(std::string&); 
	void close();
	void save(std::vector<std::string>& key, std::ostream& stream); 
	void help();

private:
	bool valid;
	objectValue base;
	Value* search(std::vector<std::string>& key);
	arrayValue* readArray(Tokenizer&) ;
	Json(const Json&);
	Json& operator=(const Json&);

};