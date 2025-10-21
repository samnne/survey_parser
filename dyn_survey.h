#ifndef _DYN_SURVEY_H_
#define _DYN_SURVEY_H_

#define MAX_QUESTIONS 12
#define MAX_LEN 1000

// BOOLEAN True or False
#define TRUE 1
#define FALSE 0


#define MAX_ANSWERS 12
#define OPTIONS 10

/* add your library includes, constants and typedefs here*/

// Process survey file. Params: Nothing Return: Nothing
void proccess_survey_file(void);

typedef struct Respondent Respondent;
typedef struct Response Response;

// Respondent
struct Respondent
{
    char *degree;
    char *residence;
};

// List type of respondents
struct Response
{
    // 
    Respondent *respondent;
    int num_answers;
};

typedef struct Survey
{
    // Bits to determine what statistics to show
    int show_averages; 
    int show_frequencies;
    int show_demographics;

    // Program array, and number of programs from the file
    char **programs;
    int num_programs;
    // Residence Status array, and number of types of residences
    char **status;
    int num_status;

    // Questions array
    char **questions;
    // Answers array
    char **answers;

    // Totals
    int num_questions;
    int num_answers;
    int num_respondents;
} Survey;

// Boolean
extern int test_answers;

extern int found_idx;

extern double **ans;
extern double *question_average;

// Responses List, Survey structure
extern Response *responses;
extern Survey survey;


#endif