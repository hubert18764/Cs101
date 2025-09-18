/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main(){
    char grade = 'B';
    printf ("Your grade is %c\n", grade);
    switch (grade) {
        case 'A':
            printf ("Excellent!\n");
            break;
        case 'B':
        case 'C':
            printf ("Well done!\n");
            break;
        case 'D':
        case 'F':
            printf ("Better try again!\n");
            break;
        default:
            printf ("Invali grade\n");
    }
    return 0;
}
