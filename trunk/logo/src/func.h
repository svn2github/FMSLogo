/* File IBMTERM.CPP: */

#include "3dsolid.h"

extern void single_step_box(NODE *the_line);
extern void checkqueue(void);
extern void emptyqueue(void);
extern void do_help(char *arg);
extern void checkwindow(int *x, int *y, int *w, int *h);
extern BOOL MyBeep(DWORD dwFreq, DWORD dwDuration);
extern void Myoutportb(short portid, unsigned char value);
extern unsigned char Myinportb(short portid);
extern void Myoutport(short portid, short value);
extern short Myinport(short portid);
extern int Myingameport (short portid, short mask);

extern bool check_stop(bool scan_for_messages);
extern void term_init_ibm(void);
extern void ibm_gotoxy(int x, int y);
extern void ibm_clear_text(void);
extern void ibm_clear_screen(void);
extern void ibm_plain_mode(void);
extern void ibm_bold_mode(void);
extern void erase_graphics_top(void);
extern void save_pen(pen_info *pen);
extern void restore_pen(const pen_info *pen);
extern void plain_xor_pen(void);
extern void pen_down(void);
extern void pen_reverse(void);
extern void pen_erase(void);
extern int get_pen_mode(void);
extern void set_pen_mode(int m);
extern int get_pen_width(void);
extern void set_pen_width(int w);
extern int get_pen_height(void);
extern void set_pen_height(int h);
extern void set_pen_pattern(const char *pat);
extern void set_list_pen_pattern(NODE *arg);
extern void get_pen_pattern(char *pat);
extern NODE *get_node_pen_pattern(void);
extern NODE *get_node_pen_mode(void);
extern void label(const char *s);
extern SIZE labelsize(const char *s);
extern void logofill(bool bOld);
extern void erase_screen(void);
extern bool button(void);
extern void tone(FIXNUM pitch, FIXNUM duration);
extern void check_scroll(void);

/* File WRKSP.CPP: */

extern NODE *ltext(NODE *args);
extern NODE *lfulltext(NODE *args);
extern NODE *ldefine(NODE *args);
extern NODE *ldefmacro(NODE *args);
extern NODE *anonymous_function(NODE *text);
extern NODE *lto(NODE *args);
extern NODE *lmacro(NODE *args);
extern NODE *lmake(NODE *args);
extern NODE *llocal(NODE *args);
extern NODE *lcontents(NODE *arg);
extern NODE *lstepped(NODE *arg);
extern NODE *ltraced(NODE *arg);
extern NODE *lburied(NODE *arg);
extern NODE *lprocedures(NODE *arg);
extern NODE *lnames(NODE *arg);
extern NODE *lplists(NODE *arg);
extern NODE *lpo(NODE *arg);
extern NODE *lpot(NODE *arg);
extern NODE *lerase(NODE *arg);
extern NODE *lbury(NODE *arg);
extern NODE *ltrace(NODE *arg);
extern NODE *lstep(NODE *arg);
extern NODE *lunbury(NODE *arg);
extern NODE *luntrace(NODE *arg);
extern NODE *lunstep(NODE *arg);
extern NODE *ledit(NODE *args);
extern bool endedit(void);
extern NODE *lthing(NODE *args);
extern NODE *lnamep(NODE *args);
extern NODE *lprocedurep(NODE *args);
extern NODE *lproplistp(NODE *args);
extern NODE *lprimitivep(NODE *args);
extern NODE *ldefinedp(NODE *args);
extern NODE *lmacrop(NODE *args);
extern NODE *lcopydef(NODE *args);

/* File GRAPHICS.CPP: */

extern FIXNUM g_round(FLONUM n);
extern FLONUM numeric_node_to_flonum(NODE* numeric_node);
extern FIXNUM numeric_node_to_fixnum(NODE* numeric_node);
extern NODE *lscrunch(NODE *arg);
extern FLONUM cut_error(FLONUM n);
extern void draw_turtle(bool erase);
extern void draw_turtles(bool erase);
extern NODE *numeric_arg(NODE *args);
extern NODE *lright(NODE *arg);
extern NODE *lleft(NODE *arg);
extern NODE *lrightroll(NODE *arg);
extern NODE *lleftroll(NODE *arg);
extern NODE *ldownpitch(NODE *arg);
extern NODE *luppitch(NODE *arg);
extern FLONUM rotation_z();
extern FLONUM rotation_y();
extern FLONUM rotation_x();
extern NODE *lforward(NODE *arg);
extern NODE *lback(NODE *arg);
extern NODE *lshowturtle(NODE *arg);
extern NODE *lhideturtle(NODE *arg);
extern NODE *lbitmapturtle(NODE *arg);
extern NODE *lnobitmapturtle(NODE *arg);
extern NODE *lshownp(NODE *arg);
extern NODE *lsetheading(NODE *arg);
extern NODE *lsetroll(NODE *arg);
extern NODE *lsetclip(NODE *arg);
extern NODE *lsetpitch(NODE *arg);
extern NODE *lsetturtle(NODE *arg);
extern NODE *lturtle(NODE *arg);
extern NODE *lturtles(NODE *arg);
extern NODE *lheading(NODE *arg);
extern NODE *lroll(NODE *arg);
extern NODE *lpitch(NODE *arg);
extern NODE *vec_arg_helper(NODE *args, bool floatok);
extern NODE *vector_arg(NODE *args);
extern NODE *vector_3_arg(NODE *args);
extern NODE *vector_4_arg(NODE *args);
extern NODE *pos_int_vector_arg(NODE *args);
extern NODE *pos_int_vector_3_arg(NODE *args);
extern NODE *pos_int_vector_4_arg(NODE *args);
extern NODE *ltowards(NODE *args);
extern NODE *ltowardsxyz(NODE *args);
extern NODE *llight(NODE *arg);
extern NODE *lpos(NODE *arg);
extern NODE *lposxyz(NODE *arg);
extern NODE *lhome(NODE *arg);
extern NODE *lclearscreen(NODE *arg);
extern NODE *lclean(NODE *arg);
extern NODE *lsetlight(NODE *args);
extern NODE *lsetpos(NODE *args);
extern NODE *lsetposxyz(NODE *args);
extern NODE *lsetxy(NODE *args);
extern NODE *lsetxyz(NODE *args);
extern NODE *lellipsearc(NODE *args);
extern NODE *lsetx(NODE *args);
extern NODE *lsety(NODE *args);
extern NODE *lsetz(NODE *args);
extern NODE *lwrap(NODE *arg);
extern NODE *lfence(NODE *arg);
extern NODE *lwindow(NODE *arg);
extern NODE *lpolystart(NODE *arg);
extern NODE *lpolyend(NODE *arg);
extern NODE *lpolyview(NODE *arg);
extern NODE *lperspective(NODE *arg);
extern NODE *lfill(NODE *arg);
extern NODE *llabel(NODE *arg);
extern NODE *llabelsize(NODE *arg);
extern NODE *ltextscreen(NODE *arg);
extern NODE *lsplitscreen(NODE *arg);
extern NODE *lfullscreen(NODE *arg);
extern NODE *lpendownp(NODE *arg);
extern NODE *lpenmode(NODE *arg);
extern NODE *lpencolor(NODE *arg);
extern NODE *lpixel(NODE *arg);
extern NODE *lsetpixel(NODE *args);
extern NODE *lfloodcolor(NODE *arg);
extern NODE *lscreencolor(NODE *arg);
extern NODE *lpensize(NODE *arg);
extern NODE *lpenpattern(NODE *arg);
extern NODE *lpendown(NODE *arg);
extern NODE *lpenup(NODE *arg);
extern NODE *lpenpaint(NODE *arg);
extern NODE *lpenerase(NODE *arg);
extern NODE *lpenreverse(NODE *arg);
extern NODE *lclearpalette(NODE *arg);
extern NODE *lbitload(NODE *arg);
extern NODE *lbitloadsize(NODE *arg);
extern NODE *lbitsize(NODE *arg);
extern void cnv_strnode_string(char *textbuf, NODE *arg);
extern void do_execution(char *string);
extern NODE *lsettimer(NODE *arg);
extern NODE *lcleartimer(NODE *arg);
extern NODE *lbitsave(NODE *arg);
extern NODE *lgifsave(NODE *arg);
extern NODE *lgifload(NODE *arg);
extern void gifsave_helper(char *textbuf, int iDelay_, int bAppendMode_, int iLoop_, int iTrans, int iMaxColorDepth);
extern void gifload_helper(char *textbuf, DWORD &dwPixelWidth, DWORD &dwPixelHeight);
extern NODE *lgifsize(NODE *arg);
extern NODE *lbitcut(NODE *arg);
extern NODE *lbitcopy(NODE *arg);
extern void turtlepaste(int turtle_which);
extern NODE *lbitpaste(NODE *arg);
extern NODE *lbitpastetoindex(NODE *arg);
extern NODE *lbitmode(NODE *arg);
extern NODE *lturtlemode(NODE *arg);
extern NODE *lmachine(NODE *arg);
extern NODE *lsetbitmode(NODE *arg);
extern NODE *lsetturtlemode(NODE *arg);
extern NODE *lbitindex(NODE *arg);
extern NODE *lsetbitindex(NODE *arg);
extern NODE *lbitfit(NODE *arg);
extern NODE *lbitblock(NODE *arg);
extern NODE *lscrollx(NODE *arg);
extern NODE *lscrolly(NODE *arg);
extern NODE *lsetpencolor(NODE *arg);
extern NODE *lsetfloodcolor(NODE *arg);
extern NODE *lsetscreencolor(NODE *arg);
extern NODE *lsetpensize(NODE *args);
extern NODE *lsetpenpattern(NODE *args);
extern NODE *lsetscrunch(NODE *args);
extern NODE *lmousepos(NODE *args);
extern NODE *lkeyboardvalue(NODE *args);
extern NODE *lbuttonp(NODE *args);
extern NODE *ltone(NODE *args);
extern NODE *lrefresh(NODE *args);
extern NODE *lnorefresh(NODE *args);

/* File MAIN.CPP: */

extern void update_status_all(BOOL bUpdate);
extern void update_status_memory(void);
extern void update_status_evals(void);
extern void update_status_vectors(void);
extern void update_status_turtleposition(void);
extern void update_status_pencolor(void);
extern void update_status_floodcolor(void);
extern void update_status_screencolor(void);
extern void update_status_paletteuse(void);
extern void update_status_penwidth(void);
extern void update_status_turtleheading(void);
extern void update_status_penstyle(void);
extern void update_status_pencontact(void);
extern void update_status_turtlevisability(void);
extern void update_status_turtlepitch(void);
extern void update_status_turtleroll(void);
extern void update_status_turtlewhich(void);

extern void MyMessageScan(void);
extern void putcombobox(char *str);
extern void putfileeditcombo(char *str);
extern void clearcombobox(void);
extern long LoadColor(int dpenr, int dpeng, int dpenb);
extern void exit_program(void);
extern bool promptuser(char *str, const char *prompt);
extern void getcombobox(char *str);
extern void ibmturt(bool hide);
extern void move_to(FLONUM x, FLONUM y);
extern void line_to(FLONUM x, FLONUM y);
extern void move_to_3d(FLONUM x, FLONUM y, FLONUM z);
extern void line_to_3d(const Point & ToPoint);
extern void thepencolor(int, int, int);
extern void thefloodcolor(int, int, int);
extern void thescreencolor(int, int, int);

/* File COMS.CPP: */

extern void prepare_to_exit(bool okay);
extern NODE *make_cont(enum labels cont, NODE *val);
extern NODE *loutput(NODE *arg);
extern NODE *lstop(NODE *arg);
extern NODE *lthrow(NODE *arg);
extern NODE *lcatch(NODE *args);
extern NODE *lgoto(NODE *arg);
extern NODE *ltag(NODE *arg);
extern bool  boolean_arg(NODE *args);
extern NODE *lnot(NODE *args);
extern NODE *land(NODE *args);
extern NODE *lor(NODE *args);
extern NODE *runnable_arg(NODE *args);
extern NODE *lif(NODE *args);
extern NODE *lifelse(NODE *args);
extern NODE *lrun(NODE *args);
extern NODE *lrunresult(NODE *args);
extern NODE *pos_int_arg(NODE *args);
extern NODE *lrepeat(NODE *args);
extern NODE *lrepcount(NODE *args);
extern NODE *lforever(NODE *args);
extern NODE *ltest(NODE *args);
extern NODE *liftrue(NODE *args);
extern NODE *liffalse(NODE *args);
extern NODE *lbye(NODE *args);
extern NODE *lwait(NODE *args);
extern NODE *leventcheck(NODE *args);
extern NODE *ltime(NODE *args);
extern NODE *ltimemilli(NODE *args);
extern NODE *lshell(NODE *args);

/* File LOGODATA.CPP: */

extern char ecma_set(int ch);
extern char ecma_clear(int ch);
extern int ecma_get(int ch);
extern char *strnzcpy(char *dst, const char *src, int len);
extern char *word_strnzcpy(char * dst, NODE *kludge, int len);
extern char *noparity_strnzcpy(char * dst, const char * src, int len);
extern char *mend_strnzcpy(char * dst, const char * src, int len);
extern char *mend_nosemi(char * dst, const char * src, int len);
extern char *quote_strnzcpy(char * dst, const char * src, int len);
extern char *colon_strnzcpy(char * dst, const char * src, int len);
extern char *low_strnzcpy(char * dst, const char * src, int len);
extern char *cap_strnzcpy(char * dst, const char * src, int len);
extern char *noparitylow_strnzcpy(char * dst, const char * src, int len);
extern int low_strncmp(const char * s1, const char * s2, int len);
extern int noparity_strncmp(const char * s1, const char * s2, int len);
extern int noparitylow_strncmp(const char * s1, const char * s2, int len);
extern NODE *make_strnode_no_copy(const char *strptr, char *strhead, int len, NODETYPES typ);
extern NODE *make_strnode(const char *string, int len, NODETYPES typ, char * (*copy_routine) (char *, const char *, int));
extern NODE *make_strnode_from_wordlist(NODE * wordlist, int len, NODETYPES typ);
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
extern NODE *make_array(int len);
extern NODE *llowercase(NODE *args);
extern NODE *luppercase(NODE *args);
extern NODE *getprop(NODE *plist, NODE *name, bool before);
extern NODE *lgprop(NODE *args);
extern NODE *lpprop(NODE *args);
extern NODE *lremprop(NODE *args);
extern NODE *copy_list(NODE *arg);
extern NODE *lplist(NODE *args);

/* File TERM.CPP: */

extern void termcap_putter(char ch);
extern void termcap_getter(char *cap, char *buf);
extern void term_init(void);
extern void charmode_on(void);
extern void charmode_off(void);
extern NODE *lcleartext(NODE *args);
extern NODE *lcursor(NODE *args);
extern NODE *lsetcursor(NODE *args);
extern NODE *lsetmargins(NODE *args);
extern NODE *lstandout(NODE *args);

/* File PRINT.CPP: */

extern void update_coords(char ch);
extern void print_char(FILE *strm, char ch);
extern void print_space(FILE *strm);
extern void ndprintf(FILE *strm, char *fmt, ...);
extern void print_helper(FILE *strm, NODE *nd);
extern void print_node(FILE *strm, NODE *nd);
extern void print_nobrak(FILE *strm, NODE *nd);
extern void new_line(FILE *strm);
extern NODE *lshow(NODE *args);
extern NODE *ltype(NODE *args);
extern NODE *lprint(NODE *args);

/* File PARSE.CPP: */

extern int rd_getc(FILE *strm);
extern NODE *reader(FILE *strm, const char *prompt);
extern NODE *list_to_array(NODE *list);
extern NODE *parser(NODE *nd, bool semi);
extern NODE *lparse(NODE *args);
extern NODE *runparse(NODE *ndlist);
extern NODE *lrunparse(NODE *args);

/* File PAREN.CPP: */

extern void make_line(NODE *tree, NODE *line);
extern void untreeify(NODE *node);
extern void untreeify_line(NODE *line);
extern void untreeify_proc(NODE *procname);
extern void make_tree_from_body(NODE *body);
extern void make_tree(NODE *list);
extern NODE *paren_line(NODE *line);
extern NODE *paren_expr(NODE **expr, bool inparen);
extern NODE *gather_args(NODE *proc, NODE **args, bool inparen, NODE **ifnode);
extern NODE *gather_some_args(int min, int max, NODE **args, bool inparen, NODE **ifnode);
extern int priority(NODE *proc_obj);
extern NODE *paren_infix(NODE *left_arg, NODE **rest, int old_pri, bool inparen);

/* File MEM.CPP: */

extern NODETYPES nodetype(NODE *nd);
extern void setobject(NODE *nd, NODE *newobj);
extern void setcar(NODE *nd, NODE *newcar);
extern void setcdr(NODE *nd, NODE *newcdr);
extern NODE *reref(NODE *proc_var, NODE *newval);
extern NODE *unref(NODE *ret_var);
extern void addseg(void);
extern NODE *newnode(NODETYPES type);
extern NODE *cons(NODE *x, NODE *y);
extern void gc(NODE *nd);
extern NODE *lnodes(NODE *args);
extern void fill_reserve_tank(void);
extern void use_reserve_tank(void);
extern void check_reserve_tank(void);

/* File MATH.CPP: */

extern int numberp(NODE *snd);
extern NODE *lrandom(NODE *arg);
extern NODE *lrerandom(NODE *arg);
extern NODE *ladd(NODE *args);
extern NODE *lsub(NODE *args);
extern NODE *lmul(NODE *args);
extern NODE *ldivide(NODE *args);
extern NODE *lremainder(NODE *args);
extern NODE *lmodulo(NODE *args);
extern NODE *lbitand(NODE *args);
extern NODE *lbitor(NODE *args);
extern NODE *lbitxor(NODE *args);
extern NODE *lashift(NODE *args);
extern NODE *llshift(NODE *args);
extern NODE *lbitnot(NODE *args);
extern NODE *lsin(NODE *args);
extern NODE *lasin(NODE *args);
extern NODE *lcos(NODE *args);
extern NODE *lacos(NODE *args);
extern NODE *ltan(NODE *args);
extern NODE *latan(NODE *args);
extern NODE *lradsin(NODE *args);
extern NODE *lradasin(NODE *args);
extern NODE *lradcos(NODE *args);
extern NODE *lradacos(NODE *args);
extern NODE *lradtan(NODE *args);
extern NODE *lradatan(NODE *args);
extern NODE *lsqrt(NODE *args);
extern NODE *linteg(NODE *args);
extern NODE *lround(NODE *args);
extern NODE *lexp(NODE *args);
extern NODE *llog10(NODE *args);
extern NODE *lln(NODE *args);
extern NODE *lpower(NODE *args);
extern NODE *torf(bool tf);
extern NODE *llessp(NODE *args);
extern NODE *lgreaterp(NODE *args);
extern int compare_node(NODE *n1, NODE *n2, bool ignorecase);
extern bool equalp_help(NODE *arg1, NODE *arg2, bool ingc);
extern NODE *lequalp(NODE *args);
extern NODE *l_eq(NODE *args);
extern NODE *lbeforep(NODE *args);

/* File UNIX.CPP: */
extern void unblock_input(void);

/* File LISTS.CPP: */

extern NODE *list_arg(NODE *args);
extern NODE *lbutfirst(NODE *args);
extern NODE *lbutlast(NODE *args);
extern NODE *lfirst(NODE *args);
extern NODE *lfirsts(NODE *args);
extern NODE *lbfs(NODE *args);
extern NODE *llast(NODE *args);
extern NODE *llist(NODE *args);
extern NODE *lemptyp(NODE *arg);
extern NODE *lascii(NODE *args);
extern NODE *lrawascii(NODE *args);
extern NODE *lbackslashedp(NODE *args);
extern NODE *lchar(NODE *args);
extern NODE *lcount(NODE *args);
extern NODE *lfput(NODE *args);
extern NODE *llput(NODE *args);
extern NODE *string_arg(NODE *args);
extern NODE *lword(NODE *args);
extern NODE *lsentence(NODE *args);
extern NODE *lwordp(NODE *arg);
extern NODE *llistp(NODE *arg);
extern NODE *lnumberp(NODE *arg);
extern NODE *larrayp(NODE *arg);
extern NODE *lmemberp(NODE *args);
extern NODE *lsubstringp(NODE *args);
extern NODE *lmember(NODE *args);
extern NODE *integer_arg(NODE *args);
extern FIXNUM int_arg(NODE *args);
extern NODE *litem(NODE *args);
extern NODE *lsetitem(NODE *args);
extern NODE *l_setitem(NODE *args);
extern NODE *larray(NODE *args);
extern FLONUM float_arg(NODE *args);
extern NODE *lform(NODE *args);
extern NODE *lscan(NODE *args);
extern NODE *l_setfirst(NODE *args);
extern NODE *l_setbf(NODE *args);

/* File INTERN.CPP: */
extern FIXNUM hash(const char *s, int len);
extern NODE *make_case(NODE *casestrnd, NODE *obj);
extern NODE *make_object(NODE *canonical, NODE *proc, NODE *val, NODE *plist, NODE *casestrnd);
extern NODE *make_instance(NODE *casend, NODE *lownd);
extern NODE *find_instance(NODE *lownd);
extern int case_compare(NODE *nd1, NODE *nd2);
extern NODE *find_case(NODE *strnd, NODE *obj);
extern NODE *intern(NODE *nd);

/* File INIT.CPP: */

extern NODE *valref(NODE *p);
extern void init(void);

/* File FILES.CPP: */

extern FILE *open_file(NODE *arg, const char *access);
extern NODE *ldribble(NODE *arg);
extern NODE *lnodribble(NODE *arg);
extern FILE *find_file(NODE *arg, bool remove);
extern NODE *lopenread(NODE *arg);
extern NODE *lopenwrite(NODE *arg);
extern NODE *lopenappend(NODE *arg);
extern NODE *lopenupdate(NODE *arg);
extern NODE *lallopen(NODE *arg);
extern NODE *lclose(NODE *arg);
extern NODE *lsetwrite(NODE *arg);
extern NODE *lsetread(NODE *arg);
extern NODE *lreader(NODE *arg);
extern NODE *lwriter(NODE *arg);
extern NODE *lerasefile(NODE *arg);
extern void filesave(const char *arg);
extern NODE *lsave(NODE *arg);
extern void runstartup(NODE *oldst);
extern void silent_load(NODE *arg, char *prefix);
extern NODE *lload(NODE *arg);
extern void fileload(const char *arg);
extern NODE *lreadlist(NODE *arg);
extern NODE *lreadword(NODE *arg);
extern NODE *lreadchar(NODE *arg);
extern NODE *lreadchars(NODE *args);
extern NODE *leofp(NODE *arg);
extern NODE *lkeyp(NODE *arg);
extern NODE *lreadpos(NODE *arg);
extern NODE *lsetreadpos(NODE *arg);
extern NODE *lwritepos(NODE *arg);
extern NODE *lsetwritepos(NODE *arg);

/* File EVAL.CPP: */

extern NODE *err_eval_driver(NODE *seq);
extern void spop(NODE **stack);
extern void spush(NODE *obj, NODE **stack);
extern void numpop(NODE **stack);
extern void numpush(FIXNUM obj, NODE **stack);
extern void eval_driver(NODE *line);
extern NODE *if_eval_driver(NODE *seq);
extern NODE *lapply(NODE *args);
extern NODE *lqm(NODE *args);
extern void tell_shadow(NODE *arg);
extern bool not_local(NODE *name, NODE *sp);
extern NODE *reverse(NODE *list);
extern NODE *append(NODE *a, NODE *b);
extern NODE *evaluator(NODE *list, enum labels where);
extern void reset_args(NODE *old_stack);

/* File ERROR.CPP: */

extern void err_print(void);
extern NODE *err_logo(ERR_TYPES error_type, NODE *error_desc);
extern NODE *lerror(NODE *arg);
extern NODE *lpause(NODE *arg);
extern NODE *lhalt(NODE *arg);
extern NODE *lyield(NODE *arg);
extern NODE *lnoyield(NODE *arg);
extern NODE *lcontinue(NODE *args);

/* File UNIX.CPP: */
extern int printfx(const char *fmt);
extern int printfx(const char *fmt, const char *str);
extern void putcombochar(char c);
extern NODE *lpushdir(NODE *arg);
extern NODE *lpopdir(NODE *arg);
extern NODE *lmkdir(NODE *arg);
extern NODE *lrmdir(NODE *arg);
extern NODE *ldirectories(NODE *arg);
extern NODE *lfiles(NODE *arg);

extern NODE *lpeek(NODE *arg);
extern NODE *lpoke(NODE *arg);

extern NODE *lstatus(NODE *arg);
extern NODE *lnostatus(NODE *arg);
extern void zoom_helper(FLONUM temp_zoom);
extern void UpdateZoomControlFlag();
extern NODE *lzoom(NODE *arg);
extern NODE *lmci(NODE *arg);
extern NODE *lmidiopen(NODE *arg);
extern NODE *lmidiclose(NODE *arg);
extern NODE *lmidimessage(NODE *arg);
extern NODE *lsound(NODE *arg);
extern NODE *ldllload(NODE *arg);
extern NODE *ldllcall(NODE *arg);
extern NODE *ldllfree(NODE *arg);
extern NODE *lplaywave(NODE *args);
extern NODE *lwinhelp(NODE *arg);
extern NODE *lhelp(NODE *arg);
//extern NODE *lsettextsize(NODE *arg);
//extern NODE *lsettextstyle(NODE *arg);
extern NODE *lsetlabelfont(NODE *arg);
extern NODE *llabelfont(NODE *arg);
extern NODE *lsetactivearea(NODE *arg);
extern NODE *lactivearea(NODE *arg);

extern NODE *lportopen(NODE *args);
extern NODE *lportclose(NODE *arg);
extern NODE *lportreadchar(NODE *arg);
extern NODE *lportwritechar(NODE *args);
extern NODE *lportreadarray(NODE *args);
extern NODE *lportwritearray(NODE *args);
extern NODE *lportflush(NODE *args);
extern NODE *lportmode(NODE *args);
extern NODE *linportb(NODE *args);
extern NODE *loutportb(NODE *args);
extern NODE *linport(NODE *args);
extern NODE *loutport(NODE *args);
extern NODE *lingameport(NODE *args);

extern NODE *lsetfocus(NODE *args);
extern NODE *lgetfocus(NODE *arg);
extern NODE *lwindowset(NODE *args);

extern NODE *lnetreceiveon(NODE *args);
extern NODE *lnetreceiveoff(NODE *arg);
extern NODE *lnetreceivesendvalue(NODE *args);
extern NODE *lnetreceivereceivevalue(NODE *arg);
extern NODE *lnetsendon(NODE *args);
extern NODE *lnetsendoff(NODE *arg);
extern NODE *lnetsendsendvalue(NODE *args);
extern NODE *lnetsendreceivevalue(NODE *arg);
extern NODE *lnetstartup(NODE *args);
extern NODE *lnetshutdown(NODE *arg);

extern BOOL CheckOnScreenControls();
extern NODE *ldebugwindows(NODE *args);
extern NODE *lmouseon(NODE *args);
extern NODE *lmouseoff(NODE *arg);
extern NODE *lkeyboardon(NODE *args);
extern NODE *lkeyboardoff(NODE *arg);
extern NODE *lmessagebox(NODE *args);
extern NODE *lquestionbox(NODE *args);
extern NODE *lyesnobox(NODE *args);
extern NODE *lselectbox(NODE *args);
extern NODE *lsetcursorwait(NODE *arg);
extern NODE *lsetcursorarrow(NODE *arg);
extern NODE *ldialogcreate(NODE *args);
extern NODE *ldialogenable(NODE *args);
extern NODE *ldialogdelete(NODE *arg);
extern NODE *lwindowcreate(NODE *args);
extern NODE *lwindowenable(NODE *args);
extern NODE *lwindowdelete(NODE *arg);
extern void windowdelete_helper();
extern NODE *lbuttoncreate(NODE *args);
extern NODE *lbuttonupdate(NODE *args);
extern NODE *lbuttonenable(NODE *args);
extern NODE *lbuttondelete(NODE *arg);
extern NODE *lscrollbarcreate(NODE *args);
extern NODE *lscrollbarenable(NODE *args);
extern NODE *lscrollbardelete(NODE *arg);
extern NODE *lscrollbarset(NODE *args);
extern NODE *lscrollbarget(NODE *arg);
extern NODE *llistboxcreate(NODE *args);
extern NODE *llistboxenable(NODE *args);
extern NODE *llistboxdelete(NODE *arg);
extern NODE *llistboxgetselect(NODE *arg);
extern NODE *llistboxaddstring(NODE *args);
extern NODE *llistboxdeletestring(NODE *args);
extern NODE *lcomboboxcreate(NODE *args);
extern NODE *lcomboboxenable(NODE *args);
extern NODE *lcomboboxdelete(NODE *arg);
extern NODE *lcomboboxgettext(NODE *arg);
extern NODE *lcomboboxsettext(NODE *arg);
extern NODE *lcomboboxaddstring(NODE *args);
extern NODE *lcomboboxdeletestring(NODE *args);
extern NODE *lstaticcreate(NODE *args);
extern NODE *lstaticupdate(NODE *args);
extern NODE *lstaticdelete(NODE *arg);
extern NODE *lgroupboxcreate(NODE *args);
extern NODE *lgroupboxdelete(NODE *arg);
extern NODE *lradiobuttoncreate(NODE *args);
extern NODE *lradiobuttonenable(NODE *args);
extern NODE *lradiobuttondelete(NODE *arg);
extern NODE *lradiobuttonset(NODE *args);
extern NODE *lradiobuttonget(NODE *arg);
extern NODE *lcheckboxcreate(NODE *args);
extern NODE *lcheckboxenable(NODE *args);
extern NODE *lcheckboxdelete(NODE *arg);
extern NODE *lcheckboxset(NODE *args);
extern NODE *lcheckboxget(NODE *arg);
extern NODE *ldialogfileopen(NODE *arg);
extern NODE *ldialogfilesave(NODE *arg);
extern NODE *lwindowfileedit(NODE *arg);

extern LPCSTR WSAGetLastErrorString(int);

typedef int (CALLBACK * LPWSAASYNCSELECT) (SOCKET, HWND, u_int, long);
typedef int (CALLBACK *LPCONNECT) (SOCKET, const struct sockaddr FAR *, int);
typedef int (CALLBACK *LPRECV) (SOCKET, char FAR *, int, int);
typedef int (CALLBACK *LPWSAGETLASTERROR) (void);
typedef SOCKET(CALLBACK *LPACCEPT) (SOCKET, struct sockaddr FAR *, int FAR *);
typedef u_short(CALLBACK *LPHTONS) (u_short);
typedef int (CALLBACK *LPBIND) (SOCKET, const struct sockaddr FAR *, int);
typedef int (CALLBACK *LPLISTEN) (SOCKET, int);
typedef int (CALLBACK *LPCLOSESOCKET) (SOCKET);
typedef int (CALLBACK *LPSEND) (SOCKET, const char FAR *, int, int);
typedef int (CALLBACK *LPSHUTDOWN) (SOCKET, int);
typedef SOCKET (CALLBACK *LPSOCKET) (int, int, int);
typedef int (CALLBACK *LPGETHOSTNAME) (char FAR * name, int namelen);
typedef struct hostent FAR * (CALLBACK *LPGETHOSTBYNAME) (const char FAR *);
typedef int (CALLBACK *LPWSASTARTUP) (WORD, LPWSADATA);
typedef int (CALLBACK *LPWSACLEANUP)();
typedef void (CALLBACK *LPWSASETLASTERROR) (int);
typedef HANDLE(CALLBACK *LPWSAASYNCGETHOSTBYNAME) (HWND, u_int, const char FAR *, char FAR *, int);

extern LPWSAASYNCSELECT lpWSAAsyncSelect;
extern LPCONNECT lpconnect;
extern LPRECV lprecv;
extern LPWSAGETLASTERROR lpWSAGetLastError;
extern LPACCEPT lpaccept;
extern LPHTONS lphtons;
extern LPBIND lpbind;
extern LPLISTEN lplisten;
extern LPCLOSESOCKET lpclosesocket;
extern LPSEND lpsend;
extern LPSHUTDOWN lpshutdown;
extern LPSOCKET lpsocket;
extern LPGETHOSTNAME lpgethostname;
extern LPGETHOSTBYNAME lpgethostbyname;
extern LPWSASTARTUP lpWSAStartup;
extern LPWSACLEANUP lpWSACleanup;
extern LPWSASETLASTERROR lpWSASetLastError;
extern LPWSAASYNCGETHOSTBYNAME lpWSAAsyncGetHostByName;

