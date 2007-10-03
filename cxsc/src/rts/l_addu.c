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

/* CVS $Id: l_addu.c,v 1.9 2007/05/16 14:59:32 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : l_addu.c                              */
/*                                                              */
/*      Entries         : multiprecision l_addu(i1,i2)          */
/*                        multiprecision i1,i2;                 */
/*                                                              */
/*      Description     : Addition of multi-precision numbers   */
/*                        with rounding upwards.                */
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
local multiprecision l_addu(multiprecision i1,multiprecision i2)
#else
local multiprecision l_addu(i1,i2)

multiprecision i1;
multiprecision i2;
#endif
        {
        int rc;
        multiprecision res;

        E_TPUSH("l_addu")

        l_init(&res);

        if (res==NULL)
                e_trap(ALLOCATION,2,E_TMSG,65);
        else if ((rc = b_badd(i1,i2,res))!=0)
                {
                switch(rc)
                   {
                   case OFLOW : e_trap(OVERFLOW,4,E_TMLT+E_TEXT(1),&i1,
                                                  E_TMLT+E_TEXT(2),&i2);
                                break;
                   case UFLOW : e_trap(UNDERFLOW,4,E_TMLT+E_TEXT(1),&i1,
                                                   E_TMLT+E_TEXT(2),&i2);
                                break;
                   case ALLOC : e_trap(ALLOCATION,2,E_TMSG,65);
                                break;
                   }
                }
        else
           {
           res->f = 1;
           if (!res->s)
              {
              if ((rc = b_brnd(res,res))!=0)
                 {
                 switch(rc)
                    {
                    case OFLOW : e_trap(OVERFLOW,4,E_TMLT+E_TEXT(1),&i1,
                                                   E_TMLT+E_TEXT(2),&i2);
                                 break;
                    case ALLOC : e_trap(ALLOCATION,2,E_TMSG,65);
                                 break;
                    }
                 }
              }
           }

        if (i1->f) l_free(&i1);
        if (i2->f) l_free(&i2);

        E_TPOPP("l_addu")
        return(res);
        }

