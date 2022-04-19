#include<stdio.h>

int absoluteValue(int);

int absoluteValue(int x)
{
    if(x>0)
    {
        return x;
    }
    else
    {
        return x*-1;
    }
}

void scan(int max,int n,int head,int temp[20])
{
    int queue[25],i,j,k,seek=0,diff;
    int queue1[20],queue2[20],temp1=0,temp2=0;
    float averageSeekTime;

    for(i=1;i<=n;i++)
    {
        if(temp[i]>head)
        {
            queue1[temp1]=temp[i];
            temp1++;
        }
        else
        {   
            queue2[temp2]=temp[i];
            temp2++;
        }
    }
    
    for(i=0;i<temp1-1;i++)
    {
        for(j=i+1;j<temp1;j++)
        {
            if(queue1[i]>queue1[j])
            {
                temp[i]=queue1[i];
                queue1[i]=queue1[j];
                queue1[j]=temp[i];
            }
        }
    }
    
    for(i=0;i<temp2-1;i++)
    {
        for(j=i+1;j<temp2;j++)
        {
            if(queue2[i]<queue2[j])
            {
                temp[i]=queue2[i];
                queue2[i]=queue2[j];
                queue2[j]=temp[i];
            }
        }
    }    
    
    for(i=1,j=0;j<temp1;i++,j++)
    {
        queue[i]=queue1[j]; 
    }
    
    queue[i]=max;
    
    for(i=temp1+2,j=0;j<temp2;i++,j++)
    {
        queue[i]=queue2[j];
    }
    
    queue[i]=0;
    queue[0]=head;
    
    for(j=0; j<=n; j++)
    {   
        diff = absoluteValue(queue[j+1]-queue[j]);
        seek = seek + diff;
        printf("Disk head moves from position %d to %d with Seek %d \n",
        queue[j], queue[j+1], diff);
    }
    
    averageSeekTime = seek/(float)n;
    
    printf("Total Seek Time= %d\n", seek);
    printf("Average Seek Time= %f\n", averageSeekTime);
}

void cscan(int max,int n,int head,int temp[20])
{
    int queue[25],i,j,k,seek=0;
    int diff,queue1[20],queue2[20],temp1=0,temp2=0;
    float averageSeekTime;
    
    for(i=1;i<=n;i++)
    {
        if(temp[i]>head)
        {
            queue1[temp1]=temp[i];
            temp1++;
        }
        else
        {   
            queue2[temp2]=temp[i];
            temp2++;
        }
    }
    
    for(i=0;i<temp1-1;i++)
    {
        for(j=i+1;j<temp1;j++)
        {
            if(queue1[i]>queue1[j])
            {
                temp[i]=queue1[i];
                queue1[i]=queue1[j];
                queue1[j]=temp[i];
            }
        }
    }
    
    for(i=0;i<temp2-1;i++)
    {
        for(j=i+1;j<temp2;j++)
        {
            if(queue2[i]>queue2[j])
            {
                temp[i]=queue2[i];
                queue2[i]=queue2[j];
                queue2[j]=temp[i];
            }
        }
    }    
    
    for(i=1,j=0;j<temp1;i++,j++)
    {
        queue[i]=queue1[j]; 
    }
    
    queue[i]=max;
    queue[i+1]=0; 
    
    for(i=temp1+3,j=0;j<temp2;i++,j++)
    {
        queue[i]=queue2[j];
    }
    
    queue[0]=head;
    
    for(j=0; j<=n+1; j++) 
    {   
        
        diff = absoluteValue(queue[j+1]-queue[j]);
        seek = seek + diff;
        printf("Disk head moves from position %d to %d with Seek %d \n",queue[j], queue[j+1], diff);
    }
    
    averageSeekTime = seek/(float)n;
    
    printf("Total Seek Time= %d\n", seek);
    printf("Average Seek Time= %f\n", averageSeekTime);
}

int fcfs(int max,int n,int head,int queue[20])
{
   int i,j,k,seek=0,diff;
   float avg;

   queue[0]=head;
   for(j=0;j<=n-1;j++)
   {
      diff=absoluteValue(queue[j+1]-queue[j]);
      seek+=diff;
      printf("Disk head moves from %d to %d with seek %d\n",queue[j],queue[j+1],diff);
   }
   printf("Total seek time is %d\n",seek);
   avg=seek/(float)n;
   printf("Average seek time is %f\n",avg);
   return 0;
}

int main()
{
    int i,maximum,x,header,que[20];
    
    printf("Enter the maximum range of Disk: ");
    scanf("%d",&maximum);
    printf("Enter the number of queue requests: ");
    scanf("%d",&x);
    printf("Enter the initial head position: ");
    scanf("%d",&header);
    printf("Enter the queue of disk positions to be read\n");
    for(i=1;i<=x;i++)
    {
       scanf("%d",&que[i]);
    }

    printf("\n*************************FCFS Disk Scheduling*************************\n");
    fcfs(maximum,x,header,que);
    printf("\n*************************SCAN Disk Scheduling*************************\n");
    scan(maximum,x,header,que);
    printf("\n*************************CSCAN Disk Scheduling*************************\n");
    cscan(maximum,x,header,que);
   
}
