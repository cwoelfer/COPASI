/*
 * CreateNewSpecieCommand.h
 *
 *  Created on: 2 Sep 2014
 *      Author: dada
 */

#ifndef CREATENEWSPECIECOMMAND_H_
#define CREATENEWSPECIECOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQSpeciesDetail;
class UndoSpecieData;

class CreateNewSpecieCommand: public CCopasiUndoCommand {
public:
	CreateNewSpecieCommand(CQSpeciesDetail *pSpecieDetail);
	void redo();
	void undo();
	QString createNewSpecieText() const;
	virtual ~CreateNewSpecieCommand();

private:
	UndoSpecieData *mpSpecieData;
	CQSpeciesDetail* mpSpecieDetail;
};

#endif /* CREATENEWSPECIECOMMAND_H_ */
