#include "Includes/projet.h"

noeud_t **get_nodes(char *filename, graphe_t *metro){
	FILE *file;
	noeud_t *station = NULL;
	noeud_t **vec_sommets = NULL;
	int tmp_line;
	int tmp_voisins;
	int *tmp_tab_indice_voisin;

	char *token = NULL;
	char buff[BUFF_SYZE];
	int i, j, k, alloc_voisins, conteur_voisins;
	char *ptr;



	k = 0;
	alloc_voisins = 0;
	file = fopen(filename, "r");
	vec_sommets = (noeud_t **)malloc(sizeof(noeud_t *) * metro->nb_noeud);
	if (file != NULL){
		while ((fgets(buff, BUFF_SYZE, file)) != NULL){
			ptr = buff;
			j = 0;
			i = 0;
			conteur_voisins = 0;

			station = calloc(1, sizeof(*station));
			if (station != NULL){
				while ((token = strtok(ptr, DELIM)) != NULL){
					if (j == 0)
						ptr = NULL;
					if (i == 0){
						tmp_line = atoi(token);
						station->line = tmp_line;
					}
					if (i == 1)
						station->nom_station = strdup(token);
					if (i == 2){
						station->nb_voisins = atoi(token);
					}
					if (station->nb_voisins == 0 && alloc_voisins == 0){
						tmp_tab_indice_voisin = malloc(8 + sizeof(int) * station->nb_voisins);
						alloc_voisins = 1;
					}
					if (i > 2){
						tmp_voisins = atoi(token);
						tmp_tab_indice_voisin[conteur_voisins] = tmp_voisins;
						conteur_voisins++;
					}
					i++;
				}
				station->tab_indice_voisins = tmp_tab_indice_voisin;
			}
			vec_sommets[k] = malloc(sizeof(noeud_t));
			vec_sommets[k]->line = station->line;
			vec_sommets[k]->nom_station = strdup(station->nom_station);
			vec_sommets[k]->nb_voisins = station->nb_voisins;
			vec_sommets[k]->tab_indice_voisins = malloc(sizeof(int) * vec_sommets[k]->nb_voisins);
			for (int o = 0; o < vec_sommets[k]->nb_voisins; o++)
				vec_sommets[k]->tab_indice_voisins[o] = station->tab_indice_voisins[o];
			vec_sommets[k]->vu = 0;
			k++;
		}
		free(tmp_tab_indice_voisin);
	}
	return vec_sommets;
}

void add_list(save_t *list, int indice_voisin){
	list_t *new;

	new = malloc(sizeof(list_t*));
	new->indice_voisin = indice_voisin;
	new->next = list->first;
	list->first = new;
}


node_t **get_list(char *filename, graphe_t *metro){
	FILE *file;
	node_t *station = NULL;
	node_t **vec_sommets = NULL;
	int tmp_line;
	int tmp_voisins;
	int *tmp_tab_indice_voisin;

	char *token = NULL;
	char buff[BUFF_SYZE];
	int i, j, k, y, alloc_voisins, conteur_voisins;
	char *ptr;
	list_t *tmp_list_voisin;



	k = 0;
	alloc_voisins = 0;
	file = fopen(filename, "r");
	vec_sommets = (node_t **)malloc(sizeof(node_t *) * metro->nb_noeud);
	if (file != NULL){
		while ((fgets(buff, BUFF_SYZE, file)) != NULL){
			ptr = buff;
			j = 0;
			i = 0;
			conteur_voisins = 0;

			station = calloc(1, sizeof(*station));
			if (station != NULL){
				while ((token = strtok(ptr, DELIM)) != NULL){
					if (j == 0)
						ptr = NULL;
					if (i == 0){
						tmp_line = atoi(token);
						station->line = tmp_line;
					}
					if (i == 1)
						station->nom_station = strdup(token);
					if (i == 2){
						station->nb_voisins = atoi(token);
					}
					if (station->nb_voisins == 0 && alloc_voisins == 0){
						tmp_tab_indice_voisin = malloc(8 + sizeof(int *) * station->nb_voisins);
						alloc_voisins = 1;
					}
					if (i > 2){
						tmp_voisins = atoi(token);
						tmp_tab_indice_voisin[conteur_voisins] = tmp_voisins;
						conteur_voisins++;
					}
					i++;
				}
				tmp_list_voisin = malloc(sizeof(tmp_list_voisin));
				station->voisins = malloc(sizeof(save_t *));
				tmp_list_voisin->indice_voisin = tmp_tab_indice_voisin[0];
				tmp_list_voisin->next = NULL;
				station->voisins->first = tmp_list_voisin;
				for (y = 1; y < station->nb_voisins; y++){
					add_list(station->voisins, tmp_tab_indice_voisin[y]);
				}
			}
			vec_sommets[k] = malloc(sizeof(noeud_t));
			vec_sommets[k]->line = station->line;
			vec_sommets[k]->nom_station = strdup(station->nom_station);
			vec_sommets[k]->nb_voisins = station->nb_voisins;
			vec_sommets[k]->voisins = station->voisins;
			vec_sommets[k]->vu = 0;
			k++;
		}
		free(tmp_tab_indice_voisin);
	}
	return vec_sommets;
}

void clear_buf(){
	int c = 0;
	
	while(c != '\n' && c !=  EOF)
		c = getchar();
}

void free_graphe(graphe_t *metro){
	int i = 0;
	while (i < metro->nb_noeud && metro->vec_sommets != NULL){
		free(metro->vec_sommets[i]->tab_indice_voisins);
		i++;
	}
	free(metro->vec_sommets);
}


int main(void){
	FILE *f;
	char buf[4];
	graphe_t *metro;
	graphe_l_t *metre;
	int nb_station;
	int d = 0;
	int indice_start;
	int indice_end;
	char station_start[30];
	char station_end[30];
	int fin = 0;
	int valide = 0;
	double debut_vec = 0;
	double fin_vec = 0;
	double result_vec = 0;
	double debut_list = 0;
	double fin_list = 0;
	double result_list = 0;


	srand(time(NULL));

	f = fopen("nbStation.txt", "rt");
	if (f == NULL){
		printf("Error : fopen return NULL\n");
		return 0;
	}

	fgets(buf, 4, f);
	metro = malloc(sizeof(*metro) * 1);
	metre = malloc(sizeof(*metre) * 1);
	fclose(f);

	nb_station = atoi(buf);
	metro->nb_noeud = nb_station;
	metre->nb_noeud = nb_station;
	metro->vec_sommets = get_nodes("metro.csv", metro);
	metre->vec_sommets = get_list("metro.csv", metro);

	while (fin == 0){
		while (valide == 0){
			printf("Veuillez entrer le nom de la station de depart:\n");
			fgets(station_start, sizeof station_start, stdin);
			printf("Veuillez entrer le nom de la station d'arriver:\n");
			fgets(station_end, sizeof station_end, stdin);
			printf("Vous avez choisis de partir de %s Pour aller a %s", station_start, station_end);

			for (d = 0; d < 30; d++){
				if (station_start[d] == '\n')
					station_start[d] = '\0';
				if (station_end[d] == '\n')
					station_end[d] = '\0';
			}

			if (test_station(station_start, station_end, metro) == 0){
				printf("La station de depart ou d'arriver choisis n'est pas repertoriee\n");
				printf("Consultez le fichier stations.txt");
				printf("Veuillez relancer la recherche\n");
				clear_buf();
			}
			else
				valide = 1;
		}

		indice_start = recup_indice(station_start, metro);
		indice_end = recup_indice(station_end, metro);
		valide = 0;
		debut_vec = (double)clock();
		get_way(metro, indice_start, indice_end);
		fin_vec = (double)clock();
		debut_list = (double)clock();
		get_way_list(metre, indice_start, indice_end);
		fin_list = (double)clock();
		result_list = fin_list - debut_list;
		result_vec = fin_vec - debut_vec;
		printf("L'algorithme MC a trouver un chemins en %ftics pour un graphe a vecteur de successeur\n", result_vec);
		printf("L'algorithme MC a trouver un chemins en %ftics pour un graphe a liste de successeur\n", result_list);
		printf("Voulez-vous effectuer une autre recherche? [0]YES [1]NO\n");
		scanf("%d", &fin);
		clear_buf();
	}


	free_graphe(metro);
	return 0;
}
