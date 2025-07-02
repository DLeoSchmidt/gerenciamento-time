#ifndef BUSCAS_H
#define BUSCAS_H

#include "types.h"
#include <stdio.h>
#include "utils.h"
#include "menus.h"
#include "relatorios.h"

void gerar_buscas(int opc, team_t *criciuma);
void saida_de_dados_buscas(int encontradas, int opc, int opc_exp, int * ids, int qtd_ids, team_t * criciuma);
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

#endif