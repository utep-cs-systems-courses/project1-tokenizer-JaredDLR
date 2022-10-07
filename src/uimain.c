#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"

int buffer_size = 100;

int main()
{
  List *list;

  list = init_history();
  while (1) {
    char input[buffer_size];
    
    printf("$ ");
    fgets(input, buffer_size, stdin);
    if (input[0] == '!') {
      if (input[1] == 'q') {
	free_history(list);
	printf("Thank you for using Tokenizer\n");
	return 0;
      } else if (input[1] == 'h') {
	print_history(list);
      } else {
	int id;
	char *selectedHistory;

	id = atoi(&input[1]);
	selectedHistory = get_history(list, id);
	printf("[%d]: %s", id, selectedHistory);
      }
    } else {
      char **tokens;

      tokens = tokenize(input);

      add_history(list, input);
      print_tokens(tokens);
      free_tokens(tokens);
    }
  }
}
