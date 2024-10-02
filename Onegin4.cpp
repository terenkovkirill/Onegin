#include <TXLib.h>
#include <stdio.h>
#include <ctype.h>
//#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Reading.h"
#include "Sorting.h"


int main(int argc, const char* argv[])
{
    printf("%d", argc);
    /*
    if (argc != 3)
    {
        puts("Wrong number of elements.");
        assert(0);
    }
    */

    struct TextData data_fromfile =  ReadingFile(argv[1]);

    PrintText(data_fromfile.dinamic_text, data_fromfile.count_str);

    printf("\n\n\n\n\n\n\n");

    BubbleSort(data_fromfile.dinamic_text, data_fromfile.count_str);
    //qsort(dinamic_text, count_str, sizeof(char *), strcmp);

    WriteFile(data_fromfile.dinamic_text, data_fromfile.count_str, argv[2]);

    return 0;
}



void PrintText(char** dinamic_text, int count_str)
{
    assert(dinamic_text != NULL);

    for (int i = 0; i < count_str; i++)
    {
        printf("%s \n", dinamic_text[i]);
    }
}

void WriteFile(char** dinamic_text, int count_str, const char* filename)
{
    assert(dinamic_text != NULL);

    FILE* fileptr = fopen(filename, "wb");

    for (int i = 0; i < count_str; i++)
    {
        printf("%s \n", dinamic_text[i]);

        size_t len_string = strlen(dinamic_text[i]);
        fwrite(dinamic_text[i], sizeof(dinamic_text[i][0]), len_string, fileptr);       //fprinf();
    }
}

/*
char** dinamic_text = (char **)calloc(...)    //указатель на массив указателей
dinamic_text[1] := *(dinamic_text + 1)        //указатель на первую строку в массиве
dinamic_text[1][2] := *(*(dinamic_text + 1) + 2)
*/



// все ли assert я поставил

//проблема с isalnum (невозможно пропустить пробел в одной строке и не пропустить символ в другой)
//todo: разность ASCII-кодов букв вместо их сравнения
