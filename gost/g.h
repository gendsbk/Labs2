#include <iostream>
#include <fstream>
#include <memory.h>

using namespace std;


class Gost
{
    typedef unsigned char byte;
    typedef byte B[32];
    typedef byte B32[4];

    byte *buffer, res[32];

    unsigned int length;

    int fi(int argument);

    void crypg(byte A[], byte K[], byte R[]);
    void E(byte D[], byte K[], byte R[]);
    void a(byte Y[], byte R[]);
    void p(byte Y[], byte R[]);
    void psy(byte arr[]);
    void PSY(byte arr[], int p);
    void f(byte H[], byte M[], byte newH[]);
public:
    bool FILER(char *fileName);
    bool printhash();
    
    void gost();
};