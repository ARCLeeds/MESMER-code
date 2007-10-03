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

/* CVS $Id: t_gtrg.c,v 1.9 2007/05/16 14:59:45 cxsc Exp $ */

#ifdef AIX
#include "/u/p88c/runtime/tbyte/t_defs.h"
#else
#include "t_defs.h"
#endif

/*----------------------------------------------------------------------*
 | gza liefert ganzzahligen Anteil j: arg = j * 2/Pi + t  fuer Trg Fktn |
 *----------------------------------------------------------------------*/

#ifdef ANSI_C
#ifdef LINT_ARGS
int gza_trg(const ExtReal *arg, int jinit, int p,
                  DReal *v, ExtReal *j, int *jmod4)
#else
int gza_trg(arg, jinit, p, v, j, jmod4)
const ExtReal  *arg; /* Argumente                                       */
      int      jinit;      /* Initialisierung des ganzzahligen Anteils j*/
      int      p;          /* Kennung Periode pi/2 bzw. pi/4            */
                     /* Ergebnisse                                      */
      DReal    *v;         /* Produkt des Arguments mit 1/Periode       */
      ExtReal  *j;         /* Ganzzahliger Anteil von v                 */
      int      *jmod4;     /* j modulo 4                                */
#endif /* LINT_ARGS */
#else  /* NOT ANSI_C */
#ifdef LINT_ARGS
int gza_trg(ExtReal *arg, int jinit, int p, DReal *v, ExtReal *j, int *jmod4)
#else
int gza_trg(arg, jinit, p, v, j, jmod4)
ExtReal  *arg;
int      jinit;
int      p;
DReal    *v;
ExtReal  *j;
int      *jmod4;
#endif /* LINT_ARGS */
#endif /* ANSI_C */
{
   ExtReal     ve;         /* = *v                              */
   int         rnd;        /* RundungsMode                      */

   /* --- RundungsMode sichern --- */
   rnd  = getrndmode();

   /* --- v = arg/Periode = arg*p/Pi, p = (2 oder 4) --- */
   mulendpi(arg, p, v);

   /* --- j = int(v) --- */
   setrndmode(DOWN);
   dreal_to_extreal(v, &ve);
   rndintee(&ve, j);

   /* --- (j+jinit) mod 4, jinit = (0 fuer sin, 1 cos, 0 tan, 2 cot) --- */
   *jmod4 = mod4e(j) + jinit;
   if (*jmod4 > 3) *jmod4 -= 4;

   /* --- RundungsMode zuruecksetzen --- */
   setrndmode(rnd);

   /* --- keine Fehler moeglich --- */
   return NoErr;
} /* gza_trg() */

