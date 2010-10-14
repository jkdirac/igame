/* 
 * Public Domain getopt header
 *
 */

#ifndef RAPTOR_GETOPT_H
#define RAPTOR_GETOPT_H

#ifdef __cplusplus
extern "C" {
#endif

int getopt(int argc, char * const argv[], const char *optstring);
extern char *optarg;
extern int optind, opterr, optopt;

#ifdef __cplusplus
}
#endif

#endif
