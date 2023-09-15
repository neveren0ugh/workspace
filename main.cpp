#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int arr[5], size_arr, arr3[5], counter;
    cout << size(arr) << '\n';
    size_arr = 5;
    int * arr1 =(int*) calloc(size_arr, sizeof(int));
    int * arr2 = (int*) malloc(size_arr);
    int sum = 0;
    for (counter = 0; counter < 5; counter++){
        cin >> arr3[counter];
    }
    return 0;
}