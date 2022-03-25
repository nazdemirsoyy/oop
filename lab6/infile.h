#pragma once
#include <iostream>
#include <fstream>

struct Occur{
    int number;
    int count;

};

enum Status{norm,abnorm};

class infile
{
     private:
         std::fstream m_x;
         int m_dx;
         Status m_sx;
         Occur m_curr;
         bool m_end;

         void read(Status &sx,int &dx,std::fstream &x);

    public:

        enum Exceptions{OPEN_FILE_ERROR};
        infile(const std::string &filename); //constructor
        ~infile(){}; //destroctur

        void first(){
            read(m_sx, m_dx,m_x);
            next();
        }

        void next();
        Occur current(){return m_curr;};
        bool end(){return m_end;};

};
