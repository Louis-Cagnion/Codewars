#include "skyscraper.h"

/**
 * @brief
 * Entry point of the skyscraper puzzle solver.
 *
 * This function initializes all required data structures:
 * 
 * - marks empty clues as already fulfilled
 * 
 * - allocates and initializes `available_nbs`
 * 
 * - allocates and initializes the `solution` grid
 *
 * It then applies all deterministic deductions before
 * entering the recursive backtracking phase.
 *
 * @param clues  the array of clues surrounding the board
 *
 * @return
 * A dynamically allocated 2D array representing the solution,
 * or `NULL` if `clues` is invalid.
 */
int **SolvePuzzle(int *clues)
{
	//return NULL if clues == NULL
	if (!clues)
		return (NULL);

	//init the boards of available numbers
	int available_nbs[N][N][N] = {0}, solution[N][N] = {0};
	init_availability(available_nbs);
	put_towers_deduced(available_nbs, solution, clues);
	//return the solution
	if (!backtracking_solve(available_nbs, solution, clues, 0))
		return NULL;
	int **result = init_solution();
	for (int line = 0; line < N; line++)
		for (int col = 0; col < N; col++)
			result[line][col] = solution[line][col];
	return result;
}
