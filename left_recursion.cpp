#include <bits/stdc++.h>
using namespace std;

// Function to remove left recursion from a single non-terminal grammar
void removeLeftRecursion(const string& nonTerminal, const vector<string>& productions) {
    vector<string> alpha, beta;

    // Separate productions into alpha (left-recursive) and beta (non-left-recursive)
    for (size_t i = 0; i < productions.size(); ++i) {
        if (productions[i][0] == nonTerminal[0]) {
            alpha.push_back(productions[i].substr(1)); // Remove the left recursion part
        } else {
            beta.push_back(productions[i]);
        }
    }

    if (alpha.empty()) {
        // No left recursion present
        cout << nonTerminal << " -> ";
        for (size_t i = 0; i < productions.size(); ++i) {
            cout << productions[i];
            if (i < productions.size() - 1) cout << " | ";
        }
        cout << endl;
        return;
    }

    // Create new grammar rules
    string newNonTerminal = nonTerminal + "'";
    cout << nonTerminal << " -> ";
    for (size_t i = 0; i < beta.size(); ++i) {
        cout << beta[i] << newNonTerminal;
        if (i < beta.size() - 1) cout << " | ";
    }
    cout << endl;

    cout << newNonTerminal << " -> ";
    for (size_t i = 0; i < alpha.size(); ++i) {
        cout << alpha[i] << newNonTerminal << " | ";
    }
    cout << "e" << endl; // e denotes the empty string
}

int main() {
    // Input grammar
    string nonTerminal = "A";
    vector<string> productions;
    productions.push_back("Aa");
    productions.push_back("b");
    productions.push_back("Ac");
    productions.push_back("d");

    cout << "Original Grammar:\n";
    cout << nonTerminal << " -> ";
    for (size_t i = 0; i < productions.size(); ++i) {
        cout << productions[i];
        if (i < productions.size() - 1) cout << " | ";
    }
    cout << endl;

    cout << "\nGrammar after removing left recursion:\n";
    removeLeftRecursion(nonTerminal, productions);

    return 0;
}
