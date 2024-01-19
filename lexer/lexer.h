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
#define ASSIGN "ASSIGN"
#define PLUS "PLUS"

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

#define ILLEGAL "ILLEGAL"
#define END "END"

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
// void new(char *input);
