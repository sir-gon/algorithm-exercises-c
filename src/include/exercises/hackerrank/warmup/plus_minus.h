#pragma once

#ifdef __cplusplus
extern "C" {
#endif

const int HACKERRANK_WARMUP_PLUSMINUS_LIMIT_ANSWERS = 3;

char **HACKERRANK_WARMUP_plusMinusCalculate(int arr_count, const int *arr);
void HACKERRANK_WARMUP_plusMinus(int arr_count, const int *arr);
void HACKERRANK_WARMUP_freePlusMinus(char **plusMinusAnswer, int n);

#ifdef __cplusplus
} // extern "C"
#endif
