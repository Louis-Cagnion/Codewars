#ifndef SKYSCRAPER_H
# define SKYSCRAPER_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


//─────────────────────────────
// Defines
//─────────────────────────────

# define  N  7
extern int (*expe)[N];

# ifndef RESET
#  define RESET				"\033[0m"
# endif

/* Green text */
# ifndef GREEN
#  define GREEN				"\033[32m"
# endif

/* Bold text */
# ifndef BOLD
#  define BOLD				"\033[1m"
# endif

/* Underlined text */
# ifndef UNDERLINE
#  define UNDERLINE			"\033[4m"
# endif

/* Red text */
# ifndef RED
#  define RED				"\033[31m"
# endif


/* Cyan text */
# ifndef CYAN
#  define CYAN				"\033[36m"
# endif


/**
 * @enum Direction
 * @brief Reading directions for the Skyscraper puzzle
 * 
 * LTR = Left To Right
*/
/**
 * RTL = Right To Left
*/
/**
 * BTT = Bottom To Top
*/
/**
 * TTB = Top To Bottom
 */
typedef enum Direction
{
	LTR,	//Left To Right
	RTL,	//Right To Left
	BTT,	//Bottom To Top
	TTB		//Top To Bottom
}	Direction;

//main
int main(int ac, char **av);

//main function
int **SolvePuzzle(int *clues);

//─────────────────────────────
// Backtracking
//─────────────────────────────

bool	backtracking_solve(int available_nbs[N][N], int solution[N][N], int *clues, int depth);

//─────────────────────────────
// Backtracking Utils
//─────────────────────────────

bool	empty_box(int solution[N][N]);
void	sol_dup(int solution_dup[N][N], int solution[N][N]);
bool	clues_respected(int *clues, int solution[N][N]);
bool	prefix_respects_clues(int *clues, int solution[N][N]);
void	empty_box_coords(int solution[N][N], int available_nbs[N][N], int *line, int *col);
void	available_dup(int available_nbs_dup[N][N], int available_nbs[N][N]);
int		highest_available(int available_nbs[N][N], int line, int col, int start);

//─────────────────────────────
// Deduction
//─────────────────────────────

void    put_towers_deduced(int available_nbs[N][N], int solution[N][N], int *clues);
void	actualise_max_clue(int cur_clue, int available_nbs[N][N], int solution[N][N]);


//─────────────────────────────
// Actualise solution
//─────────────────────────────

void	set_valid_pos(int nb, int line, int col, int available_nbs[N][N], int solution[N][N]);

//─────────────────────────────
// Print
//─────────────────────────────

void	print_indices(int clues[N * 4]);
void	print_col(int **solution, int col);
void	print_line(int **solution, int line);
void	print_array(int array[N][N], int nb, int clues[N * 4]);
void	print_answer_array(int **array, int **wrapper_array, int clues[N * 4]);
void	print_answer(int **array, int **wrapper_array, int clues[N * 4]);
void	print_all_nb_arrays(int available_nbs[N][N], int clues[N * 4]);
void	print_all_available_each_box(int available_nbs[N][N], int clues[N * 4], int **solution);

//─────────────────────────────
// Utils
//─────────────────────────────

int		rev_nb(int pos);
int		top_cond_nb(int col);
int		**init_solution(void);
int		left_cond_nb(int line);
int		right_cond_nb(int line);
int		bottom_cond_nb(int col);
void	free_array2(int **arr2);
int		**wrapped_array(int static_array[N][N]);
void	init_availability(int available_nbs[N][N]);
bool	compare_solution(int **solution, int expected[N][N]);
int		visible_towers(Direction way, int line, int col, int solution[N][N]);
int		visible_towers_prefix(Direction way, int line, int col, int solution[N][N]);
int		prefix_length(Direction way, int line, int col, int solution[N][N]);
int		prefix_max(Direction way, int line, int col, int solution[N][N]);

#endif