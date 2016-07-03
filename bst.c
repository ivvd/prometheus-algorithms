#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Node subtree directions */
#define LEFT    0
#define RIGHT   1

typedef struct tree_node
{
    int key;
    struct tree_node *parent;
    struct tree_node *left;
    struct tree_node *right;
}BinaryTree_t;

struct 
{
    int sum;
    int cntr;
    int list[10];
}find_path_data;

BinaryTree_t* make_node(const int *key, BinaryTree_t *parent, unsigned int *count, int dir);
void inorder_tree_walk(BinaryTree_t *tree);
void inorder_tree_walk_store(BinaryTree_t *tree, int **buff);
void inorder_tree_walk_restore(BinaryTree_t *tree, int **buff);
int compare(const void *a, const void *b);
void print_tree(BinaryTree_t *tree);
int print_t(BinaryTree_t *tree);
void print_leafs(BinaryTree_t *tree);
void find_all_paths(BinaryTree_t *tree, int path[], int path_len);
void find_path(BinaryTree_t *tree, int path[], int path_len, int number);

int n = 0;

int main(int argc, const char *argv[])
{
    if(argc == 3)
    {
        printf("Hello!\n");
        
        /* Open file */
        FILE *fp;
        int x;
        int *arr, *tmp;
        printf("Opening file %s...\n", argv[1]);
        fp = fopen(argv[1], "r");

        /* Print third parameter - the sum for which we will find the path */
        int path_sum = atoi(argv[2]);
        printf("Will find path for sum %i.\n", path_sum);
        
        /* Find number of elements */
        while(fscanf(fp, "%i", &x) != EOF)
        {
            ++n;
        }
        rewind(fp);

        /* Allocate array and read from file to this array */
        arr = malloc(n*sizeof(int));
        if(arr == 0)
        {
            printf("Memory allocation error!\n");
            return -1;
        }
        tmp = arr;
        while(fscanf(fp, "%i", &x) != EOF)
        {
            *tmp++ = x;
        }

        /* Print array */
        //printf("%i\n", n);
        int node_number = 0; /* none zero items in this array are number of nodes in tree */
        for(x = 0; x < n; x++)
        {
            if(arr[x] != 0)
            {
                ++node_number;
            }
            //printf("%i ", arr[x]);
        }
        //printf("\n");

        BinaryTree_t *root;
        int i = 0;
        root = make_node(arr, 0, &i, LEFT);

        /* Store tree to array */
        int *tree_buff = malloc(node_number*sizeof(int));
        int *buff_p = tree_buff;
        inorder_tree_walk_store(root, &buff_p);
        for(i = 0; i < node_number; i++)
        {
            //printf("%i ", tree_buff[i]);
        }
        //printf("\n");
        
        /* Sort array */
        qsort(tree_buff, node_number, sizeof(int), compare);
        for(i = 0; i < node_number; i++)
        {
            //printf("%i ", tree_buff[i]);
        }
        //printf("\n");

        /* Update tree from array */
        buff_p = tree_buff;
        inorder_tree_walk_restore(root, &buff_p);
        //inorder_tree_walk(root);
        //printf("\n");

        /* Print tree */
        //print_tree(root);
        //print_t(root);
        
        /* Inorder print */
        //inorder_tree_walk(root);
        //printf("\n");
        
        /* Print tree leafs */
        printf("Leafs: ");
        print_leafs(root);
        printf("\n");

        /* Print root */
        printf("Root: %i\n", root->key);

        /* Print all root to leaf paths */
        int down_path[300];
        int down_path_len = 0;
        //printf("-------\n");
        //find_all_paths(root, down_path, down_path_len);
        //printf("-------\n");
        
        /* Find path with sum */
        down_path_len = 0;
        find_path(root, down_path, down_path_len, path_sum);

        /* Free resources */
        fclose(fp);
        free(arr);
        free(tree_buff);
    }
    else
    {
        printf("Wrong number of parameters!\n");
    }

    return 0;
}

int compare(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

BinaryTree_t* make_node(const int *key, BinaryTree_t *parent, unsigned int *count, int dir)
{
    //printf("%i\t%i\n", *count, key[*count]);
    BinaryTree_t *ret = 0;

    if(key[*count] != 0 && *count < n)
    {
        BinaryTree_t *new_node = malloc(sizeof(BinaryTree_t));
        new_node->key = key[*count];
        new_node->parent = parent;
        new_node->left = 0;
        new_node->right = 0;
        ret = new_node;

        if(parent != 0)
        {
            if(dir == LEFT)
            {
                parent->left = new_node;
            }
            else
            {
                parent->right = new_node;
            }
        }
        
        *count += 1;
        if(*count >= n)
        {
            return 0;
        }
        make_node(key, new_node, count, LEFT);

        *count += 1;
        if(*count >= n)
        {
            return 0;
        }
        make_node(key, new_node, count, RIGHT);
    }

    return ret;
}

void inorder_tree_walk(BinaryTree_t *tree)
{
    if(tree != 0)
    {
        inorder_tree_walk(tree->left);
        printf("%i ", tree->key);
        inorder_tree_walk(tree->right);
    }
}

void print_leafs(BinaryTree_t *tree)
{
    if(tree != 0)
    {
        print_leafs(tree->left);
        if(tree->left == 0 && tree->right == 0)
        {
            //printf("%i %x %x\n", tree->key, (uint32_t)tree->left, (uint32_t)tree->right);
            printf("%i ", tree->key);
        }
        print_leafs(tree->right);
    }
}

void inorder_tree_walk_store(BinaryTree_t *tree, int **buff)
{
    if(tree != 0)
    {
        inorder_tree_walk_store(tree->left, buff);
        **buff = tree->key;
        *buff += 1;
        inorder_tree_walk_store(tree->right, buff);
    }
}

void inorder_tree_walk_restore(BinaryTree_t *tree, int **buff)
{
    if(tree != 0)
    {
        inorder_tree_walk_restore(tree->left, buff);
        tree->key = **buff;
        *buff += 1;
        inorder_tree_walk_restore(tree->right, buff);
    }
}

void print_tree(BinaryTree_t *tree)
{
    if(tree != 0)
    {
        print_tree(tree->left);
        printf("\n%i\t", tree->key);
        print_tree(tree->right);
    }
}

/* Find all root to leaf paths */
void find_all_paths(BinaryTree_t *tree, int path[], int path_len)
{
    if(tree != 0)
    {
        path[path_len++] = tree->key;

        if(tree->left == 0 && tree->right == 0)
        {
            int i;
            for(i = 0; i < path_len; i++)
            {
                printf("%i ", path[i]);
            }
            printf("\n");
        }
        else
        {
            find_all_paths(tree->left, path, path_len);
            find_all_paths(tree->right, path, path_len);
        }
    }
}

/* Find downgrade path which element's sum equal to parameter. */
void find_path(BinaryTree_t *tree, int path[], int path_len, int number)
{
    if(tree != 0)
    {
        path[path_len++] = tree->key;

        int i, sum = 0;
        for(i = path_len-1; i >= 0; i--)
        {
            sum += path[i];
            if(sum == number)
            {
                int j;
                for(j = i; j < path_len; j++)
                {
                    printf("%i ", path[j]);
                }
                printf("\n");
                break;
            }
        }

        find_path(tree->left, path, path_len, number);
        find_path(tree->right, path, path_len, number);
    }
}

#define TREE_LINES  100
#define LINE_LENGTH 1000

int _print_t(BinaryTree_t *tree, int is_left, int offset, int depth, char s[TREE_LINES][LINE_LENGTH])
{
    char b[6];
    int width = 6;
    int i;

    if (!tree) return 0;

    sprintf(b, "(%04d)", tree->key);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

    for (i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }

    //sprintf(b, "%04d", depth);
    //for (i = 0; i < 4; i++)
    //    s[2 * depth][LINE_LENGTH + i - 8] = b[i];

    return left + width + right;
}

int print_t(BinaryTree_t *tree)
{
    char s[TREE_LINES][LINE_LENGTH];
    int i;
    for (i = 0; i < TREE_LINES; i++)
    {
        memset(&s[i][0], ' ', LINE_LENGTH-1);
        s[i][LINE_LENGTH-1] = 0;
    }

    _print_t(tree, 0, 0, 0, s);

    for (i = 0; i < TREE_LINES; i++)
    {
        printf("%s\n", s[i]);
    }
}
