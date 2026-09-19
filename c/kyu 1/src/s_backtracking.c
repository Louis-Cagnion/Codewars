#include "skyscraper.h"

/**
 * @brief
 * Solve the skyscraper puzzle using backtracking.
 *
 * The current solution is saved before attempting recursive resolution.
 *
 * @param available_nbs the array of possible numbers
 * @param solution      The solution grid
 * @param clues         The array of clues
 * @param depth         The level of depth in my recursivity
 *
 * @return The solved grid or NULL if no solutions was found
 */
bool	backtracking_solve(int available_nbs[N][N][N], int solution[N][N], int *clues, int depth)
{
	if (depth >= N * N)//avoid going too deep in the research
		return true;
	
	int line, col;

	empty_box_coords(solution, available_nbs, &line, &col);//get empty box coordinates
	if (line == -1 && col == -1)//if no empty box and clues are respected
		return clues_respected(clues, solution);//solution found

	int available_nbs_dup[N][N][N], solution_dup[N][N], nb_try = N + 1;//set nb to try to the highest one
	while (nb_try > 0)//while i have a number to place
	{
		sol_dup(solution_dup, solution);//dup solution
		available_dup(available_nbs_dup, available_nbs);//dup avaiable nbs
		nb_try = highest_available(available_nbs, line, col, nb_try - 1);//get numbers to try, if no numbers are available, return NULL
		if (!nb_try)
			break;
		set_valid_pos(nb_try, line, col, available_nbs_dup, solution_dup);//i put the number in the dup solution and change the dup avaiable numbers accordingly
		if (!prefix_respects_clues(clues, solution_dup))
			continue;
		//print_all_available_each_box(available_nbs_dup, clues, solution_dup);
		bool found = backtracking_solve(available_nbs_dup, solution_dup, clues, depth + 1);//i test if it works recursively
		if (!found || empty_box(solution_dup))//if i got NULL, or i didn't get the right solution, or there's no available numbers on the box
			continue;//i try another one
		found = true;
		sol_dup(solution, solution_dup);//else, i got the right solution
		return true;
		
	}
	return false;
}
