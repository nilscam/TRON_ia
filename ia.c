#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct s_search {
	int x;
	int y;
	int id;
	struct s_search *next;
} searcher;

typedef struct head_list {
	int x;
	int y;
	int id;
	struct head_list *next;
} head_list;


char **fill_map(char **, head_list *, int, int, int);
void  play_best_move(char **, head_list *, int);

void	print_map(char **map)
{
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 30; x++) {
			if (map[y][x] == 42)
				fprintf(stderr, "  ");
			else
				fprintf(stderr, " %d", map[y][x]);
		}
		fprintf(stderr, "\n");
	}
	fprintf(stderr, "\n");
}

void  free_head_list(head_list *heads)
{
	if (heads) {
		free_head_list(heads->next);
		free(heads);
	}
}

char **create_map()
{
	char **map = malloc(sizeof(char*) * 20);

	for (int i = 0; i < 20; i++) {
		map[i] = malloc(30);
		for (int j = 0; j < 30; j++) {
			map[i][j] = 0;
		}
	}
	return map;
}

void  free_map(char **map)
{
	for (int i = 0; i < 20; i++) {
		free(map[i]);
	}
	free(map);
}

char **dup_map(char **map) {
	char **newmap = malloc(sizeof(char*) * 20);

	for (int y = 0; y < 20; y++) {
		newmap[y] = malloc(30);
		strcpy(newmap[y], map[y]);
	}
	return newmap;
}

// replace case with id by 99
char **dup_map_abstract(char **map) {
	char **newmap = malloc(sizeof(char*) * 20);

	for (int y = 0; y < 20; y++) {
		newmap[y] = malloc(30);
		memset(newmap[y], 0, 30);
		for (int x = 0; x < 30; x++) {
			if (map[y][x] != 0) {
				newmap[y][x] = 42;
			}
		}
	}
	return newmap;
}

void  add_move(int id_player, int x1, int y1, char **map)
{
	map[y1][x1] = id_player;
}

head_list  *push_head(head_list *heads, int x, int y, int id)
{
	head_list *new_head = malloc(sizeof(head_list));

	new_head->x = x;
	new_head->y = y;
	new_head->id = id;
	new_head->next = heads;
	return new_head;
}

void	remove_dead_player(char **map, int id)
{
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 30; x++) {
			if (map[y][x] == id)
				map[y][x] = 0;
		}
	}
}

int main()
{
	char  **map = create_map(map);
	int toto = 0;

	while (1) {
		int N;
		int P;
		head_list *heads = NULL;

		scanf("%d%d", &N, &P);
		P += 1;
		int MX1;
		int MY1;
		for (int i = 0; i < N; i++) {
			int X0;
			int Y0;
			int X1;
			int Y1;
			scanf("%d%d%d%d", &X0, &Y0, &X1, &Y1);
			if (X0 == -1)
				remove_dead_player(map, i + 1);
			else {
				add_move(i+1, X0, Y0, map);
				add_move(i+1, X1, Y1, map);
				if (i != P - 1)
					heads = push_head(heads, X1, Y1, i + 1);
				else {
					MX1 = X1;
					MY1 = Y1;
				}
			}
		}
		heads = push_head(heads, MX1, MY1, P);

		play_best_move(map, heads, P);
	}

	return 0;
}

void  free_searcher(searcher *search) {
	if (search) {
		if (search->next)
			free_searcher(search->next);
		free(search);
	}
}

searcher  *push_new_searcher(searcher *search, int x, int y, int id)
{
	searcher *newsearcher = malloc(sizeof(struct s_search));

	newsearcher->x = x;
	newsearcher->y = y;
	newsearcher->id = id;
	newsearcher->next = search;
	return newsearcher;
}

int count_searchers(searcher *search)
{
	if (search != NULL) {
		return count_searchers(search->next) + 1;
	}
	return 0;
}

#define TRY_PROP(x, y) ({ if (x >= 0 && y >= 0 && x < 30 && y < 20 && map[y][x] == 0) {	\
				newsearch = push_new_searcher(newsearch, x, y, tmp->id); \
				map[y][x] = tmp->id;			\
			}})

void  fill_map_s(char **map, searcher *search)
{
	searcher *newsearch = NULL;
	int i = 0;

	for (searcher *tmp = search; tmp; tmp = tmp->next) {

		for (int dir = 0; dir < 4; dir++) {
			switch (dir)
			{
			case 0:
				TRY_PROP(tmp->x - 1, tmp->y);
				break;
			case 1:
				TRY_PROP(tmp->x, tmp->y - 1);
				break;
			case 2:
				TRY_PROP(tmp->x + 1, tmp->y);
				break;
			case 3:
				TRY_PROP(tmp->x, tmp->y + 1);
				break;
			default:
				break;
			}
		}
		++i;
	}
	free_searcher(search);
	if (newsearch)
		fill_map_s(map, newsearch);
}

char **fill_map(char **cur_map, head_list *heads, int xme, int yme, int idme)
{
	searcher *search = NULL;
	char **newmap = dup_map_abstract(cur_map);

	for (head_list *tmp = heads; tmp; tmp = tmp->next) {
		if (idme == tmp->id) {
			search = push_new_searcher(search, xme, yme, tmp->id);
			newmap[yme][xme] = tmp->id;
		} else {
			search = push_new_searcher(search, tmp->x, tmp->y, tmp->id);
			newmap[tmp->y][tmp->x] = tmp->id;
		}
	}
	fill_map_s(newmap, search);
	return newmap;
}



int count_nb(char **map, int id)
{
	int result = 0;

	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 30; x++) {
			if (map[y][x] == id)
				result += 1;
		}
	}
	return result;
}

int eval(char **map, int x, int y, head_list *players, int my_id)
{
	char **filled_map;
	int evaluation;

	if (x < 0 || y < 0 || x >= 30 || y >= 20 || map[y][x] != 0)
		return 0;
	filled_map = fill_map(map, players, x, y, my_id);
	print_map(filled_map);
	evaluation = count_nb(filled_map, my_id);
	return evaluation;
}

#define TEST_MOVE(x, y, direction) ({ tmp = eval(map, x, y, players, players->id); \
			fprintf(stderr, "count eval for %s = %d\n", direction, tmp); \
			if (tmp > best) { dir = i; best = tmp; }})

void  play_best_move(char **map, head_list *players, int id)
{
	int dir = 1;
	int best = 0;
	int tmp;
	clock_t	start = clock();

	fprintf(stderr, "computing\n");
	for (int i = 0; i < 4; i++) {
		switch (i)
		{
		case 0:
			TEST_MOVE(players->x - 1, players->y, "LEFT");
			break;
		case 1:
			TEST_MOVE(players->x, players->y - 1, "UP");
			break;
		case 2:
			TEST_MOVE(players->x + 1, players->y, "RIGHT");
			break;
		case 3:
			TEST_MOVE(players->x, players->y + 1, "DOWN");
			break;
		default:
			break;
		}
	}
	switch (dir)
	{
	case 0:
		printf("LEFT\n");
		break;
	case 1:
		printf("UP\n");
		break;
	case 2:
		printf("RIGHT\n");
		break;
	case 3:
		printf("DOWN\n");
		break;
	default:
		break;
	}
	fprintf(stderr, "computed in %.3fms\n", (clock() - start) / CLOCKS_PER_SEC);
}
