#include "area.h"


//Area changes
Area* Plain::change(Weather *x)
{
    x->change(this);
    if (_water > 15) {
        Grassland *p = new Grassland(_name,_water);
        delete this;
        return p;
    } else {
        return this;
    }
}

Area * Grassland::change(Weather *x)
{
    x->change(this);
    if (_water > 50) {
        Lake *p = new Lake(_name, _water);
        return p;
        delete this;
    } else if (_water < 16) {
        Plain *p = new Plain(_name, _water);
        delete this;
        return p;
    } else {
        return this;
    }
}

Area *Lake::change(Weather *x)
{
    x->change(this);
    if (_water > 51) {
        Grassland *p = new Grassland(_name,_water);
        delete this;
        return p;
    } else {
        return this;
    }
}
