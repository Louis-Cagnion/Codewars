#include "skyscraper.h"

int (*expe)[N];

/**
 * @brief
 * Parse a space-separated list of clues from a CLI argument.
 *
 * @param str   the raw argument string
 * @param clues Output: the parsed clues, filled in on success
 *
 * @return `true` if exactly `N * 4` valid numbers were parsed, else `false`
 */
bool parse_clues(char *str, int clues[N * 4])
{
    int count = 0;
    char *end;

    while (*str)
    {
        while (*str == ' ')
            str++;
        if (*str == '\0')
            break;
        int value = strtol(str, &end, 10);
        if (str == end || count >= N * 4)
            return 0; // caractere invalide ou trop de nombres
        clues[count] = value;
        count++;
        str = end;
    }
    return (count == N * 4);
}

/**
 * @brief
 * Entry point of the Skyscraper solver test program.
 *
 * This function runs predefined test cases for the Skyscraper puzzle solver.
 * For each test case:
 * 
 * - it calls `SolvePuzzle` with a set of `clues`
 * 
 * - compares the returned solution with the expected grid
 * 
 * - prints the result and highlights any difference
 *
 * After each test:
 * 
 * - allocated memory is freed
 * 
 * - global state (`clues_fullfilled`, `nbs_found`) is reset
 *
 * The program exits with status 0 after all tests are executed.
 *
 * @return 0 on normal execution
 */
int main(int ac, char **av)
{
	if (ac > 2)
		return fprintf(stderr, "usage: ./Skyscraper \"<%d clues>\"\n", N * 4);
	static int clues[][N * 4] = {
	  { 7, 0, 0, 0, 2, 2, 3,
		0, 0, 3, 0, 0, 0, 0,
		3, 0, 3, 0, 0, 5, 0,
		0, 0, 0, 0, 5, 0, 4 },
	  { 0, 0, 5, 0, 0, 0, 6,
		4, 0, 0, 2, 0, 2, 0,
		0, 5, 2, 0, 0, 0, 5,
		0, 3, 0, 5, 0, 0, 3 }
	};
	static int expected[][N][N] = {
		{{ 1, 5, 6, 7, 4, 3, 2 },
		 { 2, 7, 4, 5, 3, 1, 6 },
		 { 3, 4, 5, 6, 7, 2, 1 },
		 { 4, 6, 3, 1, 2, 7, 5 },
		 { 5, 3, 1, 2, 6, 4, 7 },
		 { 6, 2, 7, 3, 1, 5, 4 },
		 { 7, 1, 2, 4, 5, 6, 3 }},
		{{ 3, 4, 1, 7, 6, 5, 2 },
		 { 7, 1, 2, 5, 4, 6, 3 },
		 { 6, 3, 5, 2, 1, 7, 4 },
		 { 1, 2, 3, 6, 7, 4, 5 },
		 { 5, 7, 6, 4, 2, 3, 1 },
		 { 4, 5, 7, 1, 3, 2, 6 },
		 { 2, 6, 4, 3, 5, 1, 7 }}
	};
	int clues_cli[N * 4];
	
	if (ac == 2 && !parse_clues(av[1], clues_cli))
		return fprintf(stderr, "Erreur: %d nombres attendus pour les clues\n", N * 4);
	for (int i = 0; i < (ac == 2 ? 1 : 2); i++)
	{
		expe = expected[i];
		int *clue = (ac == 2 ? clues_cli : clues[i]), **result = SolvePuzzle(clue);
        if (ac == 2)
        {
			print_answer_array(result, result, clue);
            free_array2(result);
            break;
        }
		fprintf(stderr, CYAN UNDERLINE BOLD "Test %d :\n" RESET, i + 1);
		if (!result || !compare_solution(result, expe))
		{
			fprintf(stderr, RED "diff !\n" RESET);
			print_answer(result, wrapped_array(expe), clue);
			free_array2(result);
			break;
		}
		else
		{
			print_answer_array(result, wrapped_array(expe), clue);
			fprintf(stderr, GREEN "no diff ! congrats !\n" RESET);
		}
		fprintf(stderr, "\n");
		free_array2(result);
	}
	return (0);
}
