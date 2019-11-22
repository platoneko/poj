#include <iostream>
#include <random>
#include <algorithm>
#include <cassert>
using namespace std;

void exchange(int &a, int &b);
int select(int n, int begin, int end, int *array);

int main() {
    for (int i = 0; i < 10000; ++i) {
        int n = rand() % 20;
        int array[n];
        int array_copy_1[n];
        int array_copy_2[n];
        for (int j = 0; j < n; ++j) {
            array[j] = rand() % 1000;
            array_copy_1[j] = array[j];
            array_copy_2[j] = array[j];
        }
        sort(array_copy_1, array_copy_1+n);
        for (int k = 0; k < n; ++k) {
            cout << array[k] << " ";
        }
        cout << endl;
        int median = select((n-1)/2, 0, n, array_copy_2);
        if (array_copy_1[(n-1)/2] != median) {
            cout << "wrong answer in " << i << endl;
            cout << "expect " << array_copy_1[(n-1)/2] << " , however get " << median << endl;
            for (int k = 0; k < n; ++k) {
                cout << array[k] << " ";
            }
            cout << endl;
            return -1;
        }
    }
    return 0;
}

inline void exchange(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int select(int n, int begin, int end, int *array) {
    int pivot = array[begin];
    int left = begin, right = end;
    while (left < right) {
        while (--right > left && array[right] >= pivot);
        exchange(array[left], array[right]);   
        while (left < right && array[++left] <= pivot);
        exchange(array[left], array[right]);    
    }
    // assert(left == right);
    if (left == n) return array[left];
    if (n < left) return select(n, begin, left, array);
    else return select(n, left+1, end, array);
}