#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Exam
{
    std::string neptun_code;
    int grade;

    std::vector<int> results;

    friend std::ostream &operator<<(std::ostream &os, Exam &exam)
    {

        os << "Neptun code: " << exam.neptun_code << ", grade: " << exam.grade << ", results: ";
        for (int x : exam.results)
            os << x << " ";
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Exam &exam)
    {
        std::string line;
        std::getline(is, line, '\n');
        std::stringstream ss(line);
        ss >> exam.neptun_code >> exam.grade;
        int e;
        exam.results.clear();

        while (ss >> e)
        {
            exam.results.push_back(e);
        }
        return is;
    }

    bool fail()
    {
        return grade = 1;
    }
};

enum Status
{
    norm,
    abnorm
};

void read(Exam &exam, Status &st, std::fstream &x)
{
    x >> exam;
    if (x.fail())
        st = abnorm;
    else
        st = norm;
}

// Grade 5 after first fail
int afterFail(Exam &exam, Status st, std::fstream &x)
{
    read(exam, st, x);
    while (st == norm && exam.grade != 1) // search for the first fail
    {
        read(exam, st, x);
    }
    read(exam, st, x); // read that fail
    int countExcellent = 0;
    while (st == norm)
    {
        if (exam.grade == 5)
        {
            countExcellent++; // start counting afterwards
        }
        read(exam, st, x);
    }
    return countExcellent;
}

int beforeFail(Exam &exam, Status st, std::fstream &x)
{
    int count = 0;
    read(exam, st, x);
    while (st == norm && exam.grade != 1)
    {
        if (exam.grade == 5)
        {
            count++; // start counting afterwards
        }
        read(exam, st, x);
    }
    return count;
}

pair<int, int> beforeAfter(Exam &exam, Status st, std::fstream &x)
{
    pair<int, int> result2;

    int successCount1 = 0;
    read(exam, st, x); // read the first elem
    while (st == norm && exam.grade != 1)
    {
        if (exam.grade == 5)
        {
            successCount1++; // count till the first fail
        }
        read(exam, st, x);
    }
    result2.first = successCount1;
    read(exam, st, x); // read the fails

    int successCount2 = 0;
    read(exam, st, x);
    while (st == norm)
    {
        if (exam.grade == 5)
        {
            successCount2++; // read until eof
        }
        read(exam, st, x);
    }
    result2.second = successCount2;
    return result2;
}

int main()
{
    Exam exam;
    Status st = norm;

    std::cout << "grade 3: \n";

     std::fstream g("input.txt");
    int results = beforeFail(exam, st, g);
    std::cout << "Before: ";
    std::cout << results << std::endl;

    std::fstream x("input.txt");
    int result = afterFail(exam, st, x);
    std::cout << "After: ";
    std::cout << result << std::endl;


    std::fstream h("input.txt");
    pair<int, int> result2 = beforeAfter(exam, st, h);
    cout << "Before & After: " << result2.first << " - " << result2.second << endl;
    return 1;
}
