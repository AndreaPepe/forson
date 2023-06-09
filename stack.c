/*
stack.c -- implementation of a dinamically growing, pushdown stack
Copyright 2005 Alfonso Tarantini
This file is part of Forson.

Forson is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Forson is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Forson; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <generation.h>

/*ALLOCATES MEMORY FOR A STACK STRUCTURE, WIPES IT TO ZERO AND RETURNS A POINTER*/
stack *
initialize_new_stack()
{
	stack *new_stack = NULL;

	new_stack = xcalloc(1, sizeof(stack));
	new_stack->buffer = xcalloc(STACK_DEFAULT_SIZE, sizeof(symbol_id *));
	new_stack->stack_size = STACK_DEFAULT_SIZE;

	return new_stack;
}


/*POP THE SYMBOL ON TOP, RETURNS ZERO IF STACK IS EMPTY*/
symbol_id
pop(stack *st)
{
	int fragment, offset;
	symbol_id *buf = NULL;

	assert(st != NULL);

	if(st->size == 0)
	{
		return 0;
	}

	st->size--;

	buf = st->buffer[st->size];

	int ret = *buf;
	free(buf);
	return ret;
}


/*PUSH A NEW SYMBOL ON THE STACK. symb CAN'T BE ZERO*/
int
push(stack *st, symbol_id symb)
{
	int fragment, offset;
	symbol_id *buf = NULL;

	assert(st != NULL);
	assert(symb != (symbol_id) 0);

	st->size++;
	if(st->size - 1 >= st->stack_size){
		// double the size
		st->buffer = realloc(st->buffer, sizeof(symbol_id *) * st->stack_size * 2);
		st->stack_size *= 2;
	}
	
	st->buffer[st->size - 1] = xcalloc(1, sizeof(symbol_id));
	buf = st->buffer[st->size - 1];
	*buf = symb;
	

	return st->size;
}


/*RETURNS NUMBER OF SYMBOLS CURRENTLY ON THE STACK*/
int get_size(stack *st)
{
	assert(st != NULL);

	return st->size;
}


/*FREES MEMORY USED BY A STACK STRUCTURE*/
int clean_stack(stack *st)
{
	assert(st != NULL);

	for (int i = 0; i < st->size; i++){
		free(st->buffer[i]);
	}
	free(st->buffer);
	free(st);
}

