//Count prime numbers in a file
//BLD0YM
//Naz Demirsoy
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main( )
{
    ifstream inputFile;
    string filename;
    int num;
    int x;
    int factor = 0;
    int count = 0;


    cout << "Please enter the name of the input file: ";
    cin >> filename;

    inputFile.open(filename.c_str());

     if (inputFile)
    {

        while (inputFile >> num)
        {
            int factor = 0;

            for (x = 2; x <= num; x++)
                if (num % x == 0)
                    factor++;

            if (factor == 1)
            {
                count++;
            }
        }

        cout << "The number of the primes in " << filename << " ";
        cout << "is " << count;
    }
    else
    {
        cout << "The file "<< filename << " does not exist.";
    }

    inputFile.close();

return 0;
}
