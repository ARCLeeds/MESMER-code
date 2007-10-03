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

/* CVS $Id: q_cth1.cpp,v 1.3 2007/05/16 14:59:12 cxsc Exp $ */

#ifndef Q_CTH1_CPP
#define Q_CTH1_CPP

#include "fi_lib.hpp" 

namespace fi_lib{

 using cxsc::real;
 
 real q_cth1(real x){
  real absx, res;
  int sgn;

  if (x<0) { sgn=-1; absx=-x; }
  else     { sgn=1; absx=x;  }

  if (absx>22.875) res=sgn;
  else if (absx>=q_ln2h) res=sgn*(1+2/(q_ep1(2*absx)-1));
  else res=sgn*(1+2/q_epm1(2*absx));

  return(res);
 }

} // Namespace

#endif

