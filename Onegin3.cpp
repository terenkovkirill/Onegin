#include <TXLib.h>                    //в отдельной функции сортируем строки обычного прямогоугольного  массива
#include <stdio.h>
#include <math.h>
#include <ctype.h>

const int SIZE_Y = 18;
const int SIZE_X = 90;
void ChangePlaceMaxLine(char *text, int limiter, int *index);

int main()
{
    char text[SIZE_Y][SIZE_X] =    {"My uncle used to be so sound",             //0
                                    "But after falling gravely ill",            //1
                                    "Is craving homage, and has found",         //2
                                    "That could not make a better deal.",       //3
                                    "It is for others a good lesson,",          //4
                                    "But what a boredom is the session:",       //5
                                    "To watch a sick man day and night",        //6
                                    "And do not make a step aside!",            //7
                                    "What mean deceitfulness it is:",           //8
                                    "To feign compassion, dose the drugs,",     //9
                                    "To set and fluff the pillows, thus,",      //10
                                    "To entertain a half deceased,",            //11
                                    "To show fake sympathy, then, sigh",        //12
                                    "And think: Oh gosh, when will you die!",   //13
                                    "It was what a young rake expected,",       //14
                                    "When dusting post-chaise speeded him,",    //15
                                    "By Zeus’s supreme will elected",           //16
                                    "The only heir of all his kin."};           //17

    for (int i = 0; i < SIZE_Y; i++)
    {
        printf( "--%s \n", text[i]);
    }
    printf("\n\n");

    int index[SIZE_Y];          //создаём массив индексов
    for (int i = 0; i < SIZE_Y; i++)
    {
        index[i] = i;
    }

    int limiter = SIZE_Y - 1;
    while (limiter > 0)      //SIZE_Y - 1 раз отправляем max строчку в конец
    {
        ChangePlaceMaxLine((char *)text, limiter, index);
        limiter--;
    }

    for (int i = 0; i < SIZE_Y; i++)
    {
        printf("--%s \n", text[index[i]]);
    }

    return 0;
}


void ChangePlaceMaxLine(char* text, int limiter, int *index)
{
    int temp = 0;
    for (int i = 0; i < limiter; i++)
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            if (*(text + *(index + i) * SIZE_X + j) < *(text + *(index + i + 1) * SIZE_X + j))
            {
                //printf("left: %d, right: %d \n", *(index + i), *(index + i + 1));
                //printf("left: %c, right: %c, %d \n", *(text + i * SIZE_X + j), *(text + (i + 1) * SIZE_X + j), j);
                break;
            }

            if (*(text + *(index + i) * SIZE_X + j) > *(text + *(index + i + 1) * SIZE_X + j))     //меняет индексы двух отличающихся строк местами
            {
                //printf("1 left_old: %d, right_old: %d \n", *(index + i), *(index + i + 1));
                temp =  *(index + i);
                *(index + i) = *(index + i + 1);
                *(index + i + 1) = temp;
                //printf("2 left_new: %d, right_new: %d \n", *(index + i), *(index + i + 1));
                break;
            }
        }
    }
}
