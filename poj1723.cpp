/*
SOLDIERS

Description
N soldiers of the land Gridland are randomly scattered around the country.A
position in Gridland is given by a pair (x,y) of integer coordinates. Soldiers
can move - in one move, one soldier can go one unit up, down, left or right
(hence, he can change either his x or his y coordinate by 1 or -1).
The soldiers want to get into a horizontal line next to each other (so that
their final positions are (x,y), (x+1,y), ..., (x+N-1,y), for some x and y).
Integers x and y, as well as the final order of soldiers along the horizontal
line is arbitrary.
The goal is to minimise the total number of moves of all the soldiers that
takes them into such configuration.
Two or more soldiers must never occupy the same position at the same
time.
Input
The first line of the input contains the integer N, 1 <= N <= 10000, the
number of soldiers.
The following N lines of the input contain initial positions of the soldiers :
for each i, 1 <= i <= N, the (i+1)st line of the input file contains a pair of
integers x[i] and y[i] separated by a single blank character, representing the
coordinates of the ith soldier, -10000 <= x[i],y[i] <= 10000.
Output
The first and the only line of the output should contain the minimum total
number of moves that takes the soldiers into a horizontal line next to each
other.
Sample Input
5
1 2
2 2
1 3
3 -2
3 3
Sample Output
8
*/
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

void solution(int n, int *x, int *y);
int select(int n, int begin, int end, int *array);

int main() {
    int n;
    cin >> n;
    int x[n], y[n];
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    solution(n, x, y);
    return 0;
}

void solution(int n, int *x, int *y) {
    int xMedian, yMedian;
    int mid = (n-1)/2;  // 下中位数下标
    sort(x, x+n);
    yMedian = select(mid, 0, n, y);
    // cout << "yMedian " << yMedian << endl; 
    for (int i = 0; i < n; ++i) {
        x[i] -= i;
    }
    xMedian = select(mid, 0, n, x);
    // sort(x, x+n);
    // sort(y, y+n);
    int xSum = 0, ySum = 0;
    for (int i = 0; i < n; ++i) {
        xSum += abs(x[i] - xMedian);
        ySum += abs(y[i] - yMedian);
    }
    cout << xSum + ySum << endl;
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
