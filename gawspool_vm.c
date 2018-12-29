/* ------------------------------------------------------------------------ *
 * Program		:	gawspool_vm.c
 * Author		:	Gerard Wassink
 * Date			:	December 2018
 *
 * Function		:	Split jobs out of VMnder Hercules
 *
 * ------------------------------------------------------------------------ *
 * 						GNU LICENSE CONDITIONS
 * ------------------------------------------------------------------------ *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * ------------------------------------------------------------------------ *
 *				Copyright (C) 2018 Gerard Wassink
 * ------------------------------------------------------------------------ */

#include <stdio.h>
#include <string.h>

void logIt(char *);		/* our logging routine */
int logging = 0;		/* switch it on or off */

int main(int argc, char* argv[])
{

/*
 * Check number of arguments:
 * 1 Directory to write files to
 * 2 command to process files [optional]
 */
  if(argc != 2 && argc != 3)
  {
   printf("%s - a print spooler for 1403 printers\n", argv[0]);
   printf("    developed on VM sixpack 1.3 beta, by Gerard Wassink\n");
   printf("usage: %s {output_directory} [command]\n", argv[0]);
   return 0;
  }

  int num = 1;			/* Sequence number for output files */

  while (!feof(stdin))
  {

    char line[200];		/* input from VM printer */
    char cmd[225];		/* command to be executed, if present */
    if(argc == 3)
      snprintf(cmd, 225, "%s %s", argv[2], argv[1]);

    logIt("Starting\n"); /* and we're of */

/* ------------------------------------------------------------------------ *
 * define and open the output file for every job we encounter in the
 * output stream (determined by the end-of-file marker)
 * ------------------------------------------------------------------------ */
    FILE* jobfp;
    char path[250];
    snprintf(path, 250, "%s%s%i%s", argv[1], "job-", num, ".txt");
    jobfp = fopen(path, "w");

    int endFile = 0;		/* End of print job switch */

/* ------------------------------------------------------------------------ *
 * Read lines from the stream until we encounter the end-of-fie marker, 
 * Once we encounter that, print, exit the loop and close the file
 * ------------------------------------------------------------------------ */
    while(!endFile && !feof(stdin))	/* we there yet? */
    {
      fgets(line, 200, stdin);
      if (strstr(line, "---===### END OF PRINT JOB ###===---") != NULL)
        endFile = 1;

      if (!feof(stdin))
      {
        fprintf(jobfp, line);
      }
    }
    fclose(jobfp);		/* close output file */

    logIt("End of print file loop\n"); /* log it */

/* ------------------------------------------------------------------------ *
 * Check to see wether the optional command was specified
 * If so, execute it
 * ------------------------------------------------------------------------ */
    if(argc == 3)			/* command specified? */
    {
      logIt("Starting external command:\n");
      system(cmd);
    }

    logIt("Closing logfile\n");

    num++;			/* bump up the text file numer */
  }

/*
 * End of program, VM apparently shut down
 */

    logIt("End of program\n");

}


/* ------------------------------------------------------------------------ *
 * Logging routine for debugging purposes, switch on or off using the
 * 'logging' variable that will act like a boolean here
 * ------------------------------------------------------------------------ */
void logIt(char s[])
{
  if (logging)
  {
    FILE* logfp;			/* Define and open the log file */
    char logf[250];
    snprintf(logf, 250, "~/log.prt");
    logfp = fopen(logf, "a");

    fprintf(logfp, "gawspool_vm - %s\n", s);

    fclose(logfp);
  }
}
