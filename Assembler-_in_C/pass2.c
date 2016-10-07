#include"myheader.h"

void main(){
	int ch;
	char buffer[80];
	
	accept();
	generate_mc();
	printf("\n------- MACHINE CODE -----\n\n");
	mp=fopen("mc.txt","r");
	while(fgets(buffer,80,mp)) 
		printf("%s",buffer);
	fclose(mp);
	printf("\n+------------------------+");
	printf("\n\t\t--- BYE ;) ---\n\n");
}

int lc,ptb;
int sn,ln,pn;

void accept(){
int i=1,index;
	char array[80];
	fp=fopen("symtab.txt","r");
	llp=fopen("littab.txt","r");
	pt=fopen("pooltab.txt","r");
	while(fgets(array,80,fp)){
		sscanf(array,"%d%s%d",&index,s[i].symbol_name,&s[i].symbol_addr);
		s[i].symbol_no=index;i++;
	}
	i=1;
	while(fgets(array,80,llp)){
		sscanf(array,"%d%s%d",&index,l[i].litral_name,&l[i].litral_addr);
		l[i].litral_no=index;i++;
	}
	i=1;
	while(fgets(array,80,pt)){
		sscanf(array,"%d%d",&index,&pooltable[i]);
	i++;
	}
	fclose(fp);
	fclose(llp);
	fclose(pt);
}

void generate_mc(){
	char buffer[80],tok1[10],tok2[10],tok3[10],tok4[10],tok5[10];
	int n,x,i;
	int temp;
	ip=fopen("ic.txt","r");
	mp=fopen("mc.txt","w");

	while(fgets(buffer,80,ip)){
		n=sscanf(buffer,"%s%s%s%s%s",tok1,tok2,tok3,tok4,tok5);
		switch(n){
			case 2: lc=0;
				break;
			case 3:  //ltorg
				fprintf(mp,"\t00 – 00%s\n",tok3);
				break;
			case 4: //start with const.
				if(strcmp(tok2,"01")==0){
					x=atoi(tok4);
					lc=x;
				}
				if(strcmp(tok2,"05")==0){
					temp=atoi(tok4);
					fprintf(mp,"\t00 – 00%s\n",tok4);
				}
				if(strcmp(tok2,"06")==0){
					temp=atoi(tok4);
					for(i=0;i<temp;i++)
						fprintf(mp,"\t00\n");
				}
				break;
			case 5:  //imperative statements
				if(strcmp(tok4,"S")==0){
					temp=atoi(tok5);
					fprintf(mp,"\t%s %s %d\n",tok2,tok3,s[temp].symbol_addr);
				}
				if(strcmp(tok4,"L")==0){
					temp=atoi(tok5);
					fprintf(mp,"\t%s %s %d\n",tok2,tok3,l[temp].litral_addr);
				}
				break;
		} //switch
	} //while
	fclose(ip);
	fclose(mp);
}
