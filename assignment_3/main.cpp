#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/summation.hpp"
#include "library/counting.hpp"


using namespace std;


struct Fish {
    string specie;
    int size;
    friend istream &operator>>(istream &is, Fish &c) {
        is >> c.specie >> c.size;
        return is;
    };
};


class MaxCatFish : public MaxSearch<Fish,int> {
protected:
    bool cond(const Fish &e) const override {
        return e.specie == "catfish";
    }

    int func(const Fish &e) const override {
        return e.size;
    }

};

struct Line {
    string id;
    string angler;
    bool catfish;
    int size ;
    friend istream &operator>>(istream &is, Line &c) {
        string str;
        getline(is, str);
        stringstream ss(str);
        ss >> c.angler >> c.id;
        MaxCatFish pr;
        StringStreamEnumerator<Fish> ssenor(ss);
        pr.addEnumerator(&ssenor);
        pr.run();
        c.catfish = pr.found();
        if (c.catfish)
            c.size = pr.opt();
        else
            c.size = 0;
//        printf("Size -- %d  --  Found : %d\n", c.size, c.catfish);
        return is;
    };
    friend ostream &operator<<(ostream &os, Line &c) {
        os << "ID : " << c.id << " -- Angler : " << c.angler << " -- Catfish caught : " << c.catfish;
        return os;
    }
};

//maxSearch by fish size
class BiggestCatFish : public MaxSearch<Line,int> {
protected:
    int func(const Line &e) const override {
        return e.size;
    }

    bool cond(const Line &e) const override {
        return e.catfish;
    }
};

// second question
struct Angler {
    bool valid ; // caught bigger than 30 cm
    string name;
    friend ostream &operator<<(ostream &os, Angler &c) {
        os << "name : " << c.name << " -- " << c.valid;
        return os;
    }
};

class biggerThan30 : public Counting<Line> {
private :
    string name;
public:
    biggerThan30(const string &name) : name(name) {}

protected:
    bool cond(const Line &e) const override {
        return e.size > 30;
    }

    void first() override {}

    bool whileCond(const Line &current) const override {
        return current.angler == name;
    }
};

class AnglerEnum : public Enumerator<Angler> {
private:
    SeqInFileEnumerator<Line> *_f;
    Angler _angler;
    bool _end;

public:
    AnglerEnum(const string &fname) {
        _f = new SeqInFileEnumerator<Line>(fname);
    }

    virtual ~AnglerEnum() {
        delete _f;
    }

    void first() override {
        _f->first();
        next();
    }

    bool end() const override {
        return _end;
    }

    Angler current() const override {
        return _angler;
    }

    void next() override {
        _end = _f->end();
        if(_end) return;
        _angler.name = _f->current().angler;
        biggerThan30 pr(_angler.name);
        pr.addEnumerator(_f);
        pr.run();
        _angler.valid = pr.result() > 0;
        //cout << _angler << "\n";
    }
};


class AllAnglerAreValid : public Summation<Angler,bool> {
protected:
    bool add(const bool &a, const bool &b) const override {
        return a&b;
    }

    bool neutral() const override {
        return true;
    }

    bool func(const Angler &e) const override {
        return e.valid;
    }

};

int main() {
    try{

        BiggestCatFish pr;
        SeqInFileEnumerator<Line> myenor("input.txt");
        pr.addEnumerator(&myenor);
        pr.run();

        if (pr.found()){

            cout << "Biggest cat fish size is : " << pr.optElem().size << ", Angler name: " << pr.optElem().angler <<", Contest ID: " << pr.optElem().id <<endl;

        }

        // (2)Has every angler caught a catfish bigger than 30 cm?
        AllAnglerAreValid pr_2;
        AnglerEnum enum_2("input.txt");
        pr_2.addEnumerator(&enum_2);
        pr_2.run();

        cout << "\nIs every angler valid :  " << pr_2.result() << endl;
    }   catch (SeqInFileEnumerator<int>::Exceptions e) {
        cout << e;
    }

    return 0;
}

