#include "../includes/menus.h"

int menu_exportar(void){
    int opc;
    definir_cor(COR_CIANO, -1, ESTILO_BOLD);
    printf("\nO que você deseja fazer agora?\n\n");
    resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[0] "); resetar_cor(); printf("Continuar (Voltar)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[1] "); resetar_cor(); printf("Exportar para arquivo .txt\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[2] "); resetar_cor(); printf("Exportar para arquivo .csv\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[3] "); resetar_cor(); printf("Exportar para arquivo .html\n");
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("\n-> "); resetar_cor();
    scanf("%d", &opc);
    getchar();
    return opc;
}

int menu_principal(void){
    int opc;
    definir_cor(COR_CIANO, -1, ESTILO_BOLD); printf("Escolha uma área:\n\n"); resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[1] "); resetar_cor(); printf("Cadastros\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[2] "); resetar_cor(); printf("Relatórios\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[3] "); resetar_cor(); printf("Buscas\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[0] "); resetar_cor(); printf("Sair\n\n");
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("-> "); resetar_cor();
    scanf("%d",&opc);
    getchar(); 
    return opc;
}

int menu_cadastros(void){
    int opc;
    definir_cor(COR_CIANO, -1, ESTILO_BOLD);
    printf("\nEscolha um tipo de cadastro:\n\n");
    resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[1] "); resetar_cor(); printf("Cadastrar nova jogadora\n");
	definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[2] "); resetar_cor(); printf("Alterar estado de jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[3] "); resetar_cor(); printf("Cadastrar novo jogo\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[0] "); resetar_cor(); printf("Voltar\n\n");
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("-> "); resetar_cor();
    scanf("%d",&opc);
    getchar(); 
    return opc;
}

int menu_relatorios(void){
    int opc;
    definir_cor(COR_CIANO, -1, ESTILO_BOLD); printf("\nEscolha um relatório:\n\n"); resetar_cor();
    definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("--- Relatórios de Jogadoras ---\n"); resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[1] "); resetar_cor(); printf("Completo de todas as jogadoras\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[2] "); resetar_cor(); printf("Jogadoras por faixa de idade\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[3] "); resetar_cor(); printf("Jogadoras por faixa de altura\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[4] "); resetar_cor(); printf("Jogadoras por faixa de peso\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[5] "); resetar_cor(); printf("Jogadoras por faixa de passe para venda (mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[6] "); resetar_cor(); printf("Jogadoras por faixa de valor de aquisição (mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[7] "); resetar_cor(); printf("Jogadoras por faixa de salário (mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[8] "); resetar_cor(); printf("Jogadoras vendidas por faixa de valor de venda (mil R$)\n");
    definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Relatórios de Jogos ---\n"); resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[9] "); resetar_cor(); printf("Completo de todos os jogos\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[10] "); resetar_cor(); printf("Aproveitamento geral do time\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[11] "); resetar_cor(); printf("Desempenho contra times adversários\n");
    definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Relatórios Financeiros ---\n"); resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[12] "); resetar_cor(); printf("Valor total do time (baseado no valor de venda das jogadoras vendidas, em mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("\n[0] "); resetar_cor(); printf("Voltar\n\n");
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("-> "); resetar_cor();
    scanf("%d",&opc);
    getchar(); 
    return opc;
}

int menu_buscas(void){
    int opc;
    definir_cor(COR_CIANO, -1, ESTILO_BOLD); printf("\nEscolha uma busca:\n\n"); resetar_cor();
    definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("--- Buscar Jogadoras ---\n"); resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[1] "); resetar_cor(); printf("Por nome da jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[2] "); resetar_cor(); printf("Por idade da jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[3] "); resetar_cor(); printf("Por altura da jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[4] "); resetar_cor(); printf("Por peso da jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[5] "); resetar_cor(); printf("Por posição da jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[6] "); resetar_cor(); printf("Por passe para venda da jogadora (mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[7] "); resetar_cor(); printf("Por valor de aquisição da jogadora (mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[8] "); resetar_cor(); printf("Por salário da jogadora (mil R$)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[9] "); resetar_cor(); printf("Por estado da jogadora\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[10] "); resetar_cor(); printf("Por valor de venda da jogadora (entre as vendidas, mil R$)\n");
    definir_cor(COR_AZUL, -1, ESTILO_BOLD); printf("\n--- Buscar Jogos ---\n"); resetar_cor();
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[11] "); resetar_cor(); printf("Por nome do time adversário\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[12] "); resetar_cor(); printf("Por data do jogo (dd/mm/yyyy)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[13] "); resetar_cor(); printf("Por local do jogo\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[14] "); resetar_cor(); printf("Por resultado do jogo (Vitória, Empate, Derrota)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[15] "); resetar_cor(); printf("Jogos em que uma jogadora específica participou (titulares)\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("[16] "); resetar_cor(); printf("Por quantidade de substituições no jogo\n");
    definir_cor(COR_AMARELO, -1, ESTILO_NORMAL); printf("\n[0] "); resetar_cor(); printf("Voltar\n\n");
    definir_cor(COR_VERDE, -1, ESTILO_NORMAL); printf("-> "); resetar_cor();
    scanf("%d",&opc);
    getchar(); 
    return opc;
}