#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool fileSetup(vector<int> &vec, const string &filename);
bool condMaxSreatch(const vector<int> &x, int &maxi , int &ind);
bool condMaxSreatchFromAfile(const string &filename, int &maxi);

int main()
{
    cout << "Enter a file name: " ;
    string filename;
    cin >> filename;
    vector<int> vec;
    int maxi, ind;

    bool fileExists = fileSetup(vec, filename);
    if(fileExists == true){
        bool maxSearchWorks = condMaxSreatch(vec, maxi, ind);
        if(maxSearchWorks){
            cout << "The maximum valley is: " << maxi << " and it is in index number: " << ind << endl;
        }else{
            cout << "NO valley exists!" << endl;
        }

        if(condMaxSreatchFromAfile(filename, maxi)){
            cout << "The maximum search from a file result is: " << maxi << endl;
        }else{
            cout << "NO valley exists!" << endl;
        }
    }else{
        cout << "File doesn't exitst";
    }

    return 0;
}

bool fileSetup(vector<int> &vec, const string &filename){
    fstream fileStream(filename);
    if(fileStream.fail()){
        return false;
    }

    int num;
    vec.clear();
    while(fileStream >> num){
        vec.push_back(num);
    }
    //fileStream.close();
    return true;
}

bool condMaxSreatch(const vector<int> &x, int &maxi , int &ind){
    bool l = false;

    for(int i = 1; i < x.size() - 1; i++){
        if(l && (x[i-1] >= x[i] && x[i] <= x[i+1]) ){
            if(maxi < x[i]){
                maxi = x[i];
                ind = i;
            }
        }
        if(!l && (x[i-1] >= x[i] && x[i] <= x[i+1])){
            l    = true;
            maxi = x[i];
            ind  = i;
        }
    }

    return l;
}

bool condMaxSreatchFromAfile(const string &filename, int &maxi){
    fstream filestream(filename);
    int before, current, after;
    filestream >> before;
    filestream >> current;
    filestream >> after;

    bool l = false;
    while(!filestream.fail()){
        if(l && current <= before && current <= after){
            if(maxi < current){
                maxi = current;
            }
        }
        if(!l && current <= before && current <= after){
            l = true;
            maxi = current;
        }
        before = current;
        current = after;
        filestream >> after;
    }

    return l;


}
