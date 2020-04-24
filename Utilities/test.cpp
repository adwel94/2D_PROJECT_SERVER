#include <iostream>
#include <process.h>
#include <Windows.h>




int main()
{

	
}

int j_printf(char* afmt, ...)
{
    int afmt_index = 0;
    int arg_index = 1;
    int afmt_len;
    int i;
    char t;
    char c;
    char* p;
    char tmp[11]; //int형의 최대크기의 길이는 10자리수 이므로
    int tmp_index;
    int in;
    va_list sarg;
    va_start(sarg, afmt); //뒤쪽 인수를 가리키기위한 초기화
    for (i = 0; afmt[i]; i++)
    {
        if (afmt[i] == '%')
        {
            i++;
            switch (afmt[i])
            {
            case 'c': //문자
                c = (char)va_arg(sarg, char);
                putchar(c);
                break;

            case 's': //문자열
                p = (char*)va_arg(sarg, char*);
                while (*p != '\0')
                {
                    putchar(*p);
                    p++;
                }
                break;

            case 'd': //정수형
                in = (int)va_arg(sarg, int);
                tmp_index = 0;

                while (in) //ASCII to integer
                {
                    tmp[tmp_index] = (in % 10) + '0';
                    in /= 10;
                    tmp_index++;
                }

                tmp_index--; //마지막 배열을 가리키도록 인덱스 값의 1을 빼줌

                while (tmp_index >= 0)
                {
                    putchar(tmp[tmp_index]);
                    tmp_index--;
                }
                break;

            }

        }
        else {
            putchar(afmt[i]);
        }
    }
    va_end(sarg);
    return 0;
}