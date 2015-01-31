#include "g.h"

int main(int argc, char **argv)
 {
    if (argc != 2)
    {
        cout << endl << "ERROR usage: ./g file_in" << endl << endl;

        return -1;
    }
    else
    {
        Gost hash;

        if (hash.FILER(argv[1]))
        {
            hash.gost();

            cout << "hash gost: "<<endl;
            hash.printhash();
        }
        else
            cout << "ERROR!!!FILE NOT FOUND!" << endl << endl;
    }

    return 0;
}