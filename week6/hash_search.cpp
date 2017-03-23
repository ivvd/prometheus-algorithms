#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

void use_unordered_set(ifstream &f);

int main(int argc, const char *argv[])
{
    cout << "Hi everyone!\n";

    if(argc == 2)
    {
        ifstream file;
        cout << argv[1] << " opening...\n";
        file.open(argv[1], ifstream::in);

        use_unordered_set(file);

        file.close();
    }
    else
    {
        cout << "Wrong number of parameters.\n";
    }

    return 0;
}

void use_unordered_set(ifstream &f)
{
    string s;
    unordered_set<long long> table;

    while(!f.eof())
    {
        f >> s;
        table.insert(atoll(s.c_str()));
    }

    cout << "Unordered set size is " << table.size() << "\n";
    cout << "Bucket numbers is " << table.bucket_count() << "\n";
    cout << "Load factor is " << table.load_factor() << "\n";

    int sum_num = 0;

    
    long long y;
    unordered_set<long long>::const_iterator got;
    for(int i = -1000; i <= 1000; i++)
    {
        for(const long long &x: table)
        {
            y = i - x;
            got = table.find(y);
            if(got != table.end())
            {
                sum_num++;
                cout << "i = " << i << "; x = " << x << "; y = " << y << ";\n";
                break;
            }
        }
    }
    
    cout << "\n" << sum_num << "\n";

    //for(const long &x: table)
    //{
    //    cout << x << "\n";
    //}
}

