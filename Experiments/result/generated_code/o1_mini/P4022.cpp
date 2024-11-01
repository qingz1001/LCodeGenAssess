#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1100000
#define ALPHABET 2

typedef struct State {
    int len;
    int link;
    int next[ALPHABET];
} State;

State sam[2 * MAXLEN + 5];
int size, last;

// Initialize SAM
void sam_init(){
    size = 1;
    last = 0;
    memset(sam, 0, sizeof(State));
}

// Add character to SAM
void sam_extend(char c){
    int curr = size++;
    sam[curr].len = sam[last].len + 1;
    memset(sam[curr].next, -1, sizeof(sam[curr].next));
    int x = last;
    int c_idx = c - '0';
    while(x != -1 && sam[x].next[c_idx] == -1){
        sam[x].next[c_idx] = curr;
        x = sam[x].link;
    }
    if(x == -1){
        sam[curr].link = 0;
    }
    else{
        int y = sam[x].next[c_idx];
        if(sam[x].len + 1 == sam[y].len){
            sam[curr].link = y;
        }
        else{
            int clone = size++;
            sam[clone].len = sam[x].len + 1;
            memcpy(sam[clone].next, sam[y].next, sizeof(sam[y].next));
            sam[clone].link = sam[y].link;
            while(x != -1 && sam[x].next[c_idx] == y){
                sam[x].next[c_idx] = clone;
                x = sam[x].link;
            }
            sam[y].link = clone;
            sam[curr].link = clone;
        }
    }
    last = curr;
}

// Interval structure
typedef struct Interval {
    int start;
    int end;
    int len;
} Interval;

// Compare intervals by end
int cmp_end(const void *a, const void *b){
    Interval *ia = (Interval*)a;
    Interval *ib = (Interval*)b;
    if(ia->end != ib->end)
        return ia->end - ib->end;
    return ia->start - ib->start;
}

// Binary search for DP
long long dp[2 * MAXLEN + 5];
int main(){
    sam_init();
    int N, M;
    scanf("%d %d", &N, &M);
    char buffer[MAXLEN + 5];
    for(int i=0;i<M;i++){
        scanf("%s", buffer);
        for(int j=0; buffer[j]; j++) sam_extend(buffer[j]);
        // Reset last to root for next string
        last = 0;
    }
    for(int i=0;i<N;i++){
        scanf("%s", buffer);
        int lenA = strlen(buffer);
        // Binary search L from 1 to lenA
        int l = 1, r = lenA, res = 0;
        while(l <= r){
            int mid = l + (r - l)/2;
            // Traverse A and collect intervals with len >= mid
            int current = 0;
            int current_len = 0;
            // Allocate space for intervals
            Interval *intervals = (Interval*)malloc(sizeof(Interval)*lenA);
            int cnt =0;
            for(int j=0; j<lenA; j++){
                int c = buffer[j] - '0';
                if(sam[current].next[c] != -1){
                    current = sam[current].next[c];
                    current_len++;
                }
                else{
                    while(current != -1 && sam[current].next[c] == -1){
                        current = sam[current].link;
                    }
                    if(current == -1){
                        current = 0;
                        current_len = 0;
                    }
                    else{
                        current = sam[current].next[c];
                        current_len = sam[current].len +1;
                    }
                }
                if(current_len >= mid){
                    intervals[cnt].end = j +1;
                    intervals[cnt].start = j +1 - current_len;
                    intervals[cnt].len = current_len;
                    cnt++;
                }
            }
            if(cnt ==0){
                free(intervals);
                // No intervals, check condition
                if(0 *10 >=9 * lenA){
                    res = mid;
                    l = mid +1;
                }
                else{
                    r = mid -1;
                }
                continue;
            }
            // Sort intervals by end
            qsort(intervals, cnt, sizeof(Interval), cmp_end);
            // DP to maximize total coverage
            // Initialize
            long long total =0;
            // Create an array to hold the best total up to each interval
            long long *best = (long long*)malloc(sizeof(long long)*cnt);
            for(int j=0; j<cnt; j++) best[j] = intervals[j].len;
            for(int j=0; j<cnt; j++){
                for(int k=0; k<j; k++){
                    if(intervals[k].end <= intervals[j].start){
                        if(best[j] < best[k] + intervals[j].len){
                            best[j] = best[k] + intervals[j].len;
                        }
                    }
                }
                if(total < best[j]) total = best[j];
            }
            free(best);
            free(intervals);
            if(total *10 >= 9LL * lenA){
                res = mid;
                l = mid +1;
            }
            else{
                r = mid -1;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}