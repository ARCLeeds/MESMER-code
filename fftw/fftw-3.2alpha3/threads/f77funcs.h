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

/* Functions in the FFTW Fortran API, mangled according to the
   F77(...) macro.  This file is designed to be #included by
   f77api.c, possibly multiple times in order to support multiple
   compiler manglings (via redefinition of F77). */

FFTW_VOIDFUNC F77(plan_with_nthreads, PLAN_WITH_NTHREADS)(int *nthreads)
{
     X(plan_with_nthreads)(*nthreads);
}

FFTW_VOIDFUNC F77(init_threads, INIT_THREADS)(int *okay)
{
     *okay = X(init_threads)();
}

FFTW_VOIDFUNC F77(cleanup_threads, CLEANUP_THREADS)(void)
{
     X(cleanup_threads)();
}
