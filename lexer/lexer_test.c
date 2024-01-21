// #include "../token.c"
#include <stdio.h>
#include <string.h>
#include "lexer.h"

void delimeters_and_operators_test(void);
void add_two_numbers_test(void);

int main(void){
    // delimeters_and_operators_test();
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
    //this literal string has 79 characters
    //and gets an \0 implicitly added to the end of the string
    //strlen will count up to but not including the \0 char, so 79 chars
    char *input =
    "let five = 5;"
    "let ten = 10;"
    "let add = fn(x, y){x+y;};"
    "let result = add(five, ten);";
    printf("input:\n%s\n", input);
    printf("input length: %zu\n", strlen(input));
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
    //dinamically getting the size of tests array if more cases are needed
    size_t test_count = sizeof(tests)/sizeof(Token);
    printf("Currently executing %zu tests.\n", test_count);
    Lexer *lexer = new_lexer(input);
    for(int i = 0; i < 36; i++){
        Token *token = next_token(lexer);
        printf("lexer token type: %s, test token type: %s.\n", token->type, tests[i].type);
        printf("lexer token literal: %s, test token literal: %s.\n", token->literal, tests[i].literal);
        printf("\n");
    }
}
