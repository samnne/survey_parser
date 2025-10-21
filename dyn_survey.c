/* dyn_survey.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "dyn_survey.h"
#include "input_handling.h"

#include "processing.h"

#include "output.h"

// Store filelines
char *buffer;

// Store question average
double *question_average = NULL;

// store frequency of answers
double **ans;

int found_idx = 0;

int r_idx = 0;
int question_idx = 0;
int test_answers = FALSE;
int total_answers = 0;


// Initalize Response and Survey structures.
Response *responses = NULL;
Survey survey = {0};

/*
    Proccess the entire survey file.
    Params: Nothing
    Returns: Nothing
*/
void proccess_survey_file()
{
    // Handle Parse State
    int parse_state = 0;
    
    // parses the amount of responses.
    char *max_num;


    buffer = (char *)emalloc(MAX_LEN);

    while (fgets(buffer, MAX_LEN, stdin) != NULL)
    {
        // tokenized line to handle all survey answers
        char *line;
        if (buffer[0] == '#' || strlen(buffer) <= 1)
            continue;

        switch (parse_state)
        {
        case 0:
            // scan the required bits to determine what data to show
            sscanf(buffer, "%d,%d,%d", &survey.show_frequencies, &survey.show_averages, &survey.show_demographics);

            parse_state = 1;
            break;
        case 1:

            // parse the survey programs
            dyn_parse(buffer, &survey.programs, &survey.num_programs);
           
            parse_state = 2;
            break;
        case 2:
            // parse the survey residence status
            dyn_parse(buffer, &survey.status, &survey.num_status);
            parse_state = 3;
            break;
        case 3:
            // get the questions
            get_questions(buffer);
            parse_state = 4;
            break;
        case 4:
            // getting the possible answers first then get survet responses 
            if (strchr(buffer, ',') != NULL && test_answers == FALSE)
            {
                get_answers(buffer);
                test_answers = TRUE;
                parse_state = 5;
            }
            else
            {
                // tokenize the buffer
                line = strtok(buffer, ",\n");
                
                /*
                    Allocate memory for respondent, degree. and residence to correctly copy the toekn into each property of respondent.
                */
                responses[r_idx].respondent = (Respondent *)emalloc(sizeof(Respondent));
                responses[r_idx].respondent->degree = (char *)emalloc(strlen(line) + 1);

                strncpy(responses[r_idx].respondent->degree, line, strlen(line));
                responses[r_idx].respondent->degree[strlen(line)] = '\0';

                line = strtok(NULL, ",\n");

                responses[r_idx].respondent->residence = (char *)emalloc(strlen(line) + 1);

                strncpy(responses[r_idx].respondent->residence, line, strlen(line));
                responses[r_idx].respondent->residence[strlen(line)] = '\0';

                get_answers(line);
               
                r_idx++;
            }
            break;

        case 5:
            // Stores the max number of respondents in survey.num_respondents
            
            max_num = strtok(buffer, "\n");
            survey.num_respondents = atoi(max_num);
            responses = (Response *)emalloc(sizeof(Response) * survey.num_respondents);
            // initalize each respondent of response to NULL
            for (int i = 0; i < survey.num_respondents; i++)
            {
               responses[i].respondent = NULL;
            }
            parse_state = 4;
            break;
        }
    }

    free(buffer);
    
    
}

/*
Free all items used in to process the survey.
Params: Nothing
Returns: Nothing
*/
void free_items()
{

    if (survey.questions != NULL)
    {
        for (int i = 0; i < survey.num_questions; i++)
        {
            if (survey.questions[i] != NULL)
                free(survey.questions[i]);
        }
        free(survey.questions);
    }
    
    if (survey.programs != NULL)
    {
        for (int i = 0; i < survey.num_programs; i++)
        {
            if (survey.programs[i] != NULL)
                free(survey.programs[i]);
        }
        free(survey.programs);
    }

   
    if (survey.status != NULL)
    {
        for (int i = 0; i < survey.num_status; i++)
        {
            if (survey.status[i] != NULL)
                free(survey.status[i]);
        }
        free(survey.status);
    }

  
    if (ans != NULL)
    {
        for (int i = 0; i < MAX_ANSWERS; i++)
        {
            if (ans[i] != NULL)
                free(ans[i]);
        }
        free(ans);
    }

   
    if (question_average != NULL)
        free(question_average);

    if (responses != NULL)
    {
        for (int i = 0; i < survey.num_respondents; i++)
        {
            if (responses[i].respondent != NULL)
            {
                free(responses[i].respondent->degree);
                free(responses[i].respondent->residence);
                free(responses[i].respondent);
            }
        }
        free(responses);
    }
}

/*
    where the magic happens ;)
*/
int main(int argc, char *argv[])
{

    init_answer_values();

    proccess_survey_file();
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
    double *program_freq = NULL;
    double *status_freq = NULL;
    if (survey.show_demographics == TRUE)
    {
        // Calculating Program and Status frequencies 
        program_freq = (double *)emalloc(survey.num_programs * sizeof(double)); // allocate memory for both arrays and initalize each index to zero
        for (int i = 0; i < survey.num_programs; i++)
            program_freq[i] = 0.0;
        status_freq = (double *)emalloc(survey.num_status * sizeof(double));
        for (int i = 0; i < survey.num_status; i++)
            status_freq[i] = 0.0;
        // calcuate both respondent with a the frequency destination array
        calc_respondent(responses, survey, &program_freq);
        calc_status(responses, survey, &status_freq);

        printf("\n#####\n");
        printf("FOR EACH DEMOGRAPHIC CATEGORY BELOW, RELATIVE PERCENTUAL FREQUENCIES ARE COMPUTED FOR EACH ATTRIBUTE VALUE\n\n");
      
        // display both program and status to the stdin.
        display_demographics(survey, program_freq, "UNDERGRADUATE PROGRAM\n", &survey.num_programs, survey.programs);
        
        display_demographics(survey, status_freq, "\nRESIDENCE STATUS\n", &survey.num_status, survey.status);
        free(status_freq);
        free(program_freq);
    };
    
    // Free items after everything is used.
    free_items();

    return 0;
}
