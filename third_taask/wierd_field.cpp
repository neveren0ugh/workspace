#include <iostream>

using namespace std;


int main( void ) {
    setlocale(LC_ALL, "Russian");
    wcout << L"Загадайте слово:\n";
    string word, curr_str = "", hyp = "-", attempt;
    int size, is_solved = 0, met_letter = 0;
    cin >> word;
    size = word.size();
    for (int tmp = size; tmp > 0; tmp--) {
        curr_str += hyp;
    }
    cout << curr_str << "\n";
    wcout << L"Введите букву:\n";

    while (!is_solved) {
        int tmp = size;
        cin >> attempt;
        if (attempt.size() != 1) {
            wcout << L"Вводите по одной букве!\n";
        }
        else {
            for (tmp; tmp > -1; tmp--) {
                if (word[tmp] == attempt[0]) {
                    curr_str[tmp] = attempt[0];
                    met_letter = 1;
                }
            }
            if (!met_letter) {
                wcout << L"Такой буквы нет!\n";
            }
            else {
                wcout << L"Такая буква есть в слове!\n";
                cout << curr_str << "\n";
            }
            met_letter = 0;
        }
        is_solved = 1;
        tmp = size;
        for (tmp; tmp > -1; tmp--) {
            if (curr_str[tmp] == hyp[0]){
                is_solved = 0;
            }
        }
    }
    wcout << L"Вы угадали слово!";
}
