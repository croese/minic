#ifndef minic_scanner_h
#define minic_scanner_h

typedef enum {
  // single-character tokens
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN,
  TOKEN_LEFT_BRACE,
  TOKEN_RIGHT_BRACE,
  TOKEN_SEMICOLON,
  TOKEN_COMMA,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_STAR,
  TOKEN_SLASH,
  TOKEN_MODULO,
  TOKEN_LESS,
  TOKEN_GREATER,
  TOKEN_EQUAL,
  TOKEN_BANG,
  TOKEN_LEFT_BRACKET,
  TOKEN_RIGHT_BRACKET,
  TOKEN_DOT,

  // two-character operators
  TOKEN_LE,
  TOKEN_GE,
  TOKEN_EQ,
  TOKEN_NE,
  TOKEN_OR,
  TOKEN_AND,

  // keywords
  TOKEN_IF,
  TOKEN_ELSE,
  TOKEN_WHILE,
  TOKEN_RETURN,
  TOKEN_BREAK,
  TOKEN_NEW,
  TOKEN_SIZE,
  TOKEN_VOID,
  TOKEN_BOOL,
  TOKEN_INT,
  TOKEN_FLOAT,
  TOKEN_TRUE,
  TOKEN_FALSE,

  // literals
  TOKEN_INT_LIT,
  TOKEN_FLOAT_LIT,
  TOKEN_IDENT,

  TOKEN_ERROR,
  TOKEN_EOF
} TokenType;

typedef struct {
  TokenType type;
  const char* start;
  int length;
  int line;
} Token;

void initScanner(const char* source);
Token scanToken();

#endif