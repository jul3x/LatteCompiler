#ifndef CLASSESVISITOR_HEADER
#define CLASSESVISITOR_HEADER

#include "Absyn.h"

class ClassesVisitor : public Visitor
{
public:
    void visitProgram(Program *p);
    void visitProg(Prog *p);
    void visitClsDef(ClsDef *p);
    void visitInhClsDef(InhClsDef *p);
    void visitVarDef(VarDef *p);
    void visitMetDef(MetDef *p);
    void visitAr(Ar *p);
    void visitListClsFld(ListClsFld *p);
    void visitListTopDef(ListTopDef *p);
    void visitListArg(ListArg *p);
};

#endif
