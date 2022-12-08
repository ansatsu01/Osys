#include <iostream>
#include <sstream>

int main()
{
    int n, sum = 0;
    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);
    while (ss >> n) {
        sum += n;
    }
    std::cout << sum << std::endl;
    return 0;
}
