#include<stdio.h> 
#include<conio.h>

void roundrobin(int no,int rem_t[10],int cur_t,int ar_t[10], int bs_t[10]);

main() 
{
	int Pro_no,j,no,cur_t,Rem_Pro,count,time_q,wait,tut,ar_t[10],bs_t[10],rem_t[10],x=1;
	
	wait = 0;
	
	printf("Enter the number of processes you want to run "); 
	scanf("%d",&no);
	Rem_Pro = no;
	
	printf("\nEnter the arrival time and burst time of the processes\n");
	for(Pro_no = 0;Pro_no < no;Pro_no++) 
	{
		printf("\nProcess P%d\n",Pro_no+1);
		printf("Arrival time = "); 
		scanf("%d",&ar_t[Pro_no]);
		printf("Burst time = "); 
		scanf("%d",&bs_t[Pro_no]); 
		rem_t[Pro_no]=bs_t[Pro_no]; 
	} 
	printf("The details of time quantum are:\n");
	printf("The time quantum for first round is 6.\n"); 
	time_q=6;
	tut = 0;
	cur_t=0;count = 0;
	for(Pro_no=0;Rem_Pro!=0;) 
	{
		if(rem_t[Pro_no]<=time_q && rem_t[Pro_no]>0)
		{ 
			cur_t+=rem_t[Pro_no]; 
			rem_t[Pro_no]=0; 
			count=1; 
		} 
		else if(rem_t[Pro_no]>0)
		{ 
			rem_t[Pro_no]-=time_q; 
			cur_t+=time_q; 
		} 
		if(rem_t[Pro_no]==0 && count==1)			
		{ printf("%d",Pro_no);
			Rem_Pro--;				
			printf("P %d",Pro_no+1); 
			printf("\t%d",cur_t-ar_t[Pro_no]);
			printf("\t%d\n",cur_t-bs_t[Pro_no]-ar_t[Pro_no]);
			wait+=cur_t-ar_t[Pro_no]-bs_t[Pro_no]; 
			tut+=cur_t-ar_t[Pro_no]; 
			count=0; 
                       
		} 
		if(Pro_no==no-1){
			x++;
			if(x==2){
				Pro_no=0;
				time_q=10;
				
				printf("The time quantum for second round is 10. \n");
			}
			else{
				break;
			}
		}
		else if(cur_t >= ar_t[Pro_no+1]){
			Pro_no++;
		}
		else{
			Pro_no=0;
		}
	}
	
	roundrobin(no,rem_t,cur_t,ar_t,bs_t);
	
	return 0;
}


void roundrobin(int no,int rem_t[10],int cur_t,int ar_t[10], int bs_t[10]){
	
	float avg_wait,avg_tat;
    int i,j,n=no,temp,burst[20],Pro_no[20],w_time[20],tat_t[20],total=0,loc;
    
    printf("Third round with greatest burst time.\n");
    
    for(i=0;i<n;i++)
    {
        burst[i]=rem_t[i];
        w_time[i]=cur_t-ar_t[i]-burst[i];
		Pro_no[i]=i+1;
    }
	
    for(i=0;i<n;i++)
    {
        loc=i;
        for(j=i+1;j<n;j++)
        {
            if(burst[j]>burst[loc]){
            	loc=j;
            }
        }
        temp=burst[i];
        burst[i]=burst[loc];
        burst[loc]=temp;
        temp=Pro_no[i];
        Pro_no[i]=Pro_no[loc];
        Pro_no[loc]=temp;
    }
	
    for(i=1;i<n;i++)
    {
        for(j=0;j<i;j++){
        	w_time[i]+=burst[j];
        }
        total+=w_time[i];
    }
 
    avg_wait=(float)total/n;
    total=0;
    printf("\nProcess\tArrival time\twaiting time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tat_t[i]=burst[i]+w_time[i];
        total=total + tat_t[i];
        printf("\nP%d\t\t%d\t\t%d\t\t%d",Pro_no[i],burst[i],w_time[i],tat_t[i]);
    }
    avg_tat=(float)total/n;
    printf("\n\nAverage waiting time = %f",avg_wait);
    printf("\n Average turnaround time = %f\n",avg_tat);
	
}

