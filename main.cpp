#include "functions.h"

int main()
{
    char ch;
    cout << "*** Huffman compression ***\n";
    cout << "Author: Jakub \"Horuss\" Czajkowski, GNU GPL License\n";
    cout << "Program allows you to compress text (ASCII only) files\n";
    do
    {
        cout << "MENU:\n1. Code (compress)\n2. Decode (decompress)\n3. Exit\n";
        cin >> ch;
        switch(ch)
        {
            case '1':
                cout << code();
                break;
            case '2':
                cout << decode();
                break;
        }
    }
    while(ch!='3');
    return 0;
}
