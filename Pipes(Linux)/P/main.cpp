#include <iostream>
#include <sstream>
#include <cmath>

int main()
{
    int n;
    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);
    while (ss >> n) {
        std::cout << std::pow(n, 3) << " ";
    }
    std::cout << std::endl;
}
