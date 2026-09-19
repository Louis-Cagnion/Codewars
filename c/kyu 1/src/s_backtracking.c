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
 * @param prev_empty_box The position of the previous empty box, start at -1
 *
 * @return The solved grid or NULL if no solutions was found
 */
int	**backtracking_solve(int available_nbs[N][N][N], int **solution, int *clues, int depth)
{
	if (depth >= N * N)//avoid going too deep in the research
		return (solution);
	
	int line, col;
	bool found = false;

	empty_box_coords(solution, &line, &col);//get empty box coordinates
	if (line == -1 && col == -1 && clues_respected(clues, solution))//if no empty box and clues are respected
		return solution;//solution found
	else if (line == -1 && col == -1)//else return NULL, wrong solution
		return NULL;

	int available_nbs_dup[N][N][N], **solution_dup = init_solution(), nb_try = N + 1;//set nb to try to the highest one
	while (nb_try > 0)//while i have a number to place
	{
		sol_dup(solution_dup, solution);//dup solution
		available_dup(available_nbs_dup, available_nbs);//dup avaiable nbs
		nb_try = highest_available(available_nbs, line, col, nb_try - 1);//get numbers to try, if no numbers are available, return NULL
		if (!nb_try)
			break;
		set_valid_pos(nb_try, line, col, available_nbs_dup, solution_dup);//i put the number in the dup solution and change the dup avaiable numbers accordingly
		//print_all_available_each_box(available_nbs_dup, clues, solution_dup);
		int **input = backtracking_solve(available_nbs_dup, solution_dup, clues, depth + 1);//i test if it works recursively
		if (!input || !clues_respected(clues, input) || empty_box(solution_dup))//if i got NULL, or i didn't get the right solution, or there's no available numbers on the box
			continue;//i try another one
		found = true;
		sol_dup(solution, input);//else, i got the right solution
		break;
		
	}
	if (!found && !depth)
	{
		free_array2(solution);
		solution = NULL;
	}
	free_array2(solution_dup);
	return solution;
}
