#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
/*A company has made a couple of hackathons, many people contributed to those hackathons. The results of those hackathons are stored in a file. 
Each line in the files of the results starts with the ID of the hackathon (string without white spaces), then the name of the competitor 
(string without white spaces), then the results of every task the competitor solved on the scale of 1..100 (integer), the competitor solved 
at least one task! GRADE 3:get the competitor who got the max score before the first failing competitor (the score is the average
of all of the results of one competitor, and a competitor fails if he scored less than 40%) */
struct Hackaton{
    std::string HackID;
    std::string name;

    std::vector<int> results;

    friend std::ostream &operator<<(std::ostream &os, Hackaton &hack){
    os<<"Hackaton ID: " << hack.HackID << ",name of the competitor: "<< hack.name << ",results: ";
    for (int x : hack.results) os << x << " ";
    return os;
    }

    friend std::istream &operator>> (std::istream &is, Hackaton &hack){
    std::string line;
    std::getline(is,line,'\n');
    std::stringstream ss(line);
    ss >> hack.HackID >> hack.name;
    int e;
    hack.results.clear();

    while(ss >> e){
        hack.results.push_back(e);
        }
        return is;
    }

    float avg(){
        int sum = 0;
        for(int a : results){
            sum += a;
        }
        return sum/results.size();
    }

    bool fail(){
        return avg() < 40;
    }
};

enum Status {norm,abnorm};

void read(Hackaton &hack, Status &st, std::fstream &x){
    x >> hack;
    if(x.fail()) st = abnorm;
    else st = norm;
}

Hackaton maxBeforeFail(Hackaton &hack, Status &st, std::fstream &x){
    read(hack,st,x);
    Hackaton max = hack;
    while(st == norm && !hack.fail()){
            if(hack.avg() >= max.avg()){
                max = hack;
            }
            read(hack,st,x);
    }
        return max;
}

int main()
{
    Hackaton hack;
    std::fstream x("input.txt");
    Status st = norm;
    Hackaton result = maxBeforeFail(hack,st,x);
    std::cout << result << std::endl;

    return 1;
}
