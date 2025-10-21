/* dyn_survey.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "input_handling.h"
#include "processing.h"

#include "output.h"

#define MAX_QUESTIONS 12

#define NUM__OF_STUDENTS 10

#define MAX_LEN 1000

#define DISAGREE 0
#define AGREE 3
#define PARTIALLY_DISAGREE 1
#define PARTIALLY_AGREE 2

#define TRUE 1
#define FALSE 0

#define MAX_ANSWERS 12
#define OPTIONS 10

// Store filelines
char *buffer;

// Store question strings

// Store question average
double question_average[MAX_ANSWERS];
// dynamic array to tell what answers to look out for.

// store frequency of answers
double **ans;

int found_idx = 0;

int MAX_RESPONDANTS = 0;

int question_idx = 0;
int test_answers = FALSE;
int total_answers = 0;

typedef struct Respondent Respondent;
struct Respondent
{
    char *degree;
    char *residence;
    Respondent *next;
};

typedef struct Response Response;
typedef struct Survey Survey;

typedef struct Response
{
    Respondent respondent;
    char *answers;
    int num_answers;
} Response;

struct Survey
{

    int show_averages;
    int show_frequencies;
    int show_demographics;
    char **programs;
    int num_programs;
    char **status;
    int num_status;
    char **questions;
    char **answers;
    int num_questions;

    int num_answers;
    int num_respondents;
};

Response *responses;

Survey survey;

Respondent *newRespondent(char *degree, char *residence)
{
    Respondent *temp;

    temp = (Respondent *)emalloc(sizeof(Respondent));
    temp->degree = degree;
    temp->residence = residence;
    temp->next = NULL;

    return temp;
}

Respondent *addRes(Respondent *listp, Respondent *newRes)
{

    Respondent *temp;

    if (listp == NULL)
    {
        return newRes;
    }
    for (temp = listp; temp->next != NULL; temp = temp->next)
        ;

    temp->next = newRes;

    return listp;
}

/*
    Proccess the entire survey file.
    Params: Nothing
    Returns: Nothing
*/
void proccess_survey_file()
{

    // test whether user reached answers in file.

    int parse_state = 0;
    char *max_num;
    char *degree;
    char *residence;
    Respondent *nm;
    buffer = (char *)emalloc(MAX_LEN);
    int initalSize = 10;
    printf("Fail???");
    responses = (Response *) emalloc(sizeof(Response) * initalSize);
    while (fgets(buffer, MAX_LEN, stdin) != NULL)
    {
        char *line;
        if (buffer[0] == '#' || strlen(buffer) <= 1)
            continue;

        switch (parse_state)
        {
        case 0:
            get_config(buffer);
            sscanf(buffer, "%d,%d,%d", &survey.show_frequencies, &survey.show_averages, &survey.show_demographics);

            parse_state = 1;
            break;
        case 1:
            dyn_parse(buffer, survey.programs, &survey.num_programs);
            parse_state = 2;
            break;
        case 2:
            printf("Helloooo");
            dyn_parse(buffer, survey.status, &survey.num_status);
            parse_state = 3;
            break;
        case 3:
            get_questions(buffer);
            parse_state = 4;
            break;
        case 4:
            if (strchr(buffer, ',') != NULL && test_answers == FALSE)
            {
                printf("%s\n", buffer);
                get_answers(buffer);
                test_answers = TRUE;
                parse_state = 5;
            }
            else
            {

                line = strtok(buffer, ",\n");

                degree = (char *)emalloc(strlen(line) + 1);
                strncpy(degree, line, strlen(line));
                degree[strlen(line) - 1] = '\0';

                line = strtok(NULL, ",\n");

                residence = (char *)emalloc(strlen(line) + 1);
                strncpy(residence, line, strlen(line));
                residence[strlen(line) - 1] = '\0';

                nm = newRespondent(degree, residence);
                printf("Hello \n");
                responses[0].respondent = *nm;
                get_answers(line);
            }

            break;

        case 5:
            max_num = strtok(buffer, "\n");
            survey.num_respondents = atoi(max_num);

            parse_state = 4;
            break;
        }
    }
    free(nm);
    free(degree);
    free(residence);
    free(buffer);
}

/*
    where the magic happens ;)
*/
int main(int argc, char *argv[])
{

    init_answer_values();

    proccess_survey_file();
    printf("%s : %s\n", responses[0].respondent.degree, responses[0].respondent.residence);
    calc_averages();
    header_section();
    if (survey.show_frequencies == TRUE)
    {
        printf("\n#####\n");
        printf("FOR EACH QUESTION/ASSERTION BELOW, RELATIVE PERCENTUAL FREQUENCIES ARE COMPUTED FOR EACH LEVEL OF AGREEMENT\n\n");
        display_frequencies(survey.questions, survey.num_answers, ans, survey.answers);
    }

    if (survey.show_averages == TRUE)
    {
        printf("\n#####\n");
        printf("FOR EACH QUESTION/ASSERTION BELOW, THE AVERAGE RESPONSE IS SHOWN (FROM 1-DISAGREEMENT TO 4-AGREEMENT)\n\n");
        display_averages(survey.questions, question_average);
    }

    if (survey.show_demographics == TRUE)
    {
        printf("\n#####\n");
        printf("FOR EACH DEMOGRAPHIC CATEGORY BELOW, RELATIVE PERCENTUAL FREQUENCIES ARE COMPUTED FOR EACH ATTRIBUTE VALUE\n\n");
        printf("UNDERGRADUATE PROGRAM\n");

        printf("RESIDENCE STATUS\n");
    }

    for (int i = 0; i < MAX_ANSWERS; i++)
    {
        free(survey.answers[i]);
    }

    for (int i = 0; i < MAX_ANSWERS; i++)
    {
        free(ans[i]);
    }
    free(ans);
    free(survey.answers);
    free(responses);

    return 0;
}
