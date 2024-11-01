#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge {
    int to;
    int length;
    struct Edge* next;
} Edge;

typedef struct Node {
    Edge* head;
} Node;

Node* tree;
int n;
long long s;

// Fast IO
char buffer[1 << 20];
int buf_pos = 0, buf_len = 0;

int getInt() {
    int x = 0, sign = 1;
    while (buffer[buf_pos] != '-' && (buffer[buf_pos] < '0' || buffer[buf_pos] > '9')) {
        buf_pos++;
        if (buf_pos >= buf_len) {
            buf_len = fread(buffer, 1, sizeof(buffer), stdin);
            buffer[buf_len] = '\0';
            if (buf_len == 0) return 0;
        }
    }
    if (buffer[buf_pos] == '-') {
        sign = -1;
        buf_pos++;
    }
    while (buffer[buf_pos] >= '0' && buffer[buf_pos] <= '9') {
        x = x * 10 + (buffer[buf_pos++] - '0');
        if (buf_pos >= buf_len) {
            buf_len = fread(buffer, 1, sizeof(buffer), stdin);
            buffer[buf_len] = '\0';
            if (buf_len == 0) break;
        }
    }
    return x * sign;
}

long long max(long long a, long long b){
    return a > b ? a : b;
}

long long min(long long a, long long b){
    return a < b ? a : b;
}

long long global_ans;
long long required_length;

long long dfs(int u, int parent, long long d) {
    long long max1 = -1, max2 = -1;
    long long total = 0;
    Edge* edge = tree[u].head;
    while(edge){
        int v = edge->to;
        if(v == parent){
            edge = edge->next;
            continue;
        }
        long long res = dfs(v, u, d) + edge->length;
        if(res > d){
            required_length += res - d;
        }
        if(res > max1){
            max2 = max1;
            max1 = res;
        }
        else if(res > max2){
            max2 = res;
        }
        edge = edge->next;
    }
    if(max1 == -1) return 0;
    if(max1 + max2 > d){
        required_length += max1 + max2 - d;
        return 0;
    }
    return max1;
}

int check(long long d){
    required_length = 0;
    dfs(1, -1, d);
    return required_length <= s;
}

int main(){
    n = getInt();
    s = getInt();
    tree = (Node*)calloc(n+1, sizeof(Node));
    for(int i=2;i<=n;i++){
        int u = getInt();
        int v = getInt();
        int z = getInt();
        Edge* e1 = (Edge*)malloc(sizeof(Edge));
        e1->to = v;
        e1->length = z;
        e1->next = tree[u].head;
        tree[u].head = e1;
        Edge* e2 = (Edge*)malloc(sizeof(Edge));
        e2->to = u;
        e2->length = z;
        e2->next = tree[v].head;
        tree[v].head = e2;
    }
    long long low = 0, high = 300000000;
    while(low < high){
        long long mid = low + (high - low)/2;
        if(check(mid)){
            high = mid;
        }
        else{
            low = mid + 1;
        }
    }
    printf("%lld\n", low);
    // Free memory
    for(int i=1;i<=n;i++){
        Edge* edge = tree[i].head;
        while(edge){
            Edge* tmp = edge;
            edge = edge->next;
            free(tmp);
        }
    }
    free(tree);
    return 0;
}