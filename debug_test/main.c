#include <iostream>

int add(int a, int b) {
    int ret = a + b;
    for(int i=0;i<10;i++)
    {
        ret++;
    }
    return ret;
}
int main() {
    int x = 2;
    int y = 3;
    int z = add(x, y);
    std::cout << z << std::endl;
    z = add(x, z);
    std::cout << z << std::endl;
    return 0;
}