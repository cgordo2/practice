//  Declarations for an AST calculator
//  From "flex & bison", fb3-1, by John Levine

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
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


Ast(char n) : id(setid()),nodetype(n) { } 
  virtual ~Ast() {}
  virtual char getNodetype() const {   return nodetype; }
  virtual Ast* getLeft() const { return 0; }
  virtual Ast* getRight() const {return 0; }
  // added
  virtual Ast* getstmt() const {return 0;}
  virtual Ast* getparm() const {return 0;}
  virtual Ast* getiff() const {return 0;}
  virtual Ast* getthen() const {return 0;}
  virtual Ast* getelse1() const {return 0;}
 //virtual float getFloat() const {throw std::string("No Float");}
  // end added
  virtual double getNumber() const { throw std::string("No Number"); }
  virtual std::string getIdent() const { throw std::string("No Ident");}
  virtual int getId() { return id; }
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
/*
// added FLOAT
class AstFloat : public Ast {
public:
  AstFloat(char nodetype, float f) : Ast(nodetype), flo(f) {} 
  virtual ~AstFloat() {}
  virtual float getFloat() const { return flo; }
private:
  float flo;
};
// end FLOAT
*/
class AstIdent : public Ast {
public:
  AstIdent(char nodetype, char* n) : Ast(nodetype), ident(n) {} 
  virtual ~AstIdent() {}
  virtual std::string getIdent() const { return ident; }
private:
  char* ident;
};

class AstAssign : public Ast {
public:
  AstAssign(char nodetype, char* n, Ast* l) : Ast(nodetype), ident(new char[strlen(n)+1] ), left(l)
  {
    strcpy(ident, n);
  } 
  virtual ~AstAssign() {}
  virtual std::string getIdent() const { return ident; }
  virtual Ast* getLeft() const { return left; }
private:
  char* ident;
  Ast *left;
};

class AstPrint : public Ast {
public:
  AstPrint(char nodetype, Ast* l) : Ast(nodetype), left(l) {} 
  virtual ~AstPrint() {}
  virtual Ast* getLeft() const { return left; }
private:
  Ast *left;
};

class AstStmt : public Ast {
public:
  AstStmt(char nodetype, Ast* l) : Ast(nodetype), left(l) {} 
  virtual ~AstStmt() {}
  virtual Ast* getLeft() const { return left; }
private:
  Ast *left;
};
// inssert here 
class AstStart : public Ast {
public:
  AstStart(char nodetype, Ast* l) : Ast(nodetype), left(l) {} 
  virtual ~AstStart() {}
  virtual Ast* getLeft() const { return left; }
private:
  Ast *left;
};

class AstFuncdef : public Ast {
public:
  AstFuncdef(char nodetype, char* i , Ast* p , Ast* s) : Ast(nodetype), ident(i), parm(p), stmt(s) {} 
  virtual ~AstFuncdef() {}
  // added 
  virtual std::string getIdent() const { return ident; }
  virtual Ast* getparm() const { return parm; }
  virtual Ast* getstmt() const { return stmt; }
  // end added 
private:
  char *ident;
  Ast *parm;
  Ast *stmt;
};
// added for main

// end added for main 
class AstParm : public Ast {
public:
  AstParm(char nodetype, Ast* l ,Ast* r) : Ast(nodetype), left(l) ,right(r){} 
  virtual ~AstParm() {}
  virtual Ast* getLeft() const { return left; }
  virtual Ast* getRight() const {return right;}
private:
  Ast *left;
  Ast *right;
};

class AstExpress : public Ast {
public:
  AstExpress(char nodetype, Ast* l) : Ast(nodetype), left(l) {} 
  virtual ~AstExpress() {}
  virtual Ast* getLeft() const { return left; }
private:
  Ast *left;
};

class AstSelect : public Ast {
public:
  AstSelect(char nodetype, Ast* l ,Ast* r) : Ast(nodetype), left(l), right(r) {} 
  virtual ~AstSelect() {}
  virtual Ast* getLeft() const { return left; }
  virtual Ast* getRight() const {return right;}
private:
  Ast *left;
  Ast *right;
};

class AstIf : public Ast {
public:
  AstIf(char nodetype, Ast* l, Ast* r) : Ast(nodetype), left(l), right(r) {} 
  virtual ~AstIf() {}
  virtual Ast* getLeft() const { return left; }
  virtual Ast* getRight() const {return right;}
private:
  Ast *left;
  Ast *right;
};

class AstElse : public Ast {
public:
  AstElse(char nodetype,Ast* i, Ast* t, Ast* e ) : Ast(nodetype), iff(i), then(t), else1(e)  {} 
  virtual ~AstElse() {}
  // added 
  virtual Ast* getiff() const { return iff; }
  virtual Ast* getthen() const { return then; }
  virtual Ast* getelse1() const { return else1; }
 // end added 
  
private:
  Ast *iff;
  Ast *then;
  Ast *else1;
};

class AstFunc : public Ast {
public:
  AstFunc(char nodetype, char* i, Ast* l ) : Ast(nodetype), ident(i), left(l) {} 
  virtual ~AstFunc() {}
  virtual Ast* getLeft() const { return left; }
  virtual std::string getIdent() const {return ident;}
private:
  char *ident;
  Ast *left;
};
double eval(Ast*);   // Evaluate an AST
void treeFree(Ast*); // delete and free an AST 
void makeGraph(const Ast* , std::fstream& ) ;
int  makeGraph();

