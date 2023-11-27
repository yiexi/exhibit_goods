/***************************************************
> Copyright (C) 2023 ==KINGYI== All rights reserved.
> File Name: user_client.c
> Author:cor
> Mail:cor_02@163.com 
> Created Time: 2023年11月17日 星期五 16时33分37秒
***************************************************/

#include "exhibit_goods.h"
#include "user_client.h"

CONTAINER *goods_buy(CONTAINER*head)//购买
{
	CONTAINER* temp=head;
	char verify[10]={0};	//验证信息
	int key=0;		//退出死循环钥匙	
	int id=0;
	int flag=0;
	while(1)
	{
		printf("请输入商品编号\n");
		scanf("%d",&id);
		temp=find_id(temp,id,0);
		if(temp!=NULL)
		{
			printf("请输入'Y'or'N'\n");
			scanf("%s",verify);	//确认信息
			if(strcmp(verify,"Y") == 0||strcmp(verify,"y") == 0)
			{
				//具体修改的内容					
				temp->number=temp->number-1;
				key=1;	//修改成功
			}
		}	
		if(key==1)
		{	//判断是否修改成功
			break;	
		}
		else
		{
			printf("Input error\n""Please input again\n");
		}
	}
	goodsInfo_write_file(head);
	return head;
}

