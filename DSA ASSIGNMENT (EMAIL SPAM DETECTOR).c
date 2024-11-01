#include <stdio.h>
#include <string.h>
#define FILE_NAME "user_pass_save.txt"
#define SPAM_FILE "spam_keyword_save.txt"


int check_spam(char user[100])
{
    // load in to a array
    char spam_keyword[1000][50];
    char file_split[1000][50];
    FILE*fobj ;
    int i = 0 ;
    int j = 0;
    fobj = fopen (SPAM_FILE , "r") ;
    if (fobj == NULL)
    {
        printf ("\nError finding file.") ;
    }


        rewind(fobj) ;


        while (fscanf(fobj , "%s\n" , spam_keyword[i]) != EOF && i < 1000)
        {
            i++ ;
        }


    fclose (fobj) ;


    //split message

    FILE* fobj1 ;
    char filename[100];
    sprintf(filename , "%s.txt", user);

    fobj1 = fopen ( filename, "r") ;
    rewind(fobj1) ;

    while (fscanf (fobj1 , "%s\n" ,file_split[j] )!= EOF  && j<1000)
    {
        j++ ;
    }

    fclose(fobj1) ;

    for (int k =0 ; k<i ; k++)
    {
        for (int l =0 ; l<j ; l++)
        {
            if (strcmp(file_split[k] , spam_keyword[l]) == 0)
            {
                return 1  ;
            }

        }
    }


}


void Spam_keyword()
{
    FILE*fobj ;
    fobj = fopen (SPAM_FILE , "a");
    char str[100]  ;
    printf ("New spam keyword : ") ;
    scanf ("%s" ,str) ;
    fprintf(fobj, "%s\n", str);
    fclose (fobj);
}




void compose_email(char user[50])
{
    int flag = check_spam(user) ;
    char spam[100] ;
    if (flag == 1)
    {
        strcpy (spam , "SPAM") ;
    }
    else
    {
        strcpy(spam , "NOT SPAM") ;
    }


    char email[50];
    char title[100];
    char main_email[1000];
    char to_store[100] ;


    printf("\nFROM : %s", user);
    printf("\nTO : ");
    scanf("%s",&email) ;

    strcpy(to_store , email) ;

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nTITLE : ");
    fgets(title, sizeof(title), stdin);
    printf("\n\n:::::::::::::::: COMPOSE :::::::::::::::\n\n");
    fgets(main_email, sizeof(main_email), stdin);

    strtok(email, "\n");
    strtok(title, "\n");

    char filename[100];
    sprintf(filename , "%s.txt", email);

    char filename2[100] ;
    sprintf (filename2 , "%s_inbox.txt" , email) ;




    FILE *fobj;
    fobj = fopen(filename, "w");
    if (fobj == NULL) {
        printf("\nEmpty Inbox.");
        return;
    }

    fprintf (fobj , "\nSTATUS :%s\n" , spam) ;
    fprintf(fobj, "FROM : %s\n", user);
    fprintf(fobj, "TO : %s\n", to_store);
    fprintf(fobj, "TITLE : %s\n", title);
    fprintf(fobj, "\n\nBODY :\n%s", main_email);

    fclose(fobj);

    printf("\n\n\nEmail sent to %s\n", to_store);




    FILE*fobj3 ;
    fobj3 = fopen (filename2 , "a");
    if (fobj3 == NULL)
    {
        printf ("\nEmpty Inbox") ;
        return  ;
    }

    fprintf (fobj3 , "\n\nSTATUS :%s\n" , spam) ;
    fprintf(fobj3, "FROM : %s\n", user);
    fprintf(fobj3, "TO : %s\n", to_store);
    fprintf(fobj3, "TITLE : %s\n", title);
    fprintf(fobj3, "\n\nBODY :\n%s", main_email);
    fprintf (fobj3 , "\n\n***********************************************\n") ;

    fclose (fobj3) ;


}


void new_email(char user[])
{
    FILE *fobj ;
    char ch ;
    char fname[100] ;
    sprintf (fname, "%s.txt" , user) ;
    fobj = fopen (fname , "r") ;
    rewind(fobj) ;
    printf ("\n\n\n") ;
    printf ("*************************************************************\n\n") ;
    rewind(fobj) ;
   while ( 1 )
   {
     ch = fgetc ( fobj ) ;
     if ( ch == EOF )
         break ;
     printf ( "%c", ch ) ;
   }

        printf ("\n\n");
        printf ("\n*************************************************************") ;

        printf ("\n\n\n") ;
        fclose(fobj) ;

}




void inbox(char user[])
{
    char filename2[100] ;
    sprintf (filename2 , "%s_inbox.txt" , user) ;
    FILE*fobj3 ;
    fobj3 = fopen (filename2 , "r");
    printf ("\n\n***********************************************\n") ;
    if (fobj3 == NULL)
    {
        printf ("\nEmpty Inbox") ;
    }
    printf ("\n\n\n") ;
    rewind(fobj3) ;


    while (1)
    {

        char ch = fgetc(fobj3);
        if (ch == EOF)
        {
            break ;
        }
        else
        {
            printf ("%c" , ch);
        }
    }

    fclose (fobj3) ;

    printf ("\n\n\n\n") ;


}




void menu_choice(char user[50])
{

    while (1)
    {
        printf ("\n\n\n") ;
        printf ("\n1.COMPOSE EMAIL\n2.NEW EMAIL\n3.INBOX\n4.EXIT\nChoice : ") ;
        int choice ;
        scanf ("%d" ,&choice) ;

        switch(choice)
        {
        case 1:
            compose_email(user) ;
            break ;

        case 2:
            new_email(user) ;
            break ;

        case 3:
            inbox(user) ;
            break ;

        case 4 :
            return 0 ;

        default :
            printf ("Enter Valid Option") ;
        }
        }
}





int num_user() {
    FILE *file;
    file = fopen(FILE_NAME, "r");
    rewind(file);
    int no = 0;
    char line[300];
    while (fgets(line , sizeof(line) , file)!= NULL)
    {
        char *comma = strchr(line , ',') ;
        if (comma != NULL)
        {
            no++;
        }
    }


    fclose(file);
    return no;
}



void load_user_pass(char split[][2][50], int num_users) {
    FILE*fobj1 ;
    fobj1 = fopen(FILE_NAME , "a") ;
    fclose(fobj1);
    FILE *file;
    file = fopen(FILE_NAME, "r");
    rewind(file) ;
    if (file == NULL) {
        printf("File does not exist.\n");
        return;
    }
    rewind(file) ;
     char line[300];
    for (int i = 0; i < num_users; i++) {
        if (fgets(line, sizeof(line), file) != NULL) {
            char *token = strtok(line, ",");
            if (token != NULL) {
                strcpy(split[i][0], token);
            }
            token = strtok(NULL, "\n");
            if (token != NULL) {
                strcpy(split[i][1], token);
            }
        }
    }

    fclose(file);
}


int login(char split[][2][50], int no , char user[50] , char password[50])

 {

    for (int i = 0; i < no; i++)

    {
        if (strcmp(split[i][0], user) == 0 && strcmp(split[i][1], password) == 0)

        {
            printf ("\n--------------------");
            printf("\nLogin Successful\n");
            printf ("\n--------------------");

            return 1;
        }
    }
    printf("\nInvalid UserId Password\n");
    return 0;
}




void signup(char split[][2][50], int *num_users)
{
    FILE *file;
    file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("File does not exist.\n");
        return;
    }
    char first_name[50];
    char last_name[50];
    char pass[50];
    printf("FIRST NAME : ");
    scanf("%s", first_name);
    printf("LAST NAME : ");
    scanf("%s", last_name);
    strcat(first_name, last_name);
    strcat(first_name, "@gmail.com");


    for (int i = 0; i < *num_users; i++) {
        if (strcmp(first_name, split[i][0]) == 0)

        {
            printf("\nThis Email already exists\n");
            fclose(file);
            return;
        }
    }

    printf("\nPASSWORD : ");
    scanf("%s", pass);

    printf("\nEMAIL ID : %s\n", first_name);

    fprintf(file, "%s,%s\n", first_name, pass);
    fclose(file);

    strcpy(split[*num_users][0], first_name);
    strcpy(split[*num_users][1], pass);
    (*num_users)++;

}






void forgot_pass(char split[300][2][50] , int no)
{
    int flag = 0;
    char email[50] ;
    printf ("\nEMAIL : ");
    scanf("%s" ,email) ;
     for (int i = 0; i < no; i++) {
        if (strcmp(split[i][0],email) == 0)
        {
            printf("\nPASSWORD : %s" ,split[i][1]);
            flag = 0 ;
        }

    }


}


int main()
{
    char split[300][2][50];
    int no = num_user();
    load_user_pass(split, no);

    while (1)

        {
        printf ("\n\n\n");
        printf("\n1.SIGN UP\n2.LOGIN\n3.FORGOT PASSWORD\n4.SPAM KEYWORD ADD\n5.EXIT\nChoice : ");
        int choice_main;
        scanf("%d", &choice_main);
        switch (choice_main) {
            case 1:
                signup(split, &no);
                break;
            case 2:
                {


                char user_name[50];
                char pass[50];
                printf("\nEMAIL ID : ");
                scanf("%s", user_name);
                printf("\nPASSWORD : ");
                scanf("%s", pass);
                if (login(split, no , user_name , pass))
                    menu_choice(user_name);
                else
                    printf("Enter Valid Email Id and Password\n");
                break;
                }
            case 3:
                forgot_pass(split , no);
                break;

            case 4:
                Spam_keyword();
                break ;

            case 5:
                return 0 ;
            default:
                printf("Enter valid option\n");
        }
    }
}
