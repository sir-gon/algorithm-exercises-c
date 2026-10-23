#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void minimumBribes(int q_count, int *q);

static int minimumBribesCompute(int q_count, const int *q, bool *ok);
const char *minimumBribesText(int q_count, const int *q);

#ifdef __cplusplus
} // extern "C"
#endif
