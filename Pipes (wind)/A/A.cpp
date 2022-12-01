#include <iostream>
#include <sstream>

int main()
{
    int n, num = 4;
    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);
    while (ss >> n) {
        std::cout << n + num << " ";
    }
    std::cout << std::endl;
    return 0;
}