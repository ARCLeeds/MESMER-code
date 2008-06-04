/*
 * Copyright (c) 2003, 2007 Matteo Frigo
 * Copyright (c) 2003, 2007 Massachusetts Institute of Technology
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Tue Nov 13 18:00:19 EST 2007 */

#include "codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_r2cb -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -sign 1 -n 2 -name r2cbIII_2 -dft-III -include r2cbIII.h */

/*
 * This function contains 0 FP additions, 2 FP multiplications,
 * (or, 0 additions, 2 multiplications, 0 fused multiply/add),
 * 4 stack variables, and 4 memory accesses
 */
#include "r2cbIII.h"

static void r2cbIII_2(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     INT i;
     for (i = v; i > 0; i = i - 1, R0 = R0 + ovs, R1 = R1 + ovs, Cr = Cr + ivs, Ci = Ci + ivs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	  E T1, T2;
	  T1 = Cr[0];
	  T2 = Ci[0];
	  R0[0] = KP2_000000000 * T1;
	  R1[0] = -(KP2_000000000 * T2);
     }
}

static const kr2c_desc desc = { 2, "r2cbIII_2", {0, 2, 0, 0}, &GENUS };

void X(codelet_r2cbIII_2) (planner *p) {
     X(kr2c_register) (p, r2cbIII_2, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_r2cb -compact -variables 4 -pipeline-latency 4 -sign 1 -n 2 -name r2cbIII_2 -dft-III -include r2cbIII.h */

/*
 * This function contains 0 FP additions, 2 FP multiplications,
 * (or, 0 additions, 2 multiplications, 0 fused multiply/add),
 * 4 stack variables, and 4 memory accesses
 */
#include "r2cbIII.h"

static void r2cbIII_2(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     INT i;
     for (i = v; i > 0; i = i - 1, R0 = R0 + ovs, R1 = R1 + ovs, Cr = Cr + ivs, Ci = Ci + ivs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	  E T1, T2;
	  T1 = Cr[0];
	  T2 = Ci[0];
	  R0[0] = KP2_000000000 * T1;
	  R1[0] = -(KP2_000000000 * T2);
     }
}

static const kr2c_desc desc = { 2, "r2cbIII_2", {0, 2, 0, 0}, &GENUS };

void X(codelet_r2cbIII_2) (planner *p) {
     X(kr2c_register) (p, r2cbIII_2, &desc);
}

#endif				/* HAVE_FMA */
