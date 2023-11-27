/***************************************************
> Copyright (C) 2023 ==KINGYI== All rights reserved.
> File Name: exhibit_goods.h
> Author:cor
> Mail:cor_02@163.com 
> Created Time: 2023年11月17日 星期五 16时34分07秒
***************************************************/

#ifndef _EXHIBIT_GOODS_H_
#define _EXHIBIT_GOODS_H_
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <assert.h>
#include <time.h>
#include <errno.h>

typedef struct container_system
{
	int id;
	char name[20];
	float price;
	int number;
	struct container_system* next;
}CONTAINER;
#define SIZE sizeof(CONTAINER)
CONTAINER *goods_grounding(CONTAINER*,int len);
CONTAINER *goods_off_shelf(CONTAINER*);
CONTAINER *goods_price_modify(CONTAINER*);
CONTAINER *goods_replenishment(CONTAINER*);


CONTAINER* find_id(CONTAINER*temp,int id,int len);
//末端地址
CONTAINER* find_end_point(CONTAINER*temp);
FILE* open_file_goodsInfo(const char *filename, const char *mode);
void goodsInfo_write_file(CONTAINER* head);	
CONTAINER* goodsOutput_read_file();
void goods_report_form(CONTAINER *head);

char* get_localtime(char*str);
char *get_all_info(char *info,int line,char*err,char*itime,char*fun);
void write_file(char*str);
#endif
