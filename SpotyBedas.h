#ifndef SPOTYBEDAS_H
#define SPOTYBEDAS_H

typedef struct Musica
{
    char artista[100];
    char nome_musica[100];
    struct Musica *proximo;
    struct Musica *anterior;
} Musica;

void criar_lista(Musica *playlist[], int *quantidade_de_musicas);
void atualizar_arquivo(Musica *playlist[], int quantidade_de_musicas);
void inserir_musica(Musica *playlist[], int *quantidade_de_musicas);
void excluir_musica(Musica *playlist[], int *quantidade_de_musicas);
void buscar_musica(Musica *playlist[], int quantidade_de_musicas);
void ultimas_adicionadas(Musica *playlist[], int quantidade_de_musicas);
void ordenada_alfabetica(Musica *playlist[], int quantidade_de_musicas);
void proxima_musica(Musica **musica_atual);
void musica_anterior(Musica **musica_atual);

#endif
