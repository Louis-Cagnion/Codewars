#include "skyscraper.h"

void	empty_box_coords(int **solution, int *line, int *col)
{
	for (*line = 0; *line < N; (*line)++)
	{
		for (*col = 0; *col < N; (*col)++)
			if (!solution[*line][*col])
				return ;
	}
	*col = *line = -1;
}

int highest_available(int available_nbs[N][N][N], int line, int col, int start)
{
	for (int nb = start; nb > 0; nb--)
		if (available_nbs[nb - 1][line][col])
			return available_nbs[nb - 1][line][col];
	return 0;
}

void sol_dup(int **solution_dup, int **solution)
{
	for (int line = 0; line < N; line++)
		for (int col = 0; col < N; col++)
			solution_dup[line][col] = solution[line][col];
}

void available_dup(int available_nbs_dup[N][N][N], int available_nbs[N][N][N])
{
	for (int nb = 0; nb < N; nb++)
	{
		for (int line = 0; line < N; line++)
			for (int col = 0; col < N; col++)
				available_nbs_dup[nb][line][col] = available_nbs[nb][line][col];
	}
}

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
