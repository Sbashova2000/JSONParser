#include "Tokenizer.h"
#include <exception>
#include <iostream>


Tokenizer::Tokenizer(std::istream& _in) : in(_in) {};


Tokenizer::Token Tokenizer::nextToken(bool isArray)
{
    clearWhiteSpace();
    Tokenizer::Token result({ Tokenizer::Token::error,"",nullptr }); 
    if (in.eof()) {
        result.type = Tokenizer::Token::endOfFile;
        return result;
    }
    char c = in.peek();

    if (c == '}' || c==']')
    {
        in.get(c);
        result.type = Tokenizer::Token::close_bracket;
        clearWhiteSpace();
        if (in.peek() == ',')
        {
            in.get(c);
        }
        return result;
    }    

    if (c == '"' && isArray==false) 
    {
        in.get();
       
        while (in.peek() != '"') 
        {
            
            in.get(c); 
            result.name += c;
        }
       in.get();
    }
    else if(isArray==false) 
    {
        result.type = Tokenizer::Token::error;
        return result;
    }

    clearWhiteSpace(); 

    if (in.peek() != ':' && isArray == false)
    {
        result.type = Tokenizer::Token::error;
        return result;
    }
    else if(isArray == false)
    {
        in.get();
    }

    clearWhiteSpace();
    c = in.peek();
   


    if (std::isdigit(c))
    {
        double temp;
        in >> temp; 
        result.type = Tokenizer::Token::number;
        result.val = new numberValue(temp);
    }
    else if (c == '"')
    {
        std::string value;
        in.get();
        
        while (in.peek() != '"') 
        {
            in.get(c); 
            
            if (c =='\\')    
            {
                value += c;
                in.get(c);
            }
            value += c;
        }
        in.get();
       
        result.type = Tokenizer::Token::string;
        result.val = new stringValue(value); 

    }
    else if (c == '{')       
    {
        in.get(c);
        result.type = Tokenizer::Token::open_bracket;
    }
    else if (c == '[')                                
    {
         in.get(c);
         result.type = Tokenizer::Token::open_array_bracket;
    }
   
    clearWhiteSpace();

    if (in.peek() == ',')
    {
        in.get(c);
    }
    
    return result;
}

//Функция, която изчиства празното пространство и някои символи
void Tokenizer::clearWhiteSpace()
{
    while (in && (in.peek() <= 32 || in.peek()== '\n' || in.peek() == ' ' || in.peek()=='\t') ) 
    {
        in.get();
    }
}

//Функция, която връща на кой символ е курсора в момента на четене. Помага за по-лесното откриване на грешки.
int Tokenizer::getPosition()
{
    return in.tellg(); 
}