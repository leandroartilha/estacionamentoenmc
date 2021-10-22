#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

typedef struct{
	int horaEnt;
	int minEnt;
	int horaSaida;
	int minSaida;	
}Tempo;

typedef struct{
	Tempo tempo;
	char placa[8];
}Estac;

int menu(){
	int opt;
	printf("\nMenu:");
	printf("\n1 - Cadastrar a entrada de um veiculo.");
	printf("\n2 - Lancar a retirada do veiculo.");
	printf("\n3 - Sair.");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opt);
	getchar();
	return opt;
	system("cls");
}

Estac cadastrarVeiculo(){

	Estac vei;
	printf("\nPlaca do veiculo: ");
	gets(vei.placa);
	printf("Tempo de entrada: ");
	printf("\nHoras (de 06 a 18): ");
	scanf("%d", &vei.tempo.horaEnt);
	printf("\nMinutos (de 00 a 59): ");
	scanf("%d", &vei.tempo.minEnt);
	if(vei.tempo.minEnt > 59){
		printf("\nMinutos invalidos, insira novamente: ");
		scanf("%d", &vei.tempo.minEnt);
	}
	getchar();
	
	return vei;
	
}

void exibirVeiculo(Estac v){
	printf("\n\nPlaca: %s", v.placa);
	printf("\nTempo de entrada: ");
	printf("\nHoras: %d", v.tempo.horaEnt);
	printf("\nMinutos: %d", v.tempo.minEnt);
}

void listarVeiculo(Estac veic[]){
	
	int i;
	for(i=0; i<MAX; i++){
		exibirVeiculo(veic[i]);
	}
}


int pagamento(int horaE, int minE, int horaSai, int minS){
	//horas
	
	int horaS;
	
	if(horaSai>18){
		horaS = 18;
	}else{
		horaS = horaSai;
	}
	
	float taxa = 0.10;
	float horasTotais = horaS - horaE;
	float hTMinutos = horasTotais * 60;  
	float valorDeHoras = hTMinutos * taxa;
	float taxaMin;
	
	//minutos
	float minTotais;
	if(minS > minE){
		minTotais = minS - minE;
		taxaMin = minTotais*taxa;
		printf("\nValor a ser pago: %.2f Reais.", valorDeHoras + taxaMin );
		
	}else if(minE > minS){
		minTotais = minE - minS;
		taxaMin = minTotais*taxa;
		printf("\nValor a ser pago: %.2f Reais.", valorDeHoras - taxaMin);
	}else{
		printf("\nValor a ser pago: %2.f Reais.", valorDeHoras);
	}
}


void buscarVeiculo(Estac veiculo[], int tam, char placaV[8]){
	
	int i;
	int retorno;
	for(i=0; i<=tam; i++){
		retorno = strcmp(veiculo[i].placa, placaV);
		if(retorno == 0){
			exibirVeiculo(veiculo[i]);
			printf("\n\nInsira a hora e os minutos que voce saiu");
			printf("\nHora de saida (de 06 a 18): ");
			scanf("%d", &veiculo[i].tempo.horaSaida);
			getchar();
			if(veiculo[i].tempo.horaSaida < veiculo[i].tempo.horaEnt){
				printf("\nHora de saida invalida, insira novamente: ");
				printf("\nHora de saida (de 06 a 18): ");
				scanf("%d", &veiculo[i].tempo.horaSaida);
				getchar();
			}
		
			printf("Minuto de saida (de 00 a 59): ");
			scanf("%d", &veiculo[i].tempo.minSaida);
			if(veiculo[i].tempo.minSaida > 59){
				printf("\nMinuto invalido, insira novamente: ");
				scanf("%d", &veiculo[i].tempo.minSaida);
			}
			
			
			
			pagamento(veiculo[i].tempo.horaEnt, veiculo[i].tempo.minEnt, veiculo[i].tempo.horaSaida, veiculo[i].tempo.minSaida);
			return;
			
		}
			
			}
			printf("\nVeiculo nao cadastrado");
}

int main(int argc, char *argv[]){
	
	Estac *veiculo;
	Estac vei;
	int contVeiculo = -1;
	int i;
	int opt;
	char placaV[8];
	veiculo = (Estac*) malloc(MAX * sizeof(Estac));

	do{
		opt = menu();
		switch(opt){
			case 1:
				
				if(contVeiculo < MAX - 1){
				vei = cadastrarVeiculo();
				veiculo[++contVeiculo] = vei;
				}else{
					printf("\n\nEstacionamento cheio.");
				}
				break;
			case 2:
				printf("Digite a placa do veiculo que voce ira retirar: ");
				gets(placaV);
				buscarVeiculo(veiculo,contVeiculo, placaV);
				break;
			case 3:
				break;
			
			default:
				printf("Opcao invalida.");
				break;
		}
		
	}while(opt !=3);
	free(veiculo);
}

