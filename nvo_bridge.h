#ifndef __OBF_NVO_BRIDGE_H__
#define __OBF_NVO_BRIDGE_H__
#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/Refactoring.h"
#include "clang/Lex/Lexer.h"
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <hash_map>
#include "utils.h" 

class MyBridgeVisitor : public RecursiveASTVisitor<MyBridgeVisitor> {
private:
    ASTContext *astContext; // used for getting additional AST info

public:
    explicit MyBridgeVisitor(CompilerInstance *); 
    virtual bool VisitCallExpr(CallExpr *);
};

class MyBridgeASTConsumer : public ASTConsumer {
private:
    MyBridgeVisitor *visitor; // doesn't have to be private

public:
    // override the constructor in order to pass CI
    explicit MyBridgeASTConsumer(CompilerInstance *CI)
        : visitor(new MyBridgeVisitor(CI)) // initialize the visitor
    { }
    // override this to call our ExampleVisitor on the entire source file
    virtual void HandleTranslationUnit(ASTContext &);

    // override this to call our ExampleVisitor on each top-level Decl
    //virtual bool HandleTopLevelDecl(DeclGroupRef);
};

class MyBridgeFrontendAction : public ASTFrontendAction {
public:
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(CompilerInstance &, StringRef);
};

#endif
