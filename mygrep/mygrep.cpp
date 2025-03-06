#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <exception>

using namespace std;

// Funktio muuntaa merkkijonon pieniksi kirjaimiksi
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

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
    else if (argc >= 3) { // Komentoriviargumentit käytössä
        string searchString = argv[1];
        string filename = argv[argc - 1];

        bool ignoreCase = false;
        bool reverseSearch = false;
        bool countNonMatching = false;

        for (int i = 2; i < argc - 1; i++) {
            string option = argv[i];
            if (option == "-i") ignoreCase = true;
            if (option == "-r") reverseSearch = true;
            if (option == "-o") countNonMatching = true;
        }

        if (ignoreCase) {
            searchString = toLowerCase(searchString);
        }

        try {
            ifstream file(filename);
            if (!file) {
                throw runtime_error("Error: Could not open file " + filename);
            }

            string line;
            int lineNumber = 0;
            int matchCount = 0;
            int nonMatchCount = 0;

            while (getline(file, line)) {
                lineNumber++;
                string processedLine = ignoreCase ? toLowerCase(line) : line;
                bool found = (processedLine.find(searchString) != string::npos);

                if ((found && !reverseSearch) || (!found && reverseSearch)) {
                    cout << lineNumber << ": " << line << "\n";
                    matchCount++;
                }
                if (!found) {
                    nonMatchCount++;
                }
            }

            cout << "Occurrences of lines " << (reverseSearch ? "NOT " : "") << "containing \"" << searchString << "\": " << matchCount << "\n";
            if (countNonMatching) {
                cout << "Occurrences of lines NOT containing \"" << searchString << "\": " << nonMatchCount << "\n";
            }

            file.close();
        }
        catch (const exception& e) {
            cerr << "An exception occurred: " << e.what() << "\n";
            return 1;
        }
    }
    else {
        cerr << "Usage: ./mygrep [search_string] [-i] [-r] [-o] [filename]" << endl;
        return 1;
    }

    return 0;
}