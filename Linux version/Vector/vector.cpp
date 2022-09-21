#include "vector.h"

const Vector ZERO = Vector(0.0, 0.0);
const Vector ONE = Vector(1,1);

Vector::Vector() {
    this->x = MathLibrary::CreateNumber(0);
    this->y = MathLibrary::CreateNumber(0);
}

Vector::Vector(MathLibrary::Numbers x_, MathLibrary::Numbers y_) {
    this->x = x_;
    this->y = y_;
}
Vector::Vector(double x_, double y_) {
    this->x = MathLibrary::CreateNumber(x_);
    this->y = MathLibrary::CreateNumber(y_);
}

MathLibrary::Numbers Vector::RadiusinPolarCoord() {
    MathLibrary::Numbers result = (this->x * this->x) + (this->y * this->y);
    return MathLibrary::Sqrt(result);
}

MathLibrary::Numbers Vector::CosInPolarCoord() {
    return this->x / RadiusinPolarCoord();
}
MathLibrary::Numbers Vector::Get_X(){
    return this->x;
}
MathLibrary::Numbers Vector::Get_Y() {
    return this->y;
}
Vector Vector::operator+(Vector right) {
    return(Vector(x + right.x, y + right.y));
}
