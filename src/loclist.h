#ifndef LOCLIST_H
#define LOCLIST_H

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


/*  loclist.h

	include file for loclist

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


/* location structure */

//typedef struct location
//{
//	HypoDesc* phypo;	/* location data */
//	ArrivalDesc* parrivals;	/* phase arrival data */
//		/* WARNING: for nll_assoc this data is temporary, definitive associated arrivals specified by PhsNode.passoc_locations location id list!!! */
//	int narrivals;		/* num of phase arrival data */
//	GridDesc* pgrid;	/* location grid */
//	Tree3D* poctTree;	/* location oct-tree structure */
//	float* pscatterSample;	/* location scatter sample data */
//
//} Location;


/* loclist node structure*/

typedef struct locnode
{
	struct locnode *prev;	/* pointer to previous vertex */
	struct locnode *next;	/* pointer to next vertex */
	int id;			/* vertex identification - sort value */
	Location *plocation;	/* location data */
	double first_phase_time;	/* time value for earliest phase */
	// NOT NEEDED? PhsNode *phsNodeList;	/* list of phase nodes used for location */
} LocNode;


/*------------------------------------------------------------/ */




/*------------------------------------------------------------/ */
/* function declarations */
/*------------------------------------------------------------/ */

/* loclist */
Location *newLocation(HypoDesc *phypo, ArrivalDesc* parrivals, int narrivals, GridDesc *pgrid, Tree3D* poctTree, float *pscatterSample);
LocNode *addLocationToLocList(LocNode **phead, Location *plocation, int id);
/*
LocNode *removeLocationFromLocList(LocNode *head, LocNode* addr, int freeHypoDesc);
int freeLocList(LocNode *head, int freeHypoDesc);
void freeLocation(Location *plocation);
//LocNode *addNLLLocationFileToLocList(LocNode **phead, char *filein, int id, PhsNode **phsNodeList);
int writeLocList(LocNode *head, FILE *out);
void writeLocNode(LocNode *addr, FILE *out);
double getLocTimeValue(HypoDesc *phypo);
LocNode **findLocsWithFirstPhaseInTimeWindow(LocNode *LocListHead, double tmin, double tmax);
ArrivalDesc *findArrivalInLocation(Location *plocation, ArrivalDesc *arrivalKey);
int arrivalBeforeLastLocateArrival(ArrivalDesc *arrivalKey, Location *plocation);
// AJL 20070323-
LocNode *getLocationFromLocList(LocNode *head, int id);
*/

/* */
/*------------------------------------------------------------/ */


#endif //LOCLIST_H
