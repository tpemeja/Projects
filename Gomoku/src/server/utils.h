/**
 * @file utils.h
 */

#ifndef UTILS_H
#define UTILS_H

/*Indicate if the swap option is true or not, default : no*/
extern int opening;

/*Indicate the size of the board, default : 7*/
extern size_t size_of_board;

/**
 * \brief Retrieve the args during the run
 * \param argc number of args
 * \param *argv[] array of args
 * \return The number of mandatory arguments (dynamic libraries)
 */
int parse_opts(int argc, char *argv[]);

#endif
