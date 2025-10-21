#ifndef _DYN_SURVEY_H_
#define _DYN_SURVEY_H_

/* add your library includes, constants and typedefs here*/
void proccess_survey_file();

typedef struct Respondent Respondent;
typedef struct Survey Survey;
typedef struct Response Response;

struct Respondent
{
    char *degree;
    char *residence;
    Respondent *next;
};

struct Response
{
    Respondent respondent;
    char **answers;
    int num_answers;
};

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
    // char likert_items[MAX_LIKERT][MAX_STRING];
    int num_answers;
    int num_respondents;
};

extern Survey survey;
extern Respondent *list;

#endif
