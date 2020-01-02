#include "CodeGenVisitor.h"
#include "GlobalSymbols.h"
#include "CompilerOutput.h"


void CodeGenVisitor::visitProgram(Program *t)
{
    t->accept(this);
}

void CodeGenVisitor::visitTopDef(TopDef *t) {}   //abstract class
void CodeGenVisitor::visitClsFld(ClsFld *t) {}   //abstract class
void CodeGenVisitor::visitArg(Arg *t) {}         //abstract class
void CodeGenVisitor::visitBlock(Block *t) {}     //abstract class
void CodeGenVisitor::visitStmt(Stmt *t) {}       //abstract class
void CodeGenVisitor::visitItem(Item *t) {}       //abstract class
void CodeGenVisitor::visitStdType(StdType *t) {} //abstract class
void CodeGenVisitor::visitType(Type *t) {}       //abstract class
void CodeGenVisitor::visitExpr(Expr *t) {}       //abstract class
void CodeGenVisitor::visitAddOp(AddOp *t) {}     //abstract class
void CodeGenVisitor::visitMulOp(MulOp *t) {}     //abstract class
void CodeGenVisitor::visitRelOp(RelOp *t) {}     //abstract class

void CodeGenVisitor::visitProg(Prog *prog)
{
    prog->listtopdef_->accept(this);
}

void CodeGenVisitor::visitFnDef(FnDef *fn_def)
{
    CompilerOutput::getInstance().printOutput(fn_def->ident_ + ":\n"
                                              "  pushl %ebp\n"
                                              "  movl %esp, %ebp\n");

    fn_def->type_->accept(this);
    visitIdent(fn_def->ident_);
    fn_def->listarg_->accept(this);
    fn_def->block_->accept(this);
}

void CodeGenVisitor::visitClsDef(ClsDef *cls_def)
{
    /* Code For ClsDef Goes Here */

    //visitIdent(cls_def->ident_);
    //cls_def->listclsfld_->accept(this);
}

void CodeGenVisitor::visitInhClsDef(InhClsDef *inh_cls_def)
{
    /* Code For InhClsDef Goes Here */

    //visitIdent(inh_cls_def->ident_1);
    //visitIdent(inh_cls_def->ident_2);
    //inh_cls_def->listclsfld_->accept(this);
}

void CodeGenVisitor::visitVarDef(VarDef *var_def)
{
    /* Code For VarDef Goes Here */

    //var_def->type_->accept(this);
    //var_def->listident_->accept(this);
}

void CodeGenVisitor::visitMetDef(MetDef *met_def)
{
    /* Code For MetDef Goes Here */

    //met_def->type_->accept(this);
    //visitIdent(met_def->ident_);
    //met_def->listarg_->accept(this);
    //met_def->block_->accept(this);
}

void CodeGenVisitor::visitAr(Ar *ar)
{
    ar->type_->accept(this);
    visitIdent(ar->ident_);
}

void CodeGenVisitor::visitBlk(Blk *blk)
{
    blk->liststmt_->accept(this);
}

void CodeGenVisitor::visitEmpty(Empty *empty)
{
}

void CodeGenVisitor::visitBStmt(BStmt *b_stmt)
{
    b_stmt->block_->accept(this);
}

void CodeGenVisitor::visitDecl(Decl *decl)
{
    decl->type_->accept(this);
    decl->listitem_->accept(this);
}

void CodeGenVisitor::visitAss(Ass *ass)
{
    ass->expr_1->accept(this);
    ass->expr_2->accept(this);
}

void CodeGenVisitor::visitIncr(Incr *incr)
{
    incr->expr_->accept(this);
}

void CodeGenVisitor::visitDecr(Decr *decr)
{
    decr->expr_->accept(this);
}

void CodeGenVisitor::visitRet(Ret *ret)
{
    ret->expr_->accept(this);

    // TODO - JUST FOR NOW
    CompilerOutput::getInstance().printOutput("  pushl $2\n");

    CompilerOutput::getInstance().printOutput("  popl %eax\n");
    CompilerOutput::getInstance().printOutput("  movl %ebp, %esp\n"
                                              "  popl %ebp\n"
                                              "  ret\n\n");
}

void CodeGenVisitor::visitVRet(VRet *v_ret)
{
    CompilerOutput::getInstance().printOutput("  movl %ebp, %esp\n"
                                              "  popl %ebp\n"
                                              "  ret\n\n");
}

void CodeGenVisitor::visitCond(Cond *cond)
{
    cond->expr_->accept(this);

    if (!cond->expr_->is_always_false_ && !cond->expr_->is_always_true_)
    {
        cond->stmt_->accept(this);
    }
    else if (cond->expr_->is_always_true_)
    {
        cond->stmt_->accept(this);
    }
}

void CodeGenVisitor::visitCondElse(CondElse *cond_else)
{
    cond_else->expr_->accept(this);

    if (!cond_else->expr_->is_always_false_ && !cond_else->expr_->is_always_true_)
    {
        cond_else->stmt_1->accept(this);
        cond_else->stmt_2->accept(this);
    }
    else if (cond_else->expr_->is_always_true_)
    {
        cond_else->stmt_1->accept(this);
    }
    else if (cond_else->expr_->is_always_false_)
    {
        cond_else->stmt_2->accept(this);
    }
}

void CodeGenVisitor::visitWhile(While *while_)
{
    while_->expr_->accept(this);

    // infinite loop
    if (while_->expr_->is_always_true_)
    {
    }

    while_->stmt_->accept(this);
}

void CodeGenVisitor::visitFor(For *for_)
{
    for_->type_->accept(this);
    visitIdent(for_->ident_);

    for_->expr_->accept(this);

    for_->stmt_->accept(this);
}

void CodeGenVisitor::visitSExp(SExp *s_exp)
{
    s_exp->expr_->accept(this);
}

void CodeGenVisitor::visitNoInit(NoInit *no_init)
{
}

void CodeGenVisitor::visitInit(Init *init)
{
    init->expr_->accept(this);
}

void CodeGenVisitor::visitInt(Int *int_)
{
}

void CodeGenVisitor::visitStr(Str *str)
{
}

void CodeGenVisitor::visitBool(Bool *bool_)
{
}

void CodeGenVisitor::visitVoid(Void *void_)
{
}

void CodeGenVisitor::visitStVarType(StVarType *st_var_type)
{
    st_var_type->stdtype_->accept(this);
}

void CodeGenVisitor::visitStArrType(StArrType *st_arr_type)
{
    st_arr_type->stdtype_->accept(this);
}

void CodeGenVisitor::visitVarType(VarType *var_type)
{
    visitIdent(var_type->ident_);
}

void CodeGenVisitor::visitArrType(ArrType *arr_type)
{
    visitIdent(arr_type->ident_);
}

void CodeGenVisitor::visitFun(Fun *fun)
{
    fun->type_->accept(this);
    fun->listtype_->accept(this);
}

void CodeGenVisitor::visitEVar(EVar *e_var)
{
    visitIdent(e_var->ident_);
}

void CodeGenVisitor::visitEClsVar(EClsVar *e_cls_var)
{
    /* Code For EClsVar Goes Here */

    //e_cls_var->expr_->accept(this);
    //visitIdent(e_cls_var->ident_);
}

void CodeGenVisitor::visitEArrVar(EArrVar *e_arr_var)
{
    e_arr_var->expr_1->accept(this);
    e_arr_var->expr_2->accept(this);
}

void CodeGenVisitor::visitELitInt(ELitInt *e_lit_int)
{
    visitInteger(e_lit_int->integer_);
}

void CodeGenVisitor::visitEString(EString *e_string)
{
    visitString(e_string->string_);
}

void CodeGenVisitor::visitELitTrue(ELitTrue *e_lit_true)
{
}

void CodeGenVisitor::visitELitFalse(ELitFalse *e_lit_false)
{
}

void CodeGenVisitor::visitELitNull(ELitNull *e_lit_null)
{
}

void CodeGenVisitor::visitEApp(EApp *e_app)
{
    visitIdent(e_app->ident_);
    e_app->listexpr_->accept(this);
}

void CodeGenVisitor::visitEClsApp(EClsApp *e_cls_app)
{
    /* Code For EClsApp Goes Here */

    //e_cls_app->expr_->accept(this);
    //visitIdent(e_cls_app->ident_);
    //e_cls_app->listexpr_->accept(this);
}

void CodeGenVisitor::visitENeg(ENeg *e_neg)
{
    e_neg->expr_->accept(this);
}

void CodeGenVisitor::visitENot(ENot *e_not)
{
    e_not->expr_->accept(this);
}

void CodeGenVisitor::visitEVarNew(EVarNew *e_var_new)
{
    /* Code For EVarNew Goes Here */

    //visitIdent(e_var_new->ident_);
}

void CodeGenVisitor::visitEVStdNew(EVStdNew *ev_std_new)
{
    ev_std_new->stdtype_->accept(this);
}

void CodeGenVisitor::visitEArrNew(EArrNew *e_arr_new)
{

    //visitIdent(e_arr_new->ident_);
    //e_arr_new->expr_->accept(this);
}

void CodeGenVisitor::visitEAStdNew(EAStdNew *ea_std_new)
{
    ea_std_new->stdtype_->accept(this);
    ea_std_new->expr_->accept(this);
}

void CodeGenVisitor::visitEVarCast(EVarCast *e_var_cast)
{
    /* Code For EVarCast Goes Here */

    //visitIdent(e_var_cast->ident_);
    //e_var_cast->expr_->accept(this);
}

void CodeGenVisitor::visitEVStdCast(EVStdCast *ev_std_cast)
{
    /* Code For EVStdCast Goes Here */

    //ev_std_cast->stdtype_->accept(this);
    //ev_std_cast->expr_->accept(this);
}

void CodeGenVisitor::visitEArrCast(EArrCast *e_arr_cast)
{
    /* Code For EArrCast Goes Here */

    //visitIdent(e_arr_cast->ident_);
   // e_arr_cast->expr_->accept(this);
}

void CodeGenVisitor::visitEAStdCast(EAStdCast *ea_std_cast)
{
    /* Code For EAStdCast Goes Here */

    //ea_std_cast->stdtype_->accept(this);
    //ea_std_cast->expr_->accept(this);
}

void CodeGenVisitor::visitEMul(EMul *e_mul)
{
    e_mul->expr_1->accept(this);
    e_mul->mulop_->accept(this);
    e_mul->expr_2->accept(this);

    auto is_mul = dynamic_cast<Times*>(e_mul->mulop_);
    auto is_div = dynamic_cast<Div*>(e_mul->mulop_);
    auto is_mod = dynamic_cast<Mod*>(e_mul->mulop_);
}

void CodeGenVisitor::visitEAdd(EAdd *e_add)
{
    e_add->expr_1->accept(this);
    e_add->addop_->accept(this);
    e_add->expr_2->accept(this);

    auto is_plus = dynamic_cast<Plus*>(e_add->addop_);

    if (e_add->expr_1->type_ == "string" &&
        e_add->expr_2->type_ == "string" &&
        is_plus != nullptr)
    {
    }
    else if (e_add->expr_1->type_ == "int" &&
             e_add->expr_2->type_ == "int")
    {
    }
}

void CodeGenVisitor::visitERel(ERel *e_rel)
{
    e_rel->expr_1->accept(this);
    e_rel->relop_->accept(this);
    e_rel->expr_2->accept(this);

    auto is_eq = dynamic_cast<EQU*>(e_rel->relop_);
    auto is_neq = dynamic_cast<NE*>(e_rel->relop_);
    auto is_lt = dynamic_cast<LTH*>(e_rel->relop_);
    auto is_le = dynamic_cast<LE*>(e_rel->relop_);
    auto is_gt = dynamic_cast<GTH*>(e_rel->relop_);
    auto is_ge = dynamic_cast<GE*>(e_rel->relop_);
}

void CodeGenVisitor::visitEAnd(EAnd *e_and)
{
    e_and->expr_1->accept(this);
    e_and->expr_2->accept(this);
}

void CodeGenVisitor::visitEOr(EOr *e_or)
{
    e_or->expr_1->accept(this);
    e_or->expr_2->accept(this);
}

void CodeGenVisitor::visitPlus(Plus *plus)
{
}

void CodeGenVisitor::visitMinus(Minus *minus)
{
}

void CodeGenVisitor::visitTimes(Times *times)
{
}

void CodeGenVisitor::visitDiv(Div *div)
{
}

void CodeGenVisitor::visitMod(Mod *mod)
{
}

void CodeGenVisitor::visitLTH(LTH *lth)
{
}

void CodeGenVisitor::visitLE(LE *le)
{
}

void CodeGenVisitor::visitGTH(GTH *gth)
{
}

void CodeGenVisitor::visitGE(GE *ge)
{
}

void CodeGenVisitor::visitEQU(EQU *equ)
{
}

void CodeGenVisitor::visitNE(NE *ne)
{
}

void CodeGenVisitor::visitListClsFld(ListClsFld *list_cls_fld)
{
    for (ListClsFld::iterator i = list_cls_fld->begin(); i != list_cls_fld->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void CodeGenVisitor::visitListTopDef(ListTopDef *list_top_def)
{
    for (ListTopDef::iterator i = list_top_def->begin(); i != list_top_def->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void CodeGenVisitor::visitListIdent(ListIdent *list_ident)
{
    for (ListIdent::iterator i = list_ident->begin(); i != list_ident->end(); ++i)
    {
        visitIdent(*i);
    }
}

void CodeGenVisitor::visitListArg(ListArg *list_arg)
{
    for (ListArg::iterator i = list_arg->begin(); i != list_arg->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void CodeGenVisitor::visitListStmt(ListStmt *list_stmt)
{
    for (ListStmt::iterator i = list_stmt->begin(); i != list_stmt->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void CodeGenVisitor::visitListItem(ListItem *list_item)
{
    for (ListItem::iterator i = list_item->begin(); i != list_item->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void CodeGenVisitor::visitListType(ListType *list_type)
{
    for (ListType::iterator i = list_type->begin(); i != list_type->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void CodeGenVisitor::visitListExpr(ListExpr *list_expr)
{
    for (ListExpr::iterator i = list_expr->begin(); i != list_expr->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void CodeGenVisitor::visitInteger(Integer x)
{
}

void CodeGenVisitor::visitChar(Char x)
{
}

void CodeGenVisitor::visitDouble(Double x)
{
}

void CodeGenVisitor::visitString(String x)
{
}

void CodeGenVisitor::visitIdent(Ident x)
{
}
