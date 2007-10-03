/*
**  CXSC is a C++ library for eXtended Scientific Computing (V 2.2.1)
**
**  Copyright (C) 1990-2000 Institut fuer Angewandte Mathematik,
**                          Universitaet Karlsruhe, Germany
**            (C) 2000-2007 Wiss. Rechnen/Softwaretechnologie
**                          Universitaet Wuppertal, Germany   
**
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the GNU Library General Public
**  License as published by the Free Software Foundation; either
**  version 2 of the License, or (at your option) any later version.
**
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**  Library General Public License for more details.
**
**  You should have received a copy of the GNU Library General Public
**  License along with this library; if not, write to the Free
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* CVS $Id: t_sico.c,v 1.9 2007/05/16 14:59:47 cxsc Exp $ */

#ifdef AIX
#include "/u/p88c/runtime/tbyte/t_defs.h"
#else
#include "t_defs.h"
#endif

/*--------------------------------------------------------------*/
/* sincos                                                       */
/*--------------------------------------------------------------*/
#ifdef ANSI_C
#ifdef LINT_ARGS
int sincos(const ExtReal *arg, ExtReal *res)
#else
int sincos(arg, res)
const ExtReal  *arg;    /* reduziertes Argument                 */
      ExtReal  *res;    /* Ergebnis                             */
#endif /* LINT_ARGS */
#else  /* NOT ANSI_C */
#ifdef LINT_ARGS
int sincos(ExtReal *arg, ExtReal *res)
#else
int sincos(arg, res)
ExtReal  *arg;          /* reduziertes Argument                 */
ExtReal  *res;          /* Ergebnis                             */
#endif /* LINT_ARGS */
#endif /* ANSI_C */
{
   ExtReal     t;       /* -pi/2 <= Argument t <= pi/2          */
   int         rnd;     /* RundungsMode                         */
   int         ret;     /* Rueckgabe                            */

   /* --- RundungsMode sichern, NEAR setzen --- */
   rnd  = getrndmode();
   setrndmode(NEAR);

   /* --- arg*Pi/2 --- */
   mulee(arg, &PiHalf, &t);

   /* --- Sinus --- */
   ret = _s_sin(&t, res);

   /* --- RundungsMode zuruecksetzen --- */
   setrndmode(rnd);

   return ret;
} /* sincos() */

