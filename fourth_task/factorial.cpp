#include <iostream>
#include <string.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    
    string number, hyp = "-", point = ".,";
    int i, tmp, size;
    wcout << L"Введите число: \n";
    cin >> number;
    tmp = number.length();
    
    if (number[0] == hyp[0]) {
        wcout << L"Нельзя вводить отрицательное число!";
        exit(-1);
    }
    for (i = 0; i < tmp; i++){
        if (number[i] == point[0] || number[i] == point[1]) {
            wcout << L"Нельзя вводить нецелое число!";
            exit(-1);
        }
        if (!isdigit(number[i])) {
            wcout << L"Введите число!";
            exit(-1);
        }
    }
    
    size = stoi(number);
    long long int fact[size + 1];
    if (size > 20) {
        wcout << L"Заданное число слишком велико!";
        exit(-1);
    }
    
    for(int j = 0; j < size + 1; j++) {
        if (j == 0)
            fact[j] = 1;
        else
            fact[j] = fact[j-1] * j;
    }
    cout << fact[size];
    return 0;
}
