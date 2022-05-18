#pragma once
#include "AST/AST.hpp"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/ADT/DenseMap.h"

class CGCompileUnit{
llvm::Module *M;

CompileUnitDeclaration *Mod;

llvm::DenseMap<TypeDeclaration *, llvm::Type *> TypeCache;

public:
  llvm::Type *VoidTy;
  llvm::Type *Int1Ty;
  llvm::Type *Int32Ty;
  llvm::Type *Int64Ty;
  llvm::Constant *Int32Zero;

  // Repository of global objects.
  llvm::DenseMap<Decl *, llvm::GlobalObject *> Globals;
public:
  CGCompileUnit( llvm::Module *M);
  void initialize();

  llvm::LLVMContext &getLLVMCtx() {
    return M->getContext();
  }
  llvm::Module *getModule() { return M; }
  CompileUnitDeclaration *getModuleDeclaration() { return Mod; }

  llvm::Type *convertType(TypeDeclaration *Ty);
  std::string mangleName(Decl *D);

  llvm::GlobalObject *getGlobal(Decl *);

  void run(CompileUnitDeclaration *Mod);
};