void other()
{

    int other_menu_selected;

    int repeat, yes, no;

    repeat = 1, yes = 1, no = 0;

    do
    {
        printf("\n\n\n");
        printf("======================================\n");
        printf("         WELCOME TO BRK STORE         \n");
        printf("             Other System             \n");
        printf("======================================\n\n\n");
        printf("**************************************\n");
        printf("1 --> Simple Calculator\n");
        printf("9 --> Main Menu\n");
        printf("0 --> Exit Program\n");
        printf("**************************************\n\n\n");

        printf("Enter Choice : ");
        scanf("%d", &other_menu_selected);

        switch (other_menu_selected)
        {
        case 1:
            sim_cal();
            repeat = no;
            break;
        case 9:
            menu();
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

void sim_cal()
{
    int op;
    double first, second;
    printf("\n\n\n");
    printf("======================================\n");
    printf("         WELCOME TO BRK STORE         \n");
    printf("              CALCULATOR              \n");
    printf("======================================\n\n\n");
    printf("**************************************\n");
    printf("1 --> + (Plus)\n");
    printf("2 --> - (Minus)\n");
    printf("3 --> x (Multiply)\n");
    printf("4 --> ÷ (Divide)\n");
    printf("0 --> Exit Program\n");
    printf("**************************************\n\n\n");

    printf("Enter Choice : ");
    scanf("%d", &op);
    printf("\nEnter First operands: ");
    scanf("%lf", &first);
    printf("Enter Second operands: ");
    scanf("%lf", &second);

    printf("\n");
    switch (op)
    {
    case 1:
        for (int i = 0; i < 3; i++)
        {
            printf("%.1lf + %.1lf = %.1lf\n", first, second, first + second);
        }
        break;
    case 2:
        for (int i = 0; i < 3; i++)
        {
            printf("%.1lf - %.1lf = %.1lf\n", first, second, first - second);
        }
        break;
    case 3:
        for (int i = 0; i < 3; i++)
        {
            printf("%.1lf * %.1lf = %.1lf\n", first, second, first * second);
        }
        break;
    case 4:
        for (int i = 0; i < 3; i++)
        {
            printf("%.1lf / %.1lf = %.1lf\n", first, second, first / second);
        }
        break;
    default:
        for (int i = 0; i < 3; i++)
        {
            printf("Error! operator is not correct.");
        }
    }

    int back;

    printf("\n\nEnter (1) for calculate again ! \n");
    printf("\n\nEnter (0) for go to Other Page ! \n");
    printf("\n\nEnter number : ");
    scanf("%d", &back);
    switch (back)
    {
    case 1:
        sim_cal();
        break;

    default:
        other();
        break;
    }
}
