/**
 * CScanTask class.
 *
 * This class implements a scan task which is comprised of a
 * of a problem and a method.
 *  
 */
#include "copasi.h"
#include "CScanTask.h"
#include "CScanProblem.h"
#include "CScanMethod.h"
#include "utilities/CGlobals.h"
#include "utilities/readwrite.h"
#include "output/COutputEvent.h"
#include "output/COutputList.h"
#include "output/COutput.h"
#include "report/CKeyFactory.h"
#include "model/CModel.h"
#include "model/CState.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"

CScanTask::CScanTask():
    CCopasiContainer("ScanTask", NULL, "ScanTask", CCopasiObject::Container),
    mKey(CKeyFactory::add("ScanTask", this)),
    mRequested(true),
    mpProblem(new CScanProblem),
    mpMethod(CScanMethod::createMethod()),
    mpOutEnd(NULL)
{}

CScanTask::CScanTask(const CScanTask & src):
    CCopasiContainer("ScanTask", NULL, "ScanTask", CCopasiObject::Container),
    mKey(CKeyFactory::add("ScanTask", this)),
    mRequested(src.mRequested),
    mpProblem(new CScanProblem(*src.mpProblem)),
    mpMethod(new CScanMethod(*src.mpMethod)),
    mpOutEnd(src.mpOutEnd)
{}

CScanTask::~CScanTask()
{cleanup();}

void CScanTask::cleanup()
{
  CKeyFactory::remove(mKey);
  pdelete(mpProblem);
  pdelete(mpMethod);
  pdelete(mpOutEnd);
}

void CScanTask::initializeReporting(std::ostream & out)
{
  pdelete(mpOutEnd);
  mpOut = & out;
  if (mpProblem->ifSteadyStateTask())
    mpProblem->getSteadyStateTask()->initializeReporting(out);
  if (mpProblem->ifTrajectoryTask())
    mpProblem->getTrajectoryTask()->initializeReporting(out);
}

void CScanTask::load(CReadConfig & configBuffer)
{
  mpProblem->load(configBuffer);
}

void CScanTask::save(CWriteConfig & configBuffer)
{
  mpProblem->save(configBuffer);
}

void CScanTask::setRequested(const bool & requested)
{mRequested = requested;}

bool CScanTask::isRequested() const {return mRequested;}

CScanProblem * CScanTask::getProblem()
{return mpProblem;}

void CScanTask::setProblem(CScanProblem * pProblem)
{mpProblem = pProblem;}

CScanMethod * CScanTask::getMethod()
{return mpMethod;}

void CScanTask::setMethod(CScanMethod * pMethod)
{mpMethod = pMethod;}

void CScanTask::process()
{
  if (!mpProblem)
    fatalError();
  if (!mpMethod)
    fatalError();

  mpMethod->setProblem(mpProblem);
  mpProblem->InitScan();

  if ((mpProblem->getSteadyStateTask() != NULL) && mpProblem->processSteadyState())
    {
      mpProblem->getSteadyStateTask()->getProblem()->getModel()->compile();
      mpProblem->getSteadyStateTask()->getProblem()->
      setInitialState(mpProblem->getSteadyStateTask()->getProblem()->getModel()->getInitialState());
    }
  if ((mpProblem->getTrajectoryTask() != NULL) && mpProblem->processTrajectory())
    {
      mpProblem->getTrajectoryTask()->getProblem()->getModel()->compile();
      mpProblem->getTrajectoryTask()->getProblem()->
      setInitialState(mpProblem->getTrajectoryTask()->getProblem()->getModel()->getInitialState());
      mpProblem->getTrajectoryTask()->getProblem()->
      setStartTime(mpProblem->getTrajectoryTask()->getProblem()->getStartTime());
    }

  unsigned C_INT32 scanDimension = mpProblem->getListSize();
  int i;
  // find the last master
  for (i = scanDimension - 1; i >= 0; i--)
    if (mpProblem->getScanItemParameter(i, "indp")) break;
  if (i >= 0)
    // execute many simulations
    mpMethod->scan(i, true);

  //  if (mpOutEnd)
  //    mpOutEnd->print(*Copasi->pOutputList, *mpOut);

  return;
}
