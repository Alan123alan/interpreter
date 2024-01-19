// #include "../token.c"
#include <stdio.h>
#include "lexer.h"

int main(void){
    char *input = "=+(){},;";
    Token tests[9] = {
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
        // if(token->type != tests[i].type){
        //     printf("lexer token type: %s, test token type: %s.\n", token->type, tests[i].type);
        // }
        // printf("token type: %s, token literal %s.\n", tests[i].type, tests[i].literal);
    }
    return 0;
}
