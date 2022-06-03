#ifndef AREA_H
#define AREA_H

#include <string>
#include "weather.h"

class Area
{
    public:
        std::string getName() const { return _name; }
        int getWater() const { return _water; }
        virtual std::string getType() const = 0;
        bool exist() const { return _water > -1; } // it cannot be negative 0 included
        void changeWater(int e) { _water += e; }
        virtual Area* change(Weather* x) = 0;
        virtual ~Area() {}

    protected:
        std::string _name;
        int _water;
        Area(const std::string &str, int e = 0) : _name(str), _water(e) {}

};

class Plain : public Area{
    public:
        Plain(const std::string &str, int e = 0) : Area(str, e) {}
        Area* change(Weather* x) override;
        std::string getType() const override { return "Plain"; }
};

class Grassland : public Area{
    public:
        Grassland(const std::string &str, int e = 0) : Area(str, e) {}
        Area* change(Weather* x) override;
        std::string getType() const override { return "Grassland"; }
};

class Lake : public Area{
    public:
        Lake(const std::string &str, int e = 0) : Area(str, e) {}
        Area* change(Weather* x) override;
        std::string getType() const override { return "Lake"; }
};



#endif // AREA_H
