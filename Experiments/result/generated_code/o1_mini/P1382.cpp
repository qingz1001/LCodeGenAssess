#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int h;
    int isStart;
} Event;

typedef struct {
    int x;
    int y;
} Point;

// Comparator for sorting heights
int cmp_heights(const void *a, const void *b) {
    int ha = *(int*)a;
    int hb = *(int*)b;
    if (ha < hb) return -1;
    else if (ha > hb) return 1;
    else return 0;
}

// Binary search to get height index
int get_height_index(int h, int *heights, int size){
    int left=0, right=size-1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(heights[mid] == h) return mid;
        else if(heights[mid] < h) left = mid +1;
        else right = mid -1;
    }
    return -1;
}

// Comparator for sorting events
int cmp_events(const void *a, const void *b){
    Event *ea = (Event*)a;
    Event *eb = (Event*)b;
    if(ea->x != eb->x){
        return ea->x - eb->x;
    }
    else{
        if(ea->isStart != eb->isStart){
            return eb->isStart - ea->isStart; // start before end
        }
        else{
            if(ea->isStart){
                return eb->h - ea->h; // higher height first for starts
            }
            else{
                return ea->h - eb->h; // lower height first for ends
            }
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int max_events = 2 * n;
    Event *events = (Event*)malloc(sizeof(Event) * max_events);
    int *heights = (int*)malloc(sizeof(int) * (max_events +1));
    int height_count =0;
    // Add 0 height
    heights[height_count++] =0;
    for(int i=0;i<n;i++){
        int h, l, r;
        scanf("%d %d %d", &h, &l, &r);
        events[2*i].x = l;
        events[2*i].h = h;
        events[2*i].isStart =1;
        events[2*i+1].x = r;
        events[2*i+1].h = h;
        events[2*i+1].isStart =0;
        heights[height_count++] = h;
    }
    // Sort and remove duplicates
    qsort(heights, height_count, sizeof(int), cmp_heights);
    int uniq_size =1;
    for(int i=1;i<height_count;i++){
        if(heights[i] != heights[i-1]){
            heights[uniq_size++] = heights[i];
        }
    }
    // Sort events
    qsort(events, max_events, sizeof(Event), cmp_events);
    // Initialize frequency array
    int *freq = (int*)malloc(sizeof(int) * uniq_size);
    memset(freq, 0, sizeof(int)*uniq_size);
    int zero_idx = get_height_index(0, heights, uniq_size);
    freq[zero_idx] =1;
    // Initialize heap
    int heap_size =1;
    int *heap = (int*)malloc(sizeof(int) * (max_events +2));
    heap[1] =0;
    // Initialize result list
    int max_m = 4 * n +2;
    Point *result = (Point*)malloc(sizeof(Point) * max_m);
    int m =0;
    int prev =0;
    int i_event =0;
    while(i_event < max_events){
        int current_x = events[i_event].x;
        // Process all events at current_x
        while(i_event < max_events && events[i_event].x == current_x){
            if(events[i_event].isStart){
                int h = events[i_event].h;
                // Push h to heap
                heap_size++;
                heap[heap_size] = h;
                // Heapify up
                int pos = heap_size;
                while(pos >1 && heap[pos] > heap[pos/2]){
                    int temp = heap[pos];
                    heap[pos] = heap[pos/2];
                    heap[pos/2] = temp;
                    pos /=2;
                }
                // Update frequency
                int h_idx = get_height_index(h, heights, uniq_size);
                freq[h_idx]++;
            }
            else{
                int h = events[i_event].h;
                int h_idx = get_height_index(h, heights, uniq_size);
                freq[h_idx]--;
            }
            i_event++;
        }
        // Remove heights from heap top if their frequency is 0
        while(heap_size >0){
            int current_top = heap[1];
            int top_idx = get_height_index(current_top, heights, uniq_size);
            if(freq[top_idx] >0){
                break;
            }
            else{
                // Remove top
                heap[1] = heap[heap_size];
                heap_size--;
                // Heapify down
                int pos =1;
                while(1){
                    int largest = pos;
                    int left = pos *2;
                    int right = pos *2 +1;
                    if(left <= heap_size && heap[left] > heap[largest]){
                        largest = left;
                    }
                    if(right <= heap_size && heap[right] > heap[largest]){
                        largest = right;
                    }
                    if(largest != pos){
                        int temp = heap[pos];
                        heap[pos] = heap[largest];
                        heap[largest] = temp;
                        pos = largest;
                    }
                    else{
                        break;
                    }
                }
            }
        }
        // Get current max height
        int current_max = heap_size >0 ? heap[1] :0;
        if(current_max != prev){
            // Add (x, prev) and (x, current_max)
            result[m].x = current_x;
            result[m].y = prev;
            m++;
            result[m].x = current_x;
            result[m].y = current_max;
            m++;
            prev = current_max;
        }
    }
    // Ensure the last point has y=0
    if(m ==0 || result[m-1].y !=0){
        int last_x = events[max_events-1].x;
        result[m].x = last_x;
        result[m].y =0;
        m++;
    }
    // Remove consecutive duplicate points
    Point *final_result = (Point*)malloc(sizeof(Point) * m);
    int final_m =0;
    for(int i=0;i<m;i++){
        if(final_m ==0 || !(final_result[final_m-1].x == final_result[final_m-1].x && final_result[final_m-1].y == final_result[final_m-1].y)){
            final_result[final_m++] = result[i];
        }
    }
    // Print the result
    printf("%d\n", m);
    for(int i=0;i<m;i++){
        printf("%d %d\n", final_result[i].x, final_result[i].y);
    }
    // Free allocated memory
    free(events);
    free(heights);
    free(freq);
    free(heap);
    free(result);
    free(final_result);
    return 0;
}