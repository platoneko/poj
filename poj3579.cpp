/*
Median

Description
Given N numbers, X1, X2, ... , XN, let us calculate the difference of every pair
of numbers: ∣ Xi - Xj∣ (1 ≤ i ＜ j ≤ N). We can get C(N,2) differences
through this work, and now your task is to find the median of the differences
as quickly as you can!
Note in this problem, the median is defined as the (m/2)-th smallest number
if m,the amount of the differences, is even. For example, you have to find
the third smallest one in the case of m = 6.
Input
The input consists of several test cases.
In each test case, N will be given in the first line. Then N numbers are given,
representing X1, X2, ... , XN, ( Xi ≤ 1,000,000,000 3 ≤ N ≤ 1,00,000 )
Output
For each test case, output the median in a separate line.
Sample Input
4
1 3 2 4
3
1 10 2
Sample Output
1 8
*/
#include <iostream>
#include <cmath>
using namespace std;

void solution(int n, int *array);
int select(int n, int begin, int end, int *array);

int main() {
    int n;
    while (cin >> n) {
        int array[n];
        for (int i = 0; i < n; ++i) {
            cin >> array[i];
        }
        solution(n, array);
    }
    cout << endl;
    return 0;
}

void solution(int n, int *array) {
    int size = n*(n-1)/2;
    cout << "size " << size << endl;
    int diffArray[size];
    for (int i = 0, k = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            diffArray[k++] = abs(array[i] - array[j]);
        }
    }
    cout << select((size-1)/2, 0, size, diffArray) << " ";
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
