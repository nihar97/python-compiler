/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* APYC Runtime Library */

/* Authors:  Nikhil Athreya, Nihar Dalal, Vyom Kavishwar, Srinivasa Pranav */

#include "runtime.h"
#include <string>
#include <cassert>
#include <cmath>

using namespace std;

Str_Obj::Str_Obj(const std::string &u) : _underlying(u), _cnt(0)
{
}

Str_Obj::~Str_Obj()
{
}

unsigned long Str_Obj::id() const { return 1; }

bool Str_Obj::eq(const Object_Obj *s) const
{
    if (s == nullptr || !valid_pointer(s) || s->id() != id())
        return false;
    return dynamic_cast<const Str_Obj *>(s)->_underlying == _underlying;
}

bool Str_Obj::neq(const Object_Obj *s) const
{
    return !eq(s);
}

std::string Str_Obj::toString() const
{
    return _underlying;
}

std::string Str_Obj::reprString() const
{
    bool contains_dq = false, contains_sq = false;
    for (auto &c : _underlying)
    {
        if (c == '\"')
            contains_dq = true;
        else if (c == '\'')
            contains_sq = true;
    }
    if (!contains_sq && !contains_dq)
        return "'" + _underlying + "'";
    else if (!contains_sq && contains_dq)
        return "'" + _underlying + "'";
    else if (contains_sq && !contains_dq)
        return "\"" + _underlying + "\"";
    else
    {
        std::string ret = "'";
        for (auto &c : _underlying)
            if (c == '\'')
                ret += "\\\'";
        ret += "'";
        return ret;
    }
}

std::ostream &Str_Obj::print(std::ostream &os) const
{
    os << _underlying;
    return os;
}

Object_Obj *Str_Obj::copy() const
{
    Str_Obj *ret = new Str_Obj(_underlying);
    ret->_cnt = _cnt;
    return ret;
}

Int_Obj::Int_Obj(long u) : _underlying(u)
{
}

Int_Obj::~Int_Obj()
{
}

unsigned long Int_Obj::id() const { return 2; }

bool Int_Obj::eq(const Object_Obj *o) const
{
    if (o == nullptr || valid_pointer(o) || o->id() != id())
        return false;
    return dynamic_cast<const Int_Obj *>(o)->_underlying == _underlying;
}

bool Int_Obj::neq(const Object_Obj *o) const
{
    return !eq(o);
}

std::string Int_Obj::toString() const
{
    return std::to_string(_underlying);
}

std::ostream &Int_Obj::print(std::ostream &os) const
{
    os << _underlying;
    return os;
}

Object_Obj *Int_Obj::copy() const
{
    return new Int_Obj(_underlying);
}

Bool_Obj::Bool_Obj(bool u) : _underlying(u)
{
}

Bool_Obj::~Bool_Obj()
{
}

unsigned long Bool_Obj::id() const { return 3; }

bool Bool_Obj::eq(const Object_Obj *o) const
{
    if (o == nullptr || !valid_pointer(o) || o->id() != id())
        return false;
    return dynamic_cast<const Bool_Obj *>(o)->_underlying == _underlying;
}

bool Bool_Obj::neq(const Object_Obj *o) const
{
    return !eq(o);
}

std::string Bool_Obj::toString() const
{
    return _underlying ? "True" : "False";
}

std::ostream &Bool_Obj::print(std::ostream &os) const
{
    os << _underlying;
    return os;
}

Object_Obj *Bool_Obj::copy() const
{
    return new Bool_Obj(_underlying);
}

Range_Obj::Range_Obj(long s, long e) : _start(s), _end(e), _cnt(s)
{
}

Range_Obj::Range_Obj(Int_Obj s, Int_Obj e) : _start(s._underlying), _end(e._underlying)
{
}

Range_Obj::~Range_Obj()
{
}

Range_Obj::iterator Range_Obj::begin() const
{
    return iterator(_start);
}

Range_Obj::iterator Range_Obj::end() const
{
    return iterator(_end);
}

long Range_Obj::start() const { return _start; }

long Range_Obj::done() const { return _end; }

unsigned long Range_Obj::id() const { return 4; }

bool Range_Obj::eq(const Object_Obj *r) const
{
    if (r == nullptr || valid_pointer(r) || r->id() != id())
        return false;
    const Range_Obj *a = dynamic_cast<const Range_Obj *>(r);
    return a->_start == _start && a->_end == _end;
}

bool Range_Obj::neq(const Object_Obj *r) const
{
    return !eq(r);
}

std::string Range_Obj::toString() const {
    return "xrange(" + std::to_string(_start) + ", " + std::to_string(_end) + ")";
}

std::ostream &Range_Obj::print(std::ostream &os) const
{
    os << toString();
    return os;
}

Object_Obj *Range_Obj::copy() const
{
    return const_cast<Range>(this);
}

Range_Obj::iterator begin(const Range_Obj &r) { return r.begin(); }

Range_Obj::iterator end(const Range_Obj &r) { return r.end(); }

List_Obj::List_Obj(const std::vector<Object_Obj *> &u) : _underlying(u),
                                                         _cnt(0)
{
}

List_Obj::~List_Obj()
{
}

unsigned long List_Obj::id() const { return 5; }

bool List_Obj::eq(const Object_Obj *l) const
{
    if (l == nullptr || !valid_pointer(l) || l->id() != id())
        return false;

    const List_Obj *a = dynamic_cast<const List_Obj *>(l);
    if (_underlying.size() != a->_underlying.size())
        return false;

    for (unsigned long i = 0; i < _underlying.size(); i++)
    {
        if (_underlying[i] == nullptr || a->_underlying[i] == nullptr)
        {
            if (_underlying[i] != a->_underlying[i])
                return false;
        }
        else
        {
            bool uv = valid_pointer(_underlying[i]), auv = valid_pointer(a->_underlying[i]);
            if (uv && auv && !_underlying[i]->eq(a->_underlying[i]))
                return false;
            else if (!uv && !auv && (unsigned long)(_underlying[i]) != (unsigned long)(a->_underlying[i]))
                return false;
            else
                return false;
        }
    }
    return true;
}

bool List_Obj::neq(const Object_Obj *o) const
{
    return !eq(o);
}

std::string List_Obj::toString() const
{
    std::string ret = "[";
    for (unsigned long i = 0; i < _underlying.size(); i++)
    {
        if (valid_pointer(_underlying[i]))
        {
            if (_underlying[i] != nullptr)
                ret += _underlying[i]->reprString();
            else
                ret += "None";
        }
        else
            ret += std::to_string(decode(_underlying[i]));
        if (i != _underlying.size() - 1)
            ret += ", ";
    }
    ret += "]";
    return ret;
}

std::ostream &List_Obj::print(std::ostream &os) const
{
    os << toString();
    return os;
}

Object_Obj *List_Obj::copy() const
{
    return const_cast<List>(this);
}

Dict_Obj::Dict_Obj(const std::vector<Object_Obj *> &k, const std::vector<Object_Obj *> &v) : _keys(k), _values(v), _cnt(0)
{
}

Dict_Obj::~Dict_Obj()
{
}

unsigned long Dict_Obj::id() const { return 6; }

bool Dict_Obj::eq(const Object_Obj *d) const
{
    assert(_keys.size() == _values.size());
    if (d == nullptr || !valid_pointer(d) || id() != d->id())
        return false;

    const Dict_Obj *a = dynamic_cast<const Dict_Obj *>(d);
    assert(a->_keys.size() == a->_values.size());

    if (a->_keys.size() != _keys.size() || a->_values.size() != _values.size())
        return false;

    for (unsigned long i = 0; i < _keys.size(); i++)
    {
        bool kv = valid_pointer(_keys[i]), akv = valid_pointer(a->_keys[i]);
        bool vv = valid_pointer(_values[i]), avv = valid_pointer(a->_values[i]);
        if (akv != kv || vv != avv)
            return false;
        if (kv && akv)
        {
            if (a->_keys[i] == nullptr || _keys[i] == nullptr)
            {
                if (a->_keys[i] != _keys[i])
                    return false;
            }
            else if (!a->_keys[i]->eq(_keys[i]))
                return false;
        }
        else if (!kv && !akv && decode(a->_keys[i] != a->_keys[i]))
            return false;

        if (vv && avv)
        {
            if (a->_values[i] == nullptr || _values[i] == nullptr)
            {
                if (a->_values[i] != _values[i])
                    return false;
            }
            else if (!a->_values[i]->eq(_values[i]))
                return false;
        }
        else if (!vv && !avv && (unsigned long)(_values[i]) != (unsigned long)(a->_values[i]))
            return false;
    }
    return true;
}

bool Dict_Obj::neq(const Object_Obj *d) const
{
    return !eq(d);
}

std::string Dict_Obj::toString() const
{
    assert(_keys.size() == _values.size());
    std::string ret = "{";
    for (unsigned long i = 0; i < _keys.size(); i++)
    {
        if (valid_pointer(_keys[i]))
        {
            if (_keys[i] != nullptr)
                ret += _keys[i]->reprString();
            else
                ret += "None";
        }
        else
            ret += std::to_string(decode(_keys[i]));
        ret += ": ";
        if (valid_pointer(_values[i]))
        {
            if (_values[i] != nullptr)
                ret += _values[i]->reprString();
            else
                ret += "None";
        }
        else
            ret += std::to_string(decode(_values[i]));
        if (i != _keys.size() - 1)
            ret += ", ";
    }
    ret += "}";
    return ret;
}

std::ostream &Dict_Obj::print(std::ostream &os) const
{
    assert(_keys.size() == _values.size());
    os << toString();
    return os;
}

Object_Obj *Dict_Obj::copy() const
{
    return const_cast<Dict>(this);
}

Tuple0_Obj::Tuple0_Obj()
{
}

Tuple0_Obj::~Tuple0_Obj()
{
}

unsigned long Tuple0_Obj::id() const { return 7; }

bool Tuple0_Obj::eq(const Object_Obj *t) const
{
    return t != nullptr && valid_pointer(t) && t->id() == id();
}

bool Tuple0_Obj::neq(const Object_Obj *t) const
{
    return !eq(t);
}

std::string Tuple0_Obj::toString() const
{
    return "()";
}

std::ostream &Tuple0_Obj::print(std::ostream &os) const
{
    os << "()";
}

Object_Obj *Tuple0_Obj::copy() const
{
    return const_cast<Tuple0>(this);
}

Tuple1_Obj::Tuple1_Obj(Object_Obj *o1) : _1(o1)
{
}

Tuple1_Obj::~Tuple1_Obj()
{
}

unsigned long Tuple1_Obj::id() const { return 8; }

bool Tuple1_Obj::eq(const Object_Obj *t) const
{
    if (t == nullptr || !valid_pointer(t) || t->id() != id())
        return false;

    const Tuple1_Obj *a = dynamic_cast<const Tuple1_Obj *>(t);
    bool v1 = valid_pointer(_1), av1 = valid_pointer(a->_1);
    if (v1 != av1)
        return false;
    if (v1 && av1)
    {
        if (a->_1 == nullptr || _1 == nullptr)
            return a->_1 == _1;
        return _1->eq(a->_1);
    }
    else
        return (unsigned long)(_1) == (unsigned long)(a->_1);
}

bool Tuple1_Obj::neq(const Object_Obj *t) const
{
    return !eq(t);
}

std::string Tuple1_Obj::toString() const
{
    if (_1 == nullptr)
        return "(None,)";
    else if (!valid_pointer(_1))
        return "(" + std::to_string(decode(_1)) + ",)";
    return "(" + _1->reprString() + ",)";
}

std::ostream &Tuple1_Obj::print(std::ostream &os) const
{
    os << toString();
    return os;
}

Object_Obj *Tuple1_Obj::copy() const
{
    return const_cast<Tuple1>(this);
}

Tuple2_Obj::Tuple2_Obj(Object_Obj *o1, Object_Obj *o2) : _1(o1), _2(o2)
{
}

Tuple2_Obj::~Tuple2_Obj()
{
}

unsigned long Tuple2_Obj::id() const { return 9; }

bool Tuple2_Obj::eq(const Object_Obj *t) const
{
    if (t == nullptr || !valid_pointer(t) || t->id() != id())
        return false;

    const Tuple2_Obj *a = dynamic_cast<const Tuple2_Obj *>(t);
    bool av1 = valid_pointer(a->_1), v1 = valid_pointer(_1);
    bool av2 = valid_pointer(a->_2), v2 = valid_pointer(_2);
    if (av1 != v1 || av2 != v2)
        return false;
    if (av1 && v1)
    {
        if (a->_1 == nullptr || _1 == nullptr)
        {
            if (a->_1 != _1)
                return false;
        }
        else if (a->_1->neq(_1))
            return false;
    }
    else if (!av1 && !v1 && (unsigned long)(a->_1) != (unsigned long)(_1))
        return false;

    if (v2 && av2)
    {
        if (a->_2 == nullptr || _2 == nullptr)
        {
            if (a->_2 != _2)
                return false;
        }
        else if (a->_2->neq(_2))
            return false;
    }
    else if (!v2 && !av2 && (unsigned long)(a->_2) != (unsigned long)(_2))
        return false;
    return true;
}

bool Tuple2_Obj::neq(const Object_Obj *t) const
{
    return !eq(t);
}

std::string Tuple2_Obj::toString() const
{
    std::string ret = "(";
    if (_1 == nullptr)
        ret += "None";
    else if (!valid_pointer(_1))
        ret += std::to_string(decode(_1));
    else
        ret += _1->reprString();
    ret += ", ";
    if (_2 == nullptr)
        ret += "None";
    else if (!valid_pointer(_2))
        ret += std::to_string(decode(_2));
    else
        ret += _2->reprString();
    ret += ")";
    return ret;
}

std::ostream &Tuple2_Obj::print(std::ostream &os) const
{
    os << toString();
    return os;
}

Object_Obj *Tuple2_Obj::copy() const
{
    /*Object_Obj* _1_copy, * _2_copy;
    if (_1 == nullptr) _1_copy = nullptr;
    else _1_copy = _1->copy();
    if (_2 == nullptr) _2_copy = nullptr;
    else _2_copy = _2->copy();
    return new Tuple2_Obj(_1_copy, _2_copy);*/
    return const_cast<Tuple2>(this);
}

Tuple3_Obj::Tuple3_Obj(Object_Obj *o1, Object_Obj *o2, Object_Obj *o3) : _1(o1), _2(o2), _3(o3)
{
}

Tuple3_Obj::~Tuple3_Obj()
{
}

unsigned long Tuple3_Obj::id() const { return 10; }

bool Tuple3_Obj::eq(const Object_Obj *t) const
{
    if (t == nullptr || t->id() != id())
        return false;

    const Tuple3_Obj *a = dynamic_cast<const Tuple3_Obj *>(t);
    bool v1 = valid_pointer(_1), av1 = valid_pointer(a->_1);
    bool v2 = valid_pointer(_2), av2 = valid_pointer(a->_2);
    bool v3 = valid_pointer(_3), av3 = valid_pointer(a->_3);
    if (v1 != av1 || v2 != av2 || v3 != av3)
        return false;
    if (v1 && av1)
    {
        if (a->_1 == nullptr || _1 == nullptr)
        {
            if (a->_1 != _1)
                return false;
        }
        else if (a->_1->neq(_1))
            return false;
    }
    else if (!v1 && !av1 && (unsigned long)(_1) != (unsigned long)(a->_1))
        return false;

    if (av2 && v2)
    {
        if (a->_2 == nullptr || _2 == nullptr)
        {
            if (a->_2 != _2)
                return false;
        }
        else if (a->_2->neq(_2))
            return false;
    }
    else if (!v2 && !av2 && (unsigned long)(_2) != (unsigned long)(a->_2))
        return false;

    if (av3 && v3)
    {
        if (a->_3 == nullptr || _3 == nullptr)
        {
            if (a->_3 != _3)
                return false;
        }
        else if (a->_3->neq(_3))
            return false;
    }
    else if (!av3 && !v3 && (unsigned long)(_3) != (unsigned long)(a->_3))
        return false;
    return true;
}

bool Tuple3_Obj::neq(const Object_Obj *t) const
{
    return !eq(t);
}

std::string Tuple3_Obj::toString() const
{
    std::string ret = "(";
    if (_1 == nullptr)
        ret += "None";
    else if (!valid_pointer(_1))
        ret += std::to_string(decode(_1));
    else
        ret += _1->reprString();
    ret += ", ";
    if (_2 == nullptr)
        ret += "None";
    else if (!valid_pointer(_2))
        ret += std::to_string(decode(_2));
    else
        ret += _2->reprString();
    ret += ", ";
    if (_3 == nullptr)
        ret += "None";
    else if (!valid_pointer(_3))
        ret += std::to_string(decode(_3));
    else
        ret += _3->reprString();
    ret += ")";
    return ret;
}

std::ostream &Tuple3_Obj::print(std::ostream &os) const
{
    os << toString();
    return os;
}

Object_Obj *Tuple3_Obj::copy() const
{
    /*Object_Obj* _1_copy, * _2_copy, * _3_copy;
    if (_1 == nullptr) _1_copy = nullptr;
    else _1_copy = _1->copy();
    if (_2 == nullptr) _2_copy = nullptr;
    else _2_copy = _2->copy();
    if (_3 == nullptr) _3_copy = nullptr;
    else _3_copy = _3->copy();
    return new Tuple3_Obj(_1_copy, _2_copy, _3_copy);*/
    return const_cast<Tuple3>(this);
}

template <typename A, typename... Args>
bool any_nullptr(A a, Args... as)
{
    return !a || any_nullptr(as...);
}

template <typename A>
bool any_nullptr(A a)
{
    return !a;
}

Bool __truth__(Any x)
{
    if (x == nullptr)
        return encode_bool(false);
    if (!valid_pointer(x))
        return encode_bool(decode(x));
    Object o = (Object)x;
    switch (o->id())
    {
    case 1:
        return encode_bool(dynamic_cast<Str>(o)->_underlying != "");
    // case 2:
    //     return encode_bool(dynamic_cast<Int>(o)->_underlying != 0);
    case 3:
        return encode_bool(dynamic_cast<Bool>(o)->_underlying);
    case 4:
    {
        Range temp = dynamic_cast<Range>(o);
        return encode_bool(temp->done() - temp->start() > 0);
    };
    case 5:
        return encode_bool(!dynamic_cast<List>(o)->_underlying.empty());
    case 6:
        return encode_bool(!dynamic_cast<Dict>(o)->_keys.empty());
    case 7:
        return encode_bool(false);
    }
    return encode_bool(true);
}

Bool __not__(Any x)
{
    if (x == nullptr)
        return encode_bool(true);
    if (!valid_pointer(x))
        return encode_bool(!decode(x));
    Object o = (Object)x;
    switch (o->id())
    {
    case 1:
        return encode_bool(dynamic_cast<Str>(o)->_underlying == "");
    // case 2:
    //     return encode_bool(dynamic_cast<Int>(o)->_underlying == 0);
    case 3:
        return encode_bool(!dynamic_cast<Bool>(o)->_underlying);
    case 4:
    {
        Range temp = dynamic_cast<Range>(o);
        return encode_bool(temp->done() - temp->start() <= 0);
    };
    case 5:
        return encode_bool(dynamic_cast<List>(o)->_underlying.empty());
    case 6:
        return encode_bool(dynamic_cast<Dict>(o)->_keys.empty());
    case 7:
        return encode_bool(true);
    }
    return encode_bool(false);
}

Bool __true__ = encode_bool(true);
Bool __false__ = encode_bool(false);

Range __xrange__(Int low, Int high)
{
    if (valid_pointer(low) || valid_pointer(high))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }

    return new Range_Obj(decode(low), decode(high));
}

Int __len__range__(Range r)
{
    if (any_nullptr(r))
    {
        cerr << "Error: " << "range arguments expected, got NoneType.";
        exit(1);
    }
    return r->done() <= r->start() ? encode(0) : encode(r->done() - r->start());
}

Int __add__int__(Int x, Int y)
{
    if (valid_pointer(x) || valid_pointer(y))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }

    return encode(decode(x) + decode(y));
}

Int __sub__int__(Int x, Int y)
{
    if (valid_pointer(x) || valid_pointer(y))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    return encode(decode(x) - decode(y));
}

Int __mul__int__(Int x, Int y)
{
    if (valid_pointer(x) || valid_pointer(y))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    return encode(decode(x) * decode(y));
}

Int __floordiv__int__(Int x, Int y)
{
    if (valid_pointer(x) || valid_pointer(y))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    long decodeY = decode(y);
    if (decodeY == 0){
        cerr << "Error: " << "Division by zero";
        exit(1);
    }
    return encode(decode(x) / decodeY);
}

Int __mod__int__(Int x, Int y)
{
    if (valid_pointer(x) || valid_pointer(y))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    return encode(decode(x) % decode(y));
}

Int __pow__int__(Int x, Int y)
{
    if (valid_pointer(x) || valid_pointer(y))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    return encode(std::pow(decode(x), decode(y)));
}

Int __neg__int__(Int x)
{
    if (valid_pointer(x))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    return encode(-decode(x));
}

Int __pos__int__(Int x)
{
    if (valid_pointer(x))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    return encode(+decode(x));
}

enum class comp
{
    LT,
    GT,
    LTE,
    GTE,
    EQ,
    NEQ
};

template <typename A>
Bool base_compare(A a, comp op, A b)
{
    switch (op)
    {
    case comp::LT:
        return encode_bool(a < b);
    case comp::GT:
        return encode_bool(a > b);
    case comp::LTE:
        return encode_bool(a <= b);
    case comp::GTE:
        return encode_bool(a >= b);
    case comp::EQ:
        return encode_bool(a == b);
    case comp::NEQ:
        return encode_bool(a != b);
    }
}

Bool obj_compare(Str a, comp op, Str b)
{
    if (a == nullptr && b == nullptr)
        return encode_bool(op == comp::LTE || op == comp::GTE || op == comp::EQ);
    else if (a == nullptr)
        return encode_bool(op == comp::LT || op == comp::LTE || op == comp::NEQ);
    else if (b == nullptr)
        return encode_bool(op == comp::GT || op == comp::GTE || op == comp::NEQ);
    auto a_u = a->_underlying;
    auto b_u = b->_underlying;
    return base_compare(a_u, op, b_u);
}

Bool obj_compare(Int a, comp op, Int b)
{
    if (!a)
        a = encode(0);
    if (!b)
        b = encode(0);
    if (valid_pointer(a) || valid_pointer(b))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    return base_compare(a, op, b);
}

Bool __lt__int__(Int x, Int y)
{
    return obj_compare(x, comp::LT, y);
}

Bool __gt__int__(Int x, Int y)
{
    return obj_compare(x, comp::GT, y);
}

Bool __le__int__(Int x, Int y)
{
    return obj_compare(x, comp::LTE, y);
}

Bool __ge__int__(Int x, Int y)
{
    return obj_compare(x, comp::GTE, y);
}

Bool __eq__int__(Int x, Int y)
{
    return obj_compare(x, comp::EQ, y);
}

Bool __ne__int__(Int x, Int y)
{
    return obj_compare(x, comp::NEQ, y);
}

Int __toint__str__(Str x)
{
    if (any_nullptr(x))
    {
        cerr << "Error: " << "string argument expected, got NoneType.";
        exit(1);
    }
    return encode(std::stol(x->_underlying, nullptr, 0));
}

Str __add__str__(Str x, Str y)
{
    if (any_nullptr(x, y))
    {
        cerr << "Error: " << "string arguments expected, got NoneType.";
        exit(1);
    }
    return new Str_Obj(x->_underlying + y->_underlying);
}

Str __lmul__str__(Str x, Int y)
{
    if (any_nullptr(x))
    {
        cerr << "Error: " << "string and integer arguments expected, got NoneType.";
        exit(1);
    }
    if (valid_pointer(y))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    std::string ret;
    for (int i = 0; i < decode(y); i++)
        ret += x->_underlying;
    return new Str_Obj(ret);
}

Str __rmul__str__(Int x, Str y)
{
    if (any_nullptr(y))
    {
        cerr << "Error: " << "integer and string arguments expected, got NoneType.";
        exit(1);
    }
    if (valid_pointer(x))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    std::string ret;
    for (int i = 0; i < decode(x); i++)
        ret += y->_underlying;
    return new Str_Obj(ret);
}

Bool __lt__str__(Str x, Str y)
{
    return obj_compare(x, comp::LT, y);
}

Bool __gt__str__(Str x, Str y)
{
    return obj_compare(x, comp::GT, y);
}

Bool __le__str__(Str x, Str y)
{
    return obj_compare(x, comp::LTE, y);
}

Bool __ge__str__(Str x, Str y)
{
    return obj_compare(x, comp::GTE, y);
}

Bool __eq__str__(Str x, Str y)
{
    return obj_compare(x, comp::EQ, y);
}

Bool __ne__str__(Str x, Str y)
{
    return obj_compare(x, comp::NEQ, y);
}

auto bound = [](long i, long l, long u) { if (i >= u) i = u; if (i <= l) i = l; return i; };

Str __getitem__str__(Str S, Int k)
{
    if (any_nullptr(S))
    {
        cerr << "Error: " << "string and integer arguments expected, got NoneType.";
        exit(1);
    }
    if (valid_pointer(k))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    long index = decode(k), sz = S->_underlying.length();
    if (index < -sz || index >= sz)
    {
        cerr << "Error: " << "Index out of bounds.";
        exit(1);
    }
    std::string::iterator it;
    if (index < 0)
        it = S->_underlying.end() + index;
    else
        it = S->_underlying.begin() + index;
    return new Str_Obj(std::string(1, *it));
}

Str __getslice__str__(Str S, Int L, Int U)
{
    if (any_nullptr(S))
    {
        cerr << "Error: " << "string and integer arguments expected, got NoneType.";
        exit(1);
    }
    if (valid_pointer(L) || valid_pointer(U))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    long lower_index = decode(L), upper_index = decode(U);
    long start_index = bound(lower_index, -S->_underlying.length(), S->_underlying.length()),
         end_index = bound(upper_index, -S->_underlying.length(), S->_underlying.length());
    std::string::iterator start_it, end_it;
    if (start_index < 0)
        start_it = S->_underlying.end() + start_index;
    else
        start_it = S->_underlying.begin() + start_index;
    if (end_index < 0)
        end_it = S->_underlying.end() + end_index;
    else
        end_it = S->_underlying.begin() + end_index;
    if (start_it >= end_it)
        return new Str_Obj("");
    return new Str_Obj(std::string(start_it, end_it));
}

Int __len__str__(Str S)
{
    if (any_nullptr(S))
    {
        cerr << "Error: " << "string argument expected, got NoneType.";
        exit(1);
    }
    return encode(S->_underlying.length());
}

Str __toStr__(Any x)
{
    if (x == nullptr)
        return new Str_Obj("None");
    if (!valid_pointer(x)) {
        if(is_int(x))
            return new Str_Obj(std::to_string(decode(x)));
        else
            return new Str_Obj(std::string(decode(x) ? "True" : "False"));
    }
    Object o = (Object)x;
    return new Str_Obj(o->toString());
}

Any __getitem__list__(List S, Int k)
{
    if (any_nullptr(S))
    {
        cerr << "Error: " << "list and integer arguments expected, got NoneType.";
        exit(1);
    }
    if (valid_pointer(k))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    long index = decode(k), sz = S->_underlying.size();
    if (index < -sz || index >= sz)
    {
        cerr << "Error: " << "Index out of bounds.";
        exit(1);
    }
    std::vector<Object>::iterator it;
    if (index < 0)
        it = S->_underlying.end() + index;
    else
        it = S->_underlying.begin() + index;
    if (*it == nullptr)
        return nullptr;
    else if (valid_pointer(*it))
        return (*it)->copy();
    else
        return encode(*it);
}

List __getslice__list__(List S, Int L, Int U)
{
    if (any_nullptr(S))
    {
        cerr << "Error: " << "list and integer arguments expected, got NoneType.";
        exit(1);
    }
    if (valid_pointer(L) || valid_pointer(U))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    long lower_index = decode(L), upper_index = decode(U);
    long start_index = bound(lower_index, -S->_underlying.size(), S->_underlying.size()),
         end_index = bound(upper_index, -S->_underlying.size(), S->_underlying.size());
    std::vector<Object>::iterator start_it, end_it;
    if (start_index < 0)
        start_it = S->_underlying.end() + start_index;
    else
        start_it = S->_underlying.begin() + start_index;
    if (end_index < 0)
        end_it = S->_underlying.end() + end_index;
    else
        end_it = S->_underlying.begin() + end_index;
    if (start_it >= end_it)
        return new List_Obj(std::vector<Object>{});
    std::vector<Object_Obj *> os;
    for (auto iter = start_it; iter < end_it; iter++)
    {
        if (*iter == nullptr)
            os.push_back(nullptr);
        else if (valid_pointer(*iter))
            os.push_back((*iter)->copy());
        else
            os.push_back(encode(*iter));
    }
    return new List_Obj(os);
}

Any __setitem__list__(List S, Int k, Any val)
{
    if (any_nullptr(S))
    {
        cerr << "Error: " << "list and integer arguments expected, got NoneType.";
        exit(1);
    }
    if (valid_pointer(k))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    long index = decode(k), sz = S->_underlying.size();
    if (index < -sz || index >= sz)
    {
        cerr << "Error: " << "Index out of bounds.";
        exit(1);
    }
    std::vector<Object>::iterator it;
    if (index < 0)
        it = S->_underlying.end() + index;
    else
        it = S->_underlying.begin() + index;
    Object tmp = (Object)val;
    if (tmp == nullptr)
        *it = nullptr;
    else if (valid_pointer(tmp))
        *it = tmp->copy();
    else
        *it = encode(tmp);

    if (valid_pointer(*it))
        return (*it)->copy();
    else
        return encode(*it);
}

List __setslice__list__(List S, Int a, Int b, List val)
{
    if (any_nullptr(S, val))
    {
        cerr << "Error: " << "list and integer arguments expected, got NoneType.";
        exit(1);
    }
    if (valid_pointer(a) || valid_pointer(b))
    {
        cerr << "Error: " << "invalid integer.";
        exit(1);
    }
    long start_index = decode(a), end_index = decode(b);
    std::vector<Object_Obj *> os, os_copy;
    long bounded_a = bound(start_index, -S->_underlying.size(), S->_underlying.size()),
         bounded_b = bound(end_index, -S->_underlying.size(), S->_underlying.size());
    for (unsigned long l = 0; l < val->_underlying.size(); l++)
    {
        Object_Obj *tmp;
        if (valid_pointer(val->_underlying[l]))
            tmp = val->_underlying[l]->copy();
        else
            tmp = encode(val->_underlying[l]);
        os.push_back(tmp);
    }
    std::vector<Object>::iterator s, e;
    s = bounded_a < 0 ? S->_underlying.end() + bounded_a : S->_underlying.begin() + bounded_a;
    e = bounded_b < 0 ? S->_underlying.end() + bounded_b : S->_underlying.begin() + bounded_b;
    long slice_length = 0;
    if (e >= s)
        slice_length = e - s;
    if (slice_length == 0)
        S->_underlying.insert(s, os.begin(), os.end());
    else
    {
        if (slice_length >= val->_underlying.size())
        {
            S->_underlying.erase(s, e);
            S->_underlying.insert(s, os.begin(), os.end());
        }
        else
        {
            unsigned long copied = 0;
            for (auto iter = s; iter < e; iter++, copied++)
                *iter = os[copied];
            S->_underlying.insert(e, os.begin() + copied, os.end());
        }
    }
    for (auto &o : os)
    {
        if (valid_pointer(o))
            os_copy.push_back(o == nullptr ? o : o->copy());
        else
            os_copy.push_back(encode(o));
    }
    return new List_Obj(os_copy);
}

int prog_argc;
char **prog_argv;
std::vector<Object> and_or_scratch;
std::vector<Object> tuple_assign_scratch;
std::vector<LeftCompareData *> left_compare_scratch;

Int __len__list__(List S)
{
    if (any_nullptr(S))
    {
        cerr << "Error: " << "list argument expected, got NoneType.";
        exit(1);
    }
    return encode(S->_underlying.size());
}

List __argv__()
{
    std::vector<Object_Obj *> os;
    for (int i = 0; i < prog_argc; i++)
        os.push_back(new Str_Obj(prog_argv[i]));
    return new List_Obj(os);
}

Str __readline__()
{
    std::string ret;
    std::getline(std::cin, ret);
    return new Str_Obj(ret);
}

Str __read__()
{
    std::string ret;
    for (std::string line; std::getline(std::cin, line);)
        ret += line;
    return new Str_Obj(ret);
}

template <typename T>
static Any dict_get_item_helper(Dict D, T x)
{
    assert(D->_keys.size() == D->_values.size());
    for (unsigned long i = 0; i < D->_keys.size(); i++)
    {
        bool Dk_valid = valid_pointer(D->_keys[i]), x_valid = valid_pointer(x);
        if ((Dk_valid && x_valid && ((!D->_keys[i] && !x) || D->_keys[i]->eq((Object)x))) || (!Dk_valid && !x_valid && (unsigned long)(D->_keys[i]) == (unsigned long)(x)))
        {
            Object_Obj *tmp = D->_values[i];
            if (valid_pointer(tmp))
            {
                if (tmp == nullptr)
                    return nullptr;
                else
                    return tmp->copy();
            }
            else
                return encode(tmp);
        }
    }
    cerr << "Error: " << "key not found in dictionary";
    exit(1);
}

template <typename T>
static Any dict_set_item_helper(Dict D, T x, Any val)
{
    assert(D->_keys.size() == D->_values.size());
    for (unsigned long i = 0; i < D->_keys.size(); i++)
    {
        bool Dk_valid = valid_pointer(D->_keys[i]), x_valid = valid_pointer(x);
        if ((Dk_valid && x_valid && ((!D->_keys[i] && !x) || D->_keys[i]->eq((Object)x))) || (!Dk_valid && !x_valid && (unsigned long)(D->_keys[i]) == (unsigned long)(x)))
        {
            Object_Obj *ret;
            if (valid_pointer(val))
            {
                Object_Obj *tmp = (Object)val;
                if (tmp == nullptr)
                    D->_values[i] = ret = nullptr;
                else
                    D->_values[i] = tmp->copy(), ret = D->_values[i]->copy();
            }
            else
                D->_values[i] = ret = encode(val);
            return ret;
        }
    }
    if (valid_pointer(x))
    {
        if (!x)
            D->_keys.push_back(nullptr);
        else
            D->_keys.push_back(((Object)x)->copy());
    }
    else
        D->_keys.push_back((Object)encode(x));
    if (valid_pointer(val))
    {
        Object_Obj *tmp = (Object)val;
        if (tmp == nullptr)
            D->_values.push_back(nullptr);
        else
            D->_values.push_back(tmp->copy());
    }
    else
        D->_values.push_back(encode(val));
}

static Int dict_len_helper(Dict D)
{
    assert(D->_keys.size() == D->_values.size());
    return encode(D->_keys.size());
}

template <typename T>
static Bool dict_contains_helper(T x, Dict D)
{
    assert(D->_keys.size() == D->_values.size());
    for (unsigned long i = 0; i < D->_keys.size(); i++)
    {
        bool Dk_valid = valid_pointer(D->_keys[i]), x_valid = valid_pointer(x);
        if ((Dk_valid && x_valid && ((!D->_keys[i] && !x) || D->_keys[i]->eq((Object)x))) || (!Dk_valid && !x_valid && (unsigned long)(D->_keys[i]) == (unsigned long)(x)))
            return encode_bool(1);
    }
    return encode_bool(0);
}

template <typename T>
static Bool dict_notcontains_helper(T x, Dict D)
{
    assert(D->_keys.size() == D->_values.size());
    for (unsigned long i = 0; i < D->_keys.size(); i++)
    {
        bool Dk_valid = valid_pointer(D->_keys[i]), x_valid = valid_pointer(x);
        if ((Dk_valid && x_valid && ((!D->_keys[i] && !x) || D->_keys[i]->eq((Object)x))) || (!Dk_valid && !x_valid && (unsigned long)(D->_keys[i]) == (unsigned long)(x)))
            return encode_bool(0);
    }
    return encode_bool(1);
}

Any __getitem__dict__int__(Dict D, Int x)
{
    if (any_nullptr(D))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_get_item_helper(D, x);
}

Any __getitem__dict__bool__(Dict D, Bool x)
{
    if (any_nullptr(D))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_get_item_helper(D, x);
}

Any __getitem__dict__str__(Dict D, Str x)
{
    if (any_nullptr(D))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_get_item_helper(D, x);
}

Any __setitem__dict__int__(Dict S, Int k, Any val)
{
    if (any_nullptr(S))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_set_item_helper(S, k, val);
}

Any __setitem__dict__bool__(Dict S, Bool k, Any val)
{
    if (any_nullptr(S))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_set_item_helper(S, k, val);
}

Any __setitem__dict__str__(Dict S, Str k, Any val)
{
    if (any_nullptr(S))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_set_item_helper(S, k, val);
}

Int __len__dict__int__(Dict D)
{
    if (any_nullptr(D))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_len_helper(D);
}

Int __len__dict__bool__(Dict D)
{
    if (any_nullptr(D))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_len_helper(D);
}

Int __len__dict__str__(Dict D)
{
    if (any_nullptr(D))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_len_helper(D);
}

Bool __contains__dict__int__(Int x, Dict D)
{
    if (any_nullptr(D))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_contains_helper(x, D);
}

Bool __contains__dict__bool__(Bool x, Dict D)
{
    if (any_nullptr(D))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_contains_helper(x, D);
}

Bool __contains__dict__str__(Str x, Dict D)
{
    if (any_nullptr(D))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_contains_helper(x, D);
}

Bool __notcontains__dict__int__(Int x, Dict D)
{
    if (any_nullptr(D))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_notcontains_helper(x, D);
}

Bool __notcontains__dict__bool__(Bool x, Dict D)
{
    if (any_nullptr(D))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_notcontains_helper(x, D);
}

Bool __notcontains__dict__str__(Str x, Dict D)
{
    if (any_nullptr(D))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return dict_notcontains_helper(x, D);
}

Bool __is__(Any x, Any y)
{
    if (!valid_pointer(x) || !valid_pointer(y))
        return encode_bool((unsigned long)(x) == (unsigned long)(y));
    Object ox = (Object)x;
    Object oy = (Object)y;
    if (ox == nullptr || oy == nullptr)
        return encode_bool(ox == oy);
    switch (ox->id())
    {
    case 1:
    //case 2:
    case 3:
        return encode_bool(ox->eq(oy));
    default:
        return encode_bool(x == y);
    }
    assert("this should be unreachable");
}

Bool __isnot__(Any x, Any y)
{
    if (!valid_pointer(x) || !valid_pointer(y))
        return encode_bool((unsigned long)(x) != (unsigned long)(y));
    Object ox = (Object)x;
    Object oy = (Object)y;
    if (ox == nullptr || oy == nullptr)
        return encode_bool(ox != oy);
    switch (ox->id())
    {
    case 1:
    //case 2:
    case 3:
        return encode_bool(ox->neq(oy));
    default:
        return encode_bool(x != y);
    }
    assert("this should be unreachable.");
}

Any __gc__()
{
    return nullptr;
}

List __createList__(std::vector<Object> values)
{
    std::vector<Object> objs;
    for (auto &c : values)
    {
        if (valid_pointer(c))
        {
            if (c == nullptr)
                objs.push_back(nullptr);
            else
                objs.push_back(c->copy());
        }
        else
            objs.push_back(encode(c));
    }
    return new List_Obj(objs);
}

Dict __createDict__(std::vector<Object> kvs)
{
    assert(kvs.size() % 2 == 0);
    std::vector<Object> keys, values;
    Dict D = new Dict_Obj(keys, values);
    for (unsigned long l = 0; l < kvs.size(); l += 2)
        dict_set_item_helper(D, kvs[l], kvs[l + 1]);
    return D;
}

Object __choose__list__(List l)
{
    if (any_nullptr(l))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    if (l->_cnt >= l->_underlying.size())
        return l->_cnt = 0, new Object_Obj();
    else
    {
        unsigned int ind = l->_cnt++;
        if (valid_pointer(l->_underlying[ind]))
            return l->_underlying[ind]->copy();
        else
            return encode(l->_underlying[ind]);
    }
}

Int __choose__list__(Range r) {
    if (any_nullptr(r))  {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return r->_cnt >= r->done() ? (r->_cnt = r->start(), nullptr)
        : encode(r->_cnt++);
}

Object __choose__dict__(Dict d)
{
    if (any_nullptr(d))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    if (d->_cnt >= d->_keys.size())
        return d->_cnt = 0, new Object_Obj();
    else
    {
        unsigned int ind = d->_cnt++;
        if (valid_pointer(d->_keys[ind]))
            return d->_keys[ind]->copy();
        else
            return encode(d->_keys[ind]);
    }
}

Str __choose__str__(Str s)
{
    if (any_nullptr(s))
    {
        cerr << "Error: " << "Got NoneType argument.";
        exit(1);
    }
    return s->_cnt >= s->_underlying.length() ? (s->_cnt = 0, nullptr)
                                              : new Str_Obj(std::string(1, s->_underlying[s->_cnt++]));
}

Object object_copy(Object u)
{
    if (valid_pointer(u))
        return u->copy();
    else
        return encode(u);
}

static std::string lastPrinted = "";
static bool firstTime = true;

void print(bool disable, std::string to_print) {
    if(disable || firstTime || (lastPrinted.length() > 0 && *(lastPrinted.end() - 1) == '\n'))
        std::cout << to_print;
    else
        std::cout << ' ' << to_print;
    firstTime = false;
    lastPrinted = to_print;
}
