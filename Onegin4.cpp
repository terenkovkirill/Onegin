#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

enum Direct {
    SIZE_X = 90,
    RIGHT_LOCATION = 1,
    INVALID_LOCATION = 2,
    BEGIN_STR = 1000000,
    SIMPLE_ELEM = - 1000000,
};

void BubbleSort(char** dinamic_text, int count_str);
void ChangePlaceMaxLine(char** dinamic_text, int limiter, int count_str);
int CompareLetters(int dinamic_text_i_j, int dinamic_text_i1_j);
void PrintText(char** dinamic_text, int count_str);


int main()
{
    FILE *text_file = fopen("Onegin_text.txt", "rb");
    assert(text_file != NULL);

    fseek(text_file, 0, SEEK_END);                //вычисляем длину файла
    long file_len = ftell(text_file);
    fseek(text_file, 0, SEEK_SET);

    char* buffer = (char *)calloc(file_len, sizeof(char));
    fread(buffer, sizeof(char), file_len, text_file);           //считываем файл в Buffer
    fclose(text_file);

    int count_str = 0;                          //считаем кол-во строк (\n)
    for(int i = 0; i < file_len - 1; i++)
    {
        if (buffer[i] == '\n')
        {
            count_str++;
        }
    }


    char** dinamic_text = 0;
    dinamic_text = (char **)calloc(count_str, sizeof(char*));
    assert(dinamic_text != NULL);

    *dinamic_text = buffer;

    int num_ptr = 0;
    for (int i = 0; i < file_len - 1; i++)
    {
        assert(0 <= i && i < file_len);
        assert(0 <= i + 1 && i + 1 < file_len);

        if (buffer[i] == '\r')
        {
            buffer[i] = '\0';
        }

        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            num_ptr++;
            *(dinamic_text + num_ptr) = buffer + i + 1;
        }
    }


    PrintText((char **)dinamic_text, count_str);

    printf("\n\n\n\n\n\n\n");

    BubbleSort((char **)dinamic_text, count_str);
    //qsort(dinamic_text, count_str, sizeof(char *), strcmp);

    PrintText((char **)dinamic_text, count_str);


    return 0;
}



void BubbleSort(char** dinamic_text, int count_str)
{
    assert(dinamic_text != NULL);

    int limiter = count_str - 1;
    while (limiter > 0)      //SIZE_Y - 1 раз отправляем max строчку в конец
    {
        ChangePlaceMaxLine(dinamic_text, limiter, count_str);
        limiter--;
    }
}



void ChangePlaceMaxLine(char** dinamic_text, int limiter, int count_str)
{
    assert(dinamic_text != NULL);
    char* temp = 0;

    for (int i = 0; i < limiter; i++)
    {
        assert(0 <= i && i < count_str);          //нужны ли эти assert?
        assert(0 <= i + 1 && i + 1 < count_str);

        int space1 = 0, space2 = 0;
        for (int j = 0; j < SIZE_X; j++)
        {
            space1 = space1 + isspace(dinamic_text[i][j + space1]);
            space2 = space2 + isspace(dinamic_text[i + 1][j + space2]);

            if (CompareLetters(dinamic_text[i][j + space1], dinamic_text[i + 1][j + space2]) == RIGHT_LOCATION)
            {
                //printf("left: %s, right: %s, %d \n", dinamic_text[i], dinamic_text[i+1], j);
                break;
            }

            if ((CompareLetters(dinamic_text[i][j + space1], dinamic_text[i + 1][j + space2])) == INVALID_LOCATION)     //меняет индексы двух отличающихся строк местами
            {
                temp =  *(dinamic_text + i);
                *(dinamic_text + i) = *(dinamic_text + i + 1);
                *(dinamic_text + i + 1) = temp;
                //printf("left_old: %s, right_old: %s, %d \n", dinamic_text[i], dinamic_text[i + 1], j);
                //printf("left_new: %s, right_new: %s, %d \n", dinamic_text[i + 1], dinamic_text[i], j);
                break;
            }
        }
    }
}




int CompareLetters(int dinamic_text_i_j1, int dinamic_text_i1_j2)
{
    if (tolower(dinamic_text_i_j1) < tolower(dinamic_text_i1_j2))
    {
        return RIGHT_LOCATION;
    }

    else if (tolower(dinamic_text_i_j1) > tolower(dinamic_text_i1_j2))
    {
        return INVALID_LOCATION;
    }

    else
    {
        return 0;
    }

}


void PrintText(char** dinamic_text, int count_str)
{
    assert(dinamic_text != NULL);

    for (int i = 0; i < count_str; i++)
    {
        printf("%s", dinamic_text[i]);
        printf("\n");
    }
}

/*
char** dinamic_text = (char **)calloc(...)    //указатель на массив указателей
dinamic_text[1] := *(dinamic_text + 1)        //указатель на первую строку в массиве
dinamic_text[1][2] := *(*(dinamic_text + 1) + 2)
*/


//правильно ли я записал flag?
// все ли assert я поставил

//проблема с isalnum (невозможно пропустить пробел в одной строке и не пропустить символ в другой)
//todo: разность ASCII-кодов букв вместо их сравнения
