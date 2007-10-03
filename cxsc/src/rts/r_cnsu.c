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

/* CVS $Id: r_cnsu.c,v 1.9 2007/05/16 14:59:36 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : r_cnsu.c                              */
/*                                                              */
/*      Entries         : a_real r_cnsu(str)                    */
/*                        char *str;                            */
/*                                                              */
/*      Arguments       : str - input string                    */
/*                                                              */
/*      Description     : Convert a character string            */
/*                        to IEEE double format rounded         */
/*                        upwards.                              */
/*                                                              */
/****************************************************************/

#ifndef ALL_IN_ONE
#ifdef AIX
#include "/u/p88c/runtime/o_defs.h"
#else
#include "o_defs.h"
#endif
#define local
extern a_real *r_zero;
#endif

#ifdef LINT_ARGS
local a_real r_cnsu(char *str)
#else
local a_real r_cnsu(str)

char *str;
#endif
        {
        a_real s;
        a_char *next;

        E_TPUSH("r_cnsu")

        R_ASSIGN(s,*r_zero);
        r_conv((a_char *) str,&s,(a_intg)1,&next);

        E_TPOPP("r_cnsu")
        return(s);
        }

