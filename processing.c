/* processing.c */
#include <string.h>
#include <stdio.h>
#include "dyn_survey.h"
#define TRUE 1
#define FALSE 0
#define MAX_QUESTIONS 12
#define OPTIONS 10
#define MAX_ANSWERS 12

// dynamic array to tell what answers to look out for.





extern int found_idx;



extern int total_undergrad;
extern int total_residence;

extern double **ans;
extern double question_average[MAX_ANSWERS];
/*
    Finds the index where the given answer ("agree", "disagree", ...) is stored in the array answers;
    Params: char *answer the given answer to find in the answers array
    Returns: The index where the answer is, or -1;
*/
int find_answer(char *line, int n, char **array)
{
    for (int i = 0; i < n; i++)
    {
        if (strncmp(line, array[i], strlen(line)) == 0)
        {
            return i;
        }
    }

    return -1;
}

/*
    Retrieves all the possible options given in the stdin and copies it in the answers array => Works with any likert answers (eg. "yes", "no", "maybe")
    Params: char *answer the possible new answer
    Returns: None
*/

void get_options(char *line, int *n, char **array)
{
    int found = FALSE;

    for (int i = 0; i < *n; i++)
    {
        if (strncmp(line, array[i], strlen(line)) == 0 && found == FALSE)
        {
            found = TRUE;
            break;
        }
    }
    if (found == FALSE)
    {
        (*n)++;
        strncpy(survey.answers[found_idx++], line, strlen(line));
    }
}

void check_answer(char *answer, int question, int test_answers)
{

    get_options(answer, &survey.num_answers, survey.answers);

    int answer_idx = find_answer(answer, survey.num_answers, survey.answers);
    if (answer_idx >= 0 && test_answers == TRUE)
    {
        ans[question][answer_idx] += 10;
    }
}

void calc_averages()
{
    for (int i = 0; i < MAX_QUESTIONS; i++)
    {
        double q_sum = 0;

        for (int j = 0; j < survey.num_answers; j++)
        {

            q_sum += (int)ans[i][j] * (j + 1);
        }
        question_average[i] = q_sum / 100;
    }
}

void check_undergrad(char *line)
{
    
}