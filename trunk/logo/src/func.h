/* File IBMTERM.CPP: */

extern void single_step_box(NODE *the_line);
extern void checkqueue(void);
extern void emptyqueue(void);
extern void do_help(char *arg);
extern void checkwindow(int *x, int *y, int *w, int *h);
extern BOOL MyBeep(DWORD dwFreq, DWORD dwDuration);
void Myoutportb(short portid, unsigned char value);
unsigned char Myinportb(short portid);
void Myoutport(short portid, short value);
short Myinport(short portid);
short Myingameport (short portid, short mask);

extern void gr_mode(void);             /*routine                              */
extern void ibm_prepare_to_draw_turtle(void);
extern void ibm_done_drawing_turtle(void);
extern void nop(void);
extern void init_ibm_memory(void);
extern BOOLEANx check_ibm_stop(int scan);
extern void term_init_ibm(void);
extern void ibm_gotoxy(int x, int y);
extern void ibm_clear_text(void);
extern void ibm_clear_screen(void);
extern void ibm_plain_mode(void);
extern void ibm_bold_mode(void);
extern void erase_graphics_top(void);
extern void save_pen(pen_info *p);
extern void restore_pen(pen_info *p);
extern void plain_xor_pen(void);
extern void ibm_pen_down(void);
extern void ibm_pen_xor(void);
extern void ibm_pen_erase(void);
extern int get_ibm_pen_mode(void);
extern void set_ibm_pen_mode(int m);
extern int get_ibm_pen_width(void);
extern void set_ibm_pen_width(int w);
extern void set_pen_pattern(char *pat);
extern void set_list_pen_pattern(NODE *arg);
extern void get_pen_pattern(char *pat);
extern NODE *Get_node_pen_pattern(void);
extern NODE *Get_node_pen_mode(void);
extern void label(char *s);
extern SIZE labelsize(char *s);
extern void logofill(BOOL bOld);
extern void erase_screen(void);
extern void t_screen(void);
extern void s_screen(void);
extern void f_screen(void);
extern FIXNUM mickey_x(void);
extern FIXNUM mickey_y(void);
extern BOOLEANx Button(void);
extern void tone(FIXNUM pitch, FIXNUM duration);
extern FIXNUM t_height(void);
extern FLONUM t_half_bottom(void);
extern FLONUM t_side(void);
extern void check_scroll(void);

/* File WRKSP.CPP: */

extern NODE *make_procnode(NODE *lst, NODE *wrds, short min, short df, short max);
extern NODE *get_bodywords(NODE *proc, NODE *name);
extern NODE *name_arg(NODE *args);
extern NODE *ltext(NODE *args);
extern NODE *lfulltext(NODE *args);
extern NODE *define_helper(NODE *args, BOOLEANx macro_flag);
extern NODE *ldefine(NODE *args);
extern NODE *ldefmacro(NODE *args);
extern NODE *anonymous_function(NODE *text);
extern NODE *to_helper(NODE *args, BOOLEANx macro_flag);
extern NODE *lto(NODE *args);
extern NODE *lmacro(NODE *args);
extern NODE *lmake(NODE *args);
extern NODE *llocal(NODE *args);
extern int bck(int flag);
extern void contents_map(NODE *sym);
extern void zigzag(NODE *nd);
extern NODE *merge(NODE *a, NODE *b);
extern NODE *mergesort(NODE *nd);
extern NODE *get_contents(void);
extern NODE *lcontents(void);
extern NODE *lstepped(void);
extern NODE *ltraced(void);
extern NODE *lburied(void);
extern NODE *lprocedures(void);
extern NODE *lnames(void);
extern NODE *lplists(void);
extern NODE *one_list(NODE *nd);
extern void three_lists(NODE *arg, NODE **proclst, NODE **varlst, NODE **plistlst);
extern NODE *po_helper(NODE *arg, int just_titles);
extern NODE *lpo(NODE *arg);
extern NODE *lpot(NODE *arg);
extern NODE *lerase(NODE *arg);
extern NODE *bury_helper(NODE *arg, int flag);
extern NODE *lbury(NODE *arg);
extern NODE *ltrace(NODE *arg);
//extern NODE *lsilent();
extern NODE *lstep(NODE *arg);
extern NODE *unbury_helper(NODE *arg, int flag);
extern NODE *lunbury(NODE *arg);
extern NODE *luntrace(NODE *arg);
extern NODE *lunstep(NODE *arg);
//extern NODE *lunsilent();
extern NODE *ledit(NODE *args);
extern int lendedit(void);
extern NODE *lthing(NODE *args);
extern NODE *lnamep(NODE *args);
extern NODE *lprocedurep(NODE *args);
extern NODE *lproplistp(NODE *args);
extern NODE *check_proctype(NODE *args, int wanted);
extern NODE *lprimitivep(NODE *args);
extern NODE *ldefinedp(NODE *args);
extern NODE *lmacrop(NODE *args);
extern NODE *lcopydef(NODE *args);

/* File GRAPHICS.CPP: */

extern FIXNUM g_round(FLONUM n);
extern NODE *lscrunch(void);
extern double pfmod(double x, double y);
extern FLONUM cut_error(FLONUM n);
extern FIXNUM round(FLONUM n);
extern void draw_turtle(int erase);
extern void draw_turtles(int erase);
extern void right(FLONUM a);
extern void rightroll(FLONUM a);
extern void uppitch(FLONUM a);
extern NODE *numeric_arg(NODE *args);
extern NODE *lright(NODE *arg);
extern NODE *lleft(NODE *arg);
extern NODE *lrightroll(NODE *arg);
extern NODE *lleftroll(NODE *arg);
extern NODE *ldownpitch(NODE *arg);
extern NODE *luppitch(NODE *arg);
extern void forward(FLONUM d);
extern void forward_helper(FLONUM d);
extern void forward_helper3d(FLONUM d);
extern int wrap_right(FLONUM d, FLONUM x1, FLONUM y1, FLONUM x2, FLONUM y2);
extern int wrap_left(FLONUM d, FLONUM x1, FLONUM y1, FLONUM x2, FLONUM y2);
extern int wrap_up(FLONUM d, FLONUM x1, FLONUM y1, FLONUM x2, FLONUM y2);
extern int wrap_down(FLONUM d, FLONUM x1, FLONUM y1, FLONUM x2, FLONUM y2);
extern FLONUM rotation_z();
extern FLONUM rotation_y();
extern FLONUM rotation_x();
extern NODE *lforward(NODE *arg);
extern NODE *lback(NODE *arg);
extern NODE *lshowturtle(void);
extern NODE *lhideturtle(void);
extern NODE *lbitmapturtle(void);
extern NODE *lnobitmapturtle(void);
extern NODE *lshownp(void);
extern NODE *lsetheading(NODE *arg);
extern NODE *lsetroll(NODE *arg);
extern NODE *lsetclip(NODE *arg);
extern NODE *lsetpitch(NODE *arg);
extern NODE *lsetturtle(NODE *arg);
extern NODE *lturtle(void);
extern NODE *lturtles(void);
extern NODE *lheading(void);
extern NODE *lroll(void);
extern NODE *lpitch(void);
extern NODE *vec_arg_helper(NODE *args, BOOLEANx floatok);
extern NODE *vector_arg(NODE *args);
extern NODE *vector_3_arg(NODE *args);
extern NODE *vector_4_arg(NODE *args);
extern NODE *pos_int_vector_arg(NODE *args);
extern NODE *pos_int_vector_3_arg(NODE *args);
extern NODE *pos_int_vector_4_arg(NODE *args);
extern FLONUM towards_helper(FLONUM x, FLONUM y, FLONUM from_x, FLONUM from_y);
extern NODE *ltowards(NODE *args);
extern NODE *ltowardsxyz(NODE *args);
extern NODE *llight(void);
extern NODE *lpos(void);
extern NODE *lposxyz(void);
extern NODE *lhome(void);
extern void cs_helper(int centerp, int clearp);
extern NODE *lclearscreen(void);
extern NODE *lclean(void);
extern void setpos_helper(NODE *xnode, NODE *ynode, NODE *znode, BOOL bEraseTurtle=TRUE);
extern NODE *lsetlight(NODE *args);
extern NODE *lsetpos(NODE *args);
extern NODE *lsetposxyz(NODE *args);
extern NODE *lsetxy(NODE *args);
extern NODE *lsetxyz(NODE *args);
extern NODE *lellipsearc(NODE *args);
extern NODE *lsetx(NODE *args);
extern NODE *lsety(NODE *args);
extern NODE *lsetz(NODE *args);
extern NODE *lwrap(void);
extern NODE *lfence(void);
extern NODE *lwindow(void);
extern NODE *lpolystart(void);
extern NODE *lpolyend();
extern NODE *lpolyview();
extern NODE *lperspective(void);
extern NODE *lfill(NODE *arg);
extern NODE *llabel(NODE *arg);
extern NODE *llabelsize(NODE *arg);
extern NODE *ltextscreen(void);
extern NODE *lsplitscreen(void);
extern NODE *lfullscreen(void);
extern NODE *lpendownp(void);
extern NODE *lpenmode(void);
extern NODE *lpencolor(void);
extern NODE *lpixel(void);
extern NODE *lsetpixel(NODE *args);
extern NODE *lfloodcolor(void);
extern NODE *lscreencolor(void);
extern NODE *lpensize(void);
extern NODE *lpenpattern(void);
extern NODE *lpendown(void);
extern NODE *lpenup(void);
extern NODE *lpenpaint(void);
extern NODE *lpenerase(void);
extern NODE *lpenreverse(void);
extern NODE *lclearpalette(void);
extern NODE *lbitload(NODE *arg);
extern NODE *lbitloadsize(NODE *arg);
extern NODE *lbitsize(void);
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
extern NODE *lbitpaste(void);
extern NODE *lbitpastetoindex(NODE *arg);
extern NODE *lbitmode(void);
extern NODE *lturtlemode(void);
extern NODE *lmachine(void);
extern NODE *lsetbitmode(NODE *arg);
extern NODE *lsetturtlemode(NODE *arg);
extern NODE *lbitindex(void);
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
extern NODE *lmousepos(void);
extern NODE *lkeyboardvalue(void);
extern NODE *lbuttonp(void);
extern NODE *ltone(NODE *args);
extern BOOLEANx safe_to_save(void);
extern void save_lm_helper(void);
extern void save_line(void);
extern void save_move(void);
extern void save_vis(void);
extern void save_mode(void);
extern void save_color_pen(void);
extern void save_color_screen(void);
extern void save_color_flood(void);
extern void save_size(void);
extern void save_pattern(void);
extern void save_string(char s[]);
extern NODE *lrefresh(void);
extern NODE *lnorefresh(void);
extern void redraw_graphics(void);
extern void resize_record(int dh, int dv);

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
extern int TMyWindow_MyPopupEdit(char *FileName, NODE *args);
extern void exit_program(void);
extern int promptuser(char *str, char *pmt);
extern void getcombobox(char *str);
extern void transline(LOGPEN &logPen, long modex, FLONUM fromx, FLONUM fromy, FLONUM tox, FLONUM toy);
extern void transline3d(LOGPEN &logPen, long modex, FLONUM fromx, FLONUM fromy, FLONUM fromz, FLONUM tox, FLONUM toy, FLONUM toz);
extern void ibmturt(int hide);
extern void ibmfrom(FLONUM x, FLONUM y);
extern void ibmto(FLONUM x, FLONUM y);
extern void ibmfrom3d(FLONUM x, FLONUM y, FLONUM z);
extern void ibmto3d(FLONUM x, FLONUM y, FLONUM z);
extern void thepencolor(int, int, int);
extern void thefloodcolor(int, int, int);
extern void thescreencolor(int, int, int);
extern struct object *bitcut(struct object *argx, struct object *argy);
extern struct object *bitfit(struct object *argx, struct object *argy);
extern struct object *bitpaste(void);
extern struct object *scrollx(struct object *arg);
extern struct object *scrolly(struct object *arg);

/* File COMS.CPP: */

extern void prepare_to_exit(BOOLEANx okay);
extern NODE *make_cont(enum labels cont, NODE *val);
extern NODE *loutput(NODE *arg);
extern NODE *lstop(void);
extern NODE *lthrow(NODE *arg);
extern NODE *lcatch(NODE *args);
extern NODE *lgoto(NODE *arg);
extern NODE *ltag(NODE *arg);
extern int torf_arg(NODE *args);
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
extern NODE *lrepcount(void);
extern NODE *lforever(NODE *args);
extern NODE *ltest(NODE *args);
extern NODE *liftrue(NODE *args);
extern NODE *liffalse(NODE *args);
extern NODE *lbye(void);
extern NODE *lwait(NODE *args);
extern NODE *leventcheck(void);
extern NODE *ltime(void);
extern NODE *ltimemilli(void);
extern NODE *lshell(NODE *args);

/* File LOGODATA.CPP: */

extern char ecma_set(int ch);
extern char ecma_clear(int ch);
extern int ecma_get(int ch);
extern char *strnzcpy(char *s1, char *s2, int n);
extern char *word_strnzcpy(char *s1, NODE *kludge, int n);
extern char *noparity_strnzcpy(char *s1, char *s2, int n);
extern char *mend_strnzcpy(char *s1, char *s2, int n);
extern char *mend_nosemi(char *s1, char *s2, int n);
extern char *quote_strnzcpy(char *s1, char *s2, int n);
extern char *colon_strnzcpy(char *s1, char *s2, int n);
extern char *low_strnzcpy(char *s1, char *s2, int n);
extern char *cap_strnzcpy(char *s1, char *s2, int n);
extern char *noparitylow_strnzcpy(char *s1, char *s2, int n);
extern int low_strncmp(char *s1, char *s2, int n);
extern int noparity_strncmp(char *s1, char *s2, int n);
extern int noparitylow_strncmp(char *s1, char *s2, int n);
extern NODE *make_strnode(char *strptr, char *strhead, int len, NODETYPES typ, char * (*copy_routine) (char *, char *, int));
extern void make_runparse(NODE *ndi);
extern NODE *make_quote(NODE *qnd);
extern NODE *maybe_quote(NODE *nd);
extern NODE *make_caseobj(NODE *cstrnd, NODE *obj);
extern NODE *make_colon(NODE *cnd);
extern NODE *make_intnode(FIXNUM i);
extern NODE *make_floatnode(FLONUM f);
extern NODE *cnv_node_to_numnode(NODE *ndi);
extern NODE *cnv_node_to_strnode(NODE *nd);
extern NODE *make_static_strnode(char *strptr);
extern NODE *cons_list(int dummy, ...);
extern NODE *cons_list3(NODE *node1, NODE *node2, NODE *node3);
extern NODE *make_array(int len);
extern NODE *llowercase(NODE *args);
extern NODE *luppercase(NODE *args);
extern NODE *getprop(NODE *plist, NODE *name, BOOLEANx before);
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
extern NODE *lcleartext(void);
extern NODE *lcursor(void);
extern NODE *lsetcursor(NODE *args);
extern NODE *lsetmargins(NODE *args);
extern NODE *lstandout(NODE *args);

/* File PRINT.CPP: */

extern void update_coords(char ch);
extern void print_char(FILE *strm, char ch);
extern void print_space(FILE *strm);
extern void ndprintf(FILE *strm, char *fmt, ...);
extern void real_print_help(FILE *strm, NODE *ndlist, int depth, int width);
extern void real_print_node(FILE *strm, NODE *nd, int depth, int width);
extern int find_limit(NODE *nd);
extern void print_help(FILE *strm, NODE *nd);
extern void print_node(FILE *strm, NODE *nd);
extern void print_nobrak(FILE *strm, NODE *nd);
extern void new_line(FILE *strm);
extern NODE *lshow(NODE *args);
extern void type_help(NODE *args, int sp);
extern NODE *ltype(NODE *args);
extern NODE *lprint(NODE *args);

/* File PARSE.CPP: */

extern int rd_getc(FILE *strm);
extern void rd_print_prompt(char *str);
extern NODE *reader(FILE *strm, char *prompt);
extern NODE *list_to_array(NODE *list);
extern NODE *parser_iterate(char **inln, char *inlimit, char *inhead, BOOLEANx semi, int endchar);
extern NODE *parser(NODE *nd, BOOLEANx semi);
extern NODE *lparse(NODE *args);
extern NODE *runparse_node(NODE *nd, NODE **ndsptr);
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
extern NODE *paren_expr(NODE **expr, BOOLEANx inparen);
extern NODE *gather_args(NODE *proc, NODE **args, BOOLEANx inparen, NODE **ifnode);
extern NODE *gather_some_args(int min, int max, NODE **args, BOOLEANx inparen, NODE **ifnode);
extern int priority(NODE *proc_obj);
extern NODE *paren_infix(NODE *left_arg, NODE **rest, int old_pri, BOOLEANx inparen);

/* File MEM.CPP: */

extern NODETYPES nodetype(NODE *nd);
extern void setobject(NODE *nd, NODE *newobj);
extern void setcar(NODE *nd, NODE *newcar);
extern void setcdr(NODE *nd, NODE *newcdr);
extern NODE *_reref(NODE *proc_var, NODE *newval);
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
extern void handle_oflo(int);
extern void allow_intov(void);
extern double infnan(void);
extern int matherrx(struct exception *x);
extern NODE *binary(NODE *args, char fcn);
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
extern int compare_numnodes(NODE *n1, NODE *n2);
extern NODE *torf(BOOLEANx tf);
extern NODE *llessp(NODE *args);
extern NODE *lgreaterp(NODE *args);
extern int compare_node(NODE *n1, NODE *n2, BOOLEANx ignorecase);
extern BOOLEANx equalp_help(NODE *arg1, NODE *arg2, BOOLEANx ingc);
extern NODE *lequalp(NODE *args);
extern NODE *l_eq(NODE *args);
extern NODE *lbeforep(NODE *args);

/* File MAINX.CPP: */

extern void unblock_input(void);
extern void logo_stop(int);
extern void logo_pause(int);

/* File LISTS.CPP: */

extern NODE *bfable_arg(NODE *args);
extern NODE *list_arg(NODE *args);
extern NODE *lbutfirst(NODE *args);
extern NODE *lbutlast(NODE *args);
extern NODE *lfirst(NODE *args);
extern NODE *lfirsts(NODE *args);
extern NODE *lbfs(NODE *args);
extern NODE *llast(NODE *args);
extern NODE *llist(NODE *args);
extern NODE *lemptyp(NODE *arg);
extern NODE *char_arg(NODE *args);
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
extern NODE *memberp_help(NODE *args, BOOLEANx notp, BOOLEANx substr);
extern NODE *lmemberp(NODE *args);
extern NODE *lsubstringp(NODE *args);
extern NODE *lmember(NODE *args);
extern NODE *integer_arg(NODE *args);
extern FIXNUM int_arg(NODE *args);
extern NODE *litem(NODE *args);
extern int circular(NODE *arr, NODE *newk);
extern NODE *setitem_helper(NODE *args, BOOLEANx safe);
extern NODE *lsetitem(NODE *args);
extern NODE *l_setitem(NODE *args);
extern NODE *larray(NODE *args);
extern FLONUM float_arg(NODE *args);
extern NODE *lform(NODE *args);
extern NODE *lscan(NODE *args);
extern NODE *l_setfirst(NODE *args);
extern NODE *l_setbf(NODE *args);

/* File INTERN.CPP: */

extern void map_oblist(void (*fcn) (NODE *));
extern FIXNUM hash(char *s, int len);
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

extern FILE *open_file(NODE *arg, char *access);
extern NODE *ldribble(NODE *arg);
extern NODE *lnodribble(void);
extern FILE *find_file(NODE *arg, BOOLEANx remove);
extern NODE *lopen(NODE *arg, char *mode);
extern NODE *lopenread(NODE *arg);
extern NODE *lopenwrite(NODE *arg);
extern NODE *lopenappend(NODE *arg);
extern NODE *lopenupdate(NODE *arg);
extern NODE *lallopen(void);
extern NODE *lclose(NODE *arg);
extern NODE *lsetwrite(NODE *arg);
extern NODE *lsetread(NODE *arg);
extern NODE *lreader(void);
extern NODE *lwriter(void);
extern NODE *lerasefile(NODE *arg);
extern void filesave(char *arg);
extern NODE *lsave(NODE *arg);
extern void runstartup(NODE *oldst);
extern void silent_load(NODE *arg, char *prefix);
extern NODE *lload(NODE *arg);
extern void fileload(char *arg);
extern NODE *lreadlist(void);
extern NODE *lreadword(void);
extern NODE *lreadchar(void);
extern NODE *lreadchars(NODE *args);
extern NODE *leofp(void);
extern NODE *lkeyp(void);
extern NODE *lreadpos(void);
extern NODE *lsetreadpos(NODE *arg);
extern NODE *lwritepos(void);
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
extern int not_local(NODE *name, NODE *sp);
extern NODE *reverse(NODE *list);
extern NODE *append(NODE *a, NODE *b);
extern NODE *evaluator(NODE *list, enum labels where);
extern void reset_args(NODE *old_stack);

/* File ERROR.CPP: */

extern void err_print(void);
extern NODE *err_logo(ERR_TYPES error_type, NODE *error_desc);
extern NODE *lerror(void);
extern void bcopy(char *from, char *to, int len);
extern NODE *lpause(void);
extern NODE *lhalt(void);
extern NODE *lyield(void);
extern NODE *lnoyield(void);
extern NODE *lcontinue(NODE *args);

/* File UNIX.CPP: */
extern int printfx(const char *fmt);
extern int printfx(const char *fmt, const char *str);
extern void putcombochar(char c);
extern NODE *lpushdir(NODE *arg);
extern NODE *lpopdir(void);
extern NODE *lmkdir(NODE *arg);
extern NODE *lrmdir(NODE *arg);
extern NODE *ldirectories(void);
extern NODE *lfiles(void);

extern NODE *lpeek(NODE *arg);
extern NODE *lpoke(NODE *arg);

extern NODE *lstatus(void);
extern NODE *lnostatus(void);
extern void zoom_helper(NUMBER temp_zoom);
extern void UpdateZoomControlFlag();
extern NODE *lzoom(NODE *arg);
extern NODE *lmci(NODE *arg);
extern NODE *lmidiopen(NODE *arg);
extern NODE *lmidiclose(NODE *arg);
extern NODE *lmidimessage(NODE *arg);
extern NODE *lsound(NODE *arg);
extern NODE *ldllload(NODE *arg);
extern NODE *ldllcall(NODE *arg);
extern NODE *ldllfree(void);
extern NODE *lplaywave(NODE *args);
extern NODE *lwinhelp(NODE *arg);
extern NODE *lhelp(NODE *arg);
//extern NODE *lsettextsize(NODE *arg);
//extern NODE *lsettextstyle(NODE *arg);
extern NODE *lsetlabelfont(NODE *arg);
extern NODE *llabelfont(void);
extern NODE *lsetactivearea(NODE *arg);
extern NODE *lactivearea(void);
extern void label(char *s);

extern NODE *lportopen(NODE *args);
extern NODE *lportclose(void);
extern NODE *lportreadchar(void);
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
extern NODE *lgetfocus(void);
extern NODE *lwindowset(NODE *args);

extern NODE *lnetreceiveon(NODE *args);
extern NODE *lnetreceiveoff(void);
extern NODE *lnetreceivesendvalue(NODE *args);
extern NODE *lnetreceivereceivevalue(void);
extern NODE *lnetsendon(NODE *args);
extern NODE *lnetsendoff(void);
extern NODE *lnetsendsendvalue(NODE *args);
extern NODE *lnetsendreceivevalue(void);
extern NODE *lnetstartup(NODE *args);
extern NODE *lnetshutdown(void);

extern BOOL CheckOnScreenControls();
extern NODE *ldebugwindows(NODE *args);
extern NODE *lmouseon(NODE *args);
extern NODE *lmouseoff(void);
extern NODE *lkeyboardon(NODE *args);
extern NODE *lkeyboardoff(void);
extern NODE *lmessagebox(NODE *args);
extern NODE *lquestionbox(NODE *args);
extern NODE *lyesnobox(NODE *args);
extern NODE *lselectbox(NODE *args);
extern NODE *lsetcursorwait(void);
extern NODE *lsetcursorarrow(void);
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

extern LPSTR WSAGetLastErrorString(int);

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


