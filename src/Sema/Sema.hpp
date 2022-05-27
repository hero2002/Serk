#pragma once
#include "AST/AST.hpp"
#include "Diag/Diagnostic.hpp"
#include "Scope.hpp"


class Sema {
public:
  void enterScope(Decl *);
  void leaveScope();
  Scope *CurrentScope;
  Decl *CurrentDecl;
  DiagnosticsEngine &Diags;

  TypeDeclaration *IntegerType;
  TypeDeclaration *BoolType;
  TypeDeclaration *StrType;
  Sema(DiagnosticsEngine &Diags)
      : CurrentScope(nullptr), CurrentDecl(nullptr), Diags(Diags) {
    initialize();
  }

  void initialize();

  FunctionDeclaration *actOnFunctionDeclaration(SMLoc Loc, StringRef Name);
  void actOnFunctionHeading(FunctionDeclaration *ProcDecl, ParamList &Params,
                            Decl *RetType);
  void actOnFunctionDeclaration(FunctionDeclaration *ProcDecl, SMLoc Loc,
                                StringRef Name, DeclList &Decls,
                                StmtList &Stmts);

  TypeDeclaration *actOnTypeRefernce(SMLoc Loc, StringRef Name);
  ParameterDeclaration *actOnParmaDecl(SMLoc Loc, StringRef Name, Decl *Type);
  VariableDeclaration *actOnVarDeceleration(SMLoc Loc, StringRef Name,
                                            Decl *Type);
  void actOnReturnStatement(StmtList &Stmts, SMLoc Loc, Expr *RetVal);
  Decl *actOnVarRefernce(SMLoc Loc, StringRef Name);

  void actOnAssignment(StmtList &Stmts, SMLoc Loc, Expr *D, Expr *E);

  CompileUnitDeclaration *actOnCompileUnitDeclaration(SMLoc Loc,
                                                      StringRef Name);
  void actOnCompileUnitDeclaration(CompileUnitDeclaration *ModDecl, SMLoc Loc,
                                   StringRef Name, DeclList &Decls,
                                   StmtList &Stmts);

  Expr *actOnDesignator(Decl *D);
  Expr *actOnIntegerLiteral(SMLoc Loc, StringRef Literal);
  Expr *actOnExpression(Expr *Left, Expr *Right, const OperatorInfo &Op);
  Expr *actOnSimpleExpression(Expr *Left, Expr *Right, const OperatorInfo &Op);
  Expr *actOnTerm(Expr *Left, Expr *Right, const OperatorInfo &Op);
  Expr *actOnPrefixExpression(Expr *E, const OperatorInfo &Op);
  bool isOperatorForType(tok::TokenKind Op,
                             TypeDeclaration *Ty) ;
  FunctionCallStatement *actOnFunctionCallStatemnt(SMLoc Loc, Decl *D,
                     ExprList &Params);
  Expr *actOnFunctionCallExpr(SMLoc Loc, Decl *D,
                     ExprList &Params);
  void actOnIfStatement(StmtList &Stmts, SMLoc Loc,
                        Expr *Cond, StmtList &IfStmts,
                        StmtList &ElseStmts);
  void actOnWhileStatement(StmtList &Stmts, SMLoc Loc,
                        Expr *Cond, StmtList &WhileStmts);
  void actOnForStatement(StmtList &Stmts, SMLoc Loc,
                        Expr *Cond, StmtList &Start_Val,StmtList &ForStepStmts, StmtList &ForBodyStmts);
  ClassDeclaration *actOnClassDeclaration(SMLoc Loc, StringRef Name);
  void actOnClassBody(Decl* D,DeclList &Decls,StmtList &Start);
  Expr *actOnStringLiteral(SMLoc Loc, StringRef Literal);
};

class EnterDeclScope {
  Sema &Semantics;

public:
  EnterDeclScope(Sema &Semantics, Decl *D) : Semantics(Semantics) {
    Semantics.enterScope(D);
  }
  ~EnterDeclScope() { Semantics.leaveScope(); }
};