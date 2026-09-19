#include "skyscraper.h"

/**
 * @brief
 * Handle a top or right clue whose opposite (bottom or left) clue sums with
 * it to `N + 1`. When that holds, the tallest tower (N) must sit at the
 * intersection line/column implied by the two clue values, and gets placed
 * there directly.
 *
 * @param cur_clue      The index of the current (top or right) clue
 * @param available_nbs The array of possible numbers
 * @param solution      The solution grid
 * @param clues         The array of clues
 */
void	opposite_clues(int cur_clue, int available_nbs[N][N][N], int solution[N][N], int *clues)
{
	int f_clue = clues[cur_clue], s_clue, line = 0, col = 0;

	if (cur_clue < N)//top clue
	{
		s_clue = clues[N * 3 - 1 - cur_clue];//opposite bottom clue
		col = cur_clue;
		line = f_clue - 1;
	}
	else//right clue
	{
		s_clue = clues[N * 5 - 1 - cur_clue];//opposite left clue (* 5 because cur_clue has to lose N to be correct)
		line = cur_clue - N;
		col = s_clue - 1;
	}
	if (f_clue + s_clue == N + 1)
		set_valid_pos(N, line, col, available_nbs, solution);
}

/**
 * @brief
 * Handle a clue equal to 1 by placing the tallest tower (N) right next to
 * that clue, since a visibility of 1 means the very first box already
 * blocks the view of everything behind it.
 *
 * @param cur_clue       The index of the current clue
 * @param available_nbs the array of possible numbers
 * @param solution      The solution grid
 */
void	actualise_min_clue(int cur_clue, int available_nbs[N][N][N], int solution[N][N])
{
	int way = cur_clue / N;// to know on which side the clue is

	if (way == 0)// if the clue is at the top
		set_valid_pos(N, 0, top_cond_nb(cur_clue), available_nbs, solution);
	else if (way == 1)// if the clue is on the right
		set_valid_pos(N, right_cond_nb(cur_clue), N - 1, available_nbs, solution);
	else if (way == 2)// if the clue is at the bottom
		set_valid_pos(N, N - 1, bottom_cond_nb(cur_clue), available_nbs, solution);
	else// if the clue is on the left
		set_valid_pos(N, left_cond_nb(cur_clue), 0, available_nbs, solution);
}

/**
 * @brief
 * Handle a clue equal to N by placing every tower along the corresponding
 * line or column in the only order that makes all N of them visible:
 * ascending from the clue's side (1 first) if it starts at box value 1,
 * descending (N first) if it starts at box value N.
 *
 * @param cur_clue       The index of the current clue
 * @param available_nbs the array of possible numbers
 * @param solution      The solution grid
 */
void	actualise_max_clue(int cur_clue, int available_nbs[N][N][N], int solution[N][N])
{
	int way = cur_clue / N;// to know on which side the clue is
	/* {upper clue, right clue, lower clue, left clue} */
	int nbs[4] = {1, N, N, 1};//starting number
	int cur_clues[4] = {top_cond_nb(cur_clue), right_cond_nb(cur_clue), bottom_cond_nb(cur_clue), left_cond_nb(cur_clue)};// the clue position on a line (0 to N - 1)

	const int i = (nbs[way] == 1) ? 1 : -1;
	// if the clue is on a column
	if (way == 0 || way == 2)
	{
		for (int line = 0; line < N; line++)
		{
			set_valid_pos(nbs[way], line, cur_clues[way], available_nbs, solution);
			nbs[way] += i;
		}
	}
	// if the clue is on a line
	else
	{
		for (int col = 0; col < N; col++)
		{
			set_valid_pos(nbs[way], cur_clues[way], col, available_nbs, solution);
			nbs[way] += i;
		}
	}
}

/**
 * @brief
 * For every non-zero clue, eliminate the tower values that would make it
 * impossible to reach that clue's visibility count from its side — a tower
 * placed too early and too tall would block the view of enough towers
 * behind it that the required count could never be reached.
 *
 * @param available_nbs The array of possible numbers
 * @param clues         The array of clues
 */
void	reduce_possibilities_from_clues(int available_nbs[N][N][N], int *clues)
{
	int	limit;

	for (int i = 0; i < N * 4; i++)
	{
		if (clues[i])
		{
			limit = rev_nb(clues[i]) + 2;//for N = 4 : 1 -> first nb is 4, 2 -> first nb is 3, 3 -> first nb is 2, 4 -> first nb is 1
			if (i < N)
			{
				int line = 0;
				while (limit != N)
				{
					int inc = 0;
					while (limit + inc < N)
						available_nbs[limit + inc++][line][top_cond_nb(i)] = 0;//i remove every number above the limit
					line++;//i go to the next line
					limit++;//i remove numbers above limit + 1 on the next box to keep the visibility of towers according to the clue
				}
			}
			else if (i < N * 2)
			{
				int col = N - 1;
				while (limit != N)
				{
					int inc = 0;
					while (limit + inc < N)
						available_nbs[limit + inc++][right_cond_nb(i)][col] = 0;//i remove every number above the limit
					col--;//i go to the next column
					limit++;//same
				}
			}
			else if (i < N * 3)
			{
				int line = N - 1;
				while (limit != N)
				{
					int inc = 0;
					while (limit + inc < N)
						available_nbs[limit + inc++][line][bottom_cond_nb(i)] = 0;//i remove every number above the limit
					line--;//i go to the next line
					limit++;//same
				}
			}
			else
			{
				int col = 0;
				while (limit != N)
				{
					int inc = 0;
					while (limit + inc < N)
						available_nbs[limit + inc++][left_cond_nb(i)][col] = 0;//i remove every number above the limit
					col++;//i go to the next col
					limit++;//same
				}
			}
		}
	}
}

/**
 * @brief
 * Apply every deterministic deduction that can be made directly from the
 * clues, before any guessing starts: eliminate impossible values on every
 * clued line/column, place the full ascending/descending run for clues
 * equal to N, place the tallest tower next to clues equal to 1, and place
 * it at the crossroads of opposite top/right clues that sum to N + 1.
 *
 * @param available_nbs The array of possible numbers
 * @param solution      The solution grid
 * @param clues         The array of clues
 */
void    put_towers_deduced(int available_nbs[N][N][N], int solution[N][N], int *clues)
{
	reduce_possibilities_from_clues(available_nbs, clues);
	for (int i = 0; i < N * 4; i++)
	{
		if (clues[i] == N)//if max clue found, put every tower in ascending order from the clue
			actualise_max_clue(i, available_nbs, solution);
		else if (clues[i] == 1)//if min clue found, put N close to the clue
			actualise_min_clue(i, available_nbs, solution);
		else if (i < N * 2)//if 2 opposites clues = N + 1, N is at the crossroads of both clues
			opposite_clues(i, available_nbs, solution, clues);
	}
}