#include <TXLib.h>
#include <stdio.h>
#include "Reading.h"

enum Direct {
    RIGHT_LOCATION = 1,
    INVALID_LOCATION = 2,
    BEGIN_STR = 1000000,
    SIMPLE_ELEM = - 1000000,
};

void BubbleSort(char** dinamic_text, int count_str);
int DirectComparator(char* str1, char* str2);
int CompareLetters(int dinamic_text_i_j, int dinamic_text_i1_j);
void PrintText(char** dinamic_text, int count_str);
