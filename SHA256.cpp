#include "SHA256.h"
 void SHA256::SetText(string text)
 {
     original=text;
 }


 SHA256& SHA256::operator=(const string& text)
 {
     original=text;
     return *this;
 }

 void InitializeH(uint32_t *h)
{
    h[0] = 0x6a09e667;
    h[1] = 0xbb67ae85;
    h[2] = 0x3c6ef372;
    h[3] = 0xa54ff53a;
    h[4] = 0x510e527f;
    h[5]= 0x9b05688c;
    h[6] = 0x1f83d9ab;
    h[7] = 0x5be0cd19;
    return;
}
vector<uint32_t> splitBinaryString(const string& binaryString) {
    vector<uint32_t> result;
    size_t length = binaryString.length();
    size_t numBlocks = (length + 31) / 32; // Numero di blocchi di 32 bit necessari

    // Itera su ciascun blocco di 32 bit e converte in uint32_t
    for (size_t i = 0; i < numBlocks; ++i) {
        size_t start = i * 32;
        size_t end = start + 32;
        if (end > length) {
            end = length;
        }
        string block = binaryString.substr(start, end - start);
        // Aggiungi zero a sinistra se la lunghezza è inferiore a 32
        block = string(32 - block.length(), '0') + block;
        result.push_back(bitset<32>(block).to_ulong());
    }
    return result;
}

string stringToBinary(const string& text) {
    string binaryString;
    for (char c : text) {
        // Converti ogni carattere in binario e aggiungilo alla stringa binaria
        binaryString +=bitset<8>(c).to_string();
    }
    return binaryString;
}

uint32_t rot(uint32_t input,int n,int option) //0 LEFT 1 RIGHT
{
  if(option!=1&&option!=0) {cout<<"ERROR SHIFT"<<endl;exit(1);}
  uint32_t tmp=input;
  int bit=32;
  if(option)
       input=(tmp >> n)|(tmp << (bit - n));
  else
      input=(tmp << n)|(tmp >> (bit - n));
  return input;
}
uint32_t shift(uint32_t input,int n,int option)  //0 LEFT 1 RIGHT
{
  if(option!=1&&option!=0) {cout<<"ERROR SHIFT"<<endl;exit(1);}
  uint32_t tmp=input;
  if(option)
    tmp=tmp>>n;
  else
    tmp=tmp<<n;
  return tmp;

}
uint32_t op1(uint32_t input)
{
    uint32_t tmp=input;
    return rot(tmp,7,1)^rot(tmp,18,1)^shift(tmp,3,1);
}
uint32_t op2(uint32_t input)
{
    uint32_t tmp=input;
    return rot(tmp,17,1)^rot(tmp,19,1)^shift(tmp,10,1);
}
//Main loop operation
uint32_t op3(uint32_t input)
{
    uint32_t tmp=input;
    return rot(tmp,2,1)^rot(tmp,13,1)^rot(tmp,22,1);
}
uint32_t op4(uint32_t input)
{
    uint32_t tmp=input;
    return rot(tmp,6,1)^rot(tmp,11,1)^rot(tmp,25,1);
}

string Uint32ToHexString(uint32_t value)
{
    stringstream ss;
    ss<<hex<<setw(8)<<setfill('0')<<value;
    return ss.str();
}
void CreateBlock(vector<vector<uint32_t>> &block,vector<uint32_t> &w)
{
    int nblock=w.size()/16;
    if(w.size()%16>0)nblock+=1;
    for(int i=0;i<nblock;i++)
    {
            vector<uint32_t> tmp;
            block.push_back(tmp);
            block[i].assign(w.begin()+i*16,w.begin()+(i+1)*16);
    }
}
void SHA256::Convert()
{
    uint32_t *h=(uint32_t*)calloc(8,sizeof(uint32_t));
    InitializeH(h);
    uint32_t k[64] = {
       0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
       0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
       0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
       0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
       0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
       0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
       0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
       0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    string message = this->original;

    string binmsg = stringToBinary(message);
    uint64_t l=binmsg.length();
    //append 1 bit
    binmsg+='1';
    //append 0 until 448
    int nblock=(l+1)/512;
    int resto=(l+1)%512;
    for(int i=resto;i<448;i++) //FORSE NON BISOGNA USARE IL RESTO QUI
    {
        binmsg+='0';
    }
    //append length
    binmsg+=bitset<64>(l).to_string();
    //TODO: aggiungere i reserve qui
    vector<uint32_t> w=splitBinaryString(binmsg);

    vector<vector<uint32_t>> Block;
    //Break message into 512 chunk
    CreateBlock(Block,w);
    //Per ogni blocco
    nblock=Block.size();
    for(int i=0;i<nblock;i++)
    {
        //ESTRAGGO LA WORD
        w=Block[i];
        //Estensione fino a 64 righe totali
        w.insert(w.end(),64-16,0);
        //Operazione
        for(int i=16;i<64;i++)
        {
            uint32_t a1=op1(w[i-15]);
            uint32_t a2=op2(w[i-2]);
            w[i]=w[i-16]+a1+w[i-7]+a2;
        }
        //Inizializzazione variabili
        uint32_t a= h[0];
        uint32_t b= h[1];
        uint32_t c= h[2];
        uint32_t d= h[3];
        uint32_t e= h[4];
        uint32_t f= h[5];
        uint32_t g= h[6];
        uint32_t xh= h[7];


        //Main loop operation
        for(int i=0;i<64;i++)
        {
            uint32_t s0= op3(a);
            uint32_t maj= (a&b)^(a&c)^(b&c);
            uint32_t t2=s0+maj;
            uint32_t s1=op4(e);
            uint32_t ch=(e&f)^((~e)&g);
            uint32_t t1=xh+s1+ch+k[i]+w[i];
            //
            xh=g;
            g=f;
            f=e;
            e=d+t1;
            d=c;
            c=b;
            b=a;
            a=t1+t2;
        }
        //Add this chunk's hash to result so far:
        h[0]=h[0]+a;
        h[1]=h[1]+b;
        h[2]=h[2]+c;
        h[3]=h[3]+d;
        h[4]=h[4]+e;
        h[5]=h[5]+f;
        h[6]=h[6]+g;
        h[7]=h[7]+xh;

    }   //FINE BLOCCO

    //Produce the final hash value (big-endian):
    string dig;
    for(int i=0;i<8;i++)
    {
        dig+=Uint32ToHexString(h[i]);
    }
    this->digest=dig;


}
string SHA256::GetDigest()
{
    return digest;
}
void SHA256::PrintDigest()
{

    cout<<"ORIGINAL: " <<original<<endl<<"DIGEST: "<<endl;
    cout<<digest<<endl;
}
