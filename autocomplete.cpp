#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool verifyWordPresence(const vector<string>& wordList, const string& query) {
    int start = 0;
    int end = wordList.size() - 1;

    while (start <= end) {
        int midpoint = start + (end - start) / 2;

        if (wordList[midpoint] == query) {
            return true;
        }
        if (wordList[midpoint] < query) {
            start = midpoint + 1;
        } else {
            end = midpoint - 1;
        }
    }
    return false;
}

void triggerSuggestions(const vector<string>& wordList, const string& characters) {
    int start = 0;
    int end = wordList.size() - 1;
    int locationMarker = -1;

    while (start <= end) {
        int midpoint = start + (end - start) / 2;

        if (wordList[midpoint].compare(0, characters.length(), characters) == 0) {
            locationMarker = midpoint;
            end = midpoint - 1; 
        }
        else if (wordList[midpoint] < characters) {
            start = midpoint + 1;
        } else {
            end = midpoint - 1;
        }
    }

    if (locationMarker == -1) {
        cout << " No matches found for: " << characters << endl;
        return;
    }

    cout << " Suggested words:" << endl;
    for (int i = locationMarker; i < wordList.size(); i++) {
        if (wordList[i].compare(0, characters.length(), characters) != 0) {
            break;
        }
        cout << " -> " << wordList[i] << endl;
    }
}

int main() {
    vector<string> wordList = {
        "apple", "app", "application", "banana", "band", "bandwidth", 
        "code", "coder", "codeforces", "cpp", "data", "database", 
        "dynamic", "leet", "leetcode", "search", "sorting"
    };

    sort(wordList.begin(), wordList.end());

    cout << "--- TEXT SEARCH UTILITY ---" << endl;
    
    while (true) {
        int modeSelection;
        cout << "\n[1] Check Spelling\n[2] Get Auto-Suggestions\n[3] Quit\nSelection: ";
        cin >> modeSelection;

        if (modeSelection == 3) break;

        if (modeSelection == 1) {
            string inputWord;
            cout << "Type word: ";
            cin >> inputWord;
            if (verifyWordPresence(wordList, inputWord)) {
                cout << " Found in database." << endl;
            } else {
                cout << " Not found." << endl;
            }
        } 
        else if (modeSelection == 2) {
            string inputPrefix;
            cout << "Type starting letters: ";
            cin >> inputPrefix;
            triggerSuggestions(wordList, inputPrefix);
        }
    }
    return 0;
}