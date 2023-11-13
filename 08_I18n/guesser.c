#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
//#include "config.h"

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

int main(int argc, char *argv[])
{
    char *dir;
    char *buf = NULL;
    size_t len = 0;

    dir = dirname(realpath(argv[0], NULL));
    setlocale (LC_ALL, "");
    bindtextdomain ("guesser", LOCALE_PATH);
    textdomain ("guesser");

    puts(_("Think of a number from 1 to 100.\n"));
    
    int low = 1;
    int high = 100;    

    while (low != high)
    {
        int step = (low+high)/2;
        printf(_("Is your number greater than %d? [y/n]:"), step);
        if (getline(&buf, &len, stdin))
        {
            if (strcmp(buf, _("y\n")) == 0)
                low = step+1;
            else if (strcmp(buf, _("n\n")) == 0)
                high = step;
        }
        
    }
    printf(_("Your number is %d!\n"), low);

    return 0;
}
