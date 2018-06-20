/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* stmts.cc: AST subclasses related to statements and modules. */

/* Authors:  Nikhil Athreya, Nihar Dalal, Vyom Kavishwar, Srinivasa Pranav */

#include <iostream>
#include "apyc.h"
#include "ast.h"

using namespace std;

/*****   MODULE    *****/

/** A module, representing a complete source file. */
class Module_AST : public AST_Tree {
public:

    Location location () const override {
        return 0;
    }

    /** Top-level semantic processing for the program. */
    AST_Ptr doOuterSemantics () override {
        mainModule = makeModuleDecl (makeId ("__main__", 0));
        outerEnviron = mainModule->getEnviron ();
        for (auto& c : *this) {
            c = c->doOuterSemantics ();
        }
        return this;
    }

    void gatherFunctions(Decl* curr, Decl_Set& func_decls) {
        if(curr == mainModule || curr->isOverloadable() || curr->isType()) {
            for(auto& d : curr->getEnviron()->get_members()) {
                if(d->isOverloadable()) func_decls.insert(d);
                gatherFunctions(d, func_decls);
            }
        }
    }

    void gatherGlobalFunctions(Decl* curr, Decl_Set& func_decls) {
        if(curr->isOverloadable()) func_decls.insert(curr);
        else if(curr == mainModule || curr->isType()) {
            for(auto& d : curr->getEnviron()->get_members())
                gatherGlobalFunctions(d, func_decls);
        }
    }

    /* This function starts code generation for our entire module.
       This function does a couple of things:

           1. First we collect all ASTs that need to put outside of our main function. In
           our case, we placed functions and classes outside of our main function.

           2. For classes defined in the prelude, since we defined special hooks for these
           in runtime.{cc,h}, we disabled code generation for these classes. For user-defined
           classes that weren't in the prelude, we first forward declare all these classes so
           we can reference these classes as pointers in any order we wish later in our code.

           3. We also forward declare functions as well, so functions can be used and called
           in any order later in our code. (How we declare each function and the specific types
           chosen for parameters are explained later in our Def_AST codeGen function). We only
           forward declare functions in global and class scopes. Functions nested within other
           functions and methods are handled differently (see our Def_AST's codeGen documentation
           for more details).

           4. Additionally, for each function (nested or not), since we need to support general
           closures, we need to be able to back up each stack frame onto the heap. As a result,
           for each function, we create a different stack frame struct containing declarations
           of each local variable inside of our function. The types of each declaration are
           whatever types we deduced for each variable in phase 2 during our semantic
           analysis. We initialize all of these variables to null pointers initially. As our
           functions get called, we will fill in our respective stack frames with usable data.
           Since global variables are shared across functions are not based on stack frames,
           we leave our python global variables as C++ global variables. Additionally, inside
           each stack frame struct, if a function is nested inside another function, it contains
           a pointer to the stack frame of the enclosing function, so we have static links to
           whichever function we are lexically nested under. We'll need these in order to access
           local variables that are scoped under parent functions if we are inside a nested function
           (see the Id_AST's codeGen documentation for more details).

           5. Finally, we codeGen for classes and global functions outside of our main function,
           and for everything else (expressions, if statements, etc.) we generate the code
           inside of our main function. We additionally store our program argc and argv in global
           variables that we can reference later since we'll them for our argv() function. (See
           Def_AST's codeGen for more details about how code for the main function is generated).
    */
    void codeGen(Code_Context& context) {
        context << "#include \"runtime.h\"" << endl << endl;
        context << "using namespace std;" << endl << endl;

        AST_Vect outside_main, inside_main;
        for(auto& c : *this) {
            if(c->typeIndex() == DEF_AST || c->typeIndex() == CLASS_AST) outside_main.push_back(c);
            else inside_main.push_back(c);
        }

        Decl_Set func_decls, global_func_decls;
        gatherFunctions(mainModule, func_decls);
        gatherGlobalFunctions(mainModule, global_func_decls);

        for(auto& c : outside_main) { 
            if(c->typeIndex() == CLASS_AST) {
                auto classId = *c->begin();
                if(classId->text() != "int" && classId->text() != "str" && classId->text() != "bool" &&
                    classId->text() != "list" && classId->text() != "range" && classId->text() != "tuple0" &&
                    classId->text() != "tuple1" && classId->text() != "tuple2" && classId->text() != "tuple3" &&
                    classId->text() != "dict")
                    context << "struct " << classId->text() << "_"
                        << std::to_string(classId->getDecl()->getIndex()) << ";" << endl;
            }
        }
        context << endl;

        for(auto& d : global_func_decls) {
            assert(d->isOverloadable());
            context << "Object ";
            std::string func_name = d->getName() + "_" + std::to_string(d->getIndex());
            context << func_name << " (";
            unsigned long num = d->getType()->numParams();
            for(unsigned long l = 0; l < num; l++) {
                context << "Object";
                if(l != num - 1) context << ", ";
            }
            context << ");" << endl;
        }
        context << endl;

        std::unordered_set<int> decls_hit;
        for(auto& d : mainModule->getEnviron()->get_members()) {
            if(decls_hit.find(d->getIndex()) == decls_hit.end() && d->assignable()) {
                decls_hit.insert(d->getIndex());
                std::string declName = d->getName() + "_" + std::to_string(d->getIndex());
                d->getType()->codeGen(context);
                context << " " << declName << " = nullptr;" << endl;
            }
        }

        context << endl;

        for(auto& d : func_decls) {
            context << "struct " << d->getName() << "_" << std::to_string(d->getIndex())
                << "_stack_frame;" << endl;
        }

        context << endl;

        for(auto& d : func_decls) {
            assert(d->isOverloadable());
            context << "struct " << d->getName() << "_" << std::to_string(d->getIndex())
                << "_stack_frame {" << endl << endl;
            context.indent();
            if(d->getContainer() != mainModule && !d->getContainer()->isType()) {
                context << "struct " << d->getContainer()->getName() << "_"
                    << std::to_string(d->getContainer()->getIndex())
                    << "_stack_frame* _parent;" << endl << endl;
            }
            std::unordered_set<int> decls_hit;
            for(auto& mem : d->getEnviron()->get_members()) {
                if(decls_hit.find(mem->getIndex()) == decls_hit.end() && (mem->assignable()
                    || mem->isOverloadable())) {
                    decls_hit.insert(mem->getIndex());
                    std::string declName = mem->getName() + "_" + std::to_string(mem->getIndex());
                    mem->getType()->codeGen(context);
                    context << " " << declName << " = nullptr;" << endl;
                }
            }
            context.indent(-1);
            context << "};" << endl << endl;
        }

        context.setContext(mainModule);
        for(auto& c : outside_main) c->codeGen(context);

        context << "int main(int argc, char* argv[]) {" << endl;
        context.indent();
        context << "prog_argv = argv, prog_argc = argc;" << endl << endl;
        std::vector<unsigned long> scratch_sizes = {0, 0, 0};
        for(auto& c : inside_main) c->calculateScratchSizes(scratch_sizes);
        context << "std::vector<Object> tuple_assign_scratch("
            << std::to_string(scratch_sizes[0]) << ");" << endl;
        context << "std::vector<LeftCompareData*> left_compare_scratch;" << endl;
        context << "for (unsigned long l = 0; l < " << std::to_string(scratch_sizes[1])
            << "; l++) left_compare_scratch.push_back(new LeftCompareData());" << endl;
        context << "std::vector<Object> and_or_scratch("
            << std::to_string(scratch_sizes[2]) << ");" << endl;
        context.setContext(mainModule);
        context.setTupleAssignScratchPos(0);
        context.setLeftCompareScratchPos(0);
        context.setAndOrScratchPos(0);
        for(auto& c : inside_main) c->codeGen(context), context << ";" << endl;
        assert(scratch_sizes[0] >= context.getTupleAssignScratchPos());
        assert(scratch_sizes[1] >= context.getLeftCompareScratchPos());
        assert(scratch_sizes[2] >= context.getAndOrScratchPos());
        context << endl << "return 0;" << endl;
        context.indent(-1);
        context << "}" << endl;
    }
     
    FACTORY (Module_AST);

};

EXEMPLAR (Module_AST, MODULE_AST);


/*****   PRINTLN   *****/

/** A print statement without trailing comma. */
class PrintCommon : public AST_Tree {
public:

    void codeGen(Code_Context& context) override {
        if(begin() == end()) {
            if(typeIndex() == PRINT_AST) context << "print(true, \" \");" << endl;
            else context << "print(true, \"\\n\");" << endl;
            return;
        }
        for(auto iter = begin(); iter != end(); iter++) {
            context << "print(false, __toStr__(";
            (*iter)->codeGen(context);
            context << ")->_underlying);" << endl;
        }
        if(typeIndex() != PRINT_AST) context << "print(true, \"\\n\");" << endl;
    }
};

class Print_AST : public PrintCommon {
public:

    FACTORY(Print_AST);
};

EXEMPLAR(Print_AST, PRINT_AST);

class Println_AST : public PrintCommon {
public:

    FACTORY (Println_AST);
};

EXEMPLAR (Println_AST, PRINTLN_AST);


/***** STMT_LIST *****/

/** A list of statements. */
class StmtList_AST : public AST_Tree {
protected:

    FACTORY (StmtList_AST);

    AST_Ptr doOuterSemantics () override {
        for (auto& c : *this) {
            c = c->doOuterSemantics ();
        }
        return this;
    }

    void codeGen(Code_Context& context) override {
        for(auto& c : *this) {
            c->codeGen(context);
            context << ";" << std::endl;
        }
    }
};

EXEMPLAR (StmtList_AST, STMT_LIST_AST);

/***** DEF *****/

/** def ID(...): ... */
class Def_AST : public AST_Tree {
protected:

    Decl* getDecl () override {
        return child (0)->getDecl ();
    }

    AST_Ptr getId () override {
        return child (0);
    }

    void freezeDecls (bool frozen) override {
        Decl* me = getDecl ();
        if (me != nullptr)
            me->setFrozen (frozen);
        for (auto c : trimmedAST (*this, 3))
            c->freezeDecls (frozen);
    }

    void collectDecls (Decl* enclosing) override {
        AST_Ptr id = child (0);
        AST_Ptr params = child (1);
        AST_Ptr returnType = child (2);
        Decl* me = enclosing->addDefDecl(child(0), params->arity ());
        id->addDecl (me);
        params->collectDecls (me);
        params->collectTypeVarDecls (me);
        returnType->collectTypeVarDecls (me);
        for (auto c : trimmedAST (*this, 3)) {
            c->collectDecls (me);
        }
    }

    AST_Ptr resolveSimpleIds (const Environ* env) override {
        for (auto& c : *this) {
            c = c->resolveSimpleIds (getDecl ()->getEnviron ());
        }
        return this;
    }

    void resolveTypes (Decl* context, Unifier& subst) override {
        Decl* me = getDecl ();
        Type_Ptr funcType = me->getType ();
        Type_Ptr returnType = child (2)->asType ();
        AST_Ptr formals = child (1);
        getId ()->resolveTypes (me, subst);
        formals->resolveTypes (me, subst);
        if (!unify (funcType->returnType (), returnType, subst))
            error (this, "inconsistent return type");
        for (int i = 0; i < formals->arity (); i += 1) {
            if (!unify (formals->child (i)->getType (),
                        funcType->paramType (i), subst)) {
                error (this, "inconsistent parameter type");
            }
        }
        for (auto c : trimmedAST(*this, 3)) {
            c->resolveTypes (me, subst);
        }
        assert (subst[me->getType ()]->numParams () == formals->arity ());
    }

    void freeTypeVarCheck (const Type_Set& allowed) override {
    }

    /* This codeGen function handles code generation for functions, nested or otherwise.
       This function does a couple of things:

           1. If a function is a global function or a method in python, it becomes a global
           function in our generated C++ code. Otherwise, if a function is nested inside another
           function or a method, it becomes a lambda (since C++11 has support for lambdas with
           capture lists, we use this to our advantage).

           2. Regardless of the types of the parameters we deduced from phase 2, we always leave our
           parameters as Objects. The reason is because we may need to support functions like this:

               def f(x): return x

               print f(2)
               print f('2')

           Each call to f in this case has a different type for the parameter, so in order to support
           generic functions, we leave all of our parameters as generic objects (since every single
           class, user-defined or the ones defined in our prelude inherit from our Object_Obj class),
           and we special case inside of our function if our types are specific. We leave the return
           type generic as well for the same reason.

           3. For nested functions, we define them as lambdas. these lambdas are wrapped inside
           Function_Obj's (which also inherit from Object_Obj's), but they can be used as functions as
           well (its implementation is in runtime.h). The parameter and return types are also generic
           just like regular functions. These lambdas are treated as local variables of the functions
           under which they are nested, since we found this simplifies our implementation since we do
           not have to differentiate between local variables and nested functions.

           4. Before we generate any actual code for our function, we first initialize a new struct
           that corresponds to our stack frame (generated in our Module_AST's codeGen, see it's
           documentation for more details), on the heap, since we need to support general closures.
           Additionally, since python is pass by value, we copy the parameters passed into our function
           into their corresponding variables inside of our stack frame struct. Since every object in
           our code will inherit from our Object_Obj class, we defined a virtual method called copy()
           that every single object will override. (We use the object_copy() function now for integer
           optimization purposes, which just special-cases our object copy when we detect we are trying
           to copy an invalid pointer, which will either be an integer or a boolean). Additionally,
           if a function is nested inside another function (which will be a lambda), we capture the
           enclosing stack frame so we can reference variables in parent functions even after they return.
           (see Id_AST's codeGen for more details). We then set the parent of our current stack frame
           to the parent lexically enclosing function inside of our lambda (this emulates static links).

           5. At this point, we can generate code for our function. There are two different cases we need to
           handle here:
               
               a. If our function just has a native AST, this will mean the corresponding function will be
               defined in our C++ code. So our codeGen will just call that function and return whatever value
               it returns.

               b. Otherwise, we generate the code for each statement inside of our function.

           6. We have a couple of vectors used for keeping track of left compares, chained assignments, and
           short-circuiting. We first determine the size of these vectors (their size will be fixed and pre-
           determined at codeGen time), initialize them appropriately, and then generate the main body of our
           function.

           7. Methods are handled very similarly, since our first parameter is the object instance we are
           referencing, so that will also become a local variable. The only special case we have to deal with
           are __init__ method's where we explicitly return the new object we construct at the end of the
           method. The only difference is that a user-defined class's first parameter is initialized with the
           init() for __init__ method's appropriately before the rest of the __init__ method's code is generated
           (see Class_AST's codeGen for more details).
    */
    void codeGen(Code_Context& context) override {
        AST_Ptr id = *begin();
        AST_Ptr formals = *(begin() + 1);
        AST_Ptr ret_type = *(begin() + 2);
        std::string funcName = id->text() + "_" + std::to_string(id->getDecl()->getIndex());

        if(context.getContext() == mainModule || context.getContext()->isType()) {
            if(context.getContext()->isType() && id->text() == "__init__" && typeIndex() == METHOD_AST)
                context << "Object";
            else
                context << "Object"; //ret_type->codeGen(context);
            context << " " << funcName << "(";
        }
        else {
            assert(context.getContext()->isOverloadable());
            std::string contextName = context.getContext()->getName() + "_"
                + std::to_string(context.getContext()->getIndex());
            context << contextName << "_frame->" << funcName << " = new Function_Obj<";
            //ret_type->codeGen(context);
            context << "Object";
            if(formals->begin() != formals->end()) context << ", ";
            for(auto iter = formals->begin(); iter != formals->end(); iter++) {
                auto param = *iter;
                //(*(param->begin() + 1))->codeGen(context);
                context << "Object";
                if(iter != formals->end() - 1) context << ", ";
            }
            context << ">(\"" << funcName << "\", [" << contextName << "_frame] (";
        }

        std::unordered_set<int> decls_hit;
        decls_hit.insert(id->getDecl()->getIndex());
        for(auto iter = formals->begin(); iter != formals->end(); iter++) {
            auto param = *iter;
            //(*(param->begin() + 1))->codeGen(context);
            context << "Object";
            context << " ";
            context << (*param->begin())->getDecl()->getName() << "_"
                << std::to_string((*param->begin())->getDecl()->getIndex());
            decls_hit.insert((*param->begin())->getDecl()->getIndex());
            if(iter != formals->end() - 1) context << ", ";
        }

        if(context.getContext() == mainModule || context.getContext()->isType()) {
            context << ") {" << endl << endl;
        }
        else {
            context << ") -> ";
            ret_type->codeGen(context);
            context << " {" << endl << endl;
        }
        context.indent();

        context << "struct " << funcName << "_stack_frame* " << funcName <<  "_frame = new "
            << funcName << "_stack_frame();" << endl;

        std::vector<unsigned long> scratch_sizes = {0, 0, 0};
        if(begin() + 3 >= end() || (*(begin() + 3))->typeIndex() != NATIVE_AST) {
            for(auto iter = begin() + 3; iter != end(); iter++)
                (*iter)->calculateScratchSizes(scratch_sizes);
        }
        context << "std::vector<Object> tuple_assign_scratch("
            << std::to_string(scratch_sizes[0]) << ");" << endl;
        context << "std::vector<LeftCompareData*> left_compare_scratch;" << endl;
        context << "for (unsigned long l = 0; l < " << std::to_string(scratch_sizes[1])
            << "; l++) left_compare_scratch.push_back(new LeftCompareData());" << endl;
        context << "std::vector<Object> and_or_scratch("
            << std::to_string(scratch_sizes[2]) << ");" << endl;

        for(auto iter = formals->begin(); iter != formals->end(); iter++) {
            auto param = *iter;
            auto paramId = *param->begin();
            std::string paramName = paramId->getDecl()->getName() + "_"
                + std::to_string(paramId->getDecl()->getIndex());
            context << funcName << "_frame->" << paramName << " = ";
            context << paramName << " == nullptr ? nullptr : wrapped_dynamic_cast<";
            paramId->getType()->codeGen(context);
            context << ">(object_copy(" << paramName << "));" << endl;
        }
        if(context.getContext() != mainModule && !context.getContext()->isType()) {
            std::string contextName = context.getContext()->getName() + "_"
                + std::to_string(context.getContext()->getIndex());
            context << funcName << "_frame->_parent = " << contextName << "_frame;" << endl;
        }
        if(context.getContext()->isType() && typeIndex() == METHOD_AST && id->text() == "__init__") {
            auto selfParam = *formals->begin();
            auto selfId = *selfParam->begin();
            std::string selfName = selfId->getDecl()->getName() + "_"
                + std::to_string(selfId->getDecl()->getIndex());
            context << funcName << "_frame->" << selfName << "->init();" << endl;
        }

        Decl* old = context.getContext();
        unsigned long oandor = context.getAndOrScratchPos(), olc = context.getLeftCompareScratchPos(),
            otupa = context.getTupleAssignScratchPos();
        context.setTupleAssignScratchPos(0);
        context.setLeftCompareScratchPos(0);
        context.setAndOrScratchPos(0);
        context.setContext(getDecl());
        if(begin() + 3 != end() && (*(begin() + 3))->typeIndex() == NATIVE_AST) {
            auto native = *(begin() + 3);
            std::string rawFuncName = (*native->begin())->denotedText();
            context << "return wrapped_dynamic_cast<";
            ret_type->codeGen(context);
            context << ">(" << rawFuncName << " (";
            context.indent();
            for(auto iter = formals->begin(); iter != formals->end(); iter++) {
                auto param = *iter;
                auto paramId = *param->begin();
                std::string paramName = paramId->getDecl()->getName() + "_"
                    + std::to_string(paramId->getDecl()->getIndex());
                context << funcName << "_frame->" << paramName;
                if(iter != formals->end() - 1) context << ", " << endl;
                else context << endl;
            }
            context.indent(-1);
            context << "));" << endl;
        }
        else {
            for(auto iter = begin() + 3; iter != end(); iter++)
                (*iter)->codeGen(context), context << ";" << endl;
            assert(scratch_sizes[0] >= context.getTupleAssignScratchPos()); 
            assert(scratch_sizes[1] >= context.getLeftCompareScratchPos());
            assert(scratch_sizes[2] >= context.getAndOrScratchPos());
        }
        context.setContext(old);
        context.setTupleAssignScratchPos(otupa);
        context.setLeftCompareScratchPos(olc);
        context.setAndOrScratchPos(oandor);

        if(context.getContext()->isType() && id->text() == "__init__" && typeIndex() == METHOD_AST) {
            auto selfParam = *formals->begin();
            auto paramId = *selfParam->begin();
            std::string paramName = paramId->getDecl()->getName() + "_"
                + std::to_string(paramId->getDecl()->getIndex());
            context << "return " << funcName << "_frame->" << paramName << ";" << endl;
        }
        else
            context << "; return nullptr;" << endl;
        context.indent(-1);
        if(context.getContext() != mainModule && !context.getContext()->isType())
            context << "});" << endl;
        else
            context << "}" << endl << endl;
    }

    FACTORY (Def_AST);
};


EXEMPLAR (Def_AST, DEF_AST);

/***** METHOD *****/

/**  def ID(...): ... (in class)     */
class Method_AST : public Def_AST {
protected:

    FACTORY (Method_AST);

    void collectDecls (Decl* enclosing) override {
        AST_Ptr params = child (1);
        if (params->arity () == 0) {
            error (this, "method must have at least one parameter");
            setChild (1, NODE (FORMALS_LIST_AST,
                               makeId("__self__", location ()),
                               params->children ()));
        }
        Def_AST::collectDecls (enclosing);
    }

    void resolveClassStmtTypes (Decl* context, Unifier& subst,
                                bool doMethods) override {
        if (doMethods)
            resolveTypes (context, subst);
    }
};

EXEMPLAR (Method_AST, METHOD_AST);


/***** FORMALS_LIST *****/

/** ... (E1, ...)  */
class FormalsList_AST : public AST_Tree {
protected:

    FACTORY (FormalsList_AST);

    void collectDecls (Decl* enclosing) override {
        int k;
        k = 0;
        for (auto c : *this) {
            AST_Ptr id = c->getId ();
            c->addDecl (enclosing->addParamDecl(id, k));
            k += 1;
        };

        for (auto c : *this) {
            c->collectTypeVarDecls (enclosing);
        };
    }

};

EXEMPLAR (FormalsList_AST, FORMALS_LIST_AST);

static unsigned int classIdCounter = 12;

/***** CLASS *****/

/** class ID of [...]: ...  */
class Class_AST : public AST_Tree {
protected:

    FACTORY (Class_AST);

    Decl* getDecl () override {
        return child (0)->getDecl ();
    }

    void collectDecls (Decl* enclosing) override {
        AST_Ptr id = child (0);
        string name = id->text ();
        AST_Ptr params = child (1);
        const Environ* env = enclosing->getEnviron ();

        Decl* me = makeClassDecl (id, params);

        if (env->findImmediate (name) != nullptr) {
            error (id, "attempt to redefine %s", name.c_str ());
        } else {
            enclosing->addMember (me);
        }

        setBuiltinDecl (me);

        id->addDecl (me);
        params->collectDecls (me);

        for (auto c : trimmedAST (*this, 2)) {
            c->collectDecls (me);
        }
    }

    AST_Ptr resolveSimpleIds (const Environ* env) override {
        for (auto& c : trimmedAST (*this, 2)) {
            c = c->resolveSimpleIds (getDecl ()->getEnviron ());
        }
        return this;
    }

    void resolveTypes (Decl* context, Unifier& subst) override {
        int errs0 = numErrors ();
        for (auto c : trimmedAST (*this, 2)) {
            c->resolveClassStmtTypes (getDecl (), subst, false);
        }
        if (errs0 == numErrors ())
            replaceBindings (subst);
        for (auto c : trimmedAST (*this, 2)) {
            c->resolveClassStmtTypes (getDecl (), subst, true);
        }
    }

    void freeTypeVarCheck (const Type_Set& allowed) override {
        Type_Set typeParams;
        for (auto c : *child (1)) {
            typeParams.insert (c->asType ());
        }
        for (auto c : trimmedAST (*this, 2)) {
            c->freeTypeVarCheck (typeParams);
        }
    }

    /* This function handles code generation for classes.
       This function does a couple of things:

           1. First, we disable code generation for builtin classes defined in our prelude (since we handle
           their implementation in our runtime.{cc,h} files. Each user-defined class we generate will inherit
           from our Object_Obj class. As a result, we dynamically generate code that handles overrides the
           corresponding virtual methods inside of our Object_Obj class. Equality is based on pointers (since
           different instances of classes are considered unequal), additionally, each class has a unique id,
           since for the 'is' and 'is not' operators, we need to determine whether two object are actually the
           same, so we need to make sure they are actually originate from the same instance. We additionally
           declare all of our instance variables inside of our struct and initialize them to nullptr's.

           2. Our toString() method generates a string with the name of a class and the address it is stored
           at (similar to python), and our print() method (which will be called if we ever print an instance
           of our object), just prints the string generated in our toString() method.

           3. Since our class can initialize instance variables and have arbitrary statements, we generate all
           of the code necessary for this inside of our init() method. We call this init method inside of our
           __init__ function since we need values for our instance variables appropriately initialized before
           we start our class's constructor (see the Def_AST's codeGen for more documentation).

           4. As stated in the Def_AST's documentation, methods are handled very similarly to functions so this
           codeGen does not deal with generating code for methods.
    */
    void codeGen(Code_Context& context) override {
        auto classId = *begin();
        Decl* classDecl = classId->getDecl(), * old = context.getContext();
        context.setContext(getDecl());
        unsigned long oandor = context.getAndOrScratchPos(), olc = context.getLeftCompareScratchPos(),
            otupa = context.getTupleAssignScratchPos();
        context.setTupleAssignScratchPos(0);
        context.setLeftCompareScratchPos(0);
        context.setAndOrScratchPos(0);
        if(classId->text() == "int" || classId->text() == "str" || classId->text() == "bool"
            || classId->text() == "list" || classId->text() == "dict" || classId->text() == "range"
            || classId->text() == "tuple0" || classId->text() == "tuple1" || classId->text() == "tuple2"
            || classId->text() == "tuple3") return;

        AST_Set methods, other;
        for(auto iter = begin() + 2; iter != end(); iter++) {
            if((*iter)->typeIndex() == DEF_AST || (*iter)->typeIndex() == METHOD_AST)
                methods.insert(*iter);
            else other.insert(*iter);
        }

        std::unordered_set<int> decls_hit;
        Decl_Vect instanceDecls;
        AST_Vect non_functions;
        std::string className = classId->text() + "_" + std::to_string(classId->getDecl()->getIndex());
        context << "struct " << className << " : public Object_Obj {" << endl;
        context.indent();

        for(Decl* mem : classDecl->getEnviron()->get_members()) {
            if(decls_hit.find(mem->getIndex()) == decls_hit.end() && mem->assignable()) {
                decls_hit.insert(mem->getIndex());
                instanceDecls.push_back(mem);
            }
        }

        for(auto& d : instanceDecls) { 
            std::string declName = d->getName() + "_" + std::to_string(d->getIndex());
            auto declType = d->getType();
            declType->codeGen(context);
            context << " " << declName << " = nullptr;" << endl;
        }
        context << endl;

        context << "unsigned long id() const override { return " << std::to_string(classIdCounter++)
            << "; }" << endl << endl;

        context << "bool eq(const Object_Obj* o) const override {" << endl;
        context.indent();
        context << "if (o == nullptr || o->id() != id()) return false;" << endl;
        context << "return o == this;" << endl;
        context.indent(-1);
        context << "}" << endl << endl;

        context << "bool neq(const Object_Obj* o) const override {" << endl;
        context.indent();
        context << "return !eq(o);" << endl;
        context.indent(-1);
        context << "}" << endl << endl;

        context << "Object_Obj* copy() const override { return const_cast<" << className
            << "*>(this); }" << endl << endl;

        context << "std::string toString() const override {" << endl;
        context.indent();
        context << "return \"<" << className << "\" + "
            << "std::to_string((unsigned long) this) + \">\";" << endl;
        context.indent(-1);
        context << "}" << endl << endl;

        context << "std::ostream& print(std::ostream& os) const override {" << endl;
        context.indent(); 
        context << "os << toString();" << endl;
        context << "return os;" << endl;
        context.indent(-1);
        context << "}" << endl;

        context << "void init() override {" << endl;
        context.indent();
        unsigned long oandor2 = context.getAndOrScratchPos(), olc2 = context.getLeftCompareScratchPos(),
            otupa2 = context.getTupleAssignScratchPos();
        context.setTupleAssignScratchPos(0);
        context.setLeftCompareScratchPos(0);
        context.setAndOrScratchPos(0);
        std::vector<unsigned long> scratch_sizes = {0, 0, 0};
        for(auto& o : other) o->calculateScratchSizes(scratch_sizes);
        context << "std::vector<Object> tuple_assign_scratch("
            << std::to_string(scratch_sizes[0]) << ");" << endl;
        context << "std::vector<LeftCompareData*> left_compare_scratch;" << endl;
        context << "for (unsigned long l = 0; l < " << std::to_string(scratch_sizes[1])
            << "; l++) left_compare_scratch.push_back(new LeftCompareData());" << endl;
        context << "std::vector<Object> and_or_scratch("
            << std::to_string(scratch_sizes[2]) << ");" << endl;
        for(auto& o : other) o->codeGen(context), context << ";" << endl;
        assert(scratch_sizes[0] >= context.getTupleAssignScratchPos()); 
        assert(scratch_sizes[1] >= context.getLeftCompareScratchPos());
        assert(scratch_sizes[2] >= context.getAndOrScratchPos());
        context.setTupleAssignScratchPos(otupa2);
        context.setLeftCompareScratchPos(olc2);
        context.setAndOrScratchPos(oandor2);
        context.indent(-1);
        context << "}" << endl;

        context.indent(-1);
        context << "};" << endl << endl;

        for(auto& m : methods) m->codeGen(context);
        context.setContext(old);
        context.setTupleAssignScratchPos(otupa);
        context.setLeftCompareScratchPos(olc);
        context.setAndOrScratchPos(oandor);
    }

};

EXEMPLAR (Class_AST, CLASS_AST);

/***** TYPE_FORMALS_LIST *****/

/** of [$T, ...]      */
class TypeFormalsList_AST : public AST_Tree {
protected:

    FACTORY (TypeFormalsList_AST);

    void collectDecls (Decl* enclosing) override {
        const Environ* env = enclosing->getEnviron ();
        for (auto c : *this) {
            string name = c->text ();
            if (env->findImmediate (name) != nullptr) {
                error (c, "duplicate type parameter: %s",
                       name.c_str ());
            } else {
                c->addDecl (enclosing->addTypeVarDecl (c));
            }
        }                                                                        
    }

};

EXEMPLAR (TypeFormalsList_AST, TYPE_FORMALS_LIST_AST);


/***** TYPED_ID *****/

/** ID::TYPE */
class TypedId_AST : public AST_Tree {
protected:

    FACTORY (TypedId_AST);

    AST_Ptr getId () override {
        return child (0);
    }

    Decl* getDecl () override {
        return getId ()->getDecl ();
    }

    const Decl_Vect& getDecls () override {
        return getId ()->getDecls ();
    }

    Type_Ptr getType () override {
        return child (1)->asType ();
    }

    void addTargetDecls (Decl* enclosing) override {
        getId ()->addTargetDecls (enclosing);
    }
    
    void collectTypeVarDecls (Decl* enclosing) override {
        child (1)->collectTypeVarDecls (enclosing);
    }

    void addDecl (Decl* decl) override {
        getId ()->addDecl (decl);
    }

    
    void resolveTypes (Decl* context, Unifier& subst) override {
        getId ()->resolveTypes (context, subst);
        if (!getId ()->setType (child (1)->asType (), subst))
            error (this, "incompatible type assignment");
    }

    void codeGen(Code_Context& context) override {
        (*begin())->codeGen(context);
    }
};

EXEMPLAR (TypedId_AST, TYPED_ID_AST);

/***** ASSIGN *****/

/** TARGET(s) = EXPR */
class Assign_AST : public Typed_Tree {
protected:

    FACTORY (Assign_AST);

    void collectDecls (Decl* enclosing) override {
        child(1)->collectDecls (enclosing);
        child(0)->addTargetDecls (enclosing);
    }

    void resolveTypes (Decl* context, Unifier& subst) override {
        int errs0 = numErrors ();
        AST::resolveTypes (context, subst);
        if (!unify (child (0)->getType (), child (1)->getType (), subst)
            && errs0 == numErrors ())
            error (this, "type mismatch in assignment");
        if (!setType (child (1)->getType (), subst) && errs0 == numErrors ())
            error (this, "type mismatch in assignment");
    }

    void calculateScratchSizes(std::vector<unsigned long>& sizes) override {
        sizes[0]++;
        for(auto& c : *this) c->calculateScratchSizes(sizes);
    }

    void specialCase(Code_Context& context) {
        auto lhs = *begin(), rhs = *(begin() + 1);
        lhs->codeGen(context);
        context << " = ";
        rhs->codeGen(context);
    }

    void codeGen(Code_Context& context) override {
        AST_Ptr rhs = *(begin() + 1), initial_lhs = *begin();
        if((rhs->typeIndex() == BINOP_AST || rhs->typeIndex() == INT_LITERAL_AST || rhs->typeIndex() == UNOP_AST)
            && initial_lhs->typeIndex() == ID_AST
            && isTypeInt(initial_lhs->getDecl()->getType()) && isTypeInt(rhs->getType()))
            return specialCase(context);
        while(rhs->typeIndex() == ASSIGN_AST)
            rhs = *(rhs->begin() + 1);
        AST_Ptr curr = this;
        unsigned long currPos = context.advanceTupleAssignScratchPos();
        context << "(tuple_assign_scratch[" << std::to_string(currPos) << "] = ";
        context << "(";
        rhs->codeGen(context);
        context << "), " << endl;
        context.indent();
        while(curr->typeIndex() == ASSIGN_AST) {
            AST_Ptr lhs = *curr->begin();
            unsigned long limit = lhs->typeIndex() == TARGET_LIST_AST
                ? lhs->children().size() : 1;
            std::string num = std::to_string(limit);
            if(lhs->typeIndex() == TARGET_LIST_AST) {
                context << "new Tuple" << num << "_Obj(" << endl;
                context.indent();
            }
            for(unsigned int i = 0; i < limit; i++) {
                AST_Ptr target;
                if(lhs->typeIndex() == TARGET_LIST_AST)
                    target = lhs->children()[i];
                else
                    target = lhs;
                if(target->typeIndex() == ID_AST || target->typeIndex() == ATTRIBUTEREF_AST
                    || target->typeIndex() == TYPED_ID_AST) {
                    target->codeGen(context);
                    context << " = wrapped_dynamic_cast<";
                    target->getType()->codeGen(context);
                    context << ">(";
                    if(lhs->typeIndex() == TARGET_LIST_AST)
                        context << "wrapped_dynamic_cast<Tuple" << num << ">("
                            << "tuple_assign_scratch[" << std::to_string(currPos) << "])->_"
                            << std::to_string(i + 1);
                    else
                        context << "tuple_assign_scratch[" << std::to_string(currPos) << "]";
                    context << ")";
                }
                else if(target->typeIndex() == SLICE_ASSIGN_AST || target->typeIndex() == SUBSCRIPT_ASSIGN_AST) {
                    auto funcExpr = *target->begin();
                    auto funcType = funcExpr->getType();
                    context << "((*(";
                    funcExpr->codeGen(context);
                    context << ")) (" << endl;
                    context.indent();
                    for(auto iter = target->begin() + 1; iter != target->end() - 1; iter++) {
                        auto paramExpr = *iter;
                        context << "wrapped_dynamic_cast<";
                        funcType->typeParam(iter - target->begin())->codeGen(context);
                        context << ">((";
                        paramExpr->codeGen(context);
                        context << "))";
                        context << ", " << endl;
                    }
                    context << "wrapped_dynamic_cast<";
                    funcType->typeParam(target->end() - target->begin() - 1)->codeGen(context);
                    context << ">(";
                    if(lhs->typeIndex() == TARGET_LIST_AST)
                        context << "wrapped_dynamic_cast<Tuple" << num << ">("
                            << "tuple_assign_scratch[" << std::to_string(currPos) << "])->_"
                            << std::to_string(i + 1) << ")";
                    else
                        context << "tuple_assign_scratch[" << std::to_string(currPos) << "])";
                    context.indent(-1);
                    context << "))";
                }
                if(lhs->typeIndex() == TARGET_LIST_AST &&
                    i != lhs->children().size() - 1) context << ", " << endl;
            }
            context << endl;
            if(lhs->typeIndex() == TARGET_LIST_AST) {
                context.indent(-1);
                context << ")";
            }
            curr = *(curr->begin() + 1);
            if(curr->typeIndex() == ASSIGN_AST) context << ", " << endl << endl;
        }
        context << endl;
        context.indent(-1);
        context << ")";
    }
    
};

EXEMPLAR (Assign_AST, ASSIGN_AST);

/***** FOR *****/

/**  for target in exprs: body [ else: body ]     */
class For_AST : public AST_Tree {
public:

    For_AST () : sequence (nullptr) {
    }

protected:

    FACTORY (For_AST);

    AST_Ptr add (AST_Ptr c) override {
        AST_Tree::add (c);
        if (arity () == 4)
            setSequence ();
        return this;
    }


    AST_Ptr add (const AST_Vect& v) override {
        AST_Tree::add (v);
        if (arity () == 4)
            setSequence ();
        return this;
    }

    void resolveTypes (Decl* context, Unifier& subst) override {
        int errs0 = numErrors ();
        AST_Ptr target = child (0);
        sequence->resolveTypes (context, subst);
        target->resolveTypes (context, subst);
        if (!unify (sequence->getType (), target->getType (), subst)
            && errs0 == numErrors ()) {
            error (this, "bad sequence type in 'for' statement");
        }

        for (auto c : trimmedAST (*this, 2))
            c->resolveTypes (context, subst);
    }
        
    void collectDecls (Decl* enclosing) override {
        AST_Ptr target = child (0);
        for (auto c : trimmedAST (*this, 2)) {
            c->collectDecls (enclosing);
        }
        target->addTargetDecls (enclosing);
    }

    void getOverloadings (Resolver& resolver) override {
        assert (sequence != nullptr);
        AST_Tree::getOverloadings (resolver);
        sequence->getOverloadings (resolver);
    }

    AST_Ptr resolveSimpleIds (const Environ* env) override {
        sequence->resolveSimpleIds (env);
        return AST::resolveSimpleIds (env);
    }

    void calculateScratchSizes(std::vector<unsigned long>& sizes) override { 
        sizes[0]++;
        for(auto& c : *this) c->calculateScratchSizes(sizes);
    }

    void codeGen(Code_Context& context) override {
        auto exprType = (*(begin() + 1))->getType();
        auto sequenceType = sequence->getType();
        auto sequenceRetType = (*sequence->begin())->getDecl()->getType()->returnType();
        auto sequenceArgType = (*sequence->begin())->getDecl()->getType()->typeParam(1);
        context << "{" << endl;
        context.indent();
        exprType->codeGen(context);
        context << " loop_expr = wrapped_dynamic_cast<";
        exprType->codeGen(context);
        context << ">(";
        (*(begin() + 1))->codeGen(context);
        context << ");" << endl;
        context << "long init_cnt = loop_expr->_cnt;" << endl;
        context << "while (true) {" << endl;
        context.indent();
        (*sequence->begin())->getDecl()->getType()->returnType()->codeGen(context);
        context << " loop_var = wrapped_dynamic_cast<";
        (*sequence->begin())->getDecl()->getType()->returnType()->codeGen(context);
        context << ">((*";
        (*sequence->begin())->codeGen(context);
        context << ") (loop_expr));" << endl;
        context << "if (valid_pointer(loop_var) && ";
        if((*sequence->begin())->getDecl()->getType()->returnType()->isTypeVariable())
            context << "!loop_var->eq(loop_var)";
        else
            context << "loop_var == nullptr";
        context << ") {" << endl;
        context.indent();
        (*(begin() + 3))->codeGen(context);
        context << "break; " << endl;
        context.indent(-1);
        context << "}" << endl;
        if(sequenceArgType->typeIndex() == TYPE_AST && !(
            (*sequenceArgType->begin())->text() == "dict" || (*sequenceArgType->begin())->text() == "list"
                || (*sequenceArgType->begin())->text() == "range"
        )) context << "loop_expr->_cnt++;" << endl;

        auto lhs = *begin();
        if(lhs->typeIndex() == ID_AST || lhs->typeIndex() == ATTRIBUTEREF_AST
            || lhs->typeIndex() == TYPED_ID_AST) {
            lhs->codeGen(context);
            context << " = wrapped_dynamic_cast<";
            lhs->getDecl()->getType()->codeGen(context);
            context << ">(loop_var);" << endl;
        }
        else if(lhs->typeIndex() == SLICE_ASSIGN_AST || lhs->typeIndex() == SUBSCRIPT_ASSIGN_AST) {
            auto funcExpr = *lhs->begin();
            auto funcType = funcExpr->getType();
            context << "(*(";
            funcExpr->codeGen(context);
            context << ")) (" << endl;
            context.indent();
            for(auto iter = lhs->begin() + 1; iter != lhs->end() - 1; iter++) {
                auto paramExpr = *iter;
                context << "wrapped_dynamic_cast<";
                funcType->typeParam(iter - lhs->begin())->codeGen(context);
                context << ">((";
                paramExpr->codeGen(context);
                context << ")), " << endl;
            }
            context << "wrapped_dynamic_cast<";
            funcType->typeParam(lhs->end() - lhs->begin() - 1)->codeGen(context);
            context << ">(loop_var)" << endl;
            context.indent(-1);
            context << ");" << endl;
        }
        else {
            unsigned long currPos = context.advanceTupleAssignScratchPos();
            std::string num = std::to_string(lhs->children().size());
            assert(lhs->typeIndex() == TARGET_LIST_AST);
            context << "(tuple_assign_scratch[" << std::to_string(currPos) << "] = (";
            context << "loop_var), new Tuple" << num << "_Obj(" << endl;
            context.indent();
            for(unsigned int i = 0; i < lhs->children().size(); i++) {
                auto target = lhs->children()[i];
                if(target->typeIndex() == ID_AST || target->typeIndex() == ATTRIBUTEREF_AST
                    || target->typeIndex() == TYPED_ID_AST) {
                    target->codeGen(context);
                    context << " = wrapped_dynamic_cast<";
                    target->getType()->codeGen(context);
                    context << ">(wrapped_dynamic_cast<Tuple" << num << ">("
                        << "tuple_assign_scratch[" << std::to_string(currPos) << "])->_"
                        << std::to_string(i + 1) << ")";
                }
                else if(target->typeIndex() == SLICE_ASSIGN_AST || target->typeIndex() == SUBSCRIPT_ASSIGN_AST) {
                    auto funcExpr = *target->begin();
                    auto funcType = funcExpr->getType();
                    context << "(*(";
                    funcExpr->codeGen(context);
                    context << ")) (" << endl;
                    context.indent();
                    for(auto iter = target->begin() + 1; iter != target->end() - 1; iter++) {
                        auto paramExpr = *iter;
                        context << "wrapped_dynamic_cast<";
                        funcType->typeParam(iter - target->begin())->codeGen(context);
                        context << ">((";
                        paramExpr->codeGen(context);
                        context << ")), " << endl;
                    }
                    context << "wrapped_dynamic_cast<";
                    funcType->typeParam(target->end() - target->begin() - 1)->codeGen(context);
                    context << ">(wrapped_dynamic_cast<Tuple" << num << ">("
                        << "tuple_assign_scratch[" << std::to_string(currPos) << "])->_"
                        << std::to_string(i + 1) << ")";
                    context.indent(-1);
                    context << ")";
                }
                if(i != lhs->children().size() - 1) context << ", " << endl;
            }
            context << endl;
            context.indent(-1);
            context << "));" << endl;
        }

        (*(begin() + 2))->codeGen(context);
        context << ";" << endl;
        
        context.indent(-1);
        context << endl << "}" << endl;

        context << "loop_expr->_cnt = init_cnt;" << endl;
        context.indent(-1);
        context << "}" << endl;
    }

private:

    /** Initialize sequence (assuming all children present). */
    void setSequence () {
        if (sequence == nullptr) {
            sequence = NODE (CALL_AST, makeId ("__choose__", location ()),
                             child (1));
        }
    }

    /** Artificial identifier used to define the legal sequences for 
     *  for statements.  Shares parameter with child(1). */
    AST_Ptr sequence;
};

EXEMPLAR (For_AST, FOR_AST);


/***** RETURN *****/

/**  return EXPR */
class Return_AST : public AST_Tree {
protected:

    FACTORY(Return_AST);

    void resolveTypes (Decl* context, Unifier& subst) override {
        AST_Tree::resolveTypes (context, subst);
        AST_Ptr expr = child (0);
        Type_Ptr returnType = context->getType ()->returnType ();
        if (!unify (returnType, expr->getType (), subst))
            error (this, "inconsistent return type");
    }

    void codeGen(Code_Context& context) {
        AST_Ptr expr = *begin();
        AST_Ptr func_ret_type = context.getContext()->getType()->returnType();
        if(context.getContext()->isMethod() && context.getContext()->getName() == "__init__"
            && expr->typeIndex() == NONE_AST) {
            std::string funcName = context.getContext()->getName() + "_" +
                std::to_string(context.getContext()->getIndex());
            std::string selfParamName;
            for(auto& d : context.getContext()->getEnviron()->get_members()) {
                if(d->getPosition() == 0 && d->assignable()) {
                    selfParamName = d->getName() + "_" + std::to_string(d->getIndex());
                    break;
                }
            }
            context << "return " << funcName << "_frame->" << selfParamName << ";" << endl;
        }
        else {
            context << "return wrapped_dynamic_cast<";
            func_ret_type->codeGen(context);
            context << ">((";
            expr->codeGen(context);
            context << "));" << endl;
        }
    }
};

EXEMPLAR (Return_AST, RETURN_AST);

bool compareOptimizable(AST_Ptr base) {
    if(base->typeIndex() != COMPARE_AST) return false;
    while(base->typeIndex() == COMPARE_AST || base->typeIndex() == LEFT_COMPARE_AST) {
        AST_Ptr which = *base->begin();
        assert(which->typeIndex() == ID_AST);
        if(which->text() == "__le__" || which->text() == "__ge__" || which->text() == "__gt__"
            || which->text() == "__lt__" || which->text() == "__ne__" || which->text() == "__eq__") {
            auto whichType = which->getDecl()->getType();
            if(whichType->typeIndex() != FUNCTION_TYPE_AST || whichType->numParams() != 2)
                return false;
            auto ret_type = whichType->typeParam(0), param1_type = whichType->typeParam(1), param2_type = whichType->typeParam(2);
            if(ret_type->typeIndex() != TYPE_AST || param1_type->typeIndex() != TYPE_AST || param2_type->typeIndex() != TYPE_AST)
                return false;
            std::string rk = (*ret_type->begin())->text(), p1k = (*param1_type->begin())->text(), p2k = (*param2_type->begin())->text();
            if(rk != "bool" || p1k != "int" || p2k != "int") return false;
            base = *(base->begin() + 1);
        }
        else return false;
    }
    return true;
}

/***** IF *****/

/** if COND: STMT else: STMT */
class If_AST : public AST_Tree {
protected:

    FACTORY(If_AST);

    void resolveTypes (Decl* context, Unifier& subst) override {
        AST_Tree::resolveTypes (context, subst);
        if (!unify (child (0)->getType (), boolDecl->asType (), subst)) {
            error (child (0), "condition must be boolean");
        }
    }

    void codeGen(Code_Context& context) override {
        AST_Ptr cond = *begin();
        context << "if (";
        if(compareOptimizable(cond)
            || cond->typeIndex() == TRUE_AST || cond->typeIndex() == FALSE_AST) {
            cond->setBooleanContext(true);
            cond->codeGen(context);
        }
        else {
            context << "decode(";
            cond->codeGen(context);
            context << ")";
        }
        context << ") {" << endl;
        context.indent();
        AST_Ptr if_body = *(begin() + 1);
        if_body->codeGen(context);
        context << ";" << endl;
        context.indent(-1);
        context << "}" << endl << "else {" << endl;
        context.indent(1);
        AST_Ptr else_body = *(begin() + 2);
        else_body->codeGen(context);
        context << ";" << endl;
        context.indent(-1);
        context << "}" << endl;
    }
};

EXEMPLAR (If_AST, IF_AST);

/***** WHILE *****/

/** while COND: STMT else: STMT */
class While_AST : public AST_Tree {
protected:

    FACTORY(While_AST);

    void resolveTypes (Decl* context, Unifier& subst) override{
        AST_Tree::resolveTypes (context, subst);
        if (!unify (child (0)->getType (), boolDecl->asType (), subst)) {
            error (child (0), "condition must be boolean");
        }
    }

    void codeGen(Code_Context& context) override {
        AST_Ptr cond = *begin();
        context << "while (true) {" << endl;
        context.indent();
        context << "if (";
        if(compareOptimizable(cond)
            || cond->typeIndex() == TRUE_AST || cond->typeIndex() == FALSE_AST) {
            cond->setBooleanContext(true);
            cond->codeGen(context);
        }
        else {
            context << "decode(";
            cond->codeGen(context);
            context << ")";
        }
        context << ") {" << endl;
        context.indent();
        AST_Ptr while_body = *(begin() + 1);
        while_body->codeGen(context);
        context << ";" << endl;
        context.indent(-1);
        context << "}" << endl;
        context << "else {" << endl;
        context.indent();
        AST_Ptr else_body = *(begin() + 2);
        else_body->codeGen(context);
        context << ";" << endl;
        context << "break;" << endl;
        context.indent(-1);
        context << "}" << endl;
        context.indent(-1);
        context << "}" << endl;
    }
};

EXEMPLAR (While_AST, WHILE_AST);

class Break_AST : public AST_Tree {
public:

    FACTORY(Break_AST);

    void codeGen(Code_Context& context) override {
        context << "break;" << endl;
    }
};

EXEMPLAR(Break_AST, BREAK_AST);

class Continue_AST : public AST_Tree {
public:

    FACTORY(Continue_AST);

    void codeGen(Code_Context& context) override {
        context << "continue;" << endl;
    }
};

EXEMPLAR(Continue_AST, CONTINUE_AST);
