#include "skyscraper.h"

/**
 * @brief
 * Find the empty box with the fewest remaining candidates (MRV heuristic).
 *
 * Scans the whole grid and, among the still-empty boxes, keeps the one with
 * the smallest count of non-zero entries in `available_nbs`. Picking the
 * most constrained box first makes wrong guesses fail faster during
 * backtracking, since it is the box least likely to have many valid options.
 *
 * @param solution      The solution grid
 * @param available_nbs The array of possible numbers
 * @param line          Output: the row of the chosen box, or -1 if the grid is full
 * @param col           Output: the column of the chosen box, or -1 if the grid is full
 */
void	empty_box_coords(int **solution, int available_nbs[N][N][N], int *line, int *col)
{
	int best_line = -1;
	int best_col = -1;
	int best_count = N + 1;

	for (*line = 0; *line < N && best_count; (*line)++)
	{
		for (*col = 0; *col < N && best_count; (*col)++) {
			if (solution[*line][*col])
				continue;
			int count = 0;
			for (int nb = 0; nb < N; nb++)
				if (available_nbs[nb][*line][*col])
					count += 1;
			if (count < best_count) {
				best_count = count;
				best_line = *line;
				best_col = *col;
			}
		}
	}
	*line = best_line;
	*col = best_col;
}

/**
 * @brief
 * Find the highest value still available for a box, no higher than `start`.
 *
 * @param available_nbs The array of possible numbers
 * @param line          The line in `available_nbs`
 * @param col           The column in `available_nbs`
 * @param start         The highest value to consider (inclusive)
 *
 * @return the highest available value `<= start`, or 0 if none is available
 */
int highest_available(int available_nbs[N][N][N], int line, int col, int start)
{
	for (int nb = start; nb > 0; nb--)
		if (available_nbs[nb - 1][line][col])
			return available_nbs[nb - 1][line][col];
	return 0;
}

/**
 * @brief
 * Copy every box of `solution` into `solution_dup`.
 *
 * @param solution_dup The destination grid, already allocated
 * @param solution     The source grid
 */
void sol_dup(int **solution_dup, int **solution)
{
	for (int line = 0; line < N; line++)
		for (int col = 0; col < N; col++)
			solution_dup[line][col] = solution[line][col];
}

/**
 * @brief
 * Copy every entry of `available_nbs` into `available_nbs_dup`.
 *
 * @param available_nbs_dup The destination array
 * @param available_nbs     The source array
 */
void available_dup(int available_nbs_dup[N][N][N], int available_nbs[N][N][N])
{
	for (int nb = 0; nb < N; nb++)
	{
		for (int line = 0; line < N; line++)
			for (int col = 0; col < N; col++)
				available_nbs_dup[nb][line][col] = available_nbs[nb][line][col];
	}
}

/**
 * @brief
 * Check that no clue is already exceeded by what's currently filled in.
 *
 * Unlike @ref clues_respected, this can be called on a partially filled grid:
 * it only rejects a clue once the visible-tower count on its filled prefix
 * (see @ref visible_towers_prefix) has gone strictly above the clue's value,
 * which can only get worse as more boxes are filled in. A `true` result does
 * not mean the grid is a valid solution, only that nothing filled in so far
 * rules it out yet — meant to prune a branch during backtracking before it
 * reaches a fully filled, and much more expensive to check, grid.
 *
 * @param clues    The array of clues
 * @param solution The (possibly partial) solution grid
 *
 * @return `false` if some clue is already exceeded, `true` otherwise
 */
bool	prefix_respects_clues(int *clues, int **solution)
{
	for (int i = 0; i < N * 4; i++)
	{
		if (clues[i] && !((i < N && clues[i] >= visible_towers_prefix(TTB, 0, top_cond_nb(i), solution))
			|| (i >= N && i < N * 2 && clues[i] >= visible_towers_prefix(RTL, right_cond_nb(i), 0, solution))
			|| (i >= N * 2 && i < N * 3 && clues[i] >= visible_towers_prefix(BTT, 0, bottom_cond_nb(i), solution))
			|| (i >= N * 3 && clues[i] >= visible_towers_prefix(LTR, left_cond_nb(i), 0, solution))))
			return false;
	}
	return true;
}

/**
 * @brief
 * Check that a fully filled solution grid matches every clue exactly.
 *
 * Unlike @ref prefix_respects_clues, this requires the grid to be complete:
 * it computes the real visible-tower count for each clue's line or column
 * (see @ref visible_towers) and compares it to the clue's value.
 *
 * @param clues    The array of clues
 * @param solution The (fully filled) solution grid
 *
 * @return `true` if every clue matches, else `false`
 */
bool	clues_respected(int *clues, int **solution)
{
	for (int i = 0; i < N * 4; i++)
	{
		if (clues[i] && !((i < N && clues[i] == visible_towers(TTB, 0, top_cond_nb(i), solution))
			|| (i >= N && i < N * 2 && clues[i] == visible_towers(RTL, right_cond_nb(i), 0, solution))
			|| (i >= N * 2 && i < N * 3 && clues[i] == visible_towers(BTT, 0, bottom_cond_nb(i), solution))
			|| (i >= N * 3 && clues[i] == visible_towers(LTR, left_cond_nb(i), 0, solution))))
			return false;
	}
	return true;
}

/**
 * @brief
 * Check whether a solution grid still has at least one empty box.
 *
 * @param solution The solution grid
 *
 * @return `true` if at least one box is still empty, else `false`
 */
bool empty_box(int **solution)
{
	for (int line = N - 1; line >= 0; line--)
	{
		for (int col = N - 1; col >= 0; col--)
			if (!solution[line][col])
				return true;
	}
	return false;
}
