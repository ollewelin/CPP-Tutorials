
#include <iostream>
#include <stdio.h>
#include <typeinfo>
#include <stdio.h>

class olle2
{
  public:
  void ollefunc1(void);
  int testdata[2]{15,7};
};
void olle2::ollefunc1(void)
{
  printf("ollefunc1 call\n");
  printf("testdata[0] = %d\n", testdata[0]);
  printf("testdata[1] = %d\n", testdata[1]);
}

class OW1 : public olle2
{
  int testdata2[2]{1,2};
};

class olleTest1 : public olle2
{
  public:
    template<typename T>
    class Alu :public olle2
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
  printf("**********************************\n");
  printf("Test class inheritance \n");
  printf("**********************************\n");
  OW1 objA;
  objA.ollefunc1();
  
  printf("testdata[0] = %d\n", objA.testdata[0]);
  objA.testdata[0] = 90;
  printf("testdata[0] = %d\n", objA.testdata[0]);


  printf("**********************************\n");
  printf("Templates in C++ tutorial examples\n");
  printf("with inheritance \n");
  printf("**********************************\n");
  float a = 10.2f;
  float b = 10.1f;
  float result = 0.0f;
  olleTest1 obj1;
  olleTest1 obj2;
 // olleTest1 obj4;
  olleTest1::Alu<int> obj3;
  olleTest1::Alu<float> obj4;
  
  obj2.ollefunc1();
  obj2.testdata[0] = 40;
  obj4.testdata[0] = 5;
  obj4.ollefunc1();
  obj2.ollefunc1();
 

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
