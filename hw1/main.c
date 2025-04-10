#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_SIZE 128

void printToken(const char* lexeme, const char* tokenType) {
    printf("%s: %s\n", lexeme, tokenType);
}

// 輔助函式：判斷是否為字母 (不使用 <ctype.h>)
int isLetter(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

// 輔助函式：判斷是否為數字
int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int main() {
    FILE* file = fopen(__FILE__, "r");
    if (file == NULL) {
        printf("Cannot open file\n");
        return 1;
    }
    
    int ch;
    char token[MAX_TOKEN_SIZE];
    
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t')
            continue;
        
        // 處理以字母開頭的 token：識別符或關鍵字
        if (isLetter(ch)) {
            int pos = 0;
            token[pos++] = (char)ch;
            while ((ch = fgetc(file)) != EOF && (isLetter(ch) || isDigit(ch))) {
                if (pos < MAX_TOKEN_SIZE - 1)
                    token[pos++] = (char)ch;
            }
            token[pos] = '\0';
            if (ch != EOF)
                ungetc(ch, file);
            // 判斷是否為預定義關鍵字
            if (strcmp(token, "int") == 0) {
                printToken(token, "TYPE_TOKEN");
            } else if (strcmp(token, "main") == 0) {
                printToken(token, "MAIN_TOKEN");
            } else if (strcmp(token, "if") == 0) {
                printToken(token, "IF_TOKEN");
            } else if (strcmp(token, "else") == 0) {
                printToken(token, "ELSE_TOKEN");
            } else if (strcmp(token, "while") == 0) {
                printToken(token, "WHILE_TOKEN");
            } else {
                printToken(token, "ID_TOKEN");
            }
        }
        // 處理數字 token (只辨識整數)
        else if (isDigit(ch)) {
            int pos = 0;
            token[pos++] = (char)ch;
            while ((ch = fgetc(file)) != EOF && isDigit(ch)) {
                if (pos < MAX_TOKEN_SIZE - 1)
                    token[pos++] = (char)ch;
            }
            token[pos] = '\0';
            if (ch != EOF)
                ungetc(ch, file);
            printToken(token, "LITERAL_TOKEN");
        }
        // 處理運算子與符號
        else {
            if (ch == '=') {
                int next = fgetc(file);
                if (next == '=') {
                    printToken("==", "EQUAL_TOKEN");
                } else {
                    if (next != EOF)
                        ungetc(next, file);
                    printToken("=", "ASSIGN_TOKEN");
                }
            } else if (ch == '>') {
                int next = fgetc(file);
                if (next == '=') {
                    printToken(">=", "GREATEREQUAL_TOKEN");
                } else {
                    if (next != EOF)
                        ungetc(next, file);
                    printToken(">", "GREATER_TOKEN");
                }
            } else if (ch == '<') {
                int next = fgetc(file);
                if (next == '=') {
                    printToken("<=", "LESSEQUAL_TOKEN");
                } else {
                    if (next != EOF)
                        ungetc(next, file);
                    printToken("<", "LESS_TOKEN");
                }
            } else if (ch == '+') {
                printToken("+", "PLUS_TOKEN");
            } else if (ch == '-') {
                printToken("-", "MINUS_TOKEN");
            } else if (ch == '(') {
                printToken("(", "LEFTPAREN_TOKEN");
            } else if (ch == ')') {
                printToken(")", "REFTPAREN_TOKEN");
            } else if (ch == '{') {
                printToken("{", "LEFTBRACE_TOKEN");
            } else if (ch == '}') {
                printToken("}", "REFTBRACE_TOKEN");
            } else if (ch == ';') {
                printToken(";", "SEMICOLON_TOKEN");
            }
            // 對於其他未列出的符號，可視需求忽略或擴充
        }
    }
    
    fclose(file);
    return 0;
}
