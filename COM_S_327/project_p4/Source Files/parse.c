#include <stdio.h>
#include "check.h"

extern int line;
extern char c;

void parse(FILE *fp)
{
	c = fgetc(fp);
	while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '#' == c)
	{
		while ('#' == c)
		{
			for (;;)
			{
				c = fgetc(fp);
				if ('\n' == c)
				{
					break;
				}
			}
		}
		if ('\n' == c)
		{
			line++;
		}
		c = fgetc(fp);
		if (EOF == c)
		{
			return;
		}
	}
	ungetc(c, fp);
}