#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include <stdio.h>
#include "student.h"
#include <stdlib.h>
#include <string.h>
#include "quiz.h"

struct STUDENT_H_INCLUDED {};

FILE *file;


void studentMenu();
void login();
void adminMenu();
void input(struct student *s);
void display(struct student st);
void write_student();
void display_all();
void display_sp(int n);
void modify_student();
void delete_student();
void unosString(char *staUnos,char *unos);


void adminMenu()
{




    int choice=0;
    while(choice!=8)
    {
        printf("\nWelcome to Admin Menu.");
        printf("\nChoose your option");
        printf("\n1.Create a new User");
        printf("\n2.Delete a User");
        printf("\n3.Edit a User");
        printf("\n4.Show list of Users");
        printf("\n5.Create an exam");
        printf("\n6.Exit");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            write_student();
            break;
        case 2:
            delete_student();
            break;
        case 3:
            modify_student();
            break;
        case 4:
            display_all();
            break;
        case 5:
            write_quiz();
            break;
        case 6:
            login();
            break;
        default:
            printf("Wrong input");
            adminMenu();

        }
    }

}


void input(struct student *s)
{
    printf("\nEnter the roll number of student: ");
    scanf("%d", &s->rollno);
    fflush(stdin);
    printf("\nEnter the email of student: ");
    gets(s->email);
    printf("\nEnter the pass of student: ");
    gets(s->pass);

}

void display(struct student st)
{
    printf("\nRoll Number of student : %d", st.rollno);
    printf("\nName of student : %s", st.email);
    printf("\nPassword of student : %s", st.pass);

}

void write_student()
{
    struct student data;
    file = fopen("student.dat", "ab");
    printf("\n\nPlease enter the details of student \n");
    input(&data);
    fwrite(&data, sizeof(data), 1, file);
    fclose(file);
    printf("\nStudent Record Has Been Created ");
}

void display_all()
{
    struct student data;
    printf("\n\nDISPLAY ALL RECORD !!!\n");
    file = fopen("student.dat", "rb");
    while ((fread(&data, sizeof(data), 1, file)) > 0)
    {
        display(data);
        printf("\n====================================\n");
    }
    fclose(file);
}

void display_sp(int n)
{
    struct student data;
    int flag = 0;
    file = fopen("student.dat", "rb");
    while ((fread(&data, sizeof(data), 1, file)) > 0)
    {
        if (data.rollno == n)
        {
            display(data);
            flag = 1;
        }
    }
    fclose(file);
    if (flag == 0)
        printf("\nRecord does not exist");
}


void modify_student()
{
    struct student data;
    int no, found = 0;

    printf("\nTo Modify ");
    printf("\nPlease Enter The roll number of student: ");
    scanf("%d", &no);
    file = fopen("student.dat", "rb+");
    while ((fread(&data, sizeof(data), 1, file)) > 0 && found == 0)
    {
        if (data.rollno == no)
        {
            display(data);
            printf("\nPlease enter the new details of student \n");
            input(&data);
            fseek(file,  - (long)sizeof(data), 1);
            fwrite(&data, sizeof(data), 1, file);
            printf("\n Record Updated");
            found = 1;
        }
    }
    fclose(file);
    if (found == 0)
        printf("\n Record Not Found ");
}

void delete_student()
{
    int no;
    struct student data;
    struct student array[50];
    printf("\n\nDelete Record");
    printf("\nPlease Enter The roll number you want to delete: ");
    scanf("%d", &no);
    file = fopen("student.dat", "rb+");
    int i=0;

    while ((fread(&array[i], sizeof(struct student), 1, file)))
    {
        i++;
    }

    fclose(file);
    file = fopen("student.dat", "wb+");
    int num=i;
    for(int i=0; i<num; i++)
    {
        if (array[i].rollno != no)
        {
            fwrite(&array[i], sizeof(struct student), 1, file);
        }
    }
    fclose(file);

    printf("\nRecord deleted.");
}






void login()
{

    struct student students [50];

    char email[40];
    char pass[40];
    unosString("Enter Your email : ",email);
    unosString("Enter Your password: ",pass);
    FILE *file;
    file=fopen("student.dat","rb+");
    if (file==NULL)
    {
        printf("ERROR");
        return;
    }
    int i=0;
    while(fread(&students[i],sizeof(struct student),1,file))
    {
        i++;
    };

    if(!strcmp("1",email)&&!strcmp("1",pass))
    {
        adminMenu();
        return;
    }

    for(int i=0; i<50; i++)
    {
        if(!strcmp(students[i].email,email)&&!strcmp(students[i].pass,pass))
        {


            printf("Welcome user");
            studentMenu();
            break;
        }
    }

    printf("There is no such user");



}

void unosString(char *staUnos,char *unos)
{
    printf("\n%s",staUnos);
    scanf("%s",unos);
}







void studentMenu()
{

    int choice=0;
    while(choice!=3)
    {
        printf("Welcome to Student Menu.");
        printf("\nChoose your option");
        printf("\n1.Show your own profile");
        printf("\n2.Start an exam");
        printf("\n3.Exit");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
        {
            int num;

            printf("\n\nPlease enter your ID number: ");
            scanf("%d", &num);
            display_sp(num);
        }
        break;
        case 2:
            startQuiz();
            break;
        case 3:
            login();
            break;
        default:
            printf("Wrong input");
            studentMenu();
        }

    }
}

#endif // OBJECTS_H_INCLUDED
