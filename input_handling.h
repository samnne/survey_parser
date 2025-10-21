#ifndef _INPUT_HANDLING_H_
#define _INPUT_HANDLING_H_

/* add your include and prototypes here*/

#define MAX_QUESTIONS 12
#define MAX_LEN 1000
#define TRUE 1
#define FALSE 0
#define MAX_ANSWERS 12
#define OPTIONS 10





int init_answer_values();
void get_config(char *line);
void dyn_parse(char *line, char **items, int *count);
void get_res_status(char *line);
void get_questions(char *line);
void get_answers(char *line);


#endif
