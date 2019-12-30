#ifndef GLOBALSYMBOLSCOLLECTOR_HEADER
#define GLOBALSYMBOLSCOLLECTOR_HEADER

#include <string>

#include "Absyn.h"

class GlobalSymbolsCollector : public Visitor
{
public:
    void visitProgram(Program *p);
    void visitProg(Prog *p);
    void visitFnDef(FnDef *p);
    void visitClsDef(ClsDef *p);
    void visitInhClsDef(InhClsDef *p);
    void visitListTopDef(ListTopDef *p);
};

#endif
