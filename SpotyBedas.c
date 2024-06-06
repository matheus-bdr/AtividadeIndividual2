//matheus da cruz santos UC21200334
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SpotyBedas.h"
void criar_lista(Musica *playlist[], int *quantidade_de_musicas)
{
    char artista_musica[300];
    char *delimitador;
    int i = 0;
    FILE *arq = fopen("musicas.txt", "r");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fgets(artista_musica, sizeof(artista_musica), arq) != NULL)
    {
        playlist[i] = (Musica *)malloc(sizeof(Musica));
        if (i == 0)
        {
            playlist[i]->anterior = NULL;
        }
        else
        {
            playlist[i]->anterior = playlist[i - 1];
            playlist[i - 1]->proximo = playlist[i];
        }

        delimitador = strtok(artista_musica, ";");
        if (delimitador)
        {
            strcpy(playlist[i]->artista, delimitador);
            delimitador = strtok(NULL, "\n");
            if (delimitador)
            {
                strcpy(playlist[i]->nome_musica, delimitador);
            }
        }
        i++;
    }

    if (i > 0)
    {
        playlist[0]->anterior = playlist[i - 1];
        playlist[i - 1]->proximo = playlist[0];
    }

    *quantidade_de_musicas = i;
    fclose(arq);
}

void atualizar_arquivo(Musica *playlist[], int quantidade_de_musicas)
{
    FILE *arq = fopen("musicas.txt", "w");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < quantidade_de_musicas; i++)
    {
        fprintf(arq, "%s;%s\n", playlist[i]->artista, playlist[i]->nome_musica);
    }

    fclose(arq);
}

void inserir_musica(Musica *playlist[], int *quantidade_de_musicas)
{
    int quantidade = *quantidade_de_musicas;
    playlist[quantidade] = (Musica *)malloc(sizeof(Musica));

    printf("Digite o nome do artista a ser inserido: ");
    fgets(playlist[quantidade]->artista, sizeof(playlist[quantidade]->artista), stdin);
    playlist[quantidade]->artista[strcspn(playlist[quantidade]->artista, "\n")] = '\0';  // Remover a nova linha

    printf("Digite o nome da musica a ser inserida: ");
    fgets(playlist[quantidade]->nome_musica, sizeof(playlist[quantidade]->nome_musica), stdin);
    playlist[quantidade]->nome_musica[strcspn(playlist[quantidade]->nome_musica, "\n")] = '\0';  // Remover a nova linha

    if (quantidade > 0)
    {
        playlist[quantidade - 1]->proximo = playlist[quantidade];
        playlist[quantidade]->anterior = playlist[quantidade - 1];
    }
    playlist[quantidade]->proximo = playlist[0];
    playlist[0]->anterior = playlist[quantidade];

    *quantidade_de_musicas += 1;
    atualizar_arquivo(playlist, *quantidade_de_musicas);
}

void excluir_musica(Musica *playlist[], int *quantidade_de_musicas)
{
    char nome_artista_musica[100];
    int i = 0, indicador = -1;

    printf("Digite o nome do artista ou da musica: ");
    fgets(nome_artista_musica, sizeof(nome_artista_musica), stdin);
    nome_artista_musica[strcspn(nome_artista_musica, "\n")] = '\0';  // Remover a nova linha

    while (i < *quantidade_de_musicas)
    {
        if (strcmp(nome_artista_musica, playlist[i]->nome_musica) == 0 || strcmp(nome_artista_musica, playlist[i]->artista) == 0)
        {
            indicador = i;

            printf("Artista e musica deletados.\n");

            if (i == *quantidade_de_musicas - 1)
            {
                playlist[i - 1]->proximo = playlist[0];
                playlist[0]->anterior = playlist[i - 1];
            }
            else if (i == 0)
            {
                playlist[*quantidade_de_musicas - 1]->proximo = playlist[1];
                playlist[1]->anterior = playlist[*quantidade_de_musicas - 1];
            }
            else
            {
                playlist[i - 1]->proximo = playlist[i + 1];
                playlist[i + 1]->anterior = playlist[i - 1];
            }

            free(playlist[i]);
            for (int j = i; j < *quantidade_de_musicas - 1; j++)
            {
                playlist[j] = playlist[j + 1];
            }
            *quantidade_de_musicas -= 1;
            atualizar_arquivo(playlist, *quantidade_de_musicas);
            return;
        }
        i++;
    }

    if (indicador == -1)
    {
        printf("Artista ou musica nao encontrado\n");
    }
}

void buscar_musica(Musica *playlist[], int quantidade_de_musicas)
{
    char recebe_nome[100];
    int i = 0;

    printf("Digite o nome do artista ou da musica: ");
    fgets(recebe_nome, sizeof(recebe_nome), stdin);
    recebe_nome[strcspn(recebe_nome, "\n")] = '\0';  // Remover a nova linha

    while (i < quantidade_de_musicas)
    {
        if (strcmp(recebe_nome, playlist[i]->nome_musica) == 0 || strcmp(recebe_nome, playlist[i]->artista) == 0)
        {
            printf("Artista e Musica encontrado com sucesso.\n");
            printf("Musica na posicao %d da sua playlist.\n", i + 1);
            printf("Artista: %s, Musica: %s.\n", playlist[i]->artista, playlist[i]->nome_musica);
            return;
        }
        i++;
    }

    printf("Artista ou musica nao encontrado.\n");
}

void ultimas_adicionadas(Musica *playlist[], int quantidade_de_musicas)
{
    printf("___________________________________________________________________\n");

    for (int i = 0; i < quantidade_de_musicas; i++)
    {
        printf("Artista/Banda: %s, Musica: %s.\n", playlist[i]->artista, playlist[i]->nome_musica);
        if (i < quantidade_de_musicas - 1)
        {
            printf("...\n");
        }
    }
    printf("___________________________________________________________________\n");
}

int musicas_comparadas(const void *a, const void *b)
{
    Musica *musicaA = *(Musica **)a;
    Musica *musicaB = *(Musica **)b;
    return strcasecmp(musicaA->nome_musica, musicaB->nome_musica);
}

void ordenada_alfabetica(Musica *playlist[], int quantidade_de_musicas)
{
    Musica *lista2[50];

    for (int i = 0; i < quantidade_de_musicas; i++)
    {
        lista2[i] = playlist[i];
    }

    qsort(lista2, quantidade_de_musicas, sizeof(Musica *), musicas_comparadas);

    printf("___________________________________________________________________\n");
    printf("\nPlaylist em ordem alfabetica:\n");
    for (int i = 0; i < quantidade_de_musicas; i++)
    {
        printf("Artista: %s, Musica: %s\n", lista2[i]->artista, lista2[i]->nome_musica);
        if (i < quantidade_de_musicas - 1)
        {
            printf("...\n");
        }
    }
    printf("___________________________________________________________________\n");
}

void proxima_musica(Musica **musica_atual)
{
    *musica_atual = (*musica_atual)->proximo;
}

void musica_anterior(Musica **musica_atual)
{
    *musica_atual = (*musica_atual)->anterior;
}

int main()
{
    Musica *playlist[50];
    Musica *musica_atual;
    int quantidade_de_musicas = 0, opcao = 0;

    criar_lista(playlist, &quantidade_de_musicas);

    if (quantidade_de_musicas > 0)
    {
        musica_atual = playlist[0];
    }

    while (opcao != 8)
    {
        if (quantidade_de_musicas > 0)
        {
            printf("\n-> Voce esta ouvindo: %s\n\n", musica_atual->nome_musica);
        }
        else
        {
            printf("\nNenhuma musica na playlist.\n");
        }
        printf("-------------------------MENU do SpotyBedas--------------------------\n");

        printf("1 - Exibir a playlist pela ordem de cadastro\n");
        printf("2 - Ordenar por nome das musicas (a-z)\n");
        printf("3 - Inserir nova musica\n");
        printf("4 - Remover musica\n");
        printf("5 - Buscar musica\n");
        printf("6 - Pular musica\n");
        printf("7 - Voltar para a musica anterior\n");
        printf("8 - sair\n");
        printf("-> ");
        scanf("%d", &opcao);
        getchar();  // Consumir a nova linha deixada pelo scanf

        switch (opcao)
        {
        case 1:
            ultimas_adicionadas(playlist, quantidade_de_musicas);
            break;
        case 2:
            ordenada_alfabetica(playlist, quantidade_de_musicas);
            break;
        case 3:
            inserir_musica(playlist, &quantidade_de_musicas);
            break;
        case 4:
            excluir_musica(playlist, &quantidade_de_musicas);
            break;
        case 5:
            buscar_musica(playlist, quantidade_de_musicas);
            break;
        case 6:
            if (quantidade_de_musicas > 0)
            {
                proxima_musica(&musica_atual);
            }
            break;
        case 7:
            if (quantidade_de_musicas > 0)
            {
                musica_anterior(&musica_atual);
            }
            break;
        case 8:
            printf("Encerrando spotyBedas.\n");
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }
    }

    // Liberar memória alocada
    for (int i = 0; i < quantidade_de_musicas; i++)
    {
        free(playlist[i]);
    }

    return 0;
}
