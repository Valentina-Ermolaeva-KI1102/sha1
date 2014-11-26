#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#define F(x, y, z) ((x & y) | ((~x) & z))
#define G(x, y, z) (x ^ y ^ z)
#define H(x, y, z) ((x & y) | (x & z) | (y & z))
#define Cyclic_shift(x, y) (x << y | x >> (32-y))
unsigned char* sha1(std::ifstream *in)
{
int lenght, size = 64, rest, i;
in->seekg(0, std::ios::end);
lenght = in->tellg();
in->seekg(0, std::ios::beg);
bool end = false;
rest = lenght % 64;
unsigned char *msg_for_hash = new unsigned char[size];
char buf;
unsigned int A = 0x67452301, B = 0xEFCDAB89, C = 0x98BADCFE, D = 0x10325476, E = 0xC3D2E1F0, AA, BB, CC, DD, EE;
unsigned int K[4] = {0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6};
unsigned int *X=(unsigned int*)(msg_for_hash);
unsigned int k, f, temp;
unsigned int w[80];
while(!in->eof() && !end)
{
for(i = 0; i < size; i++)
{
in->get(buf);
if(in->eof())
{
if(i < 55)
{
msg_for_hash[i] = 0x80;
for(i++; i < 56; i++)
msg_for_hash[i] = 0;
long long bit_length = (unsigned int)(lenght)*8; // lounge of massage into bit
for(int i = 0; i < 8; i++) // last 8 b
msg_for_hash[size - 8 + i] = (unsigned char)(bit_length >> i * 8);
break;
}
else
{
msg_for_hash[i] = 0x80;
for(i++; i < size; i++)
msg_for_hash[i] = 0;
end = true;
break;
}
}
msg_for_hash[i] = buf;
}
if(end)
{
for(i++; i < 56; i++)
msg_for_hash[i] = 0;
long long bit_length = (unsigned int)(lenght)*8; // lounge of massage into bit
for(int i = 0; i < 8; i++) // last 8 b
msg_for_hash[size - 8 + i] = (unsigned char)(bit_length >> i * 8);
end = false;
}
AA = A;
BB = B;
CC = C;
DD = D;
EE = E;
for (int j = 0; j < 80; j++)
{
if (j < 16)
w[j] = X[j];
else
w[j] = Cyclic_shift((w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16]), 1);
if (j < 20)
{
f = F(BB, CC, DD);
k = K[0];
}
else if (j < 40)
{
f = G(BB, CC, DD);
k = K[1];
}
else if (j < 60)
{
f = H(BB, CC, DD);
k = K[2];
}
else if (j < 80)
{
f = G(BB, CC, DD);
k = K[3];
}
temp = Cyclic_shift(AA, 5) + f + EE + k + w[j];
EE = DD;
DD = CC;
CC = Cyclic_shift(BB, 30);
BB = AA;
AA = temp;
}
// recording result of rounds;
A += AA;
B += BB;
C += CC;
D += DD;
E += EE;
}
//
unsigned char *SHA1 =new unsigned char[20];
SHA1[0] = A % 256;
SHA1[1] = (A /= 256) % 256;
SHA1[2] = (A /= 256) % 256;
SHA1[3] = (A / 256);
SHA1[4] = B % 256;
SHA1[5] = (B /= 256) % 256;
SHA1[6] = (B /= 256) % 256;
SHA1[7] = B / 256;
SHA1[8] = C % 256;
SHA1[9] = (C /= 256) % 256;
SHA1[10] = (C /= 256) % 256;
SHA1[11] = (C / 256);
SHA1[12] = D % 256;
SHA1[13] = (D /= 256) % 256;
SHA1[14] = (D /= 256) % 256;
SHA1[15] = D / 256;
SHA1[16] = E % 256;
SHA1 [17] = (E /= 256) % 256;;
SHA1[18] = (E /= 256) % 256;;
SHA1[19] = (E / 256);
return SHA1;
}
int main(int argc, char **argv)
{
char in_name[512], out_name[512];
if (argc > 2)
{
strcpy(in_name, argv[1]);
strcpy(out_name, argv[2]);
}
else if (argc == 2)
{
if(!strcmp("-h", argv[1]) || !strcmp("-H", argv[1]) || !strcmp("-help", argv[1]))
{
std::cout<<"this is program are created for calculate hash sha1\nExample of using:\n sha1.exe input_file_neme out_file_name\n sha1.exe input_file_name\n sha1.exe\n";
return 1;
}
strcpy(in_name, argv[1]);
std::cout<<"Enter the output file: ";
std::cin>>out_name;
}
else
{
std::cout<<"Enter the input file: ";
std::cin>>in_name;
std::cout<<"Enter the output file: ";
std::cin>>out_name;
}
std::ifstream in(in_name, std::ios_base::in);
if(!in) return 1;
std::ofstream out(out_name, std::ios_base::out);
unsigned char *SHA1 = sha1(&in);
for(int i = 0; i < 20; i++)
out<<std::hex<<std::uppercase<< (unsigned int)SHA1[i]<<" ";
in.close();
out.close();
return 0;
}
