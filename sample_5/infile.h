#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


struct Hackaton{
    std::string HackID;
    std::string name;

    std::vector<int> results;

     int countMore80 = 0;

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


class infile
{
    public:
        enum Exceptions {OPEN_ERROR};
        infile(const std::string &filename);
        ~infile();

        void first(){
        read();
        next();
    }
        void next();
        Hackaton current() const {return curr;}
        bool end() const {return m_end;}

    private:
        std::fstream x;
        Status st;
        Hackaton e;
        Hackaton curr;
        bool m_end;

        void read();
};

