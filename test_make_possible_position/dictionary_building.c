#include "dictionary_building.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define NUMBUILDING 162 

//Dictionary_Building dictionary_building[NUMBUILDING];

Building *dictionary_building[NUMBUILDING];

void put_data_of_building_to_dictionary(void) {
	
	int i;
	FILE *fp;


	for(i=0; i<NUMBUILDING; i++) {
		dictionary_building[i] = malloc(sizeof(Building));
		*(dictionary_building[i]) = building_null();
	}

	
	char *fname = "data_building.csv";

	fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("%sファイルが開けません\n", fname);
	}
	
	printf("\n");
	
	int building_length_buffer[2] = {0,0};
	
	for(i=0; i<NUMBUILDING; i++) {

		fscanf(fp, "%[^,],%d,%d\n", dictionary_building[i]->B_name, &building_length_buffer[0], &building_length_buffer[1]);
		
		dictionary_building[i]->B_length = building_length_buffer[0];
		dictionary_building[i]->B_width = building_length_buffer[1];
		dictionary_building[i]->id = i;

		if(building_length_buffer[0] == building_length_buffer[1]) {
			dictionary_building[i]->B_rotate = &(flag_f);
		}
		else {
			dictionary_building[i]->B_rotate = &(flag_t);
		}	
	}
	printf("dictionary_building[%d] = { \n\n", NUMBUILDING);

	for(i=0; i<NUMBUILDING; i++) {

		printf("{%s, %d, %d}\n", dictionary_building[i]->B_name, dictionary_building[i]->B_length, dictionary_building[i]->B_width);
	}

	printf("\n} \n");

/*	while( (ret=fscanf(fp, "%lf,%lf,%lf", &data[0], &data[1], &data[2])) != EOF) {
	  printf("%lf %lf %lf\n", data[0], data[1], data[2]);
	  }

	  printf("\n");*/
	fclose(fp);

}

Building *search_building_from_dictionary(char B_name[]) {

	int i=0;
	
	if(B_name == NULL) {
		return NULL;
	}

	while(1) {
		
		if(i == NUMBUILDING) {
			return NULL;
		}

		if(strcmp(B_name, dictionary_building[i]->B_name) == 0) {
			break;
		}

		i++;
	}
	
	Building *b = dictionary_building[i];//building_init(B_name, point_init_zero(), dictionary_building[i].DB_length, dictionary_building[i].DB_width);

	return b;
}


