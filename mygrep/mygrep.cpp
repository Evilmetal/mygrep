#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1) { // Käyttäjä antaa syötteet käsin
        string bigString, searchString;

        cout << "Give a string from which to search for: ";
        getline(cin, bigString);

        cout << "Give search string: ";
        getline(cin, searchString);

        size_t found = bigString.find(searchString);

        if (found != string::npos) {
            cout << "\"" << searchString << "\" found in \"" << bigString << "\" in position " << found << "\n";
        }
        else {
            cout << "\"" << searchString << "\" NOT found in \"" << bigString << "\"\n";
        }
    }
    else if (argc == 3) { // Komentoriviargumentit käytössä
        string searchString = argv[1];
        string filename = argv[2];
        ifstream file(filename);

        if (!file) {
            cerr << "Error: Could not open file " << filename << "\n";
            return 1;
        }

        string line;
        while (getline(file, line)) {
            if (line.find(searchString) != string::npos) {
                cout << line << "\n";
            }
        }
        file.close();
    }
    else {
        cerr << "Usage: ./mygrep [search_string filename]" << endl;
        return 1;
    }

    return 0;
}