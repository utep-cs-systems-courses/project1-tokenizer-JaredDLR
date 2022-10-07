#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

int space_char(char c)
{
  return c == '\t' || c == ' ' ? 1 : 0;
}

int non_space_char(char c)
{
  return !space_char(c);
}

char *word_start(char *str)
{
  while (*str != '\0') {
    if (non_space_char(*str))
      return str;
    str++;
  }
  return NULL;
}

char *word_terminator(char *word)
{
  while (*word != '\0') {
    if (space_char(*word))
      return word;
    word++;
  }
  return word;
}

int count_words(char *str)
{
  int count;

  count = 0;
  do {
    if (str = word_start(str)) count++;
    else break;
  } while (str = word_terminator(str));
  
  return count;
}

char *copy_str(char *inStr, short len)
{
  char *str;
  int i;

  str = (char *) malloc(len + 1);
  for (i = 0; i < len; i++)
    str[i] = inStr[i];
  str[i] = '\0';
  return str;
}

char **tokenize(char *str)
{
  char **tokens;
  int count, i;

  count = count_words(str);
  tokens = (char **) malloc((count + 1) * sizeof(char *));
  for (i = 0; i < count; i++) {
    char *endWord;

    endWord = word_terminator(str = word_start(str));
    tokens[i] = copy_str(str, endWord - str);
    str = endWord;
  }
  tokens[i] = NULL;
  return tokens;
}

void print_tokens(char **tokens)
{
  while (*tokens) {
    printf("%s\n", *tokens++);
  }
}

void free_tokens(char **tokens)
{
  char **temp;

  for (temp = tokens; *temp; free(*temp++));
  free(tokens);
}
