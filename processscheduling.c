#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

typedef struct 
{
	int pid;
	int AT;
	int BT;
	int ST;
	int CT;
	int WT;
	int TAT;
	int RT;
	int pri;
}process;

int compare (const void * pa, const void * pb)
{
   const process *p1=pa;
   const process *p2=pb;
   return ( p1->AT - p2->AT );
}

int compare1 (const void * pa, const void * pb)
{
   const process *p1=pa;
   const process *p2=pb;
   return ( p1->pid - p2->pid );
}

int max(int a,int b)
{
   if(a>=b)
   {
      return a;
   }
   else
   {
      return b;
   }
}

void roundrobin(int at[],int bt[],int rt[],int n,int quant)
{
    float avg_wt, avg_tat;  
    int i=0;
    int time=0,count=0,remain,wt=0, tat=0;
    remain=n;
    printf("\nProcess No \tBurst Time \tTAT \t\t Waiting Time ");  
    for(time=0, i = 0; remain!=0; )  
    {  
       if(rt[i] <= quant && rt[i] > 0) 
       {  
           time = time + rt[i];  
           rt[i] = 0;  
           count=1;  
       }     
       else if(rt[i] > 0)  
       {  
           rt[i] = rt[i] - quant;  
           time = time + quant;    
       }  
       if(rt[i]==0 && count==1)  
       {  
           remain--; //decrement the process no.  
           printf("\n%d \t\t %d\t\t %d\t\t %d", i+1, bt[i], time-at[i], time-at[i]-bt[i]);  
           wt = wt+time-at[i]-bt[i];  
           tat = tat+time-at[i];  
           count =0;     
       }  
       if(i==n-1)  
       {  
           i=0;  
       }  
       else if(at[i+1]<=time)  
       {  
           i++;  
       }  
       else  
       {  
           i=0;  
       }  
    }  
    // represents the average waiting time and Turn Around time  
    avg_wt = wt * 1.0/n;  
    avg_tat = tat * 1.0/n;  
    printf("\n Average Turn Around Time: \t%.2f", avg_wt);  
    printf("\n Average Waiting Time: \t%.2f", avg_tat);  
}
  
void priority(int n,process p[])
{
    int total_TAT=0,total_WT=0,total_RT=0,is_completed[100];
    memset(is_completed,0,sizeof(is_completed));
    int C=0;//c is for current time
    int prev=0,Completed=0;
    while( Completed != n)
    {
	int idx=-1;
	int mx=-1;//to find biggest
	for(int i=0;i<n;i++)
 	{ 
	    if(p[i].AT<=C && is_completed[i]==0)
	    {
	        if (p[i].pri>mx)
		{
		   mx=p[i].pri;
		   idx=i;
	        }
	        if (p[i].pri==mx)
		{
		   if (p[i].AT<p[idx].AT)
		   {
			mx=p[i].pri;
			idx=i;
		   }
		}
	    }
        }
        if (idx != -1)
        {
     	    p[idx].ST = C;
            p[idx].CT = p[idx].ST + p[idx].BT;
            p[idx].TAT = p[idx].CT - p[idx].AT;
            p[idx].WT = p[idx].TAT - p[idx].BT;
            p[idx].RT = p[idx].ST - p[idx].AT;
            
            total_TAT += p[idx].TAT;
            total_WT += p[idx].WT;
            total_RT += p[idx].RT;
          

            is_completed[idx] = 1;
            Completed++;
            C = p[idx].CT;
            prev =C;
        }
        else
        {
            C++;
        }
   }
   float avg_TAT=(float)total_TAT/n;
   float avg_WT=(float)total_WT/n;
   float avg_RT=(float)total_RT/n;
   printf("\n---------------------------------------------\n" );
   printf("The average Turnaround time is :%.2f\n", avg_TAT);
   printf("The average Waiting time is :%.2f\n", avg_WT);
   printf("The average Response time is :%.2f\n", avg_RT);
   //qsort(p,n,sizeof(process),compare1);//pid
   printf("\n---------------------------------------------\n" );
   printf("#PID\tAT\tBT\tRT\tCT\tTAT\tWT ");
   for(int i=0;i<n;i++)
   {
       printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d \n",p[i].pid,p[i].AT,p[i].BT,p[i].RT,p[i].CT,p[i].TAT,p[i].WT);
   }
}

void sjf(int n,process p[])
{
    int total_TAT=0,total_WT=0,total_RT=0,is_completed[100];
    memset(is_completed,0,sizeof(is_completed));
    int C=0;//c is for current time
    int prev=0,Completed=0;
    while( Completed != n)
    {
	int idx=-1;
	int mn=100000;
        for(int i=0;i<n;i++)
        { 
	    if(p[i].AT<=C && is_completed[i]==0)
	    {
		if (p[i].BT<mn)
		{
			mn=p[i].BT;
			idx=i;
		}
		if (p[i].BT==mn)
		{
		    if (p[i].AT<p[idx].AT)
		    {
		        mn=p[i].BT;
			idx=i;
		    }
		}
	    }
        }
        if (idx != -1)
        {
            p[idx].ST = C;//     ------------------------->imp
            p[idx].CT = p[idx].ST + p[idx].BT;
            p[idx].TAT = p[idx].CT - p[idx].AT;
            p[idx].WT = p[idx].TAT - p[idx].BT;
            p[idx].RT = p[idx].ST - p[idx].AT;          
            total_TAT += p[idx].TAT;
            total_WT += p[idx].WT;
            total_RT += p[idx].RT;
            is_completed[idx] = 1;
            Completed++;//-------------------
            C = p[idx].CT;//-------------
            prev =C;
        }
        else
        {
           C++;
        }
    }
    float avg_TAT=(float)total_TAT/n;
    float avg_WT=(float)total_WT/n;
    float avg_RT=(float)total_RT/n;
    printf("\n---------------------------------------------\n" );
    printf("The average Turnaround time is :%.2f\n", avg_TAT);
    printf("The average Waiting time is :%.2f\n", avg_WT);
    printf("The average Response time is :%.2f\n", avg_RT);
    //qsort(p,n,sizeof(process),compare1);//pid
    printf("\n---------------------------------------------\n" );
    printf("#PID\tAT\tBT\tRT\tCT\tTAT\tWT ");
    for(int i=0;i<n;i++)
    {
	printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d \n",p[i].pid,p[i].AT,p[i].BT,p[i].RT,p[i].CT,p[i].TAT,p[i].WT);
    }
}

void fcfs(int n,process p[])
{
    int total_TAT=0,total_WT=0,total_RT=0;
    qsort(p,n,sizeof(process),compare);//arrivalch
    for(int i=0;i<n;i++)
    {
	if(i==0)
	{
	    p[i].ST=p[i].AT;	
	}
	else
	{
	    p[i].ST=max(p[i].AT,p[i-1].CT);
	}
	p[i].CT=p[i].ST+p[i].BT;
	p[i].TAT=p[i].CT-p[i].AT;
	p[i].WT=p[i].TAT-p[i].BT;
	p[i].RT=p[i].ST-p[i].AT;
	total_TAT=total_TAT+p[i].TAT;
	total_WT=total_WT+p[i].WT;
	total_RT=total_RT+p[i].RT;
    }
    float avg_TAT=(float)total_TAT/n;
    float avg_WT=(float)total_WT/n;
    float avg_RT=(float)total_RT/n;
    printf("\n---------------------------------------------\n" );
    printf("The average Turnaround time is :%.2f\n", avg_TAT);
    printf("The average Waiting time is :%.2f\n", avg_WT);
    printf("The average Response time is :%.2f\n", avg_RT);
    qsort(p,n,sizeof(process),compare1);//pid
    printf("\n---------------------------------------------\n" );
    printf("#PID\tAT\tBT\tRT\tCT\tTAT\tWT ");
    for(int i=0;i<n;i++)
    {
	printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d \n",p[i].pid,p[i].AT,p[i].BT,p[i].RT,p[i].CT,p[i].TAT,p[i].WT);
    }
}

void main()
{

    int  n, quant, at[10], bt[10], rt[10];
    process p[100]; 

    printf("Enter Number of process\n");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
	printf("Print arraival time of the process %d:",i+1);
	scanf("%d",&p[i].AT);
	printf("Print burst time of the process %d:",i+1);
	scanf("%d",&p[i].BT);
	printf("Print priority of the process %d:",i+1);
        scanf("%d",&p[i].pri);
        p[i].pid=i+1;
        at[i] = p[i].AT;
        bt[i] = p[i].BT;
        rt[i] = p[i].BT;
    }
    printf("Enter the Time Quantum for the process: \t");  
    scanf("%d", &quant);
    
    printf("\n*************************FCFS Scheduling*************************\n");
    fcfs(n,p);
    printf("\n*************************SJF Scheduling*************************\n");
    sjf(n,p);
    printf("\n*************************Priority Scheduling*************************\n");
    priority(n,p); 
    printf("\n*************************RobinRound Scheduling*************************\n");           
    roundrobin(at,bt,rt,n,quant);

}
