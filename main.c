#include "header.h"

int main()
{
    int choice=0;

    for(;;){
    printf("1: Add Excursion\n");
	printf("2: Print longest excursion\n");
	printf("3: Print expired excursions\n");
	printf("4: Delete Excursion\n");
	printf("5: Exit\n");


 do{
    	printf("Enter number between 1 and 5 to choose: ");
    scanf("%d",&choice);
    fflush(stdin);
    } while(!(choice>=0 && choice<=6));
      printf("%d \n",choice);
    switch(choice)
    {
        case 1:
        {
            read();
            add();
            save();
            head=NULL;
            break;
        }
        case 2:
        {
        	read();
			longest();
			head=NULL;
			break;
		}
        case 3:
        {   read();
            exp();
            head=NULL;
            break;
        }
        case 4:
        {   read();
            del();
            save();
            head=NULL;
            break;
        }
        
        case 5:
        {
            exit(5);
        }

    }

}
return 0;
}
void read(){
    FILE *fp;
    int i;
    int size_of_code;
    if((fp=fopen("Excursions","rb"))==NULL){
        printf("Error open file!");
        exit(0);
    }

while(1){
        if(fread(&size_of_code, sizeof(int), 1, fp)!=1)
            {
                printf("Error reading1");

                exit(4);
            }
            if (size_of_code==-1)
            break;

            struct eks *temp=(struct eks*)malloc(sizeof(struct eks));
            if(head==NULL)
            {
                head=temp  ;
                current=head;
                current->next=NULL;
            }
            else
            {
            current->next=temp;
            current=temp;
            current->next=NULL;
            }
            if((fread(temp->code,size_of_code,1,fp))!=1){
                printf("error");
                exit (20);
                }

            if((fread(&temp->day,sizeof(int),1,fp))!=1){
                printf("error");
                exit (22);
                }
            if((fread(&temp->month,sizeof(int),1,fp))!=1){
                printf("error");
                exit (22);
                }
            if((fread(&temp->year,sizeof(int),1,fp))!=1){
                printf("error");
                exit (22);
                }

            if((fread(&temp->dur,sizeof(int),1,fp)!=1)){
                printf("error");
                exit(24);
            }
			if((fread(&temp->price,sizeof(double),1,fp)!=1)){
                printf("error");
                exit(23);
            }

        }
fclose(fp);
}

void add(){

    struct eks *temp;
    temp=head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    struct eks *newE;
    newE=(struct eks*) malloc(sizeof(struct eks));
    printf("Enter the new ID ");
    scanf("%s",newE->code);
    printf("Enter the new day ");
    scanf("%d",&newE->day);
    printf("Enter the new month ");
    scanf("%d",&newE->month);
    printf("Enter the new year ");
    scanf("%d",&newE->year);
    printf("Enter the new duration ");
    scanf("%d",&newE->dur);
    printf("Enter the new price ");
    scanf("%lf",&newE->price);
    newE->next=NULL;
    temp->next=newE;
    printf("Add new client : SUCCESSFUL\n");
}


void del(){
    struct eks* prev_item=head;
	struct eks* curr_item=head;
	int f=0;
    char *arr;
    arr=(char*)malloc(20);
    printf("Input excursion code : \n");
    gets(arr);
	while(curr_item!=NULL)
	{
		if(strcmp (curr_item->code, arr) == 0)
		{
			if(curr_item == head)
			{
				head = head->next;
				prev_item = head;
				f=1;
			}
			else
            prev_item->next = curr_item->next;
			free(curr_item);
			curr_item = prev_item;
		}
		prev_item = curr_item;
		if(f == 0)
			curr_item=curr_item->next;
		f=0;
	}
}
void exp()
{

struct eks*temp;
temp=head;
int day,month,year;
int flag=0;
    printf("Input day  : \n");
    scanf("%d",&day);
    printf("Input month  : \n");
    scanf("%d",&month);
    printf("Input year  : \n");
    scanf("%d",&year);
while(temp!=NULL)
{
  if(temp->year<year)
  {
    printf("excursion with code %s expired!\n",temp->code);
    flag=1;
  }
  else if(temp->month<month)
  {
    printf("excursion with code %s expired!\n",temp->code);
    flag=1;
  }
  else if(temp->day<day)
  {
    printf("excursion with code %s expired!\n",temp->code);
    flag=1;
  }
  temp=temp->next;
}
if(flag==0) 
printf("NO expired excursions!");
}

void longest()
{
	int longest=0;
	struct eks *temp;
	struct eks *longestE;
	temp=head;
	while(temp!=NULL)
	{
  		if(temp->dur>longest)
  		{
  			longest=temp->dur;
			longestE=temp;	
		}
  		temp=temp->next;
	}
	printf("%s\n",longestE->code);
}
void save(){
    FILE *fp;
    int stoper=-1;
    if((fp=fopen("Excursions","wb"))==NULL){
        printf("Error open file!");
        exit(0);
    }
    struct eks *temp;
    temp=head;
    int size_of_code;
    while(temp!=NULL){
        size_of_code=strlen(temp->code);size_of_code++;
        if(fwrite(&size_of_code,sizeof(int),1,fp)!=1){
           printf("Error");
           exit(1);
        }
       if(fwrite(temp->code,size_of_code,1,fp)!=1){
            printf("Error");
            exit(1);
       }
       if(fwrite(&temp->day,sizeof(int),1,fp)!=1){
            printf("Error");
            exit(1);
       }
       if(fwrite(&temp->month,sizeof(int),1,fp)!=1){
            printf("Error");
            exit(1);
       }
       if(fwrite(&temp->year,sizeof(int),1,fp)!=1){
            printf("Error");
            exit(1);
       }
       if(fwrite(&temp->dur,sizeof(int),1,fp)!=1){
            printf("Error");
           exit(1);
        }
       if(fwrite(&temp->price,sizeof(double),1,fp)!=1){
            printf("Error");
            exit(1);
       }
        
        temp=temp->next;
    }
     if(fwrite(&stoper,sizeof(int),1,fp)!=1){
            printf("Error");
           exit(1);
        }
    fclose(fp);
}
