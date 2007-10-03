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

/* CVS $Id: s_ssge.c,v 1.9 2007/05/16 14:59:41 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : s_ssge.c                              */
/*                                                              */
/*      Entries         : a_bool s_ssge(s,t)                    */
/*                        s_trng s,t;                           */
/*                                                              */
/*      Arguments       : s = first string                      */
/*                        t = second string                     */
/*                                                              */
/*      Description     : Compare for greater/equal strings.    */
/*                                                              */
/****************************************************************/

#ifndef ALL_IN_ONE
#ifdef AIX
#include "/u/p88c/runtime/o_defs.h"
#else
#include "o_defs.h"
#endif
#define local
#endif

#ifdef LINT_ARGS
local a_bool s_ssge(s_trng s,s_trng t)
#else
local a_bool s_ssge(s,t)

s_trng s;
s_trng t;
#endif
        {
        a_bool res;

        if (t.clen==0) res = TRUE;
        else if (s.clen==0) res = FALSE;
        else if (s.clen<t.clen)
           res = (strncmp(s.ptr,t.ptr,s.clen)>0) ? TRUE : FALSE;
        else
           res = (strncmp(s.ptr,t.ptr,t.clen)>=0) ? TRUE : FALSE;

        if (s.tmp) s_free(&s);
        if (t.tmp) s_free(&t);

        return(res);
        }

