#include <iostream>

void ret2nums(int x, int &n1, int &n2);

int main(int argc, char const *argv[])
{
    int n1, n2;
    ret2nums(5,n1,n2);
    std::cout<<n1<<' '<<n2;
}

void ret2nums(int x, int &n1, int &n2)
{
    n1 = x-1;
    n2 = x+1;
}
