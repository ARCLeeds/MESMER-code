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
/* Generated on Tue Nov 13 17:19:11 EST 2007 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_twiddle -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -n 10 -name t1_10 -include t.h */

/*
 * This function contains 102 FP additions, 72 FP multiplications,
 * (or, 48 additions, 18 multiplications, 54 fused multiply/add),
 * 70 stack variables, and 40 memory accesses
 */
#include "t.h"

static void t1_10(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP618033988, +0.618033988749894848204586834365638117720309180);
     INT m;
     for (m = mb, W = W + (mb * 18); m < me; m = m + 1, ri = ri + ms, ii = ii + ms, W = W + 18, MAKE_VOLATILE_STRIDE(rs)) {
	  E T1X, T21, T20, T22;
	  {
	       E T23, T1U, T8, T12, T1y, T25, T1P, T1H, T1Y, T18, T10, T2b, T1K, T1O, T15;
	       E T1Z, T2a, Tz, T24, T1n;
	       {
		    E T1, T1T, T3, T6, T2, T5;
		    T1 = ri[0];
		    T1T = ii[0];
		    T3 = ri[WS(rs, 5)];
		    T6 = ii[WS(rs, 5)];
		    T2 = W[8];
		    T5 = W[9];
		    {
			 E T1w, TY, T1s, T1F, TM, T16, T1u, TS;
			 {
			      E TF, T1p, TO, TR, T1r, TL, TN, TQ, T1t, TP;
			      {
				   E TU, TX, TT, TW;
				   {
					E TB, TE, T1R, T4, TA, TD;
					TB = ri[WS(rs, 4)];
					TE = ii[WS(rs, 4)];
					T1R = T2 * T6;
					T4 = T2 * T3;
					TA = W[6];
					TD = W[7];
					{
					     E T1S, T7, T1o, TC;
					     T1S = FNMS(T5, T3, T1R);
					     T7 = FMA(T5, T6, T4);
					     T1o = TA * TE;
					     TC = TA * TB;
					     T23 = T1T - T1S;
					     T1U = T1S + T1T;
					     T8 = T1 - T7;
					     T12 = T1 + T7;
					     TF = FMA(TD, TE, TC);
					     T1p = FNMS(TD, TB, T1o);
					}
				   }
				   TU = ri[WS(rs, 1)];
				   TX = ii[WS(rs, 1)];
				   TT = W[0];
				   TW = W[1];
				   {
					E TH, TK, TJ, T1q, TI, T1v, TV, TG;
					TH = ri[WS(rs, 9)];
					TK = ii[WS(rs, 9)];
					T1v = TT * TX;
					TV = TT * TU;
					TG = W[16];
					TJ = W[17];
					T1w = FNMS(TW, TU, T1v);
					TY = FMA(TW, TX, TV);
					T1q = TG * TK;
					TI = TG * TH;
					TO = ri[WS(rs, 6)];
					TR = ii[WS(rs, 6)];
					T1r = FNMS(TJ, TH, T1q);
					TL = FMA(TJ, TK, TI);
					TN = W[10];
					TQ = W[11];
				   }
			      }
			      T1s = T1p - T1r;
			      T1F = T1p + T1r;
			      TM = TF - TL;
			      T16 = TF + TL;
			      T1t = TN * TR;
			      TP = TN * TO;
			      T1u = FNMS(TQ, TO, T1t);
			      TS = FMA(TQ, TR, TP);
			 }
			 {
			      E T1e, Te, T1l, Tx, Tn, Tq, Tp, T1g, Tk, T1i, To;
			      {
				   E Tt, Tw, Tv, T1k, Tu;
				   {
					E Ta, Td, T9, Tc, T1d, Tb, Ts;
					Ta = ri[WS(rs, 2)];
					Td = ii[WS(rs, 2)];
					{
					     E T1G, T1x, TZ, T17;
					     T1G = T1u + T1w;
					     T1x = T1u - T1w;
					     TZ = TS - TY;
					     T17 = TS + TY;
					     T1y = T1s - T1x;
					     T25 = T1s + T1x;
					     T1P = T1F + T1G;
					     T1H = T1F - T1G;
					     T1Y = T16 - T17;
					     T18 = T16 + T17;
					     T10 = TM + TZ;
					     T2b = TM - TZ;
					     T9 = W[2];
					}
					Tc = W[3];
					Tt = ri[WS(rs, 3)];
					Tw = ii[WS(rs, 3)];
					T1d = T9 * Td;
					Tb = T9 * Ta;
					Ts = W[4];
					Tv = W[5];
					T1e = FNMS(Tc, Ta, T1d);
					Te = FMA(Tc, Td, Tb);
					T1k = Ts * Tw;
					Tu = Ts * Tt;
				   }
				   {
					E Tg, Tj, Tf, Ti, T1f, Th, Tm;
					Tg = ri[WS(rs, 7)];
					Tj = ii[WS(rs, 7)];
					T1l = FNMS(Tv, Tt, T1k);
					Tx = FMA(Tv, Tw, Tu);
					Tf = W[12];
					Ti = W[13];
					Tn = ri[WS(rs, 8)];
					Tq = ii[WS(rs, 8)];
					T1f = Tf * Tj;
					Th = Tf * Tg;
					Tm = W[14];
					Tp = W[15];
					T1g = FNMS(Ti, Tg, T1f);
					Tk = FMA(Ti, Tj, Th);
					T1i = Tm * Tq;
					To = Tm * Tn;
				   }
			      }
			      {
				   E T1h, T1I, Tl, T13, T1j, Tr;
				   T1h = T1e - T1g;
				   T1I = T1e + T1g;
				   Tl = Te - Tk;
				   T13 = Te + Tk;
				   T1j = FNMS(Tp, Tn, T1i);
				   Tr = FMA(Tp, Tq, To);
				   {
					E T1m, T1J, T14, Ty;
					T1m = T1j - T1l;
					T1J = T1j + T1l;
					T14 = Tr + Tx;
					Ty = Tr - Tx;
					T1K = T1I - T1J;
					T1O = T1I + T1J;
					T15 = T13 + T14;
					T1Z = T13 - T14;
					T2a = Tl - Ty;
					Tz = Tl + Ty;
					T24 = T1h + T1m;
					T1n = T1h - T1m;
				   }
			      }
			 }
		    }
	       }
	       {
		    E T2c, T2e, T29, T2d;
		    {
			 E T1b, T11, T26, T28, T27;
			 T1b = Tz - T10;
			 T11 = Tz + T10;
			 T26 = T24 + T25;
			 T28 = T24 - T25;
			 {
			      E T1B, T1z, T1a, T1A, T1c;
			      T1B = FNMS(KP618033988, T1n, T1y);
			      T1z = FMA(KP618033988, T1y, T1n);
			      ri[WS(rs, 5)] = T8 + T11;
			      T1a = FNMS(KP250000000, T11, T8);
			      T1A = FNMS(KP559016994, T1b, T1a);
			      T1c = FMA(KP559016994, T1b, T1a);
			      T27 = FNMS(KP250000000, T26, T23);
			      T2c = FMA(KP618033988, T2b, T2a);
			      T2e = FNMS(KP618033988, T2a, T2b);
			      ri[WS(rs, 1)] = FMA(KP951056516, T1z, T1c);
			      ri[WS(rs, 9)] = FNMS(KP951056516, T1z, T1c);
			      ri[WS(rs, 3)] = FMA(KP951056516, T1B, T1A);
			      ri[WS(rs, 7)] = FNMS(KP951056516, T1B, T1A);
			 }
			 ii[WS(rs, 5)] = T26 + T23;
			 T29 = FMA(KP559016994, T28, T27);
			 T2d = FNMS(KP559016994, T28, T27);
		    }
		    {
			 E T1E, T1M, T1L, T1N, T19, T1D, T1C, T1Q, T1W, T1V;
			 T19 = T15 + T18;
			 T1D = T15 - T18;
			 ii[WS(rs, 7)] = FMA(KP951056516, T2e, T2d);
			 ii[WS(rs, 3)] = FNMS(KP951056516, T2e, T2d);
			 ii[WS(rs, 9)] = FMA(KP951056516, T2c, T29);
			 ii[WS(rs, 1)] = FNMS(KP951056516, T2c, T29);
			 T1C = FNMS(KP250000000, T19, T12);
			 ri[0] = T12 + T19;
			 T1E = FNMS(KP559016994, T1D, T1C);
			 T1M = FMA(KP559016994, T1D, T1C);
			 T1L = FNMS(KP618033988, T1K, T1H);
			 T1N = FMA(KP618033988, T1H, T1K);
			 T1Q = T1O + T1P;
			 T1W = T1O - T1P;
			 ri[WS(rs, 6)] = FMA(KP951056516, T1N, T1M);
			 ri[WS(rs, 4)] = FNMS(KP951056516, T1N, T1M);
			 ri[WS(rs, 8)] = FMA(KP951056516, T1L, T1E);
			 ri[WS(rs, 2)] = FNMS(KP951056516, T1L, T1E);
			 T1V = FNMS(KP250000000, T1Q, T1U);
			 ii[0] = T1Q + T1U;
			 T1X = FNMS(KP559016994, T1W, T1V);
			 T21 = FMA(KP559016994, T1W, T1V);
			 T20 = FNMS(KP618033988, T1Z, T1Y);
			 T22 = FMA(KP618033988, T1Y, T1Z);
		    }
	       }
	  }
	  ii[WS(rs, 6)] = FNMS(KP951056516, T22, T21);
	  ii[WS(rs, 4)] = FMA(KP951056516, T22, T21);
	  ii[WS(rs, 8)] = FNMS(KP951056516, T20, T1X);
	  ii[WS(rs, 2)] = FMA(KP951056516, T20, T1X);
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 0, 10},
     {TW_NEXT, 1, 0}
};

static const ct_desc desc = { 10, "t1_10", twinstr, &GENUS, {48, 18, 54, 0}, 0, 0, 0 };

void X(codelet_t1_10) (planner *p) {
     X(kdft_dit_register) (p, t1_10, &desc);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_twiddle -compact -variables 4 -pipeline-latency 4 -n 10 -name t1_10 -include t.h */

/*
 * This function contains 102 FP additions, 60 FP multiplications,
 * (or, 72 additions, 30 multiplications, 30 fused multiply/add),
 * 45 stack variables, and 40 memory accesses
 */
#include "t.h"

static void t1_10(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     INT m;
     for (m = mb, W = W + (mb * 18); m < me; m = m + 1, ri = ri + ms, ii = ii + ms, W = W + 18, MAKE_VOLATILE_STRIDE(rs)) {
	  E T7, T1O, TT, T1C, TF, TQ, TR, T1o, T1p, T1y, TX, TY, TZ, T1d, T1g;
	  E T1M, Ti, Tt, Tu, T1r, T1s, T1x, TU, TV, TW, T16, T19, T1L;
	  {
	       E T1, T1B, T6, T1A;
	       T1 = ri[0];
	       T1B = ii[0];
	       {
		    E T3, T5, T2, T4;
		    T3 = ri[WS(rs, 5)];
		    T5 = ii[WS(rs, 5)];
		    T2 = W[8];
		    T4 = W[9];
		    T6 = FMA(T2, T3, T4 * T5);
		    T1A = FNMS(T4, T3, T2 * T5);
	       }
	       T7 = T1 - T6;
	       T1O = T1B - T1A;
	       TT = T1 + T6;
	       T1C = T1A + T1B;
	  }
	  {
	       E Tz, T1b, TP, T1f, TE, T1c, TK, T1e;
	       {
		    E Tw, Ty, Tv, Tx;
		    Tw = ri[WS(rs, 4)];
		    Ty = ii[WS(rs, 4)];
		    Tv = W[6];
		    Tx = W[7];
		    Tz = FMA(Tv, Tw, Tx * Ty);
		    T1b = FNMS(Tx, Tw, Tv * Ty);
	       }
	       {
		    E TM, TO, TL, TN;
		    TM = ri[WS(rs, 1)];
		    TO = ii[WS(rs, 1)];
		    TL = W[0];
		    TN = W[1];
		    TP = FMA(TL, TM, TN * TO);
		    T1f = FNMS(TN, TM, TL * TO);
	       }
	       {
		    E TB, TD, TA, TC;
		    TB = ri[WS(rs, 9)];
		    TD = ii[WS(rs, 9)];
		    TA = W[16];
		    TC = W[17];
		    TE = FMA(TA, TB, TC * TD);
		    T1c = FNMS(TC, TB, TA * TD);
	       }
	       {
		    E TH, TJ, TG, TI;
		    TH = ri[WS(rs, 6)];
		    TJ = ii[WS(rs, 6)];
		    TG = W[10];
		    TI = W[11];
		    TK = FMA(TG, TH, TI * TJ);
		    T1e = FNMS(TI, TH, TG * TJ);
	       }
	       TF = Tz - TE;
	       TQ = TK - TP;
	       TR = TF + TQ;
	       T1o = T1b + T1c;
	       T1p = T1e + T1f;
	       T1y = T1o + T1p;
	       TX = Tz + TE;
	       TY = TK + TP;
	       TZ = TX + TY;
	       T1d = T1b - T1c;
	       T1g = T1e - T1f;
	       T1M = T1d + T1g;
	  }
	  {
	       E Tc, T14, Ts, T18, Th, T15, Tn, T17;
	       {
		    E T9, Tb, T8, Ta;
		    T9 = ri[WS(rs, 2)];
		    Tb = ii[WS(rs, 2)];
		    T8 = W[2];
		    Ta = W[3];
		    Tc = FMA(T8, T9, Ta * Tb);
		    T14 = FNMS(Ta, T9, T8 * Tb);
	       }
	       {
		    E Tp, Tr, To, Tq;
		    Tp = ri[WS(rs, 3)];
		    Tr = ii[WS(rs, 3)];
		    To = W[4];
		    Tq = W[5];
		    Ts = FMA(To, Tp, Tq * Tr);
		    T18 = FNMS(Tq, Tp, To * Tr);
	       }
	       {
		    E Te, Tg, Td, Tf;
		    Te = ri[WS(rs, 7)];
		    Tg = ii[WS(rs, 7)];
		    Td = W[12];
		    Tf = W[13];
		    Th = FMA(Td, Te, Tf * Tg);
		    T15 = FNMS(Tf, Te, Td * Tg);
	       }
	       {
		    E Tk, Tm, Tj, Tl;
		    Tk = ri[WS(rs, 8)];
		    Tm = ii[WS(rs, 8)];
		    Tj = W[14];
		    Tl = W[15];
		    Tn = FMA(Tj, Tk, Tl * Tm);
		    T17 = FNMS(Tl, Tk, Tj * Tm);
	       }
	       Ti = Tc - Th;
	       Tt = Tn - Ts;
	       Tu = Ti + Tt;
	       T1r = T14 + T15;
	       T1s = T17 + T18;
	       T1x = T1r + T1s;
	       TU = Tc + Th;
	       TV = Tn + Ts;
	       TW = TU + TV;
	       T16 = T14 - T15;
	       T19 = T17 - T18;
	       T1L = T16 + T19;
	  }
	  {
	       E T11, TS, T12, T1i, T1k, T1a, T1h, T1j, T13;
	       T11 = KP559016994 * (Tu - TR);
	       TS = Tu + TR;
	       T12 = FNMS(KP250000000, TS, T7);
	       T1a = T16 - T19;
	       T1h = T1d - T1g;
	       T1i = FMA(KP951056516, T1a, KP587785252 * T1h);
	       T1k = FNMS(KP587785252, T1a, KP951056516 * T1h);
	       ri[WS(rs, 5)] = T7 + TS;
	       T1j = T12 - T11;
	       ri[WS(rs, 7)] = T1j - T1k;
	       ri[WS(rs, 3)] = T1j + T1k;
	       T13 = T11 + T12;
	       ri[WS(rs, 9)] = T13 - T1i;
	       ri[WS(rs, 1)] = T13 + T1i;
	  }
	  {
	       E T1N, T1P, T1Q, T1U, T1W, T1S, T1T, T1V, T1R;
	       T1N = KP559016994 * (T1L - T1M);
	       T1P = T1L + T1M;
	       T1Q = FNMS(KP250000000, T1P, T1O);
	       T1S = Ti - Tt;
	       T1T = TF - TQ;
	       T1U = FMA(KP951056516, T1S, KP587785252 * T1T);
	       T1W = FNMS(KP587785252, T1S, KP951056516 * T1T);
	       ii[WS(rs, 5)] = T1P + T1O;
	       T1V = T1Q - T1N;
	       ii[WS(rs, 3)] = T1V - T1W;
	       ii[WS(rs, 7)] = T1W + T1V;
	       T1R = T1N + T1Q;
	       ii[WS(rs, 1)] = T1R - T1U;
	       ii[WS(rs, 9)] = T1U + T1R;
	  }
	  {
	       E T1m, T10, T1l, T1u, T1w, T1q, T1t, T1v, T1n;
	       T1m = KP559016994 * (TW - TZ);
	       T10 = TW + TZ;
	       T1l = FNMS(KP250000000, T10, TT);
	       T1q = T1o - T1p;
	       T1t = T1r - T1s;
	       T1u = FNMS(KP587785252, T1t, KP951056516 * T1q);
	       T1w = FMA(KP951056516, T1t, KP587785252 * T1q);
	       ri[0] = TT + T10;
	       T1v = T1m + T1l;
	       ri[WS(rs, 4)] = T1v - T1w;
	       ri[WS(rs, 6)] = T1v + T1w;
	       T1n = T1l - T1m;
	       ri[WS(rs, 2)] = T1n - T1u;
	       ri[WS(rs, 8)] = T1n + T1u;
	  }
	  {
	       E T1H, T1z, T1G, T1F, T1J, T1D, T1E, T1K, T1I;
	       T1H = KP559016994 * (T1x - T1y);
	       T1z = T1x + T1y;
	       T1G = FNMS(KP250000000, T1z, T1C);
	       T1D = TX - TY;
	       T1E = TU - TV;
	       T1F = FNMS(KP587785252, T1E, KP951056516 * T1D);
	       T1J = FMA(KP951056516, T1E, KP587785252 * T1D);
	       ii[0] = T1z + T1C;
	       T1K = T1H + T1G;
	       ii[WS(rs, 4)] = T1J + T1K;
	       ii[WS(rs, 6)] = T1K - T1J;
	       T1I = T1G - T1H;
	       ii[WS(rs, 2)] = T1F + T1I;
	       ii[WS(rs, 8)] = T1I - T1F;
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 0, 10},
     {TW_NEXT, 1, 0}
};

static const ct_desc desc = { 10, "t1_10", twinstr, &GENUS, {72, 30, 30, 0}, 0, 0, 0 };

void X(codelet_t1_10) (planner *p) {
     X(kdft_dit_register) (p, t1_10, &desc);
}
#endif				/* HAVE_FMA */
