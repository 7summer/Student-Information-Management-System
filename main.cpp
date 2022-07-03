#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student
{
	long Id; //ѧ��
	char Name[10]; //����
	char Sex; //�Ա�
	int Age; //����
	char Note[100]; //��ע
	struct student *next;
};
struct student* Input_Information(struct student *head,int n);
struct student* Look_Up(struct student *head,long id); //�����������ѧ��Ϊid��ѧ�����򷵻ظý��ĵ�ַ
void Printf_Link(struct student *head); //��ӡѧ����Ϣ
void Save_to_File(struct student *head,int n); //��ѧ����Ϣ���浽����
struct student* Ouput_from_File(struct student *head,int *pn);
struct student* Delete_Information(struct student *head,int *pn); //*pn��ѧ������
void Change_Information(struct student *head);
void Find_Information(struct student *head,int n); //n����ѧ������
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
	int sum=0; //��¼ѧ������  
	int i;
	int *pn=&sum;
    int choice;
	printf("����������:");
	again:scanf("%s",secret); 
    if(!strcmp(secret,Real_secret))
    {
		do
		{
			printf("��ѡ��ϵͳ������:\n\
	1.ѧ��������Ϣ¼��\n\
	2.ѧ��������Ϣ��ʾ\n\
	3.ѧ��������Ϣ����\n\
    4.��ȡѧ��������Ϣ\n\
	5.ѧ��������Ϣɾ��\n\
	6.ѧ��������Ϣ�޸ģ�Ҫ�����������룩\n\
	7.ѧ��������Ϣ��ѯ\n\
	8.�˳�ϵͳ\n");
			scanf("%d%*c",&choice);
            switch (choice)
            {
                case 1:
					if(sum)
					{
						DelteMemory(&head);
					}
                    printf("������ѧ������:");
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
					printf("�������!\n");
                    break;
            }
        }while(choice!=8);
    }
    else
    {
        printf("�������!\n");
        printf("����������:");
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
        head->Id=0; //ΪLook_Up�����ṩ����
	}
	else
	{
		while(q->next!=NULL)
		{
			q=q->next;
		}
		q->next=p;
	}
	printf("�������%dλѧ����ѧ��:",n);
	again:scanf("%ld",&(p->Id));
    temp=Look_Up(head,p->Id);
    if(!temp)
    {
        printf("��(%d)%s��ͻ\n",temp->Id,temp->Name);
        printf("�����������%dλѧ����ѧ��:",n);
        goto again;
    }
	printf("�������%dλѧ��������:",n);
	scanf("%s%*c",p->Name);
	printf("�������%dλѧ�����Ա�:",n);
	scanf("%c%*c",&(p->Sex));
	printf("�������%dλѧ��������:",n);
	scanf("%d%*c",&(p->Age));
	printf("�������%dλѧ���ı�ע:",n);
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
	fp=fopen("F:\\ѧ����Ϣ�ĵ�.txt","w");
	fprintf(fp,"ѧ������:%d\n",n);
	for(i=1;i<=n;i++)
	{
		fprintf(fp,"%ld\t%s\t%c\t%d\t%s\n",p->Id,p->Name,
		p->Sex,p->Age,p->Note);
		p=p->next;
	}
	printf("����ɹ�!\n");
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
	fp=fopen("F:\\ѧ����Ϣ�ĵ�.txt","r");
	fscanf(fp,"ѧ������:%d\n",pn);
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
	printf("����������Ҫɾ��ѧ����ѧ��:");
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
		(*pn)--; //ɾ��ѧ����ѧ��������1
		free(p);
	}
	else
	{
		printf("û���ҵ���ѧ��!\n");
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
			do
			{
				printf("%ld\t%s\t%c\t%d\t%s\n",position->Id
				,position->Name,position->Sex,position->Age,
				position->Note);
				printf("��ѡ������Ҫ�޸ĵ���Ϣ:\n\
	(1)ѧ��\n\
	(2)����\n\
	(3)�Ա�\n\
	(4)����\n\
	(5)��ע\n\
	(6)�˳�");
				scanf("%d",&ch);
				switch(ch)
				{
					case 1:
						printf("������ѧ��:");
						again:scanf("%ld%*c",&id);
						temp=Look_Up(head,id);
						if(temp==position)
						{
							printf("�޸ĺ��ѧ��(%d)��û�޸�֮ǰ��ͬ\n",position->Id);
						}
						else if(temp!=NULL)
						{
							printf("��(%d)%s��ͻ\n",temp->Id,temp->Name);
							printf("����������:");
							goto again;
						}
						else
						{
							position->Id=id;
							printf("�޸ĳɹ�\n");
						}
						break;
					case 2:
						printf("����������:");
						scanf("%s%*c",position->Name);
						printf("�޸ĳɹ�\n");
						break;
					case 3:
						printf("�������Ա�:");
						scanf("%c%*c",&position->Sex);
						printf("�޸ĳɹ�\n");
						break;
					case 4:
						printf("����������:");
						scanf("%d%*c",&position->Age);
						printf("�޸ĳɹ�\n");
						break;
					case 5:
						printf("�����뱸ע:");
						scanf("%s%*c",position->Note);
						printf("�޸ĳɹ�\n");
						break;
					case 6:
						printf("лл!\n");
						break;
					default:
						printf("�������!\n");
						break;
				}
				printf("%d\t%s\t%c\t%d\t%s\n",position->Id,position->Name,position->Sex,position->Age,
				position->Note);
			} while (ch!=6);
		}
	}
	else
	{
		printf("�����������!\n");
	}
}
void Find_Information(struct student *head,int n)
{
	int ch;
	do
	{
		printf("��ѡ���ѯ��ʽ:\n\
	(1)��ѧ�Ų�ѯ\n\
	(2)��������ѯ\n\
	(3)���Ա��ѯ\n\
	(4)�������ѯ\n\
	(5)�˳�");
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
				printf("лл!\n");
				break;
			default:
				printf("�������!\n");
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
	while(p!=NULL&&id!=(p->Id))  //Ѱ��ѧ����λ�� 
	{
		p=p->next;
	}
	return p;
}