#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_MAX 100

typedef char string[STRING_MAX];

string nome_posicoes[] = {
    "Goleira","Zagueira Esquerda","Zagueira Direita","Lateral Esquerda","Lateral Direita",
    "Meia Central","Meia Esquerdo","Meia Direito","Atacante","Ponta Esquerda","Ponta Direita"
};

#define POSICOES_QTD 11

string nome_estado[] = {
    "Ativa","Vendida","Em recuperação médica"
};

#define ESTADOS_QTD 3

typedef struct dados_jogadora {
	int id;
    string nome;
    int idade;
    float altura;
    int peso;
    int posicao;
    int passe_para_venda;
    int valor_de_aquisicao;
    int salario;
    int estado;
	int valor_de_venda; // (-1 == não vendida)
} dados_jogadora_t;

typedef struct jogadoras {
	dados_jogadora_t dados;
	struct jogadoras *proxima;
} jogadoras_t;

string nome_resultados[] = {
    "Vitória","Empate","Derrota"
};

#define RESULTADOS_QTD 3

#define TAMANHO_TIME 11

typedef struct dados_jogos {
	int id;
    string nome_adversario;
    string data; // formato: "dd/mm/yyyy"
    string local;
	int goals[2]; // goals[0] = Criciúma, goals[1] = adversário
	int resultado; // 0=Vitória, 1=Empate, 2=Derrota
    int time[TAMANHO_TIME]; // nomes das jogadoras antes da substituição
    int substituicoes_qtd;
} dados_jogos_t;

typedef struct jogos {
	dados_jogos_t dados;
	struct jogos *proximo;
} jogos_t;

typedef struct time {
	jogadoras_t *primeira_jogadora;
	int qtd_jogadoras;
	jogos_t *primeiro_jogo;
	int qtd_jogos;
} team_t;

#define SAVE_DIR "./saves/"
#define EXPORT_DIR "./exportados/"
#define FORMATO_TELA 1
#define FORMATO_TXT  2
#define FORMATO_CSV  3
#define FORMATO_HTML 4

// menus

int menu_principal(void);
int menu_cadastros(void);
int menu_relatorios(void);
int menu_buscas(void);

// cadastro

void gerar_cadastros(int opc, team_t *criciuma);
jogadoras_t* cadastro_jogadora(int qtd_jogadoras);
void inserir_jogadora_inicio(jogadoras_t*jogadora,team_t * criciuma);
void alterar_jogadora_por_nome(team_t * criciuma);
jogos_t *cadastro_jogo(team_t*criciuma);
void inserir_jogo_inicio(jogos_t*jogo,team_t * criciuma);

// relatório

void gerar_relatorios(int opc, team_t *criciuma);
int relatorio_jogadoras(int * ids, jogadoras_t * primeira, int qtd_ids); // completo
void selecionar_i(char* frase_min, char*frase_max, int i_range[2]);
void selecionar_f(char* frase_min,char* frase_max,float f_range[2]);
int *relatorio_idade(int idade[2],team_t * criciuma, int*qtd_ids);
int *relatorio_altura(float altura[2],team_t * criciuma, int*qtd_ids);
int *relatorio_peso(int peso[2],team_t * criciuma, int*qtd_ids);
int *relatorio_passe_para_venda(int passe_venda[2],team_t * criciuma,int *qtd_ids);
int *relatorio_valor_de_aquisicao(int aquisicao[2],team_t * criciuma, int*qtd_ids);
int *relatorio_salario(int salario[2],team_t * criciuma,int *qtd_ids);
int *relatorio_valor_de_venda(int venda[2],team_t * criciuma, int*qtd_ids);
int relatorio_jogos(team_t * criciuma,int qtd_ids,int * ids); // completo
int relatorio_aproveitamento(team_t * criciuma, FILE *saida, int formato);
int relatorio_adversarios(team_t * criciuma, FILE *saida, int formato);
int relatorio_valor(team_t * criciuma, FILE *saida, int formato); // jogadoras vendidas
void saida_de_dados_relatorios(int encontradas, int opc, int opc_exp, int * ids, int qtd_ids, team_t * criciuma);

// busca

void gerar_buscas(int opc, team_t *criciuma);
void busca_i(char* frase,int i_busca[2]);
void busca_f(char* frase,float f_busca[2]);
void busca_string(char * frase,char * palavra);
void busca_vetor_i(char * frase, string*nomes, int qtd_nomes,int i_busca[2]);
int *busca_jogadora_nome(char * nome_busca,team_t * criciuma,int *qtd_ids);
int *busca_jogadora_posicao(int pos_busca,team_t * criciuma, int*qtd_ids);
int *busca_jogadora_estado(int estado_busca,team_t * criciuma, int*qtd_ids);
int *busca_jogo_nome_adversario(char *nome_busca,team_t * criciuma, int*qtd_ids);
int *busca_jogo_data(char * data_busca,team_t * criciuma, int*qtd_ids);
int *busca_jogo_local(char* local_busca,team_t * criciuma, int*qtd_ids);
int *busca_jogo_resultado(int res_busca,team_t * criciuma, int*qtd_ids);
int *busca_jogo_time(char * jogadora_busca,team_t * criciuma, int*qtd_ids);
int *busca_jogo_substituicoes_qtd(int subs_busca,team_t * criciuma, int*qtd_ids);
void saida_de_dados_buscas(int encontradas, int opc, int opc_exp, int * ids, int qtd_ids, team_t * criciuma);

// saída e exp
int menu_exportar(void);
void obter_nome_arquivo(string nome_arquivo, const char *extensao);
void exportar_jogadoras_txt(FILE *arquivo, int *ids, jogadoras_t *primeira, int qtd_ids);
int exportar_jogadoras_csv(FILE *arquivo, int *ids, jogadoras_t *primeira, int qtd_ids);
int exportar_jogadoras_html(FILE *arquivo, int *ids, jogadoras_t *primeira, int qtd_ids);
void exportar_jogos_txt(FILE *arquivo, int *ids, team_t *criciuma, int qtd_ids);
int exportar_jogos_csv(FILE *arquivo, int *ids, team_t *criciuma, int qtd_ids);
int exportar_jogos_html(FILE *arquivo, int *ids, team_t *criciuma, int qtd_ids);

// util

/* Função de cores
Estilo: 0=Normal, 1=Negrito, 2=Dim, 4=Sublinhado, 5=Piscar, 7=Reverter, 8=Oculto
Cor Texto: 0=Preto, 1=Vermelho, 2=Verde, 3=Amarelo, 4=Azul, 5=Roxo, 6=Ciano, 7=Branco
Cor Fundo: 0=Preto, 1=Vermelho, 2=Verde, 3=Amarelo, 4=Azul, 5=Roxo, 6=Ciano, 7=Branco, -1=Nenhum*/
void definir_cor(int cor_texto, int cor_fundo, int estilo);
void resetar_cor();

#define COR_PRETO 0
#define COR_VERMELHO 1
#define COR_VERDE 2
#define COR_AMARELO 3
#define COR_AZUL 4
#define COR_ROXO 5
#define COR_CIANO 6
#define COR_BRANCO 7

#define ESTILO_NORMAL 0
#define ESTILO_BOLD 1
#define ESTILO_DIM 2
#define ESTILO_SUBLINHADO 4
#define ESTILO_PISCAR 5
#define ESTILO_REVERTER 7
#define ESTILO_OCULTO 8

void ler_string(char* palavra);
void mostrar_jogadora(jogadoras_t* jogadora);
void mostrar_jogo(jogos_t*jogo,team_t * criciuma);
char *obter_nome_jogadora_por_id(int id, team_t *criciuma);
void salvar_bin_jogadoras(jogadoras_t * jogadoras);
void salvar_bin_jogos(jogos_t * jogos);
void ler_bin_jogadoras(team_t * criciuma);
void ler_bin_jogos(team_t * criciuma);
void ordenar_jogos_id(team_t*criciuma);
void ordenar_jogadoras_id(team_t * criciuma);

int main(){
	team_t criciuma;
	criciuma.primeira_jogadora=NULL;
	criciuma.primeiro_jogo=NULL;
    criciuma.qtd_jogadoras=0;
	criciuma.qtd_jogos=0;

    ler_bin_jogadoras(&criciuma);
    ler_bin_jogos(&criciuma);
    ordenar_jogadoras_id(&criciuma);
    ordenar_jogos_id(&criciuma);
	
    definir_cor(COR_VERDE, -1, ESTILO_BOLD);
    printf("Olá, seja bem vindo(a)!\n\n");
    resetar_cor();
	
    int opcao,opcao2;

    do {
        opcao = menu_principal();

        switch(opcao){
            case 1: //cadastros
                do {
                    opcao2 = menu_cadastros();
                    gerar_cadastros(opcao2, &criciuma);
                } while (opcao2!=0);
            break;

            case 2: //relatórios
                do {
                    opcao2 = menu_relatorios();
                    gerar_relatorios(opcao2, &criciuma);
                } while (opcao2!=0);
            break;

            case 3: //buscas
                do {
                    opcao2 = menu_buscas();
                    gerar_buscas(opcao2, &criciuma);
                } while (opcao2!=0);
            break;

            case 0:
                definir_cor(COR_VERDE, -1, ESTILO_BOLD);
                printf("\nTchau!!!\n\n");
                resetar_cor();
            break;

            default:
                definir_cor(COR_VERMELHO, -1, ESTILO_BOLD);
                printf("\nOpção invalida!!!\n\n");
                resetar_cor();
            break;
        }
    } while (opcao!=0);

    jogadoras_t * aux_jogadora;
    jogos_t*aux_jogo;
    if(criciuma.primeira_jogadora){
        salvar_bin_jogadoras(criciuma.primeira_jogadora);
    }
    while(criciuma.primeira_jogadora){
        aux_jogadora=criciuma.primeira_jogadora;
        criciuma.primeira_jogadora=criciuma.primeira_jogadora->proxima;
        free(aux_jogadora);
    }
    if(criciuma.primeiro_jogo){
        salvar_bin_jogos(criciuma.primeiro_jogo);
        
    }
    while(criciuma.primeiro_jogo){
        aux_jogo=criciuma.primeiro_jogo;
        criciuma.primeiro_jogo=criciuma.primeiro_jogo->proximo;
        free(aux_jogo);
    }

    return 0;
}

int menu_principal(void){
    int opc;
    definir_cor(COR_CIANO, -1, ESTILO_BOLD); printf("Escolha uma área:\n\n"); resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[1] "); resetar_cor(); printf("Cadastros\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[2] "); resetar_cor(); printf("Relatórios\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[3] "); resetar_cor(); printf("Buscas\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[0] "); resetar_cor(); printf("Sair\n\n");
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("-> "); resetar_cor();
    scanf("%d",&opc);
    getchar(); 
    return opc;
}

int menu_cadastros(void){
    int opc;
    definir_cor(COR_CIANO, -1, ESTILO_BOLD);
    printf("\nEscolha um tipo de cadastro:\n\n");
    resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[1] "); resetar_cor(); printf("Cadastrar nova jogadora\n");
	definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[2] "); resetar_cor(); printf("Alterar estado de jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[3] "); resetar_cor(); printf("Cadastrar novo jogo\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[0] "); resetar_cor(); printf("Voltar\n\n");
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("-> "); resetar_cor();
    scanf("%d",&opc);
    getchar(); 
    return opc;
}

void gerar_cadastros(int opc, team_t *criciuma){
	jogadoras_t *jogadora_aux;
	jogos_t *jogo_aux;
    ordenar_jogadoras_id(criciuma);
    ordenar_jogos_id(criciuma);
    switch (opc){
        case 1:
            definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Cadastrando nova jogadora ---\n\n"); resetar_cor();
            jogadora_aux = cadastro_jogadora(criciuma->qtd_jogadoras);
			inserir_jogadora_inicio(jogadora_aux,criciuma);
            definir_cor(COR_VERDE, -1, ESTILO_BOLD); printf("\nCadastro de jogadora finalizado!!!\n"); resetar_cor();
        break;
		case 2:
            definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Alterando estado da jogadora ---\n\n"); resetar_cor();
            alterar_jogadora_por_nome(criciuma);
            definir_cor(COR_VERDE, -1, ESTILO_BOLD); printf("\nAlteração de estado da jogadora finalizado!!!\n"); resetar_cor();
		break;
        case 3:
            definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Cadastrando novo jogo ---\n\n"); resetar_cor();
            jogo_aux=cadastro_jogo(criciuma);
            inserir_jogo_inicio(jogo_aux,criciuma);
            definir_cor(COR_VERDE, -1, ESTILO_BOLD); printf("\nCadastro de jogo finalizado!!!\n"); resetar_cor();
        break;
        case 0:
            definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("\nVoltando ao menu principal...\n\n"); resetar_cor();
        break;
        default:
            definir_cor(COR_VERMELHO, -1, ESTILO_BOLD); printf("\nOpção invalida!!!\n"); resetar_cor();
        break;
    }
    return;
}

jogadoras_t * cadastro_jogadora(int qtd_jogadoras){
	jogadoras_t *nova_jogadora = (jogadoras_t*)malloc(sizeof(jogadoras_t));
	
	if(!nova_jogadora) return NULL;
	
	nova_jogadora->dados.id= ++qtd_jogadoras;
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o nome da jogadora: "); resetar_cor();
	ler_string(nova_jogadora->dados.nome);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite a idade da jogadora: "); resetar_cor();
	scanf("%d",&nova_jogadora->dados.idade);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite a altura da jogadora (ex: 1.75): "); resetar_cor();
	scanf("%f",&nova_jogadora->dados.altura);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o peso da jogadora (kg): "); resetar_cor();
	scanf("%d",&nova_jogadora->dados.peso);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Escolha a posição da jogadora: \n"); resetar_cor();
	for(int i = 0; i<POSICOES_QTD;i++){
        definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[%d] ",i); resetar_cor(); printf("%s\n",nome_posicoes[i]);
	}
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("\n-> "); resetar_cor();
	scanf("%d",&nova_jogadora->dados.posicao);
    while(nova_jogadora->dados.posicao < 0 || nova_jogadora->dados.posicao >= POSICOES_QTD){
        definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL); printf("Posição inválida. Tente novamente: "); resetar_cor();
        scanf("%d",&nova_jogadora->dados.posicao);
    }

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o passe para venda da jogadora (em mil R$): "); resetar_cor();
	scanf("%d",&nova_jogadora->dados.passe_para_venda);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o valor de aquisição da jogadora (em mil R$): "); resetar_cor();
	scanf("%d",&nova_jogadora->dados.valor_de_aquisicao);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o salário da jogadora (em mil R$): "); resetar_cor();
	scanf("%d",&nova_jogadora->dados.salario);
    nova_jogadora->dados.estado=0;
	getchar(); 

	nova_jogadora->proxima=NULL;
	return nova_jogadora;
}

void alterar_jogadora_por_nome(team_t *criciuma){
    string aux;
    int *ids,temp_id,contido = 0,opcao,qtd_ids;
    jogadoras_t * jogadora = criciuma->primeira_jogadora;

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("\nDigite o nome da jogadora a ter o estado alterado: "); resetar_cor();
    ler_string(aux);
    ids = busca_jogadora_nome(aux, criciuma,&qtd_ids);
    while(*ids==-1){
        definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL); printf("Jogadora não encontrada. Tente novamente: "); resetar_cor();
        ler_string(aux);
        ids = busca_jogadora_nome(aux, criciuma,&qtd_ids);
    }
    if(qtd_ids==1){
        temp_id=*ids;
    } else {
        relatorio_jogadoras(ids, criciuma->primeira_jogadora,qtd_ids);
        definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Mais de uma jogadora encontrada, digite o Id da jogadora: "); resetar_cor();
        scanf("%d",&temp_id);
        getchar();
        while(!contido){
            for(int j = 0; j<qtd_ids; j++){
                if(temp_id==*(ids+j)){
                    contido=1;
                    break;
                }
            }
            if(contido) break;
            definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL); printf("Id não encontrado. Tente novamente: "); resetar_cor();
            scanf("%d",&temp_id);
            getchar();
        }
    }
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Escolha o estado da jogadora: \n"); resetar_cor();
	for(int i = 0; i<ESTADOS_QTD;i++){
		definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[%d] ",i); resetar_cor(); printf("%s\n",nome_estado[i]);
	}
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("\n-> "); resetar_cor();
	scanf("%d",&opcao);
    while(opcao < 0 || opcao >= ESTADOS_QTD){
        definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL); printf("Estado inválido. Tente novamente: "); resetar_cor();
        scanf("%d",&opcao);
    }
    while(jogadora){
        if(jogadora->dados.id==temp_id){
            switch(opcao){
                case 0:
                    jogadora->dados.estado=0;
                break;
                case 1:
                    jogadora->dados.estado=1;
                    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o valor de venda da jogadora: "); resetar_cor();
                    scanf("%d",&jogadora->dados.valor_de_venda);
                break;
                case 2:
                    jogadora->dados.estado=2;
                break;
            }
			break;
        }
		jogadora=jogadora->proxima;
    }
    getchar();
}

jogos_t* cadastro_jogo(team_t * criciuma){
    int qtd_ativas=0;
    jogadoras_t * jogadora_aux = criciuma->primeira_jogadora;
    while(jogadora_aux){
        if(jogadora_aux->dados.estado==0){
            qtd_ativas++;
        }
        jogadora_aux=jogadora_aux->proxima;
    }
	if(qtd_ativas<11){
		definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL); printf("Quantidade de jogadoras ativas insuficiente para escalar um jogo.\n"); resetar_cor();
        return NULL;
	}

	jogos_t *novo_jogo = (jogos_t*)malloc(sizeof(jogos_t));
	
	if(!novo_jogo) return NULL;
	
	novo_jogo->dados.id=criciuma->qtd_jogos+1;
	
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o nome do time adversário: "); resetar_cor();
	ler_string(novo_jogo->dados.nome_adversario);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite a data do jogo (formato dd/mm/yyyy, preencha os zeros): "); resetar_cor();
	ler_string(novo_jogo->dados.data);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o local do jogo: "); resetar_cor();
	ler_string(novo_jogo->dados.local);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite a quantidade de gols do Criciúma: "); resetar_cor();
	scanf("%d",&novo_jogo->dados.goals[0]);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite a quantidade de gols do time adversário: "); resetar_cor();
	scanf("%d",&novo_jogo->dados.goals[1]);

	if(novo_jogo->dados.goals[0] > novo_jogo->dados.goals[1]){
		novo_jogo->dados.resultado=0; // vitória
	} 
    else if(novo_jogo->dados.goals[0] == novo_jogo->dados.goals[1]){
		novo_jogo->dados.resultado=1; // empate
	} 
    else {
		novo_jogo->dados.resultado=2; // derrota
	}
	getchar(); 

    string aux;
    int *ids;
    int temp_id;
    int contido;
    int qtd_ids;
    int repetido;
    int vendida;
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL);
    printf("\nDigite o nome das %d jogadoras titulares do jogo: \n", TAMANHO_TIME);
    resetar_cor();

    for (int i =0; i<TAMANHO_TIME; i++){
        definir_cor(COR_VERDE, -1, ESTILO_NORMAL);
        printf("Titular %d: ", i + 1);
        resetar_cor();

        do {
            ler_string(aux);
            ids = busca_jogadora_nome(aux, criciuma, &qtd_ids);

            if (*ids !=-1){
                for (int j=qtd_ids-1; j>=0; j--){
                    vendida = 0;
                    jogadora_aux = criciuma->primeira_jogadora;
                    while (jogadora_aux){
                        if (jogadora_aux->dados.id == *(ids + j)){
                            if (jogadora_aux->dados.estado != 0){
                                vendida = 1;
                            }
                            break;
                        }
                        jogadora_aux = jogadora_aux->proxima;
                    }

                    repetido = 0;
                    for (int k = 0; k < i; k++){
                        if (*(novo_jogo->dados.time + k) == *(ids + j)){
                            repetido = 1;
                            break;
                        }
                    }

                    if (vendida || repetido){
                        for (int k = j; k < qtd_ids - 1; k++){
                            *(ids + k) = *(ids + (k + 1));
                        }
                        qtd_ids--;
                    }
                }
                if (qtd_ids > 0){
                    ids = realloc(ids, sizeof(int) * qtd_ids);
                } else {
                    free(ids);
                    ids = malloc(sizeof(int));
                    *ids = -1;
                }
            }

            if (*ids == -1){
                definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL);
                printf("Jogadora não encontrada (ou não está ativa/já está em uso). Tente novamente: ");
                resetar_cor();
            }

        } while (*ids == -1);

        if (qtd_ids == 1){
            *(novo_jogo->dados.time + i) = *ids;
        } else {
            relatorio_jogadoras(ids, criciuma->primeira_jogadora, qtd_ids);
            definir_cor(COR_VERDE, -1, ESTILO_NORMAL);
            printf("Mais de uma jogadora encontrada, digite o ID da jogadora: ");
            resetar_cor();
            contido = 0;
            do {
                scanf("%d", &temp_id);
                getchar();
                for (int j = 0; j < qtd_ids; j++){
                    if (temp_id == *(ids + j)){
                        contido = 1;
                        break;
                    }
                }
                if (contido) break;
                definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL);
                printf("ID não encontrado na lista. Tente novamente: ");
                resetar_cor();
            } while (!contido);
            *(novo_jogo->dados.time + i) = temp_id;
        }
    }

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite a quantidade de substituições realizadas no jogo: "); resetar_cor();
	scanf("%d",&novo_jogo->dados.substituicoes_qtd);
	getchar(); 

	novo_jogo->proximo=NULL;

    free(ids);
	return novo_jogo;
}

void inserir_jogadora_inicio(jogadoras_t*nova_jogadora,team_t * criciuma){
    if(!nova_jogadora){
        return;
    }

    if (criciuma->qtd_jogadoras==0){
        criciuma->primeira_jogadora = nova_jogadora;
        criciuma->qtd_jogadoras++;
        return;
    }

    nova_jogadora->proxima = criciuma->primeira_jogadora;
    criciuma->primeira_jogadora = nova_jogadora;
    criciuma->qtd_jogadoras++;
}

void inserir_jogo_inicio(jogos_t*novo_jogo,team_t * criciuma){
    if(!novo_jogo){
        return;
    }

    if (criciuma->qtd_jogos==0){
        criciuma->primeiro_jogo = novo_jogo;
        criciuma->qtd_jogos++;
        return;
    }

    novo_jogo->proximo = criciuma->primeiro_jogo;
    criciuma->primeiro_jogo = novo_jogo;
    criciuma->qtd_jogos++;
}

int menu_relatorios(void){
    int opc;
    definir_cor(COR_CIANO, -1, ESTILO_BOLD); printf("\nEscolha um relatório:\n\n"); resetar_cor();
    definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("--- Relatórios de Jogadoras ---\n"); resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[1] "); resetar_cor(); printf("Completo de todas as jogadoras\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[2] "); resetar_cor(); printf("Jogadoras por faixa de idade\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[3] "); resetar_cor(); printf("Jogadoras por faixa de altura\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[4] "); resetar_cor(); printf("Jogadoras por faixa de peso\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[5] "); resetar_cor(); printf("Jogadoras por faixa de passe para venda (mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[6] "); resetar_cor(); printf("Jogadoras por faixa de valor de aquisição (mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[7] "); resetar_cor(); printf("Jogadoras por faixa de salário (mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[8] "); resetar_cor(); printf("Jogadoras vendidas por faixa de valor de venda (mil R$)\n");
    definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Relatórios de Jogos ---\n"); resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[9] "); resetar_cor(); printf("Completo de todos os jogos\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[10] "); resetar_cor(); printf("Aproveitamento geral do time\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[11] "); resetar_cor(); printf("Desempenho contra times adversários\n");
    definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Relatórios Financeiros ---\n"); resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[12] "); resetar_cor(); printf("Valor total do time (baseado no valor de venda das jogadoras vendidas, em mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("\n[0] "); resetar_cor(); printf("Voltar\n\n");
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("-> "); resetar_cor();
    scanf("%d",&opc);
    getchar(); 
    return opc;
}

void gerar_relatorios(int opc, team_t*criciuma){
    int i_range[2];
    float f_range[2];
    int encontradas=0;
    int *ids=NULL;
    int qtd_ids=0;
    int opc_saida;
	int opc_exp;
    
    if(criciuma->qtd_jogadoras==0 && opc>=1 && opc<=8){ 
        definir_cor(COR_AMARELO, -1, ESTILO_BOLD);
        printf("\nSem jogadoras cadastradas!!!\n\n");
        resetar_cor();
        return; 
    }
    if(criciuma->qtd_jogos==0 && opc>=9 && opc<=12){ 
        definir_cor(COR_AMARELO, -1, ESTILO_BOLD);
        printf("\nSem jogos cadastrados!!!\n\n");
        resetar_cor();
        return; 
    }
    ordenar_jogadoras_id(criciuma);
    ordenar_jogos_id(criciuma);

    switch(opc){
        case 1:
        qtd_ids = criciuma->qtd_jogadoras;
        break;
        case 2:
            selecionar_i("\nDigite a idade mínima para o relatório: ","Digite a idade máxima para o relatório: ", i_range);
            ids = relatorio_idade(i_range, criciuma, &qtd_ids);
        break;
        case 3:
            selecionar_f("\nDigite a altura mínima (ex: 1.60): ","Digite a altura máxima (ex: 1.80): ", f_range);
            ids = relatorio_altura(f_range, criciuma, &qtd_ids);
        break;
        case 4:
            selecionar_i("\nDigite o peso mínimo (kg): ","Digite o peso máximo (kg): ", i_range);
            ids = relatorio_peso(i_range, criciuma, &qtd_ids);
        break;
        case 5:
            selecionar_i("\nDigite o valor mínimo do passe (mil R$): ","Digite o valor máximo do passe (mil R$): ", i_range);
            ids = relatorio_passe_para_venda(i_range, criciuma, &qtd_ids);
        break;
        case 6:
            selecionar_i("\nDigite o valor mínimo de aquisição (mil R$): ","Digite o valor máximo de aquisição (mil R$): ", i_range);
            ids = relatorio_valor_de_aquisicao(i_range, criciuma, &qtd_ids);
        break;
        case 7:
            selecionar_i("\nDigite o salário mínimo (mil R$): ","Digite o salário máximo (mil R$): ", i_range);
            ids = relatorio_salario(i_range, criciuma, &qtd_ids);
        break;
        case 8:
            selecionar_i("\nDigite o valor de venda mínimo (mil R$, apenas vendidas): ","Digite o valor de venda máximo (mil R$): ", i_range);
            ids = relatorio_valor_de_venda(i_range, criciuma, &qtd_ids);
        break;
        case 9:
            qtd_ids = criciuma->qtd_jogos;
        break;
        case 10: case 11: case 12:
            qtd_ids = 1;
        break;
        case 0:
            definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("\nVoltando ao menu principal...\n\n"); resetar_cor();
            return;
        default:
            definir_cor(COR_VERMELHO, -1, ESTILO_BOLD); printf("\nOpção invalida!!!\n"); resetar_cor();
            return;
    }

    switch(opc){
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
            definir_cor(COR_ROXO,-1,ESTILO_BOLD); printf("\n--- Relatório de Jogadoras ---\n"); resetar_cor();
            encontradas = relatorio_jogadoras(ids, criciuma->primeira_jogadora, qtd_ids);
        break;
        case 9:
            definir_cor(COR_ROXO,-1,ESTILO_BOLD); printf("\n--- Relatório de Jogos ---\n"); resetar_cor();
            encontradas = relatorio_jogos(criciuma, qtd_ids, ids);
        break;
        case 10:
            definir_cor(COR_ROXO, -1, ESTILO_BOLD); printf("\n--- Relatório de Aproveitamento Geral ---\n"); resetar_cor();
            encontradas = relatorio_aproveitamento(criciuma, stdout, FORMATO_TELA);
        break;
        case 11:
            definir_cor(COR_ROXO, -1, ESTILO_BOLD); printf("\n--- Relatório de Desempenho por Adversário ---\n"); resetar_cor();
            encontradas = relatorio_adversarios(criciuma, stdout, FORMATO_TELA);
        break;
        case 12:
            definir_cor(COR_ROXO, -1, ESTILO_BOLD); printf("\n--- Relatório de Valor Total do Time ---\n"); resetar_cor();
            encontradas = relatorio_valor(criciuma, stdout, FORMATO_TELA);
        break;
    }

    do {
        opc_exp = menu_exportar();
        saida_de_dados_relatorios(encontradas,opc,opc_exp,ids,qtd_ids,criciuma);
    } while (opc_exp !=1);

    if(ids) free(ids);
    definir_cor(COR_ROXO,-1,ESTILO_NORMAL);
    printf("\n--- Fim do Relatório ---\n\n");
    resetar_cor();
}

void saida_de_dados_relatorios(int encontradas, int opc, int opc_exp, int * ids, int qtd_ids, team_t * criciuma){
    if (opc_exp == 1) return;
    if(encontradas != 0){ 
        definir_cor(COR_AMARELO,-1,ESTILO_NORMAL); printf("\nNenhum item encontrado para exportar.\n"); resetar_cor();
        return;
    }
    
    string nome_arquivo;
    FILE *arquivo;
    const char *extensao;
    int itens_exportados = 0;

    switch(opc_exp){
        case 2: extensao = ".txt"; break;
        case 3: extensao = ".csv"; break;
        case 4: extensao = ".html"; break;
    }

    obter_nome_arquivo(nome_arquivo, extensao);
    arquivo = fopen(nome_arquivo, "w");

    if(!arquivo){
        definir_cor(COR_VERMELHO,-1,ESTILO_BOLD);vprintf("\nErro ao criar o arquivo '%s'!\n", nome_arquivo); resetar_cor();
        return;
    }
    switch(opc){
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
            if(opc_exp == 2) exportar_jogadoras_txt(arquivo, ids, criciuma->primeira_jogadora, qtd_ids);
            if(opc_exp == 3) exportar_jogadoras_csv(arquivo, ids, criciuma->primeira_jogadora, qtd_ids);
            if(opc_exp == 4) exportar_jogadoras_html(arquivo, ids, criciuma->primeira_jogadora, qtd_ids);
            itens_exportados = 1;
        break;
        case 9:
            if(opc_exp == 2) exportar_jogos_txt(arquivo, ids, criciuma, qtd_ids);
            if(opc_exp == 3) exportar_jogos_csv(arquivo, ids, criciuma, qtd_ids);
            if(opc_exp == 4) exportar_jogos_html(arquivo, ids, criciuma, qtd_ids);
            itens_exportados = 1;
        break;
        case 10:
            relatorio_aproveitamento(criciuma, arquivo, opc_exp);
            itens_exportados = 1;
        break;
        case 11:
            relatorio_adversarios(criciuma, arquivo, opc_exp);
            itens_exportados = 1;
        break;
        case 12:
            relatorio_valor(criciuma, arquivo, opc_exp);
            itens_exportados = 1;
        break;
    }
    fclose(arquivo);
    if(itens_exportados){
        definir_cor(COR_VERDE,-1,ESTILO_BOLD);
        printf("\nRelatório exportado com sucesso para '%s'!\n", nome_arquivo);
        resetar_cor();
    }
}

void gerar_buscas(int opc, team_t* criciuma){
    int i_busca[2];
    float f_busca[2];
    string string_busca;
    int encontradas = 1; // Inicia como 'não encontrado'
    int *ids = NULL;
    int qtd_ids = 0;
    int opc_exp;
    
    if(criciuma->qtd_jogadoras == 0 && opc >= 1 && opc <= 10){ 
        definir_cor(COR_AMARELO, -1, ESTILO_BOLD);
        printf("\nSem jogadoras cadastradas!\n\n");
        resetar_cor();
        return; 
    }
    if(criciuma->qtd_jogos == 0 && opc >= 11 && opc <= 16){ 
        definir_cor(COR_AMARELO, -1, ESTILO_BOLD);
        printf("\nSem jogos cadastrados!\n\n");
        resetar_cor();
        return; 
    }
    ordenar_jogadoras_id(criciuma);
    ordenar_jogos_id(criciuma);
    
    switch(opc){
        case 1:
            busca_string("Digite o nome (ou parte do nome) da jogadora a buscar: ", string_busca);
            ids = busca_jogadora_nome(string_busca, criciuma, &qtd_ids);
            break;
        case 2:
            busca_i("Digite a idade da jogadora a buscar: ", i_busca);
            ids = relatorio_idade(i_busca, criciuma, &qtd_ids);
            break;
        case 3:
            busca_f("Digite a altura da jogadora a buscar (ex: 1.75): ", f_busca);
            ids = relatorio_altura(f_busca, criciuma, &qtd_ids);
            break;
        case 4:
            busca_i("Digite o peso da jogadora a buscar (kg): ", i_busca);
            ids = relatorio_peso(i_busca, criciuma, &qtd_ids);
            break;
        case 5:
            busca_vetor_i("Escolha a posição a buscar:\n", nome_posicoes, POSICOES_QTD, i_busca);
            ids = busca_jogadora_posicao(i_busca[0], criciuma, &qtd_ids);
            break;
        case 6:
            busca_i("Digite o valor do passe para venda a buscar (mil R$): ", i_busca);
            ids = relatorio_passe_para_venda(i_busca, criciuma, &qtd_ids);
            break;
        case 7:
            busca_i("Digite o valor de aquisição a buscar (mil R$): ", i_busca);
            ids = relatorio_valor_de_aquisicao(i_busca, criciuma, &qtd_ids);
            break;
        case 8:
            busca_i("Digite o salário da jogadora a buscar (mil R$): ", i_busca);
            ids = relatorio_salario(i_busca, criciuma, &qtd_ids);
            break;
        case 9:
            busca_vetor_i("Escolha o estado a buscar:\n", nome_estado, ESTADOS_QTD, i_busca);
            ids = busca_jogadora_estado(i_busca[0], criciuma, &qtd_ids);
            break;
        case 10:
            busca_i("Digite o valor de venda da jogadora a buscar (mil R$, apenas entre as vendidas): ", i_busca);
            ids = relatorio_valor_de_venda(i_busca, criciuma, &qtd_ids);
            break;
        case 11:
            busca_string("Digite o nome (ou parte do nome) do time adversário a buscar: ", string_busca);
            ids = busca_jogo_nome_adversario(string_busca, criciuma, &qtd_ids);
            break;
        case 12:
            busca_string("Digite a data do jogo a buscar (dd/mm/yyyy): ", string_busca);
            ids = busca_jogo_data(string_busca, criciuma, &qtd_ids);
            break;
        case 13:
            busca_string("Digite o local (ou parte do local) do jogo a buscar: ", string_busca);
            ids = busca_jogo_local(string_busca, criciuma, &qtd_ids);
            break;
        case 14:
            busca_vetor_i("Escolha o resultado do jogo a buscar:\n", nome_resultados, RESULTADOS_QTD, i_busca);
            ids = busca_jogo_resultado(i_busca[0], criciuma, &qtd_ids);
            break;
        case 15:
            busca_string("Digite o nome da jogadora para buscar nos times titulares dos jogos: ", string_busca);
            ids = busca_jogo_time(string_busca, criciuma, &qtd_ids);
            break;
        case 16:
            busca_i("Digite a quantidade de substituições no jogo a buscar: ", i_busca);
            ids = busca_jogo_substituicoes_qtd(i_busca[0], criciuma, &qtd_ids);
            break;
        case 0:
            definir_cor(COR_CIANO, -1, ESTILO_NORMAL);
            printf("\nVoltando ao menu principal...\n\n");
            resetar_cor();
            return;
        default:
            definir_cor(COR_VERMELHO, -1, ESTILO_BOLD);
            printf("\nOpção inválida!\n");
            resetar_cor();
            return;
    }

    if (qtd_ids > 0) {
        if (opc >= 1 && opc <= 10) {
            definir_cor(COR_ROXO, -1, ESTILO_BOLD); printf("\n--- Resultado da Busca por Jogadoras ---\n"); resetar_cor();
            encontradas = relatorio_jogadoras(ids, criciuma->primeira_jogadora, qtd_ids);
        } else if (opc >= 11 && opc <= 16) {
            definir_cor(COR_ROXO, -1, ESTILO_BOLD); printf("\n--- Resultado da Busca por Jogos ---\n"); resetar_cor();
            encontradas = relatorio_jogos(criciuma, qtd_ids, ids);
        }
    }
    
    do {
        opc_exp = menu_exportar();
        saida_de_dados_buscas(encontradas, opc, opc_exp, ids, qtd_ids, criciuma);
    } while (opc_exp != 1);

    if (ids) free(ids);

    definir_cor(COR_ROXO, -1, ESTILO_NORMAL);
    printf("\n--- Fim da Busca ---\n\n");
    resetar_cor();
}

void saida_de_dados_buscas(int encontradas, int opc, int opc_exp, int * ids, int qtd_ids, team_t * criciuma){
    if (opc_exp == 1) return;
    if(encontradas != 0){ 
        definir_cor(COR_AMARELO,-1,ESTILO_NORMAL); printf("\nNenhum item encontrado para exportar.\n"); resetar_cor();
        return;
    }

    string nome_arquivo;
    FILE *arquivo;
    const char *extensao;
    int itens_exportados = 0;

    switch(opc_exp){
        case 2: extensao = ".txt"; break;
        case 3: extensao = ".csv"; break;
        case 4: extensao = ".html"; break;
        default: return;
    }

    obter_nome_arquivo(nome_arquivo, extensao);
    arquivo = fopen(nome_arquivo, "w");

    if(!arquivo){
        definir_cor(COR_VERMELHO,-1,ESTILO_BOLD);
        printf("\nErro ao criar o arquivo '%s'!\n", nome_arquivo); 
        resetar_cor();
        return;
    }

    if (opc >= 1 && opc <= 10) {
        if(opc_exp == 2) exportar_jogadoras_txt(arquivo, ids, criciuma->primeira_jogadora, qtd_ids);
        if(opc_exp == 3) exportar_jogadoras_csv(arquivo, ids, criciuma->primeira_jogadora, qtd_ids);
        if(opc_exp == 4) exportar_jogadoras_html(arquivo, ids, criciuma->primeira_jogadora, qtd_ids);
        itens_exportados = 1;
    } else if (opc >= 11 && opc <= 16) {
        if(opc_exp == 2) exportar_jogos_txt(arquivo, ids, criciuma, qtd_ids);
        if(opc_exp == 3) exportar_jogos_csv(arquivo, ids, criciuma, qtd_ids);
        if(opc_exp == 4) exportar_jogos_html(arquivo, ids, criciuma, qtd_ids);
        itens_exportados = 1;
    }
    
    fclose(arquivo);

    if(itens_exportados){
        definir_cor(COR_VERDE,-1,ESTILO_BOLD);
        printf("\nBusca exportada com sucesso para '%s'!\n", nome_arquivo);
        resetar_cor();
    }
}

int relatorio_jogadoras(int * ids, jogadoras_t * jogadoras, int qtd_ids){
    int encontradas = 1;
    if(!ids){
        while(jogadoras){
            mostrar_jogadora(jogadoras);
            jogadoras=jogadoras->proxima;
            encontradas = 0;
        }
    } else {
        while(jogadoras){
            for(int i =0;i<qtd_ids;i++){
                if(jogadoras->dados.id==*(ids+i)){
                    mostrar_jogadora(jogadoras);
                    encontradas = 0;
                    break;
                }
            }
            jogadoras=jogadoras->proxima;
        }
    }
    
	return encontradas;
}

void selecionar_i(char* frase_min, char*frase_max, int i_range[2]){
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("%s",frase_min); resetar_cor();
	scanf("%d",&i_range[0]);
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("%s",frase_max); resetar_cor();
	scanf("%d",&i_range[1]);
	getchar(); 
	return;
}

void selecionar_f(char* frase_min,char* frase_max,float f_range[2]){
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("%s",frase_min); resetar_cor();
    scanf("%f", &f_range[0]);
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("%s",frase_max); resetar_cor();
    scanf("%f", &f_range[1]);
    getchar(); 
    return;
}

int *relatorio_idade(int idade[2],team_t * criciuma, int *qtd_ids){
    int *ids = (int *)malloc(sizeof(int));
    if(!ids) return NULL;
    jogadoras_t *aux = criciuma->primeira_jogadora;
    *ids=-1;
    *qtd_ids=0;
	for(int i =0;i<criciuma->qtd_jogadoras;i++){
		if(aux->dados.idade>=idade[0] && aux->dados.idade<=idade[1]){
			if(*qtd_ids>0){
                ids=realloc(ids,sizeof(int)*(*qtd_ids+1));
                if (!ids) return NULL;
            }
            *(ids+(*qtd_ids)) = aux->dados.id;
			*qtd_ids+=1;
		}
        aux=aux->proxima;
	}
	return ids;
}

int *relatorio_altura(float altura[2], team_t *criciuma, int *qtd_ids){
    int *ids = (int *)malloc(sizeof(int));
    if(!ids) return NULL;
    jogadoras_t *aux = criciuma->primeira_jogadora;
    *ids=-1;
    *qtd_ids=0;
	for(int i =0;i<criciuma->qtd_jogadoras;i++){
		if(aux->dados.altura>=altura[0] && aux->dados.altura<=altura[1]){
			if(*qtd_ids>0){
                ids=realloc(ids,sizeof(int)*(*qtd_ids+1));
                if (!ids) return NULL;
            }
            *(ids+(*qtd_ids)) = aux->dados.id;
			*qtd_ids+=1;
		}
        aux=aux->proxima;
	}
	return ids;
}

int *relatorio_peso(int peso[2], team_t *criciuma, int *qtd_ids){
    int *ids = (int *)malloc(sizeof(int));
    if(!ids) return NULL;
    jogadoras_t *aux = criciuma->primeira_jogadora;
    *ids=-1;
    *qtd_ids=0;
	for(int i =0;i<criciuma->qtd_jogadoras;i++){
		if(aux->dados.peso>=peso[0] && aux->dados.peso<=peso[1]){
			if(*qtd_ids>0){
                ids=realloc(ids,sizeof(int)*(*qtd_ids+1));
                if (!ids) return NULL;
            }
            *(ids+(*qtd_ids)) = aux->dados.id;
			*qtd_ids+=1;
		}
        aux=aux->proxima;
	}
	return ids;
}

int *relatorio_passe_para_venda(int passe_venda[2], team_t *criciuma, int *qtd_ids){
    int *ids = (int *)malloc(sizeof(int));
    if(!ids) return NULL;
    jogadoras_t *aux = criciuma->primeira_jogadora;
    *ids=-1;
    *qtd_ids=0;
	for(int i =0;i<criciuma->qtd_jogadoras;i++){
		if(aux->dados.passe_para_venda>=passe_venda[0] && aux->dados.passe_para_venda<=passe_venda[1]){
			if(*qtd_ids>0){
                ids=realloc(ids,sizeof(int)*(*qtd_ids+1));
                if (!ids) return NULL;
            }
            *(ids+(*qtd_ids)) = aux->dados.id;
			*qtd_ids+=1;
		}
        aux=aux->proxima;
	}
	return ids;
}

int *relatorio_valor_de_aquisicao(int aquisicao[2], team_t *criciuma, int *qtd_ids){
    int *ids = (int *)malloc(sizeof(int));
    if(!ids) return NULL;
    jogadoras_t *aux = criciuma->primeira_jogadora;
    *ids=-1;
    *qtd_ids=0;
	for(int i =0;i<criciuma->qtd_jogadoras;i++){
		if(aux->dados.valor_de_aquisicao>=aquisicao[0] && aux->dados.valor_de_aquisicao<=aquisicao[1]){
			if(*qtd_ids>0){
                ids=realloc(ids,sizeof(int)*(*qtd_ids+1));
                if (!ids) return NULL;
            }
            *(ids+(*qtd_ids)) = aux->dados.id;
			*qtd_ids+=1;
		}
        aux=aux->proxima;
	}
	return ids;
}

int *relatorio_salario(int salario[2], team_t *criciuma, int *qtd_ids){
    int *ids = (int *)malloc(sizeof(int));
    if(!ids) return NULL;
    jogadoras_t *aux = criciuma->primeira_jogadora;
    *ids=-1;
    *qtd_ids=0;
	for(int i =0;i<criciuma->qtd_jogadoras;i++){
		if(aux->dados.salario>=salario[0] && aux->dados.salario<=salario[1]){
			if(*qtd_ids>0){
                ids=realloc(ids,sizeof(int)*(*qtd_ids+1));
                if (!ids) return NULL;
            }
            *(ids+(*qtd_ids)) = aux->dados.id;
			*qtd_ids+=1;
		}
        aux=aux->proxima;
	}
	return ids;
}

int *relatorio_valor_de_venda(int venda[2], team_t *criciuma, int *qtd_ids){
    int *ids = (int *)malloc(sizeof(int));
    if(!ids) return NULL;
    jogadoras_t *aux = criciuma->primeira_jogadora;
    *ids=-1;
    *qtd_ids=0;
	for(int i =0;i<criciuma->qtd_jogadoras;i++){
		if(aux->dados.estado == 1 && aux->dados.valor_de_venda>=venda[0] && aux->dados.valor_de_venda<=venda[1]){
			if(*qtd_ids>0){
                ids=realloc(ids,sizeof(int)*(*qtd_ids+1));
                if (!ids) return NULL;
            }
            *(ids+(*qtd_ids)) = aux->dados.id;
			*qtd_ids+=1;
		}
        aux=aux->proxima;
	}
	return ids;
}

int relatorio_jogos(team_t * criciuma,int qtd_ids,int * ids){
	jogos_t * aux = criciuma->primeiro_jogo;
    int encontradas = 2;
	if(!ids){
        while(aux){
            mostrar_jogo(aux,criciuma);
            aux=aux->proximo;
            encontradas = 0;
        }
    } else {
        while(aux){
            for(int i =0;i<qtd_ids;i++){
                if(aux->dados.id==*(ids+i)){
                    mostrar_jogo(aux,criciuma);
                    encontradas = 0;
                    break;
                }
            }
            aux=aux->proximo;
        }
    }
    
	return encontradas;
}

int relatorio_aproveitamento(team_t * criciuma, FILE *saida, int formato){
    jogos_t * jogos = criciuma->primeiro_jogo;
    int resultados_jogos[] = {0,0,0}, qtd_jogos = 0; // [0]=Vitorias, [1]=Empates, [2]=Derrotas
    if (!jogos) return 2;

    while(jogos){
        resultados_jogos[jogos->dados.resultado]++;
        qtd_jogos++;
        jogos = jogos->proximo;
    }

    float p_vitorias = 100 * (float)resultados_jogos[0]/qtd_jogos;
    float p_empates = 100 * (float)resultados_jogos[1]/qtd_jogos;
    float p_derrotas = 100 * (float)resultados_jogos[2]/qtd_jogos;

    switch(formato) {
        case FORMATO_TELA:
            definir_cor(COR_CIANO, -1, ESTILO_NORMAL); fprintf(saida, "\nTotal de jogos: %d\n", qtd_jogos); resetar_cor();
            fprintf(saida, "Porcentagem de "); definir_cor(COR_VERDE, -1, ESTILO_BOLD); fprintf(saida, "vitórias"); resetar_cor(); fprintf(saida, ": %.2f%% (%d)\n", p_vitorias, resultados_jogos[0]);
            fprintf(saida, "Porcentagem de "); definir_cor(COR_AMARELO, -1, ESTILO_BOLD); fprintf(saida, "empates"); resetar_cor(); fprintf(saida, ": %.2f%% (%d)\n", p_empates, resultados_jogos[1]);
            fprintf(saida, "Porcentagem de "); definir_cor(COR_VERMELHO, -1, ESTILO_BOLD); fprintf(saida, "derrotas"); resetar_cor(); fprintf(saida, ": %.2f%% (%d)\n", p_derrotas, resultados_jogos[2]);
            break;
        case FORMATO_TXT:
            fprintf(saida, "--- Relatório de Aproveitamento Geral ---\n\n");
            fprintf(saida, "Total de jogos: %d\n", qtd_jogos);
            fprintf(saida, "Vitórias: %.2f%% (%d)\n", p_vitorias, resultados_jogos[0]);
            fprintf(saida, "Empates: %.2f%% (%d)\n", p_empates, resultados_jogos[1]);
            fprintf(saida, "Derrotas: %.2f%% (%d)\n", p_derrotas, resultados_jogos[2]);
            break;
        case FORMATO_CSV:
            fprintf(saida, "Descrição;Valor\n");
            fprintf(saida, "Total de Jogos;%d\n", qtd_jogos);
            fprintf(saida, "Vitorias (%%);%.2f\n", p_vitorias);
            fprintf(saida, "Vitorias (Qtd);%d\n", resultados_jogos[0]);
            fprintf(saida, "Empates (%%);%.2f\n", p_empates);
            fprintf(saida, "Empates (Qtd);%d\n", resultados_jogos[1]);
            fprintf(saida, "Derrotas (%%);%.2f\n", p_derrotas);
            fprintf(saida, "Derrotas (Qtd);%d\n", resultados_jogos[2]);
            break;
        case FORMATO_HTML:
            fprintf(saida, "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><title>Aproveitamento Geral</title>");
            fprintf(saida, "<style>body{font-family:sans-serif;margin:2em} h2{color:#a303a3} table{border-collapse:collapse;width:50%%;margin-top:1em}");
            fprintf(saida, "th,td{border:1px solid #ddd;text-align:left;padding:8px} thead{background-color:#a303a3;color:white}</style>");
            fprintf(saida, "</head><body><h2>Relatório de Aproveitamento Geral do Time</h2>");
            fprintf(saida, "<h3>Total de jogos: %d</h3>", qtd_jogos);
            fprintf(saida, "<table><thead><tr><th>Métrica</th><th>Porcentagem</th><th>Quantidade</th></tr></thead><tbody>");
            fprintf(saida, "<tr><td>Vitórias</td><td>%.2f%%</td><td>%d</td></tr>", p_vitorias, resultados_jogos[0]);
            fprintf(saida, "<tr><td>Empates</td><td>%.2f%%</td><td>%d</td></tr>", p_empates, resultados_jogos[1]);
            fprintf(saida, "<tr><td>Derrotas</td><td>%.2f%%</td><td>%d</td></tr>", p_derrotas, resultados_jogos[2]);
            fprintf(saida, "</tbody></table></body></html>");
            break;
    }
    return 0;
}

int relatorio_adversarios(team_t * criciuma, FILE *saida, int formato){
    int encontradas = 2;
    int qtd_times_adversarios_distintos = 0;
    int achado;
    jogos_t *aux = criciuma->primeiro_jogo;

    typedef struct time_adversario {
        string nome;
        int qtd_jogos_contra;
        int vitorias;
        int empates;
        int derrotas;
    } times_adversarios_t;

    times_adversarios_t *times_adversarios = (times_adversarios_t*)malloc(sizeof(times_adversarios_t) * criciuma->qtd_jogos);
    if (!times_adversarios) {
        printf("Erro de alocação de memória!\n");
        return encontradas;
    }

    while(aux){
        achado = 0;
        for(int j = 0; j < qtd_times_adversarios_distintos; j++){
            if(strcmp(aux->dados.nome_adversario, times_adversarios[j].nome) == 0){
                achado = 1;
                break;
            }
        }
        if(achado == 0){
            strcpy(times_adversarios[qtd_times_adversarios_distintos].nome, aux->dados.nome_adversario);
            times_adversarios[qtd_times_adversarios_distintos].qtd_jogos_contra = 0;
            times_adversarios[qtd_times_adversarios_distintos].vitorias = 0;
            times_adversarios[qtd_times_adversarios_distintos].empates = 0;
            times_adversarios[qtd_times_adversarios_distintos].derrotas = 0;
            qtd_times_adversarios_distintos++;
        }
        aux = aux->proximo;
    }
    
    aux = criciuma->primeiro_jogo;
    while(aux){
        for(int j = 0; j < qtd_times_adversarios_distintos; j++){
            if(strcmp(aux->dados.nome_adversario, times_adversarios[j].nome) == 0){
                encontradas = 0;
                times_adversarios[j].qtd_jogos_contra++;
                if(aux->dados.resultado == 0) times_adversarios[j].vitorias++;
                if(aux->dados.resultado == 1) times_adversarios[j].empates++;
                if(aux->dados.resultado == 2) times_adversarios[j].derrotas++;
                break; 
            }
        }
        aux = aux->proximo;
    }

    switch(formato){
        case FORMATO_CSV:
            fprintf(saida, "Adversário;Total Jogos;Vitorias (%%);Vitorias (Qtd);Empates (%%);Empates (Qtd);Derrotas (%%);Derrotas (Qtd)\n");
        break;
        case FORMATO_TXT: 
            fprintf(saida, "--- Relatório de Desempenho por Adversário ---\n");
        break;
        case FORMATO_HTML:
            fprintf(saida, "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><title>Desempenho por Adversário</title>");
            fprintf(saida, "<style>body{font-family:sans-serif;margin:2em} h2{color:#a303a3} table{border-collapse:collapse;width:100%%;margin-top:1em}");
            fprintf(saida, "th,td{border:1px solid #ddd;text-align:left;padding:8px} thead{background-color:#a303a3;color:white}</style>");
            fprintf(saida, "</head><body><h2>Desempenho Contra Times Adversários</h2>");
            fprintf(saida, "<table><thead><tr><th>Adversário</th><th>Total de Jogos</th><th>Vitórias (%%)</th><th>Vitórias (Qtd)</th><th>Empates (%%)</th><th>Empates (Qtd)</th><th>Derrotas (%%)</th><th>Derrotas (Qtd)</th></tr></thead><tbody>");
        break;
    }

    for(int i = 0; i < qtd_times_adversarios_distintos; i++){
        float total_jogos = (float)times_adversarios[i].qtd_jogos_contra;
        float p_vitorias = (total_jogos > 0) ? (100 * times_adversarios[i].vitorias / total_jogos) : 0;
        float p_empates = (total_jogos > 0) ? (100 * times_adversarios[i].empates / total_jogos) : 0;
        float p_derrotas = (total_jogos > 0) ? (100 * times_adversarios[i].derrotas / total_jogos) : 0;
        
        switch(formato) {
            case FORMATO_TELA:
                definir_cor(COR_AZUL, -1, ESTILO_BOLD); fprintf(saida, "\n--- Desempenho contra: %s ---\n", times_adversarios[i].nome); resetar_cor();
                definir_cor(COR_CIANO, -1, ESTILO_NORMAL); fprintf(saida, "Total de jogos: %d\n", times_adversarios[i].qtd_jogos_contra); resetar_cor();
                fprintf(saida, "Vitórias: "); definir_cor(COR_VERDE, -1, ESTILO_NORMAL); fprintf(saida, "%.2f%% (%d)\n", p_vitorias, times_adversarios[i].vitorias); resetar_cor();
                fprintf(saida, "Empates: "); definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); fprintf(saida, "%.2f%% (%d)\n", p_empates, times_adversarios[i].empates); resetar_cor();
                fprintf(saida, "Derrotas: "); definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL); fprintf(saida, "%.2f%% (%d)\n", p_derrotas, times_adversarios[i].derrotas); resetar_cor();
                break;
            case FORMATO_TXT:
                fprintf(saida, "\nAdversário: %s\n", times_adversarios[i].nome);
                fprintf(saida, "---------------------------------\n");
                fprintf(saida, "Total de jogos: %d\n", times_adversarios[i].qtd_jogos_contra);
                fprintf(saida, "Vitórias: %.2f%% (%d)\n", p_vitorias, times_adversarios[i].vitorias);
                fprintf(saida, "Empates: %.2f%% (%d)\n", p_empates, times_adversarios[i].empates);
                fprintf(saida, "Derrotas: %.2f%% (%d)\n", p_derrotas, times_adversarios[i].derrotas);
                break;
            case FORMATO_CSV:
                fprintf(saida, "\"%s\";%d;%.2f;%d;%.2f;%d;%.2f;%d\n",
                    times_adversarios[i].nome, times_adversarios[i].qtd_jogos_contra,
                    p_vitorias, times_adversarios[i].vitorias,
                    p_empates, times_adversarios[i].empates,
                    p_derrotas, times_adversarios[i].derrotas);
                break;
            case FORMATO_HTML:
                fprintf(saida, "<tr><td>%s</td><td>%d</td><td>%.2f%%</td><td>%d</td><td>%.2f%%</td><td>%d</td><td>%.2f%%</td><td>%d</td></tr>",
                    times_adversarios[i].nome, times_adversarios[i].qtd_jogos_contra,
                    p_vitorias, times_adversarios[i].vitorias,
                    p_empates, times_adversarios[i].empates,
                    p_derrotas, times_adversarios[i].derrotas);
                break;
        }
    }

    if (formato == FORMATO_HTML) fprintf(saida, "</tbody></table></body></html>");

    free(times_adversarios);
    return encontradas;
}

int relatorio_valor(team_t * criciuma, FILE *saida, int formato){
    int valor_total_time = 0;
    int jogadoras_vendidas_cont = 0;
    int encontradas = 1;
    jogadoras_t *aux = criciuma->primeira_jogadora;

    while(aux){
        if(aux->dados.estado == 1){ 
            valor_total_time += aux->dados.valor_de_venda;
            jogadoras_vendidas_cont++;
            encontradas = 0;
        }
        aux = aux->proxima;
    }
    if(encontradas){
        switch (formato) {
             case FORMATO_TELA:
                definir_cor(COR_AMARELO, -1, ESTILO_NORMAL);
                fprintf(saida, "\nNenhuma jogadora foi vendida ainda.\n");
                resetar_cor();
                break;
            case FORMATO_TXT:
                fprintf(saida, "Nenhuma jogadora foi vendida ainda.\n");
                break;
            case FORMATO_CSV:
                fprintf(saida, "Descrição;Valor\n");
                fprintf(saida, "Nenhuma jogadora vendida;0\n");
                break;
            case FORMATO_HTML:
                fprintf(saida, "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><title>Valor Total do Time</title>");
                fprintf(saida, "<style>body{font-family:sans-serif;margin:2em} h2{color:#a303a3}</style>");
                fprintf(saida, "</head><body><h2>Relatório de Valor Total do Time</h2>");
                fprintf(saida, "<p>Nenhuma jogadora foi vendida ainda.</p>");
                fprintf(saida, "</body></html>");
                break;
        }
        return encontradas;
    }
    switch (formato) {
        case FORMATO_TELA:
            definir_cor(COR_VERDE, -1, ESTILO_BOLD);
            fprintf(saida, "\nValor total do time (soma dos valores de venda de %d jogadoras vendidas): %d mil R$\n", jogadoras_vendidas_cont, valor_total_time);
            resetar_cor();
            break;
        case FORMATO_TXT:
            fprintf(saida, "--- Relatório de Valor Total do Time ---\n\n");
            fprintf(saida, "Jogadoras vendidas: %d\n", jogadoras_vendidas_cont);
            fprintf(saida, "Valor total do time (soma dos valores de venda): %d mil R$\n", valor_total_time);
            break;
        case FORMATO_CSV:
            fprintf(saida, "Jogadoras Vendidas (Qtd);Valor Total Time (mil R$)\n");
            fprintf(saida, "%d;%d\n", jogadoras_vendidas_cont, valor_total_time);
            break;
        case FORMATO_HTML:
            fprintf(saida, "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><title>Valor Total do Time</title>");
            fprintf(saida, "<style>body{font-family:sans-serif;margin:2em} h2{color:#a303a3}</style>");
            fprintf(saida, "</head><body><h2>Relatório de Valor Total do Time</h2>");
            fprintf(saida, "<h3>Baseado na soma dos valores de venda de %d jogadoras vendidas.</h3>", jogadoras_vendidas_cont);
            fprintf(saida, "<p style=\"font-size:1.2em; font-weight:bold;\">Valor Total: %d mil R$</p>", valor_total_time);
            fprintf(saida, "</body></html>");
            break;
    }
    return encontradas;
}

int menu_buscas(void){
    int opc;
    definir_cor(COR_CIANO, -1, ESTILO_BOLD); printf("\nEscolha uma busca:\n\n"); resetar_cor();
    definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("--- Buscar Jogadoras ---\n"); resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[1] "); resetar_cor(); printf("Por nome da jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[2] "); resetar_cor(); printf("Por idade da jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[3] "); resetar_cor(); printf("Por altura da jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[4] "); resetar_cor(); printf("Por peso da jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[5] "); resetar_cor(); printf("Por posição da jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[6] "); resetar_cor(); printf("Por passe para venda da jogadora (mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[7] "); resetar_cor(); printf("Por valor de aquisição da jogadora (mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[8] "); resetar_cor(); printf("Por salário da jogadora (mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[9] "); resetar_cor(); printf("Por estado da jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[10] "); resetar_cor(); printf("Por valor de venda da jogadora (entre as vendidas, mil R$)\n");
    definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Buscar Jogos ---\n"); resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[11] "); resetar_cor(); printf("Por nome do time adversário\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[12] "); resetar_cor(); printf("Por data do jogo (dd/mm/yyyy)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[13] "); resetar_cor(); printf("Por local do jogo\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[14] "); resetar_cor(); printf("Por resultado do jogo (Vitória, Empate, Derrota)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[15] "); resetar_cor(); printf("Jogos em que uma jogadora específica participou (titulares)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[16] "); resetar_cor(); printf("Por quantidade de substituições no jogo\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("\n[0] "); resetar_cor(); printf("Voltar\n\n");
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("-> "); resetar_cor();
    scanf("%d",&opc);
    getchar(); 
    return opc;
}

int *busca_jogadora_nome(char * nome_busca,team_t * criciuma, int *qtd_ids){
    int *ids = (int *)malloc(sizeof(int));
    if(!ids) return NULL;
    jogadoras_t *aux = criciuma->primeira_jogadora;
    *ids=-1;
	*qtd_ids=0;
    for(int i=0; i<criciuma->qtd_jogadoras; i++){
        if(strstr(aux->dados.nome, nome_busca) != NULL){ //strstr para buscar substring
            if(*qtd_ids>0){
                ids=realloc(ids,sizeof(int)*(*qtd_ids+1));
                if (!ids) return NULL;
            }
            *(ids+(*qtd_ids)) = aux->dados.id;
			*qtd_ids+=1;
        }
        aux=aux->proxima;
    }    
    return ids;
}

void busca_i(char* frase, int i_busca[2]){
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("%s",frase); resetar_cor();
    scanf("%d", &i_busca[0]); 
    getchar();
    i_busca[1]=i_busca[0];    
    return;
}

void busca_f(char* frase, float f_busca[2]){
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("%s",frase); resetar_cor();
    scanf("%f", &f_busca[0]); 
    getchar();
    f_busca[1]=f_busca[0];    
    return;
}

void busca_string(char * frase,char * palavra){
	definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("%s",frase); resetar_cor();
    ler_string(palavra);
	return;
}

void busca_vetor_i(char * frase, string nomes[], int qtd_nomes,int i_busca[2]){
	definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("%s",frase); resetar_cor();
    for(int i=0; i<qtd_nomes; i++){
        definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[%d] ", i); resetar_cor(); printf("%s\n", nomes[i]);
    }
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("\n-> "); resetar_cor();
    scanf("%d", &i_busca[0]);
    while(i_busca[0] < 0 || i_busca[0] >= qtd_nomes){
        definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL); printf("Valor inválido.\n"); resetar_cor();
        definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("\n-> "); resetar_cor();
        scanf("%d", &i_busca[0]);
    }
    getchar();
    i_busca[1]=i_busca[0];  
    return;
}

int *busca_jogadora_posicao(int pos_busca, team_t *criciuma, int * qtd_ids){
    int *ids = (int *)malloc(sizeof(int));
    if(!ids) return NULL;
    jogadoras_t *aux = criciuma->primeira_jogadora;
    *ids=-1;
    *qtd_ids=0;
    for(int i=0; i<criciuma->qtd_jogadoras; i++){
        if(aux->dados.posicao == pos_busca){
            if(*qtd_ids>0){
                ids=realloc(ids,sizeof(int)*(*qtd_ids+1));
                if (!ids) return NULL;
            }
            *(ids+(*qtd_ids)) = aux->dados.id;
			*qtd_ids+=1;
		}
        aux=aux->proxima;
    }
    return ids;
}

int *busca_jogadora_estado(int estado_busca, team_t *criciuma, int * qtd_ids){
    int *ids = (int *)malloc(sizeof(int));
    if(!ids) return NULL;
    jogadoras_t *aux = criciuma->primeira_jogadora;
    *ids=-1;
	*qtd_ids=0;
    for(int i=0; i<criciuma->qtd_jogadoras; i++){
        if(aux->dados.estado == estado_busca){
            if(*qtd_ids>0){
                ids=realloc(ids,sizeof(int)*(*qtd_ids+1));
                if (!ids) return NULL;
            }
            *(ids+(*qtd_ids)) = aux->dados.id;
			*qtd_ids+=1;
		}
        aux=aux->proxima;
    }    
    return ids;
}

int* busca_jogo_nome_adversario(char *nome_busca, team_t *criciuma, int *qtd_ids){
    int* ids= (int*)malloc(sizeof(int));
    if(!ids) return NULL;
    jogos_t *aux =criciuma->primeiro_jogo;
    *ids= -1;
    *qtd_ids= 0;
    while(aux){
        if(strstr(aux->dados.nome_adversario, nome_busca)!= NULL){
            if(*qtd_ids >0){
                ids= realloc(ids, sizeof(int)*(*qtd_ids+1));
                if(!ids) return NULL;
            }
            *(ids + (*qtd_ids))= aux->dados.id;
            *qtd_ids+= 1;
        }
        aux= aux->proximo;
    }
    return ids;
}

int *busca_jogo_data(char*data_busca, team_t *criciuma, int* qtd_ids){
    int *ids =(int *)malloc(sizeof(int));
    if(!ids) return NULL;
    jogos_t* aux= criciuma->primeiro_jogo;
    *ids= -1;
    *qtd_ids= 0;
    while(aux){
        if(strstr(aux->dados.data, data_busca) !=NULL){
            if(*qtd_ids> 0){
                ids= realloc(ids, sizeof(int) * (*qtd_ids +1));
                if(!ids) return NULL;
            }
            *(ids+(*qtd_ids)) =aux->dados.id;
            *qtd_ids+=1;
        }
        aux=aux->proximo;
    }
    return ids;
}

int* busca_jogo_local(char *local_busca, team_t* criciuma, int *qtd_ids){
    int *ids= (int*)malloc(sizeof(int));
    if(!ids) return NULL;
    jogos_t *aux= criciuma->primeiro_jogo;
    *ids= -1;
    *qtd_ids= 0;
    while(aux){
        if(strstr(aux->dados.local, local_busca)!= NULL){
            if(*qtd_ids >0){
                ids= realloc(ids, sizeof(int)*(*qtd_ids + 1));
                if(!ids) return NULL;
            }
            *(ids + (*qtd_ids))= aux->dados.id;
            *qtd_ids+= 1;
        }
        aux= aux->proximo;
    }
    return ids;
}

int* busca_jogo_resultado(int res_busca, team_t *criciuma, int *qtd_ids){
    int* ids= (int*)malloc(sizeof(int));
    if(!ids) return NULL;
    jogos_t *aux =criciuma->primeiro_jogo;
    *ids= -1;
    *qtd_ids= 0;
    while(aux){
        if(aux->dados.resultado ==res_busca){
            if(*qtd_ids>0){
                ids= realloc(ids, sizeof(int)*(*qtd_ids+1));
                if (!ids) return NULL;
            }
            *(ids+(*qtd_ids))= aux->dados.id;
            *qtd_ids+=1;
        }
        aux =aux->proximo;
    }
    return ids;
}

int* busca_jogo_time(string jogadora_busca, team_t* criciuma, int *qtd_ids){
    int *ids =(int *)malloc(sizeof(int));
    if(!ids) return NULL;
    jogos_t *aux= criciuma->primeiro_jogo;
    *ids= -1;
    *qtd_ids= 0;
    while(aux){
        for(int j= 0; j< TAMANHO_TIME; j++){
            int jogadora_id =aux->dados.time[j];
            char* nome_da_jogadora= obter_nome_jogadora_por_id(jogadora_id, criciuma);

            if(nome_da_jogadora !=NULL && strstr(nome_da_jogadora, jogadora_busca)!= NULL){
                if(*qtd_ids >0){
                    ids= realloc(ids, sizeof(int) *(*qtd_ids +1));
                    if(!ids) return NULL;
                }
                *(ids +(*qtd_ids))= aux->dados.id;
                *qtd_ids+= 1;
                break; 
            }
        }
        aux =aux->proximo;
    }
    return ids;
}

int* busca_jogo_substituicoes_qtd(int subs_busca, team_t *criciuma, int* qtd_ids){
    int* ids= (int*)malloc(sizeof(int));
    if(!ids) return NULL;
    jogos_t *aux= criciuma->primeiro_jogo;
    *ids= -1;
    *qtd_ids= 0;
    while(aux){
        if(aux->dados.substituicoes_qtd== subs_busca){
            if(*qtd_ids >0){
                ids= realloc(ids, sizeof(int) *(*qtd_ids +1));
                if(!ids) return NULL;
            }
            *(ids+(*qtd_ids)) =aux->dados.id;
            *qtd_ids+= 1;
        }
        aux= aux->proximo;
    }
    return ids;
}

char *obter_nome_jogadora_por_id(int id, team_t *criciuma){
    jogadoras_t *aux_jogadora = criciuma->primeira_jogadora;
    for (int i = 0; i < criciuma->qtd_jogadoras; i++){
        if (aux_jogadora->dados.id == id){
            return aux_jogadora->dados.nome;
        }
        aux_jogadora = aux_jogadora->proxima;
    }

    return NULL;
}

/* Função de cores
Estilo: 0=Normal, 1=Negrito, 2=Dim, 4=Sublinhado, 5=Piscar, 7=Reverter, 8=Oculto
Cor Texto: 0=Preto, 1=Vermelho, 2=Verde, 3=Amarelo, 4=Azul, 5=Roxo, 6=Ciano, 7=Branco
Cor Fundo: 0=Preto, 1=Vermelho, 2=Verde, 3=Amarelo, 4=Azul, 5=Roxo, 6=Ciano, 7=Branco, -1=Nenhum*/
void definir_cor(int cor_texto, int cor_fundo, int estilo){
    printf("\033[");
	if(estilo!=-1){
		printf("%d",estilo); //estilo texto
	}
	if(cor_texto!=-1){
		printf(";3%d", cor_texto); // Cor do texto
	}
    if (cor_fundo != -1){
        printf(";4%d", cor_fundo);  // Cor do fundo
    }
    printf("m");    
    return;
}

void resetar_cor(){
    printf("\033[0m");
    return;
}

void ler_string(char *palavra){
    fgets(palavra, STRING_MAX, stdin);
    palavra[strcspn(palavra, "\n")]='\0';
    return;
}

void mostrar_jogadora(jogadoras_t * jogadora){
    definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Detalhes da Jogadora [%d] ---\n", jogadora->dados.id); resetar_cor();
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Nome: "); resetar_cor(); printf("%s\n",jogadora->dados.nome);
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Idade: "); resetar_cor(); printf("%d anos\n",jogadora->dados.idade);
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Altura: "); resetar_cor(); printf("%.2f m\n",jogadora->dados.altura);
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Peso: "); resetar_cor(); printf("%d kg\n",jogadora->dados.peso);
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Posição: "); resetar_cor(); printf("%s (%d)\n",nome_posicoes[jogadora->dados.posicao], jogadora->dados.posicao);
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Passe para venda: "); resetar_cor(); printf("%d mil R$\n",jogadora->dados.passe_para_venda);
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Valor de Aquisição: "); resetar_cor(); printf("%d mil R$\n",jogadora->dados.valor_de_aquisicao);
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Salário: "); resetar_cor(); printf("%d mil R$\n",jogadora->dados.salario);
    
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Estado: "); resetar_cor();
    switch(jogadora->dados.estado){
        case 0: definir_cor(COR_VERDE, -1, ESTILO_BOLD); break; // ativa
        case 1: definir_cor(COR_AMARELO, -1, ESTILO_BOLD); break; // vendida
        case 2: definir_cor(COR_VERMELHO, -1, ESTILO_BOLD); break; // em recuperação
        default: break;
    }
    printf("%s", nome_estado[jogadora->dados.estado]); resetar_cor();
    printf(" (%d)\n", jogadora->dados.estado);

	if(jogadora->dados.estado==1){ //se vendida
        definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Valor de venda: "); resetar_cor(); printf("%d mil R$\n",jogadora->dados.valor_de_venda);
	}
    definir_cor(COR_AZUL, -1, ESTILO_NORMAL); printf("-----------------------------\n"); resetar_cor();
	return;
}

void mostrar_jogo(jogos_t * jogo,team_t * criciuma){
    definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Detalhes do Jogo [%d] ---\n", jogo->dados.id); resetar_cor();
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Time adversário: "); resetar_cor(); printf("%s\n", jogo->dados.nome_adversario);
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Data: "); resetar_cor(); printf("%s\n", jogo->dados.data);
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Local: "); resetar_cor(); printf("%s\n", jogo->dados.local);
    
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Placar: "); resetar_cor(); 
    printf("Criciúma %d x %d %s\n", jogo->dados.goals[0], jogo->dados.goals[1], jogo->dados.nome_adversario);
    
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Resultado para Criciúma: "); resetar_cor();
    switch (jogo->dados.resultado){
        case 0: definir_cor(COR_VERDE, -1, ESTILO_BOLD); break;   // Vitória
        case 1: definir_cor(COR_AMARELO, -1, ESTILO_BOLD); break; // Empate
        case 2: definir_cor(COR_VERMELHO, -1, ESTILO_BOLD); break; // Derrota
        default: break;
    }
    printf("%s\n", nome_resultados[jogo->dados.resultado]); resetar_cor();
    
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Quantidade de substituições: "); resetar_cor(); printf("%d\n", jogo->dados.substituicoes_qtd);
    definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("Jogadoras titulares (pré-substituição):\n"); resetar_cor();
   
    for (int i = 0; i < TAMANHO_TIME; i++){
        int jogadora_id = jogo->dados.time[i];
		char *nome_jogadora = obter_nome_jogadora_por_id(jogadora_id, criciuma);
		printf("    %d. %s\n", i + 1, nome_jogadora);
    }
    
    definir_cor(COR_AZUL, -1, ESTILO_NORMAL); printf("--------------------------\n"); resetar_cor();
    return;
}

void salvar_bin_jogadoras(jogadoras_t * jogadoras){
    string caminho_arquivo;
    strcpy(caminho_arquivo, SAVE_DIR);
    strcat(caminho_arquivo, "dados_jogadoras.bin");
    FILE *fp = fopen(caminho_arquivo, "wb");
    if (!fp){
        printf("Erro ao tentar abrir o arquivo dados_jogadoras.bin\n");
        return;
    }

    while (jogadoras){
        fwrite(&jogadoras->dados, sizeof(dados_jogadora_t), 1, fp);
        jogadoras=jogadoras->proxima;
    }
    fclose(fp);
}

void salvar_bin_jogos(jogos_t * jogos){
    string caminho_arquivo;
    strcpy(caminho_arquivo, SAVE_DIR);
    strcat(caminho_arquivo, "dados_jogos.bin");
    FILE *fp = fopen(caminho_arquivo, "wb");
    if (!fp){
        printf("Erro ao tentar abrir o arquivo dados_jogos.bin\n");
        return;
    }
    while (jogos){
        fwrite(&jogos->dados, sizeof(dados_jogos_t), 1, fp);
        jogos=jogos->proximo;
    }
    fclose(fp);
}

void ler_bin_jogadoras(team_t * criciuma){
    string caminho_arquivo;
    strcpy(caminho_arquivo, SAVE_DIR);
    strcat(caminho_arquivo, "dados_jogadoras.bin");
    FILE *fp = fopen(caminho_arquivo, "rb");
    if(!fp){
        printf("Falha ao abrir o arquivo dados_jogadoras.bin!\n");
        return;
    }
    while(!feof(fp)){
        jogadoras_t *aux = (jogadoras_t*)malloc(sizeof(jogadoras_t));
        fread(&aux->dados, sizeof(dados_jogadora_t), 1, fp);
        if (!feof(fp)){ 
            aux->proxima = NULL;
            inserir_jogadora_inicio(aux, criciuma);
        }
        else {
            free(aux);
        }
    }

    fclose(fp);
}

void ler_bin_jogos(team_t * criciuma){
    string caminho_arquivo;
    strcpy(caminho_arquivo, SAVE_DIR);
    strcat(caminho_arquivo, "dados_jogos.bin");
    FILE *fp = fopen(caminho_arquivo, "rb");
    if(!fp){
        printf("Falha ao abrir o arquivo dados_jogos.bin!\n");
        return;
    }
    while(!feof(fp)){
        jogos_t *aux = (jogos_t*)malloc(sizeof(jogos_t));
        fread(&aux->dados, sizeof(dados_jogos_t), 1, fp);
        if (!feof(fp)){ 
            aux->proximo = NULL;
            inserir_jogo_inicio(aux, criciuma);
        }
        else {
            free(aux);
        }
    }
    fclose(fp);
}

void ordenar_jogos_id(team_t*criciuma){
    if(criciuma->primeiro_jogo==NULL || criciuma->primeiro_jogo->proximo==NULL) return;
    
    jogos_t * aux = criciuma->primeiro_jogo, *aux2, temp;

    while(aux){
        aux2=aux->proximo;
        while(aux2){
            if(aux->dados.id>aux2->dados.id){
                temp.dados=aux->dados;
                aux->dados=aux2->dados;
                aux2->dados=temp.dados;
            }
            aux2=aux2->proximo;
        }
        aux=aux->proximo;
    }
}

void ordenar_jogadoras_id(team_t * criciuma){
    if(criciuma->primeira_jogadora==NULL || criciuma->primeira_jogadora->proxima==NULL) return;
    
    jogadoras_t * aux = criciuma->primeira_jogadora, *aux2, temp;

    while(aux){
        aux2=aux->proxima;
        while(aux2){
            if(aux->dados.id>aux2->dados.id){
                temp.dados=aux->dados;
                aux->dados=aux2->dados;
                aux2->dados=temp.dados;
            }
            aux2=aux2->proxima;
        }
        aux=aux->proxima;
    }
}

int menu_exportar(void){
    int opc;
    definir_cor(COR_CIANO, -1, ESTILO_BOLD);
    printf("\nO que você deseja fazer agora?\n\n");
    resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[1] "); resetar_cor(); printf("Continuar (Voltar)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[2] "); resetar_cor(); printf("Exportar para arquivo .txt\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[3] "); resetar_cor(); printf("Exportar para arquivo .csv\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[4] "); resetar_cor(); printf("Exportar para arquivo .html\n");
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("\n-> "); resetar_cor();
    scanf("%d", &opc);
    getchar();
    return opc;
}

void obter_nome_arquivo(string nome_arquivo, const char*extensao){
    string nome_base;
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL);
    printf("Digite o nome do arquivo (sem extensão): ");
    resetar_cor();
    ler_string(nome_base);

    strcpy(nome_arquivo, EXPORT_DIR);
    strcat(nome_arquivo, nome_base);
    strcat(nome_arquivo, extensao);
}

void exportar_jogadoras_txt(FILE *arquivo, int *ids, jogadoras_t *primeira, int qtd_ids) {
    jogadoras_t *jogadora_atual = primeira;
    fprintf(arquivo, "--- Relatório de Jogadoras ---\n");

    while(jogadora_atual){
        int deve_exportar = 0;
        if(!ids) { deve_exportar = 1; } 
        else {
            for(int i=0; i < qtd_ids; i++){
                if(jogadora_atual->dados.id == *(ids + i)){ deve_exportar = 1; break; }
            }
        }
        if(deve_exportar){
            fprintf(arquivo, "\n--- Detalhes da Jogadora [%d] ---\n", jogadora_atual->dados.id);
            fprintf(arquivo, "Nome: %s\n", jogadora_atual->dados.nome);
            fprintf(arquivo, "Idade: %d anos\n", jogadora_atual->dados.idade);
            fprintf(arquivo, "Altura: %.2f m\n", jogadora_atual->dados.altura);
            fprintf(arquivo, "Peso: %d kg\n", jogadora_atual->dados.peso);
            fprintf(arquivo, "Posição: %s\n", nome_posicoes[jogadora_atual->dados.posicao]);
            fprintf(arquivo, "Passe para venda: %d mil R$\n", jogadora_atual->dados.passe_para_venda);
            fprintf(arquivo, "Valor de Aquisição: %d mil R$\n", jogadora_atual->dados.valor_de_aquisicao);
            fprintf(arquivo, "Salário: %d mil R$\n", jogadora_atual->dados.salario);
            fprintf(arquivo, "Estado: %s\n", nome_estado[jogadora_atual->dados.estado]);
            if(jogadora_atual->dados.estado == 1){
                fprintf(arquivo, "Valor de venda: %d mil R$\n", jogadora_atual->dados.valor_de_venda);
            }
        }
        jogadora_atual = jogadora_atual->proxima;
    }
}

void exportar_jogos_txt(FILE *arquivo, int *ids, team_t *criciuma, int qtd_ids) {
    jogos_t *jogo_atual = criciuma->primeiro_jogo;
    fprintf(arquivo, "--- Relatório de Jogos ---\n");
    
    while(jogo_atual){
        int deve_exportar = 0;
        if(!ids) { deve_exportar = 1; }
        else {
            for(int i = 0; i < qtd_ids; i++){
                if(jogo_atual->dados.id == *(ids + i)){ deve_exportar = 1; break; }
            }
        }
        if(deve_exportar){
            fprintf(arquivo, "\n--- Detalhes do Jogo [%d] ---\n", jogo_atual->dados.id);
            fprintf(arquivo, "Adversário: %s\n", jogo_atual->dados.nome_adversario);
            fprintf(arquivo, "Data: %s\n", jogo_atual->dados.data);
            fprintf(arquivo, "Local: %s\n", jogo_atual->dados.local);
            fprintf(arquivo, "Placar: Criciúma %d x %d %s\n", jogo_atual->dados.goals[0], jogo_atual->dados.goals[1], jogo_atual->dados.nome_adversario);
            fprintf(arquivo, "Resultado: %s\n", nome_resultados[jogo_atual->dados.resultado]);
            fprintf(arquivo, "Substituições: %d\n", jogo_atual->dados.substituicoes_qtd);
            fprintf(arquivo, "Jogadoras Titulares:\n");
            for (int i = 0; i < TAMANHO_TIME; i++){
                char *nome_jogadora = obter_nome_jogadora_por_id(jogo_atual->dados.time[i], criciuma);
                fprintf(arquivo, "    - %s\n", nome_jogadora ? nome_jogadora : "ID não encontrado");
            }
        }
        jogo_atual = jogo_atual->proximo;
    }
}

int exportar_jogadoras_csv(FILE *arquivo, int *ids, jogadoras_t*primeira, int qtd_ids){
    jogadoras_t *jogadora_atual=primeira;
    int encontradas=0;

    fprintf(arquivo, "ID;Nome;Idade;Altura;Peso;Posição;Passe para Venda (mil R$);Valor de Aquisição (mil R$);Salario (mil R$);Estado;Valor de Venda (mil R$)\n");

    while(jogadora_atual){
        int deve_exportar=0;
        if(!ids){
            deve_exportar=1;
        } else {
            for(int i=0; i<qtd_ids; i++){
                if(jogadora_atual->dados.id == *(ids + i)){
                    deve_exportar=1;
                    break;
                }
            }
        }
        if(deve_exportar){
            encontradas++;
            int valor_venda_final;
            if(jogadora_atual->dados.estado == 1){
                valor_venda_final=jogadora_atual->dados.valor_de_venda;
            } else {
                valor_venda_final=-1;
            }
            fprintf(arquivo, "%d;\"%s\";%d;%.2f;%d;\"%s\";%d;%d;%d;\"%s\";%d\n",
                    jogadora_atual->dados.id, jogadora_atual->dados.nome, jogadora_atual->dados.idade,
                    jogadora_atual->dados.altura, jogadora_atual->dados.peso, nome_posicoes[jogadora_atual->dados.posicao],
                    jogadora_atual->dados.passe_para_venda, jogadora_atual->dados.valor_de_aquisicao,
                    jogadora_atual->dados.salario, nome_estado[jogadora_atual->dados.estado], valor_venda_final);
        }
        jogadora_atual=jogadora_atual->proxima;
    }
    return encontradas;
}

int exportar_jogadoras_html(FILE *arquivo, int *ids, jogadoras_t* primeira, int qtd_ids){
    jogadoras_t*jogadora_atual = primeira;
    int encontradas=0;

    fprintf(arquivo, "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><title>Relatório de Jogadoras</title>");
    fprintf(arquivo, "<style>body{font-family:sans-serif} table{border-collapse:collapse;width:100%%}");
    fprintf(arquivo, "th,td{border:1px solid #ddd;text-align:left;padding:8px}");
    fprintf(arquivo, "thead{background-color:#a303a3;color:white}</style>");
    fprintf(arquivo, "</head><body><h1>Relatório de Jogadoras</h1><table><thead><tr>");
    fprintf(arquivo, "<th>ID</th><th>Nome</th><th>Idade</th><th>Altura (m)</th><th>Peso (kg)</th><th>Posição</th>");
    fprintf(arquivo, "<th>Passe (mil R$)</th><th>Aquisição (mil R$)</th><th>Salario (mil R$)</th><th>Estado</th><th>Venda (mil R$)</th>");
    fprintf(arquivo, "</tr></thead><tbody>");

    while(jogadora_atual){
        int deve_exportar=0;
        if(!ids){
            deve_exportar=1;
        } else {
            for(int i=0; i<qtd_ids; i++){
                if(jogadora_atual->dados.id == *(ids + i)){
                    deve_exportar=1;
                    break;
                }
            }
        }
        if(deve_exportar){
            encontradas++;
            int valor_venda_final;
            if(jogadora_atual->dados.estado == 1){
                valor_venda_final=jogadora_atual->dados.valor_de_venda;
            } else {
                valor_venda_final=-1;
            }
            fprintf(arquivo, "<tr><td>%d</td><td>%s</td><td>%d</td><td>%.2f</td><td>%d</td><td>%s</td><td>%d</td><td>%d</td><td>%d</td><td>%s</td><td>%d</td></tr>",
                    jogadora_atual->dados.id, jogadora_atual->dados.nome, jogadora_atual->dados.idade,
                    jogadora_atual->dados.altura, jogadora_atual->dados.peso, nome_posicoes[jogadora_atual->dados.posicao],
                    jogadora_atual->dados.passe_para_venda, jogadora_atual->dados.valor_de_aquisicao,
                    jogadora_atual->dados.salario, nome_estado[jogadora_atual->dados.estado], valor_venda_final);
        }
        jogadora_atual=jogadora_atual->proxima;
    }

    fprintf(arquivo, "</tbody></table></body></html>");
    return encontradas;
}

int exportar_jogos_csv(FILE *arquivo, int *ids, team_t*criciuma, int qtd_ids){
    jogos_t*jogo_atual=criciuma->primeiro_jogo;
    int encontradas=0;

    fprintf(arquivo, "ID;Adversário;Data;Local;Gols Criciúma;Gols Adversário;Resultado;Substituições;Time Titular\n");

    while(jogo_atual){
        int deve_exportar=0;
        if(!ids){
            deve_exportar=1;
        } else {
            for(int i=0; i<qtd_ids; i++){
                if(jogo_atual->dados.id == *(ids + i)){
                    deve_exportar=1;
                    break;
                }
            }
        }
        if(deve_exportar){
            encontradas++;
            fprintf(arquivo, "%d;\"%s\";\"%s\";\"%s\";%d;%d;\"%s\";%d;\"",
                    jogo_atual->dados.id, jogo_atual->dados.nome_adversario, jogo_atual->dados.data,
                    jogo_atual->dados.local, jogo_atual->dados.goals[0], jogo_atual->dados.goals[1],
                    nome_resultados[jogo_atual->dados.resultado], jogo_atual->dados.substituicoes_qtd);
            
            for(int i=0; i<TAMANHO_TIME; i++){
                fprintf(arquivo, "%s", obter_nome_jogadora_por_id(jogo_atual->dados.time[i], criciuma));
                if(i < TAMANHO_TIME - 1){
                    fprintf(arquivo, ", ");
                }
            }
            fprintf(arquivo, "\"\n");
        }
        jogo_atual=jogo_atual->proximo;
    }
    return encontradas;
}

int exportar_jogos_html(FILE *arquivo, int *ids, team_t*criciuma, int qtd_ids){
    jogos_t*jogo_atual=criciuma->primeiro_jogo;
    int encontradas=0;
    
    fprintf(arquivo, "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><title>Relatório de Jogos</title>");
    fprintf(arquivo, "<style>body{font-family:sans-serif} table{border-collapse:collapse;width:100%%}");
    fprintf(arquivo, "th,td{border:1px solid #ddd;text-align:left;padding:8px} thead{background-color:#a303a3;color:white} ul{padding-left:20px;margin:0}</style>");
    fprintf(arquivo, "</head><body><h1>Relatório de Jogos</h1><table><thead><tr>");
    fprintf(arquivo, "<th>ID</th><th>Adversário</th><th>Data</th><th>Local</th><th>Placar</th><th>Resultado</th><th>Substituições</th><th>Time Titular</th>");
    fprintf(arquivo, "</tr></thead><tbody>");

    while(jogo_atual){
        int deve_exportar=0;
        if(!ids){
            deve_exportar=1;
        } else {
            for(int i=0; i<qtd_ids; i++){
                if(jogo_atual->dados.id == *(ids + i)){
                    deve_exportar=1;
                    break;
                }
            }
        }
        if(deve_exportar){
            encontradas++;
            fprintf(arquivo, "<tr><td>%d</td><td>%s</td><td>%s</td><td>%s</td><td>Criciúma %d x %d %s</td><td>%s</td><td>%d</td><td><ul>",
                    jogo_atual->dados.id, jogo_atual->dados.nome_adversario, jogo_atual->dados.data,
                    jogo_atual->dados.local, jogo_atual->dados.goals[0], jogo_atual->dados.goals[1],
                    jogo_atual->dados.nome_adversario, nome_resultados[jogo_atual->dados.resultado],
                    jogo_atual->dados.substituicoes_qtd);
            
            for(int i=0; i<TAMANHO_TIME; i++){
                fprintf(arquivo, "%s, ", obter_nome_jogadora_por_id(jogo_atual->dados.time[i], criciuma));
            }
            fprintf(arquivo, "</ul></td></tr>");
        }
        jogo_atual=jogo_atual->proximo;
    }
    
    fprintf(arquivo, "</tbody></table></body></html>");
    return encontradas;
}

//separar em arquivos