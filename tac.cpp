#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <algorithm>
#include <sstream>  

using namespace std;

string int_to_string(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

void apply_operator(stack<string>& stk, stack<char>& ops, vector<string>& tac, int& temp_counter) {
    string op2 = stk.top(); stk.pop();
    string op1 = stk.top(); stk.pop();
    char operator_ = ops.top(); ops.pop();
    string temp_var = "t" + int_to_string(temp_counter++); 
    tac.push_back(temp_var + " = " + op1 + " " + operator_ + " " + op2);
    stk.push(temp_var);  
}
vector<string> generate_TAC(const string& expression) {
    int temp_counter = 1;  
    vector<string> tac;    
    stack<string> stk;     
    stack<char> ops;       

    int i = 0;
    while (i < expression.size()) {
        char ch = expression[i];

        if (isalnum(ch)) {  
            stk.push(string(1, ch));
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') { 
            while (!ops.empty() &&
                ((ops.top() == '*' || ops.top() == '/') ||
                (ch == '+' || ch == '-') && (ops.top() == '+' || ops.top() == '-'))) {
                apply_operator(stk, ops, tac, temp_counter);
            }
            ops.push(ch);
        }

        i++;
    }

    while (!ops.empty()) {
        apply_operator(stk, ops, tac, temp_counter);
    }

    return tac;
}

int main() {
    string expr;
    cout << "Enter the expression (e.g., a = b + c * d - e / f): ";
    getline(cin, expr);  

    size_t equal_sign_pos = expr.find('=');

    if (equal_sign_pos == string::npos) {
        cout << "Invalid expression. No '=' sign found." << endl;
        return 1;  
    }
    string result_var = expr.substr(0, equal_sign_pos); 
    string expression = expr.substr(equal_sign_pos + 1); 
    expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());
    vector<string> tac = generate_TAC(expression);
    tac.push_back(result_var + " = t" + int_to_string(tac.size()));  

    for (size_t i = 0; i < tac.size(); i++) {
        cout << tac[i] << endl;
    }

    return 0;
}
