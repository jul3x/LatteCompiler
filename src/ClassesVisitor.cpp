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
    ControlFlow::getInstance().newClass(cls_def->ident_);

    cls_def->listclsfld_->accept(this);
}

void ClassesVisitor::visitInhClsDef(InhClsDef *inh_cls_def)
{
    throw std::invalid_argument("Unfortunately inherited classes are not permitted in this version of latc_x86!");
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
    throw std::invalid_argument("Unfortunately methods in classes are not permitted in this version of latc_x86!");
}

void ClassesVisitor::visitAr(Ar *ar)
{
    // TODO
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
    for (ListTopDef::iterator i = list_top_def->begin(); i != list_top_def->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void ClassesVisitor::visitListArg(ListArg *list_arg)
{
    for (ListArg::iterator i = list_arg->begin(); i != list_arg->end(); ++i)
    {
        (*i)->accept(this);
    }
}
