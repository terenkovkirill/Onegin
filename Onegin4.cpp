#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
//#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


enum Direct {
    SIZE_X = 90,
    RIGHT_LOCATION = 1,
    INVALID_LOCATION = 2,
    BEGIN_STR = 1000000,
    SIMPLE_ELEM = - 1000000,
};

struct TextData
{
    char** dinamic_text;
    int count_str;
};

int CalculationLen(FILE *text_file);
int CounterStrings(char* buffer, long file_len);
void SetPointer(char** dinamic_text, char* buffer, long file_len, int count_str);
struct TextData ReadingFile();
void BubbleSort(char** dinamic_text, int count_str);
void ChangePlaceMaxLine(char** dinamic_text, int limiter, int count_str);
int CompareLetters(int dinamic_text_i_j, int dinamic_text_i1_j);
void PrintText(char** dinamic_text, int count_str);



int main()
{
    struct TextData news =  ReadingFile();

    PrintText(news.dinamic_text, news.count_str);

    printf("\n\n\n\n\n\n\n");

    BubbleSort(news.dinamic_text, news.count_str);
    //qsort(dinamic_text, count_str, sizeof(char *), strcmp);

    PrintText(news.dinamic_text, news.count_str);


    return 0;
}



struct TextData ReadingFile()               //считывает данные из файла и запихивает нужные значения в структуру
{
    FILE *text_file = fopen("Onegin_text.txt", "rb");
    assert(text_file != NULL);

    long file_len = CalculationLen(text_file);

    char* buffer = (char *)calloc(file_len, sizeof(char));
    fread(buffer, sizeof(char), file_len, text_file);           //считываем файл в Buffer
    fclose(text_file);

    int count_str = CounterStrings(buffer, file_len);

    char** dinamic_text = 0;                                     //адрес массива с указателями
    dinamic_text = (char **)calloc(count_str + 1, sizeof(char*));
    assert(dinamic_text != NULL);

    *dinamic_text = buffer;

    SetPointer(dinamic_text, buffer, file_len, count_str);

    struct TextData knowledge;
    knowledge.dinamic_text = dinamic_text;
    knowledge.count_str = count_str;

    return knowledge;
}




int CalculationLen(FILE *text_file)            //вычисляем длину файла
{
    struct stat file_data = {};
    int fileDescriptor = fileno(text_file);
    fstat(fileDescriptor, &file_data);
    return file_data.st_size;

    /*
    fseek(text_file, 0, SEEK_END);
    long file_len = ftell(text_file);
    fseek(text_file, 0, SEEK_SET);
    */
}



int CounterStrings(char* buffer, long file_len)
{
    int count_str = 0;                          //считаем кол-во строк (\n)
    for(int i = 0; i < file_len - 1; i++)
    {
        if (buffer[i] == '\n')
        {
            count_str++;
        }
    }

    return count_str;
}



void SetPointer(char** dinamic_text, char* buffer, long file_len, int count_str)
{
    int num_ptr = 0;
    for (int i = 0; i < file_len - 1; i++)              //расставляем указатели на строки
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
            assert(num_ptr < count_str + 1);
            *(dinamic_text + num_ptr) = buffer + i + 1;
        }
    }
}




void BubbleSort(char** dinamic_text, int count_str)
{
    assert(dinamic_text != NULL);

    int limiter = count_str - 1;
    while (limiter > 0)      //count_str - 1 раз отправляем max строчку в конец
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
