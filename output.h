#ifndef _OUTPUT_H_
#define _OUTPUT_H_

/* add your include and prototypes here*/

// Prints the header section. Params: Nothing. Returns: Nothing.
void header_section();
/*
    Displays the questions gathered and the parsed frequencies of each possible answer in the file/stdin.
    Params: char questions_array: The char array containing all the questions,
            int total_possible_answers: the total number likert answers in this survey,
            double answer_array: the frequnecies of answers given in the file/stdin,
            char **possible_answers: All the likert answers parsed from the file/stdin
    Returns: Nothing
*/
void display_frequencies(char **questions_array, int total_possible_answers, double **answer_array, char **possible_answers);
/*
    Displays the questions gathered and the averages calculated of each quesiton from the file/stdin.
    Params: char question_array: char array of all the given questions,
            double* average_array: double array containing the calculated averages.
*/
void display_averages(char **question_array, double *average_array);
/**
 * Displays the demograpics for the survey
 * Params: Survey config -> The Survey struct, double *frequnecy -> frequency array, char *text -> header text to display, int *n -> total items, char **items -> items to display
 * Return: Nothing
 */
void display_demographics(Survey config, double *frequency, char *text, int *n, char **items);

#endif
