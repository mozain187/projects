#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void book_list();
void log();
void reg();
void welcom();
void admin();

typedef struct us {
    char username[100];
    char password[100];
    int ok;
} user;

typedef struct book_library {
    char id[20];
    char title[100];
    char author[100];
    char describe[100];
    int copys;
} livro;

char admin_name[] = "CrabBoy";
int admin_password = 1111;

int main() {
    welcom();
    return 0;
}

void welcom() {
    int chosed;
    printf("\t\t****************************************\n");
    printf("\t\t\tWelcome to the CrabBoyz library\n\t\t\tWhat can I do for you?\n");
    printf("Choose (1) for login\nChoose (2) for sign up\n");
    scanf("%d", &chosed);

    if (chosed == 1) {
        log();
    } else {
        reg();
    }
}

void log() {
    char in[100];
    char pass[100];
    do {
        printf("\t\t\tEnter the username:\n");
        scanf("%s", in);
        printf("\t\t\tEnter the password:\n");
        scanf("%s", pass);

        if (strcmp(admin_name, in) == 0 && strcmp(pass, "1111") == 0) {
            printf("\t\t\tWelcome boss\n");
            admin();
            return;
        }

        FILE *file = fopen("login.txt", "r");
        if (!file) {
            printf("Please register first.\n");
            reg();
            return;
        }

        user en;
        int found = 0;
        while (fread(&en, sizeof(user), 1, file)) {
            if (strcmp(en.username, in) == 0 && strcmp(en.password, pass) == 0) {
                printf("\t\t\tWelcome, %s!\n", in);
                found = 1;
                     book_list(in);
                break;
            }
        }
        fclose(file);

        if (!found) {
            printf("Invalid username or password. Please try again.\nor sign up if you dont have an acount \n for making new acount chose (1):\n");
            int n=0;
            scanf("%d",&n);
            if(n==1){
                reg();
                return;
            }
            


        } else {
            return;
        }
    } while (1);
}

void admin() {
    int in;
    printf("\t\t\tAre we adding new books or doing some boss thigs ?\n");
    printf("Adding new books (1)\n boss sh*t  (2)\n");
    scanf("%d", &in);

    if (in == 1) {
        int stop=0;
       do{
           FILE *new = fopen("book2.txt", "a");
        if (!new) {
            printf("Error opening file\n");
            return;
        }
        livro newbook;
        printf("Enter book title: ");
        getchar();
        fgets(newbook.title, 100, stdin);
        newbook.title[strcspn(newbook.title, "\n")] = 0;

        printf("Enter book author: ");
        fgets(newbook.author, 100, stdin);
        newbook.author[strcspn(newbook.author, "\n")] = 0;

        printf("Enter book ISBN: ");
        fgets(newbook.id, 20, stdin);
        newbook.id[strcspn(newbook.id, "\n")] = 0;

        printf("Enter books describiton: ");
        fgets(newbook.describe,100,stdin);
        newbook.describe[strcspn(newbook.describe,"\n")] = 0;

        printf("Enter number of copies: ");
        scanf("%d", &newbook.copys);

        int l = strlen(newbook.title);

        for(int i=0;i<l;i++){
            newbook.title[i]= tolower(newbook.title[i]);
        }

        fwrite(&newbook, sizeof(livro), 1, new);
        fclose(new);

        printf("Book '%s' by '%s' added successfully!\n", newbook.title, newbook.author);
        printf("\n\nDo you wanna add more book or are we done?\nchose (1) if we are done \n if you entered any thing else i will just continue :)\n");
        scanf("%d",&stop);
        
       }while(stop == 0);
    }
    
      else {
        FILE *file = fopen("book2.txt", "r");
        if (!file) {
            printf("No books available.\n");
            return;
        }

        livro book;
        printf("\nList of Books:\n");
        printf("----------------------------\n");
        while (fread(&book, sizeof(livro), 1, file)) {
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            printf("ISBN: %s\n", book.id);
            printf("Copies: %d\n", book.copys);
            printf("----------------------------\n");
        }
        fclose(file);

        FILE *activ = fopen("activites.txt","r");
        if(!activ){
            printf("I could't open the activites file boss ,please dont fire me :( \n");

        }

        char line[100];

        printf("\nList of users activites \n");
        printf("----------------------------\n");
        while (fgets(line,sizeof(line),activ))
        {
            printf(" %s\n",line);

        }
        fclose(activ);
        


    }
}

void reg() {
    user new;
    printf("\t\t\tEnter the username:\n");
    scanf("%s", new.username);
    printf("\t\t\tEnter the password:\n");
    scanf("%s", new.password);

    FILE *file = fopen("login.txt", "a");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    fwrite(&new, sizeof(user), 1, file);
    fclose(file);

    printf("Welcome to our humble library! %s \nHere is what we have for now:\n",new.username);
       book_list(new.username);
    

    
    }


    void book_list(char user[]){
         FILE *bookFile = fopen("book2.txt", "r");
    if (!bookFile) {
        printf("No books available.\n");
        return;
    }
    

    livro book;
    printf("\nList of Books:\n");
    printf("----------------------------\n");
    while (fread(&book, sizeof(livro), 1, bookFile)) {
        printf("Title: %s\n", book.title);
        printf("Author: %s\n", book.author);
        printf("ISBN: %s\n", book.id);
        printf("Copies: %d\n", book.copys);
        printf("----------------------------\n");
    }
    fclose(bookFile);

    printf("Do you want any of them ?\nYes (1)\n No (2)\n");
    int ans;
    scanf("%d",&ans);

    if (ans == 1){
        FILE *file = fopen("book2.txt","r");
        FILE *temp = fopen("temp.txt","w");

        if(!file || !temp){
            printf("something went wrong ,but you can check us another time tho\nbye\n");
            if (file)fclose(file);
            if (temp)fclose(temp);
            return;
        }
        char title[100];

         printf("Write the title of the book you want: \n");
    getchar(); 
    fgets(title, sizeof(title), stdin);
    title[strcspn(title,"\n")] = 0;
    int l=strlen(title);
    for(int i=0;i<l;i++){
      title[i]= tolower(title[i]);
    }

    livro book;
    int found = 0;

    while (fread(&book, sizeof(livro), 1, file)) {
        if (strcmp(book.title, title) == 0) {
            found = 1;
            if (book.copys > 0) {
                book.copys--;
                printf("So %s , alrghit i got you \nBook '%s' borrowed successfully.\ndont foregt to bring it back when you are done reading it\nenjoy \n^-^\n",book.describe, book.title);

                FILE *userfile = fopen("username.txt", "a");
                FILE *activ = fopen("activites.txt","a");
                if (userfile) {
                    fprintf(userfile, "Borrowed Book: %s by %s\n", book.title, book.author);
                    fprintf(activ, "user: '%s' Borrowed Book: %s by %s\n",user, book.title, book.author);
                    fclose(userfile);
                    fclose(activ);
                }
            } else {
                printf("No copies available for '%s'.\n", book.title);
            }
        }
        fwrite(&book, sizeof(livro), 1, temp);
        
        
        
    }

    if (!found) {
        printf("Book not found.\n");
    }

    fclose(file);
    fclose(temp);

    remove("book2.txt");
    rename("temp.txt", "book2.txt");
}
else{
    printf("we are waiting for you any time \n\t\tbye ^-^");
    return 0;
}
    }

