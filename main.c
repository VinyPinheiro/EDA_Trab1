#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "list.h"

void menu(){
	printf("\n0 - Sair\n");
	printf("1 - Inserir processo\n");
	printf("2 - Encerrar processo\n");
	printf("3 - Reorganizar processos\n");
	printf("4 - Mostrar status da memória\n\n");
}

int main(){
	char *p=malloc(50),*f=malloc(50),*t=malloc(50);
	List *li;
	int sizeProcess, page, option=1;

	li=(List *)malloc(sizeof(List));

	startList(li);

	while(option){
		menu();
		printf("Opção: ");
		scanf("%d", &option);

		switch(option){
			case 1:
				printf("Digite o tamanho do novo processo: ");
				scanf("%d", &sizeProcess);
				insert(li, sizeProcess);
			break;

			case 2:
				printf("Digite a página do processo que deseja encerrar: ");
				scanf("%d", &page);
				closeProcess(li, page);
			break;

			case 3:
				organizeProcesses(li);
			break;

			case 4:
				sprintf(p,"%d",li->total_process);
				sprintf(t,"%.0f",li->total_memory);
				sprintf(f,"%.0f",li->process_memory);
				mountScreen(p,f, t);
			break;
		}
	}
	return 0;
}

