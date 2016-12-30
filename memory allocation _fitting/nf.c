#include<stdio.h>
#define max 25

void main()
{
	int frag[max],b[max],f[max],i,j,nb,nf,temp,highest=0;
	static int bf[max],ff[max];int flag,flagn[max],fragi = 0,fragx = 0;

	printf("\n\tMemory Management Scheme - First Fit");
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
	printf("\nExternal Fragmentation = %d\n",fragx);

}
