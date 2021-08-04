/************************************
 Project:  Library Management System
 Author:   Tabitha Ndua
 Date:     July, 2021
 Compiler: C99
 License:  LOL
************************************/

#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<string.h>
#include<conio.h>

//Adding user:
//Name
//id
//Contact
//is_staff

//Data structures

struct user {
    char name[100];
    int id;
    char tel[13];
    int is_staff;
};

struct book {
    char title[100];
    char author[100];
    int copies;
    int id;

};

// Function prototype

void execute_action(int action);
void close();
int menu();
void add_user();
void view_users();
void delete_user();
void add_book();
void view_books();
void delete_books();


int main()
{

    int action;
    while(1){
        action=menu();
        execute_action(action);
        printf("\nPress any key to continue");
        getchar();
        getch ();
        system("cls");
    }
    return 0;
}
//Actions
void execute_action(int action){
switch(action) {
case 1:
    add_user();
break;

case 2:
    view_users();
break;
case 3:
    delete_user();
    break;

case 4:
    add_book();
    break;

case 5:
    view_books();
    break;

case 6:
    delete_books();
    break;

case 7:
    close();
    printf("*****Good Bye*****");
    break;

default:
    printf("Unknown function.\n");
}


}
//Exit notice
void close() {
printf("***Thank you for using the system***\n");
printf("--GoodBye----");
Sleep(2000);
exit(0);
}

int menu (){

 //welcome notice
 int action;
    do {
   //navigation menu
    printf("welcome Tabitha Ndua\n");
    printf("1. Add user\n");
    printf("2.view all users\n");
    printf("3.Delete user\n");
    printf("4. Add book\n");
    printf("5.View all books\n");
    printf("6.Delete book\n");
    printf("7. Exit\n");
    printf("Select action(1-7): ");
    scanf("%d",&action);

    //Validate input
    if (action < 1 || action > 7){
        printf("Invalid action.Try again\n");
        Sleep(2000);
        system( "cls");
    }

    }while(action < 1 || action > 7);

	 return action;

}
//Add user
void add_user(){
struct user u;
FILE *fp;

if ((fp=fopen("users","ab"))==NULL){
    printf("cannot open file.\n");
    exit(1);
}
printf("Name: ");
getchar();
gets(u.name);
printf("Id number: ");
scanf("%d",&u.id);
printf("Phone Number: ");
scanf("%s",u.tel);
printf("User type (1 for staff,0 for ordinary user:");
scanf("%d",&u.is_staff);

fwrite(&u, sizeof(struct user),1,fp);
fclose(fp);
printf("user successfully added\n");

}
//view user
void view_users() {
    struct user u;
    FILE *fp;

    fp = fopen("users","rb");
    if (!fp) {
        printf("Unable to open file");
        exit(0);
    }
    printf("id\t\tName\t\tPhone Number\t\tIs Staff\n");
    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        printf("%8d %20s %13s %1d\n",u.id,u.name,u.tel,u.is_staff);
    }
    fclose(fp);
}
//Add book
void add_book(){
    struct book c;
    FILE *fp;
    if ((fp=fopen("books","ab"))==NULL){
    printf("cannot open file.\n");
    exit(1);
}
printf("Title: ");
getchar();
gets(c.title);
printf("Author: ");
scanf("%s",c.author);
printf("Book ID NO  = ");
scanf("%u",&c.id);
printf("Copies: ");
scanf("%d",&c.copies);


fwrite(&c, sizeof(struct book),1,fp);
fclose(fp);
printf("Book successfully added\n");

}
//view books
void view_books(){
 struct book c;
    FILE *fp;

    fp = fopen("books","rb");
    if (!fp) {
        printf("Unable to open file");
        exit(0);
    }
    printf("Title\t\tAuthor\t\t\t\tcopies\tid number");
    while(!feof(fp)) {
        fread(&c, sizeof(struct book), 1, fp);
        printf("%8s %20s %13d %24u\n",c.title,c.author,c.copies,c.id);
    }
    fclose(fp);

}

//Delete book
void delete_books() //displaying only deleting books function
  {
     struct book c;
    FILE *fp;
    system("cls");
    int d;
    char findbook;
    char another = 'y';
    while (another == 'y') //infinite loop
    {
      system("cls");

      printf("Enter the Book ID to  delete:");
      scanf("%d", & d);
       fp = fopen("books","rb");
      rewind(fp);
      while (fread( & c, sizeof(struct book), 1, fp) == 1) {
        if (c.id == d) {
          printf("The book record is available\n\n\n\n");

          printf("Book title is %s\n\n", c.title);

          printf("Author name is %s\n\n", c.author);
          findbook = 't';
        }
      }
      if (findbook != 't') {

        printf("No record is found modify the search\n\n");
        if (getch())
          menu();
      }
      if (findbook == 't') {

        printf("Do you want to delete it?(Y/N):\n");
        if (getch() == 'y') {
          fp = fopen("test.dat", "wb+"); //temporary file for delete
          rewind(fp);
          while (fread( & c, sizeof(struct book), 1, fp) == 1) {
            if (c.id!= d) {
              fseek(fp, 0, SEEK_CUR);
              fwrite( & c, sizeof(struct book), 1, fp); //write all in tempory file except that
            } //we want to delete
          }
          fclose(fp);
          fclose(fp);
          remove("library.dat");
          rename("test.dat", "library.dat"); //copy all item from temporary file to fp except that
          fp = fopen("library.dat", "rb+"); //we want to delete
          if (findbook == 't') {

            printf("The record is sucessfully deleted\n");

            printf("\nDelete another record?(Y/N)");
          }
        } else
          menu();
        fflush(stdin);
        another = getch();
      }
    }

    menu();
  }

  //Delete user
  void delete_user(){
   struct user u;
    FILE *fp;
    system("cls");
    int d;
    char finduser;
    char another = 'y';
    while (another == 'y') //infinite loop
    {
      system("cls");

      printf("Enter user id  delete:");
      scanf("%d", & d);
       fp = fopen("users","rb");
      rewind(fp);
      while (fread( & u, sizeof(struct user), 1, fp) == 1) {
        if (u.id == d) {
          printf("The user record is available\n\n\n\n");

          printf("user name is %s\n\n", u.name);

          printf("User tel is %s\n\n", u.tel);
          finduser = 't';
        }
      }
      if (finduser != 't') {

        printf("No record is found modify the search\n\n");
        if (getch())
          menu();
      }
      if (finduser == 't') {

        printf("Do you want to delete it?(Y/N):\n");
        if (getch() == 'y') {
          fp = fopen("test.dat", "wb+"); //temporary file for delete
          rewind(fp);
          while (fread( & u, sizeof(struct user), 1, fp) == 1) {
            if (u.id!= d) {
              fseek(fp, 0, SEEK_CUR);
              fwrite( & u, sizeof(struct user), 1, fp); //write all in tempory file except that
            } //we want to delete
          }
          fclose(fp);
          fclose(fp);
          remove("library.dat");
          rename("test.dat", "library.dat"); //copy all item from temporary file to fp except that
          fp = fopen("library.dat", "rb+"); //we want to delete
          if (finduser == 't') {

            printf("The record is sucessfully deleted\n");

            printf("\nDelete another record?(Y/N)");
          }
        } else
          menu();
        fflush(stdin);
        another = getch();
      }
    }

    menu();

  }







