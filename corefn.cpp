#include <iostream>
#include "codegen.h"
#include "node.h"

using namespace std;

extern int yyparse();
extern NBlock* programBlock;


llvm::Function* createPrintfFunction(CodeGenContext& context)
{
    std::vector<llvm::Type*> printf_arg_types;
    printf_arg_types.push_back(llvm::Type::getInt8PtrTy(getGlobalContext())); //char*

    llvm::FunctionType* printf_type =
        llvm::FunctionType::get(
            llvm::Type::getInt32Ty(getGlobalContext()), printf_arg_types, true);

    llvm::Function *func = llvm::Function::Create(
                printf_type, llvm::Function::ExternalLinkage,
                llvm::Twine("printf"),
                context.module
           );
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}

llvm::Function* createPutcharFunction(CodeGenContext& context)
{
    std::vector<Type*> putchar_args;
    putchar_args.push_back(IntegerType::get(getGlobalContext(), 32));

    FunctionType* putchar_type = FunctionType::get(IntegerType::get(getGlobalContext(), 32), putchar_args, false);

    Function* func_putchar = Function::Create(putchar_type, GlobalValue::ExternalLinkage, "putchar", context.module); 
    func_putchar->setCallingConv(CallingConv::C);

    return func_putchar;
}

/*void createEchoFunction(CodeGenContext& context, llvm::Function* printfFn)
{
    std::vector<llvm::Type*> echo_arg_types;
    echo_arg_types.push_back(llvm::Type::getInt64Ty(getGlobalContext()));

    llvm::FunctionType* echo_type =
        llvm::FunctionType::get(
            llvm::Type::getVoidTy(getGlobalContext()), echo_arg_types, false);

    llvm::Function *func = llvm::Function::Create(
                echo_type, llvm::Function::InternalLinkage,
                llvm::Twine("echo"),
                context.module
           );
    llvm::BasicBlock *bblock = llvm::BasicBlock::Create(getGlobalContext(), "entry", func, 0);
	context.pushBlock(bblock, false);
    
    const char *constValue = "%d\n";
    llvm::Constant *format_const = llvm::ConstantDataArray::getString(getGlobalContext(), constValue);
    llvm::GlobalVariable *var =
        new llvm::GlobalVariable(
            *context.module, llvm::ArrayType::get(llvm::IntegerType::get(getGlobalContext(), 8), strlen(constValue)+1),
            true, llvm::GlobalValue::PrivateLinkage, format_const, ".str");
    llvm::Constant *zero =
        llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(getGlobalContext()));

    std::vector<llvm::Constant*> indices;
    indices.push_back(zero);
    indices.push_back(zero);
    llvm::Constant *var_ref =
        llvm::ConstantExpr::getGetElementPtr(var, indices);

    std::vector<Value*> args;
    args.push_back(var_ref);

    Function::arg_iterator argsValues = func->arg_begin();
    Value* toPrint = argsValues++;
    toPrint->setName("toPrint");
    args.push_back(toPrint);
    
	CallInst *call = CallInst::Create(printfFn, makeArrayRef(args), "", bblock);
	ReturnInst::Create(getGlobalContext(), bblock);
	context.popBlock();
}*/

void createCoreFunctions(CodeGenContext& context){
	createPrintfFunction(context);
    /*createEchoFunction(context, printfFn);*/
    createPutcharFunction(context);
}
