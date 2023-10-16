#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        int i = 0;
        if (argc == 1)
            printf("Usage:\n  range(stop) -> range object\n  range(start, stop[, step]) -> range object\n\
  Return an object that produces a sequence of integers from start (inclusive)\n\
  to stop (exclusive) by step.  range(i, j) produces i, i+1, i+2, ..., j-1.\n\
  start defaults to 0, and stop is omitted!  range(4) produces 0, 1, 2, 3.\n\
  These are exactly the valid indices for a list of 4 elements.\n\
  When step > 0 is given, it specifies the increment (or decrement).\n");
        else if (argc == 2)
            for(i = 0; i < atoi(argv[1]); i++)
                printf("%d\n", i);
        else if (argc == 3)
            for(i = atoi(argv[1]); i < atoi(argv[2]); i++)
                printf("%d\n", i);
        else if (atoi(argv[3]) > 0)
            for(i = atoi(argv[1]); i < atoi(argv[2]); i+=atoi(argv[3]))
                printf("%d\n", i);
        return 0;
}
