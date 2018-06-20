/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* exprs.cc: AST subclasses related to expressions. */

/* Authors:  Nikhil Athreya, Nihar Dalal, Vyom Kavishwar, Srinivasa Pranav */

#include <iostream>
#include <iomanip>
#include <cassert>
#include <sstream>
#include "apyc.h"
#include "ast.h"

using namespace std;

                     /*** PRIMARY EXPRESSIONS ***/

/** Represents an identifier. */
class Id_AST : public AST_Leaf {

    void print (AST_Printer& printer) override {
        printer.os << "(id " << location () << " " << text ();
        if (getDecl () != nullptr)
            printer.os << " " << getDecl ()->getIndex ();
        printer.os << ")";
    }

    AST_Ptr getId () override {
        return this;
    }

    bool isType () override {
        Decl* me = getDecl ();
        return (me != nullptr && me->isType ());
    }

    bool hasType () override {
        return getDecl () != nullptr && getDecl ()->hasType ();
    }

    Type_Ptr computeType () override {
        return newTypeVar ();
    }

    int getNumDecls () override {
        return _me.size ();
    }

    const Decl_Vect& getDecls () override {
        return _me;
    }

    void addDecl (Decl* decl) override {
        _me.push_back (decl);
    }

    Decl* getDecl () override {
        if (_me.size () == 0)
            return nullptr;
        return _me[_index];
    }

    void setDecl (int k) override {
        if (k < 0 || k >= _me.size ())
            throw range_error ("declaration selection out of range");
        _index = k;
    }

    void removeDecl (int k) override {
        assert (k >= 0 && k < (int) _me.size ());
        _me.erase (_me.begin () + k);
    }

    void addTargetDecls (Decl* enclosing) override {
        string name = text ();
        Decl* old = enclosing->getEnviron ()->findImmediate (name);
        if (old == nullptr) {
            addDecl (enclosing->addVarDecl(this));
        } else if (! old->assignable ()) {
            error (this, "attempt to assign to non-assignable object: %s",
                   name.c_str ());
            addDecl (old);
        } else {
            addDecl (old);
        }
    }   

    AST_Ptr resolveSimpleIds (const Environ* env) override {
        string name = text ();
        if (getDecl () != nullptr)
            return this;
        Decl_Vect defns;
        env->find (name, defns);
        if (defns.empty ()) {
            error (this, "undefined identifier: %s", name.c_str ());
            addDecl (makeUnknownDecl (this, false));
            return this;
        }
        if (defns.size () == 1 && defns[0]->isType ()) {
            AST_Ptr asTypeId;
            addDecl (defns[0]);
            if (defns[0]->getTypeArity () != 0) {
                error (this, "wrong number (0) of type parameters");
                asTypeId = defns[0]->asGenericType ();
            } else
                asTypeId = defns[0]->asType ();
            asTypeId->setLoc (location ());
            return asTypeId;
        }
        for (auto d : defns)
            addDecl (d);
        return this;
    }

    void getOverloadings (Resolver& resolver) override {
        resolver.addId (this);
    }            

    void resolveTypes (Decl* context, Unifier& subst) override {
        Decl* decl = getDecl ();
        if (decl != nullptr && !decl->isType ()) {
            if (!unify (decl->getType (), getType (), subst))
                error (this, "no suitable declaration of %s",
                       text ().c_str ());
        }
    }

    void findUsedDecls (Decl_Set& used) override {
        if (getNumDecls () > 0) {
            used.insert (getDecl ());
        }
        getType ()->findUsedDecls (used);
    }    

    void reachableDecls (Decl_Set& decls, AST_Set& visited) override {
        if (visited.count (this) == 0) {
            visited.insert (this);
            decls.insert (_me.begin (), _me.end ());
        }
    }

    AST_Ptr replaceBindings (const Unifier& subst, AST_Set& visiting) override {
        AST::replaceBindings (subst, visiting);
        for (auto d : getDecls ()) {
            d->replaceBindings (subst);
        }
        return this;
    }

    void freeTypeVarCheck (const Type_Set& allowed) override {
        if (getDecl ()->assignable ()) {
            Type_Set typeVars;
            Type_Set visited;
            getType ()->getTypeVariables (typeVars, visited);
            for (auto c : allowed)
                typeVars.erase (c);
            if (!typeVars.empty ()) {
                error (this, "type of %s has free type variables",
                       text ().c_str ());
            }
        }
    }

    /* This function handles code generation for identifiers. If an identifier is a global variable, we just
       reference it directly. Otherwise, if we are inside of a function and we are referencing a local variable,
       we need to get the variable from our current stack frame. Additionally, if we are inside a nested function
       and we need to refer to a variable inside of an enclosing function, we traverse the static links inside of
       our stack frames until we reach the appropriate parent function which contains the variable we want.

       We also want to wrap all global function inside of Function_Obj's just to make sure that so that we can treat
       global functions within our type system. Nested functions are already declared as Function_Obj's inside of our
       stack frame classes (see our Module_AST's codeGen for more details). So only global functions and methods
       undergo this wrapping.
    */
    void codeGen(Code_Context& context) override {
        if(getDecl()->isOverloadable() &&
            (getDecl()->getContainer() == mainModule || getDecl()->getContainer()->isType())) {
            context << "new Function_Obj<";
            Type_Ptr t = getDecl()->getType();
            for(auto iter = t->begin(); iter != t->end(); iter++) {
                //(*iter)->codeGen(context);
                context << "Object";
                if(iter != t->end() - 1) context << ", ";
            }
            context << ">(\"" << text() << "\", ";
        }
        if(getDecl()->getContainer() != mainModule && !getDecl()->getContainer()->isType()) {
            std::string currContext = context.getContext()->getName()
                + "_" + std::to_string(context.getContext()->getIndex());
            context << currContext << "_frame->";
            Decl* curr = context.getContext();
            while(curr != getDecl()->getContainer())
                context << "_parent->", curr = curr->getContainer();
        }
        context << text() << "_" << std::to_string(getDecl()->getIndex());
        if(getDecl()->isOverloadable() && 
            (getDecl()->getContainer() == mainModule || getDecl()->getContainer()->isType()))
            context << ")";
    }

    FACTORY (Id_AST);

public:
    
    Id_AST () : _index (0) { }

private:

    /** Possible Decls that represent me. */
    Decl_Vect _me;
    /** Index in _me of the current value of getDecl (). */
    int _index;
};

EXEMPLAR (Id_AST, ID_AST);


/** Superclass of leaves that represent values having types. */
class Typed_Leaf : public AST_Leaf
{
protected:

    bool hasType () override {
        return true;
    }

};

/** Represents an integer literal. */
class Int_Literal_AST : public Typed_Leaf {
private:

    void print (AST_Printer& printer) override {
        printer.os << "(int_literal " << location () << " " << value << ")";
    }

    /** Augment setText to initialize value from the text of the lexeme,
     *  checking that the literal is in range. */
    void setText (const string& text) override {
        AST_Leaf::setText(text);
        try {
            size_t opos = text.find_first_of ("oO");
            if (opos != string::npos) {
                value = stoi (text.substr(opos+1), nullptr, 8);
            } else {
                value = stoi (text, nullptr, 0);
            }
        } catch (out_of_range excp) {
            error (location (), "integer literal out of range");
            value = 0;
        }
    }

    Type_Ptr computeType () override {
        return intDecl->asType ();
    }

    long value;

    /** This function generates code for Int_Literals employing the integer optimizations that
     * we have implemented, using the encode function defined in runtime.cc.
     * **/
    void codeGen(Code_Context& context) override {
        context << "encode(" << std::to_string(value) << "ul)";
    }

    FACTORY(Int_Literal_AST);

};

EXEMPLAR(Int_Literal_AST, INT_LITERAL_AST);

    
/** A string literal. In Python, a string may be denoted by a number of
 *  string and raw string tokens concatentated together.  For example:
 *       message = 'He said, "Don"' "'t do that!" 
 *  A String_Literal_AST contains a sequence of string tokens and,
 *  when printing an AST, concatenates them together. **/
class String_Literal_AST : public Typed_Leaf {
public:
    
    string denotedText () const override {
        return literalText;
    }

    void setText (const string& text) override {
        literalText.clear ();
        AST_Leaf::setText ("");
        appendText(text);
    }        

    void appendText(const string& s0) override {
        if (s0.empty ()) {
            return;
        }
        
        string s (s0);

        if (!text ().empty ()) {
            AST_Leaf::appendText (" ");
        }
        AST_Leaf::appendText (s);

        for (size_t p = s.find ("\r\n"); p != string::npos;
             p = s.find ("\r\n", p + 2)) {
            s.replace(p, 2, "\n");
        }
        for (size_t p = s.find ('\r'); p != string::npos;
             p = s.find ('\r', p + 1)) {
            s[p] = '\n';
        }

        if (s[0] == 'r') {
            if (s.compare (0, 4, "r'''") == 0
                || s.compare (0, 4, "r\"\"\"") == 0
                || s.compare (0, 4, "R'''") == 0
                || s.compare (0, 4, "R\"\"\"") == 0) {
                literalText += s.substr (4, s.size () - 7);
            } else {
                literalText += s.substr (2, s.size () - 3);
            }
        } else {
            int v;
            size_t i;

            if (s.compare (0, 3, "'''") == 0
                || s.compare (0, 3, "\"\"\"") == 0) {
                s = s.substr (3, s.size () - 6);
            } else {
                s = s.substr (1, s.size () - 2);
            }

            i = 0;
            while (i < s.size ()) {
                i += 1;
                if (s[i-1] == '\\') {
                    i += 1;
                    switch (s[i-1]) {
                    default: literalText += '\\'; v = s[i-1]; break;
                    case '\r':
                    {
                        if (s[i] == '\n') {
                            i += 1;
                            continue;
                        } else {
                            error (location(), "stray carriage return");
                        }
                        break;
                    }
                    case '\n': continue;
                    case 'a': v = '\007'; break;
                    case 'b': v = '\b'; break;
                    case 'f': v = '\f'; break;
                    case 'n': v = '\n'; break;
                    case 'r': v = '\r'; break;
                    case 't': v = '\t'; break;
                    case 'v': v = '\v'; break;
                    case '\'': v = '\''; break;
                    case '"': case '\\': v = s[i-1]; break;
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': 
                    { 
                        v = s[i-1] - '0';
                        for (int j = 0; j < 2; j += 1) {
                            if ('0' > s[i] || s[i] > '7')
                                break;
                            v = v*8 + (s[i] - '0');
                            i += 1;
                        }
                        break;
                    }
                    case 'x': {
                        if (i+2 > s.size () || 
                            !isxdigit (s[i]) || !isxdigit (s[i+1])) {
                            error (location (),
                                   "bad hexadecimal escape sequence");
                            break;
                        }
                        sscanf (s.c_str ()+i, "%2x", &v);
                        i += 2;
                        break;
                    }
                    }
                } else
                    v = s[i-1];
                literalText += (char) v;        
            }
        }
    }

    void print (AST_Printer& printer) override {
        printer.os << "(string_literal " << location () << " \"";
        for (size_t i = 0; i < literalText.size (); i += 1) {
            int c = literalText[i] & 0377;
            if (c < '\040' || c == '\\' || c == '"' || c >= '\177') {
                printer.os << "\\" << oct << setw (3) << setfill('0') << c
                    << setfill (' ') << dec;
            } else
                printer.os << (char) c;
        }
        printer.os << "\")";
    }

    Type_Ptr computeType () override {
        return strDecl->asType ();
    }
    /** This function handles code generation for String Literals using the defined object for
     * String Types known as Str_Obj. Characters are correctly escaped and formatted using ASCII codes. **/
    void codeGen(Code_Context& context) override {
        context << "new Str_Obj(\"";
        stringstream ss;
        for(size_t i = 0; i < literalText.size(); i++) {
            int c = literalText[i] & 0377;
            if(c < '\040' || c == '\\' || c == '"' || c >= '\177')
                ss << "\\" << oct << setw(3) << setfill('0') << c << setfill(' ') << dec;
            else
                ss << std::string(1, (char) c);
        }
        context << ss.str() << "\")";
    }
        
private:
    FACTORY(String_Literal_AST);

    string literalText;
};

EXEMPLAR(String_Literal_AST, STRING_LITERAL_AST);


                 /* OTHER EXPRESSIONS */

/* The following are EXAMPLES (possibly incomplete) of potentially
 * useful AST classes. */

/*****   NONE, TRUE, FALSE     *****/

class None_AST : public Typed_Tree {
protected:

    FACTORY (None_AST);
    // This function handles code generation for None in python by replacing to  
    void codeGen(Code_Context& context) override {
        context << "nullptr";
    }

};

EXEMPLAR(None_AST, NONE_AST);

class True_AST : public Typed_Tree {
protected:

    FACTORY (True_AST);

    Type_Ptr computeType () override {
        return boolDecl->asType ();
    }
    /**  This function handles code generation for True in python by implementing our 
     * Boolean optimizations and calling encode_bool if we are not in an if or while context. If we
     * are in an if or while context we simply write true, because we need to return a true or false
     * for checking conditions in if and while **/   
    void codeGen(Code_Context& context) override {
        if(getBooleanContext()) context << "true";
        else context << "encode_bool(1)";
    }

};

EXEMPLAR(True_AST, TRUE_AST);


class False_AST : public Typed_Tree {
protected:

    FACTORY (False_AST);

    Type_Ptr computeType () override {
        return boolDecl->asType ();
    }

     /**  This function handles code generation for False in python by implementing our 
     * Boolean optimizations and calling encode_bool if we are not in an if or while context. If we
     * are in an if or while context we simply write false, because we need to return a true or false
     * for checking conditions in if and while **/   
    void codeGen(Code_Context& context) override {
        if(getBooleanContext()) context << "false";
        else context << "encode_bool(0)";
    }

};

EXEMPLAR(False_AST, FALSE_AST);

/*****   CALLS    *****/

/** The supertype of "callable" things, including ordinary calls,
 *  binary operators, unary operators, subscriptions, and slices. */

class Callable : public Typed_Tree {
protected:

    /** Returns the expression representing the quantity that is
     *  called to evaluate this expression. */
    virtual AST_Ptr calledExpr () {
        return child (0);
    }

    /** Returns the number of actual parameters in this call. */
    virtual int numActuals () {
        return arity () - 1;
    }

    /** Return the Kth actual parameter in this call. */
    virtual AST_Ptr actualParam (int k) {
        return child (k + 1);
    }

    /** Set the Kth actual parameter in this call to EXPR. */
    virtual void setActual (int k, AST_Ptr expr) {
        setChild (k + 1, expr);
    }

    /** Perform type resolution on me, assuming my children have been
     *  resolved.  Arguments are as for resolveTypes. */
    virtual void resolveMyType (Decl* context, Unifier& subst) {
        Type_Ptr funcType;
        funcType = calledExpr ()->getType ();

        if (!makeFuncType (numActuals (), funcType, subst)) {
            error (this,
                   "called object is not a %d-parameter function",
                   numActuals ());
            return;
        }

        funcType = subst[funcType];
        setExprType (subst);


        for (int i = 0; i < numActuals (); i += 1) {
            if (!unify (actualParam (i)->getType (),
                        funcType->paramType (i), subst)) {
                error (this, "non-matching parameter type (parameter #%d)",
                       i);
                break;
            }
        }
    }


    /** Set my type. */
    virtual void setExprType (Unifier& subst) {
        if (!setType (subst[calledExpr ()->getType ()]->returnType (),
                      subst)) {
            error (this, "inappropriate function return type");
            return;
        }
    }

    void resolveTypes (Decl* context, Unifier& subst)  override {
        AST::resolveTypes (context, subst);
        resolveMyType (context, subst);
    }

    bool isIntBuiltin() {
        if((*begin())->typeIndex() != ID_AST) return false;
        std::string func_name = (*begin())->text();
        auto funcType = (*begin())->getDecl()->getType();
        if(func_name == "__add__" || func_name == "__sub__" || func_name == "__mul__"
            || func_name == "__floordiv__" || func_name == "__mod__" || func_name == "__pow__") {
            if(funcType->numParams() != 2) return false;
            auto param1 = funcType->typeParam(1), param2 = funcType->typeParam(2), ret = funcType->typeParam(0);
            if(param1->typeIndex() != TYPE_AST || param2->typeIndex() != TYPE_AST || ret->typeIndex() != TYPE_AST) return false;
            std::string param1Type = (*param1->begin())->text(), param2Type = (*param2->begin())->text(), retType = (*ret->begin())->text();
            return param1Type == "int" && param2Type == "int" && retType == "int";
        }
        else if(func_name == "__lt__" || func_name == "__gt__" || func_name == "__eq__"
            || func_name == "__ne__" || func_name == "__ge__" || func_name == "__le__") { 
            if(funcType->numParams() != 2) return false;
            auto param1 = funcType->typeParam(1), param2 = funcType->typeParam(2), ret = funcType->typeParam(0);
            if(param1->typeIndex() != TYPE_AST || param2->typeIndex() != TYPE_AST || ret->typeIndex() != TYPE_AST) return false;
            std::string param1Type = (*param1->begin())->text(), param2Type = (*param2->begin())->text(), retType = (*ret->begin())->text();
            return param1Type == "int" && param2Type == "int" && retType == "bool";
        }
        else if(func_name == "__neg__" || func_name == "__pos__") {
            if(funcType->numParams() != 1) return false;
            auto param1 = funcType->typeParam(1), ret = funcType->typeParam(0);
            if(param1->typeIndex() != TYPE_AST || ret->typeIndex() != TYPE_AST) return false;
            std::string param1Type = (*param1->begin())->text(), retType = (*ret->begin())->text();
            return param1Type == "int" && retType == "int";
        }
        return false;
    }

    void calculateScratchSizes(std::vector<unsigned long>& sizes) override {
        if(isIntBuiltin() && (*begin())->text() == "__floordiv__") sizes[0] += 2;
        if(typeIndex() == LEFT_COMPARE_AST) sizes[1]++;
        if(begin() + 1 < end() && (*(begin() + 1))->typeIndex() == LEFT_COMPARE_AST) sizes[1]++;
        for(auto& c : *this) c->calculateScratchSizes(sizes);
    }
    /** This function is the main function responsible for generating code for all types of Callable things like functions and operators.
     *  First we check if a function is a built-in Int function, because in that case we must use our Int optimizations.
     *  Within the many built-in Int functions there are several possibilities. 
     *      If the functions are pos or neg then we encode in a + or - respectively
     *      and then encode or decode depending on whether the argument is an int literal or not.
     *      
     *      If the function is anything other than a power or floordivision function then we have to worry about left compares. 
     *      We advance the position in the list of LeftCompareData in this context. For every LEFT_COMPARE_AST in the current AST we advance the position
     *      in the array and we assign the data to the data of the next ast. The result of the left compare is encoded using our boolean optimizations.
     *      
     *      We have a series of simple outputs that for various functions that output the right c++ symbol for the python functions.
     *      
     *      If the function is a floordiv, then we use the list of tuple_assigns to add the two operands into the array using int optimizations as necessary.
     *      We check if there is a division by 0 and output an error if there is. We use tuple assign because the spec says that all assigns are to be viewed
     *      as tuples.
     * 
     *      If the function is a power function, we use the standard c++ power function with the relevant int optimizations.
     * 
     *  If the function is not a built-in integer function, we once again check if it is a left compare and if it is then we do the right assignments in the array
     *  of left compares and assign the optimized boolean values to their results.
     * 
     *  For the other types of functions we cast the result of the function to the type of the function.
     * 
     *  If the function is a reference to a function to a class then we first find the relevant class declaration and then we use the correct method number
     *  to call the function.
     *       **/
    void codeGen(Code_Context& context) {
        unsigned long leftComparePos = 0;
        auto funcExpr = *begin();
        auto funcType = funcExpr->getType();
        if(isIntBuiltin()) {
            context << "(";
            std::string which = (*begin())->text();
            if(which == "__pos__" || which == "__neg__") {
                context << "encode(";
                if(which == "__pos__") context << "+";
                else context << "-";
                context << " ";
                if((*(begin() + 1))->typeIndex() == INT_LITERAL_AST) {
                    context << (*(begin() + 1))->text() << "ul";
                }
                else {
                    context << " decode(";
                    (*(begin() + 1))->codeGen(context);
                    context << ")";
                }
                context << ")";
            }
            else if(which != "__pow__" && which != "__floordiv__") {
                if(typeIndex() == LEFT_COMPARE_AST)
                    currPos = context.advanceLeftCompareScratchPos();
                if(begin() + 1 != end() && (*(begin() + 1))->typeIndex() == LEFT_COMPARE_AST) {
                    leftComparePos = context.advanceLeftCompareScratchPos();
                    auto left_compare = dynamic_cast<Callable*>(*(begin() + 1));
                    context << "(" << endl;
                    context.indent();
                    left_compare->setBooleanContext(getBooleanContext());
                    left_compare->codeGen(context);
                    context.indent(-1);
                    context << ")," << endl;
                    context << "left_compare_scratch[" << std::to_string(leftComparePos)
                        << "] = left_compare_scratch[" << std::to_string(left_compare->currPos) << "],"
                        << endl;
                    context << "!decode(left_compare_scratch[" << std::to_string(leftComparePos)
                        << "]->_result)" << endl;
                    context.indent();
                    if(typeIndex() == LEFT_COMPARE_AST)
                        context << "? (left_compare_scratch[" << std::to_string(currPos)
                            << "]->_result = encode_bool(0))" << endl;
                    else {
                        if(getBooleanContext()) context << "? false" << endl;
                        else context << "? encode_bool(0)" << endl;
                    }
                    context << ": (" << endl;
                    context.indent();
                }
                if(typeIndex() == LEFT_COMPARE_AST) {
                    context << "left_compare_scratch[" << std::to_string(currPos) << "]->_result = "
                        << "wrapped_dynamic_cast<Bool>((" << endl;
                    context.indent();
                }
                if(which == "__le__" || which == "__ge__" || which == "__gt__" || which == "__lt__" || which == "__ne__"
                    || which == "__eq__") {
                    if(!getBooleanContext()) context << "encode_bool";
                    context << "(" << endl;
                }
                else
                    context << "encode(" << endl;
                context.indent();
                if(begin() + 1 != end() && (*(begin() + 1))->typeIndex() == LEFT_COMPARE_AST)
                    context << "decode(left_compare_scratch[" << std::to_string(leftComparePos) << "]->_rhs)";
                else {
                    if((*(begin() + 1))->typeIndex() == INT_LITERAL_AST)
                        context << (*(begin() + 1))->text() << "ul";
                    else {
                        context << "decode(";
                        (*(begin() + 1))->codeGen(context);
                        context << ")";
                    }
                }
                context << endl;
                if(which == "__add__") context << "+ ";
                else if(which == "__sub__") context << "- ";
                else if(which == "__mul__") context << "* ";
                else if(which == "__mod__") context << "% ";
                else if(which == "__le__") context << "<= ";
                else if(which == "__ge__") context << ">= ";
                else if(which == "__lt__") context << "< ";
                else if(which == "__gt__") context << "> ";
                else if(which == "__eq__") context << "== ";
                else if(which == "__ne__") context << "!= ";
                if(typeIndex() != LEFT_COMPARE_AST
                    && (*(begin() + 2))->typeIndex() == INT_LITERAL_AST) {
                    context << (*(begin() + 2))->text() << "ul" << endl;
                }
                else {
                    context << "decode(";
                    if(typeIndex() == LEFT_COMPARE_AST)
                        context << "left_compare_scratch[" << std::to_string(currPos) << "]->_rhs = ";
                    (*(begin() + 2))->codeGen(context);
                    context << ")" << endl;
                }
                context.indent(-1);
                context << ")";
                if(typeIndex() == LEFT_COMPARE_AST) {
                    context << endl;
                    context.indent(-1);
                    context << "))";
                }
                if(begin() + 1 != end() && (*(begin() + 1))->typeIndex() == LEFT_COMPARE_AST) {
                    context << endl;
                    context.indent(-1);
                    context << ")";
                    context.indent(-1);
                }
            }
            else if(which == "__floordiv__") {
                unsigned int tlhs = context.advanceTupleAssignScratchPos(),
                    trhs = context.advanceTupleAssignScratchPos();
                context << "tuple_assign_scratch[" << std::to_string(tlhs) << "] = encode(" << endl;
                context.indent();
                (*(begin() + 1))->codeGen(context);
                context << endl;
                context.indent(-1);
                context << ")," << endl;

                context << "tuple_assign_scratch[" << std::to_string(trhs) << "] = encode(" << endl;
                context.indent();
                (*(begin() + 2))->codeGen(context);
                context << endl;
                context.indent(-1);
                context << ")," << endl;

                context << "decode(tuple_assign_scratch[" << std::to_string(trhs) << "]) == 0" << endl;
                context.indent();
                context << "? (std::cerr << \"Error: divide by zero\\n\", std::exit(1), encode(0))" << endl;
                context << ": encode(decode(tuple_assign_scratch[" << std::to_string(tlhs) << "]) / decode(tuple_assign_scratch[" << std::to_string(trhs) << "]))" << endl;
                context.indent(-1);
            }
            else {
                context << "encode(std::pow(" << endl;
                context.indent();
                if((*(begin() + 1))->typeIndex() == INT_LITERAL_AST) {
                    context << (*(begin() + 1))->text() << "ul," << endl;
                }
                else {
                    context << "decode(";
                    (*(begin() + 1))->codeGen(context);
                    context << ")," << endl;
                }
                if((*(begin() + 2))->typeIndex() == INT_LITERAL_AST) {
                    context << (*(begin() + 2))->text() << "ul";
                }
                else {
                    context << "decode(";
                    (*(begin() + 2))->codeGen(context);
                    context << ")" << endl;
                }
                context.indent(-1);
                context << "))";
            }
            context << ")";
            return;
        }

        context << "(";
        if(typeIndex() == LEFT_COMPARE_AST)
            currPos = context.advanceLeftCompareScratchPos();
        if(begin() + 1 != end() && (*(begin() + 1))->typeIndex() == LEFT_COMPARE_AST) {
            leftComparePos = context.advanceLeftCompareScratchPos();
            auto left_compare = dynamic_cast<Callable*>(*(begin() + 1));
            context << "((" << endl;
            context.indent();
            left_compare->setBooleanContext(getBooleanContext());
            left_compare->codeGen(context);
            context.indent(-1);
            context << "), ";
            context << "left_compare_scratch[" << std::to_string(leftComparePos) << "] = ";
            context << "left_compare_scratch[" << std::to_string(left_compare->currPos) << "]";
            context << ")," << endl;
            context << "!decode(left_compare_scratch[" << std::to_string(leftComparePos)
                << "]->_result)" << endl;
            context.indent();
            if(typeIndex() == LEFT_COMPARE_AST)
                context << "? (left_compare_scratch[" << std::to_string(currPos)
                    << "]->_result = encode_bool(0))" << endl;
            else {
                if(getBooleanContext()) context << "? false" << endl;
                else context << "? encode_bool(0)" << endl;
            }
            context << ": (";
        }
        if(typeIndex() == LEFT_COMPARE_AST) {
            context << "left_compare_scratch[" << std::to_string(currPos) << "]->_result = ";
            context << "wrapped_dynamic_cast<Bool>((";
        }
        context << "(*(";
        if(funcExpr->typeIndex() != ID_AST && funcExpr->typeIndex() != ATTRIBUTEREF_AST) {
            context << "wrapped_dynamic_cast<";
            funcType->codeGen(context);
            context << ">((" << endl;
            context.indent();
            funcExpr->codeGen(context);
            context << endl;
            context.indent(-1);
            context << "))";
        }
        else
            funcExpr->codeGen(context);
        context << ")) (" << endl;
        context.indent();
        unsigned long offset = 1;
        if(funcExpr->typeIndex() == ATTRIBUTEREF_AST) {
            auto funcId = *(funcExpr->begin() + 1);
            assert(funcId->typeIndex() == ID_AST);
            auto classContainer = funcId->getDecl()->getContainer()->asGenericType();
            context << "wrapped_dynamic_cast<";
            classContainer->codeGen(context);
            context << ">((";
            auto obj = *funcExpr->begin();
            obj->codeGen(context);
            context << "))";
            if(begin() + offset < end()) context << ",";
            context << endl;
        }
        for(auto iter = begin() + offset; iter < end(); iter++) {
            auto paramExpr = *iter;
            context << "wrapped_dynamic_cast<";
            funcType->typeParam(iter - begin())->codeGen(context);
            context << ">((";
            if(iter == begin() + 1 && begin() + 1 != end() &&
                (*(begin() + 1))->typeIndex() == LEFT_COMPARE_AST)
                context << "left_compare_scratch[" << std::to_string(leftComparePos) << "]->_rhs";
            else {
                if(iter == end() - 1 && typeIndex() == LEFT_COMPARE_AST)
                    context << "left_compare_scratch[" << std::to_string(currPos) << "]->_rhs = (";
                paramExpr->codeGen(context);
                if(iter == end() - 1 && typeIndex() == LEFT_COMPARE_AST)
                    context << ")";
            }
            context << "))";
            if(iter != end() - 1) context << ", " << endl;
            else context << endl;
        }
        context.indent(-1);
        context << ")";
        if(begin() + 1 != end() && (*(begin() + 1))->typeIndex() == LEFT_COMPARE_AST) {
            context << ")" << endl;
            context.indent(-1);
        }
        if(typeIndex() == LEFT_COMPARE_AST)
            context << "))";
        context << ")";
    }

private:
    unsigned long currPos;
};

/** A function call. */
class Call_AST : public Callable {
protected:

    FACTORY (Call_AST);

    AST_Ptr resolveAllocators (const Environ* env) override {
        Callable::resolveAllocators (env);
        AST_Ptr callable = calledExpr ();
        if (callable->isType ()) {
            AST_Vect initArgs;
            AST_Ptr init =
                NODE(ATTRIBUTEREF_AST, callable,
                     makeId ("__init__", location ()));
            initArgs.push_back (init);
            initArgs.push_back (NODE (NEW_AST, callable));
            for (int i = 0; i < numActuals (); i += 1)
                initArgs.push_back (actualParam (i));
            return NODE (CALL1_AST, initArgs);
        }
        return this;
    }

};

EXEMPLAR (Call_AST, CALL_AST);

/** A binary operator. */
class Binop_AST : public Callable {

    FACTORY (Binop_AST);

};

EXEMPLAR (Binop_AST, BINOP_AST);

/** A unary operator. */
class Unop_AST : public Callable {

    FACTORY (Unop_AST);

};    

EXEMPLAR (Unop_AST, UNOP_AST);


/***** COMPARE *****/

/** A comparison yielding bool */
class Compare_AST : public Binop_AST {
protected:

    FACTORY (Compare_AST);

    Type_Ptr computeType () override {
        return boolDecl->asType ();
    }
};

EXEMPLAR (Compare_AST, COMPARE_AST);



/***** LEFT_COMPARE *****/

/** A comparison yielding its second operand's type. */
class LeftCompare_AST : public Binop_AST {
protected:

    FACTORY (LeftCompare_AST);

    void setExprType (Unifier& subst) override {
        if (!setType (actualParam (1)->getType (), subst)) {
            error (this, "inappropriate type");
            return;
        }
    }

    Type_Ptr computeType () override {
        return actualParam (1)->getType ();
    }

};

EXEMPLAR (LeftCompare_AST, LEFT_COMPARE_AST);

/***** CALL1 *****/

/** __init__(new T, ...)      */
class Call1_AST : public Call_AST {
protected:

    FACTORY (Call1_AST);

    Type_Ptr computeType () override {
        return actualParam (0)->getType ();
    }
    /** This function handles code generation for a specific type of call which is the creation of a new user created class. 
     *  The return type is dynamically cast to a new instance of the user created class. It reflects the __init__ function in python.
     * **/
    void codeGen(Code_Context& context) override {
        auto funcExpr = *begin();
        auto funcType = funcExpr->getType();
        auto retType = *(begin() + 1);
        auto classId = *retType->begin();
        AST_Vect args(begin() + 2, end());
        std::string constructedClassName = classId->getDecl()->getName() + "_"
            + std::to_string(classId->getDecl()->getIndex());

        context << "wrapped_dynamic_cast<" << constructedClassName << "*>((*(";
        funcExpr->codeGen(context);
        context << ")) (" << endl;
        context.indent();
        context << "new " << constructedClassName << "()";
        if(args.size() != 0) context << ",";
        context << endl;
        for(auto iter = args.begin(); iter != args.end(); iter++) {
            auto paramExpr = *iter;
            context << "wrapped_dynamic_cast<";
            funcType->typeParam(iter - args.begin() + 2)->codeGen(context);
            context << ">((";
            paramExpr->codeGen(context);
            context << "))";
            if(iter != args.end() - 1) context << ", " << endl;
        }
        context.indent(-1);
        context << "))";
    }

};

EXEMPLAR (Call1_AST, CALL1_AST);


/***** SUBSCRIPTION *****/

/** E1[E2] */
class Subscription_AST : public Callable {
protected:

    FACTORY (Subscription_AST);

    void addTargetDecls (Decl* enclosing) override {
    }

};

EXEMPLAR (Subscription_AST, SUBSCRIPT_AST);

class Subscript_Assign_AST : public Callable {
protected:

    FACTORY (Subscript_Assign_AST);

    void addTargetDecls (Decl* enclosing) override {
    }

};

EXEMPLAR (Subscript_Assign_AST, SUBSCRIPT_ASSIGN_AST);
    
    
/***** SLICING *****/

/** E1[E2:E3] */
class Slicing_AST : public Callable {
protected:

    FACTORY (Slicing_AST);

    void addTargetDecls (Decl* enclosing) override {
    }

};

EXEMPLAR (Slicing_AST, SLICE_AST);

class Slicing_Assign_AST : public Callable {
protected:

    FACTORY (Slicing_Assign_AST);

    void addTargetDecls (Decl* enclosing) override {
    }

};

EXEMPLAR (Slicing_Assign_AST, SLICE_ASSIGN_AST);
    

/***** NEW *****/

/**  new T     */
class New_AST : public Typed_Tree {
protected:

    FACTORY (New_AST);

    void resolveTypes (Decl* context, Unifier& subst) override {
        if (!setType (child (0)->asType (), subst)) {
            error (this, "inconsistent types");
        }
    }

};

EXEMPLAR (New_AST, NEW_AST);


/***** ATTRIBUTEREF *****/

/** E.ID */
class AttributeRef_AST : public Typed_Tree {
protected:

    FACTORY (AttributeRef_AST);

    AST_Ptr getId () override {
        return child (1);
    }

    const Decl_Vect& getDecls () override {
        return getId ()->getDecls ();
    }

    int getNumDecls () override {
        return getId ()->getNumDecls ();
    }

    void addTargetDecls (Decl* enclosing) override {
    }

    AST_Ptr resolveStaticSelections (const Environ* env) override {
        AST_Ptr left = child (0)->resolveStaticSelections (env);
        if (!left->isType ())
            return this;
        AST_Ptr id = getId ();
        if (id->getDecl () != nullptr)
            return id;
        string name = id->text ();
        const Environ* members = left->getDecl ()->getEnviron ();
        Decl_Vect defns;
        members->findImmediate (name, defns);
        if (defns.empty ()) {
            error (this, "no definition of %s in type", name.c_str ());
            id->addDecl (makeUnknownDecl (id, false));
        }
        for (size_t i = 0; i < defns.size (); i += 1) {
            if (!defns[i]->isMethod ())
                error (this, "np class variables in this dialect");
            id->addDecl (defns[i]);
        }
        return id;
    }

    void resolveTypes (Decl* context, Unifier& subst) override {
        int errs0 = numErrors ();
        AST_Ptr obj = child (0);
        AST_Ptr id = getId ();
        obj->resolveTypes (context, subst);
        string name = id->text ();
        Decl* attrDecl = id->getDecl ();
        if (attrDecl == nullptr)
            return;
        Decl* expectedClassDecl = attrDecl->getContainer ();
        if (expectedClassDecl != nullptr && expectedClassDecl->isType ()) {
            vector<Type_Ptr> linkedTypes;
            linkedTypes.push_back (expectedClassDecl->asBaseType ());
            linkedTypes.push_back (attrDecl->getSelectedType ());
            freshen (linkedTypes);
            if (!unify (linkedTypes[0], obj->getType (), subst)
                || (errs0 == numErrors () 
                    && (!setType (linkedTypes[1], subst)
                        || !unify (getType (), id->getType (), subst)))) {
                error (this,
                       "attribute %s has no definition that fits the context.",
                       name.c_str ());
            }
        }
    }

    AST_Ptr resolveSimpleIds (const Environ* env) override {
        setChild (0, child (0)->resolveSimpleIds (env));
        AST_Ptr id = getId ();
        string name = id->text ();
        const Decl_Vect& decls = outerEnviron->get_members ();
        for (auto classd : decls)
            classd->addAttributeDecls (id);
        if (id->getNumDecls () == 0) {
            error (this, "no definitions of the %s attribute", name.c_str ());
            id->addDecl (makeUnknownDecl (id, false));
        }
        return this;
    }
    /** This function handles code generation for attributes of classes. If the attribute is a method then we create a new function object with a name that
     *  reflects the class that is a member of. The return types are parsed and there is a special case for __init__ in which case the return is always just an
     *  Object. If the attribute is not a method then we use pointer notation to refer to an instance variable of a class.
     * **/
    void codeGen(Code_Context& context) override {
        auto obj = *begin();
        auto mem = *(begin() + 1);
        std::string memberName = mem->getDecl()->getName() + "_"
            + std::to_string(mem->getDecl()->getIndex());
        if(mem->getDecl()->isOverloadable()) {
            auto methodType = mem->getDecl()->getType();
            context << "new Function_Obj<";
            if(mem->text() == "__init__") context << "Object";
            else context << "Object"; //methodType->typeParam(0)->codeGen(context);
            if(methodType->children().size() != 1) {
                context << ", ";
                for(unsigned long l = 1; l < methodType->children().size(); l++) {
                    //methodType->typeParam(l)->codeGen(context);
                    context << "Object";
                    if(l != methodType->children().size() - 1) context << ", ";
                }
            }
            context << ">(\"" << memberName << "\", " << memberName << ")";
        }
        else {
            context << "(";
            obj->codeGen(context);
            context << ")->";
            context << memberName;
        }
    }

};

EXEMPLAR (AttributeRef_AST, ATTRIBUTEREF_AST);


/***** TUPLE *****/

/** (E1, ...)  */
class Tuple_AST : public Typed_Tree {
protected:

    FACTORY (Tuple_AST);

    void resolveTypes (Decl* context, Unifier& subst) override {
        Typed_Tree::resolveTypes (context, subst);
        if (arity () > 3)
            error (this, "tuple has too many elements (max 3)");
        Type_Vect componentTypes;
        for (auto c : *this)
            componentTypes.push_back (c->getType ());
        Type_Ptr tupleType =
            tupleDecl[arity ()]->asType (componentTypes);
        if (!setType (tupleType, subst))
            error (this, "type mismatch on tuple");
    }        
    
    /** This function generates code for Tuples. First we determine the correct
     * number of elements in the tuple and then we create a new instance of the right
     * sized Tuple object. **/
    void codeGen(Code_Context& context) override {
        std::string num = std::to_string(arity());
        context << "new Tuple" << num << "_Obj(" << endl;
        context.indent();
        for(auto iter = begin(); iter != end(); iter++) {
            context << "(";
            (*iter)->codeGen(context);
            context << ")";
            if(iter != end() - 1) context << ", " << endl;
        }
        context << endl;
        context.indent(-1);
        context << ")";
    }
};

EXEMPLAR (Tuple_AST, TUPLE_AST);

/***** TARGET_LIST *****/

/** (TARGET, ...) on left-hand side of assignment, for. */
class TargetList_AST : public Typed_Tree {
protected:

    FACTORY (TargetList_AST);

    void addTargetDecls (Decl* enclosing) override {
        for (auto c :  *this) {
            c->addTargetDecls (enclosing);
        }
    }

    void resolveTypes (Decl* context, Unifier& subst) override {
        if (arity () > 3)
            error (this, "target list has too many elements (max 3)");
        Type_Vect componentTypes;
        for (int i = 0; i < arity (); i += 1)
            componentTypes.push_back (newTypeVar ());
        Type_Ptr tupleType =
            tupleDecl[arity ()]->asType (componentTypes);
        if (!setType (tupleType, subst))
            error (this, "type mismatch on assignment");
        for (int i = 0; i < arity (); i += 1) {
            child (i)->resolveTypes (context, subst);
            if (!unify(child (i)->getType (), componentTypes[i], subst)) 
                error (child (i), "type mismatch on assignment");
        }
    }        

};

EXEMPLAR (TargetList_AST, TARGET_LIST_AST);


/***** LIST_DISPLAY *****/

/** [E1, ...]  */
class ListDisplay_AST : public Typed_Tree {
protected:

    FACTORY (ListDisplay_AST);

    void resolveTypes (Decl* context, Unifier& subst) override {
        Typed_Tree::resolveTypes (context, subst);
        Type_Ptr componentType =
            arity () == 0 ? newTypeVar () : child (0)->getType ();
        for (int i = 1; i < arity (); i += 1)
            if (!unify (componentType, child (i)->getType (), subst)) {
                error (child (i), "type mismatch in list display");
                break;
            }
        Type_Ptr listType =
            listDecl->asType (AST_Vect (1, componentType));
        if (!setType (listType, subst))
            error (this, "type mismatch on list display");
    }    

    /** This function handles code generation for list displays. It creates a new list of general object type and adds all objects to this new list. **/
    void codeGen(Code_Context& context) override {
        context << "__createList__(std::vector<Object>{" << endl;
        context.indent();
        for(auto iter = begin(); iter != end(); iter++) {
            context << "(";
            (*iter)->codeGen(context);
            context << ")";
            if(iter != end() - 1) context << ", " << endl;
        }
        context << endl;
        context.indent(-1);
        context << "})";
    }
};

EXEMPLAR (ListDisplay_AST, LIST_DISPLAY_AST);


/***** DICT_DISPLAY *****/

/** { a: b, ... }  */
class DictDisplay_AST : public Typed_Tree {
protected:

    FACTORY (DictDisplay_AST);

    void resolveTypes (Decl* context, Unifier& subst) override {
        Typed_Tree::resolveTypes (context, subst);
        Type_Ptr keyType, valType;
        if (arity () == 0) {
            keyType = newTypeVar ();
            valType = newTypeVar ();
        } else  {
            keyType = child (0)->child (0)->getType ();
            valType = child (0)->child (1)->getType ();
        }
        for (int i = 1; i < arity (); i += 1) {
            if (!unify (keyType, child (i)->child (0)->getType (), subst)) {
                error (child (i), "key type mismatch in dict display");
                break;
            }
            if (!unify (valType, child (i)->child (1)->getType (), subst)) {
                error (child (i), "value type mismatch in dict display");
                break;
            }
        }
        Type_Ptr dictType =
            dictDecl->asType (AST_Vect ({ keyType, valType }));
        if (!setType (dictType, subst))
            error (this, "type mismatch on dict display");
    }
    /** This function handles code generation for dictionaries. It uses our createDict function and then adds in a list of pair and values to this newly 
     *  created dictionary. **/

    void codeGen(Code_Context& context) override {
        context << "__createDict__ (std::vector<Object>{" << endl;
        context.indent();
        for(auto iter = begin(); iter != end(); iter++) {
            auto pair = *iter;
            auto& key = *pair->begin();
            auto& value = *(pair->begin() + 1);
            context << "(";
            key->codeGen(context);
            context << "), (";
            value->codeGen(context);
            context << ")";
            if(iter != end() - 1) context << ", " << endl;
        }
        context <<  endl;
        context.indent(-1);
        context << "})";
    }

};

EXEMPLAR (DictDisplay_AST, DICT_DISPLAY_AST);


/***** NEXT_VALUE *****/

/** The dummy source for assignments in target lists. */
class NextValue_AST : public Typed_Tree {
protected:

    FACTORY (NextValue_AST);

};

EXEMPLAR (NextValue_AST, NEXT_VALUE_AST);

/** A class of expression in which its subexpressions must agree as to
 *  type and its value's type is that of its subexpressios. */
class BalancedExpr : public Typed_Tree {
protected:

    FACTORY (BalancedExpr);

    void resolveTypes (Decl* context, Unifier& subst) override {
        int k = arity ();
        Typed_Tree::resolveTypes (context, subst);
        if (!unify (child (k - 2)->getType (), child (k - 1)->getType (), subst))
            error (this, "types of alternatives do not match");
        if (!setType (child (k - 1)->getType (), subst))
            error (this, "inconsistent types");
    }

    void calculateScratchSizes(std::vector<unsigned long>& sizes) override {
        sizes[2]++;
        for(auto& c : *this) c->calculateScratchSizes(sizes);
    }

    /** This function handles general code generation for balanced expressions. We cast the types of all subexpressions to the the type of the function as
     *  a whole, which in this case is always a Boolean. We once again employ Boolean optimizations in this case. For the if expressions we also cast both 
     *  possible results to the same type.
     * **/
    void codeGen(Code_Context& context) override {
        switch(typeIndex()) {
	case AND_AST:
	case OR_AST: {
            unsigned long currPos = context.advanceAndOrScratchPos();
            context << "wrapped_dynamic_cast<";
            child(arity() - 1)->getType()->codeGen(context);
            context << ">";
            context << "((and_or_scratch[" << std::to_string(currPos) << "] = (Object) (";
            AST_Ptr first = *begin();
            first->codeGen(context);
            context.indent();
            context << ")," << endl;
            context << "(" << (typeIndex() == AND_AST ? "!" : "")
                << "decode(__truth__(and_or_scratch[" << std::to_string(currPos) << "]))" << endl;
            context << "? and_or_scratch[" << std::to_string(currPos) << "]" << endl;
            context << ": (Object) (";
            AST_Ptr second = *(begin() + 1);
            second->codeGen(context);
            context << "))))";
            context.indent(-1);
        }
        break;
        case IF_EXPR_AST: {
            context << "(decode(";
            AST_Ptr cond = *begin();
            cond->codeGen(context);
            context << ")" << endl;
            context.indent();
            context << "? wrapped_dynamic_cast<";
            child(arity() - 1)->getType()->codeGen(context);
            context << ">((";
            AST_Ptr true_path = *(begin() + 1);
            true_path->codeGen(context);
            context << "))" << endl;
            context << ": wrapped_dynamic_cast<";
            child(arity() - 1)->getType()->codeGen(context);
            context << ">((";
            AST_Ptr false_path = *(begin() + 2);
            false_path->codeGen(context);
            context << ")))";
            context.indent(-1);
        };
        break;
        default:
        break;
        }
    }

};

/***** IF_EXPR *****/

/**  E1 if Cond else E2  */
class IfExpr_AST : public BalancedExpr {
protected:

    void resolveTypes (Decl* context, Unifier& subst) override {
        BalancedExpr::resolveTypes (context, subst);
        if (!unify (child (0)->getType (), boolDecl->asType (), subst)) {
            error (child (0), "condition must be boolean");
        }
    }

    FACTORY (IfExpr_AST);
};              


EXEMPLAR (IfExpr_AST, IF_EXPR_AST);

/***** AND *****/

/** E1 and E2 */
class And_AST : public BalancedExpr {
protected:

    FACTORY (And_AST);
};

EXEMPLAR (And_AST, AND_AST);

/***** OR *****/

/** E1 or E2 */
class Or_AST : public BalancedExpr {
protected:

    FACTORY (Or_AST);

};

EXEMPLAR (Or_AST, OR_AST);
    
