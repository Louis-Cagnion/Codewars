#include "skyscraper.h"

/**
 * @brief
 * Entry point of the skyscraper puzzle solver.
 *
 * `available_nbs` and the working `solution` grid live on the stack for the
 * whole solve, so no allocation happens until a solution is actually found.
 * This function:
 *
 * - initializes `available_nbs` with every value possible everywhere
 *
 * - applies every deterministic deduction from the clues (@ref
 *   put_towers_deduced)
 *
 * - runs the recursive backtracking search (@ref backtracking_solve)
 *
 * - on success, copies the stack-based result into a freshly allocated grid,
 *   the only heap allocation of the whole solve, so the caller can keep it
 *   after this function returns
 *
 * @param clues  the array of clues surrounding the board
 *
 * @return
 * A dynamically allocated 2D array representing the solution,
 * or `NULL` if `clues` is invalid or no solution was found.
 */
int **SolvePuzzle(int *clues)
{
	//return NULL if clues == NULL
	if (!clues)
		return (NULL);

	//init the boards of available numbers
	int available_nbs[N][N] = {0}, solution[N][N] = {0};
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
