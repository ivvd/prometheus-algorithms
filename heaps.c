#include <stdio.h>

#define HEAP_PARENT(x)  (x-1)/2
#define HEAP_LEFT(x)    2*(x)+1
#define HEAP_RIGHT(x)   2*(x)+2

typedef struct
{
    int *data;
    int size;
}Heap_t;

void print_heap(Heap_t *heap, char *end);

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

void print_heap(Heap_t *heap, char *end)
{
    int i;
    for(i = 0; i < heap->size; i++)
    {
        printf("%i ", heap->data[i]);
    }
    printf("%s", end);
}

int main(int argc, const char *argv[])
{
    printf("Hello!\n");

    int arr[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    Heap_t my_heap;
    my_heap.size = 10;
    my_heap.data = arr;

    print_heap(&my_heap, "\n");
    build_min_heap(&my_heap);
    print_heap(&my_heap, "\n");

    return 0;
}

