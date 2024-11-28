#include "mmm_c.h"
#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>

U16_DMAT DU16_NewZeros(uint16_t rows, uint16_t cols) {
  U16_DMAT mat;
  mat.rows = rows;
  mat.cols = cols;

  if (DU16_AllocateMemory(&mat) != Ok) {
    mat.cells = NULL;
  }

  return mat;
}

Result DU16_AllocateMemory(U16_DMAT *mat) {
  if (!calloc(mat->cols * mat->rows, sizeof(uint16_t))) {
    return Error;
  }
  return Ok;
}

Result DU16_FreeMatrix(U16_DMAT *mat) {
  if (mat->cells == NULL) {
    return Error;
  }

  free(mat->cells);
  return Ok;
}
