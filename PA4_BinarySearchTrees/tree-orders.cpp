#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node{
    int key, left, right;
};
class TreeOrders{
    int n;
    vector <Node> node;

public:
    void read(){
        cin >> n;
        node.resize(n);
        for (int i = 0; i < n; i++){
            cin >> node[i].key >> node[i].left >> node[i].right;
        }
    }
    void in_order(int vertex){
        if(vertex != -1){
            in_order(node[vertex].left);
            cout << node[vertex].key << ' ';
            in_order(node[vertex].right);
        }
    }
    void pre_order(int vertex){
        if(vertex != -1){
            cout << node[vertex].key << ' ';
            pre_order(node[vertex].left);
            pre_order(node[vertex].right);
        }
    }
    void post_order(int vertex){
        if(vertex != -1){
            post_order(node[vertex].left);
            post_order(node[vertex].right);
            cout << node[vertex].key << ' ';
        }
    }
};
int main(){
    ios_base::sync_with_stdio(0);
    TreeOrders t;
    t.read();

    t.in_order(0);
    cout << endl;
    t.pre_order(0);
    cout << endl;
    t.post_order(0);
    cout << endl;
    return 0;
}
