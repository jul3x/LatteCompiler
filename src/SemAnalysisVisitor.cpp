#include "SemAnalysisVisitor.h"
#include "LocalSymbols.h"
#include "GlobalSymbols.h"
#include "ControlFlow.h"


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
    LocalSymbols::getInstance().enterBlock();

    ControlFlow::getInstance().newFunction();

    fn_def->type_->accept(this);
    visitIdent(fn_def->ident_);
    fn_def->listarg_->accept(this);
    fn_def->block_->accept(this);

    LocalSymbols::getInstance().exitBlock();
}

void SemAnalysisVisitor::visitClsDef(ClsDef *cls_def)
{
    /* Code For ClsDef Goes Here */

    //visitIdent(cls_def->ident_);
    //cls_def->listclsfld_->accept(this);
}

void SemAnalysisVisitor::visitInhClsDef(InhClsDef *inh_cls_def)
{
    /* Code For InhClsDef Goes Here */

    //visitIdent(inh_cls_def->ident_1);
    //visitIdent(inh_cls_def->ident_2);
    //inh_cls_def->listclsfld_->accept(this);
}

void SemAnalysisVisitor::visitVarDef(VarDef *var_def)
{
    /* Code For VarDef Goes Here */

    //var_def->type_->accept(this);
    //var_def->listident_->accept(this);
}

void SemAnalysisVisitor::visitMetDef(MetDef *met_def)
{
    /* Code For MetDef Goes Here */

    //met_def->type_->accept(this);
    //visitIdent(met_def->ident_);
    //met_def->listarg_->accept(this);
    //met_def->block_->accept(this);
}

void SemAnalysisVisitor::visitAr(Ar *ar)
{
    /* Code For Ar Goes Here */

    ar->type_->accept(this);
    visitIdent(ar->ident_);

    if (ar->type_->get().substr(0, 4) == "void")
    {
        std::string error = "Cannot declare variable with void type!\n";
        throw std::invalid_argument(error.c_str());
    }

    LocalSymbols::getInstance().append(ar->ident_, ar->type_->get());
}

void SemAnalysisVisitor::visitBlk(Blk *blk)
{
    /* Code For Blk Goes Here */
    LocalSymbols::getInstance().enterBlock();
    blk->liststmt_->accept(this);
    LocalSymbols::getInstance().exitBlock();
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

    decl->listitem_->type_ = decl->type_->get();

    decl->listitem_->accept(this);
}

void SemAnalysisVisitor::visitAss(Ass *ass)
{
    /* Code For Ass Goes Here */
    // TODO - check if lvalue is assignable
    ass->expr_1->accept(this);
    ass->expr_2->accept(this);

    if (ass->expr_1->type_ != ass->expr_2->type_)
    {
        std::string error = "Lvalue of type: " + ass->expr_1->type_ +
            " does not match rvalue of type: " + ass->expr_2->type_ + "!\n";
        throw std::invalid_argument(error.c_str());
    }

    if (!ass->expr_1->is_lvalue_)
    {
        std::string error = "Assignment can be done only for appropriate lvalues!\n";
        throw std::invalid_argument(error.c_str());
    }
}

void SemAnalysisVisitor::visitIncr(Incr *incr)
{
    /* Code For Incr Goes Here */

    incr->expr_->accept(this);

    if (incr->expr_->type_ != "int")
    {
        std::string error = "Only int variables can be incremented!\n";
        throw std::invalid_argument(error.c_str());
    }

    if (!incr->expr_->is_lvalue_)
    {
        std::string error = "Incrementing can be done only for appropriate lvalues!\n";
        throw std::invalid_argument(error.c_str());
    }
}

void SemAnalysisVisitor::visitDecr(Decr *decr)
{
    /* Code For Decr Goes Here */

    decr->expr_->accept(this);

    if (decr->expr_->type_ != "int")
    {
        std::string error = "Only int variables can be decremented!\n";
        throw std::invalid_argument(error.c_str());
    }

    if (!decr->expr_->is_lvalue_)
    {
        std::string error = "Decrementing can be done only for appropriate lvalues!\n";
        throw std::invalid_argument(error.c_str());
    }
}

void SemAnalysisVisitor::visitRet(Ret *ret)
{
    /* Code For Ret Goes Here */
    // TODO Check if appropriate return type
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

    if (cond->expr_->type_ != "boolean")
    {
        std::string error = "Condition in if statement must be of boolean type!\n";
        throw std::invalid_argument(error.c_str());
    }

    auto parent = ControlFlow::getInstance().getCurrentBlock();

    ControlFlow::getInstance().addBlock();

    auto if_block = ControlFlow::getInstance().getCurrentBlock();

    ControlFlow::getInstance().addChild(parent, if_block);

    cond->stmt_->accept(this);

    auto parent_from_if = ControlFlow::getInstance().getCurrentBlock();

    ControlFlow::getInstance().addBlock();
    auto after_if = ControlFlow::getInstance().getCurrentBlock();

    ControlFlow::getInstance().addChild(parent, after_if);
    ControlFlow::getInstance().addChild(parent_from_if, after_if);

}

void SemAnalysisVisitor::visitCondElse(CondElse *cond_else)
{
    /* Code For CondElse Goes Here */

    cond_else->expr_->accept(this);

    if (cond_else->expr_->type_ != "boolean")
    {
        std::string error = "Condition in if statement must be of boolean type!\n";
        throw std::invalid_argument(error.c_str());
    }

    auto parent = ControlFlow::getInstance().getCurrentBlock();
    ControlFlow::getInstance().addBlock();

    auto if_block = ControlFlow::getInstance().getCurrentBlock();
    ControlFlow::getInstance().addChild(parent, if_block);

    cond_else->stmt_1->accept(this);

    auto parent_from_if = ControlFlow::getInstance().getCurrentBlock();

    ControlFlow::getInstance().addBlock();

    auto else_block = ControlFlow::getInstance().getCurrentBlock();
    ControlFlow::getInstance().addChild(parent, else_block);

    cond_else->stmt_2->accept(this);

    auto parent_from_else = ControlFlow::getInstance().getCurrentBlock();

    ControlFlow::getInstance().addBlock();

    auto after_if = ControlFlow::getInstance().getCurrentBlock();

    ControlFlow::getInstance().addChild(parent_from_if, after_if);
    ControlFlow::getInstance().addChild(parent_from_else, after_if);

}

void SemAnalysisVisitor::visitWhile(While *while_)
{
    /* Code For While Goes Here */

    // Lets treat while as normal statement without any jumps - for now it does not matter

    while_->expr_->accept(this);

    if (while_->expr_->type_ != "boolean")
    {
        std::string error = "Condition in while statement must be of boolean type!\n";
        throw std::invalid_argument(error.c_str());
    }

    while_->stmt_->accept(this);
}

void SemAnalysisVisitor::visitFor(For *for_)
{
    /* Code For For Goes Here */
    LocalSymbols::getInstance().enterBlock();

    for_->type_->accept(this);
    visitIdent(for_->ident_);

    if (for_->type_->get().substr(0, 4) == "void")
    {
        std::string error = "Cannot declare variable with void type!\n";
        throw std::invalid_argument(error.c_str());
    }

    LocalSymbols::getInstance().append(for_->ident_, for_->type_->get());

    for_->expr_->accept(this);

    if (for_->type_->get() + "[]" != for_->expr_->type_)
    {
        std::string error = "Type of iterator: " + for_->type_->get() +
            " of for loop does not match type of array: " + for_->expr_->type_ + "\n";
        throw std::invalid_argument(error.c_str());
    }

    for_->stmt_->accept(this);

    LocalSymbols::getInstance().exitBlock();
}

void SemAnalysisVisitor::visitSExp(SExp *s_exp)
{
    /* Code For SExp Goes Here */

    s_exp->expr_->accept(this);
}

void SemAnalysisVisitor::visitNoInit(NoInit *no_init)
{
    /* Code For NoInit Goes Here */
    if (no_init->type_.substr(0, 4) == "void")
    {
        std::string error = "Cannot declare variable with void type!\n";
        throw std::invalid_argument(error.c_str());
    }

    LocalSymbols::getInstance().append(no_init->ident_, no_init->type_);
}

void SemAnalysisVisitor::visitInit(Init *init)
{
    /* Code For Init Goes Here */
    init->expr_->accept(this);

    if (init->type_.substr(0, 4) == "void")
    {
        std::string error = "Cannot declare variable with void type!\n";
        throw std::invalid_argument(error.c_str());
    }

    if (init->expr_->type_ != init->type_)
    {
        std::string error = "Type of value: " + init->expr_->type_ +
            " does not match type: " + init->type_ +
            " of declared variable of name " + init->ident_ + "!\n";
        throw std::invalid_argument(error.c_str());
    }

    LocalSymbols::getInstance().append(init->ident_, init->type_);
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
    e_var->type_ = LocalSymbols::getInstance().getSymbolType(e_var->ident_);

    visitIdent(e_var->ident_);
    e_var->is_lvalue_ = true;
}

void SemAnalysisVisitor::visitEClsVar(EClsVar *e_cls_var)
{
    /* Code For EClsVar Goes Here */

    //e_cls_var->expr_->accept(this);
    //visitIdent(e_cls_var->ident_);
}

void SemAnalysisVisitor::visitEArrVar(EArrVar *e_arr_var)
{
    /* Code For EArrVar Goes Here */

    e_arr_var->expr_1->accept(this);
    e_arr_var->expr_2->accept(this);

    if (e_arr_var->expr_1->type_.substr(e_arr_var->expr_1->type_.length() - 2) != "[]")
    {
        std::string error = "[] operation can be performed only for array types!\n";
        throw std::invalid_argument(error.c_str());
    }

    if (!e_arr_var->expr_1->is_lvalue_)
    {
        std::string error = "[] operation can be performed only on lvalue array types!\n";
        throw std::invalid_argument(error.c_str());
    }

    if (e_arr_var->expr_2->type_ != "int")
    {
        std::string error = "[] operation can be performed only using int parameter!\n";
        throw std::invalid_argument(error.c_str());
    }

    e_arr_var->type_ = e_arr_var->expr_1->type_.substr(0, e_arr_var->expr_1->type_.length() - 2);
    e_arr_var->is_lvalue_ = true;
}

void SemAnalysisVisitor::visitELitInt(ELitInt *e_lit_int)
{
    /* Code For ELitInt Goes Here */

    visitInteger(e_lit_int->integer_);

    e_lit_int->type_ = "int";
    e_lit_int->is_lvalue_ = false;
}

void SemAnalysisVisitor::visitEString(EString *e_string)
{
    /* Code For EString Goes Here */

    visitString(e_string->string_);

    e_string->type_ = "string";
    e_string->is_lvalue_ = false;
}

void SemAnalysisVisitor::visitELitTrue(ELitTrue *e_lit_true)
{
    /* Code For ELitTrue Goes Here */
    e_lit_true->type_ = "boolean";
    e_lit_true->is_lvalue_ = false;
}

void SemAnalysisVisitor::visitELitFalse(ELitFalse *e_lit_false)
{
    /* Code For ELitFalse Goes Here */
    e_lit_false->type_ = "boolean";
    e_lit_false->is_lvalue_ = false;
}

void SemAnalysisVisitor::visitELitNull(ELitNull *e_lit_null)
{
    /* Code For ELitNull Goes Here */
    e_lit_null->type_ = "void";
    e_lit_null->is_lvalue_ = false;

}

void SemAnalysisVisitor::visitEApp(EApp *e_app)
{
    /* Code For EApp Goes Here */
    e_app->type_ = GlobalSymbols::getInstance().getFunctionType(e_app->ident_);

    visitIdent(e_app->ident_);
    e_app->listexpr_->accept(this);

    auto args = GlobalSymbols::getInstance().getFunctionArgs(e_app->ident_);

    if (e_app->listexpr_->size() != args->size())
    {
        std::string error = e_app->ident_ + " function requires " + std::to_string(args->size()) +
            " arguments, provided: " + std::to_string(e_app->listexpr_->size()) + "!\n";
        throw std::invalid_argument(error.c_str());
    }

    for (int i = 0; i < args->size(); ++ i)
    {
        if (e_app->listexpr_->at(i)->type_ != args->at(i)->getType())
        {
        std::string error = e_app->ident_ + " function's " + std::to_string(i + 1) + 
            " argument needs to be of type: " + args->at(i)->getType() +
            ", provided: " + e_app->listexpr_->at(i)->type_ + "!\n";
        throw std::invalid_argument(error.c_str());
        }
    }

    // TODO It depends on what function returns!
    e_app->is_lvalue_ = false;
}

void SemAnalysisVisitor::visitEClsApp(EClsApp *e_cls_app)
{
    /* Code For EClsApp Goes Here */

    //e_cls_app->expr_->accept(this);
    //visitIdent(e_cls_app->ident_);
    //e_cls_app->listexpr_->accept(this);
}

void SemAnalysisVisitor::visitENeg(ENeg *e_neg)
{
    /* Code For ENeg Goes Here */
    e_neg->expr_->accept(this);
    e_neg->type_ = "int";

    if (e_neg->expr_->type_ != "int")
    {
        std::string error = "Negation operation can be performed only using int parameter!\n";
        throw std::invalid_argument(error.c_str());
    }

    e_neg->is_lvalue_ = false;
}

void SemAnalysisVisitor::visitENot(ENot *e_not)
{
    /* Code For ENot Goes Here */
    e_not->expr_->accept(this);

    e_not->type_ = "boolean";

    if (e_not->expr_->type_ != "boolean")
    {
        std::string error = "Not operation can be performed only using boolean parameter!\n";
        throw std::invalid_argument(error.c_str());
    }

    e_not->is_lvalue_ = false;
}

void SemAnalysisVisitor::visitEVarNew(EVarNew *e_var_new)
{
    /* Code For EVarNew Goes Here */

    //visitIdent(e_var_new->ident_);
}

void SemAnalysisVisitor::visitEVStdNew(EVStdNew *ev_std_new)
{
    /* Code For EVStdNew Goes Here */

    ev_std_new->stdtype_->accept(this);
    ev_std_new->type_ = ev_std_new->stdtype_->get();

    ev_std_new->is_lvalue_ = false;
}

void SemAnalysisVisitor::visitEArrNew(EArrNew *e_arr_new)
{
    /* Code For EArrNew Goes Here */

    //visitIdent(e_arr_new->ident_);
    //e_arr_new->expr_->accept(this);
}

void SemAnalysisVisitor::visitEAStdNew(EAStdNew *ea_std_new)
{
    /* Code For EAStdNew Goes Here */

    ea_std_new->stdtype_->accept(this);
    ea_std_new->expr_->accept(this);

    if (ea_std_new->expr_->type_ != "int")
    {
        std::string error = "New operation for arrays can be performed only using int parameter!\n";
        throw std::invalid_argument(error.c_str());
    }

    ea_std_new->type_ = ea_std_new->stdtype_->get() + "[]";
    ea_std_new->is_lvalue_ = false;
}

void SemAnalysisVisitor::visitEVarCast(EVarCast *e_var_cast)
{
    /* Code For EVarCast Goes Here */

    //visitIdent(e_var_cast->ident_);
    //e_var_cast->expr_->accept(this);
}

void SemAnalysisVisitor::visitEVStdCast(EVStdCast *ev_std_cast)
{
    /* Code For EVStdCast Goes Here */

    //ev_std_cast->stdtype_->accept(this);
    //ev_std_cast->expr_->accept(this);
}

void SemAnalysisVisitor::visitEArrCast(EArrCast *e_arr_cast)
{
    /* Code For EArrCast Goes Here */

    //visitIdent(e_arr_cast->ident_);
   // e_arr_cast->expr_->accept(this);
}

void SemAnalysisVisitor::visitEAStdCast(EAStdCast *ea_std_cast)
{
    /* Code For EAStdCast Goes Here */

    //ea_std_cast->stdtype_->accept(this);
    //ea_std_cast->expr_->accept(this);
}

void SemAnalysisVisitor::visitEMul(EMul *e_mul)
{
    /* Code For EMul Goes Here */

    e_mul->expr_1->accept(this);
    e_mul->mulop_->accept(this);
    e_mul->expr_2->accept(this);

    if (e_mul->expr_1->type_ != "int" ||
        e_mul->expr_2->type_ != "int")
    {
        std::string error = "Multiplication operation can be performed only using two int parameters!\n";
        throw std::invalid_argument(error.c_str());
    }

    e_mul->type_ = "int";

    e_mul->is_lvalue_ = false;
}

void SemAnalysisVisitor::visitEAdd(EAdd *e_add)
{
    /* Code For EAdd Goes Here */

    e_add->expr_1->accept(this);
    e_add->addop_->accept(this);
    e_add->expr_2->accept(this);

    auto is_plus = dynamic_cast<Plus*>(e_add->addop_);

    if (e_add->expr_1->type_ == "string" &&
        e_add->expr_2->type_ == "string" &&
        is_plus != nullptr)
    {
        e_add->type_ = "string";
    }
    else if (e_add->expr_1->type_ == "int" &&
             e_add->expr_2->type_ == "int")
    {
        e_add->type_ = "int";
    }
    else
    {
        if (is_plus != nullptr)
        {
            std::string error = "Add operation can be performed only using two int or two string parameters!\n";
            throw std::invalid_argument(error.c_str());
        }
        else
        {
            std::string error = "Substracting operation can be performed only using two int parameters!\n";
            throw std::invalid_argument(error.c_str());
        }
    }

    e_add->is_lvalue_ = false;
}

void SemAnalysisVisitor::visitERel(ERel *e_rel)
{
    /* Code For ERel Goes Here */

    e_rel->expr_1->accept(this);
    e_rel->relop_->accept(this);
    e_rel->expr_2->accept(this);

    auto is_eq = dynamic_cast<EQU*>(e_rel->relop_);
    auto is_neq = dynamic_cast<NE*>(e_rel->relop_);
    bool is_ok = false;

    if (is_eq != nullptr || is_neq != nullptr)
    {
        if (e_rel->expr_1->type_ == "int" &&
            e_rel->expr_2->type_ == "int")
            is_ok = true;

        if (e_rel->expr_1->type_ == "boolean" &&
            e_rel->expr_2->type_ == "boolean")
            is_ok = true;

        if (!is_ok)
        {
            std::string error = "Relation operation can be performed only using two int or two boolean parameters!\n";
            throw std::invalid_argument(error.c_str());
        }
    }
    else if (e_rel->expr_1->type_ == "int" ||
             e_rel->expr_2->type_ == "int")
    {
        is_ok = true;
    }

    if (!is_ok)
    {
        std::string error = "Relation operation can be performed only using two int parameters!\n";
        throw std::invalid_argument(error.c_str());
    }

    e_rel->type_ = "boolean";
    e_rel->is_lvalue_ = false;
}

void SemAnalysisVisitor::visitEAnd(EAnd *e_and)
{
    /* Code For EAnd Goes Here */

    e_and->expr_1->accept(this);
    e_and->expr_2->accept(this);

    if (e_and->expr_1->type_ != "boolean" ||
        e_and->expr_2->type_ != "boolean")
    {
        std::string error = "And operation can be performed only using two boolean parameters!\n";
        throw std::invalid_argument(error.c_str());
    }

    e_and->type_ = "boolean";
    e_and->is_lvalue_ = false;
}

void SemAnalysisVisitor::visitEOr(EOr *e_or)
{
    /* Code For EOr Goes Here */

    e_or->expr_1->accept(this);
    e_or->expr_2->accept(this);

    if (e_or->expr_1->type_ != "boolean" ||
        e_or->expr_2->type_ != "boolean")
    {
        std::string error = "Or operation can be performed only using two boolean parameters!\n";
        throw std::invalid_argument(error.c_str());
    }

    e_or->type_ = "boolean";
    e_or->is_lvalue_ = false;
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
        (*i)->type_ = list_item->type_;
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
