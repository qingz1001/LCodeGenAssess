#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int rooms = 0;
    int i = 0;
    while (i < n) {
        int count1 = 0, count2 = 0;
        int j = i;
        while (j < n) {
            if (arr[j] == 1) count1++;
            else count2++;
            if (count1 > 0 && count2 > 0 && (count1 - count2 > m || count2 - count1 > m)) {
                break;
            }
            j++;
        }
        rooms++;
        i = j;
    }

    printf("%d\n", rooms);
    return 0;
}