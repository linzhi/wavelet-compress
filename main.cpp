#include <iostream>
#include "WaveletCompress.h"
#include "WaveletDecompress.h"
#include "WaveletComDec.h"
using namespace std;

int main(int argc, char *argv[])
{
    //A example to show how to compress the data
    int choice = 3;
    int exit = 0;
    int level = 1;
    int value = 5;
    char file_input[20];
    char file_save[20];
    char file_output[20];
    
    cout << "Wavelet Compression Programme: " << endl;
    cout << "1. Compress.\n2. Decompress.\n3. Compress & Decompress.\n4. Exit.\n" << endl;
    
    do
    {
        cin >> choice;
        
        switch(choice)
        {
        case 1:
            cout << "Syntax: [input filename] [output filename] [level = 1] [value = 5]\n=>";
            cin >> file_input >> file_save >> level >> value;
            cout << "Compressing......" << endl;
            Compress(file_input, file_save, level, value);
            cout << "Done.\n\n";
            system("pause");
            break;
        
        case 2:
            cout << "Syntax: [input filename] [output filename]\n=>";
            cin >> file_save >>file_output;
            cout << "Decompressing" << endl;
            Decompress(file_save, file_output);
            cout << "Done.\n\n";
            system("pause");
            break;
        
        case 3:
            cout << "Syntax: [input filename][output filename] [level = 1] [value = 5]\n=>";
            cin >> file_input >> file_output >> level >> value;
            cout << "Compressing & Decompressing......" << endl;
            CompressDecompress(file_input, file_output, level, value);
            cout << "Done.\n\n";
            system("pause");
            break;
        
        case 4:
            exit = 1;
            cout <<"Exit wavelet compression programme\n";
            system("pause");
            break;
        
        default:
            cout << "Invalid choice. Choose again.\n" << endl;
            system("pause");
            break;
        }
    }
    
    while (exit == 0);
    
    return 0;
}
