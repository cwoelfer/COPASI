/*
 * DeleteReactionCommand.h
 *
 *  Created on: 4 Jul 2014
 *      Author: dada
 */

#ifndef DELETEREACTIONCOMMAND_H_
#define DELETEREACTIONCOMMAND_H_

#include "CCopasiUndoCommand.h"

class CReaction;
class ReactionsWidget1;

class DeleteReactionCommand: public CCopasiUndoCommand {
public:
	DeleteReactionCommand(ReactionsWidget1 *pReactionWidget);
	void redo();
	void undo();
	QString deleteReactionText(std::string &name) const;

	virtual ~DeleteReactionCommand();

private:
	std::string mReaObjectName;
	CReactionInterface *mpRi;
	CReaction *mpReaction;
	ReactionsWidget1* mpReactionWidget;
};

#endif /* DELETEREACTIONCOMMAND_H_ */
