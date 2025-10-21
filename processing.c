/* processing.c */
#include <string.h>
#include <stdio.h>
#include "dyn_survey.h"
#include "emalloc.h"
#include "input_handling.h"

// dynamic array to tell what answers to look out for.

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

/**
 * Checks whether the given line from the file is already stored in the answers array
 * If not store it at the correct index
 * Params: char *line -> string to check for, int *n -> count of the size of the list, char **array -> destination array
 * Return: Nothing
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

/**
 * Calculates frequencies of each answer in the survey
 * Params: char *answer -> answer to both check if its already stored, int questions -> locations in ans array to increment, int test_answers -> boolean to see if we are processing answers.
 */
void check_answer(char *answer, int question, int test_answers)
{

    get_options(answer, &survey.num_answers, survey.answers);

    int answer_idx = find_answer(answer, survey.num_answers, survey.answers);
    if (answer_idx >= 0 && test_answers == TRUE)
    {
        ans[question][answer_idx] += 10;
    }
}

/**
 * Calculates the averages from the likert survey system
 * Params: Nothing
 * Return: Nothing
 */

void calc_averages()
{
    question_average = (double *)emalloc(survey.num_questions * sizeof(double));
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

/**
 * Calculates the frequency of the respondent
 * Params: Response *response -> Respondent array, Survey config -> The Survey, double **dest -> destination array
 * Return: Nothing
 */
void calc_respondent(Response *response, Survey config, double **dest)
{
    for (int i = 0; i < config.num_respondents; i++)
    {
        for (int j = 0; j < config.num_programs; j++)
        {
            if (strncmp(response[i].respondent->degree, config.programs[j], strlen(response[i].respondent->degree) + 1) == 0)
            {
                (*dest)[j]++;
                break;
            }
        }
    }
}

/**
 * Calculates the frequency of the Residence Status 
 * Params: Response *response -> Respondent array, Survey config -> The Survey, double **dest -> destination array
 * Return: Nothing
 */
void calc_status(Response *response, Survey config, double **dest)
{
    for (int i = 0; i < config.num_respondents; i++)
    {
        for (int j = 0; j < config.num_status; j++)
        {

            if (strncmp(response[i].respondent->residence, config.status[j], strlen(response[i].respondent->residence) + 1) == 0)
            {
                (*dest)[j] += 1.0;
                break;
            }
        }
    }
}