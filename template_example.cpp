
#include <iostream>
#include <stdio.h>
#include <typeinfo>


class olleTest1 
{
  public:
    template<typename T>
    class Alu
    {
      public:
      T add(T,T);
      T mul(T,T);
    };
};

template<typename T>
T olleTest1::Alu<T>::add(T a, T b)
{
  return a + b;
}

template<typename T>
T olleTest1::Alu<T>::mul(T a, T b)
{
  return a * b;
}


int main() {

  float a = 10.2f;
  float b = 10.1f;
  float result = 0.0f;
  olleTest1 obj1;
  olleTest1 obj2;
  olleTest1::Alu<int> obj3;
  olleTest1::Alu<float> obj4;
  printf("Test template int add\n");
  result = (float)obj3.add(a, b);
  printf("a + b = %f\n", result);
  result = (float)obj3.mul(a, b);
  printf("a * b = %f\n", result);
  printf("Test template float add\n");
  result = (float)obj4.add(a, b);
  printf("a + b = %f\n", result);
  result = (float)obj4.mul(a, b);
  printf("a * b = %f\n", result);


  printf("Type of obj3 T = ");
  const float c = 1.3f;
  std::cout << typeid(obj3.add(a, b)).name() << '\n';
  printf("Type of obj4 T = ");
  std::cout << typeid(obj4.add(a, b)).name() << '\n';
}
