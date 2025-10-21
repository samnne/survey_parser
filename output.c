/* output.c */
#include <stdio.h>
#include "dyn_survey.h"
#define MAX_QUESTIONS 12
#define MAX_LEN 1000
#define OPTIONS 10
extern Survey survey;

// Prints the header section. Params: Nothing. Returns: Nothing.
void header_section()
{
    printf("ECS Student Survey\nSURVEY RESPONSE STATISTICS\n\nNUMBER OF RESPONDENTS: %d\n", survey.num_respondents);
}

/*
    I love commenting, but this is does pretty much what it says it does.

    Displays the questions gathered and the parsed frequencies of each possible answer in the file/stdin.
    Params: char questions_array[][MAX_LEN]: The char array containing all the questions,
            int total_possible_answers: the total number likert answers in this survey,
            double answer_array[][OPTIONS]: the frequnecies of answers given in the file/stdin,
            char **possible_answers: All the likert answers parsed from the file/stdin
    Returns: Nothing
*/
void display_frequencies(char **questions_array, int total_possible_answers, double **answer_array, char **possible_answers)
{
    for (int q = 0; q < MAX_QUESTIONS; q++)
    {
      
        printf("%d. %s\n", q + 1, questions_array[q]);

        for (int a = 0; a < total_possible_answers; a++)
        {
            printf("%.2f: %s\n", answer_array[q][a], possible_answers[a]);
        }
        if (q != MAX_QUESTIONS - 1)
        {
            printf("\n");
        }
    }
}

/*
    This as well

    Displays the questions gathered and the averages calculated of each quesiton from the file/stdin.
    Params: char question_array[][MAX_LEN]: char array of all the given questions,
            double* average_array: double array containing the calculated averages.
*/
void display_averages(char **question_array, double *average_array)
{
    for (int k = 0; k < MAX_QUESTIONS; k++)
    {
        printf("%d. %s - %.2f\n", k + 1, question_array[k], average_array[k]);
    }
}
