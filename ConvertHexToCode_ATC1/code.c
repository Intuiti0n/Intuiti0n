#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------- ESTRUTURAS, FUNÇOES DE ABRIR/FECHAR FICHEIROS E DE LIMPAR AS ESTRUTURAS --------------------------------------------
struct instrucao 
{
	unsigned int flag_mnemonica :1 ;
	unsigned int flag_operando :1 ;
	unsigned int flag_valor :1 ;
	unsigned int flag_endereco :1 ;
	unsigned int flag_label :1 ;
	char label [50];
	char offset[5];				//Vai ficar com os offset para os saltos (numa string em hexadecimal. O PC esta em decimal)
	char mnemonica [5];
	char operando [20];
	char valor [20];
	char endereco [20];			//Usado para a instruçao CJNE (o endereço de salto)
	char temp [20];				//String que vai servir para comparar no ficheiro  (ex: MOV 75H, #5H -> MOVH,#) 
	short int PC;				//2 bytes para o program_counter
}ins;

struct opcode					//Vai ser o "dicionário". Estrutura para as strings q vêm do ficheiro "opcode"
{
	char comando[14];			//ex: MOVA,H
	char tamanho[1];			//ex: 1 (byte)
	char opcode[2];				//ex: EA
}op;

struct ficheiros{
	FILE *in, *hex, *opcodes;
}fich;


int abrir_ficheiros()
{
	char nome_in[80];
	printf("Ficheiro Origem: "); scanf("%79s%*c", &nome_in);
	if ((fich.in = fopen ( nome_in, "r")) == NULL ) {											//Ficheiro .a51
		fprintf(stderr, "Abertura de \"%s\" falhou ", nome_in); perror("because"); return 1;
	}
	nome_in[strlen(nome_in)-3]='h';	nome_in[strlen(nome_in)-2]='e'; nome_in[strlen(nome_in)-1]='x';   
 	printf("Ficheiro Destino: "); printf("%s\n", nome_in);
	if ((fich.hex = fopen ( nome_in, "w")) == NULL ) {											//Ficheiro Hex
		fprintf(stderr, "abertura de \"%s\" falhou ", nome_in); perror("because"); return 1;
	}
}

void fechar_ficheiros(){
	fclose(fich.in); fclose(fich.hex); fclose(fich.opcodes);
}

int clear_struct(){		//limpa a estrutura para esta nao vir com as informaçoes da linha de codigo anterior
	int i=0;
	ins.flag_endereco = ins.flag_mnemonica = ins.flag_operando = ins.flag_valor= ins.flag_label = 0;		//limpa as flags
	for(i; i<5;i++) {ins.mnemonica[i]=0;}								
	for(i=0; i<20;i++) {ins.operando[i]=ins.valor[i]=ins.endereco[i]=ins.temp[i]=0;}
	for(i=0; i<51;i++) {ins.label[i]=0;}
}

void clear_struct_op(){
	int i=0;
	for (i=0;i<14;i++) op.comando[i]=0;
	op.tamanho[0]=0;
	op.opcode[0]=0; op.opcode[1]=0;
}
//............................................ Lista Ligada................................................................
struct nodo {
	char nome[50];
	int endereco; 
	struct nodo *prox;
};

struct nodo *inicio;

void iniciar_lista(){
	struct nodo *aux;
	aux= (struct nodo*) malloc(sizeof(struct nodo));
	inicio= aux;
	inicio->prox=NULL;
}

void inserir_na_lista(){
	struct nodo *novo;
	novo = (struct nodo*) malloc(sizeof(struct nodo)); 
	novo->prox= inicio->prox;
	inicio->prox= novo;
	strcpy(novo->nome,ins.label);
	novo->endereco = ins.PC;
}

int procurar_label (char label[]){		/*Funçao que retorna o endereço de uma label*/
	struct nodo *atual;								//É com o "atual" q vamos percorrer o vetor. Assim nao se "perde" o inicio da lista
	atual = (struct nodo*) malloc(sizeof(struct nodo)); 
	atual = inicio->prox;							//posiciona-se no inicio da lista
	while(atual!= NULL) 
	{
		//A estrutura atual tem o msm conteudo da posiçao 0 do vetor		
		if (strcmp(atual->nome,label)==0) return atual->endereco;	
		atual = atual->prox;						//O "atual->inicio" fica a apontar para a proxima posiçao
	}
	return -1;										//Não existe a label. Retorna -1 como erro
}

void imprime_lista() {
	struct nodo *aux;
	aux= (struct nodo*) malloc (sizeof(struct nodo));
	aux = inicio->prox;
	while (aux!=NULL){
	printf("Label: %s   Endereco: %d\n",aux->nome,aux->endereco);
	aux= aux->prox;
	}

}

//---------------------------- FUNÇOES DE TRATAMENTO DAS STINGS DO FICHEIRO .A51 -------------(MOV A, #75H -> MOVA,#)-----

void tratar_str (char str[], int n){		/*Esta funçao separa a string e guarda as varias partes na estrutura "instruçao" */
	char mnemonica[20]={0}, operando[6]={0}, valor[6]={0};
	int flag_eq = 0, i=0, j=0, k=0, l=0, m=0;			//"i" é para o vetor mnemonica, "j" é para o vetor operando e "k" é para o vetor valor	
	for (i=0;i<strlen(str);i++) if(str[i]==':') {printf("\nLABEL\n"); declaracao_label(str); ins.flag_label=1;}
	i=0;
	if(ins.flag_label==0){
	while(str[i]!='\0'){
		while(ins.flag_mnemonica==0 && (str[i]==' '||str[i]=='\t')) i++;
		if (str[i]==' ' &&  flag_eq==0) flag_eq=50;			//ex: MOV A, #50H
		if (str[i]==',' && flag_eq!=2) flag_eq=51;
		if (str[i]==',' && flag_eq==2) flag_eq=3;
		
		if (flag_eq==0 && str[i]!='\n') {ins.mnemonica[m]=str[i];m++; ins.flag_mnemonica=1;}
		if (flag_eq==1 && str[i]!='\n') {ins.operando[j]=str[i]; j++; if(str[i]==' ')j--; ins.flag_operando=1;}
		if (flag_eq==2 && str[i]!='\n') {ins.valor[k]=str[i]; k++; if(str[i]==' ') k--; ins.flag_valor=1;}
		if (flag_eq==3 && str[i+1]!='\n') {ins.endereco[l]=str[i+1]; l++; if(str[i+1]==' ') l--; ins.flag_endereco=1;}

		if (flag_eq==50) flag_eq=1;
		if (flag_eq==51) flag_eq=2;
		i++;
	}

	for (i=0;i<strlen(ins.mnemonica);i++) {if(ins.mnemonica[i]>=97) ins.mnemonica[i] -=32;}		//Passa para maiusculas a mnemonica (ex:mov -> MOV)
	for (i=0;i<strlen(ins.operando);i++) {if(ins.operando[i]>=97) ins.operando[i] -=32;}		//Passa para maiusculas o operando (ex: a -> A)
	for (i=0;i<strlen(ins.valor);i++) {if(ins.valor[i]>=97) ins.valor[i] -=32;}					//Passa para maiusculas o valor (ex: 75h -> 75H)
	for (i=0;i<strlen(ins.endereco);i++) {if(ins.endereco[i]>=97) ins.endereco[i] -=32;}		//Passa para maiusculas o endereço no CJNE (ex: loop -> LOOP)
	
	if (n!=0){printf ("mnemonica:%s\n",ins.mnemonica);
	printf ("operando:%s\n",ins.operando);						//estes printf so servem p ser tipo debug, no fim vamos apaga-los
	printf ("valor:%s\n",ins.valor);
	printf ("endereco de salto:%s\n",ins.endereco);
	printf ("flag_mnemonica: %d\n",ins.flag_mnemonica);
	printf ("flag_operando: %d\n",ins.flag_operando);
	printf ("flag_valor: %d\n",ins.flag_valor);
	printf ("flag_endereco: %d\n",ins.flag_endereco);}
	if(strcmp(ins.mnemonica,"CSEG")!=0) criar_temp(n);
	else cseg();
	}
	//if (strcmp(str, "END") == 0) { imprime_hex_file(":00000001\0"); }
}

int cseg (){
	int a=0, i=2;
	char opc [5] ={0};
	while(ins.operando[i]!='H') {opc[i-2]=ins.operando[i]; i++;}	//Apaga o "AT" e o "H" (ex: AT50H -> opc= 50)
	a= atoi(opc);
	ins.PC = a;
}

int criar_temp(int n){	/* Esta é uma funçao + coordenadora. Passa os parametros (estruturas e flags) para a funçao "escreve_temp" */	
	escreve_temp (ins.mnemonica,ins.flag_operando);					// ex: MOV 7H, #55H    Passa para o temp a mnemonica (temp= MOV)	
	if (strlen(ins.operando)!=0) escreve_temp (ins.operando,ins.flag_valor);						//temp= MOVH  &&  temp= MOVH,
	if (strlen(ins.valor)!=0) escreve_temp (ins.valor,ins.flag_endereco);						//temp= MOVH,#
	if (strlen(ins.endereco)!=0) escreve_temp (ins.endereco,0);									//Para o CJNE
	if(n!=0) printf("%s\n\n",ins.temp);
}

int escreve_temp (char s[],int flag){		/* Com a ajuda da "etiqueta", a "escreve_temp" é a responsavel pela escrita na string temp */
	static int i=0;
	int j=0;
	if (i!=0 && (strcmp(s,ins.mnemonica)==0)) i=0;
	if (strcmp(s,ins.mnemonica)==0) {while(s[i]!='\0') {ins.temp[i] = s[j]; i++;j++;}}	//Passa para o temp a mnemonica (temp= MOV)
	else{
		while(s[j]!='\0') {if(s[j]=='.') {ins.temp[i]='.';i++;} j++;}			//Poe o ponto qd é ao bit (ex. 20.5H -> .H)
		switch(etiqueta(s)){
			case 0: ins.temp[i]='L'; i++; break;								//temp= JMPL
			case 1: { if(s[0]>=48 && s[0]<58) {ins.temp[i]='H'; i++;}			//temp= MOVH
						else {ins.temp[i]=s[0];i++;} } break;					//temp= MOV#
	 		case 2: j=0; while(s[j]!='\0') {
							ins.temp[i] = s[j]; i++;j++;} break;
		}
		if(strcmp(s,ins.operando)==0 && flag==1) {ins.temp[i]=',';i++;}
		if(strcmp(s,ins.valor)==0 && flag==1) {ins.temp[i]=',';i++;}
	}
}

int etiqueta (char s[]){	  /* Serve para na funçao "criar_temp" ver se estamos perante uma etiqueta ou um registo (por exemplo) */
	int i=0;
	char string [13]= "0123456789#";								//String de variaveis programaveis ao bit (compara 1 posiçao de cada vez)
	char var [5]="CRAB";											//Variaveis nao programaveis ao bit (p.e. nao se pode usar R2.6)
	char string_2_pos[5]= "OV@R";									
	
	if (s[0]=='R') {if(s[1]<48 || s[1]>=56)  return 0;}								//Para nao confundir um registo com uma etiqueta começada por R
	if (s[0]==var[2] && s[1]==var[3] && strlen(s)==2) return 2;						// Para o AB
	for(i=0;i<14;i++) if (s[0]==string[i]) return 1;								//Se a 1ª posiçao for igual alguma da string, entao é um valor (ex:70H ou R3)
	for(i=0;i<3;i++) if (s[0]==var[i] && strlen(s)<=3) return 1;					// (ex:A  B   C)
	if (s[0]==string_2_pos[0] && s[1]==string_2_pos[1] && strlen(s)==2) return 1;	// Para o OV
	if (s[0]==string_2_pos[2] && s[1]==string_2_pos[3] && strlen(s)==3) return 1;	// Para o @R	
	if ((strcmp(s,"@A+DPTR")==0) || (strcmp(s,"@A")==0) || (strcmp(s,"@A+PC")==0) || (strcmp(s,"DPTR")==0) || (strcmp(s,"@DPTR")==0)) return 2;
	return 0;
}		// return:  0 -> label		1 -> endereço memoria/variavel (0,1,2,3,4,5,6,7,8,9,A,B,C,#,OV,@R)   2 -> apontadores (@A+DPTR, @A)

int declaracao_label(char s[]){	/* Qd é encontrada a declaraçao de uma etiqueta (ex: "LOOP:"), é aqui q se poe o nome desta na string "ins.label" */
	int i=0,j=0;
	while (s[i]!=':') {ins.label[j]=s[i]; i++; j++; 
					   if(s[i-1]==' '||s[i-1]=='\t') j--;}
	for (i=0;i<strlen(ins.label);i++) {if(ins.label[i]>=97) ins.label[i] -=32;}		//Converte a etiqueta em maiusculas
	printf("Etiqueta:%s\n\n",ins.label);
	return 1;			//Retorna 1 para na main saber que é uma label e que se tem de por na lista
}
//........................................... Incrementar o Program counter ..............................................
void converte_hexa(unsigned short int a){
	sprintf(ins.offset, "%02X", a);
	puts(ins.offset);
}

void incrementar_PC (){
	int a= op.tamanho[0] - 48;
	ins.PC+= a;
}

void offset (char s[]){		/* Retorna o offset de um call, jmp,etc ou -1 se a label procurada nao existir */ 
	short int a= procurar_label (s);		//Esta funçao retorna o endereço da label ou -1 se esta nao estiver na lista
	int size = op.tamanho[0]-48;
	if (a >= 0) { a = a - ins.PC; }				//Se a label existe (a!=-1), subtrai ins.PC (valor do PC atual) ao "a" (endereço da label) 
	a = a & 0xFF;
	converte_hexa(a);								//Converte o "a" num hexadecimal (fica guardado no ins.offset)
}
//------------------------------------------------------------------------------------------------------------------------


void construir_string_opcodes(char origem[], char destino[])
{
	int i=0, j=0;
	while(destino[j]!='\0') j++;
	while(origem[i]!='\0')	{destino[j]=origem[i]; i++; j++;}
}

int soma_registo(char registo, char b[]){
	int a;
	char aux=b[1];//aux=2º digito do opcode
	aux = aux + registo - 48;//somar o numero do registo ao 2º digito do opcode
	if (aux > 57) aux = aux - 48 - 10 + 'A';//Se o digito ultrapassar o 9, converter para letra do hexadecimal
	a = aux;
	return a;
}

void procura_opcode(char opcodes[]){	/* A partir da string temp, vai-se comparar com a lista de instruçoes permitidas para certificar q esta tudo em ordem */
	int i=0, parar=0, j=32, k=1, contador_opcodes=0;			/* Se for uma instruçao valida, vao ser copiados as caracteristicas (mne.,tamanho,hexa) desta para a estrutura "opcode" */
	char aux[19]= {0};						//String para onde vai toda a instruçao (mnemonica + tamanho + hexa) 
	char temp[39] = "";				//vetor de segurança, maior do que o dos opcodes, para o caso de exceder o tamanho;
	char extra[10] = "";			//vetor para ficar com o excesso de opcodes
	char teste[44] = ":000000";
	fich.opcodes = fopen ( "Opcodes.txt", "r");
	while(!feof(fich.opcodes) && parar==0)
	{
		fgets(aux,19,fich.opcodes);
		while(aux[i]!=' ') {op.comando[i]=aux[i];i++;}
		if (strcmp(ins.temp,op.comando)==0) 
		{
			i+=1;
			op.tamanho[0]=aux[i]; i+=2;
			contador_opcodes=atoi(op.tamanho);//contador de opcodes fica com o numero de opcodes que devem ser escritos na instruçao
			printf("PC antes: %d\n",ins.PC); incrementar_PC(); printf("PC: %d\n",ins.PC);
			instrucao_valida();
			//Escrever opcodes dos operandos
			while(k<=contador_opcodes)
			{
				//quando k=1, copia o opcode da instruçao e acrescenta a string opcodes
				if (k == 1) { op.opcode[0] = aux[i]; i++; op.opcode[1] = aux[i];}
				//quando k=2 e contador =2, copia o opcode do operando
				if (k == 2 && contador_opcodes == 2)
				{
					//ver se existe um 'L' na string aux, ou seja se a instruçao tem como 2º operando uma label
					//como entra em conflito com instruçoes que possuem L existe 1 condiçao X1
					if (strchr(aux,'L')==NULL)
					{
						if (ins.valor[0] == '#') { op.opcode[0] = ins.valor[1]; op.opcode[1] = ins.valor[2]; }
						else if (ins.valor[0] == 'A') { op.opcode[0] = ins.operando[0]; op.opcode[1] = ins.operando[1]; }
						else if (ins.operando[2] == 'H') { op.opcode[0] = ins.operando[0]; op.opcode[1] = ins.operando[1]; }
						else if (ins.valor[0] != '#') { op.opcode[0] = ins.valor[0]; op.opcode[1] = ins.valor[1]; }
					}
					else if (strchr(aux, 'L') != NULL){
						if (aux[6] == 'L') {//CONDIÇAO PARA DJNZ
							offset(ins.valor); op.opcode[0] = ins.offset[0]; op.opcode[1] = ins.offset[1];
						}
						//se tamanho==2, tipo DJNZ r0,label
						//se tamanho==3 tipo CJNE A,#13H,LABEL
					//if(op.tamanho[0]==2) {offset(ins.operando); }
						//condiçao X1
						else if (ins.operando[2] == 'H') { op.opcode[0] = ins.operando[0]; op.opcode[1] = ins.operando[1]; }
						//Caso ORLA,# OU ANDLA,# OU XRLA,#
						else if (ins.valor[0] == '#') { op.opcode[0] = ins.valor[1]; op.opcode[1] = ins.valor[2]; }
						else if (ins.valor[2] == 'H') { op.opcode[0] = ins.valor[0]; op.opcode[1] = ins.valor[1]; }
						else { offset(ins.valor); op.opcode[0] = ins.offset[0]; op.opcode[1] = ins.offset[1]; } //Aqui meti uma coisa à sorte, é suposto metermos o offset da label
						//o Afonso é que tem que meter isso pq eu não sei bem como meter}
					}
				}
				if (k == 2 && contador_opcodes == 3)
				{
					//Caso do opcode do operando de DJNZ 30h,main
					if (strcmp(ins.operando, "DPTR") == 0) { op.opcode[0] = '0'; op.opcode[1] = '0'; }
					else if (ins.operando[2] == 'H') { op.opcode[0] = ins.operando[0]; op.opcode[1] = ins.operando[1]; }
					//Caso CJNE R0,#imed,label
					else if (ins.valor[0] == '#') { op.opcode[0] = ins.valor[1]; op.opcode[1] = ins.valor[2]; }
					else if (ins.operando[0] == 'A'){ op.opcode[0] = ins.valor[0]; op.opcode[1] = ins.valor[1]; }
				}
				if (k == 3)
				{
					if (aux[8] == 'L') {//CONDIÇAO PARA CJNE
						offset(ins.endereco); op.opcode[0] = ins.offset[0]; op.opcode[1] = ins.offset[1];}
					else if (aux[6] == 'L') {//CONDIÇAO PARA DJNZ
						offset(ins.valor); op.opcode[0] = ins.offset[0]; op.opcode[1] = ins.offset[1];
					}
					//criar caso para labels, calcular offset e imprimir offset. offset =pc da label-tamanho da instruçao atual
					//sabemos que existe label porque fica ,L
					//caso ORLH,#
					else if (ins.valor[3] == 'H') { op.opcode[0] = ins.valor[1]; op.opcode[1] = ins.valor[2]; }
					else if (ins.valor[2] == 'H') { op.opcode[0] = ins.valor[0]; op.opcode[1] = ins.valor[1]; }
					else { offset(ins.operando); op.opcode[0] = ins.offset[0]; op.opcode[1] = ins.offset[1]; } //Aqui meti uma coisa à sorte, é suposto metermos o offset da label
					//o Afonso é que tem que meter isso pq eu não sei bem como meter
				}
				//Quando deteta um registo no 1º operando temos de somar o que esta a seguir ao R ao opcode
			if (ins.operando[0] == 'R'&&k==1) op.opcode[1] = soma_registo(ins.operando[1], op.opcode);
			if (ins.valor[0] == 'R'&&k==1) op.opcode[1] = soma_registo(ins.valor[1], op.opcode);
			if (ins.operando[0] == '@'&&k == 1 && ins.operando[1] == 'R') op.opcode[1] = soma_registo(ins.operando[2], op.opcode);
			if (ins.valor[0] == '@'&&k == 1 && ins.valor[1] == 'R') op.opcode[1] = soma_registo(ins.valor[2], op.opcode);
				//construir_string_opcodes(op.opcode, opcodes);
				//Receber para temp os opcodes; Se a posiçao 33 estiver ocupada, copia ate a posiçao 32 para a string opcodes
				//Mete o excesso em aux
			//encoding da instruçao MOV DIRECT DIRECT é especial
			if (strcmp(aux, "MOVH,H 3 85\n") == 0 && k == 3) {
				int size = strlen(opcodes) - 2;
				extra[0] = opcodes[size];
				extra[1] = opcodes[size + 1];
				opcodes[size] = op.opcode[0];
				opcodes[size+1] = op.opcode[1];
				strcpy(op.opcode, extra);
			}
				strcat(opcodes, op.opcode);
				if (strlen(opcodes)> 31)
				{//a cada vez que na string onde sao escritos os opcodes o tamanho excede os 16 bytes, imprime a linha
					strncpy(temp, opcodes, 32);//copia para temp os 32 primeiros chars da string opcodes
					//imprimir linha com opcodes
					trata_hex(teste, temp);
					imprime_hex_file(teste);
					while (opcodes[j] != '\0') aux[j - 32] = opcodes[j++]; aux[j - 32] = '\0';//copia para aux o excesso
					opcodes[0] = '\0';//limpar string temp
					strcat(opcodes, aux);//adiciona à string temp o que ficou em excesso;
					aux[0] = '\0';//limpar string aux
				}
				k++;
		}
			parar=1;
	}
		clear_struct_op();
		i=0;
	}	
	fclose(fich.opcodes);
}

int instrucao_valida(){printf("A instrucao existe!!!\n\n");}


void opcode_lista(){	/* Esta funçao é so para a 1ª passagem pelo codigo. So se preocupa em ficar com o tamanho */
	int i=0, parar=0;			/* Se for uma instruçao valida, copia o tamanho desta para a estrutura "opcode" */
	char aux[19]= {0};						//String para onde vai toda a instruçao (mnemonica + tamanho) 
	fich.opcodes = fopen ( "Opcodes.txt", "r");
	while(!feof(fich.opcodes) && parar==0)
	{
		fgets(aux,19,fich.opcodes);
		while(aux[i]!=' ') {op.comando[i]=aux[i];i++;}
		if (strcmp(ins.temp,op.comando)==0) 
		{
			i+=1;
			op.tamanho[0]=aux[i];
			incrementar_PC();
			parar=1;
		}
		clear_struct_op();
		i=0;
	}	
	fclose(fich.opcodes);
}












//-----------------------------------------------------FICHEIRO .HEX-----------------------------------------------------------------------------------
int mystrlen(char s[])	//retorna tamanho da string
{
	int i = 0;
	while (s[i++] != '\0');//i fica com o valor da posiçao do caracter a esquerda do '\0'
	i--;
	return i;
}

int elevado(int base, int expoente)
{
	int resultado = 1, i;
	for (i = 0; i < expoente; i++)
		resultado = resultado*base;
	//printf("%d", resultado);
	return resultado;
}

int hex2dec(char vect[])	//função usada no tp5 mas modificada para converter um vetor com 2 chars (1 byte de dados Ex: 02h)
{
	int dec = 0, j, aux = 0;
	for (j = 1; j>=0;j--){
		if (vect[j] >= '0'&& vect[j] <= '9') {
			dec = dec + (vect[j] - '0')*elevado(16, aux); aux++;
		}
		else if (vect[j] >= 'a'&& vect[j] <= 'f'){
			dec = dec + ((vect[j] - 'a') + 10)*elevado(16, aux); aux++;
		}
		else if (vect[j] >= 'A'&& vect[j] <= 'F'){
			dec = dec + ((vect[j] - 'A') + 10)*elevado(16, aux); aux++;
		}
	}
	return dec;
}

int trata_hex(char hex[], char opc[]){	//Recebe 2 strings, string original e a string com os opcodes
	//Altera o valor de SS-> Tamanho dos bytes de dados desta linha do ficheiro hex (máximo é 10H)
	static s = 0;
	char aux1[10] = "";
	int i= strlen(opc)/2;
	_itoa(i, hex, 16);//itoa ja existe numa biblioteca. _itoa porque o windows quer que se use esta
	
	hex[2] = hex[1];
	hex[1] = hex[0];
	if (i != 16) hex[2] = hex[1];
	if (i != 16) hex[1] = '0';
	hex[0] = ':';
	hex[3] = '\0';
	//Tratar do endereço da linha:
	sprintf(aux1, "%04X", s * 16);
	strcat(hex, aux1);
	aux1[0] = '\0';
	hex[7]='0';hex[8]='0';
	//converter chars para maiusculas
	if (hex[2] > 57) hex[2] = hex[2] - 32;
	//Adciona os opcodes à string original. 
	strcat(hex, opc);
	s++;
}

int imprime_hex(char linha[])
{
	printf("%s", linha);
	//printf("%s", opcodes);
	printf("%X\n", checksum(linha));
}



int imprime_hex_file(char linha[]){
	int i=0;
	fprintf(fich.hex,"%s", linha);
	//fprintf(hex,"%s", opcodes);
	fprintf(fich.hex,"%02X\n", checksum(linha));
}

int checksum(char linha[]){
	short int soma=0;
	char aux[3] = "";
	int size = 0;
	int i;
	size = mystrlen(linha);
	for (i = 1; i < size; i += 2)
	{
		aux[0] = linha[i];
		aux[1] = linha[i + 1];
		soma = soma + hex2dec(aux);
	}
	soma = soma & 0xFF;
	soma = soma ^ 0xFF;
	soma += 1;
	//printf("%X\n", soma);
	return soma;
}









//---------------------------------------------- MAIN ------------------------------------------------------------------
int main()
{
	char opcodes[40]={0};
	char linha[40] = ":10000000";
	char hex[44]="";
	char teste[44]="0300300002337A";
	char temp[100];
	
	iniciar_lista();
	abrir_ficheiros(); printf("\n\n");
	
	while (!feof(fich.in))
	{									//1ª passagem pelo codigo para fazer a lista de labels
		fgets(temp,200,fich.in);
		if (temp[0]!='\n') {
			tratar_str(temp,0); 
			opcode_lista();
			if(ins.flag_label==1) inserir_na_lista(); 
			clear_struct();
			clear_struct_op();
		}
	}
	ins.PC=0;
	imprime_lista(); printf("\n\n");
	fseek(fich.in,0,SEEK_SET);
	
	while (!feof(fich.in))
	{
		fgets(temp,200,fich.in);
		if (temp[0]!='\n') {
			tratar_str(temp,1); 
			procura_opcode(opcodes); 
			clear_struct();
			clear_struct_op();
		}
	}
	trata_hex(hex, opcodes);//escreve o que sobrar das instruções numa nova linha com tamanho menor do que 10h
	imprime_hex_file(hex);//escreve essa linha no ficheiro
	if (strcmp(temp, "END") == 0) imprime_hex_file(":00000001");//quando deteta que na string temporaria existe a instruçao end escreve a linha final
	
	printf("ISTO SAO OS OPCODES %s\n", opcodes);
	//checksum(hex);//so para testar se o checksum funciona
	imprime_hex(hex);
	fechar_ficheiros();
	getchar();
}
