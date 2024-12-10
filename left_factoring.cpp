#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

string int_to_string(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}
string longest_common_prefix(const vector<string>& strings) {
    if (strings.empty()) {
        return "";
    }

    string prefix = strings[0];

    for (size_t i = 1; i < strings.size(); ++i) {
        while (strings[i].find(prefix) != 0) { 
            prefix = prefix.substr(0, prefix.length() - 1);  
            if (prefix.empty()) {
                return "";
            }
        }
    }

    return prefix;
}

vector<string> left_factoring(const map<string, vector<string> >& productions) {
    vector<string> factored_productions;

    for (map<string, vector<string> >::const_iterator it = productions.begin(); it != productions.end(); ++it) {
        string lhs = it->first;
        const vector<string>& rhs_list = it->second;

        string common_prefix = longest_common_prefix(rhs_list);

        if (!common_prefix.empty()) {
            string new_lhs = lhs + "'";
            factored_productions.push_back(lhs + " -> " + common_prefix + new_lhs);

            vector<string> new_rhs;
            for (size_t i = 0; i < rhs_list.size(); ++i) {
                string rhs = rhs_list[i].substr(common_prefix.length());
                new_rhs.push_back(rhs);
            }

            stringstream new_rhs_str;
            for (size_t i = 0; i < new_rhs.size(); ++i) {
                new_rhs_str << new_rhs[i];
                if (i < new_rhs.size() - 1) {
                    new_rhs_str << " | ";
                }
            }

            factored_productions.push_back(new_lhs + " -> " + new_rhs_str.str());
        } else {
            stringstream rhs_str;
            for (size_t i = 0; i < rhs_list.size(); ++i) {
                rhs_str << rhs_list[i];
                if (i < rhs_list.size() - 1) {
                    rhs_str << " | ";
                }
            }
            factored_productions.push_back(lhs + " -> " + rhs_str.str());
        }
    }

    return factored_productions;
}

int main() {
    map<string, vector<string> > productions;

    cout << "Enter grammar productions (one by one):\n";
    cout << "Format: <Non-terminal> -> <Production1> | <Production2> ...\n";
    cout << "Type 'done' when you're finished.\n\n";

    while (true) {
        string line;
        cout << "Enter production: ";
        getline(cin, line);

        if (line == "done" || line == "DONE") {
            break;
        }

        size_t pos = line.find("->");
        if (pos != string::npos) {
            string lhs = line.substr(0, pos);
            string rhs = line.substr(pos + 2);
            size_t start = lhs.find_first_not_of(" \t");
            size_t end = lhs.find_last_not_of(" \t");
            lhs = lhs.substr(start, end - start + 1);

            start = rhs.find_first_not_of(" \t");
            end = rhs.find_last_not_of(" \t");
            rhs = rhs.substr(start, end - start + 1);

            vector<string> rhs_list;
            size_t prev_pos = 0;
            size_t next_pos;
            while ((next_pos = rhs.find("|", prev_pos)) != string::npos) {
                rhs_list.push_back(rhs.substr(prev_pos, next_pos - prev_pos));
                prev_pos = next_pos + 1;
            }
            rhs_list.push_back(rhs.substr(prev_pos));

            productions[lhs] = rhs_list;
        } else {
            cout << "Invalid format. Use the format <Non-terminal> -> <Production1> <Production2>.\n";
        }
    }
    vector<string> factored = left_factoring(productions);

    cout << "\nLeft Factored Productions:\n";
    for (size_t i = 0; i < factored.size(); ++i) {
        cout << factored[i] << endl;
    }

    return 0;
}
