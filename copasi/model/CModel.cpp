// model.cpp : interface of the CModel class
//
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CModel
#include <string>
#include <vector>

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "CModel.h"
#include "CCompartment.h"
#include "tnt/luX.h"
#include "tnt/triang.h"
#include "tnt/transv.h"

CModel::CModel()
{
  mCompartments = NULL;
  mSteps        = NULL;
  mMoieties     = NULL;

  initialize();
}

void CModel::initialize()
{
  if ( !mCompartments ) mCompartments = new CCopasiVector < CCompartment >;
  if ( !mSteps )        mSteps        = new CCopasiVector < CReaction >;
  if ( !mMoieties )     mMoieties     = new CCopasiVector < CMoiety >;
}

CModel::~CModel()
{
  cleanup();
}

void CModel::cleanup()
{
  if ( mCompartments ) 
    {
      mCompartments->cleanup();
      mCompartments = NULL;
    }
    
  if ( mSteps )
    {
      mSteps->cleanup();
      mSteps = NULL;
    }

  if ( mMoieties )
    {
      mMoieties->cleanup();
      mMoieties = NULL;
    }
}

C_INT32 CModel::load(CReadConfig & configBuffer)
{
  C_INT32 Size = 0;
  C_INT32 Fail = 0;
  unsigned C_INT32 i;

  initialize();
    
  // For old Versions we need must read the list of Metabolites beforehand
  if (configBuffer.getVersion() < "4")
    {
      if ((Fail = configBuffer.getVariable("TotalMetabolites", "C_INT32", 
                                           &Size, CReadConfig::LOOP)))
        return Fail;
        
      if ((Fail = Copasi.OldMetabolites.load(configBuffer, Size)))
        return Fail;
    }

  if ((Fail = configBuffer.getVariable("Title", "string", &mTitle,
                                       CReadConfig::LOOP)))
    return Fail;

  if ((Fail = configBuffer.getVariable("Comments", "multiline", &mComments,
                                       CReadConfig::SEARCH)))
    return Fail;
 
  if ((Fail = configBuffer.getVariable("TotalCompartments", "C_INT32", &Size,
                                       CReadConfig::LOOP)))
    return Fail;
 
  if ((Fail = mCompartments->load(configBuffer, Size))) return Fail;
    
  if (configBuffer.getVersion() < "4")
    {
      // Create the correct compartment / metabolite relationships
      CMetab Metabolite;
      for (i = 0; i < Copasi.OldMetabolites.size(); i++)
        {
          Metabolite = Copasi.OldMetabolites[i];
            
          (*mCompartments)[Copasi.OldMetabolites[i].getIndex()].
            addMetabolite(Metabolite);
        }
    }

  initializeMetabolites();

  if ((Fail = Copasi.FunctionDB.load(configBuffer))) return Fail;

  if ((Fail = configBuffer.getVariable("TotalSteps", "C_INT32", &Size,
                                       CReadConfig::LOOP)))
    return Fail;
    
  if ((Fail = mSteps->load(configBuffer, Size))) return Fail;
    
  // We must postprocess the steps for old file versions
  if (configBuffer.getVersion() < "4")
    for (i = 0; i < mSteps->size(); i++)
      (*mSteps)[i].old2New(mMetabolites);
            
  for (i = 0; i < mSteps->size(); i++)
    (*mSteps)[i].compile(mCompartments);

  return Fail;
}

C_INT32 CModel::save(CWriteConfig & configBuffer)
{
  C_INT32 Size;
  C_INT32 Fail = 0;
    
  if ((Fail = configBuffer.setVariable("Title", "string", &mTitle)))
    return Fail;

  if ((Fail = configBuffer.setVariable("Comments", "multiline", &mComments)))
    return Fail;
 
  Size = mCompartments->size();
  if ((Fail = configBuffer.setVariable("TotalCompartments", "C_INT32", &Size)))
    return Fail;
 
  if ((Fail = mCompartments->save(configBuffer))) return Fail;
    
  if ((Fail = Copasi.FunctionDB.save(configBuffer))) return Fail;

  Size = mSteps->size();
  if ((Fail = configBuffer.setVariable("TotalSteps", "C_INT32", &Size)))
    return Fail;
    
  if ((Fail = mSteps->save(configBuffer))) return Fail;

  return Fail;
}

void CModel::buildStoi()
{
  vector < CReaction::ELEMENT > Structure;
  unsigned C_INT32 i,j,k;
  string Name;
  
  mStoi.newsize(mMetabolites.size(), mSteps->size());
    
  for (i=0; i<mSteps->size(); i++)
    {
      Structure = (*mSteps)[i].getChemStructure();
        
      for (j=0; j<mMetabolites.size(); j++)
        {
          mStoi[j][i] = 0.0;
          Name = mMetabolites[j]->getName();

          for (k=0; k<Structure.size(); k++)
            if (Structure[k].mName == Name)
              {
                mStoi[j][i] = Structure[k].mValue;
                break;
              }
        }
    }
  cout << "Stoichiometry Matrix" << endl;
  cout << mStoi << endl;
    
  return;
}

void CModel::lUDecomposition()
{
  unsigned C_INT32 i;
    
  TNT::Vector < unsigned C_INT32 > rowLU(mStoi.num_rows());
  TNT::Vector < unsigned C_INT32 > colLU(mStoi.num_cols());
  
  mLU = mStoi;
  
  TNT::LUX_factor(mLU, rowLU, colLU);
  
  TNT::UpperTriangularView < TNT::Matrix < C_FLOAT64 > > U(mLU);
  TNT::UnitLowerTriangularView < TNT::Matrix < C_FLOAT64 > > L(mLU);

  cout << "U" << endl;
  cout << U << endl;
  cout << "L" << endl;
  cout << L << endl;

  mMetabolitesX = mMetabolites;
    
  mStepsX.resize(mSteps->size());
  for (i=0; i<mSteps->size(); i++)
    mStepsX[i] = &(*mSteps)[i];

  // permutate Metabolites and Steps to match rearangements done during
  // LU decomposition

  CMetab *pMetab;
  for (i = 0; i < mMetabolitesX.size(); i++) 
    {
      if (rowLU[i] - 1 > i)
        {
          pMetab = mMetabolitesX[i];
          mMetabolitesX[i] = mMetabolitesX[rowLU[i]-1];
          mMetabolitesX[rowLU[i]-1] = pMetab;
        }
    }
    
  CReaction *pStep;
  for (i = mStepsX.size(); 0 < i--; ) 
    {
      if (colLU[i]-1 < i)
        {
          pStep = mStepsX[i];
          mStepsX[i] = mStepsX[colLU[i]-1];
          mStepsX[colLU[i]-1] = pStep;
        }
    }

  return;
}

void CModel::setMetabolitesStatus()
{
  C_INT32 i,j,k;
  C_FLOAT64 Sum;
    
  // for (i=0; i<min(mLU.num_rows(), mLU.num_cols()); i++)
  // for compiler
  C_INT32 imax = (mLU.num_rows() < mLU.num_cols()) ? 
    mLU.num_rows() : mLU.num_cols();
  for (i=0; i<imax; i++)
    {
      if (mLU[i][i] == 0.0) break;
      mMetabolitesX[i]->setStatus(METAB_VARIABLE);
    }
  mMetabolitesInd.clear();
  mMetabolitesInd.insert(0,&mMetabolitesX[0],&mMetabolitesX[i]);
  mStepsInd.insert(0,&mStepsX[0],&mStepsX[i]);
    
  for (j=i; j<mLU.num_rows(); j++)
    {
      Sum = 0.0;
        
      for (k=0; k<mLU.num_cols(); k++)
        Sum += fabs(mLU[j][k]);
      if (Sum == 0.0) break;
      mMetabolitesX[j]->setStatus(METAB_DEPENDENT);
    }
  mMetabolitesDep.clear();
  mMetabolitesDep.insert(0,&mMetabolitesX[i],&mMetabolitesX[j]);

  for (k=j; k<mLU.num_rows(); k++)
    mMetabolitesX[k]->setStatus(METAB_FIXED);

  return;
}

void CModel::buildRedStoi()
{
  C_INT32 i,j,k;
  C_FLOAT64 Sum;
  C_INT32 imax, jmax, kmax;                // wei for compiler

  imax = mMetabolitesInd.size();
  jmax = mStepsX.size();
  
  mRedStoi.newsize(imax, jmax);
  
  for (i=0; i<imax; i++)
    for (j=0; j<jmax; j++)
      {
        Sum = 0.0;

        /* Since L[i,k] = 1 for k = i and L[i,k] = 0 for k > i
           we have to avoid L[i,k] where k >= i, i.e.. k < i.
           Similarly, since U[k,j] = 0 for k > j
           we have to avoid U[k,j] where k > j, i.e., k <= j.
           Therefore, kmax = min(i-1, j). */
        kmax = (i - 1 < j) ? i - 1: j;
        for (k=0; k<kmax; k++)
          Sum += mLU[i][k] * mLU[k][j];

        /* For i - 1 < j we are missing a part of the sum: */
        if (i - 1 < j) Sum += /* mLU[i][i]* */ mLU[i][j]; // since L[i,i] = 1

        mRedStoi[i][j] = Sum;
      }
  cout << "Reduced Stoichiometry Matrix" << endl;
  cout << mRedStoi << endl;
    
  return;
}

void CModel::buildL()
{
  unsigned C_INT32 size = mMetabolites.size();
  unsigned C_INT32 i, j, jmax, k;
  TNT::UnitLowerTriangularView < TNT::Matrix < C_FLOAT64 > > L(mLU);
  
  mL.newsize(size,size);
  jmax = (size < mSteps->size()) ? size : mSteps->size();
 
  /* Create L from the UnitLowerTriangularView of mLU */
  for (i=0; i<size; i++)
    for (j=0; j<jmax; j++)
      mL[i][j] = L(i+1,j+1);
  
  /* We complete L so that it is a square matrix */
  for (i=0; i<size; i++)
    for (j=jmax; j<size; j++)
      mL[i][j] = 0.0;

  for (j=jmax; j<size; j++)
    mL[j][j] = 1.0;

  /* Calculate the inverse of L and store it in the upper triangular 
     part of L */

  C_FLOAT64 *sum;
  for (j=0; j<size-1;j++)
    for (i=j+1; i<size; i++)
    {
        sum = &mL[j][i];
        *sum = - mL[i][j];
        for (k=j+1; k<i-1; k++)
            // I[i][j] -= mL[i][k] * I[k][j]
            *sum -= mL[i][k] * mL[j][k];
    }

  cout << "L" << endl; 
  cout << 
    TNT::LowerTriangularView< TNT::Matrix< C_FLOAT64 > >(mL) 
       << endl;
  cout << "L inverse" << endl; 
  cout << 
    TNT::Transpose_View< TNT::UpperTriangularView< TNT::Matrix< C_FLOAT64 > > >(mL)
       << endl;
  
}

#ifdef XXXX
void CModel::buildConsRel()
{
  mConsRel.newsize(mMetabolites.size(), mMetabolitesInd.size());
    
  C_INT32 i,j;

  C_INT32 imax = (mConsRel.num_rows() > mConsRel.num_cols()) ? 
    mConsRel.num_cols() : mConsRel.num_rows();
    
  // wei for compiler for (i=0; i<min(mConsRel.num_rows(), mConsRel.num_cols()); i++)
  for (i=0; i<imax; i++)
    mConsRel[i+1][i] = mLU[i+1][i];
    
  for (j=0; j<mConsRel.num_cols(); j++)
    for (i=j+2; i<mConsRel.num_rows(); i++)
      mConsRel[i][j] = mLU[i][j] + mLU[i][i-1] * mConsRel[i-1][j];

  cout << mConsRel << endl;
  
  return;
}
#endif // XXXX

void CModel::buildMoieties()
{
  unsigned C_INT32 i;
  unsigned C_INT32 imin = mMetabolitesInd.size();
  unsigned C_INT32 imax = imin + mMetabolitesDep.size();
  unsigned C_INT32 j;
  unsigned C_INT32 jmax = imin;
  
  CMoiety Moiety;
  
  mMoieties->cleanup();

  for (i=imin; i<imax; i++)
    {
      Moiety.cleanup();
    
      Moiety.setName(mMetabolitesX[i]->getName());
      Moiety.add(1.0, mMetabolitesX[i]);
        
      for (j=0; j<jmax; j++)
        {
          if (mL[j][i] != 0.0)
            Moiety.add(mL[j][i], mMetabolitesX[j]);
        }
      Moiety.setInitialValue();
      cout << Moiety.getDescription() << endl;
      
      mMoieties->add(Moiety);
    }
    
  return;
}

void CModel::setConcentrations(const C_FLOAT64 * y)
{
  unsigned C_INT32 i;

  // Set the concentration of the independent metabolites
  for (i=0; i < mMetabolitesInd.size(); i++)
    mMetabolitesInd[i]->setNumber(y[i]);
    
  // Set the concentration of the dependent metabolites
  for (i=0; i<mMetabolitesDep.size(); i++)
    mMetabolitesDep[i]->setNumber((*mMoieties)[i].dependentNumber());

  return;
}

CCopasiVector < CReaction > & CModel::getReactions()
{
  return *mSteps;
}

vector < CReaction * > & CModel::getReactionsX()
{
  return mStepsX;
}

void CModel::lSODAEval(C_INT32 n, C_FLOAT64 t, C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  unsigned C_INT32 i,j;
  //FIXME: This should be a member
  C_FLOAT64 * v = new C_FLOAT64[mSteps->size()];
    
  cout << mTitle << endl;

  setConcentrations(y);
    
  // Calculate the velocity vector depending on the step kinetics
  for (i=0; i<mSteps->size(); i++)
    v[i] = (*mSteps)[i].calculate();

  // Calculate ydot = RedStoi * v
  for (i=0; i<(unsigned C_INT32) n; i++)
    {
      ydot[i] = 0.0;
      for (j=0; j<mSteps->size(); j++)
        ydot[i] += mRedStoi[i][j] * v[j];
    }
    
  delete [] v;
    
  return;
}

vector < CMetab * > & CModel::getMetabolitesInd(){return mMetabolitesInd;}

vector < CMetab * > & CModel::getMetabolitesX(){return mMetabolitesX;}

C_INT32 CModel::getTotMetab() const
{
  return mMetabolites.size();
}

C_INT32 CModel::getIntMetab() const
{
  return mMetabolitesInd.size() + mMetabolitesDep.size();
}

C_INT32 CModel::getIndMetab() const
{
  return mMetabolitesInd.size();
}

C_INT32 CModel::getDepMetab() const
{
  return mMetabolitesDep.size();
}


// Added by Yongqun He
/**
 * Get the total steps
 *
*/
//C_INT32 CModel::getTotSteps()
//{
// return mSteps;   //should not return mSteps
//}

C_INT32 CModel::getDimension() const
{
  return mMetabolitesInd.size();
}

/**
 *        Return the comments of this model        Wei Sun 
 */
string CModel::getComments() const
{
  return mComments;
}


/**
 *        Return the title of this model
 *        @return string
 */
string CModel::getTitle() const
{
  return mTitle;
}

/**
 *        Return the comments of this model
 *        @return CCopasiVector < CCompartment > *
 */
CCopasiVector < CCompartment > * CModel::getCompartments()
{
  return mCompartments;
}

/**
 *        Return the metabolites of this model
 *        @return vector < CMetab * > 
 */
vector < CMetab * > & CModel::getMetabolites()
{
  return mMetabolites;
}

/**
 *  Get the Reduced Stoichiometry Matrix of this Model
 */
TNT::Matrix < C_FLOAT64 >& CModel::getRedStoi()
{
  return mRedStoi;
}

/**
 *        Return the mMoieties of this model        
 *        @return CCopasiVector < CMoiety > * 
 */
CCopasiVector < CMoiety > * CModel::getMoieties()
{
  return mMoieties;
}

/**
 *        Returns the index of the metab
 */
C_INT32 CModel::findMetab(string &Target)
{
  unsigned C_INT32 i;
  string name;

  for(i = 0; i < mMetabolites.size(); i++ )
    {
      name = mMetabolites[i]->getName();
      if( name == Target) return i;
    }

  return -1;
}

/**
 *        Returns the index of the step
 */
C_INT32 CModel::findStep(string &Target)
{
  unsigned C_INT32 i;
  string name;

  for(i = 0; i < mSteps->size(); i++ )
    {
      name = (*mSteps)[i].getName();
      if( name == Target) return i;
    }

  return -1;
}

/**
 *        Returns the index of the compartment
 */
C_INT32 CModel::findCompartment(string &Target)
{
  unsigned C_INT32 i;
  string name;

  for(i = 0; i < mCompartments->size(); i++ )
    {
      name = (*mCompartments)[i].getName();
      if( name == Target) return i;
    }

  return -1;
}

/**
 *        Returns the index of the Moiety
 */
C_INT32 CModel::findMoiety(string &Target)
{
  unsigned C_INT32 i;
  string name;

  for(i = 0; i < mMoieties->size(); i++ )
    {
      name = (*mMoieties)[i].getName();
      if( name == Target) return i;
    }

  return -1;
}
void CModel::initializeMetabolites()
{
  unsigned C_INT32 i, j;

  // Create a vector of pointers to all metabolites.
  // Note, the metabolites physically exist in the compartments.
  for (i = 0; i < mCompartments->size(); i++)
    for (j = 0; j < (*mCompartments)[i].metabolites().size(); j++)
      mMetabolites.push_back(&(*mCompartments)[i].metabolites()[j]);
}

/**
 * Returns the mStepsX of this model
 * @return vector < CStep * > 
 */
vector < CReaction * > & CModel::getStepsX()
{
	return mStepsX;
}

/**
 *  Get the mLU matrix of this model
 */
TNT::Matrix < C_FLOAT64 >& CMolde::getmLU()
{
	return mLU;
}
