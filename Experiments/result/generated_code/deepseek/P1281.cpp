#include <stdio.h>
#include <stdlib.h>

int m, k;
int pages[500];

int can_finish_in_time(int max_pages) {
    int current_pages = 0;
    int people_needed = 1;
    for (int i = 0; i < m; i++) {
        if (current_pages + pages[i] <= max_pages) {
            current_pages += pages[i];
        } else {
            people_needed++;
            current_pages = pages[i];
        }
    }
    return people_needed <= k;
}

void assign_books(int max_pages) {
    int current_pages = 0;
    int people_assigned = 0;
    int start = 0;
    for (int i = 0; i < m; i++) {
        if (current_pages + pages[i] > max_pages || (m - i - 1) < (k - people_assigned - 1)) {
            printf("%d %d\n", start + 1, i);
            start = i;
            current_pages = pages[i];
            people_assigned++;
        } else {
            current_pages += pages[i];
        }
    }
    printf("%d %d\n", start + 1, m);
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
    int result = right;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (can_finish_in_time(mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    assign_books(result);

    return 0;
}