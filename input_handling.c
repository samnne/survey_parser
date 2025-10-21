/* input_handling.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"

#include "dyn_survey.h"
#include "processing.h"

#define MAX_QUESTIONS 12
#define MAX_LEN 1000
#define TRUE 1
#define FALSE 0
#define MAX_ANSWERS 12
#define OPTIONS 10

// Store filelines

extern Response *responses;

extern int test_answers;

// Store question strings

// dynamic array to tell what answers to look out for.

// store frequency of answers
extern double **ans;

extern int found_idx;

extern int show_averages;
extern int show_frequencies;
extern int show_demographics;

extern int question_idx;

extern Survey survey;

extern int total_answers;

Respondent *newRespondent(char *degree, char *residence);

Respondent *addRes(Respondent *listp, Respondent *newRes);

int init_answer_values()
{
    survey.questions = (char **)emalloc(MAX_QUESTIONS * sizeof(char **));

    for (int i = 0; i < MAX_QUESTIONS; i++)
    {
        survey.questions[i] = emalloc(MAX_LEN * sizeof(char *));
    }

    // allocate memory to answers char array.
    survey.answers = (char **)emalloc(MAX_ANSWERS * sizeof(char *));

    ans = (double **)emalloc(MAX_ANSWERS * sizeof(double *));

    for (int i = 0; i < MAX_ANSWERS; i++)
    {
        survey.answers[i] = (char *)malloc(MAX_LEN * sizeof(char));
        ans[i] = (double *)emalloc(10 * sizeof(double));

        for (int j = 0; j < OPTIONS; j++)
            ans[i][j] = 0.0;

        strncpy(survey.answers[i], "", MAX_LEN);
    }

    return 0;
}

/*
    Find's whether to display the Frequencies of Answers or the Averages.
    Params: the line that determines the configuration.
    Returns: Nothing
*/
void get_config(char *line)
{
}

void dyn_parse(char *line, char **items, int *count)
{

    char *delimiter = ",\n";
    char *temp = emalloc(strlen(line) + 1);
    strncpy(temp, line, strlen(line));
    temp[strlen(line)] = '\0';
    char *token = strtok(temp, delimiter);
    
    int initalSize = 10;

    items = (char **)emalloc(initalSize * sizeof(char *));
    
    while (token != NULL)
    {
        if (*count >= initalSize){
            items = (char **)realloc(&items, initalSize * sizeof(char *));
    
        }
        items[*count] = (char *)emalloc(1 + strlen(token) * sizeof(char ));
        
        strncpy(items[*count], token, strlen(token));

        (*count)++;
        token = strtok(NULL, delimiter);
    }
    free(temp);
}


/*
    Gets the questions in the given text from the stdin seperated by semi-colons.
    Params: char *line in the file.
    Return: Nothing
*/
void get_questions(char *line)
{
    char *delimiter = ";\n";
    char *temp = (char *)emalloc(strlen(line) * sizeof(char *));
    strncpy(temp, line, strlen(line));

    char *question = strtok(temp, delimiter);

    while (question != NULL && survey.num_questions < MAX_QUESTIONS)
    {
        strncpy(survey.questions[survey.num_questions], question, MAX_LEN);

        survey.num_questions++;
        question = strtok(NULL, delimiter);
    }
}

void get_answers(char *line)
{
    char *each_answer;

    each_answer = test_answers == FALSE ? strtok(line, ",\n") : strtok(NULL, ",\n");

    for (int i = 0; i < MAX_ANSWERS && each_answer != NULL; i++)
    {
        check_answer(each_answer, i, test_answers);
        each_answer = strtok(NULL, ",\n");
    }
}

