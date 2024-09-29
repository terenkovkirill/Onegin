#include <TXLib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Reading.h"



struct TextData ReadingFile(const char *file_name)               //  ReadFile считывает данные из файла и запихивает нужные значения в структуру
{
    FILE *text_file = fopen(file_name, "rb");
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
    int file_descriptor = fileno(text_file);           //GetFileSize
    fstat(file_descriptor, &file_data);
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
