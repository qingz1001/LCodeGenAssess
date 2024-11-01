#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_PASTURES 52
#define MAX_ROADS 10000

typedef struct {
    int dest;
    int length;
} Road;

typedef struct {
    Road* roads;
    int count;
} Pasture;

Pasture pastures[MAX_PASTURES];
int distances[MAX_PASTURES];
int visited[MAX_PASTURES];

int char_to_index(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 26;
    return -1;
}

char index_to_char(int index) {
    if (index < 26) return 'a' + index;
    return 'A' + (index - 26);
}

void add_road(char from, char to, int length) {
    int from_index = char_to_index(from);
    int to_index = char_to_index(to);
    
    Road* new_road = malloc(sizeof(Road));
    new_road->dest = to_index;
    new_road->length = length;
    
    pastures[from_index].roads = realloc(pastures[from_index].roads, (pastures[from_index].count + 1) * sizeof(Road));
    pastures[from_index].roads[pastures[from_index].count++] = *new_road;
}

int find_nearest_unvisited() {
    int min_dist = INT_MAX;
    int min_index = -1;
    
    for (int i = 0; i < MAX_PASTURES; i++) {
        if (!visited[i] && distances[i] < min_dist) {
            min_dist = distances[i];
            min_index = i;
        }
    }
    
    return min_index;
}

void dijkstra() {
    int barn_index = char_to_index('Z');
    
    for (int i = 0; i < MAX_PASTURES; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
    }
    
    distances[barn_index] = 0;
    
    for (int i = 0; i < MAX_PASTURES; i++) {
        int current = find_nearest_unvisited();
        if (current == -1) break;
        
        visited[current] = 1;
        
        for (int j = 0; j < pastures[current].count; j++) {
            Road road = pastures[current].roads[j];
            int new_dist = distances[current] + road.length;
            
            if (new_dist < distances[road.dest]) {
                distances[road.dest] = new_dist;
            }
        }
    }
}

int main() {
    int P;
    scanf("%d", &P);
    
    for (int i = 0; i < P; i++) {
        char from, to;
        int length;
        scanf(" %c %c %d", &from, &to, &length);
        add_road(from, to, length);
        add_road(to, from, length);
    }
    
    dijkstra();
    
    int min_dist = INT_MAX;
    char fastest_cow = '\0';
    
    for (int i = 26; i < MAX_PASTURES - 1; i++) {
        if (distances[i] < min_dist) {
            min_dist = distances[i];
            fastest_cow = index_to_char(i);
        }
    }
    
    printf("%c %d\n", fastest_cow, min_dist);
    
    return 0;
}