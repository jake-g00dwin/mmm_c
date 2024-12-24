#include "mmm_c.h"
#include <stdio.h>
#include <stdlib.h>

Result DU16_PrintMatrix(U16_DMAT *mat) {
  printf("matrix: shape(r, c):");
  printf("%lu, %lu\n", mat->rows, mat->cols);

  for (int i = 0; i < mat->cols; i++) {
    printf("Column[%d]:\n[\n", i);
    for (int j = 0; j < mat->rows; j++) {
      uint_fast16_t *cptr = DU16_CellIndex(mat, j, i);

      if (!cptr) {
        return Error;
      }

      printf("%lu,\n", *cptr);
    }
    printf("]\n");
  }

  return Ok;
}

U16_DMAT DU16_New(unsigned int rows, unsigned int cols) {
  U16_DMAT mat = {rows, cols, NULL, false};
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

Result DU16_SetAllTo(U16_DMAT *mat, uint16_t value) {
  if (!mat->is_allocated) {
    return Error;
  }

  unsigned int i;
  for (i = 0; i < (mat->cols * mat->rows); i++) {
    mat->cells[i] = value;
  }

  return Ok;
}

uint_fast16_t *DU16_CellIndex(U16_DMAT *mat, unsigned int row,
                              unsigned int col) {
  uint_fast16_t *ptr = NULL;

  if (row >= mat->rows || col >= mat->cols) {
    return ptr;
  }

  unsigned int index = (col * mat->rows) + row;
  ptr = &mat->cells[index];

  return ptr;
}

Result DU16_MultiplyByNum(U16_DMAT *mat, uint16_t value) {
  if ((mat->cells == NULL) || !mat->is_allocated) {
    return Error;
  }

  for (unsigned int i = 0; i < (mat->cols * mat->rows); i++) {
    mat->cells[i] *= value;
  }
  return Ok;
}

// Things to keep in mind:
// 1. Columns of 1st matrix must equal number of rows of second matrix.
// 2. the result will have:
//   - same number of rows as 1st matrix.
//   - same number of columns as 2nd matrix.

Result DU16_MultiplyInPlace(U16_DMAT *mata, U16_DMAT *matb) { return Ok; }

U16_DMAT DU16_DotProduct(U16_DMAT *mata, U16_DMAT *matb) {
  U16_DMAT mat_result = DU16_New(mata->rows, matb->cols);
  DU16_AllocateMemory(&mat_result);
  DU16_SetAllTo(&mat_result, 0);

  for (int i = 0; i < matb->cols; i++) {
    for (int j = 0; j < mata->rows; j++) { // Shared column/row value
      uint_fast16_t *cellr = DU16_CellIndex(&mat_result, i, j);
      *cellr = 0;
      for (int k = 0; k < mata->cols; k++) {
        uint_fast16_t *cella = DU16_CellIndex(mata, i, k);
        uint_fast16_t *cellb = DU16_CellIndex(matb, k, j);
        *cellr += (*cella) * (*cellb);
      } // K Loop End
    }   // J Loop End
  }     // I Loop End

  return mat_result;
}
