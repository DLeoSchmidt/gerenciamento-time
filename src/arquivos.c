#include "../includes/arquivos.h"

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