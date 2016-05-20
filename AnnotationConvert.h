#ifndef __ANNOTATION_CONVERT_H__
#define __ANNOTATION_CONVERT_H__

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

#define READ_FILE_NAME "input.c"
#define WRITE_FILE_NAME "output.c"

typedef enum STATE
{
	NUL_STATE,
	C_STATE,
	CPP_STATE,
	END_STATE
}STATE;

void DoConvertWork(char *readfile,char *writefile);
void AnnotationConvert();

#endif  //__ANNOTATION_CONVERT_H__
