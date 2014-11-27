//  Declarations for an calculator that builds an AST
//  and a graphical representation of the AST.
//  by Brian Malloy
#ifndef _ASTHEAD_H_
#define _ASTHEAD_H_
#include <string>
#include <map>
#include <cstdlib>
#include <fstream>

extern void yyerror(const char*);
extern void yyerror(const char*, const char);

class Node {
public:
  Node() : id(++idCount) {}
  virtual ~Node() {}
  virtual double eval() const = 0;
  int getId() const { return id; }
  virtual char* getIdent(){return NULL;}
private:

  int id;
  static int idCount;
};

class NumberNode : public Node {
public:
  NumberNode(double n) : Node(), number(n) {} 
  virtual ~NumberNode() {}
  virtual double eval() const {return number; }
private:
  double number;
};

class BinaryNode : public Node {
public:
  BinaryNode(Node* l, Node* r) : Node(), left(l), right(r) {}
  virtual ~BinaryNode();
  virtual double eval() const = 0;
protected:
  Node *left;
  Node *right;
};

class UnaryMinusNode : public Node {
public:
  UnaryMinusNode(Node* expr) : Node(), node(expr) { }
  ~UnaryMinusNode() { delete node; }
  virtual double eval() const { return -node->eval(); }
protected:
  Node *node;
};

class AddBinaryNode : public BinaryNode {
public:
  AddBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual double eval() const;
};

class SubBinaryNode : public BinaryNode {
public:
  SubBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }

  virtual double eval() const;
};

class MulBinaryNode : public BinaryNode {
public:
  MulBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual double eval() const;
};

class DivBinaryNode : public BinaryNode {
public:
  DivBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual double eval() const;
};

class ModBinaryNode : public BinaryNode {
public:
  ModBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual double eval() const;
};

class ExpBinaryNode : public BinaryNode {
public:
  ExpBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual double eval() const;
};

// insert code here ..........................................

class LessBinaryNode : public BinaryNode {
public:
  LessBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual double eval() const;
};

class LessEQBinaryNode : public BinaryNode {
public:
  LessEQBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual double eval() const;
};

class GreatBinaryNode : public BinaryNode {
public:
  GreatBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual double eval() const;
};

class GreatEQBinaryNode : public BinaryNode {
public:
  GreatEQBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual double eval() const;
};

class EQBinaryNode : public BinaryNode {
public:
  EQBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual double eval() const;
};

class NotEQBinaryNode : public BinaryNode {
public:
  NotEQBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual double eval() const;
};

// ....... insert code ..............

class IdentNode : public Node {
public:
  IdentNode(char* n) : Node(), Ident(n) {} 
  virtual ~IdentNode() {}
  virtual double eval() const ;
  char* getIdent()const {return Ident;}
private:
  char* Ident;
};

class AssignNode : public BinaryNode {
public:
  AssignNode(Node* l, Node* r) : BinaryNode(l, r) { }
  virtual double eval() const;

};

class PrintNode : public Node {
public:
  PrintNode(Node* l) : Node(), left(l) { }
  ~PrintNode() { }
  virtual double eval() const;
protected:
  Node *left;

};

class SelectNode : public Node {
public:
  SelectNode(Node* l, Node* r) : Node(), left(l), right(r) { }
  ~SelectNode() {}
  virtual double eval() const;
protected:
  Node *left;
  Node *right;
};

class SelectionNode : public Node {
public:
  //SelectionNode(Node* l, Node* r) : BinaryNode(l, r) { }
  SelectionNode(Node* l, Node* r ) : Node(), left(l) ,right(r) { }
  ~SelectionNode() {}
  virtual double eval() const;
protected:
  Node *left;
  Node *right;

};

class StmtNode : public Node {
public:
  StmtNode(Node* l) : Node(), left(l) { }
  ~StmtNode() { }
  virtual double eval() const;
protected:
  Node *left;

};

class IfNode : public Node {
public:
  IfNode(Node* l, Node* r ) : Node(), left(l) ,right(r) { }
  ~IfNode() { }
  virtual double eval() const;
protected:
  Node *left;
  Node *right;

};

class ElseNode : public Node {
public:
  ElseNode(Node* i, Node* t , Node* e ) : Node(), if_1(i), then(t), else_1(e)  { }
  ~ElseNode() { }
  virtual double eval() const;
protected:
  Node *if_1;
  Node *then;
  Node *else_1;

};

class FuncNode : public Node {
public:
  FuncNode(char* l, Node* r ) : Node(), Ident(l) ,right(r) { }
  ~FuncNode() { }
  virtual double eval() const;
protected:
  char *Ident;
  Node *right;

};

class ExpressNode : public Node {
public:
  ExpressNode(Node* l) : Node(), left(l) {}
  ~ExpressNode() {}
  virtual double eval() const;
protected:
  Node *left;
};

class ParmNode : public Node {
public:
  ParmNode(Node* l, Node* r) : Node(), left(l) , right(r) {}
  ~ParmNode() {}
  virtual double eval() const;
protected:
  Node *left;
  Node *right;
};



class FuncdefNode : public Node {
public:
  FuncdefNode(char* i, Node* p , Node* s ) : Node(), Ident(i), param(p), stmt(s)  { }
  ~FuncdefNode() { }
  virtual double eval() const;
protected:
  char *Ident;
  Node *param;
  Node *stmt;

};

class StartNode : public Node {
public:
  StartNode(Node* l) : Node(), left(l) {}
  ~StartNode() {}
  virtual double eval() const;
protected:
  Node *left;
};

#endif
