#include "ReverieEngine/Core/Core.h"

#include <iostream>

using namespace ReverieEngine::Core;
    
void PrintHelloWorld()
{
    std::cout << "Hello World!\n";
    std::cin.get();
}

void Print(const std::string& message)
{
    std::cout << message << '\n';
}
