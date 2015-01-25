#include <string>                                                                       
#include <iostream>                                                                   
#include <sstream>                                                                      
#include <fstream>                                                                  

#define shift(x, n) (((x) << (n)) | ((x) >> (32-(n))))                           

using namespace std;                                                                    

class RIPE                                                                       
{
    string message;                                                                    

    unsigned long long bitlen;                                                          

    unsigned int **X;                                                                   

    unsigned int blocks;                                                                
    
    unsigned int H0, H1, H2, H3, H4;                                                   

    unsigned int A1, B1, C1, D1, E1, A2, B2, C2, D2, E2, T;                            

    unsigned int F(unsigned int j, unsigned int x, unsigned int y, unsigned int z);     
    unsigned int K1(unsigned int j);                                                    
    unsigned int K2(unsigned int j);                                                   
    unsigned int inv(unsigned int value);                                               
    unsigned int bytes_to_uint(char* bytes);                                            
    
    void dopoln();                                                                  
    void addlen();                                                                                                  
    void init();                                                          
    void obrobotka();                                                         
    ostringstream result;                                                              
public:
    bool rfile(char *fileName);                                                    
   

    string ripe();                                                                
};