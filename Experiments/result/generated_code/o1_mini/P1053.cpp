#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node* next;
    struct Node* prev;
} Node;

int main(){
    int n;
    scanf("%d", &n);
    int **adj = (int **)malloc((n+1)*sizeof(int *));
    for(int i=1;i<=n;i++) {
        adj[i] = (int *)malloc(2*sizeof(int));
        scanf("%d %d", &adj[i][0], &adj[i][1]);
    }
    // Check degrees
    // Since input guarantees each has exactly two preferences, skip degree check
    // Check if single cycle
    int *visited = (int *)calloc(n+1, sizeof(int));
    int current =1;
    visited[current]=1;
    Node *head = NULL, *tail = NULL;
    // Build the cycle order
    Node *prev = NULL;
    for(int i=0;i<n;i++){
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->val = current;
        newNode->next = NULL;
        newNode->prev = prev;
        if(prev){
            prev->next = newNode;
        }
        else{
            head = newNode;
        }
        prev = newNode;
        // Move to next
        int next;
        if(i==0){
            next = adj[current][0];
        }
        else{
            if(adj[current][0] != prev->val){
                next = adj[current][0];
            }
            else{
                next = adj[current][1];
            }
        }
        if(visited[next]){
            if(i != n-1 || next !=1){
                break;
            }
        }
        visited[next]=1;
        current = next;
    }
    // Check if all visited and cycle closed
    int single_cycle =1;
    for(int i=1;i<=n;i++) if(!visited[i]) {single_cycle=0; break;}
    // Also check if the last node connects back to head
    if(single_cycle){
        Node *last = head;
        while(last->next) last = last->next;
        if(last->next != NULL){
            single_cycle=0;
        }
    }
    if(!single_cycle){
        printf("-1");
        return 0;
    }
    // Traverse the cycle to get order
    int *order = (int *)malloc(n*sizeof(int));
    int idx=0;
    Node *ptr = head;
    while(ptr){
        order[idx++] = ptr->val;
        ptr = ptr->next;
    }
    // Create reversed order
    int *order_rev = (int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++) order_rev[i] = order[n-1-i];
    // Count for original order
    int *count = (int *)calloc(n, sizeof(int));
    for(int i=0;i<n;i++){
        int k = (order[i]-1 - i + n)%n;
        count[k]++;
    }
    // Find max m for original
    int m1 =0;
    for(int i=0;i<n;i++) if(count[i] > m1) m1 = count[i];
    // Count for reversed order
    int *count_rev = (int *)calloc(n, sizeof(int));
    for(int i=0;i<n;i++){
        int k = (order_rev[i]-1 - i + n)%n;
        count_rev[k]++;
    }
    // Find max m for reversed
    int m2 =0;
    for(int i=0;i<n;i++) if(count_rev[i] > m2) m2 = count_rev[i];
    // Maximum m
    int m = m1 > m2 ? m1 : m2;
    printf("%d", n - m);
    // Free memory
    for(int i=1;i<=n;i++) free(adj[i]);
    free(adj);
    free(visited);
    free(order);
    free(order_rev);
    free(count);
    free(count_rev);
    while(head){
        Node *temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}