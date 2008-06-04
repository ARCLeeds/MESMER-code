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
/* Generated on Tue Nov 13 17:51:45 EST 2007 */

#include "codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_hc2cdft -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -n 16 -dit -name hc2cfdft_16 -include hc2cf.h */

/*
 * This function contains 206 FP additions, 132 FP multiplications,
 * (or, 136 additions, 62 multiplications, 70 fused multiply/add),
 * 96 stack variables, and 64 memory accesses
 */
#include "hc2cf.h"

static void hc2cfdft_16(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DK(KP414213562, +0.414213562373095048801688724209698078569671875);
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 30); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 30, MAKE_VOLATILE_STRIDE(rs)) {
	  E T4d, T4g;
	  {
	       E T1f, T2e, T3D, T1K, T2g, T1c, T3H, T2W, T2j, TR, T3E, T2R, T2l, T11, T3G;
	       E T1v, T3p, T2s, Tl, T3o, T3w, T2G, T3z, T1Y, T23, T20, T2H, T21, T29, Tz;
	       E T26, TE, TA, T2v, T2J, T27, Tv, T2u, TB, T22, T28;
	       {
		    E T1o, T1u, T2T, T2V;
		    {
			 E T1I, T1A, T16, T1C, T1H, T1G, T2U, T1z, T1b, T1x, T1w;
			 {
			      E T1d, T1e, T14, T15;
			      T1d = Ip[0];
			      T1e = Im[0];
			      T14 = Ip[WS(rs, 4)];
			      T15 = Im[WS(rs, 4)];
			      {
				   E T1F, T1D, T1E, T19, T1a;
				   T1D = Rm[0];
				   T1I = T1d + T1e;
				   T1f = T1d - T1e;
				   T1E = Rp[0];
				   T1A = T14 + T15;
				   T16 = T14 - T15;
				   T1C = W[0];
				   T2e = T1E + T1D;
				   T1F = T1D - T1E;
				   T1H = W[1];
				   T19 = Rp[WS(rs, 4)];
				   T1a = Rm[WS(rs, 4)];
				   T1G = T1C * T1F;
				   T2U = T1H * T1F;
				   T1z = W[17];
				   T1b = T19 + T1a;
				   T1x = T1a - T19;
				   T1w = W[16];
			      }
			 }
			 {
			      E T2S, T1y, T13, T18;
			      T2S = T1z * T1x;
			      T1y = T1w * T1x;
			      T13 = W[14];
			      T18 = W[15];
			      {
				   E T1J, T1B, T2f, T17;
				   T1J = FNMS(T1H, T1I, T1G);
				   T1B = FNMS(T1z, T1A, T1y);
				   T2f = T13 * T1b;
				   T17 = T13 * T16;
				   T2T = FMA(T1w, T1A, T2S);
				   T3D = T1J - T1B;
				   T1K = T1B + T1J;
				   T2g = FMA(T18, T16, T2f);
				   T1c = FNMS(T18, T1b, T17);
				   T2V = FMA(T1C, T1I, T2U);
			      }
			 }
		    }
		    {
			 E T1n, TL, T1m, T1j, TQ, T1l, T2N, TV, T1t, T10, T1q, T1s, T1p, T1r, T2O;
			 E T2Q;
			 {
			      E TO, TP, TJ, TK;
			      TJ = Ip[WS(rs, 2)];
			      TK = Im[WS(rs, 2)];
			      TO = Rp[WS(rs, 2)];
			      T3H = T2V - T2T;
			      T2W = T2T + T2V;
			      T1n = TJ + TK;
			      TL = TJ - TK;
			      TP = Rm[WS(rs, 2)];
			      T1m = W[9];
			      T1j = W[8];
			      {
				   E TT, T1k, TU, TY, TZ;
				   TT = Ip[WS(rs, 6)];
				   TQ = TO + TP;
				   T1k = TP - TO;
				   TU = Im[WS(rs, 6)];
				   TY = Rp[WS(rs, 6)];
				   TZ = Rm[WS(rs, 6)];
				   T1l = T1j * T1k;
				   T2N = T1m * T1k;
				   TV = TT - TU;
				   T1t = TT + TU;
				   T10 = TY + TZ;
				   T1q = TZ - TY;
				   T1s = W[25];
				   T1p = W[24];
			      }
			 }
			 {
			      E TN, T2P, T2i, TM, TI;
			      TI = W[6];
			      TN = W[7];
			      T2P = T1s * T1q;
			      T1r = T1p * T1q;
			      T2i = TI * TQ;
			      TM = TI * TL;
			      T2O = FMA(T1j, T1n, T2N);
			      T2Q = FMA(T1p, T1t, T2P);
			      T2j = FMA(TN, TL, T2i);
			      TR = FNMS(TN, TQ, TM);
			 }
			 {
			      E TX, T2k, TW, TS;
			      TS = W[22];
			      T3E = T2O - T2Q;
			      T2R = T2O + T2Q;
			      TX = W[23];
			      T2k = TS * T10;
			      TW = TS * TV;
			      T1o = FNMS(T1m, T1n, T1l);
			      T1u = FNMS(T1s, T1t, T1r);
			      T2l = FMA(TX, TV, T2k);
			      T11 = FNMS(TX, T10, TW);
			 }
		    }
		    {
			 E T1Q, T1N, T2C, T1O, T1W, Te, T1T, Tj, Tf, T2q, T2E, T1U, Ta, T2p, Tg;
			 E T1P, T1V;
			 {
			      E T4, T9, T5, T2o, Tb, T1S, T1, T1M, T6;
			      {
				   E T2, T3, T7, T8;
				   T2 = Ip[WS(rs, 1)];
				   T3G = T1o - T1u;
				   T1v = T1o + T1u;
				   T3 = Im[WS(rs, 1)];
				   T7 = Rp[WS(rs, 1)];
				   T8 = Rm[WS(rs, 1)];
				   T1 = W[2];
				   T1Q = T2 + T3;
				   T4 = T2 - T3;
				   T1N = T7 - T8;
				   T9 = T7 + T8;
				   T1M = W[4];
				   T5 = T1 * T4;
			      }
			      {
				   E Tc, Td, Th, Ti;
				   Tc = Ip[WS(rs, 5)];
				   T2o = T1 * T9;
				   T2C = T1M * T1Q;
				   T1O = T1M * T1N;
				   Td = Im[WS(rs, 5)];
				   Th = Rp[WS(rs, 5)];
				   Ti = Rm[WS(rs, 5)];
				   Tb = W[18];
				   T1W = Tc + Td;
				   Te = Tc - Td;
				   T1T = Th - Ti;
				   Tj = Th + Ti;
				   T1S = W[20];
				   Tf = Tb * Te;
			      }
			      T6 = W[3];
			      T2q = Tb * Tj;
			      T2E = T1S * T1W;
			      T1U = T1S * T1T;
			      Ta = FNMS(T6, T9, T5);
			      T2p = FMA(T6, T4, T2o);
			      Tg = W[19];
			      T1P = W[5];
			      T1V = W[21];
			 }
			 {
			      E Tp, Tu, Tq, T2t, Tw, T25, Tm, T1Z, Tr;
			      {
				   E Tn, To, Ts, Tt, T2r, Tk;
				   Tn = Ip[WS(rs, 7)];
				   T2r = FMA(Tg, Te, T2q);
				   Tk = FNMS(Tg, Tj, Tf);
				   {
					E T2D, T1R, T2F, T1X;
					T2D = FNMS(T1P, T1N, T2C);
					T1R = FMA(T1P, T1Q, T1O);
					T2F = FNMS(T1V, T1T, T2E);
					T1X = FMA(T1V, T1W, T1U);
					T3p = T2p - T2r;
					T2s = T2p + T2r;
					Tl = Ta + Tk;
					T3o = Ta - Tk;
					T3w = T2F - T2D;
					T2G = T2D + T2F;
					T3z = T1X - T1R;
					T1Y = T1R + T1X;
					To = Im[WS(rs, 7)];
				   }
				   Ts = Rp[WS(rs, 7)];
				   Tt = Rm[WS(rs, 7)];
				   Tm = W[26];
				   T23 = Tn + To;
				   Tp = Tn - To;
				   T20 = Ts - Tt;
				   Tu = Ts + Tt;
				   T1Z = W[28];
				   Tq = Tm * Tp;
			      }
			      {
				   E Tx, Ty, TC, TD;
				   Tx = Ip[WS(rs, 3)];
				   T2t = Tm * Tu;
				   T2H = T1Z * T23;
				   T21 = T1Z * T20;
				   Ty = Im[WS(rs, 3)];
				   TC = Rp[WS(rs, 3)];
				   TD = Rm[WS(rs, 3)];
				   Tw = W[10];
				   T29 = Tx + Ty;
				   Tz = Tx - Ty;
				   T26 = TC - TD;
				   TE = TC + TD;
				   T25 = W[12];
				   TA = Tw * Tz;
			      }
			      Tr = W[27];
			      T2v = Tw * TE;
			      T2J = T25 * T29;
			      T27 = T25 * T26;
			      Tv = FNMS(Tr, Tu, Tq);
			      T2u = FMA(Tr, Tp, T2t);
			      TB = W[11];
			      T22 = W[29];
			      T28 = W[13];
			 }
		    }
	       }
	       {
		    E T3r, T3s, T3A, T3x, T3M, T3l, T3L, T3m, T3f, T3i;
		    {
			 E T3c, TH, T36, T3g, T3h, T39, T32, T1h, T2A, T2d, T2h, T31, T2y, T30, T2Y;
			 E T2m, T2B, T1i;
			 {
			      E T2x, T2M, T1L, T2c, T2X, T12, T1g;
			      {
				   E TG, T2b, T34, T2L, T2w, TF, T37, T38, T35;
				   T2w = FMA(TB, Tz, T2v);
				   TF = FNMS(TB, TE, TA);
				   {
					E T2I, T24, T2K, T2a;
					T2I = FNMS(T22, T20, T2H);
					T24 = FMA(T22, T23, T21);
					T2K = FNMS(T28, T26, T2J);
					T2a = FMA(T28, T29, T27);
					T3r = T2u - T2w;
					T2x = T2u + T2w;
					TG = Tv + TF;
					T3s = Tv - TF;
					T2L = T2I + T2K;
					T3A = T2I - T2K;
					T3x = T2a - T24;
					T2b = T24 + T2a;
				   }
				   T2M = T2G + T2L;
				   T34 = T2L - T2G;
				   T37 = T1K - T1v;
				   T1L = T1v + T1K;
				   T2c = T1Y + T2b;
				   T35 = T1Y - T2b;
				   T3c = Tl - TG;
				   TH = Tl + TG;
				   T38 = T2W - T2R;
				   T2X = T2R + T2W;
				   T36 = T34 + T35;
				   T3g = T34 - T35;
				   T3M = TR - T11;
				   T12 = TR + T11;
				   T3h = T37 + T38;
				   T39 = T37 - T38;
				   T1g = T1c + T1f;
				   T3l = T1f - T1c;
			      }
			      T32 = T1g - T12;
			      T1h = T12 + T1g;
			      T2A = T2c + T1L;
			      T2d = T1L - T2c;
			      T3L = T2e - T2g;
			      T2h = T2e + T2g;
			      T31 = T2x - T2s;
			      T2y = T2s + T2x;
			      T30 = T2M + T2X;
			      T2Y = T2M - T2X;
			      T2m = T2j + T2l;
			      T3m = T2j - T2l;
			 }
			 T2B = T1h - TH;
			 T1i = TH + T1h;
			 {
			      E T3e, T3d, T3j, T3k;
			      {
				   E T33, T3b, T2z, T2Z, T3a, T2n;
				   T3f = T32 - T31;
				   T33 = T31 + T32;
				   T3b = T2h - T2m;
				   T2n = T2h + T2m;
				   Im[WS(rs, 7)] = KP500000000 * (T2d - T1i);
				   Ip[0] = KP500000000 * (T1i + T2d);
				   Im[WS(rs, 3)] = KP500000000 * (T2Y - T2B);
				   Ip[WS(rs, 4)] = KP500000000 * (T2B + T2Y);
				   T2z = T2n - T2y;
				   T2Z = T2n + T2y;
				   T3a = T36 + T39;
				   T3e = T39 - T36;
				   T3d = T3b - T3c;
				   T3j = T3b + T3c;
				   Rp[WS(rs, 4)] = KP500000000 * (T2z + T2A);
				   Rm[WS(rs, 3)] = KP500000000 * (T2z - T2A);
				   Rp[0] = KP500000000 * (T2Z + T30);
				   Rm[WS(rs, 7)] = KP500000000 * (T2Z - T30);
				   Im[WS(rs, 5)] = -(KP500000000 * (FNMS(KP707106781, T3a, T33)));
				   Ip[WS(rs, 2)] = KP500000000 * (FMA(KP707106781, T3a, T33));
				   T3k = T3g + T3h;
				   T3i = T3g - T3h;
			      }
			      Rp[WS(rs, 2)] = KP500000000 * (FMA(KP707106781, T3k, T3j));
			      Rm[WS(rs, 5)] = KP500000000 * (FNMS(KP707106781, T3k, T3j));
			      Rp[WS(rs, 6)] = KP500000000 * (FMA(KP707106781, T3e, T3d));
			      Rm[WS(rs, 1)] = KP500000000 * (FNMS(KP707106781, T3e, T3d));
			 }
		    }
		    {
			 E T3Z, T3n, T3F, T3I, T4e, T44, T4f, T47, T4a, T3u, T3U, T3C, T49, T3N, T40;
			 E T3Q;
			 {
			      E T3y, T3B, T3O, T3q, T3t, T3P;
			      {
				   E T42, T43, T45, T46;
				   T3y = T3w + T3x;
				   T42 = T3w - T3x;
				   Im[WS(rs, 1)] = -(KP500000000 * (FNMS(KP707106781, T3i, T3f)));
				   Ip[WS(rs, 6)] = KP500000000 * (FMA(KP707106781, T3i, T3f));
				   T3Z = T3m + T3l;
				   T3n = T3l - T3m;
				   T43 = T3A - T3z;
				   T3B = T3z + T3A;
				   T3F = T3D - T3E;
				   T45 = T3E + T3D;
				   T46 = T3H - T3G;
				   T3I = T3G + T3H;
				   T3O = T3p + T3o;
				   T3q = T3o - T3p;
				   T4e = FNMS(KP414213562, T42, T43);
				   T44 = FMA(KP414213562, T43, T42);
				   T4f = FNMS(KP414213562, T45, T46);
				   T47 = FMA(KP414213562, T46, T45);
				   T3t = T3r + T3s;
				   T3P = T3r - T3s;
			      }
			      T4a = T3q - T3t;
			      T3u = T3q + T3t;
			      T3U = FNMS(KP414213562, T3y, T3B);
			      T3C = FMA(KP414213562, T3B, T3y);
			      T49 = T3L - T3M;
			      T3N = T3L + T3M;
			      T40 = T3P - T3O;
			      T3Q = T3O + T3P;
			 }
			 {
			      E T3T, T3v, T3X, T3R, T3J, T3V;
			      T3T = FNMS(KP707106781, T3u, T3n);
			      T3v = FMA(KP707106781, T3u, T3n);
			      T3X = FMA(KP707106781, T3Q, T3N);
			      T3R = FNMS(KP707106781, T3Q, T3N);
			      T3J = FNMS(KP414213562, T3I, T3F);
			      T3V = FMA(KP414213562, T3F, T3I);
			      {
				   E T4c, T4b, T4h, T4i, T41, T48;
				   T4d = FMA(KP707106781, T40, T3Z);
				   T41 = FNMS(KP707106781, T40, T3Z);
				   T48 = T44 - T47;
				   T4c = T44 + T47;
				   {
					E T3Y, T3W, T3K, T3S;
					T3Y = T3U + T3V;
					T3W = T3U - T3V;
					T3K = T3C + T3J;
					T3S = T3J - T3C;
					Im[WS(rs, 2)] = -(KP500000000 * (FNMS(KP923879532, T3W, T3T)));
					Ip[WS(rs, 5)] = KP500000000 * (FMA(KP923879532, T3W, T3T));
					Rp[WS(rs, 1)] = KP500000000 * (FMA(KP923879532, T3Y, T3X));
					Rm[WS(rs, 6)] = KP500000000 * (FNMS(KP923879532, T3Y, T3X));
					Rp[WS(rs, 5)] = KP500000000 * (FMA(KP923879532, T3S, T3R));
					Rm[WS(rs, 2)] = KP500000000 * (FNMS(KP923879532, T3S, T3R));
					Im[WS(rs, 6)] = -(KP500000000 * (FNMS(KP923879532, T3K, T3v)));
					Ip[WS(rs, 1)] = KP500000000 * (FMA(KP923879532, T3K, T3v));
					Ip[WS(rs, 7)] = KP500000000 * (FMA(KP923879532, T48, T41));
					Im[0] = -(KP500000000 * (FNMS(KP923879532, T48, T41)));
				   }
				   T4b = FMA(KP707106781, T4a, T49);
				   T4h = FNMS(KP707106781, T4a, T49);
				   T4i = T4e + T4f;
				   T4g = T4e - T4f;
				   Rm[0] = KP500000000 * (FMA(KP923879532, T4i, T4h));
				   Rp[WS(rs, 7)] = KP500000000 * (FNMS(KP923879532, T4i, T4h));
				   Rp[WS(rs, 3)] = KP500000000 * (FMA(KP923879532, T4c, T4b));
				   Rm[WS(rs, 4)] = KP500000000 * (FNMS(KP923879532, T4c, T4b));
			      }
			 }
		    }
	       }
	  }
	  Im[WS(rs, 4)] = -(KP500000000 * (FNMS(KP923879532, T4g, T4d)));
	  Ip[WS(rs, 3)] = KP500000000 * (FMA(KP923879532, T4g, T4d));
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 16},
     {TW_NEXT, 1, 0}
};

static const hc2c_desc desc = { 16, "hc2cfdft_16", twinstr, &GENUS, {136, 62, 70, 0} };

void X(codelet_hc2cfdft_16) (planner *p) {
     X(khc2c_register) (p, hc2cfdft_16, &desc, HC2C_VIA_DFT);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_hc2cdft -compact -variables 4 -pipeline-latency 4 -n 16 -dit -name hc2cfdft_16 -include hc2cf.h */

/*
 * This function contains 206 FP additions, 100 FP multiplications,
 * (or, 168 additions, 62 multiplications, 38 fused multiply/add),
 * 61 stack variables, and 64 memory accesses
 */
#include "hc2cf.h"

static void hc2cfdft_16(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP461939766, +0.461939766255643378064091594698394143411208313);
     DK(KP191341716, +0.191341716182544885864229992015199433380672281);
     DK(KP353553390, +0.353553390593273762200422181052424519642417969);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 30); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 30, MAKE_VOLATILE_STRIDE(rs)) {
	  E T19, T3h, T21, T2Y, T1o, T3d, T2s, T39, TW, T3i, T24, T2Z, T1z, T3c, T2p;
	  E T3a, Tj, T2S, T28, T2R, T1L, T36, T2i, T32, TC, T2V, T2b, T2U, T1W, T35;
	  E T2l, T33;
	  {
	       E T10, T1m, T14, T1k, T18, T1h, T1f, T1Z;
	       {
		    E TY, TZ, T12, T13;
		    TY = Ip[WS(rs, 4)];
		    TZ = Im[WS(rs, 4)];
		    T10 = TY - TZ;
		    T1m = TY + TZ;
		    T12 = Rp[WS(rs, 4)];
		    T13 = Rm[WS(rs, 4)];
		    T14 = T12 + T13;
		    T1k = T12 - T13;
	       }
	       {
		    E T16, T17, T1d, T1e;
		    T16 = Ip[0];
		    T17 = Im[0];
		    T18 = T16 - T17;
		    T1h = T16 + T17;
		    T1d = Rm[0];
		    T1e = Rp[0];
		    T1f = T1d - T1e;
		    T1Z = T1e + T1d;
	       }
	       {
		    E T15, T20, TX, T11;
		    TX = W[14];
		    T11 = W[15];
		    T15 = FNMS(T11, T14, TX * T10);
		    T20 = FMA(TX, T14, T11 * T10);
		    T19 = T15 + T18;
		    T3h = T1Z - T20;
		    T21 = T1Z + T20;
		    T2Y = T18 - T15;
	       }
	       {
		    E T1i, T2r, T1n, T2q;
		    {
			 E T1c, T1g, T1j, T1l;
			 T1c = W[0];
			 T1g = W[1];
			 T1i = FNMS(T1g, T1h, T1c * T1f);
			 T2r = FMA(T1g, T1f, T1c * T1h);
			 T1j = W[16];
			 T1l = W[17];
			 T1n = FMA(T1j, T1k, T1l * T1m);
			 T2q = FNMS(T1l, T1k, T1j * T1m);
		    }
		    T1o = T1i - T1n;
		    T3d = T2r - T2q;
		    T2s = T2q + T2r;
		    T39 = T1n + T1i;
	       }
	  }
	  {
	       E TH, T1s, TL, T1q, TQ, T1x, TU, T1v;
	       {
		    E TF, TG, TJ, TK;
		    TF = Ip[WS(rs, 2)];
		    TG = Im[WS(rs, 2)];
		    TH = TF - TG;
		    T1s = TF + TG;
		    TJ = Rp[WS(rs, 2)];
		    TK = Rm[WS(rs, 2)];
		    TL = TJ + TK;
		    T1q = TJ - TK;
	       }
	       {
		    E TO, TP, TS, TT;
		    TO = Ip[WS(rs, 6)];
		    TP = Im[WS(rs, 6)];
		    TQ = TO - TP;
		    T1x = TO + TP;
		    TS = Rp[WS(rs, 6)];
		    TT = Rm[WS(rs, 6)];
		    TU = TS + TT;
		    T1v = TS - TT;
	       }
	       {
		    E TM, T22, TV, T23;
		    {
			 E TE, TI, TN, TR;
			 TE = W[6];
			 TI = W[7];
			 TM = FNMS(TI, TL, TE * TH);
			 T22 = FMA(TE, TL, TI * TH);
			 TN = W[22];
			 TR = W[23];
			 TV = FNMS(TR, TU, TN * TQ);
			 T23 = FMA(TN, TU, TR * TQ);
		    }
		    TW = TM + TV;
		    T3i = TM - TV;
		    T24 = T22 + T23;
		    T2Z = T22 - T23;
	       }
	       {
		    E T1t, T2n, T1y, T2o;
		    {
			 E T1p, T1r, T1u, T1w;
			 T1p = W[8];
			 T1r = W[9];
			 T1t = FMA(T1p, T1q, T1r * T1s);
			 T2n = FNMS(T1r, T1q, T1p * T1s);
			 T1u = W[24];
			 T1w = W[25];
			 T1y = FMA(T1u, T1v, T1w * T1x);
			 T2o = FNMS(T1w, T1v, T1u * T1x);
		    }
		    T1z = T1t + T1y;
		    T3c = T1y - T1t;
		    T2p = T2n + T2o;
		    T3a = T2n - T2o;
	       }
	  }
	  {
	       E T4, T1E, T8, T1C, Td, T1J, Th, T1H;
	       {
		    E T2, T3, T6, T7;
		    T2 = Ip[WS(rs, 1)];
		    T3 = Im[WS(rs, 1)];
		    T4 = T2 - T3;
		    T1E = T2 + T3;
		    T6 = Rp[WS(rs, 1)];
		    T7 = Rm[WS(rs, 1)];
		    T8 = T6 + T7;
		    T1C = T6 - T7;
	       }
	       {
		    E Tb, Tc, Tf, Tg;
		    Tb = Ip[WS(rs, 5)];
		    Tc = Im[WS(rs, 5)];
		    Td = Tb - Tc;
		    T1J = Tb + Tc;
		    Tf = Rp[WS(rs, 5)];
		    Tg = Rm[WS(rs, 5)];
		    Th = Tf + Tg;
		    T1H = Tf - Tg;
	       }
	       {
		    E T9, T26, Ti, T27;
		    {
			 E T1, T5, Ta, Te;
			 T1 = W[2];
			 T5 = W[3];
			 T9 = FNMS(T5, T8, T1 * T4);
			 T26 = FMA(T1, T8, T5 * T4);
			 Ta = W[18];
			 Te = W[19];
			 Ti = FNMS(Te, Th, Ta * Td);
			 T27 = FMA(Ta, Th, Te * Td);
		    }
		    Tj = T9 + Ti;
		    T2S = T26 - T27;
		    T28 = T26 + T27;
		    T2R = T9 - Ti;
	       }
	       {
		    E T1F, T2g, T1K, T2h;
		    {
			 E T1B, T1D, T1G, T1I;
			 T1B = W[4];
			 T1D = W[5];
			 T1F = FMA(T1B, T1C, T1D * T1E);
			 T2g = FNMS(T1D, T1C, T1B * T1E);
			 T1G = W[20];
			 T1I = W[21];
			 T1K = FMA(T1G, T1H, T1I * T1J);
			 T2h = FNMS(T1I, T1H, T1G * T1J);
		    }
		    T1L = T1F + T1K;
		    T36 = T2g - T2h;
		    T2i = T2g + T2h;
		    T32 = T1K - T1F;
	       }
	  }
	  {
	       E Tn, T1P, Tr, T1N, Tw, T1U, TA, T1S;
	       {
		    E Tl, Tm, Tp, Tq;
		    Tl = Ip[WS(rs, 7)];
		    Tm = Im[WS(rs, 7)];
		    Tn = Tl - Tm;
		    T1P = Tl + Tm;
		    Tp = Rp[WS(rs, 7)];
		    Tq = Rm[WS(rs, 7)];
		    Tr = Tp + Tq;
		    T1N = Tp - Tq;
	       }
	       {
		    E Tu, Tv, Ty, Tz;
		    Tu = Ip[WS(rs, 3)];
		    Tv = Im[WS(rs, 3)];
		    Tw = Tu - Tv;
		    T1U = Tu + Tv;
		    Ty = Rp[WS(rs, 3)];
		    Tz = Rm[WS(rs, 3)];
		    TA = Ty + Tz;
		    T1S = Ty - Tz;
	       }
	       {
		    E Ts, T29, TB, T2a;
		    {
			 E Tk, To, Tt, Tx;
			 Tk = W[26];
			 To = W[27];
			 Ts = FNMS(To, Tr, Tk * Tn);
			 T29 = FMA(Tk, Tr, To * Tn);
			 Tt = W[10];
			 Tx = W[11];
			 TB = FNMS(Tx, TA, Tt * Tw);
			 T2a = FMA(Tt, TA, Tx * Tw);
		    }
		    TC = Ts + TB;
		    T2V = Ts - TB;
		    T2b = T29 + T2a;
		    T2U = T29 - T2a;
	       }
	       {
		    E T1Q, T2j, T1V, T2k;
		    {
			 E T1M, T1O, T1R, T1T;
			 T1M = W[28];
			 T1O = W[29];
			 T1Q = FMA(T1M, T1N, T1O * T1P);
			 T2j = FNMS(T1O, T1N, T1M * T1P);
			 T1R = W[12];
			 T1T = W[13];
			 T1V = FMA(T1R, T1S, T1T * T1U);
			 T2k = FNMS(T1T, T1S, T1R * T1U);
		    }
		    T1W = T1Q + T1V;
		    T35 = T1V - T1Q;
		    T2l = T2j + T2k;
		    T33 = T2j - T2k;
	       }
	  }
	  {
	       E T1b, T2f, T2u, T2w, T1Y, T2e, T2d, T2v;
	       {
		    E TD, T1a, T2m, T2t;
		    TD = Tj + TC;
		    T1a = TW + T19;
		    T1b = TD + T1a;
		    T2f = T1a - TD;
		    T2m = T2i + T2l;
		    T2t = T2p + T2s;
		    T2u = T2m - T2t;
		    T2w = T2m + T2t;
	       }
	       {
		    E T1A, T1X, T25, T2c;
		    T1A = T1o - T1z;
		    T1X = T1L + T1W;
		    T1Y = T1A - T1X;
		    T2e = T1X + T1A;
		    T25 = T21 + T24;
		    T2c = T28 + T2b;
		    T2d = T25 - T2c;
		    T2v = T25 + T2c;
	       }
	       Ip[0] = KP500000000 * (T1b + T1Y);
	       Rp[0] = KP500000000 * (T2v + T2w);
	       Im[WS(rs, 7)] = KP500000000 * (T1Y - T1b);
	       Rm[WS(rs, 7)] = KP500000000 * (T2v - T2w);
	       Rm[WS(rs, 3)] = KP500000000 * (T2d - T2e);
	       Im[WS(rs, 3)] = KP500000000 * (T2u - T2f);
	       Rp[WS(rs, 4)] = KP500000000 * (T2d + T2e);
	       Ip[WS(rs, 4)] = KP500000000 * (T2f + T2u);
	  }
	  {
	       E T2z, T2L, T2J, T2P, T2C, T2M, T2F, T2N;
	       {
		    E T2x, T2y, T2H, T2I;
		    T2x = T2b - T28;
		    T2y = T19 - TW;
		    T2z = KP500000000 * (T2x + T2y);
		    T2L = KP500000000 * (T2y - T2x);
		    T2H = T21 - T24;
		    T2I = Tj - TC;
		    T2J = KP500000000 * (T2H - T2I);
		    T2P = KP500000000 * (T2H + T2I);
	       }
	       {
		    E T2A, T2B, T2D, T2E;
		    T2A = T2l - T2i;
		    T2B = T1L - T1W;
		    T2C = T2A + T2B;
		    T2M = T2A - T2B;
		    T2D = T1z + T1o;
		    T2E = T2s - T2p;
		    T2F = T2D - T2E;
		    T2N = T2D + T2E;
	       }
	       {
		    E T2G, T2Q, T2K, T2O;
		    T2G = KP353553390 * (T2C + T2F);
		    Ip[WS(rs, 2)] = T2z + T2G;
		    Im[WS(rs, 5)] = T2G - T2z;
		    T2Q = KP353553390 * (T2M + T2N);
		    Rm[WS(rs, 5)] = T2P - T2Q;
		    Rp[WS(rs, 2)] = T2P + T2Q;
		    T2K = KP353553390 * (T2F - T2C);
		    Rm[WS(rs, 1)] = T2J - T2K;
		    Rp[WS(rs, 6)] = T2J + T2K;
		    T2O = KP353553390 * (T2M - T2N);
		    Ip[WS(rs, 6)] = T2L + T2O;
		    Im[WS(rs, 1)] = T2O - T2L;
	       }
	  }
	  {
	       E T30, T3w, T3F, T3j, T2X, T3G, T3D, T3L, T3m, T3v, T38, T3q, T3A, T3K, T3f;
	       E T3r;
	       {
		    E T2T, T2W, T34, T37;
		    T30 = KP500000000 * (T2Y - T2Z);
		    T3w = KP500000000 * (T2Z + T2Y);
		    T3F = KP500000000 * (T3h - T3i);
		    T3j = KP500000000 * (T3h + T3i);
		    T2T = T2R - T2S;
		    T2W = T2U + T2V;
		    T2X = KP353553390 * (T2T + T2W);
		    T3G = KP353553390 * (T2T - T2W);
		    {
			 E T3B, T3C, T3k, T3l;
			 T3B = T3a + T39;
			 T3C = T3d - T3c;
			 T3D = FNMS(KP461939766, T3C, KP191341716 * T3B);
			 T3L = FMA(KP461939766, T3B, KP191341716 * T3C);
			 T3k = T2S + T2R;
			 T3l = T2U - T2V;
			 T3m = KP353553390 * (T3k + T3l);
			 T3v = KP353553390 * (T3l - T3k);
		    }
		    T34 = T32 + T33;
		    T37 = T35 - T36;
		    T38 = FMA(KP191341716, T34, KP461939766 * T37);
		    T3q = FNMS(KP191341716, T37, KP461939766 * T34);
		    {
			 E T3y, T3z, T3b, T3e;
			 T3y = T33 - T32;
			 T3z = T36 + T35;
			 T3A = FMA(KP461939766, T3y, KP191341716 * T3z);
			 T3K = FNMS(KP461939766, T3z, KP191341716 * T3y);
			 T3b = T39 - T3a;
			 T3e = T3c + T3d;
			 T3f = FNMS(KP191341716, T3e, KP461939766 * T3b);
			 T3r = FMA(KP191341716, T3b, KP461939766 * T3e);
		    }
	       }
	       {
		    E T31, T3g, T3t, T3u;
		    T31 = T2X + T30;
		    T3g = T38 + T3f;
		    Ip[WS(rs, 1)] = T31 + T3g;
		    Im[WS(rs, 6)] = T3g - T31;
		    T3t = T3j + T3m;
		    T3u = T3q + T3r;
		    Rm[WS(rs, 6)] = T3t - T3u;
		    Rp[WS(rs, 1)] = T3t + T3u;
	       }
	       {
		    E T3n, T3o, T3p, T3s;
		    T3n = T3j - T3m;
		    T3o = T3f - T38;
		    Rm[WS(rs, 2)] = T3n - T3o;
		    Rp[WS(rs, 5)] = T3n + T3o;
		    T3p = T30 - T2X;
		    T3s = T3q - T3r;
		    Ip[WS(rs, 5)] = T3p + T3s;
		    Im[WS(rs, 2)] = T3s - T3p;
	       }
	       {
		    E T3x, T3E, T3N, T3O;
		    T3x = T3v + T3w;
		    T3E = T3A + T3D;
		    Ip[WS(rs, 3)] = T3x + T3E;
		    Im[WS(rs, 4)] = T3E - T3x;
		    T3N = T3F + T3G;
		    T3O = T3K + T3L;
		    Rm[WS(rs, 4)] = T3N - T3O;
		    Rp[WS(rs, 3)] = T3N + T3O;
	       }
	       {
		    E T3H, T3I, T3J, T3M;
		    T3H = T3F - T3G;
		    T3I = T3D - T3A;
		    Rm[0] = T3H - T3I;
		    Rp[WS(rs, 7)] = T3H + T3I;
		    T3J = T3w - T3v;
		    T3M = T3K - T3L;
		    Ip[WS(rs, 7)] = T3J + T3M;
		    Im[0] = T3M - T3J;
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 16},
     {TW_NEXT, 1, 0}
};

static const hc2c_desc desc = { 16, "hc2cfdft_16", twinstr, &GENUS, {168, 62, 38, 0} };

void X(codelet_hc2cfdft_16) (planner *p) {
     X(khc2c_register) (p, hc2cfdft_16, &desc, HC2C_VIA_DFT);
}
#endif				/* HAVE_FMA */
