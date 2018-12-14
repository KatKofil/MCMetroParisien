#include "Includes/projet.h"

int new_station(graphe_t *metro, int indice_station){
	int find = 0;
	int indice_rand;
	int result;

	while (find == 0){
		indice_rand = rand() % (metro->vec_sommets[indice_station]->nb_voisins);
		result = metro->vec_sommets[indice_station]->tab_indice_voisins[indice_rand];
		if (metro->vec_sommets[result]->vu == 0)
			find = 1;
	}
	return result;
}

int test_node(graphe_t *metro, int indice_station, int indice_end){
	int i;
	int nb_station_visit;

	i = 0;
	nb_station_visit = 0;
	if (indice_station == indice_end)
		return 0;
	while (i < metro->vec_sommets[indice_station]->nb_voisins){
		if (DEBUG){
			printf("Passage dans la fonction test_node n°%d\n", i);
			printf("Vu de la station %s est a %d\n", metro->vec_sommets[metro->vec_sommets[indice_station]->tab_indice_voisins[i]]->nom_station, metro->vec_sommets[metro->vec_sommets[indice_station]->tab_indice_voisins[i]]->vu);
		}
		if (metro->vec_sommets[metro->vec_sommets[indice_station]->tab_indice_voisins[i]]->vu == 1)
			nb_station_visit++;
		i++;
	}
	if (nb_station_visit == metro->vec_sommets[indice_station]->nb_voisins)
		return 1;
	return 2;
}


void print_way(chemin_t *best_way, graphe_t *metro){
	int i;

	i = 0;
	printf("___________________________Chemin trouve avec le graphe de vecteur de successeur en %d arrets\n", best_way->nb_arret);
	for (i = 0; i < best_way->nb_arret; i++){
		printf("Station : %s\n", metro->vec_sommets[best_way->way[i]]->nom_station);
		printf("-----------------------------------------------------------\n");
	}
}


void get_way(graphe_t *metro, int indice_start, int indice_end){
	chemin_t *best_way;
	int *way;
	int nb_way;
	int result_test;
	int i;
	int k;
	int j;
	int continu;
	int indice_station;


	way = malloc(sizeof(int) * 300);
	nb_way = 0;
	best_way = malloc(sizeof(chemin_t));
	best_way->nb_arret = 300;
	best_way->way = malloc(sizeof(int) * 300);


	
	for (i = 0; i < ROLLOUT; i++){
		continu = 1;
		indice_station = indice_start;
		while(continu == 1){
			metro->vec_sommets[indice_station]->vu = 1;
			way[nb_way] = indice_station;
			nb_way++;
			result_test = test_node(metro, indice_station, indice_end);
			if (result_test == 2){
				indice_station = new_station(metro, indice_station);
			}
			if (result_test == 0){
				if (nb_way < best_way->nb_arret){
					best_way->nb_arret = nb_way;
					for (j = 0; j < nb_way; j++)
						best_way->way[j] = way[j];
					}
					continu = 0;
			}
			if (result_test == 1)
				continu = 0;
		}
		for (k = 0; k < metro->nb_noeud; k++)
			metro->vec_sommets[k]->vu = 0;
		for (k = 0; k < 300; k++)
			way[k] = 0;
		nb_way = 0;
	}
	if (best_way->nb_arret == 300){
		printf("La recherche d'un chemins a echoue\n");
	}
	else
		print_way(best_way, metro);
	free(way);
}
