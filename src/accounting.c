void accounting()
{

    int accounting_menu_selected;

    int repeat, yes, no;

    repeat = 1, yes = 1, no = 0;

    do
    {
        printf("\n\n\n");
        printf("======================================\n");
        printf("         WELCOME TO BRK STORE         \n");
        printf("          Accounting System           \n");
        printf("======================================\n\n\n");
        printf("**************************************\n");
        printf("1 --> Profit of product\n");
        printf("2 --> All Profit\n");
        printf("3 --> Product Sell Log\n");
        printf("4 --> Minimum Alert\n");
        printf("9 --> Main Menu\n");
        printf("0 --> Exit Program\n");
        printf("**************************************\n\n\n");

        printf("Enter Choice : ");
        scanf("%d", &accounting_menu_selected);

        switch (accounting_menu_selected)
        {
        case 1:
            profit();
            repeat = no;
            break;
        case 2:
            profit_all();
            repeat = no;
            break;
        case 3:
            sell_log();
            repeat = no;
            break;
        case 4:
            minimum_alert();
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

void profit()
{
    FILE *file, *temp;

    char filename[1000];
    char product_name[1000];
    char path_real[6] = {'d', 'a', 't', 'a', '/', '\0'};
    char buffer[1000];
    int purchased_value;
    double profit_value;
    int purchased_line;
    int profit_line;
    double product_profit;

    purchased_line = 7;
    profit_line = 5;

    printf("\n\n\n");
    printf("======================================\n");
    printf("              SHOW PROFIT             \n");
    printf("======================================\n\n");
    printf("Product name : ");
    scanf("%s", filename);
    strcpy(product_name, filename);
    strcat(filename, ".productdata");

    int i, j;

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
            fgets(buffer, 2048, file);
            if (feof(file))
            {
                keep_reading = false;
            }
            else if (current_line == purchased_line)
            {
                purchased_value = atoi(buffer);
            }
            else if (current_line == profit_line)
            {
                profit_value = atoi(buffer);
            }
            current_line++;
        } while (keep_reading);
        fclose(file);

        product_profit = purchased_value * profit_value;

        printf("\n");
        for (int i = 0; i < 3; i++)
        {
            printf("The profit of %s is %.2f THB\n", product_name, product_profit);
        }
    }

    int back;

    printf("\n\nEnter (1) for view more Profit Item ! \n");
    printf("\n\nEnter (0) for go to Accounting Page ! \n");
    printf("\n\nEnter number : ");
    scanf("%d", &back);
    switch (back)
    {
    case 1:
        profit();
        break;

    default:
        accounting();
        break;
    }
}

struct pro
{
    char filename[1000];
    double total;
} pro[1000];

void profit_all()
{
    DIR *dir;
    FILE *entry_file;
    struct dirent *in_file;
    int no;

    no = 0;
    printf("\n\n\n");
    printf("======================================\n");
    printf("               ALL PROFIT             \n");
    printf("======================================\n\n");
    dir = opendir("data/");
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
            strcpy(pro[no].filename, in_file->d_name);
            no++;
        }
        closedir(dir);
        for (int loop_data = 0; loop_data < no; loop_data++)
        {
            FILE *file, *temp;

            char product_name[1000];
            char path_real[6] = {'d', 'a', 't', 'a', '/', '\0'};
            char buffer[1000];
            int purchased_value;
            double profit_value;
            int purchased_line;
            int profit_line;
            double product_profit;

            purchased_line = 7;
            profit_line = 5;

            strcpy(product_name, pro[loop_data].filename);

            int i, j;

            i = 0;
            j = 0;

            while (path_real[i] != '\0')
            {
                i++;
            }
            while (pro[loop_data].filename[j] != '\0')
            {
                path_real[i] = pro[loop_data].filename[j];
                j++;
                i++;
            }
            path_real[i] = '\0';
            char r_file[1000];
            strcpy(r_file, path_real);

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
                    fgets(buffer, 2048, file);
                    if (feof(file))
                    {
                        keep_reading = false;
                    }
                    else if (current_line == purchased_line)
                    {
                        purchased_value = atoi(buffer);
                    }
                    else if (current_line == profit_line)
                    {
                        profit_value = atoi(buffer);
                    }
                    current_line++;
                } while (keep_reading);

                product_profit = purchased_value * profit_value;

                pro[loop_data].total = product_profit;

                printf("The profit of %s is %.2f THB\n", product_name, product_profit);
                fclose(file);
            }
        }
        double all_total;

        all_total = 0;

        for (int i = 0; i < no; i++)
        {
            all_total = all_total + pro[i].total;
        }
        printf("\nTotal Profit is %.2f THB", all_total);
    }
    int back;

    printf("\n\nEnter any number for go to Accounting Page ! \n");
    printf("\n\nEnter number : ");

    scanf("%d", &back);
    switch (back)
    {
    default:
        accounting();
        break;
    }
}

struct sell
{
    char filename[1000];
} sell[1000];

void sell_log()
{
    DIR *dir;
    FILE *entry_file;
    struct dirent *in_file;
    int no;

    no = 0;
    printf("\n\n\n");
    printf("======================================\n");
    printf("                SELL LOG              \n");
    printf("======================================\n\n");
    dir = opendir("log/");
    if (dir == NULL)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("Error! Unable to read directory");
        }
    }

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
        strcpy(sell[no].filename, in_file->d_name);
        no++;
    }
    closedir(dir);
    for (int loop_data = 0; loop_data < no; loop_data++)
    {
        FILE *file, *temp;

        char path_real[100] = {'l', 'o', 'g', '/', '\0'};
        char buffer[1000];
        char name_value[1000];
        int quantity_value;
        char date_value[1000];
        int name_line;
        int quantity_line;
        int date_line;

        name_line = 1;
        quantity_line = 2;
        date_line = 3;

        int i, j;

        i = 0;
        j = 0;

        while (path_real[i] != '\0')
        {
            i++;
        }
        while (sell[loop_data].filename[j] != '\0')
        {
            path_real[i] = sell[loop_data].filename[j];
            j++;
            i++;
        }
        path_real[i] = '\0';
        char r_file[1000];
        strcpy(r_file, path_real);

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
                fgets(buffer, 2048, file);
                if (feof(file))
                {
                    keep_reading = false;
                }
                else if (current_line == name_line)
                {
                    strcpy(name_value, buffer);
                }
                else if (current_line == quantity_line)
                {
                    quantity_value = atoi(buffer);
                }
                else if (current_line == date_line)
                {
                    strcpy(date_value, buffer);
                }
                current_line++;
            } while (keep_reading);

            printf("Product %sOrdered %d units \nOn %s\n", name_value, quantity_value, date_value);

            fclose(file);
        }
    }

    int back;

    printf("\n\nEnter any number for go to Accounting Page ! \n");
    printf("\n\nEnter number : ");

    scanf("%d", &back);
    switch (back)
    {
    default:
        accounting();
        break;
    }
}

struct min
{
    char filename[1000];
} min[1000];

void minimum_alert()
{
    DIR *dir;
    FILE *entry_file;
    struct dirent *in_file;
    int no;

    no = 0;
    printf("\n\n\n");
    printf("======================================\n");
    printf("             MINIMUM ALERT            \n");
    printf("======================================\n\n");
    dir = opendir("data/");
    if (dir == NULL)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("Error! Unable to read directory");
        }
    }

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
        strcpy(min[no].filename, in_file->d_name);
        no++;
    }
    closedir(dir);
    for (int loop_data = 0; loop_data < no; loop_data++)
    {
        FILE *file, *temp;

        char product_name[1000];
        char path_real[6] = {'d', 'a', 't', 'a', '/', '\0'};
        char buffer[1000];
        int stock_value;
        int min_value;
        int stock_line;
        int min_line;

        stock_line = 2;
        min_line = 6;
        strcpy(product_name, min[loop_data].filename);

        int i, j;

        i = 0;
        j = 0;

        while (path_real[i] != '\0')
        {
            i++;
        }
        while (min[loop_data].filename[j] != '\0')
        {
            path_real[i] = min[loop_data].filename[j];
            j++;
            i++;
        }
        path_real[i] = '\0';
        char r_file[1000];
        strcpy(r_file, path_real);

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
                fgets(buffer, 2048, file);
                if (feof(file))
                {
                    keep_reading = false;
                }
                else if (current_line == stock_line)
                {
                    stock_value = atoi(buffer);
                }
                else if (current_line == min_line)
                {
                    min_value = atoi(buffer);
                }
                current_line++;
            } while (keep_reading);

            if (stock_value < min_value)
            {
                printf("The stock of %s is lower tham Minimum !!!\n", product_name);
            }
            fclose(file);
        }
    }
    int back;

    printf("\n\nEnter any number for go to Accounting Page ! \n");
    printf("\n\nEnter number : ");

    scanf("%d", &back);
    switch (back)
    {
    default:
        accounting();
        break;
    }
}
