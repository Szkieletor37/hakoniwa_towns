// eval_result_of_combination.h

#ifndef _EVAL_RESULT_OF_COMBINATION_H_
#define _EVAL_RESULT_OF_COMBINATION_H_

typedef struct {

	LinkedList_Possible_Relative_Position *LinkedList_position_best_combination;
	int* sum_of_landprice_bonus_rate;
	
	LinkedList_Pair_of_Position_Combination_and_Sum_Bonus_Rate *next_llppcsr;

} LinkedList_Pair_of_Position_Combination_and_Sum_Bonus_Rate;



extern LinkedList_Possible_Relative_Position_Combination_and_Sum_Bonus_Rate *LinkedList_position_best_16_combination;

extern void eval_result_of_combination(LinkedList_Possible_Relative_Position *LinkedList_possible_position_combination);

extern void LinkedList_pair_of_position_combination_and_sum_bonus_rate_init(void);

LinkedList_Pair_of_Position_Combination_and_Sum_Bonus_Rate *nth_LinkedList_paie_of_position_combination_and_sum_bonus_rate;
#endif // _EVAL_RESULT_OF_COMBINATION_H_
