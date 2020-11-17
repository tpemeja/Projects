/**
 * @file utils.c
 */

/* Libraries */
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

/* Files */
#include "utils.h"

/**
 * @brief Retrieve all options given during the run
 * @param[in] argc number of arguments
 * @param[in] argv array of arguments
 * @return all arguments given during running shifted 
 */
int parse_opts(int argc, char *argv[]){

  int opt = 0;
  int option_index = 0;

  /**
   * @brief Structure that describes all options we allow
   * @param swap if the option 'o' is given, has no argument after
   * @param size_of_board if the option 'n' is given, argument is mandatory
   */
  static struct option long_options[] =
    { {"opening",no_argument, 0, 'o'}, {"size_of_board",required_argument,0,'n'},{0, 0, 0, 0} };

  /* Retrieve all options in arguments */
  while((opt = getopt_long(argc, argv, "n:o",
			   long_options, &option_index)) != -1){
      switch(opt){
	/* Size of board */
      case 'n':
	size_of_board = atoi(optarg);
	break;
	/* Swap */
      case 'o':
	opening = 1;
	break;
	/* Invalid option */
      default:
	printf("Error with options.\nTry 'project --help' for more information.\n");
	exit(EXIT_FAILURE);
      }
  }

  return argc - optind ;
}
