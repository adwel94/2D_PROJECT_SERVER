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
    char tmp[11]; //int���� �ִ�ũ���� ���̴� 10�ڸ��� �̹Ƿ�
    int tmp_index;
    int in;
    va_list sarg;
    va_start(sarg, afmt); //���� �μ��� ����Ű������ �ʱ�ȭ
    for (i = 0; afmt[i]; i++)
    {
        if (afmt[i] == '%')
        {
            i++;
            switch (afmt[i])
            {
            case 'c': //����
                c = (char)va_arg(sarg, char);
                putchar(c);
                break;

            case 's': //���ڿ�
                p = (char*)va_arg(sarg, char*);
                while (*p != '\0')
                {
                    putchar(*p);
                    p++;
                }
                break;

            case 'd': //������
                in = (int)va_arg(sarg, int);
                tmp_index = 0;

                while (in) //ASCII to integer
                {
                    tmp[tmp_index] = (in % 10) + '0';
                    in /= 10;
                    tmp_index++;
                }

                tmp_index--; //������ �迭�� ����Ű���� �ε��� ���� 1�� ����

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