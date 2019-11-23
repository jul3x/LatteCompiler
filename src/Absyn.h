#ifndef ABSYN_HEADER
#define ABSYN_HEADER

#include <string>
#include <vector>

//C++ Abstract Syntax Interface generated by the BNF Converter.

/********************   TypeDef Section    ********************/

typedef int Integer;
typedef char Char;
typedef double Double;
typedef std::string String;
typedef std::string Ident;

/********************   Forward Declarations    ********************/

class Program;
class TopDef;
class ClsFld;
class Arg;
class Block;
class Stmt;
class Item;
class StdType;
class Type;
class Expr;
class AddOp;
class MulOp;
class RelOp;
class Prog;
class FnDef;
class ClsDef;
class InhClsDef;
class VarDef;
class MetDef;
class Ar;
class Blk;
class Empty;
class BStmt;
class Decl;
class NoInit;
class Init;
class Ass;
class Incr;
class Decr;
class Ret;
class VRet;
class Cond;
class CondElse;
class While;
class For;
class SExp;
class Int;
class Str;
class Bool;
class Void;
class StVarType;
class StArrType;
class VarType;
class ArrType;
class Fun;
class EVar;
class EClsVar;
class EArrVar;
class ELitInt;
class EString;
class ELitTrue;
class ELitFalse;
class ELitNull;
class EApp;
class EClsApp;
class ENeg;
class ENot;
class EVarNew;
class EVStdNew;
class EArrNew;
class EAStdNew;
class EVarCast;
class EVStdCast;
class EArrCast;
class EAStdCast;
class EMul;
class EAdd;
class ERel;
class EAnd;
class EOr;
class Plus;
class Minus;
class Times;
class Div;
class Mod;
class LTH;
class LE;
class GTH;
class GE;
class EQU;
class NE;
class ListClsFld;
class ListTopDef;
class ListIdent;
class ListArg;
class ListStmt;
class ListItem;
class ListType;
class ListExpr;

/********************   Visitor Interfaces    ********************/
class Visitor
{
public:
    virtual ~Visitor() {}
    virtual void visitProgram(Program *p) = 0;
    virtual void visitTopDef(TopDef *p) = 0;
    virtual void visitClsFld(ClsFld *p) = 0;
    virtual void visitArg(Arg *p) = 0;
    virtual void visitBlock(Block *p) = 0;
    virtual void visitStmt(Stmt *p) = 0;
    virtual void visitItem(Item *p) = 0;
    virtual void visitStdType(StdType *p) = 0;
    virtual void visitType(Type *p) = 0;
    virtual void visitExpr(Expr *p) = 0;
    virtual void visitAddOp(AddOp *p) = 0;
    virtual void visitMulOp(MulOp *p) = 0;
    virtual void visitRelOp(RelOp *p) = 0;
    virtual void visitProg(Prog *p) = 0;
    virtual void visitFnDef(FnDef *p) = 0;
    virtual void visitClsDef(ClsDef *p) = 0;
    virtual void visitInhClsDef(InhClsDef *p) = 0;
    virtual void visitVarDef(VarDef *p) = 0;
    virtual void visitMetDef(MetDef *p) = 0;
    virtual void visitAr(Ar *p) = 0;
    virtual void visitBlk(Blk *p) = 0;
    virtual void visitEmpty(Empty *p) = 0;
    virtual void visitBStmt(BStmt *p) = 0;
    virtual void visitDecl(Decl *p) = 0;
    virtual void visitNoInit(NoInit *p) = 0;
    virtual void visitInit(Init *p) = 0;
    virtual void visitAss(Ass *p) = 0;
    virtual void visitIncr(Incr *p) = 0;
    virtual void visitDecr(Decr *p) = 0;
    virtual void visitRet(Ret *p) = 0;
    virtual void visitVRet(VRet *p) = 0;
    virtual void visitCond(Cond *p) = 0;
    virtual void visitCondElse(CondElse *p) = 0;
    virtual void visitWhile(While *p) = 0;
    virtual void visitFor(For *p) = 0;
    virtual void visitSExp(SExp *p) = 0;
    virtual void visitInt(Int *p) = 0;
    virtual void visitStr(Str *p) = 0;
    virtual void visitBool(Bool *p) = 0;
    virtual void visitVoid(Void *p) = 0;
    virtual void visitStVarType(StVarType *p) = 0;
    virtual void visitStArrType(StArrType *p) = 0;
    virtual void visitVarType(VarType *p) = 0;
    virtual void visitArrType(ArrType *p) = 0;
    virtual void visitFun(Fun *p) = 0;
    virtual void visitEVar(EVar *p) = 0;
    virtual void visitEClsVar(EClsVar *p) = 0;
    virtual void visitEArrVar(EArrVar *p) = 0;
    virtual void visitELitInt(ELitInt *p) = 0;
    virtual void visitEString(EString *p) = 0;
    virtual void visitELitTrue(ELitTrue *p) = 0;
    virtual void visitELitFalse(ELitFalse *p) = 0;
    virtual void visitELitNull(ELitNull *p) = 0;
    virtual void visitEApp(EApp *p) = 0;
    virtual void visitEClsApp(EClsApp *p) = 0;
    virtual void visitENeg(ENeg *p) = 0;
    virtual void visitENot(ENot *p) = 0;
    virtual void visitEVarNew(EVarNew *p) = 0;
    virtual void visitEVStdNew(EVStdNew *p) = 0;
    virtual void visitEArrNew(EArrNew *p) = 0;
    virtual void visitEAStdNew(EAStdNew *p) = 0;
    virtual void visitEVarCast(EVarCast *p) = 0;
    virtual void visitEVStdCast(EVStdCast *p) = 0;
    virtual void visitEArrCast(EArrCast *p) = 0;
    virtual void visitEAStdCast(EAStdCast *p) = 0;
    virtual void visitEMul(EMul *p) = 0;
    virtual void visitEAdd(EAdd *p) = 0;
    virtual void visitERel(ERel *p) = 0;
    virtual void visitEAnd(EAnd *p) = 0;
    virtual void visitEOr(EOr *p) = 0;
    virtual void visitPlus(Plus *p) = 0;
    virtual void visitMinus(Minus *p) = 0;
    virtual void visitTimes(Times *p) = 0;
    virtual void visitDiv(Div *p) = 0;
    virtual void visitMod(Mod *p) = 0;
    virtual void visitLTH(LTH *p) = 0;
    virtual void visitLE(LE *p) = 0;
    virtual void visitGTH(GTH *p) = 0;
    virtual void visitGE(GE *p) = 0;
    virtual void visitEQU(EQU *p) = 0;
    virtual void visitNE(NE *p) = 0;
    virtual void visitListClsFld(ListClsFld *p) = 0;
    virtual void visitListTopDef(ListTopDef *p) = 0;
    virtual void visitListIdent(ListIdent *p) = 0;
    virtual void visitListArg(ListArg *p) = 0;
    virtual void visitListStmt(ListStmt *p) = 0;
    virtual void visitListItem(ListItem *p) = 0;
    virtual void visitListType(ListType *p) = 0;
    virtual void visitListExpr(ListExpr *p) = 0;

    virtual void visitInteger(Integer x) = 0;
    virtual void visitChar(Char x) = 0;
    virtual void visitDouble(Double x) = 0;
    virtual void visitString(String x) = 0;
    virtual void visitIdent(Ident x) = 0;
};

class Visitable
{
public:
    virtual ~Visitable() {}
    virtual void accept(Visitor *v) = 0;
};

/********************   Abstract Syntax Classes    ********************/

class Program : public Visitable
{
public:
    virtual Program *clone() const = 0;
};

class TopDef : public Visitable
{
public:
    virtual TopDef *clone() const = 0;
};

class ClsFld : public Visitable
{
public:
    virtual ClsFld *clone() const = 0;
};

class Arg : public Visitable
{
public:
    virtual Arg *clone() const = 0;
};

class Block : public Visitable
{
public:
    virtual Block *clone() const = 0;
};

class Stmt : public Visitable
{
public:
    virtual Stmt *clone() const = 0;
};

class Item : public Visitable
{
public:
    virtual Item *clone() const = 0;
};

class StdType : public Visitable
{
public:
    virtual StdType *clone() const = 0;
};

class Type : public Visitable
{
public:
    virtual Type *clone() const = 0;
};

class Expr : public Visitable
{
public:
    virtual Expr *clone() const = 0;
};

class AddOp : public Visitable
{
public:
    virtual AddOp *clone() const = 0;
};

class MulOp : public Visitable
{
public:
    virtual MulOp *clone() const = 0;
};

class RelOp : public Visitable
{
public:
    virtual RelOp *clone() const = 0;
};

class Prog : public Program
{
public:
    ListTopDef *listtopdef_;

    Prog(const Prog &);
    Prog &operator=(const Prog &);
    Prog(ListTopDef *p1);
    ~Prog();
    virtual void accept(Visitor *v);
    virtual Prog *clone() const;
    void swap(Prog &);
};

class FnDef : public TopDef
{
public:
    Type *type_;
    Ident ident_;
    ListArg *listarg_;
    Block *block_;

    FnDef(const FnDef &);
    FnDef &operator=(const FnDef &);
    FnDef(Type *p1, Ident p2, ListArg *p3, Block *p4);
    ~FnDef();
    virtual void accept(Visitor *v);
    virtual FnDef *clone() const;
    void swap(FnDef &);
};

class ClsDef : public TopDef
{
public:
    Ident ident_;
    ListClsFld *listclsfld_;

    ClsDef(const ClsDef &);
    ClsDef &operator=(const ClsDef &);
    ClsDef(Ident p1, ListClsFld *p2);
    ~ClsDef();
    virtual void accept(Visitor *v);
    virtual ClsDef *clone() const;
    void swap(ClsDef &);
};

class InhClsDef : public TopDef
{
public:
    Ident ident_1;
    Ident ident_2;
    ListClsFld *listclsfld_;

    InhClsDef(const InhClsDef &);
    InhClsDef &operator=(const InhClsDef &);
    InhClsDef(Ident p1, Ident p2, ListClsFld *p3);
    ~InhClsDef();
    virtual void accept(Visitor *v);
    virtual InhClsDef *clone() const;
    void swap(InhClsDef &);
};

class VarDef : public ClsFld
{
public:
    Type *type_;
    ListIdent *listident_;

    VarDef(const VarDef &);
    VarDef &operator=(const VarDef &);
    VarDef(Type *p1, ListIdent *p2);
    ~VarDef();
    virtual void accept(Visitor *v);
    virtual VarDef *clone() const;
    void swap(VarDef &);
};

class MetDef : public ClsFld
{
public:
    Type *type_;
    Ident ident_;
    ListArg *listarg_;
    Block *block_;

    MetDef(const MetDef &);
    MetDef &operator=(const MetDef &);
    MetDef(Type *p1, Ident p2, ListArg *p3, Block *p4);
    ~MetDef();
    virtual void accept(Visitor *v);
    virtual MetDef *clone() const;
    void swap(MetDef &);
};

class Ar : public Arg
{
public:
    Type *type_;
    Ident ident_;

    Ar(const Ar &);
    Ar &operator=(const Ar &);
    Ar(Type *p1, Ident p2);
    ~Ar();
    virtual void accept(Visitor *v);
    virtual Ar *clone() const;
    void swap(Ar &);
};

class Blk : public Block
{
public:
    ListStmt *liststmt_;

    Blk(const Blk &);
    Blk &operator=(const Blk &);
    Blk(ListStmt *p1);
    ~Blk();
    virtual void accept(Visitor *v);
    virtual Blk *clone() const;
    void swap(Blk &);
};

class Empty : public Stmt
{
public:
    Empty(const Empty &);
    Empty &operator=(const Empty &);
    Empty();
    ~Empty();
    virtual void accept(Visitor *v);
    virtual Empty *clone() const;
    void swap(Empty &);
};

class BStmt : public Stmt
{
public:
    Block *block_;

    BStmt(const BStmt &);
    BStmt &operator=(const BStmt &);
    BStmt(Block *p1);
    ~BStmt();
    virtual void accept(Visitor *v);
    virtual BStmt *clone() const;
    void swap(BStmt &);
};

class Decl : public Stmt
{
public:
    Type *type_;
    ListItem *listitem_;

    Decl(const Decl &);
    Decl &operator=(const Decl &);
    Decl(Type *p1, ListItem *p2);
    ~Decl();
    virtual void accept(Visitor *v);
    virtual Decl *clone() const;
    void swap(Decl &);
};

class Ass : public Stmt
{
public:
    Expr *expr_1;
    Expr *expr_2;

    Ass(const Ass &);
    Ass &operator=(const Ass &);
    Ass(Expr *p1, Expr *p2);
    ~Ass();
    virtual void accept(Visitor *v);
    virtual Ass *clone() const;
    void swap(Ass &);
};

class Incr : public Stmt
{
public:
    Expr *expr_;

    Incr(const Incr &);
    Incr &operator=(const Incr &);
    Incr(Expr *p1);
    ~Incr();
    virtual void accept(Visitor *v);
    virtual Incr *clone() const;
    void swap(Incr &);
};

class Decr : public Stmt
{
public:
    Expr *expr_;

    Decr(const Decr &);
    Decr &operator=(const Decr &);
    Decr(Expr *p1);
    ~Decr();
    virtual void accept(Visitor *v);
    virtual Decr *clone() const;
    void swap(Decr &);
};

class Ret : public Stmt
{
public:
    Expr *expr_;

    Ret(const Ret &);
    Ret &operator=(const Ret &);
    Ret(Expr *p1);
    ~Ret();
    virtual void accept(Visitor *v);
    virtual Ret *clone() const;
    void swap(Ret &);
};

class VRet : public Stmt
{
public:
    VRet(const VRet &);
    VRet &operator=(const VRet &);
    VRet();
    ~VRet();
    virtual void accept(Visitor *v);
    virtual VRet *clone() const;
    void swap(VRet &);
};

class Cond : public Stmt
{
public:
    Expr *expr_;
    Stmt *stmt_;

    Cond(const Cond &);
    Cond &operator=(const Cond &);
    Cond(Expr *p1, Stmt *p2);
    ~Cond();
    virtual void accept(Visitor *v);
    virtual Cond *clone() const;
    void swap(Cond &);
};

class CondElse : public Stmt
{
public:
    Expr *expr_;
    Stmt *stmt_1;
    Stmt *stmt_2;

    CondElse(const CondElse &);
    CondElse &operator=(const CondElse &);
    CondElse(Expr *p1, Stmt *p2, Stmt *p3);
    ~CondElse();
    virtual void accept(Visitor *v);
    virtual CondElse *clone() const;
    void swap(CondElse &);
};

class While : public Stmt
{
public:
    Expr *expr_;
    Stmt *stmt_;

    While(const While &);
    While &operator=(const While &);
    While(Expr *p1, Stmt *p2);
    ~While();
    virtual void accept(Visitor *v);
    virtual While *clone() const;
    void swap(While &);
};

class For : public Stmt
{
public:
    Type *type_;
    Ident ident_;
    Expr *expr_;
    Stmt *stmt_;

    For(const For &);
    For &operator=(const For &);
    For(Type *p1, Ident p2, Expr *p3, Stmt *p4);
    ~For();
    virtual void accept(Visitor *v);
    virtual For *clone() const;
    void swap(For &);
};

class SExp : public Stmt
{
public:
    Expr *expr_;

    SExp(const SExp &);
    SExp &operator=(const SExp &);
    SExp(Expr *p1);
    ~SExp();
    virtual void accept(Visitor *v);
    virtual SExp *clone() const;
    void swap(SExp &);
};

class NoInit : public Item
{
public:
    Ident ident_;

    NoInit(const NoInit &);
    NoInit &operator=(const NoInit &);
    NoInit(Ident p1);
    ~NoInit();
    virtual void accept(Visitor *v);
    virtual NoInit *clone() const;
    void swap(NoInit &);
};

class Init : public Item
{
public:
    Ident ident_;
    Expr *expr_;

    Init(const Init &);
    Init &operator=(const Init &);
    Init(Ident p1, Expr *p2);
    ~Init();
    virtual void accept(Visitor *v);
    virtual Init *clone() const;
    void swap(Init &);
};

class Int : public StdType
{
public:
    Int(const Int &);
    Int &operator=(const Int &);
    Int();
    ~Int();
    virtual void accept(Visitor *v);
    virtual Int *clone() const;
    void swap(Int &);
};

class Str : public StdType
{
public:
    Str(const Str &);
    Str &operator=(const Str &);
    Str();
    ~Str();
    virtual void accept(Visitor *v);
    virtual Str *clone() const;
    void swap(Str &);
};

class Bool : public StdType
{
public:
    Bool(const Bool &);
    Bool &operator=(const Bool &);
    Bool();
    ~Bool();
    virtual void accept(Visitor *v);
    virtual Bool *clone() const;
    void swap(Bool &);
};

class Void : public StdType
{
public:
    Void(const Void &);
    Void &operator=(const Void &);
    Void();
    ~Void();
    virtual void accept(Visitor *v);
    virtual Void *clone() const;
    void swap(Void &);
};

class StVarType : public Type
{
public:
    StdType *stdtype_;

    StVarType(const StVarType &);
    StVarType &operator=(const StVarType &);
    StVarType(StdType *p1);
    ~StVarType();
    virtual void accept(Visitor *v);
    virtual StVarType *clone() const;
    void swap(StVarType &);
};

class StArrType : public Type
{
public:
    StdType *stdtype_;

    StArrType(const StArrType &);
    StArrType &operator=(const StArrType &);
    StArrType(StdType *p1);
    ~StArrType();
    virtual void accept(Visitor *v);
    virtual StArrType *clone() const;
    void swap(StArrType &);
};

class VarType : public Type
{
public:
    Ident ident_;

    VarType(const VarType &);
    VarType &operator=(const VarType &);
    VarType(Ident p1);
    ~VarType();
    virtual void accept(Visitor *v);
    virtual VarType *clone() const;
    void swap(VarType &);
};

class ArrType : public Type
{
public:
    Ident ident_;

    ArrType(const ArrType &);
    ArrType &operator=(const ArrType &);
    ArrType(Ident p1);
    ~ArrType();
    virtual void accept(Visitor *v);
    virtual ArrType *clone() const;
    void swap(ArrType &);
};

class Fun : public Type
{
public:
    Type *type_;
    ListType *listtype_;

    Fun(const Fun &);
    Fun &operator=(const Fun &);
    Fun(Type *p1, ListType *p2);
    ~Fun();
    virtual void accept(Visitor *v);
    virtual Fun *clone() const;
    void swap(Fun &);
};

class EVar : public Expr
{
public:
    Ident ident_;

    EVar(const EVar &);
    EVar &operator=(const EVar &);
    EVar(Ident p1);
    ~EVar();
    virtual void accept(Visitor *v);
    virtual EVar *clone() const;
    void swap(EVar &);
};

class EClsVar : public Expr
{
public:
    Expr *expr_;
    Ident ident_;

    EClsVar(const EClsVar &);
    EClsVar &operator=(const EClsVar &);
    EClsVar(Expr *p1, Ident p2);
    ~EClsVar();
    virtual void accept(Visitor *v);
    virtual EClsVar *clone() const;
    void swap(EClsVar &);
};

class EArrVar : public Expr
{
public:
    Expr *expr_1;
    Expr *expr_2;

    EArrVar(const EArrVar &);
    EArrVar &operator=(const EArrVar &);
    EArrVar(Expr *p1, Expr *p2);
    ~EArrVar();
    virtual void accept(Visitor *v);
    virtual EArrVar *clone() const;
    void swap(EArrVar &);
};

class ELitInt : public Expr
{
public:
    Integer integer_;

    ELitInt(const ELitInt &);
    ELitInt &operator=(const ELitInt &);
    ELitInt(Integer p1);
    ~ELitInt();
    virtual void accept(Visitor *v);
    virtual ELitInt *clone() const;
    void swap(ELitInt &);
};

class EString : public Expr
{
public:
    String string_;

    EString(const EString &);
    EString &operator=(const EString &);
    EString(String p1);
    ~EString();
    virtual void accept(Visitor *v);
    virtual EString *clone() const;
    void swap(EString &);
};

class ELitTrue : public Expr
{
public:
    ELitTrue(const ELitTrue &);
    ELitTrue &operator=(const ELitTrue &);
    ELitTrue();
    ~ELitTrue();
    virtual void accept(Visitor *v);
    virtual ELitTrue *clone() const;
    void swap(ELitTrue &);
};

class ELitFalse : public Expr
{
public:
    ELitFalse(const ELitFalse &);
    ELitFalse &operator=(const ELitFalse &);
    ELitFalse();
    ~ELitFalse();
    virtual void accept(Visitor *v);
    virtual ELitFalse *clone() const;
    void swap(ELitFalse &);
};

class ELitNull : public Expr
{
public:
    ELitNull(const ELitNull &);
    ELitNull &operator=(const ELitNull &);
    ELitNull();
    ~ELitNull();
    virtual void accept(Visitor *v);
    virtual ELitNull *clone() const;
    void swap(ELitNull &);
};

class EApp : public Expr
{
public:
    Ident ident_;
    ListExpr *listexpr_;

    EApp(const EApp &);
    EApp &operator=(const EApp &);
    EApp(Ident p1, ListExpr *p2);
    ~EApp();
    virtual void accept(Visitor *v);
    virtual EApp *clone() const;
    void swap(EApp &);
};

class EClsApp : public Expr
{
public:
    Expr *expr_;
    Ident ident_;
    ListExpr *listexpr_;

    EClsApp(const EClsApp &);
    EClsApp &operator=(const EClsApp &);
    EClsApp(Expr *p1, Ident p2, ListExpr *p3);
    ~EClsApp();
    virtual void accept(Visitor *v);
    virtual EClsApp *clone() const;
    void swap(EClsApp &);
};

class ENeg : public Expr
{
public:
    Expr *expr_;

    ENeg(const ENeg &);
    ENeg &operator=(const ENeg &);
    ENeg(Expr *p1);
    ~ENeg();
    virtual void accept(Visitor *v);
    virtual ENeg *clone() const;
    void swap(ENeg &);
};

class ENot : public Expr
{
public:
    Expr *expr_;

    ENot(const ENot &);
    ENot &operator=(const ENot &);
    ENot(Expr *p1);
    ~ENot();
    virtual void accept(Visitor *v);
    virtual ENot *clone() const;
    void swap(ENot &);
};

class EVarNew : public Expr
{
public:
    Ident ident_;

    EVarNew(const EVarNew &);
    EVarNew &operator=(const EVarNew &);
    EVarNew(Ident p1);
    ~EVarNew();
    virtual void accept(Visitor *v);
    virtual EVarNew *clone() const;
    void swap(EVarNew &);
};

class EVStdNew : public Expr
{
public:
    StdType *stdtype_;

    EVStdNew(const EVStdNew &);
    EVStdNew &operator=(const EVStdNew &);
    EVStdNew(StdType *p1);
    ~EVStdNew();
    virtual void accept(Visitor *v);
    virtual EVStdNew *clone() const;
    void swap(EVStdNew &);
};

class EArrNew : public Expr
{
public:
    Ident ident_;
    Expr *expr_;

    EArrNew(const EArrNew &);
    EArrNew &operator=(const EArrNew &);
    EArrNew(Ident p1, Expr *p2);
    ~EArrNew();
    virtual void accept(Visitor *v);
    virtual EArrNew *clone() const;
    void swap(EArrNew &);
};

class EAStdNew : public Expr
{
public:
    StdType *stdtype_;
    Expr *expr_;

    EAStdNew(const EAStdNew &);
    EAStdNew &operator=(const EAStdNew &);
    EAStdNew(StdType *p1, Expr *p2);
    ~EAStdNew();
    virtual void accept(Visitor *v);
    virtual EAStdNew *clone() const;
    void swap(EAStdNew &);
};

class EVarCast : public Expr
{
public:
    Ident ident_;
    Expr *expr_;

    EVarCast(const EVarCast &);
    EVarCast &operator=(const EVarCast &);
    EVarCast(Ident p1, Expr *p2);
    ~EVarCast();
    virtual void accept(Visitor *v);
    virtual EVarCast *clone() const;
    void swap(EVarCast &);
};

class EVStdCast : public Expr
{
public:
    StdType *stdtype_;
    Expr *expr_;

    EVStdCast(const EVStdCast &);
    EVStdCast &operator=(const EVStdCast &);
    EVStdCast(StdType *p1, Expr *p2);
    ~EVStdCast();
    virtual void accept(Visitor *v);
    virtual EVStdCast *clone() const;
    void swap(EVStdCast &);
};

class EArrCast : public Expr
{
public:
    Ident ident_;
    Expr *expr_;

    EArrCast(const EArrCast &);
    EArrCast &operator=(const EArrCast &);
    EArrCast(Ident p1, Expr *p2);
    ~EArrCast();
    virtual void accept(Visitor *v);
    virtual EArrCast *clone() const;
    void swap(EArrCast &);
};

class EAStdCast : public Expr
{
public:
    StdType *stdtype_;
    Expr *expr_;

    EAStdCast(const EAStdCast &);
    EAStdCast &operator=(const EAStdCast &);
    EAStdCast(StdType *p1, Expr *p2);
    ~EAStdCast();
    virtual void accept(Visitor *v);
    virtual EAStdCast *clone() const;
    void swap(EAStdCast &);
};

class EMul : public Expr
{
public:
    Expr *expr_1;
    MulOp *mulop_;
    Expr *expr_2;

    EMul(const EMul &);
    EMul &operator=(const EMul &);
    EMul(Expr *p1, MulOp *p2, Expr *p3);
    ~EMul();
    virtual void accept(Visitor *v);
    virtual EMul *clone() const;
    void swap(EMul &);
};

class EAdd : public Expr
{
public:
    Expr *expr_1;
    AddOp *addop_;
    Expr *expr_2;

    EAdd(const EAdd &);
    EAdd &operator=(const EAdd &);
    EAdd(Expr *p1, AddOp *p2, Expr *p3);
    ~EAdd();
    virtual void accept(Visitor *v);
    virtual EAdd *clone() const;
    void swap(EAdd &);
};

class ERel : public Expr
{
public:
    Expr *expr_1;
    RelOp *relop_;
    Expr *expr_2;

    ERel(const ERel &);
    ERel &operator=(const ERel &);
    ERel(Expr *p1, RelOp *p2, Expr *p3);
    ~ERel();
    virtual void accept(Visitor *v);
    virtual ERel *clone() const;
    void swap(ERel &);
};

class EAnd : public Expr
{
public:
    Expr *expr_1;
    Expr *expr_2;

    EAnd(const EAnd &);
    EAnd &operator=(const EAnd &);
    EAnd(Expr *p1, Expr *p2);
    ~EAnd();
    virtual void accept(Visitor *v);
    virtual EAnd *clone() const;
    void swap(EAnd &);
};

class EOr : public Expr
{
public:
    Expr *expr_1;
    Expr *expr_2;

    EOr(const EOr &);
    EOr &operator=(const EOr &);
    EOr(Expr *p1, Expr *p2);
    ~EOr();
    virtual void accept(Visitor *v);
    virtual EOr *clone() const;
    void swap(EOr &);
};

class Plus : public AddOp
{
public:
    Plus(const Plus &);
    Plus &operator=(const Plus &);
    Plus();
    ~Plus();
    virtual void accept(Visitor *v);
    virtual Plus *clone() const;
    void swap(Plus &);
};

class Minus : public AddOp
{
public:
    Minus(const Minus &);
    Minus &operator=(const Minus &);
    Minus();
    ~Minus();
    virtual void accept(Visitor *v);
    virtual Minus *clone() const;
    void swap(Minus &);
};

class Times : public MulOp
{
public:
    Times(const Times &);
    Times &operator=(const Times &);
    Times();
    ~Times();
    virtual void accept(Visitor *v);
    virtual Times *clone() const;
    void swap(Times &);
};

class Div : public MulOp
{
public:
    Div(const Div &);
    Div &operator=(const Div &);
    Div();
    ~Div();
    virtual void accept(Visitor *v);
    virtual Div *clone() const;
    void swap(Div &);
};

class Mod : public MulOp
{
public:
    Mod(const Mod &);
    Mod &operator=(const Mod &);
    Mod();
    ~Mod();
    virtual void accept(Visitor *v);
    virtual Mod *clone() const;
    void swap(Mod &);
};

class LTH : public RelOp
{
public:
    LTH(const LTH &);
    LTH &operator=(const LTH &);
    LTH();
    ~LTH();
    virtual void accept(Visitor *v);
    virtual LTH *clone() const;
    void swap(LTH &);
};

class LE : public RelOp
{
public:
    LE(const LE &);
    LE &operator=(const LE &);
    LE();
    ~LE();
    virtual void accept(Visitor *v);
    virtual LE *clone() const;
    void swap(LE &);
};

class GTH : public RelOp
{
public:
    GTH(const GTH &);
    GTH &operator=(const GTH &);
    GTH();
    ~GTH();
    virtual void accept(Visitor *v);
    virtual GTH *clone() const;
    void swap(GTH &);
};

class GE : public RelOp
{
public:
    GE(const GE &);
    GE &operator=(const GE &);
    GE();
    ~GE();
    virtual void accept(Visitor *v);
    virtual GE *clone() const;
    void swap(GE &);
};

class EQU : public RelOp
{
public:
    EQU(const EQU &);
    EQU &operator=(const EQU &);
    EQU();
    ~EQU();
    virtual void accept(Visitor *v);
    virtual EQU *clone() const;
    void swap(EQU &);
};

class NE : public RelOp
{
public:
    NE(const NE &);
    NE &operator=(const NE &);
    NE();
    ~NE();
    virtual void accept(Visitor *v);
    virtual NE *clone() const;
    void swap(NE &);
};

class ListClsFld : public Visitable, public std::vector<ClsFld *>
{
public:
    virtual void accept(Visitor *v);
    virtual ListClsFld *clone() const;
};

class ListTopDef : public Visitable, public std::vector<TopDef *>
{
public:
    virtual void accept(Visitor *v);
    virtual ListTopDef *clone() const;
};

class ListIdent : public Visitable, public std::vector<Ident>
{
public:
    virtual void accept(Visitor *v);
    virtual ListIdent *clone() const;
};

class ListArg : public Visitable, public std::vector<Arg *>
{
public:
    virtual void accept(Visitor *v);
    virtual ListArg *clone() const;
};

class ListStmt : public Visitable, public std::vector<Stmt *>
{
public:
    virtual void accept(Visitor *v);
    virtual ListStmt *clone() const;
};

class ListItem : public Visitable, public std::vector<Item *>
{
public:
    virtual void accept(Visitor *v);
    virtual ListItem *clone() const;
};

class ListType : public Visitable, public std::vector<Type *>
{
public:
    virtual void accept(Visitor *v);
    virtual ListType *clone() const;
};

class ListExpr : public Visitable, public std::vector<Expr *>
{
public:
    virtual void accept(Visitor *v);
    virtual ListExpr *clone() const;
};

#endif
