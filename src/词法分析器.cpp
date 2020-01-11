#include <stdio.h>
#include <string.h>
#define norw 13         /*�ؼ��ָ���*/
#define nmax 14         //number�����λ��
#define al 10           //���ŵ���ĳ��� ���ž���+ - �����
#define cxmax 200       //���������������

enum symbol {
    nul, ident, number, plus, minus, times, slash, oddsym, eql, neq,
    lss, leq, gtr, geq, lparen, rparen, comma, semicolon, period, becomes,
    beginsym, endsym, ifsym, thensym, whilesym, writesym, readsym, dosym,
    callsym, constsym, varsym, procsym,
};

FILE* fa1;              //����������ļ����׵�ַ �׵�ַ�������ָ��
char ch;                //getch��ȡ���ַ�
enum symbol sym;
char id[al+1];          //��ǰ��ident
int num;
int cc, ll;             //getch������
int cx;                 //���������ָ�룬ȡֵ��Χ0-cxmax-1
char line[81];
char a[al+1];           //��ȡһ������ ��ʱ��������
char word[norw][al];    //������13�� ����begin end if ʲô��
//enum symbol wsym[norw]; //�����ֶ�Ӧ�ķ��� begin��Ӧbeginsym
enum symbol ssym[256];  //���ַ��ķ���ֵ
 
FILE* fin;
FILE* fout;
char fname[al];         //������ļ���
int err;
 
#define getchdo         if(-1==getch()) return -1;
 
void error(int n);
 
void error(int n)
{
    char space[81];
    memset(space, 32, 81);
    space[cc-1] = 0;
    printf("****���ִ���\n");
    fprintf(fa1, "****���ִ���\n");
    err++;
}
int getch()
{
    if(cc == ll)
    {
        if(feof(fin))
        {
            printf("\n�����ˣ�\n");
            return -1;
        }
        ll = 0;
        cc = 0;
        //printf("%d ", cx);
        //fprintf(fa1, "%d", cx);
        ch = ' ';
        while(ch != 10)
        {
            if(fscanf(fin, "%c", &ch) == EOF)
            {
                line[ll] = 0;
                break;
            }
            printf("%c", ch);
            line[ll] = ch;
            ll++;
        }
        printf("\n");
    }
    ch = line[cc];
    cc++;
    return 0;
}
 
int getsym()
{
    int i, j, k;
    while(ch == ' ' || ch == 10 || ch == 9||ch== 13)
    {
        getchdo;
    }
    if(ch >= 'a' && ch <= 'z')
    {
        k = 0;
        do
        {
            if(k < al)
            {
                a[k] = ch;
                k++;
            }
            getchdo;
        }while(ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9');
        a[k] = '\0';
        strcpy(id, a);
        i = 0;
        j = norw-1;
        do
        {
            k = (i+j)/2;
            if(strcmp(id, word[k]) <= 0)
                j = k-1;
            if(strcmp(id, word[k]) >= 0)
                i = k+1;
        }while(i <= j);
 
        if(i-1 > j)
        {
            printf("������ (1,'%s')\n", id);
        }
        else
        {
            printf("��ʶ�� (3,'%s')\n", id);
        }
    }
    else
    {
        if(ch >= '0' && ch <= '9')
        {
            k = 0;
            num = 0;
            //sym = number;
            do
            {
                num = num * 10 + ch - '0';
                k++;
                getchdo;
            }while(ch >= '0' && ch <= '9');
            k--;
            if(k > nmax)
            {
                error(30);
            }
            printf("��  �� (2,'%d')\n",num);
        }
        else
        {
            if(ch == ':')
            {
                getchdo;
                //k=0;
                //b[k]=ch;
                if(ch == '=')
                {
                    //sym = becomes;
                    printf("����� (4,':=')\n");
                    getchdo;
                }
                else
                {
                     printf("error!��������ʹ�á�����\n");
                }
            }
            else
            {
                if(ch == '<')
                {
                    getchdo;
                    if(ch == '=')
                    {
                        printf("����� (4,'<=')\n");
                        getchdo;
                    }
                    else
                    {
                        printf("����� (4,'<')\n");
                    }
                }
                else
                {
                    if(ch == '>')
                    {
                        getchdo;
                        if(ch == '=')
                        {
                            printf("����� (4,'>=')\n");
                            getchdo;
                        }
                        else
                        {
                            printf("����� (4,'>')\n");
                        }
                    }
                    else
                    {
                        if(ch=='+')
                        {
                            printf("����� (4,'+')\n");
                            getchdo;
                        }
                        else if(ch=='-')
                        {
                            printf("����� (4,'-')\n");
                            getchdo;
                        }
                        else if(ch=='*')
                        {
                            printf("����� (4,'*')\n");
                            getchdo;
                        }
                        else if(ch=='/')
                        {
                            printf("����� (4,'/')\n");
                            getchdo;
                        }
                        else if(ch=='#')
                        {
                            printf("����� (4,'#')\n");
                            getchdo;
                        }
                        else if(ch=='!')
                        {
                            printf("����� (4,'!')\n");
                            getchdo;
                        }
                        else if(ch=='(')
                        {
                            printf("�ֽ�� (5,'(')\n");
                            getchdo;
                        }
                        else if(ch==')')
                        {
                            printf("�ֽ�� (5,')')\n");
                            getchdo;
                        }
                        else if(ch==',')
                        {
                            printf("�ֽ�� (5,',')\n");
                            getchdo;
                        }
                        else if(ch==';')
                        {
                            printf("�ֽ�� (5,';')\n");
                            getchdo;
                        }
                        else if(ch=='.')
                        {
                            printf("�ֽ�� (5,'.')\n");
                            getchdo;
                        }
                        else if(ch=='{')
						{
							printf("�ֽ�� (5,'{')\n");
                        	getchdo;	
						} 
						else if(ch=='}')
						{
							printf("�ֽ�� (5,'}')\n");
                        	getchdo;	
						} 
						else if(ch==';')
						{
							printf("�ֽ�� (5,';')\n");
                        	getchdo;	
						} 
						else if(ch=='"')
						{
							printf("�ֽ�� (5,'\"')\n");
                        	getchdo;	
						} 
                        else
                        {
                            printf("error!��������Ƿ�ƴд��ȷ��\n");
                            return -1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
void init()
{
    
    int i;
    for(i = 0; i < 256; i++)
        ssym[i] =  nul;
    ssym['+'] = plus;
    ssym['-'] = minus;
    ssym['*'] = times;
    ssym['/'] = slash;
    ssym['('] = lparen;
    ssym[')'] = rparen;
    ssym['='] = eql;
    ssym[','] = comma;
    ssym['.'] = period;
    ssym['#'] = neq;
    ssym[';'] = semicolon;

    strcpy(&(word[0][0]), "begin");
    strcpy(&(word[1][0]), "call");
    strcpy(&(word[2][0]), "const");
    strcpy(&(word[3][0]), "do");
    strcpy(&(word[4][0]), "end");
    strcpy(&(word[5][0]), "if");
    strcpy(&(word[6][0]), "odd");
    strcpy(&(word[7][0]), "procedure");
    strcpy(&(word[8][0]), "read");
    strcpy(&(word[9][0]), "then");
    strcpy(&(word[10][0]), "var");
    strcpy(&(word[11][0]), "while");
    strcpy(&(word[12][0]), "write");
/*
    wsym[0] = beginsym;
    wsym[1] = callsym;
    wsym[2] = constsym;
    wsym[3] = dosym;
    wsym[4] = endsym;
    wsym[5] = ifsym;
    wsym[6] = oddsym;
    wsym[7] = procsym;
    wsym[8] = readsym;
    wsym[9] = thensym;
    wsym[10] = varsym;
    wsym[11] = whilesym;
    wsym[12] = writesym;
*/
 
}
int main()
{
    printf("������Ҫ�������ļ�����\n");
    scanf("%s", fname);
    fin = fopen(fname, "r");
    if(fin)
    {
        /*
        printf("������Ҫ������ļ���\n");
        scanf("%s", fname);
        fa1 = fopen(fname, "w");
        */
 
        init();
        printf("\n������ϣ�\n\n");
        err = 0;
        cc = cx = ll = 0;
        ch = ' ';
        while(getsym() != -1)
        {
            //printf("111\n");
        }
 
 
    }
    else
    {
        printf("�Ҳ����ļ�\n");
    }
    printf("\n");
    return 0;
}

