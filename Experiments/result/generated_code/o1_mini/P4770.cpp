#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum sizes based on problem constraints
#define MAXLEN 500005
#define MAXSTATE 1000005

typedef struct State {
    int len;
    int link;
    int next[26];
    int *end_pos;
    int cnt;
} State;

State st[MAXSTATE];
int sz, last;

// Comparator for sorting end positions
int cmp_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Initialize SAM
void init_sam() {
    st[0].len = 0;
    st[0].link = -1;
    memset(st[0].next, -1, sizeof(st[0].next));
    st[0].end_pos = NULL;
    st[0].cnt = 0;
    sz = 1;
    last = 0;
}

// Extend SAM with character c at position pos
void extend(char c, int pos) {
    int curr = sz++;
    st[curr].len = st[last].len + 1;
    memset(st[curr].next, -1, sizeof(st[curr].next));
    st[curr].end_pos = (int*)malloc(sizeof(int));
    st[curr].end_pos[0] = pos;
    st[curr].cnt = 1;
    int p = last;
    while (p != -1 && st[p].next[c - 'a'] == -1) {
        st[p].next[c - 'a'] = curr;
        p = st[p].link;
    }
    if (p == -1) {
        st[curr].link = 0;
    }
    else {
        int q = st[p].next[c - 'a'];
        if (st[p].len + 1 == st[q].len) {
            st[curr].link = q;
        }
        else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
            st[clone].end_pos = NULL;
            st[clone].cnt = 0;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c - 'a'] == q) {
                st[p].next[c - 'a'] = clone;
                p = st[p].link;
            }
            st[q].link = clone;
            st[curr].link = clone;
        }
    }
    last = curr;
}

// Array to hold order of states sorted by len
int order[MAXSTATE];
int main(){
    char S[MAXLEN];
    scanf("%s", S);
    int n = strlen(S);
    init_sam();
    for(int i=0;i<n;i++) {
        extend(S[i], i+1);
    }

    // Counting sort based on len
    int max_len = 0;
    for(int i=0;i<sz;i++) if(st[i].len > max_len) max_len = st[i].len;
    int *cnt_len = (int*)calloc(max_len+1, sizeof(int));
    for(int i=0;i<sz;i++) cnt_len[st[i].len]++;
    for(int i=1;i<=max_len;i++) cnt_len[i] += cnt_len[i-1];
    for(int i=sz-1;i>=0;i--){
        order[--cnt_len[st[i].len]] = i;
    }
    free(cnt_len);

    // Propagate end positions
    for(int i=sz-1;i>=0;i--){
        int state = order[i];
        if(st[state].link != -1){
            int link = st[state].link;
            if(st[link].end_pos == NULL){
                st[link].end_pos = (int*)malloc(st[state].cnt * sizeof(int));
                memcpy(st[link].end_pos, st[state].end_pos, st[state].cnt * sizeof(int));
                st[link].cnt = st[state].cnt;
            }
            else{
                st[link].end_pos = (int*)realloc(st[link].end_pos, (st[link].cnt + st[state].cnt) * sizeof(int));
                memcpy(st[link].end_pos + st[link].cnt, st[state].end_pos, st[state].cnt * sizeof(int));
                st[link].cnt += st[state].cnt;
            }
        }
    }

    // Sort the end positions for each state
    for(int i=0;i<sz;i++) {
        if(st[i].end_pos != NULL){
            qsort(st[i].end_pos, st[i].cnt, sizeof(int), cmp_int);
        }
    }

    int Q;
    scanf("%d", &Q);
    // For marking visited states per query
    int *last_visit = (int*)calloc(sz, sizeof(int));
    int current_query = 1;
    while(Q--){
        char T[MAXLEN];
        int l, r;
        scanf("%s %d %d", T, &l, &r);
        int lenT = strlen(T);
        long long answer = 0;
        int state_sam = 0;
        int len_current = 0;
        for(int i=0;i<lenT;i++){
            char c = T[i];
            while(state_sam != -1 && st[state_sam].next[c - 'a'] == -1){
                state_sam = st[state_sam].link;
                if(state_sam != -1){
                    len_current = st[state_sam].len;
                }
            }
            if(state_sam == -1){
                state_sam = 0;
                len_current = 0;
            }
            if(st[state_sam].next[c - 'a'] != -1){
                state_sam = st[state_sam].next[c - 'a'];
                len_current = st[state_sam].len;
            }
            else{
                state_sam = 0;
                len_current = 0;
            }
            if(state_sam == 0) continue;
            int link = st[state_sam].link;
            int new_sub = st[state_sam].len - st[link].len;
            if(last_visit[state_sam] != current_query){
                last_visit[state_sam] = current_query;
                // Check if there is any end_pos in [l + len -1, r]
                int min_pos = l + st[state_sam].len -1;
                if(min_pos > r) {
                    answer += new_sub;
                    continue;
                }
                // Binary search
                int left = 0, right = st[state_sam].cnt -1;
                int found = 0;
                while(left <= right){
                    int mid = left + (right - left)/2;
                    if(st[state_sam].end_pos[mid] >= min_pos){
                        if(st[state_sam].end_pos[mid] <= r){
                            found = 1;
                            break;
                        }
                        right = mid -1;
                    }
                    else{
                        left = mid +1;
                    }
                }
                if(!found){
                    answer += new_sub;
                }
            }
        }
        printf("%lld\n", answer);
        current_query++;
    }

    // Free allocated memory
    for(int i=0;i<sz;i++) {
        if(st[i].end_pos != NULL){
            free(st[i].end_pos);
        }
    }
    free(last_visit);
    return 0;
}