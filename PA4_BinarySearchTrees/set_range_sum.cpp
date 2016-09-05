#include <cstdio>
#include <iostream>
#include <cstring>
#include <climits>
using namespace std;

// Splay tree implementation

// Vertex of a splay tree
struct Vertex{
    int key;
    // Sum of all the keys in the subtree - remember to update
    // it after each operation that changes the tree.
    long long sum;
    Vertex* left;
    Vertex* right;
    Vertex* parent;

    Vertex(int key, long long sum, Vertex* left, Vertex* right, Vertex* parent)
        : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

Vertex* root = NULL;

void update(Vertex* v){
    if (v == NULL) return;
    v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
    if (v->left != NULL){
        v->left->parent = v;
    }
    if (v->right != NULL){
        v->right->parent = v;
    }
}

void small_rotation(Vertex* v){
    Vertex* parent = v->parent;
    if (parent == NULL){
        return;
    }
    Vertex* grandparent = v->parent->parent;
    if (parent->left == v){
        Vertex* m = v->right;
        v->right = parent;
        parent->left = m;
    }
    else{
        Vertex* m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != NULL){
        if (grandparent->left == parent){
            grandparent->left = v;
        }
        else{
            grandparent->right = v;
        }
    }
}

void big_rotation(Vertex* v){
    if (v->parent->left == v && v->parent->parent->left == v->parent){
        // Zig-zig right, 最左的子樹移到root
        small_rotation(v->parent);
        small_rotation(v);
    }
    else if (v->parent->right == v && v->parent->parent->right == v->parent){
        // Zig-zig left, 最右的子樹移到root
        small_rotation(v->parent);
        small_rotation(v);
    }
    else{
        // Zig-zag
        small_rotation(v);
        small_rotation(v);
    }
}
void traversal(Vertex *n){
    if(n != NULL){
        traversal(n->left);
        cout << n->key << " " << endl;
        cout << "sum: " << n->sum << endl;
        traversal(n->right);
    }

}
// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v){
    if (v == NULL) return;
    while (v->parent != NULL){
        if (v->parent->parent == NULL){
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree,
// returns NULL.
Vertex* find(Vertex*& root, int key){
    Vertex* v = root;
    Vertex* last = root;
    Vertex* next = NULL;

    while (v != NULL){
        //  紀錄比key還大或等於的vertex
        if (v->key >= key && (next == NULL || v->key < next->key)){
            next = v;
        }
        last = v;
        // 找到了
        if (v->key == key){
            break;
        }
        // 要找的key比當前的vertex還大, 則往此vertex的右子樹找
        if (v->key < key){
            v = v->right;
        }
        else{
            v = v->left;
        }
    }

    // 如果key沒有找到, 且他的值比所有vertex都大, return NULL
    // 如果key沒有找到, 他的值並沒有比所有vertex還大, return 比他大或等於他的vertex (key的前一個vertex)
    // 如果key有找到, return該vertex
    if(next != NULL){
        //cout << "next: " << next->key << endl;
        // 如果有找到, 把key的vertex提升到root, 沒找到則把最後一個找尋的vertex提升到root
        splay(root, next);
    }
    else
        splay(root, last);

    return next;


}

void split(Vertex*& root, int key, Vertex*& left, Vertex*& right){
    right = find(root, key);

    if (right == NULL){
        left = root;
        return;
    }


    left = right->left;
    right->left = NULL;
    if (left != NULL){
        left->parent = NULL;
    }

    update(left);
    update(right);

    /*if(left != NULL)
        cout << "sp left: " << left->key << " sum: " << left->sum << endl;
    if(right != NULL)
        cout << "sp right: " << right->key << " sum: " << right->sum << endl;*/

}
void merge(Vertex* left, Vertex* right, Vertex*& root){

    if(left != NULL){
        find(left, INT_MAX);
        left->right = right;
        if(right != NULL){
            right->parent = left;
        }
        root = left;
    }
    else{
        if(right != NULL)
            root = right;
        else
            root = NULL;
    }
    update(root);
    return;
    /*
    if (left == NULL) return right;
    if (right == NULL) return left;
    Vertex* min_right = right;
    while (min_right->left != NULL){
        min_right = min_right->left;
    }
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;*/
}

// Code that uses splay tree to solve the problem

void insert(int x){
    //Vertex* left = NULL;
    //Vertex* right = NULL;
    Vertex* new_vertex = NULL;
    /*split(root, x, left, right);
    if (right == NULL || right->key != x){
        // key, sum, left, right, parent
        new_vertex = new Vertex(x, x, NULL, NULL, NULL);
    }
    root = merge(merge(left, new_vertex), right);*/
    if(root == NULL){
        new_vertex = new Vertex(x, x, NULL, NULL, NULL);
        root = new_vertex;
        return;
    }
    Vertex* current = root;
    Vertex* anterior = NULL;
    string directie;
    while(current != NULL){
        if(x == current->key)
            return;
        anterior = current;
        if(x < current->key){
            directie = "LEFT";
            current = current->left;
        }
        else{
            directie = "RIGHT";
            current = current->right;
        }
    }

    current = new Vertex(x, x, NULL, NULL, anterior);
    if(directie == "LEFT")
        anterior->left = current;
    else
        anterior->right = current;
    splay(root, current);
}

bool found(int x){
    // Implement find yourself

    if(root == NULL)
        return false;

    Vertex* f = find(root, x);

    if(f == NULL || f->key != x)
        return false;
    else{
        return true;
    }
}
void erase(int x){
    // Implement erase yourself
    if(found(x)){
        // 如果有找到key, 此key目前提升為root, 將兩邊child的parent都指向NULL
        Vertex* leftChild = root->left;
        Vertex* rightChild = root->right;

        if(leftChild)
            leftChild->parent = NULL;

        if(rightChild)
            rightChild->parent = NULL;

        // 合併兩子樹
        merge(leftChild, rightChild, root);
    }
    else
        return;
}

long long sum(int from, int to){
    Vertex* left = NULL;
    Vertex* middle = NULL;
    Vertex* right = NULL;

    split(root, from, left, middle);
    split(middle, to+1, middle, right);
    long long ans = 0;

    // Complete the implementation of sum
    if(middle != NULL)
        ans = middle->sum;
    merge(left, middle, root);
    merge(root, right, root);

    return ans;
}

const int MODULO = 1000000001;

int main(){
    int n;
    scanf("%d", &n);

    long long last_sum_result = 0;

    for (int i = 0; i < n; i++){
        char buffer[10];
        scanf("%s", buffer);

        char type = buffer[0];
        switch (type){
            case '+' :{
                int x;
                scanf("%d", &x);
                insert((x + last_sum_result) % MODULO);
            }
            break;
            case '-' :{
                int x;
                scanf("%d", &x);
                erase((x + last_sum_result) % MODULO);
            }
            break;
            case '?' :{
                int x;
                scanf("%d", &x);
                string sol = found((x + last_sum_result) % MODULO) ? "Found" : "Not found";
                cout << sol << endl;
            }
            break;
            case 's' :{
                int l, r;
                scanf("%d %d", &l, &r);
                long long res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);

                cout << res << endl;
                last_sum_result = res % MODULO;
            }
        }
        /*if(root != NULL){
            cout << "root: " << root->key << endl;
            cout << "root sum of subtree: " << root->sum << endl;
            traversal(root);
        }
        else
            cout << "root: NULL" << endl;*/

    }
    return 0;
}
