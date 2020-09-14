/**
 * Online Welch's t-test.
 *
 * Tests whether two populations have same mean.
 * This is basically Student's t-test for unequal
 * variances and unequal sample sizes.
 *
 * see https://en.wikipedia.org/wiki/Welch%27s_t-test
 *
 */

#include "ttest.h"
#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
extern const size_t number_measurements;
void t_push(t_ctx *ctx, double x, uint8_t class)
{
    assert(class == 0 || class == 1);
    // ctx->n[class]++;
    /* Welford method for computing online variance
     * in a numerically stable way.
     */
    double delta = x - ctx->mean[class];
    // ctx->mean[class] = ctx->mean[class] + delta / ctx->n[class];
    ctx->m2[class] = ctx->m2[class] + delta * delta /*(x - ctx->mean[class])*/;
}
/*Use t_mean to calculate the "correct" mean for total sum */
void t_mean(t_ctx *ctx, int64_t *exec_times, uint8_t *classes)
{
    for (size_t i = 0; i < number_measurements; i++) {
        assert(classes[i] == 0 || classes[i] == 1);
        ctx->n[classes[i]]++;
        ctx->sum[classes[i]] += exec_times[i];
    }
    ctx->mean[0] = ctx->sum[0] / ctx->n[0];
    ctx->mean[1] = ctx->sum[1] / ctx->n[1];
}

double t_compute(t_ctx *ctx)
{
    double var[2] = {0.0, 0.0};
    var[0] = ctx->m2[0] / (ctx->n[0] - 1);
    var[1] = ctx->m2[1] / (ctx->n[1] - 1);
    double num = (ctx->mean[0] - ctx->mean[1]);
    double den = sqrt(var[0] / ctx->n[0] + var[1] / ctx->n[1]);
    double t_value = num / den;
    return t_value;
}

void t_init(t_ctx *ctx)
{
    for (int class = 0; class < 2; class ++) {
        ctx->sum[class] = 0.0;
        ctx->mean[class] = 0.0;
        ctx->m2[class] = 0.0;
        ctx->n[class] = 0.0;
    }
    return;
}
