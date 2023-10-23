#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAXGR 10

int main(int argc, char *argv[])
{
    char *buf;
    char *err_buf;
    size_t len = 0;
    int chars;

    int err_code;

    regex_t regex;
    regmatch_t bags[MAXGR];
    
    if ((err_code = regcomp(&regex, argv[1], 0)) != 0)
    {
        err_buf = malloc(512);
        regerror(err_code, &regex, err_buf, 512);
        printf("%s\n", err_buf);
        free(err_buf);
        return -1;
    }

    for (buf = NULL; (chars = getline(&buf, &len, stdin)) != -1; buf = NULL)
    {
        buf[chars - 1] = 0;
        if (regexec(&regex, buf, MAXGR, bags, 0) == 0)
        {
            chars = strlen(argv[2]);
            char * subs = malloc(chars);
            int j = 0;
            for (int i=0; argv[2][i] != 0; i++, j++)
            {
                if (argv[2][i] != '\\')
                    subs[j] = argv[2][i];
                else if (argv[2][i+1] == '\\')
                {
                    subs[j] = '\\';
                    i++;
                }
                else if (argv[2][i+1] - '0' < 0 || argv[2][i+1] - '0' > MAXGR)
                {
                    printf("There is no group \"\\%c\"\n",argv[2][i+1]);
                    return -2;
                }  
                else if (bags[argv[2][i+1] - '0'].rm_so < 0)
                {
                    printf("There is no group #%c\n",argv[2][i+1]);
                    return -2;
                }  
                else 
                {
                    int num = argv[2][i+1] - '0';
                    int b = bags[num].rm_so, e = bags[num].rm_eo;
                    subs = realloc(subs, chars += e - b);
                    sprintf(subs, "%.*s%.*s", j, subs, e - b, buf + b);
                    j += e - b - 1;
                    i++;
                }
            }
            subs[j] = 0;
            int b = bags[0].rm_so, e = bags[0].rm_eo;
            char * res = malloc(j+len+e-b);
            sprintf(res, "%.*s%s%.*s", b, buf, subs, (int)len-e, buf+e);
            puts(res);
            free(subs);
            free(res);
        }
        free(buf);
    }

    regfree(&regex);
    return 0;
}
