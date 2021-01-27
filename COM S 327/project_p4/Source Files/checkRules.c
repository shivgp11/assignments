#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "check.h"

extern int line;
extern int turnNum;
extern char c;
extern int limit;
extern int found_limit;

int checkRules(FILE *fp)
{
	char rules[6];
	fgets(rules, 7, fp);
	if (strcmp(rules, "RULES:") != 0)
	{
		fprintf(stderr, "Expected 'RULES:' near line %d\n", line);
		return 0;
	}

	parse(fp);
	char turn[4];
	fgets(turn, 5, fp);
	if (strcmp(turn, "turn") != 0)
	{
		fprintf(stderr, "Expected 'turn 1 or 3' near line %d\n", line);
		return 0;
	}

	parse(fp);
	c = getc(fp);
	if (c != '1' && c != '3')
	{
		fprintf(stderr, "Expected '1' or '3' after 'turn' near line %d\n", line);
		return 0;
	}
	else
	{
		turnNum = c - '0';
	}

	parse(fp);
	c = fgetc(fp);
	ungetc(c, fp);
	if (c == 'u')
	{
		char lim[9];
		fgets(lim, 10, fp);
		if (strcmp(lim, "unlimited") != 0)
		{
			fprintf(stderr, "Expected 'unlimited' near line %d\n", line);
			return 0;
		}
		parse(fp);
	}
	else if (c == 'l')
	{
		char lim[5];
		fgets(lim, 6, fp);
		if (strcmp(lim, "limit") != 0)
		{
			fprintf(stderr, "Expected 'limit n' near line %d\n", line);
			return 0;
		}
		parse(fp);
		c = fgetc(fp);
		char d = fgetc(fp);
		ungetc(d, fp);
		if (c < 48 || c > 57)
		{
			fprintf(stderr, "Expected n between 0 and 9 near line %d\n", line);
			return 0;
		}
		else
		{
			found_limit = 1;
			limit = c - '0';
		}

		if (isspace(d) == 0)
		{
			fprintf(stderr, "Expected n between 0 and 9 near line %d\n", line);
			return 0;
		}
	}
	else
	{
		fprintf(stderr, "Expected 'Unlimited' or 'Limit n' near line %d\n", line);
		return 0;
	}
	return 1;
}