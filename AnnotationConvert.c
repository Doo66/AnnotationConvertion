#include "AnnotationConvert.h"

//STATE
STATE g_state = NUL_STATE;

void DoNulState(FILE *pfRead,FILE *pfWrite)
{
	int first = 0;
	int second = 0;
	first = fgetc(pfRead);
	switch (first)
	{
	case '/':
		second = fgetc(pfRead);
		if (second == '*')
		{
			fputc('/', pfWrite);
			fputc('/', pfWrite);
			g_state = C_STATE;
		}
		else if (second == '/')
		{
			fputc(first, pfWrite);
			fputc(second, pfWrite);
			 g_state = CPP_STATE;
		}
		else
		{
			fputc(first, pfWrite);
			fputc(second, pfWrite);
		}
		break;
	case EOF:
		g_state = END_STATE;
		break;
	default:
		fputc(first, pfWrite);
		break;
	}
	
}
void DoCState(FILE *pfRead,FILE *pfWrite)
{
	int first = 0;
	int second = 0;
	first = fgetc(pfRead);
	switch(first)
	{
	case '*':
		second = fgetc(pfRead);
		if (second == '/')
		{
			 int next = fgetc(pfRead);
			 if (next != '\n')
			 {
				 fputc('\n', pfWrite);
				 fputc(next, pfWrite);
			 }
			 else
			 {
				 fputc(next,pfWrite);
			 }
			g_state = NUL_STATE;
		}
		else
		{
			fputc(first, pfWrite);
			ungetc(second, pfRead);
		}
		break;
	case '\n':
		fputc(first, pfWrite);
		fputc('/', pfWrite);
		fputc('/', pfWrite);
		break;
	case EOF:
		g_state = END_STATE;
		break;
	default:
		fputc(first, pfWrite);
	}	
}
void DoCppState(FILE *pfRead,FILE *pfWrite)
{
	int first = 0;
	first = fgetc(pfRead);
	switch(first)
	{
	case '\n':
		fputc(first, pfWrite);
		g_state = NUL_STATE;
		break;
	case EOF:
		g_state = END_STATE;
		break;
	default:
		fputc(first, pfWrite);
	}
}
void DoConvertWork(char *readfile,char *writefile)
{
   FILE* pfRead = NULL;
   FILE* pfWrite = NULL;
   pfRead = fopen(readfile,"r");
   if (pfRead == NULL)
   {
	   perror("open file for read");
	   exit(EXIT_FAILURE);
   }
   pfWrite = fopen(writefile,"w");
   if (pfWrite == NULL)
   {
	   fclose(pfRead);
	   perror("open file for write");
	   exit(EXIT_FAILURE);
   }
   //×ª»»
   while (g_state != END_STATE)
   {
		switch (g_state)
		{
		case NUL_STATE:
			DoNulState(pfRead,pfWrite);
			break;
		case C_STATE:
			DoCState(pfRead,pfWrite);
			break;
		case CPP_STATE:
			DoCppState(pfRead,pfWrite);
			break;
		case END_STATE:
			return;
		}
   }
   fclose(pfRead);
   fclose(pfWrite);

}
void AnnotationConvert()
{
	DoConvertWork(READ_FILE_NAME,WRITE_FILE_NAME);
}