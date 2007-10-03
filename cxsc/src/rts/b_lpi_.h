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

/* CVS $Id: b_lpi_.h,v 1.10 2007/05/16 14:59:23 cxsc Exp $ */

/*
 * Descriptive Name : Lpi.h              Processor : C
 *
 * Predefined approximations for PI/4 and 4/PI
 * ============================================
 *
 */

static a_btyp    mPiov4[Lpi_init]     = {
#if SHORTABTYP
                 0xc90fdaa2 ,0x2168c234 ,0xc4c6628b ,0x80dc1cd1 ,0x29024e08 ,
                 0x8a67cc74 ,0x020bbea6 ,0x3b139b22 ,0x514a0879 ,0x8e3404dd ,
                 0xef9519b3 ,0xcd3a431b ,0x302b0a6d ,0xf25f1437 ,0x4fe1356d ,
                 0x6d51c245 ,0xe485b576 ,0x625e7ec6 ,0xf44c42e9 ,0xa637ed6b ,
                 0x0bff5cb6 ,0xf406b7ed ,0xee386bfb ,0x5a899fa5 ,0xae9f2411 ,
                 0x7c4b1fe6 ,0x49286651 ,0xece45b3d ,0xc2007cb8 ,0xa163bf05 ,
                 0x98da4836 ,0x1c55d39a ,0x69163fa8 ,0xfd24cf5f ,0x83655d23 ,
                 0xdca3ad96 ,0x1c62f356 ,0x208552bb ,0x9ed52907 ,0x7096966d ,
                 0x670c354e ,0x4abc9804 ,0xf1746c08 ,0xca18217c ,0x32905e46 ,
                 0x2e36ce3b ,0xe39e772c ,0x180e8603 ,0x9b2783a2 ,0xec07a28f ,
                 0xb5c55df0 ,0x6f4c52c9 ,0xde2bcbf6 ,0x95581718 ,0x3995497c ,
                 0xea956ae5 ,0x15d22618 ,0x98fa0510 ,0x15728e5a ,0x8aaac42d ,
                 0xad33170d ,0x04507a33 ,0xa85521ab ,0xdf1cba64 ,0xecfb8504 ,
                 0x58dbef0a ,0x8aea7157 ,0x5d060c7d ,0xb3970f85 ,0xa6e1e4c7 ,
                 0xabf5ae8c ,0xdb0933d7 ,0x1e8c94e0 ,0x4a25619d ,0xcee3d226 ,
                 0x1ad2ee6b ,0xf12ffa06 ,0xd98a0864 ,0xd8760273 ,0x3ec86a64 ,
                 0x521f2b18 ,0x177b200c ,0xbbe11757 ,0x7a615d6c ,0x770988c0 ,
                 0xbad946e2 ,0x08e24fa0 ,0x74e5ab31 ,0x43db5bfc ,0xe0fd108e ,
                 0x4b82d120 ,0xa9210801 ,0x1a723c12 ,0xa787e6d7 ,0x88719a10 ,
                 0xbdba5b26 ,0x99c32718 ,0x6af4e23c ,0x1a946834 ,0xb6150bda 
#else
                 0xc90fdaa2L,0x2168c234L,0xc4c6628bL,0x80dc1cd1L,0x29024e08L,
                 0x8a67cc74L,0x020bbea6L,0x3b139b22L,0x514a0879L,0x8e3404ddL,
                 0xef9519b3L,0xcd3a431bL,0x302b0a6dL,0xf25f1437L,0x4fe1356dL,
                 0x6d51c245L,0xe485b576L,0x625e7ec6L,0xf44c42e9L,0xa637ed6bL,
                 0x0bff5cb6L,0xf406b7edL,0xee386bfbL,0x5a899fa5L,0xae9f2411L,
                 0x7c4b1fe6L,0x49286651L,0xece45b3dL,0xc2007cb8L,0xa163bf05L,
                 0x98da4836L,0x1c55d39aL,0x69163fa8L,0xfd24cf5fL,0x83655d23L,
                 0xdca3ad96L,0x1c62f356L,0x208552bbL,0x9ed52907L,0x7096966dL,
                 0x670c354eL,0x4abc9804L,0xf1746c08L,0xca18217cL,0x32905e46L,
                 0x2e36ce3bL,0xe39e772cL,0x180e8603L,0x9b2783a2L,0xec07a28fL,
                 0xb5c55df0L,0x6f4c52c9L,0xde2bcbf6L,0x95581718L,0x3995497cL,
                 0xea956ae5L,0x15d22618L,0x98fa0510L,0x15728e5aL,0x8aaac42dL,
                 0xad33170dL,0x04507a33L,0xa85521abL,0xdf1cba64L,0xecfb8504L,
                 0x58dbef0aL,0x8aea7157L,0x5d060c7dL,0xb3970f85L,0xa6e1e4c7L,
                 0xabf5ae8cL,0xdb0933d7L,0x1e8c94e0L,0x4a25619dL,0xcee3d226L,
                 0x1ad2ee6bL,0xf12ffa06L,0xd98a0864L,0xd8760273L,0x3ec86a64L,
                 0x521f2b18L,0x177b200cL,0xbbe11757L,0x7a615d6cL,0x770988c0L,
                 0xbad946e2L,0x08e24fa0L,0x74e5ab31L,0x43db5bfcL,0xe0fd108eL,
                 0x4b82d120L,0xa9210801L,0x1a723c12L,0xa787e6d7L,0x88719a10L,
                 0xbdba5b26L,0x99c32718L,0x6af4e23cL,0x1a946834L,0xb6150bdaL
#endif
                 };

static a_btyp    m4ovPi[Lpi_init]  = {
#if SHORTABTYP
                 0x00000001 ,0x45f306dc ,0x9c882a53 ,0xf84eafa3 ,0xea69bb81 ,
                 0xb6c52b32 ,0x78872083 ,0xfca2c757 ,0xbd778ac3 ,0x6e48dc74 ,
                 0x849ba5c0 ,0x0c925dd4 ,0x13a32439 ,0xfc3bd639 ,0x62534e7d ,
                 0xd1046bea ,0x5d768909 ,0xd338e04d ,0x68befc82 ,0x7323ac73 ,
                 0x06a673e9 ,0x3908bf17 ,0x7bf25076 ,0x3ff12fff ,0xbc0b301f ,
                 0xde5e2316 ,0xb414da3e ,0xda6cfd9e ,0x4f96136e ,0x9e8c7ecd ,
                 0x3cbfd45a ,0xea4f758f ,0xd7cbe2f6 ,0x7a0e73ef ,0x14a525d4 ,
                 0xd7f6bf62 ,0x3f1aba10 ,0xac06608d ,0xf8f6d757 ,0xe19f7841 ,
                 0x35e86c3b ,0x53c722c2 ,0xbdcc3610 ,0xcb330abe ,0x2940d081 ,
                 0x1bffb100 ,0x9ae64e62 ,0x0c0c2aad ,0x94e75192 ,0xc1c4f781 ,
                 0x18d68f88 ,0x3386cf9b ,0xb9d01255 ,0x06b388ed ,0x172c394d ,
                 0xbb5e89a2 ,0xae320a7d ,0x4bfe0e0a ,0x7efc67d0 ,0x6585bc9f ,
                 0x3064fb77 ,0x867a4dde ,0xd63cbdf1 ,0x3e743e6b ,0x95e4fe3b ,
                 0x0fe24320 ,0xf8f848d5 ,0xf4ddaaee ,0x5a608676 ,0x2b8c296b ,
                 0x3a338785 ,0x895a829a ,0x58ba0018 ,0x8cfb0c5a ,0xe3c7358d ,
                 0x3600c466 ,0xf9a5692f ,0x4f69aaaa ,0x6fec7dae ,0x302147f8 ,
                 0xec9a553a ,0xc957aee1 ,0xf0f8c6af ,0x60f5ce2a ,0x2eac9381 ,
                 0xb3ac7671 ,0x094f9646 ,0x48ef15ac ,0x46a8b572 ,0x3e003615 ,
                 0xe3bf9c33 ,0xfe633ed4 ,0x3cccc2af ,0x328ff759 ,0xb0fefd6e ,
                 0xca4513d0 ,0x64c17fcd ,0x9b89de12 ,0x6cd9a87e ,0xbbafbc2d 
#else
                 0x00000001L,0x45f306dcL,0x9c882a53L,0xf84eafa3L,0xea69bb81L,
                 0xb6c52b32L,0x78872083L,0xfca2c757L,0xbd778ac3L,0x6e48dc74L,
                 0x849ba5c0L,0x0c925dd4L,0x13a32439L,0xfc3bd639L,0x62534e7dL,
                 0xd1046beaL,0x5d768909L,0xd338e04dL,0x68befc82L,0x7323ac73L,
                 0x06a673e9L,0x3908bf17L,0x7bf25076L,0x3ff12fffL,0xbc0b301fL,
                 0xde5e2316L,0xb414da3eL,0xda6cfd9eL,0x4f96136eL,0x9e8c7ecdL,
                 0x3cbfd45aL,0xea4f758fL,0xd7cbe2f6L,0x7a0e73efL,0x14a525d4L,
                 0xd7f6bf62L,0x3f1aba10L,0xac06608dL,0xf8f6d757L,0xe19f7841L,
                 0x35e86c3bL,0x53c722c2L,0xbdcc3610L,0xcb330abeL,0x2940d081L,
                 0x1bffb100L,0x9ae64e62L,0x0c0c2aadL,0x94e75192L,0xc1c4f781L,
                 0x18d68f88L,0x3386cf9bL,0xb9d01255L,0x06b388edL,0x172c394dL,
                 0xbb5e89a2L,0xae320a7dL,0x4bfe0e0aL,0x7efc67d0L,0x6585bc9fL,
                 0x3064fb77L,0x867a4ddeL,0xd63cbdf1L,0x3e743e6bL,0x95e4fe3bL,
                 0x0fe24320L,0xf8f848d5L,0xf4ddaaeeL,0x5a608676L,0x2b8c296bL,
                 0x3a338785L,0x895a829aL,0x58ba0018L,0x8cfb0c5aL,0xe3c7358dL,
                 0x3600c466L,0xf9a5692fL,0x4f69aaaaL,0x6fec7daeL,0x302147f8L,
                 0xec9a553aL,0xc957aee1L,0xf0f8c6afL,0x60f5ce2aL,0x2eac9381L,
                 0xb3ac7671L,0x094f9646L,0x48ef15acL,0x46a8b572L,0x3e003615L,
                 0xe3bf9c33L,0xfe633ed4L,0x3cccc2afL,0x328ff759L,0xb0fefd6eL,
                 0xca4513d0L,0x64c17fcdL,0x9b89de12L,0x6cd9a87eL,0xbbafbc2dL
#endif
                 };

