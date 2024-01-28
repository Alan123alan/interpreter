typedef char* TokenType;

typedef struct{
    TokenType type;
    char* literal;
}Token; 

/******** TOKEN TYPES ********/

//identifiers + literals
#define IDENT "IDENT"
#define INT "INT"

//operators
#define ASSIGN "="
#define PLUS "+"
#define BANG "!"
#define MINUS "-"
#define SLASH "/"
#define ASTERISK "*"
#define LT "<"
#define GT ">"
#define EQ "=="
#define NOT_EQ "!="

//delimiters
#define COMMA ","
#define SEMICOLON ";"
#define LPAREN "("
#define RPAREN ")"
#define LBRACE "{"
#define RBRACE "}"

//keywords
#define FUNCTION "FUNCTION"
#define LET "LET"
#define TRUE "TRUE"
#define FALSE "FALSE"
#define IF "IF"
#define ELSE "ELSE"
#define RETURN "RETURN"

#define ILLEGAL "ILLEGAL"
#define END "END"

typedef struct{
    char *key;
    char *value;
}Item;

// const Item [] = {
//     {"fn", FUNCTION},
//     {"let", LET}
// };


typedef struct {
    char *input;
    int position;
    int read_position;
    char ch;
}Lexer;

Lexer *new_lexer(char *input);
void print_lexer(Lexer *lexer);
void lexer_read_char(Lexer *lexer);
Token *next_token(Lexer *lexer);
Token *new_token(TokenType type, char *literal);
void print_token(Token *token);
TokenType get_identifier_or_keyword_type(char *literal);
char *get_identifier_or_keyword_literal(Lexer *lexer);
char *get_int(Lexer *lexer);
char lexer_peek_char(Lexer *lexer);
// void new(char *input);

