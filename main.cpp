#include <iostream>
#include "SHA256.h"

using namespace std;

int main()
{
    SHA256 obj("");
    obj.Convert();
    obj.PrintDigest();
    string digest=obj.GetDigest();
    //Tramite i file
    obj.FromFile("myfile.txt");
    obj.Convert();
    obj.SaveFile();
    obj.PrintDigest();

    return 0;
}
