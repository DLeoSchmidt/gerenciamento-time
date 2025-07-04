#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#define FORMATO_TELA 0
#define FORMATO_TXT  1
#define FORMATO_CSV  2
#define FORMATO_HTML 3

#include "types.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void salvar_bin_jogadoras(jogadoras_t * jogadoras);
void salvar_bin_jogos(jogos_t * jogos);
void ler_bin_jogadoras(team_t * criciuma);
void ler_bin_jogos(team_t * criciuma);
void exportar_jogadoras_txt(FILE *arquivo, int *ids, jogadoras_t *primeira, int qtd_ids);
int exportar_jogadoras_csv(FILE *arquivo, int *ids, jogadoras_t *primeira, int qtd_ids);
int exportar_jogadoras_html(FILE *arquivo, int *ids, jogadoras_t *primeira, int qtd_ids);
void exportar_jogos_txt(FILE *arquivo, int *ids, team_t *criciuma, int qtd_ids);
int exportar_jogos_csv(FILE *arquivo, int *ids, team_t *criciuma, int qtd_ids);
int exportar_jogos_html(FILE *arquivo, int *ids, team_t *criciuma, int qtd_ids);

#endif