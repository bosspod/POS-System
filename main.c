
/////////////////////////////////////////////
//              GROUP MEMBER               //
// 1. PODSAWEE WANATHAM      (65070503458) //
// 2. PATTAVEE KAEWPITAKKHUN (65070503460) //
// 3. RAVIBHAS SVETARUNDRA   (65070503463) //
// 4. PARATTHAKON SUKSUKHON  (65070503457) //
/////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "src/menu.h"
#include "src/inventory.h"
#include "src/accounting.h"
#include "src/pos.h"
#include "src/other.h"
#include "src/menu.c"
#include "src/inventory.c"
#include "src/accounting.c"
#include "src/pos.c"
#include "src/other.c"

int main()
{
    printf("======================================\n");
    printf("           BRK GROUP MEMBER           \n");
    printf("======================================\n");
    printf("1. PODSAWEE WANATHAM (65070503458)\n");
    printf("2. PATTAVEE KAEWPITAKKHUN (65070503460)\n");
    printf("3. RAVIBHAS SVETARUNDRA (65070503463)\n");
    printf("4. PARATTHAKON SUKSUKHON (65070503457)\n");
    printf("5. Finding Member Jaaa!!\n");
    printf("======================================\n\n\n");

    int main_menu;
    printf("Enter ( 1 ) to Enter the Program : ");
    scanf("%d", &main_menu);

    switch (main_menu)
    {
    case 1:
        menu();
        break;

    default:
        exit(0);
        break;
    }

    return 0;
}