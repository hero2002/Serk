#pragma once
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "llvm/IR/LegacyPassManager.h"
#include "KaleidoscopeJIT.h"
#include "AST/AST.hpp"
class CodeGenerator {
	llvm::LLVMContext& Ctx;
	llvm::TargetMachine* TM;
	ModuleDeclaration * CM;
protected:
	CodeGenerator(llvm::LLVMContext& Ctx, llvm::TargetMachine* TM)
		: Ctx(Ctx),CM(nullptr),TM(TM) {}

public:
	static CodeGenerator* create(llvm::LLVMContext& Ctx, llvm::TargetMachine* TM);

	std::unique_ptr<llvm::Module> run(ModuleDeclaration * CM, std::string FileName,SourceMgr& mgr,bool Debug);
};