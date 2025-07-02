#include "../includes/cadastros.h"

void gerar_cadastros(int opc, team_t *criciuma){
	jogadoras_t *jogadora_aux;
	jogos_t *jogo_aux;
    ordenar_jogadoras_id(criciuma);
    ordenar_jogos_id(criciuma);
    switch (opc){
        case 1:
            definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Cadastrando nova jogadora ---\n\n"); resetar_cor();
            jogadora_aux = cadastro_jogadora(criciuma->qtd_jogadoras);
			inserir_jogadora_inicio(jogadora_aux,criciuma);
            definir_cor(COR_VERDE, -1, ESTILO_BOLD); printf("\nCadastro de jogadora finalizado!!!\n"); resetar_cor();
        break;
		case 2:
            definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Alterando estado da jogadora ---\n\n"); resetar_cor();
            alterar_jogadora_por_nome(criciuma);
            definir_cor(COR_VERDE, -1, ESTILO_BOLD); printf("\nAlteração de estado da jogadora finalizado!!!\n"); resetar_cor();
		break;
        case 3:
            definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Cadastrando novo jogo ---\n\n"); resetar_cor();
            jogo_aux=cadastro_jogo(criciuma);
            inserir_jogo_inicio(jogo_aux,criciuma);
            definir_cor(COR_VERDE, -1, ESTILO_BOLD); printf("\nCadastro de jogo finalizado!!!\n"); resetar_cor();
        break;
        case 0:
            definir_cor(COR_CIANO, -1, ESTILO_NORMAL); printf("\nVoltando ao menu principal...\n\n"); resetar_cor();
        break;
        default:
            definir_cor(COR_VERMELHO, -1, ESTILO_BOLD); printf("\nOpção invalida!!!\n"); resetar_cor();
        break;
    }
    return;
}

jogadoras_t * cadastro_jogadora(int qtd_jogadoras){
	jogadoras_t *nova_jogadora = (jogadoras_t*)malloc(sizeof(jogadoras_t));
	
	if(!nova_jogadora) return NULL;
	
	nova_jogadora->dados.id= ++qtd_jogadoras;
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o nome da jogadora: "); resetar_cor();
	ler_string(nova_jogadora->dados.nome);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite a idade da jogadora: "); resetar_cor();
	scanf("%d",&nova_jogadora->dados.idade);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite a altura da jogadora (ex: 1.75): "); resetar_cor();
	scanf("%f",&nova_jogadora->dados.altura);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o peso da jogadora (kg): "); resetar_cor();
	scanf("%d",&nova_jogadora->dados.peso);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Escolha a posição da jogadora: \n"); resetar_cor();
	for(int i = 0; i<POSICOES_QTD;i++){
        definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[%d] ",i); resetar_cor(); printf("%s\n",nome_posicoes[i]);
	}
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("\n-> "); resetar_cor();
	scanf("%d",&nova_jogadora->dados.posicao);
    while(nova_jogadora->dados.posicao < 0 || nova_jogadora->dados.posicao >= POSICOES_QTD){
        definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL); printf("Posição inválida. Tente novamente: "); resetar_cor();
        scanf("%d",&nova_jogadora->dados.posicao);
    }

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o passe para venda da jogadora (em mil R$): "); resetar_cor();
	scanf("%d",&nova_jogadora->dados.passe_para_venda);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o valor de aquisição da jogadora (em mil R$): "); resetar_cor();
	scanf("%d",&nova_jogadora->dados.valor_de_aquisicao);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o salário da jogadora (em mil R$): "); resetar_cor();
	scanf("%d",&nova_jogadora->dados.salario);
    nova_jogadora->dados.estado=0;
	getchar(); 

	nova_jogadora->proxima=NULL;
	return nova_jogadora;
}

void alterar_jogadora_por_nome(team_t *criciuma){
    string aux;
    int *ids,temp_id,contido = 0,opcao,qtd_ids;
    jogadoras_t * jogadora = criciuma->primeira_jogadora;

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("\nDigite o nome da jogadora a ter o estado alterado: "); resetar_cor();
    ler_string(aux);
    ids = busca_jogadora_nome(aux, criciuma,&qtd_ids);
    while(*ids==-1){
        definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL); printf("Jogadora não encontrada. Tente novamente: "); resetar_cor();
        ler_string(aux);
        ids = busca_jogadora_nome(aux, criciuma,&qtd_ids);
    }
    if(qtd_ids==1){
        temp_id=*ids;
    } else {
        relatorio_jogadoras(ids, criciuma->primeira_jogadora,qtd_ids);
        definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Mais de uma jogadora encontrada, digite o Id da jogadora: "); resetar_cor();
        scanf("%d",&temp_id);
        getchar();
        while(!contido){
            for(int j = 0; j<qtd_ids; j++){
                if(temp_id==*(ids+j)){
                    contido=1;
                    break;
                }
            }
            if(contido) break;
            definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL); printf("Id não encontrado. Tente novamente: "); resetar_cor();
            scanf("%d",&temp_id);
            getchar();
        }
    }
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Escolha o estado da jogadora: \n"); resetar_cor();
	for(int i = 0; i<ESTADOS_QTD;i++){
		definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[%d] ",i); resetar_cor(); printf("%s\n",nome_estado[i]);
	}
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("\n-> "); resetar_cor();
	scanf("%d",&opcao);
    while(opcao < 0 || opcao >= ESTADOS_QTD){
        definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL); printf("Estado inválido. Tente novamente: "); resetar_cor();
        scanf("%d",&opcao);
    }
    while(jogadora){
        if(jogadora->dados.id==temp_id){
            switch(opcao){
                case 0:
                    jogadora->dados.estado=0;
                break;
                case 1:
                    jogadora->dados.estado=1;
                    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o valor de venda da jogadora: "); resetar_cor();
                    scanf("%d",&jogadora->dados.valor_de_venda);
                break;
                case 2:
                    jogadora->dados.estado=2;
                break;
            }
			break;
        }
		jogadora=jogadora->proxima;
    }
    getchar();
}

jogos_t* cadastro_jogo(team_t * criciuma){
    int qtd_ativas=0;
    jogadoras_t * jogadora_aux = criciuma->primeira_jogadora;
    while(jogadora_aux){
        if(jogadora_aux->dados.estado==0){
            qtd_ativas++;
        }
        jogadora_aux=jogadora_aux->proxima;
    }
	if(qtd_ativas<11){
		definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL); printf("Quantidade de jogadoras ativas insuficiente para escalar um jogo.\n"); resetar_cor();
        return NULL;
	}

	jogos_t *novo_jogo = (jogos_t*)malloc(sizeof(jogos_t));
	
	if(!novo_jogo) return NULL;
	
	novo_jogo->dados.id=criciuma->qtd_jogos+1;
	
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o nome do time adversário: "); resetar_cor();
	ler_string(novo_jogo->dados.nome_adversario);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite a data do jogo (formato dd/mm/yyyy, preencha os zeros): "); resetar_cor();
	ler_string(novo_jogo->dados.data);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite o local do jogo: "); resetar_cor();
	ler_string(novo_jogo->dados.local);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite a quantidade de gols do Criciúma: "); resetar_cor();
	scanf("%d",&novo_jogo->dados.goals[0]);

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite a quantidade de gols do time adversário: "); resetar_cor();
	scanf("%d",&novo_jogo->dados.goals[1]);

	if(novo_jogo->dados.goals[0] > novo_jogo->dados.goals[1]){
		novo_jogo->dados.resultado=0; // vitória
	} 
    else if(novo_jogo->dados.goals[0] == novo_jogo->dados.goals[1]){
		novo_jogo->dados.resultado=1; // empate
	} 
    else {
		novo_jogo->dados.resultado=2; // derrota
	}
	getchar(); 

    string aux;
    int *ids;
    int temp_id;
    int contido;
    int qtd_ids;
    int repetido;
    int vendida;
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL);
    printf("\nDigite o nome das %d jogadoras titulares do jogo: \n", TAMANHO_TIME);
    resetar_cor();

    for (int i =0; i<TAMANHO_TIME; i++){
        definir_cor(COR_VERDE, -1, ESTILO_NORMAL);
        printf("Titular %d: ", i + 1);
        resetar_cor();

        do {
            ler_string(aux);
            ids = busca_jogadora_nome(aux, criciuma, &qtd_ids);

            if (*ids !=-1){
                for (int j=qtd_ids-1; j>=0; j--){
                    vendida = 0;
                    jogadora_aux = criciuma->primeira_jogadora;
                    while (jogadora_aux){
                        if (jogadora_aux->dados.id == *(ids + j)){
                            if (jogadora_aux->dados.estado != 0){
                                vendida = 1;
                            }
                            break;
                        }
                        jogadora_aux = jogadora_aux->proxima;
                    }

                    repetido = 0;
                    for (int k = 0; k < i; k++){
                        if (*(novo_jogo->dados.time + k) == *(ids + j)){
                            repetido = 1;
                            break;
                        }
                    }

                    if (vendida || repetido){
                        for (int k = j; k < qtd_ids - 1; k++){
                            *(ids + k) = *(ids + (k + 1));
                        }
                        qtd_ids--;
                    }
                }
                if (qtd_ids > 0){
                    ids = realloc(ids, sizeof(int) * qtd_ids);
                } else {
                    free(ids);
                    ids = malloc(sizeof(int));
                    *ids = -1;
                }
            }

            if (*ids == -1){
                definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL);
                printf("Jogadora não encontrada (ou não está ativa/já está em uso). Tente novamente: ");
                resetar_cor();
            }

        } while (*ids == -1);

        if (qtd_ids == 1){
            *(novo_jogo->dados.time + i) = *ids;
        } else {
            relatorio_jogadoras(ids, criciuma->primeira_jogadora, qtd_ids);
            definir_cor(COR_VERDE, -1, ESTILO_NORMAL);
            printf("Mais de uma jogadora encontrada, digite o ID da jogadora: ");
            resetar_cor();
            contido = 0;
            do {
                scanf("%d", &temp_id);
                getchar();
                for (int j = 0; j < qtd_ids; j++){
                    if (temp_id == *(ids + j)){
                        contido = 1;
                        break;
                    }
                }
                if (contido) break;
                definir_cor(COR_VERMELHO, -1, ESTILO_NORMAL);
                printf("ID não encontrado na lista. Tente novamente: ");
                resetar_cor();
            } while (!contido);
            *(novo_jogo->dados.time + i) = temp_id;
        }
    }

    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("Digite a quantidade de substituições realizadas no jogo: "); resetar_cor();
	scanf("%d",&novo_jogo->dados.substituicoes_qtd);
	getchar(); 

	novo_jogo->proximo=NULL;

    free(ids);
	return novo_jogo;
}