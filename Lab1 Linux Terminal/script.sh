g++ -c -o StaticLib/StaticLib.o StaticLib/library.cpp
ar rvs StaticLib/libNumber.a StaticLib/StaticLib.o
g++ -c -o Vector/Vector.o Vector/vector.cpp -IStaticLib -LStaticLib -lStaticLib -fPIC
g++ -shared -o Vector/libVector.so Vector/Vector.o -fPIC
g++ -o main Main/main.cpp -IStaticLib -IVector ./StaticLib/libNumber.a ./Vector/libVector.so
./main

