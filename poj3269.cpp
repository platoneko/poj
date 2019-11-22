/*
Building A New Barn

Description
After scrimping and saving for years, Farmer John has decided to build a
new barn. He wants the barn to be highly accessible, and he knows the
coordinates of the grazing spots of all N (2 ≤ N ≤ 10,000 cows. Each grazing
spot is at a point with integer coordinates (Xi, Yi) (-10,000 ≤ Xi ≤ 10,000;
-10,000 ≤ Yi ≤ 10,000). The hungry cows never graze in spots that are
horizontally or vertically adjacent.
The barn must be placed at integer coordinates and cannot be on any cow's
grazing spot. The inconvenience of the barn for any cow is given the
Manhattan distance formula | X - Xi | + | Y - Yi|, where (X, Y) and (Xi, Yi) are
the coordinates of the barn and the cow's grazing spot, respectively. Where
should the barn be constructed in order to minimize the sum of its
inconvenience for all the cows?
Input
Line 1: A single integer: N
Lines 2..N+1: Line i+1 contains two space-separated integers which are the
grazing location (Xi, Yi) of cow i
Output
Line 1: Two space-separated integers: the minimum inconvenience for the
barn and the number of spots on which Farmer John can build the barn to
achieve this minimum.
Sample Input
4
1 -3
0 1
-2 1
1 -1
Sample Output
10 4
*/
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
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
    int xMed, yMed;
    int mid = (n-1)/2;  // 下中位数下标
    int xCopy[n], yCopy[n];
    memcpy(xCopy, x, sizeof(xCopy));
    memcpy(yCopy, y, sizeof(yCopy));
    yMed = select(mid, 0, n, yCopy);
    xMed = select(mid, 0, n, xCopy);
    // sort(x, x+n);
    // sort(y, y+n);
    int xSum = 0, ySum = 0, occupied = 0;
    if (n % 2) {
        for (int i = 0; i < n; ++i) {
            xSum += abs(x[i] - xMed);
            ySum += abs(y[i] - yMed);
            if (x[i] == xMed && y[i] == yMed) ++occupied;
        }
        if (occupied) {
            int xLeftSum = 0, xRightSum = 0, yUpSum = 0, yDownSum = 0;
            for (int i = 0; i < n; ++i) {
                xRightSum += abs(x[i] - (xMed+1));
                xLeftSum += abs(x[i] - (xMed-1));
                yUpSum += abs(y[i] - (yMed+1));
                yDownSum += abs(y[i] - (yMed-1));
            }
            int sum[4], solNum = 1;
            sum[0] = xRightSum + ySum;
            sum[1] = xLeftSum + ySum;
            sum[2] = xSum + yUpSum;
            sum[3] = xSum + yDownSum;
            sort(sum, sum+4);
            solNum += (sum[0] == sum[1]) + (sum[0] == sum[2]) + (sum[0] == sum[3]);
            cout << sum[0] << " " << solNum << endl;
        } else {
            cout << xSum + ySum << " " << 1 << endl;
        }
    } else {
        int xUpMed = select(mid+1, 0, n, xCopy);
        int yUpMed = select(mid+1, 0, n, yCopy);
        if (xUpMed == xMed && yUpMed == yMed) {
            for (int i = 0; i < n; ++i) {
                xSum += abs(x[i] - xMed);
                ySum += abs(y[i] - yMed);
                if (x[i] == xMed && y[i] == yMed) ++occupied;
            }
            if (occupied) {
                int xLeftSum = 0, xRightSum = 0, yUpSum = 0, yDownSum = 0;
                for (int i = 0; i < n; ++i) {
                    xRightSum += abs(x[i] - (xMed+1));
                    xLeftSum += abs(x[i] - (xMed-1));
                    yUpSum += abs(y[i] - (yMed+1));
                    yDownSum += abs(y[i] - (yMed-1));
                }
                int sum[4], solNum = 1;
                sum[0] = xRightSum + ySum;
                sum[1] = xLeftSum + ySum;
                sum[2] = xSum + yUpSum;
                sum[3] = xSum + yDownSum;
                sort(sum, sum+4);
                solNum += (sum[0] == sum[1]) + (sum[0] == sum[2]) + (sum[0] == sum[3]);
                cout << sum[0] << " " << solNum << endl;
            } else {
                cout << xSum + ySum << " " << 1 << endl;
            } 
        } else {
            for (int i = 0; i < n; ++i) {
                xSum += abs(x[i] - xMed);
                ySum += abs(y[i] - yMed);
                if ((x[i] == xMed && y[i] == yMed) ||
                    (x[i] == xMed && y[i] == yUpMed) ||
                    (x[i] == xUpMed && y[i] == yMed) ||
                    (x[i] == xUpMed && y[i] == yUpMed)) 
                    ++occupied;
            }
            cout << xSum + ySum << " " << (xUpMed-xMed+1) * (yUpMed-yMed+1) - occupied << endl; 
        }
    } 
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
