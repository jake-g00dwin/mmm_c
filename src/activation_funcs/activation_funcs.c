/*
 * Author: username
 * Date: todays_date
 * filename: activation_funcs.c
 * description: module_purpose
 */

#include "activation_funcs.h"
#include "math.h"

float AF_Sigmoid(float z) { return (1 / (1 + expf(-z))); }
