/*
 * Copyright (c) 2019 xieqing. https://github.com/xieqing
 * May be freely redistributed, but copyright notice must be retained.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avl_data.h"

mydata *makedata(int key)
{
	mydata* p = (mydata *) malloc(sizeof(mydata));
	if (p)
		p->key = key;

	return p;
}

int compare_func(const void *d1, const void *d2)
{
	assert(d1);
	assert(d2);

	mydata* p1 = (mydata *) d1;
	mydata* p2 = (mydata *) d2;
	if (p1->key == p2->key)
		return 0;
	if (p1->key > p2->key)
		return 1;
	return -1;
}

void destroy_func(void *d)
{
	assert(d);

	free(d);
}

void print_func(void *d)
{
	assert(d);

	mydata* p = (mydata *) d;
	printf("%d", p->key);
}

void print_char_func(void *d)
{
	assert(d);

	mydata* p = (mydata *) d;
	printf("%c", p->key & 127);
}

