#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

enum Direct {
    SIZE_Y = 18,
    SIZE_X = 90,
    RIGHT_LOCATION = 1,
    INVALID_LOCATION = 2,
};

void BubbleSort(char** dinamic_text);
void ChangePlaceMaxLine(char** dinamic_text, int limiter);
int CompareLetters(int dinamic_text_i_j, int dinamic_text_i1_j);
void PrintText(char** dinamic_text);


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


    char** dinamic_text = 0;
    dinamic_text = (char **)calloc(SIZE_X * SIZE_Y, sizeof(char));    //создаём и заполняем динамический массив

    for (int i = 0; i < SIZE_Y; i++)
    {
        int size_line = sizeof(text[i]) / sizeof(text[i][0]);

        dinamic_text[i] = (char *)calloc(size_line, sizeof(char));
        assert(dinamic_text[i] != NULL);

        for (int j = 0; j < size_line; j++)
        {
            dinamic_text[i][j] = text[i][j];
        }
    }

    PrintText((char **)dinamic_text);

    printf("\n \n");

    BubbleSort((char **)dinamic_text);

    PrintText((char **)dinamic_text);

    return 0;
}



void BubbleSort(char** dinamic_text)
{
    assert(dinamic_text != NULL);

    int limiter = SIZE_Y - 1;
    while (limiter > 0)      //SIZE_Y - 1 раз отправляем max строчку в конец
    {
        ChangePlaceMaxLine(dinamic_text, limiter);
        limiter--;
    }
}



void ChangePlaceMaxLine(char** dinamic_text, int limiter)
{
    assert(dinamic_text != NULL);
    char* temp = 0;

    for (int i = 0; i < limiter; i++)
    {
        assert(0 <= i && i< SIZE_Y);          //нужны ли эти assert?
        assert(0 <= i + 1 && i + 1 < SIZE_Y);
        for (int j = 0; j < SIZE_X; j++)
        {
            if (CompareLetters(dinamic_text[i][j], dinamic_text[i+1][j]) == RIGHT_LOCATION)
            {
                break;
            }

            if ((CompareLetters(dinamic_text[i][j], dinamic_text[i+1][j])) == INVALID_LOCATION)     //меняет индексы двух отличающихся строк местами
            {
                temp =  *(dinamic_text + i);
                *(dinamic_text + i) = *(dinamic_text + i + 1);
                *(dinamic_text + i + 1) = temp;
                break;
            }
        }
    }
}




int CompareLetters(int dinamic_text_i_j, int dinamic_text_i1_j)
{
    if (isalnum(dinamic_text_i_j) && isalnum(dinamic_text_i1_j))
    {
        if (tolower(dinamic_text_i_j) < tolower(dinamic_text_i1_j))
        {
            return RIGHT_LOCATION;
        }

        else if (tolower(dinamic_text_i_j) > tolower(dinamic_text_i1_j))
        {
            return INVALID_LOCATION;
        }

        else
        {
            return 0;
        }
    }

    else
    {
        return 0;
    }
}


void PrintText(char** dinamic_text)
{
    assert(dinamic_text != NULL);

    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            printf("%c", dinamic_text[i][j]);
        }
        printf("\n");
    }
}




//проблема с isalnum (невозможно пропустить пробел в одной строке и не пропустить символ в другой)
