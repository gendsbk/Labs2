#include <string> 
#include <sstream> 
#include <iostream> 
#include <fstream> 

using namespace std; 
#define shift(x, n) (((x) << (n)) | ((x) >> (32-(n)))) 
class sha1 
{
	string strg;
 
	unsigned long long dlin; 
	unsigned char block[64]; 
	unsigned int word[80]; 
	unsigned int K[4]; 
	unsigned int H0, H1, H2, H3, H4; 
	unsigned int A, B, C, D, E, T; 
	unsigned int Funk(unsigned int j, unsigned int x, unsigned int y, unsigned int z); 

	void razm(); 
	void addlen(); 
	void init(); 
	void obrab(); 
	
	ostringstream res; 
public:
	bool readf(char *fileName); 
	bool write(char *fileName, string str); 

	string sha_1(); 
};
