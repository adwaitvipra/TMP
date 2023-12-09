#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *tokenTypeLabels[] = {
    "KEYWORD", "IDENTIFIER", "INTEGER", "OPERATOR", "OPENING_BRACKET", "CLOSING_BRACKET", "SEMICOLON", "LITERAL", "UNKNOWN"
};

typedef enum {
    KEYWORD, IDENTIFIER, INTEGER, OPERATOR, OPENING_BRACKET, CLOSING_BRACKET, SEMICOLON, LITERAL, UNKNOWN
} TokenType;

const char *keywords[] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "main"};

typedef struct {
    TokenType type;
    char value[100];
} Token;


int isKeyword(const char *word) {
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int tokenizeProgram(const char *program, int line, Token *tokens, int tokenCount) {
    int index = 0;
    int programLength = strlen(program);
    int inString = 0;

    while (index < programLength) {
        while (isspace(program[index])) {
            index++;
        }

        if (isalpha(program[index]) || program[index] == '_') {
            int j = 0;
            while (isalnum(program[index]) || program[index] == '_') {
                tokens[tokenCount].value[j++] = program[index++];
            }
            tokens[tokenCount].value[j] = '\0';
            tokens[tokenCount].type = isKeyword(tokens[tokenCount].value) ? KEYWORD : IDENTIFIER;
            tokenCount++;
        } else if (isdigit(program[index])) {
            int j = 0;
            while (isdigit(program[index])) {
                tokens[tokenCount].value[j++] = program[index++];
            }
            tokens[tokenCount].value[j] = '\0';
            tokens[tokenCount].type = INTEGER;
            tokenCount++;
        } else if (strchr("+-*/=<>!%", program[index]) != NULL) {
            tokens[tokenCount].value[0] = program[index++];
            tokens[tokenCount].value[1] = '\0';
            tokens[tokenCount].type = OPERATOR;
            tokenCount++;
        } else if (strchr("({", program[index]) != NULL) {
            tokens[tokenCount].value[0] = program[index++];
            tokens[tokenCount].value[1] = '\0';
            tokens[tokenCount].type = OPENING_BRACKET;
            tokenCount++;
        } else if (strchr(")}", program[index]) != NULL) {
            tokens[tokenCount].value[0] = program[index++];
            tokens[tokenCount].value[1] = '\0';
            tokens[tokenCount].type = CLOSING_BRACKET;
            tokenCount++;
        } else if (strchr(";", program[index]) != NULL) {
            tokens[tokenCount].value[0] = program[index++];
            tokens[tokenCount].value[1] = '\0';
            tokens[tokenCount].type = SEMICOLON;
            tokenCount++;
        } else if (program[index] == '"' && !inString) {
            int j = 0;
            tokens[tokenCount].value[j++] = program[index++];
            while (program[index] != '"' && index < programLength) {
                tokens[tokenCount].value[j++] = program[index++];
            }
            if (program[index] == '"') {
                tokens[tokenCount].value[j++] = program[index++];
            }
            tokens[tokenCount].value[j] = '\0';
            tokens[tokenCount].type = LITERAL;
            tokenCount++;
        } else {
            tokens[tokenCount].value[0] = program[index++];
            tokens[tokenCount].value[1] = '\0';
            tokens[tokenCount].type = UNKNOWN;
            tokenCount++;
        }
    }
    return tokenCount;
}

void writeTokensToFile(FILE *outputFile, Token *tokens, int tokenCount, int line) {
    for (int i = 0; i < tokenCount; i++) {
    fprintf(outputFile, "ln : %d\t\t", line);
        fprintf(outputFile, "token : %d\t\tclass : %24s\t\tlexeme : %s\n", i + 1, tokenTypeLabels[tokens[i].type], tokens[i].value);
    }
    fprintf(outputFile, "\n");
}

int main(const int argc, const char *argv[])
{
    Token tokens[4096];
    int tokenCount = 0;
    char lines[128][1024];
    int numLines = 0;

    FILE *inputFile = fopen ("input.txt", "r");

    if (inputFile == NULL) {
        perror("input file error");
        return 1;
    }

    while (numLines < 100 && fgets(lines[numLines], 1000, inputFile) != NULL) {
        lines[numLines][strcspn(lines[numLines], "\n")] = '\0';
        numLines++;
    }

    fclose(inputFile);

    FILE *outputFile = fopen("output.txt", "w");

    if (outputFile == NULL) {
        perror("output file error");
        return 1;
    }

    for (int i = 0; i < numLines; i++) {
        tokenCount = tokenizeProgram(lines[i], i + 1, tokens, tokenCount);
        writeTokensToFile(outputFile, tokens, tokenCount, i + 1);
        tokenCount = 0; // Reset token count for the next line
    }

    fclose(outputFile);

    printf("success!\n");

    return 0;
}
