#ifndef PHASELIST_H
#define PHASELIST_H
/*
 * Copyright (C) 1999-2010 Anthony Lomax <anthony@alomax.net, http://www.alomax.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.

 * You should have received a copy of the GNU Lesser Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */


/*  phaselist.h

	include file for phaselist

*/



/*-----------------------------------------------------------------------
Anthony Lomax
Anthony Lomax Scientific Software
161 Allee du Micocoulier, 06370 Mouans-Sartoux, France
tel: +33(0)493752502  e-mail: anthony@alomax.net  web: http://www.alomax.net
-------------------------------------------------------------------------*/

#include "location.h"
//#include "GridLib.h"


/*------------------------------------------------------------/ */
/* structures */
/*------------------------------------------------------------/ */


/* phaselist */

/* phaselist node */

//typedef struct phasenode
//{
//	struct phasenode *prev;	/* pointer to previous vertex */
//	struct phasenode *next;	/* pointer to next vertex */
//	int id;			/* vertex identification */
//	double phase_time;	/* phase time in seconds - sort value */
//	ArrivalDesc* parrival;	/* phase arrival data (observation part only is initialized) */
//	int *passoc_locations;	/* id's of associated locations, -1 if none */
//	int passoc_locations_size;	/* size of passoc_locations array */
//} PhsNode;



/*------------------------------------------------------------/ */




/*------------------------------------------------------------/ */
/* function declarations */
/*------------------------------------------------------------/ */

/* phaselist */

//PhsNode *addArrivalToPhaseList(PhsNode **phead, ArrivalDesc* parrival, int id, int addDuplicates);
//PhsNode *addPhsNodeToPhaseList(PhsNode *phead, PhsNode* addr);
//PhsNode *removeArrivalFromPhaseList(PhsNode *head, PhsNode* addr, int freeArrivalDesc);
//int freePhaseList(PhsNode *head, int freeArrivalDesc);
//PhsNode *addNLLPhaseStringToPhaseList(PhsNode **phead, char *phase_string, int id, int addDuplicates);
//int writePhaseList(PhsNode *head, FILE *out);
double getPhaseTimeValue(ArrivalDesc *parrival);
int compareTimeValue(double t1, double t2);
//int addRemoveLocationInAssocLocationsList(PhsNode *addr, int locID, int addLocID);
//int updateAssociatedLocation(PhsNode *head, Location *plocation, int locID, double tmin, double tmax);
//PhsNode *findPhaseInTimeWindow(PhsNode *head, double tmin, double tmax, int associatedFlag);
//PhsNode *findPhase(PhsNode *head, ArrivalDesc *arrivalKey);
int compareArrivals(ArrivalDesc *parrival, ArrivalDesc *arrivalKey, int compareTimes);
//int strcmp_to_null(char *s1, char *s2);
// AJL 20070323-
//PhsNode *getPhsNodeFromPhaseList(PhsNode *head, int id);
//int removeLocationAssociation(PhsNode *head, int locID, double tmin_nomimnal, double tmax_nomimnal);


/* */
/*------------------------------------------------------------/ */


#endif //PHASELIST_H
