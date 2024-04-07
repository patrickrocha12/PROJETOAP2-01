// Projeto Algoritmos 01 - CC2N
// Fabio Oliveira da Silva - RA:10420458
// Leonardo Silva Moreno Ruiz - RA:10420477
// Patrick Rocha de Andrade - RA:10410902

// Bibliotecas útilizadas
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#include <time.h> 

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Valores constantes usado ao decorrer do projeto
#define TAM_PALAVRA 5 
#define MAX_TENTATIVAS 6
#define MAX_PALAVRA 50
// Arquivo contendo as palavras sem acentos e o arquivo para armazenar o score
#define SEM_ACENTOS "sem_acentos.txt" 
#define ARQUIVO_SCORES "scores.txt" 

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Função para carregar uma palavra aleatória do arquivo 
void carregar_palavra(char *palavra_secreta) {

    // Abre o arquivo sem_acentos.txt e lê o dicionário 
    FILE *arquivo = fopen(SEM_ACENTOS, "r"); 

    srand(time(NULL)); 
    int num_palavras = 0;
    char palavra[MAX_PALAVRA];

    // Verifica se a palavra tem o tamanho desejado
    while (fscanf(arquivo, "%s", palavra) != EOF) {
        if (strlen(palavra) == TAM_PALAVRA) { 
            num_palavras++;}
    }

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

    // Bloco que sorteia uma palavra aleatória de 5 caracteres
    int palavra_sorteada = rand() % num_palavras; 
    rewind(arquivo);
    while (palavra_sorteada >= 0) {
        fscanf(arquivo, "%s", palavra_secreta); 

        // Verifica se a palavra sorteada tem o tamanho desejado
        if (strlen(palavra_secreta) == TAM_PALAVRA) { 
            palavra_sorteada--;}
    }

    // Fecha o arquivo após sortear a palavra
    fclose(arquivo); 
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Função para exibir o layout inicial
void layout_inicial() {
    printf("Bem-vindo ao Descubra a palavra!\n");
    printf("Tente adivinhar a palavra secreta de %d letras.\n", TAM_PALAVRA);
    printf("Use letras minúsculas sem acentos.\n\n");
    printf("+-----------+\n");
    printf("|           |\n");
    printf("| x x x x x |\n");
    printf("+-----------+\n\n");
    printf("LEGENDA:\n");
    printf("• ^ faz parte da palavra e está na posição correta.\n");
    printf("• ! faz parte da palavra, mas não está na posição correta.\n");
    printf("• x não faz parte da palavra.\n\n");
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Funções para exibir o layout com as tentativas do jogador e a legenda

// Função para imprimir a legenda da tentativa
void imprimir_letras(char *letras, int num_letras, const char *mensagem) {
    if (num_letras > 0) {
        printf("• ");
        // Loop para iterar as letras no array
        for (int i = 0; i < num_letras; i++) { 
            printf("%c", letras[i]);
            // Verifica se não é a última letra
            if (i < num_letras - 1) { 
                // Verifica se não é a penúltima letra
                if (i < num_letras - 2) { 
                    // Imprime vírgula para separar as letras
                    printf(", ");
                } 
                else {
                    // Imprime "e" para separar as últimas duas letras
                    printf(" e "); 
                }
            }
        }
        printf(" %s.\n", mensagem);
    }
}

// Função para exibir o layout do jogo e a legenda
void layout_tentativa(char *palavra, char *tentativa) {
    printf("\n+-----------+\n"); 
    printf("| ");
    for (int i = 0; i < TAM_PALAVRA; i++) {
        // Converte para maiúscula
        printf("%c ", toupper(tentativa[i])); 
    }
    printf("|\n");
    printf("| ");

    // Loop que faz a comparação das letras da palavra secreta com a tentativa do jogador e adiciona a legenda ^, ! e x
    for (int i = 0; i < TAM_PALAVRA; i++) {
        if (tentativa[i] == palavra[i]) {
            printf("^ ");
        } 
        else if (strchr(palavra, tentativa[i]) != NULL && palavra[i] != tentativa[i]) {
            printf("! ");
        } 
        else {
            printf("x ");
        }
    }
    printf("|\n");
    printf("+-----------+\n\n"); 
    printf("LEGENDA:\n"); 

    // Arrays para armazenar letras corretas, incorretas e que não fazem parte da palavra secreta
    char corretas[TAM_PALAVRA], incorretas[TAM_PALAVRA], nao_faz_farte[TAM_PALAVRA];
    int num_corretas = 0, num_incorretas = 0, num_nao_faz_parte = 0;

    // Preenche os arrays de letras corretas, incorretas e que não fazem parte da palavra
    for (int i = 0; i < TAM_PALAVRA; i++) {
        if (tentativa[i] == palavra[i]) {
            corretas[num_corretas++] = toupper(tentativa[i]);
        } 
        else if (strchr(palavra, tentativa[i]) != NULL && palavra[i] != tentativa[i]) {
            incorretas[num_incorretas++] = toupper(tentativa[i]);
        } 
        else {
            nao_faz_farte[num_nao_faz_parte++] = toupper(tentativa[i]);
        }
    }

    // Exibe as letras corretas
    imprimir_letras(corretas, num_corretas, "faz(em) parte da palavra e está(ão) na posição correta");

    // Exibe as letras incorretas
    imprimir_letras(incorretas, num_incorretas, "faz(em) parte da palavra e está(ão) na posição incorreta");

    // Exibe as letras que não fazem parte
    imprimir_letras(nao_faz_farte, num_nao_faz_parte, "não faz(em) parte da palavra");

    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Função para verificar se a tentativa tem o tamanho correto, contém apenas letras minúsculas e sem acentos
int validar_tentativa(char *tentativa) {
    if (strlen(tentativa) != TAM_PALAVRA) {
        printf("A tentativa deve ter exatamente %d caracteres.\n\n", TAM_PALAVRA);
        return 0;
    }
    for (int i = 0; i < TAM_PALAVRA; i++) {
        if (!islower(tentativa[i])) {
            printf("Use apenas letras minúsculas sem acentos.\n\n");
            return 0;
        }
    }
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Função main para inicializar o jogo
int main() {
    char palavra_secreta[TAM_PALAVRA + 1];
    char tentativa[TAM_PALAVRA + 1];

    // Inicializa o número de tentativas restantes
    int tentativas_restantes = MAX_TENTATIVAS;

    // Variáveis para medir o tempo decorrido
    clock_t inicio, fim; 

    // Carrega a palavra secreta
    carregar_palavra(palavra_secreta); 

    // Exibe o layout inicial do jogo
    layout_inicial(); 

    // Loop para cada tentativa do jogador
    for (int tentativa_atual = 1; tentativa_atual <= MAX_TENTATIVAS; tentativa_atual++) { 
        // Inicia a contagem de tempo no início das tentativas
        if(tentativa_atual == 1) {
            inicio = clock(); 
        }
        printf("Tentativa %d de %d:\n", tentativa_atual, MAX_TENTATIVAS); 
        scanf("%s", tentativa);

        // Verifica se a tentativa tem o tamanho correto, contém apenas letras minúsculas e sem acentos
        if (!validar_tentativa(tentativa)) {
            tentativa_atual--;
            continue;
        }

        // Exibe o layout com a palavra adivinhada e sua legenda
        layout_tentativa(palavra_secreta, tentativa);

        // Verifica se o jogador adivinhou a palavra secreta
        if (strcmp(tentativa, palavra_secreta) == 0) {
            printf("Parabéns! Você acertou a palavra secreta: %s\n", palavra_secreta);

            // Solicita o nome do jogador
            char nome_jogador[100];
            printf("Por favor, digite seu nome: ");
            scanf("%s", nome_jogador);

            // Calcula o tempo total até acertar a palavra sorteada
            fim = clock();
            double tempoTotal = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            // Registra as informações no arquivo scores.txt
            FILE *arquivoScores = fopen(ARQUIVO_SCORES, "a");
            fprintf(arquivoScores, "%s %s %d %.2f\n", nome_jogador, palavra_secreta, tentativa_atual, tempoTotal);
            // Fecha o arquivo
            fclose(arquivoScores);
            // Encerra o programa caso o jogador acerte a palavra secreta
            return 0; 
        }

    }

    // Se o jogador não adivinhar após 6 tentativas, mostra qual era a palavra secreta
    printf("Você excedeu o número máximo de tentativas. A palavra secreta era: %s\n", palavra_secreta);

    // Encerra o programa caso o jogador não adivinhar a palavra secreta
    return 0; 
}

