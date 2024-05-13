#ifndef SHA256_Class
#define SHA256_Class

#include <iostream>
#include <string.h>
#include <bitset>
#include <vector>
#include <iomanip>

using namespace std;
class SHA256
{
public:
     SHA256(string _original):original(_original){}
     ~SHA256(){}
     void SetText(string text);
     void Convert();
     SHA256& operator=(const string& text);
     void PrintDigest();
     string GetDigest();

private:
    string GetOr(){return original;}
     string original;
     string digest;


};

//Function
 void InitializeH(uint32_t *h);
 vector<uint32_t> splitBinaryString(const string& binaryString);
 string stringToBinary(const string& text);
 string uint32ToBinaryString(uint32_t num);
 string uint64ToBinaryString(uint64_t num);
 string uint32ToBinaryString(uint32_t num);
 string uint64ToBinaryString(uint64_t num);
 void ExtendVector(vector<uint32_t> &w,int n);
 uint32_t rot(uint32_t input,int n,int option);
 uint32_t shift(uint32_t input,int n,int option);
 uint32_t op1(uint32_t input);
 uint32_t op2(uint32_t input);
 uint32_t op3(uint32_t input);
 uint32_t op4(uint32_t input);
 void CopyVector(vector<uint32_t> &v,vector<uint32_t> &original,int start,int n);
 void CreateBlock(vector<vector<uint32_t>> &block,vector<uint32_t> &w);





#endif // SHA256_Class
