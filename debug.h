#ifndef minic_debug_h
#define minic_debug_h

#include <stdio.h>

#include "scanner.h"

#define PRINT_TOKEN(token)                                                     \
  printf("%s: line %d: %.*s\n", tokenString((token).type), (token).line,       \
         (token).length, (token).start)

#define TYPE_CASE(type)                                                        \
  case type:                                                                   \
    return #type

const char* tokenString(TokenType type) {
  switch (type) {
    TYPE_CASE(TOKEN_LEFT_PAREN);
    TYPE_CASE(TOKEN_RIGHT_PAREN);
    TYPE_CASE(TOKEN_LEFT_BRACE);
    TYPE_CASE(TOKEN_RIGHT_BRACE);
    TYPE_CASE(TOKEN_SEMICOLON);
    TYPE_CASE(TOKEN_COMMA);
    TYPE_CASE(TOKEN_PLUS);
    TYPE_CASE(TOKEN_MINUS);
    TYPE_CASE(TOKEN_STAR);
    TYPE_CASE(TOKEN_SLASH);
    TYPE_CASE(TOKEN_MODULO);
    TYPE_CASE(TOKEN_LESS);
    TYPE_CASE(TOKEN_GREATER);
    TYPE_CASE(TOKEN_EQUAL);
    TYPE_CASE(TOKEN_BANG);
    TYPE_CASE(TOKEN_LEFT_BRACKET);
    TYPE_CASE(TOKEN_RIGHT_BRACKET);
    TYPE_CASE(TOKEN_DOT);
    TYPE_CASE(TOKEN_LE);
    TYPE_CASE(TOKEN_GE);
    TYPE_CASE(TOKEN_EQ);
    TYPE_CASE(TOKEN_NE);
    TYPE_CASE(TOKEN_OR);
    TYPE_CASE(TOKEN_AND);
    TYPE_CASE(TOKEN_IF);
    TYPE_CASE(TOKEN_ELSE);
    TYPE_CASE(TOKEN_WHILE);
    TYPE_CASE(TOKEN_RETURN);
    TYPE_CASE(TOKEN_BREAK);
    TYPE_CASE(TOKEN_NEW);
    TYPE_CASE(TOKEN_SIZE);
    TYPE_CASE(TOKEN_VOID);
    TYPE_CASE(TOKEN_BOOL);
    TYPE_CASE(TOKEN_INT);
    TYPE_CASE(TOKEN_FLOAT);
    TYPE_CASE(TOKEN_TRUE);
    TYPE_CASE(TOKEN_FALSE);
    TYPE_CASE(TOKEN_INT_LIT);
    TYPE_CASE(TOKEN_FLOAT_LIT);
    TYPE_CASE(TOKEN_IDENT);
    TYPE_CASE(TOKEN_ERROR);
    TYPE_CASE(TOKEN_EOF);
  default:
    return "Unrecognized token type";
  }
}

void printTokens(const char* source) {
  initScanner(source);
  Token token = scanToken();
  while (token.type != TOKEN_EOF) {
    PRINT_TOKEN(token);
    token = scanToken();
  }

  PRINT_TOKEN(token);
}

#endif