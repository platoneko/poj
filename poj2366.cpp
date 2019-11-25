#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    int m, n;
    scanf("%d", &m);
    int A[m];
    for (int i = 0; i < m; ++i) {
        scanf("%d", &A[i]);
    }
    scanf("%d", &n);
    int B[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &B[i]);
    }
    for (int i = 0; i < n; ++i) {
        int left = 10000 - B[i];
        if (binary_search(A, A+m, left)) {
            printf("YES\n");
            return 0;
        }
    }
    printf("NO\n");
    return 0;
}
