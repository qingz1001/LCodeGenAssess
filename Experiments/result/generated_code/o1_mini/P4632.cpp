#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store a store's information
typedef struct {
    int x;
    int a;
    int b;
} Store;

// Structure to store a query's information
typedef struct {
    int y;
    int l;
    int index;
} Query;

// Structure to store a sorted query
typedef struct {
    int y;
    int l;
    int index;
} SortedQuery;

// Structure to store events for sweep line
typedef struct {
    int y;
    int type; // 0 = start, 1 = query, 2 = end
    int identifier; // type for start/end, query index for query
} Event;

// Structure to store intervals after merging
typedef struct {
    int a;
    int b;
} Interval;

// Structure to store type information
typedef struct {
    Interval *merged_intervals;
    int num_intervals;
    int *x;
    int num_x;
} TypeInfo;

// Comparator for sorting stores by 'a' then by 'b'
int cmp_store_a(const void *a, const void *b) {
    Store *sa = (Store *)a;
    Store *sb = (Store *)b;
    if(sa->a != sb->a)
        return sa->a - sb->a;
    return sa->b - sb->b;
}

// Comparator for sorting x in ascending order
int cmp_x(const void *a, const void *b) {
    int xa = *(int*)a;
    int xb = *(int*)b;
    if(xa < xb) return -1;
    if(xa > xb) return 1;
    return 0;
}

// Comparator for sorting events
int cmp_event(const void *a, const void *b) {
    Event *ea = (Event *)a;
    Event *eb = (Event *)b;
    if(ea->y != eb->y)
        return ea->y - eb->y;
    return ea->type - eb->type; // start < query < end
}

// Comparator for sorting queries by y
int cmp_sorted_query(const void *a, const void *b) {
    SortedQuery *qa = (SortedQuery *)a;
    SortedQuery *qb = (SortedQuery *)b;
    if(qa->y != qb->y)
        return qa->y - qb->y;
    return 0;
}

// Function to find lower bound
int lower_bound_queries(SortedQuery *sorted_queries, int q, int a) {
    int left = 0, right = q;
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(sorted_queries[mid].y >= a)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

// Function to find upper bound
int upper_bound_queries(SortedQuery *sorted_queries, int q, int b) {
    int left = 0, right = q;
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(sorted_queries[mid].y > b)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

// Function to get minimum distance
int get_min_distance(int *x_list, int m_x, int l) {
    if(m_x == 0)
        return 1000000000;
    int low = 0, high = m_x - 1;
    int pos = m_x;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(x_list[mid] >= l) {
            pos = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    int min_d = 1000000000;
    if(pos < m_x) {
        int diff = x_list[pos] - l;
        if(diff < min_d)
            min_d = diff;
    }
    if(pos > 0) {
        int diff = l - x_list[pos - 1];
        if(diff < min_d)
            min_d = diff;
    }
    return min_d;
}

int main(){
    int n, k, q;
    scanf("%d %d %d", &n, &k, &q);
    
    // Allocate memory for stores per type
    Store **stores_per_type = (Store **)malloc((k+1) * sizeof(Store *));
    int *stores_count = (int *)calloc(k+1, sizeof(int));
    for(int t=1; t<=k; t++) {
        stores_per_type[t] = NULL;
    }
    
    // Read n stores
    for(int i=0; i<n; i++) {
        int xi, ti, ai, bi;
        scanf("%d %d %d %d", &xi, &ti, &ai, &bi);
        stores_per_type[ti] = (Store *)realloc(stores_per_type[ti], (stores_count[ti]+1)*sizeof(Store));
        stores_per_type[ti][stores_count[ti]].x = xi;
        stores_per_type[ti][stores_count[ti]].a = ai;
        stores_per_type[ti][stores_count[ti]].b = bi;
        stores_count[ti]++;
    }
    
    // Initialize type information
    TypeInfo *types = (TypeInfo *)malloc((k+1) * sizeof(TypeInfo));
    for(int t=1; t<=k; t++) {
        types[t].merged_intervals = NULL;
        types[t].num_intervals = 0;
        types[t].x = NULL;
        types[t].num_x = 0;
    }
    
    // Merge intervals and sort x's for each type
    for(int t=1; t<=k; t++) {
        if(stores_count[t] == 0)
            continue;
        // Sort stores by a
        qsort(stores_per_type[t], stores_count[t], sizeof(Store), cmp_store_a);
        // Merge intervals
        Interval *merged = (Interval *)malloc(stores_count[t] * sizeof(Interval));
        int m = stores_count[t];
        merged[0].a = stores_per_type[t][0].a;
        merged[0].b = stores_per_type[t][0].b;
        int cnt = 1;
        for(int i=1; i<m; i++) {
            if(stores_per_type[t][i].a <= merged[cnt-1].b) {
                if(stores_per_type[t][i].b > merged[cnt-1].b)
                    merged[cnt-1].b = stores_per_type[t][i].b;
            }
            else {
                merged[cnt].a = stores_per_type[t][i].a;
                merged[cnt].b = stores_per_type[t][i].b;
                cnt++;
            }
        }
        types[t].num_intervals = cnt;
        types[t].merged_intervals = merged;
        // Collect and sort x's
        types[t].x = (int *)malloc(m * sizeof(int));
        for(int i=0; i<m; i++) {
            types[t].x[i] = stores_per_type[t][i].x;
        }
        qsort(types[t].x, m, sizeof(int), cmp_x);
        types[t].num_x = m;
        free(stores_per_type[t]);
    }
    free(stores_per_type);
    free(stores_count);
    
    // Prepare events
    int total_merged_intervals = 0;
    for(int t=1; t<=k; t++) {
        total_merged_intervals += types[t].num_intervals;
    }
    Event *events = (Event *)malloc((2*total_merged_intervals + q) * sizeof(Event));
    int event_count = 0;
    for(int t=1; t<=k; t++) {
        for(int i=0; i < types[t].num_intervals; i++) {
            events[event_count].y = types[t].merged_intervals[i].a;
            events[event_count].type = 0; // start
            events[event_count].identifier = t;
            event_count++;
            events[event_count].y = types[t].merged_intervals[i].b + 1;
            events[event_count].type = 2; // end
            events[event_count].identifier = t;
            event_count++;
        }
    }
    
    // Read queries
    Query *queries = (Query *)malloc(q * sizeof(Query));
    for(int i=0; i<q; i++) {
        scanf("%d %d", &queries[i].l, &queries[i].y);
        queries[i].index = i;
    }
    
    // Add query events
    for(int i=0; i<q; i++) {
        events[event_count].y = queries[i].y;
        events[event_count].type = 1; // query
        events[event_count].identifier = i;
        event_count++;
    }
    
    // Sort events
    qsort(events, event_count, sizeof(Event), cmp_event);
    
    // Sort queries by y
    SortedQuery *sorted_queries = (SortedQuery *)malloc(q * sizeof(SortedQuery));
    for(int i=0; i<q; i++) {
        sorted_queries[i].y = queries[i].y;
        sorted_queries[i].l = queries[i].l;
        sorted_queries[i].index = queries[i].index;
    }
    qsort(sorted_queries, q, sizeof(SortedQuery), cmp_sorted_query);
    
    // Initialize answers
    int *ans = (int *)malloc(q * sizeof(int));
    for(int i=0; i<q; i++) {
        ans[i] = -1;
    }
    
    // Sweep line to determine valid queries
    int *active = (int *)calloc(k+1, sizeof(int));
    int active_types_count = 0;
    for(int i=0; i<event_count; i++) {
        Event e = events[i];
        if(e.type == 0) { // start
            int t = e.identifier;
            if(active[t] == 0)
                active_types_count++;
            active[t]++;
        }
        else if(e.type == 2) { // end
            int t = e.identifier;
            active[t]--;
            if(active[t] == 0)
                active_types_count--;
        }
        else { // query
            int q_idx = e.identifier;
            if(active_types_count == k)
                ans[q_idx] = 0; // valid
            else
                ans[q_idx] = -1; // invalid
        }
    }
    free(events);
    free(active);
    
    // Second phase: Compute max of min distances for valid queries
    for(int t=1; t<=k; t++) {
        if(types[t].num_x == 0)
            continue;
        for(int i=0; i < types[t].num_intervals; i++) {
            int a = types[t].merged_intervals[i].a;
            int b = types[t].merged_intervals[i].b;
            // Find lower and upper bounds in sorted_queries
            int lower = lower_bound_queries(sorted_queries, q, a);
            int upper = upper_bound_queries(sorted_queries, q, b);
            for(int j=lower; j < upper; j++) {
                int q_idx = sorted_queries[j].index;
                if(ans[q_idx] == -1)
                    continue;
                int l_val = sorted_queries[j].l;
                // Get min distance
                int min_d = get_min_distance(types[t].x, types[t].num_x, l_val);
                if(min_d > ans[q_idx])
                    ans[q_idx] = min_d;
            }
        }
    }
    
    // Output the answers
    for(int i=0; i<q; i++) {
        printf("%d\n", ans[i]);
    }
    
    // Free allocated memory
    for(int t=1; t<=k; t++) {
        if(types[t].num_intervals > 0)
            free(types[t].merged_intervals);
        if(types[t].num_x > 0)
            free(types[t].x);
    }
    free(types);
    free(queries);
    free(sorted_queries);
    free(ans);
    
    return 0;
}