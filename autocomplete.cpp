#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Quick iterative binary search for exact word matches
bool isWordPresent(const vector<string>& words, const string& target) {
    int low = 0;
    int high = words.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (words[mid] == target) {
            return true;
        }
        if (words[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}

// Modified binary search to find the lower bound of a prefix and list matches
void printPrefixMatches(const vector<string>& words, const string& prefix) {
    int low = 0;
    int high = words.size() - 1;
    int firstMatchIdx = -1;

    // Binary search to locate the *first* index matching the prefix
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (words[mid].compare(0, prefix.length(), prefix) == 0) {
            firstMatchIdx = mid;
            high = mid - 1; // Keep searching left to find the absolute first occurrence
        }
        else if (words[mid] < prefix) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (firstMatchIdx == -1) {
        cout << "No matches found for prefix: " << prefix << endl;
        return;
    }

    // Print all consecutive words that share the same prefix
    cout << "Suggested words:" << endl;
    for (int i = firstMatchIdx; i < words.size(); i++) {
        if (words[i].compare(0, prefix.length(), prefix) != 0) {
            break; 
        }
        cout << " -> " << words[i] << endl;
    }
}

int main() {
    // Local database of words
    vector<string> dictionary = {
        "apple", "app", "application", "banana", "band", "bandwidth", 
        "code", "coder", "codeforces", "cpp", "data", "database", 
        "dynamic", "leet", "leetcode", "search", "sorting"
    };

    // Ensure database is sorted for binary search operations
    sort(dictionary.begin(), dictionary.end());

    cout << "=== TEXT UTILITY TOOL ===" << endl;
    
    while (true) {
        int choice;
        cout << "\n1. Spell Check\n2. Auto-Suggestions\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 3) break;

        if (choice == 1) {
            string word;
            cout << "Enter word to check: ";
            cin >> word;
            if (isWordPresent(dictionary, word)) {
                cout << "Valid word found." << endl;
            } else {
                cout << "Word not found in dictionary." << endl;
            }
        } 
        else if (choice == 2) {
            string prefix;
            cout << "Enter prefix characters: ";
            cin >> prefix;
            printPrefixMatches(dictionary, prefix);
        }
    }
    return 0;
}
//Refactor autocomplete logic for clean boundary checks.
