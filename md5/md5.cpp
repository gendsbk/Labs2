

#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string.h>
using namespace std;

bool Readfile(char* fileName, vector<unsigned char> &info);
void stepOne(vector<unsigned char> &info);
void Round(unsigned long *buf, unsigned long *part);
const char* getHash(vector<unsigned char> input);

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((~z) & (y)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((~z) | (x)))

#define shift(x, s) (((x) << (s)) | ((x) >> (32-(s))))

#define step(Fun, a, b, c, d, x, s, ac) {\
  (a) += Fun((b), (c), (d)) + (x) + (unsigned int)(ac);\
  (a) = shift((a), (s));\
  (a) += (b);\
 }
int main(int argc, char* argv[])
{
  vector<unsigned char> input;
  if (!Readfile(argv[1], input))
  {
    cerr << "Can't open file: " << endl;
    return -1;
  }

  cout << getHash(input);

  return 0;
}

bool Readfile(char* fileName, vector<unsigned char> &info)
{
  ifstream inputStream(fileName, std::ios::binary);
  if (inputStream.fail())
    return false;

  inputStream.seekg(0, std::ios::end);
  int inputSize = inputStream.tellg();
  inputStream.seekg(0, std::ios::beg);

  if (!inputSize)
  {
    info.clear();
    return true;
  }

  info.resize(inputSize);
  inputStream.read((char*)&info.front(), inputSize);
  inputStream.close();

  return true;
}

void stepOne(vector<unsigned char> &info)
{
  size_t size = info.size() * 8;
  info.push_back(0x80);

  int nZero = 56 - info.size() % 64;
  if (nZero < 0)
    nZero += 64;
  info.insert(info.end(), nZero, 0);

  for (int i = 0; i < 4; i++)
    info.push_back(size >> i * 8);
  info.insert(info.end(), 4, 0);
}

void Round(unsigned long *buf, unsigned long *part)
{
  unsigned long a = buf[0];
  unsigned long b = buf[1];
  unsigned long c = buf[2];
  unsigned long d = buf[3];

  #define S11 7
  #define S12 12
  #define S13 17
  #define S14 22
  step (F, a, b, c, d, part[ 0], S11, 0xD76AA478L);
  step (F, d, a, b, c, part[ 1], S12, 0xE8C7B756L);
  step (F, c, d, a, b, part[ 2], S13, 0x242070DBL);
  step (F, b, c, d, a, part[ 3], S14, 0xC1BDCEEEL);
  step (F, a, b, c, d, part[ 4], S11, 0xF57C0FAFL);
  step (F, d, a, b, c, part[ 5], S12, 0x4787C62AL);
  step (F, c, d, a, b, part[ 6], S13, 0xA8304613L);
  step (F, b, c, d, a, part[ 7], S14, 0xFD469501L);
  step (F, a, b, c, d, part[ 8], S11, 0x698098D8L);
  step (F, d, a, b, c, part[ 9], S12, 0x8B44F7AFL);
  step (F, c, d, a, b, part[10], S13, 0xFFFF5BB1L);
  step (F, b, c, d, a, part[11], S14, 0x895CD7BEL);
  step (F, a, b, c, d, part[12], S11, 0x6B901122L);
  step (F, d, a, b, c, part[13], S12, 0xFD987193L);
  step (F, c, d, a, b, part[14], S13, 0xA679438EL);
  step (F, b, c, d, a, part[15], S14, 0x49B40821L);

  #define S21 5
  #define S22 9
  #define S23 14
  #define S24 20
  step (G, a, b, c, d, part[ 1], S21, 0xF61E2562L);
  step (G, d, a, b, c, part[ 6], S22, 0xC040B340L);
  step (G, c, d, a, b, part[11], S23, 0x265E5A51L);
  step (G, b, c, d, a, part[ 0], S24, 0xE9B6C7AAL);
  step (G, a, b, c, d, part[ 5], S21, 0xD62F105DL);
  step (G, d, a, b, c, part[10], S22, 0x02441453L);
  step (G, c, d, a, b, part[15], S23, 0xD8A1E681L);
  step (G, b, c, d, a, part[ 4], S24, 0xE7D3FBC8L);
  step (G, a, b, c, d, part[ 9], S21, 0x21E1CDE6L);
  step (G, d, a, b, c, part[14], S22, 0xC33707D6L);
  step (G, c, d, a, b, part[ 3], S23, 0xF4D50D87L);
  step (G, b, c, d, a, part[ 8], S24, 0x455A14EDL);
  step (G, a, b, c, d, part[13], S21, 0xA9E3E905L);
  step (G, d, a, b, c, part[ 2], S22, 0xFCEFA3F8L);
  step (G, c, d, a, b, part[ 7], S23, 0x676F02D9L);
  step (G, b, c, d, a, part[12], S24, 0x8D2A4C8AL);

  #define S31 4
  #define S32 11
  #define S33 16
  #define S34 23
  step (H, a, b, c, d, part[ 5], S31, 0xFFFA3942L);
  step (H, d, a, b, c, part[ 8], S32, 0x8771F681L);
  step (H, c, d, a, b, part[11], S33, 0x6D9D6122L);
  step (H, b, c, d, a, part[14], S34, 0xFDE5380CL);
  step (H, a, b, c, d, part[ 1], S31, 0xA4BEEA44L);
  step (H, d, a, b, c, part[ 4], S32, 0x4BDECFA9L);
  step (H, c, d, a, b, part[ 7], S33, 0xF6BB4B60L);
  step (H, b, c, d, a, part[10], S34, 0xBEBFBC70L);
  step (H, a, b, c, d, part[13], S31, 0x289B7EC6L);
  step (H, d, a, b, c, part[ 0], S32, 0xEAA127FAL);
  step (H, c, d, a, b, part[ 3], S33, 0xD4EF3085L);
  step (H, b, c, d, a, part[ 6], S34, 0x04881D05L);
  step (H, a, b, c, d, part[ 9], S31, 0xD9D4D039L);
  step (H, d, a, b, c, part[12], S32, 0xE6DB99E5L);
  step (H, c, d, a, b, part[15], S33, 0x1FA27CF8L);
  step (H, b, c, d, a, part[ 2], S34, 0xC4AC5665L);

  #define S41 6
  #define S42 10
  #define S43 15
  #define S44 21
  step (I, a, b, c, d, part[ 0], S41, 0xF4292244L);
  step (I, d, a, b, c, part[ 7], S42, 0x432AFF97L);
  step (I, c, d, a, b, part[14], S43, 0xAB9423A7L);
  step (I, b, c, d, a, part[ 5], S44, 0xFC93A039L);
  step (I, a, b, c, d, part[12], S41, 0x655B59C3L);
  step (I, d, a, b, c, part[ 3], S42, 0x8F0CCC92L);
  step (I, c, d, a, b, part[10], S43, 0xFFEFF47DL);
  step (I, b, c, d, a, part[ 1], S44, 0x85845DD1L);
  step (I, a, b, c, d, part[ 8], S41, 0x6FA87E4FL);
  step (I, d, a, b, c, part[15], S42, 0xFE2CE6E0L);
  step (I, c, d, a, b, part[ 6], S43, 0xA3014314L);
  step (I, b, c, d, a, part[13], S44, 0x4E0811A1L);
  step (I, a, b, c, d, part[ 4], S41, 0xF7537E82L);
  step (I, d, a, b, c, part[11], S42, 0xBD3AF235L);
  step (I, c, d, a, b, part[ 2], S43, 0x2AD7D2BBL);
  step (I, b, c, d, a, part[ 9], S44, 0xEB86D391L);

  buf[0] += a;
  buf[1] += b;
  buf[2] += c;
  buf[3] += d;
}

unsigned long inv(unsigned long value)
{
    unsigned long res = 0;

    res |= ((value >> 0) & 0xFF) << 24;
    res |= ((value >> 8) & 0xFF) << 16;
    res |= ((value >> 16) & 0xFF) << 8;
    res |= ((value >> 24) & 0xFF) << 0;

    return res;
}

const char* getHash(vector<unsigned char> input)
{
  stepOne(input);
  // инициализация буфера
  unsigned long* buf = new unsigned long[4];
  buf[0] = 0x67452301;
  buf[1] = 0xEFCDAB89;
  buf[2] = 0x98BADCFE;
  buf[3] = 0x10325476;

  for (int i = 0; i < input.size() / (16 * 4); i++)//номер блока
  {
    unsigned long part[16];
    for (int j = 0; j < 16; j++)//номер элемента в блоке
    {
      unsigned long mi = 0;
      for (int k = 0; k < 4; k++)
      {
        mi |= input[i * 16 * 4 + j * 4 + k] << k * 8;
      }
      part[j] = mi;
    }
    Round(buf, part);
  }
  
  ostringstream res;
  res.fill ('0'); //нулями будут «залиты» пустые позиции в результирующей строке
  for (int i = 0; i < 4; i++)
  {
    res << std::hex << setw(8) << inv(buf[i]);
  }

  char* result = new char[33];
  strcpy(result, (char*) res.str().c_str());
  return result;
}