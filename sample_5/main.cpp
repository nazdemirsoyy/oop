#include <iostream>
#include "infile.h"
/* Hackaton, find a competitor who finished at least more than 80. */
int main()
{
    try{
        infile t("input.txt");
        t.first();
        int maxiCircuits = t.current().countMore80;
        std::string maxComp = t.current().name;
        std::string hackName = t.current().HackID;

        for(; !t.end();t.next())
            {
                if(t.current().countMore80 > maxiCircuits){
                    maxiCircuits = t.current().countMore80;
                    maxComp = t.current().name;
                    hackName = t.current().HackID;
                }
            }
        if(maxiCircuits != 0) std::cout <<"\nThe competitor is: "<<maxComp<< "at the " <<hackName;
        else std::cout <<"There is no competitor.";
    }
    catch(infile::Exceptions e)
        {
    std::cerr <<"Opening file failed.\n";
    exit(-1);
        
    return 0;
    }
}
