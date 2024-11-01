#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20005
#define MAX_M 200005
#define MAX_K 100005

typedef struct Node {
    int x;
    struct Node* next;
} Node;

int main(){
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    Node* tracks[MAX_N];
    for(int i=1;i<=N;i++) tracks[i]=NULL;
    for(int i=0;i<M;i++){
        int X, Y;
        scanf("%d %d", &X, &Y);
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->x = X;
        newNode->next = tracks[Y];
        tracks[Y] = newNode;
    }
    // Sort each track
    for(int i=1;i<=N;i++){
        // Simple insertion sort as N<=20000 and M<=2e5
        if(tracks[i]==NULL) continue;
        Node* sorted = NULL;
        Node* current = tracks[i];
        while(current){
            Node* next = current->next;
            if(sorted == NULL || current->x < sorted->x){
                current->next = sorted;
                sorted = current;
            }
            else{
                Node* temp = sorted;
                while(temp->next && temp->next->x < current->x) temp = temp->next;
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        tracks[i] = sorted;
    }
    long long total = 0;
    for(int round=0; round<K; round++){
        int best_track = -1;
        int max_kill = -1;
        // Find the best track
        for(int i=1;i<=N;i++){
            if(tracks[i]==NULL) continue;
            // Simulate killing
            // Make a copy of tracks
            int kill=0;
            int current_track = i;
            int direction = (i <= N/2) ? 1 : -1; // 1: down-right, -1: up-right
            int pos = tracks[i]->x;
            // Temporarily mark killed zombies
            Node* temp = tracks[i];
            Node* prev = NULL;
            // Kill the first zombie
            kill++;
            // Remove the first zombie
            if(temp->next){
                // Do nothing
            }
            // Assign max_kill
            if(kill > max_kill){
                max_kill = kill;
                best_track = i;
            }
        }
        if(best_track == -1){
            printf("1 0\n");
            continue;
        }
        // Now simulate and kill
        int A = best_track;
        int B = 0;
        int current_track = A;
        int direction = (A <= N/2) ? 1 : -1;
        int pos = 0;
        while(1){
            if(tracks[current_track]==NULL) break;
            Node* z = tracks[current_track];
            pos = z->x;
            B++;
            // Remove the zombie
            tracks[current_track] = z->next;
            free(z);
            // Change direction
            direction = -direction;
            current_track += direction;
            if(current_track <1 || current_track >N) break;
        }
        printf("%d %d\n", A, B);
        total += B;
    }
    printf("%lld\n", total);
    return 0;
}