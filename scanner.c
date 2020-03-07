#include <string.h>

#include "common.h"
#include "scanner.h"

typedef struct {
  const char* start;
  const char* current;
  int line;
} Scanner;

Scanner scanner;

void initScanner(const char* source) {
  scanner.start = source;
  scanner.current = source;
  scanner.line = 1;
}

static char advance() {
  scanner.current++;
  return scanner.current[-1];
}

static Token makeToken(TokenType type) {
  Token token;
  token.line = scanner.line;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  token.type = type;

  return token;
}

static Token errorToken(const char* message) {
  Token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = (int)strlen(message);
  token.line = scanner.line;

  return token;
}

static bool isAtEnd() { return *scanner.current == '\0'; }

static char peek() { return *scanner.current; }

static char peekNext() {
  if (isAtEnd())
    return '\0';
  return scanner.current[1];
}

static bool match(char expected) {
  if (isAtEnd())
    return false;
  if (*scanner.current != expected)
    return false;

  scanner.current++;
  return true;
}

static void skipWhitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      advance();
      break;
    case '\n':
      scanner.line++;
      advance();
      break;
    case '/':
      if (peekNext() == '/') {
        while (peek() != '\n' && !isAtEnd())
          advance();
      } else {
        return;
      }
    default:
      return;
    }
  }
}

static bool isDigit(char c) { return c >= '0' && c <= '9'; }

static Token number() {
  while (isDigit(peek()))
    advance();

  if (peek() == '.' && isDigit(peekNext())) {
    advance();

    while (isDigit(peek()))
      advance();

    return makeToken(TOKEN_FLOAT_LIT);
  }

  return makeToken(TOKEN_INT_LIT);
}

static bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static TokenType checkKeyword(int start, int length, const char* rest,
                              TokenType type) {
  if (scanner.current - scanner.start == start + length &&
      memcmp(scanner.start + start, rest, length) == 0) {
    return type;
  }

  return TOKEN_IDENT;
}

static TokenType identifierType() {
  switch (scanner.start[0]) {
  case 'b':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'r':
        return checkKeyword(2, 3, "eak", TOKEN_BREAK);
      case 'o':
        return checkKeyword(2, 2, "ol", TOKEN_BOOL);
      }
    }
    break;
  case 'e':
    return checkKeyword(1, 3, "lse", TOKEN_ELSE);
  case 'f':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'l':
        return checkKeyword(2, 3, "oat", TOKEN_FLOAT);
      case 'a':
        return checkKeyword(2, 3, "lse", TOKEN_FALSE);
      }
    }
    break;
  case 'i':
    if (scanner.current - scanner.start > 1) {
      if (scanner.start[1] == 'f') {
        return TOKEN_IF;
      } else {
        return checkKeyword(1, 2, "nt", TOKEN_INT);
      }
    }
    break;
  case 'n':
    return checkKeyword(1, 2, "ew", TOKEN_NEW);
  case 'r':
    return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
  case 's':
    return checkKeyword(1, 3, "ize", TOKEN_SIZE);
  case 't':
    return checkKeyword(1, 3, "rue", TOKEN_TRUE);
  case 'v':
    return checkKeyword(1, 3, "oid", TOKEN_VOID);
  case 'w':
    return checkKeyword(1, 4, "hile", TOKEN_WHILE);
  }

  return TOKEN_IDENT;
}

static Token identifier() {
  while (isAlpha(peek()) || isDigit(peek()))
    advance();

  return makeToken(identifierType());
}

Token scanToken() {
  skipWhitespace();

  scanner.start = scanner.current;

  if (isAtEnd())
    return makeToken(TOKEN_EOF);

  char c = advance();
  if (isAlpha(c))
    return identifier();
  if (isDigit(c))
    return number();

  switch (c) {
  case '(':
    return makeToken(TOKEN_LEFT_PAREN);
  case ')':
    return makeToken(TOKEN_RIGHT_PAREN);
  case '{':
    return makeToken(TOKEN_LEFT_BRACE);
  case '}':
    return makeToken(TOKEN_RIGHT_BRACE);
  case ';':
    return makeToken(TOKEN_SEMICOLON);
  case ',':
    return makeToken(TOKEN_COMMA);
  case '+':
    return makeToken(TOKEN_PLUS);
  case '-':
    return makeToken(TOKEN_MINUS);
  case '*':
    return makeToken(TOKEN_STAR);
  case '/':
    return makeToken(TOKEN_SLASH);
  case '%':
    return makeToken(TOKEN_MODULO);
  case '<':
    return makeToken(match('=') ? TOKEN_LE : TOKEN_LESS);
  case '>':
    return makeToken(match('=') ? TOKEN_GE : TOKEN_GREATER);
  case '=':
    return makeToken(match('=') ? TOKEN_EQ : TOKEN_EQUAL);
  case '!':
    return makeToken(match('=') ? TOKEN_NE : TOKEN_BANG);
  case '[':
    return makeToken(TOKEN_LEFT_BRACKET);
  case ']':
    return makeToken(TOKEN_RIGHT_BRACKET);
  case '.':
    return makeToken(TOKEN_DOT);
  case '&':
    if (match('&')) {
      return makeToken(TOKEN_AND);

      break;
    }
  case '|':
    if (match('|')) {
      return makeToken(TOKEN_OR);
    }
    break;
  }

  return errorToken("Unexpected character");
}