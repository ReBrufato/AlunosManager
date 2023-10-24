//bibliotecas utilizadas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
//constantes
#define TAMNOME 50
#define TAMSOBRENOME 50

//variáveis de escopo global
typedef struct data{
	int dia, mes, ano;
}data;

typedef struct registro{
	char nome[TAMNOME], sobrenome[TAMSOBRENOME];
	data datadenascimento; //datadenascimento é uma struct do tipo data
	int prontuario;
	char curso[4];
}aluno;
aluno alunos[1000]; //alunos[1000] é um vetor de struct do tipo aluno/registro

int cont=0; //indica quantos alunos tem cadastrados

int para_mtd_ord_escolhido = 0; //armazena qual foi o último parâmetro para o método de ordenação escolhido

//declaração das funções
bool ValidaProntuario(int);  //recebe 1 inteiro como parâmetro
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

//funções para excluir
void excluir_nome(char*);	//recebe 1 ponteiro char como parâmetro
void excluir_sobrenome(char*);	//recebe 1 ponteiro char como parâmetro
void excluir_nome_sobrenome(char*, char*);	//recebe 3 ponteiros char como parâmetro
void excluir_curso(char*);	//recebe 1 ponteiro char como parâmetro
void excluir_prontuario(int); //recebe 1 inteiro como parâmetro
void excluir_datanasc(int, int, int); //recebe 3 inteiros como parâmetro

//funções de ordenação
void selection_sort();

//função para comparar
bool compara_data(struct data, struct data);

//função principal
int main(void){
	//chama função que recupera dados salvos
	recuperar();
	//[1,2,4,8,9,57]
	//variáveis
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
		
		//realiza a busca binária do aluno especificado na função
		else if (opcao == 4){
			int posicao;
			
			busca_binaria();
		}
		
		//ordena struct de alunos de acordo com a opção escolhida
		else if (opcao == 5){
			ordenar();
		}
		
		//ordena struct de alunos de acordo com o método escolhido
		else if (opcao == 6){
			//variáveis
			int opc=0;
			
			while(opc != 5){
				printf("Escolha o metodo de ordenacao: \n");
				printf("(1) - Quick Sort \n");
				printf("(2) - Merge Sort \n");
				printf("(3) - Insertion Sort \n");
				printf("(4) - Selection Sort \n");
				printf("(5) - Voltar para o Menu Principal \n");
				
				scanf("%d",&opc);
				
				//opção 1 - Quick Sort
				if(opc == 1){
					int ini = 0;
					int fim = cont-1;
					int escolha;
					
					//menu de opções para ordenação
					printf("Digite qual opcao deseja utilizar para a ordenacao: \n");
					printf("(1) - Nome e sobrenome \n");
					printf("(2) - Sobrenome e nome\n");
					printf("(3) - Data de nascimento \n");
					printf("(4) - Prontuario \n");			
					printf("(5) - Curso \n\n");
					scanf("%d", &escolha);
					
					para_mtd_ord_escolhido = escolha; // altera o valor do parâmetro escolhido para o método de ordenação
					
					quick_sort(ini, fim, escolha);
					
					printf("Ordenacao feita com sucesso! \n");
				}
				
				//opção 2 - Merge Sort
				else if(opc == 2){
					int ini = 0;
					int fim = cont-1;
					int escolha;
					
					//menu de opções para ordenação
					printf("Digite qual opcao deseja utilizar para a ordenacao: \n");
					printf("(1) - Nome e sobrenome \n");
					printf("(2) - Sobrenome e nome\n");
					printf("(3) - Data de nascimento \n");
					printf("(4) - Prontuario \n");			
					printf("(5) - Curso \n\n");
					scanf("%d", &escolha);
	
					para_mtd_ord_escolhido = escolha; // altera o valor do parâmetro escolhido para o método de ordenação
					
					merge_sort(ini, fim, escolha);
					
					printf("Ordenacao feita com sucesso! \n");
				}
				
				//opção 3 - insertion Sort
				else if(opc == 3){
					insertion_sort();
				}
				
				//opção 4 - selection Sort
				else if(opc == 4){
					selection_sort();
				}
				
				//opção 5
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
	
	//define número de alunos a serem cadastrados
	printf("Digite quantos alunos deseja cadastrar: \n");
	scanf("%d", &escolha);
	
	//laço para incrementar alunos na struct
	for(int i=0; i<escolha; i++){
		bool isProntuarioValido = false;
		//função para verificar a existência do prontuário
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
		
		//incrementa o número de alunos cadastrados
		cont++;
		
		//pausa a tela 
		system("pause");
		//limpa a tela
		system("cls");
	}
}

//imprimi todos os alunos
void imprimir_todos(){
	//variáveis
	int i;
	
	//analisa se existem alunos cadastrados
	if(cont==0){
		printf("Nao existe aluno cadastrado");
	}
	
	//laço que imprime todos os dados de cada aluno
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
	//variáveis para a primeira parte
	int opcao=0, i, pront_al;
	char nome_al[50], sobre_al[50];
	//variável boleana que define se algum aluno já foi impresso
	bool verificacao_1;

	//variável que decide se os alunos impressos serão excluídos
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
				//a função "strcmp" retorna "0" para strings iguais (string.h)
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
					//função para excluir os alunos escolhidos
					excluir_nome_sobrenome(nome_al, sobre_al);
				}
			}
		}
		
		//NOME
		else if (opcao==2){
			printf("Digite o nome do aluno: \n");
			scanf("%s", &nome_al);
			
			for(i=0; i<cont; i++){
				//comparação de duas strings
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
					//função para excluir os alunos escolhidos
					excluir_nome(nome_al);
				}
			}
		}
		
		//SOBRENOME
		else if (opcao==3){
			printf("Digite o sobrenome do aluno: \n");
			scanf("%s", sobre_al);
			
			for(i=0; i<cont; i++){
				//comparação de duas strings
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
					//função para excluir os alunos escolhidos
					excluir_sobrenome(sobre_al);
				}
			}
		}
		
		//PRONTUÁRIO
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
					//função para excluir os alunos escolhidos
					excluir_prontuario(pront_al);
				}
			}
		}
		
		//Data de nascimento
		else if (opcao==5){
			//variáveis
			int dia, mes, ano, i;
			
			//entradas
			printf("Digite o dia de nascimento: \n");
			scanf("%d", &dia);
			printf("Digite o mes de nascimento: \n");
			scanf("%d", &mes);
			printf("Digite o ano de nascimento: \n");
			scanf("%d", &ano);
			
			//análise de data
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
					//função para excluir os alunos escolhidos
					excluir_datanasc(dia, mes, ano);
				}
			}
		}
		
		//CURSO
		else if (opcao==6){
			//variáveis
			int vet_aux[cont], resultados=0;
			int i;
			char curso[4];
			
			printf("Digite o curso: \n");
			scanf("%s", &curso);
			
			//itera sobre o vetor alunos
			for(i=0; i<cont; i++){
				//comparação de duas strings
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
					//função para excluir os alunos escolhidos
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
	//variáveis
	int escolha;
	
	//menu de opções para ordenação
	printf("Digite qual metodo deseja utilizar para a ordenacao: \n");
	printf("1 - Nome e sobrenome \n");
	printf("2 - Sobrenome e nome\n");
	printf("3 - Data de nascimento \n");
	printf("4 - Prontuario \n");			
	printf("5 - Curso \n\n");
	scanf("%d", &escolha);
	
	para_mtd_ord_escolhido = escolha; // altera o valor do parâmetro escolhido para o método de ordenação
	
	//ordenar por nome e sobrenome
	if(escolha == 1){
		//a variável contador faz os indices serem percorridos cont vezes, para ter certeza de que todos elementos
		//foram posicionados corretamente
		int i, contador; //contador: controla o primeiro laço cont-1 vezes
		aluno aux;
		
		for(contador=1; contador < cont; contador++){
			for(i=0; i<cont-1; i++){
				//condição de troca de posição entre os elementos analisados
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
				//condição de troca de posição entre os elementos analisados
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
		bool retorno = false;	//retorna true se for preciso inverter a posição entre os alunos
		
		for(contador=1; contador < cont; contador++){
			for(i=0; i<cont-1; i++){
				//condição de troca de posição entre os elementos analisados
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
	
	//ordenar por prontuário
	if(escolha == 4){
		int i, contador;
		aluno aux;

		for(contador=1; contador<cont; contador++){
			for(i=0; i<cont-1; i++){
				//condição de troca de posição entre os elementos analisados
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
				//condição de troca de posição entre os elementos analisados
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

//função para testar se o prontuário escolhido não existe
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
	//variáveis
	int i, j;
    for(i = 0; i < cont; i++){
        if(strcmp(alunos[i].nome, nome) == 0){
        	
        	//cria variável j para realocar cada posição do vetor uma casa à esquerda
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
            
            //zera o indice para percorrer o vetor desde o início
            i=-1;
        }
    }
    main();
}

//exclui sobrenome especificado
void excluir_sobrenome(char *sobrenome){
	//variáveis
	int i, j;
	for(i = 0; i < cont; i++){
    	if(strcmp(alunos[i].sobrenome, sobrenome) == 0){
    		
    		//cria variável j para realocar cada posição do vetor uma casa à esquerda
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
            
            //zera o indice para percorrer o vetor desde o início
            i=-1;
        }
    }
    main();
}

//exclui prontuário
void excluir_prontuario(int prontuario){
		//variáveis
		int i, j;
		
		for(i = 0; i < cont; i++){
    	if(alunos[i].prontuario == prontuario){
    		
    		//cria variável j para realocar cada posição do vetor uma casa à esquerda
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
            
            //zera o indice para percorrer o vetor desde o início
            i=-1;
        }
    }
    main();
}

//exclui curso
void excluir_curso(char *curso){
	//variáveis
	int i, j;
	
	for(i = 0; i < cont; i++){
    	if(strcmp(alunos[i].curso, curso) == 0){
    		
    		//cria variável j para realocar cada posição do vetor uma casa à esquerda
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
            
            //zera o indice para percorrer o vetor desde o início
            i=-1;
        }
    }
    main();
}

//exclui data de nascimento especificada
void excluir_datanasc(int dia, int mes, int ano){
	//variáveis
	int i, j;
		
	for(i = 0; i < cont; i++){
    	if((alunos[i].datadenascimento.dia == dia) && (alunos[i].datadenascimento.mes == mes) && (alunos[i].datadenascimento.ano == ano)){
    		
    	//cria variável j para realocar cada posição do vetor uma casa à esquerda
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
            
        //zera o indice para percorrer o vetor desde o início
        i=-1;
    }
    }
    main();
}

//exclui nome e sobrenome especificados
void excluir_nome_sobrenome(char *nome, char *sobrenome){
	//variáveis
	int i, j;
				
    for(i = 0; i < cont; i++){
        if(strcmp(alunos[i].nome, nome) == 0){
        	if(strcmp(alunos[i].sobrenome, sobrenome) == 0){
        		
			//{aluno1[0], aluno2[1], aluno3[2], aluno4[3]}
			//cria variável j para realocar cada posição do vetor uma casa à esquerda
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

//compara datas para usar na função de ordenar
bool compara_data(data data_1, data data_2){
	//analisa se o primeiro ano é maior do que o segundo
	if(data_1.ano > data_2.ano){
		return true;
	}
	//analisa se os dois anos são iguais
	else if(data_1.ano == data_2.ano){
		
		//analisa se o mes 1 é maior que o 2
		if(data_1.mes > data_2.mes){
			return true;
		}
		//analisa se o mes 1 e 2 são iguais
		else if(data_1.mes == data_2.mes){
			
			//analisa se o dia 1 é maior que o dia 2
			if(data_1.dia > data_2.dia){
				return true;
			}
			//analisa se os dias das datas 1 e 2 são iguas
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

//método selction sort
void selection_sort(){
	//exemplo: [2,4,1,3,0,5]
	
	//variáveis
	int escolha, i, j, menor;
	
	//menu de opções para ordenação
	printf("Digite qual opcao deseja utilizar para a ordenacao: \n");
	printf("(1) - Nome e sobrenome \n");
	printf("(2) - Sobrenome e nome\n");
	printf("(3) - Data de nascimento \n");
	printf("(4) - Prontuario \n");			
	printf("(5) - Curso \n\n");
	scanf("%d", &escolha);
	
	para_mtd_ord_escolhido = escolha; // altera o valor do parâmetro escolhido para o método de ordenação
	
	//[23,4,67,-8,90,54,21]
	
	//ordenação
	//primeiro laço - seleciona sempre o "primeiro" elemento
	for(i=0; i<cont; i++){
		menor=i;
		//segundo laço - compara cada elemento com o "primeiro"
		for(j = i+1; j < cont; j++){
			//função que compara os dados dos alunos de acordo com a opção escolhida
			if(compara_info(alunos[menor], alunos[j], escolha)){
				menor = j;
			}
		}
		//troca a posição dos alunos
		trocar_alunos(&alunos[i], &alunos[menor]);
	}
	
	printf("Ordenacao feita com sucesso!\n");
	
}

//método merge sort - repartição
void merge_sort(int ini, int fim, int escolha) {
	//exemplo: [2,4,1,3,0,5]
	
	//realiza as divisões das structs de alunos e chama a função merge para comparar e realizar a ordenação
	if(ini < fim) {
		int meio = (ini + fim) / 2;
		merge_sort(ini, meio, escolha); //primeira metade do vetor
		merge_sort(meio+1, fim, escolha); //segunda metade do vetor
		merge(ini, meio, fim, escolha); 
	}
}

//método merge sort - ordenação
void merge(int ini, int meio, int fim, int escolha) {
	//variáveis
	int i = ini, j = meio + 1, k = 0;
	aluno aux[cont]; //vetor auxiliar
	
	//laço de comparação entre os índices
	while(i <= meio && j <= fim) {
		//função que retorna false ou true de acordo com a condição
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

//método quick sort
void quick_sort(int ini, int fim, int escolha){
	//exemplo: [2,4,1,3,0,5]
	
	int pos;
	
	if(ini < fim){
		pos = particao(ini, fim, escolha);	//particiona o vetor de forma a separar elementos maiores que o pivo de um lado e menores de outro
		quick_sort(ini, pos - 1, escolha);
		quick_sort(pos, fim, escolha);
	}

}

//partição dos elementos
int particao(int ini, int fim, int escolha){
	aluno pivo;
	pivo = alunos[fim];
	
	while (ini < fim) {
		
		while (ini < fim && (compara_info(alunos[ini], pivo, escolha) == false)) { //se o primeiro for maior que o segundo irá retornar true
			ini++;
		}
		
		while (ini < fim && (compara_info(alunos[fim], pivo, escolha) == true)) { //se o primeiro for maior que o segundo irá retornar true
			fim--;
		}
		
		trocar_alunos(&alunos[ini], &alunos[fim]);
	}
	
	return ini;
}

//método insertion sort
void insertion_sort(){
	//exemplo: [2,4,1,3,0,5]
	
	//variáveis
	int escolha, i, j, k;
				
	//menu de opções para ordenação
	printf("Digite qual opcao deseja utilizar para a ordenacao: \n");
	printf("(1) - Nome e sobrenome \n");
	printf("(2) - Sobrenome e nome\n");
	printf("(3) - Data de nascimento \n");
	printf("(4) - Prontuario \n");			
	printf("(5) - Curso \n\n");
	scanf("%d", &escolha);
	
	para_mtd_ord_escolhido = escolha; // altera o valor do parâmetro escolhido para o método de ordenação
	
	//[5,1,4,5,2]
	// j i
	      
	//laço mais externo - controla a seleção de cada índice para comparar com o anterior
	for(i = 1; i < cont; i++) {
		for(j = 0; j < i; j++) {
			if(compara_info(alunos[i], alunos[j], escolha) == false) { //se o primeiro for maior que o segundo é retornado true
				for(k = j; k < i; k++) {
					trocar_alunos(&alunos[k], &alunos[i]);				
				}
				break;
			}
		}
	}
	
	printf("Ordenacao concluida ! \n");
}

//função para realizar busca binária
int busca_binaria(){
	//variáveis
	int escolha;
	bool verifica = false;  //variável que verifica se algum aluno foi encontrado
	
	//menu de opções para a busca
	printf("Digite qual opcao deseja utilizar para a busca binária: \n");
	printf("(1) - Nome e sobrenome \n");
	printf("(2) - Sobrenome e nome\n");
	printf("(3) - Data de nascimento \n");
	printf("(4) - Prontuario \n");			
	printf("(5) - Curso \n\n");
	scanf("%d", &escolha);
	
	if(escolha == para_mtd_ord_escolhido){

		//NOME
		//exibe de acordo com o tipo de critério
		if(escolha == 1){
			//variáveis
			char nome[50];
			
			printf("Digite o nome do aluno desejado: \n");
			scanf("%s", &nome);
			
			//variáveis
			int ini = 0;
			int fim = cont-1;
			int meio;
			
			while(ini <= fim){
				meio = (ini + fim) / 2;
				//primeira situação - se o dado procurado for o do meio do vetor
				if(strcmp(alunos[meio].nome, nome) == 0){
					imprimir(meio);
					
					verifica = true;
				}
				//segunda situação - se o dado procurado estiver antes da metade
				if(strcmp(alunos[meio].nome, nome) > 0){
					fim = meio-1;
				}
				//terceira situação - se o dado procurado estiver além da metade do vetor
				else{
					ini = meio+1;
				}
				
			}
			if(verifica == false){
					printf("\n Aluno nao existe no registro! \n \n");	
			}
		}
		
		//SOBRENOME
		//exibe de acordo com o tipo de critério
		else if(escolha == 2){
			//variáveis
			char sobrenome[50];
			
			printf("Digite o sobrenome do aluno desejado: \n");
			scanf("%s", &sobrenome);
			
			//variáveis
			int ini = 0;
			int fim = cont-1;
			int meio;
			
			while(ini <= fim){
				meio = (ini + fim) / 2;
				//primeira situação - se o dado procurado for o do meio do vetor
				if(strcmp(alunos[meio].sobrenome, sobrenome) == 0){
					imprimir(meio);
					
					verifica = true;
				}
				//segunda situação - se o dado procurado estiver antes da metade
				if(strcmp(alunos[meio].sobrenome, sobrenome) > 0){
					fim = meio-1;
				}
				//terceira situação - se o dado procurado estiver além da metade do vetor
				else{
					ini = meio+1;
				}
				
			}
			if(verifica == false){
					printf("\n Aluno nao existe no registro! \n \n");	
			}
		}
		
		//DATA
		//exibe de acordo com o tipo de critério
		else if(escolha == 3){
			//variáveis
			data data_aux;
			//entradas
			printf("Digite o dia de nascimento: \n");
			scanf("%d", &data_aux.dia);
			printf("Digite o mes de nascimento: \n");
			scanf("%d", &data_aux.mes);
			printf("Digite o ano de nascimento: \n");
			scanf("%d", &data_aux.ano);
			
			//variáveis
			int ini = 0;
			int fim = cont-1;
			int meio;
			
			while(ini <= fim){
				meio = (ini + fim) / 2;
				//primeira situação - se o dado procurado for o do meio do vetor
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
				//segunda situação - se o dado procurado estiver antes da metade
				if(compara_data(data_aux, alunos[meio].datadenascimento) == false){
					fim = meio-1;
				}
				//terceira situação - se o dado procurado estiver além da metade do vetor
				else{
					ini = meio+1;
				}
				
			}
			if(verifica == false){
					printf("\n Aluno nao existe no registro! \n \n");	
			}
		}
		
		//PRONTUÁRIO
		//exibe de acordo com o tipo de critério
		else if(escolha == 4){
			//variáveis
			int prontuario;
			
			printf("Digite o prontuario do aluno desejado: \n");
			scanf("%d", &prontuario);
			
			//variáveis
			int ini = 0;
			int fim = cont-1;
			int meio, i;
			
			while(ini <= fim){
				meio = (ini + fim) / 2;
				//primeira situação - se o dado procurado for o do meio do vetor
				if(alunos[meio].prontuario == prontuario){
					imprimir(meio);
					
					verifica = true;
				}
				//segunda situação - se o dado procurado estiver antes da metade
				if(alunos[meio].prontuario > prontuario){
					fim = meio-1;
				}
				//terceira situação - se o dado procurado estiver além da metade do vetor
				else{
					ini = meio+1;
				}
				
			}
			if(verifica == false){
					printf("\n Aluno nao existe no registro! \n \n");	
			}
		}
		
		//CURSO
		//exibe de acordo com o tipo de critério
		else if(escolha == 5){
			//variáveis
			char curso[4];
			
			printf("Digite o curso do aluno desejado: \n");
			scanf("%s", &curso);
			
			//variáveis
			int ini = 0;
			int fim = cont-1;
			int meio;
			
			while(ini <= fim){
				meio = (ini + fim) / 2;
				//primeira situação - se o dado procurado for o do meio do vetor
				if(strcmp(alunos[meio].curso, curso) == 0){
					imprimir(meio);
					
					verifica = true;
				}
				//segunda situação - se o dado procurado estiver antes da metade
				if(strcmp(alunos[meio].curso, curso) > 0){
					fim = meio-1;
				}
				//terceira situação - se o dado procurado estiver além da metade do vetor
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

// função para carregar alunos de um arquivo
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

// função para salvar alunos num arquivo
void salvar(){ //chamada com a opção 7
	FILE *arquivo;
	
	arquivo = fopen("alunos.bin", "wb"); //write bin
	if(arquivo != 0) {
		fwrite(&cont, sizeof(int), 1, arquivo);
		fwrite(&alunos, sizeof(aluno), cont, arquivo);
		
		fclose(arquivo);
	
		printf("Alunos salvos com sucesso \n");
	} else {
		printf("Erro na criação do arquivo \n \n");
	}
}

bool compara_info(aluno aluno_menor, aluno aluno_j, int escolha){
	//variáveis
	int i;
	//analisa a opção escolhida
	if(escolha == 1){
		//ordenação por nome e sobrenome
		if(strcmp(aluno_menor.nome ,aluno_j.nome)>0){
			return true;
		}else{
			return false;
		}
	}
	
	else if(escolha == 2){
		//ordenação por sobrenome e nome
		if(strcmp(aluno_menor.sobrenome ,aluno_j.sobrenome)>0){
			return true;
		}else{
			return false;
		}
	}
	else if(escolha == 3){
		//ordenação feita por data
		if(compara_data(aluno_menor.datadenascimento, aluno_j.datadenascimento) == true){
			return true;
		}else{
			return false;
		}
	}
	
	else if(escolha == 4){
		//ordenação por prontuário
		if(aluno_j.prontuario < aluno_menor.prontuario){
			return true;
		}
		else{
			return false;
		}
	}
	
	else if(escolha == 5){
		//ordenação por curso
		if(strcmp(aluno_menor.curso ,aluno_j.curso)>0){
			return true;
		}else{
			return false;
		}
	}	
}

void trocar_alunos(aluno *a, aluno *b){
	//variáveis
	aluno aux;
	
	//printf("Aluno A: %d \n", a.prontuario);
	//printf("Aluno B: %d \n", b.prontuario);
	
	aux = *a;
	*a = *b;
	*b = aux;
}

//imprime aluno passado pela busca binária
void imprimir(int i){
	printf("\n");
	printf("Prontuario: %d \n", alunos[i].prontuario);
	printf("Nome: %s \n", alunos[i].nome);
	printf("Sobrenome: %s \n", alunos[i].sobrenome);
	printf("Data de nascimento: %d/%d/%d \n", alunos[i].datadenascimento.dia,alunos[i].datadenascimento.mes,alunos[i].datadenascimento.ano);
	printf("Curso: %s \n \n", alunos[i].curso);
	
}
