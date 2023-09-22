#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    string number, point = ".,";
    wcout << L"Введите целое число от 1 до 100: \n";
    cin >> number;

    int tmp, value = stoi(number);
    unsigned long long int fib[value];
    tmp = number.length();

    if (value > 100 || value < 1) {
        wcout << L"Число должно быть целым и лежать в пределах от 1 до 100: \n";
        exit(-1);
    }
    for (int i = tmp; i > 0; i--) {
        if (number[i - 1] == point[0] || number[i - 1] == point[1]) {
            wcout << L"Нельзя вводить нецелое число!";
            exit(-1);
        }
        if (!isdigit(number[i - 1])) {
            wcout << L"Введите число!";
            exit(-1);
        }
    }

    for (int i = 0; i < value; i++) {
        if (i == 0 || i == 1)
            fib[i] = 1;
        else
            fib[i] = fib[i-1] + fib[i-2];
        cout << fib[i] << " ";
    }
    return 0;
}
