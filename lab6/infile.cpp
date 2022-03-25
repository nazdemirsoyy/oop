#include "infile.h"

infile::infile(const std::string &filename){
    m_x.open(filename);
    if(m_x.fail())throw OPEN_FILE_ERROR;
    }

void infile::read(Status &sx,int &dx,std::fstream &x){
    x >> dx;
    if(x.fail()) sx = abnorm;
    else sx = norm;
}

void infile::next(){
    if(!(m_end = (m_sx == abnorm))){
        m_curr.count = 0;
        m_curr.number = m_dx;
        while(m_sx == norm && m_dx == m_curr.number){
            m_curr.count += 1;
            read(m_sx, m_dx,m_x);

        }
    }

}
