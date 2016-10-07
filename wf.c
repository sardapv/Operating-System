#include<stdio.h>
#define max 25

void main()
{
	int frag[max],b[max],f[max],i,j,nb,nf,temp,highest=0;
	static int bf[max],ff[max];int flag,fragi = 0;

	printf("\n\tMemory Management Scheme - Worst Fit");
	printf("\nEnter the number of blocks:");
	scanf("%d",&nb);
	printf("Enter the number of Process:");
	scanf("%d",&nf);
	printf("\nEnter the size of the blocks:-\n");
	for(i=1;i<=nb;i++) {
		printf("Block %d:",i);
		scanf("%d",&b[i]);
		ff[i] = i;
	}
	printf("Enter the size of the Processes :-\n");

	for(i=1;i<=nf;i++) {
		printf("Process %d:",i);
		scanf("%d",&f[i]);
	}
	int y,z,temp1;
	/*sorting for worst and best fit only*/
	for(y=1;y<=nb;y++)
	{
		for(z=y;z<=nb;z++)
		{
			if(b[y]<b[z])    /*change < to > for best fit*/
			{
				temp=b[y];
				b[y]=b[z];
				b[z]=temp;
				temp1=ff[y];
				ff[y]=ff[z];
				ff[z]=temp1;
			}
          }
	}
	int flagn[max];
	int fragx = 0;
	/*Following is the code of next fit*/
	  printf("\n\nProcess_No\tProcess_Size\tBlock_No\tBlock_Size\tFragment\n");
	  for(i=1;i<=nf;i++)
	  {
	    flag = 1;
	    for(j=1;j<=nb;j++)
	    {
	      if(f[i] <= b[j]){
					flagn[j] = 1;
	        printf("%-15d\t%-15d\t%-15d\t%-15d\t",i, f[i],ff[j],b[j]);
	        b[j] = b[j] - f[i];
					fragi = fragi + b[j];
	        printf("%-15d\n",b[j]);
	        break;
	      }
	      else
				{flagn[j] = 0;
	      flag++;
				}
	    }
	    if(flag > nb)
	    printf("%-15d\t%-15d\t%-15s\t%-15s\t%-15s\n",i, f[i],"WAIT...","WAIT...","WAIT...");
	  }
		printf("Internal Fragmentation = %d",fragi );
		for (j= 1; j <=nb ; j++) {
			if (flagn[j] != 1)
					fragx = fragx + b[j];
						/* code */
		}
		printf("\nExternal Fragmentation = %d\n",fragx);/*next fit ends*/
}
