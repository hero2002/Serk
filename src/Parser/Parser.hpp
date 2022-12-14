#pragma once
#include "Diag/Diagnostic.hpp"
#include "Lexer/Lexer.hpp"
#include "Sema/Sema.hpp"
#include "AST/AST.hpp"
#include <set>
inline StringMap<ModuleDeclaration *> imported;
class Parser {
  Lexer &Lex;

  Sema &Actions;

  Token Tok;
  Token Prev_Tok;
  DiagnosticsEngine &getDiagnostics() const { return Lex.getDiagnostics(); }

  void advance() { 
    Prev_Tok = Tok;
    Lex.next(Tok); 
  }

  bool expect(tok::TokenKind ExpectedTok) {
    if (Tok.is(ExpectedTok)) {
      return false;
    }
    // There must be a better way!
    const char *Expected = tok::getPunctuatorSpelling(ExpectedTok);
    if (!Expected)
      Expected = tok::getKeywordSpelling(ExpectedTok);
    llvm::StringRef Actual(Tok.getLocation().getPointer(), Tok.getLength());
    getDiagnostics().report(Prev_Tok.getLocation(), diag::err_expected, Expected,
                            Actual);
    return true;
  }

  bool consume(tok::TokenKind ExpectedTok) {
    if (Tok.is(ExpectedTok)) {
      advance();
      return false;
    }
    return true;
  }

public:
  Parser(Lexer &Lex, Sema &Actions);
  ModuleDeclaration  *module = nullptr;
  ModuleDeclaration  *parse(StringRef Name);
  bool ParseFuction(DeclList &ParentDecls);
  bool ParseExternFunction(DeclList &ParentDecls);
  bool parseParameters(DeclList &ParentDecls, ParamList &Params);
  bool parseParameter(DeclList &ParentDecls, ParamList& Params);
  bool parseBlock(DeclList& Decls,
      StmtList& Stmts);
  bool parseVarDecleration(DeclList& Decls,
      StmtList& Stmts);
  bool parseStatement(DeclList& Decls,
      StmtList& Stmts);
  bool parseStatementSequence(DeclList& Decls,
      StmtList& Stmts);
  bool parseReturnStatement(DeclList& Decls,
      StmtList& Stmts);
  bool parseFunctionCallStatment(StmtList& Stmts);

  bool parseTemepleteList(DeclList & Decls,TypeDeclaration *&type_D,std::vector<std::variant<TypeDeclaration *, Expr *>> &Args);
  bool parseExpList(ExprList &Exprs);
  bool parseExpression(Expr* &E);
  bool parseSimpleExpression(Expr*& E);
  bool parseRelation(OperatorInfo &Op);
  bool parseAddOperator(OperatorInfo &Op);
  bool parseTerm(Expr *&E);
  bool parseMulOperator(OperatorInfo &Op);
  bool parseFactor(Expr *&E);
  bool parseIfStatement(DeclList& Decls,
      StmtList& Stmts);
  bool parseWhileStatement(DeclList& Decls,
      StmtList& Stmts);
  bool parseForStatement(DeclList& Decls,
      StmtList& Stmts);    
  bool ParseClass(DeclList &ParentDecls);
  bool ParseMethodCallStatment(StmtList& Stmts,Expr *E);
  bool ParseEnum(DeclList &ParentDecls,
      StmtList& Stmts);
  bool ParseUsing(DeclList &ParentDecls);
  bool parseSelectors(Expr *&E);
  bool ParseTempleteArgs(DeclList &ParentDecls,std::vector<std::tuple<int, StringRef,TypeDeclaration *,SMLoc>> &Decls);
  bool SkipUntil(ArrayRef<tok::TokenKind> Toks,bool eat = false);
  bool ParseType(DeclList &ParentDecls,TypeDeclaration *&Ty);
  bool ParseImport();
  bool ParseConstructorOrDecostructor(DeclList &ParentDecls,Decl *Class);
};