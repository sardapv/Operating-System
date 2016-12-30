#include<stdio.h>
int main()
{
	int min(int, int []);
	int temp,time,temp4,c,n,i,j,a1[20],wt[20],pr[20],bt[20],gc[20],arr_ti[20],tat[20],sum_bt=0,a=0,p=0,temp1,count;
	printf("Enter the no. of proceses");
	scanf("%d",&n);
	printf("Enter the burst time of processes");
	for(i=0; i<n; i++)
	{scanf("%d",&bt[i]);
		sum_bt=sum_bt+bt[i];
		a1[i]=bt[i];}
	for(i=0; i<n; i++)
		pr[i]=i+1;
	printf("Enter the arrival time");
	for(i=0; i<n; i++)
		scanf("%d",&arr_ti[i]);
	for(i=0; i<(n-2); i++)
	{  for(j=i; j<((n-2)-i); i++)
		{
			if(arr_ti[j]>arr_ti[j+1])
			{   temp=arr_ti[j];
				arr_ti[j]=arr_ti[j+1];
				arr_ti[j+1]=temp;
				temp=a1[j];
				a1[j]=a1[j+1];
				a1[j+1]=temp;
				temp=pr[j];
				pr[j]=pr[j+1];
				pr[j+1]=temp;
			}}}
	for(i=0; i<n; i++)
	{
		wt[i]=0;
		tat[i]=0;
	}
	for(i=0; i<=sum_bt; i++)
	{
		a++;
		if(a<5)
		{
			c=min(a,a1)+1;
			gc[i]=c;
		}
		else
		{
			c=min(5,a1)+1;
			gc[i]=c;
		}  }
	for(i=0; i<n; i++)
	{
		temp=i+1;
		time=0;
		temp1=0;
		for(j=0; j<sum_bt; j++)
		{time++;
			if(temp==gc[j])
			{
				if(temp1==0)
				{
					wt[i]=wt[i]+time-(i+1);
					temp1=j+2;
				}
				else
				{
					wt[i]=wt[i]+(j+1)-temp1;
					temp1=j+2;
				}}}}

	for(i=0; i<n; i++)
	{
		temp=0;
		for(j=0; j<sum_bt; j++)
		{
			if(i+1==gc[j])
			{
				if(temp==0)
				{
					tat[i]=tat[i]+bt[i]+j-arr_ti[i];
					temp=j+1;
				}
				else
				{
					tat[i]=tat[i]+j-temp;
					temp=j+1;
				}  }}}
	//printing the output

/*	printf("DATA IS AS FOLLOWS: \n");
	printf("Process\t Burst Time\t Arrival Time\t Waiting Time\t Turn Around Time\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t %d\t\t\t %d\t\t %d\t\t %d\n",pr[i],bt[i],arr_ti[i],wt[i],tat[i]);
	}*/
	printf("\n \n");
	printf("GANTT CHART: \n");
	c=gc[0];
	for (i=1;i<=n;i++)
		printf("--------");
	printf("-\n");
	printf("|   P%d  ",gc[0]);
		
	for(i=1;i<sum_bt;i++)
	{
		if(gc[i]!=c)
		{printf("|   P%d  ",gc[i]);
			c=gc[i];}
	}
	printf("|\n");
	for (i=1;i<=n;i++)
		printf("--------");
	printf("-\n0\t");
	c=gc[0];
	for(i=1;i<=sum_bt;i++)
	{    p=p+1;
		if(gc[i]!=c)
		{printf("%d \t",p);
			c=gc[i];
		}
	}
}


int min(int a,int a1[20])
{
	int i,count=0;
	int temp=a1[0];
	if(a==1)
	{ temp--;}
	else
	{
		for(i=0; i<a; i++)
		{
			if(temp>a1[i])
			{
				temp=a1[i];
				count=i;}}
		temp--;}
	if(temp==0)
	{temp=500;}
	a1[count]=temp;
	return(count);  /* returning the index of array whose value is minimum*/
}
