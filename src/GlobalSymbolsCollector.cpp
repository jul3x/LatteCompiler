#include "GlobalSymbols.h"
#include "CompilerMsgs.h"
#include "GlobalSymbolsCollector.h"


void GlobalSymbolsCollector::visitProgram(Program *t)
{
    t->accept(this);
}

void GlobalSymbolsCollector::visitProg(Prog *prog)
{
    prog->listtopdef_->accept(this);
}

void GlobalSymbolsCollector::visitFnDef(FnDef *fn_def)
{
    if (!GlobalSymbols::getInstance().appendFunc(fn_def->ident_, fn_def->type_, fn_def->listarg_))
    {
        CompilerMsgs::getInstance().error(fn_def->line_number_,
            "Identifier " + fn_def->ident_ + " already exists!");
    }
}

void GlobalSymbolsCollector::visitClsDef(ClsDef *cls_def)
{
    if (!GlobalSymbols::getInstance().appendClass(cls_def->ident_, ""))
    {
        CompilerMsgs::getInstance().error(cls_def->line_number_,
            "Identifier " + cls_def->ident_ + " already exists!");
    }
}

void GlobalSymbolsCollector::visitInhClsDef(InhClsDef *inh_cls_def)
{
    if (!GlobalSymbols::getInstance().appendClass(inh_cls_def->ident_1, inh_cls_def->ident_2))
    {
        CompilerMsgs::getInstance().error(inh_cls_def->line_number_,
            "Identifier " + inh_cls_def->ident_1 + " already exists!");
    }
}

void GlobalSymbolsCollector::visitListTopDef(ListTopDef *list_top_def)
{
    for (ListTopDef::iterator i = list_top_def->begin(); i != list_top_def->end(); ++i)
    {
        (*i)->accept(this);
    }
}