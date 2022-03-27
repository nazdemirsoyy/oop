#pragma once
#include <string>
#include <iostream>
#include <fstream>

enum Status {norm,abnorm};

struct Prey{
    std::string name;
    std::string spec;
    int weight;
    friend std::istream &operator>>(std::istream &is, Prey &p);
};


class enor
{
    public:
        enum Errors{FILE_ERROR};
        enor(const std::string &filename);
        ~enor(){_x.close();}
        void first(){read();next();}
        void next();
        bool current() const{return _cur;}
        bool end() const {return _end;}
    private:
        std::ifstream _x;
        Prey _dx;
        Status _sx;
        bool _cur;
        bool _end;

        void read();
};


