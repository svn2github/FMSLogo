// Copyright (C) 2005 by David Costanzo

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef __MEM_H_
#define __MEM_H_

#include "logodata.h"

extern NODE **gcstack;
extern NODE **gctop;

extern NODETYPES nodetype(const NODE *nd);
extern void setobject(NODE *nd, NODE *newobj);
extern void setcar(NODE *nd, NODE *newcar);
extern void setcdr(NODE *nd, NODE *newcdr);
extern NODE *reref(NODE *proc_var, NODE *newval);
extern NODE *unref(NODE *ret_var);
extern NODE *newnode(NODETYPES type);
extern NODE *cons(NODE *x, NODE *y);
extern void gc(NODE *nd);
extern NODE *lnodes(NODE *args);
extern void fill_reserve_tank(void);
extern void use_reserve_tank(void);
extern void check_reserve_tank(void);
extern void free_segment_list(void);
extern void spush(NODE *obj, NODE **stack);
extern void eval_driver(NODE *line);
extern NODE *lapply(NODE *args);
extern NODE *lqm(NODE *args);
extern NODE *llocal(NODE *args);
extern void uninitialize_eval(void);

#endif // __MEM_H_
