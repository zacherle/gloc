#ifndef LOCATION_H
#define LOCATION_H

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


/*-----------------------------------------------------------------------
Anthony Lomax
Anthony Lomax Scientific Software
161 Allee du Micocoulier, 06370 Mouans-Sartoux, France
tel: +33(0)493752502  e-mail: anthony@alomax.net  web: http://www.alomax.net
-------------------------------------------------------------------------*/

#include "GridLib.h"



/*------------------------------------------------------------/ */
/* structures */
/*------------------------------------------------------------/ */


/* location structure */

typedef struct location
{
	HypoDesc* phypo;	/* location data */
	ArrivalDesc* parrivals;	/* phase arrival data */
		/* WARNING: for nll_assoc this data is temporary, definitive associated arrivals specified by PhsNode.passoc_locations location id list!!! */
	int narrivals;		/* num of phase arrival data */
	GridDesc* pgrid;	/* location grid */
	Tree3D* poctTree;	/* location oct-tree structure */
	float* pscatterSample;	/* location scatter sample data */

} Location;


/*------------------------------------------------------------/ */


#endif //LOCATION_H
