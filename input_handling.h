#ifndef _INPUT_HANDLING_H_
#define _INPUT_HANDLING_H_
#include "dyn_survey.h"
/* add your include and prototypes here*/



/*
    Initalize the survey values
    Params: Nothing
    Returns: Nothing
*/
int init_answer_values();

/* Dynamically Parse Survey array's.
    Params: char *line -> token
            char ***items -> the destination to place each token in an array
            int *count -> the size of the array and which specific index to grow from
    Returns: Nothing
*/
void dyn_parse(char *line, char ***items, int *count);
/*
    Gets the questions in the given text from the stdin seperated by semi-colons.
    Params: char *line in the file.
    Return: Nothing
*/

void get_questions(char *line);
/**
 * Gets the answers from the file. Initialzing the answers array on first function call with test_answers;
 * Params: line -> token
 * Return: Nothing
 */
void get_answers(char *line);

#endif
