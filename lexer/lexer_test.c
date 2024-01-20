// #include "../token.c"
#include <stdio.h>
#include "lexer.h"

void delimeters_and_operators_test(void);
void add_two_numbers_test(void);

int main(void){
    delimeters_and_operators_test();
    add_two_numbers_test();
    return 0;
}

void delimeters_and_operators_test(void){
    char *input = "=+(){},;";
    Token tests[] = {
        {ASSIGN, "="},
        {PLUS, "+"},
        {LPAREN, "("},
        {RPAREN, ")"},
        {LBRACE, "{"},
        {RBRACE, "}"},
        {COMMA, ","},
        {SEMICOLON, ";"},
        {END, ""},
    };
    Lexer *lexer = new_lexer(input);
    for(int i = 0; i < 9; i++){
        Token *token = next_token(lexer);
        printf("lexer token type: %s, test token type: %s.\n", token->type, tests[i].type);
        printf("lexer token literal: %s, test token literal: %s.\n", token->literal, tests[i].literal);
    }
}


void add_two_numbers_test(void){
    char *input =
    "let five = 5;"
    "let ten = 10;"
    "let add = fn(x, y){x+y;};"
    "let result = add(five, ten);";
    printf("%s\n", input);
    Token tests[] ={
        {LET, "let"},
        {IDENT, "five"},
        {ASSIGN, "="},
        {INT, "5"},
        {SEMICOLON, ";"},
        {LET, "let"},
        {IDENT, "ten"},
        {ASSIGN, "="},
        {INT, "10"},
        {SEMICOLON, ";"},
        {LET, "let"},
        {IDENT, "add"},
        {ASSIGN, "="},
        {FUNCTION, "fn"},
        {LPAREN, "("},
        {IDENT, "x"},
        {COMMA, ","},
        {IDENT, "y"},
        {RPAREN, ")"},
        {LBRACE, "{"},
        {IDENT, "x"},
        {PLUS, "+"},
        {IDENT, "y"},
        {SEMICOLON, ";"},
        {RBRACE, "}"},
        {SEMICOLON, ";"},
        {LET, "let"},
        {IDENT, "result"},
        {ASSIGN, "="},
        {IDENT, "add"},
        {LPAREN, "("},
        {IDENT, "five"},
        {COMMA, ","},
        {IDENT, "ten"},
        {RPAREN, ")"},
        {SEMICOLON, ";"}
    };
    Lexer *lexer = new_lexer(input);
}
