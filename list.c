#include "list.h"
#include "list.h"

/*Start the List*/
void startList(List *li){
	int sizeMemory;

	printf("Memória total: ");
	scanf("%d", &sizeMemory);

    li->first=(Node *)malloc(sizeof(Node));
    li->first->type='H';
    li->first->page=0;
    li->first->sizeProcess=sizeMemory;
    li->total_memory = sizeMemory;
    li->process_memory = 0;
    li->total_process = 0;

	li->last=li->first;
}

/*Insert a node in the list*/
void insert(List *li, int sizeNewProcess){
	Node *p, *aux;

	p=li->first;

	while(p->type !='H' || p->sizeProcess-p->page<sizeNewProcess){
		if(p->next==NULL){
			printf("%c", (char)7);
			printf("\nSem memória disponível. Tente novamente após reorganizar os processos de memória\n");
			return;
		}
		p=p->next;
	}

	aux=(Node *)malloc(sizeof(Node));
	aux->type='P';
	aux->page=p->page;
	aux->sizeProcess=p->page+sizeNewProcess;

	p->page=aux->sizeProcess;
	aux->next=p;
	
	li->total_process++;
	li->process_memory += sizeNewProcess;
	
	if(p->previous==NULL){
		p->previous=aux;

		li->first=aux;

		return;
	}

	p->previous->next=aux;
	aux->previous=p->previous;

	aux->next=p;
	p->previous=aux;

	p=li->first;

}

/*Remove a process from the list*/
void closeProcess(List *li, int page){
	Node *p = malloc(sizeof(Node));

	p=li->first;

	while(p->page!=page){
		p=p->next;
		if(p == NULL)
			return;
	}
	
	if(p == NULL || p->type == 'H')
		return;
	li->total_process--;
	li->process_memory -= (p->sizeProcess - p->page);
	p->type='H';

	if(p->previous!=NULL && p->previous->type=='H'){
		p->previous->sizeProcess=p->sizeProcess;
		p->previous->next=p->next;
		p->next->previous=p->previous;
		p=p->previous;
	}

	if(p->next!=NULL &&  p->next->type=='H'){
		p->sizeProcess=p->next->sizeProcess;
		p->next=p->next->next;
		if(p->next!=NULL){
			p->next->previous=p;
		}
		
	}
}

/*Show all process*/
void showProcesses(List *li){
	Node *p;

	p=li->first;
	printf("Tipo\tPonto de Inicio\tTamanho\n");
	while(p!=NULL){
		printf("%c\t", p->type);
		printf("%d\t\t", p->page);
		printf("%d\n", p->sizeProcess-p->page);

		p=p->next;
	}
}

/*Rearranges the process so that it has no free memory fragments between processes*/
void organizeProcesses(List *li){
	int sum=0, sizeProcess;
	Node *p;

	if(li->total_process == 0)
		return;
	
	p=li->first;

	while(p->next!=NULL){

		if(p->type=='H'){
			/*Check when the p->previous is NULL*/

			if(p->previous==NULL){
				p=p->next;
				p->sizeProcess=p->sizeProcess - p->page;
				p->page=0;
				p->previous=NULL;

				li->first=p;

				p=p->next;

				continue;
			}
			
			sizeProcess=p->next->sizeProcess - p->next->page;
	
			p->next->page=p->previous->sizeProcess;
			p->next->sizeProcess=p->next->page + sizeProcess;

			p->previous->next=p->next;
			p->next->previous=p->previous;
		}
		
		p=p->next;
	}

	p->type='H';
	p->page=p->previous->sizeProcess;
	p->next=NULL;
	
}

