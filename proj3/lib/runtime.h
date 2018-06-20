/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* APYC Runtime Library Headers */

/* Authors:  Nikhil Athreya, Nihar Dalal, Vyom Kavishwar, Srinivasa Pranav */

/* The functions here are suggestions. Feel free to replace at will. 
 * Though this file is C++, we have avoided overloading and inheritance, so
 * that changing to C is relatively easy. */

#ifndef _RUNTIME_H_
#define _RUNTIME_H_

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <initializer_list>
#include <algorithm>

using namespace std;

                /* STUBS FOR BUILTIN TYPES */
/* A base class for all other classes.
   Most methods are overridden in inheriting classes. */
class Object_Obj {
public:
    /* id is used to check the type of an object. */
    virtual unsigned long id() const { return 0; }

    /* Functions used for comparing objects. */
    virtual bool eq(const Object_Obj* o) const { return false; }

    virtual bool neq(const Object_Obj* o) const { return false; }

    /* Functions used for printing and serializing objects. */
    virtual std::ostream& print(std::ostream& os) const { return os; }

    virtual std::string toString() const { return ""; }

    virtual std::string reprString() const { return toString(); }

    /* Depending on the class, returns a new instance of the same object
       with all instance variables copied. This is often called during 
       assigns, so implementation varies based on whether an object 
       should be copied or passed during an assign. */
    virtual Object_Obj* copy() const { return nullptr; }

    /* Standard initialization called when object is created. */
    virtual void init() {}
};

/* Represents Integers
   NOTE: should not be used as later runtime optimizations
   necessitated representing Python integers as C++ longs,
   without the use of this wrapper class.*/
class Int_Obj : public Object_Obj {
public:
    /* The underlying representation is a C++ long
       NOT a C++ integer. This is later used for optimizing 
       integer operations. */
    long _underlying;

    Int_Obj(long u);

    ~Int_Obj();

    unsigned long id() const override;

    bool eq(const Object_Obj* o) const override;

    bool neq(const Object_Obj* o) const override;

    std::ostream& print(std::ostream& os) const override;

    std::string toString() const override;

    virtual Object_Obj* copy() const override;
};

/* Represents Booleans.
   NOTE: used in very few cases as later runtime optimizations
   necessitated representing Python booleans as C++ longs. */
class Bool_Obj : public Object_Obj {
public:
    /* The underlying representation is a C++ boolean. */
    bool _underlying;

    Bool_Obj(bool u);

    ~Bool_Obj();

    unsigned long id() const override;

    bool eq(const Object_Obj* o) const override;

    bool neq(const Object_Obj* o) const override;

    std::ostream& print(std::ostream& os) const override;

    std::string toString() const override;

    virtual Object_Obj* copy() const override;
};

/* Represents Ranges */
class Range_Obj : public Object_Obj {
    /* Stores start and end indices passed into constructor. */
    long _start, _end;

public:
    unsigned long _cnt;

    /* Iterator used mainly in for loops.
       Tracks current number to return.
       This is used as the underlying implementation.
       Implements standard iterator methods.  */
    struct iterator {
    private:
        long _curr;
    public:
        iterator(long c) : _curr(c) {

        }

        ~iterator() {
    
        }

        Int_Obj operator*() {
            Int_Obj i(_curr);
            return i;
        }

        iterator& operator++() {
            _curr++;
            return *this;
        }

        bool operator==(const iterator& i) const {
            return i._curr == _curr;
        }

        bool operator!=(const iterator& i) const {
            return !(i == *this);
        }
    };

    Range_Obj(long s, long e);

    Range_Obj(Int_Obj s, Int_Obj e);

    ~Range_Obj();

    /* Returns iterator that implements functionality of range.
       Accessing begin() + int will provide the same integer
       that a range in Python provides. */
    iterator begin() const;

    iterator end() const;

    /* Return bounds supplied when initializing a range.
       Note the similar names to the begin and end, but different
       return types! */
    long start() const;

    long done() const;

    unsigned long id() const override;

    bool eq(const Object_Obj* o) const override;

    bool neq(const Object_Obj* o) const override;

    std::ostream& print(std::ostream& os) const override;

    std::string toString() const override;

    virtual Object_Obj* copy() const override;
};

Range_Obj::iterator begin(const Range_Obj& r);

Range_Obj::iterator end(const Range_Obj& r);

/* Represents Strings */
class Str_Obj : public Object_Obj {
public:
    /* The underlying representation is a C++ string.
       _cnt is used specifically for __choose__str__ instead of
       implementing the method via a full iterator. */
    unsigned long _cnt;
    std::string _underlying;

    Str_Obj(const std::string& u);

    ~Str_Obj();

    unsigned long id() const override;

    bool eq(const Object_Obj* o) const override;

    bool neq(const Object_Obj* o) const override;

    std::ostream& print(std::ostream& os) const override;

    std::string toString() const override;

    std::string reprString() const override;

    virtual Object_Obj* copy() const override;
};

/* Represents Lists */
class List_Obj : public Object_Obj {
public:
    /* The underlying representation is a C++ vector<Object_Obj*>. 
       _cnt is used specifically for __choose__list__ instead of
       implementing the method via a full iterator. */
    unsigned long _cnt;
    std::vector<Object_Obj*> _underlying;

    List_Obj(const std::vector<Object_Obj*>& u);

    ~List_Obj();

    unsigned long id() const override;

    bool eq(const Object_Obj* o) const override;

    bool neq(const Object_Obj* o) const override;

    std::ostream& print(std::ostream& os) const override;

    std::string toString() const override;

    virtual Object_Obj* copy() const override;
};

/* Represents Dictionaries */
class Dict_Obj : public Object_Obj {
public:
    /* The underlying representation is two C++ vector<Object_Obj*>.
       One is used to store keys and the other to store the corresponding
       value in the same index as the key.
       _cnt is used specifically for __choose__dict__ instead of
       implementing the method via a full iterator. */
    unsigned long _cnt;
    std::vector<Object_Obj*> _keys;
    std::vector<Object_Obj*> _values;

    Dict_Obj(const std::vector<Object_Obj*>& k, const std::vector<Object_Obj*>& v);

    ~Dict_Obj();

    unsigned long id() const override;

    bool eq(const Object_Obj* o) const override;

    bool neq(const Object_Obj* o) const override;

    std::ostream& print(std::ostream& os) const override;

    /* Due to the deterministic ordering of a vector, the string representation
       of a dictionary is also deterministic (unlike Python). */
    std::string toString() const override;

    virtual Object_Obj* copy() const override;
};

/* Represents Tuples with no contents.
   NOTE: there is no real underlying representation and everything
   is hard-coded. */
class Tuple0_Obj : public Object_Obj {
public:
    Tuple0_Obj();

    ~Tuple0_Obj();

    unsigned long id() const override;

    bool eq(const Object_Obj* o) const override;

    bool neq(const Object_Obj* o) const override;

    std::ostream& print(std::ostream& os) const override;

    std::string toString() const override;

    virtual Object_Obj* copy() const override;
};

/* Represents Tuples containing 1 item. */
class Tuple1_Obj : public Object_Obj {
public:
    /* The underlying representation is a pointer. */
    Object_Obj* _1;

    Tuple1_Obj(Object_Obj* o1);

    ~Tuple1_Obj();

    unsigned long id() const override;

    bool eq(const Object_Obj* o) const override;

    bool neq(const Object_Obj* o) const override;

    std::ostream& print(std::ostream& os) const override;

    std::string toString() const override;

    virtual Object_Obj* copy() const override;
};

/* Represents Tuples containing 2 items. */
class Tuple2_Obj : public Object_Obj {
public:
    /* The underlying representation is two pointers.
       This is used for simplicity as a tuples are unmutable. */
    Object_Obj* _1, * _2;

    Tuple2_Obj(Object_Obj* o1, Object_Obj* o2);

    ~Tuple2_Obj();

    unsigned long id() const override;

    bool eq(const Object_Obj* o) const override;

    bool neq(const Object_Obj* o) const override;

    std::ostream& print(std::ostream& os) const override;

    std::string toString() const override;

    virtual Object_Obj* copy() const override;
};

/* Represents Tuples containing 3 items. */
class Tuple3_Obj : public Object_Obj {
public:
    /* The underlying representation is three pointers.
       This is used for simplicity as a tuples are unmutable. */
    Object_Obj* _1, * _2, * _3;

    Tuple3_Obj(Object_Obj* o1, Object_Obj* o2, Object_Obj* o3);

    ~Tuple3_Obj();

    unsigned long id() const override;

    bool eq(const Object_Obj* o) const override;

    bool neq(const Object_Obj* o) const override;

    std::ostream& print(std::ostream& os) const override;

    std::string toString() const override;

    virtual Object_Obj* copy() const override;
};

/* Represents Python functions, including class methods. */
template<typename Ret, typename... Args> class Function_Obj : public Object_Obj {
public:
    /* The underlying representation is a C++ functional with 
       the appropriate type templates. The name of the function is stored for
       code generation purposes as well. */
    std::string _function_name;
    std::function<Ret(Args...)> _underlying;

    Function_Obj(std::string fn, std::function<Ret(Args...)> f) :
        _underlying(f), _function_name(fn) {}

    /* This constructor allows anonymous (unnamed) functions. */
    Function_Obj(std::function<Ret(Args...)> f) :
        _underlying(f), _function_name("<anonymous>") {}

    ~Function_Obj() {}

    std::function<Ret(Args...)>& operator*() { return _underlying; }

    /* Calls the underlying C++ functional with the translated 
       C++ arguments. */
    Ret operator()(Args... args) const { return _underlying(args...); }

    unsigned long id() const override { return 11; }

    /* Declares equality if underlying functionals are equal. */
    bool eq(const Object_Obj* o) const override {
        if(o == nullptr || o->id() != id()) return false;
        const Function_Obj<Ret, Args...>* f = dynamic_cast<const Function_Obj<Ret, Args...>*>(o);
        if(f == nullptr) return false;
        return *_underlying.template target<Ret(Args...)>() == *f->_underlying.template target<Ret(Args...)>();
    }

    bool neq(const Object_Obj* o) const override { return !eq(o); }

    std::ostream& print(std::ostream& os) const override { os << toString(); return os; }

    std::string toString() const override {
        return "<" + _function_name + " " + std::to_string((unsigned long) this) + ">";
    }

    virtual Object_Obj* copy() const override {
        return new Function_Obj<Ret, Args...>(_function_name, _underlying);
    }
};

/* Standard typedefs to avoid typing _Obj* */
typedef Object_Obj* Object;
typedef Str_Obj* Str;
typedef Int_Obj* Int;
typedef Bool_Obj* Bool;
typedef Range_Obj* Range;
typedef List_Obj* List;
typedef Dict_Obj* Dict;
typedef Tuple0_Obj* Tuple0;
typedef Tuple1_Obj* Tuple1;
typedef Tuple2_Obj* Tuple2;
typedef Tuple3_Obj* Tuple3;

/* Catch all type, often must be case to be used. */
typedef Object Any;

/* A temporary buffer used for storing partially computed
   comparison results. Used during code generation. */
struct LeftCompareData {
    Object_Obj* _rhs;
    Bool_Obj* _result;
};

/* A vector of buffers also used for code generation. */
extern std::vector<LeftCompareData*> left_compare_scratch;

/* Temporary buffers used for storing partially computed
   logical results. Used during code generation. */
extern std::vector<Object> and_or_scratch;
extern std::vector<Object> tuple_assign_scratch;

                /* NATIVE METHODS */
/* Function names are those used in 'native' statements. */

/*  Type Bool */

extern Bool __truth__ (Any x);
extern Bool __not__ (Any x);

/** The values of True and False. */
extern Bool __true__, __false__;

/*  Type Range */

extern Range __xrange__ (Int low, Int high);
extern Int __len__range__ (Range r);

/*  Type Int */

extern Int __add__int__ (Int x, Int y);
extern Int __sub__int__ (Int x, Int y);
extern Int __mul__int__ (Int x, Int y);
extern Int __floordiv__int__ (Int x, Int y);
extern Int __mod__int__ (Int x, Int y);
extern Int __pow__int__ (Int x, Int y);
extern Int __neg__int__ (Int x);
extern Int __pos__int__ (Int x);
extern Bool __lt__int__ (Int x, Int y);
extern Bool __gt__int__ (Int x, Int y);
extern Bool __le__int__ (Int x, Int y);
extern Bool __ge__int__ (Int x, Int y);
extern Bool __eq__int__ (Int x, Int y);
extern Bool __ne__int__ (Int x, Int y);

/*  toint is the replacement for 'Int' as a function in our dialect. */
extern Int __toint__str__ (Str x);

/*  Type Str */

extern Str __add__str__ (Str x, Str y);
extern Str __lmul__str__ (Str x, Int y);
extern Str __rmul__str__ (Int x, Str y);
extern Bool __lt__str__ (Str x, Str y);
extern Bool __gt__str__ (Str x, Str y);
extern Bool __le__str__ (Str x, Str y);
extern Bool __ge__str__ (Str x, Str y);
extern Bool __eq__str__ (Str x, Str y);
extern Bool __ne__str__ (Str x, Str y);
extern Str __getitem__str__ (Str S, Int k);
extern Str __getslice__str__ (Str S, Int L, Int U);
extern Int __len__str__ (Str S);

/* toStr is the replacement for 'Str' as a function in our dialect. */
extern Str __toStr__ (Any x);

/*  Type List */

extern Any __getitem__list__ (List S, Int k);
extern List __getslice__list__ (List S, Int L, Int U);
extern Any __setitem__list__ (List S, Int k, Any val);
extern List __setslice__list__ (List S, Int a, Int b, List val);
extern Int __len__list__ (List S);

/*  Replaces sys.argv */
extern char** prog_argv;
extern int prog_argc;
extern List __argv__ ();

/*  Type File */

extern Str __readline__ ();
extern Str __read__ ();

/*  Type Dict */

extern Any __getitem__dict__int__ (Dict D, Int x);
extern Any __getitem__dict__bool__ (Dict D, Bool x);
extern Any __getitem__dict__str__ (Dict D, Str x);
extern Any __setitem__dict__int__ (Dict S, Int k, Any val);
extern Any __setitem__dict__bool__ (Dict S, Bool k, Any val);
extern Any __setitem__dict__str__ (Dict S, Str k, Any val);
extern Int __len__dict__int__ (Dict D);
extern Int __len__dict__bool__ (Dict D);
extern Int __len__dict__str__ (Dict D);

/*  Backwards from regular Python */

extern Bool __contains__dict__int__ (Int x, Dict D);
extern Bool __contains__dict__bool__ (Bool x, Dict D);
extern Bool __contains__dict__str__ (Str x, Dict D);

/*  Backwards from regular Python */

extern Bool __notcontains__dict__int__ (Int x, Dict D);
extern Bool __notcontains__dict__bool__ (Bool x, Dict D);
extern Bool __notcontains__dict__str__ (Str x, Dict D);

/*  General */

extern Bool __is__ (Any x, Any y);
extern Bool __isnot__ (Any x, Any y);

/*  Extra Credit: Attempted implementation, 
    but still work in progress. Shell usable
    if implemented in future. */
extern Any __gc__ ();


                /* OTHER RUNTIME SUPPORT (SUGGESTIONS) */

/** For implementing list displays.  __createList__(n, a1, ..., an) creates
 *  the list [a1, a2, ..., an]. */
extern List __createList__ (std::vector<Object> values);

/** For implenting dictionary displays. 
 *  __createDict__(n, k1, v1, k2, v2, ..., kn, vn) creates the dictionary
 *      { k1 : v1, k2 : v2, ..., kn : vn  }
 */
extern Dict __createDict__ (std::vector<Object> kvs);

/* Additional __choose__ methods not originally included in skeleton. */
Object __choose__list__(List l);
Int __choose__list__(Range r);
Object __choose__dict__(Dict d);
Str __choose__str__(Str s);


                        /* Extra Credit: Integer Optimization */

/* Relies on changing top byte being 4 in
   order to recognize booleans encoded as longs. */
template<typename T>
static inline bool is_bool(T p) {
    unsigned long n = (unsigned long) p;
    return n & 0x4000000000000000ul;
}

/* Opposite of is_bool. */
template<typename T>
static inline bool is_int(T p) {
    return !is_bool(p);
}

/* Decodes booleans and integers encoded as longs.
   I dentifies based on top byte and processes bottom
   32 bits to return C++ integer or boolean. */
template<typename T>
static inline long decode(T p) { 
    unsigned long n = (unsigned long) p;
    if (n & 0x4000000000000000ul) {
        return (bool) (n & 0x00000000FFFFFFFFul);
    }
    return (int) (n & 0x00000000FFFFFFFFul); 
}

/* Wrapper for future implementation of overflow checks. */
static inline bool overflow_check (long n) { return -(1l << 31) > n || n > ((1l << 31) - 1); }

/* Changes top byte to 8, encoding integer as a long. */
template<typename T>
static inline Int encode(T p) {
    unsigned long n = (unsigned long) p; 
    unsigned int u = n & 0x00000000FFFFFFFFul;
    return (Int) (u | 0x8000000000000000ul); 
}

/* Changes top byte to 4, encoding bool as a long. */
template<typename T>
static inline Bool encode_bool(T p) {
    unsigned long n = (unsigned long) p; 
    unsigned int u = n & 0x00000000FFFFFFFFul;
    return (Bool) (u | 0x4000000000000000ul); 
}

/* Processes top 16 bits to check if they are 0. 
   If they are 0, then the input is actually a pointer. */
template<typename T>
static inline bool valid_pointer (T p) {
     return !((unsigned long) p & 0x8000000000000000ul || (unsigned long) p & 0x4000000000000000ul); }

/* Several wrapped dynamic casts special-case the long
   representation of integers and booleans. These allow for
   proper type casting during code generation in order to 
   produce C++ code that compiles. */ 

/* Casts when input is not a nullpointer or boolean and output
   is not and Int or Bool. */
template<typename T, typename U,
    typename = typename std::enable_if<
        !std::is_same<T, Int>::value
        && !std::is_same<T, Bool>::value
        && !std::is_same<U, bool>::value
        && !std::is_same<U, std::nullptr_t>::value>::type>
static inline T wrapped_dynamic_cast(U u) {
    if(!valid_pointer(u)) return (T) u;
    else return dynamic_cast<T>(u);
}

/* Casts when output should be an Int. 
   Needed in case input is encoded as a long. */
template<typename T, typename U,
    typename = typename std::enable_if<std::is_same<T, Int>::value>::type>
Int wrapped_dynamic_cast(U u) {
    if(valid_pointer(u)) return dynamic_cast<Int>(u);
    else return encode(u);
}

/* Casts when output should be an Bool. 
   Needed in case input is encoded as a long. */
template<typename T, typename U,
    typename = typename std::enable_if<std::is_same<T, Bool>::value>::type>
Bool wrapped_dynamic_cast(U u) {
    if(valid_pointer(u)) return dynamic_cast<Bool>(u);
    else return encode_bool(u);
}

/* Catches nullpointer casts when the return
   type is Bool or Int. */
template<typename T>
T wrapped_dynamic_cast(std::nullptr_t u) {
    return u;
}

/* Catches and encodes booleans separately from integers.*/
template<typename T> 
T wrapped_dynamic_cast(bool b) {
    return dynamic_cast<T>(encode_bool(b));
}

/* General helper function for copying Objects.
   Useful for special-casing booleans and integers
   encoded as longs. */
Object object_copy(Object u);

/* Used in code generation to modify printing booleans
   encoded as longs. */
void print(bool disable, std::string to_print);

#endif
