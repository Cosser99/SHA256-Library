#include <iostream>

#include "SHA256.h"
using namespace std;


int main()
{
    SHA256 a("a");
    a.Convert();
    a.PrintDigest();
}
