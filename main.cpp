
#include <iostream>
#include "Tokenizer.h"
#include "Json.h"
#include <fstream>
#include <vector>


int main()
{
    std::string command;
    std::cout << "Please, enter a command" << std::endl;
    Json jp;
   
    while (std::cin >> command && command != "stop")
    {
        if (command == "validate")
        {
            std::string filename;
            std::cin >> filename;
            
            if (jp.validate(filename) != 0)
            {
                std::cout << " The JasonParser is valid! " << std::endl;
                std::cout << "Please, enter a command" << std::endl;
            }
            else
            {
                std::cout << " The JasonParser is NOT Valid! \n";
                std::cout << "Please, try again!" << std::endl;
            }
          
        }
        else  if (command == "print") 
        {
            std::vector<std::string> key;
            std::string keyWord;                    
            std::cin >> keyWord;
            
            //символ за край 

            while (keyWord != "@") {
                key.push_back(keyWord);  
                std::cin >> keyWord;
            }
            jp.print(key);
            std::cout << "Please, enter a command" << std::endl;
        }
        else if (command == "changeObject")
        {
            std::vector<std::string> key;
            std::string keyWord;
            std::string value;
            std::cin >> keyWord;

            while (keyWord != "@") {
                key.push_back(keyWord);
                std::cin >> keyWord;
            }
            std::getline(std::cin, value);
            jp.changeObject(key, value);
            std::cout << "Please, enter a command" << std::endl;
        }
        else  if (command == "createObject")
        {
            std::vector<std::string> key;
            std::string keyWord;
            std::string value;
            std::cin >> keyWord;

            while (keyWord != "@") {
                key.push_back(keyWord);
                std::cin >> keyWord;
            }
            std::getline(std::cin,value);
            jp.createObject(key, value);
            std::cout << "Please, enter a command" << std::endl;
        }
        else  if (command == "deleteElement")
        {
            std::vector<std::string> key;
            std::string keyWord;
            std::cin >> keyWord;

            while (keyWord != "@") {
                key.push_back(keyWord);
                std::cin >> keyWord;
            }
           
            jp.deleteElement(key);
            std::cout << "Please, enter a command" << std::endl;
        }
        else  if (command == "replaceElement")
        {
            std::vector<std::string> keyFrom, keyTo;
            std::string keyWord;
            std::cin >> keyWord;
            while (keyWord != "@") {
                keyFrom.push_back(keyWord);
                std::cin >> keyWord;
            }

            std::cin >> keyWord;

            while (keyWord != "@") {
                keyTo.push_back(keyWord);
                std::cin >> keyWord;
            }

            jp.replaceElement(keyFrom, keyTo);
            std::cout << "Please, enter a command" << std::endl;
        }
        else  if (command == "open")
        {
            std::string filename;
            std::cin >> filename;
            jp.open(filename);
            std::cout << std::endl;
            std::cout << " Please, enter a command " << std::endl;
            std::cout << std::endl;
        }
        else if (command == "close")
        {
            jp.close();
            std::cout << std::endl;
            std::cout << " Please, enter a command " << std::endl;
            std::cout << std::endl;
        }
        else if (command == "save")
        {
            std::vector<std::string> key;
            std::string keyWord;
            std::cin >> keyWord;

            while (keyWord != "@") {
                key.push_back(keyWord);
                std::cin >> keyWord;
            }
            std::string filename;
            std::cin >> filename;
            std::ofstream file(filename);
            jp.save(key, file); 
            std::cout << std::endl;
            std::cout << " Please, enter a command " << std::endl;
            std::cout << std::endl;
        }
        else if (command == "help")
        {
            std::cout << "The following commands are supported: " << std::endl;
            std::cout << "open <file>       opens <file> " << std::endl;
            std::cout << "close             closes currently opened file " << std::endl;
            std::cout << "save              saves the currently opened file" << std::endl;
            std::cout << "help              prints the information" << std::endl;
            std::cout << "exit              exists the program " << std::endl;
            jp.help();
           
        }
        else if (command == "exit")
        {
            std::cout << "Exit!" << std::endl;

            break;
        }
       
    }
    return 0;
}