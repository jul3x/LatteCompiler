/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include "Printer.H"
#define INDENT_WIDTH 2


//You may wish to change render
void PrintAbsyn::render(Char c)
{
  if (c == '{')
  {
     bufAppend('\n');
     indent();
     bufAppend(c);
     _n_ = _n_ + INDENT_WIDTH;
     bufAppend('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppend(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppend(c);
  }
  else if (c == '}')
  {
     int t;
     _n_ = _n_ - INDENT_WIDTH;
     for (t=0; t<INDENT_WIDTH; t++) {
       backup();
     }
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == ',')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == ';')
  {
     backup();
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == 0) return;
  else
  {
     bufAppend(' ');
     bufAppend(c);
     bufAppend(' ');
  }
}

void PrintAbsyn::render(String s_)
{
  const char *s = s_.c_str() ;
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::render(char *s)
{
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}

void PrintAbsyn::indent()
{
  int n = _n_;
  while (n > 0)
  {
    bufAppend(' ');
    n--;
  }
}

void PrintAbsyn::backup()
{
  if (buf_[cur_ - 1] == ' ')
  {
    buf_[cur_ - 1] = 0;
    cur_--;
  }
}

PrintAbsyn::PrintAbsyn(void)
{
  _i_ = 0; _n_ = 0;
  buf_ = 0;
  bufReset();
}

PrintAbsyn::~PrintAbsyn(void)
{
}

char *PrintAbsyn::print(Visitable *v)
{
  _i_ = 0; _n_ = 0;
  bufReset();
  v->accept(this);
  return buf_;
}

void PrintAbsyn::visitProgram(Program *p) {} //abstract class

void PrintAbsyn::visitProg(Prog *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  if(p->listtopdef_) {_i_ = 0; p->listtopdef_->accept(this);}

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitTopDef(TopDef *p) {} //abstract class

void PrintAbsyn::visitFnDef(FnDef *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);
  render('(');
  if(p->listarg_) {_i_ = 0; p->listarg_->accept(this);}
  render(')');
  _i_ = 0; p->block_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitClsDef(ClsDef *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("class");
  visitIdent(p->ident_);
  render('{');
  if(p->listclsfld_) {_i_ = 0; p->listclsfld_->accept(this);}
  render('}');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitInhClsDef(InhClsDef *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("class");
  visitIdent(p->ident_1);
  render("extends");
  visitIdent(p->ident_2);
  render('{');
  if(p->listclsfld_) {_i_ = 0; p->listclsfld_->accept(this);}
  render('}');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListClsFld(ListClsFld *listclsfld)
{
  for (ListClsFld::const_iterator i = listclsfld->begin() ; i != listclsfld->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listclsfld->end() - 1) render("");
  }
}void PrintAbsyn::visitListTopDef(ListTopDef *listtopdef)
{
  for (ListTopDef::const_iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listtopdef->end() - 1) render("");
  }
}void PrintAbsyn::visitClsFld(ClsFld *p) {} //abstract class

void PrintAbsyn::visitVarDef(VarDef *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->type_->accept(this);
  if(p->listident_) {_i_ = 0; p->listident_->accept(this);}
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitMetDef(MetDef *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);
  render('(');
  if(p->listarg_) {_i_ = 0; p->listarg_->accept(this);}
  render(')');
  _i_ = 0; p->block_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListIdent(ListIdent *listident)
{
  for (ListIdent::const_iterator i = listident->begin() ; i != listident->end() ; ++i)
  {
    visitIdent(*i) ;
    if (i != listident->end() - 1) render(',');
  }
}void PrintAbsyn::visitArg(Arg *p) {} //abstract class

void PrintAbsyn::visitAr(Ar *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListArg(ListArg *listarg)
{
  for (ListArg::const_iterator i = listarg->begin() ; i != listarg->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listarg->end() - 1) render(',');
  }
}void PrintAbsyn::visitBlock(Block *p) {} //abstract class

void PrintAbsyn::visitBlk(Blk *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('{');
  if(p->liststmt_) {_i_ = 0; p->liststmt_->accept(this);}
  render('}');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListStmt(ListStmt *liststmt)
{
  for (ListStmt::const_iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
    render("");
  }
}void PrintAbsyn::visitStmt(Stmt *p) {} //abstract class

void PrintAbsyn::visitEmpty(Empty *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBStmt(BStmt *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->block_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDecl(Decl *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->type_->accept(this);
  if(p->listitem_) {_i_ = 0; p->listitem_->accept(this);}
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitAss(Ass *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->expr_1->accept(this);
  render('=');
  _i_ = 0; p->expr_2->accept(this);
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitIncr(Incr *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->expr_->accept(this);
  render("++");
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDecr(Decr *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->expr_->accept(this);
  render("--");
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitRet(Ret *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("return");
  _i_ = 0; p->expr_->accept(this);
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitVRet(VRet *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("return");
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitCond(Cond *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("if");
  render('(');
  _i_ = 0; p->expr_->accept(this);
  render(')');
  _i_ = 0; p->stmt_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitCondElse(CondElse *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("if");
  render('(');
  _i_ = 0; p->expr_->accept(this);
  render(')');
  _i_ = 0; p->stmt_1->accept(this);
  render("else");
  _i_ = 0; p->stmt_2->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitWhile(While *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("while");
  render('(');
  _i_ = 0; p->expr_->accept(this);
  render(')');
  _i_ = 0; p->stmt_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitFor(For *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("for");
  render('(');
  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);
  render(':');
  _i_ = 0; p->expr_->accept(this);
  render(')');
  _i_ = 0; p->stmt_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSExp(SExp *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->expr_->accept(this);
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitItem(Item *p) {} //abstract class

void PrintAbsyn::visitNoInit(NoInit *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitInit(Init *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);
  render('=');
  _i_ = 0; p->expr_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListItem(ListItem *listitem)
{
  for (ListItem::const_iterator i = listitem->begin() ; i != listitem->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listitem->end() - 1) render(',');
  }
}void PrintAbsyn::visitStdType(StdType *p) {} //abstract class

void PrintAbsyn::visitInt(Int *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("int");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitStr(Str *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("string");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBool(Bool *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("boolean");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitVoid(Void *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("void");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitType(Type *p) {} //abstract class

void PrintAbsyn::visitStVarType(StVarType *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->stdtype_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitStArrType(StArrType *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->stdtype_->accept(this);
  render("[]");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitVarType(VarType *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitArrType(ArrType *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);
  render("[]");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitFun(Fun *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  /* Internal Category */

  _i_ = 0; p->type_->accept(this);
  render('(');
  if(p->listtype_) {_i_ = 0; p->listtype_->accept(this);}
  render(')');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListType(ListType *listtype)
{
  for (ListType::const_iterator i = listtype->begin() ; i != listtype->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listtype->end() - 1) render(',');
  }
}void PrintAbsyn::visitExpr(Expr *p) {} //abstract class

void PrintAbsyn::visitEVar(EVar *p)
{
  int oldi = _i_;
  if (oldi > 8) render(_L_PAREN);

  visitIdent(p->ident_);

  if (oldi > 8) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEClsVar(EClsVar *p)
{
  int oldi = _i_;
  if (oldi > 8) render(_L_PAREN);

  _i_ = 8; p->expr_->accept(this);
  render('.');
  visitIdent(p->ident_);

  if (oldi > 8) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEArrVar(EArrVar *p)
{
  int oldi = _i_;
  if (oldi > 8) render(_L_PAREN);

  _i_ = 8; p->expr_1->accept(this);
  render('[');
  _i_ = 0; p->expr_2->accept(this);
  render(']');

  if (oldi > 8) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitELitInt(ELitInt *p)
{
  int oldi = _i_;
  if (oldi > 8) render(_L_PAREN);

  visitInteger(p->integer_);

  if (oldi > 8) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEString(EString *p)
{
  int oldi = _i_;
  if (oldi > 8) render(_L_PAREN);

  visitString(p->string_);

  if (oldi > 8) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitELitTrue(ELitTrue *p)
{
  int oldi = _i_;
  if (oldi > 8) render(_L_PAREN);

  render("true");

  if (oldi > 8) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitELitFalse(ELitFalse *p)
{
  int oldi = _i_;
  if (oldi > 8) render(_L_PAREN);

  render("false");

  if (oldi > 8) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitELitNull(ELitNull *p)
{
  int oldi = _i_;
  if (oldi > 8) render(_L_PAREN);

  render("null");

  if (oldi > 8) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEApp(EApp *p)
{
  int oldi = _i_;
  if (oldi > 8) render(_L_PAREN);

  visitIdent(p->ident_);
  render('(');
  if(p->listexpr_) {_i_ = 0; p->listexpr_->accept(this);}
  render(')');

  if (oldi > 8) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEClsApp(EClsApp *p)
{
  int oldi = _i_;
  if (oldi > 8) render(_L_PAREN);

  _i_ = 8; p->expr_->accept(this);
  render('.');
  visitIdent(p->ident_);
  render('(');
  if(p->listexpr_) {_i_ = 0; p->listexpr_->accept(this);}
  render(')');

  if (oldi > 8) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitENeg(ENeg *p)
{
  int oldi = _i_;
  if (oldi > 7) render(_L_PAREN);

  render('-');
  _i_ = 8; p->expr_->accept(this);

  if (oldi > 7) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitENot(ENot *p)
{
  int oldi = _i_;
  if (oldi > 7) render(_L_PAREN);

  render('!');
  _i_ = 8; p->expr_->accept(this);

  if (oldi > 7) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEVarNew(EVarNew *p)
{
  int oldi = _i_;
  if (oldi > 6) render(_L_PAREN);

  render("new");
  visitIdent(p->ident_);

  if (oldi > 6) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEVStdNew(EVStdNew *p)
{
  int oldi = _i_;
  if (oldi > 6) render(_L_PAREN);

  render("new");
  _i_ = 0; p->stdtype_->accept(this);

  if (oldi > 6) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEArrNew(EArrNew *p)
{
  int oldi = _i_;
  if (oldi > 6) render(_L_PAREN);

  render("new");
  visitIdent(p->ident_);
  render('[');
  _i_ = 0; p->expr_->accept(this);
  render(']');

  if (oldi > 6) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEAStdNew(EAStdNew *p)
{
  int oldi = _i_;
  if (oldi > 6) render(_L_PAREN);

  render("new");
  _i_ = 0; p->stdtype_->accept(this);
  render('[');
  _i_ = 0; p->expr_->accept(this);
  render(']');

  if (oldi > 6) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEVarCast(EVarCast *p)
{
  int oldi = _i_;
  if (oldi > 5) render(_L_PAREN);

  render('(');
  visitIdent(p->ident_);
  render(')');
  _i_ = 5; p->expr_->accept(this);

  if (oldi > 5) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEVStdCast(EVStdCast *p)
{
  int oldi = _i_;
  if (oldi > 5) render(_L_PAREN);

  render('(');
  _i_ = 0; p->stdtype_->accept(this);
  render(')');
  _i_ = 5; p->expr_->accept(this);

  if (oldi > 5) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEArrCast(EArrCast *p)
{
  int oldi = _i_;
  if (oldi > 5) render(_L_PAREN);

  render('(');
  visitIdent(p->ident_);
  render("[]");
  render(')');
  _i_ = 5; p->expr_->accept(this);

  if (oldi > 5) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEAStdCast(EAStdCast *p)
{
  int oldi = _i_;
  if (oldi > 5) render(_L_PAREN);

  render('(');
  _i_ = 0; p->stdtype_->accept(this);
  render("[]");
  render(')');
  _i_ = 5; p->expr_->accept(this);

  if (oldi > 5) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEMul(EMul *p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  _i_ = 4; p->expr_1->accept(this);
  _i_ = 0; p->mulop_->accept(this);
  _i_ = 5; p->expr_2->accept(this);

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEAdd(EAdd *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  _i_ = 3; p->expr_1->accept(this);
  _i_ = 0; p->addop_->accept(this);
  _i_ = 4; p->expr_2->accept(this);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitERel(ERel *p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 2; p->expr_1->accept(this);
  _i_ = 0; p->relop_->accept(this);
  _i_ = 3; p->expr_2->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEAnd(EAnd *p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 2; p->expr_1->accept(this);
  render("&&");
  _i_ = 1; p->expr_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEOr(EOr *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 1; p->expr_1->accept(this);
  render("||");
  _i_ = 0; p->expr_2->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListExpr(ListExpr *listexpr)
{
  for (ListExpr::const_iterator i = listexpr->begin() ; i != listexpr->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listexpr->end() - 1) render(',');
  }
}void PrintAbsyn::visitAddOp(AddOp *p) {} //abstract class

void PrintAbsyn::visitPlus(Plus *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('+');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitMinus(Minus *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('-');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitMulOp(MulOp *p) {} //abstract class

void PrintAbsyn::visitTimes(Times *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('*');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDiv(Div *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('/');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitMod(Mod *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('%');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitRelOp(RelOp *p) {} //abstract class

void PrintAbsyn::visitLTH(LTH *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('<');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitLE(LE *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("<=");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitGTH(GTH *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('>');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitGE(GE *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render(">=");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEQU(EQU *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("==");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitNE(NE *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("!=");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}

void PrintAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}

void PrintAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}

void PrintAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}

void PrintAbsyn::visitIdent(String s)
{
  render(s);
}

ShowAbsyn::ShowAbsyn(void)
{
  buf_ = 0;
  bufReset();
}

ShowAbsyn::~ShowAbsyn(void)
{
}

char *ShowAbsyn::show(Visitable *v)
{
  bufReset();
  v->accept(this);
  return buf_;
}

void ShowAbsyn::visitProgram(Program *p) {} //abstract class

void ShowAbsyn::visitProg(Prog *p)
{
  bufAppend('(');
  bufAppend("Prog");
  bufAppend(' ');
  bufAppend('[');
  if (p->listtopdef_)  p->listtopdef_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitTopDef(TopDef *p) {} //abstract class

void ShowAbsyn::visitFnDef(FnDef *p)
{
  bufAppend('(');
  bufAppend("FnDef");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listarg_)  p->listarg_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->block_)  p->block_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitClsDef(ClsDef *p)
{
  bufAppend('(');
  bufAppend("ClsDef");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listclsfld_)  p->listclsfld_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitInhClsDef(InhClsDef *p)
{
  bufAppend('(');
  bufAppend("InhClsDef");
  bufAppend(' ');
  visitIdent(p->ident_1);
  bufAppend(' ');
  visitIdent(p->ident_2);
  bufAppend(' ');
  bufAppend('[');
  if (p->listclsfld_)  p->listclsfld_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitListClsFld(ListClsFld *listclsfld)
{
  for (ListClsFld::const_iterator i = listclsfld->begin() ; i != listclsfld->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listclsfld->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitListTopDef(ListTopDef *listtopdef)
{
  for (ListTopDef::const_iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listtopdef->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitClsFld(ClsFld *p) {} //abstract class

void ShowAbsyn::visitVarDef(VarDef *p)
{
  bufAppend('(');
  bufAppend("VarDef");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->listident_)  p->listident_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitMetDef(MetDef *p)
{
  bufAppend('(');
  bufAppend("MetDef");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listarg_)  p->listarg_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->block_)  p->block_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitListIdent(ListIdent *listident)
{
  for (ListIdent::const_iterator i = listident->begin() ; i != listident->end() ; ++i)
  {
    visitIdent(*i) ;
    if (i != listident->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitArg(Arg *p) {} //abstract class

void ShowAbsyn::visitAr(Ar *p)
{
  bufAppend('(');
  bufAppend("Ar");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitListArg(ListArg *listarg)
{
  for (ListArg::const_iterator i = listarg->begin() ; i != listarg->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listarg->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitBlock(Block *p) {} //abstract class

void ShowAbsyn::visitBlk(Blk *p)
{
  bufAppend('(');
  bufAppend("Blk");
  bufAppend(' ');
  bufAppend('[');
  if (p->liststmt_)  p->liststmt_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitListStmt(ListStmt *liststmt)
{
  for (ListStmt::const_iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != liststmt->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitStmt(Stmt *p) {} //abstract class

void ShowAbsyn::visitEmpty(Empty *p)
{
  bufAppend("Empty");
}
void ShowAbsyn::visitBStmt(BStmt *p)
{
  bufAppend('(');
  bufAppend("BStmt");
  bufAppend(' ');
  bufAppend('[');
  if (p->block_)  p->block_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitDecl(Decl *p)
{
  bufAppend('(');
  bufAppend("Decl");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->listitem_)  p->listitem_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitAss(Ass *p)
{
  bufAppend('(');
  bufAppend("Ass");
  bufAppend(' ');
  p->expr_1->accept(this);
  bufAppend(' ');
  p->expr_2->accept(this);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitIncr(Incr *p)
{
  bufAppend('(');
  bufAppend("Incr");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitDecr(Decr *p)
{
  bufAppend('(');
  bufAppend("Decr");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitRet(Ret *p)
{
  bufAppend('(');
  bufAppend("Ret");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitVRet(VRet *p)
{
  bufAppend("VRet");
}
void ShowAbsyn::visitCond(Cond *p)
{
  bufAppend('(');
  bufAppend("Cond");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->stmt_)  p->stmt_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitCondElse(CondElse *p)
{
  bufAppend('(');
  bufAppend("CondElse");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  p->stmt_1->accept(this);
  bufAppend(' ');
  p->stmt_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitWhile(While *p)
{
  bufAppend('(');
  bufAppend("While");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->stmt_)  p->stmt_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitFor(For *p)
{
  bufAppend('(');
  bufAppend("For");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->stmt_)  p->stmt_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitSExp(SExp *p)
{
  bufAppend('(');
  bufAppend("SExp");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitItem(Item *p) {} //abstract class

void ShowAbsyn::visitNoInit(NoInit *p)
{
  bufAppend('(');
  bufAppend("NoInit");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitInit(Init *p)
{
  bufAppend('(');
  bufAppend("Init");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitListItem(ListItem *listitem)
{
  for (ListItem::const_iterator i = listitem->begin() ; i != listitem->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listitem->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitStdType(StdType *p) {} //abstract class

void ShowAbsyn::visitInt(Int *p)
{
  bufAppend("Int");
}
void ShowAbsyn::visitStr(Str *p)
{
  bufAppend("Str");
}
void ShowAbsyn::visitBool(Bool *p)
{
  bufAppend("Bool");
}
void ShowAbsyn::visitVoid(Void *p)
{
  bufAppend("Void");
}
void ShowAbsyn::visitType(Type *p) {} //abstract class

void ShowAbsyn::visitStVarType(StVarType *p)
{
  bufAppend('(');
  bufAppend("StVarType");
  bufAppend(' ');
  bufAppend('[');
  if (p->stdtype_)  p->stdtype_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitStArrType(StArrType *p)
{
  bufAppend('(');
  bufAppend("StArrType");
  bufAppend(' ');
  bufAppend('[');
  if (p->stdtype_)  p->stdtype_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitVarType(VarType *p)
{
  bufAppend('(');
  bufAppend("VarType");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitArrType(ArrType *p)
{
  bufAppend('(');
  bufAppend("ArrType");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitFun(Fun *p)
{
  bufAppend('(');
  bufAppend("Fun");
  bufAppend(' ');
/* Internal Category */
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->listtype_)  p->listtype_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitListType(ListType *listtype)
{
  for (ListType::const_iterator i = listtype->begin() ; i != listtype->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listtype->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitExpr(Expr *p) {} //abstract class

void ShowAbsyn::visitEVar(EVar *p)
{
  bufAppend('(');
  bufAppend("EVar");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitEClsVar(EClsVar *p)
{
  bufAppend('(');
  bufAppend("EClsVar");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitEArrVar(EArrVar *p)
{
  bufAppend('(');
  bufAppend("EArrVar");
  bufAppend(' ');
  p->expr_1->accept(this);
  bufAppend(' ');
  p->expr_2->accept(this);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitELitInt(ELitInt *p)
{
  bufAppend('(');
  bufAppend("ELitInt");
  bufAppend(' ');
  visitInteger(p->integer_);
  bufAppend(')');
}
void ShowAbsyn::visitEString(EString *p)
{
  bufAppend('(');
  bufAppend("EString");
  bufAppend(' ');
  visitString(p->string_);
  bufAppend(')');
}
void ShowAbsyn::visitELitTrue(ELitTrue *p)
{
  bufAppend("ELitTrue");
}
void ShowAbsyn::visitELitFalse(ELitFalse *p)
{
  bufAppend("ELitFalse");
}
void ShowAbsyn::visitELitNull(ELitNull *p)
{
  bufAppend("ELitNull");
}
void ShowAbsyn::visitEApp(EApp *p)
{
  bufAppend('(');
  bufAppend("EApp");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listexpr_)  p->listexpr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitEClsApp(EClsApp *p)
{
  bufAppend('(');
  bufAppend("EClsApp");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listexpr_)  p->listexpr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitENeg(ENeg *p)
{
  bufAppend('(');
  bufAppend("ENeg");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitENot(ENot *p)
{
  bufAppend('(');
  bufAppend("ENot");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEVarNew(EVarNew *p)
{
  bufAppend('(');
  bufAppend("EVarNew");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitEVStdNew(EVStdNew *p)
{
  bufAppend('(');
  bufAppend("EVStdNew");
  bufAppend(' ');
  bufAppend('[');
  if (p->stdtype_)  p->stdtype_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEArrNew(EArrNew *p)
{
  bufAppend('(');
  bufAppend("EArrNew");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitEAStdNew(EAStdNew *p)
{
  bufAppend('(');
  bufAppend("EAStdNew");
  bufAppend(' ');
  bufAppend('[');
  if (p->stdtype_)  p->stdtype_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitEVarCast(EVarCast *p)
{
  bufAppend('(');
  bufAppend("EVarCast");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEVStdCast(EVStdCast *p)
{
  bufAppend('(');
  bufAppend("EVStdCast");
  bufAppend(' ');
  bufAppend('[');
  if (p->stdtype_)  p->stdtype_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEArrCast(EArrCast *p)
{
  bufAppend('(');
  bufAppend("EArrCast");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEAStdCast(EAStdCast *p)
{
  bufAppend('(');
  bufAppend("EAStdCast");
  bufAppend(' ');
  bufAppend('[');
  if (p->stdtype_)  p->stdtype_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEMul(EMul *p)
{
  bufAppend('(');
  bufAppend("EMul");
  bufAppend(' ');
  p->expr_1->accept(this);
  bufAppend(' ');
  bufAppend('[');
  if (p->mulop_)  p->mulop_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  p->expr_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEAdd(EAdd *p)
{
  bufAppend('(');
  bufAppend("EAdd");
  bufAppend(' ');
  p->expr_1->accept(this);
  bufAppend(' ');
  bufAppend('[');
  if (p->addop_)  p->addop_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  p->expr_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitERel(ERel *p)
{
  bufAppend('(');
  bufAppend("ERel");
  bufAppend(' ');
  p->expr_1->accept(this);
  bufAppend(' ');
  bufAppend('[');
  if (p->relop_)  p->relop_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  p->expr_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEAnd(EAnd *p)
{
  bufAppend('(');
  bufAppend("EAnd");
  bufAppend(' ');
  p->expr_1->accept(this);
  bufAppend(' ');
  p->expr_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEOr(EOr *p)
{
  bufAppend('(');
  bufAppend("EOr");
  bufAppend(' ');
  p->expr_1->accept(this);
  bufAppend(' ');
  p->expr_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitListExpr(ListExpr *listexpr)
{
  for (ListExpr::const_iterator i = listexpr->begin() ; i != listexpr->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listexpr->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitAddOp(AddOp *p) {} //abstract class

void ShowAbsyn::visitPlus(Plus *p)
{
  bufAppend("Plus");
}
void ShowAbsyn::visitMinus(Minus *p)
{
  bufAppend("Minus");
}
void ShowAbsyn::visitMulOp(MulOp *p) {} //abstract class

void ShowAbsyn::visitTimes(Times *p)
{
  bufAppend("Times");
}
void ShowAbsyn::visitDiv(Div *p)
{
  bufAppend("Div");
}
void ShowAbsyn::visitMod(Mod *p)
{
  bufAppend("Mod");
}
void ShowAbsyn::visitRelOp(RelOp *p) {} //abstract class

void ShowAbsyn::visitLTH(LTH *p)
{
  bufAppend("LTH");
}
void ShowAbsyn::visitLE(LE *p)
{
  bufAppend("LE");
}
void ShowAbsyn::visitGTH(GTH *p)
{
  bufAppend("GTH");
}
void ShowAbsyn::visitGE(GE *p)
{
  bufAppend("GE");
}
void ShowAbsyn::visitEQU(EQU *p)
{
  bufAppend("EQU");
}
void ShowAbsyn::visitNE(NE *p)
{
  bufAppend("NE");
}
void ShowAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
void ShowAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
void ShowAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
void ShowAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
void ShowAbsyn::visitIdent(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}


