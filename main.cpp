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
//�鿴��Ҫ�޸ĵ�ѧ���Ƿ���ڣ�Ȼ�󷵻ظ�ѧ���������λ�� 
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
void DelteMemory(struct student *head);  //�ͷ����� 
int main()
{
	char Real_secret[]="123456789";
	char secret[20];
	struct student *head=NULL;
	int sum=0; //��¼ѧ������ 
	int n;  //��¼¼���ѧ����Ŀ 
	int i;
	int *pn=&sum;
	char ch; //ch1������ѡ������,ch2������ѡ���ѯ����
	printf("����������:");
	scanf("%s",secret); 
	if(!strcmp(secret,Real_secret))
	{
		printf("How many student?\n");
		scanf("%d",&n);
		sum += n;
		do
		{
			printf("��ѡ��ϵͳ�����\n\
		a.ѧ��������Ϣ¼��\n\
		b.ѧ��������Ϣ��ʾ\n\
		c.ѧ��������Ϣ����\n\
		d.ѧ��������Ϣɾ��\n\
		e.ѧ��������Ϣ�޸ģ�Ҫ�����������룩\n\
		f.ѧ��������Ϣ��ѯ\n\
			(1)��ѧ�Ų�ѯ\n\
			(2)��������ѯ\n\
			(3)���Ա��ѯ\n\
			(4)�������ѯ\n\
		g. �˳�ϵͳ\n");
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
					printf("���˳�\n");
					break;
				default:
					printf("�������!\n");
					break;
			}	
		}while(ch!='g');		
	}
	else
	{
		printf("�������!\n");
	}
	return 0;
}
struct student* Input_Information(struct student *head,int n)
{
	struct student *p=NULL,*temp=head;
	p=(struct student*)malloc(sizeof(struct student));
	if(p==NULL)
	{
		printf("û���㹻�Ŀռ�!\n");
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
	printf("�������%dλѧ����ѧ��:",n+1);
	scanf("%ld",&(p->Id));
	printf("�������%dλѧ��������:",n+1);
	scanf("%s",p->Name);
	printf("�������%dλѧ�����Ա�:",n+1);
	scanf(" %c",&(p->Sex));
	printf("�������%dλѧ��������:",n+1);
	scanf("%d",&(p->Age));
	printf("�������%dλѧ���ı�ע:",n+1);
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
	fp=fopen("C:\\Users\\33278\\Desktop\\ѧ����Ϣ�ĵ�.txt","a+");
	if(fp==NULL)
	{
		printf("�޷��򿪸��ļ�!\n");
		exit(0);
	}
	for(i=0;i<n;i++)
	{
		fprintf(fp,"%ld\t%s\t%c\t%d\t%s\n",p->Id,p->Name,
		p->Sex,p->Age,p->Note);
		p=p->next;
	}
	printf("����ɹ�!\n");
	fclose(fp);
}
struct student* Delete_Information(struct student *head,int *pn)
{
	long id;
	struct student *p=head,*temp=NULL;
	printf("����������Ҫɾ��ѧ����ѧ��:");
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
		(*pn)--; //ɾ��ѧ����ѧ��������1 
		free(p);
	}
	else
	{
		printf("û���ҵ���ѧ��!\n");
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
	printf("����������:");
	scanf("%s",secret);
	if(!strcmp(secret,Real_secret))
	{
		printf("��������Ҫ�޸���Ϣ��ѧ��ѧ��:");
		scanf("%ld",&id);
		position=Look_Up(head,id);   //��ȡ��ѧ���������ϵ�λ�� 
		if(position==NULL)
		{
			printf("û���ҵ���ѧ�ŵ�ѧ��!\n");
		}
		else
		{
			printf("%ld\t%s\t%c\t%d\t%s\n",position->Id
			,position->Name,position->Sex,position->Age,
			position->Note);
			printf("��ѡ������Ҫ�޸ĵ���Ϣ:\n\
	(1)ѧ��\n\
	(2)����\n\
	(3)�Ա�\n\
	(4)����\n\
	(5)��ע\n");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1:
					Change_Information_Id(&(position->Id));
					printf("�޸ĳɹ�\n");
					break;
				case 2:
					Change_Information_Name(position->Name);
					printf("�޸ĳɹ�\n");
					break;
				case 3:
					Change_Information_Sex(&(position->Sex));
					printf("�޸ĳɹ�\n");
					break;
				case 4:
					Change_Information_Age(&(position->Age));
					printf("�޸ĳɹ�\n");
					break;
				case 5:
					Change_Information_Note(position->Note);
					printf("�޸ĳɹ�\n");
					break;
				default:
					printf("�������!\n");
					break;
			}
		}
	}
	else
	{
		printf("�����������!\n");
	}
	return head;
}
struct student* Look_Up(struct student *head,long id)
{
	struct student *p=head;
	while(p!=NULL&&id!=(p->Id))  //Ѱ��ѧ����λ�� 
	{
		p=p->next;
	}
	return p;
}
void Change_Information_Id(long *id)
{
	printf("������ѧ��:");
	scanf("%ld",id);
}
void Change_Information_Name(char *name)
{
	char str[10];
	printf("����������:");
	scanf("%s",str);
	strcpy(name,str);
}
void Change_Information_Sex(char *sex)
{
	printf("�������Ա�:");
	scanf(" %c",sex);
}
void Change_Information_Age(int *age)
{
	printf("����������:");
	scanf("%d",age);
}
void Change_Information_Note(char *note)
{
	char str[100];
	printf("�����뱸ע:");
	scanf("%s",str);
	strcpy(note,str);
}
void Find_Information(struct student *head,int n)
{
	int ch;
	printf("��ѡ���ѯ��ʽ:\n\
	(1)��ѧ�Ų�ѯ\n\
	(2)��������ѯ\n\
	(3)���Ա��ѯ\n\
	(4)�������ѯ\n");
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
			printf("�������!\n");
			break;
	}
}
void Find_Information_Id(struct student *head,int n)
{
	int i; 
	int id;
	int flag=0;
	struct student *p=head;
	printf("������ѧ��:");
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
		printf("û���ҵ���ѧ��!\n");
	}
}
void Find_Information_Name(struct student *head,int n)
{
	int i;
	int flag=0; 
	char name[10];
	struct student *p=head;
	printf("����������:");
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
		printf("û���ҵ�������!\n");
	}	
} 
void Find_Information_Sex(struct student *head,int n)
{
	struct student *p=head;
	int i;
	char sex;
	int flag=0;
	printf("�������Ա�:");
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
		printf("û���ҵ����Ա�!\n");
	}		
}
void Find_Information_Age(struct student *head,int n)
{
	struct student *p=head;
	int flag=0;
	int i;
	int age;
	printf("����������:");
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
		printf("û���ҵ�������!\n");
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
