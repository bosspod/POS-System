void pos()
{
    int pos_menu_selected;

    int repeat, yes, no;

    repeat = 1, yes = 1, no = 0;

    do
    {
        printf("\n\n\n");
        printf("======================================\n");
        printf("         WELCOME TO BRK STORE         \n");
        printf("              POS System              \n");
        printf("======================================\n\n\n");
        printf("**************************************\n");
        printf("1 --> Buy System\n");
        printf("2 --> Product List\n");
        printf("3 --> Print Receipt\n");
        printf("4 --> Receipt List\n");
        printf("9 --> Main Menu\n");
        printf("0 --> Exit Program\n");
        printf("**************************************\n\n\n");

        printf("Enter Choice : ");
        scanf("%d", &pos_menu_selected);

        switch (pos_menu_selected)
        {
        case 1:
            buying();
            repeat = no;
            break;
        case 2:
            product_list();
            repeat = no;
            break;
        case 3:
            receipt_print();
            repeat = no;
            break;
        case 4:
            receipt_list();
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

void buying()
{
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20];
    char timefile[25];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, 20, "%d/%m/%G %H:%M:%S", timeinfo);
    strftime(timefile, 25, "-%d-%m-%G-%H-%M-%S.log", timeinfo);

    FILE *file, *temp, *log;

    char filename[1000];
    char tempfile[1000];
    char product_name[1000];
    char logfile[1000];
    char path_real[6] = {'d', 'a', 't', 'a', '/', '\0'};
    char path_log[5] = {'l', 'o', 'g', '/', '\0'};
    char path_temp[11] = {'d', 'a', 't', 'a', '/', 't', 'e', 'm', 'p', '_', '\0'};
    char buffer[1000];
    char buffer_old[1000];
    char buffer_old_purchased[1000];
    int replace;
    int last_value;
    int last_value_purchased;
    int replace_line;
    int replace_purchased;
    int add_purchased;
    int quantity;
    printf("\n\n\n");
    printf("======================================\n");
    printf("             BUYING SYSTEM            \n");
    printf("======================================\n\n");
    printf("Product name : ");
    scanf("%s", filename);
    strcpy(product_name, filename);
    strcpy(tempfile, product_name);
    strcpy(logfile, product_name);

    strcat(filename, ".productdata");
    strcat(tempfile, ".tmp");

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

    i = 0;
    j = 0;

    while (path_log[i] != '\0')
    {
        i++;
    }
    while (logfile[j] != '\0')
    {
        path_log[i] = logfile[j];
        j++;
        i++;
    }
    path_log[i] = '\0';

    i = 0;
    j = 0;
    while (path_log[i] != '\0')
    {
        i++;
    }
    while (timefile[j] != '\0')
    {
        path_log[i] = timefile[j];
        j++;
        i++;
    }
    path_log[i] = '\0';

    char r_log[1000];
    strcpy(r_log, path_log);

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

    replace_line = 2;
    add_purchased = 7;

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

            file = fopen(r_file, "r");

            keep_reading = true;
            current_line = 1;

            do
            {
                fgets(buffer_old_purchased, 2048, file);
                if (feof(file))
                {
                    keep_reading = false;
                }
                else if (current_line == add_purchased)
                {
                    last_value_purchased = atoi(buffer_old_purchased);
                }
                current_line++;
            } while (keep_reading);
            fclose(file);

            replace = last_value - quantity;
            replace_purchased = last_value_purchased + quantity;

            if (last_value != 0)
            {
                if (replace >= 0)
                {
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
                            log = fopen(r_log, "w");
                            fprintf(log, "%s\n%d\n%s\n", product_name, quantity, timestamp);
                            fclose(log);
                            printf("\n");
                            for (int i = 0; i < 3; i++)
                            {
                                printf("Buy Successful!!\n");
                            }
                        }
                        else if (current_line == add_purchased)
                        {
                            fprintf(temp, "%d\n", replace_purchased);
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
                else
                {
                    printf("\n");
                    for (int i = 0; i < 3; i++)
                    {
                        printf("Your order requires more than stock. (Available %d Items)\n", last_value);
                    }
                }
            }
            else
            {
                printf("\n");
                for (int i = 0; i < 3; i++)
                {
                    printf("Out of stock!!\n");
                }
            }
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

    printf("\n\nEnter (1) for buy other Item ! \n");
    printf("\n\nEnter (0) for go to POS Page ! \n");
    printf("\n\nEnter number : ");
    scanf("%d", &back);
    switch (back)
    {
    case 1:
        buying();
        break;

    default:
        pos();
        break;
    }
}

void product_list()
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

    closedir(dir);

    int back;

    printf("\n\nEnter any number for go to POS Page ! \n");
    printf("\n\nEnter number : ");

    scanf("%d", &back);
    switch (back)
    {
    default:
        pos();
        break;
    }
}

void receipt_list()
{
    DIR *dir;
    FILE *entry_file;
    struct dirent *in_file;

    dir = opendir("log/");
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

    closedir(dir);

    int back;

    printf("\n\nEnter any number for go to POS Page ! \n");
    printf("\n\nEnter number : ");

    scanf("%d", &back);
    switch (back)
    {
    default:
        pos();
        break;
    }
}

void receipt_print()
{
    FILE *fptr;
    char file_name[1000], c;
    char path[5] = {'l', 'o', 'g', '/', '\0'};

    printf("\n\n\n");
    printf("======================================\n");
    printf("              VIRW RECEIPT            \n");
    printf("======================================\n\n");
    printf("Enter Receipt Name : ");
    scanf("%s", file_name);

    strcat(file_name, ".log");
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
                    printf(" --> Timestamp");
                }
                title++;
            }
            printf("%c", c);
            c = fgetc(fptr);
        }
    }
    int back;

    printf("\n\nEnter (1) for open other Receipt ! \n");
    printf("\n\nEnter (0) for go to POS Page ! \n");
    printf("\n\nEnter number : ");
    scanf("%d", &back);
    switch (back)
    {
    case 1:
        receipt_print();
        break;

    default:
        pos();
        break;
    }
}
