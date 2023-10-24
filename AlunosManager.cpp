//bibliotecas utilizadas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
//constantes
#define TAMNOME 50
#define TAMSOBRENOME 50

//vari�veis de escopo global
typedef struct data{
	int dia, mes, ano;
}data;

typedef struct registro{
	char nome[TAMNOME], sobrenome[TAMSOBRENOME];
	data datadenascimento; //datadenascimento � uma struct do tipo data
	int prontuario;
	char curso[4];
}aluno;
aluno alunos[1000]; //alunos[1000] � um vetor de struct do tipo aluno/registro

int cont=0; //indica quantos alunos tem cadastrados

int para_mtd_ord_escolhido = 0; //armazena qual foi o �ltimo par�metro para o m�todo de ordena��o escolhido

//declara��o das fun��es
bool ValidaProntuario(int);  //recebe 1 inteiro como par�metro
//void cadastro();
void imprimir_todos();
void imprimir(int);
void imprimir_busca();
void ordenar();
void salvar();
void recuperar();
bool compara_info(aluno,aluno, int);
void trocar_alunos(aluno*, aluno*);
void merge_sort(int, int, int);
void merge(int, int, int, int);
void insertion_sort();
int particao(int, int, int);
void quick_sort(int, int, int);
int busca_binaria();

//fun��es para excluir
void excluir_nome(char*);	//recebe 1 ponteiro char como par�metro
void excluir_sobrenome(char*);	//recebe 1 ponteiro char como par�metro
void excluir_nome_sobrenome(char*, char*);	//recebe 3 ponteiros char como par�metro
void excluir_curso(char*);	//recebe 1 ponteiro char como par�metro
void excluir_prontuario(int); //recebe 1 inteiro como par�metro
void excluir_datanasc(int, int, int); //recebe 3 inteiros como par�metro

//fun��es de ordena��o
void selection_sort();

//fun��o para comparar
bool compara_data(struct data, struct data);

//fun��o principal
int main(void){
	//chama fun��o que recupera dados salvos
	recuperar();
	//[1,2,4,8,9,57]
	//vari�veis
	int opcao=0;
	
	//menu principal
	while(opcao!=7){
		printf("-------MENU PRINCIPAL------- \n");
		printf("1 - Cadastro de Aluno \n");
		printf("2 - Imprimir todos os Alunos cadastrados \n");
		printf("3 - Impressao por busca linear \n");
		printf("4 - Impressao por busca binaria \n");
		printf("5 - Ordenar Cadastro \n");
		printf("6 - Ordenar Cadastro - escolher o metodo \n");
		printf("7 - Sair \n");
		
		//seleciona a entrada
		printf("Escolha a opcao desejada: ");
		scanf("%d", &opcao);
		printf("\n");
		
		//cadastra aluno
		if (opcao == 1){
			cadastro();
		}
		
		//imprimi todos os alunos
		else if (opcao == 2){
			imprimir_todos();
		}
		
		//imprimi alunos especificados na busca
		else if (opcao == 3){
			imprimir_busca();
		}
		
		//realiza a busca bin�ria do aluno especificado na fun��o
		else if (opcao == 4){
			int posicao;
			
			busca_binaria();
		}
		
		//ordena struct de alunos de acordo com a op��o escolhida
		else if (opcao == 5){
			ordenar();
		}
		
		//ordena struct de alunos de acordo com o m�todo escolhido
		else if (opcao == 6){
			//vari�veis
			int opc=0;
			
			while(opc != 5){
				printf("Escolha o metodo de ordenacao: \n");
				printf("(1) - Quick Sort \n");
				printf("(2) - Merge Sort \n");
				printf("(3) - Insertion Sort \n");
				printf("(4) - Selection Sort \n");
				printf("(5) - Voltar para o Menu Principal \n");
				
				scanf("%d",&opc);
				
				//op��o 1 - Quick Sort
				if(opc == 1){
					int ini = 0;
					int fim = cont-1;
					int escolha;
					
					//menu de op��es para ordena��o
					printf("Digite qual opcao deseja utilizar para a ordenacao: \n");
					printf("(1) - Nome e sobrenome \n");
					printf("(2) - Sobrenome e nome\n");
					printf("(3) - Data de nascimento \n");
					printf("(4) - Prontuario \n");			
					printf("(5) - Curso \n\n");
					scanf("%d", &escolha);
					
					para_mtd_ord_escolhido = escolha; // altera o valor do par�metro escolhido para o m�todo de ordena��o
					
					quick_sort(ini, fim, escolha);
					
					printf("Ordenacao feita com sucesso! \n");
				}
				
				//op��o 2 - Merge Sort
				else if(opc == 2){
					int ini = 0;
					int fim = cont-1;
					int escolha;
					
					//menu de op��es para ordena��o
					printf("Digite qual opcao deseja utilizar para a ordenacao: \n");
					printf("(1) - Nome e sobrenome \n");
					printf("(2) - Sobrenome e nome\n");
					printf("(3) - Data de nascimento \n");
					printf("(4) - Prontuario \n");			
					printf("(5) - Curso \n\n");
					scanf("%d", &escolha);
	
					para_mtd_ord_escolhido = escolha; // altera o valor do par�metro escolhido para o m�todo de ordena��o
					
					merge_sort(ini, fim, escolha);
					
					printf("Ordenacao feita com sucesso! \n");
				}
				
				//op��o 3 - insertion Sort
				else if(opc == 3){
					insertion_sort();
				}
				
				//op��o 4 - selection Sort
				else if(opc == 4){
					selection_sort();
				}
				
				//op��o 5
				else if(opc == 5){
					break;
				}
				
				else{
					printf("Opcao invalida, tente novamente! \n \n");
				}
				
			}
		}
		
		//sair do programa
		else if (opcao == 7){
			printf("Salvando arquivo... \n");
			salvar();
			printf("Obrigado, fim do programa! \n");
		}
		
		else{
			printf("OPCAO INVALIDA, TENTE NOVAMENTE! \n");
		}
	}

}

//cadastra alunos
void cadastro(){
	int escolha, prontuario;
	
	//define n�mero de alunos a serem cadastrados
	printf("Digite quantos alunos deseja cadastrar: \n");
	scanf("%d", &escolha);
	
	//la�o para incrementar alunos na struct
	for(int i=0; i<escolha; i++){
		bool isProntuarioValido = false;
		//fun��o para verificar a exist�ncia do prontu�rio
		while(!isProntuarioValido){
			printf("Digite o prontuario do aluno: \n");
			scanf("%d",&prontuario);
			isProntuarioValido = ValidaProntuario(prontuario);
		}
		alunos[cont].prontuario = prontuario;
		
		printf("Digite o nome do aluno: \n");
		scanf("%s",&alunos[cont].nome);
		
		printf("Digite o sobrenome do aluno: \n");
		scanf("%s",&alunos[cont].sobrenome);
		
		printf("Digite o dia de nascimento do aluno: \n");
		scanf("%d",&alunos[cont].datadenascimento.dia);
		
		printf("Digite o mes de nascimento do aluno: \n");
		scanf("%d",&alunos[cont].datadenascimento.mes);
		
		printf("Digite o ano de nascimento do aluno: \n");
		scanf("%d",&alunos[cont].datadenascimento.ano);
		
		printf("Digite o curso do aluno: \n");
		scanf("%s",&alunos[cont].curso);
		
		printf("Aluno cadastrado com sucesso! \n");
		
		//incrementa o n�mero de alunos cadastrados
		cont++;
		
		//pausa a tela 
		system("pause");
		//limpa a tela
		system("cls");
	}
}

//imprimi todos os alunos
void imprimir_todos(){
	//vari�veis
	int i;
	
	//analisa se existem alunos cadastrados
	if(cont==0){
		printf("Nao existe aluno cadastrado");
	}
	
	//la�o que imprime todos os dados de cada aluno
	else{
		for(i=0; i<cont; i++){
			printf("Prontuario: %d \n", alunos[i].prontuario);
			printf("Nome: %s \n", alunos[i].nome);
			printf("Sobrenome: %s \n", alunos[i].sobrenome);
			printf("Data de nascimento: %d/%d/%d \n", alunos[i].datadenascimento.dia,alunos[i].datadenascimento.mes,alunos[i].datadenascimento.ano);
			printf("Curso: %s \n \n", alunos[i].curso);
		}
	}
	
	system("pause");
	system("cls");
}

//imprimi alunos especificados na busca
void imprimir_busca(){
	//vari�veis para a primeira parte
	int opcao=0, i, pront_al;
	char nome_al[50], sobre_al[50];
	//vari�vel boleana que define se algum aluno j� foi impresso
	bool verificacao_1;

	//vari�vel que decide se os alunos impressos ser�o exclu�dos
	int escolha;
	
	while(opcao!=7){
		printf("1 - Nome e sobrenome \n");
		printf("2 - Nome \n");
		printf("3 - Sobrenome \n");
		printf("4 - Prontuario \n");
		printf("5 - Data de Nascimento \n");
		printf("6 - Curso \n");
		printf("7 - Sair \n");
		printf("Escolha o tipo de busca que deseja: ");
		printf("\n");
		scanf("%d", &opcao);
		verificacao_1 = false;
		
		//NOME E SOBRENOME
		if (opcao==1){
			//define as entardas de nome e sobrenome
			printf("Digite o nome do aluno: \n");
			scanf("%s", &nome_al);
			printf("Digite o sobrenome do aluno: \n");
			scanf("%s", &sobre_al);
			
			//percorre a struct para selecionar nome e sobrenome escolhidos
			for(i=0; i<cont; i++){
				//a fun��o "strcmp" retorna "0" para strings iguais (string.h)
				if((strcmp(alunos[i].nome, nome_al) == 0) && (strcmp(alunos[i].sobrenome, sobre_al) == 0)){
						printf("Prontuario: %d \n", alunos[i].prontuario);
						printf("Nome: %s \n", alunos[i].nome);
						printf("Sobrenome: %s \n", alunos[i].sobrenome);
						printf("Data de nascimento: %d/%d/%d \n", alunos[i].datadenascimento.dia,alunos[i].datadenascimento.mes,alunos[i].datadenascimento.ano);
						printf("Curso: %s \n", alunos[i].curso);
						
						verificacao_1 = true;	
				}
			}
			if(verificacao_1 == false){
				printf("Nao existe aluno com os dados inseridos! \n");
			}
			else {
				printf("Deseja excluir os alunos impressos? \n");
				printf("1 - SIM \n");
				printf("2 - NAO \n");
				scanf("%d", &escolha);
				
				if(escolha == 1){
					printf("Excluindo... \n \n");
					//fun��o para excluir os alunos escolhidos
					excluir_nome_sobrenome(nome_al, sobre_al);
				}
			}
		}
		
		//NOME
		else if (opcao==2){
			printf("Digite o nome do aluno: \n");
			scanf("%s", &nome_al);
			
			for(i=0; i<cont; i++){
				//compara��o de duas strings
				if(strcmp(alunos[i].nome, nome_al) == 0){
				printf("Prontuario: %d \n", alunos[i].prontuario);
				printf("Nome: %s \n", alunos[i].nome);
				printf("Sobrenome: %s \n", alunos[i].sobrenome);
				printf("Data de nascimento: %d/%d/%d \n", alunos[i].datadenascimento.dia,alunos[i].datadenascimento.mes,alunos[i].datadenascimento.ano);
				printf("Curso: %s \n\n", alunos[i].curso);
				
				verificacao_1 = true;
				}
			}
			
			if(verificacao_1 == false){
				printf("Nao existe aluno com os dados inseridos! \n");
			} else {
				printf("Deseja excluir os alunos impressos? \n");
				printf("1 - SIM \n");
				printf("2 - NAO \n");
				scanf("%d", &escolha);
				
				if(escolha == 1){
					printf("Excluindo... \n \n");
					//fun��o para excluir os alunos escolhidos
					excluir_nome(nome_al);
				}
			}
		}
		
		//SOBRENOME
		else if (opcao==3){
			printf("Digite o sobrenome do aluno: \n");
			scanf("%s", sobre_al);
			
			for(i=0; i<cont; i++){
				//compara��o de duas strings
				if(strcmp(alunos[i].sobrenome, sobre_al) == 0){
				printf("Prontuario: %d \n", alunos[i].prontuario);
				printf("Nome: %s \n", alunos[i].nome);
				printf("Sobrenome: %s \n", alunos[i].sobrenome);
				printf("Data de nascimento: %d/%d/%d \n", alunos[i].datadenascimento.dia,alunos[i].datadenascimento.mes,alunos[i].datadenascimento.ano);
				printf("Curso: %s \n\n", alunos[i].curso);
				
				verificacao_1 = true;
				}
			}
			
			if(verificacao_1 == false){
				printf("Nao existe aluno com os dados inseridos! \n");
			}else {
				printf("Deseja excluir os alunos impressos? \n");
				printf("1 - SIM \n");
				printf("2 - NAO \n");
				scanf("%d", &escolha);
				
				if(escolha == 1){
					printf("Excluindo... \n \n");
					//fun��o para excluir os alunos escolhidos
					excluir_sobrenome(sobre_al);
				}
			}
		}
		
		//PRONTU�RIO
		else if (opcao==4){	
			printf("Digite o prontuario do aluno: \n");
			scanf("%d", &pront_al);
			
			for(i=0; i<cont; i++){
				if(pront_al == alunos[i].prontuario){
				printf("Prontuario: %d \n", alunos[i].prontuario);
				printf("Nome: %s \n", alunos[i].nome);
				printf("Sobrenome: %s \n", alunos[i].sobrenome);
				printf("Data de nascimento: %d/%d/%d \n", alunos[i].datadenascimento.dia,alunos[i].datadenascimento.mes,alunos[i].datadenascimento.ano);
				printf("Curso: %s \n\n", alunos[i].curso);
				
				verificacao_1 = true;
				
				}
			}
			if(verificacao_1 == false){
				printf("Nao existe aluno com os dados inseridos! \n");
			}else {
				printf("Deseja excluir os alunos impressos? \n");
				printf("1 - SIM \n");
				printf("2 - NAO \n");
				scanf("%d", &escolha);
				
				if(escolha == 1){
					printf("Excluindo... \n \n");
					//fun��o para excluir os alunos escolhidos
					excluir_prontuario(pront_al);
				}
			}
		}
		
		//Data de nascimento
		else if (opcao==5){
			//vari�veis
			int dia, mes, ano, i;
			
			//entradas
			printf("Digite o dia de nascimento: \n");
			scanf("%d", &dia);
			printf("Digite o mes de nascimento: \n");
			scanf("%d", &mes);
			printf("Digite o ano de nascimento: \n");
			scanf("%d", &ano);
			
			//an�lise de data
			for (i=0; i<cont; i++){
				if(dia == alunos[i].datadenascimento.dia){
					if(mes == alunos[i].datadenascimento.mes){
						if(ano == alunos[i].datadenascimento.ano){
							printf("Prontuario: %d \n", alunos[i].prontuario);
							printf("Nome: %s \n", alunos[i].nome);
							printf("Sobrenome: %s \n", alunos[i].sobrenome);
							printf("Data de nascimento: %d/%d/%d \n", alunos[i].datadenascimento.dia,alunos[i].datadenascimento.mes,alunos[i].datadenascimento.ano);
							printf("Curso: %s \n\n", alunos[i].curso);
							
							verificacao_1 = true;
						}
					}
				}
			}
			if(verificacao_1 == false){
				printf("nenhum aluno registrado com essa data de nascimento! \n");
			}
			else{
				printf("Deseja excluir os alunos impressos? \n");
				printf("1 - SIM \n");
				printf("2 - NAO \n");
				scanf("%d", &escolha);
	
				if(escolha == 1){
					printf("Excluindo... \n \n");
					//fun��o para excluir os alunos escolhidos
					excluir_datanasc(dia, mes, ano);
				}
			}
		}
		
		//CURSO
		else if (opcao==6){
			//vari�veis
			int vet_aux[cont], resultados=0;
			int i;
			char curso[4];
			
			printf("Digite o curso: \n");
			scanf("%s", &curso);
			
			//itera sobre o vetor alunos
			for(i=0; i<cont; i++){
				//compara��o de duas strings
				if(strcmp(curso, alunos[i].curso) == 0){
					printf("ok");
					printf("Prontuario: %d \n", alunos[i].prontuario);
					printf("Nome: %s \n", alunos[i].nome);
					printf("Sobrenome: %s \n", alunos[i].sobrenome);
					printf("Data de nascimento: %d/%d/%d \n", alunos[i].datadenascimento.dia,alunos[i].datadenascimento.mes,alunos[i].datadenascimento.ano);
					printf("Curso: %s \n\n", alunos[i].curso);
					
					verificacao_1 = true;
				}
			}
			if(verificacao_1 == false){
				printf("Nenhum aluno registrado com o curso %s! \n", curso);
			}else {
				printf("Deseja excluir os alunos impressos? \n");
				printf("1 - SIM \n");
				printf("2 - NAO \n");
				scanf("%d", &escolha);
				
				if(escolha == 1){
					printf("Excluindo... \n \n");
					//fun��o para excluir os alunos escolhidos
					excluir_curso(curso);
				}
			}
		}
		
		else if (opcao==7){
			printf("");
		}
		
		else{
			printf("OPCAO INVALIDA, TENTE NOVAMENTE! \n");
			main();
		}
		system("pause");
		system("cls");
	}
}

//ordena alunos de acordo com a escolha
void ordenar(){
	//vari�veis
	int escolha;
	
	//menu de op��es para ordena��o
	printf("Digite qual metodo deseja utilizar para a ordenacao: \n");
	printf("1 - Nome e sobrenome \n");
	printf("2 - Sobrenome e nome\n");
	printf("3 - Data de nascimento \n");
	printf("4 - Prontuario \n");			
	printf("5 - Curso \n\n");
	scanf("%d", &escolha);
	
	para_mtd_ord_escolhido = escolha; // altera o valor do par�metro escolhido para o m�todo de ordena��o
	
	//ordenar por nome e sobrenome
	if(escolha == 1){
		//a vari�vel contador faz os indices serem percorridos cont vezes, para ter certeza de que todos elementos
		//foram posicionados corretamente
		int i, contador; //contador: controla o primeiro la�o cont-1 vezes
		aluno aux;
		
		for(contador=1; contador < cont; contador++){
			for(i=0; i<cont-1; i++){
				//condi��o de troca de posi��o entre os elementos analisados
				if(strcmp(alunos[i].nome,alunos[i+1].nome) > 0){
					aux = alunos[i];
					alunos[i] = alunos[i+1];
					alunos[i+1] = aux;
				}
			}
		}
		
		printf("Ordenacao feita com sucesso!! \n");
	}
	
	//ordenar por sobrenome e nome
	if(escolha == 2){
		int i, contador;
		aluno aux;
		
		for(contador=1; contador < cont; contador++){
			for(i=0; i<cont-1; i++){
				//condi��o de troca de posi��o entre os elementos analisados
				if(strcmp(alunos[i].sobrenome,alunos[i+1].sobrenome) > 0){
					aux = alunos[i];
					alunos[i] = alunos[i+1];
					alunos[i+1] = aux;
				}
			}
		}
		
		printf("Ordenacao feita com sucesso!! \n");
	}
	
	//ordenar por data de nascimento
	if(escolha == 3){
		int i, contador;
		aluno aux;					
		bool retorno = false;	//retorna true se for preciso inverter a posi��o entre os alunos
		
		for(contador=1; contador < cont; contador++){
			for(i=0; i<cont-1; i++){
				//condi��o de troca de posi��o entre os elementos analisados
				retorno = compara_data(alunos[i].datadenascimento, alunos[i+1].datadenascimento);
				if(retorno == true){
					aux = alunos[i];
					alunos[i] = alunos[i+1];
					alunos[i+1] = aux;
				}
			}
		}
		
		printf("Ordenacao feita com sucesso!! \n");
	}
	
	//ordenar por prontu�rio
	if(escolha == 4){
		int i, contador;
		aluno aux;

		for(contador=1; contador<cont; contador++){
			for(i=0; i<cont-1; i++){
				//condi��o de troca de posi��o entre os elementos analisados
				if(alunos[i].prontuario > alunos[i+1].prontuario){
					aux = alunos[i];
					alunos[i] = alunos[i+1];
					alunos[i+1] = aux;
				}
			}
		}
		
		printf("Ordenacao feita com sucesso!! \n");
	}
	
	//ordenar por curso
	if(escolha == 5){
		int i, contador;
		aluno aux;
		
		for(contador=1; contador < cont; contador++){
			for(i=0; i<cont-1; i++){
				//condi��o de troca de posi��o entre os elementos analisados
				if(strcmp(alunos[i].curso,alunos[i+1].curso) > 0){
					aux = alunos[i];
					alunos[i] = alunos[i+1];
					alunos[i+1] = aux;
				}
			}
		}
		
		printf("Ordenacao feita com sucesso!! \n");
		
	}
	
	system("pause");
	system("cls");
}

//fun��o para testar se o prontu�rio escolhido n�o existe
bool ValidaProntuario(int prontuario){
	if (cont>0){
		for(int i=0; i<cont; i++){
			if(alunos[i].prontuario == prontuario){
				printf("O prontuario informado ja e utilizado por um aluno, por favor digite um prontuario valido \n");
				return false;
			}
			
		}
	}
	return true;
}

//exclui nome especificado
void excluir_nome(char *nome){   
	//vari�veis
	int i, j;
    for(i = 0; i < cont; i++){
        if(strcmp(alunos[i].nome, nome) == 0){
        	
        	//cria vari�vel j para realocar cada posi��o do vetor uma casa � esquerda
            for(j = i; j < cont; j++){
                strcpy(alunos[j].nome, alunos[j + 1].nome);
				strcpy(alunos[j].sobrenome, alunos[j + 1].sobrenome);
				strcpy(alunos[j].curso, alunos[j + 1].curso);
				alunos[j].prontuario = alunos[j + 1].prontuario;
				alunos[j].datadenascimento.dia = alunos[j + 1].datadenascimento.dia;
				alunos[j].datadenascimento.mes = alunos[j + 1].datadenascimento.mes;
				alunos[j].datadenascimento.ano = alunos[j + 1].datadenascimento.ano;
        	}
            cont--; // subtrai a valor da quantidade total de alunos cadastrados
            //printf("Total cadastrados: %d \n", cont);
            
            //zera o indice para percorrer o vetor desde o in�cio
            i=-1;
        }
    }
    main();
}

//exclui sobrenome especificado
void excluir_sobrenome(char *sobrenome){
	//vari�veis
	int i, j;
	for(i = 0; i < cont; i++){
    	if(strcmp(alunos[i].sobrenome, sobrenome) == 0){
    		
    		//cria vari�vel j para realocar cada posi��o do vetor uma casa � esquerda
        	for(j = i; j < cont; j++){
                strcpy(alunos[j].nome, alunos[j + 1].nome);
				strcpy(alunos[j].sobrenome, alunos[j + 1].sobrenome);
				strcpy(alunos[j].curso, alunos[j + 1].curso);
				alunos[j].prontuario = alunos[j + 1].prontuario;
				alunos[j].datadenascimento.dia = alunos[j + 1].datadenascimento.dia;
				alunos[j].datadenascimento.mes = alunos[j + 1].datadenascimento.mes;
				alunos[j].datadenascimento.ano = alunos[j + 1].datadenascimento.ano;
        	}
            cont--; // subtrai a valor da quantidade total de alunos cadastrados
            //printf("Total cadastrados: %d \n", cont);
            
            //zera o indice para percorrer o vetor desde o in�cio
            i=-1;
        }
    }
    main();
}

//exclui prontu�rio
void excluir_prontuario(int prontuario){
		//vari�veis
		int i, j;
		
		for(i = 0; i < cont; i++){
    	if(alunos[i].prontuario == prontuario){
    		
    		//cria vari�vel j para realocar cada posi��o do vetor uma casa � esquerda
        	for(j = i; j < cont; j++){
                strcpy(alunos[j].nome, alunos[j + 1].nome);
				strcpy(alunos[j].sobrenome, alunos[j + 1].sobrenome);
				strcpy(alunos[j].curso, alunos[j + 1].curso);
				alunos[j].prontuario = alunos[j + 1].prontuario;
				alunos[j].datadenascimento.dia = alunos[j + 1].datadenascimento.dia;
				alunos[j].datadenascimento.mes = alunos[j + 1].datadenascimento.mes;
				alunos[j].datadenascimento.ano = alunos[j + 1].datadenascimento.ano;
        	}
            cont--; // subtrai a valor da quantidade total de alunos cadastrados
            //printf("Total cadastrados: %d \n", cont);
            
            //zera o indice para percorrer o vetor desde o in�cio
            i=-1;
        }
    }
    main();
}

//exclui curso
void excluir_curso(char *curso){
	//vari�veis
	int i, j;
	
	for(i = 0; i < cont; i++){
    	if(strcmp(alunos[i].curso, curso) == 0){
    		
    		//cria vari�vel j para realocar cada posi��o do vetor uma casa � esquerda
        	for(j = i; j < cont; j++){
                strcpy(alunos[j].nome, alunos[j + 1].nome);
				strcpy(alunos[j].sobrenome, alunos[j + 1].sobrenome);
				strcpy(alunos[j].curso, alunos[j + 1].curso);
				alunos[j].prontuario = alunos[j + 1].prontuario;
				alunos[j].datadenascimento.dia = alunos[j + 1].datadenascimento.dia;
				alunos[j].datadenascimento.mes = alunos[j + 1].datadenascimento.mes;
				alunos[j].datadenascimento.ano = alunos[j + 1].datadenascimento.ano;
        	}
            cont--; // subtrai a valor da quantidade total de alunos cadastrados
            //printf("Total cadastrados: %d \n", cont);
            
            //zera o indice para percorrer o vetor desde o in�cio
            i=-1;
        }
    }
    main();
}

//exclui data de nascimento especificada
void excluir_datanasc(int dia, int mes, int ano){
	//vari�veis
	int i, j;
		
	for(i = 0; i < cont; i++){
    	if((alunos[i].datadenascimento.dia == dia) && (alunos[i].datadenascimento.mes == mes) && (alunos[i].datadenascimento.ano == ano)){
    		
    	//cria vari�vel j para realocar cada posi��o do vetor uma casa � esquerda
		for(j = i; j < cont; j++){
            strcpy(alunos[j].nome, alunos[j + 1].nome);
			strcpy(alunos[j].sobrenome, alunos[j + 1].sobrenome);
			strcpy(alunos[j].curso, alunos[j + 1].curso);
			alunos[j].prontuario = alunos[j + 1].prontuario;
			alunos[j].datadenascimento.dia = alunos[j + 1].datadenascimento.dia;
			alunos[j].datadenascimento.mes = alunos[j + 1].datadenascimento.mes;
			alunos[j].datadenascimento.ano = alunos[j + 1].datadenascimento.ano;
        }
        cont--; // subtrai a valor da quantidade total de alunos cadastrados
        //printf("Total cadastrados: %d \n", cont);
            
        //zera o indice para percorrer o vetor desde o in�cio
        i=-1;
    }
    }
    main();
}

//exclui nome e sobrenome especificados
void excluir_nome_sobrenome(char *nome, char *sobrenome){
	//vari�veis
	int i, j;
				
    for(i = 0; i < cont; i++){
        if(strcmp(alunos[i].nome, nome) == 0){
        	if(strcmp(alunos[i].sobrenome, sobrenome) == 0){
        		
			//{aluno1[0], aluno2[1], aluno3[2], aluno4[3]}
			//cria vari�vel j para realocar cada posi��o do vetor uma casa � esquerda
            for(j = i; j < cont; j++){
				strcpy(alunos[j].nome, alunos[j + 1].nome);
				strcpy(alunos[j].sobrenome, alunos[j + 1].sobrenome);
				strcpy(alunos[j].curso, alunos[j + 1].curso);
				alunos[j].prontuario = alunos[j + 1].prontuario;
				alunos[j].datadenascimento.dia = alunos[j + 1].datadenascimento.dia;
				alunos[j].datadenascimento.mes = alunos[j + 1].datadenascimento.mes;
				alunos[j].datadenascimento.ano = alunos[j + 1].datadenascimento.ano;
    		}
        	}
        	
            cont--; // subtrai a valor da quantidade total de alunos cadastrados
            //printf("Total cadastrados: %d \n", cont);
        }
    }
    main();
}

//compara datas para usar na fun��o de ordenar
bool compara_data(data data_1, data data_2){
	//analisa se o primeiro ano � maior do que o segundo
	if(data_1.ano > data_2.ano){
		return true;
	}
	//analisa se os dois anos s�o iguais
	else if(data_1.ano == data_2.ano){
		
		//analisa se o mes 1 � maior que o 2
		if(data_1.mes > data_2.mes){
			return true;
		}
		//analisa se o mes 1 e 2 s�o iguais
		else if(data_1.mes == data_2.mes){
			
			//analisa se o dia 1 � maior que o dia 2
			if(data_1.dia > data_2.dia){
				return true;
			}
			//analisa se os dias das datas 1 e 2 s�o iguas
			else if(data_1.dia == data_2.dia){
				return false;
			}
			
			//se o dia 2 for maior que o dia 1
			else{
				return false;
			}
		}
		
		//caso o mes 1 seja menor que o 2
		else{
			return false;
		}
	}
	//caso o ano 1 seja menor que o ano 2
	else{
		return false;
	}
}

//m�todo selction sort
void selection_sort(){
	//exemplo: [2,4,1,3,0,5]
	
	//vari�veis
	int escolha, i, j, menor;
	
	//menu de op��es para ordena��o
	printf("Digite qual opcao deseja utilizar para a ordenacao: \n");
	printf("(1) - Nome e sobrenome \n");
	printf("(2) - Sobrenome e nome\n");
	printf("(3) - Data de nascimento \n");
	printf("(4) - Prontuario \n");			
	printf("(5) - Curso \n\n");
	scanf("%d", &escolha);
	
	para_mtd_ord_escolhido = escolha; // altera o valor do par�metro escolhido para o m�todo de ordena��o
	
	//[23,4,67,-8,90,54,21]
	
	//ordena��o
	//primeiro la�o - seleciona sempre o "primeiro" elemento
	for(i=0; i<cont; i++){
		menor=i;
		//segundo la�o - compara cada elemento com o "primeiro"
		for(j = i+1; j < cont; j++){
			//fun��o que compara os dados dos alunos de acordo com a op��o escolhida
			if(compara_info(alunos[menor], alunos[j], escolha)){
				menor = j;
			}
		}
		//troca a posi��o dos alunos
		trocar_alunos(&alunos[i], &alunos[menor]);
	}
	
	printf("Ordenacao feita com sucesso!\n");
	
}

//m�todo merge sort - reparti��o
void merge_sort(int ini, int fim, int escolha) {
	//exemplo: [2,4,1,3,0,5]
	
	//realiza as divis�es das structs de alunos e chama a fun��o merge para comparar e realizar a ordena��o
	if(ini < fim) {
		int meio = (ini + fim) / 2;
		merge_sort(ini, meio, escolha); //primeira metade do vetor
		merge_sort(meio+1, fim, escolha); //segunda metade do vetor
		merge(ini, meio, fim, escolha); 
	}
}

//m�todo merge sort - ordena��o
void merge(int ini, int meio, int fim, int escolha) {
	//vari�veis
	int i = ini, j = meio + 1, k = 0;
	aluno aux[cont]; //vetor auxiliar
	
	//la�o de compara��o entre os �ndices
	while(i <= meio && j <= fim) {
		//fun��o que retorna false ou true de acordo com a condi��o
		if(compara_info(alunos[i], alunos[j], escolha) == true) { 
			aux[k++] = alunos[j++];
		} else {
			aux[k++] = alunos[i++];
		}
	}
	
	//preenche o vetor auxiliar com o resto do vetor incompleto
	//*****************************
	while(i <= meio) {
		aux[k++] = alunos[i++];
	}
	
	while(j <= fim) {
		aux[k++] = alunos[j++];
	}
	//******************************
	
	//copia o vetor auxiliar para o vetor de alunos
	for(i = 0, j = ini; j <= fim; i++, j++) {
		alunos[j] = aux[i];
	}
	
}

//m�todo quick sort
void quick_sort(int ini, int fim, int escolha){
	//exemplo: [2,4,1,3,0,5]
	
	int pos;
	
	if(ini < fim){
		pos = particao(ini, fim, escolha);	//particiona o vetor de forma a separar elementos maiores que o pivo de um lado e menores de outro
		quick_sort(ini, pos - 1, escolha);
		quick_sort(pos, fim, escolha);
	}

}

//parti��o dos elementos
int particao(int ini, int fim, int escolha){
	aluno pivo;
	pivo = alunos[fim];
	
	while (ini < fim) {
		
		while (ini < fim && (compara_info(alunos[ini], pivo, escolha) == false)) { //se o primeiro for maior que o segundo ir� retornar true
			ini++;
		}
		
		while (ini < fim && (compara_info(alunos[fim], pivo, escolha) == true)) { //se o primeiro for maior que o segundo ir� retornar true
			fim--;
		}
		
		trocar_alunos(&alunos[ini], &alunos[fim]);
	}
	
	return ini;
}

//m�todo insertion sort
void insertion_sort(){
	//exemplo: [2,4,1,3,0,5]
	
	//vari�veis
	int escolha, i, j, k;
				
	//menu de op��es para ordena��o
	printf("Digite qual opcao deseja utilizar para a ordenacao: \n");
	printf("(1) - Nome e sobrenome \n");
	printf("(2) - Sobrenome e nome\n");
	printf("(3) - Data de nascimento \n");
	printf("(4) - Prontuario \n");			
	printf("(5) - Curso \n\n");
	scanf("%d", &escolha);
	
	para_mtd_ord_escolhido = escolha; // altera o valor do par�metro escolhido para o m�todo de ordena��o
	
	//[5,1,4,5,2]
	// j i
	      
	//la�o mais externo - controla a sele��o de cada �ndice para comparar com o anterior
	for(i = 1; i < cont; i++) {
		for(j = 0; j < i; j++) {
			if(compara_info(alunos[i], alunos[j], escolha) == false) { //se o primeiro for maior que o segundo � retornado true
				for(k = j; k < i; k++) {
					trocar_alunos(&alunos[k], &alunos[i]);				
				}
				break;
			}
		}
	}
	
	printf("Ordenacao concluida ! \n");
}

//fun��o para realizar busca bin�ria
int busca_binaria(){
	//vari�veis
	int escolha;
	bool verifica = false;  //vari�vel que verifica se algum aluno foi encontrado
	
	//menu de op��es para a busca
	printf("Digite qual opcao deseja utilizar para a busca bin�ria: \n");
	printf("(1) - Nome e sobrenome \n");
	printf("(2) - Sobrenome e nome\n");
	printf("(3) - Data de nascimento \n");
	printf("(4) - Prontuario \n");			
	printf("(5) - Curso \n\n");
	scanf("%d", &escolha);
	
	if(escolha == para_mtd_ord_escolhido){

		//NOME
		//exibe de acordo com o tipo de crit�rio
		if(escolha == 1){
			//vari�veis
			char nome[50];
			
			printf("Digite o nome do aluno desejado: \n");
			scanf("%s", &nome);
			
			//vari�veis
			int ini = 0;
			int fim = cont-1;
			int meio;
			
			while(ini <= fim){
				meio = (ini + fim) / 2;
				//primeira situa��o - se o dado procurado for o do meio do vetor
				if(strcmp(alunos[meio].nome, nome) == 0){
					imprimir(meio);
					
					verifica = true;
				}
				//segunda situa��o - se o dado procurado estiver antes da metade
				if(strcmp(alunos[meio].nome, nome) > 0){
					fim = meio-1;
				}
				//terceira situa��o - se o dado procurado estiver al�m da metade do vetor
				else{
					ini = meio+1;
				}
				
			}
			if(verifica == false){
					printf("\n Aluno nao existe no registro! \n \n");	
			}
		}
		
		//SOBRENOME
		//exibe de acordo com o tipo de crit�rio
		else if(escolha == 2){
			//vari�veis
			char sobrenome[50];
			
			printf("Digite o sobrenome do aluno desejado: \n");
			scanf("%s", &sobrenome);
			
			//vari�veis
			int ini = 0;
			int fim = cont-1;
			int meio;
			
			while(ini <= fim){
				meio = (ini + fim) / 2;
				//primeira situa��o - se o dado procurado for o do meio do vetor
				if(strcmp(alunos[meio].sobrenome, sobrenome) == 0){
					imprimir(meio);
					
					verifica = true;
				}
				//segunda situa��o - se o dado procurado estiver antes da metade
				if(strcmp(alunos[meio].sobrenome, sobrenome) > 0){
					fim = meio-1;
				}
				//terceira situa��o - se o dado procurado estiver al�m da metade do vetor
				else{
					ini = meio+1;
				}
				
			}
			if(verifica == false){
					printf("\n Aluno nao existe no registro! \n \n");	
			}
		}
		
		//DATA
		//exibe de acordo com o tipo de crit�rio
		else if(escolha == 3){
			//vari�veis
			data data_aux;
			//entradas
			printf("Digite o dia de nascimento: \n");
			scanf("%d", &data_aux.dia);
			printf("Digite o mes de nascimento: \n");
			scanf("%d", &data_aux.mes);
			printf("Digite o ano de nascimento: \n");
			scanf("%d", &data_aux.ano);
			
			//vari�veis
			int ini = 0;
			int fim = cont-1;
			int meio;
			
			while(ini <= fim){
				meio = (ini + fim) / 2;
				//primeira situa��o - se o dado procurado for o do meio do vetor
				//verifica dia
				if(alunos[meio].datadenascimento.dia == data_aux.dia){
					//verifica mes
					if(alunos[meio].datadenascimento.mes == data_aux.mes){
						//verifica ano
						if(alunos[meio].datadenascimento.ano == data_aux.ano){
							imprimir(meio);
					
							verifica = true;
						}	
					}
				}
				//segunda situa��o - se o dado procurado estiver antes da metade
				if(compara_data(data_aux, alunos[meio].datadenascimento) == false){
					fim = meio-1;
				}
				//terceira situa��o - se o dado procurado estiver al�m da metade do vetor
				else{
					ini = meio+1;
				}
				
			}
			if(verifica == false){
					printf("\n Aluno nao existe no registro! \n \n");	
			}
		}
		
		//PRONTU�RIO
		//exibe de acordo com o tipo de crit�rio
		else if(escolha == 4){
			//vari�veis
			int prontuario;
			
			printf("Digite o prontuario do aluno desejado: \n");
			scanf("%d", &prontuario);
			
			//vari�veis
			int ini = 0;
			int fim = cont-1;
			int meio, i;
			
			while(ini <= fim){
				meio = (ini + fim) / 2;
				//primeira situa��o - se o dado procurado for o do meio do vetor
				if(alunos[meio].prontuario == prontuario){
					imprimir(meio);
					
					verifica = true;
				}
				//segunda situa��o - se o dado procurado estiver antes da metade
				if(alunos[meio].prontuario > prontuario){
					fim = meio-1;
				}
				//terceira situa��o - se o dado procurado estiver al�m da metade do vetor
				else{
					ini = meio+1;
				}
				
			}
			if(verifica == false){
					printf("\n Aluno nao existe no registro! \n \n");	
			}
		}
		
		//CURSO
		//exibe de acordo com o tipo de crit�rio
		else if(escolha == 5){
			//vari�veis
			char curso[4];
			
			printf("Digite o curso do aluno desejado: \n");
			scanf("%s", &curso);
			
			//vari�veis
			int ini = 0;
			int fim = cont-1;
			int meio;
			
			while(ini <= fim){
				meio = (ini + fim) / 2;
				//primeira situa��o - se o dado procurado for o do meio do vetor
				if(strcmp(alunos[meio].curso, curso) == 0){
					imprimir(meio);
					
					verifica = true;
				}
				//segunda situa��o - se o dado procurado estiver antes da metade
				if(strcmp(alunos[meio].curso, curso) > 0){
					fim = meio-1;
				}
				//terceira situa��o - se o dado procurado estiver al�m da metade do vetor
				else{
					ini = meio+1;
				}
				
			}
			if(verifica == false){
					printf("\n Aluno nao existe no registro! \n \n");	
			}
		}
	}
	
	else{
		printf("Realize a ordenacao do cadastro de acordo com o criterio escolhido de busca binaria! \n \n");
	}
	
}

// fun��o para carregar alunos de um arquivo
void recuperar(){
	FILE *arquivo;
	
	arquivo = fopen("alunos.bin", "rb"); //read bin
	
	if(arquivo != 0) {
		fread(&cont, sizeof(int), 1, arquivo);
		fread(&alunos, sizeof(aluno), cont, arquivo);
		
		fclose(arquivo);
		
		printf("Alunos carregados: %d \n", cont);
	} else {
		printf("Nenhum aluno cadastrado \n \n");
	}
}

// fun��o para salvar alunos num arquivo
void salvar(){ //chamada com a op��o 7
	FILE *arquivo;
	
	arquivo = fopen("alunos.bin", "wb"); //write bin
	if(arquivo != 0) {
		fwrite(&cont, sizeof(int), 1, arquivo);
		fwrite(&alunos, sizeof(aluno), cont, arquivo);
		
		fclose(arquivo);
	
		printf("Alunos salvos com sucesso \n");
	} else {
		printf("Erro na cria��o do arquivo \n \n");
	}
}

bool compara_info(aluno aluno_menor, aluno aluno_j, int escolha){
	//vari�veis
	int i;
	//analisa a op��o escolhida
	if(escolha == 1){
		//ordena��o por nome e sobrenome
		if(strcmp(aluno_menor.nome ,aluno_j.nome)>0){
			return true;
		}else{
			return false;
		}
	}
	
	else if(escolha == 2){
		//ordena��o por sobrenome e nome
		if(strcmp(aluno_menor.sobrenome ,aluno_j.sobrenome)>0){
			return true;
		}else{
			return false;
		}
	}
	else if(escolha == 3){
		//ordena��o feita por data
		if(compara_data(aluno_menor.datadenascimento, aluno_j.datadenascimento) == true){
			return true;
		}else{
			return false;
		}
	}
	
	else if(escolha == 4){
		//ordena��o por prontu�rio
		if(aluno_j.prontuario < aluno_menor.prontuario){
			return true;
		}
		else{
			return false;
		}
	}
	
	else if(escolha == 5){
		//ordena��o por curso
		if(strcmp(aluno_menor.curso ,aluno_j.curso)>0){
			return true;
		}else{
			return false;
		}
	}	
}

void trocar_alunos(aluno *a, aluno *b){
	//vari�veis
	aluno aux;
	
	//printf("Aluno A: %d \n", a.prontuario);
	//printf("Aluno B: %d \n", b.prontuario);
	
	aux = *a;
	*a = *b;
	*b = aux;
}

//imprime aluno passado pela busca bin�ria
void imprimir(int i){
	printf("\n");
	printf("Prontuario: %d \n", alunos[i].prontuario);
	printf("Nome: %s \n", alunos[i].nome);
	printf("Sobrenome: %s \n", alunos[i].sobrenome);
	printf("Data de nascimento: %d/%d/%d \n", alunos[i].datadenascimento.dia,alunos[i].datadenascimento.mes,alunos[i].datadenascimento.ano);
	printf("Curso: %s \n \n", alunos[i].curso);
	
}
