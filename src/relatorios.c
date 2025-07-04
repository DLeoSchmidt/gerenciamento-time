#include "../includes/relatorios.h"

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
        while(!(opc_exp>=0 && opc_exp<=3)){
            definir_cor(COR_VERMELHO, -1, ESTILO_BOLD); printf("\nOpção invalida!!!\n"); resetar_cor();
            opc_exp = menu_exportar();
        }
        saida_de_dados_relatorios(encontradas,opc,opc_exp,ids,qtd_ids,criciuma);
    } while (opc_exp !=0);

    if(ids) free(ids);
    definir_cor(COR_ROXO,-1,ESTILO_NORMAL);
    printf("\n--- Fim do Relatório ---\n\n");
    resetar_cor();
}

void saida_de_dados_relatorios(int encontradas, int opc, int opc_exp, int * ids, int qtd_ids, team_t * criciuma){
    if (opc_exp == FORMATO_TELA) return;
    if(encontradas != 0){ 
        definir_cor(COR_AMARELO,-1,ESTILO_NORMAL); printf("\nNenhum item encontrado para exportar.\n"); resetar_cor();
        return;
    }
    
    string nome_arquivo;
    FILE *arquivo;
    const char *extensao;
    int itens_exportados = 0;

    switch(opc_exp){
        case FORMATO_TXT: extensao = ".txt"; break;
        case FORMATO_CSV: extensao = ".csv"; break;
        case FORMATO_HTML: extensao = ".html"; break;
        default: return;
    }

    obter_nome_arquivo(nome_arquivo, extensao);
    arquivo = fopen(nome_arquivo, "w");

    if(!arquivo){
        definir_cor(COR_VERMELHO,-1,ESTILO_BOLD); printf("\nErro ao criar o arquivo '%s'!\n", nome_arquivo); resetar_cor();
        return;
    }
    switch(opc){
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
            if(opc_exp == FORMATO_TXT) exportar_jogadoras_txt(arquivo, ids, criciuma->primeira_jogadora, qtd_ids);
            if(opc_exp == FORMATO_CSV) exportar_jogadoras_csv(arquivo, ids, criciuma->primeira_jogadora, qtd_ids);
            if(opc_exp == FORMATO_HTML) exportar_jogadoras_html(arquivo, ids, criciuma->primeira_jogadora, qtd_ids);
            itens_exportados = 1;
        break;
        case 9:
            if(opc_exp == FORMATO_TXT) exportar_jogos_txt(arquivo, ids, criciuma, qtd_ids);
            if(opc_exp == FORMATO_CSV) exportar_jogos_csv(arquivo, ids, criciuma, qtd_ids);
            if(opc_exp == FORMATO_HTML) exportar_jogos_html(arquivo, ids, criciuma, qtd_ids);
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

int relatorio_jogadoras(int * ids, jogadoras_t * jogadoras, int qtd_ids){
    int encontradas = 1;
    if(!ids){
        while(jogadoras){
            if(jogadoras->dados.estado!=3){
                mostrar_jogadora(jogadoras);
                encontradas = 0;
            }
            jogadoras=jogadoras->proxima;
        }
    } else {
        while(jogadoras){
            if(jogadoras->dados.estado!=3){
                for(int i =0;i<qtd_ids;i++){
                    if(jogadoras->dados.id==*(ids+i)){
                        mostrar_jogadora(jogadoras);
                        encontradas = 0;
                        break;
                    }
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