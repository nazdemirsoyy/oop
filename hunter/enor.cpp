#include "enor.h"

std::istream &operator>>(std::istream &is,Prey &p){ //read
    is >> p.name >> p.spec >> p.weight;
    return is;
}

enor::enor(const std::string &filename){ //constructor
    _x.open(filename.c_str());
    if(_x.fail()) throw FILE_ERROR;
}

void enor::next(){

    _end = (abnorm ==_sx);
    if(!_end){
            std::string name = _dx.name;
            _cur = false;
            while(norm == _sx && _dx.name == name){
                _cur=_cur || ("rabbit" == _dx.spec);
                read();
            }

    }

}

void enor::read(){

    _x >> _dx;
    _sx = _x.fail() ? abnorm : norm;
}
