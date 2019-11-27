/*
Matrix Power Series

Description
Given a n ×n matrix A and a positive integer k, find the
sum S = A + A2 + A3 + … + Ak.
Input
The input contains exactly one test case. The first line of input contains
three positive integers n (n ≤ 30), k (k ≤ 109) and m (m < 104). Then
follow n lines each containing n nonnegative integers below 32,768,
giving A’s elements in row-major order.
Output
Output the elements of S modulo m in the same way as A is given.
Sample Input
2 2 4
0 1
1 1
Sample Output
1 2
2 3
*/
#include <iostream>
#define N 60
using namespace std;

void matmul(int A[N][N], int B[N][N], int n, int m);

int main() {
    int n, k, m;
    cin >> n >> k >> m;
    int A[N][N]={0}, B[N][N]={0};

    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            cin >> A[i][j];
            A[i][i+n] = A[i+n][i+n] = B[i][i] = B[i+n][i+n] = 1;
        }
    }
    ++k;
    /* 矩阵快速幂乘 */
    while (k > 0) {
        if (k&1) matmul(B, A, n, m);
        k >>= 1;
        matmul(A, A, n, m);
    }
    for (i = 0; i < n; ++i)
        --B[i][i+n];
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n-1; ++j) {
            cout << (B[i][j+n] < 0 ? B[i][j+n]+m : B[i][j+n]) << " ";
        }
        cout << (B[i][j+n] < 0 ? B[i][j+n]+m : B[i][j+n]) << endl;
    }
    return 0;
}

void matmul(int A[N][N], int B[N][N], int n, int m) {
    /* A <- A*B */
    n <<= 1;
    int C[N][N] = {0};
    /* i k j cache hint++ */
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            int Aik = A[i][k];
            for (int j = 0; j < n; ++j) {
                C[i][j] = (C[i][j] + Aik * B[k][j]) % m;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = C[i][j];
        }
    }
}