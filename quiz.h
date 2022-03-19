#ifndef QUIZ_H_INCLUDED
#define QUIZ_H_INCLUDED

#include "objects.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void inputQuiz();
void write_quiz();
void startQuiz();
void display_allQuiz();
void displayQuiz();

struct subject
{
    char name[30];
    char que1[30];
    char que2[30];
    char que3[30];
    char ans1[30];
    char ans2[30];
    char ans3[30];
};


void inputQuiz(struct subject *s)
{
    printf("\nEnter the name of a class: ");
    scanf("%s",&s->name);
    fflush(stdin);
    printf("\nEnter the question : ");
    gets(s->que1);
    printf("\nEnter the answer: ");
    gets(s->ans1);
    printf("\nEnter the question : ");
    gets(s->que2);
    printf("\nEnter the answer: ");
    gets(s->ans2);
    printf("\nEnter the question : ");
    gets(s->que3);
    printf("\nEnter the answer: ");
    gets(s->ans3);

}


void write_quiz()
{

    FILE * file;
    struct subject data;
    file = fopen("quiz.dat", "ab");
    printf("\n\nPlease enter the details of quiz \n");
    inputQuiz(&data);
    fwrite(&data, sizeof(data), 1, file);
    fclose(file);
    printf("\nStudent Quiz Has Been Created ");
}


void startQuiz()
{

    struct subject subjects[30];
    char name [30];

    unosString("Enter subject name : ",name);



    char odg [30];
    char odg2 [30];
    char odg3 [30];
    int  points;

    FILE *file;
    file=fopen("quiz.dat","rb+");
    if (file==NULL)
    {
        printf("\nERROR");
        return;

    }





    int i=0;
    while(fread(&subjects[i],sizeof(struct subject),1,file))
    {
        i++;
    };

    fclose(file);



    for(int i = 0; i<30; i++)
    {

        if(!strcmp(subjects[i].name,name))
        {


            printf("\n %s : ",subjects[i].que1);
            scanf("\n%s",odg);
            if(!strcmp(odg,subjects[i].ans1))
            {

                printf("\nCORRECT ANSWER");
            }
            else printf("\nWRONG ANSWER");

            printf("\n%s : ",subjects[i].que2);
            scanf("\n%s",odg);
            if(!strcmp(odg,subjects[i].ans2))
            {

                printf("\nCORRECT ANSWER");
            }
            else printf("\nWRONG ANSWER");

            printf("\n%s : ",subjects[i].que3);
            scanf("\n%s",odg);
            if(!strcmp(odg,subjects[i].ans3))
            {

                printf("\nCORRECT ANSWER");
            }
            else printf("\nWRONG ANSWER");




        }

    }

    printf("\nAll done\n");

}

void display_allQuiz()
{

    FILE *file;
    struct subject data;
    file = fopen("quiz.dat", "rb");
    while ((fread(&data, sizeof(data), 1, file)) > 0)
    {
        displayQuiz(data);
        printf("\n====================================\n");
    }
    fclose(file);
}

void displayQuiz(struct subject st)
{
    printf("\n subject : %s", st.name);
    printf("\n que : %s", st.que1);
    printf("\n answer : %s", st.ans1);

}





#endif // QUIZ_H_INCLUDED
