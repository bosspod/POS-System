
void inventory()
{

    int inventory_menu_selected;

    int repeat, yes, no;

    repeat = 1, yes = 1, no = 0;

    do
    {
        printf("\n\n\n");
        printf("======================================\n");
        printf("         WELCOME TO BRK STORE         \n");
        printf("           Inventory System           \n");
        printf("======================================\n\n\n");
        printf("**************************************\n");
        printf("1 --> Add New Product\n");
        printf("2 --> List All Product\n");
        printf("3 --> View Product\n");
        printf("4 --> Remove Product\n");
        printf("5 --> Add Stock\n");
        printf("9 --> Main Menu\n");
        printf("0 --> Exit Program\n");
        printf("**************************************\n\n\n");

        printf("Enter Choice : ");
        scanf("%d", &inventory_menu_selected);

        switch (inventory_menu_selected)
        {
        case 1:
            add_item();
            repeat = no;
            break;
        case 2:
            list_item();
            repeat = no;
            break;
        case 3:
            open_file();
            repeat = no;
            break;
        case 4:
            remove_item();
            repeat = no;
            break;
        case 5:
            add_stock();
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

void add_item()
{
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, 20, "%d/%m/%G %H:%M:%S", timeinfo);

    char product_name[1000];
    char file_name[1000];
    char path[6] = {'d', 'a', 't', 'a', '/', '\0'};

    int product_quantity;
    double product_price;
    double product_cost;
    double profit;
    int product_minimum;
    int product_purchased;
    int confirm;
    FILE *f;

    product_purchased = 0;

    printf("\n\n\n");
    printf("======================================\n");
    printf("               ADD ITEM               \n");
    printf("======================================\n\n");
    printf("Enter Product Name : ");
    scanf("%s", product_name);
    fflush(stdin);
    printf("Enter Product Quantity : ");
    scanf("%d", &product_quantity);
    printf("Enter Product Price : ");
    scanf("%lf", &product_price);
    printf("Enter Product Cost : ");
    scanf("%lf", &product_cost);
    printf("Enter Product Minimum QTY : ");
    scanf("%d", &product_minimum);
    printf("Save the Product !! Enter (1) to Confirm : ");
    scanf("%d", &confirm);

    strcpy(file_name, product_name);

    profit = product_price - product_cost;

    switch (confirm)
    {
    case 1:

        strcat(file_name, ".productdata");
        int i, j;

        i = 0;
        j = 0;

        while (path[i] != '\0')
        {
            i++;
        }
        while (file_name[j] != '\0')
        {
            path[i] = file_name[j];
            j++;
            i++;
        }
        path[i] = '\0';

        f = fopen(path, "w");
        fprintf(f, "%s\n%d\n%.2f\n%.2lf\n%.2lf\n%d\n%d\n%s\n", product_name, product_quantity, product_price, product_cost, profit, product_minimum, product_purchased, timestamp);
        fclose(f);
        printf("\n");
        for (int i = 0; i < 3; i++)
        {
            printf("Product Save !!\n");
        }
        int back;

        printf("\n\nEnter (1) for add other Item ! \n");
        printf("\n\nEnter (0) for go to Inventory Page ! \n");
        printf("\n\nEnter number : ");

        scanf("%d", &back);
        switch (back)
        {
        case 1:
            add_item();
            break;

        default:
            inventory();
            break;
        }
        break;

    default:
        inventory();
        break;
    }
}

void add_stock()
{
    FILE *file, *temp;

    char filename[1000];
    char tempfile[1000];
    char path_real[6] = {'d', 'a', 't', 'a', '/', '\0'};
    char path_temp[11] = {'d', 'a', 't', 'a', '/', 't', 'e', 'm', 'p', '_', '\0'};
    char buffer[1000];
    char buffer_old[1000];
    int replace;
    int last_value;
    int replace_line;
    int quantity;

    printf("\n\n\n");
    printf("======================================\n");
    printf("               ADD STOCK              \n");
    printf("======================================\n\n");
    printf("Product name : ");
    scanf("%s", filename);
    strcpy(tempfile, filename);
    strcat(tempfile, ".tmp");
    strcat(filename, ".productdata");

    int i, j;

    i = 0;
    j = 0;

    while (path_temp[i] != '\0')
    {
        i++;
    }
    while (tempfile[j] != '\0')
    {
        path_temp[i] = tempfile[j];
        j++;
        i++;
    }
    path_temp[i] = '\0';

    i = 0;
    j = 0;

    while (path_real[i] != '\0')
    {
        i++;
    }
    while (filename[j] != '\0')
    {
        path_real[i] = filename[j];
        j++;
        i++;
    }
    path_real[i] = '\0';

    char r_file[1000];
    strcpy(r_file, path_real);

    replace_line = 2;
    printf("Product Quantity : ");
    scanf("%d", &quantity);
    if (quantity > 0)
    {
        file = fopen(r_file, "r");
        if (file == NULL)
        {
            printf("\n");
            for (int i = 0; i < 3; i++)
            {
                printf("Item not Found!! \n");
            }
        }
        else
        {
            bool keep_reading = true;
            int current_line = 1;
            do
            {
                fgets(buffer_old, 2048, file);
                if (feof(file))
                {
                    keep_reading = false;
                }
                else if (current_line == replace_line)
                {
                    last_value = atoi(buffer_old);
                }
                current_line++;
            } while (keep_reading);
            fclose(file);

            replace = last_value + quantity;
            file = fopen(r_file, "r");
            temp = fopen(path_temp, "w");

            keep_reading = true;
            current_line = 1;

            do
            {
                fgets(buffer, 2048, file);
                if (feof(file))
                {
                    keep_reading = false;
                }
                else if (current_line == replace_line)
                {
                    fprintf(temp, "%d\n", replace);
                    printf("\n");
                    for (int i = 0; i < 3; i++)
                    {
                        printf("Add Stock Successful!!\n");
                    }
                }
                else
                {
                    fprintf(temp, "%s", buffer);
                }
                current_line++;
            } while (keep_reading);

            fclose(file);
            fclose(temp);

            remove(r_file);
            rename(path_temp, r_file);
        }
    }
    else
    {
        printf("\n");
        for (int i = 0; i < 3; i++)
        {
            printf("Please Enter a positive number only!!\n");
        }
    }
    int back;

    printf("\n\nEnter (1) for add more Stock ! \n");
    printf("\n\nEnter (0) for go to Inventory Page ! \n");
    printf("\n\nEnter number : ");
    scanf("%d", &back);
    switch (back)
    {
    case 1:
        add_stock();
        break;

    default:
        inventory();
        break;
    }
}

void list_item()
{
    DIR *dir;
    FILE *entry_file;
    struct dirent *in_file;

    dir = opendir("data/");
    printf("\n\n\n");
    printf("======================================\n");
    printf("              LIST ITEM               \n");
    printf("======================================\n\n");
    if (dir == NULL)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("Error! Unable to read directory");
        }
    }
    else
    {
        while ((in_file = readdir(dir)) != NULL)
        {
            if (!strcmp(in_file->d_name, "."))
            {
                continue;
            }
            if (!strcmp(in_file->d_name, ".."))
            {
                continue;
            }
            if (!strcmp(in_file->d_name, ".DS_Store"))
            {
                continue;
            }
            printf("%s\n", in_file->d_name);
        }
    }
    closedir(dir);

    int back;

    printf("\n\nEnter any number for go to Inventory Page ! \n");
    printf("\n\nEnter number : ");

    scanf("%d", &back);
    switch (back)
    {
    default:
        inventory();
        break;
    }
}

void remove_item()
{
    char file_name[1000];
    char path[6] = {'d', 'a', 't', 'a', '/', '\0'};

    printf("\n\n\n");
    printf("======================================\n");
    printf("             REMOVE ITEM              \n");
    printf("======================================\n\n");
    printf("Enter Product Name : ");
    scanf("%s", file_name);

    strcat(file_name, ".productdata");
    int i, j;

    i = 0;
    j = 0;

    while (path[i] != '\0')
    {
        i++;
    }
    while (file_name[j] != '\0')
    {
        path[i] = file_name[j];
        j++;
        i++;
    }
    path[i] = '\0';

    if (remove(path) == 0)
    {
        printf("\n");
        for (int i = 0; i < 3; i++)
        {
            printf("The file is remove successfully.\n");
        }
    }
    else
    {
        printf("\n");
        for (int i = 0; i < 3; i++)
        {
            printf("The file is not remove.\n");
        }
    }

    int back;

    printf("\n\nEnter (1) for remove other Item ! \n");
    printf("\n\nEnter (0) for go to Inventory Page ! \n");
    printf("\n\nEnter number : ");
    scanf("%d", &back);
    switch (back)
    {
    case 1:
        remove_item();
        break;

    default:
        inventory();
        break;
    }
}

void open_file()
{
    FILE *fptr;
    char file_name[1000], c;
    char path[6] = {'d', 'a', 't', 'a', '/', '\0'};

    printf("\n\n\n");
    printf("======================================\n");
    printf("               VIRW ITEM              \n");
    printf("======================================\n\n");
    printf("Enter Product Name : ");
    scanf("%s", file_name);

    strcat(file_name, ".productdata");
    int i, j, title;

    i = 0;
    j = 0;
    title = 0;

    while (path[i] != '\0')
    {
        i++;
    }
    while (file_name[j] != '\0')
    {
        path[i] = file_name[j];
        j++;
        i++;
    }
    path[i] = '\0';

    fptr = fopen(path, "r");

    if (fptr == NULL)
    {
        printf("\n");
        for (int i = 0; i < 3; i++)
        {
            printf("Cannot open file \n");
        }
    }
    else
    {
        printf("\n");
        c = fgetc(fptr);
        while (c != EOF)
        {
            if (c == '\n')
            {
                if (title == 0)
                {
                    printf(" --> Product Name");
                }
                else if (title == 1)
                {
                    printf(" --> Product Quantity");
                }
                else if (title == 2)
                {
                    printf(" --> Product Price");
                }
                else if (title == 3)
                {
                    printf(" --> Product Cost");
                }
                else if (title == 4)
                {
                    printf(" --> Profit per Item");
                }
                else if (title == 5)
                {
                    printf(" --> Minimum QTY");
                }
                else if (title == 6)
                {
                    printf(" --> Product Purchased");
                }
                else if (title == 7)
                {
                    printf(" --> Timestamp");
                }
                title++;
            }
            printf("%c", c);
            c = fgetc(fptr);
        }
    }
    int back;

    printf("\n\nEnter (1) for open other Item ! \n");
    printf("\n\nEnter (0) for go to Inventory Page ! \n");
    printf("\n\nEnter number : ");
    scanf("%d", &back);
    switch (back)
    {
    case 1:
        open_file();
        break;

    default:
        inventory();
        break;
    }
}
