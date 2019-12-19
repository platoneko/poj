#include<iostream>
#include<cstring>
#define N 100+5
using namespace std;

void solution(int A[N][N], int n);

int main() {
    int A[N][N] = {0};
    int n;
    cin >> n;
    for (int i=1; i <= n; ++i) {
        for (int j=1; j <= n; ++j) {
            cin >> A[i][j];
        }
    }
    solution(A, n);
    return 0;
}

void solution(int A[N][N], int n) {
    int maxi= 0x80000000;
    int sum[N] = {0};
    int tmp[N] = {0};
    for (int i=1; i <= n; ++i) {
        memset(sum, 0, sizeof(sum));
        memset(tmp, 0, sizeof(tmp));
        for (int k=i; k <= n; ++k) {
            for (int j=1; j <= n; ++j) {
                tmp[j] += A[k][j];
                if (sum[j-1] >= 0) {
                    sum[j] = sum[j-1]+tmp[j];
                } else {
                    sum[j] = tmp[j];
                } 
                maxi = sum[j] > maxi ? sum[j] : maxi;
            }
        }
    }
    cout << maxi <<endl;
}