// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
using namespace std;

void splitStr(const std::string & input,
              const std::string & patten,
              std::vector<std::string> & result)
{
    if(input.empty() || patten.empty() )
    {
        return;
    }
    std::string::size_type cur = 0;

    while (cur < input.length())
    {
        std::string::size_type pos = input.find(patten, cur);
        if(pos != std::string::npos)
        {
            if(pos != cur)
            {
                result.push_back(input.substr(cur, pos-cur));
            }
            cur = pos + patten.length();
        }
        else
        {
            result.push_back(input.substr(cur));
            return;
        }
    }
}

int main () {
    string line;
    ifstream myfile ("input.txt");
    std::list< std::vector<std::string> > restoreInfo;
    vector<std::string> tokens;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            string tempStr(line);
            splitStr(tempStr, ",",tokens);
            restoreInfo.push_back(tokens);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    std::list< std::vector<std::string> >::iterator listit;

    for(listit=restoreInfo.begin(); listit != restoreInfo.end(); ++listit)
    {
        vector<std::string> strVec = *listit;
        vector<std::string>::iterator it;
        for(it=strVec.begin(); it != strVec.end(); ++it)
        {
            cout<<"Item: "<<*it<<endl;
        }
    }
    return 0;
}
