//
//
// C++ Interface: $MODULE$
//
// Description:
//
//
// Author: sven <sven@ares>, (C) 2003
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef COPASI_CMetabNameInterface
#define COPASI_CMetabNameInterface

#include <string>

class CModel;
class CMetab;

/**
 *
 */
class CMetabNameInterface
  {
  public:
    CMetabNameInterface();

    ~CMetabNameInterface();

    /**
    * This returns a name to use for display in the gui. If the name of the
    * metabolite is unique it is used unaltered. If it is not then the compartment
    * is added to the name to make it unique.
    */
    static const std::string & getDisplayName(const CModel* model, const std::string & key);

    /**
    * This returns a name to use for display in the gui. If the name of the
    * metabolite is unique it is used unaltered. If it is not then the compartment
    * is added to the name to make it unique.
    */
    static const std::string & getDisplayName(const CModel* model, const CMetab & metab);

    /**
    * This tries to find the metabolite with the given name. If the name is not unique and 
    * is given without a compartment then the first occurence of a metabolite with this name 
    * is returned.
    */
    static std::string getMetaboliteKey(const CModel* model, const std::string & name);
    static CMetab * getMetabolite(const CModel* model, const std::string & name);

    /**
    * This returns whether the metabolite name is unique. 
    */
    static bool isUnique(const CModel* model, const std::string & name);

    /**
    * This returns whether a metabolite with the given name does exist. If a compartment is
    * also given (as an appendix to the name) then it only returns true if the metabolite
    * exists in the specified compartment.
    */
    static bool doesExist(const CModel* model, const std::string & name);

    /**
    * This extracts the compartment name from the given metabolite name. If no compartment name is 
    * present in the given metabolite name then the name of the compartment the metabolite is really 
    * in is given. If the metabolite does not exist and the name does not contain a compartment
    * then the name of the first compatmnet in the model is returned.
    */
    static std::string extractCompartmentName(const CModel* model, const std::string & name);

  private:
    static std::string empty_string;
  };

#endif
