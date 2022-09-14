#include "Numbers.h"
namespace MathLibrary {
	Numbers::Numbers(double n) {
		this->num = n;
	}
	Numbers Numbers::operator+(Numbers right) {
		return Numbers(this->num + right.num);
	}
	Numbers Numbers::operator-(Numbers right) {
		return Numbers(this->num - right.num);
	}
	Numbers Numbers::operator*(Numbers right) {
		return Numbers(this->num * right.num);
	}
	Numbers Numbers::operator/(Numbers right) {
		return Numbers(this->num / right.num);
	}
	void Numbers::setValue(double value) {
		this->num = value;
	}
	std::ostream& operator<<(std::ostream& out, const Numbers& n) {
		return out << n.num;
	}
}