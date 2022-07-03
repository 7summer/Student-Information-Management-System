#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student
{
	long Id;
	char Name[10];
	char Sex;
	int Age;
	char Note[100];
	struct student *next;
};
struct student* Input_Information(struct student *head,int n);
void Printf_Link(struct student *head);
void Save_to_File(struct student *head,int n);
struct student* Delete_Information(struct student *head,int *pn);
struct student* Change_Information(struct student *head);
struct student* Look_Up(struct student *head,long id); 
//查看需要修改的学生是否存在，然后返回该学生在链表的位置 
void Change_Information_Id(long *id);
void Change_Information_Name(char *name);
void Change_Information_Sex(char *sex);
void Change_Information_Age(int *age);
void Change_Information_Note(char *note);
void Find_Information(struct student *head,int n);
void Find_Information_Id(struct student *head,int n);
void Find_Information_Name(struct student *head,int n);
void Find_Information_Sex(struct student *head,int n);
void Find_Information_Age(struct student *head,int n);
void DelteMemory(struct student *head);  //释放链表 
int main()
{
	char Real_secret[]="123456789";
	char secret[20];
	struct student *head=NULL;
	int sum=0; //记录学生总数 
	int n;  //记录录入的学生数目 
	int i;
	int *pn=&sum;
	char ch; //ch1是用来选择功能项,ch2是用来选择查询类型
	printf("请输入密码:");
	scanf("%s",secret); 
	if(!strcmp(secret,Real_secret))
	{
		printf("How many student?\n");
		scanf("%d",&n);
		sum += n;
		do
		{
			printf("请选择系统功能项：\n\
		a.学生基本信息录入\n\
		b.学生基本信息显示\n\
		c.学生基本信息保存\n\
		d.学生基本信息删除\n\
		e.学生基本信息修改（要求先输入密码）\n\
		f.学生基本信息查询\n\
			(1)按学号查询\n\
			(2)按姓名查询\n\
			(3)按性别查询\n\
			(4)按年龄查询\n\
		g. 退出系统\n");
			scanf(" %c",&ch);
			switch(ch)
			{
				case 'a':
					for(i=0;i<n;i++)
					{
						head=Input_Information(head,i);
					}
					break;
				case 'b':
					Printf_Link(head);
					break;
				case 'c':
					Save_to_File(head,sum);
					break;
				case 'd':
					head=Delete_Information(head,pn);
					break;
				case 'e':
					head=Change_Information(head);
					break;
				case 'f':
					Find_Information(head,sum);
					break;
				case 'g':
					DelteMemory(head);
					printf("已退出\n");
					break;
				default:
					printf("输入错误!\n");
					break;
			}	
		}while(ch!='g');		
	}
	else
	{
		printf("密码错误!\n");
	}
	return 0;
}
struct student* Input_Information(struct student *head,int n)
{
	struct student *p=NULL,*temp=head;
	p=(struct student*)malloc(sizeof(struct student));
	if(p==NULL)
	{
		printf("没有足够的空间!\n");
		exit(0);
	}
	if(head==NULL)
	{
		head=p;
	}
	else
	{
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=p;
	}
	printf("请输入第%d位学生的学号:",n+1);
	scanf("%ld",&(p->Id));
	printf("请输入第%d位学生的姓名:",n+1);
	scanf("%s",p->Name);
	printf("请输入第%d位学生的性别:",n+1);
	scanf(" %c",&(p->Sex));
	printf("请输入第%d位学生的年龄:",n+1);
	scanf("%d",&(p->Age));
	printf("请输入第%d位学生的备注:",n+1);
	scanf("%s",p->Note);
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
	fp=fopen("C:\\Users\\33278\\Desktop\\学生信息文档.txt","a+");
	if(fp==NULL)
	{
		printf("无法打开该文件!\n");
		exit(0);
	}
	for(i=0;i<n;i++)
	{
		fprintf(fp,"%ld\t%s\t%c\t%d\t%s\n",p->Id,p->Name,
		p->Sex,p->Age,p->Note);
		p=p->next;
	}
	printf("保存成功!\n");
	fclose(fp);
}
struct student* Delete_Information(struct student *head,int *pn)
{
	long id;
	struct student *p=head,*temp=NULL;
	printf("请输入你需要删除学生的学号:");
	scanf("%ld",&id);
	while(p->next!=NULL&&id!=(p->Id))
	{
		temp=p;
		p=p->next;
	}
	if(id==(p->Id))
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
struct student* Change_Information(struct student *head)
{
	char Real_secret[]="123456789";
	char secret[20];
	long id;
	int ch;
	struct student *position=NULL;
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
			printf("%ld\t%s\t%c\t%d\t%s\n",position->Id
			,position->Name,position->Sex,position->Age,
			position->Note);
			printf("请选择你需要修改的信息:\n\
	(1)学号\n\
	(2)姓名\n\
	(3)性别\n\
	(4)年龄\n\
	(5)备注\n");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1:
					Change_Information_Id(&(position->Id));
					printf("修改成功\n");
					break;
				case 2:
					Change_Information_Name(position->Name);
					printf("修改成功\n");
					break;
				case 3:
					Change_Information_Sex(&(position->Sex));
					printf("修改成功\n");
					break;
				case 4:
					Change_Information_Age(&(position->Age));
					printf("修改成功\n");
					break;
				case 5:
					Change_Information_Note(position->Note);
					printf("修改成功\n");
					break;
				default:
					printf("输入错误!\n");
					break;
			}
		}
	}
	else
	{
		printf("密码输入错误!\n");
	}
	return head;
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
void Change_Information_Id(long *id)
{
	printf("请输入学号:");
	scanf("%ld",id);
}
void Change_Information_Name(char *name)
{
	char str[10];
	printf("请输入名字:");
	scanf("%s",str);
	strcpy(name,str);
}
void Change_Information_Sex(char *sex)
{
	printf("请输入性别:");
	scanf(" %c",sex);
}
void Change_Information_Age(int *age)
{
	printf("请输入年龄:");
	scanf("%d",age);
}
void Change_Information_Note(char *note)
{
	char str[100];
	printf("请输入备注:");
	scanf("%s",str);
	strcpy(note,str);
}
void Find_Information(struct student *head,int n)
{
	int ch;
	printf("请选择查询方式:\n\
	(1)按学号查询\n\
	(2)按姓名查询\n\
	(3)按性别查询\n\
	(4)按年龄查询\n");
	scanf("%d",&ch);
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
		default:
			printf("输入错误!\n");
			break;
	}
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
void DelteMemory(struct student *head)
{
	struct student *p=NULL,*temp=head;
	while(temp!=NULL)
	{
		p=temp;
		temp=temp->next;
		free(p);
	}
}
