#include <stdio.h>
#include <math.h>

int getSequenceDigit(long long position) {
    long long group = 1;
    long long groupSize = 3;
    long long totalSize = 3;

    while (totalSize < position) {
        group++;
        groupSize = group * 2 + 1;
        totalSize += groupSize;
    }

    long long offset = position - (totalSize - groupSize);
    
    if (offset == 1) return 1;
    if (offset <= group + 1) return 0;
    return 1;
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        long long A;
        scanf("%lld", &A);
        printf("%d\n", getSequenceDigit(A));
    }

    return 0;
}