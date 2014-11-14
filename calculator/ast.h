//  Declarations for an AST calculator
//  From "flex & bison", fb3-1, by John Levine
//  Adapted by Brian Malloy

#include <string>
#include <iostream>
#include <fstream>
extern void yyerror(const char*);
extern void yyerror(const char*, const char);

class Ast {
public:

int getid() const{return id;}
int setid()
{
static int idcount = 0; // static counter for the id
return idcount++;
}  


Ast(int n) : id(setid()),nodetype(n) {} 
  virtual ~Ast() {}
  char getNodetype() const { return nodetype; }
  virtual Ast* getLeft() const { return 0; }
  virtual Ast* getRight() const {return 0; }
  virtual double getNumber() const { throw std::string("No Number"); }
private:
  int id;
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
void makeGraph(const Ast* , std::fstream& ) ;
int  makeGraph();

