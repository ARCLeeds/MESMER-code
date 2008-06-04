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
/* Generated on Tue Nov 13 17:43:57 EST 2007 */

#include "codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_hc2hc -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -n 16 -dit -name hf_16 -include hf.h */

/*
 * This function contains 174 FP additions, 100 FP multiplications,
 * (or, 104 additions, 30 multiplications, 70 fused multiply/add),
 * 95 stack variables, and 64 memory accesses
 */
#include "hf.h"

static void hf_16(R *cr, R *ci, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DK(KP414213562, +0.414213562373095048801688724209698078569671875);
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 30); m < me; m = m + 1, cr = cr + ms, ci = ci - ms, W = W + 30, MAKE_VOLATILE_STRIDE(rs)) {
	  E T2T, T2Q;
	  {
	       E T3A, T3o, T8, T1I, T2w, T35, T2k, T1s, T2p, T36, T2r, T1F, T3k, T1N, T3z;
	       E Tl, T1U, T2W, T1P, Tz, T2g, T30, T25, T11, TB, TE, T2a, T31, T2h, T1e;
	       E TC, T1X, TH, TK, TG, TD, TJ;
	       {
		    E Ta, Td, Tb, T1J, Tg, Tj, Tf, Tc, Ti;
		    {
			 E T1h, T1k, T1n, T2s, T1i, T1q, T1m, T1j, T1p;
			 {
			      E T1, T3n, T3, T6, T2, T5;
			      T1 = cr[0];
			      T3n = ci[0];
			      T3 = cr[WS(rs, 8)];
			      T6 = ci[WS(rs, 8)];
			      T2 = W[14];
			      T5 = W[15];
			      {
				   E T3l, T4, T1g, T3m, T7;
				   T1h = cr[WS(rs, 15)];
				   T1k = ci[WS(rs, 15)];
				   T3l = T2 * T6;
				   T4 = T2 * T3;
				   T1g = W[28];
				   T1n = cr[WS(rs, 7)];
				   T3m = FNMS(T5, T3, T3l);
				   T7 = FMA(T5, T6, T4);
				   T2s = T1g * T1k;
				   T1i = T1g * T1h;
				   T3A = T3n - T3m;
				   T3o = T3m + T3n;
				   T8 = T1 + T7;
				   T1I = T1 - T7;
				   T1q = ci[WS(rs, 7)];
				   T1m = W[12];
			      }
			      T1j = W[29];
			      T1p = W[13];
			 }
			 {
			      E T1u, T1x, T1v, T2l, T1A, T1D, T1z, T1w, T1C;
			      {
				   E T2t, T1l, T2v, T1r, T2u, T1o, T1t;
				   T1u = cr[WS(rs, 3)];
				   T2u = T1m * T1q;
				   T1o = T1m * T1n;
				   T2t = FNMS(T1j, T1h, T2s);
				   T1l = FMA(T1j, T1k, T1i);
				   T2v = FNMS(T1p, T1n, T2u);
				   T1r = FMA(T1p, T1q, T1o);
				   T1x = ci[WS(rs, 3)];
				   T1t = W[4];
				   T2w = T2t - T2v;
				   T35 = T2t + T2v;
				   T2k = T1l - T1r;
				   T1s = T1l + T1r;
				   T1v = T1t * T1u;
				   T2l = T1t * T1x;
			      }
			      T1A = cr[WS(rs, 11)];
			      T1D = ci[WS(rs, 11)];
			      T1z = W[20];
			      T1w = W[5];
			      T1C = W[21];
			      {
				   E T2m, T1y, T2o, T1E, T2n, T1B, T9;
				   Ta = cr[WS(rs, 4)];
				   T2n = T1z * T1D;
				   T1B = T1z * T1A;
				   T2m = FNMS(T1w, T1u, T2l);
				   T1y = FMA(T1w, T1x, T1v);
				   T2o = FNMS(T1C, T1A, T2n);
				   T1E = FMA(T1C, T1D, T1B);
				   Td = ci[WS(rs, 4)];
				   T9 = W[6];
				   T2p = T2m - T2o;
				   T36 = T2m + T2o;
				   T2r = T1E - T1y;
				   T1F = T1y + T1E;
				   Tb = T9 * Ta;
				   T1J = T9 * Td;
			      }
			      Tg = cr[WS(rs, 12)];
			      Tj = ci[WS(rs, 12)];
			      Tf = W[22];
			      Tc = W[7];
			      Ti = W[23];
			 }
		    }
		    {
			 E TQ, TT, TR, T2c, TW, TZ, TV, TS, TY;
			 {
			      E To, Tr, Tp, T1Q, Tu, Tx, Tt, Tq, Tw;
			      {
				   E T1K, Te, T1M, Tk, T1L, Th, Tn;
				   To = cr[WS(rs, 2)];
				   T1L = Tf * Tj;
				   Th = Tf * Tg;
				   T1K = FNMS(Tc, Ta, T1J);
				   Te = FMA(Tc, Td, Tb);
				   T1M = FNMS(Ti, Tg, T1L);
				   Tk = FMA(Ti, Tj, Th);
				   Tr = ci[WS(rs, 2)];
				   Tn = W[2];
				   T3k = T1K + T1M;
				   T1N = T1K - T1M;
				   T3z = Te - Tk;
				   Tl = Te + Tk;
				   Tp = Tn * To;
				   T1Q = Tn * Tr;
			      }
			      Tu = cr[WS(rs, 10)];
			      Tx = ci[WS(rs, 10)];
			      Tt = W[18];
			      Tq = W[3];
			      Tw = W[19];
			      {
				   E T1R, Ts, T1T, Ty, T1S, Tv, TP;
				   TQ = cr[WS(rs, 1)];
				   T1S = Tt * Tx;
				   Tv = Tt * Tu;
				   T1R = FNMS(Tq, To, T1Q);
				   Ts = FMA(Tq, Tr, Tp);
				   T1T = FNMS(Tw, Tu, T1S);
				   Ty = FMA(Tw, Tx, Tv);
				   TT = ci[WS(rs, 1)];
				   TP = W[0];
				   T1U = T1R - T1T;
				   T2W = T1R + T1T;
				   T1P = Ts - Ty;
				   Tz = Ts + Ty;
				   TR = TP * TQ;
				   T2c = TP * TT;
			      }
			      TW = cr[WS(rs, 9)];
			      TZ = ci[WS(rs, 9)];
			      TV = W[16];
			      TS = W[1];
			      TY = W[17];
			 }
			 {
			      E T13, T16, T14, T26, T19, T1c, T18, T15, T1b;
			      {
				   E T2d, TU, T2f, T10, T2e, TX, T12;
				   T13 = cr[WS(rs, 5)];
				   T2e = TV * TZ;
				   TX = TV * TW;
				   T2d = FNMS(TS, TQ, T2c);
				   TU = FMA(TS, TT, TR);
				   T2f = FNMS(TY, TW, T2e);
				   T10 = FMA(TY, TZ, TX);
				   T16 = ci[WS(rs, 5)];
				   T12 = W[8];
				   T2g = T2d - T2f;
				   T30 = T2d + T2f;
				   T25 = TU - T10;
				   T11 = TU + T10;
				   T14 = T12 * T13;
				   T26 = T12 * T16;
			      }
			      T19 = cr[WS(rs, 13)];
			      T1c = ci[WS(rs, 13)];
			      T18 = W[24];
			      T15 = W[9];
			      T1b = W[25];
			      {
				   E T27, T17, T29, T1d, T28, T1a, TA;
				   TB = cr[WS(rs, 14)];
				   T28 = T18 * T1c;
				   T1a = T18 * T19;
				   T27 = FNMS(T15, T13, T26);
				   T17 = FMA(T15, T16, T14);
				   T29 = FNMS(T1b, T19, T28);
				   T1d = FMA(T1b, T1c, T1a);
				   TE = ci[WS(rs, 14)];
				   TA = W[26];
				   T2a = T27 - T29;
				   T31 = T27 + T29;
				   T2h = T17 - T1d;
				   T1e = T17 + T1d;
				   TC = TA * TB;
				   T1X = TA * TE;
			      }
			      TH = cr[WS(rs, 6)];
			      TK = ci[WS(rs, 6)];
			      TG = W[10];
			      TD = W[27];
			      TJ = W[11];
			 }
		    }
	       }
	       {
		    E T2U, T3u, T2Z, T21, T1W, T34, T2X, T37, T3t, T3q, T3e, T32, T3i, T3h;
		    {
			 E T3f, T3r, T1H, T3s, TO, T3g;
			 {
			      E Tm, T1Y, TF, T20, TL, T3p, T1Z, TI;
			      T2U = T8 - Tl;
			      Tm = T8 + Tl;
			      T1Z = TG * TK;
			      TI = TG * TH;
			      T1Y = FNMS(TD, TB, T1X);
			      TF = FMA(TD, TE, TC);
			      T20 = FNMS(TJ, TH, T1Z);
			      TL = FMA(TJ, TK, TI);
			      T3p = T3k + T3o;
			      T3u = T3o - T3k;
			      {
				   E T1f, TM, T1G, T3j, T2V, TN;
				   T2Z = T11 - T1e;
				   T1f = T11 + T1e;
				   T21 = T1Y - T20;
				   T2V = T1Y + T20;
				   T1W = TF - TL;
				   TM = TF + TL;
				   T1G = T1s + T1F;
				   T34 = T1s - T1F;
				   T2X = T2V - T2W;
				   T3j = T2W + T2V;
				   T3f = T35 + T36;
				   T37 = T35 - T36;
				   T3t = Tz - TM;
				   TN = Tz + TM;
				   T3r = T1G - T1f;
				   T1H = T1f + T1G;
				   T3s = T3p - T3j;
				   T3q = T3j + T3p;
				   T3e = Tm - TN;
				   TO = Tm + TN;
				   T3g = T30 + T31;
				   T32 = T30 - T31;
			      }
			 }
			 cr[WS(rs, 12)] = T3r - T3s;
			 ci[WS(rs, 11)] = T3r + T3s;
			 ci[WS(rs, 7)] = TO - T1H;
			 T3i = T3g + T3f;
			 T3h = T3f - T3g;
			 cr[0] = TO + T1H;
		    }
		    {
			 E T3a, T2Y, T3x, T3v;
			 ci[WS(rs, 15)] = T3i + T3q;
			 cr[WS(rs, 8)] = T3i - T3q;
			 ci[WS(rs, 3)] = T3e + T3h;
			 cr[WS(rs, 4)] = T3e - T3h;
			 T3a = T2U + T2X;
			 T2Y = T2U - T2X;
			 T3x = T3u - T3t;
			 T3v = T3t + T3u;
			 {
			      E T2E, T1O, T3B, T3H, T2q, T2x, T3I, T23, T2R, T2O, T2J, T2K, T3C, T2H, T2B;
			      E T2j;
			      {
				   E T2F, T1V, T22, T2G;
				   {
					E T3b, T33, T3c, T38;
					T2E = T1I + T1N;
					T1O = T1I - T1N;
					T3b = T2Z - T32;
					T33 = T2Z + T32;
					T3c = T34 + T37;
					T38 = T34 - T37;
					T3B = T3z + T3A;
					T3H = T3A - T3z;
					{
					     E T3d, T3y, T3w, T39;
					     T3d = T3b + T3c;
					     T3y = T3c - T3b;
					     T3w = T38 - T33;
					     T39 = T33 + T38;
					     ci[WS(rs, 1)] = FMA(KP707106781, T3d, T3a);
					     cr[WS(rs, 6)] = FNMS(KP707106781, T3d, T3a);
					     ci[WS(rs, 13)] = FMA(KP707106781, T3y, T3x);
					     cr[WS(rs, 10)] = FMS(KP707106781, T3y, T3x);
					     ci[WS(rs, 9)] = FMA(KP707106781, T3w, T3v);
					     cr[WS(rs, 14)] = FMS(KP707106781, T3w, T3v);
					     cr[WS(rs, 2)] = FMA(KP707106781, T39, T2Y);
					     ci[WS(rs, 5)] = FNMS(KP707106781, T39, T2Y);
					     T2F = T1P + T1U;
					     T1V = T1P - T1U;
					     T22 = T1W + T21;
					     T2G = T1W - T21;
					}
				   }
				   {
					E T2M, T2N, T2b, T2i;
					T2q = T2k - T2p;
					T2M = T2k + T2p;
					T2N = T2w + T2r;
					T2x = T2r - T2w;
					T3I = T22 - T1V;
					T23 = T1V + T22;
					T2R = FMA(KP414213562, T2M, T2N);
					T2O = FNMS(KP414213562, T2N, T2M);
					T2J = T25 + T2a;
					T2b = T25 - T2a;
					T2i = T2g + T2h;
					T2K = T2g - T2h;
					T3C = T2F - T2G;
					T2H = T2F + T2G;
					T2B = FMA(KP414213562, T2b, T2i);
					T2j = FNMS(KP414213562, T2i, T2b);
				   }
			      }
			      {
				   E T2A, T3G, T2P, T2D, T3E, T3F, T3D, T2I;
				   {
					E T24, T2L, T2C, T2y, T3J, T3L, T3K, T2S, T2z, T3M;
					T2A = FNMS(KP707106781, T23, T1O);
					T24 = FMA(KP707106781, T23, T1O);
					T2S = FNMS(KP414213562, T2J, T2K);
					T2L = FMA(KP414213562, T2K, T2J);
					T2C = FMA(KP414213562, T2q, T2x);
					T2y = FNMS(KP414213562, T2x, T2q);
					T3J = FMA(KP707106781, T3I, T3H);
					T3L = FNMS(KP707106781, T3I, T3H);
					T2T = T2R - T2S;
					T3K = T2S + T2R;
					T3G = T2y - T2j;
					T2z = T2j + T2y;
					T3M = T2O - T2L;
					T2P = T2L + T2O;
					ci[WS(rs, 14)] = FMA(KP923879532, T3K, T3J);
					cr[WS(rs, 9)] = FMS(KP923879532, T3K, T3J);
					ci[0] = FMA(KP923879532, T2z, T24);
					cr[WS(rs, 7)] = FNMS(KP923879532, T2z, T24);
					cr[WS(rs, 13)] = FMS(KP923879532, T3M, T3L);
					ci[WS(rs, 10)] = FMA(KP923879532, T3M, T3L);
					T2D = T2B + T2C;
					T3E = T2C - T2B;
				   }
				   T2Q = FNMS(KP707106781, T2H, T2E);
				   T2I = FMA(KP707106781, T2H, T2E);
				   T3F = FNMS(KP707106781, T3C, T3B);
				   T3D = FMA(KP707106781, T3C, T3B);
				   cr[WS(rs, 3)] = FMA(KP923879532, T2D, T2A);
				   ci[WS(rs, 4)] = FNMS(KP923879532, T2D, T2A);
				   cr[WS(rs, 1)] = FMA(KP923879532, T2P, T2I);
				   ci[WS(rs, 6)] = FNMS(KP923879532, T2P, T2I);
				   ci[WS(rs, 8)] = FMA(KP923879532, T3E, T3D);
				   cr[WS(rs, 15)] = FMS(KP923879532, T3E, T3D);
				   ci[WS(rs, 12)] = FMA(KP923879532, T3G, T3F);
				   cr[WS(rs, 11)] = FMS(KP923879532, T3G, T3F);
			      }
			 }
		    }
	       }
	  }
	  ci[WS(rs, 2)] = FMA(KP923879532, T2T, T2Q);
	  cr[WS(rs, 5)] = FNMS(KP923879532, T2T, T2Q);
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 16},
     {TW_NEXT, 1, 0}
};

static const hc2hc_desc desc = { 16, "hf_16", twinstr, &GENUS, {104, 30, 70, 0} };

void X(codelet_hf_16) (planner *p) {
     X(khc2hc_register) (p, hf_16, &desc);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_hc2hc -compact -variables 4 -pipeline-latency 4 -n 16 -dit -name hf_16 -include hf.h */

/*
 * This function contains 174 FP additions, 84 FP multiplications,
 * (or, 136 additions, 46 multiplications, 38 fused multiply/add),
 * 52 stack variables, and 64 memory accesses
 */
#include "hf.h"

static void hf_16(R *cr, R *ci, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP382683432, +0.382683432365089771728459984030398866761344562);
     DK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 30); m < me; m = m + 1, cr = cr + ms, ci = ci - ms, W = W + 30, MAKE_VOLATILE_STRIDE(rs)) {
	  E T7, T38, T1t, T2U, Ti, T37, T1w, T2R, Tu, T2t, T1C, T2c, TF, T2s, T1H;
	  E T2d, T1f, T1q, T2B, T2C, T2D, T2E, T1Z, T2k, T24, T2j, TS, T13, T2w, T2x;
	  E T2y, T2z, T1O, T2h, T1T, T2g;
	  {
	       E T1, T2T, T6, T2S;
	       T1 = cr[0];
	       T2T = ci[0];
	       {
		    E T3, T5, T2, T4;
		    T3 = cr[WS(rs, 8)];
		    T5 = ci[WS(rs, 8)];
		    T2 = W[14];
		    T4 = W[15];
		    T6 = FMA(T2, T3, T4 * T5);
		    T2S = FNMS(T4, T3, T2 * T5);
	       }
	       T7 = T1 + T6;
	       T38 = T2T - T2S;
	       T1t = T1 - T6;
	       T2U = T2S + T2T;
	  }
	  {
	       E Tc, T1u, Th, T1v;
	       {
		    E T9, Tb, T8, Ta;
		    T9 = cr[WS(rs, 4)];
		    Tb = ci[WS(rs, 4)];
		    T8 = W[6];
		    Ta = W[7];
		    Tc = FMA(T8, T9, Ta * Tb);
		    T1u = FNMS(Ta, T9, T8 * Tb);
	       }
	       {
		    E Te, Tg, Td, Tf;
		    Te = cr[WS(rs, 12)];
		    Tg = ci[WS(rs, 12)];
		    Td = W[22];
		    Tf = W[23];
		    Th = FMA(Td, Te, Tf * Tg);
		    T1v = FNMS(Tf, Te, Td * Tg);
	       }
	       Ti = Tc + Th;
	       T37 = Tc - Th;
	       T1w = T1u - T1v;
	       T2R = T1u + T1v;
	  }
	  {
	       E To, T1z, Tt, T1A, T1y, T1B;
	       {
		    E Tl, Tn, Tk, Tm;
		    Tl = cr[WS(rs, 2)];
		    Tn = ci[WS(rs, 2)];
		    Tk = W[2];
		    Tm = W[3];
		    To = FMA(Tk, Tl, Tm * Tn);
		    T1z = FNMS(Tm, Tl, Tk * Tn);
	       }
	       {
		    E Tq, Ts, Tp, Tr;
		    Tq = cr[WS(rs, 10)];
		    Ts = ci[WS(rs, 10)];
		    Tp = W[18];
		    Tr = W[19];
		    Tt = FMA(Tp, Tq, Tr * Ts);
		    T1A = FNMS(Tr, Tq, Tp * Ts);
	       }
	       Tu = To + Tt;
	       T2t = T1z + T1A;
	       T1y = To - Tt;
	       T1B = T1z - T1A;
	       T1C = T1y - T1B;
	       T2c = T1y + T1B;
	  }
	  {
	       E Tz, T1E, TE, T1F, T1D, T1G;
	       {
		    E Tw, Ty, Tv, Tx;
		    Tw = cr[WS(rs, 14)];
		    Ty = ci[WS(rs, 14)];
		    Tv = W[26];
		    Tx = W[27];
		    Tz = FMA(Tv, Tw, Tx * Ty);
		    T1E = FNMS(Tx, Tw, Tv * Ty);
	       }
	       {
		    E TB, TD, TA, TC;
		    TB = cr[WS(rs, 6)];
		    TD = ci[WS(rs, 6)];
		    TA = W[10];
		    TC = W[11];
		    TE = FMA(TA, TB, TC * TD);
		    T1F = FNMS(TC, TB, TA * TD);
	       }
	       TF = Tz + TE;
	       T2s = T1E + T1F;
	       T1D = Tz - TE;
	       T1G = T1E - T1F;
	       T1H = T1D + T1G;
	       T2d = T1D - T1G;
	  }
	  {
	       E T19, T1V, T1p, T22, T1e, T1W, T1k, T21;
	       {
		    E T16, T18, T15, T17;
		    T16 = cr[WS(rs, 15)];
		    T18 = ci[WS(rs, 15)];
		    T15 = W[28];
		    T17 = W[29];
		    T19 = FMA(T15, T16, T17 * T18);
		    T1V = FNMS(T17, T16, T15 * T18);
	       }
	       {
		    E T1m, T1o, T1l, T1n;
		    T1m = cr[WS(rs, 11)];
		    T1o = ci[WS(rs, 11)];
		    T1l = W[20];
		    T1n = W[21];
		    T1p = FMA(T1l, T1m, T1n * T1o);
		    T22 = FNMS(T1n, T1m, T1l * T1o);
	       }
	       {
		    E T1b, T1d, T1a, T1c;
		    T1b = cr[WS(rs, 7)];
		    T1d = ci[WS(rs, 7)];
		    T1a = W[12];
		    T1c = W[13];
		    T1e = FMA(T1a, T1b, T1c * T1d);
		    T1W = FNMS(T1c, T1b, T1a * T1d);
	       }
	       {
		    E T1h, T1j, T1g, T1i;
		    T1h = cr[WS(rs, 3)];
		    T1j = ci[WS(rs, 3)];
		    T1g = W[4];
		    T1i = W[5];
		    T1k = FMA(T1g, T1h, T1i * T1j);
		    T21 = FNMS(T1i, T1h, T1g * T1j);
	       }
	       T1f = T19 + T1e;
	       T1q = T1k + T1p;
	       T2B = T1f - T1q;
	       T2C = T1V + T1W;
	       T2D = T21 + T22;
	       T2E = T2C - T2D;
	       {
		    E T1X, T1Y, T20, T23;
		    T1X = T1V - T1W;
		    T1Y = T1k - T1p;
		    T1Z = T1X + T1Y;
		    T2k = T1X - T1Y;
		    T20 = T19 - T1e;
		    T23 = T21 - T22;
		    T24 = T20 - T23;
		    T2j = T20 + T23;
	       }
	  }
	  {
	       E TM, T1P, T12, T1M, TR, T1Q, TX, T1L;
	       {
		    E TJ, TL, TI, TK;
		    TJ = cr[WS(rs, 1)];
		    TL = ci[WS(rs, 1)];
		    TI = W[0];
		    TK = W[1];
		    TM = FMA(TI, TJ, TK * TL);
		    T1P = FNMS(TK, TJ, TI * TL);
	       }
	       {
		    E TZ, T11, TY, T10;
		    TZ = cr[WS(rs, 13)];
		    T11 = ci[WS(rs, 13)];
		    TY = W[24];
		    T10 = W[25];
		    T12 = FMA(TY, TZ, T10 * T11);
		    T1M = FNMS(T10, TZ, TY * T11);
	       }
	       {
		    E TO, TQ, TN, TP;
		    TO = cr[WS(rs, 9)];
		    TQ = ci[WS(rs, 9)];
		    TN = W[16];
		    TP = W[17];
		    TR = FMA(TN, TO, TP * TQ);
		    T1Q = FNMS(TP, TO, TN * TQ);
	       }
	       {
		    E TU, TW, TT, TV;
		    TU = cr[WS(rs, 5)];
		    TW = ci[WS(rs, 5)];
		    TT = W[8];
		    TV = W[9];
		    TX = FMA(TT, TU, TV * TW);
		    T1L = FNMS(TV, TU, TT * TW);
	       }
	       TS = TM + TR;
	       T13 = TX + T12;
	       T2w = TS - T13;
	       T2x = T1P + T1Q;
	       T2y = T1L + T1M;
	       T2z = T2x - T2y;
	       {
		    E T1K, T1N, T1R, T1S;
		    T1K = TM - TR;
		    T1N = T1L - T1M;
		    T1O = T1K - T1N;
		    T2h = T1K + T1N;
		    T1R = T1P - T1Q;
		    T1S = TX - T12;
		    T1T = T1R + T1S;
		    T2g = T1R - T1S;
	       }
	  }
	  {
	       E T1J, T27, T3a, T3c, T26, T3b, T2a, T35;
	       {
		    E T1x, T1I, T36, T39;
		    T1x = T1t - T1w;
		    T1I = KP707106781 * (T1C + T1H);
		    T1J = T1x + T1I;
		    T27 = T1x - T1I;
		    T36 = KP707106781 * (T2c - T2d);
		    T39 = T37 + T38;
		    T3a = T36 + T39;
		    T3c = T39 - T36;
	       }
	       {
		    E T1U, T25, T28, T29;
		    T1U = FNMS(KP382683432, T1T, KP923879532 * T1O);
		    T25 = FMA(KP382683432, T1Z, KP923879532 * T24);
		    T26 = T1U + T25;
		    T3b = T25 - T1U;
		    T28 = FMA(KP923879532, T1T, KP382683432 * T1O);
		    T29 = FNMS(KP923879532, T1Z, KP382683432 * T24);
		    T2a = T28 + T29;
		    T35 = T29 - T28;
	       }
	       cr[WS(rs, 7)] = T1J - T26;
	       cr[WS(rs, 11)] = T3b - T3c;
	       ci[WS(rs, 12)] = T3b + T3c;
	       ci[0] = T1J + T26;
	       ci[WS(rs, 4)] = T27 - T2a;
	       cr[WS(rs, 15)] = T35 - T3a;
	       ci[WS(rs, 8)] = T35 + T3a;
	       cr[WS(rs, 3)] = T27 + T2a;
	  }
	  {
	       E TH, T2L, T2W, T2Y, T1s, T2X, T2O, T2P;
	       {
		    E Tj, TG, T2Q, T2V;
		    Tj = T7 + Ti;
		    TG = Tu + TF;
		    TH = Tj + TG;
		    T2L = Tj - TG;
		    T2Q = T2t + T2s;
		    T2V = T2R + T2U;
		    T2W = T2Q + T2V;
		    T2Y = T2V - T2Q;
	       }
	       {
		    E T14, T1r, T2M, T2N;
		    T14 = TS + T13;
		    T1r = T1f + T1q;
		    T1s = T14 + T1r;
		    T2X = T1r - T14;
		    T2M = T2C + T2D;
		    T2N = T2x + T2y;
		    T2O = T2M - T2N;
		    T2P = T2N + T2M;
	       }
	       ci[WS(rs, 7)] = TH - T1s;
	       cr[WS(rs, 12)] = T2X - T2Y;
	       ci[WS(rs, 11)] = T2X + T2Y;
	       cr[0] = TH + T1s;
	       cr[WS(rs, 4)] = T2L - T2O;
	       cr[WS(rs, 8)] = T2P - T2W;
	       ci[WS(rs, 15)] = T2P + T2W;
	       ci[WS(rs, 3)] = T2L + T2O;
	  }
	  {
	       E T2f, T2n, T3g, T3i, T2m, T3h, T2q, T3d;
	       {
		    E T2b, T2e, T3e, T3f;
		    T2b = T1t + T1w;
		    T2e = KP707106781 * (T2c + T2d);
		    T2f = T2b + T2e;
		    T2n = T2b - T2e;
		    T3e = KP707106781 * (T1H - T1C);
		    T3f = T38 - T37;
		    T3g = T3e + T3f;
		    T3i = T3f - T3e;
	       }
	       {
		    E T2i, T2l, T2o, T2p;
		    T2i = FMA(KP382683432, T2g, KP923879532 * T2h);
		    T2l = FNMS(KP382683432, T2k, KP923879532 * T2j);
		    T2m = T2i + T2l;
		    T3h = T2l - T2i;
		    T2o = FNMS(KP923879532, T2g, KP382683432 * T2h);
		    T2p = FMA(KP923879532, T2k, KP382683432 * T2j);
		    T2q = T2o + T2p;
		    T3d = T2p - T2o;
	       }
	       ci[WS(rs, 6)] = T2f - T2m;
	       cr[WS(rs, 13)] = T3h - T3i;
	       ci[WS(rs, 10)] = T3h + T3i;
	       cr[WS(rs, 1)] = T2f + T2m;
	       cr[WS(rs, 5)] = T2n - T2q;
	       cr[WS(rs, 9)] = T3d - T3g;
	       ci[WS(rs, 14)] = T3d + T3g;
	       ci[WS(rs, 2)] = T2n + T2q;
	  }
	  {
	       E T2v, T2H, T32, T34, T2G, T2Z, T2K, T33;
	       {
		    E T2r, T2u, T30, T31;
		    T2r = T7 - Ti;
		    T2u = T2s - T2t;
		    T2v = T2r - T2u;
		    T2H = T2r + T2u;
		    T30 = Tu - TF;
		    T31 = T2U - T2R;
		    T32 = T30 + T31;
		    T34 = T31 - T30;
	       }
	       {
		    E T2A, T2F, T2I, T2J;
		    T2A = T2w + T2z;
		    T2F = T2B - T2E;
		    T2G = KP707106781 * (T2A + T2F);
		    T2Z = KP707106781 * (T2F - T2A);
		    T2I = T2w - T2z;
		    T2J = T2B + T2E;
		    T2K = KP707106781 * (T2I + T2J);
		    T33 = KP707106781 * (T2J - T2I);
	       }
	       ci[WS(rs, 5)] = T2v - T2G;
	       cr[WS(rs, 10)] = T33 - T34;
	       ci[WS(rs, 13)] = T33 + T34;
	       cr[WS(rs, 2)] = T2v + T2G;
	       cr[WS(rs, 6)] = T2H - T2K;
	       cr[WS(rs, 14)] = T2Z - T32;
	       ci[WS(rs, 9)] = T2Z + T32;
	       ci[WS(rs, 1)] = T2H + T2K;
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 16},
     {TW_NEXT, 1, 0}
};

static const hc2hc_desc desc = { 16, "hf_16", twinstr, &GENUS, {136, 46, 38, 0} };

void X(codelet_hf_16) (planner *p) {
     X(khc2hc_register) (p, hf_16, &desc);
}
#endif				/* HAVE_FMA */
