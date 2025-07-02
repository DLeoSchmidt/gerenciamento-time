#include "../includes/utils.h"

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

void inserir_jogadora_inicio(jogadoras_t*nova_jogadora,team_t * criciuma){
    if(!nova_jogadora) return;

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
    if(!novo_jogo) return;

    if (criciuma->qtd_jogos==0){
        criciuma->primeiro_jogo = novo_jogo;
        criciuma->qtd_jogos++;
        return;
    }

    novo_jogo->proximo = criciuma->primeiro_jogo;
    criciuma->primeiro_jogo = novo_jogo;
    criciuma->qtd_jogos++;
}