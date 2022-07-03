#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student
{
	long Id; //学号
	char Name[10]; //姓名
	char Sex; //性别
	int Age; //年龄
	char Note[100]; //备注
	struct student *next;
};
struct student* Input_Information(struct student *head,int n);
struct student* Look_Up(struct student *head,long id); //如果链表中有学号为id的学生，则返回该结点的地址
void Printf_Link(struct student *head); //打印学生信息
void Save_to_File(struct student *head,int n); //将学生信息保存到电脑
struct student* Ouput_from_File(struct student *head,int *pn);
struct student* Delete_Information(struct student *head,int *pn); //*pn是学生个数
void Change_Information(struct student *head);
void Find_Information(struct student *head,int n); //n代表学生个数
void Find_Information_Id(struct student *head,int n);
void Find_Information_Name(struct student *head,int n);
void Find_Information_Sex(struct student *head,int n);
void Find_Information_Age(struct student *head,int n);
void DelteMemory(struct student **head);
int main()
{
	char Real_secret[]="123456";
	char secret[20];
	struct student *head=NULL;
	int sum=0; //记录学生总数  
	int i;
	int *pn=&sum;
    int choice;
	printf("请输入密码:");
	again:scanf("%s",secret); 
    if(!strcmp(secret,Real_secret))
    {
		do
		{
			printf("请选择系统功能项:\n\
	1.学生基本信息录入\n\
	2.学生基本信息显示\n\
	3.学生基本信息保存\n\
    4.读取学生基本信息\n\
	5.学生基本信息删除\n\
	6.学生基本信息修改（要求先输入密码）\n\
	7.学生基本信息查询\n\
	8.退出系统\n");
			scanf("%d%*c",&choice);
            switch (choice)
            {
                case 1:
					if(sum)
					{
						DelteMemory(&head);
					}
                    printf("请输入学生数量:");
                    scanf("%d",&sum);
					{
						for(i=1;i<=sum;i++)
						{
							head=Input_Information(head,i);
						}
					}
                    break;
				case 2:
					Printf_Link(head);
					break;                
				case 3:
					Save_to_File(head,sum);
					break;
                case 4:
					Ouput_from_File(head,pn);
                    break;
                case 5:
					head=Delete_Information(head,pn);
					break;
				case 6:
					Change_Information(head);
					break;
				case 7:
					Find_Information(head,sum);
					break;
				case 8:
					DelteMemory(&head);
					break;
                default:
					printf("输入错误!\n");
                    break;
            }
        }while(choice!=8);
    }
    else
    {
        printf("输入错误!\n");
        printf("请重新输入:");
        goto again;
    }
}
struct student* Input_Information(struct student *head,int n)
{
	struct student *p=NULL,*q=head;
    struct student *temp;
	p=(struct student*)malloc(sizeof(struct student));
	if(head==NULL)
	{
		head=p;
        head->Id=0; //为Look_Up函数提供服务
	}
	else
	{
		while(q->next!=NULL)
		{
			q=q->next;
		}
		q->next=p;
	}
	printf("请输入第%d位学生的学号:",n);
	again:scanf("%ld",&(p->Id));
    temp=Look_Up(head,p->Id);
    if(!temp)
    {
        printf("与(%d)%s冲突\n",temp->Id,temp->Name);
        printf("请重新输入第%d位学生的学号:",n);
        goto again;
    }
	printf("请输入第%d位学生的姓名:",n);
	scanf("%s%*c",p->Name);
	printf("请输入第%d位学生的性别:",n);
	scanf("%c%*c",&(p->Sex));
	printf("请输入第%d位学生的年龄:",n);
	scanf("%d%*c",&(p->Age));
	printf("请输入第%d位学生的备注:",n);
	scanf("%s%*c",p->Note);
	printf("%d\t%s\t%c\t%d\t%s\n",p->Id,p->Name,p->Sex,p->Age,p->Note);
	p->next=NULL;
	return head;
}
void Printf_Link(struct student *head)
{
	struct student *p=head;
	while(p!=NULL)
	{
		printf("%ld\t%s\t%c\t%d\t%s\n",p->Id,p->Name,p->Sex
		,p->Age,p->Note);
		p=p->next;
	}
}
void Save_to_File(struct student *head,int n)
{
	struct student *p=head;
	FILE *fp=NULL;
	int i;
	fp=fopen("F:\\学生信息文档.txt","w");
	fprintf(fp,"学生数量:%d\n",n);
	for(i=1;i<=n;i++)
	{
		fprintf(fp,"%ld\t%s\t%c\t%d\t%s\n",p->Id,p->Name,
		p->Sex,p->Age,p->Note);
		p=p->next;
	}
	printf("保存成功!\n");
	fclose(fp);
}
struct student* Ouput_from_File(struct student *head,int *pn)
{
	if(*pn)
	{
		DelteMemory(&head);
		*pn=0;
	}
	FILE *fp=NULL;
	struct student *p=head,*q;
	head=(struct student*)malloc(sizeof(struct student));
	head->next=NULL;
	int i;
	fp=fopen("F:\\学生信息文档.txt","r");
	fscanf(fp,"学生数量:%d\n",pn);
	for(i=1;i<=*pn;i++)
	{
		q=(struct student*)malloc(sizeof(struct student));
		fscanf(fp,"%ld\t%s\t%c\t%d\t%s\n",&q->Id,q->Name,&q->Sex
		,&q->Age,q->Note);
		p->next=q;
		p=p->next;
		q->next=NULL;
	}
	return head;
}
struct student* Delete_Information(struct student *head,int *pn)
{
	long id;
	struct student *p=head,*temp=NULL;
	printf("请输入你需要删除学生的学号:");
	scanf("%ld%*c",&id);
    temp=Look_Up(head,id);
	if(temp)
	{
		if(p==head)
		{
			head=p->next;
		}
		else
		{
			temp->next=p->next;
		}
		(*pn)--; //删除学生后，学生总数减1
		free(p);
	}
	else
	{
		printf("没有找到该学号!\n");
	}
	return head;
}
void Change_Information(struct student *head)
{
	char Real_secret[]="123456";
	char secret[20];
	long id;
	int ch;
	struct student *position=NULL,*temp;
	printf("请输入密码:");
	scanf("%s",secret);
	if(!strcmp(secret,Real_secret))
	{
		printf("请输入需要修改信息的学生学号:");
		scanf("%ld",&id);
		position=Look_Up(head,id);   //获取到学生在链表上的位置 
		if(position==NULL)
		{
			printf("没有找到该学号的学生!\n");
		}
		else
		{
			do
			{
				printf("%ld\t%s\t%c\t%d\t%s\n",position->Id
				,position->Name,position->Sex,position->Age,
				position->Note);
				printf("请选择你需要修改的信息:\n\
	(1)学号\n\
	(2)姓名\n\
	(3)性别\n\
	(4)年龄\n\
	(5)备注\n\
	(6)退出");
				scanf("%d",&ch);
				switch(ch)
				{
					case 1:
						printf("请输入学号:");
						again:scanf("%ld%*c",&id);
						temp=Look_Up(head,id);
						if(temp==position)
						{
							printf("修改后的学号(%d)与没修改之前相同\n",position->Id);
						}
						else if(temp!=NULL)
						{
							printf("与(%d)%s冲突\n",temp->Id,temp->Name);
							printf("请重新输入:");
							goto again;
						}
						else
						{
							position->Id=id;
							printf("修改成功\n");
						}
						break;
					case 2:
						printf("请输入名字:");
						scanf("%s%*c",position->Name);
						printf("修改成功\n");
						break;
					case 3:
						printf("请输入性别:");
						scanf("%c%*c",&position->Sex);
						printf("修改成功\n");
						break;
					case 4:
						printf("请输入年龄:");
						scanf("%d%*c",&position->Age);
						printf("修改成功\n");
						break;
					case 5:
						printf("请输入备注:");
						scanf("%s%*c",position->Note);
						printf("修改成功\n");
						break;
					case 6:
						printf("谢谢!\n");
						break;
					default:
						printf("输入错误!\n");
						break;
				}
				printf("%d\t%s\t%c\t%d\t%s\n",position->Id,position->Name,position->Sex,position->Age,
				position->Note);
			} while (ch!=6);
		}
	}
	else
	{
		printf("密码输入错误!\n");
	}
}
void Find_Information(struct student *head,int n)
{
	int ch;
	do
	{
		printf("请选择查询方式:\n\
	(1)按学号查询\n\
	(2)按姓名查询\n\
	(3)按性别查询\n\
	(4)按年龄查询\n\
	(5)退出");
		scanf("%d%*c",&ch);
		switch(ch)
		{
			case 1:
				Find_Information_Id(head,n);
				break;
			case 2:
				Find_Information_Name(head,n);
				break;
			case 3:
				Find_Information_Sex(head,n);
				break;
			case 4:
				Find_Information_Age(head,n);
				break;
			case 5:
				printf("谢谢!\n");
				break;
			default:
				printf("输入错误!\n");
				break;
		}
	} while (ch!=5);
}
void Find_Information_Id(struct student *head,int n)
{
	int i; 
	int id;
	int flag=0;
	struct student *p=head;
	printf("请输入学号:");
	scanf("%d",&id);
	for(i=0;i<n;i++)
	{
		if(id==(p->Id))
		{
			flag=1;
			printf("%ld\t%s\t%c\t%d\t%s\n",p->Id,p->Name,p->Sex
			,p->Age,p->Note);	
		}
		p=p->next;
	}
	if(!flag)
	{
		printf("没有找到该学号!\n");
	}
}
void Find_Information_Name(struct student *head,int n)
{
	int i;
	int flag=0; 
	char name[10];
	struct student *p=head;
	printf("请输入名字:");
	scanf("%s",name);
	for(i=0;i<n;i++)
	{
		if(!strcmp(name,p->Name))
		{
			flag=1;
			printf("%ld\t%s\t%c\t%d\t%s\n",p->Id,p->Name,p->Sex
			,p->Age,p->Note);			
		}
		p=p->next;
	}
	if(!flag)
	{
		printf("没有找到该姓名!\n");
	}	
} 
void Find_Information_Sex(struct student *head,int n)
{
	struct student *p=head;
	int i;
	char sex;
	int flag=0;
	printf("请输入性别:");
	scanf(" %c",&sex);
	for(i=0;i<n;i++)
	{
		if(sex==(p->Sex))
		{
			flag=1;
			printf("%ld\t%s\t%c\t%d\t%s\n",p->Id,p->Name,p->Sex
			,p->Age,p->Note);	
		}
		p=p->next;
	}
	if(!flag)
	{
		printf("没有找到该性别!\n");
	}		
}
void Find_Information_Age(struct student *head,int n)
{
	struct student *p=head;
	int flag=0;
	int i;
	int age;
	printf("请输入年龄:");
	scanf("%d",&age);
	for(i=0;i<n;i++)
	{
		if(age==(p->Age))
		{
			flag=1;
			printf("%ld\t%s\t%c\t%d\t%s\n",p->Id,p->Name,p->Sex
			,p->Age,p->Note);			
		}
		p=p->next;
	}
	if(!flag)
	{
		printf("没有找到该年龄!\n");
	}	
}
void DelteMemory(struct student **head)
{
	struct student *p=NULL,*temp=*head;
	while(temp!=NULL)
	{
		p=temp;
		temp=temp->next;
		free(p);
	}
	*head=NULL;
}
struct student* Look_Up(struct student *head,long id)
{
	struct student *p=head;
	while(p!=NULL&&id!=(p->Id))  //寻找学生的位置 
	{
		p=p->next;
	}
	return p;
}