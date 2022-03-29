#include "infile.h"

infile::infile(const std::string &filename){
    x.open(filename.c_str());
    if(x.fail()) throw OPEN_ERROR;
}

infile::~infile(){
    x.close();
}

void infile::next(){

    m_end = (st = abnorm);
    if(!m_end){
        std::string name = e.name;
        curr = e;

        while((st == norm) && (e.name == name)){
            if(e.avg() > 80) curr.countMore80 += 1;
            read();
        }

    }

}

void infile::read(){
    st = (x >> e) ? norm:abnorm;
}
