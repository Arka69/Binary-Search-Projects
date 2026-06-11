#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Standard struct for storing the core dataset
struct Product {
    int sku;
    string name;
    double price;
};

// Index mapping structure to keep main array intact while sorting keys
struct IndexPair {
    int key;
    int originalIdx; 
};

// Comparator for sorting our index map based on SKU values
bool comparePairs(const IndexPair& a, const IndexPair& b) {
    return a.key < b.key;
}

// Clean binary search implementation operating over the mapped index table
int findProductIndex(const vector<IndexPair>& indexTable, int targetSku) {
    int low = 0;
    int high = indexTable.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (indexTable[mid].key == targetSku) {
            return indexTable[mid].originalIdx; 
        }
        if (indexTable[mid].key < targetSku) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; 
}

int main() {
    // Mock inventory dataset
    vector<Product> inventory = {
        {8812, "Gaming Laptop", 1200.50},
        {1045, "Mechanical Keyboard", 85.00},
        {4432, "Wireless Mouse", 45.25},
        {2201, "UltraWide Monitor", 349.99}
    };

    // Creating a separate index mapping array to allow binary search over an unsorted main database
    vector<IndexPair> indexTable;
    for (int i = 0; i < inventory.size(); i++) {
        indexTable.push_back({inventory[i].sku, i});
    }

    // Sort the index map based on SKU values
    sort(indexTable.begin(), indexTable.end(), comparePairs);

    cout << "--- Inventory Management System ---" << endl;

    int targetSku;
    cout << "\nEnter Item SKU to search: ";
    cin >> targetSku;

    int resultIdx = findProductIndex(indexTable, targetSku);

    if (resultIdx != -1) {
        cout << "\n[SUCCESS] Item found in database." << endl;
        cout << "Item Name: " << inventory[resultIdx].name << endl;
        cout << "Price:     $" << inventory[resultIdx].price << endl;
    } else {
        cout << "\n[ERROR] SKU not found." << endl;
    }

    return 0;
}
