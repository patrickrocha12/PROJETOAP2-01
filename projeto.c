// Projeto Algoritmos 01 - CC2N
// Fabio Oliveira da Silva - RA:10420458
// Leonardo Silva Moreno Ruiz - RA:10420477
// Patrick Rocha de Andrade - RA:10410902

// Bibliotecas �tilizadas
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

// Fun��o para carregar uma palavra aleat�ria do arquivo 
void carregar_palavra(char *palavra_secreta) {

    // Abre o arquivo sem_acentos.txt e l� o dicion�rio 
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

    // Bloco que sorteia uma palavra aleat�ria de 5 caracteres
    int palavra_sorteada = rand() % num_palavras; 
    rewind(arquivo);
    while (palavra_sorteada >= 0) {
        fscanf(arquivo, "%s", palavra_secreta); 

        // Verifica se a palavra sorteada tem o tamanho desejado
        if (strlen(palavra_secreta) == TAM_PALAVRA) { 
            palavra_sorteada--;}
    }

    // Fecha o arquivo ap�s sortear a palavra
    fclose(arquivo); 
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Fun��o para exibir o layout inicial
void layout_inicial() {
    printf("Bem-vindo ao Descubra a palavra!\n");
    printf("Tente adivinhar a palavra secreta de %d letras.\n", TAM_PALAVRA);
    printf("Use letras min�sculas sem acentos.\n\n");
    printf("+-----------+\n");
    printf("|           |\n");
    printf("| x x x x x |\n");
    printf("+-----------+\n\n");
    printf("LEGENDA:\n");
    printf("� ^ faz parte da palavra e est� na posi��o correta.\n");
    printf("� ! faz parte da palavra, mas n�o est� na posi��o correta.\n");
    printf("� x n�o faz parte da palavra.\n\n");
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Fun��es para exibir o layout com as tentativas do jogador e a legenda

// Fun��o para imprimir a legenda da tentativa
void imprimir_letras(char *letras, int num_letras, const char *mensagem) {
    if (num_letras > 0) {
        printf("� ");
        // Loop para iterar as letras no array
        for (int i = 0; i < num_letras; i++) { 
            printf("%c", letras[i]);
            // Verifica se n�o � a �ltima letra
            if (i < num_letras - 1) { 
                // Verifica se n�o � a pen�ltima letra
                if (i < num_letras - 2) { 
                    // Imprime v�rgula para separar as letras
                    printf(", ");
                } 
                else {
                    // Imprime "e" para separar as �ltimas duas letras
                    printf(" e "); 
                }
            }
        }
        printf(" %s.\n", mensagem);
    }
}

// Fun��o para exibir o layout do jogo e a legenda
void layout_tentativa(char *palavra, char *tentativa) {
    printf("\n+-----------+\n"); 
    printf("| ");
    for (int i = 0; i < TAM_PALAVRA; i++) {
        // Converte para mai�scula
        printf("%c ", toupper(tentativa[i])); 
    }
    printf("|\n");
    printf("| ");

    // Loop que faz a compara��o das letras da palavra secreta com a tentativa do jogador e adiciona a legenda ^, ! e x
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

    // Arrays para armazenar letras corretas, incorretas e que n�o fazem parte da palavra secreta
    char corretas[TAM_PALAVRA], incorretas[TAM_PALAVRA], nao_faz_farte[TAM_PALAVRA];
    int num_corretas = 0, num_incorretas = 0, num_nao_faz_parte = 0;

    // Preenche os arrays de letras corretas, incorretas e que n�o fazem parte da palavra
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
    imprimir_letras(corretas, num_corretas, "faz(em) parte da palavra e est�(�o) na posi��o correta");

    // Exibe as letras incorretas
    imprimir_letras(incorretas, num_incorretas, "faz(em) parte da palavra e est�(�o) na posi��o incorreta");

    // Exibe as letras que n�o fazem parte
    imprimir_letras(nao_faz_farte, num_nao_faz_parte, "n�o faz(em) parte da palavra");

    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Fun��o para verificar se a tentativa tem o tamanho correto, cont�m apenas letras min�sculas e sem acentos
int validar_tentativa(char *tentativa) {
    if (strlen(tentativa) != TAM_PALAVRA) {
        printf("A tentativa deve ter exatamente %d caracteres.\n\n", TAM_PALAVRA);
        return 0;
    }
    for (int i = 0; i < TAM_PALAVRA; i++) {
        if (!islower(tentativa[i])) {
            printf("Use apenas letras min�sculas sem acentos.\n\n");
            return 0;
        }
    }
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Fun��o main para inicializar o jogo
int main() {
    char palavra_secreta[TAM_PALAVRA + 1];
    char tentativa[TAM_PALAVRA + 1];

    // Inicializa o n�mero de tentativas restantes
    int tentativas_restantes = MAX_TENTATIVAS;

    // Vari�veis para medir o tempo decorrido
    clock_t inicio, fim; 

    // Carrega a palavra secreta
    carregar_palavra(palavra_secreta); 

    // Exibe o layout inicial do jogo
    layout_inicial(); 

    // Loop para cada tentativa do jogador
    for (int tentativa_atual = 1; tentativa_atual <= MAX_TENTATIVAS; tentativa_atual++) { 
        // Inicia a contagem de tempo no in�cio das tentativas
        if(tentativa_atual == 1) {
            inicio = clock(); 
        }
        printf("Tentativa %d de %d:\n", tentativa_atual, MAX_TENTATIVAS); 
        scanf("%s", tentativa);

        // Verifica se a tentativa tem o tamanho correto, cont�m apenas letras min�sculas e sem acentos
        if (!validar_tentativa(tentativa)) {
            tentativa_atual--;
            continue;
        }

        // Exibe o layout com a palavra adivinhada e sua legenda
        layout_tentativa(palavra_secreta, tentativa);

        // Verifica se o jogador adivinhou a palavra secreta
        if (strcmp(tentativa, palavra_secreta) == 0) {
            printf("Parab�ns! Voc� acertou a palavra secreta: %s\n", palavra_secreta);

            // Solicita o nome do jogador
            char nome_jogador[100];
            printf("Por favor, digite seu nome: ");
            scanf("%s", nome_jogador);

            // Calcula o tempo total at� acertar a palavra sorteada
            fim = clock();
            double tempoTotal = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            // Registra as informa��es no arquivo scores.txt
            FILE *arquivoScores = fopen(ARQUIVO_SCORES, "a");
            fprintf(arquivoScores, "%s %s %d %.2f\n", nome_jogador, palavra_secreta, tentativa_atual, tempoTotal);
            // Fecha o arquivo
            fclose(arquivoScores);
            // Encerra o programa caso o jogador acerte a palavra secreta
            return 0; 
        }

    }

    // Se o jogador n�o adivinhar ap�s 6 tentativas, mostra qual era a palavra secreta
    printf("Voc� excedeu o n�mero m�ximo de tentativas. A palavra secreta era: %s\n", palavra_secreta);

    // Encerra o programa caso o jogador n�o adivinhar a palavra secreta
    return 0; 
}

