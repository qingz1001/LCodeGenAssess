#include <stdio.h>
#include <stdlib.h>

int m, k;
int pages[500];
int result[500][2];

int can_allocate(int max_pages) {
    int current_pages = 0;
    int people_needed = 1;
    for (int i = 0; i < m; i++) {
        if (current_pages + pages[i] > max_pages) {
            people_needed++;
            current_pages = pages[i];
        } else {
            current_pages += pages[i];
        }
    }
    return people_needed <= k;
}

void allocate_books(int max_pages) {
    int current_pages = 0;
    int people_count = 0;
    int start = 0;
    for (int i = 0; i < m; i++) {
        if (current_pages + pages[i] > max_pages || (k - people_count == m - i)) {
            result[people_count][0] = start + 1;
            result[people_count][1] = i;
            people_count++;
            start = i;
            current_pages = pages[i];
        } else {
            current_pages += pages[i];
        }
    }
    result[people_count][0] = start + 1;
    result[people_count][1] = m;
}

int main() {
    scanf("%d %d", &m, &k);
    int total_pages = 0;
    int max_page = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d", &pages[i]);
        total_pages += pages[i];
        if (pages[i] > max_page) {
            max_page = pages[i];
        }
    }

    int left = max_page;
    int right = total_pages;
    while (left < right) {
        int mid = (left + right) / 2;
        if (can_allocate(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    allocate_books(left);

    for (int i = 0; i < k; i++) {
        printf("%d %d\n", result[i][0], result[i][1]);
    }

    return 0;
}