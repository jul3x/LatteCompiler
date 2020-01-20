#ifndef CLASSESVISITOR_HEADER
#define CLASSESVISITOR_HEADER

#include "Absyn.h"

class ClassesVisitor : public Visitor
{
public:
void visitProgram(Program *p);
    void visitProg(Prog *p);
    void visitFnDef(FnDef *p);
    void visitClsDef(ClsDef *p);
    void visitInhClsDef(InhClsDef *p);
    void visitVarDef(VarDef *p);
    void visitMetDef(MetDef *p);
    void visitAr(Ar *p);
    void visitBlk(Blk *p);
    void visitEmpty(Empty *p);
    void visitBStmt(BStmt *p);
    void visitDecl(Decl *p);
    void visitNoInit(NoInit *p);
    void visitInit(Init *p);
    void visitAss(Ass *p);
    void visitIncr(Incr *p);
    void visitDecr(Decr *p);
    void visitRet(Ret *p);
    void visitVRet(VRet *p);
    void visitCond(Cond *p);
    void visitCondElse(CondElse *p);
    void visitWhile(While *p);
    void visitFor(For *p);
    void visitSExp(SExp *p);
    void visitInt(Int *p);
    void visitStr(Str *p);
    void visitBool(Bool *p);
    void visitVoid(Void *p);
    void visitStVarType(StVarType *p);
    void visitStArrType(StArrType *p);
    void visitVarType(VarType *p);
    void visitArrType(ArrType *p);
    void visitFun(Fun *p);
    void visitEVar(EVar *p);
    void visitEClsVar(EClsVar *p);
    void visitEArrVar(EArrVar *p);
    void visitELitInt(ELitInt *p);
    void visitEString(EString *p);
    void visitELitTrue(ELitTrue *p);
    void visitELitFalse(ELitFalse *p);
    void visitELitNull(ELitNull *p);
    void visitEApp(EApp *p);
    void visitEClsApp(EClsApp *p);
    void visitENeg(ENeg *p);
    void visitENot(ENot *p);
    void visitEVarNew(EVarNew *p);
    void visitEVStdNew(EVStdNew *p);
    void visitEArrNew(EArrNew *p);
    void visitEAStdNew(EAStdNew *p);
    void visitEVarCast(EVarCast *p);
    void visitEVStdCast(EVStdCast *p);
    void visitEArrCast(EArrCast *p);
    void visitEAStdCast(EAStdCast *p);
    void visitEMul(EMul *p);
    void visitEAdd(EAdd *p);
    void visitERel(ERel *p);
    void visitEAnd(EAnd *p);
    void visitEOr(EOr *p);
    void visitPlus(Plus *p);
    void visitMinus(Minus *p);
    void visitTimes(Times *p);
    void visitDiv(Div *p);
    void visitMod(Mod *p);
    void visitLTH(LTH *p);
    void visitLE(LE *p);
    void visitGTH(GTH *p);
    void visitGE(GE *p);
    void visitEQU(EQU *p);
    void visitNE(NE *p);
    void visitListClsFld(ListClsFld *p);
    void visitListTopDef(ListTopDef *p);
    void visitListIdent(ListIdent *p);
    void visitListArg(ListArg *p);
    void visitListStmt(ListStmt *p);
    void visitListItem(ListItem *p);
    void visitListType(ListType *p);
    void visitListExpr(ListExpr *p);

    void visitInteger(Integer x);
    void visitChar(Char x);
    void visitDouble(Double x);
    void visitString(String x);
    void visitIdent(Ident x);

private:
    Expr* replaceIfUnknown(Expr *expr);

};

#endif
