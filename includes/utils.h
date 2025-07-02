#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include "nomes.h"
#include <stdio.h>
#include <string.h>

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

/* Função de cores
Estilo: 0=Normal, 1=Negrito, 2=Dim, 4=Sublinhado, 5=Piscar, 7=Reverter, 8=Oculto
Cor Texto: 0=Preto, 1=Vermelho, 2=Verde, 3=Amarelo, 4=Azul, 5=Roxo, 6=Ciano, 7=Branco
Cor Fundo: 0=Preto, 1=Vermelho, 2=Verde, 3=Amarelo, 4=Azul, 5=Roxo, 6=Ciano, 7=Branco, -1=Nenhum*/
void definir_cor(int cor_texto, int cor_fundo, int estilo);
void resetar_cor();

void ler_string(char* palavra);
void mostrar_jogadora(jogadoras_t* jogadora);
void mostrar_jogo(jogos_t*jogo,team_t * criciuma);
char *obter_nome_jogadora_por_id(int id, team_t *criciuma);
void ordenar_jogos_id(team_t*criciuma);
void ordenar_jogadoras_id(team_t * criciuma);
void obter_nome_arquivo(string nome_arquivo, const char *extensao);
void inserir_jogadora_inicio(jogadoras_t*jogadora,team_t * criciuma);
void inserir_jogo_inicio(jogos_t*jogo,team_t * criciuma);

#endif