#include <iostream>
#include "enor.h"

using namespace std;

/*
In a seq input file, hunt trophies are stored: hunter name, species,weight.
How many hunters have shot rabbit
*/

int main()
{
    try{
        enor t("inp.txt");
        int c = 0;
        for(t.first();!t.end();t.next()){
            if(t.current()) ++c;
        }
        cout<<"The number of hunters who shot rabbit: " << c << endl;
    }catch(enor::Errors exp){
        cout << "Wrong file name.\n";
        return 1;
    }
    return 0;

}
