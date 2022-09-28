#include <iostream>
#include <vector.h>

int main() {
    MathLibrary::Numbers n1(1), n2(5.4);
    Vector v1(3, 4);
    Vector v2(1, 1);
    std::cout << "n1 + n2 = " << n1 + n2 << std::endl;
    std::cout << "n1 - n2 = " << n1 - n2 << std::endl;
    std::cout << "n1 * n2 = " << n1 * n2 << std::endl;
    std::cout << "n1 / n2 = " << n1 / n2 << std::endl;
    std::cout << "Vector v1 : (" << v1.Get_X() << ", " << v1.Get_Y() << ")" << std::endl;
    std::cout << "v1 in polar coordinates:" << std::endl;
    std::cout <<"radius: " << v1.RadiusinPolarCoord() << std::endl;
    std::cout << "cos: " << v1.CosInPolarCoord() << std::endl;
    std::cout << "sum of v1 and v2 :" << "(" <<(v1 + v2).Get_X() << ", " << (v1 + v2).Get_Y() << ")" << std::endl;
    return 0;
}
