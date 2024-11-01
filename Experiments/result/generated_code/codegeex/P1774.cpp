#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// 归并排序的辅助函数
void merge(int *a, ll *b, int l, int mid, int r) {
    int i = l, j = mid + 1, k = l;
    int *tmp = (int *)malloc(sizeof(int) * (r - l + 1));
    ll *cnt = (ll *)malloc(sizeof(ll) * (r - l + 1));
    for (int t = 0; t < r - l + 1; t++) cnt[t] = 0;

    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            tmp[k - l] = a[i];
            b[i]++;
            cnt[k - l]++;
            i++;
        } else {
            tmp[k - l] = a[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        tmp[k - l] = a[i];
        b[i]++;
        cnt[k - l]++;
        i++;
        k++;
    }

    while (j <= r) {
        tmp[k - l] = a[j];
        j++;
        k++;
    }

    for (int t = 0; t < r - l + 1; t++) {
        a[l + t] = tmp[t];
        if (t > 0) b[l + t] += cnt[t - 1];
    }

    free(tmp);
    free(cnt);
}

// 归并排序
void merge_sort(int *a, ll *b, int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;
        merge_sort(a, b, l, mid);
        merge_sort(a, b, mid + 1, r);
        merge(a, b, l, mid, r);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(sizeof(int) * n);
    ll *b = (ll *)malloc(sizeof(ll) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i] = 0;
    }

    merge_sort(a, b, 0, n - 1);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += b[i];
    }

    printf("%lld\n", ans);

    free(a);
    free(b);

    return 0;
}