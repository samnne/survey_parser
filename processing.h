#ifndef _PROCESSING_H_
#define _PROCESSING_H_

/* add your include and prototypes here*/

/*
    Finds the index where the given answer ("agree", "disagree", ...) is stored in the array answers;
    Params: char *answer the given answer to find in the answers array
    Returns: The index where the answer is, or -1;
*/
int find_answer(char *line, int n, char **array);
/**
 * Checks whether the given line from the file is already stored in the answers array
 * If not store it at the correct index
 * Params: char *line -> string to check for, int *n -> count of the size of the list, char **array -> destination array
 * Return: Nothing
 */

void get_options(char *line, int *n, char **array);
/**
 * Calculates frequencies of each answer in the survey
 * Params: char *answer -> answer to both check if its already stored, int questions -> locations in ans array to increment, int test_answers -> boolean to see if we are processing answers.
    Return: Nothing
 */
void check_answer(char *answer, int question, int test_answers);
/**
 * Calculates the averages from the likert survey system
 * Params: Nothing
 * Return: Nothing
 */
void calc_averages();
/**
 * Calculates the frequency of the respondent
 * Params: Response *response -> Respondent array, Survey config -> The Survey, double **dest -> destination array
 * Return: Nothing
 */
void calc_respondent(Response *response, Survey config, double **dest);

/**
 * Calculates the frequency of the Residence Status
 * Params: Response *response -> Respondent array, Survey config -> The Survey, double **dest -> destination array
 * Return: Nothing
 */
void calc_status(Response *response, Survey config, double **dest);
#endif
