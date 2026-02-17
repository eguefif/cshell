#include "parser.h"

size_t get_string(char *, Token*);
size_t get_quote_token(char *, Token*);
size_t get_double_quote_token(char *, Token*);
size_t escape_char(char *, Token*);

size_t skip_white_char(char *);
TokenType get_token_type(char *);
bool is_stop_token(char c);

Token *tokenize(char *input) {
  Token *tokens = (Token *)alloc(sizeof(Token) * 200);
  size_t cursor = 0;
  size_t token_count = 0;
  char *new_token = 0;

  cursor += skip_white_char(&input[cursor]);
  while (input[cursor] != '\0' && cursor < PROMPT_MAX_SIZE) {
    switch (input[cursor]) {
      case ' ':
        new_token = (char*) alloc(1);
        tokens[token_count] = (Token) {SPACE, 0, 0};
        cursor += 1;
        token_count++;
        cursor += skip_white_char(&input[cursor]);
        break;
      case '\'':
        cursor += get_quote_token(&input[cursor], &tokens[token_count]);
        token_count++;
        break;
      case '\"':
        cursor += get_double_quote_token(&input[cursor], &tokens[token_count]);
        token_count++;
        break;
      case '~':
        new_token = (char*) alloc(1);
        memcpy(new_token, "~\0", 2);
        tokens[token_count] = (Token) {TILD, new_token, 1};
        cursor += 1;
        token_count++;
        break;
      default:
        cursor += get_string(&input[cursor], &tokens[token_count]);
        token_count++;
        break;
    }
  }
  Token token = {EOP, "", 0};
  tokens[token_count] = token;

  return tokens;
}

size_t skip_white_char(char *input) {
  size_t cursor = 0;
  while (is_whitespace(input[cursor]) && input[cursor] != '\0') {
    cursor++;
  }
  return cursor;
}

size_t get_string(char *input, Token *token) {
  size_t cursor = 0;
  size_t cursor2 = 0;
  while (!is_whitespace(input[cursor2]) && input[cursor2] != '\0') {
    if (input[cursor2] == '\'' && input[cursor2 + 1] != '\0' && input[cursor2 + 1] =='\'') {
      cursor2 += 2;
    } else if (input[cursor2] == '\"' && input[cursor2 + 1] != '\0' && input[cursor2 + 1] =='\"') {
      cursor2 += 2;
    }  else if (input[cursor2] == '\\') {
      cursor2 += 1;

    } else if (is_stop_token(input[cursor2])) {
      break;
    }
    input[cursor] = input[cursor2];
    cursor++;
    cursor2++;
  }

  char *new_token = (char *) alloc(cursor + 1);
  memcpy(new_token, &input[0], cursor);
  new_token[cursor] = '\0';
  token->type = STRING;
  token->token = new_token;
  token->size = cursor;
  return cursor2;
}

bool is_stop_token(char c) {
  return c == '\'' || c == '\"' || c == '$' || c == '~';
}


size_t get_quote_token(char *input, Token *token) {
  size_t cursor = 0;
  size_t cursor2 = 1;
  while (input[cursor2] != '\0') {
    if (input[cursor2] == '\'' && input[cursor2 + 1] != '\0' && input[cursor2 + 1] =='\'') {
      cursor2 += 2;
    } else if (input[cursor2] == '\'') {
      break;
    }
    input[cursor] = input[cursor2];
    cursor++;
    cursor2++;
  }
  char *new_token = (char *) alloc(cursor + 1);
  memcpy(new_token, input, cursor);
  new_token[cursor] = '\0';
  token->type = STRING;
  token->token = new_token;
  token->size = cursor;
  return cursor2 + 1;
}

size_t get_double_quote_token(char *input, Token *token) {
  size_t cursor = 0;
  size_t cursor2 = 1;
  while (input[cursor2] != '\0') {
    if (input[cursor2] == '\"' && input[cursor2 + 1] != '\0' && input[cursor2 + 1] =='\"') {
      cursor2 += 2;
    } else if (input[cursor2] == '\"') {
      break;
    } else if (input[cursor2] == '\\') {
      if (input[cursor2 + 1] != '\0') {
        switch (input[cursor2 + 1]) {
          case '"':
          case '\\':
            cursor2 ++;
        }
      }
    }
    input[cursor] = input[cursor2];
    cursor++;
    cursor2++;
  }
  char *new_token = (char *) alloc(cursor + 1);
  memcpy(new_token, input, cursor);
  new_token[cursor] = '\0';
  token->type = STRING;
  token->token = new_token;
  token->size = cursor;
  return cursor2 + 1;
}


TokenType get_token_type(char *value) {
  if (strncmp(value, "\"", 1) == 0) {
    return DQUOTE;
  } else if (strncmp(value, "\'", 1) == 0) {
    return QUOTE;
  } else if (strncmp(value, "|'", 1) == 0) {
    return PIPE;
  } else if (strncmp(value, "&", 1) == 0) {
    return AMPERSAND;
  } else if (strncmp(value, ">", 1) == 0) {
    return RIGHTREDIRECTION;
  } else if (strncmp(value, "<", 1) == 0) {
    return LEFTREDIRECTION;
  } else if (strncmp(value, "$", 1) == 0) {
    return DOLLAR;
  }
  return STRING;
}

size_t escape_char(char *input, Token* token) {
  if (input[1] != '\0') {
    char *new_token = alloc(2);
    *new_token = input[1];
    new_token[1] = '\0';
    token->size = 1;
    token->token = new_token;
    token->type = STRING;
  } else {
    token->size = 0;
    token->token = 0;
    token->type = EOP;
    
  }
  return 1;
}
