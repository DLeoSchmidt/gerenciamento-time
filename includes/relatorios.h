#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "types.h"
#include "utils.h"
#include <stdio.h>
#include "arquivos.h"
#include "menus.h"

void gerar_relatorios(int opc, team_t *criciuma);
void saida_de_dados_relatorios(int encontradas, int opc, int opc_exp, int * ids, int qtd_ids, team_t * criciuma);
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

#endif