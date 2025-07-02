#include "./includes/types.h"
#include "./includes/arquivos.h"
#include "./includes/utils.h"
#include "./includes/menus.h"
#include "./includes/cadastros.h"
#include "./includes/buscas.h"

int main(){
	team_t criciuma;
	criciuma.primeira_jogadora=NULL;
	criciuma.primeiro_jogo=NULL;
    criciuma.qtd_jogadoras=0;
	criciuma.qtd_jogos=0;

    ler_bin_jogadoras(&criciuma);
    ler_bin_jogos(&criciuma);
    ordenar_jogadoras_id(&criciuma);
    ordenar_jogos_id(&criciuma);
	
    definir_cor(COR_VERDE, -1, ESTILO_BOLD);
    printf("Olá, seja bem vindo(a)!\n\n");
    resetar_cor();
	
    int opcao,opcao2;

    do {
        opcao = menu_principal();

        switch(opcao){
            case 1: //cadastros
                do {
                    opcao2 = menu_cadastros();
                    gerar_cadastros(opcao2, &criciuma);
                } while (opcao2!=0);
            break;

            case 2: //relatórios
                do {
                    opcao2 = menu_relatorios();
                    gerar_relatorios(opcao2, &criciuma);
                } while (opcao2!=0);
            break;

            case 3: //buscas
                do {
                    opcao2 = menu_buscas();
                    gerar_buscas(opcao2, &criciuma);
                } while (opcao2!=0);
            break;

            case 0:
                definir_cor(COR_VERDE, -1, ESTILO_BOLD);
                printf("\nTchau!!!\n\n");
                resetar_cor();
            break;

            default:
                definir_cor(COR_VERMELHO, -1, ESTILO_BOLD);
                printf("\nOpção invalida!!!\n\n");
                resetar_cor();
            break;
        }
    } while (opcao!=0);

    jogadoras_t * aux_jogadora;
    jogos_t*aux_jogo;
    if(criciuma.primeira_jogadora){
        salvar_bin_jogadoras(criciuma.primeira_jogadora);
    }
    while(criciuma.primeira_jogadora){
        aux_jogadora=criciuma.primeira_jogadora;
        criciuma.primeira_jogadora=criciuma.primeira_jogadora->proxima;
        free(aux_jogadora);
    }
    if(criciuma.primeiro_jogo){
        salvar_bin_jogos(criciuma.primeiro_jogo);
        
    }
    while(criciuma.primeiro_jogo){
        aux_jogo=criciuma.primeiro_jogo;
        criciuma.primeiro_jogo=criciuma.primeiro_jogo->proximo;
        free(aux_jogo);
    }

    return 0;
}