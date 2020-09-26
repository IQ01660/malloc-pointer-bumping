#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int main (int argc, char **argv){

  char* x = malloc(24);
  char* y = malloc(19);
  char* z = malloc(32);
  
  printf("x = %p\n", x);
  printf("y = %p\n", y);
  printf("z = %p\n", z);

  //testing realloc

  //==========================================================
  // testing the case when new size is less than or equal to the old one
  char* x_new = realloc(x, 20);

  printf("============================\n");
  printf("Old x = %p\n", x);
  printf("New x = %p\n", x);

  if (x == x_new) {
  	printf("test #1 - done (no copying)\n");
  }

  else {
  	printf("test #1 - rejected (no copying)\n");
  }

  printf("============================\n");

  //==========================================================
  //testing the case when new size is larger than the old one
  char* y_new = realloc(y, 23);

  printf("============================\n");
  printf("Old y = %p\n", y);
  printf("New y = %p\n", y_new);

  if (y != y_new) {
  	printf("test #2 - done (copying)\n");
  }
  else {
  	printf("test #2 - rejected (copying)\n");
  }

  printf("============================\n");

  //==========================================================

  // testing if reallocating copies the contents correctly (when new size is larger than the old one
  
  // allocating memory for an array of chars of length 13
  size_t* arr = malloc(13);

  // filling up its contents
  for(size_t i = 0; i < 13; i++) {
  	*(arr + i) = i;
  }

  // calling realloc, which will memcpy
  size_t* arr_copy = realloc(arr, 17);

  // if the test is passed and contents are copied correctly
  bool didPass = true;

  for(size_t i = 0; i < 13; i++) {
  	if ((*arr + i) != (*arr_copy + i)) 
	{
		didPass = false;
	}
  }

  printf("============================\n");

  if (didPass) {
  	printf("test #3 - done (copying contents correctly)\n");
  }
  else {
  	printf("test #3 - rejected (copying contents incorrectly)\n");
  }


  printf("============================\n");

  //==========================================================
  // checking the alignment 
  //
  // I ll test malloc first
  // and then test all those ptrs getting realloced (only with new size > old size, as old size would be tested already, as it stays the same)

  char* ptr1 = malloc(123);
  char* ptr2 = malloc(321);
  char* ptr3 = malloc(56);
  
  if ((intptr_t)ptr1 % 16 == 0 && (intptr_t)ptr2 % 16 == 0 && (intptr_t)ptr3 % 16 == 0) {
  	printf("test #4 - done (alignment for malloc)\n");
  }
  else {
  	printf("test #4 - rejected (alignment for malloc)\n");
  }

  printf("============================\n");

  // testing alignment for realloc now
  char* ptr1_c = realloc(ptr1, 142);
  char* ptr2_c = realloc(ptr2, 402);
  char* ptr3_c = realloc(ptr3, 67);
  if ((intptr_t)ptr1_c % 16 == 0 && (intptr_t)ptr2_c % 16 == 0 && (intptr_t)ptr3_c % 16 == 0) {
  	printf("test #5 - done (alignment for realloc)\n");
  }
  else {	
  	printf("test #5 - rejected (alignment for realloc)\n");
  }

  printf("============================\n");


}
