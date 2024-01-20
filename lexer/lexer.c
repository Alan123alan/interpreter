#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
// #include "../token.c"

const Item keywords[] = {
    {"fn", FUNCTION},
    {"let", LET}
};


void print_lexer(Lexer *lexer){
    printf("lexer->input : %s\n", lexer->input);
    printf("lexer->position : %d\n", lexer->position);//index referring to current character being examined
    printf("lexer->read_position : %d\n", lexer->read_position);//index referrint to next character
    printf("lexer->ch : %c\n", lexer->ch);//current character being examined
}

Lexer *new_lexer(char *input){
    //strlen will only count up but not include the null terminator
    size_t input_len = strlen(input);
    //explicitly adding one byte for the null terminator
    char *lexer_input = malloc(sizeof(char)*(input_len+1));
    //memory allocating just for the size of the lexer should be enough since pointers are constant size
    Lexer *lexer = malloc(sizeof(Lexer));
    //copying the chars from input parameter into lexer_input (including null terminator)
    strcpy(lexer_input, input);
    lexer->input = lexer_input;
    lexer->position = 0;
    lexer->read_position = 0;
    lexer_read_char(lexer);
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
            if(isalpha(lexer->ch) || lexer->ch == '_'){
                // int position = lexer->position;
                // while (isalpha(lexer->ch) || lexer->ch == '_'){
                //     lexer_read_char(lexer);
                // }
                // int identifier_length = lexer->position - position;
                // char *token_literal = malloc(sizeof(char)*(identifier_length+1));
                // for(int i = 0; i < identifier_length; i++){
                //     token_literal[i] = lexer->input[position+i];    
                // }
                // token_literal[identifier_length] = '\0';
                char *literal = get_identifier_or_keyword_literal(lexer);
                printf("Possible identifier or keyword literal: %s\n", literal);
                TokenType type = get_identifier_or_keyword_type(literal);
                printf("token type linked to the literal found: %s\n", type);
                token = new_token(type, literal);
            }
            else{
                token = new_token(ILLEGAL, "illegal");
            }
            break;
    }
    lexer_read_char(lexer);
    return token;
}

char *get_identifier_or_keyword_literal(Lexer *lexer){
    int position = lexer->position;
    while (isalpha(lexer->ch) || lexer->ch == '_'){
        lexer_read_char(lexer);
    }
    int identifier_or_keyword_length = lexer->position - position;
    char *identifier_or_keyword = malloc(sizeof(char)*(identifier_or_keyword_length+1));
    for(int i = 0; i < identifier_or_keyword_length; i++){
        identifier_or_keyword[i] = lexer->input[position+i];    
    }
    identifier_or_keyword[identifier_or_keyword_length] = '\0';
    return identifier_or_keyword;
}

TokenType get_identifier_or_keyword_type(char *identifier_or_keyword_literal){
    size_t keyword_count = sizeof(keywords)/sizeof(Item);
    for(int i = 0; i < (int) keyword_count; i++){
        if(strcmp(identifier_or_keyword_literal, keywords[i].key) == 0){
            return keywords[i].value;
        }
    }
    return IDENT;
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
