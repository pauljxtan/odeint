/* Integrates a system of (coupled) ODEs using
 * the classical Runge-Kutta method. */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include "bulsto.h"
#include "eoms.h"
#include "fweuler.h"
#include "integrate.h"
#include "rk4.h"

/* TODO:
 * Include "interactive mode" for choosing system and entering parameter values
 * Add delta to user arguments
 */

/* Integrate the selected system */
int main(int argc, char * argv[]) {
    //char method[sizeof(argv[1]) / sizeof(argv[1][0])];
    char method[10];
    //char name[sizeof(argv[2]) / sizeof(argv[2][0])];
    char name[20];
    int n_vars;
    double dt;
    double t0;
    double * X0 = NULL;
    double delta;
    int n_steps;
    int verbose = 0;
    int print_params = 0;
    int write = 0;
    //char outfile[sizeof(argv[1]) / sizeof(argv[1][0]) + 4];
    char outfile[20];
    FILE * poutfile = NULL;
    int c;
    int i = 0;

    if (argc < 2) {
        printf("\nAvailable systems to integrate are:\n");
        printf(system_list);
        print_usage();
        printf("\n");
        return EXIT_SUCCESS;
    }

    /* Choose integration method */
    strcpy(method, argv[1]);

    /* Choose system to integrate */
    strcpy(name, argv[2]);
    n_vars = lookup_n_vars(name);
    X0 = malloc(n_vars * sizeof(double));
    strcpy(outfile, argv[2]);
    strcat(outfile, ".dat");

    /* Parse arguments */
    opterr = 0;
    while ((c = getopt(argc, argv, "d:t:x:n:e:vyw")) != -1)
        switch (c) {
            case 'd':
                dt = atof(optarg);
                break;
            case 't':
                t0 = atof(optarg);
                break;
            case 'x':
                if (i < n_vars)
                    X0[i++] = atof(optarg);
                break;
            case 'n':
                n_steps = atoi(optarg);
                break;
            case 'e':
                delta = atof(optarg);
            case 'v':
                verbose = 1;
                break;
            case 'y':
                print_params = 1;
            case 'w':
                write = 1;
                break;
            default:
                print_usage();
                return -1;
        }

    if (i < n_vars) {
        fprintf(stderr, "Initial state should be specified for %d variables "
                "(only %d given)\n", n_vars, i);
        return EXIT_FAILURE;
    }
    
    if (print_params) {
        printf("using: %s\n", method);
        printf("integrating: %s\n", name);
        printf("n_vars = %d\n", n_vars);
        printf("dt = %f\n", dt);
        printf("t0 = %f\n", t0);
        for (i = 0; i < n_vars; i++) {
            printf("X0[%d] = %f\n", i, X0[i]);
        }
        printf("n_steps = %d\n", n_steps);
        printf("verbose = %s\n", verbose ? "yes" : "no");
        printf("write = %s\n", write ? "yes" : "no");
        printf("outfile = %s\n", outfile);
    }

    poutfile = fopen(outfile, "w");

    /* Do integration */
    if (strcmp("rk4", method) == 0) {
        rk4 * prk4 = rk4_new(n_vars, dt, t0, X0, lookup_F(name), verbose, write, poutfile);
        rk4_integrate(prk4, n_steps);
        fclose(poutfile);
    }
    else if (strcmp("fweuler", method) == 0) { 
        fweuler * pfweuler = fweuler_new(n_vars, dt, t0, X0, lookup_F(name), verbose, write, poutfile);
        fweuler_integrate(pfweuler, n_steps);
    }
    else if (strcmp("bulsto", method) == 0) { 
        //delta = 1e-6;
        bulsto * pbulsto = bulsto_new(n_vars, dt, t0, X0, lookup_F(name), delta, verbose, write, poutfile);
        bulsto_integrate(pbulsto, n_steps);
    }

    return EXIT_SUCCESS;
}

void print_usage() {
    printf("Usage: integrate method name -d num -t num -x num [-x num]... -n num [-e num] [-v] [-y] [-w]\n");
}

func_ptr lookup_F(char * name) {
    function_table * ptable;
    for (ptable = func_table; ptable->name != NULL; ptable++)
    {
        if (strcmp(ptable->name, name) == 0)
            return ptable->F;
    }
    fprintf(stderr, "Invalid or no function specified\n");
    print_usage();
    return EXIT_FAILURE;
}

int lookup_n_vars(char * name) {
    function_table *ptable;
    for (ptable = func_table; ptable->name != NULL; ptable++)
    {
        if (strcmp(ptable->name, name) == 0)
            return ptable->n_vars;
    }
    fprintf(stderr, "Invalid or no function specified\n");
    print_usage();
    return EXIT_FAILURE;
}
