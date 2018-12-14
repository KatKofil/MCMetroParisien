#ifndef PROJET_H
#define PROJET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define BUFF_SYZE 1024
#define DELIM ";"
#define DEBUG 0			//0 pas d'affichage //1 affichage find.c //2 affichage main.c //3 affiche recup.c
#define ROLLOUT 100000


typedef struct list_sommets{
	int indice_voisin;
	struct list_sommets *next;
}				list_t;

typedef struct list_save{
	list_t *first;
}				save_t;

typedef struct list_node{
	int line;
	char *nom_station;
	int nb_voisins;
	save_t *voisins;
	int vu;
}				node_t;

typedef struct noeud{
	int line;
	char *nom_station;
	int nb_voisins;
	int *tab_indice_voisins; //recuperable dans vec_sommets
	int vu;
}				noeud_t;

typedef struct graphe_list{
	int nb_noeud;
	node_t **vec_sommets;
}				graphe_l_t;

typedef struct graphe{
	int nb_noeud;
	noeud_t **vec_sommets;
}				graphe_t;

typedef struct chemin{
	int nb_arret;
	int *way;
}				chemin_t;

//fonctions de find.c
int new_station(graphe_t *metro, int indice_station);
int test_node(graphe_t *metro, int indice_station, int indice_end);
void get_way(graphe_t * metro, int indice_start, int indice_end);
void print_way(chemin_t *best_way, graphe_t *metro);

//fonctions de find_list.c
int new_station_list(graphe_l_t *metro, int indice_station);
int test_node_list(graphe_l_t *metro, int indice_station, int indice_end);
void get_way_list(graphe_l_t *metro, int indice_start, int indice_end);

//Fonctions de recup.c
int recup_indice(char station[30], graphe_t *metro);
int test_station(char station_start[30], char station_end[30], graphe_t *metro);

//fonctions de main.c
noeud_t **get_nodes(char *filename, graphe_t *metro);
node_t **get_list(char *filename, graphe_t *metro);
void clear_buf();
void free_graphe(graphe_t *metro);


//je considere que tt les statio non un poid de 0 (assez representatif du metro parisien)

#endif
