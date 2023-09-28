#include <iostream>
#include <ctime>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

int default_check(int number){
    if (abs(number) % 2 == 1)
        return 1;
    else
        return 0;
}

int odd(int number) {
    int tmp;
    tmp = number >> 1;
    if (number == (tmp << 1))
        return 0;
    else
        return 1;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int number;
    clock_t bench_start, bench_end;
    wcout << L"Введите число:\n";
    cin >> number;

//    if (default_check(number))
//        wcout << number << L" - нечетное\n";
//    else
//        wcout << number << L" - четное\n";
//    if (odd(number))
//        wcout << number << L" - нечетное\n";
//    else
//        wcout << number << L" - четное\n";

    bench_start = clock();
    for (int i = 0; i < 9999999; i++)
        default_check(number);
    bench_end = clock();
    double req_time = double(bench_end - bench_start) / (9999999 * double(CLOCKS_PER_SEC));
    cout << req_time << "\n";

    bench_start = clock();
    for (int i = 0; i < 999999999; i++)
        odd(number);
    bench_end = clock();
    req_time = double(bench_end - bench_start) / (9999999 * double(CLOCKS_PER_SEC));
    cout << req_time << "\n";
    return 0;
}
