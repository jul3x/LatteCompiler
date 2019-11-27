#include "GlobalSymbols.h"

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
    GlobalSymbols::getInstance().appendFunc(fn_def->ident_, fn_def->type_, fn_def->listarg_);

    fprintf(stderr, "New function %s of type: %s(%s)\n", fn_def->ident_.c_str(),
        fn_def->type_->get().c_str(), fn_def->listarg_->printTypes().c_str());
}

void GlobalSymbolsCollector::visitClsDef(ClsDef *cls_def)
{
    GlobalSymbols::getInstance().appendClass(cls_def->ident_, "");
    fprintf(stderr, "New class: %s()\n", cls_def->ident_.c_str());
}

void GlobalSymbolsCollector::visitInhClsDef(InhClsDef *inh_cls_def)
{
    GlobalSymbols::getInstance().appendClass(inh_cls_def->ident_1, inh_cls_def->ident_2);
    fprintf(stderr, "New class: %s(%s)\n", inh_cls_def->ident_1.c_str(), inh_cls_def->ident_2.c_str());
}

void GlobalSymbolsCollector::visitListTopDef(ListTopDef *list_top_def)
{
    for (ListTopDef::iterator i = list_top_def->begin(); i != list_top_def->end(); ++i)
    {
        (*i)->accept(this);
    }
}