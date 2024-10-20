#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int INITIAL_SIZE = 7;
const double LOAD_FACTOR_THRESHOLD = 0.7;

struct Product {
    int code;
    string name;
    double price;

    Product(int c = -1, string n = "", double p = 0.0) : code(c), name(n), price(p) {}
};

class HashTable {
    private:
        vector<Product> table;
        int size;
        int capacity;

        int hashFunction(int key) {
            return key % capacity;
        }

        void rehash() {
            if (static_cast<double>(size) / capacity >= LOAD_FACTOR_THRESHOLD) {
                int oldCapacity = capacity;
                capacity *= 2;
                vector<Product> newTable(capacity);

                for (const auto& product : table) {
                    if (product.code != -1) {
                        int newIndex = hashFunction(product.code);
                        while (newTable[newIndex].code != -1) {
                            newIndex = (newIndex + 1) % capacity;
                        }
                        newTable[newIndex] = product;
                    }
                }
                table = newTable;
                cout << "The table has been enlarged and rehashed. New size: " << capacity << endl;
            }
        }

    public:
        HashTable(int cap = INITIAL_SIZE) : size(0), capacity(cap) {
            table.resize(capacity);
        }

        void insertProduct(int code, const string& name, double price) {
            if (size >= capacity) {
                rehash();
            }
            int index = hashFunction(code);
            while (table[index].code != -1) {
                index = (index + 1) % capacity;
            }
            table[index] = Product(code, name, price);
            size++;
            cout << "New product has been added: code " << code << ", name: " << name << ", price: " << price << endl;
            rehash();
        }

        void searchProduct(int code) {
            int index = hashFunction(code);
            int startIndex = index;
            while (table[index].code != code) {
                index = (index + 1) % capacity;
                if (index == startIndex || table[index].code == -1) {
                    cout << "Product with code " << code << " has not been found." << endl;
                    return;
                }
            }
            cout << "Product has been found: code " << code << ", name: " << table[index].name << ", price: " << table[index].price << endl;
        }

        void deleteProduct(int code) {
            int index = hashFunction(code);
            int startIndex = index;
            while (table[index].code != code) {
                index = (index + 1) % capacity;
                if (index == startIndex || table[index].code == -1) {
                    cout << "Product with code " << code << " has not been found." << endl;
                    return;
                }
            }
            table[index] = Product();
            size--;
            cout << "Product with code " << code << " has been deleted." << endl;
        }

        void displayProducts() {
            cout << "Products:" << endl;
            for (const auto& product : table) {
                if (product.code != -1) {
                    cout << "Code: " << product.code << ", name: " << product.name << ", price: " << product.price << endl;
                }
            }
        }
};

void ui(HashTable& ht) {
    int choice;
    cout << endl;
    cout << "Enter the command:" << endl;
    cout << "1. Show the list of products" << endl;
    cout << "2. Find a product by code" << endl;
    cout << "3. Add a product" << endl;
    cout << "4. Delete a product" << endl;
    cout << "5. Exit" << endl;
    cin >> choice;
    cout << endl;

    switch (choice) {
        case 1:
            ht.displayProducts();
            break;
        case 2: {
            int code;
            cout << "Enter the code of the product: ";
            cin >> code;
            ht.searchProduct(code);
            break;
        }
        case 3: {
            int code;
            string name;
            double price;
            cout << "Enter the product code: ";
            cin >> code;
            cout << "Enter the product name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter the product price: ";
            cin >> price;
            ht.insertProduct(code, name, price);
            break;
        }
        case 4: {
            int code;
            cout << "Enter the code for deleting: ";
            cin >> code;
            ht.deleteProduct(code);
            break;
        }
        case 5:
            exit(0);
        default:
            cout << "Error!" << endl;
    }
}

int main() {
    HashTable ht;
    while (true) {
        ui(ht);
    }
    return 0;
}