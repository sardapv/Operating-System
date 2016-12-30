void drawGanttChart();
#include<stdlib.h>
#include<stdio.h>
int numberOfProcesses,totalCPUBurstTime,*arrivalTime,*CPUBurstTime,*processNumber,minimumArrivalTime,*priority;
float averageWaitingTime=0,averageTurnAroundTime=0;int timeQuantum;

int main()
{
	int i,j,temp;

	arrivalTime=(int*)malloc(sizeof(int)*numberOfProcesses);
	CPUBurstTime=(int*)malloc(sizeof(int)*numberOfProcesses);
	processNumber=(int*)malloc(sizeof(int)*numberOfProcesses);
	priority=(int *)malloc(sizeof(int)*numberOfProcesses);

	minimumArrivalTime=2147483647;
	FILE *fp;
		fp=fopen("Input.txt","r");
		fscanf(fp,"%d",&numberOfProcesses);
		for(i=0;i<numberOfProcesses;i++) {
		processNumber[i] = i;
		fscanf(fp,"%d\t%d\t%d",&arrivalTime[i],&CPUBurstTime[i],&priority[i]);
		
		}fscanf(fp,"%d",&timeQuantum);
		fclose(fp);
	for(i=0;i<numberOfProcesses;i++)
	{
		/*processNumber[i]=i;
		printf("\nEnter the data for process number : %d\n",i);
		printf("\n");
		printf("Arrival Time   : ");
		scanf("%d",&arrivalTime[i]);
		printf("CPU Burst time : ");
		scanf("%d",&CPUBurstTime[i]);
		printf("Priority : ");
		scanf("%d",&priority[i]);*/

		totalCPUBurstTime+=CPUBurstTime[i];
		if(minimumArrivalTime>arrivalTime[i])
			minimumArrivalTime=arrivalTime[i];
	}

	/*
	   implementing bubble sort algorithm
	 */
	for(i=1;i<numberOfProcesses;i++)
	{
		

		for(j=1;j<numberOfProcesses-1;j++)
		{
			if(priority[j]>priority[j+1])
			{
				temp=priority[j];
				priority[j]=priority[j+1];
				priority[j+1]=temp;

				temp=arrivalTime[j];
				arrivalTime[j]=arrivalTime[j+1];
				arrivalTime[j+1]=temp;

				temp=CPUBurstTime[j];
				CPUBurstTime[j]=CPUBurstTime[j+1];
				CPUBurstTime[j+1]=temp;

				temp=processNumber[j];
				processNumber[j]=processNumber[j+1];
				processNumber[j+1]=temp;
			}
		}
	}
	/*for(i=0;i<numberOfProcesses;i++)
	{
		printf("P%d -> %d,%d\n",processNumber[i],arrivalTime[i],CPUBurstTime[i]);
	}*/
printf("\n================================================ NONPREMPTIVE PRIORITY ====================================\n");
	drawGanttChart();

}
void drawGanttChart()
{
	const int maxWidth=100;
	int scalingFactor,i,counter,tempi,currentTime;
	printf("The gantt chart for the given processes is : \n\n");

	scalingFactor=maxWidth/totalCPUBurstTime;
	for(i=0;i<scalingFactor*totalCPUBurstTime+2+numberOfProcesses;i++)
	{
		printf("-");
	}
	printf("\n|");
	counter=0,tempi=0;
	for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
	{
		if(i==CPUBurstTime[counter]*scalingFactor+tempi)
		{
			counter++;
			tempi=i;
			printf("|");
		}
		else if(i==(CPUBurstTime[counter]*scalingFactor)/2+tempi)
		{
			printf("P%d",processNumber[counter]);
		}
		else
		{
			printf(" ");
		}

	}
	printf("|");
	printf("\n");
	for(i=0;i<scalingFactor*totalCPUBurstTime+2+numberOfProcesses;i++)
	{
		printf("-");
	}
	printf("\n");

	/* printing the time labels of the gantt chart */
	counter=0;
	tempi=0;
	currentTime=minimumArrivalTime;
	printf("%d",currentTime);
	for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
	{
		if(i==CPUBurstTime[counter]*scalingFactor+tempi)
		{

			tempi=i;
			currentTime+=CPUBurstTime[counter];
			averageWaitingTime+=currentTime;
			counter++;
			printf("%2d",currentTime);
		}
		else
		{
			printf(" ");
		}
	}
	currentTime+=CPUBurstTime[counter];

	printf("%2d\n\n",currentTime);
	averageWaitingTime=averageWaitingTime/numberOfProcesses;
	averageTurnAroundTime=averageWaitingTime+totalCPUBurstTime/numberOfProcesses;

	/*printf("Average waiting Time     : %f\n",averageWaitingTime);
	printf("Average Turn Around Time : %f\n",averageTurnAroundTime);
	*/		}	
