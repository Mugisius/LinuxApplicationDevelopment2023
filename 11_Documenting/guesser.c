<<<<<<< HEAD
/** @mainpage Number guesser
 * This is free and unencumbered software released into the public domain.
 *
 * This is simple program that can guess the hidden number
 */

/** @file guessr.c
 * Implementation
 *
 * The program tries to guess the number by dividing the allowed 
 * interval into two parts, and asking which of the parts the 
 * hidden number belongs to.
 */



=======
>>>>>>> 581791d36270e0aa9104f0aee1c5afd8a83682cf
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include "config.h"

<<<<<<< HEAD
#define _(STRING) gettext(STRING) /**< Short alias for gettext() */
#define LOCALE_PATH "." /**< Local path */



/** Translate int @p n to string view
 *
 * @param n number to translate
 * @param buf buffer to place view
 * @param roman is current mode is Roman notation
 * 
 * Writes a string representation of the number @p n to the
 * buffer @p buf, depending on the selected notation
 */
void printNum(int n, char * buf, int roman)
{
    char *romanInt[] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", 
                        "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", 
                        "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", 
                        "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX",
                        "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", 
                        "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", 
                        "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", 
                        "XCIX", "C"};
    if (roman)
        strcpy(buf, romanInt[n - 1]);
    else
        sprintf(buf, "%d", n);    
}

/** @page guesser
 * Number guesser
 * @section SYNOPSIS
 * `guesser` [ \a -r ]
 * @section DESCRIPTION
 * Guess th hidden number between 1 and 100.
 *
 */
int main(int argc, char *argv[])
{
    char *dir; /**< */
    char *buf = NULL;
    size_t len = 0; 
    int roman = 0;     
    char intbuf[16]; 
=======
#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

int numPrint(int n)
{
    
}

int main(int argc, char *argv[])
{
    char *dir;
    char *buf = NULL;
    size_t len = 0;

    if (argc > 2)
    {
        printf("Usage: %s [-r]", argv[0]);
        exit(1);
    }
    if (argc == 2)
        if (strcmp(argv[1], "-r") == 0)
            using_roman = 1;
        else
        {
            printf("%s: Wrong argument: %s", argv[0], argv[1]);
            exit(2);
        }
>>>>>>> 581791d36270e0aa9104f0aee1c5afd8a83682cf

    dir = dirname(realpath(argv[0], NULL));
    setlocale (LC_ALL, "");
    bindtextdomain ("guesser", LOCALE_PATH);
    textdomain ("guesser");

<<<<<<< HEAD

    if (argc > 2)
    {
        printf(_("Usage: %s [-r | --help]\n"), argv[0]);
        exit(1);
    }
    if (argc == 2)
        if (strcmp(argv[1], "-r") == 0)
            roman = 1;
        else if (strcmp(argv[1], "--help") == 0)
        {
            printf(_("\nNumber guesser\n\nThis is free and unencumbered software released into the public domain.\
\n\n\tThis is simple program that can guess the hidden number\n\tThe program tries to guess the number by dividing the allowed\
\n\tinterval into two parts, and asking which of the parts the\n\thidden number belongs to.\n\nUsage:\n\t %s [-r]\n\
\n\n\t-r\tSwitch number notation to Roman\n\n"), argv[0]);
            exit(0);
        }
        else
        {
            printf(_("Usage: %s [-r]\n"), argv[0]);
            exit(2);
        }

=======
>>>>>>> 581791d36270e0aa9104f0aee1c5afd8a83682cf
    puts(_("Think of a number from 1 to 100.\n"));
    
    int low = 1;
    int high = 100;    

    while (low != high)
    {
        int step = (low+high)/2;
<<<<<<< HEAD
        printNum(step, intbuf, roman);
        printf(_("Is your number greater than %s? [y/n]:"), intbuf);
=======
        printf(_("Is your number greater than %d? [y/n]:"), step);
>>>>>>> 581791d36270e0aa9104f0aee1c5afd8a83682cf
        if (getline(&buf, &len, stdin))
        {
            if (strcmp(buf, _("y\n")) == 0)
                low = step+1;
            else if (strcmp(buf, _("n\n")) == 0)
                high = step;
        }
        
    }
<<<<<<< HEAD
    printNum(low, intbuf, roman);
    printf(_("Your number is %s!\n"), intbuf);
=======
    printf(_("Your number is %d!\n"), low);
>>>>>>> 581791d36270e0aa9104f0aee1c5afd8a83682cf

    return 0;
}
