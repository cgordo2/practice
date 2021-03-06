//  Declarations for an AST calculator
//  From "flex & bison", fb3-1, by John Levine
//  Adapted by Brian Malloy

#include <string>
extern void yyerror(const char*);
extern void yyerror(const char*, const char);

class Ast {
public:
  Ast(int n) : nodetype(n) {}
  virtual ~Ast() {}
  char getNodetype() const { return nodetype; }
  virtual Ast* getLeft() const { throw std::string("No Left"); }
  virtual Ast* getRight() const { throw std::string("No Right"); }
  virtual double getNumber() const { throw std::string("No Number"); }
private:
  char nodetype;
};

class AstNode : public Ast {
public:
  AstNode(char nodetype, Ast* l, Ast* r) : 
    Ast(nodetype), left(l), right(r) 
  {}
  virtual ~AstNode() {}
  virtual Ast* getLeft() const  { return left; }
  virtual Ast* getRight() const { return right; }
private:
  Ast *left;
  Ast *right;
};

class AstNumber : public Ast {
public:
  AstNumber(char nodetype, double n) : Ast(nodetype), number(n) {} 
  virtual ~AstNumber() {}
  virtual double getNumber() const { return number; }
private:
  double number;
};

double eval(Ast*);   // Evaluate an AST
void treeFree(Ast*); // delete and free an AST 

