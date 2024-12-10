#include<bits/stdc++.h>
using namespace std;

set<char> calc_first(char nt, vector< pair < char , vector <string> > > &gram, int n) {
    vector<string> der;
    set<char> ff;
    int ind = -1;

    // Search for the non-terminal in the grammar
    for (int i = 0; i < n; i++) {
        if (gram[i].first == nt) {
            der = gram[i].second;
            ind = i;
            break;
        }
    }

    // Process each string in the grammar for the non-terminal
    for (int i = 0; i < der.size(); i++) {
        if (!isupper(der[i][0])) {
            ff.insert(der[i][0]); // If it's a terminal, insert directly
        } else {
            int index = 0;
            while (index < n) {
                bool eps = false;
                set<char> der2 = calc_first(der[i][index], gram, n);

                // Replace range-based for loop with iterator
                for (set<char>::iterator it = der2.begin(); it != der2.end(); ++it) {
                    char x = *it;
                    if (x == '#') eps = true; // Epsilon symbol
                    ff.insert(x);
                }

                if (eps) {
                    index++;
                } else {
                    break;
                }
            }
        }
    }
    return ff;
}

set<char> calc_follow(char nt, vector< pair < char , vector <string> > > &gram, int n) {
    set<char> fl;
    if (nt == gram[0].first) fl.insert('$');
    
    for (int i = 0; i < n; i++) {
        vector<string> grstrings = gram[i].second;
        for (int k = 0; k < grstrings.size(); k++) {
            string grs = grstrings[k];
            for (int j = 0; j < grs.size(); j++) {
                if (nt == grs[j]) {
                    if (j == (grs.size() - 1)) {
                        set<char> der = calc_follow(gram[i].first, gram, n);
                        for (set<char>::iterator it = der.begin(); it != der.end(); ++it) {
                            fl.insert(*it);
                        }
                    } else {
                        if (!isupper(grs[j + 1])) fl.insert(grs[j + 1]);
                        else {
                            set<char> der2 = calc_first(grs[j + 1], gram, n);
                            for (set<char>::iterator it = der2.begin(); it != der2.end(); ++it) {
                                fl.insert(*it);
                            }
                        }
                    }
                    goto end;
                }
            }
        }
    }
end:
    return fl;
}

int main() {
    int n;
    cout << "lines:";
    cin >> n;
    
    vector< pair<char,vector<string> > > gram;
    cout << "grammar:\n";
    fflush(stdin);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        char lh = s[0];
        vector<string> t;
        string temp = "";
        for (int j = 3; j < s.length(); j++) {
            if (s[j] == '/') {
                t.push_back(temp);
                temp = "";
            } else {
                temp += s[j];
            }
        }
        t.push_back(temp);
        gram.push_back({lh, t});
    }

    vector<pair<char,vector<char> > > first;
    vector<pair<char,vector<char> > > follow;
    first.resize(n);
    follow.resize(n);

    for (int i = 0; i < n; i++) {
        first[i] = {gram[i].first, {}};
        follow[i] = {gram[i].first, {}};
    }

    for (int i = 0; i < n; i++) {
        set<char> st = calc_first(gram[i].first, gram, n);
        vector<char> te;
        for (set<char>::iterator it = st.begin(); it != st.end(); ++it) {
            te.push_back(*it);
        }
        first[i].second = te;
    }

    // Display First sets
    for (int i = 0; i < n; i++) {
        cout << "First[" << first[i].first << "] {";
        for (int j = 0; j < first[i].second.size(); j++) {
            cout << first[i].second[j];
            if (j != first[i].second.size() - 1) cout << ",";
        }
        cout << "}\n";
    }

    // Calculate and display Follow sets
    for (int i = 0; i < n; i++) {
        set<char> st = calc_follow(gram[i].first, gram, n);
        vector<char> te;
        for (set<char>::iterator it = st.begin(); it != st.end(); ++it) {
            te.push_back(*it);
        }
        follow[i].second = te;
    }

    for (int i = 0; i < n; i++) {
        cout << "Follow[" << follow[i].first << "] {";
        for (int j = 0; j < follow[i].second.size(); j++) {
            cout << follow[i].second[j];
            if (j != follow[i].second.size() - 1) cout << ",";
        }
        cout << "}\n";
    }

    return 0;
}
