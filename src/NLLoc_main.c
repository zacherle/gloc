/*
 * Copyright (C) 1999-2007 Anthony Lomax <anthony@alomax.net, http://www.alomax.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */


/*   NLLoc.c

	Program to do global search earthquake location in 3-D models

*/

/*-----------------------------------------------------------------------
Anthony Lomax
Anthony Lomax Scientific Software
161 Allee du Micocoulier, 06370 Mouans-Sartoux, France
tel: +33(0)493752502  e-mail: anthony@alomax.net  web: http://www.alomax.net
-------------------------------------------------------------------------*/


/*
	history:	(see also http://alomax.net/nlloc -> Updates)

	ver 01    17DEC2007  AJL  Created NLLoc_main and function call NLLoc()

	see NLLoc1.c and NLLocLib.c


.........1.........2.........3.........4.........5.........6.........7.........8

*/

/** program to perform global search event locations */

#include <stdio.h>
#include "GridLib.h"
#include "velmod.h"
#include "phaseloclist.h"
#include "otime_limit.h"
#include "alomax_matrix/alomax_matrix.h"
#include "NLLocLib.h"

#include "ran1/ran1.h"
#include "util.h"
#include <string.h>


#define PNAME  "NLLoc"

#define NARGS_MIN 2
#define ARG_DESC "<control file>"

int main(int argc, char *argv[])
{

	int istat;

	char fn_control_main[MAXLINE];	// control file name
	char pid_main[255];	// string process id


	// set program name
	strcpy(prog_name, PNAME);

	// check command line for correct usage
	if (argc < NARGS_MIN) {
		disp_usage(prog_name, ARG_DESC);
		return(EXIT_ERROR_USAGE);
	}

	// set control file
	strcpy(fn_control_main, argv[1]);

	// run NLLoc
	istat = NLLoc(pid_main, fn_control_main, NULL, -1, NULL, -1, 0, 0, 0, NULL);

	return(istat);

}




