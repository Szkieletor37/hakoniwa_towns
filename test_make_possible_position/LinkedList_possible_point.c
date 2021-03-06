#include "LinkedList_possible_point.h"
#include <stdio.h>
#include <stdlib.h>
/* Point *make_point(int *x, int *y, int *flag) {

	Point *newpoint = malloc(sizeof(Point));

	if (newpoint != NULL) {
		newpoint.x = x;
		newpoint.y = y;
		newpoint->flag = flag;
	}
	return newpoint;
}

*/


LinkedList_Possible_Point *make_LinkedList_possible_point(Point p, LinkedList_Possible_Point *llpp) {

	LinkedList_Possible_Point *new_llpp = malloc(sizeof(LinkedList_Possible_Point));
	if (new_llpp == NULL) {
		free(new_llpp);
		new_llpp = NULL;
		return NULL;
	}
	new_llpp->p = p;
	//printf("%d, %d = x, y\n", p.x, p.y);
	new_llpp->next_llpp = llpp;


	return new_llpp;

}

void delete_LinkedList_possible_point(LinkedList_Possible_Point **llpp_ptr){
	LinkedList_Possible_Point **temp = NULL;

	while(*llpp_ptr != NULL) {
		temp = &((*llpp_ptr)->next_llpp);	
		/*if(llpp->next_llpp != NULL) {
			free(llpp->p);
			//llpp->p == NULL;
		}*/
		free(*llpp_ptr);
		*llpp_ptr = NULL;
		llpp_ptr = temp;
	}

} // 先頭から順番に削除してる

LinkedList_Possible_Point *nth_LinkedList_possible_point(LinkedList_Possible_Point *llpp, int n) {

	int cnt = -1;
	
	while (cnt < n) {
		
		if (llpp == NULL) {
			return NULL;
		}
		else {
			llpp = llpp->next_llpp; 
			cnt++;
		}
	}

	return llpp;

} // ヘッダポイントは-1番目、先頭は0番目

int insert_nth_LinkedList_possible_point(LinkedList_Possible_Point **llpp_ptr, int n, Point p) {

//	int i;
	LinkedList_Possible_Point *llpp_temp;

	if (n<0) {
		return 0;
	}
	llpp_temp = nth_LinkedList_possible_point(*llpp_ptr, n-1);
	llpp_ptr = &(llpp_temp);
	(*llpp_ptr)->next_llpp = make_LinkedList_possible_point(p, llpp_temp->next_llpp);


	return 1; // true
/*	for (i=0; i<n && *llpp_ptr !=NULL; i++) {
		llpp_ptr = &((*llpp_ptr)->next_llpp);
	}

	if(i<n) {
		return 0;
	}
	pp_temp = make_LinkedList_possible_point(p, *llpp_ptr);
	if(pp_temp == NULL) {
		return 0;
	}
	*llpp_ptr = pp_temp;*/
	
	/*for(i=0; i<n && *llpp_ptr != NULL; i++) {
		llpp_ptr = &((*llpp_ptr)->next_llpp);
	}
	
	if (i<n) {
		return 0; //failed
	}
	LinkedList_Possible_Point *new_llpp = make_LinkedList_possible_point(p, (*llpp_ptr));
	*(llpp_ptr)=new_llpp;*/

}

int push_LinkedList_possible_point(LinkedList_Possible_Point **llpp_ptr, Point p) {
	
	return insert_nth_LinkedList_possible_point(llpp_ptr, 0, p);

}


int is_adjacent(Building *B_target, Building *B_object) {

	if (B_object->id == -1) {
	//	printf("隣接してないよ\n");
		return 0; //存在しなければそもそも隣接してない
	}
	else {
		int x_target = B_target->B_left_bottom_point.x, y_target =B_target->B_left_bottom_point.y;
		int l_target = B_target->B_length, w_target = B_target->B_width;
		int x_object = B_object->B_left_bottom_point.x, y_object = B_object->B_left_bottom_point.y;
		int l_object = B_object->B_length, w_object = B_object->B_width;
		
	//	printf("%sは(%d, %d), %sは(%d, %d)", B_target->B_name, B_target->B_left_bottom_point.x, B_target->B_left_bottom_point.y, B_object->B_name, B_object->B_left_bottom_point.x, B_object->B_left_bottom_point.y);
		if (((x_target - w_object == x_object || x_target + w_target == x_object) && ((y_object >= (y_target+1-l_object)) && (y_object <= (y_target+l_target-1)))) || ((y_target - l_object == y_object || y_target + l_target == y_object) && ((x_object >= x_target + 1 - w_object) && (x_object <= x_target + w_target -1)))){

	//		printf("隣接してるから追加しないよ\n");	
			return 1;
		}
		else {	
	//		printf("隣接してないよ\n");

			return 0;
		}
	}
}

int check_unoverlap(Point* possible_point, int length_object, int width_object, Building *B_element_2) {

	if (B_element_2->id == -1) {
	//	printf("重なってないよ\n");
		return 1; //存在していなければoverlapしない
	}

	int x_o = possible_point->x, y_o = possible_point->y;
	int l_o = length_object, w_o = width_object;
	int x_e2 = B_element_2->B_left_bottom_point.x;
	int y_e2 = B_element_2->B_left_bottom_point.y;
	int l_e2 = B_element_2->B_length;
	int w_e2 = B_element_2->B_width;

	if((/*objectの右側が重なる*/(x_o + w_o > x_e2 && x_o + w_o <= x_e2 + w_e2) || /*objectの左側が重なる*/(x_o - w_e2 < x_e2 && x_o + w_o >= x_e2)) && (/*objectの上側が重なる*/ (y_o + l_o > y_e2 && y_o + l_o <= y_e2 + l_e2)  ||/*objectの下側が重なる*/ (y_o - l_e2 < y_e2 && y_o + l_o >= y_e2))) {
	//	printf("重なってるよ\n");
		return 0;
	}
	else {
	//	printf("重なってないよ\n");
		return 1;
	}
}


int help_store_possible_point(int min_coordinate, int max_coordinate, int flag, int z, Building *B_object, Building *B_e2, LinkedList_Possible_Point **llpp_ptr_object, int cnt_object_possible_point) {

	//int cnt_object_possible_point = 0;
	int i;
	Point p, *pp = &p;	
	if (flag == 0) {
	printf("%dから%dまでx座標を動かすよ。y座標は%dだよ。\n", min_coordinate, max_coordinate-1, z);
	}
	else {
		printf("%dから%dまでy座標を動かすよ。x座標は%dだよ。\n", min_coordinate, max_coordinate-1, z);
	}

	for(i=min_coordinate; i<max_coordinate; i++) {

		if(flag == 0) {
			p = point_init(i, z, 1);
		}
		else {
			p = point_init(z, i, 1);
		}
		
		(B_object->B_left_bottom_point) = p; //一旦格納して条件を満たすか調べる

		printf("今のiは%dだよ\n", i);
		if(check_unoverlap(pp, (B_object->B_length), (B_object->B_width), B_e2) == 1 && is_adjacent(B_object, B_e2) == 0) {

			push_LinkedList_possible_point(llpp_ptr_object, p);
			Point p = nth_LinkedList_possible_point(*llpp_ptr_object, 0)->p;
			printf("%d, %d\n がllppの%d番目\n\n", p.x, p.y, cnt_object_possible_point);
			cnt_object_possible_point++;
		
		}
		/*else {
			
			B_object->B_left_bottom_point = point_init(0,0,0); //元に戻す
		}*/
/*
		else {
			push_LinkedList_possible_point(llpp_ptr_object,pp);
			cnt_object_possible_point++;
		}
*/
	}

	return cnt_object_possible_point;
}


// map上に存在するtargetとobjectを隣接させたい時、objectの可能な座標を教えてくれる関数。
int store_possible_point(Building *B_target, Building *B_object, Building *B_element_2, LinkedList_Possible_Point **llpp_ptr_object) {

	printf("\nstore_possible_pointに入るよ\n");

	printf("いま%sの隣に%sを置きたいよ。まわりに%sがあるかもね\n\n", B_target->B_name, B_object->B_name, B_element_2->B_name);
	int sum_cnt_object_possible_point = 0;

	int min_coordinate=0, max_coordinate=0, z=0;
//
//	int cnt_object_possible_point_top=0, cnt_object_possible_point_bottom=0, cnt_object_possible_point_left=0, cnt_object_possible_point_right=0;

	// 上隣接
	//printf("\n上隣接\n");
	min_coordinate = (B_target->B_left_bottom_point.x) + 1 - (B_object->B_width);
	max_coordinate = (B_target->B_left_bottom_point.x) + (B_target->B_width);
	z = (B_target->B_left_bottom_point.y) + (B_target->B_length);

	sum_cnt_object_possible_point = help_store_possible_point(min_coordinate, max_coordinate, 0, z, B_object, B_element_2, llpp_ptr_object, 0); 



	/*		Point *p = point_init(i, B_target->B_left_bottom_point.y + B_target->B_length);

			if (check_unoverlap(p, *(B_object->B_length), *(B_object->B_width), B_element_2) == 1 && is_adjacent(B_object, B_element_2) == 0) {

			push_LinkedList_possible_point(LinkedList_object_possible_point, p);

			cnt_object_possible_point++;
			}

			}
			*/
	//printf("\n下隣接\n");
	min_coordinate = (B_target->B_left_bottom_point.x) + 1 - (B_object->B_width);
	max_coordinate = (B_target->B_left_bottom_point.x) + (B_target->B_width);
	z = (B_target->B_left_bottom_point.y) - (B_object->B_length);

	sum_cnt_object_possible_point = help_store_possible_point(min_coordinate, max_coordinate, 0, z, B_object, B_element_2, llpp_ptr_object, sum_cnt_object_possible_point); 


	/*
	   help_store_possible_point(B_target->B_left_bottom_point.y + 1 - B_object->B_width), (B_target->B_left_bottom_point.x + B_target->B_width), 0, B_target->B_left_bottom_point.y + B_target->B_length) {for(i=(B_target->B_left_bottom_point.x + 1 - B_object->B_width); i < (B_target->B_left_bottom_point.x + B_target->B_width); i++) {

	   Point *p = point_init(i, B_target->B_left_bottom_point.y - B_object->B_length);

	   if (check_unoverlap(p, B_object->B_length, B_object->B_width, B_element_2) == 1 && is_adjacent(B_object, B_element_2) == 0) {

	   push_LinkedList_possible_point(LinkedList_object_possible_point, p);
	   cnt_object_possible_point++;

	   }
	   }
	   */	
	//printf("\n左隣接\n");
	min_coordinate = (B_target->B_left_bottom_point.y) + 1 - B_object->B_length;
	max_coordinate = (B_target->B_left_bottom_point.y + B_target->B_width);
	z = B_target->B_left_bottom_point.x - (B_object->B_width);

	sum_cnt_object_possible_point = help_store_possible_point(min_coordinate, max_coordinate, 1, z, B_object, B_element_2, llpp_ptr_object, sum_cnt_object_possible_point); 


	/*
	   for(i=(B_target->B_left_bottom_point.y + 1 - B_object->B_length); i < (B_target->B_left_bottom_point.y + B_target->B_width); i++) {

	   Point *p = point_init(B_target->B_left_bottom_point.x - B_object->B_width, i);

	   if (check_unoverlap(p, B_object->B_length, B_object->B_width, B_element_2) == 1 && is_adjacent(B_object, B_element_2) == 0) {
	   push_LinkedList_possible_point(LinkedList_object_possible_point, p);
	   cnt_object_possible_point++;
	   }
	   }
	   */
	//printf("\n右隣接");
	min_coordinate = (B_target->B_left_bottom_point.y) + 1 - (B_object->B_length);
	max_coordinate = (B_target->B_left_bottom_point.y) + (B_target->B_width);
	z = (B_target->B_left_bottom_point.x) + (B_target->B_width);
	
	sum_cnt_object_possible_point = help_store_possible_point(min_coordinate, max_coordinate, 1, z, B_object, B_element_2, llpp_ptr_object,sum_cnt_object_possible_point); 


/*
	   for(i=(B_target->B_left_bottom_point.y + 1 - B_object->B_length); i < (B_target->B_left_bottom_point.x + B_target->B_width); i++) {
	   Point *p = point_init(B_target->B_left_bottom_point.x + B_target->B_width, i);

	   if (check_unoverlap(p, B_object->B_length, B_object->B_width, B_element_2) == 1 && is_adjacent(B_object, B_element_2) == 0) {
	   push_LinkedList_possible_point(LinkedList_object_possible_point, p);
	   cnt_object_possible_point++;
	   }
	   }
	   */
	// LinkedList_e1_possible_point に全パターンが入った。

//	sum_cnt_object_possible_point = cnt_object_possible_point_top + cnt_object_possible_point_left + cnt_object_possible_point_right + cnt_object_possible_point_bottom;

	//printf("\n置ける座標が%d個出てきたよ\n", sum_cnt_object_possible_point);
	return sum_cnt_object_possible_point;

	
}


	
