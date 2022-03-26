#include <iostream>
#include <fstream>

using namespace std;

enum Status
{
    norm,
    abnorm
};

void read(Status &st, double &e, fstream &x) // read function
{
    x >> e;

    if (x.fail())
        st = abnorm;
    else
        st = norm;
}

double before(fstream &x)
{
    double s = 0.0;
    int c = 0;
    Status st;
    double e;
    read(st, e, x);
    while (e >= 0 && st == norm)
    {
        s += e;
        ++c;
        read(st, e, x);
    }
    return (c != 0) ? s / c : 0;
}

double after(fstream &x)
{
    Status st;
    double e;
    read(st, e, x);
    while (e >= 0 && st == norm)
    {
        read(st, e, x);
    }

    double s = 0.0;
    int c = 0;
    read(st, e, x);
    while (st == norm)
    {
        s += e;
        ++c;
        read(st, e, x);
    }
    return (c != 0) ? s / c : 0;
}

pair<double, double> beforeAfter(fstream &x)
{
    pair<double, double> result;
    double s1 = 0;
    int c1 = 0;
    Status st;
    double e;
    read(st, e, x);
    while (e >= 0 && st == norm)
    {
        s1 += e;
        ++c1;
        read(st, e, x);
    }
    result.first = (c1 != 0) ? s1 / c1 : 0;

    double s2 = 0;
    int c2 = 0;
    read(st, e, x);
    while (st == norm)
    {
        s2 += e;
        ++c2;
        read(st, e, x);
    }
    result.second = (c2 != 0) ? s2 / c2 : 0;

    return result;
}

// before: Calculate the avg of daily temperature before the first temperature under the freezing point

// after:Calculate the avg of daily temperature after the first temperature under the freezing point

// before after:Calculate the avg of daily temperature before and after the first temp under the freezing point if in the after version that first freezing temp is included too.
int main()
{
    fstream f("input.txt");
    cout << "before avg: "
         << before(f) << endl;
    fstream j("input.txt");
    cout << "after avg: " << after(j) << endl;
    fstream g("input.txt");
    pair<double, double> result = beforeAfter(g);
    cout << "before/after: " << result.first << "," << result.second << endl;

    return 0;
}
