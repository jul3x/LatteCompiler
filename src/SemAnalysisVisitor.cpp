#include "SemAnalysisVisitor.h"


void SemAnalysisVisitor::visitProgram(Program *t)
{
    t->accept(this);
}

void SemAnalysisVisitor::visitTopDef(TopDef *t) {}   //abstract class
void SemAnalysisVisitor::visitClsFld(ClsFld *t) {}   //abstract class
void SemAnalysisVisitor::visitArg(Arg *t) {}         //abstract class
void SemAnalysisVisitor::visitBlock(Block *t) {}     //abstract class
void SemAnalysisVisitor::visitStmt(Stmt *t) {}       //abstract class
void SemAnalysisVisitor::visitItem(Item *t) {}       //abstract class
void SemAnalysisVisitor::visitStdType(StdType *t) {} //abstract class
void SemAnalysisVisitor::visitType(Type *t) {}       //abstract class
void SemAnalysisVisitor::visitExpr(Expr *t) {}       //abstract class
void SemAnalysisVisitor::visitAddOp(AddOp *t) {}     //abstract class
void SemAnalysisVisitor::visitMulOp(MulOp *t) {}     //abstract class
void SemAnalysisVisitor::visitRelOp(RelOp *t) {}     //abstract class

void SemAnalysisVisitor::visitProg(Prog *prog)
{
    /* Code For Prog Goes Here */

    prog->listtopdef_->accept(this);
}

void SemAnalysisVisitor::visitFnDef(FnDef *fn_def)
{
    /* Code For FnDef Goes Here */

    fn_def->type_->accept(this);
    visitIdent(fn_def->ident_);
    fn_def->listarg_->accept(this);
    fn_def->block_->accept(this);
}

void SemAnalysisVisitor::visitClsDef(ClsDef *cls_def)
{
    /* Code For ClsDef Goes Here */

    visitIdent(cls_def->ident_);
    cls_def->listclsfld_->accept(this);
}

void SemAnalysisVisitor::visitInhClsDef(InhClsDef *inh_cls_def)
{
    /* Code For InhClsDef Goes Here */

    visitIdent(inh_cls_def->ident_1);
    visitIdent(inh_cls_def->ident_2);
    inh_cls_def->listclsfld_->accept(this);
}

void SemAnalysisVisitor::visitVarDef(VarDef *var_def)
{
    /* Code For VarDef Goes Here */

    var_def->type_->accept(this);
    var_def->listident_->accept(this);
}

void SemAnalysisVisitor::visitMetDef(MetDef *met_def)
{
    /* Code For MetDef Goes Here */

    met_def->type_->accept(this);
    visitIdent(met_def->ident_);
    met_def->listarg_->accept(this);
    met_def->block_->accept(this);
}

void SemAnalysisVisitor::visitAr(Ar *ar)
{
    /* Code For Ar Goes Here */

    ar->type_->accept(this);
    visitIdent(ar->ident_);
}

void SemAnalysisVisitor::visitBlk(Blk *blk)
{
    /* Code For Blk Goes Here */

    blk->liststmt_->accept(this);
}

void SemAnalysisVisitor::visitEmpty(Empty *empty)
{
    /* Code For Empty Goes Here */
}

void SemAnalysisVisitor::visitBStmt(BStmt *b_stmt)
{
    /* Code For BStmt Goes Here */

    b_stmt->block_->accept(this);
}

void SemAnalysisVisitor::visitDecl(Decl *decl)
{
    /* Code For Decl Goes Here */

    decl->type_->accept(this);
    decl->listitem_->accept(this);
}

void SemAnalysisVisitor::visitAss(Ass *ass)
{
    /* Code For Ass Goes Here */

    ass->expr_1->accept(this);
    ass->expr_2->accept(this);
}

void SemAnalysisVisitor::visitIncr(Incr *incr)
{
    /* Code For Incr Goes Here */

    incr->expr_->accept(this);
}

void SemAnalysisVisitor::visitDecr(Decr *decr)
{
    /* Code For Decr Goes Here */

    decr->expr_->accept(this);
}

void SemAnalysisVisitor::visitRet(Ret *ret)
{
    /* Code For Ret Goes Here */

    ret->expr_->accept(this);
}

void SemAnalysisVisitor::visitVRet(VRet *v_ret)
{
    /* Code For VRet Goes Here */
}

void SemAnalysisVisitor::visitCond(Cond *cond)
{
    /* Code For Cond Goes Here */

    cond->expr_->accept(this);
    cond->stmt_->accept(this);
}

void SemAnalysisVisitor::visitCondElse(CondElse *cond_else)
{
    /* Code For CondElse Goes Here */

    cond_else->expr_->accept(this);
    cond_else->stmt_1->accept(this);
    cond_else->stmt_2->accept(this);
}

void SemAnalysisVisitor::visitWhile(While *while_)
{
    /* Code For While Goes Here */

    while_->expr_->accept(this);
    while_->stmt_->accept(this);
}

void SemAnalysisVisitor::visitFor(For *for_)
{
    /* Code For For Goes Here */

    for_->type_->accept(this);
    visitIdent(for_->ident_);
    for_->expr_->accept(this);
    for_->stmt_->accept(this);
}

void SemAnalysisVisitor::visitSExp(SExp *s_exp)
{
    /* Code For SExp Goes Here */

    s_exp->expr_->accept(this);
}

void SemAnalysisVisitor::visitNoInit(NoInit *no_init)
{
    /* Code For NoInit Goes Here */

    visitIdent(no_init->ident_);
}

void SemAnalysisVisitor::visitInit(Init *init)
{
    /* Code For Init Goes Here */

    visitIdent(init->ident_);
    init->expr_->accept(this);
}

void SemAnalysisVisitor::visitInt(Int *int_)
{
    /* Code For Int Goes Here */
}

void SemAnalysisVisitor::visitStr(Str *str)
{
    /* Code For Str Goes Here */
}

void SemAnalysisVisitor::visitBool(Bool *bool_)
{
    /* Code For Bool Goes Here */
}

void SemAnalysisVisitor::visitVoid(Void *void_)
{
    /* Code For Void Goes Here */
}

void SemAnalysisVisitor::visitStVarType(StVarType *st_var_type)
{
    /* Code For StVarType Goes Here */

    st_var_type->stdtype_->accept(this);
}

void SemAnalysisVisitor::visitStArrType(StArrType *st_arr_type)
{
    /* Code For StArrType Goes Here */

    st_arr_type->stdtype_->accept(this);
}

void SemAnalysisVisitor::visitVarType(VarType *var_type)
{
    /* Code For VarType Goes Here */

    visitIdent(var_type->ident_);
}

void SemAnalysisVisitor::visitArrType(ArrType *arr_type)
{
    /* Code For ArrType Goes Here */

    visitIdent(arr_type->ident_);
}

void SemAnalysisVisitor::visitFun(Fun *fun)
{
    /* Code For Fun Goes Here */

    fun->type_->accept(this);
    fun->listtype_->accept(this);
}

void SemAnalysisVisitor::visitEVar(EVar *e_var)
{
    /* Code For EVar Goes Here */

    visitIdent(e_var->ident_);
}

void SemAnalysisVisitor::visitEClsVar(EClsVar *e_cls_var)
{
    /* Code For EClsVar Goes Here */

    e_cls_var->expr_->accept(this);
    visitIdent(e_cls_var->ident_);
}

void SemAnalysisVisitor::visitEArrVar(EArrVar *e_arr_var)
{
    /* Code For EArrVar Goes Here */

    e_arr_var->expr_1->accept(this);
    e_arr_var->expr_2->accept(this);
}

void SemAnalysisVisitor::visitELitInt(ELitInt *e_lit_int)
{
    /* Code For ELitInt Goes Here */

    visitInteger(e_lit_int->integer_);
}

void SemAnalysisVisitor::visitEString(EString *e_string)
{
    /* Code For EString Goes Here */

    visitString(e_string->string_);
}

void SemAnalysisVisitor::visitELitTrue(ELitTrue *e_lit_true)
{
    /* Code For ELitTrue Goes Here */
}

void SemAnalysisVisitor::visitELitFalse(ELitFalse *e_lit_false)
{
    /* Code For ELitFalse Goes Here */
}

void SemAnalysisVisitor::visitELitNull(ELitNull *e_lit_null)
{
    /* Code For ELitNull Goes Here */
}

void SemAnalysisVisitor::visitEApp(EApp *e_app)
{
    /* Code For EApp Goes Here */

    visitIdent(e_app->ident_);
    e_app->listexpr_->accept(this);
}

void SemAnalysisVisitor::visitEClsApp(EClsApp *e_cls_app)
{
    /* Code For EClsApp Goes Here */

    e_cls_app->expr_->accept(this);
    visitIdent(e_cls_app->ident_);
    e_cls_app->listexpr_->accept(this);
}

void SemAnalysisVisitor::visitENeg(ENeg *e_neg)
{
    /* Code For ENeg Goes Here */

    e_neg->expr_->accept(this);
}

void SemAnalysisVisitor::visitENot(ENot *e_not)
{
    /* Code For ENot Goes Here */

    e_not->expr_->accept(this);
}

void SemAnalysisVisitor::visitEVarNew(EVarNew *e_var_new)
{
    /* Code For EVarNew Goes Here */

    visitIdent(e_var_new->ident_);
}

void SemAnalysisVisitor::visitEVStdNew(EVStdNew *ev_std_new)
{
    /* Code For EVStdNew Goes Here */

    ev_std_new->stdtype_->accept(this);
}

void SemAnalysisVisitor::visitEArrNew(EArrNew *e_arr_new)
{
    /* Code For EArrNew Goes Here */

    visitIdent(e_arr_new->ident_);
    e_arr_new->expr_->accept(this);
}

void SemAnalysisVisitor::visitEAStdNew(EAStdNew *ea_std_new)
{
    /* Code For EAStdNew Goes Here */

    ea_std_new->stdtype_->accept(this);
    ea_std_new->expr_->accept(this);
}

void SemAnalysisVisitor::visitEVarCast(EVarCast *e_var_cast)
{
    /* Code For EVarCast Goes Here */

    visitIdent(e_var_cast->ident_);
    e_var_cast->expr_->accept(this);
}

void SemAnalysisVisitor::visitEVStdCast(EVStdCast *ev_std_cast)
{
    /* Code For EVStdCast Goes Here */

    ev_std_cast->stdtype_->accept(this);
    ev_std_cast->expr_->accept(this);
}

void SemAnalysisVisitor::visitEArrCast(EArrCast *e_arr_cast)
{
    /* Code For EArrCast Goes Here */

    visitIdent(e_arr_cast->ident_);
    e_arr_cast->expr_->accept(this);
}

void SemAnalysisVisitor::visitEAStdCast(EAStdCast *ea_std_cast)
{
    /* Code For EAStdCast Goes Here */

    ea_std_cast->stdtype_->accept(this);
    ea_std_cast->expr_->accept(this);
}

void SemAnalysisVisitor::visitEMul(EMul *e_mul)
{
    /* Code For EMul Goes Here */

    e_mul->expr_1->accept(this);
    e_mul->mulop_->accept(this);
    e_mul->expr_2->accept(this);
}

void SemAnalysisVisitor::visitEAdd(EAdd *e_add)
{
    /* Code For EAdd Goes Here */

    e_add->expr_1->accept(this);
    e_add->addop_->accept(this);
    e_add->expr_2->accept(this);
}

void SemAnalysisVisitor::visitERel(ERel *e_rel)
{
    /* Code For ERel Goes Here */

    e_rel->expr_1->accept(this);
    e_rel->relop_->accept(this);
    e_rel->expr_2->accept(this);
}

void SemAnalysisVisitor::visitEAnd(EAnd *e_and)
{
    /* Code For EAnd Goes Here */

    e_and->expr_1->accept(this);
    e_and->expr_2->accept(this);
}

void SemAnalysisVisitor::visitEOr(EOr *e_or)
{
    /* Code For EOr Goes Here */

    e_or->expr_1->accept(this);
    e_or->expr_2->accept(this);
}

void SemAnalysisVisitor::visitPlus(Plus *plus)
{
    /* Code For Plus Goes Here */
}

void SemAnalysisVisitor::visitMinus(Minus *minus)
{
    /* Code For Minus Goes Here */
}

void SemAnalysisVisitor::visitTimes(Times *times)
{
    /* Code For Times Goes Here */
}

void SemAnalysisVisitor::visitDiv(Div *div)
{
    /* Code For Div Goes Here */
}

void SemAnalysisVisitor::visitMod(Mod *mod)
{
    /* Code For Mod Goes Here */
}

void SemAnalysisVisitor::visitLTH(LTH *lth)
{
    /* Code For LTH Goes Here */
}

void SemAnalysisVisitor::visitLE(LE *le)
{
    /* Code For LE Goes Here */
}

void SemAnalysisVisitor::visitGTH(GTH *gth)
{
    /* Code For GTH Goes Here */
}

void SemAnalysisVisitor::visitGE(GE *ge)
{
    /* Code For GE Goes Here */
}

void SemAnalysisVisitor::visitEQU(EQU *equ)
{
    /* Code For EQU Goes Here */
}

void SemAnalysisVisitor::visitNE(NE *ne)
{
    /* Code For NE Goes Here */
}

void SemAnalysisVisitor::visitListClsFld(ListClsFld *list_cls_fld)
{
    for (ListClsFld::iterator i = list_cls_fld->begin(); i != list_cls_fld->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void SemAnalysisVisitor::visitListTopDef(ListTopDef *list_top_def)
{
    for (ListTopDef::iterator i = list_top_def->begin(); i != list_top_def->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void SemAnalysisVisitor::visitListIdent(ListIdent *list_ident)
{
    for (ListIdent::iterator i = list_ident->begin(); i != list_ident->end(); ++i)
    {
        visitIdent(*i);
    }
}

void SemAnalysisVisitor::visitListArg(ListArg *list_arg)
{
    for (ListArg::iterator i = list_arg->begin(); i != list_arg->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void SemAnalysisVisitor::visitListStmt(ListStmt *list_stmt)
{
    for (ListStmt::iterator i = list_stmt->begin(); i != list_stmt->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void SemAnalysisVisitor::visitListItem(ListItem *list_item)
{
    for (ListItem::iterator i = list_item->begin(); i != list_item->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void SemAnalysisVisitor::visitListType(ListType *list_type)
{
    for (ListType::iterator i = list_type->begin(); i != list_type->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void SemAnalysisVisitor::visitListExpr(ListExpr *list_expr)
{
    for (ListExpr::iterator i = list_expr->begin(); i != list_expr->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void SemAnalysisVisitor::visitInteger(Integer x)
{
    /* Code for Integer Goes Here */
}

void SemAnalysisVisitor::visitChar(Char x)
{
    /* Code for Char Goes Here */
}

void SemAnalysisVisitor::visitDouble(Double x)
{
    /* Code for Double Goes Here */
}

void SemAnalysisVisitor::visitString(String x)
{
    /* Code for String Goes Here */
}

void SemAnalysisVisitor::visitIdent(Ident x)
{
    /* Code for Ident Goes Here */
}
