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
/* Generated on Tue Nov 13 17:38:26 EST 2007 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_twiddle_c -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -n 20 -name t2bv_20 -include t2b.h -sign 1 */

/*
 * This function contains 123 FP additions, 88 FP multiplications,
 * (or, 77 additions, 42 multiplications, 46 fused multiply/add),
 * 68 stack variables, and 40 memory accesses
 */
#include "t2b.h"

static void t2bv_20(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DVK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DVK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DVK(KP618033988, +0.618033988749894848204586834365638117720309180);
     INT m;
     R *x;
     x = ii;
     for (m = mb, W = W + (mb * ((TWVL / VL) * 38)); m < me; m = m + VL, x = x + (VL * ms), W = W + (TWVL * 38), MAKE_VOLATILE_STRIDE(rs)) {
	  V T4, TX, T1m, T1K, T1y, Tk, Tf, T14, TQ, TZ, T1O, T1w, T1L, T1p, T1M;
	  V T1s, TF, TY, T1x, Tp;
	  {
	       V T1, TV, T2, TT;
	       T1 = LD(&(x[0]), ms, &(x[0]));
	       TV = LD(&(x[WS(rs, 15)]), ms, &(x[WS(rs, 1)]));
	       T2 = LD(&(x[WS(rs, 10)]), ms, &(x[0]));
	       TT = LD(&(x[WS(rs, 5)]), ms, &(x[WS(rs, 1)]));
	       {
		    V T9, T1n, TK, T1v, TP, Te, T1q, T1u, TB, TD, Tm, T1o, Tz, Tn, T1r;
		    V TE, To;
		    {
			 V TM, TO, Ta, Tc;
			 {
			      V T5, T7, TG, TI, T1k, T1l;
			      T5 = LD(&(x[WS(rs, 4)]), ms, &(x[0]));
			      T7 = LD(&(x[WS(rs, 14)]), ms, &(x[0]));
			      TG = LD(&(x[WS(rs, 13)]), ms, &(x[WS(rs, 1)]));
			      TI = LD(&(x[WS(rs, 3)]), ms, &(x[WS(rs, 1)]));
			      {
				   V TW, T3, TU, T6, T8, TH, TJ, TL, TN;
				   TL = LD(&(x[WS(rs, 17)]), ms, &(x[WS(rs, 1)]));
				   TW = BYTW(&(W[TWVL * 28]), TV);
				   T3 = BYTW(&(W[TWVL * 18]), T2);
				   TU = BYTW(&(W[TWVL * 8]), TT);
				   T6 = BYTW(&(W[TWVL * 6]), T5);
				   T8 = BYTW(&(W[TWVL * 26]), T7);
				   TH = BYTW(&(W[TWVL * 24]), TG);
				   TJ = BYTW(&(W[TWVL * 4]), TI);
				   TM = BYTW(&(W[TWVL * 32]), TL);
				   TN = LD(&(x[WS(rs, 7)]), ms, &(x[WS(rs, 1)]));
				   T4 = VSUB(T1, T3);
				   T1k = VADD(T1, T3);
				   TX = VSUB(TU, TW);
				   T1l = VADD(TU, TW);
				   T9 = VSUB(T6, T8);
				   T1n = VADD(T6, T8);
				   TK = VSUB(TH, TJ);
				   T1v = VADD(TH, TJ);
				   TO = BYTW(&(W[TWVL * 12]), TN);
			      }
			      Ta = LD(&(x[WS(rs, 16)]), ms, &(x[0]));
			      T1m = VSUB(T1k, T1l);
			      T1K = VADD(T1k, T1l);
			      Tc = LD(&(x[WS(rs, 6)]), ms, &(x[0]));
			 }
			 {
			      V Tb, Tx, Td, Th, Tj, Tw, Tg, Ti, Tv;
			      Tg = LD(&(x[WS(rs, 8)]), ms, &(x[0]));
			      Ti = LD(&(x[WS(rs, 18)]), ms, &(x[0]));
			      Tv = LD(&(x[WS(rs, 9)]), ms, &(x[WS(rs, 1)]));
			      TP = VSUB(TM, TO);
			      T1y = VADD(TM, TO);
			      Tb = BYTW(&(W[TWVL * 30]), Ta);
			      Tx = LD(&(x[WS(rs, 19)]), ms, &(x[WS(rs, 1)]));
			      Td = BYTW(&(W[TWVL * 10]), Tc);
			      Th = BYTW(&(W[TWVL * 14]), Tg);
			      Tj = BYTW(&(W[TWVL * 34]), Ti);
			      Tw = BYTW(&(W[TWVL * 16]), Tv);
			      {
				   V TA, TC, Ty, Tl;
				   TA = LD(&(x[WS(rs, 1)]), ms, &(x[WS(rs, 1)]));
				   TC = LD(&(x[WS(rs, 11)]), ms, &(x[WS(rs, 1)]));
				   Tl = LD(&(x[WS(rs, 12)]), ms, &(x[0]));
				   Ty = BYTW(&(W[TWVL * 36]), Tx);
				   Te = VSUB(Tb, Td);
				   T1q = VADD(Tb, Td);
				   Tk = VSUB(Th, Tj);
				   T1u = VADD(Th, Tj);
				   TB = BYTW(&(W[0]), TA);
				   TD = BYTW(&(W[TWVL * 20]), TC);
				   Tm = BYTW(&(W[TWVL * 22]), Tl);
				   T1o = VADD(Tw, Ty);
				   Tz = VSUB(Tw, Ty);
				   Tn = LD(&(x[WS(rs, 2)]), ms, &(x[0]));
			      }
			 }
		    }
		    Tf = VADD(T9, Te);
		    T14 = VSUB(T9, Te);
		    TQ = VSUB(TK, TP);
		    TZ = VADD(TK, TP);
		    T1r = VADD(TB, TD);
		    TE = VSUB(TB, TD);
		    T1O = VADD(T1u, T1v);
		    T1w = VSUB(T1u, T1v);
		    To = BYTW(&(W[TWVL * 2]), Tn);
		    T1L = VADD(T1n, T1o);
		    T1p = VSUB(T1n, T1o);
		    T1M = VADD(T1q, T1r);
		    T1s = VSUB(T1q, T1r);
		    TF = VSUB(Tz, TE);
		    TY = VADD(Tz, TE);
		    T1x = VADD(Tm, To);
		    Tp = VSUB(Tm, To);
	       }
	  }
	  {
	       V T1V, T1N, T12, T1b, TR, T1G, T1t, T1z, T1P, Tq, T15, T11, T1j, T10;
	       T1V = VSUB(T1L, T1M);
	       T1N = VADD(T1L, T1M);
	       T12 = VSUB(TY, TZ);
	       T10 = VADD(TY, TZ);
	       T1b = VFNMS(LDK(KP618033988), TF, TQ);
	       TR = VFMA(LDK(KP618033988), TQ, TF);
	       T1G = VSUB(T1p, T1s);
	       T1t = VADD(T1p, T1s);
	       T1z = VSUB(T1x, T1y);
	       T1P = VADD(T1x, T1y);
	       Tq = VADD(Tk, Tp);
	       T15 = VSUB(Tk, Tp);
	       T11 = VFNMS(LDK(KP250000000), T10, TX);
	       T1j = VADD(TX, T10);
	       {
		    V T1J, T1H, T1D, T1Z, T1X, T1T, T1f, T1h, T19, T17, T1C, T1S, T1a, Tu, T1F;
		    V T1A;
		    T1F = VSUB(T1w, T1z);
		    T1A = VADD(T1w, T1z);
		    {
			 V T1W, T1Q, Tt, Tr;
			 T1W = VSUB(T1O, T1P);
			 T1Q = VADD(T1O, T1P);
			 Tt = VSUB(Tf, Tq);
			 Tr = VADD(Tf, Tq);
			 {
			      V T1e, T16, T1d, T13;
			      T1e = VFNMS(LDK(KP618033988), T14, T15);
			      T16 = VFMA(LDK(KP618033988), T15, T14);
			      T1d = VFNMS(LDK(KP559016994), T12, T11);
			      T13 = VFMA(LDK(KP559016994), T12, T11);
			      T1J = VMUL(LDK(KP951056516), VFMA(LDK(KP618033988), T1F, T1G));
			      T1H = VMUL(LDK(KP951056516), VFNMS(LDK(KP618033988), T1G, T1F));
			      {
				   V T1B, T1R, Ts, T1i;
				   T1B = VADD(T1t, T1A);
				   T1D = VSUB(T1t, T1A);
				   T1Z = VMUL(LDK(KP951056516), VFNMS(LDK(KP618033988), T1V, T1W));
				   T1X = VMUL(LDK(KP951056516), VFMA(LDK(KP618033988), T1W, T1V));
				   T1R = VADD(T1N, T1Q);
				   T1T = VSUB(T1N, T1Q);
				   Ts = VFNMS(LDK(KP250000000), Tr, T4);
				   T1i = VADD(T4, Tr);
				   T1f = VFNMS(LDK(KP951056516), T1e, T1d);
				   T1h = VFMA(LDK(KP951056516), T1e, T1d);
				   T19 = VFNMS(LDK(KP951056516), T16, T13);
				   T17 = VFMA(LDK(KP951056516), T16, T13);
				   ST(&(x[WS(rs, 10)]), VADD(T1m, T1B), ms, &(x[0]));
				   T1C = VFNMS(LDK(KP250000000), T1B, T1m);
				   ST(&(x[0]), VADD(T1K, T1R), ms, &(x[0]));
				   T1S = VFNMS(LDK(KP250000000), T1R, T1K);
				   T1a = VFNMS(LDK(KP559016994), Tt, Ts);
				   Tu = VFMA(LDK(KP559016994), Tt, Ts);
				   ST(&(x[WS(rs, 5)]), VFMAI(T1j, T1i), ms, &(x[WS(rs, 1)]));
				   ST(&(x[WS(rs, 15)]), VFNMSI(T1j, T1i), ms, &(x[WS(rs, 1)]));
			      }
			 }
		    }
		    {
			 V T1E, T1I, T1U, T1Y;
			 T1E = VFNMS(LDK(KP559016994), T1D, T1C);
			 T1I = VFMA(LDK(KP559016994), T1D, T1C);
			 T1U = VFMA(LDK(KP559016994), T1T, T1S);
			 T1Y = VFNMS(LDK(KP559016994), T1T, T1S);
			 {
			      V T1c, T1g, T18, TS;
			      T1c = VFMA(LDK(KP951056516), T1b, T1a);
			      T1g = VFNMS(LDK(KP951056516), T1b, T1a);
			      T18 = VFMA(LDK(KP951056516), TR, Tu);
			      TS = VFNMS(LDK(KP951056516), TR, Tu);
			      ST(&(x[WS(rs, 18)]), VFMAI(T1H, T1E), ms, &(x[0]));
			      ST(&(x[WS(rs, 2)]), VFNMSI(T1H, T1E), ms, &(x[0]));
			      ST(&(x[WS(rs, 14)]), VFNMSI(T1J, T1I), ms, &(x[0]));
			      ST(&(x[WS(rs, 6)]), VFMAI(T1J, T1I), ms, &(x[0]));
			      ST(&(x[WS(rs, 16)]), VFMAI(T1X, T1U), ms, &(x[0]));
			      ST(&(x[WS(rs, 4)]), VFNMSI(T1X, T1U), ms, &(x[0]));
			      ST(&(x[WS(rs, 12)]), VFNMSI(T1Z, T1Y), ms, &(x[0]));
			      ST(&(x[WS(rs, 8)]), VFMAI(T1Z, T1Y), ms, &(x[0]));
			      ST(&(x[WS(rs, 17)]), VFMAI(T1f, T1c), ms, &(x[WS(rs, 1)]));
			      ST(&(x[WS(rs, 3)]), VFNMSI(T1f, T1c), ms, &(x[WS(rs, 1)]));
			      ST(&(x[WS(rs, 13)]), VFMAI(T1h, T1g), ms, &(x[WS(rs, 1)]));
			      ST(&(x[WS(rs, 7)]), VFNMSI(T1h, T1g), ms, &(x[WS(rs, 1)]));
			      ST(&(x[WS(rs, 9)]), VFMAI(T19, T18), ms, &(x[WS(rs, 1)]));
			      ST(&(x[WS(rs, 11)]), VFNMSI(T19, T18), ms, &(x[WS(rs, 1)]));
			      ST(&(x[WS(rs, 1)]), VFMAI(T17, TS), ms, &(x[WS(rs, 1)]));
			      ST(&(x[WS(rs, 19)]), VFNMSI(T17, TS), ms, &(x[WS(rs, 1)]));
			 }
		    }
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     VTW(0, 3),
     VTW(0, 4),
     VTW(0, 5),
     VTW(0, 6),
     VTW(0, 7),
     VTW(0, 8),
     VTW(0, 9),
     VTW(0, 10),
     VTW(0, 11),
     VTW(0, 12),
     VTW(0, 13),
     VTW(0, 14),
     VTW(0, 15),
     VTW(0, 16),
     VTW(0, 17),
     VTW(0, 18),
     VTW(0, 19),
     {TW_NEXT, VL, 0}
};

static const ct_desc desc = { 20, "t2bv_20", twinstr, &GENUS, {77, 42, 46, 0}, 0, 0, 0 };

void X(codelet_t2bv_20) (planner *p) {
     X(kdft_dit_register) (p, t2bv_20, &desc);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_twiddle_c -simd -compact -variables 4 -pipeline-latency 8 -n 20 -name t2bv_20 -include t2b.h -sign 1 */

/*
 * This function contains 123 FP additions, 62 FP multiplications,
 * (or, 111 additions, 50 multiplications, 12 fused multiply/add),
 * 54 stack variables, and 40 memory accesses
 */
#include "t2b.h"

static void t2bv_20(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DVK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DVK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DVK(KP559016994, +0.559016994374947424102293417182819058860154590);
     INT m;
     R *x;
     x = ii;
     for (m = mb, W = W + (mb * ((TWVL / VL) * 38)); m < me; m = m + VL, x = x + (VL * ms), W = W + (TWVL * 38), MAKE_VOLATILE_STRIDE(rs)) {
	  V T4, T10, T1B, T1R, TF, T14, T15, TQ, Tf, Tq, Tr, T1N, T1O, T1P, T1t;
	  V T1w, T1D, TT, TU, T11, T1K, T1L, T1M, T1m, T1p, T1C, T1i, T1j;
	  {
	       V T1, TZ, T3, TX, TY, T2, TW, T1z, T1A;
	       T1 = LD(&(x[0]), ms, &(x[0]));
	       TY = LD(&(x[WS(rs, 15)]), ms, &(x[WS(rs, 1)]));
	       TZ = BYTW(&(W[TWVL * 28]), TY);
	       T2 = LD(&(x[WS(rs, 10)]), ms, &(x[0]));
	       T3 = BYTW(&(W[TWVL * 18]), T2);
	       TW = LD(&(x[WS(rs, 5)]), ms, &(x[WS(rs, 1)]));
	       TX = BYTW(&(W[TWVL * 8]), TW);
	       T4 = VSUB(T1, T3);
	       T10 = VSUB(TX, TZ);
	       T1z = VADD(T1, T3);
	       T1A = VADD(TX, TZ);
	       T1B = VSUB(T1z, T1A);
	       T1R = VADD(T1z, T1A);
	  }
	  {
	       V T9, T1k, TK, T1s, TP, T1v, Te, T1n, Tk, T1r, Tz, T1l, TE, T1o, Tp;
	       V T1u;
	       {
		    V T6, T8, T5, T7;
		    T5 = LD(&(x[WS(rs, 4)]), ms, &(x[0]));
		    T6 = BYTW(&(W[TWVL * 6]), T5);
		    T7 = LD(&(x[WS(rs, 14)]), ms, &(x[0]));
		    T8 = BYTW(&(W[TWVL * 26]), T7);
		    T9 = VSUB(T6, T8);
		    T1k = VADD(T6, T8);
	       }
	       {
		    V TH, TJ, TG, TI;
		    TG = LD(&(x[WS(rs, 13)]), ms, &(x[WS(rs, 1)]));
		    TH = BYTW(&(W[TWVL * 24]), TG);
		    TI = LD(&(x[WS(rs, 3)]), ms, &(x[WS(rs, 1)]));
		    TJ = BYTW(&(W[TWVL * 4]), TI);
		    TK = VSUB(TH, TJ);
		    T1s = VADD(TH, TJ);
	       }
	       {
		    V TM, TO, TL, TN;
		    TL = LD(&(x[WS(rs, 17)]), ms, &(x[WS(rs, 1)]));
		    TM = BYTW(&(W[TWVL * 32]), TL);
		    TN = LD(&(x[WS(rs, 7)]), ms, &(x[WS(rs, 1)]));
		    TO = BYTW(&(W[TWVL * 12]), TN);
		    TP = VSUB(TM, TO);
		    T1v = VADD(TM, TO);
	       }
	       {
		    V Tb, Td, Ta, Tc;
		    Ta = LD(&(x[WS(rs, 16)]), ms, &(x[0]));
		    Tb = BYTW(&(W[TWVL * 30]), Ta);
		    Tc = LD(&(x[WS(rs, 6)]), ms, &(x[0]));
		    Td = BYTW(&(W[TWVL * 10]), Tc);
		    Te = VSUB(Tb, Td);
		    T1n = VADD(Tb, Td);
	       }
	       {
		    V Th, Tj, Tg, Ti;
		    Tg = LD(&(x[WS(rs, 8)]), ms, &(x[0]));
		    Th = BYTW(&(W[TWVL * 14]), Tg);
		    Ti = LD(&(x[WS(rs, 18)]), ms, &(x[0]));
		    Tj = BYTW(&(W[TWVL * 34]), Ti);
		    Tk = VSUB(Th, Tj);
		    T1r = VADD(Th, Tj);
	       }
	       {
		    V Tw, Ty, Tv, Tx;
		    Tv = LD(&(x[WS(rs, 9)]), ms, &(x[WS(rs, 1)]));
		    Tw = BYTW(&(W[TWVL * 16]), Tv);
		    Tx = LD(&(x[WS(rs, 19)]), ms, &(x[WS(rs, 1)]));
		    Ty = BYTW(&(W[TWVL * 36]), Tx);
		    Tz = VSUB(Tw, Ty);
		    T1l = VADD(Tw, Ty);
	       }
	       {
		    V TB, TD, TA, TC;
		    TA = LD(&(x[WS(rs, 1)]), ms, &(x[WS(rs, 1)]));
		    TB = BYTW(&(W[0]), TA);
		    TC = LD(&(x[WS(rs, 11)]), ms, &(x[WS(rs, 1)]));
		    TD = BYTW(&(W[TWVL * 20]), TC);
		    TE = VSUB(TB, TD);
		    T1o = VADD(TB, TD);
	       }
	       {
		    V Tm, To, Tl, Tn;
		    Tl = LD(&(x[WS(rs, 12)]), ms, &(x[0]));
		    Tm = BYTW(&(W[TWVL * 22]), Tl);
		    Tn = LD(&(x[WS(rs, 2)]), ms, &(x[0]));
		    To = BYTW(&(W[TWVL * 2]), Tn);
		    Tp = VSUB(Tm, To);
		    T1u = VADD(Tm, To);
	       }
	       TF = VSUB(Tz, TE);
	       T14 = VSUB(T9, Te);
	       T15 = VSUB(Tk, Tp);
	       TQ = VSUB(TK, TP);
	       Tf = VADD(T9, Te);
	       Tq = VADD(Tk, Tp);
	       Tr = VADD(Tf, Tq);
	       T1N = VADD(T1r, T1s);
	       T1O = VADD(T1u, T1v);
	       T1P = VADD(T1N, T1O);
	       T1t = VSUB(T1r, T1s);
	       T1w = VSUB(T1u, T1v);
	       T1D = VADD(T1t, T1w);
	       TT = VADD(Tz, TE);
	       TU = VADD(TK, TP);
	       T11 = VADD(TT, TU);
	       T1K = VADD(T1k, T1l);
	       T1L = VADD(T1n, T1o);
	       T1M = VADD(T1K, T1L);
	       T1m = VSUB(T1k, T1l);
	       T1p = VSUB(T1n, T1o);
	       T1C = VADD(T1m, T1p);
	  }
	  T1i = VADD(T4, Tr);
	  T1j = VBYI(VADD(T10, T11));
	  ST(&(x[WS(rs, 15)]), VSUB(T1i, T1j), ms, &(x[WS(rs, 1)]));
	  ST(&(x[WS(rs, 5)]), VADD(T1i, T1j), ms, &(x[WS(rs, 1)]));
	  {
	       V T1Q, T1S, T1T, T1X, T1Z, T1V, T1W, T1Y, T1U;
	       T1Q = VMUL(LDK(KP559016994), VSUB(T1M, T1P));
	       T1S = VADD(T1M, T1P);
	       T1T = VFNMS(LDK(KP250000000), T1S, T1R);
	       T1V = VSUB(T1K, T1L);
	       T1W = VSUB(T1N, T1O);
	       T1X = VBYI(VFMA(LDK(KP951056516), T1V, VMUL(LDK(KP587785252), T1W)));
	       T1Z = VBYI(VFNMS(LDK(KP951056516), T1W, VMUL(LDK(KP587785252), T1V)));
	       ST(&(x[0]), VADD(T1R, T1S), ms, &(x[0]));
	       T1Y = VSUB(T1T, T1Q);
	       ST(&(x[WS(rs, 8)]), VSUB(T1Y, T1Z), ms, &(x[0]));
	       ST(&(x[WS(rs, 12)]), VADD(T1Z, T1Y), ms, &(x[0]));
	       T1U = VADD(T1Q, T1T);
	       ST(&(x[WS(rs, 4)]), VSUB(T1U, T1X), ms, &(x[0]));
	       ST(&(x[WS(rs, 16)]), VADD(T1X, T1U), ms, &(x[0]));
	  }
	  {
	       V T1G, T1E, T1F, T1y, T1I, T1q, T1x, T1J, T1H;
	       T1G = VMUL(LDK(KP559016994), VSUB(T1C, T1D));
	       T1E = VADD(T1C, T1D);
	       T1F = VFNMS(LDK(KP250000000), T1E, T1B);
	       T1q = VSUB(T1m, T1p);
	       T1x = VSUB(T1t, T1w);
	       T1y = VBYI(VFNMS(LDK(KP951056516), T1x, VMUL(LDK(KP587785252), T1q)));
	       T1I = VBYI(VFMA(LDK(KP951056516), T1q, VMUL(LDK(KP587785252), T1x)));
	       ST(&(x[WS(rs, 10)]), VADD(T1B, T1E), ms, &(x[0]));
	       T1J = VADD(T1G, T1F);
	       ST(&(x[WS(rs, 6)]), VADD(T1I, T1J), ms, &(x[0]));
	       ST(&(x[WS(rs, 14)]), VSUB(T1J, T1I), ms, &(x[0]));
	       T1H = VSUB(T1F, T1G);
	       ST(&(x[WS(rs, 2)]), VADD(T1y, T1H), ms, &(x[0]));
	       ST(&(x[WS(rs, 18)]), VSUB(T1H, T1y), ms, &(x[0]));
	  }
	  {
	       V TR, T16, T1d, T1b, T13, T1e, Tu, T1a;
	       TR = VFNMS(LDK(KP951056516), TQ, VMUL(LDK(KP587785252), TF));
	       T16 = VFNMS(LDK(KP951056516), T15, VMUL(LDK(KP587785252), T14));
	       T1d = VFMA(LDK(KP951056516), T14, VMUL(LDK(KP587785252), T15));
	       T1b = VFMA(LDK(KP951056516), TF, VMUL(LDK(KP587785252), TQ));
	       {
		    V TV, T12, Ts, Tt;
		    TV = VMUL(LDK(KP559016994), VSUB(TT, TU));
		    T12 = VFNMS(LDK(KP250000000), T11, T10);
		    T13 = VSUB(TV, T12);
		    T1e = VADD(TV, T12);
		    Ts = VFNMS(LDK(KP250000000), Tr, T4);
		    Tt = VMUL(LDK(KP559016994), VSUB(Tf, Tq));
		    Tu = VSUB(Ts, Tt);
		    T1a = VADD(Tt, Ts);
	       }
	       {
		    V TS, T17, T1g, T1h;
		    TS = VSUB(Tu, TR);
		    T17 = VBYI(VSUB(T13, T16));
		    ST(&(x[WS(rs, 17)]), VSUB(TS, T17), ms, &(x[WS(rs, 1)]));
		    ST(&(x[WS(rs, 3)]), VADD(TS, T17), ms, &(x[WS(rs, 1)]));
		    T1g = VADD(T1a, T1b);
		    T1h = VBYI(VSUB(T1e, T1d));
		    ST(&(x[WS(rs, 11)]), VSUB(T1g, T1h), ms, &(x[WS(rs, 1)]));
		    ST(&(x[WS(rs, 9)]), VADD(T1g, T1h), ms, &(x[WS(rs, 1)]));
	       }
	       {
		    V T18, T19, T1c, T1f;
		    T18 = VADD(Tu, TR);
		    T19 = VBYI(VADD(T16, T13));
		    ST(&(x[WS(rs, 13)]), VSUB(T18, T19), ms, &(x[WS(rs, 1)]));
		    ST(&(x[WS(rs, 7)]), VADD(T18, T19), ms, &(x[WS(rs, 1)]));
		    T1c = VSUB(T1a, T1b);
		    T1f = VBYI(VADD(T1d, T1e));
		    ST(&(x[WS(rs, 19)]), VSUB(T1c, T1f), ms, &(x[WS(rs, 1)]));
		    ST(&(x[WS(rs, 1)]), VADD(T1c, T1f), ms, &(x[WS(rs, 1)]));
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     VTW(0, 3),
     VTW(0, 4),
     VTW(0, 5),
     VTW(0, 6),
     VTW(0, 7),
     VTW(0, 8),
     VTW(0, 9),
     VTW(0, 10),
     VTW(0, 11),
     VTW(0, 12),
     VTW(0, 13),
     VTW(0, 14),
     VTW(0, 15),
     VTW(0, 16),
     VTW(0, 17),
     VTW(0, 18),
     VTW(0, 19),
     {TW_NEXT, VL, 0}
};

static const ct_desc desc = { 20, "t2bv_20", twinstr, &GENUS, {111, 50, 12, 0}, 0, 0, 0 };

void X(codelet_t2bv_20) (planner *p) {
     X(kdft_dit_register) (p, t2bv_20, &desc);
}
#endif				/* HAVE_FMA */
