// #include "../token.c"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "lexer.h"

void delimeters_and_operators_test(void);
void add_two_numbers_test(void);
void new_operators_test(void);
void new_keywords_test(void);
void double_char_operator_test(void);
void repl(void);

int main(void){
    // delimeters_and_operators_test();
    // add_two_numbers_test();
    // new_operators_test();
    // new_keywords_test();
    // double_char_operator_test();
    repl();
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
        assert(strcmp(token->type, tests[i].type) == 0);
        assert(strcmp(token->literal, tests[i].literal) == 0);
        printf("lexer token type: %s, test token type: %s.\n", token->type, tests[i].type);
        printf("lexer token literal: %s, test token literal: %s.\n", token->literal, tests[i].literal);
        free(token->literal);
        free(token->type);
        free(token);
    }
    free(lexer->input);
    free(lexer);
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
    for(int i = 0; i < (int) test_count; i++){
        Token *token = next_token(lexer);
        assert(strcmp(token->type, tests[i].type) == 0);
        assert(strcmp(token->literal, tests[i].literal) == 0);
        printf("Test #%d passed.\n", i+1);
        printf("lexer token type: %s, test token type: %s.\n", token->type, tests[i].type);
        printf("lexer token literal: %s, test token literal: %s.\n", token->literal, tests[i].literal);
        printf("\n");
        free(token->type);
        free(token->literal);
        free(token);
    }
    //Lexer struct contains a char*, to correctly deallocate memory first free the char* then the *Lexer
    free(lexer->input);
    free(lexer);
}

void new_operators_test(void){
    char *input = "!-/*5;"
    "5 < 10 > 5;";

    Token tests[] = {
        {BANG, "!"},
        {MINUS, "-"},
        {SLASH, "/"},
        {ASTERISK, "*"},
        {INT, "5"},
        {SEMICOLON, ";"},
        {INT, "5"},
        {LT, "<"},
        {INT, "10"},
        {GT, ">"},
        {INT, "5"},
        {SEMICOLON, ";"},
    };
    size_t number_of_tests = sizeof(tests)/sizeof(Token);
    printf("input is %zu characters long", strlen(input));
    printf("number of tests to pass: %zu", number_of_tests);
    Lexer *lexer = new_lexer(input);
    for(size_t i = 0; i < number_of_tests; i++){
        Token *token = next_token(lexer);
        assert(strcmp(token->type, tests[i].type) == 0);
        assert(strcmp(token->literal, tests[i].literal) == 0);
        printf("test #%zu passed.\n", i+1);
        printf("lexer token type: %s, test token type: %s.\n", token->type, tests[i].type);
        printf("lexer token literal: %s, test token literal: %s.\n", token->literal, tests[i].literal);
        printf("\n");
        free(token->type);
        free(token->literal);
        free(token);
    }
    free(lexer->input);
    free(lexer);
}


void new_keywords_test(void){
    char *input = "if (5 < 10) {"
    " return true;"
    "   } else {"
    "return false;"
    "  }";
    Token tests[] = {
        {IF, "if"},
        {LPAREN, "("},
        {INT, "5"},
        {LT, "<"},
        {INT, "10"},
        {RPAREN, ")"},
        {LBRACE, "{"},
        {RETURN, "return"},
        {TRUE, "true"},
        {SEMICOLON, ";"},
        {RBRACE, "}"},
        {ELSE, "else"},
        {LBRACE, "{"},
        {RETURN, "return"},
        {FALSE, "false"},
        {SEMICOLON, ";"},
        {RBRACE, "}"}
    };
    size_t number_of_tests = sizeof(tests)/sizeof(Token);
    printf("input is %zu characters long\n", strlen(input));
    printf("number of tests to pass: %zu\n", number_of_tests);
    Lexer *lexer = new_lexer(input);
    for(int i = 0; i < (int) number_of_tests; i++){
        Token *token = next_token(lexer);
        assert(strcmp(token->type, tests[i].type) == 0);
        assert(strcmp(token->literal, tests[i].literal) == 0);
        printf("test #%d passed\n", i+1);
        printf("tests->type %s == token->type %s\n", tests[i].type, token->type);
        printf("tests->literal %s == token->literal %s\n", tests[i].literal, token->literal);
        free(token->literal);
        free(token->type);
        free(token);
    }
    free(lexer->input);
    free(lexer);
}

void double_char_operator_test(void){
    char *input = "10 == 10;"
    " 10 != 9;";
    Token tests[] = {
        {INT, "10"},
        {EQ, "=="},
        {INT, "10"},
        {SEMICOLON, ";"},
        {INT, "10"},
        {NOT_EQ, "!="},
        {INT, "9"},
        {SEMICOLON, ";"},
    };
    size_t number_of_tests = sizeof(tests)/sizeof(Token);
    printf("input is %zu characters long", strlen(input));
    printf("number of tests to pass: %zu.\n", number_of_tests);
    Lexer *lexer = new_lexer(input);
    for(size_t i = 0; i < number_of_tests; i++){
        Token *token = next_token(lexer);
        assert(strcmp(token->type, tests[i].type) == 0);
        assert(strcmp(token->literal, tests[i].literal) == 0);
        printf("test #%zu passed\n", i+1);
        printf("tests->type %s == token->type %s\n", tests[i].type, token->type);
        printf("tests->literal %s == token->literal %s\n", tests[i].literal, token->literal);
        free(token->type);
        free(token->literal);
        free(token);
    }
    free(lexer->input);
    free(lexer);
}

void repl(void){
    //testing a repl and limiting user input to 100 chars
    printf("REPL input is limited to 100 chars\n");
    char repl_buffer[100];
    uint8_t exit_repl = 0;
    while(exit_repl == 0){
        printf(">>");
        fgets(repl_buffer, 100, stdin);
        repl_buffer[strcspn(repl_buffer, "\n")] = '\0';
        printf("user input: %s and it's length: %zu\n", repl_buffer, strlen(repl_buffer));
        printf("is user input equal to 'exit': %d\n", strcmp(repl_buffer, "hello"));
        printf("\n");
        if(strcmp(repl_buffer, "exit") == 0){
            break;
        }
        Lexer *lexer = new_lexer(repl_buffer);
        while(lexer->ch != '\0'){
            Token *token = next_token(lexer);
            printf("{Type: %s, Literal: %s}\n", token->type, token->literal);
        }
    }
}
