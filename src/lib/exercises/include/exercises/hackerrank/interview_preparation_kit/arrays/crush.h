#pragma once

#ifdef __cplusplus
extern "C" {
#endif

long arrayManipulation(int n, int queries_rows, int queries_columns,
                       int **queries);

long arrayManipulationOptimized(int n, int queries_rows, int queries_columns,
                                int **queries);

#ifdef __cplusplus
} // extern "C"
#endif
