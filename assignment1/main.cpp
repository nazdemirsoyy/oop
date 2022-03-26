/* Task:
Implement the N matrix type which contains integers.
These are square matrices that can contain nonzero entries
only in their first and last column, and in their main diagonal.
Don't store the zero entries.
Store only the entries that can be nonzero in a sequence.
Implement as methods: getting the entry located at index (i, j),
adding and multiplying two matrices,
and printing the matrix (in a square shape).
*/

#include <iostream>
#include "nMatrix.h"

using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

//class for menu
class Menu
{
public:
    Menu() : a(0) { }
    void run();
private:
    Matrix a;

    void menuWrite();
    void get() const;
    void set();
    void read();
    void write();
    void sum();
    void mul();
};

int main()
{
    Menu m;
    m.run();
}

void Menu::run()
{
    int n = 0;
    do
    {
        menuWrite();
        cout << endl << "Please enter your choice: " ;
        cin >> n;
        switch(n)
        {
        case 1:
            get();
            break;
        case 2:
            set();
            break;
        case 3:
            read();
            break;
        case 4:
            write();
            break;
        case 5:
            sum();
            break;
        case 6:
            mul();
            break;
        }
    }
    while(n!=7);
}

void Menu::menuWrite()
{
    cout <<"Welcome to Menu: "<< endl;
    cout << " 1. - Get an element of the matrix" << endl;
    cout << " 2. - Update an element of the matrix" << endl;
    cout << " 3. - Read matrix from console" << endl;
    cout << " 4. - Print matrix" << endl;
    cout << " 5. - Add matrices" << endl;
    cout << " 6. - Multiply matrices" << endl;
    cout << " 7. - Quit" << endl;
}

void Menu::get() const
{
    int i,j;
    cout << "Give the index of the row: ";
    cin >> i;
    cout << "Give the index of the column: ";
    cin >> j;
    try
    {
        cout << "a[" << i << "," << j << "]= " << a(i-1,j-1) << endl;
    }
    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::OVERINDEXED)
            cout << "Overindexing" << endl;
        else
            cout << "Unhandled ecxeption" << endl;
    }
}

void Menu::set()
{
    int i,j,e;
    cout << "Give the index of the row: ";
    cin >> i;
    cout << "Give the index of the column: ";
    cin >> j;
    cout << "Give the value: ";
    cin >> e;
    try
    {
        a(i-1,j-1) = e;
    }
    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::OVERINDEXED)
            cout << "Overindexing" << endl;
        if (ex == Matrix::NULLPART)
            cout << "These indexes do not point to the N matrix" << endl;
    }
}

void Menu::read()
{
    try
    {
        cout << "Give the size and the items of the matrix: ";
        cin >> a;
    }
    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::INVALID)
            cout << "Invalid size" << endl;
        else
            cout << "Unhandled exception" << endl;
    }
}

void Menu::write()
{
    cout << a << endl;
}

void Menu::sum()
{
    try
    {
        Matrix b;

        cout << "Give the size and the items of the second  matrix: " << endl;
        cin >> b;
        cout << "Sum of the matrices: " << endl;
        cout << a + b << endl;
    }
    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::INVALID)
            cout << "Invalid size" << endl;
        if(ex == Matrix::DIFFERENT)
            cout << "Different sizes" << endl;
    }
}

void Menu::mul()
{
    try
    {
        Matrix b;

        cout << "Give the size and the items of the second  matrix: " << endl;
        cin >> b;
        cout << "Product of the matrices: " << endl;
        cout << a * b << endl;
    }
    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::INVALID)
            cout << "Invalid size" << endl;
        if(ex == Matrix::DIFFERENT)
            cout << "Different sizes" << endl;
    }
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("create", "inp.txt")
{
    const string fileName = "inp.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix c;
    in >> c; // 3
    CHECK(c(0,0) == 3);
    CHECK(c(1,1) == 3);
    CHECK(c(2,2) == 1);

    Matrix b;
    in >> b; // 2
    CHECK(b(0,0) == 2);
    CHECK(b(1,1) == 1);

    Matrix a;
    in >> a; // 1
    CHECK(a(0,0)==1);
}

TEST_CASE("getting and changing an element of the matrix", "")
{
    Matrix a( {{1,0,1},
             {3,3,4},
             {32,0,5}
        } );
    CHECK(a(0,0) == 1);
    a(0,0) = 0;
    CHECK(a(0,0) == 0);
}

TEST_CASE("copy constructor", "inp.txt")
{
    const string fileName = "inp.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix a;
    in >> a; // 3

    Matrix b = a;

    CHECK(a(0,0) == b(0,0));
    CHECK(a(1,1) == b(1,1));
    CHECK(a(2,2) == b(2,2));
}

TEST_CASE("assignment operator", "inp.txt")
{
    const string fileName = "inp.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix a, b;
    in >> a;

    b = a; // check every non-zero item
    CHECK(a(0,0) == b(0,0));
    CHECK(a(1,1) == b(1,1));
    CHECK(a(2,2) == b(2,2));

    Matrix c; // 3
    c = b = a; // check every non-zero item
    CHECK(a(0,0) == c(0,0));
    CHECK(a(1,1) == c(1,1));
    CHECK(a(2,2) == c(2,2));

    a = a; // check every non-zero item
    CHECK(a(0,0) == 3);
    CHECK(a(1,1) == 3);
    CHECK(a(2,2) == 1);
}

TEST_CASE("add", "inp2.txt")
{
    const string fileName = "inp2.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix a, b, c, d, f, e, z; // 3
    in >> a >> b >> z >> e;

    c = a + b; // check every non-zero item
    CHECK(c(0,0) == 4);
    CHECK(c(1,1) == 3);
    CHECK(c(2,2) == 3);

    d = b + a; // check every non-zero item
    CHECK(c(0,0) == d(0,0));
    CHECK(c(1,1) == d(1,1));
    CHECK(c(2,2) == d(2,2));

    d = (a + b) + c;
    f = a + (b + c); // check every non-zero item
    CHECK(d(0,0) == f(0,0));
    CHECK(d(1,1) == f(1,1));
    CHECK(d(2,2) == f(2,2));

    c = a + z; // check every non-zero item
    CHECK(c(0,0) == a(0,0));
    CHECK(c(1,1) == a(1,1));
    CHECK(c(2,2) == a(2,2));


}

TEST_CASE("multiply", "inp2.txt")
{
    const string fileName = "inp2.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix a, b, c, d, f, e, z; // 3
    in >> a >> b >> z >> e;

    c = a * b;
    CHECK(c(0,0) == 9);
    CHECK(c(1,1) == 2);
    CHECK(c(2,2) == 8);

    d = b * a;
    CHECK(c(0,0) == d(0,0));
    CHECK(c(1,1) == d(1,1));
    CHECK(c(2,2) == d(2,2));

    d = (a * b) * c;
    f = a * (b * c);
    CHECK(d(0,0) == f(0,0));
    CHECK(d(1,1) == f(1,1));
    CHECK(d(2,2) == f(2,2));

}

TEST_CASE("exceptions", "")
{

    Matrix a(3);

    try
    {
        a(3,3) = 4;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::OVERINDEXED);
    }

    try
    {
        a(-1,4) = 4;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::OVERINDEXED);
    }

    Matrix b(2);
    Matrix c(3);

    try
    {
        a = b;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::DIFFERENT);
    }

    try
    {
        c = a + b;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::DIFFERENT);
    }

    try
    {
        c = a * b;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::DIFFERENT);
    }


    try
    {
        a(1,0) = 4;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::NULLPART);
    }

    try
    {
        int  k = a(1,0);
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::NULLPART);
    }
}

#endif
