#include <iostream>
#include "infile.h"

using namespace std;

int main()
{
    string filename;
    cout << "Enter a filename: ";
    cin >> filename;

    infile enumerator(filename);

    for(enumerator.first(); !enumerator.end();enumerator.next()){
        cout << enumerator.current().number << " " << enumerator.current().count << endl;
    }

    return 1;
}
