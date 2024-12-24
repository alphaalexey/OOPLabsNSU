#include <iostream>

#include "module1.h"
#include "module2.h"
#include "module3.h"

using namespace std;

int main(int argc, char** argv)
{
    std::cout << "Hello world!" << std::endl;
    
    cout << Module1::getMyName() << std::endl;
    std::cout << Module2::getMyName() << std::endl;

    using namespace Module1;
    std::cout << getMyName() << std::endl; // (A)
    std::cout << Module2::getMyName() << std::endl;

    //using namespace Module2; // (B)
    //std::cout << getMyName() << std::endl; // COMPILATION ERROR (C)

    using Module2::getMyName;
    std::cout << getMyName() << std::endl; // (D)

    std::cout << Module3::getMyName() << std::endl;
}
