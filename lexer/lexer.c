#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
// #include "../token.c"

void print_lexer(Lexer *lexer){
    printf("lexer->input : %s\n", lexer->input);
    printf("lexer->position : %d\n", lexer->position);//index referring to current character being examined
    printf("lexer->read_position : %d\n", lexer->read_position);//index referrint to next character
    printf("lexer->ch : %c\n", lexer->ch);//current character being examined
}

Lexer *new_lexer(char *input){
    size_t input_len = strlen(input);
    printf("length of input? %zu\n", strlen(input));
    char *lexer_input = malloc(sizeof(char)*input_len);
    //memory allocating just for the size of the lexer should be enough since pointers are constant size
    Lexer *lexer = malloc(sizeof(Lexer));
    strcpy(lexer_input, input);
    printf("lexer input: %s\n", lexer_input);
    lexer->input = lexer_input;
    lexer->position = 0;
    lexer->read_position = 0;
    lexer_read_char(lexer);
    // lexer->ch = lexer->input[0];
    print_lexer(lexer);
    return lexer;
}

void lexer_read_char(Lexer *lexer){
    if(lexer->read_position > (int) strlen(lexer->input)){
        lexer->ch = '\0';
    }else{
        lexer->ch = lexer->input[lexer->read_position];
    }
    lexer->position = lexer->read_position;
    lexer->read_position++;
}

Token *next_token(Lexer *lexer){
    Token *token;
    switch (lexer->ch)
    {
        case '=':
            token = new_token(ASSIGN, "=");
            break;
        
        case '(':
            token = new_token(LPAREN, "(");
            break;
        
        case ')':
            token = new_token(RPAREN, ")");
            break;
        
        case '{':
            token = new_token(LBRACE, "{");
            break;
        
        case '}':
            token = new_token(RBRACE, "}");
            break;
        
        case ',':
            token = new_token(COMMA, ",");
            break;
        
        case ';':
            token = new_token(SEMICOLON, ";");
            break;
            
        case '+':
            token = new_token(PLUS, "+");
            break;
        
        case '\0':
            token = new_token(END, "");
            break;
        
        default:
            token = new_token(END, "");
            break;
    }
    lexer_read_char(lexer);
    return token;
}

void print_token(Token *token){
    printf("token->type: %s\n", token->type);
    printf("token->literal: %s\n", token->literal);
}

Token *new_token(TokenType type, char *literal){
    Token *token = malloc(sizeof(Token));
    // size_t type_len = strlen(type);
    // size_t literal_len = strlen(literal);
    char *token_type = malloc(sizeof(char)*strlen(type));
    char *token_literal = malloc(sizeof(char)*strlen(literal));
    strcpy(token_type, type);
    strcpy(token_literal, literal);
    token->type = token_type;
    token->literal = token_literal;
    print_token(token);
    return token;
}