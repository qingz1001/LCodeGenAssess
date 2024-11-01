#include <stdio.h>
#include <stdlib.h>

struct Point {
    long long x, y;
    char color;
};

// Comparator for qsort
int cmp_long(const void *a, const void *b){
    long long aa = *(const long long*)a;
    long long bb = *(const long long*)b;
    if (aa < bb) return -1;
    if (aa > bb) return 1;
    return 0;
}

// Function to compute gcd
long gcd_func(long a, long b){
    if(b == 0) return a;
    return gcd_func(b, a % b);
}

// Function to find lower_bound
int lower_bound_func(long long arr[], int n, long long val){
    int left = 0, right = n;
    while (left < right){
        int mid = left + (right - left) / 2;
        if (arr[mid] >= val){
            right = mid;
        }
        else{
            left = mid +1;
        }
    }
    return left;
}

// Function to find upper_bound
int upper_bound_func(long long arr[], int n, long long val){
    int left = 0, right = n;
    while (left < right){
        int mid = left + (right - left) / 2;
        if (arr[mid] > val){
            right = mid;
        }
        else{
            left = mid +1;
        }
    }
    return left;
}

int main(){
    int N;
    scanf("%d", &N);
    struct Point points[1000];
    for(int i=0; i<N; i++){
        char c;
        scanf("%lld %lld %c", &points[i].x, &points[i].y, &points[i].color);
    }
    int max_red = 0;
    for(int i=0; i<N; i++){
        for(int j=i+1; j<N; j++){
            long long dx = points[j].x - points[i].x;
            long long dy = points[j].y - points[i].y;
            long long nx = -dy;
            long long ny = dx;
            if(nx ==0 && ny ==0) continue;
            long g = gcd_func(nx <0 ? -nx : nx, ny <0 ? -ny : ny);
            long long rx = nx / g;
            long long ry = ny / g;
            if(rx <0 || (rx ==0 && ry <0)){
                rx = -rx;
                ry = -ry;
            }
            long long blue_t[1000];
            int blue_size =0;
            long long red_t[1000];
            int red_size =0;
            for(int k=0; k<N; k++){
                long long t = points[k].x * rx + points[k].y * ry;
                if (points[k].color == 'B'){
                    blue_t[blue_size++] = t;
                }
                else{
                    red_t[red_size++] = t;
                }
            }
            qsort(blue_t, blue_size, sizeof(long long), cmp_long);
            qsort(red_t, red_size, sizeof(long long), cmp_long);
            int current_max =0;
            if(blue_size ==0){
                current_max = red_size;
            }
            else{
                // Interval (-inf, blue_t[0])
                int cnt = lower_bound_func(red_t, red_size, blue_t[0]);
                if(cnt > current_max) current_max = cnt;
                // Between blue[i] and blue[i+1]
                for(int b=0; b < blue_size -1; b++){
                    long long a = blue_t[b];
                    long long b_val = blue_t[b+1];
                    int ub = upper_bound_func(red_t, red_size, a);
                    int lb = lower_bound_func(red_t, red_size, b_val);
                    int cnt_between = lb - ub;
                    if(cnt_between > current_max){
                        current_max = cnt_between;
                    }
                }
                // Interval (blue_t[blue_size -1], +inf)
                int cnt2 = red_size - upper_bound_func(red_t, red_size, blue_t[blue_size -1]);
                if(cnt2 > current_max){
                    current_max = cnt2;
                }
            }
            if(current_max > max_red){
                max_red = current_max;
            }
        }
    }
    printf("%d\n", max_red);
}