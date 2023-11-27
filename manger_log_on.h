/***************************************************
> Copyright (C) 2023 ==KINGYI== All rights reserved.
> File Name: manger_log_on.h
> Author:cor
> Mail:cor_02@163.com 
> Created Time: 2023年11月16日 星期四 14时31分25秒
***************************************************/

#ifndef _MANGER_LOG_ON_H_
#define _MANGER_LOG_ON_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct The_users
{
	char id[20];
	char name[20];
	char pwd[20];
	struct The_users* next;
} Users;
void Creat();
void GetDataFromTxt(Users* data, const char* filename, int* n);
void login_first();
#endif
