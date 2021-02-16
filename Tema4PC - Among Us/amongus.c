#include "utils.h"
#include <stdint.h>
#define MAX_DECODE_SIZE 8

void* (* Abilities[4])(void* x) = {RotateMatrix, DecodeString, InvertArray, KillPlayer};

char *fromEnumtoString(PlayerRoles playerRole)
{
	char *str = calloc(MAX_LEN_STR_ATR, sizeof(char));
	switch (playerRole)
	{
		case Rotator:
			str = strcpy(str, "Rotator");
			break;
		case Decoder:
			str = strcpy(str, "Decoder");
			break;
		case Invertor:
			str = strcpy(str, "Invertor");
			break;
		case Impostor:
			str = strcpy(str, "Impostor");
			break;
	}
	return str;
}

// Task 1
void *RotateMatrix(void *input)
{
	// TODO
	int n = *(int *)input;
	int i, j;
	int size;
	if (n < 100)
		size = 5 * n * n;
	else
		size = MAX_LEN_STR_OUT;

	char *output = malloc(size * sizeof(char));
	
	if (output == NULL)
		exit(101);
	output[0] = '\0';

	int len = 0;

	for (i = 1; i <= n; i++) {
		for(j = n; j >= 1; j--) {
			if (i < 10)
				len += sprintf(output + len, "%d ", j * 10 + i);
			else if (i < 100)
				len += sprintf(output + len, "%d ", j * 100 + i);
			else
				len += sprintf(output + len, "%d ", j * 1000 + i);
		}
		output[strlen(output) - 1] = '\n';
	}

	output[strlen(output) - 1] = '\0';
	return output;
}

// Task 2
void *DecodeString(void *input)
{
	// TODO
	char *string = (char *)input;
	int sum = 0;
	char *ai;

	ai = strtok(string, "_");
	
	while (ai != NULL) {
		// se separa dupa "_"
		sum += atoi(ai);
		ai = strtok(NULL, "_");
	}

	char *output = malloc(MAX_DECODE_SIZE * sizeof(char));

	if (output == NULL)
		exit(201);
	sprintf(output, "%d", sum);

	return output;
}

//Task 3
void *InvertArray(void *input)
{
	// TODO
	int *arr = (int *)input;
	int i, len = 0;

	char *output = calloc(MAX_LEN_STR_ATR, sizeof(char));

	if (output == NULL)
		exit(301);
	output[0] = '\0';

	if (arr[0] % 2 == 0) {
		for (i = 1; i < arr[0]; i+= 2)
			len += sprintf(output + len, "%d %d ", arr[i + 1], arr[i]);
	}

	else {
		for (i = arr[0]; i > 0; i--)
			len += sprintf(output + len, "%d ", arr[i]);
	}

	output[strlen(output) - 1] = '\0';

	return output;
}

//Task 4

Player *allocPlayer()
{
	// TODO

	Player *p1 = malloc(sizeof(Player));

	if (p1 == NULL)
		exit(401);

	p1->name = calloc(MAX_LEN_STR_ATR, sizeof(char));

	if (p1->name == NULL)
		exit(402);

	p1->color = calloc(MAX_LEN_STR_ATR, sizeof(char));

	if (p1->color == NULL)
		exit(403);

	p1->hat = calloc(MAX_LEN_STR_ATR, sizeof(char));

	if (p1->hat == NULL)
		exit(404);

	p1->alive = 1;
	p1->indexOfLocation = 0;

	return p1;
}

//Task 4
Game *allocGame()
{
	// TODO
	Game *p2 = malloc(sizeof(Game));

	if (p2 == NULL)
		exit(405);

	p2->name = calloc(MAX_LEN_STR_ATR, sizeof(char));

	if (p2->name == NULL)
		exit(406);

	return p2;
}
//Task 5

Player *ReadPlayer(FILE *inputFile)
{
	// TODO
	Player *p1 = allocPlayer();
	char *buffer = calloc(MAX_LEN_STR_ATR, sizeof(char));
	
	if (buffer == NULL)
		exit(501);

	char *role = calloc(MAX_LEN_STR_ATR, sizeof(char));

	if (role == NULL)
		exit(502);

	int i = 0;

	fscanf(inputFile, "%s", p1->name);
	fscanf(inputFile, "%s", p1->color);
	fscanf(inputFile, "%s", p1->hat);
	fscanf(inputFile, "%d", &p1->numberOfLocations);

	p1->locations = calloc(p1->numberOfLocations, sizeof(Location));
	if (p1->locations == NULL)
		exit(501);

	for (i = 0; i < p1->numberOfLocations; i++) {
		fscanf(inputFile, "%s", buffer);
		sscanf(buffer, "(%d,%d)", &p1->locations[i].x, &p1->locations[i].y);
	}
	
	free(buffer);

	fscanf(inputFile, "%s", role);

	if (strcmp(role, "Rotator") == 0) {
		p1->playerRole = 0;
		p1->ability = &RotateMatrix;
	}
	else if (strcmp(role, "Decoder") == 0) {
		p1->playerRole = 1;
		p1->ability = &DecodeString;
	}
	else if (strcmp(role, "Invertor") == 0) {
		p1->playerRole = 2;
		p1->ability = &InvertArray;
	}
	else {
		p1->playerRole = 3;
		p1->ability = &KillPlayer;
	}
	free(role);

	return p1;
}

// Task 5
Game *ReadGame(FILE *inputFile)
{
	// TODO
	Game *p2 = allocGame();
	int i;
	fscanf(inputFile, "%s", p2->name);
	fscanf(inputFile, "%d", &p2->killRange);
	fscanf(inputFile, "%d", &p2->numberOfCrewmates);

	p2->crewmates = malloc(p2->numberOfCrewmates * sizeof(Player));
	
	if (p2->crewmates == NULL)
		exit(503);

	for (i = 0; i < p2->numberOfCrewmates; i++)
		p2->crewmates[i] = ReadPlayer(inputFile);

	p2->impostor = ReadPlayer(inputFile);
	return p2;
}

// Task 6
void WritePlayer(Player *player, FILE *outputFile)
{
	// TODO
	int i;
	char *role = fromEnumtoString(player->playerRole);
	fprintf(outputFile,
	"Player %s with color %s, hat %s and role %s has entered the game.\n", 
	player->name, player->color, player->hat, role);
	free(role);
	fprintf(outputFile, "Player's locations: ");

	for (i = 0; i < player->numberOfLocations; i++)
		fprintf(outputFile, "(%d,%d) ", player->locations[i].x,
				player->locations[i].y);
	fprintf(outputFile, "\n");
	
	return;
}

// Task 6
void WriteGame(Game *game, FILE *outputFile)
{
	// TODO
	int i;
	fprintf(outputFile, "Game %s has just started!\n", game->name);
	fprintf(outputFile, "\tGame options:\n");
	fprintf(outputFile, "Kill Range: %d\n", game->killRange);
	fprintf(outputFile, "Number of crewmates: %d\n", game->numberOfCrewmates);
	fprintf(outputFile, "\n");
	fprintf(outputFile, "\tCrewmates:\n");

	for (i = 0; i < game->numberOfCrewmates; i++)
		WritePlayer(game->crewmates[i], outputFile);
	fprintf(outputFile, "\n");
	
	fprintf(outputFile, "\tImpostor:\n");
	WritePlayer(game->impostor, outputFile);
	return;
}

//Task 7

void *KillPlayer(void *input)
{
	// TODO
	Game *game = (Game *)input;
	Player *imp = game->impostor;
	char *output = malloc(MAX_LEN_STR_ATR * sizeof(char));
	if (output == NULL)
		exit(701);
	// saving the impostor's coord.
	int xi, yi;
	xi = imp->locations[imp->indexOfLocation].x;
	yi = imp->locations[imp->indexOfLocation].y;

	// finding the closest player
	// which can be killed
	int dist, xc, yc;
	int min, i, ok = 0, pos;
	min = game->killRange;

	for (i = 0; i < game->numberOfCrewmates; i++) {
		Player *crew = game->crewmates[i];
		if (crew->alive == 1) {
			xc = crew->locations[crew->indexOfLocation].x;
			yc = crew->locations[crew->indexOfLocation].y;
			// calculating the distance between imp and player
			dist = abs(xi - xc) + abs(yi - yc);

			if (dist <= min) {
				ok = 1;
				min = dist;
				pos = i;
			}
		}
	}

	if (ok == 0)
		sprintf(output, "Impostor %s couldn't kill anybody.", imp->name);

	else {
		Player *rip = game->crewmates[pos];
		rip->alive = 0;
		sprintf(output, 
				"Impostor %s has just killed crewmate %s from distance %d.",
				imp->name, rip->name, min);
	}
	
	return (void *)output;
}

// Task 8

void CalcuateNextCycleOfGame(Game *game, FILE *outputFile, void **inputMatrix)
{
	// TODO
	int i, x, y;
    for (i = 0; i < game->numberOfCrewmates; i++) {
		Player *crew = game->crewmates[i];
		if (crew->alive == 1) {
			if (crew->indexOfLocation < crew->numberOfLocations - 1)
				crew->indexOfLocation++;
			else
				crew->indexOfLocation = 0;

			x = crew->locations[crew->indexOfLocation].x;
			y = crew->locations[crew->indexOfLocation].y;

			fprintf(outputFile, "Crewmate %s went to location (%d,%d).\n",
					crew->name, x, y);
			
			fprintf(outputFile, "Crewmate %s's output:\n", crew->name);
			void *input = inputMatrix[i];
			char *output = (char *)crew->ability(input);
			fprintf(outputFile, "%s\n", output);
			free(output);
		}
		else
			fprintf(outputFile, "Crewmate %s is dead.\n", crew->name);
	}
	Player *imp = game->impostor;
	if (imp->indexOfLocation < imp->numberOfLocations - 1)
		imp->indexOfLocation++;
	else
		imp->indexOfLocation = 0;

	x = imp->locations[imp->indexOfLocation].x;
	y = imp->locations[imp->indexOfLocation].y;

	fprintf(outputFile, "Impostor %s went to location (%d,%d).\n",
			imp->name, x, y);
	fprintf(outputFile, "Impostor %s's output:\n", imp->name);
	char *output = (char *)imp->ability((void *)game);
	fprintf(outputFile, "%s\n", output);
	free(output);
	return;
}

// Task 9
void FreePlayer(Player *player)
{
	// TODO
	free(player->name);
	free(player->color);
	free(player->hat);
	free(player->locations);
	free(player);

	return;
}

// Task 9
void FreeGame(Game *game)
{
	// TODO
	int i;
	for (i = 0; i < game->numberOfCrewmates; i++)
		FreePlayer(game->crewmates[i]);
	free(game->crewmates);
	free(game->name);
	FreePlayer(game->impostor);
	free(game);
	
	return;
}