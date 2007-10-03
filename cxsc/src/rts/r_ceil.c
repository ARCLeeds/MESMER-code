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

/* CVS $Id: r_ceil.c,v 1.9 2007/05/16 14:59:36 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : r_ceil.c                              */
/*                                                              */
/*      Entries         : a_real r_ceil(r)                      */
/*                        a_real r;                             */
/*                                                              */
/*      Arguments       : r = real value                        */
/*                                                              */
/*      Description     : Returns smallest integer not less     */
/*                        than input value.                     */
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
local a_real r_ceil(a_real r)
#else
local a_real r_ceil(r)

a_real r;
#endif
        {
        a_btyp mant[2*D_U_RATIO];
        a_bool vz = FALSE;
        a_intg expo;

        E_TPUSH("r_ceil")

        B_CLEAR(mant,2*D_U_RATIO)
        if (b_deko(r,&expo,mant,&vz)==FALSE)
           {
           if (expo>=EXPO_MAX)
              {
              if (SIGNALING(mant[0]))
                 e_trap(INV_OP+E_IEEE,6,E_TMSG,5,
                        E_TDBL+E_TEXT(7),&r,E_TDBL|E_TRES,&r);
              }

           /* number is not an integer */
           else if (expo<MANTL-1)
              {
              if (expo>=0)
                 {
                 b_shru(mant,2*D_U_RATIO,(MANTL-1)-expo);
                 b_shlu(mant,D_U_RATIO,(MANTL-1)-expo);
                 }
              else
                 {
                 B_CLEAR(mant,D_U_RATIO)
                 expo = -CHARAC;
                 }

              b_comp(&r,expo,mant,vz);

              if (NOT(vz) && NOT(b_test(D_U_RATIO,&mant[D_U_RATIO])))
                 R_ASSIGN(r,r_succ(r));
              }
           }

        E_TPOPP("r_ceil")
        return(r);
        }

