#include "skyscraper.h"

/**
 * @brief
 * Print the solver's result grid, surrounded by the clues.
 *
 * Each cell is colorized green if it matches `wrapper_array` at the same
 * position, red otherwise. Prints "(null)" instead of a grid if `array` is
 * NULL or empty.
 *
 * @param array           the solution returned by the solver
 * @param wrapper_array   a wrapped 2D array to compare each cell against
 * @param clues           the array of clues surrounding the board
 */
void print_answer_array(int **array, int **wrapper_array, int clues[N * 4])
{
	fprintf(stderr, CYAN UNDERLINE"got :\n"RESET);
	if (!array || !array[0])
	{
		fprintf(stderr, "(null)\n");
		return ;
	}
	fprintf(stderr, "\n   ");
	for(int j = 0; j < N; j++)
	{
		if (clues[j])
			fprintf(stderr, " %d  ", clues[j]);
		else
			fprintf(stderr, "    ");
		
	}
	int len_bar = (4 * N + 1);
	char bar[(4 * N + 1) + 1] = {0};
	for (int i = 0; i < len_bar; i++)
		bar[i] = '-';
	fprintf(stderr, "\n  %s\n", bar);
	for (int i = N - 1; i >= 0; i--)
	{
		if (clues[N * 3 + i])
			fprintf(stderr, "%d ", clues[N * 3 + i]);
		else
			fprintf(stderr, "  ");
		fprintf(stderr, "|");
		for(int j = 0; j < N; j++)
		{
			if (array[rev_nb(i)][j] == wrapper_array[rev_nb(i)][j])
				fprintf(stderr, " "GREEN"%d"RESET" |", array[rev_nb(i)][j]);
			else
				fprintf(stderr, " "RED"%d"RESET" |", array[rev_nb(i)][j]);
		}
		if (clues[N + (rev_nb(i))])
		fprintf(stderr, " %d", clues[N + (rev_nb(i))]);
		else
			fprintf(stderr, "  ");
		fprintf(stderr, "\n  %s\n", bar);
	}
	fprintf(stderr, "   ");
	for(int j = N - 1; j >= 0; j--)
	{
		if (clues[N * 2 + j])
			fprintf(stderr, " %d  ", clues[N * 2 + j]);
		else
			fprintf(stderr, "    ");
		
	}
	fprintf(stderr, "\n\n");
}

/**
 * @brief
 * Display the expected solution and the computed solution side by side.
 *
 * This function prints two boards:
 * 
 * - the expected solution (`wrapper_array`)
 * 
 * - the solver result (`array`)
 *
 * Each cell is colorized:
 * 
 * - green if the value matches the expected one
 * 
 * - red if the value differs
 *
 * The board is displayed with the surrounding `clues` to ease debugging.
 *
 * @param array           the solution returned by the solver
 * @param wrapper_array   a wrapped 2D array containing the expected solution
 * @param clues           the array of clues surrounding the board
 */
void	print_answer(int **array, int **wrapper_array, int clues[N * 4])
{
	//print wrapper_array
	fprintf(stderr, CYAN UNDERLINE"should be :\n"RESET);
	fprintf(stderr, "\n   ");
	for(int j = 0; j < N; j++)
	{
		if (clues[j])
			fprintf(stderr, " %d  ", clues[j]);
		else
			fprintf(stderr, "    ");
		
	}
	int len_bar = (4 * N + 1);
	char bar[(4 * N + 1) + 1] = {0};
	for (int i = 0; i < len_bar; i++)
		bar[i] = '-';
	fprintf(stderr, "\n  %s\n", bar);
	for (int i = N - 1; i >= 0; i--)
	{
		if (clues[N * 3 + i])
			fprintf(stderr, "%d ", clues[N * 3 + i]);
		else
			fprintf(stderr, "  ");
		fprintf(stderr, "|");
		for(int j = 0; j < N; j++)
			fprintf(stderr, " %d |", wrapper_array[rev_nb(i)][j]);
		if (clues[N + (rev_nb(i))])
		fprintf(stderr, " %d", clues[N + (rev_nb(i))]);
		else
			fprintf(stderr, "  ");
		fprintf(stderr, "\n  %s\n", bar);
	}
	fprintf(stderr, "   ");
	for(int j = N - 1; j >= 0; j--)
	{
		if (clues[N * 2 + j])
			fprintf(stderr, " %d  ", clues[N * 2 + j]);
		else
			fprintf(stderr, "    ");
		
	}
	fprintf(stderr, "\n\n");
	//print array
	print_answer_array(array, wrapper_array, clues);
}

/**
 * @brief
 * Print an empty board showing only the clue indices.
 *
 * This function displays the board layout with all `clues`
 * but without any numbers inside the grid.
 *
 * It is useful to visualize clue placement independently
 * from the solution.
 *
 * @param clues   the array of clues
 */
void	print_indices(int clues[N * 4])
{
	fprintf(stderr, "\n   ");
	for(int j = 0; j < N; j++)
	{
		if (clues[j])
			fprintf(stderr, " %d  ", clues[j]);
		else
			fprintf(stderr, "    ");
		
	}
	int len_bar = (8 * N + 1);
	char bar[(8 * N + 1) + 1] = {0};
	for (int i = 0; i < len_bar; i++)
		bar[i] = '-';
	fprintf(stderr, "\n  %s\n", bar);
	for (int i = N - 1; i >= 0; i--)
	{
		if (clues[N * 3 + i])
			fprintf(stderr, "%d ", clues[N * 3 + i]);
		else
			fprintf(stderr, "  ");
		fprintf(stderr, "|");
		for(int j = 0; j < N; j++)
			fprintf(stderr, "   |");
		if (clues[N + (rev_nb(i))])
		fprintf(stderr, " %d", clues[N + (rev_nb(i))]);
		else
			fprintf(stderr, "  ");
		fprintf(stderr, "\n  %s\n", bar);
	}
	fprintf(stderr, "   ");
	for(int j = N - 1; j >= 0; j--)
	{
		if (clues[N * 2 + j])
			fprintf(stderr, " %d  ", clues[N * 2 + j]);
		else
			fprintf(stderr, "    ");
		
	}
	fprintf(stderr, "\n");
}

/**
 * @brief
 * Print a 2D array representing a grid, including its surrounding clues.
 *
 * This function displays:
 * 
 * - the grid values
 * 
 * - the top, bottom, left and right clues
 * 
 * - handles NULL arrays safely
 *
 * @param array   The 2D array to print
 * @param nb      The index of the number array (used for labeling)
 * @param clues   The array of clues
 */
void	print_array(int array[N][N], int nb, int clues[N * 4])
{
	if (!array || !array[0])
	{
		fprintf(stderr, "array of %d's :\n", nb + 1);
		fprintf(stderr, "(null)\n");
		return ;
	}
	//print wrapper_array
	fprintf(stderr, "array of %d's :\n", nb + 1);
	fprintf(stderr, "\n   ");
	for(int j = 0; j < N; j++)
	{
		if (clues[j])
			fprintf(stderr, " %d  ", clues[j]);
		else
			fprintf(stderr, "    ");
		
	}
	int len_bar = (8 * N + 1);
	char bar[(8 * N + 1) + 1] = {0};
	for (int i = 0; i < len_bar; i++)
		bar[i] = '-';
	fprintf(stderr, "\n  %s\n", bar);
	for (int i = N - 1; i >= 0; i--)
	{
		if (clues[N * 3 + i])
			fprintf(stderr, "%d ", clues[N * 3 + i]);
		else
			fprintf(stderr, "  ");
		fprintf(stderr, "|");
		for(int j = 0; j < N; j++)
		{
			if (array[(rev_nb(i))][j])
				fprintf(stderr, " %d |", array[(rev_nb(i))][j]);
			else
				fprintf(stderr, "   |");
		}
		if (clues[N + (rev_nb(i))])
			fprintf(stderr, " %d", clues[N + (rev_nb(i))]);
		else
			fprintf(stderr, "  ");
		fprintf(stderr, "\n  %s\n", bar);
	}
	fprintf(stderr, "   ");
	for(int j = N - 1; j >= 0; j--)
	{
		if (clues[N * 2 + j])
			fprintf(stderr, " %d  ", clues[N * 2 + j]);
		else
			fprintf(stderr, "    ");
		
	}
	fprintf(stderr, "\n");
}

/**
 * @brief
 * Print all available numbers for each box of the grid.
 *
 * Displays, for every cell:
 * 
 * - possible values if the cell is empty
 * 
 * - the fixed value if the solution already contains one
 * 
 * - surrounding clues for better visualization
 *
 * Useful for debugging the solving process.
 *
 * @param available_nbs   the array of possible numbers
 * @param clues           The array of clues
 * @param solution        The current solution grid
 */
void	print_all_available_each_box(int available_nbs[N][N][N], int clues[N * 4], int **solution)
{
	if (!solution || !available_nbs || !available_nbs[0])//can't print without solution or available nbs
	{
		fprintf(stderr, "%s is null\n", !solution ? "solution" : "available_nbs");
		return ;
	}
	int i = 0, j = 0, k = -1, clue, possibility;

	fprintf(stderr, "all nbs available :\n\n      ");
	while (i < N)//print top conditions
	{
		if ((clue = clues[top_cond_nb(i)]))//if exist
			fprintf(stderr, "  %d  ", clue);
		else
			fprintf(stderr, " N/A ");//doesn't exist
		fprintf(stderr, "   ");
		i++;
	}
	int len_bar = (8 * N + 1);
	char bar[(8 * N + 1) + 1] = {0};
	for (int i = 0; i < len_bar; i++)
		bar[i] = '-';
	fprintf(stderr, "\n    %s\n", bar);//print separation
	for (i = 0; i < N; i++)//print possibilities
	{
		fprintf(stderr, "    |");
		for (k = 0; k < N; k++)//print 1, 2 or 3
		{
			for (j = 0; j < 3; j++)
			{
				if (!solution[i][k] && j < N && (possibility = available_nbs[j][i][k]))//if no solution and 1,2 or 3 is available
					fprintf(stderr, " %d", possibility);//i print
				else
					fprintf(stderr, "  ");//else, blank
			}
			fprintf(stderr, " |");
		}
		fprintf(stderr, "\n");
		if ((clue = clues[left_cond_nb(i)]))//print left cond if it exist
			fprintf(stderr, " %d  |", clue);
		else
			fprintf(stderr, "N/A |");//else N/A
		for (k = 0; k < N; k++)
		{
			for (j = 3; j < 6; j++)//print 4, 5 or 6
			{
				if (solution[i][k])//if there's a solution, i print it
				{
					possibility = expe[i][k];
					char *color = possibility == solution[i][k] ? GREEN : RED;
					fprintf(stderr, "%s   %d  "RESET, color, solution[i][k]);
					break ;
				}	
				if (j < N && (possibility = available_nbs[j][i][k]))//else if 4, 5 or 6 is available
					fprintf(stderr, " %d", possibility);//i print
				else
					fprintf(stderr, "  ");//else, blank
			}
			fprintf(stderr, " |");
		}
		if ((clue = clues[i + N]))
			fprintf(stderr, "  %d", clue);//print right cond if it exist
		else
			fprintf(stderr, " N/A ");//else N/A
		fprintf(stderr, "\n    |");
		for (k = 0; k < N; k++)
		{
			for (j = 6; j < 9; j++)
			{
				if (!solution[i][k] && j < N && (possibility = available_nbs[j][i][k]))//if 7, 8 or 9 is available
					fprintf(stderr, " %d", possibility);//i print
				else
					fprintf(stderr, "  ");//else, blank
			}
			fprintf(stderr, " |");
		}
		fprintf(stderr, "\n    %s\n", bar);//print new separation ofr next line
	}
	fprintf(stderr, "      ");
	for(j = 0; j < N; j++)//print bottom conds
	{
		if ((clue = clues[bottom_cond_nb(j)]))//if a clue exist, i print
			fprintf(stderr, "  %d  ", clue);
		else
			fprintf(stderr, " N/A ");//else, blank
		fprintf(stderr, "   ");
		
	}
	fprintf(stderr, "\n\n");
}

/**
 * @brief
 * Print all available-number arrays.
 *
 * Iterates over each number possibility array and prints it
 * using print_array().
 *
 * This allows visualization of constraints per number.
 *
 * @param available_nbs   the array of possible numbers
 * @param clues           The array of clues
 */
void	print_all_nb_arrays(int available_nbs[N][N][N], int clues[N * 4])
{
	for (int nb = 0; nb < N; nb++)
		print_array(available_nbs[nb], nb, clues);
}

/**
 * @brief
 * Print a column
 * 
 * @param solution The answer sheet
 * @param col The column to print
 */
void print_col(int **solution, int col)
{
	fprintf(stderr, "col %d:\n", col + 1);
	for (int line = 0; line < N; line++)
		fprintf(stderr, "|%d|\n", solution[line][col]);
}

/**
 * @brief
 * Print a line
 * 
 * @param solution The answer sheet
 * @param line The line to print
 */
void print_line(int **solution, int line)
{
	fprintf(stderr, "line %d:\n", line + 1);
	fprintf(stderr, "--------------\n");
	for (int col = 0; col < N; col++)
		fprintf(stderr, "%d \n", solution[line][col]);
	fprintf(stderr, "--------------\n");
}
