/* ------------- simple phone book by hash table ----------------- */
/* input format: first line is number of queries N
/* following line is queries contains add find or del
/* add number name
/* del number
/* find number
/* output format: only find query needs to print the name or not found
/* --------------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Query{
    string type, name;
    int number;
};

vector<Query> read_queries(){
    int n;
    cin >> n;
    vector<Query> queries(n);
    // 一次讀完所有query
    for (int i = 0; i < n; ++i){
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result){
    for (size_t i = 0; i < result.size(); ++i)
        cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries){
    vector<string> result;
    // STL map (hash table)
    map<int, string> mapPhonebook;
    map<int, string>::iterator iter;
    // traverse every query
    for (int i = 0; i < queries.size(); i++){
        iter = mapPhonebook.find(queries[i].number);
        if (queries[i].type == "add"){
            mapPhonebook[queries[i].number] = queries[i].name;
        }
        else if (queries[i].type == "del"){
            if(iter != mapPhonebook.end())
                mapPhonebook.erase(iter);
        }
        else if(queries[i].type == "find"){
            string response = "not found";
            if(iter != mapPhonebook.end()){
                response = iter->second;
            }
            result.push_back(response);
        }
    }
    return result;
}

int main(){
    write_responses(process_queries(read_queries()));
    return 0;
}
