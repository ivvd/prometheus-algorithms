#include <stdio.h>
#include <stdlib.h>

#define HEAP_PARENT(x)  (x-1)/2
#define HEAP_LEFT(x)    2*(x)+1
#define HEAP_RIGHT(x)   2*(x)+2

typedef struct
{
    int *data;
    int size;
}Heap_t;

void print_heap(Heap_t *heap, char *end, int numb);
void min_heapify(Heap_t *heap, int x);
void max_heapify(Heap_t *heap, int x);

void max_heapify(Heap_t *heap, int x)
{
    int largest = x;
    int l = HEAP_LEFT(x);
    int r = HEAP_RIGHT(x);
    
    if((l < heap->size) && (heap->data[l] > heap->data[x]))
    {
        largest = l;
    }

    if((r < heap->size) && (heap->data[r] > heap->data[largest]))
    {
        largest = r;
    }

    if(largest != x)
    {
        int temp = heap->data[x];
        heap->data[x] = heap->data[largest];
        heap->data[largest] = temp;
        max_heapify(heap, largest);
    }
}

void build_max_heap(Heap_t *heap)
{
    int i = heap->size / 2 - 1;
    while(i >= 0)
    {
        max_heapify(heap, i);
        --i;
    }
}

int heap_extract_max(Heap_t *heap)
{
    int max = heap->data[0];
    heap->data[0] = heap->data[heap->size-1];
    heap->size -= 1;
    max_heapify(heap, 0);
    return max;
}

int heap_extract_min(Heap_t *heap)
{
    int min = heap->data[0];
    heap->data[0] = heap->data[heap->size-1];
    heap->size -= 1;
    min_heapify(heap, 0);
    return min;
}

void max_heap_increase_key(Heap_t *heap, int x, int key)
{
    heap->data[x] = key;
    while((x > 0) && (heap->data[HEAP_PARENT(x)] < heap->data[x]))
    {
        int temp = heap->data[HEAP_PARENT(x)];
        heap->data[HEAP_PARENT(x)] = heap->data[x];
        heap->data[x] = temp;
        x = HEAP_PARENT(x);
    }
}

void max_heap_insert(Heap_t *heap, int key)
{
    heap->size += 1;
    max_heap_increase_key(heap, heap->size-1, key);
}

void min_heapify(Heap_t *heap, int x)
{
    int smallest = x;
    int l = HEAP_LEFT(x);
    int r = HEAP_RIGHT(x);
    
    if((l < heap->size) && (heap->data[l] < heap->data[x]))
    {
        smallest = l;
    }

    if((r < heap->size) && (heap->data[r] < heap->data[smallest]))
    {
        smallest = r;
    }

    if(smallest != x)
    {
        int temp = heap->data[x];
        heap->data[x] = heap->data[smallest];
        heap->data[smallest] = temp;
        min_heapify(heap, smallest);
    }
}

void build_min_heap(Heap_t *heap)
{
    int i = heap->size / 2 - 1;
    while(i >= 0)
    {
        min_heapify(heap, i);
        --i;
    }
}

void min_heap_increase_key(Heap_t *heap, int x, int key)
{
    heap->data[x] = key;
    while((x > 0) && (heap->data[HEAP_PARENT(x)] > heap->data[x]))
    {
        int temp = heap->data[HEAP_PARENT(x)];
        heap->data[HEAP_PARENT(x)] = heap->data[x];
        heap->data[x] = temp;
        x = HEAP_PARENT(x);
    }
}

void min_heap_insert(Heap_t *heap, int key)
{
    heap->size += 1;
    min_heap_increase_key(heap, heap->size-1, key);
}

void print_heap(Heap_t *heap, char *end, int numb)
{
    int i;
    if(numb <= 0)
    {
        numb = heap->size;
    }
    for(i = 0; i < numb; i++)
    {
        printf("%i ", heap->data[i]);
    }
    printf("%s", end);
}

void init_find_median(int max_size, Heap_t *heap_low, Heap_t *heap_high)
{
    int heap_size = max_size/2 + 2;
    int *heap_low_mem = malloc(heap_size*sizeof(int));
    int *heap_high_mem = malloc(heap_size*sizeof(int));
    heap_low->data = heap_low_mem;
    heap_high->data = heap_high_mem;
    heap_low->size = 0;
    heap_high->size = 0;
}

void del_find_median(Heap_t *heap_low, Heap_t *heap_high)
{
    free(heap_low->data);
    free(heap_high->data);
}

int find_median(int new, Heap_t *heap_low, Heap_t *heap_high, int *m1, int *m2)
{
    int temp = 0;
    int ret = 0;

    if((heap_low->size > 0) && (new < heap_low->data[0]))
    {
        max_heap_insert(heap_low, new);
    }
    else if((heap_high->size > 0) && (new > heap_low->data[0]))
    {
        min_heap_insert(heap_high, new);
    }
    else
    {
        max_heap_insert(heap_low, new);
    }

    if(heap_low->size - heap_high->size > 1)
    {
        temp = heap_extract_max(heap_low);
        min_heap_insert(heap_high, temp);
    }
    else if(heap_high->size - heap_low->size > 1)
    {
        temp = heap_extract_min(heap_high);
        max_heap_insert(heap_low, temp);
    }

    if(heap_high->size == heap_low->size)
    {
        ret = 1;
        if(heap_high->data[0] > heap_low->data[0])
        {
            *m2 = heap_high->data[0];
            *m1 = heap_low->data[0];
        }
        else
        {
            *m1 = heap_high->data[0];
            *m2 = heap_low->data[0];
        }
    }
    else if(heap_high->size > heap_low->size)
    {
        ret = 0;
        *m1 = heap_high->data[0];
    }
    else
    {    
        ret = 0; 
        *m1 = heap_low->data[0];
    }

    return ret;
}

int main(int argc, const char *argv[])
{
    printf("Hello!\n");

    if(argc == 1)
    {
        int arr[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
        Heap_t my_heap;
        my_heap.size = 10;
        my_heap.data = arr;

        print_heap(&my_heap, "\n", 0);
        build_min_heap(&my_heap);
        print_heap(&my_heap, "\n", 0);
        min_heap_insert(&my_heap, 1);
        print_heap(&my_heap, "\n", 0);
    }
    else if(argc == 2)
    {
        printf("Opening file %s...\n", argv[1]);

        FILE *fp;
        int arr_len = 0;
        int new_numb = 0;
        int i = 0;
        int *arr;
        int target = 2014;

        fp = fopen(argv[1], "r");
        fscanf(fp, "%i", &arr_len);
        arr = malloc(arr_len*sizeof(int));
        
        while(fscanf(fp, "%i", &new_numb) != EOF)
        {
            arr[i++] = new_numb;
        }
        
        //printf("%i\n", arr_len);
        //for(i = 0; i < arr_len; i++)
        //{
        //    printf("%i ", arr[i]);
        //}
        //printf("\n");

        Heap_t heap_low, heap_high;
        int m1, m2, ret;
        init_find_median(arr_len, &heap_low, &heap_high);
        for(i = 0; i < arr_len; i++)
        {
            ret = find_median(arr[i], &heap_low, &heap_high, &m1, &m2);
            if(ret == 0)
            {
                if(i == target)
                {
                    printf("%i\n", m1);
                    printf("Heap low: ");
                    print_heap(&heap_low, "\n", 5);
                    printf("Heap high: ");
                    print_heap(&heap_high, "\n\n", 5);
                }
            }
            else
            {
                if(i == target)
                {
                    printf("%i %i\n", m1, m2);
                    printf("Heap low: ");
                    print_heap(&heap_low, "\n", 5);
                    printf("Heap high: ");
                    print_heap(&heap_high, "\n\n", 5);
                }
            }
            //print_heap(&heap_low, "\n", 0);
            //print_heap(&heap_high, "\n\n", 0);
        }
        del_find_median(&heap_low, &heap_high);
        
        fclose(fp);
        free(arr);
    }
    else
    {
        printf("Wrong number of parameters!\n");
    }

    return 0;
}

