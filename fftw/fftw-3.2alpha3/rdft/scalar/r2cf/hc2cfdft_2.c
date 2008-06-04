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
/* Generated on Tue Nov 13 17:51:39 EST 2007 */

#include "codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_hc2cdft -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -n 2 -dit -name hc2cfdft_2 -include hc2cf.h */

/*
 * This function contains 10 FP additions, 8 FP multiplications,
 * (or, 8 additions, 6 multiplications, 2 fused multiply/add),
 * 12 stack variables, and 8 memory accesses
 */
#include "hc2cf.h"

static void hc2cfdft_2(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 2); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 2, MAKE_VOLATILE_STRIDE(rs)) {
	  E T9, Ta, T3, Tc, T7, T4;
	  {
	       E T1, T2, T5, T6;
	       T1 = Ip[0];
	       T2 = Im[0];
	       T5 = Rm[0];
	       T6 = Rp[0];
	       T9 = W[1];
	       Ta = T1 + T2;
	       T3 = T1 - T2;
	       Tc = T6 + T5;
	       T7 = T5 - T6;
	       T4 = W[0];
	  }
	  {
	       E Td, T8, Te, Tb;
	       Td = T9 * T7;
	       T8 = T4 * T7;
	       Te = FMA(T4, Ta, Td);
	       Tb = FNMS(T9, Ta, T8);
	       Rp[0] = KP500000000 * (Tc + Te);
	       Rm[0] = KP500000000 * (Tc - Te);
	       Im[0] = KP500000000 * (Tb - T3);
	       Ip[0] = KP500000000 * (T3 + Tb);
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 2},
     {TW_NEXT, 1, 0}
};

static const hc2c_desc desc = { 2, "hc2cfdft_2", twinstr, &GENUS, {8, 6, 2, 0} };

void X(codelet_hc2cfdft_2) (planner *p) {
     X(khc2c_register) (p, hc2cfdft_2, &desc, HC2C_VIA_DFT);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_hc2cdft -compact -variables 4 -pipeline-latency 4 -n 2 -dit -name hc2cfdft_2 -include hc2cf.h */

/*
 * This function contains 10 FP additions, 8 FP multiplications,
 * (or, 8 additions, 6 multiplications, 2 fused multiply/add),
 * 10 stack variables, and 8 memory accesses
 */
#include "hc2cf.h"

static void hc2cfdft_2(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 2); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 2, MAKE_VOLATILE_STRIDE(rs)) {
	  E T3, T9, T7, Tb;
	  {
	       E T1, T2, T5, T6;
	       T1 = Ip[0];
	       T2 = Im[0];
	       T3 = T1 - T2;
	       T9 = T1 + T2;
	       T5 = Rm[0];
	       T6 = Rp[0];
	       T7 = T5 - T6;
	       Tb = T6 + T5;
	  }
	  {
	       E Ta, Tc, T4, T8;
	       T4 = W[0];
	       T8 = W[1];
	       Ta = FNMS(T8, T9, T4 * T7);
	       Tc = FMA(T8, T7, T4 * T9);
	       Ip[0] = KP500000000 * (T3 + Ta);
	       Rp[0] = KP500000000 * (Tb + Tc);
	       Im[0] = KP500000000 * (Ta - T3);
	       Rm[0] = KP500000000 * (Tb - Tc);
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 2},
     {TW_NEXT, 1, 0}
};

static const hc2c_desc desc = { 2, "hc2cfdft_2", twinstr, &GENUS, {8, 6, 2, 0} };

void X(codelet_hc2cfdft_2) (planner *p) {
     X(khc2c_register) (p, hc2cfdft_2, &desc, HC2C_VIA_DFT);
}
#endif				/* HAVE_FMA */
