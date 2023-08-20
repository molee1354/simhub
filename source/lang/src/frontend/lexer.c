#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "frontend.h"

Token* token(char* word, TokenType t_type) {
    Token* out = (Token*)malloc(sizeof(Token));
    out->value = strdup(word);
    out->type = t_type;

    return out;
}

/**
 * @brief Function to determine if a word is a reserved word
 * 
 * @param word character array to check if it's reserved
 * @return TokenType 
 */
TokenType wordType(char* word) {
    if (!strcmp(word, "let")) {
        return Let;

    // add if-else statements for different keywords
    } else {
        return Identifier;
    }
}

/**
 * @brief Function to determine if the character is skippable (whitespace)
 * 
 * @param c current character
 * @return int 
 */
int isSkippable(char c) {
    return c=='\n' || c=='\t' || c==' ';
}

Array* tokenize(char* sourceCode, int srcSize) {
    Array* out = makeArray();
    
    for (int i = 0; i < srcSize; i++) {
        char currentChar = sourceCode[i];

        if (currentChar == '(') {
            Token* t = token("(", OpenParen);
            append(out, *t);
            free(t);
        } else if ( currentChar == ')') {
            Token* t = token(")", CloseParen);
            append(out, *t);
            free(t);

        } else if ( currentChar == '*' ) {
            Token* t = token("*", BinaryOperator);
            append(out, *t);
            free(t);
        } else if ( currentChar == '+' ) {
            Token* t = token("+", BinaryOperator);
            append(out, *t);
            free(t);
        } else if ( currentChar == '-' ) {
            Token* t = token("-", BinaryOperator);
            append(out, *t);
            free(t);
        } else if ( currentChar == '/' ) {
            Token* t = token("/", BinaryOperator);
            append(out, *t);
            free(t);

        } else if ( currentChar == '=' ) {
            Token* t = token("=", Equals);
            append(out, *t);
            free(t);

        } else if ( currentChar == ';' ){
            Token* t = token("EndOfLine", EndOfLine);
            append(out, *t);
            free(t);

        } else {
            // handling multicharacter tokens

            // Numbers
            if (isdigit(currentChar)) {
                int numStart = i;
                int numEnd = numStart;
                int numLen = 0;

                // determining the indices where the number is
                while (isdigit(sourceCode[numEnd])) {
                    numLen++;
                    numEnd++;
                }
                char* num = (char*)malloc((numLen+1)*sizeof(char));

                // setting the token value from number index
                for (int j=numStart, jj=0; j < numEnd; j++) {
                    num[jj] = sourceCode[j];
                    jj++;
                }
                num[numLen] = '\0';
                Token* t = token(num, Number);
                append(out, *t);
                free(num);
                free(t);
                i = numEnd-1;
            }

            // Alphabetic
            else if (isalpha(currentChar)) {
                int wordStart = i;
                int wordEnd = wordStart;
                int wordLen = 0;

                // determining the indices where the number is
                while (isalpha(sourceCode[wordEnd])) {
                    wordLen++;
                    wordEnd++;
                }
                char* word = (char*)malloc((wordLen+1)*sizeof(char));

                // setting the token value from wordber index
                for (int j=wordStart, jj=0; j < wordEnd; j++) {
                    word[jj] = sourceCode[j];
                    jj++;
                }
                word[wordLen] = '\0';
                Token* t = token(word, wordType(word));
                append(out, *t);
                free(word);
                free(t);
                i = wordEnd-1;
            }

            // Handling whitespace, newlines, tabs
            else if ( isSkippable(currentChar) ) {
                continue;
            }

            // Unhandled characters
            else {
                fprintf(stderr, "Unhandled character found in source : ");
                printf("\"%c\"\n", currentChar);
                // exit(1);
            }
        }
    }
    Token* eof = token("EndOfFile", EndOfFile);
    append(out, *eof);
    free(eof);

    return out;
}
