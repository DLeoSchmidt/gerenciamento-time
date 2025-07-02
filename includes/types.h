#ifndef TYPES_H
#define TYPES_H

#define STRING_MAX 100

typedef char string[STRING_MAX];

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

#endif