/* ------------------------ Check brackets ------------------------- */
/* Input contains one string S which consists of big and small
/* latin letters, digits, punctuation marks and brackets from the set []{}()
/* If the code in S uses brackets correctly, output "Success"
/* Otherwise, output the 1-based index of the first unmatched closing bracket
/* output the 1-based index of the first unmatched opening bracket.
/* ------------------------------------------------------------------*/
#include <iostream>
#include <stack>
#include <string>
using namespace std;
struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }
    char type;
    int position;
};

int main() {
    // 經典的stack問題, 將左括號都放入stack, 遇到右括號就pop最上面的左括號檢查是否成對
    string text;
    getline(cin, text);
    stack <Bracket> opening_brackets_stack;
    int pos;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        if (next == '(' || next == '[' || next == '{') {
            // struct型態的stack, 要push資料就要宣告成該struct型態
            struct Bracket data = Bracket(next, position);
            opening_brackets_stack.push(data);
        }
        if (next == ')' || next == ']' || next == '}') {
            // opening brackets should exist first
            if(opening_brackets_stack.empty()){
                cout << position+1 << endl;
                return 0;
            }
            // match
            if(opening_brackets_stack.top().Matchc(next))
                opening_brackets_stack.pop();
            // not match
            else{
                cout << position+1 << endl;
                return 0;
            }
        }
    }
    if(opening_brackets_stack.empty())
        cout << "Success" << endl;
    // 迴圈結束後stack還有東西, 代表有多餘的左括號
    else
        cout << opening_brackets_stack.top().position+1 << endl;
    return 0;
}
