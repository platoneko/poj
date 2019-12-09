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
#include <cstdio>
#include <algorithm>
using namespace std;

int array[100005];
int n;
int median;

bool check(int x) {
    int cnt = 0;
    for(int i=0; i<n; ++i) {
       int t = upper_bound(array, array+n, array[i]+x) - array;  // 比a[i]+x小的元素的个数
       cnt += (t-i-1);  // 排除a[i]之前的那些元素,共有i+1;
       if(cnt >= median) return true;  
    }
    return false;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i=0; i<n; ++i) {
            scanf("%d", &array[i]);
        }
        sort(array, array+n);
        int totalLength = n*(n-1)>>1;
        median = (totalLength+1)>>1;
        int leftVal = 0, rightVal = array[n-1] - array[0];
        int ans;
        while (leftVal <= rightVal) {
            int midVal = (leftVal+rightVal)>>1;
            if(check(midVal)) {
                ans = midVal;
                rightVal = midVal-1;
            } else {
                leftVal = midVal+1;
            }
         }
         printf("%d\n",ans);
    }
    return 0;
}