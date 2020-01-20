#include "ClassesVisitor.h"
#include "GlobalSymbols.h"
#include "CompilerOutput.h"
#include "ControlFlow.h"



void ClassesVisitor::visitProgram(Program *t)
{
    t->accept(this);
}

void ClassesVisitor::visitProg(Prog *prog)
{
    prog->listtopdef_->accept(this);
}

void ClassesVisitor::visitClsDef(ClsDef *cls_def)
{
    if (!GlobalSymbols::getInstance().isClassInitialized(cls_def->ident_))
    {
        fprintf(stderr, "%s:\n", cls_def->ident_.c_str());
        ControlFlow::getInstance().newClass(cls_def->ident_);

        cls_def->listclsfld_->accept(this);

        GlobalSymbols::getInstance().setClassInitialized(cls_def->ident_);
    }
}

void ClassesVisitor::visitInhClsDef(InhClsDef *inh_cls_def)
{
    if (!GlobalSymbols::getInstance().isClassInitialized(inh_cls_def->ident_1) &&
         GlobalSymbols::getInstance().isClassInitialized(inh_cls_def->ident_2))
    {
        fprintf(stderr, "%s:\n", inh_cls_def->ident_1.c_str());
        ControlFlow::getInstance().newClass(inh_cls_def->ident_1);

        GlobalSymbols::getInstance().appendSymbolsFromInheritedClass(
            inh_cls_def->ident_1, inh_cls_def->ident_2);
        inh_cls_def->listclsfld_->accept(this);

        GlobalSymbols::getInstance().setClassInitialized(inh_cls_def->ident_1);
    }
}

void ClassesVisitor::visitVarDef(VarDef *var_def)
{
    if (!GlobalSymbols::getInstance().checkType(var_def->type_->get()))
    {
        CompilerOutput::getInstance().error(var_def->type_->line_number_,
            var_def->type_->get() + " is not a valid type name!");
        return;
    }

    if (var_def->type_->get().substr(0, 4) == "void")
    {
        CompilerOutput::getInstance().error(var_def->type_->line_number_,
            "Cannot declare variable with void type!");
        return;
    }

    auto class_name = ControlFlow::getInstance().getCurrentClassName();

    for (const auto &ident : *(var_def->listident_))
    {
        if (!GlobalSymbols::getInstance().appendClassVars(class_name, ident, var_def->type_->get()))
        {
            std::string error = "Identifier " + ident + " was already declared in this scope!";
            CompilerOutput::getInstance().error(var_def->line_number_, error);
        }
    }
}

void ClassesVisitor::visitMetDef(MetDef *met_def)
{
    auto class_name = ControlFlow::getInstance().getCurrentClassName();

    visitIdent(met_def->ident_);

    met_def->listarg_->insert(met_def->listarg_->begin(), new Ar(new VarType(class_name), "self"));

    if (!GlobalSymbols::getInstance().appendClassMethod(class_name, met_def->ident_, met_def->type_, met_def->listarg_))
    {
        std::string error = "Identifier " + met_def->ident_ + " was already declared in this scope!";
        CompilerOutput::getInstance().error(met_def->line_number_, error);
        return;
    }

    if (!GlobalSymbols::getInstance().appendFunc(class_name + "." + met_def->ident_,
                                                 met_def->type_, met_def->listarg_))
    {
        std::string error = "Identifier " + met_def->ident_ + " was already declared in this scope!";
        CompilerOutput::getInstance().error(met_def->line_number_, error);
        return;
    }

    met_def->listarg_->accept(this);

    met_def->block_->accept(this);
}

void ClassesVisitor::visitAr(Ar *ar)
{
    GlobalSymbols::getInstance().appendClassMethodLocal(ar->ident_);
}

void ClassesVisitor::visitFnDef(FnDef *fn_def)
{
}

void ClassesVisitor::visitBlk(Blk *blk)
{
    blk->liststmt_->accept(this);
}

void ClassesVisitor::visitEmpty(Empty *empty)
{
}

void ClassesVisitor::visitBStmt(BStmt *b_stmt)
{
    b_stmt->block_->accept(this);
}

void ClassesVisitor::visitDecl(Decl *decl)
{
    decl->type_->accept(this);
    decl->listitem_->accept(this);
}

void ClassesVisitor::visitAss(Ass *ass)
{
    ass->expr_1 = replaceIfUnknown(ass->expr_1);
    ass->expr_2 = replaceIfUnknown(ass->expr_2);

    ass->expr_1->accept(this);
    ass->expr_2->accept(this);
}

void ClassesVisitor::visitIncr(Incr *incr)
{
    incr->expr_ = replaceIfUnknown(incr->expr_);

    incr->expr_->accept(this);
}

void ClassesVisitor::visitDecr(Decr *decr)
{
    decr->expr_ = replaceIfUnknown(decr->expr_);

    decr->expr_->accept(this);
}

void ClassesVisitor::visitRet(Ret *ret)
{
    ret->expr_ = replaceIfUnknown(ret->expr_);

    ret->expr_->accept(this);
}

void ClassesVisitor::visitVRet(VRet *v_ret)
{
}

void ClassesVisitor::visitCond(Cond *cond)
{
    cond->expr_ = replaceIfUnknown(cond->expr_);

    cond->expr_->accept(this);
    cond->stmt_->accept(this);
}

void ClassesVisitor::visitCondElse(CondElse *cond_else)
{
    cond_else->expr_ =replaceIfUnknown(cond_else->expr_);

    cond_else->expr_->accept(this);
    cond_else->stmt_1->accept(this);
    cond_else->stmt_2->accept(this);
}

void ClassesVisitor::visitWhile(While *while_)
{
    while_->expr_ = replaceIfUnknown(while_->expr_);

    while_->expr_->accept(this);
    while_->stmt_->accept(this);
}

void ClassesVisitor::visitFor(For *for_)
{
    for_->type_->accept(this);
    visitIdent(for_->ident_);
    GlobalSymbols::getInstance().appendClassMethodLocal(for_->ident_);

    for_->expr_ = replaceIfUnknown(for_->expr_);

    for_->expr_->accept(this);
    for_->stmt_->accept(this);
}

void ClassesVisitor::visitSExp(SExp *s_exp)
{
    s_exp->expr_ = replaceIfUnknown(s_exp->expr_);
    s_exp->expr_->accept(this);
}

void ClassesVisitor::visitNoInit(NoInit *no_init)
{
    GlobalSymbols::getInstance().appendClassMethodLocal(no_init->ident_);
}

void ClassesVisitor::visitInit(Init *init)
{
    init->expr_ = replaceIfUnknown(init->expr_);
    init->expr_->accept(this);
    GlobalSymbols::getInstance().appendClassMethodLocal(init->ident_);
}

void ClassesVisitor::visitInt(Int *int_)
{
}

void ClassesVisitor::visitStr(Str *str)
{
}

void ClassesVisitor::visitBool(Bool *bool_)
{
}

void ClassesVisitor::visitVoid(Void *void_)
{
}

void ClassesVisitor::visitStVarType(StVarType *st_var_type)
{
    st_var_type->stdtype_->accept(this);
}

void ClassesVisitor::visitStArrType(StArrType *st_arr_type)
{
    st_arr_type->stdtype_->accept(this);
}

void ClassesVisitor::visitVarType(VarType *var_type)
{
    visitIdent(var_type->ident_);
}

void ClassesVisitor::visitArrType(ArrType *arr_type)
{
    visitIdent(arr_type->ident_);
}

void ClassesVisitor::visitFun(Fun *fun)
{
    fun->type_->accept(this);
    fun->listtype_->accept(this);
}

void ClassesVisitor::visitEVar(EVar *e_var)
{
}

void ClassesVisitor::visitEClsVar(EClsVar *e_cls_var)
{
    e_cls_var->expr_ = replaceIfUnknown(e_cls_var->expr_);

    e_cls_var->expr_->accept(this);
}

void ClassesVisitor::visitEArrVar(EArrVar *e_arr_var)
{
    e_arr_var->expr_1 = replaceIfUnknown(e_arr_var->expr_1);
    e_arr_var->expr_2 = replaceIfUnknown(e_arr_var->expr_2);

    e_arr_var->expr_1->accept(this);
    e_arr_var->expr_2->accept(this);
}

void ClassesVisitor::visitELitInt(ELitInt *e_lit_int)
{
}

void ClassesVisitor::visitEString(EString *e_string)
{
}

void ClassesVisitor::visitELitTrue(ELitTrue *e_lit_true)
{
}

void ClassesVisitor::visitELitFalse(ELitFalse *e_lit_false)
{
}

void ClassesVisitor::visitELitNull(ELitNull *e_lit_null)
{
}

void ClassesVisitor::visitEApp(EApp *e_app)
{
    visitIdent(e_app->ident_);
    e_app->listexpr_->accept(this);
}

void ClassesVisitor::visitEClsApp(EClsApp *e_cls_app)
{
    e_cls_app->expr_ = replaceIfUnknown(e_cls_app->expr_);
    e_cls_app->listexpr_->accept(this);
}

void ClassesVisitor::visitENeg(ENeg *e_neg)
{
    e_neg->expr_ = replaceIfUnknown(e_neg->expr_);
    e_neg->expr_->accept(this);
}

void ClassesVisitor::visitENot(ENot *e_not)
{
    e_not->expr_ = replaceIfUnknown(e_not->expr_);
    e_not->expr_->accept(this);
}

void ClassesVisitor::visitEVarNew(EVarNew *e_var_new)
{
}

void ClassesVisitor::visitEVStdNew(EVStdNew *ev_std_new)
{
}

void ClassesVisitor::visitEArrNew(EArrNew *e_arr_new)
{
    e_arr_new->expr_ = replaceIfUnknown(e_arr_new->expr_);

    e_arr_new->expr_->accept(this);
}

void ClassesVisitor::visitEAStdNew(EAStdNew *ea_std_new)
{
    ea_std_new->expr_ = replaceIfUnknown(ea_std_new->expr_);

    ea_std_new->stdtype_->accept(this);
    ea_std_new->expr_->accept(this);
}

void ClassesVisitor::visitEVarCast(EVarCast *e_var_cast)
{
    e_var_cast->expr_ = replaceIfUnknown(e_var_cast->expr_);

    e_var_cast->expr_->accept(this);
}

void ClassesVisitor::visitEVStdCast(EVStdCast *ev_std_cast)
{
}

void ClassesVisitor::visitEArrCast(EArrCast *e_arr_cast)
{
}

void ClassesVisitor::visitEAStdCast(EAStdCast *ea_std_cast)
{
}

void ClassesVisitor::visitEMul(EMul *e_mul)
{
    e_mul->expr_1 = replaceIfUnknown(e_mul->expr_1);
    e_mul->expr_2 = replaceIfUnknown(e_mul->expr_2);

    e_mul->expr_1->accept(this);
    e_mul->mulop_->accept(this);
    e_mul->expr_2->accept(this);
}

void ClassesVisitor::visitEAdd(EAdd *e_add)
{
    e_add->expr_1 = replaceIfUnknown(e_add->expr_1);
    e_add->expr_2 = replaceIfUnknown(e_add->expr_2);

    e_add->expr_1->accept(this);
    e_add->addop_->accept(this);
    e_add->expr_2->accept(this);
}

void ClassesVisitor::visitERel(ERel *e_rel)
{
    e_rel->expr_1 = replaceIfUnknown(e_rel->expr_1);
    e_rel->expr_2 = replaceIfUnknown(e_rel->expr_2);

    e_rel->expr_1->accept(this);
    e_rel->relop_->accept(this);
    e_rel->expr_2->accept(this);
}

void ClassesVisitor::visitEAnd(EAnd *e_and)
{
    e_and->expr_1 = replaceIfUnknown(e_and->expr_1);
    e_and->expr_2 = replaceIfUnknown(e_and->expr_2);

    e_and->expr_1->accept(this);
    e_and->expr_2->accept(this);
}

void ClassesVisitor::visitEOr(EOr *e_or)
{
    e_or->expr_1 = replaceIfUnknown(e_or->expr_1);
    e_or->expr_2 = replaceIfUnknown(e_or->expr_2);

    e_or->expr_1->accept(this);
    e_or->expr_2->accept(this);
}

void ClassesVisitor::visitPlus(Plus *plus)
{
}

void ClassesVisitor::visitMinus(Minus *minus)
{
}

void ClassesVisitor::visitTimes(Times *times)
{
}

void ClassesVisitor::visitDiv(Div *div)
{
}

void ClassesVisitor::visitMod(Mod *mod)
{
}

void ClassesVisitor::visitLTH(LTH *lth)
{
}

void ClassesVisitor::visitLE(LE *le)
{
}

void ClassesVisitor::visitGTH(GTH *gth)
{
}

void ClassesVisitor::visitGE(GE *ge)
{
}

void ClassesVisitor::visitEQU(EQU *equ)
{
}

void ClassesVisitor::visitNE(NE *ne)
{
}

void ClassesVisitor::visitListIdent(ListIdent *list_ident)
{
    for (ListIdent::iterator i = list_ident->begin(); i != list_ident->end(); ++i)
    {
        visitIdent(*i);
    }
}

void ClassesVisitor::visitListStmt(ListStmt *list_stmt)
{
    for (ListStmt::iterator i = list_stmt->begin(); i != list_stmt->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void ClassesVisitor::visitListItem(ListItem *list_item)
{
    for (ListItem::iterator i = list_item->begin(); i != list_item->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void ClassesVisitor::visitListType(ListType *list_type)
{
    for (ListType::iterator i = list_type->begin(); i != list_type->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void ClassesVisitor::visitListExpr(ListExpr *list_expr)
{
    for (ListExpr::iterator i = list_expr->begin(); i != list_expr->end(); ++i)
    {
        *i = replaceIfUnknown(*i);
        (*i)->accept(this);
    }
}

void ClassesVisitor::visitListClsFld(ListClsFld *list_cls_fld)
{
    for (ListClsFld::iterator i = list_cls_fld->begin(); i != list_cls_fld->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void ClassesVisitor::visitListTopDef(ListTopDef *list_top_def)
{
    // TODO - make it faster
    for (auto &i : *list_top_def)
    {
        for (auto &j : *list_top_def)
            j->accept(this);
    }
}

void ClassesVisitor::visitListArg(ListArg *list_arg)
{
    for (ListArg::iterator i = list_arg->begin(); i != list_arg->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void ClassesVisitor::visitInteger(Integer x)
{
}

void ClassesVisitor::visitChar(Char x)
{
}

void ClassesVisitor::visitDouble(Double x)
{
}

void ClassesVisitor::visitString(String x)
{
}

void ClassesVisitor::visitIdent(Ident x)
{
}

Expr* ClassesVisitor::replaceIfUnknown(Expr *expr) {
    auto expr_1_var = dynamic_cast<EVar *>(expr);
    auto expr_1_app = dynamic_cast<EApp *>(expr);

    Expr* new_expr = expr;
    if (expr_1_var != nullptr && !GlobalSymbols::getInstance().methodLocalExists(expr_1_var->ident_))
    {
        auto ident = expr_1_var->ident_;
        fprintf(stderr, "Replaced: %s\n", ident.c_str());

        new_expr = new EClsVar(new EVar("self"), ident);
        return new_expr;
    }

    if (expr_1_app != nullptr)
    {
        try
        {
            GlobalSymbols::getInstance().getFunctionType(expr_1_app->ident_);
        }
        catch (const std::invalid_argument &e)
        {
            auto ident = expr_1_app->ident_;
            auto args = expr_1_app->listexpr_;
            fprintf(stderr, "Function Replaced: %s\n", ident.c_str());

            new_expr = new EClsApp(new EVar("self"), ident, args);
            return new_expr;
        }
    }

    return new_expr;
}
