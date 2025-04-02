#include <iostream>
#include <string>

using namespace std;

constexpr char operators[4] = {'*', '/', '+', '-'};

// Simple algorithm to check if an item is in a list.
bool listContains(auto toFind, auto list[]) {
    bool found = false;
    for (int i = 0; i < strlen(list); i++) {
        if (toFind == list[i]) {
            found = true;
        }
    }
    return found;
}

// Find all the indexes of the operator in the operators variable in the string
vector<int> findIndexesOfOperatorsInString(const string& theString) {
    vector<int> indexes;
    for (int i = 0; i < strlen(theString.c_str()); i++) {
        if (listContains(theString[i], operators)) indexes.push_back(i);
    }
    return indexes;
}

string getStringBetweenIndexes(const string& input, const int startIndex, const int endIndex) {
    string output;
    for (int i = startIndex + 1; i < endIndex; i++) {
        output += input[i];
    }
    //debug
    cout << "Output: " << output << endl;

    return output;
}

int main() {
    // Get input

    cout << "(*,/,+,-)" << endl <<"Enter the calculation you want to perform: " << endl;
    //cin >> input;
    string input;
    // Use this function to get the entire line of the input... :3
    getline(cin, input);

    // Check all characters are valid characters
    bool validInput = true;

    for (int i = 0; i < input.length(); i++) {
        if (!(isdigit(input[i]) || listContains(input[i], operators) || input[i] == ' ' || input[i] == '.')) {
            validInput = false;
        }

    }

    if (!validInput) {
        cout << "Invalid input!" << endl;
        return 1;
    }

    vector<int> indexes = findIndexesOfOperatorsInString(input);

    for (int i = 0; i < indexes.size(); i++) {
        cout << i << ": " << indexes[i] << endl;
    }


    // Splitting the numbers and what operators to use as well as using them i n calculations
    for (int o = 0; o < strlen(operators); o++) {
        for (int i = 0; i < indexes.size(); i++) {
            if (input[indexes[i]] == operators[o]) {
                // Uses functions to get the string between two indexes: getStringBetweenIndexes()
                string numString1 = getStringBetweenIndexes(input, i-1 < 0 ? -1 : indexes[i - 1], indexes[i]);
                string numString2 = getStringBetweenIndexes(input, indexes[i], i + 1 > indexes.size() ? input.length() : indexes[i + 1]);

                //Debug
                cout << numString1 << endl;
                cout << numString2 << endl;

                float num1 = stof(numString1);
                float num2 = stof(numString2);
                float ans;

                // Doing calculation based on the operator
                switch (operators[o]) {
                    case '*': ans = num1 * num2; break;
                    case '/': ans = num1 / num2; break;
                    case '+': ans = num1 + num2; break;
                    case '-': ans = num1 - num2; break;
                    default: {
                        //If another letter is not identified as an ooperator
                        cout << "Invalid operator!" << endl;
                        ans = 0;
                    }
                }

                input.erase(i < 0 ? 0 : indexes[i - 1], i + 1 > indexes.size() ? input.length() : indexes[i + 1]);
                input.insert(i < 0 ? 0 : indexes[i - 1], to_string(ans));
                indexes = findIndexesOfOperatorsInString(input);
            }
        }
    }


    cout << input << endl;

    return 0;
}
