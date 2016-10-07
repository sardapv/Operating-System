#include"myheader.h"

int search_in_INS	(char tok1[16]){
	int i;
	for(i=0; i<5; i++) {
		if(strcmp(tok1,INS[i]) == 0)
			return i+1;
	}
	return (-1);
}

int search_in_ASD(char tok1[16]){
	int i;
	for(i=0; i<6; i++) {
		if(strcmp(tok1,ASD[i]) == 0)
			return i+1;
	}
	return (-1);
}

int search_in_reg(char tok1[16]){
	int i;
	for(i=0; i<4; i++) {
		if(strcmp(tok1,reg[i]) == 0)
			return i+1;
	}
	return (-1);
}

int search_in_DL(char tok1[16]){
	int i;
	for(i=0; i<3; i++) {
		if(strcmp(tok1,declstat[i]) == 0)
			return i+1;
	}
	return (-1);
}

int litral_value(char tok2[16]){
	int len = strlen(tok2);
	int i , j;
	j=0;
	char a[16];
	tok2[len] = '\0';
	for (i=2 ; tok2[i] != 39; i++, j++)
		a[j] = tok2[i];
	a[j] = '\0';
	//	printf("a = %s   tok2 = %s", a, tok2);
	return (atoi(a));
}

int search_in_symbol_tab(char tok1[16], int counts){
	int  i;
	for (i=0; i<counts; i++) {
		if (strcmp(tok1,s[i].symbol_name) == 0)
			return i;
	}
	return (-1);
}

void pass1(){
	int lc=0,i=0,n,m,m1,m2,m3,m4,k1,a=0,ltorg=0,litral=0,value,x;
	char buffer[80],tok1[10],tok2[10],tok3[10],tok4[10];
	sp=fopen("input.txt","r");
	ip=fopen("ic.txt","w");
	while(fgets(buffer,80,sp)){
		n = sscanf(buffer,"%s%s%s%s",tok1,tok2,tok3,tok4);
		switch(n)
		{
			case 1 :  // 1 label only                                                                                                  
				m = search_in_INS(tok1);
				POOLTAB[countp] = l[a].litral_no;
				a = a+litral;
				countp++;
				litral=0;
				if(m==2){
					x=lc;
					for(i=POOLTAB[countp-1];i<=countl;i++){
						l[i-1].litral_addr = lc;
						lc++;
					}
					for(i=POOLTAB[countp-1];i<=countl;i++){
						value=litral_value(l[i-1].litral_name);
						printf("\t(AD,0%d) (%d)\n",m,value);
						fprintf(ip,"AD 0%d %d\n",m,value);
						x++;
					}
				}
				else{
					if(ltorg==0){
						for(i=0;i<countl;i++){
							l[i].litral_addr = lc;
							value=litral_value(l[i].litral_name);
							printf("\t(AD,0%d) (%d)\n",m,value);
							fprintf(ip,"AD 0%d %d\n",m,value);
							lc++;
						}
					}
					else{
						for(i=POOLTAB[countp-1];i<=countl;i++){
							l[i-1].litral_addr = lc;
							value=litral_value(l[i-1].litral_name);
							printf("\t(AD,0%d) (%d)\n",m,value);
							fprintf(ip,"AD 0%d %d\n",m,value);
							lc++;
						}
					}
					ltorg++;
				}
				if(m==1){
					lc=0;
					printf("\t(AD,0%d) (C,%d)\n",m,lc);
					fprintf(ip,"AD 0%d C %d\n",m,lc);
				}
				break;
				//2 labels catched
			case 2 : m = search_in_INS(tok1);  //START 200
				 if(m==1){
					 lc = atoi(tok2);
					 printf("\n\t(AD,0%d) (C,%d)\n",m,lc);
					 fprintf(ip,"AD 0%d C %d\n",m,lc);
				 }
				 else
					 lc = atoi(tok2);
				 break;

				 //3 lables catched
			case 3 : m1 = search_in_ASD(tok1);
				 m2 = search_in_reg(tok2);
				 m3 = search_in_INS(tok2);
				 if(m1>=1){
					 if(tok3[0]=='='){
						 l[countl].litral_no = countl+1;
						 strcpy(l[countl].litral_name,tok3);
						 printf("\t(IS,0%d) (%d)(L,%d)\n",m1,m2,l[countl].litral_no);
						 fprintf(ip,"IS 0%d %d L %d\n",m1,m2,l[countl].litral_no);
						 countl++;
						 litral++;
					 }
					 else{
						 int m11=search_in_symbol_tab(tok3,counts);
						 if(m11==-1){
							 s[counts].symbol_no = counts+1;
							 strcpy(s[counts].symbol_name,tok3);
						 }
						 printf("\t(IS,0%d) (%d)(S,%d)\n",m1,m2,s[counts].symbol_no);
						 fprintf(ip,"IS 0%d %d S %d\n",m1,m2,s[counts].symbol_no);
						 counts++;
					 }
				 }
				 else{
					 if(strcmp(tok2,"DC")==0){
						 m4=search_in_symbol_tab(tok1,counts);
						 s[m4].symbol_addr = lc;
						 k1=atoi(tok3);
						 printf("\t(AD,05) (C,%d)\n",k1);
						 fprintf(ip,"AD 05 C %d\n",k1);
					 }
					 else
						 if(strcmp(tok2,"DS")==0){
							 m4=search_in_symbol_tab(tok1,counts);
							 s[m4].symbol_addr = lc;
							 x=lc;
							 k1=atoi(tok3);
							 lc +=  k1 - 1;
							 printf("\t(AD,06) (C,%d)\n",k1);
							 fprintf(ip,"AD 06 C %d\n",k1);
						 }
				 }
				 if(m3==4){
					 m4=search_in_symbol_tab(tok3,counts);
					 s[counts].symbol_no = counts+1;
					 strcpy(s[counts].symbol_name,tok1);
					 s[counts].symbol_addr=  s[m4].symbol_addr;
					 counts++;
					 lc--;
				 }
				 lc++;
				 break;
			case 4 :
				 s[counts].symbol_no = counts+1;
				 strcpy(s[counts].symbol_name,tok1);
				 s[counts].symbol_addr = lc;
				 counts++;
				 m1 = search_in_ASD(tok2);
				 m2 = search_in_reg(tok3);
				 if(m1>=01){
					 if(tok3[0]=='='){
						 l[countl].litral_no = countl+1;
						 strcpy(l[countl].litral_name,tok4);
						 printf("\t(IS,0%d) (%d)(L,%d)\n",m1,m2,l[countl].litral_no);
						 fprintf(ip,"IS 0%d %d L %d\n",m1,m2,l[countl].litral_no);
						 countl++;
						 litral++;
					 }
					 else{

						 if(search_in_symbol_tab(tok4,counts) == -1){
							 s[counts].symbol_no = counts+1;
							 strcpy(s[counts].symbol_name,tok4);
						 }
						 printf("\t(IS,0%d) (%d)(S,%d)\n",m1,m2,l[countl].litral_no);
						 fprintf(ip,"IS 0%d %d S %d\n",m1,m2,s[counts].symbol_no);
						 counts++;
					 }
				 }
				 else{
					 if(strcmp(tok3,"DC")==0)
					 {
						 m4=search_in_symbol_tab(tok2,counts);
						 s[m4].symbol_addr = lc;
						 k1=atoi(tok4);
						 printf("\t(AD,05) (C,%d)\n",k1);
						 fprintf(ip,"AD 05 C %d\n",k1);

					 }
					 else
						 if(strcmp(tok3,"DS")==0){
							 m4=search_in_symbol_tab(tok2,counts);
							 s[m4].symbol_addr = lc;
							 x=lc;
							 k1=atoi(tok4);
							 printf("\t(AD,06) (C,%d)\n",k1);
							 fprintf(ip,"AD 06 C %d\n",k1);
						 }
				 }
				 lc++;
				 break;
		}
	}
	fclose(ip);
	printf("+-----------------------------------+\n");
}

void display_symbol_table(){
	int i = 0;
	tp = fopen("symtab.txt","w");
	//printf("--------------------- Symbol Table --------------------------\n");
	printf("\n+----------------------------------------------------+\n");
	printf("\t%-10s\t%-10s\t%-10s","Sym_No", "Sym_Name", "Sym_Addr");
	printf("\n+----------------------------------------------------+\n");
	for (i=0; i<counts; i++){
		printf("\t%-10d\t%-10s\t%-10d\t\n", s[i].symbol_no, s[i].symbol_name, s[i].symbol_addr);
		fprintf(tp,"\t%-10d\t%-10s\t%-10d\t\n", s[i].symbol_no, s[i].symbol_name, s[i].symbol_addr);
	}
	fclose(tp);
	printf("+----------------------------------------------------+\n");	
}

void display_litral_table(){
	int i = 0;
	tp = fopen("littab.txt","w");
	//	printf("--------------------- Litral Table --------------------------\n");
	printf("\n+----------------------------------------------------+\n");
	printf("\t%-10s\t%-10s\t%-10s","Lit_No", "Lit_name", "Lit_Addr");
	printf("\n+----------------------------------------------------+\n");
	for (i=0; i<countl; i++){
		printf("\t%-10d\t%-10s\t%-10d\t\n", l[i].litral_no, l[i].litral_name, l[i].litral_addr);
		fprintf(tp,"\t%-10d\t%-10s\t%-10d\t\n", l[i].litral_no, l[i].litral_name, l[i].litral_addr);
	}
	fclose(tp);
	printf("+----------------------------------------------------+\n");
}

void display_Pool_Tab(){
	int i = 0;
	pt = fopen("pooltab.txt","w");
	//	printf("--------------------- POOL TAB --------------------------\n");
	printf("\n+----------------------------------------+\n");
	printf("\t%-10s\t%-10s","Pool_No", "Pool_Index");
	printf("\n+----------------------------------------+\n");	
	for (i=0; i< countp;i++) {
		printf("\t%-10d\t%-10d\n", i+1, POOLTAB[i]);
		fprintf(pt,"\t%-10d\t%-10d\n", i+1, POOLTAB[i]);
	}
	fclose(pt);
	printf("+----------------------------------------+\n");
}

int main() {
	int choice;
	char buffer[64];
	sp = fopen("input.txt","r");
	printf("\n+--------------------------+\n");
	while(fgets(buffer,80,sp))
		printf("\t%s",buffer);
	fclose(sp);
	printf("\n+----------------------------+");
	printf("\n\t********** Intermediate Code ***********\n");
	pass1();
	printf("\t********** Symbol Table ************\n");
	display_symbol_table();
	printf("\t********** Litral Table ***********\n");
	display_litral_table();
	printf("\t********** Pool Table ************\n");
	display_Pool_Tab();
	printf(" \n\n\t\t* * * Bye ;) * * *\n\n");
	return 0;
}
