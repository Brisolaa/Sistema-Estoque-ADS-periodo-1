// Nome(s): Felipe Brisola, 
// Turma: Análise e Desenvolvimento de Sistemas 1º período Noturno
// Tema: Estoque Simples
// Descrição: Objetivo do sistema é permitir o gerenciamento básico de produtos,
//            simulando operações reais de estoque como cadastro, entrada e saída de mercadorias,
//            consultas e relatórios.
// Funcionalidade extra: Remover produto.

#include <stdio.h>
#include <windows.h> // ****** AJUSTAR O DELAY PARA FUNÇÃO SLEEP() DO WINDOWS, MELHORANDO A PERFORMANCE E SIMULAÇÃO DE CARREGAMENTO. ******
#include <string.h> // Utilizada para manipulação de texto com strcpy. 
#include <time.h>  // Utilizada para criar delay no sistema usando.
#define MAX 10 // Implementação de memória dinâmica aumentaria a complexidade e probabilidade de bugs.

    void verde() {
        printf("\033[1;32m");
    }
    
    void vermelho() {
        printf("\033[1;31m");
    }
    
    void amarelo() {
        printf("\033[1;33m");
    }
    
    void magenta() {
        printf("\033[1;35m");
    }
    
    void resetarCor() {
        printf("\033[0m");
    }
    
    // Como o terminal online não aceita sleep() do Windows.
    void delay(int milissegundos){  // Essa função foi criada para pausas controladas nas animações do terminal.
        clock_t inicio = clock(); // Registra tempo atual do processador.
        while (clock() < inicio + milissegundos * CLOCKS_PER_SEC / 3000);
    }
    
    void barraCarregamento(){
        amarelo();
        printf("Encerrando sistema...\n\n");
        resetarCor();
        printf("[");
        for(int i = 0; i < 20; i++){
            printf("■");
            fflush(stdout); //Força o terminal a mostrar imediatamente.
            delay(120);
        }
        printf("] 100%%\n");
        delay(500);
        printf("\n");
        printf("Finalizando processos...\n");
        fflush(stdout);
        delay(500);
        printf("Liberando memoria...\n");
        fflush(stdout);
        delay(500);
        printf("Encerrando sessao...\n");
        fflush(stdout);
        delay(500);
        verde();
        printf("\nSistema encerrado com sucesso!\n");
        resetarCor();
        printf("\n");
        printf("\n");
    }

    void limparTela() {
        for (int i = 0; i < 10; i++) {
            printf("\n");
        }
    }
    
    void pausa(){ // Pausar o sistema até o usuário apertar Enter.
        amarelo();
        printf("\nPressione Enter para voltar ao menu...");
        resetarCor();
        setbuf(stdin, NULL); // Desativa o buffer de input, evita problemas com lixo.
        getchar(); // Aguarda o Enter.
    }

    void carregarDadosIniciais(int idprod[], char nomeprod[][50], int qtdprod[], float precoprod[], int *total) {
        idprod[0] = 1; strcpy(nomeprod[0], "Arroz"); qtdprod[0] = 100; precoprod[0] = 15.90;
        idprod[1] = 2; strcpy(nomeprod[1], "Feijao"); qtdprod[1] = 80; precoprod[1] = 9.99;
        idprod[2] = 3; strcpy(nomeprod[2], "Macarrao"); qtdprod[2] = 250; precoprod[2] = 4.89;
        idprod[3] = 4; strcpy(nomeprod[3], "Lentilha"); qtdprod[3] = 130; precoprod[3] = 10;
        *total = 4;
    }
    
    int buscarIndicePorId(int idprod[], int total, int id){ 
        for (int i = 0; i < total; i++){
            if (idprod[i] == id){
                return i; // Retorna o índice do vetor.
            }
        }
        return -1; // Não encontrado.
    }
    
    void cadastrarProduto(int idprod[], char nomeprod[][50], int qtdprod[], float precoprod[], int *total){
       if (*total >= MAX){
           printf("\n\n.......................................................\n\n");
           vermelho();
           printf("Limite de produtos atingido! (10)\n");
           resetarCor();
           return;
       }
        printf("\n\n\n");
        printf(" ██████╗ █████╗ ██████╗  █████╗ ███████╗████████╗██████╗  █████╗ ██████╗ \n");
        printf("██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔════╝╚══██╔══╝██╔══██╗██╔══██╗██╔══██╗\n");
        printf("██║     ███████║██║  ██║███████║███████╗   ██║   ██████╔╝███████║██████╔╝\n");
        printf("██║     ██╔══██║██║  ██║██╔══██║╚════██║   ██║   ██╔══██╗██╔══██║██╔══██╗\n");
        printf("╚██████╗██║  ██║██████╔╝██║  ██║███████║   ██║   ██║  ██║██║  ██║██║  ██║\n");
        printf(" ╚═════╝╚═╝  ╚═╝╚═════╝ ╚═╝  ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝\n");
        printf("██████╗ ██████╗  ██████╗ ██████╗ ██╗   ██╗████████╗ ██████╗ \n");
        printf("██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██║   ██║╚══██╔══╝██╔═══██╗\n");
        printf("██████╔╝██████╔╝██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
        printf("██╔═══╝ ██╔══██╗██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
        printf("██║     ██║  ██║╚██████╔╝██████╔╝╚██████╔╝   ██║   ╚██████╔╝\n");
        printf("╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝    ╚═╝    ╚═════╝ \n");
        printf("\n\n");
        printf("Digite o nome do produto: ");
        resetarCor();
        scanf(" %49[^\n]", nomeprod[*total]);
        printf("Digite a quantidade: ");
        scanf("%d", &qtdprod[*total]);
        if (qtdprod[*total] <= 0){  // Validação
            vermelho();
            printf("\n\nDigite uma quantidade válida! (números positivos)\n");
            resetarCor();
            return;
        }
        printf("Digite o preço: R$");
        scanf("%f", &precoprod[*total]);
        if (precoprod[*total] <= 0){ // Validação
            vermelho();
            printf("Digite um preço válido! (valores positivos)\n");
            resetarCor();
            return;
        }
        idprod[*total] = (*total + 1);  // Id gerado somente pós validação.
        verde();
        printf("\n\nID:[%.2d] Produto [ %s ] cadastrado com sucesso!",idprod[*total], nomeprod[*total]);
        resetarCor();
        (*total)++;
        printf("\nTotal de produtos cadastrados: %d\n\n", *total);  
    }
    
    void listarProduto(int idprod[], char nomeprod[][50], int qtdprod[], float precoprod[], int total){
        printf("\n\n\n");
        printf("██╗     ██╗███████╗████████╗ █████╗ ██████╗ \n");
        printf("██║     ██║██╔════╝╚══██╔══╝██╔══██╗██╔══██╗\n");
        printf("██║     ██║███████╗   ██║   ███████║██████╔╝\n");
        printf("██║     ██║╚════██║   ██║   ██╔══██║██╔══██╗\n");
        printf("███████╗██║███████║   ██║   ██║  ██║██║  ██║\n");
        printf("╚══════╝╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝\n");
        printf("██████╗ ██████╗  ██████╗ ██████╗ ██╗   ██╗████████╗ ██████╗ \n");
        printf("██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██║   ██║╚══██╔══╝██╔═══██╗\n");
        printf("██████╔╝██████╔╝██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
        printf("██╔═══╝ ██╔══██╗██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
        printf("██║     ██║  ██║╚██████╔╝██████╔╝╚██████╔╝   ██║   ╚██████╔╝\n");
        printf("╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝    ╚═╝    ╚═════╝ \n");
        printf("\n\n");
        if (total == 0) {
        amarelo();
        printf(" [!] Nenhum produto cadastrado.\n");
        resetarCor();
        return;
    }
        magenta();
        printf(" ┌─────┬──────────────────────┬───────┬─────────────┐\n");
        printf(" │ ID  │ NOME                 │ QTD   │ PRECO       │\n");
        printf(" ├─────┼──────────────────────┼───────┼─────────────┤\n");
        for (int i = 0; i < total; i++){
            printf(" │ %-3d │ %-20s │ %-5d │ R$%9.2f │\n", idprod[i], nomeprod[i], qtdprod[i], precoprod[i]);
        }
        printf(" └─────┴──────────────────────┴───────┴─────────────┘\n");
        resetarCor();
    }
    
    void entradaProduto(int idprod[], char nomeprod[][50], int qtdprod[], int total){
        printf("\n\n\n");
        printf("███████╗███╗   ██╗████████╗██████╗  █████╗ ██████╗  █████╗ \n");
        printf("██╔════╝████╗  ██║╚══██╔══╝██╔══██╗██╔══██╗██╔══██╗██╔══██╗\n");
        printf("█████╗  ██╔██╗ ██║   ██║   ██████╔╝███████║██║  ██║███████║\n");
        printf("██╔══╝  ██║╚██╗██║   ██║   ██╔══██╗██╔══██║██║  ██║██╔══██║\n");
        printf("███████╗██║ ╚████║   ██║   ██║  ██║██║  ██║██████╔╝██║  ██║\n");
        printf("╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝ ╚═╝  ╚═╝\n");
        printf("██████╗ ██████╗  ██████╗ ██████╗ ██╗   ██╗████████╗ ██████╗ \n");
        printf("██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██║   ██║╚══██╔══╝██╔═══██╗\n");
        printf("██████╔╝██████╔╝██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
        printf("██╔═══╝ ██╔══██╗██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
        printf("██║     ██║  ██║╚██████╔╝██████╔╝╚██████╔╝   ██║   ╚██████╔╝\n");
        printf("╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝    ╚═╝    ╚═════╝ \n");
        printf("\n\n");
        printf("\nQual opção que gostaria de ADICIONAR quantidade? \n\n");
        printf("----------------------------------------\n");
        printf("ID     | NOME                 | QTD          \n");
        printf("----------------------------------------\n");
        
        int idadd = 0;
        int quantidadeadd = 0;
        
            for (int i = 0; i < total; i++){
                printf("Id: %-3d  %-20s   %-5dun. \n", idprod[i], nomeprod[i], qtdprod[i]);
                }
                printf("----------------------------------------\n");
                printf("\nDigite o Id do produto: ");
                scanf(" %d", &idadd);
                
                if (idadd <= 0 || idadd > total){
                    vermelho();
                    printf("\nID inválido!\n");
                    resetarCor();
                        return; 
                    }
                    
                int idx = buscarIndicePorId(idprod, total, idadd);
                if (idx == -1){
                    vermelho();
                    printf("\nProduto não encontrado!\n");
                    resetarCor();
                    return;
                }

                printf("\nDigite a quantidade de unidades que gostaria de ADICIONAR: ");
                scanf(" %d", &quantidadeadd);
                if (quantidadeadd <= 0){ // Validação
                    vermelho();
                    printf("\nQuantidade inválida!\n");
                    resetarCor();
                        return;
                    }
                    qtdprod[idx] += quantidadeadd;
                    verde();
                    printf("\n ┌──────────────────────────────────────────┐");
                    printf("\n │      ENTRADA DE ESTOQUE REALIZADA        │");
                    printf("\n ├──────────────────────────────────────────┤");
                    printf("\n │ Produto: %-31s │", nomeprod[idx]);
                    printf("\n │ Quantidade Adicionada: %-17d │", quantidadeadd);
                    printf("\n │ Estoque Atualizado: %-20d │", qtdprod[idx]);
                    printf("\n └──────────────────────────────────────────┘\n");
                    printf("\n\n");
                    resetarCor();
                    return;
                
    }
    
    void saidaProduto(int idprod[], char nomeprod[][50], int qtdprod[], int total){
        printf("\n\n\n");
        printf("███████╗ █████╗ ██╗██████╗  █████╗ \n");
        printf("██╔════╝██╔══██╗██║██╔══██╗██╔══██╗\n");
        printf("███████╗███████║██║██║  ██║███████║\n");
        printf("╚════██║██╔══██║██║██║  ██║██╔══██║\n");
        printf("███████║██║  ██║██║██████╔╝██║  ██║\n");
        printf("╚══════╝╚═╝  ╚═╝╚═╝╚═════╝ ╚═╝  ╚═╝\n");
        printf("██████╗ ██████╗  ██████╗ ██████╗ ██╗   ██╗████████╗ ██████╗ \n");
        printf("██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██║   ██║╚══██╔══╝██╔═══██╗\n");
        printf("██████╔╝██████╔╝██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
        printf("██╔═══╝ ██╔══██╗██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
        printf("██║     ██║  ██║╚██████╔╝██████╔╝╚██████╔╝   ██║   ╚██████╔╝\n");
        printf("╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝    ╚═╝    ╚═════╝ \n");
        printf("\n\n");
        printf("\nQual opção que gostaria de RETIRAR quantidade? \n\n");
        printf("----------------------------------------\n");
        printf("ID     | NOME                 | QTD          \n");
        printf("----------------------------------------\n");
        
        int idsub = 0;
        int quantidadesub = 0;
               
            for (int i = 0; i < total; i++){
                printf("Id: %-3d  %-20s   %-5dun. \n", idprod[i], nomeprod[i], qtdprod[i]);
                }
                printf("----------------------------------------\n");
                printf("\nDigite o Id do produto: ");
                scanf(" %d", &idsub);
                
                if (idsub <= 0 || idsub > total){
                    vermelho();
                    printf("\nID inválido!\n");
                    resetarCor();
                    return; 
                    }
                int idx = buscarIndicePorId(idprod, total, idsub);
                if (idx == -1){
                    vermelho();
                    printf("\nProduto não encontrado!");
                    resetarCor();
                    return;
                }
                
                printf("\nDigite a quantidade de unidades que gostaria de RETIRAR: ");
                scanf(" %d", &quantidadesub);
                if (quantidadesub <= 0){  // Validação
                    vermelho();
                    printf("\nQuantidade inválida!\n");
                    resetarCor();
                    return;
                    }
                if (quantidadesub > qtdprod[idx]){ // Essa validação impede que o estoque fique negativo.
                    vermelho();
                    printf("\nQuantidade inválida, o produto seria negativado!\n");
                    resetarCor();
                    return;
                }
                    qtdprod[idx] -= quantidadesub;
                    verde();
                    printf("\n ┌──────────────────────────────────────────┐");
                    printf("\n │       SAÍDA DE ESTOQUE REALIZADA         │");
                    printf("\n ├──────────────────────────────────────────┤");
                    printf("\n │ Produto: %-31s │", nomeprod[idx]);
                    printf("\n │ Quantidade Retirada: %-19d │", quantidadesub);
                    printf("\n │ Estoque Atualizado: %-20d │", qtdprod[idx]);
                    printf("\n └──────────────────────────────────────────┘\n");
                    printf("\n\n");
                    resetarCor();
                    return;
    }
    
    void buscaProduto(int idprod[], char nomeprod[][50], int qtdprod[], float precoprod[], int total){
        printf("\n\n\n");
        printf("██████╗ ██╗   ██╗███████╗ ██████╗ █████╗ \n");
        printf("██╔══██╗██║   ██║██╔════╝██╔════╝██╔══██╗\n");
        printf("██████╔╝██║   ██║███████╗██║     ███████║\n");
        printf("██╔══██╗██║   ██║╚════██║██║     ██╔══██║\n");
        printf("██████╔╝╚██████╔╝███████║╚██████╗██║  ██║\n");
        printf("╚═════╝  ╚═════╝ ╚══════╝ ╚═════╝╚═╝  ╚═╝\n");
        printf("██████╗  ██████╗ ██████╗     ██╗██████╗ \n");
        printf("██╔══██╗██╔═══██╗██╔══██╗    ██║██╔══██╗\n");
        printf("██████╔╝██║   ██║██████╔╝    ██║██║  ██║\n");
        printf("██╔═══╝ ██║   ██║██╔══██╗    ██║██║  ██║\n");
        printf("██║     ╚██████╔╝██║  ██║    ██║██████╔╝\n");
        printf("╚═╝      ╚═════╝ ╚═╝  ╚═╝    ╚═╝╚═════╝ \n");
        printf("\n\n");
        
        int idbusca;

        printf("Digite a Id para buscar o produto: ");
        scanf("%d", &idbusca);
        
        if (idbusca <= 0 || idbusca > total){
            vermelho();
            printf("\nID inválido!\n");
            resetarCor();
            return; 
        }
        
        int idx = buscarIndicePorId(idprod, total, idbusca);
        if (idx == -1){
            vermelho();
            printf("\nProduto não encontrado!");
            resetarCor();
            return;
        }
        
        float valortotal = precoprod[idx] * qtdprod[idx];
        
        printf("\n ┌──────────────────────────────────────────┐");
        printf("\n │       RESULTADO DA BUSCA POR ID          │");
        printf("\n ├──────────────────────────────────────────┤");
        printf("\n │ ID: %-36d │", idprod[idx]);
        printf("\n │ Nome: %-34s │", nomeprod[idx]);
        printf("\n │ Quantidade: %-28d │", qtdprod[idx]);
        printf("\n │ Preço Unitário: R$ %-21.2f │", precoprod[idx]);
        printf("\n ├──────────────────────────────────────────┤");
        printf("\n │ VALOR TOTAL EM ESTOQUE: R$ %-13.2f │", valortotal);
        printf("\n └──────────────────────────────────────────┘\n\n");
        return; 
    }
    
    void relatorioProduto(char nomeprod[][50], int qtdprod[], float precoprod[], int total){
        printf("\n\n\n");
        printf("██████╗ ███████╗██╗      █████╗ ████████╗ ██████╗ ██████╗ ██╗ ██████╗ ███████╗\n");
        printf("██╔══██╗██╔════╝██║     ██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗██║██╔═══██╗██╔════╝\n");
        printf("██████╔╝█████╗  ██║     ███████║   ██║   ██║   ██║██████╔╝██║██║   ██║███████╗\n");
        printf("██╔══██╗██╔══╝  ██║     ██╔══██║   ██║   ██║   ██║██╔══██╗██║██║   ██║╚════██║\n");
        printf("██║  ██║███████╗███████╗██║  ██║   ██║   ╚██████╔╝██║  ██║██║╚██████╔╝███████║\n");
        printf("╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝ ╚═════╝ ╚══════╝\n");
        printf("\n\n");
        
        float valortotalprodutos = 0;
        int maior = 0;
        int menor = 0;
        
        if (total == 0){
            vermelho();
            printf("Nenhum produto cadastrado.\n");
            resetarCor();
            return;
        }
        for (int i = 0; i < total; i++){
            valortotalprodutos += (qtdprod[i] * precoprod [i]);
        }
        for (int i = 1; i < total; i++){
            if (qtdprod[i] > qtdprod[maior]){
                maior = i;
            }
            if (qtdprod[i] < qtdprod[menor]){
                menor = i;
            }
        }
            
        printf("\n ┌────────────────────────────────────────────────────────────┐");
        printf("\n │ RESUMO GERAL DO ESTOQUE                                    │");
        printf("\n ├────────────────────────────────────────────────────────────┤");
        printf("\n │ Valor Total em Mercadorias: R$ %-27.2f │", valortotalprodutos);
        printf("\n │                                                            │");
        printf("\n │ Produto em MAIOR quantidade: %-29s │", nomeprod[maior]);
        printf("\n │ Volume: %-50d │", qtdprod[maior]);
        printf("\n │                                                            │");
        printf("\n │ Produto em MENOR quantidade: %-29s │", nomeprod[menor]);
        printf("\n │ Volume: %-50d │", qtdprod[menor]);
        printf("\n └────────────────────────────────────────────────────────────┘\n\n");
    }
    
    void removerProduto(int idprod[], char nomeprod[][50], int qtdprod[], float precoprod[], int *total) {
        printf("\n\n\n");
        printf("██████╗ ███████╗███╗   ███╗ ██████╗ ██╗   ██╗███████╗██████╗ \n");
        printf("██╔══██╗██╔════╝████╗ ████║██╔═══██╗██║   ██║██╔════╝██╔══██╗\n");
        printf("██████╔╝█████╗  ██╔████╔██║██║   ██║██║   ██║█████╗  ██████╔╝\n");
        printf("██╔══██╗██╔══╝  ██║╚██╔╝██║██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗\n");
        printf("██║  ██║███████╗██║ ╚═╝ ██║╚██████╔╝ ╚████╔╝ ███████╗██║  ██║\n");
        printf("╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝\n");
        printf("██████╗ ██████╗  ██████╗ ██████╗ ██╗   ██╗████████╗ ██████╗ \n");
        printf("██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██║   ██║╚══██╔══╝██╔═══██╗\n");
        printf("██████╔╝██████╔╝██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
        printf("██╔═══╝ ██╔══██╗██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
        printf("██║     ██║  ██║╚██████╔╝██████╔╝╚██████╔╝   ██║   ╚██████╔╝\n");
        printf("╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝    ╚═╝    ╚═════╝ \n");
        printf("\n\n");
        printf("\nQual opção que gostaria de REMOVER do sistema? \n\n");
        printf("----------------------------------------\n");
        printf("ID     | NOME                 | QTD          \n");
        printf("----------------------------------------\n");
        
        int iddel = 0;
               
            for (int i = 0; i < *total; i++){
                printf("Id: %-3d  %-20s   %-5dun. \n", idprod[i], nomeprod[i], qtdprod[i]);
                }
                printf("----------------------------------------\n");
                printf("\nDigite o Id do produto: ");
                scanf(" %d", &iddel);
                
                if (iddel <= 0 || iddel > *total){
                    vermelho();
                    printf("\nID inválido!\n");
                    resetarCor();
                    return; 
                    }
                    
                int idx = buscarIndicePorId(idprod, *total, iddel);
                if (idx == -1) {
                    vermelho();
                    printf("\nProduto não encontrado!");
                    resetarCor();
                    return;
                }
                
                char nomeRemovido[50];
                strcpy(nomeRemovido, nomeprod[idx]);
                
                for (int i = idx; i < *total -1; i++) {
                    idprod[i] = idprod[i + 1];
                    qtdprod[i] = qtdprod[i + 1];
                    precoprod[i] = precoprod [i + 1];
                    strcpy(nomeprod[i], nomeprod[i + 1]);
                }
                (*total)--;
                
                for (int i = 0; i < *total; i++) {
                 idprod[i] = i + 1;
                }
                    verde();
                    printf("\n ┌──────────────────────────────────────────┐");
                    printf("\n │      REMOÇAO DE ESTOQUE REALIZADA        │");
                    printf("\n ├──────────────────────────────────────────┤");
                    printf("\n │ Produto: %-31s │", nomeRemovido) ;
                    printf("\n └──────────────────────────────────────────┘\n");
                    printf("\n\n");
                    resetarCor();
                    return;
    }
    
    int main(){
        SetConsoleOutputCP(65001); // Configura o console para UTF-8, garantindo a exibição correta dos caracteres acentuados.
        SetConsoleCP(65001); // Configura o console para UTF-8, garantindo a leitura correta dos caracteres acentuados. 

        int idprod [MAX];
        char nomeprod[MAX][50];
        int qtdprod[MAX];
        float precoprod[MAX];
        int total = 0;
        int menu; 
        
        carregarDadosIniciais(idprod, nomeprod, qtdprod, precoprod, &total);
       
        printf("\033[1;36m"); // Ciano brilhante
        printf(" ██████╗ ██████╗ ███╗   ██╗████████╗██████╗  ██████╗ ██╗     ███████╗\n");
        printf("██╔════╝██╔═══██╗████╗  ██║╚══██╔══╝██╔══██╗██╔═══██╗██║     ██╔════╝\n");
        printf("██║     ██║   ██║██╔██╗ ██║   ██║   ██████╔╝██║   ██║██║     █████╗  \n");
        printf("██║     ██║   ██║██║╚██╗██║   ██║   ██╔══██╗██║   ██║██║     ██╔══╝  \n");
        printf("╚██████╗╚██████╔╝██║ ╚████║   ██║   ██║  ██║╚██████╔╝███████╗███████╗\n");
        printf(" ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝\n");
        printf("██████╗ ███████╗    ███████╗███████╗████████╗ ██████╗  ██████╗ ██╗   ██╗███████╗\n");
        printf("██╔══██╗██╔════╝    ██╔════╝██╔════╝╚══██╔══╝██╔═══██╗██╔═══██╗██║   ██║██╔════╝\n");
        printf("██║  ██║█████╗      █████╗  ███████╗   ██║   ██║   ██║██║   ██║██║   ██║█████╗  \n");
        printf("██║  ██║██╔══╝      ██╔══╝  ╚════██║   ██║   ██║   ██║██║▄▄ ██║██║   ██║██╔══╝  \n");
        printf("██████╔╝███████╗    ███████╗███████║   ██║   ╚██████╔╝╚██████╔╝╚██████╔╝███████╗\n");
        printf("╚═════╝ ╚══════╝    ╚══════╝╚══════╝   ╚═╝    ╚═════╝  ╚══▀▀═╝  ╚═════╝ ╚══════╝\n");
        printf("\033[0m"); 
                
        do {
            
            printf("\n\n");
            printf("███╗   ███╗███████╗███╗   ██╗██╗   ██╗\n");
            printf("████╗ ████║██╔════╝████╗  ██║██║   ██║\n");
            printf("██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║\n");
            printf("██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║\n");
            printf("██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝\n");
            printf("╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝ \n");
            amarelo();
            printf("Produtos cadastrados: %d/%d\n\n", total, MAX);
            resetarCor();
            magenta();
            printf("1 - Cadastro de produtos\n2 - Listar produtos\n3 - Entrada de estoque\n4 - Saída de estoque\n5 - Busca por ID\n6 - Relatorios (Valor total - Produtos com maior e menor quantidade)\n7 - Remover Produto\n8 - SAIR\n\n");
            resetarCor();
            printf("Digite a opção desejada: ");
            if (scanf("%d", &menu) != 1){  // Validar caracter
                printf("\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
                vermelho();
                printf("Opção inválida, digite somente os números disponíveis!");
                resetarCor();
                printf("\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
                limparTela();
                while (getchar() != '\n'); // Limpa o buffer, descarta os caracteres inválidos, deixa limpo para leitura seguinte.
                continue;
            }
            if (menu < 1 || menu > 8){
                printf("\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
                vermelho();
                printf("   Opção (%d) inválida ", menu);
                resetarCor();
                printf("\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
                limparTela();
                continue;
            }
            
            switch (menu){ 
                case (1): cadastrarProduto(idprod, nomeprod, qtdprod, precoprod, &total); break;
                case (2): listarProduto(idprod, nomeprod, qtdprod, precoprod, total); break;
                case (3): entradaProduto(idprod, nomeprod, qtdprod, total); break;
                case (4): saidaProduto(idprod, nomeprod, qtdprod, total); break;
                case (5): buscaProduto(idprod, nomeprod, qtdprod, precoprod, total); break;
                case (6): relatorioProduto(nomeprod, qtdprod, precoprod, total); break;
                case (7): removerProduto(idprod, nomeprod, qtdprod, precoprod, &total); break;
                case (8):
                        printf("\n\n\n\n");
                        printf("███████╗██╗███╗   ███╗\n");
                        printf("██╔════╝██║████╗ ████║\n");
                        printf("█████╗  ██║██╔████╔██║\n");
                        printf("██╔══╝  ██║██║╚██╔╝██║\n");
                        printf("██║     ██║██║ ╚═╝ ██║\n");
                        printf("╚═╝     ╚═╝╚═╝     ╚═╝\n");
                        barraCarregamento(); 
                        break;
                default:
                printf("\n...................................................................\n");break;
            }
        if (menu != 8){
            pausa();
        limparTela(); 
        }
        }while (menu != 8); 
      return 0;
    } 