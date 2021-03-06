/*
 *  logodata.h      intern header file
 *
 *    Copyright (C) 1993 by the Regents of the University of California
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 * 
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __LOGODATA_H_
#define __LOGODATA_H_

#include "logocore.h"

extern char ecma_set(int ch);
extern char ecma_clear(int ch);
extern bool ecma_get(int ch);
extern void init_ecma_array(void);
extern bool is_special_character(char ch);
extern char *strnzcpy(char *dst, const char *src, int len);
extern char *word_strnzcpy(char * dst, NODE *kludge, int len);
extern char *noparity_strnzcpy(char * dst, const char * src, int len);
extern char *mend_strnzcpy(char * dst, const char * src, int len);
extern char *mend_nosemi(char * dst, const char * src, int len);
extern char *quote_strnzcpy(char * dst, const char * src, int len);
extern char *colon_strnzcpy(char * dst, const char * src, int len);
extern char capital(char ch);
extern char uncapital(char ch);
extern char *low_strnzcpy(char * dst, const char * src, int len);
extern char *cap_strnzcpy(char * dst, const char * src, int len);
extern char * NormalizeCaseForDisplay(char *dst, const char * src, int len);
extern char *noparitylow_strnzcpy(char * dst, const char * src, int len);
extern int low_strncmp(const char * s1, const char * s2, int len);
extern int noparity_strncmp(const char * s1, const char * s2, int len);
extern int noparitylow_strncmp(const char * s1, const char * s2, int len);
extern NODE *make_strnode_no_copy(const char *strptr, char *strhead, int len, NODETYPES typ);
extern NODE *make_strnode(const char *string, int len, NODETYPES typ, char * (*copy_routine) (char *, const char *, int));
extern NODE *make_strnode(const char *string);
extern NODE *make_strnode_from_wordlist(NODE * wordlist, int len, NODETYPES typ);
extern NODE *make_lowercase_strnode_from_strnode(NODE * OriginalNode);
extern void make_runparse(NODE *ndi);
extern NODE *make_quote(NODE *qnd);
extern NODE *maybe_quote(NODE *nd);
extern NODE *make_caseobj(NODE *cstrnd, NODE *obj);
extern NODE *make_colon(NODE *cnd);
extern NODE *make_intnode(FIXNUM i);
extern NODE *make_floatnode(FLONUM f);
extern NODE *cnv_node_to_numnode(NODE *ndi);
extern NODE *cnv_node_to_strnode(NODE *nd);
extern NODE *make_static_strnode(const char *strptr);
extern NODE *cons_list(void);
extern NODE *cons_list(NODE * node1);
extern NODE *cons_list(NODE * node1, NODE * node2);
extern NODE *cons_list(NODE * node1, NODE * node2, NODE * node3);
extern NODE *cons_list(NODE * node1, NODE * node2, NODE * node3, NODE * node4);
extern NODE *cons_list(NODE * node1, NODE * node2, NODE * node3, NODE * node4, NODE * node5);
extern int list_length(const NODE * List);
extern NODE *make_array(int len);
extern NODE *llowercase(NODE *args);
extern NODE *luppercase(NODE *args);
extern NODE *getprop(NODE *plist, NODE *name, bool before);
extern NODE *lgprop(NODE *args);
extern NODE *lpprop(NODE *args);
extern NODE *lremprop(NODE *args);
extern NODE *lplist(NODE *args);
extern NODE *llogoversion(NODE *args);
extern bool variableIsTrue(NODE *variable);
extern bool isCaseIgnored();
extern bool canRedefinePrimitives();

#endif // __LOGODATA_H_
