#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const char *__RANSOM_NOTE_YES__;
extern const char *__RANSOM_NOTE_NO__;

void checkMagazine(int magazine_count, char **magazine, int note_count,
                   char **note);
const char *checkMagazineText(int magazine_count, char **magazine,
                              int note_count, char **note);

#ifdef __cplusplus
} // extern "C"
#endif
