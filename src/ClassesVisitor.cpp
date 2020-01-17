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

    met_def->listarg_->insert(met_def->listarg_->begin(), new Ar(new VarType(class_name), "$this"));

    met_def->listarg_->accept(this);
    met_def->block_->accept(this);
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
