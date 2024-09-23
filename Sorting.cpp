#include <TXLib.h>
#include <stdio.h>
#include <ctype.h>

#include "Sorting.h"


void BubbleSort(char** dinamic_text, int count_str)
{
    assert(dinamic_text != NULL);

    char* temp = 0;

    for (int i = 0; i < count_str - 1; i++)
    {
        assert(0 <= i && i < count_str);          //нужны ли эти assert?
        assert(0 <= i + 1 && i + 1 < count_str);
        for (int j = 0; j < count_str - 1 - i; j++)
        {
            if (DirectComparator(dinamic_text, j) == INVALID_LOCATION)
            {
                //printf("left_old: %s, right_old: %s, %d \n", dinamic_text[j], dinamic_text[j + 1]);
                //printf("left_new: %s, right_new: %s, %d \n", dinamic_text[j + 1], dinamic_text[j]);
                temp =  *(dinamic_text + j);
                *(dinamic_text + j) = *(dinamic_text + j + 1);
                *(dinamic_text + j + 1) = temp;
            }
        }
    }
}





int DirectComparator(char** dinamic_text, int j)
{
    int space1 = 0, space2 = 0;
    for (int k = 0; k < SIZE_X; k++)
    {
        space1 = space1 + isspace(dinamic_text[j][k + space1]);
        space2 = space2 + isspace(dinamic_text[j + 1][k + space2]);

        if (CompareLetters(dinamic_text[j][k + space1], dinamic_text[j + 1][k + space2]) == RIGHT_LOCATION)
        {
            //printf("left: %s, right: %s, %d \n", dinamic_text[j], dinamic_text[j+1]);
            break;
        }

        if ((CompareLetters(dinamic_text[j][k + space1], dinamic_text[j + 1][k + space2])) == INVALID_LOCATION)     //меняет индексы двух отличающихся строк местами
        {
            return INVALID_LOCATION;
        }
    }

    return RIGHT_LOCATION;
}


int CompareLetters(int dinamic_text_j_k1, int dinamic_text_j1_k2)
{
    if (tolower(dinamic_text_j_k1) < tolower(dinamic_text_j1_k2))
    {
        return RIGHT_LOCATION;
    }

    else if (tolower(dinamic_text_j_k1) > tolower(dinamic_text_j1_k2))
    {
        return INVALID_LOCATION;
    }

    else
    {
        return 0;
    }

}
