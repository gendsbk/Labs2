#include "ripe.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << endl << "Использование: ./RIPEMD-160 file_in" << endl << endl;

	return -1;
    }
    else
    {
        RIPE hash;

        if (!hash.rfile(argv[1]))
            cout << "Ошибка чтения файла!" << endl << endl;
        
            cout << hash.ripe() << endl;
       
    }

    return 0;
}