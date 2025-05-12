#include <stdio.h>

#include <string.h>     // Necessário para STRCSPN.
#include <stdlib.h>     // Necessário para ATOI/ATOL/ATOF.


// Definição da estrutura para uma carta.
struct Carta {
    char estado[70];          // Estado (ex: "PR" ou "Paraná")
    char codigo[50];          // Código da carta (ex: "01")
    char cidade_nome[80];     // Nome da cidade (ex: "Curitiba")
    int populacao;            // População (ex: 1774000)
    float area;               // Área (em km²) (ex: 432)
    float pib;                // PIB (em bilhões de reais) (ex: 98)
    int pontos_turisticos;    // Número de pontos turísticos (ex: 20)
    float densidade;          // Densidade populacional (População/Área) (ex: 4100.00)
    float pib_per_capita;     // PIB per capita (PIB/População) (ex: 55000.00)
};

// Função para registrar os dados da carta.
void registroCarta(struct Carta *carta) {                           // Recebe um ponteiro para a estrutura 'Carta'.
    char buffer[100];                                               // Buffer para armazenar temporariamente a entrada do usuário.
    
    printf("Digite o estado (por exemplo, 'PR' ou 'Paraná'): ");
    fgets(carta->estado, sizeof(carta->estado), stdin);             // Lê e armazena a entrada do usuário na variável 'carta->estado'.
    carta->estado[strcspn(carta->estado, "\n")] = '\0';             // Remove a quebra de linha indesejada do final da string lida.
    
    printf("Digite o codigo da carta (por exemplo, '01'): ");
    fgets(carta->codigo, sizeof(carta->codigo), stdin);             // [...]
    carta->codigo[strcspn(carta->codigo, "\n")] = '\0';             // [...] ...
    
    printf("Digite o nome da cidade (por exemplo, 'Curitiba'): ");
    fgets(carta->cidade_nome, sizeof(carta->cidade_nome), stdin);
    carta->cidade_nome[strcspn(carta->cidade_nome, "\n")] = '\0';
    
    printf("Digite a populacao da cidade (por exemplo, '1774000'): ");
    fgets(buffer, sizeof(buffer), stdin);
    carta->populacao = atoi(buffer);
    
    printf("Digite a area da cidade em km² (por exemplo, '432'): ");
    fgets(buffer, sizeof(buffer), stdin);
    carta->area = atof(buffer);
    
    printf("Digite o PIB da cidade em bilhoes de reais (por exemplo, '98'): ");
    fgets(buffer, sizeof(buffer), stdin);
    carta->pib = atof(buffer);
    
    printf("Digite o numero de pontos turisticos (por exemplo, '20'): ");
    fgets(buffer, sizeof(buffer), stdin);
    carta->pontos_turisticos = atoi(buffer);
    
    // Cálculo dos valores derivados.
    if (carta->area > 0)                      // Se a área for maior que 0, calcula a densidade populacional.
                                              // Isso evita que seja mostrado "NaN" (Not a Number) se a área inserida for negativa.

        carta->densidade = carta->populacao / carta->area;  // Densidade = População / Área.
    
    // Do contrário, se a área for 0 ou negativa, a densidade é definida como 0.
    else
        carta->densidade = 0;
    
    if (carta->populacao > 0)                 // Se a população for maior que 0, calcula o PIB per capita.
                                              // Isso evita que seja mostrado "NaN" (Not a Number) se a população inserida for negativa.

        carta->pib_per_capita = (carta->pib * 1e9) / carta->populacao;      // PIB per capita = (PIB * 1e9) / População.

    // Do contrário, se a população for 0 ou negativa, o PIB per capita é definido como 0.
    else
        carta->pib_per_capita = 0;
}

// Função para mostrar os dados da carta.
void mostrarCarta(struct Carta carta, int numCarta) {           // Recebe a carta e o número da carta (1 ou 2).

    // Exibição dos dados da carta.
    printf("\nCARTA %d:\n", numCarta);                          // Título para a respectiva carta (1 ou 2).
    printf("Estado: %s\n", carta.estado);                       // Exibe o estado com %s, pois é uma string (texto).
    printf("Codigo: %s\n", carta.codigo);                       // Exibe o código da carta com %s, pois é uma string (texto).
    printf("Cidade: %s\n", carta.cidade_nome);                  // Exibe o nome da cidade com %s, pois é uma string (texto).
    printf("Populacao: %d\n", carta.populacao);                 // Exibe a população com %d, pois é um inteiro (número).

    printf("Area: %.2f km²\n", carta.area);                             // Exibe a área com 2 casas decimais (.2f).
                                                                        // Sufixo "km²" para indicar que é em quilômetros quadrados.

    printf("PIB: R$%.2f bi\n", carta.pib);                              // Exibe o PIB com 2 casas decimais (.2f).
    printf("Pontos Turisticos: %d\n", carta.pontos_turisticos);
    printf("Densidade populacional: %.2f\n", carta.densidade);          // Exibe a densidade populacional com 2 casas decimais (.2f).
    printf("PIB per capita: R$%.2f\n", carta.pib_per_capita);           // Exibe o PIB per capita com 2 casas decimais (.2f).
}

int main() {
    struct Carta carta1, carta2;                            // Declaração de duas cartas.
    // Variáveis para armazenar os atributos escolhidos pelo usuário.

    int op1 = 0, op2 = 0;                   // 0 para não escolhido, 1 a 5 para os atributos.

    float valor1_cartaAtr1 = 0, valor1_cartaAtr2 = 0;       // Valores para o primeiro atributo.
    float valor2_cartaAtr1 = 0, valor2_cartaAtr2 = 0;       // Valores para o segundo atributo.

    // Variáveis para armazenar os resultados finais.
    char *nomeAtributo1, *nomeAtributo2;
    
    // Cadastro das cartas.
    printf("\nDIGITE OS DETALHES DA PRIMEIRA CARTA.\n");
    registroCarta(&carta1);     // Registro das informações da Carta 1
    
    // Limpar o buffer do teclado para evitar problemas de leitura.
    fflush(stdin);
    
    printf("\nDIGITE OS DETALHES DA SEGUNDA CARTA.\n");
    registroCarta(&carta2);    // Registro das informações da Carta 2
    
    // Exibição dos dados cadastrados.
    printf("\nDetalhes da Carta 1:");
    mostrarCarta(carta1, 1);            // Exibe os dados da carta 1.

    printf("\nDetalhes da Carta 2:");
    mostrarCarta(carta2, 2);            // Exibe os dados da carta 2.
    
    // MENU para escolha do primeiro atributo.
    printf("\nEscolha o PRIMEIRO atributo para comparar:\n");
    printf("1. Populacao\n");
    printf("2. Area\n");
    printf("3. PIB\n");
    printf("4. Pontos Turisticos\n");
    printf("5. Densidade Populacional\n");

    printf("Opcao: ");
    scanf("%d", &op1);          // Lê a opção do usuário.
    
    // MENU dinâmico para escolha do segundo atributo (não pode repetir o primeiro).
    printf("\nEscolha o SEGUNDO atributo para comparar (diferente de %d):\n", op1);

    if (op1 != 1) printf("1. Populacao\n");                     // Se o primeiro atributo não for População, exibe a opção.
    if (op1 != 2) printf("2. Area\n");                          // Se o primeiro atributo não for Área, exibe a opção.
    if (op1 != 3) printf("3. PIB\n");                           // Se o primeiro atributo não for PIB, exibe a opção.
    if (op1 != 4) printf("4. Pontos Turisticos\n");             // Se o primeiro atributo não for Pontos Turísticos, exibe a opção.
    if (op1 != 5) printf("5. Densidade Populacional\n");        // Se o primeiro atributo não for Densidade Populacional, exibe a opção.

    printf("Opcao: ");
    scanf("%d", &op2);      // Lê a opção do usuário para o segundo atributo.
    
 // Se o segundo atributo for igual ao primeiro ou fora do intervalo de 1 a 5, solicitar nova entrada.
    while(op2 == op1 || op2 < 1 || op2 > 5) {
        printf("Opcao invalida! Selecione um atributo diferente.\nOpcao: ");
        scanf("%d", &op2);          // Lê a nova opção do usuário.
    }
    
    // Obtenção dos valores correspondentes para o PRIMEIRO atributo.
    switch(op1) {
        case 1:
            nomeAtributo1 = "Populacao";                    // Nome do atributo
            valor1_cartaAtr1 = (float)carta1.populacao;       // Atribui o valor da carta 1 à população;
            valor1_cartaAtr2 = (float)carta2.populacao;       // Atribuii o valor da carta 2 à população;
            break;
        case 2:
            nomeAtributo1 = "Area";                         // [...]
            valor1_cartaAtr1 = carta1.area;                   // [...]
            valor1_cartaAtr2 = carta2.area;                   // [...] ...
            break;
        case 3:
            nomeAtributo1 = "PIB";
            valor1_cartaAtr1 = carta1.pib;
            valor1_cartaAtr2 = carta2.pib;
            break;
        case 4:
            nomeAtributo1 = "Pontos Turisticos";
            valor1_cartaAtr1 = (float)carta1.pontos_turisticos;
            valor1_cartaAtr2 = (float)carta2.pontos_turisticos;
            break;
        case 5:
            nomeAtributo1 = "Densidade Populacional";
            valor1_cartaAtr1 = carta1.densidade;
            valor1_cartaAtr2 = carta2.densidade;
            break;
        default:
            printf("Opcao invalida!\n");            // Se o usuário inserir um número fora do intervalo de 1 a 5, exibe uma mensagem de erro.
            return 1;                               // Retorna 1 para indicar o erro.
    }
    
    // Obtenção dos valores correspondentes para o SEGUNDO atributo (op2).
    // O mesmo processo do primeiro atributo.

    switch(op2) {
        case 1:
            nomeAtributo2 = "Populacao";                // Nome do atributo
            valor2_cartaAtr1 = (float)carta1.populacao;   // Atribui o valor da carta 1 à população;
            valor2_cartaAtr2 = (float)carta2.populacao;   // Atribuii o valor da carta 2 à população;
            break;
        case 2:
            nomeAtributo2 = "Area";                     // [...]
            valor2_cartaAtr1 = carta1.area;               // [...]
            valor2_cartaAtr2 = carta2.area;               // [...] ...
            break;
        case 3:
            nomeAtributo2 = "PIB";
            valor2_cartaAtr1 = carta1.pib;
            valor2_cartaAtr2 = carta2.pib;
            break;
        case 4:
            nomeAtributo2 = "Pontos Turisticos";
            valor2_cartaAtr1 = (float)carta1.pontos_turisticos;
            valor2_cartaAtr2 = (float)carta2.pontos_turisticos;
            break;
        case 5:
            nomeAtributo2 = "Densidade Populacional";
            valor2_cartaAtr1 = carta1.densidade;
            valor2_cartaAtr2 = carta2.densidade;
            break;

        // Se o usuário inserir um número fora do intervalo de 1 a 5, exibe uma mensagem de erro.
        default:
            printf("Opcao invalida!\n");
            return 1;       // Retorna 1 para indicar o erro.
    }
    
    // Exibição dos resultados para os dois atributos.
    printf("\n--- Comparacao Individual dos Atributos ---\n");
    
    // Para o PRIMEIRO atributo.
    printf("\nAtributo: %s\n", nomeAtributo1);
    printf("Carta 1 - %s: %.2f\n", carta1.cidade_nome, valor1_cartaAtr1);
    printf("Carta 2 - %s: %.2f\n", carta2.cidade_nome, valor1_cartaAtr2);

    // Comparação dos valores do primeiro atributo.
    if(op1 == 5)  // Densidade Populacional

        // Se o primeiro atributo for Densidade Populacional, vence o menor.
        printf("Resultado: Carta %s venceu!\n", (valor1_cartaAtr1 < valor1_cartaAtr2) ? carta1.cidade_nome : (valor1_cartaAtr1 > valor1_cartaAtr2) ? carta2.cidade_nome : "Empate");
      
        // Se o primeiro atributo não for Densidade Populacional, vence o maior.
        else
        printf("Resultado: Carta %s venceu!\n", (valor1_cartaAtr1 > valor1_cartaAtr2) ? carta1.cidade_nome : (valor1_cartaAtr1 < valor1_cartaAtr2) ? carta2.cidade_nome : "Empate");
    
    // Para o SEGUNDO atributo.
    printf("\nAtributo: %s\n", nomeAtributo2);                           // Nome do segundo atributo.
    printf("Carta 1 - %s: %.2f\n", carta1.cidade_nome, valor2_cartaAtr1);  // Valor da carta 1.
    printf("Carta 2 - %s:%.2f\n", carta2.cidade_nome, valor2_cartaAtr2);   // Valor da carta 2.

    // Comparação dos valores do segundo atributo.
    if(op2 == 5)  // Densidade Populacional

        // Se o segundo atributo for Densidade Populacional, vence o menor.
        printf("Resultado: Carta %s venceu!\n", (valor2_cartaAtr1 < valor2_cartaAtr2) ? carta1.cidade_nome : (valor2_cartaAtr1 > valor2_cartaAtr2) ? carta2.cidade_nome : "Empate");
    
        // Se o segundo atributo não for Densidade Populacional, vence o maior.
        else
        printf("Resultado: Carta %s venceu!\n", (valor2_cartaAtr1 > valor2_cartaAtr2) ? carta1.cidade_nome : (valor2_cartaAtr1 < valor2_cartaAtr2) ? carta2.cidade_nome : "Empate");
    
    // Soma dos dois atributos para cada carta.
    float somaCarta1 = valor1_cartaAtr1 + valor2_cartaAtr1;         // Soma dos atributos da carta 1.
    float somaCarta2 = valor1_cartaAtr2 + valor2_cartaAtr2;         // Soma dos atributos da carta 2.
    
    // Exibição do resultado final.

    printf("\n-------------------------------------\n");        // Separador visual.

    printf("\n--- Resultado Final (Soma dos Atributos) ---\n");
    printf("Carta 1 - %s: Soma = %.2f\n", carta1.cidade_nome, somaCarta1);      // Soma dos atributos da carta 1.
    printf("Carta 2 - %s: Soma = %.2f\n", carta2.cidade_nome, somaCarta2);      // Soma dos atributos da carta 2.
    
    printf("\n-------------------------------------\n");        // Separador visual.

    // Uso do operador ternário para determinar o vencedor final.
    printf("\nCarta Vencedora: %s\n", 

        // Se a soma dos atributos da carta 1 for maior que a da carta 2, exibe o nome da carta 1.
           (somaCarta1 > somaCarta2) ? carta1.cidade_nome : 

           // Se a soma dos atributos da carta 1 for menor que a da carta 2, exibe o nome da carta 2.
           (somaCarta1 < somaCarta2) ? carta2.cidade_nome : "Empate");
                                                            // Empate se as somas forem iguais.
    
    return 0;           // Retorna 0 para indicar que o programa foi executado com sucesso.
}
