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

/* CVS $Id: l_trun.c,v 1.9 2007/05/16 14:59:34 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : l_trun.c                              */
/*                                                              */
/*      Entries         : a_intg l_trun(a)                      */
/*                        multiprecision a;                     */
/*                                                              */
/*      Arguments       : a = INTERN value                      */
/*                                                              */
/*      Description     : Truncate INTERN value to integer.     */
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
local a_intg l_trun(multiprecision a)
#else
local a_intg l_trun(a)

multiprecision a;
#endif
        {
        a_intg res = 0;

        E_TPUSH("l_trun")

        if (a->z)
           {
           }
        else if (a->e>0 || (a->e==0 && (a->m[0] & MSB)))
           e_trap(OVERFLOW,4,E_TMSG,15,E_TMLT+E_TEXT(7),&a);
        else if (a->e==0)
           {
           if (a->s)
#if C_P_2
              res = -a->m[0];
#else
              res = ~(a->m[0])+1;
#endif
           else
              res = a->m[0];
           }

        if (a->f) l_free(&a);

        E_TPOPP("l_trun")
        return(res);
        }

