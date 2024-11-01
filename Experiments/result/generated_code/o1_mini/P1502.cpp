#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long x;
    long y;
    long l;
} Star;

// Comparison function for sorting by x, then by y
int cmp_x(const void *a, const void *b) {
    Star *s1 = (Star*)a;
    Star *s2 = (Star*)b;
    if (s1->x != s2->x)
        return (s1->x < s2->x) ? -1 : 1;
    if (s1->y != s2->y)
        return (s1->y < s2->y) ? -1 : 1;
    return 0;
}

// Comparison function for sorting by y
int cmp_y(const void *a, const void *b) {
    Star *s1 = (Star*)a;
    Star *s2 = (Star*)b;
    if (s1->y != s2->y)
        return (s1->y < s2->y) ? -1 : 1;
    return 0;
}

// Function to insert a star into the y-sorted array
void insert_sorted_y(Star *arr, int *m, Star s) {
    int left = 0, right = *m;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].y < s.y)
            left = mid + 1;
        else
            right = mid;
    }
    for(int i = *m; i > left; i--) {
        arr[i] = arr[i-1];
    }
    arr[left] = s;
    (*m)++;
}

// Function to remove a star from the y-sorted array
void remove_sorted_y(Star *arr, int *m, Star s) {
    int left = 0, right = *m - 1;
    int pos = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].y == s.y) {
            // Search for the exact star
            int temp = mid;
            while (temp >= left && arr[temp].y == s.y) temp--;
            temp++;
            while (temp <= right && arr[temp].y == s.y) {
                if (arr[temp].x == s.x && arr[temp].l == s.l) {
                    pos = temp;
                    break;
                }
                temp++;
            }
            if (pos != -1)
                break;
            left = mid + 1;
        }
        else if (arr[mid].y < s.y)
            left = mid + 1;
        else
            right = mid - 1;
    }
    if(pos != -1){
        for(int i = pos; i < (*m) - 1; i++) {
            arr[i] = arr[i+1];
        }
        (*m)--;
    }
}

// Function to calculate maximum sum in y-window
long calculate_max_y_sum(Star *arr, int m, long H){
    long max_sum = 0;
    long current_sum = 0;
    int start = 0, end = 0;
    while(start < m){
        while(end < m && arr[end].y < arr[start].y + H){
            current_sum += arr[end].l;
            end++;
        }
        if(current_sum > max_sum){
            max_sum = current_sum;
        }
        current_sum -= arr[start].l;
        start++;
    }
    return max_sum;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        long n, W, H;
        scanf("%ld %ld %ld", &n, &W, &H);
        Star *stars = (Star*)malloc(n * sizeof(Star));
        for(long i = 0; i < n; i++) {
            scanf("%ld %ld %ld", &stars[i].x, &stars[i].y, &stars[i].l);
        }
        qsort(stars, n, sizeof(Star), cmp_x);
        // Sliding window on x
        long left = 0, right = 0;
        Star *current_y_sorted = (Star*)malloc(n * sizeof(Star));
        int m = 0;
        long max_total = 0;
        while(left < n){
            while(right < n && stars[right].x < stars[left].x + W){
                insert_sorted_y(current_y_sorted, &m, stars[right]);
                right++;
            }
            // Calculate max y sum
            long current_max = calculate_max_y_sum(current_y_sorted, m, H);
            if(current_max > max_total){
                max_total = current_max;
            }
            // Remove the left star from y-sorted array
            remove_sorted_y(current_y_sorted, &m, stars[left]);
            left++;
        }
        printf("%ld\n", max_total);
        free(stars);
        free(current_y_sorted);
    }
    return 0;
}