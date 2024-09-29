#ifndef READING_H
#define READING_H
#include <TXLib.h>
#include <stdio.h>


struct TextData
{
    char** dinamic_text;
    int count_str;
};

int CalculationLen(FILE *text_file);
int CounterStrings(char* buffer, long file_len);
void SetPointer(char** dinamic_text, char* buffer, long file_len, int count_str);
struct TextData ReadingFile(const char* file_name);


#endif


