#include "mmm_c.h"
#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>

U16_DMAT DU16_New(uint16_t rows, uint16_t cols) {
  U16_DMAT mat = {rows, cols, NULL, false};

  return mat;
}

U16_DMAT DU16_NewZeros(uint16_t rows, uint16_t cols) {
  U16_DMAT mat;
  mat.rows = rows;
  mat.cols = cols;
  mat.cells = NULL;

  if (DU16_AllocateMemory(&mat) != Ok) {
    mat.is_allocated = false;
  } else {
    mat.is_allocated = true;
  }
  return mat;
}

Result DU16_AllocateMemory(U16_DMAT *mat) {

  mat->cells =
      (uint_fast16_t *)malloc(sizeof(uint_fast16_t) * mat->cols * mat->rows);
  if (!mat->cols) {
    mat->is_allocated = false;
    return Error;
  }

  mat->is_allocated = true;
  return Ok;
}

Result DU16_FreeMatrix(U16_DMAT *mat) {
  if (!mat->is_allocated) {
    return Error;
  } else if (mat->cells == NULL) {
    mat->is_allocated = false;
    return Error;
  }

  free(mat->cells);
  mat->cells = NULL;
  mat->is_allocated = false;
  return Ok;
}
