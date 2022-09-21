#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <library.h>

class  Vector {
private:
    MathLibrary::Numbers x;
    MathLibrary::Numbers y;
public:
    Vector();
    Vector(MathLibrary::Numbers x_, MathLibrary::Numbers y_);
    Vector(double x_, double y_);
    MathLibrary::Numbers RadiusinPolarCoord();
    MathLibrary::Numbers CosInPolarCoord();
    Vector operator+(Vector right);
    MathLibrary::Numbers Get_X();
    MathLibrary::Numbers Get_Y();
};

extern const Vector ZERO;
extern const  Vector ONE;

#endif //VECTOR_VECTOR_H
