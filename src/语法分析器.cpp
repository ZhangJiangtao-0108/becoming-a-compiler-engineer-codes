#include<stdio.h>
#include<ctype.h>//ctype.h��C��׼�������е�ͷ�ļ���������һ��C�����ַ����ຯ�������ڲ����ַ��Ƿ������ض����ַ����
#include<conio.h>//conio.h���ļ�������ͨ������̨���������������������ĺ�������Ҫ��һЩ�û�ͨ�������̲����Ķ�Ӧ����
#include<string.h>
#include<stdlib.h>
#define keywordSum 9
//�ַ���ָ�����鱣�汣���֣����䵽9��char�����Ķ���
char *keyword[keywordSum] = { "if","else","for","while","do","read","write","char","int" };//return,switch,case,break,continue
//�����ֽ�����Ķ���
char singleword[50] = { '+','-','*','(',')','{','}',',',';',':' ,'.'};
//˫�ֽ��������ĸ
char doubleword[10] = { '>','<','=','!' };
//���롢����ļ���
char Scanin[300], Scanout[300],Result[300];
//ָ���ļ���ָ��
FILE *fin, *fout,*fp,*fr;
char token[20], token1[40];//token���浥�ʷ��ţ�token1���浥��ֵ

//��������
int TESTscan();
int TESTparse();
int program();
int declaration_list();
int statement_list();
int if_stat();
int while_stat();
int for_stat();
int write_stat();
int read_stat();
int declaration_stat();
int compound_stat();
int expression_stat();
int statement();
int expression();
int bool_expr();
int additive_expr();
int term();
int factor();

//�ʷ���������
int TESTscan() {//����1�������ļ����󣻷���2������ļ����󣻷���3���Ƿ����ţ�
	char ch;//ÿ�ζ�����ַ�
	char token[40];//����ʶ��ĵ���
	int es = 0, j, n;//esΪ0��ʾ�޴���
	printf("������Դ�����ļ���������·������");
	scanf("%s", Scanin);
	getchar();
	printf("������ʷ���������ļ���������·������");
	scanf("%s", Scanout);
	getchar();
	if ((fin = fopen(Scanin, "r")) == NULL)
	{
		printf("\n�򿪴ʷ����������ļ�����\n");
		return(1);
	}
	if ((fout = fopen(Scanout, "w")) == NULL)
	{
		printf("\n�����ʷ���������ļ�����\n");
		return(2);
	}
	ch = getc(fin);//���ļ��ж�ȡ�ַ�
	while (ch != EOF)//�ļ�δ����ʱ
	{
		while (ch == ' ' || ch == '\n' || ch == '\t')//�˹��ո��ת���ַ�
			ch = getc(fin);
		//�ж��Ƿ���ʶ������Ǳ�����
		if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z' || ch == '_')//������һ���»��ߣ����Ķ���
		{
			token[0] = ch;
			j = 1;
			ch = getc(fin);
			while (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z' || ch == '_' || ch >= '0'&&ch <= '9')
			{
				token[j++] = ch;
				ch = getc(fin);
			}
			token[j] = '\0';
			//���Ƿ�Ϊ������
			n = 0;
			while ((n<keywordSum) && strcmp(token, keyword[n]))
				n++;
			if (n >= keywordSum)//���Ǳ�����
				fprintf(fout, "%s\t%s\n", "ID", token);
			else
				fprintf(fout, "%s\t%s\n", token, token);
		}
		//����
		else if (ch >= '0'&&ch <= '9')
		{
			token[0] = ch;
			j = 1;
			ch = getc(fin);
			while (ch >= '0'&&ch <= '9')
			{
				token[j++] = ch;
				ch = getc(fin);
			}
			token[j] = '\0';
			fprintf(fout, "%s\t%s\n", "NUM", token);
		}
		//�������
		else if (strchr(singleword, ch) > 0)//�����ַ���s���״γ����ַ�ch��λ��,�����״γ���ch��λ�õ�ָ�룬���s�в�����ch�򷵻�NULL��
		{
			token[0] = ch;
			token[1] = '\0';
			ch = getc(fin);
			fprintf(fout, "%s\t%s\n", token, token);
		}
		//˫�ֽ��
		else if (strchr(doubleword, ch) > 0)
		{
			token[0] = ch;
			ch = getc(fin);
			if (ch == '=')
			{
				token[1] = ch;
				token[2] = '\0';
				ch = getc(fin);
			}
			else
				token[1] = '\0';
			fprintf(fout, "%s\t%s\n", token, token);
		}
		//ע�ʹ���
		else if (ch == '/')
		{
			ch = getc(fin);
			if (ch == '*')
			{
				char ch1;
				ch1 = getc(fin);
				do
				{
					ch = ch1;
					ch1 = getc(fin);
				} while ((ch != '*' || ch1 != '/') && ch1 != EOF);
				ch = getc(fin);
			}
			else
			{
				token[0] = '/';
				token[1] = '\0';
				fprintf(fout, "%s\t%s\n", token, token);
			}

		}
		//������
		else
		{
			token[0] = ch;
			token[1] = '\0';
			ch = getc(fin);//��������ʶ����һ�����ʡ�
			es = 3;
			fprintf(fout, "%s\t%s\n", "ERROR", token);
		}
	}
	fclose(fin);
	fclose(fout);
	return(es);
}

//�﷨��������
int TESTparse() 
{
	
	int es = 0;
	if ((fp = fopen(Scanout, "r")) == NULL)
	{
		printf("\n�򿪴ʷ���������ļ�����\n");
		es=10;
	}
	printf("�������﷨��������ļ���������·������");
	scanf("%s", Result);
	if ((fr = fopen(Result, "w")) == NULL)
	{
		printf("\n���﷨��������ļ�����\n");
		return(8);
	}
	if (es == 0)
		es = program();
	printf("\n�﷨����������£�\n");
	switch (es)
	{
	case 0:
		printf("�﷨�����ɹ���\n");
		fprintf(fr,"\n%s\n","�﷨�����ɹ���\n");
		break;
	case 1:
		printf("ȱ��{\n");
		fprintf(fr, "\n%s\n", "ȱ��{\n");
		break;
	case 2:
		printf("ȱ��}\n");
		fprintf(fr, "\n%s\n", "ȱ��}\n");
		break;
	case 3:
		printf("ȱ��ʶ���\n");//declaration_stat()
		fprintf(fr, "\n%s\n", "ȱ��ʶ���\n");
		break;
	case 4:
		printf("ȱ�ٷֺ�\n");
		fprintf(fr, "\n%s\n", "ȱ�ٷֺ�\n");
		break;
	case 5:
		printf("ȱ��(\n");
		fprintf(fr, "\n%s\n", "ȱ�٣�\n");
		break;
	case 6:
		printf("ȱ��)\n");
		fprintf(fr, "\n%s\n", "ȱ�٣�\n");
		break;
	case 7:
		printf("ȱ�ٲ�����\n");//factor()
		fprintf(fr, "\n%s\n", "ȱ�ٲ�����\n");
		break;
	case 8:
		printf("\n���﷨��������ļ�����\n");
		fprintf(fr, "\n%s\n", "\n���﷨��������ļ�����\n");
		break;
	case 10:
		printf("\n�򿪴ʷ���������ļ�����\n");
		fprintf(fr, "\n%s\n", "\n�򿪴ʷ���������ļ�����\n");
		break;
	}
	fclose(fp);
	fclose(fr);
	return(es);
}

//���� �Ӻ���
int program() 
{
	int es = 0;
	fscanf(fp,"%s\t%s\n",&token,&token1);//�����ļ�������
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, "{"))//���ʱ�����ء�0������ִ�и���䣬�Ƚϵ���token
	{
		es = 1;
		return es;
	}
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = declaration_list();//fscanf��printf�����������Ӻ�����
	if (es > 0)
		return(es);
	es = statement_list();
	if (es > 0)
		return(es);
	if (strcmp(token, "}"))
	{
		es = 2;
		return(es);
	}
	return(es);
}

int declaration_list() 
{
	int es = 0;
	while ((strcmp(token,"int")==0)||(strcmp(token,"char")==0))//������char��
	{
		es = declaration_stat();
		if (es > 0)
			return(es);
	}
	return(es);
}

int declaration_stat() 
{
	int es = 0;
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, "ID"))
		return(es=3);//ȱ��ʶ���
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, ";"))
		return(es = 4);
	fscanf(fp, "%s\t%s\n", &token, &token1);//����һ��token�������ж�declaration_list()��ѭ������
	fprintf(fr, "%s\t%s\n", &token, &token1);
	return(es);
}

int statement_list() 
{
	int es = 0;
	while (strcmp(token, "}"))//��ɨ�赽token�ǡ�}��ʱ��while��0��,����䲻ִ�У���������statement�ˡ�program������
		                      //���program()��������
	{
		es = statement();
		if (es > 0)
			return(es);
	}
	return(es);
}

int compound_stat() 
{
	int es = 0;
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = statement_list();
	return(es);
}

int statement()
{
	int es = 0;
	if (es == 0 && strcmp(token, "if") == 0)
	{
		fprintf(fr, "\n%s\n", "\n---if���---\n");
		printf("\nԴ�������if���\n");
		es = if_stat();
	}
	if (es == 0 && strcmp(token, "while") == 0)
		{
		fprintf(fr, "\n%s\n", "\n---while���---\n");
			printf("\nԴ�������while���\n");
			es = while_stat();
		}
	if (es == 0 && strcmp(token, "for") == 0)
		{
		fprintf(fr, "\n%s\n", "\n---for���---\n");
			printf("\nԴ�������for���\n");
			es = for_stat();
		}
	if (es == 0 && strcmp(token, "read") == 0)
		{
		fprintf(fr, "\n%s\n", "\n---read���---\n");
			printf("\nԴ�������read���\n");
			es = read_stat();
		}
	if (es == 0 && strcmp(token, "write") == 0)
		{
		fprintf(fr, "\n%s\n", "\n---write���---\n");
			printf("\nԴ�������write���\n");
			es = write_stat();
		}
	if (es == 0 && strcmp(token, "{") == 0)
		{
		fprintf(fr, "\n%s\n", "\n---�������---\n");
			printf("\nԴ������ڸ������\n");
			es = compound_stat();
		}
	if (es == 0 && strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0)
		{
		
			printf("\nԴ������ڱ��ʽ���\n");
			es = expression_stat();
		}
	return(es);
}

int if_stat(){
    int es=0;
	
    fscanf(fp,"%s\t%s\n",&token,&token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
    if(strcmp(token,"("))    
		return(es=5);
    fscanf(fp,"%s\t%s\n",&token,&token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
    es=expression();
    if(es>0) 
		return(es);
    if(strcmp(token,")"))    
		return(es=6);
    fscanf(fp,"%s\t%s\n",&token,&token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
    es=statement();
    if(es>0) 
		return(es);
    if(strcmp(token,"else")==0)
    {
      fscanf(fp,"%s\t%s\n",&token,&token1);
	  fprintf(fr, "%s\t%s\n", &token, &token1);
      es=statement();
      if(es>0) 
		  return(es);
    }
    return(es);
}

int while_stat()
{
	int es = 0;
	
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, "(")) 
		return(es = 5);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = expression();
	if (es>0)
		return(es);
	if (strcmp(token, ")")) 
		return(es = 6);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = statement();
	return(es);
}

int for_stat()
{
	int es = 0;
	
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, "(")) 
		return(es = 5);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = expression();
	if (es>0) 
		return(es);
	if (strcmp(token, ";")) 
		return(es = 4);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = expression();
	if (es>0) 
		return(es);
	if (strcmp(token, ";")) 
		return(es = 4);
	fscanf(fp, "%s\t%s\n",&token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = expression();
	if (es>0) 
		return(es);
	if (strcmp(token, ")")) 
		return(es = 6);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = statement();

	return(es);
}

int write_stat()
{
	int es = 0;
	
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	es = expression();
	if (es>0) 
		return(es);
	if (strcmp(token, ";")) 
		return(es = 4);
	fscanf(fp, "%s\t%s\n", &token, &token1); 
	fprintf(fr, "%s\t%s\n", &token, &token1);
	return(es);
}

int read_stat()
{
	int es = 0;
	
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, "ID")) 
		return(es = 3);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	if (strcmp(token, ";")) 
		return(es = 4);
	fscanf(fp, "%s\t%s\n", &token, &token1);
	fprintf(fr, "%s\t%s\n", &token, &token1);
	return (es);
}

int expression_stat()
{
	int es = 0;
	if (strcmp(token, ";") == 0)
	{
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
		return(es);
	}
	es = expression();
	if (es > 0)
		return(es);
	if (es == 0 && strcmp(token, ";") == 0) 
	{
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
		return(es);
	}
	else
	{
		es = 4;
		return(es);//ȱ�٣�
	}
}

int expression()
{
	int es = 0, fileadd;
	char token2[20], token3[40];
	if (strcmp(token, "ID") == 0)
	{
		fileadd = ftell(fp);
		fscanf(fp, "%s\t%s\n", &token2, &token3);
		fprintf(fr, "%s\t%s\n", &token2, &token3);
		if (strcmp(token2, "=") == 0)
		{
			fscanf(fp, "%s\t%s\n", &token, &token1);
			fprintf(fr, "%s\t%s\n", &token, &token1);
			es = bool_expr();
			if (es>0)
				return(es);
		}
		else
		{
			fseek(fp, fileadd, 0);
			  
			es = bool_expr();
			if (es>0)
				return(es);
		}
	}
	else
		es = bool_expr();
	return(es);
}

int bool_expr()
{
	int es = 0;
	es = additive_expr();
	if (es>0)
		return(es);
	if (strcmp(token, ">") == 0 || strcmp(token, ">=") == 0 || strcmp(token, "<") == 0 || strcmp(token, "<=") == 0 || strcmp(token, "==") == 0 || strcmp(token, "!=") == 0)
	{
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
		es = additive_expr();
		if (es>0)
			return(es);
	}
	return(es);
}

int additive_expr(){
	int es = 0;
	es = term();
	if (es>0) 
		return(es);
	while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0)
	{
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
		es = term();
		if (es>0) return(es);
	}
	return(es);
}

int term(){
	int es = 0;
	es = factor();
	if (es>0) 
		return(es);
	while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0)
	{
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
		es = factor();
		if (es>0) 
			return(es);
	}
	return(es);
}

int factor(){
	int es = 0;
	if (strcmp(token, "(") == 0)
	{
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
		es = expression();
		if (es>0) 
			return(es);
		if (strcmp(token, ")")) 
			return(es = 6);
		fscanf(fp, "%s\t%s\n", &token, &token1);
		fprintf(fr, "%s\t%s\n", &token, &token1);
	}
	else
	{
		if (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0)
		{
			fscanf(fp, "%s\t%s\n", &token, &token1);
			fprintf(fr, "%s\t%s\n", &token, &token1);
			return(es);
		}
		else
		{
			es = 7;
			return(es);
		}
	}
	return(es);
}

//������
int main() 
{
	int es = 0;
	es = TESTscan();
	switch (es) {//switch�����ϸ���ʹ������
	case 0:
		printf("�ʷ������ɹ���\n");
		break;
	case 1:
		printf("�����ļ��д�����ֹͣ��\n");
		break;
	case 2:
		printf("����ļ��д�����ֹͣ��\n");
		break;
	case 3:
		printf("���ڷǷ����ţ�����ֹͣ��\n");
		break;
	}
	if (es == 0) 
	{
		es = TESTparse();
		if (es == 0)
			printf("�﷨�����ɹ���\n");
		else
			printf("�﷨��������\n");
	}
	system("pause");
	return 0; 
}

