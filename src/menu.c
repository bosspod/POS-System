void menu()
{
    int main_menu_selected;

    int repeat, yes, no;

    repeat = 1, yes = 1, no = 0;

    do
    {
        printf("\n\n\n");
        printf("======================================\n");
        printf("         WELCOME TO BRK STORE         \n");
        printf("======================================\n\n\n");
        printf("**************************************\n");
        printf("1 --> Inventory System\n");
        printf("2 --> Accounting System\n");
        printf("3 --> Point of sale (POS)\n");
        printf("4 --> Other System\n");
        printf("0 --> Exit Program\n");
        printf("**************************************\n\n\n");

        printf("Enter Choice : ");
        scanf("%d", &main_menu_selected);

        switch (main_menu_selected)
        {
        case 1:
            inventory();
            repeat = no;
            break;
        case 2:
            accounting();
            repeat = no;
            break;
        case 3:
            pos();
            repeat = no;
            break;
        case 4:
            other();
            repeat = no;
            break;
        case 0:
            exit(0);
            break;
        default:
            for (int i = 0; i < 10; i++)
            {
                printf("Invalid Choice (Try Again)\n");
            }
            repeat = yes;
            break;
        }
    } while (repeat == yes);
}