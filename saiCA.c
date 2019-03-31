#include <stdio.h>
#include <stdbool.h>
typedef struct{
 
    int arrival;
    int burst;
    int priorty;
    int index;
    int status;
	int ct;
	int tat;
	int  wt;
}process;
 
void swap(process *x,process *y)
{
    process temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
 
void bublesort(process p[], int n)
{
 
    int i,j;
    for(i=0;i<(n-1);i++)
        for(j=0;j<(n-(i+1));j++)
            if(p[j].arrival > p[j+1].arrival||(p[j].arrival==p[j+1].arrival&&p[j].priorty>p[j+1].priorty))
                swap(&p[j],&p[j+1]);
}
 
void sortpr(process p[],int n)
{
    int i,j;
    for(i=0;i<(n-1);i++)
        for(j=0;j<(n-(i+1));j++)
            if(p[j].priorty > p[j+1].priorty)
                swap(&p[j],&p[j+1]);
}
 
void deletep(process p[],int size,int index)
{ 
    int i=index;
    while(i<size-1)
    {
        p[i]=p[i+1];
        i++;
    }
    return;
}
 
bool nonew(process p[],int size)
{ 
    for(int i=0;i<size;i++)
    {
        if(p[i].status == 0 )
		return false;
    }
    return true;
}
 
bool noready(process p[],int size)
{
    for(int i=0;i<size;i++)
        if(p[i].status==1)
            return false;
    return true;
}
 
int ready(process p[],int size)
{ 
    int min=0;
    for(int i=0;i<size;i++)
        if(p[i].status==1&&p[i].priorty<p[min].priorty)
            min=i;
    return min;
}
 

void NonPreemtiveAging(process p[],int size)
{
    int i,j,minpr,current=p[0].arrival;
    for(i=0;i<size-1;i++)
    { 
        printf("p%d from %d to %d\n",p[i].index,current,current+p[i].burst);
        p[i].ct = current+p[i].burst + 2; // 2 is cost for context switching
	p[i].tat = p[i].ct - p[i].arrival;
	p[i].wt = p[i].tat - p[i].burst;
        current=current+p[i].burst;
        if (p[i+1].arrival==current)
        {
            continue;
        }
        else{
            if(p[i+1].arrival>current){
                current=p[i+1].arrival;
            }
            else{ j=i+1;
            minpr=p[j].priorty-(current-p[j].arrival)/size;
            for(j=i+1;j<size;j++)
            { 
                if(p[j].arrival<current){
                    if (p[j].priorty-(current-p[j].arrival)/ size < minpr)
                    {
                        minpr=p[j].priorty-(current-p[j].arrival)/size;
                        swap(&p[i+1],&p[j]);
                    }
                }
            }
            }
        }
    }
    printf("p%d from %d to %d\n",p[i].index,current,current+p[i].burst);
       p[i].ct = current+p[i].burst;
	p[i].tat = p[i].ct - p[i].arrival;
	p[i].wt = p[i].tat - p[i].burst;
}
 
void showTable(process p[], int size){
	printf("ID\tAT\tBT\tCT\tTAT\tWT\n");
	for(int i = 0 ; i < size ; i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].index, p[i].arrival, p[i].burst, p[i].ct, p[i].tat, p[i].wt);
	}
	
	
} 
int  main()
{
    int i,c;            	
	int n;                                                                                                                 
    printf("Enter number of processes : ");
 	scanf("%d", &n);		
    process p[n];

    for (i=0;i<n;i++)
    {
        printf("\nenter the arrival time of p %d:",i);
        scanf("%d",&p[i].arrival);
        printf("enter the burst time of p %d:",i);
        scanf("%d",&p[i].burst);
        printf("enter the priorty of p %d:",i);
        scanf("%d",&p[i].priorty);
        p[i].status=0;
        p[i].index=i;
    }
    bublesort(p,n);
    printf("\nsorted:\nprocess\tarrival time\tburst time\tpriorty\n");
    for (i=0;i<n;i++)
    {
        printf( " p%d\t%d\t\t%d\t\t%d\n",p[i].index,p[i].arrival,p[i].burst,p[i].priorty);
    }
	putchar('\n');
   	NonPreemtiveAging(p,n);
	showTable(p, n);   
    
	return 0;
}
