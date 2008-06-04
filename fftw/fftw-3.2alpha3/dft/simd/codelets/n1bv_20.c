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
/* Generated on Tue Nov 13 17:28:16 EST 2007 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_notw_c -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -sign 1 -n 20 -name n1bv_20 -include n1b.h */

/*
 * This function contains 104 FP additions, 50 FP multiplications,
 * (or, 58 additions, 4 multiplications, 46 fused multiply/add),
 * 71 stack variables, and 40 memory accesses
 */
#include "n1b.h"

static void n1bv_20(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DVK(KP618033988, +0.618033988749894848204586834365638117720309180);
     DVK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DVK(KP250000000, +0.250000000000000000000000000000000000000000000);
     INT i;
     const R *xi;
     R *xo;
     xi = ii;
     xo = io;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V TS, TA, TN, TV, TK, TU, TR, Tl;
	  {
	       V T3, TE, T1r, T13, Ta, TL, Tz, TG, Ts, TF, Th, TM, T1u, T1C, T1n;
	       V T1a, T1m, T1h, T1x, T1D, Tk, Ti;
	       {
		    V T1, T2, TC, TD;
		    T1 = LD(&(xi[0]), ivs, &(xi[0]));
		    T2 = LD(&(xi[WS(is, 10)]), ivs, &(xi[0]));
		    TC = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
		    TD = LD(&(xi[WS(is, 15)]), ivs, &(xi[WS(is, 1)]));
		    {
			 V T14, T6, T1c, Tv, Tm, T1f, Ty, T17, T9, Tn, Tp, T1b, Td, Tq, Te;
			 V Tf, T15, To;
			 {
			      V Tw, Tx, T7, T8, Tb, Tc;
			      {
				   V T4, T5, Tt, Tu, T11, T12;
				   T4 = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
				   T5 = LD(&(xi[WS(is, 14)]), ivs, &(xi[0]));
				   Tt = LD(&(xi[WS(is, 13)]), ivs, &(xi[WS(is, 1)]));
				   Tu = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
				   Tw = LD(&(xi[WS(is, 17)]), ivs, &(xi[WS(is, 1)]));
				   T3 = VSUB(T1, T2);
				   T11 = VADD(T1, T2);
				   TE = VSUB(TC, TD);
				   T12 = VADD(TC, TD);
				   T14 = VADD(T4, T5);
				   T6 = VSUB(T4, T5);
				   T1c = VADD(Tt, Tu);
				   Tv = VSUB(Tt, Tu);
				   Tx = LD(&(xi[WS(is, 7)]), ivs, &(xi[WS(is, 1)]));
				   T7 = LD(&(xi[WS(is, 16)]), ivs, &(xi[0]));
				   T8 = LD(&(xi[WS(is, 6)]), ivs, &(xi[0]));
				   T1r = VADD(T11, T12);
				   T13 = VSUB(T11, T12);
			      }
			      Tb = LD(&(xi[WS(is, 8)]), ivs, &(xi[0]));
			      Tc = LD(&(xi[WS(is, 18)]), ivs, &(xi[0]));
			      Tm = LD(&(xi[WS(is, 9)]), ivs, &(xi[WS(is, 1)]));
			      T1f = VADD(Tw, Tx);
			      Ty = VSUB(Tw, Tx);
			      T17 = VADD(T7, T8);
			      T9 = VSUB(T7, T8);
			      Tn = LD(&(xi[WS(is, 19)]), ivs, &(xi[WS(is, 1)]));
			      Tp = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
			      T1b = VADD(Tb, Tc);
			      Td = VSUB(Tb, Tc);
			      Tq = LD(&(xi[WS(is, 11)]), ivs, &(xi[WS(is, 1)]));
			      Te = LD(&(xi[WS(is, 12)]), ivs, &(xi[0]));
			      Tf = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
			 }
			 Ta = VADD(T6, T9);
			 TL = VSUB(T6, T9);
			 T15 = VADD(Tm, Tn);
			 To = VSUB(Tm, Tn);
			 Tz = VSUB(Tv, Ty);
			 TG = VADD(Tv, Ty);
			 {
			      V T1d, T1v, T18, Tr, T1e, Tg, T16, T1s;
			      T1d = VSUB(T1b, T1c);
			      T1v = VADD(T1b, T1c);
			      T18 = VADD(Tp, Tq);
			      Tr = VSUB(Tp, Tq);
			      T1e = VADD(Te, Tf);
			      Tg = VSUB(Te, Tf);
			      T16 = VSUB(T14, T15);
			      T1s = VADD(T14, T15);
			      {
				   V T1t, T19, T1w, T1g;
				   T1t = VADD(T17, T18);
				   T19 = VSUB(T17, T18);
				   Ts = VSUB(To, Tr);
				   TF = VADD(To, Tr);
				   T1w = VADD(T1e, T1f);
				   T1g = VSUB(T1e, T1f);
				   Th = VADD(Td, Tg);
				   TM = VSUB(Td, Tg);
				   T1u = VADD(T1s, T1t);
				   T1C = VSUB(T1s, T1t);
				   T1n = VSUB(T16, T19);
				   T1a = VADD(T16, T19);
				   T1m = VSUB(T1d, T1g);
				   T1h = VADD(T1d, T1g);
				   T1x = VADD(T1v, T1w);
				   T1D = VSUB(T1v, T1w);
			      }
			 }
		    }
	       }
	       Tk = VSUB(Ta, Th);
	       Ti = VADD(Ta, Th);
	       {
		    V TJ, T1k, T1A, TZ, Tj, T1E, T1G, TI, T10, T1j, T1z, T1i, T1y, TH;
		    TJ = VSUB(TF, TG);
		    TH = VADD(TF, TG);
		    T1i = VADD(T1a, T1h);
		    T1k = VSUB(T1a, T1h);
		    T1y = VADD(T1u, T1x);
		    T1A = VSUB(T1u, T1x);
		    TZ = VADD(T3, Ti);
		    Tj = VFNMS(LDK(KP250000000), Ti, T3);
		    T1E = VMUL(LDK(KP951056516), VFMA(LDK(KP618033988), T1D, T1C));
		    T1G = VMUL(LDK(KP951056516), VFNMS(LDK(KP618033988), T1C, T1D));
		    TI = VFNMS(LDK(KP250000000), TH, TE);
		    T10 = VADD(TE, TH);
		    T1j = VFNMS(LDK(KP250000000), T1i, T13);
		    ST(&(xo[0]), VADD(T1r, T1y), ovs, &(xo[0]));
		    T1z = VFNMS(LDK(KP250000000), T1y, T1r);
		    ST(&(xo[WS(os, 10)]), VADD(T13, T1i), ovs, &(xo[0]));
		    {
			 V T1p, T1l, T1o, T1q, T1F, T1B;
			 TS = VFNMS(LDK(KP618033988), Ts, Tz);
			 TA = VFMA(LDK(KP618033988), Tz, Ts);
			 TN = VFMA(LDK(KP618033988), TM, TL);
			 TV = VFNMS(LDK(KP618033988), TL, TM);
			 ST(&(xo[WS(os, 5)]), VFMAI(T10, TZ), ovs, &(xo[WS(os, 1)]));
			 ST(&(xo[WS(os, 15)]), VFNMSI(T10, TZ), ovs, &(xo[WS(os, 1)]));
			 T1p = VFMA(LDK(KP559016994), T1k, T1j);
			 T1l = VFNMS(LDK(KP559016994), T1k, T1j);
			 T1o = VMUL(LDK(KP951056516), VFNMS(LDK(KP618033988), T1n, T1m));
			 T1q = VMUL(LDK(KP951056516), VFMA(LDK(KP618033988), T1m, T1n));
			 T1F = VFNMS(LDK(KP559016994), T1A, T1z);
			 T1B = VFMA(LDK(KP559016994), T1A, T1z);
			 ST(&(xo[WS(os, 14)]), VFNMSI(T1q, T1p), ovs, &(xo[0]));
			 ST(&(xo[WS(os, 6)]), VFMAI(T1q, T1p), ovs, &(xo[0]));
			 ST(&(xo[WS(os, 18)]), VFMAI(T1o, T1l), ovs, &(xo[0]));
			 ST(&(xo[WS(os, 2)]), VFNMSI(T1o, T1l), ovs, &(xo[0]));
			 ST(&(xo[WS(os, 16)]), VFMAI(T1E, T1B), ovs, &(xo[0]));
			 ST(&(xo[WS(os, 4)]), VFNMSI(T1E, T1B), ovs, &(xo[0]));
			 ST(&(xo[WS(os, 12)]), VFNMSI(T1G, T1F), ovs, &(xo[0]));
			 ST(&(xo[WS(os, 8)]), VFMAI(T1G, T1F), ovs, &(xo[0]));
			 TK = VFMA(LDK(KP559016994), TJ, TI);
			 TU = VFNMS(LDK(KP559016994), TJ, TI);
			 TR = VFNMS(LDK(KP559016994), Tk, Tj);
			 Tl = VFMA(LDK(KP559016994), Tk, Tj);
		    }
	       }
	  }
	  {
	       V TY, TW, TO, TQ, TB, TP, TX, TT;
	       TY = VFMA(LDK(KP951056516), TV, TU);
	       TW = VFNMS(LDK(KP951056516), TV, TU);
	       TO = VFMA(LDK(KP951056516), TN, TK);
	       TQ = VFNMS(LDK(KP951056516), TN, TK);
	       TB = VFNMS(LDK(KP951056516), TA, Tl);
	       TP = VFMA(LDK(KP951056516), TA, Tl);
	       TX = VFNMS(LDK(KP951056516), TS, TR);
	       TT = VFMA(LDK(KP951056516), TS, TR);
	       ST(&(xo[WS(os, 9)]), VFMAI(TQ, TP), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 11)]), VFNMSI(TQ, TP), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 1)]), VFMAI(TO, TB), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 19)]), VFNMSI(TO, TB), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 17)]), VFMAI(TW, TT), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 3)]), VFNMSI(TW, TT), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 13)]), VFMAI(TY, TX), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 7)]), VFNMSI(TY, TX), ovs, &(xo[WS(os, 1)]));
	  }
     }
}

static const kdft_desc desc = { 20, "n1bv_20", {58, 4, 46, 0}, &GENUS, 0, 0, 0, 0 };
void X(codelet_n1bv_20) (planner *p) {
     X(kdft_register) (p, n1bv_20, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_notw_c -simd -compact -variables 4 -pipeline-latency 8 -sign 1 -n 20 -name n1bv_20 -include n1b.h */

/*
 * This function contains 104 FP additions, 24 FP multiplications,
 * (or, 92 additions, 12 multiplications, 12 fused multiply/add),
 * 53 stack variables, and 40 memory accesses
 */
#include "n1b.h"

static void n1bv_20(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DVK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DVK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DVK(KP559016994, +0.559016994374947424102293417182819058860154590);
     INT i;
     const R *xi;
     R *xo;
     xi = ii;
     xo = io;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V T3, T1y, TH, T1i, Ts, TL, TM, Tz, T13, T16, T1j, T1u, T1v, T1w, T1r;
	  V T1s, T1t, T1a, T1d, T1k, Ti, Tk, TE, TI, TZ, T10;
	  {
	       V T1, T2, T1g, TF, TG, T1h;
	       T1 = LD(&(xi[0]), ivs, &(xi[0]));
	       T2 = LD(&(xi[WS(is, 10)]), ivs, &(xi[0]));
	       T1g = VADD(T1, T2);
	       TF = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
	       TG = LD(&(xi[WS(is, 15)]), ivs, &(xi[WS(is, 1)]));
	       T1h = VADD(TF, TG);
	       T3 = VSUB(T1, T2);
	       T1y = VADD(T1g, T1h);
	       TH = VSUB(TF, TG);
	       T1i = VSUB(T1g, T1h);
	  }
	  {
	       V T6, T11, Tv, T19, Ty, T1c, T9, T14, Td, T18, To, T12, Tr, T15, Tg;
	       V T1b;
	       {
		    V T4, T5, Tt, Tu;
		    T4 = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
		    T5 = LD(&(xi[WS(is, 14)]), ivs, &(xi[0]));
		    T6 = VSUB(T4, T5);
		    T11 = VADD(T4, T5);
		    Tt = LD(&(xi[WS(is, 13)]), ivs, &(xi[WS(is, 1)]));
		    Tu = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
		    Tv = VSUB(Tt, Tu);
		    T19 = VADD(Tt, Tu);
	       }
	       {
		    V Tw, Tx, T7, T8;
		    Tw = LD(&(xi[WS(is, 17)]), ivs, &(xi[WS(is, 1)]));
		    Tx = LD(&(xi[WS(is, 7)]), ivs, &(xi[WS(is, 1)]));
		    Ty = VSUB(Tw, Tx);
		    T1c = VADD(Tw, Tx);
		    T7 = LD(&(xi[WS(is, 16)]), ivs, &(xi[0]));
		    T8 = LD(&(xi[WS(is, 6)]), ivs, &(xi[0]));
		    T9 = VSUB(T7, T8);
		    T14 = VADD(T7, T8);
	       }
	       {
		    V Tb, Tc, Tm, Tn;
		    Tb = LD(&(xi[WS(is, 8)]), ivs, &(xi[0]));
		    Tc = LD(&(xi[WS(is, 18)]), ivs, &(xi[0]));
		    Td = VSUB(Tb, Tc);
		    T18 = VADD(Tb, Tc);
		    Tm = LD(&(xi[WS(is, 9)]), ivs, &(xi[WS(is, 1)]));
		    Tn = LD(&(xi[WS(is, 19)]), ivs, &(xi[WS(is, 1)]));
		    To = VSUB(Tm, Tn);
		    T12 = VADD(Tm, Tn);
	       }
	       {
		    V Tp, Tq, Te, Tf;
		    Tp = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
		    Tq = LD(&(xi[WS(is, 11)]), ivs, &(xi[WS(is, 1)]));
		    Tr = VSUB(Tp, Tq);
		    T15 = VADD(Tp, Tq);
		    Te = LD(&(xi[WS(is, 12)]), ivs, &(xi[0]));
		    Tf = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
		    Tg = VSUB(Te, Tf);
		    T1b = VADD(Te, Tf);
	       }
	       Ts = VSUB(To, Tr);
	       TL = VSUB(T6, T9);
	       TM = VSUB(Td, Tg);
	       Tz = VSUB(Tv, Ty);
	       T13 = VSUB(T11, T12);
	       T16 = VSUB(T14, T15);
	       T1j = VADD(T13, T16);
	       T1u = VADD(T18, T19);
	       T1v = VADD(T1b, T1c);
	       T1w = VADD(T1u, T1v);
	       T1r = VADD(T11, T12);
	       T1s = VADD(T14, T15);
	       T1t = VADD(T1r, T1s);
	       T1a = VSUB(T18, T19);
	       T1d = VSUB(T1b, T1c);
	       T1k = VADD(T1a, T1d);
	       {
		    V Ta, Th, TC, TD;
		    Ta = VADD(T6, T9);
		    Th = VADD(Td, Tg);
		    Ti = VADD(Ta, Th);
		    Tk = VMUL(LDK(KP559016994), VSUB(Ta, Th));
		    TC = VADD(To, Tr);
		    TD = VADD(Tv, Ty);
		    TE = VMUL(LDK(KP559016994), VSUB(TC, TD));
		    TI = VADD(TC, TD);
	       }
	  }
	  TZ = VADD(T3, Ti);
	  T10 = VBYI(VADD(TH, TI));
	  ST(&(xo[WS(os, 15)]), VSUB(TZ, T10), ovs, &(xo[WS(os, 1)]));
	  ST(&(xo[WS(os, 5)]), VADD(TZ, T10), ovs, &(xo[WS(os, 1)]));
	  {
	       V T1x, T1z, T1A, T1E, T1G, T1C, T1D, T1F, T1B;
	       T1x = VMUL(LDK(KP559016994), VSUB(T1t, T1w));
	       T1z = VADD(T1t, T1w);
	       T1A = VFNMS(LDK(KP250000000), T1z, T1y);
	       T1C = VSUB(T1r, T1s);
	       T1D = VSUB(T1u, T1v);
	       T1E = VBYI(VFMA(LDK(KP951056516), T1C, VMUL(LDK(KP587785252), T1D)));
	       T1G = VBYI(VFNMS(LDK(KP951056516), T1D, VMUL(LDK(KP587785252), T1C)));
	       ST(&(xo[0]), VADD(T1y, T1z), ovs, &(xo[0]));
	       T1F = VSUB(T1A, T1x);
	       ST(&(xo[WS(os, 8)]), VSUB(T1F, T1G), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 12)]), VADD(T1G, T1F), ovs, &(xo[0]));
	       T1B = VADD(T1x, T1A);
	       ST(&(xo[WS(os, 4)]), VSUB(T1B, T1E), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 16)]), VADD(T1E, T1B), ovs, &(xo[0]));
	  }
	  {
	       V T1n, T1l, T1m, T1f, T1p, T17, T1e, T1q, T1o;
	       T1n = VMUL(LDK(KP559016994), VSUB(T1j, T1k));
	       T1l = VADD(T1j, T1k);
	       T1m = VFNMS(LDK(KP250000000), T1l, T1i);
	       T17 = VSUB(T13, T16);
	       T1e = VSUB(T1a, T1d);
	       T1f = VBYI(VFNMS(LDK(KP951056516), T1e, VMUL(LDK(KP587785252), T17)));
	       T1p = VBYI(VFMA(LDK(KP951056516), T17, VMUL(LDK(KP587785252), T1e)));
	       ST(&(xo[WS(os, 10)]), VADD(T1i, T1l), ovs, &(xo[0]));
	       T1q = VADD(T1n, T1m);
	       ST(&(xo[WS(os, 6)]), VADD(T1p, T1q), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 14)]), VSUB(T1q, T1p), ovs, &(xo[0]));
	       T1o = VSUB(T1m, T1n);
	       ST(&(xo[WS(os, 2)]), VADD(T1f, T1o), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 18)]), VSUB(T1o, T1f), ovs, &(xo[0]));
	  }
	  {
	       V TA, TN, TU, TS, TK, TV, Tl, TR, TJ, Tj;
	       TA = VFNMS(LDK(KP951056516), Tz, VMUL(LDK(KP587785252), Ts));
	       TN = VFNMS(LDK(KP951056516), TM, VMUL(LDK(KP587785252), TL));
	       TU = VFMA(LDK(KP951056516), TL, VMUL(LDK(KP587785252), TM));
	       TS = VFMA(LDK(KP951056516), Ts, VMUL(LDK(KP587785252), Tz));
	       TJ = VFNMS(LDK(KP250000000), TI, TH);
	       TK = VSUB(TE, TJ);
	       TV = VADD(TE, TJ);
	       Tj = VFNMS(LDK(KP250000000), Ti, T3);
	       Tl = VSUB(Tj, Tk);
	       TR = VADD(Tk, Tj);
	       {
		    V TB, TO, TX, TY;
		    TB = VSUB(Tl, TA);
		    TO = VBYI(VSUB(TK, TN));
		    ST(&(xo[WS(os, 17)]), VSUB(TB, TO), ovs, &(xo[WS(os, 1)]));
		    ST(&(xo[WS(os, 3)]), VADD(TB, TO), ovs, &(xo[WS(os, 1)]));
		    TX = VADD(TR, TS);
		    TY = VBYI(VSUB(TV, TU));
		    ST(&(xo[WS(os, 11)]), VSUB(TX, TY), ovs, &(xo[WS(os, 1)]));
		    ST(&(xo[WS(os, 9)]), VADD(TX, TY), ovs, &(xo[WS(os, 1)]));
	       }
	       {
		    V TP, TQ, TT, TW;
		    TP = VADD(Tl, TA);
		    TQ = VBYI(VADD(TN, TK));
		    ST(&(xo[WS(os, 13)]), VSUB(TP, TQ), ovs, &(xo[WS(os, 1)]));
		    ST(&(xo[WS(os, 7)]), VADD(TP, TQ), ovs, &(xo[WS(os, 1)]));
		    TT = VSUB(TR, TS);
		    TW = VBYI(VADD(TU, TV));
		    ST(&(xo[WS(os, 19)]), VSUB(TT, TW), ovs, &(xo[WS(os, 1)]));
		    ST(&(xo[WS(os, 1)]), VADD(TT, TW), ovs, &(xo[WS(os, 1)]));
	       }
	  }
     }
}

static const kdft_desc desc = { 20, "n1bv_20", {92, 12, 12, 0}, &GENUS, 0, 0, 0, 0 };
void X(codelet_n1bv_20) (planner *p) {
     X(kdft_register) (p, n1bv_20, &desc);
}

#endif				/* HAVE_FMA */
