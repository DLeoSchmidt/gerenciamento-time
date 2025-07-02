#include "../includes/buscas.h"

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