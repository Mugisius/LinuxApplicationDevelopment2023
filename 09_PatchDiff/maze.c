#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
 
#define msize 6
#define arsize 2*msize*(msize-1)
#define prsize (2*msize+1)*(2*msize+2)
 

int in(int * node, int in_tree[msize*msize][2], int in_tree_n)
{
    int in_t = 0;
    for (int i = 0; i < in_tree_n; i++)
        if (node[0] == in_tree[i][0] && node[1] == in_tree[i][1])
            in_t = 1;
    return in_t; 
}

int main()
{
    srand(time(NULL));

    int G[arsize][2][2], spanning[msize*msize-1][2][2], in_tree[msize*msize][2];
    int spanning_n = 0, in_tree_n = 0;

    int k = 0;
    for (int i = 0; i < msize-1; i++)
        for (int j = 0; j < msize; j++,k++)
        {
            G[k][0][0] = i;
            G[k][0][1] = j;
            G[k][1][0] = i+1;
            G[k][1][1] = j;
        }
    for (int i = 0; i < msize; i++)
        for (int j = 0; j < msize-1; j++,k++)
        {
            G[k][0][0] = i;
            G[k][0][1] = j;
            G[k][1][0] = i;
            G[k][1][1] = j+1;
        }
    
    //for(int i = 0; i < arsize; i++)
    //    printf("(%d,%d)-(%d,%d)\n",G[i][0][0], G[i][0][1],G[i][1][0],G[i][1][1]);

    char tmp[4*sizeof(int)];
    char *arr = (char*) G;
    size_t stride = 4*sizeof(int);

    size_t i;
    for (i = 0; i < arsize-1; ++i) 
    {
        size_t rnd = (size_t) rand();
        size_t j = i + rnd / (RAND_MAX / (arsize - i) + 1);
        memcpy(tmp, arr + j * stride, 4*sizeof(int));
        memcpy(arr + j * stride, arr + i * stride, 4*sizeof(int));
        memcpy(arr + i * stride, tmp, 4*sizeof(int));
    }
    //printf("\n\n");
    //for(int i = 0; i < arsize; i++)
    //    printf("(%d,%d)-(%d,%d)\n",G[i][0][0], G[i][0][1],G[i][1][0],G[i][1][1]);
    
    
    in_tree[in_tree_n][0] = rand() % msize;
    in_tree[in_tree_n][1] = rand() % msize;
    in_tree_n++;

    while (in_tree_n < msize*msize)
    {
        for (int i = 0;;i++)
        {
            if (in(G[i][0], in_tree, in_tree_n) && ! in(G[i][1], in_tree, in_tree_n))
            {
                memcpy(*spanning[spanning_n], *G[i], 4*sizeof(int));
                spanning_n++;
                in_tree[in_tree_n][0] = G[i][1][0];
                in_tree[in_tree_n][1] = G[i][1][1];
                in_tree_n++;
                break;
            }
            if (! in(G[i][0], in_tree, in_tree_n) && in(G[i][1], in_tree, in_tree_n))
            {
                memcpy(*spanning[spanning_n], *G[i], 4*sizeof(int));
                spanning_n++;
                in_tree[in_tree_n][0] = G[i][0][0];
                in_tree[in_tree_n][1] = G[i][0][1];
                in_tree_n++;
                break;
            }
        }
    }
    //printf("\n\n");
    //for(int i = 0; i < spanning_n; i++)
    //    printf("(%d,%d)-(%d,%d)\n",spanning[i][0][0], spanning[i][0][1],spanning[i][1][0],spanning[i][1][1]);

    
    char maze[prsize]; 
    for(int i = 0; i < prsize; i++)
        if ((i+1)%(2*msize+2) == 0)
            maze[i] = '\n';
        else if (i % (4*msize+4) > (2*msize+1) && i % 2 == 1)
            maze[i] = '.';
        else
            maze[i] = '#';
    maze[prsize-1] = 0;
    //printf("%s\n\n", maze); 
        
    
    for(int i = 0; i < spanning_n; i++)
        maze[ spanning[i][0][0] + spanning[i][1][0] + 1 + (spanning[i][0][1] + spanning[i][1][1] + 1) *(2*msize+2) ] = '.';
    printf("%s\n", maze); 
	return 0;
}
