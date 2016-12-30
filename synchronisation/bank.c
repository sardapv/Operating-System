#include<stdio.h>
int main() {
int allocation[10][5],max[10][5],need[10][5],available[3],flag[10],sq[10];
int n,r,i,j,k,count,count1=0;
printf("\n Input the number of processes running ");
scanf("%d",&n);
for(i=0;i<10;i++)
    flag[i]=0;
printf("\n Input the number of resources ");
scanf("%d",&r);
printf("\n Input the allocation matrix for the processes in row major order..\n");
for(i=0;i<n;i++)
{
    printf("\n Process %d\n",i);
    for(j=0;j<r;j++)
    {
        printf("\n Resource %d\n",j);
        scanf("%d",&allocation[i][j]);
    }
}
printf("\n Input the no. of resources that a process can maximum have..\n");
for(i=0;i<n;i++)
{
    printf("\n Process %d\n",i);
    for(j=0;j<r;j++)
    {
        printf("\n Resource %d\n",j);
        scanf("%d",&max[i][j]);
    }
}
printf("\n Input the no. of available instances of each resource..\n");
for(i=0;i<r;i++)
{
    printf("\n Resource %d : ",i);
    scanf("%d",&available[i]);
}
printf("\n The need matrix is as follows : \n");
for(i=0;i<n;i++)
{
    for(j=0;j<r;j++)
    {
        need[i][j]= max[i][j]-allocation[i][j];
	if(need[i][j] < 0) {
		
	}       
	else {
	printf("\t %d",need[i][j]);
    }
    }
    printf("\n");
}
do{
  for(k=0;k<n;k++)
  {
      for(i=0;i<n;i++)
      {
          if(flag[i]==0)
          {
            count=0;
            for(j=0;j<r;j++)
            {
               if(available[j]>=need[i][j])
               count++;
            }
            if(count==r)
            {
               count1++;
               flag[i]=1;
               sq[count1-1]=i;
               for(j=0;j<r;j++)
              {
                   available[j]=available[j]+allocation[i][j];
              }
               break;
            }
         }
     }
  }
  if(count1!=n)
  {
     printf("\n---------------IT'S AN UNSAFE STATE---------------");
     break;
  }
}while(count1!=n);
if(count1==n)
{
   printf("\n *******************IT'S A SAFE STATE*******************");
   printf("\n The safe sequence is....\n");
   for(i=0;i<n;i++)
       printf("\t P%d",sq[i]);
   printf("\n");
   printf("\n The available matrix is now : ");
   for(i=0;i<r;i++)
       printf("\t %d",available[i]);
}
}
