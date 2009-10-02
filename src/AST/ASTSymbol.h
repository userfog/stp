// -*- c++ -*-
/********************************************************************
 * AUTHORS: Vijay Ganesh
 *
 * BEGIN DATE: November, 2005
 *
 * LICENSE: Please view LICENSE file in the home dir of this Program
 ********************************************************************/

#ifndef ASTSYMBOL_H
#define ASTSYMBOL_H
namespace BEEV
{
  /******************************************************************
   *  Class ASTSymbol:                                              *
   *                                                                *
   *  Class to represent internals of Symbol node.                  *
   ******************************************************************/
  class ASTSymbol: public ASTInternal
  {
    friend class BeevMgr;
    friend class ASTNode;
    friend class ASTNodeHasher;
    friend class ASTNodeEqual;

  private:
    /****************************************************************
     * Private Data                                                 *
     ****************************************************************/

    // The name of the symbol
    const char * const _name;

    /****************************************************************
     * Class ASTSymbolHasher:                                       *
     *                                                              *
     * Hasher for ASTSymbol nodes                                   *
     ****************************************************************/
    class ASTSymbolHasher
    {
    public:
      size_t operator()(const ASTSymbol *sym_ptr) const
      {
#ifdef TR1_UNORDERED_MAP
        tr1::hash<string> h;
#else
        hash<char*> h;
#endif
        return h(sym_ptr->_name);
      }
      ;
    };

    /****************************************************************
     * Class ASTSymbolEqual:                                        *
     *                                                              *
     * Equality for ASTSymbol nodes                                 *
     ****************************************************************/
    class ASTSymbolEqual
    {
    public:
      bool operator()(const ASTSymbol *sym_ptr1, 
		      const ASTSymbol *sym_ptr2) const
      {
        return (*sym_ptr1 == *sym_ptr2);
      }
    };

    friend bool operator==(const ASTSymbol &sym1, 
			   const ASTSymbol &sym2)
    {
      return (strcmp(sym1._name, sym2._name) == 0);
    }

    const char * /**const**/ GetName() const
    {
      return _name;
    }

    /****************************************************************
     * Private Member Functions                                     *
     ****************************************************************/

    // Print function for symbol -- return name. (c_friendly is for
    // printing hex. numbers that C compilers will accept)
    virtual void nodeprint(ostream& os, bool c_friendly = false)
    {
      os << _name;
    }

    // Call this when deleting a node that has been stored in the the
    // unique table
    virtual void CleanUp();

  public:

    /****************************************************************
     * Public Member Functions                                      *
     ****************************************************************/

    // Default constructor
    ASTSymbol() : ASTInternal(), _name(NULL)
    {
    }

    // Constructor.  This does NOT copy its argument.
    ASTSymbol(const char * const name) :
      ASTInternal(SYMBOL), _name(name)
    {
    }

    // Destructor (does nothing, but is declared virtual here.
    virtual ~ASTSymbol();

    // Copy constructor
    ASTSymbol(const ASTSymbol &sym) :
      ASTInternal(sym._kind, sym._children), _name(sym._name)
    {
    }
  }; //End of ASTSymbol
}; //end of namespace
#endif
