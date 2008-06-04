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
/* Generated on Tue Nov 13 17:42:18 EST 2007 */

#include "codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_r2cf -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -n 32 -name r2cf_32 -include r2cf.h */

/*
 * This function contains 156 FP additions, 68 FP multiplications,
 * (or, 88 additions, 0 multiplications, 68 fused multiply/add),
 * 89 stack variables, and 64 memory accesses
 */
#include "r2cf.h"

static void r2cf_32(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP831469612, +0.831469612302545237078788377617905756738560812);
     DK(KP668178637, +0.668178637919298919997757686523080761552472251);
     DK(KP980785280, +0.980785280403230449126182236134239036973933731);
     DK(KP198912367, +0.198912367379658006911597622644676228597850501);
     DK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     DK(KP414213562, +0.414213562373095048801688724209698078569671875);
     INT i;
     for (i = v; i > 0; i = i - 1, R0 = R0 + ivs, R1 = R1 + ivs, Cr = Cr + ovs, Ci = Ci + ovs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	  E T1x, T1M, T1I, T1E, T1J, T1H;
	  {
	       E Tv, T1h, T7, T2b, Te, T2n, Ty, T1i, T1l, TF, T2d, Tt, T1k, TC, T2c;
	       E Tm, T2j, T1Z, T2k, T22, TK, T1B, T19, T1C, T1e, TO, TV, T1T, TN, TP;
	       E T2g, T1S;
	       {
		    E TD, Tp, Tq, Tr;
		    {
			 E T1, T2, T4, T5;
			 T1 = R0[0];
			 T2 = R0[WS(rs, 8)];
			 T4 = R0[WS(rs, 4)];
			 T5 = R0[WS(rs, 12)];
			 {
			      E Ta, Tw, Tx, Td, Tn, To;
			      {
				   E T8, T3, T6, T9, Tb, Tc;
				   T8 = R0[WS(rs, 2)];
				   Tv = T1 - T2;
				   T3 = T1 + T2;
				   T1h = T4 - T5;
				   T6 = T4 + T5;
				   T9 = R0[WS(rs, 10)];
				   Tb = R0[WS(rs, 14)];
				   Tc = R0[WS(rs, 6)];
				   T7 = T3 + T6;
				   T2b = T3 - T6;
				   Ta = T8 + T9;
				   Tw = T8 - T9;
				   Tx = Tb - Tc;
				   Td = Tb + Tc;
			      }
			      Tn = R0[WS(rs, 15)];
			      To = R0[WS(rs, 7)];
			      Te = Ta + Td;
			      T2n = Td - Ta;
			      Ty = Tw + Tx;
			      T1i = Tx - Tw;
			      TD = Tn - To;
			      Tp = Tn + To;
			      Tq = R0[WS(rs, 3)];
			      Tr = R0[WS(rs, 11)];
			 }
		    }
		    {
			 E Tj, TA, Ti, Tk;
			 {
			      E Tg, Th, TE, Ts;
			      Tg = R0[WS(rs, 1)];
			      Th = R0[WS(rs, 9)];
			      Tj = R0[WS(rs, 5)];
			      TE = Tq - Tr;
			      Ts = Tq + Tr;
			      TA = Tg - Th;
			      Ti = Tg + Th;
			      T1l = FNMS(KP414213562, TD, TE);
			      TF = FMA(KP414213562, TE, TD);
			      T2d = Tp - Ts;
			      Tt = Tp + Ts;
			      Tk = R0[WS(rs, 13)];
			 }
			 {
			      E T11, T15, T1c, T20, T14, T16, T1X, T1Y, T1Q, T1R;
			      {
				   E T1a, T1b, T12, T13;
				   {
					E TZ, T10, TB, Tl;
					TZ = R1[WS(rs, 15)];
					T10 = R1[WS(rs, 7)];
					T1a = R1[WS(rs, 11)];
					TB = Tj - Tk;
					Tl = Tj + Tk;
					T1X = TZ + T10;
					T11 = TZ - T10;
					T1k = FMA(KP414213562, TA, TB);
					TC = FNMS(KP414213562, TB, TA);
					T2c = Ti - Tl;
					Tm = Ti + Tl;
					T1b = R1[WS(rs, 3)];
				   }
				   T12 = R1[WS(rs, 1)];
				   T13 = R1[WS(rs, 9)];
				   T15 = R1[WS(rs, 13)];
				   T1Y = T1b + T1a;
				   T1c = T1a - T1b;
				   T20 = T12 + T13;
				   T14 = T12 - T13;
				   T16 = R1[WS(rs, 5)];
			      }
			      T2j = T1X - T1Y;
			      T1Z = T1X + T1Y;
			      {
				   E TT, TU, TL, TM;
				   {
					E TI, T21, T17, TJ, T18, T1d;
					TI = R1[0];
					T21 = T15 + T16;
					T17 = T15 - T16;
					TJ = R1[WS(rs, 8)];
					TT = R1[WS(rs, 4)];
					T2k = T21 - T20;
					T22 = T20 + T21;
					T18 = T14 + T17;
					T1d = T17 - T14;
					T1Q = TI + TJ;
					TK = TI - TJ;
					T1B = FNMS(KP707106781, T18, T11);
					T19 = FMA(KP707106781, T18, T11);
					T1C = FNMS(KP707106781, T1d, T1c);
					T1e = FMA(KP707106781, T1d, T1c);
					TU = R1[WS(rs, 12)];
				   }
				   TL = R1[WS(rs, 2)];
				   TM = R1[WS(rs, 10)];
				   TO = R1[WS(rs, 14)];
				   T1R = TT + TU;
				   TV = TT - TU;
				   T1T = TL + TM;
				   TN = TL - TM;
				   TP = R1[WS(rs, 6)];
			      }
			      T2g = T1Q - T1R;
			      T1S = T1Q + T1R;
			 }
		    }
	       }
	       {
		    E T1P, T25, T23, T2h, T1W, T1y, TS, T1z, TX, T27, T2a;
		    {
			 E Tf, Tu, T29, T28;
			 {
			      E T1U, TQ, T1V, TR, TW;
			      T1P = T7 - Te;
			      Tf = T7 + Te;
			      T1U = TO + TP;
			      TQ = TO - TP;
			      Tu = Tm + Tt;
			      T25 = Tt - Tm;
			      T23 = T1Z - T22;
			      T29 = T1Z + T22;
			      T2h = T1U - T1T;
			      T1V = T1T + T1U;
			      TR = TN + TQ;
			      TW = TN - TQ;
			      T27 = Tf + Tu;
			      T1W = T1S - T1V;
			      T28 = T1S + T1V;
			      T1y = FNMS(KP707106781, TR, TK);
			      TS = FMA(KP707106781, TR, TK);
			      T1z = FNMS(KP707106781, TW, TV);
			      TX = FMA(KP707106781, TW, TV);
			      T2a = T28 + T29;
			 }
			 Cr[WS(csr, 8)] = Tf - Tu;
			 Ci[WS(csi, 8)] = T29 - T28;
		    }
		    Cr[0] = T27 + T2a;
		    Cr[WS(csr, 16)] = T27 - T2a;
		    {
			 E T2s, T2i, T2v, T2f, T2r, T2p, T2l, T2t;
			 {
			      E T2o, T2e, T26, T24;
			      T2o = T2d - T2c;
			      T2e = T2c + T2d;
			      T2s = FNMS(KP414213562, T2g, T2h);
			      T2i = FMA(KP414213562, T2h, T2g);
			      T26 = T23 - T1W;
			      T24 = T1W + T23;
			      T2v = FNMS(KP707106781, T2e, T2b);
			      T2f = FMA(KP707106781, T2e, T2b);
			      T2r = FMA(KP707106781, T2o, T2n);
			      T2p = FNMS(KP707106781, T2o, T2n);
			      Ci[WS(csi, 4)] = FMA(KP707106781, T26, T25);
			      Ci[WS(csi, 12)] = FMS(KP707106781, T26, T25);
			      Cr[WS(csr, 4)] = FMA(KP707106781, T24, T1P);
			      Cr[WS(csr, 12)] = FNMS(KP707106781, T24, T1P);
			      T2l = FNMS(KP414213562, T2k, T2j);
			      T2t = FMA(KP414213562, T2j, T2k);
			 }
			 {
			      E T1v, T1G, TH, T1s, T1F, T1w, T1o, T1g, T1p, T1n;
			      {
				   E T1f, TY, T1t, T1u, T1j, T1m;
				   {
					E Tz, TG, T1q, T1r;
					T1v = FNMS(KP707106781, Ty, Tv);
					Tz = FMA(KP707106781, Ty, Tv);
					{
					     E T2q, T2m, T2w, T2u;
					     T2q = T2l - T2i;
					     T2m = T2i + T2l;
					     T2w = T2t - T2s;
					     T2u = T2s + T2t;
					     Ci[WS(csi, 10)] = FMA(KP923879532, T2q, T2p);
					     Ci[WS(csi, 6)] = FMS(KP923879532, T2q, T2p);
					     Cr[WS(csr, 2)] = FMA(KP923879532, T2m, T2f);
					     Cr[WS(csr, 14)] = FNMS(KP923879532, T2m, T2f);
					     Cr[WS(csr, 10)] = FNMS(KP923879532, T2w, T2v);
					     Cr[WS(csr, 6)] = FMA(KP923879532, T2w, T2v);
					     Ci[WS(csi, 2)] = FMA(KP923879532, T2u, T2r);
					     Ci[WS(csi, 14)] = FMS(KP923879532, T2u, T2r);
					     TG = TC + TF;
					     T1G = TF - TC;
					}
					T1f = FNMS(KP198912367, T1e, T19);
					T1q = FMA(KP198912367, T19, T1e);
					T1r = FMA(KP198912367, TS, TX);
					TY = FNMS(KP198912367, TX, TS);
					T1t = FNMS(KP923879532, TG, Tz);
					TH = FMA(KP923879532, TG, Tz);
					T1u = T1r + T1q;
					T1s = T1q - T1r;
					T1F = FMA(KP707106781, T1i, T1h);
					T1j = FNMS(KP707106781, T1i, T1h);
					T1m = T1k + T1l;
					T1w = T1k - T1l;
				   }
				   Cr[WS(csr, 7)] = FMA(KP980785280, T1u, T1t);
				   T1o = T1f - TY;
				   T1g = TY + T1f;
				   T1p = FMA(KP923879532, T1m, T1j);
				   T1n = FNMS(KP923879532, T1m, T1j);
				   Cr[WS(csr, 9)] = FNMS(KP980785280, T1u, T1t);
			      }
			      Cr[WS(csr, 1)] = FMA(KP980785280, T1g, TH);
			      Cr[WS(csr, 15)] = FNMS(KP980785280, T1g, TH);
			      Ci[WS(csi, 1)] = FMS(KP980785280, T1s, T1p);
			      Ci[WS(csi, 15)] = FMA(KP980785280, T1s, T1p);
			      Ci[WS(csi, 9)] = FMS(KP980785280, T1o, T1n);
			      Ci[WS(csi, 7)] = FMA(KP980785280, T1o, T1n);
			      {
				   E T1A, T1D, T1N, T1O, T1K, T1L;
				   T1A = FMA(KP668178637, T1z, T1y);
				   T1K = FNMS(KP668178637, T1y, T1z);
				   T1L = FNMS(KP668178637, T1B, T1C);
				   T1D = FMA(KP668178637, T1C, T1B);
				   T1N = FNMS(KP923879532, T1w, T1v);
				   T1x = FMA(KP923879532, T1w, T1v);
				   T1O = T1K + T1L;
				   T1M = T1K - T1L;
				   Cr[WS(csr, 5)] = FNMS(KP831469612, T1O, T1N);
				   T1I = T1D - T1A;
				   T1E = T1A + T1D;
				   T1J = FMA(KP923879532, T1G, T1F);
				   T1H = FNMS(KP923879532, T1G, T1F);
				   Cr[WS(csr, 11)] = FMA(KP831469612, T1O, T1N);
			      }
			 }
		    }
	       }
	  }
	  Ci[WS(csi, 3)] = FMA(KP831469612, T1M, T1J);
	  Cr[WS(csr, 3)] = FMA(KP831469612, T1E, T1x);
	  Ci[WS(csi, 13)] = FMS(KP831469612, T1M, T1J);
	  Cr[WS(csr, 13)] = FNMS(KP831469612, T1E, T1x);
	  Ci[WS(csi, 11)] = FMA(KP831469612, T1I, T1H);
	  Ci[WS(csi, 5)] = FMS(KP831469612, T1I, T1H);
     }
}

static const kr2c_desc desc = { 32, "r2cf_32", {88, 0, 68, 0}, &GENUS };

void X(codelet_r2cf_32) (planner *p) {
     X(kr2c_register) (p, r2cf_32, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_r2cf -compact -variables 4 -pipeline-latency 4 -n 32 -name r2cf_32 -include r2cf.h */

/*
 * This function contains 156 FP additions, 42 FP multiplications,
 * (or, 140 additions, 26 multiplications, 16 fused multiply/add),
 * 54 stack variables, and 64 memory accesses
 */
#include "r2cf.h"

static void r2cf_32(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP555570233, +0.555570233019602224742830813948532874374937191);
     DK(KP831469612, +0.831469612302545237078788377617905756738560812);
     DK(KP195090322, +0.195090322016128267848284868477022240927691618);
     DK(KP980785280, +0.980785280403230449126182236134239036973933731);
     DK(KP382683432, +0.382683432365089771728459984030398866761344562);
     DK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT i;
     for (i = v; i > 0; i = i - 1, R0 = R0 + ivs, R1 = R1 + ivs, Cr = Cr + ovs, Ci = Ci + ovs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	  E T7, T2b, Tv, T1l, Te, T2o, Ty, T1k, Tt, T2d, TF, T1h, Tm, T2c, TC;
	  E T1i, T1Z, T22, T2k, T2j, T1e, T1C, T19, T1B, T1S, T1V, T2h, T2g, TX, T1z;
	  E TS, T1y;
	  {
	       E T1, T2, T3, T4, T5, T6;
	       T1 = R0[0];
	       T2 = R0[WS(rs, 8)];
	       T3 = T1 + T2;
	       T4 = R0[WS(rs, 4)];
	       T5 = R0[WS(rs, 12)];
	       T6 = T4 + T5;
	       T7 = T3 + T6;
	       T2b = T3 - T6;
	       Tv = T1 - T2;
	       T1l = T4 - T5;
	  }
	  {
	       E Ta, Tw, Td, Tx;
	       {
		    E T8, T9, Tb, Tc;
		    T8 = R0[WS(rs, 2)];
		    T9 = R0[WS(rs, 10)];
		    Ta = T8 + T9;
		    Tw = T8 - T9;
		    Tb = R0[WS(rs, 14)];
		    Tc = R0[WS(rs, 6)];
		    Td = Tb + Tc;
		    Tx = Tb - Tc;
	       }
	       Te = Ta + Td;
	       T2o = Td - Ta;
	       Ty = KP707106781 * (Tw + Tx);
	       T1k = KP707106781 * (Tx - Tw);
	  }
	  {
	       E Tp, TD, Ts, TE;
	       {
		    E Tn, To, Tq, Tr;
		    Tn = R0[WS(rs, 15)];
		    To = R0[WS(rs, 7)];
		    Tp = Tn + To;
		    TD = Tn - To;
		    Tq = R0[WS(rs, 3)];
		    Tr = R0[WS(rs, 11)];
		    Ts = Tq + Tr;
		    TE = Tq - Tr;
	       }
	       Tt = Tp + Ts;
	       T2d = Tp - Ts;
	       TF = FMA(KP923879532, TD, KP382683432 * TE);
	       T1h = FNMS(KP923879532, TE, KP382683432 * TD);
	  }
	  {
	       E Ti, TA, Tl, TB;
	       {
		    E Tg, Th, Tj, Tk;
		    Tg = R0[WS(rs, 1)];
		    Th = R0[WS(rs, 9)];
		    Ti = Tg + Th;
		    TA = Tg - Th;
		    Tj = R0[WS(rs, 5)];
		    Tk = R0[WS(rs, 13)];
		    Tl = Tj + Tk;
		    TB = Tj - Tk;
	       }
	       Tm = Ti + Tl;
	       T2c = Ti - Tl;
	       TC = FNMS(KP382683432, TB, KP923879532 * TA);
	       T1i = FMA(KP382683432, TA, KP923879532 * TB);
	  }
	  {
	       E T11, T1X, T1d, T1Y, T14, T20, T17, T21, T1a, T18;
	       {
		    E TZ, T10, T1b, T1c;
		    TZ = R1[WS(rs, 15)];
		    T10 = R1[WS(rs, 7)];
		    T11 = TZ - T10;
		    T1X = TZ + T10;
		    T1b = R1[WS(rs, 3)];
		    T1c = R1[WS(rs, 11)];
		    T1d = T1b - T1c;
		    T1Y = T1b + T1c;
	       }
	       {
		    E T12, T13, T15, T16;
		    T12 = R1[WS(rs, 1)];
		    T13 = R1[WS(rs, 9)];
		    T14 = T12 - T13;
		    T20 = T12 + T13;
		    T15 = R1[WS(rs, 13)];
		    T16 = R1[WS(rs, 5)];
		    T17 = T15 - T16;
		    T21 = T15 + T16;
	       }
	       T1Z = T1X + T1Y;
	       T22 = T20 + T21;
	       T2k = T21 - T20;
	       T2j = T1X - T1Y;
	       T1a = KP707106781 * (T17 - T14);
	       T1e = T1a - T1d;
	       T1C = T1d + T1a;
	       T18 = KP707106781 * (T14 + T17);
	       T19 = T11 + T18;
	       T1B = T11 - T18;
	  }
	  {
	       E TK, T1Q, TW, T1R, TN, T1T, TQ, T1U, TT, TR;
	       {
		    E TI, TJ, TU, TV;
		    TI = R1[0];
		    TJ = R1[WS(rs, 8)];
		    TK = TI - TJ;
		    T1Q = TI + TJ;
		    TU = R1[WS(rs, 4)];
		    TV = R1[WS(rs, 12)];
		    TW = TU - TV;
		    T1R = TU + TV;
	       }
	       {
		    E TL, TM, TO, TP;
		    TL = R1[WS(rs, 2)];
		    TM = R1[WS(rs, 10)];
		    TN = TL - TM;
		    T1T = TL + TM;
		    TO = R1[WS(rs, 14)];
		    TP = R1[WS(rs, 6)];
		    TQ = TO - TP;
		    T1U = TO + TP;
	       }
	       T1S = T1Q + T1R;
	       T1V = T1T + T1U;
	       T2h = T1U - T1T;
	       T2g = T1Q - T1R;
	       TT = KP707106781 * (TQ - TN);
	       TX = TT - TW;
	       T1z = TW + TT;
	       TR = KP707106781 * (TN + TQ);
	       TS = TK + TR;
	       T1y = TK - TR;
	  }
	  {
	       E Tf, Tu, T27, T28, T29, T2a;
	       Tf = T7 + Te;
	       Tu = Tm + Tt;
	       T27 = Tf + Tu;
	       T28 = T1S + T1V;
	       T29 = T1Z + T22;
	       T2a = T28 + T29;
	       Cr[WS(csr, 8)] = Tf - Tu;
	       Ci[WS(csi, 8)] = T29 - T28;
	       Cr[WS(csr, 16)] = T27 - T2a;
	       Cr[0] = T27 + T2a;
	  }
	  {
	       E T1P, T25, T24, T26, T1W, T23;
	       T1P = T7 - Te;
	       T25 = Tt - Tm;
	       T1W = T1S - T1V;
	       T23 = T1Z - T22;
	       T24 = KP707106781 * (T1W + T23);
	       T26 = KP707106781 * (T23 - T1W);
	       Cr[WS(csr, 12)] = T1P - T24;
	       Ci[WS(csi, 12)] = T26 - T25;
	       Cr[WS(csr, 4)] = T1P + T24;
	       Ci[WS(csi, 4)] = T25 + T26;
	  }
	  {
	       E T2f, T2v, T2p, T2r, T2m, T2q, T2u, T2w, T2e, T2n;
	       T2e = KP707106781 * (T2c + T2d);
	       T2f = T2b + T2e;
	       T2v = T2b - T2e;
	       T2n = KP707106781 * (T2d - T2c);
	       T2p = T2n - T2o;
	       T2r = T2o + T2n;
	       {
		    E T2i, T2l, T2s, T2t;
		    T2i = FMA(KP923879532, T2g, KP382683432 * T2h);
		    T2l = FNMS(KP382683432, T2k, KP923879532 * T2j);
		    T2m = T2i + T2l;
		    T2q = T2l - T2i;
		    T2s = FNMS(KP382683432, T2g, KP923879532 * T2h);
		    T2t = FMA(KP382683432, T2j, KP923879532 * T2k);
		    T2u = T2s + T2t;
		    T2w = T2t - T2s;
	       }
	       Cr[WS(csr, 14)] = T2f - T2m;
	       Ci[WS(csi, 14)] = T2u - T2r;
	       Cr[WS(csr, 2)] = T2f + T2m;
	       Ci[WS(csi, 2)] = T2r + T2u;
	       Ci[WS(csi, 6)] = T2p + T2q;
	       Cr[WS(csr, 6)] = T2v + T2w;
	       Ci[WS(csi, 10)] = T2q - T2p;
	       Cr[WS(csr, 10)] = T2v - T2w;
	  }
	  {
	       E TH, T1t, T1s, T1u, T1g, T1o, T1n, T1p;
	       {
		    E Tz, TG, T1q, T1r;
		    Tz = Tv + Ty;
		    TG = TC + TF;
		    TH = Tz + TG;
		    T1t = Tz - TG;
		    T1q = FNMS(KP195090322, TS, KP980785280 * TX);
		    T1r = FMA(KP195090322, T19, KP980785280 * T1e);
		    T1s = T1q + T1r;
		    T1u = T1r - T1q;
	       }
	       {
		    E TY, T1f, T1j, T1m;
		    TY = FMA(KP980785280, TS, KP195090322 * TX);
		    T1f = FNMS(KP195090322, T1e, KP980785280 * T19);
		    T1g = TY + T1f;
		    T1o = T1f - TY;
		    T1j = T1h - T1i;
		    T1m = T1k - T1l;
		    T1n = T1j - T1m;
		    T1p = T1m + T1j;
	       }
	       Cr[WS(csr, 15)] = TH - T1g;
	       Ci[WS(csi, 15)] = T1s - T1p;
	       Cr[WS(csr, 1)] = TH + T1g;
	       Ci[WS(csi, 1)] = T1p + T1s;
	       Ci[WS(csi, 7)] = T1n + T1o;
	       Cr[WS(csr, 7)] = T1t + T1u;
	       Ci[WS(csi, 9)] = T1o - T1n;
	       Cr[WS(csr, 9)] = T1t - T1u;
	  }
	  {
	       E T1x, T1N, T1M, T1O, T1E, T1I, T1H, T1J;
	       {
		    E T1v, T1w, T1K, T1L;
		    T1v = Tv - Ty;
		    T1w = T1i + T1h;
		    T1x = T1v + T1w;
		    T1N = T1v - T1w;
		    T1K = FNMS(KP555570233, T1y, KP831469612 * T1z);
		    T1L = FMA(KP555570233, T1B, KP831469612 * T1C);
		    T1M = T1K + T1L;
		    T1O = T1L - T1K;
	       }
	       {
		    E T1A, T1D, T1F, T1G;
		    T1A = FMA(KP831469612, T1y, KP555570233 * T1z);
		    T1D = FNMS(KP555570233, T1C, KP831469612 * T1B);
		    T1E = T1A + T1D;
		    T1I = T1D - T1A;
		    T1F = TF - TC;
		    T1G = T1l + T1k;
		    T1H = T1F - T1G;
		    T1J = T1G + T1F;
	       }
	       Cr[WS(csr, 13)] = T1x - T1E;
	       Ci[WS(csi, 13)] = T1M - T1J;
	       Cr[WS(csr, 3)] = T1x + T1E;
	       Ci[WS(csi, 3)] = T1J + T1M;
	       Ci[WS(csi, 5)] = T1H + T1I;
	       Cr[WS(csr, 5)] = T1N + T1O;
	       Ci[WS(csi, 11)] = T1I - T1H;
	       Cr[WS(csr, 11)] = T1N - T1O;
	  }
     }
}

static const kr2c_desc desc = { 32, "r2cf_32", {140, 26, 16, 0}, &GENUS };

void X(codelet_r2cf_32) (planner *p) {
     X(kr2c_register) (p, r2cf_32, &desc);
}

#endif				/* HAVE_FMA */
