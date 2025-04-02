#include <iostream>
#include <string>

using namespace std;

char operators[4] = {'*', '/', '+', '-'};


bool listContains(auto toFind, auto list[]) {
    bool found = false;
    for (int i = 0; i < strlen(list); i++) {
        if (toFind == list[i]) {
            found = true;
        }
    }
    return found;
}

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
    return output;
}

int main() {
    // Get input

    cout << "(*,/,+,-)" << endl <<"Enter the calculation you want to perform: " << endl;
    string input;
    cin >> input;

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

    /*respace:
    for (int i = 0; i < input.length(); i++) {
        if (listContains(input[i], operators) && !(input[i-1] == ' ' && input[i+1] == ' ')) {
            if (input[i - 1] != ' ') input.insert(i, " ");
            if (input[i + 1] != ' ') input.insert(i + 1, " ");
            goto respace;
        }
    }*/

    vector<int> indexes = findIndexesOfOperatorsInString(input);

    for (int i = 0; i < indexes.size(); i++) {
        cout << indexes[i] << endl;
    }

    for (int o = 0; o < strlen(operators); o++) {
        for (int i = 0; i < indexes.size(); i++) {
            if (input[indexes[i]] == operators[o]) {
                cout << o << ',' << i << endl;
                string numString1 = getStringBetweenIndexes(input, i < 0 ? 0 : indexes[i - 1], indexes[i]);
                string numString2 = getStringBetweenIndexes(input, indexes[i], i > indexes.size() ? input.length() : indexes[i + 1]);
cout << numString1 << endl;
                cout << numString2 << endl;

                float num1 = stof(numString1);
                float num2 = stof(numString2);
                float ans;

                switch (operators[o]) {
                    case '*': ans = num1 * num2;
                    case '/': ans = num1 / num2;
                    case '+': ans = num1 + num2;
                    case '-': ans = num1 - num2;
                    default: {
                        cout << "Invalid operator!" << endl;
                        ans = 0;
                    }
                }

                input.erase(i < 0 ? 0 : indexes[i - 1], i > indexes.size() ? input.length() : indexes[i + 1]);
                input.insert(i < 0 ? 0 : indexes[i - 1], to_string(ans));
            }
        }
    }


    cout << input << endl;

    return 0;
}
