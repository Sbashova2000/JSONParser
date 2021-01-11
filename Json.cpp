#include "Json.h"
#include <sstream>

Json::Json() {

}

Json::~Json() {
    base.clear();
}

//функция, която проверява дали файлът, който сме подали е валиден спрямо граматиката на “JSON”
bool Json::validate(std::string name)
{
    std::ifstream file;
    file.open(name);
    file.get(); 
    objectValue* temp = new objectValue();
    Tokenizer tokenizer(file);
    bool result =  read(tokenizer, temp);
    temp->clear();
    delete temp;
    return result;
}


bool Json::read(Tokenizer& tokenizer, objectValue* object)
{
    Tokenizer::Token result = tokenizer.nextToken(false);
    while (result.type != Tokenizer::Token::close_bracket)
    {
        bool isArray;
        if (result.type == Tokenizer::Token::error)
        {
            std::cerr << "Parsing error on line!" << tokenizer.getPosition();
            return false;
        }
        if (result.type == Tokenizer::Token::open_bracket)
        {
            isArray = false;
            objectValue*  newObject = new objectValue(); 
            read(tokenizer, newObject); 
            object->map[result.name] = newObject;
        }
        else if (result.type == Tokenizer::Token::open_array_bracket)
        {
            isArray = true;
            arrayValue* newObject = readArray(tokenizer);
            
            object->map[result.name] = newObject;
        }
        else
        {
            object->map[result.name] = result.val;
        }
        result = tokenizer.nextToken(false);
    } 
    return true;    
}

arrayValue* Json::readArray(Tokenizer& tokenizer)
{
    arrayValue* resultValue = new arrayValue;
    Tokenizer::Token result = tokenizer.nextToken(true);
    while (result.type != Tokenizer::Token::close_bracket)
    {
        bool isArray;
        if (result.type == Tokenizer::Token::error)
        {
            std::cerr << "Parsing error on line!" << tokenizer.getPosition();
            return nullptr;
        }
        if (result.type == Tokenizer::Token::open_bracket)
        {
            isArray = false;
            objectValue* newObject = new objectValue(); 
            read(tokenizer, newObject); 
            resultValue->array.push_back(newObject);
        }
        else if (result.type == Tokenizer::Token::open_array_bracket)
        {
            isArray = true;
            arrayValue* newObject = readArray(tokenizer);
            resultValue->array.push_back(newObject);
        }
        else
        {
            resultValue->array.push_back(result.val);
        }
        
        result = tokenizer.nextToken(true);
    }
    return resultValue;
}


//Извежда на екрана съдържанието на обекта в четлив вид.
void  Json::print(std::vector<std::string>& key)
{
   Value* object = search(key); 
   if (object != nullptr)
   {
       object->serialize(std::cout,key.size()- 1); 
   }
}

Value* Json::search(std::vector<std::string>& key) 
{
    
    if (key.size() == 0)
    {
        return &base;
    }
    objectValue* current = &base;    

    for (int i = 0; i < key.size() - 1; i++) {

        current = (objectValue*)current->map[key[i]];  
    }
   return  current->map[key.back()]; 
}

//Променя стойността на елемент на даден обект при подаване на пълен път до съответния елемент.
void Json::changeObject(std::vector<std::string>& key, std::string& valueName)
{
    Value* value;
    std::stringstream  stream(valueName); 
    Tokenizer tokenizer(stream); 
    Tokenizer::Token result;

    result = tokenizer.nextToken(false); 
    if (result.type == Tokenizer::Token::open_bracket)
    {
        objectValue* newValue = new objectValue();
        read(tokenizer, newValue);
        value = newValue;
    }
    else
    {
        value = result.val;
    }
    
    objectValue* parent = (objectValue*) search(key);  
    
    if (parent != nullptr)
    {
        
        delete parent->map[result.name];
        parent->map[result.name] = value;  
       
    }
}

//При подаване на пълен път към даден елемент и символен низ добавя елементът 
//и му присвоява прочетената според синтаксиса на “JSON” стойност на низа
void Json::createObject(std::vector<std::string>& key, std::string& valueName) 
{
    Value* value;
    std::stringstream  stream(valueName); 
    Tokenizer tokenizer(stream);
    Tokenizer::Token result;
    
    result=tokenizer.nextToken(false); 
    if (result.type == Tokenizer::Token::open_bracket)
    {
        objectValue* newValue = new objectValue();
        read(tokenizer, newValue);
        value = newValue;
    }
    else
    {
        value = result.val;
    }
   
    Value* parent= search(key);  
    if (parent != nullptr && parent->type == "object")
    {
      ( (objectValue*) parent) -> map[result.name] = value;  
    }
    else
    {
        std::cout << "It`s not successful!" << std::endl;
    }
}

//При подаване на пълен път до даден елемент, изтрива елемента
void Json::deleteElement(std::vector<std::string>& key)
{
    if (key.size() < 1)
    {
        base.clear();
    }
    std::string name = key.back();
    key.pop_back();
    Value* parent = search(key);
    if (parent != nullptr && parent->type == "object")
    {
        ((objectValue*)parent)->map[name]->clear();
        delete ((objectValue*)parent)->map[name];   
        ((objectValue*)parent)->map.erase(name);  
        std::cout << "Siccessfully deleted!" << name << std::endl;
    }
    else
    {
        std::cout << "It`s not successful!" <<std:: endl;
    }
}

//	При подаване на два пътя, всички елементи, намиращи се на първия път се преместват на втория
void Json::replaceElement(std::vector<std::string>& keyFrom, std::vector<std::string>& keyTo)
{
    
    if (keyFrom.size() < 1)
    {
        return;
    }
    std::string nameFrom = keyFrom.back(); 
    keyFrom.pop_back();                    
    Value* fromParent = search(keyFrom);
    if (fromParent != nullptr && fromParent->type == "object")
    {
        Value* fromValue = ((objectValue*)fromParent)->map[nameFrom]; 
        ((objectValue*)fromParent)->map.erase(nameFrom); 

        std::string nameTo = keyTo.back();
        deleteElement(keyTo);
        Value* toParent = search(keyTo);
        if (toParent != nullptr && toParent->type == "object")
        {
           ((objectValue*)toParent)->map[nameFrom] = fromValue;
            std:: cout << nameTo;
        }
       
    }

}

void Json::open(std::string& filename)
{
    std::ifstream file;
    file.open(filename);
    file.get(); 
    Tokenizer tokenizer(file);
    read(tokenizer,&base);
   
}
void Json::close()
{
    base.clear();
}

void  Json::save(std::vector<std::string>& key, std::ostream& stream)
{
    Value* object = search(key); 
    if (object != nullptr)
    {
        object->serialize(stream, key.size()-1); 
    }
}

void Json::help()
{

    std::cout << "validate          checks if the Json file is valid "          << std::endl;
    std::cout << "read              reads Json file " << std::endl;
    std::cout << "print             prints the content of the file about Json " << std::endl;
    std::cout << "changeObject      changes the value of an item in the object" << std::endl;
    std::cout << "createObject      creates a new object"                       << std::endl;
    std::cout << "deleteElement     deletes an element "                        << std::endl;
    std::cout << "replaceElement    replaces elements from one place to another"<< std::endl;
   
}