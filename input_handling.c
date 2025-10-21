/* input_handling.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"

#include "dyn_survey.h"
#include "processing.h"


/*
    Initalize the survey values
    Params: Nothing
    Returns: Nothing

*/
int init_answer_values()
{
    survey.questions = (char **)emalloc(MAX_QUESTIONS * sizeof(char **));

    for (int i = 0; i < MAX_QUESTIONS; i++)
    {
        survey.questions[i] = emalloc(MAX_LEN * sizeof(char ));
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


/* Dynamically Parse Survey array's. 
    Params: char *line -> token
            char ***items -> the destination to place each token in an array
            int *count -> the size of the array and which specific index to grow from
    Returns: Nothing
*/
void dyn_parse(char *line, char ***items, int *count)
{
    char *delimiter = ",\n";
    char *temp = emalloc(strlen(line) + 1);
    strncpy(temp, line, strlen(line)+ 1);
    temp[strlen(line)] = '\0';
    char *token = strtok(temp, delimiter);

    int initalSize = 10;

    if (*items == NULL || *count == 0)
    {
        *items = (char **)emalloc(initalSize * sizeof(char *));
        *count = 0;
    }

    while (token != NULL)
    {

        (*items)[*count] = (char *)emalloc(strlen(token) +1);
        strncpy((*items)[*count], token, strlen(token) + 1);
        (*items)[*count][strlen(token)] = '\0';
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
        survey.questions[survey.num_questions][MAX_LEN-1] = '\0';
        survey.num_questions++;
        question = strtok(NULL, delimiter);
    }
    free(temp);
}


/**
 * Gets the answers from the file. Initialzing the answers array on first function call with test_answers;
 * Params: line -> token
 * Return: Nothing
 */
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
