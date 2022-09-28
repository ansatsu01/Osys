#pragma once

#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif // VECTOR_EXPORTS

#include "Numbers.h"

class VECTOR_API Vector {
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

extern const VECTOR_API Vector ZERO;
extern const VECTOR_API Vector ONE;
