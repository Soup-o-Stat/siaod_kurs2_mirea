#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

int global_num_of_phones = 0;
vector<streampos> offset_table;  // Таблица смещений

// Генерация файла с номерами телефонов
void create_file() {
    vector<string> used_phonenumbers;
    srand(static_cast<unsigned int>(time(0)));
    ofstream file("common_file.txt");
    int num_of_strings = 0;
    cout << "Enter number of phone numbers: " << endl;
    cin >> num_of_strings;
    global_num_of_phones = num_of_strings;
    cout << endl;

    for (int i = 0; i < num_of_strings; i++) {
        int randomNumber1 = 10 + rand() % (99 - 10 + 1);
        int randomNumber2 = 100 + rand() % (999 - 100 + 1);
        int randomNumber3 = 1000 + rand() % (9000 - 10 + 1);
        string phonenumber = "89" + to_string(randomNumber1) + to_string(randomNumber2) + to_string(randomNumber3);
        if (find(used_phonenumbers.begin(), used_phonenumbers.end(), phonenumber) == used_phonenumbers.end()) {
            used_phonenumbers.push_back(phonenumber);
        } else {
            cout << phonenumber << " has been used. DETERMINATE THIS!!!" << endl;
            i--;
        }
    }
    sort(used_phonenumbers.begin(), used_phonenumbers.end());
    for (const auto& number : used_phonenumbers) {
        file << number << endl;
    }
    file.close();
}

void mega_converter(const string& ntext_file, const string& nbinary_file) {
    ifstream text_file(ntext_file);
    ofstream binary_file(nbinary_file, ios::binary);

    if (text_file.is_open() && binary_file.is_open()) {
        string line;
        while (getline(text_file, line)) {
            streampos pos = binary_file.tellp();  // Получаем текущее смещение в файле
            offset_table.push_back(pos);          // Записываем это смещение в таблицу
            line.resize(20, '\0');                // Удлиняем строку до 20 символов
            binary_file.write(line.c_str(), 20);  // Записываем ровно 20 символов
        }
        text_file.close();
        binary_file.close();

        // Сохраняем таблицу смещений
        ofstream offset_file("offset_table.bin", ios::binary);
        for (const auto& offset : offset_table) {
            offset_file.write(reinterpret_cast<const char*>(&offset), sizeof(streampos));
        }
        offset_file.close();

        cout << "Converted file successfully and saved offset table!" << endl;
    } else {
        cout << "File could not be opened!" << endl;
    }
}

void load_offset_table(const string& offset_file) {
    ifstream file(offset_file, ios::binary);
    if (file.is_open()) {
        offset_table.clear();
        streampos offset;
        while (file.read(reinterpret_cast<char*>(&offset), sizeof(streampos))) {
            offset_table.push_back(offset);
        }
        file.close();
    } else {
        cerr << "Failed to load offset table!" << endl;
    }
}

int bin_file_search() {
    string key;
    cout << "Binary search using offset table" << endl;
    cout << "Enter phone number (key): " << endl;
    cin >> key;
    auto start_time = high_resolution_clock::now();
    ifstream file("common_file.bin", ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening binary file!" << endl;
        return -1;
    }
    int left = 0;
    int right = global_num_of_phones - 1;
    const int record_size = 20;
    char buffer[record_size + 1];
    while (left <= right) {
        int mid = left + (right - left) / 2;
        streampos pos = offset_table[mid];
        file.seekg(pos);
        file.read(buffer, record_size);
        buffer[record_size] = '\0';
        string current_number(buffer);
        current_number = current_number.substr(0, current_number.find('\0'));
        if (current_number == key) {
            cout << "Phone number found!" << endl;
            cout << current_number << endl;
            auto end_time = high_resolution_clock::now();
            duration<double> elapsed = end_time - start_time;
            cout << "Search completed in: " << elapsed.count() << " seconds." << endl;
            return 0;
        } else if (current_number < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << "Phone number not found! (¬_¬)" << endl;
    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << "Search completed in: " << elapsed.count() << " seconds." << endl;

    return 0;
}

int main() {
    string mode;
    create_file();
    mega_converter("common_file.txt", "common_file.bin");

    // Загружаем таблицу смещений для бинарного поиска
    load_offset_table("offset_table.bin");

    cout << "Enter mode (Binary with offset table)" << endl;
    cin >> mode;

    if (mode == "Binary") {
        bin_file_search();
    }

    return 0;
}
