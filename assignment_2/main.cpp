#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <time.h>

#include "weather.h"
#include "area.h"

using namespace std;

void create(const string &str, vector<Area*> &areas)
{
    ifstream f(str);
    if(f.fail()) { cout << "Wrong file name!\n"; exit(1);}
    int n;
    f >> n;
    areas.resize(n);

    for(int i = 0; i < n ; i++){
        string name;
        char type;
        int e;
        string name2;
        f >> name >> name2 >> type >> e;
        name += " " + name2; // total name with spaces
        switch(type){
            case 'P' : areas[i] = new Plain(name,e);
            break;
            case 'G' : areas[i] = new Grassland(name,e);
            break;
            case 'L' : areas[i] = new Lake(name,e);
        }
    }
    f >> Weather::humidity;
    f.close();
}

void printArea(vector<Area*> &areas)
{
    if(areas[0]!= nullptr)
    {
        cout << "Number of Areas: " << areas.size() << "\n";
        for(unsigned int i = 0; i < areas.size(); i++)
        {
            if(areas[i]->exist()){
                cout << areas[i]->getName() << " Type: " << areas[i]->getType() << " Amount of Water:  " << areas[i]->getWater() << "\n";
            }
        }
        cout <<"The humidity: " << Weather::humidity << "\n\n";
    }

    else{
    cout << "Empty. \n";
    }
}

//to determine the probability
bool rainyOrCloudy(float probabilityOfRainy) {
   srand (time(NULL));
   return (float)(rand() % 100 + 1) < probabilityOfRainy;
}

void simulation(vector<Area*> &areas)
{
    if(Weather::humidity > 0){

        for(unsigned int i = 0; i < 10; i++)
        {
            Weather *s = Sunny::instance();
            Weather *c = Cloudy::instance();
            Weather *r = Rainy::instance();

            for(unsigned int i = 0; i < areas.size(); i++)
            {
                Area *tmp; //Store area in a tmp value because we might change it
                if(Weather::humidity > 70){
                    tmp = areas[i]->change(r);
                    Weather::humidity = 30;
                }
                else if(Weather::humidity < 40){
                    tmp = areas[i]->change(s);
                }
                else{
                    float prob = (Weather::humidity-30) *3.3;
                    bool rainy = rainyOrCloudy(prob);
                    if(rainy){
                        tmp = areas[i]->change(r);
                    }
                    else{ //cloudy
                        tmp = areas[i]->change(c);
                        }
                }
                areas[i] = tmp; //after the changes assign area
                cout << areas[i]->getName() << " Type: " << areas[i]->getType() << ", Amount of Water:  " << areas[i]->getWater() << ", Humidity: " << Weather::humidity << endl;
            }
            cout << "End of Simulation\n\n\n" ;
        }
    }
}

void destroy(vector <Area*> &areas)
{
    for(unsigned int i = 0; i < areas.size(); i++)
    {
        delete areas[i];
        areas[i] = nullptr;
    }
}

void destroyWeather()
{
    Sunny::destroy();
    Rainy::destroy();
    Cloudy::destroy();
}

#define NORMAL_MODE
#ifdef NORMAL_MODE


int main()
{
    vector<Area*> areas;
    create("input.txt", areas);


    printArea(areas);
    simulation(areas);

    // Destruction of the objects
    destroy(areas);
    destroyWeather();

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("0", "t0.txt")
{
    vector<Area*> areas;


    create("t0.txt", areas);
    //simulation(areas);
    CHECK(areas.size() == 0);
    destroy(areas);
}

TEST_CASE("1", "t1.txt"){
    vector<Area*> areas;
    create("t1.txt", areas);
    //simulation(areas);
    CHECK(areas.size() == 1);
    destroy(areas);
}

TEST_CASE("2", "t2.txt"){
    vector<Area*> areas;
    create("t2.txt", areas);
    //simulation(areas);
    CHECK(areas.size() == 2);
    destroy(areas);
}

TEST_CASE("3", "t3.txt"){
    vector<Area*> areas;
    create("t3.txt", areas);
    //simulation(areas);
    CHECK(areas.size() == 2);
    CHECK(areas[1]->getType() == "Grassland");
    destroy(areas);

    areas.clear();
    create("t3.txt", areas);
    CHECK(areas[0]->getName() == "Mr Lake");
    CHECK(areas[1]->getName() == "Mr Green");
    CHECK(areas[0]->getType() == "Lake");

    //simulation(areas);
    destroy(areas);

}

TEST_CASE("21", "t21*.txt")
{
    vector<Area*> areas;
    create("t21.txt",areas);
    CHECK(areas.size() == 2);
    CHECK(areas[0]->getWater() == 86);
    //simulation(areas);

    destroy(areas);
}

TEST_CASE("4", "")
{

    //create
    Weather::humidity = 10;
    CHECK(Weather::humidity == 10);

    Area* p = new Lake("Mr X", 80);
    CHECK(p->getName() == "Mr X");
    CHECK(p->getWater() == 80);
    CHECK(p->getType() == "Lake");

    Weather* sunny = Sunny::instance();
    Area* x = p->change(sunny);
    CHECK(Weather::humidity == 25);
    CHECK(x->getType() == "Grassland");
    CHECK(p->exist() == true);
    CHECK(p->getWater() == 70);
    //test func

    Area* y = new Grassland("Mr Desert", 2);
    y = y->change(sunny);
    CHECK(y->exist() == false);
    delete x;
    delete y;

}





#endif // NORMAL_MODE
