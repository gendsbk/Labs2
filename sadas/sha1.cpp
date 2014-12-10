#include "sha1.h" 

unsigned int sha1::Funk(unsigned int j, unsigned int x, unsigned int y, unsigned int z) //Выбор битовой функции в соответсвии с номером цикла
{
	if (j < 20)
		return (x & y) | ((~x) & z);
	else if (j < 40)
		return x ^ y ^ z;
	else if (j < 60)
		return (x & y) | (x & z) | (y & z);
	else if (j < 80)
		return x ^ y ^ z;
	else
	return 0;
}


bool sha1::readf(char *fileName) 
{	
	ifstream in(fileName, ios::binary);

	if (in.fail())
		return false;

	in.seekg(0, ios::end); 
	int size = in.tellg(); 
	in.seekg(0, ios::beg); 

	char *mas = new char[size]; 

	strg.resize(size); 
	in.read(mas, size); 
	in.close(); 

	for (int i = 0; i < size; i++) 
		strg[i] = mas[i]; 

	delete[] mas; 

	return true; 
}

bool sha1::write(char *fileName, string str) 
{
	ofstream out(fileName); 
	if (out.fail()) 
	return false; 
	out << str; 
	return true; 
}

void sha1::razm() 
{
	dlin = strg.size() * 8; 
	strg.push_back((unsigned char)0x80); 
	while ((strg.size() * 8) % 512 != 448) 
	strg.push_back(0); 
}

void sha1::addlen() 
{
	unsigned int temp = strg.size(); 
	strg.resize(temp + 8); 
	for (unsigned int i = strg.size() - 1; i >= temp; i--) {
		strg[i] = (unsigned char)dlin; 
		dlin >>= 8; 
	}
}

void sha1::init()
{
H0 = 0x67452301; 
H1 = 0xEFCDAB89, H2 = 0x98BADCFE, H3 = 0x10325476, H4 = 0xC3D2E1F0; 
K[0] = 0x5A827999, K[1] = 0x6ED9EBA1, K[2] = 0x8F1BBCDC, K[3] = 0xCA62C1D6; }

void sha1::obrab() 
{
	for (unsigned int i = 0; i < strg.size(); i += 64) 
	{
		for (int k = 0; k < 64; k++) 
		block[k] = strg[k + i]; 
		for (int k = 0; k < 16; k++) 
	{
	word[k] = ((unsigned int)block[k * 4]) << 24; 
	word[k] |= ((unsigned int)block[k * 4 + 1]) << 16; 
	word[k] |= ((unsigned int)block[k * 4 + 2]) << 8; 
	word[k] |= ((unsigned int)block[k * 4 + 3]); 
}

for (int k = 16; k < 80; k++) 
	word[k] = shift((word[k - 3] ^ word[k - 8] ^ word[k - 14] ^ word[k - 16]), 1); 
	A = H0; B = H1; C = H2; D = H3; E = H4; 

for (int i = 0; i < 80; i++)
{
	T = shift(A, 5) + Funk(i, B, C, D) + E + word[i] + K[i / 20];
	E = D;
	D = C;
	C = shift(B, 30);
	B = A;
	A = T;
}

H0 += A; H1 += B; H2 += C; H3 += D; H4 += E; 
}
}

string sha1::sha_1() 
{
	razm(); 
	addlen(); 
	init();
	obrab(); 
	res << hex << H0 << H1 << H2 << H3 << H4; 
	return res.str(); 
}
