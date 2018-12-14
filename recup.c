#include "Includes/projet.h"


//retourne 0 si la station n est pas dans le graphe
int test_station(char station_start[30], char station_end[30], graphe_t *metro){
	int i;
	int valid_start;
	int valid_end;

	for (i = 0; i < metro->nb_noeud; i++){
		if (strcmp(station_start, metro->vec_sommets[i]->nom_station) == 0)
			valid_start = 1;
		if (strcmp(station_end, metro->vec_sommets[i]->nom_station) == 0)
			valid_end = 1;
	}
	if (valid_start == 1 && valid_end == 1)
		return 1;
	return 0;
}

int recup_indice(char station[30], graphe_t *metro){
	int i;

	for (i = 0; i < metro->nb_noeud; i++){
		if (strcmp(station, metro->vec_sommets[i]->nom_station) == 0)
			return i;
	}
	return (-1);
}
