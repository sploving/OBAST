CLANG_LEVEL := ../..

TOOLNAME = obot  #the name of your tool's executable

SOURCES := obfuscator/funcobf.cpp obfuscator/cfgobf.cpp obfuscator/utils.h \
	   obfuscator/varobf.cpp \
           case/nvo_sha1.cpp case/utils.h \
           main.cpp  #the Clang source files you want to compile

include $(CLANG_LEVEL)/../../Makefile.config

LINK_COMPONENTS := $(TARGETS_TO_BUILD) asmparser bitreader support mc option
 
USEDLIBS = clangFrontend.a clangSerialization.a clangDriver.a \
           clangTooling.a clangParse.a clangSema.a \
           clangAnalysis.a clangRewriteFrontend.a clangRewrite.a \
	   clangEdit.a clangAST.a clangLex.a clangBasic.a \
           clangASTMatchers.a clangApplyReplacements.a clangToolingCore.a 


include $(CLANG_LEVEL)/Makefile

