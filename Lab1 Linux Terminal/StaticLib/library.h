#ifndef STATICLIB_LIBRARY_H
#define STATICLIB_LIBRARY_H

#include <ostream>
#include <cmath>
namespace MathLibrary {

    class Numbers {
    private:
        double num;
    public:
        Numbers() {
            this->num = 0.0;
        }
        Numbers(double n);
        Numbers operator+(Numbers right);
        Numbers operator-(Numbers right);
        Numbers operator*(Numbers right);
        Numbers operator/(Numbers right);
        void setValue(double value);
        double GetValue() {
            return num;
        }
        friend std::ostream& operator<<(std::ostream& out, const Numbers& n);
    };

    static Numbers CreateNumber(double n) {
        Numbers a(n);
        return a;
    }

    static Numbers Sqrt(Numbers& value) {
        Numbers result(sqrt(value.GetValue()));
        return result;
    }
    static Numbers ONE = CreateNumber(1);
    static Numbers ZERO = CreateNumber(0.0);

}

#endif //STATICLIB_LIBRARY_H
