//  Declarations for an calculator that builds an AST
//  and a graphical representation of the AST.
//  by Brian Malloy
#ifndef _ASTHEAD_H_
#define _ASTHEAD_H_
#include <string>
#include <map>
#include <cstdlib>
#include <fstream>
extern std::map<char*, int> table;
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

// insert

class IdentNode : public Node {
public:
  IdentNode(char* n) : Node(), Ident(n) {} 
  virtual ~IdentNode() {}
  virtual double eval() const ;
  char* getIdent()const {return Ident;}
private:
  char* Ident;
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

// assign node 
class AssignNode : public BinaryNode {
public:
  AssignNode(Node* l, Node* r) : BinaryNode(left, right) { }
  virtual double eval() const;
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

#endif
