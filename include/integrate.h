#ifndef INTEGRATE_H
#define INTEGRATE_H

/*! @file */

/*! Prints program usage */
void print_usage();

/*! Retrieves function pointer given system name */
func_ptr lookup_F(char * name);

/*! Retrieves dimensions given system name */
int lookup_n_vars(char * name);

#endif /* INTEGRATE_H */
