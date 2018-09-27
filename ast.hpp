#ifndef _AST_HPP_
#define _AST_HPP_

#include <vector>
#include <string>
#include <iostream>
#include "type.hpp"

using namespace std;

class ExprAST {
public:
  virtual ~ExprAST();
  virtual Type *typecheck() const = 0;
};

class ConstantExprAST : public ExprAST {
public:
    ConstantExprAST(Type* t) 
    : _t(t) 
    {}
    ~ConstantExprAST();
    Type *typecheck() const;

  private:
    Type* _t;
};

class VariableExprAST : public ExprAST {
public:
    VariableExprAST(string name) 
    : _name(name)
    {}
    Type *typecheck() const;

  private:
    string _name;
};

class InnerExprAST : public ExprAST {
public:
    InnerExprAST(ExprAST* e1);
    InnerExprAST(ExprAST *e1, ExprAST *e2);
    InnerExprAST(ExprAST *e1, ExprAST *e2, ExprAST *e3);
    InnerExprAST(vector<ExprAST *> v)
        : _v(v)
    {}
    ~InnerExprAST();

  protected:
    vector<ExprAST*> _v;
};

class AddExprAST : public InnerExprAST {
public:
    AddExprAST(ExprAST* e1, ExprAST* e2) 
    : InnerExprAST(e1, e2) 
    {}
    Type *typecheck() const;
};

class SubExprAST : public InnerExprAST {
public:
    SubExprAST(ExprAST* e1, ExprAST* e2) 
    : InnerExprAST(e1, e2) 
    {}
    Type *typecheck() const;
};

class MulExprAST : public InnerExprAST {
public:
    MulExprAST(ExprAST* e1, ExprAST* e2) 
    : InnerExprAST(e1, e2) 
    {}
    Type *typecheck() const;
};

class DivExprAST : public InnerExprAST {
public:
    DivExprAST(ExprAST* e1, ExprAST* e2) 
    : InnerExprAST(e1, e2) 
    {}
    Type *typecheck() const;
};

class AssignExprAST : public InnerExprAST
{
  public:
    AssignExprAST(string s, ExprAST *e, Type *t)
        : InnerExprAST(e), _s(s), _t(t)
    {}
    Type *typecheck() const;

  private:
    string _s;
    Type *_t;
};

class PredefineExprAST : public InnerExprAST {
  public:
    PredefineExprAST(string s, ExprAST *e)
        : InnerExprAST(e), _s(s)
    {}
    Type *typecheck() const;

  private:
    string _s;
};

class PredefineArrayExprAST : public InnerExprAST {
public:
    PredefineArrayExprAST(string s, ExprAST *e1, ExprAST *e2)
        : InnerExprAST(e1, e2), _s(s)
    {}
    Type* typecheck() const;
private:
    string _s;
};

class ElementOfArrayExprAST : public InnerExprAST {
public:
    ElementOfArrayExprAST(string s, ExprAST* e) 
        : InnerExprAST(e), _s(s)
    {}
    Type* typecheck() const;
private:
    string _s;
};

class SeqExprAST : public InnerExprAST {
public:
    SeqExprAST(ExprAST* e1, ExprAST* e2)
        : InnerExprAST(e1, e2)
    {}
    Type* typecheck() const;
};


/* odavde su dodate klase */

class Field {
public:
    Field(Type* t, string name) 
    : _t(t), _name(name)
    {}
private:
    Type* _t;
    string _name;
};

class Constructor : public InnerExprAST {
public:
    Constructor(string name, vector < pair < Type*, string > > arrayArg, ExprAST* body)  
    : InnerExprAST(body), _name(name), _arrayArg(arrayArg)
    {}
    Type* typecheck() const;
    string getName();
private:
    string _name;
    vector < pair < Type*, string > > _arrayArg;
};

class Method : public InnerExprAST {
public:
    Method(Type* retType, string name, vector < pair < Type*, string> > arrayArg, ExprAST* body, ExprAST* retInstruction) 
    : InnerExprAST(body, retInstruction), _retType(retType) , _name(name), _arrayArg(arrayArg) 
    {}
    Type* typecheck() const;
private:
    Type* _retType;
    string _name;
    vector < pair < Type*, string > > _arrayArg;
};

class Class {
public:
<<<<<<< HEAD
    Class(string name, vector < Field* > fields, Constructor *constructor, vector < Method*> methods)
=======
    Class(string name, vector < Field* > fields, Constructor constructor, vector < Method*> methods)
>>>>>>> c21f709d39009fe0eb9ae919c240a1d90e9aca4f
    : _name(name), _fields(fields), _constructor(constructor), _methods(methods)
    {}
public:
    string _name;
    vector<Field*> _fields;
<<<<<<< HEAD
    Constructor *_constructor;
=======
    Constructor _constructor;
>>>>>>> c21f709d39009fe0eb9ae919c240a1d90e9aca4f
    vector<Method*> _methods;
};

class EmptyAST : public ExprAST {
public:
    EmptyAST()
    {}
    Type* typecheck() const;
};

#endif