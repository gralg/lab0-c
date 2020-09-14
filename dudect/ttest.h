#ifndef DUDECT_TTEST_H
#define DUDECT_TTEST_H

#include <stdint.h>
typedef struct {
    double sum[2]; /*member added to keep total sums*/
    double mean[2];
    double m2[2];
    double n[2];
} t_ctx;

void t_push(t_ctx *ctx, double x, uint8_t class);
/*Calculate means of total sums*/
void t_mean(t_ctx *ctx, int64_t *exec_times, uint8_t *classes);
double t_compute(t_ctx *ctx);
void t_init(t_ctx *ctx);

#endif
