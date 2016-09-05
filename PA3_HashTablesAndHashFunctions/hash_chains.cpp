/* ------------------------------------------------- */
/* 2d vector iterator http://stackoverflow.com/questions/1784573/iterator-for-2d-vector
/*
/*
/* ------------------------------------------------- */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

struct Query{
    string type, s;
    size_t ind;
};
int test = 100;
class QueryProcessor{
    int bucket_count;
    vector<list<string> > buckets; // hash table
    size_t hash_func(const string& s) const{
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        // polynomial hash function
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    // 一行一行query處理, 不是全部先讀起來
    Query readQuery() const{
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const{
        cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query){
        buckets.resize(bucket_count);
        // declare a interator
        vector<list<string> >::iterator itRow;  // this interator points to row
        list<string>::iterator itCol; // this iterator points to col

        if (query.type == "check"){
            // pointer to a single bucket
            list<string>& bucket = buckets[query.ind];
            for(itCol = bucket.begin(); itCol != bucket.end(); ++itCol){
                cout << *itCol << " ";
            }
            cout << "\n";
        }
        else{
            int hashValue = hash_func(query.s);
            list<string>& bucket = buckets[hashValue];
            for(itCol = bucket.begin(); itCol != bucket.end(); ++itCol){
                if(*itCol == query.s)
                    break;
            }
            if(query.type == "find"){
                writeSearchResult(itCol != bucket.end()); // if it != .end() is ture, found
            }
            else if(query.type == "add"){
                if(itCol == bucket.end())
                    bucket.push_front(query.s);
            }
            else if(query.type == "del"){
                if(itCol != bucket.end())
                    bucket.erase(itCol);
            }
        }
    }

    void processQueries(){
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main(){
    ios::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
