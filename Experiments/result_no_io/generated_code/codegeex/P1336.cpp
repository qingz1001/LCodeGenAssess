#include <stdio.h>
#include <math.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int A[20], B[20];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &A[i], &B[i]);
    }

    int min_time = INT_MAX;

    // 枚举每个课题的论文数量
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n; j++) {
            int remaining_papers = n - j;
            int time = A[i] * pow(j, B[i]);
            int min_papers = remaining_papers;
            for (int k = 0; k < m; k++) {
                if (k != i) {
                    int papers_for_k = remaining_papers / (m - 1);
                    time += A[k] * pow(papers_for_k, B[k]);
                    min_papers = fmin(min_papers, papers_for_k);
                }
            }
            remaining_papers -= min_papers;
            for (int k = 0; k < m; k++) {
                if (k != i) {
                    time += A[k] * pow(remaining_papers, B[k]);
                }
            }
            min_time = fmin(min_time, time);
        }
    }

    printf("%d\n", min_time);
    return 0;
}