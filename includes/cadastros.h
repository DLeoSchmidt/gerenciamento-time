#ifndef CADASTROS_H
#define CADASTROS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"
#include "buscas.h"
#include "relatorios.h"

void gerar_cadastros(int opc, team_t *criciuma);
jogadoras_t* cadastro_jogadora(int qtd_jogadoras);
void alterar_jogadora_por_nome(team_t * criciuma);
jogos_t *cadastro_jogo(team_t*criciuma);

#endif