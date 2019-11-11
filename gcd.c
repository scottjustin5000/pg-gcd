#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "catalog/pg_type.h"
#include "utils/array.h"

PG_MODULE_MAGIC;

Datum gcd(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(gcd);

int recurseGcd(int a, int b);
int getGcd(int arr[], int n);

int recurseGcd(int a, int b) {
  if(a==0) return b;
  return recurseGcd(b%a,a);
}
int getGcd(int arr[], int n) {
 int result = arr[0]; 
    for (int i = 1; i < n; i++) 
        result = recurseGcd(arr[i], result); 
  
    return result; 
}

Datum 
gcd(PG_FUNCTION_ARGS) {
  ArrayType *array;
  array = PG_GETARG_ARRAYTYPE_P(0);
  Oid valueType;
  valueType = ARR_ELEMTYPE(array);

   if (valueType != INT2OID &&
      valueType != INT4OID &&
      valueType != INT8OID) {
    ereport(ERROR, (errmsg("gcd only works with int value types")));
  }
  
  int16 valueTypeWidth;
  // should always be true 
  bool valueTypeByValue;
  char valueTypeAlignmentCode;
  Datum *arrayContent;

  // List of "is null" flags for the array contents:
  bool *arrayNullFlags;
  int arrayLength;
  int* array2;

  // The size of array:
  arrayLength = (ARR_DIMS(array))[0];

  get_typlenbyvalalign(valueType, &valueTypeWidth, &valueTypeByValue, &valueTypeAlignmentCode);
  deconstruct_array(array, valueType, valueTypeWidth, valueTypeByValue, valueTypeAlignmentCode, &arrayContent, &arrayNullFlags, &arrayLength);
  array2 = palloc0(sizeof(int) * arrayLength);
  int i = 0;
  switch (valueType) {
    case INT2OID:
      for (i = 0; i < arrayLength; i++) {
        array2[i] = DatumGetInt16(arrayContent[i]);
      }
      break;
    case INT4OID:
      for (i = 0; i < arrayLength; i++) {
        array2[i] = DatumGetInt32(arrayContent[i]);
      }
      break;
    case INT8OID:
      for (i = 0; i < arrayLength; i++) {
        array2[i] = DatumGetInt64(arrayContent[i]);
      }
      break;
  }
  int result =  getGcd(array2, arrayLength); 

   PG_RETURN_INT64(result);
}