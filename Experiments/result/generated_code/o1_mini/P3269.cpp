#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

int cmp_ranges(const void* a, const void* b) {
    Range* ra = (Range*)a;
    Range* rb = (Range*)b;
    if (ra->start != rb->start)
        return ra->start - rb->start;
    return ra->end - rb->end;
}

int A_length;
char A_str[10005];
int N;
char substrings[4][10005];
int sub_lengths[4];
int pos_lists[4][10005];
int pos_counts[4];
long long min_ans, max_ans;

void find_positions(int idx) {
    int len = sub_lengths[idx];
    pos_counts[idx] = 0;
    for(int i=0; i <= A_length - len; i++) {
        if(strncmp(&A_str[i], substrings[idx], len) == 0){
            pos_lists[idx][pos_counts[idx]++] = i;
        }
    }
}

Range selected_ranges[4];

void backtrack(int depth, Range current_ranges[], int selected_count, long long* current_min, long long* current_max) {
    if(depth == N){
        Range merged[4];
        int m = 0;
        for(int i=0;i<N;i++) {
            merged[m++] = current_ranges[i];
        }
        qsort(merged, m, sizeof(Range), cmp_ranges);
        long long total = 0;
        int current_start = merged[0].start;
        int current_end = merged[0].end;
        for(int i=1;i<m;i++) {
            if(merged[i].start > current_end +1){
                total += (current_end - current_start +1);
                current_start = merged[i].start;
                current_end = merged[i].end;
            }
            else{
                if(merged[i].end > current_end){
                    current_end = merged[i].end;
                }
            }
        }
        total += (current_end - current_start +1);
        if(total < *current_min) *current_min = total;
        if(total > *current_max) *current_max = total;
        return;
    }
    for(int i=0;i<pos_counts[depth];i++){
        current_ranges[depth].start = pos_lists[depth][i];
        current_ranges[depth].end = pos_lists[depth][i] + sub_lengths[depth] -1;
        backtrack(depth+1, current_ranges, selected_count+1, current_min, current_max);
    }
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%s", A_str);
        A_length = strlen(A_str);
        scanf("%d", &N);
        for(int i=0;i<N;i++) {
            scanf("%s", substrings[i]);
            sub_lengths[i] = strlen(substrings[i]);
            find_positions(i);
        }
        min_ans = LLONG_MAX;
        max_ans = 0;
        Range current_ranges_temp[4];
        backtrack(0, current_ranges_temp, 0, &min_ans, &max_ans);
        printf("%lld %lld\n", min_ans, max_ans);
    }
    return 0;
}