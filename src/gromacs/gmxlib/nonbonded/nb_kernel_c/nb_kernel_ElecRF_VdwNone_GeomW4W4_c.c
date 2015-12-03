/*
 * This file is part of the GROMACS molecular simulation package.
 *
 * Copyright (c) 2012,2013,2014.2015, by the GROMACS development team, led by
 * Mark Abraham, David van der Spoel, Berk Hess, and Erik Lindahl,
 * and including many others, as listed in the AUTHORS file in the
 * top-level source directory and at http://www.gromacs.org.
 *
 * GROMACS is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * GROMACS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GROMACS; if not, see
 * http://www.gnu.org/licenses, or write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
 *
 * If you want to redistribute modifications to GROMACS, please
 * consider that scientific software is very special. Version
 * control is crucial - bugs must be traceable. We will be happy to
 * consider code for inclusion in the official distribution, but
 * derived work must not be called official GROMACS. Details are found
 * in the README & COPYING files - if they are missing, get the
 * official version at http://www.gromacs.org.
 *
 * To help us fund GROMACS development, we humbly ask that you cite
 * the research papers on the package. Check out http://www.gromacs.org.
 */
/*
 * Note: this file was generated by the GROMACS c kernel generator.
 */
#include "gmxpre.h"

#include "config.h"

#include <math.h>

#include "../nb_kernel.h"
#include "gromacs/math/vec.h"
#include "gromacs/gmxlib/nrnb.h"

/*
 * Gromacs nonbonded kernel:   nb_kernel_ElecRF_VdwNone_GeomW4W4_VF_c
 * Electrostatics interaction: ReactionField
 * VdW interaction:            None
 * Geometry:                   Water4-Water4
 * Calculate force/pot:        PotentialAndForce
 */
void
nb_kernel_ElecRF_VdwNone_GeomW4W4_VF_c
                    (t_nblist                    * gmx_restrict       nlist,
                     rvec                        * gmx_restrict          xx,
                     rvec                        * gmx_restrict          ff,
                     t_forcerec                  * gmx_restrict          fr,
                     t_mdatoms                   * gmx_restrict     mdatoms,
                     nb_kernel_data_t gmx_unused * gmx_restrict kernel_data,
                     t_nrnb                      * gmx_restrict        nrnb)
{
    int              i_shift_offset,i_coord_offset,j_coord_offset;
    int              j_index_start,j_index_end;
    int              nri,inr,ggid,iidx,jidx,jnr,outeriter,inneriter;
    real             shX,shY,shZ,tx,ty,tz,fscal,rcutoff,rcutoff2;
    int              *iinr,*jindex,*jjnr,*shiftidx,*gid;
    real             *shiftvec,*fshift,*x,*f;
    int              vdwioffset1;
    real             ix1,iy1,iz1,fix1,fiy1,fiz1,iq1,isai1;
    int              vdwioffset2;
    real             ix2,iy2,iz2,fix2,fiy2,fiz2,iq2,isai2;
    int              vdwioffset3;
    real             ix3,iy3,iz3,fix3,fiy3,fiz3,iq3,isai3;
    int              vdwjidx1;
    real             jx1,jy1,jz1,fjx1,fjy1,fjz1,jq1,isaj1;
    int              vdwjidx2;
    real             jx2,jy2,jz2,fjx2,fjy2,fjz2,jq2,isaj2;
    int              vdwjidx3;
    real             jx3,jy3,jz3,fjx3,fjy3,fjz3,jq3,isaj3;
    real             dx11,dy11,dz11,rsq11,rinv11,rinvsq11,r11,qq11,c6_11,c12_11,cexp1_11,cexp2_11;
    real             dx12,dy12,dz12,rsq12,rinv12,rinvsq12,r12,qq12,c6_12,c12_12,cexp1_12,cexp2_12;
    real             dx13,dy13,dz13,rsq13,rinv13,rinvsq13,r13,qq13,c6_13,c12_13,cexp1_13,cexp2_13;
    real             dx21,dy21,dz21,rsq21,rinv21,rinvsq21,r21,qq21,c6_21,c12_21,cexp1_21,cexp2_21;
    real             dx22,dy22,dz22,rsq22,rinv22,rinvsq22,r22,qq22,c6_22,c12_22,cexp1_22,cexp2_22;
    real             dx23,dy23,dz23,rsq23,rinv23,rinvsq23,r23,qq23,c6_23,c12_23,cexp1_23,cexp2_23;
    real             dx31,dy31,dz31,rsq31,rinv31,rinvsq31,r31,qq31,c6_31,c12_31,cexp1_31,cexp2_31;
    real             dx32,dy32,dz32,rsq32,rinv32,rinvsq32,r32,qq32,c6_32,c12_32,cexp1_32,cexp2_32;
    real             dx33,dy33,dz33,rsq33,rinv33,rinvsq33,r33,qq33,c6_33,c12_33,cexp1_33,cexp2_33;
    real             velec,felec,velecsum,facel,crf,krf,krf2;
    real             *charge;

    x                = xx[0];
    f                = ff[0];

    nri              = nlist->nri;
    iinr             = nlist->iinr;
    jindex           = nlist->jindex;
    jjnr             = nlist->jjnr;
    shiftidx         = nlist->shift;
    gid              = nlist->gid;
    shiftvec         = fr->shift_vec[0];
    fshift           = fr->fshift[0];
    facel            = fr->epsfac;
    charge           = mdatoms->chargeA;
    krf              = fr->ic->k_rf;
    krf2             = krf*2.0;
    crf              = fr->ic->c_rf;

    /* Setup water-specific parameters */
    inr              = nlist->iinr[0];
    iq1              = facel*charge[inr+1];
    iq2              = facel*charge[inr+2];
    iq3              = facel*charge[inr+3];

    jq1              = charge[inr+1];
    jq2              = charge[inr+2];
    jq3              = charge[inr+3];
    qq11             = iq1*jq1;
    qq12             = iq1*jq2;
    qq13             = iq1*jq3;
    qq21             = iq2*jq1;
    qq22             = iq2*jq2;
    qq23             = iq2*jq3;
    qq31             = iq3*jq1;
    qq32             = iq3*jq2;
    qq33             = iq3*jq3;

    outeriter        = 0;
    inneriter        = 0;

    /* Start outer loop over neighborlists */
    for(iidx=0; iidx<nri; iidx++)
    {
        /* Load shift vector for this list */
        i_shift_offset   = DIM*shiftidx[iidx];
        shX              = shiftvec[i_shift_offset+XX];
        shY              = shiftvec[i_shift_offset+YY];
        shZ              = shiftvec[i_shift_offset+ZZ];

        /* Load limits for loop over neighbors */
        j_index_start    = jindex[iidx];
        j_index_end      = jindex[iidx+1];

        /* Get outer coordinate index */
        inr              = iinr[iidx];
        i_coord_offset   = DIM*inr;

        /* Load i particle coords and add shift vector */
        ix1              = shX + x[i_coord_offset+DIM*1+XX];
        iy1              = shY + x[i_coord_offset+DIM*1+YY];
        iz1              = shZ + x[i_coord_offset+DIM*1+ZZ];
        ix2              = shX + x[i_coord_offset+DIM*2+XX];
        iy2              = shY + x[i_coord_offset+DIM*2+YY];
        iz2              = shZ + x[i_coord_offset+DIM*2+ZZ];
        ix3              = shX + x[i_coord_offset+DIM*3+XX];
        iy3              = shY + x[i_coord_offset+DIM*3+YY];
        iz3              = shZ + x[i_coord_offset+DIM*3+ZZ];

        fix1             = 0.0;
        fiy1             = 0.0;
        fiz1             = 0.0;
        fix2             = 0.0;
        fiy2             = 0.0;
        fiz2             = 0.0;
        fix3             = 0.0;
        fiy3             = 0.0;
        fiz3             = 0.0;

        /* Reset potential sums */
        velecsum         = 0.0;

        /* Start inner kernel loop */
        for(jidx=j_index_start; jidx<j_index_end; jidx++)
        {
            /* Get j neighbor index, and coordinate index */
            jnr              = jjnr[jidx];
            j_coord_offset   = DIM*jnr;

            /* load j atom coordinates */
            jx1              = x[j_coord_offset+DIM*1+XX];
            jy1              = x[j_coord_offset+DIM*1+YY];
            jz1              = x[j_coord_offset+DIM*1+ZZ];
            jx2              = x[j_coord_offset+DIM*2+XX];
            jy2              = x[j_coord_offset+DIM*2+YY];
            jz2              = x[j_coord_offset+DIM*2+ZZ];
            jx3              = x[j_coord_offset+DIM*3+XX];
            jy3              = x[j_coord_offset+DIM*3+YY];
            jz3              = x[j_coord_offset+DIM*3+ZZ];

            /* Calculate displacement vector */
            dx11             = ix1 - jx1;
            dy11             = iy1 - jy1;
            dz11             = iz1 - jz1;
            dx12             = ix1 - jx2;
            dy12             = iy1 - jy2;
            dz12             = iz1 - jz2;
            dx13             = ix1 - jx3;
            dy13             = iy1 - jy3;
            dz13             = iz1 - jz3;
            dx21             = ix2 - jx1;
            dy21             = iy2 - jy1;
            dz21             = iz2 - jz1;
            dx22             = ix2 - jx2;
            dy22             = iy2 - jy2;
            dz22             = iz2 - jz2;
            dx23             = ix2 - jx3;
            dy23             = iy2 - jy3;
            dz23             = iz2 - jz3;
            dx31             = ix3 - jx1;
            dy31             = iy3 - jy1;
            dz31             = iz3 - jz1;
            dx32             = ix3 - jx2;
            dy32             = iy3 - jy2;
            dz32             = iz3 - jz2;
            dx33             = ix3 - jx3;
            dy33             = iy3 - jy3;
            dz33             = iz3 - jz3;

            /* Calculate squared distance and things based on it */
            rsq11            = dx11*dx11+dy11*dy11+dz11*dz11;
            rsq12            = dx12*dx12+dy12*dy12+dz12*dz12;
            rsq13            = dx13*dx13+dy13*dy13+dz13*dz13;
            rsq21            = dx21*dx21+dy21*dy21+dz21*dz21;
            rsq22            = dx22*dx22+dy22*dy22+dz22*dz22;
            rsq23            = dx23*dx23+dy23*dy23+dz23*dz23;
            rsq31            = dx31*dx31+dy31*dy31+dz31*dz31;
            rsq32            = dx32*dx32+dy32*dy32+dz32*dz32;
            rsq33            = dx33*dx33+dy33*dy33+dz33*dz33;

            rinv11           = gmx_invsqrt(rsq11);
            rinv12           = gmx_invsqrt(rsq12);
            rinv13           = gmx_invsqrt(rsq13);
            rinv21           = gmx_invsqrt(rsq21);
            rinv22           = gmx_invsqrt(rsq22);
            rinv23           = gmx_invsqrt(rsq23);
            rinv31           = gmx_invsqrt(rsq31);
            rinv32           = gmx_invsqrt(rsq32);
            rinv33           = gmx_invsqrt(rsq33);

            rinvsq11         = rinv11*rinv11;
            rinvsq12         = rinv12*rinv12;
            rinvsq13         = rinv13*rinv13;
            rinvsq21         = rinv21*rinv21;
            rinvsq22         = rinv22*rinv22;
            rinvsq23         = rinv23*rinv23;
            rinvsq31         = rinv31*rinv31;
            rinvsq32         = rinv32*rinv32;
            rinvsq33         = rinv33*rinv33;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            velec            = qq11*(rinv11+krf*rsq11-crf);
            felec            = qq11*(rinv11*rinvsq11-krf2);

            /* Update potential sums from outer loop */
            velecsum        += velec;

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx11;
            ty               = fscal*dy11;
            tz               = fscal*dz11;

            /* Update vectorial force */
            fix1            += tx;
            fiy1            += ty;
            fiz1            += tz;
            f[j_coord_offset+DIM*1+XX] -= tx;
            f[j_coord_offset+DIM*1+YY] -= ty;
            f[j_coord_offset+DIM*1+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            velec            = qq12*(rinv12+krf*rsq12-crf);
            felec            = qq12*(rinv12*rinvsq12-krf2);

            /* Update potential sums from outer loop */
            velecsum        += velec;

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx12;
            ty               = fscal*dy12;
            tz               = fscal*dz12;

            /* Update vectorial force */
            fix1            += tx;
            fiy1            += ty;
            fiz1            += tz;
            f[j_coord_offset+DIM*2+XX] -= tx;
            f[j_coord_offset+DIM*2+YY] -= ty;
            f[j_coord_offset+DIM*2+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            velec            = qq13*(rinv13+krf*rsq13-crf);
            felec            = qq13*(rinv13*rinvsq13-krf2);

            /* Update potential sums from outer loop */
            velecsum        += velec;

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx13;
            ty               = fscal*dy13;
            tz               = fscal*dz13;

            /* Update vectorial force */
            fix1            += tx;
            fiy1            += ty;
            fiz1            += tz;
            f[j_coord_offset+DIM*3+XX] -= tx;
            f[j_coord_offset+DIM*3+YY] -= ty;
            f[j_coord_offset+DIM*3+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            velec            = qq21*(rinv21+krf*rsq21-crf);
            felec            = qq21*(rinv21*rinvsq21-krf2);

            /* Update potential sums from outer loop */
            velecsum        += velec;

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx21;
            ty               = fscal*dy21;
            tz               = fscal*dz21;

            /* Update vectorial force */
            fix2            += tx;
            fiy2            += ty;
            fiz2            += tz;
            f[j_coord_offset+DIM*1+XX] -= tx;
            f[j_coord_offset+DIM*1+YY] -= ty;
            f[j_coord_offset+DIM*1+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            velec            = qq22*(rinv22+krf*rsq22-crf);
            felec            = qq22*(rinv22*rinvsq22-krf2);

            /* Update potential sums from outer loop */
            velecsum        += velec;

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx22;
            ty               = fscal*dy22;
            tz               = fscal*dz22;

            /* Update vectorial force */
            fix2            += tx;
            fiy2            += ty;
            fiz2            += tz;
            f[j_coord_offset+DIM*2+XX] -= tx;
            f[j_coord_offset+DIM*2+YY] -= ty;
            f[j_coord_offset+DIM*2+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            velec            = qq23*(rinv23+krf*rsq23-crf);
            felec            = qq23*(rinv23*rinvsq23-krf2);

            /* Update potential sums from outer loop */
            velecsum        += velec;

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx23;
            ty               = fscal*dy23;
            tz               = fscal*dz23;

            /* Update vectorial force */
            fix2            += tx;
            fiy2            += ty;
            fiz2            += tz;
            f[j_coord_offset+DIM*3+XX] -= tx;
            f[j_coord_offset+DIM*3+YY] -= ty;
            f[j_coord_offset+DIM*3+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            velec            = qq31*(rinv31+krf*rsq31-crf);
            felec            = qq31*(rinv31*rinvsq31-krf2);

            /* Update potential sums from outer loop */
            velecsum        += velec;

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx31;
            ty               = fscal*dy31;
            tz               = fscal*dz31;

            /* Update vectorial force */
            fix3            += tx;
            fiy3            += ty;
            fiz3            += tz;
            f[j_coord_offset+DIM*1+XX] -= tx;
            f[j_coord_offset+DIM*1+YY] -= ty;
            f[j_coord_offset+DIM*1+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            velec            = qq32*(rinv32+krf*rsq32-crf);
            felec            = qq32*(rinv32*rinvsq32-krf2);

            /* Update potential sums from outer loop */
            velecsum        += velec;

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx32;
            ty               = fscal*dy32;
            tz               = fscal*dz32;

            /* Update vectorial force */
            fix3            += tx;
            fiy3            += ty;
            fiz3            += tz;
            f[j_coord_offset+DIM*2+XX] -= tx;
            f[j_coord_offset+DIM*2+YY] -= ty;
            f[j_coord_offset+DIM*2+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            velec            = qq33*(rinv33+krf*rsq33-crf);
            felec            = qq33*(rinv33*rinvsq33-krf2);

            /* Update potential sums from outer loop */
            velecsum        += velec;

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx33;
            ty               = fscal*dy33;
            tz               = fscal*dz33;

            /* Update vectorial force */
            fix3            += tx;
            fiy3            += ty;
            fiz3            += tz;
            f[j_coord_offset+DIM*3+XX] -= tx;
            f[j_coord_offset+DIM*3+YY] -= ty;
            f[j_coord_offset+DIM*3+ZZ] -= tz;

            /* Inner loop uses 279 flops */
        }
        /* End of innermost loop */

        tx = ty = tz = 0;
        f[i_coord_offset+DIM*1+XX] += fix1;
        f[i_coord_offset+DIM*1+YY] += fiy1;
        f[i_coord_offset+DIM*1+ZZ] += fiz1;
        tx                         += fix1;
        ty                         += fiy1;
        tz                         += fiz1;
        f[i_coord_offset+DIM*2+XX] += fix2;
        f[i_coord_offset+DIM*2+YY] += fiy2;
        f[i_coord_offset+DIM*2+ZZ] += fiz2;
        tx                         += fix2;
        ty                         += fiy2;
        tz                         += fiz2;
        f[i_coord_offset+DIM*3+XX] += fix3;
        f[i_coord_offset+DIM*3+YY] += fiy3;
        f[i_coord_offset+DIM*3+ZZ] += fiz3;
        tx                         += fix3;
        ty                         += fiy3;
        tz                         += fiz3;
        fshift[i_shift_offset+XX]  += tx;
        fshift[i_shift_offset+YY]  += ty;
        fshift[i_shift_offset+ZZ]  += tz;

        ggid                        = gid[iidx];
        /* Update potential energies */
        kernel_data->energygrp_elec[ggid] += velecsum;

        /* Increment number of inner iterations */
        inneriter                  += j_index_end - j_index_start;

        /* Outer loop uses 31 flops */
    }

    /* Increment number of outer iterations */
    outeriter        += nri;

    /* Update outer/inner flops */

    inc_nrnb(nrnb,eNR_NBKERNEL_ELEC_W4W4_VF,outeriter*31 + inneriter*279);
}
/*
 * Gromacs nonbonded kernel:   nb_kernel_ElecRF_VdwNone_GeomW4W4_F_c
 * Electrostatics interaction: ReactionField
 * VdW interaction:            None
 * Geometry:                   Water4-Water4
 * Calculate force/pot:        Force
 */
void
nb_kernel_ElecRF_VdwNone_GeomW4W4_F_c
                    (t_nblist                    * gmx_restrict       nlist,
                     rvec                        * gmx_restrict          xx,
                     rvec                        * gmx_restrict          ff,
                     t_forcerec                  * gmx_restrict          fr,
                     t_mdatoms                   * gmx_restrict     mdatoms,
                     nb_kernel_data_t gmx_unused * gmx_restrict kernel_data,
                     t_nrnb                      * gmx_restrict        nrnb)
{
    int              i_shift_offset,i_coord_offset,j_coord_offset;
    int              j_index_start,j_index_end;
    int              nri,inr,ggid,iidx,jidx,jnr,outeriter,inneriter;
    real             shX,shY,shZ,tx,ty,tz,fscal,rcutoff,rcutoff2;
    int              *iinr,*jindex,*jjnr,*shiftidx,*gid;
    real             *shiftvec,*fshift,*x,*f;
    int              vdwioffset1;
    real             ix1,iy1,iz1,fix1,fiy1,fiz1,iq1,isai1;
    int              vdwioffset2;
    real             ix2,iy2,iz2,fix2,fiy2,fiz2,iq2,isai2;
    int              vdwioffset3;
    real             ix3,iy3,iz3,fix3,fiy3,fiz3,iq3,isai3;
    int              vdwjidx1;
    real             jx1,jy1,jz1,fjx1,fjy1,fjz1,jq1,isaj1;
    int              vdwjidx2;
    real             jx2,jy2,jz2,fjx2,fjy2,fjz2,jq2,isaj2;
    int              vdwjidx3;
    real             jx3,jy3,jz3,fjx3,fjy3,fjz3,jq3,isaj3;
    real             dx11,dy11,dz11,rsq11,rinv11,rinvsq11,r11,qq11,c6_11,c12_11,cexp1_11,cexp2_11;
    real             dx12,dy12,dz12,rsq12,rinv12,rinvsq12,r12,qq12,c6_12,c12_12,cexp1_12,cexp2_12;
    real             dx13,dy13,dz13,rsq13,rinv13,rinvsq13,r13,qq13,c6_13,c12_13,cexp1_13,cexp2_13;
    real             dx21,dy21,dz21,rsq21,rinv21,rinvsq21,r21,qq21,c6_21,c12_21,cexp1_21,cexp2_21;
    real             dx22,dy22,dz22,rsq22,rinv22,rinvsq22,r22,qq22,c6_22,c12_22,cexp1_22,cexp2_22;
    real             dx23,dy23,dz23,rsq23,rinv23,rinvsq23,r23,qq23,c6_23,c12_23,cexp1_23,cexp2_23;
    real             dx31,dy31,dz31,rsq31,rinv31,rinvsq31,r31,qq31,c6_31,c12_31,cexp1_31,cexp2_31;
    real             dx32,dy32,dz32,rsq32,rinv32,rinvsq32,r32,qq32,c6_32,c12_32,cexp1_32,cexp2_32;
    real             dx33,dy33,dz33,rsq33,rinv33,rinvsq33,r33,qq33,c6_33,c12_33,cexp1_33,cexp2_33;
    real             velec,felec,velecsum,facel,crf,krf,krf2;
    real             *charge;

    x                = xx[0];
    f                = ff[0];

    nri              = nlist->nri;
    iinr             = nlist->iinr;
    jindex           = nlist->jindex;
    jjnr             = nlist->jjnr;
    shiftidx         = nlist->shift;
    gid              = nlist->gid;
    shiftvec         = fr->shift_vec[0];
    fshift           = fr->fshift[0];
    facel            = fr->epsfac;
    charge           = mdatoms->chargeA;
    krf              = fr->ic->k_rf;
    krf2             = krf*2.0;
    crf              = fr->ic->c_rf;

    /* Setup water-specific parameters */
    inr              = nlist->iinr[0];
    iq1              = facel*charge[inr+1];
    iq2              = facel*charge[inr+2];
    iq3              = facel*charge[inr+3];

    jq1              = charge[inr+1];
    jq2              = charge[inr+2];
    jq3              = charge[inr+3];
    qq11             = iq1*jq1;
    qq12             = iq1*jq2;
    qq13             = iq1*jq3;
    qq21             = iq2*jq1;
    qq22             = iq2*jq2;
    qq23             = iq2*jq3;
    qq31             = iq3*jq1;
    qq32             = iq3*jq2;
    qq33             = iq3*jq3;

    outeriter        = 0;
    inneriter        = 0;

    /* Start outer loop over neighborlists */
    for(iidx=0; iidx<nri; iidx++)
    {
        /* Load shift vector for this list */
        i_shift_offset   = DIM*shiftidx[iidx];
        shX              = shiftvec[i_shift_offset+XX];
        shY              = shiftvec[i_shift_offset+YY];
        shZ              = shiftvec[i_shift_offset+ZZ];

        /* Load limits for loop over neighbors */
        j_index_start    = jindex[iidx];
        j_index_end      = jindex[iidx+1];

        /* Get outer coordinate index */
        inr              = iinr[iidx];
        i_coord_offset   = DIM*inr;

        /* Load i particle coords and add shift vector */
        ix1              = shX + x[i_coord_offset+DIM*1+XX];
        iy1              = shY + x[i_coord_offset+DIM*1+YY];
        iz1              = shZ + x[i_coord_offset+DIM*1+ZZ];
        ix2              = shX + x[i_coord_offset+DIM*2+XX];
        iy2              = shY + x[i_coord_offset+DIM*2+YY];
        iz2              = shZ + x[i_coord_offset+DIM*2+ZZ];
        ix3              = shX + x[i_coord_offset+DIM*3+XX];
        iy3              = shY + x[i_coord_offset+DIM*3+YY];
        iz3              = shZ + x[i_coord_offset+DIM*3+ZZ];

        fix1             = 0.0;
        fiy1             = 0.0;
        fiz1             = 0.0;
        fix2             = 0.0;
        fiy2             = 0.0;
        fiz2             = 0.0;
        fix3             = 0.0;
        fiy3             = 0.0;
        fiz3             = 0.0;

        /* Start inner kernel loop */
        for(jidx=j_index_start; jidx<j_index_end; jidx++)
        {
            /* Get j neighbor index, and coordinate index */
            jnr              = jjnr[jidx];
            j_coord_offset   = DIM*jnr;

            /* load j atom coordinates */
            jx1              = x[j_coord_offset+DIM*1+XX];
            jy1              = x[j_coord_offset+DIM*1+YY];
            jz1              = x[j_coord_offset+DIM*1+ZZ];
            jx2              = x[j_coord_offset+DIM*2+XX];
            jy2              = x[j_coord_offset+DIM*2+YY];
            jz2              = x[j_coord_offset+DIM*2+ZZ];
            jx3              = x[j_coord_offset+DIM*3+XX];
            jy3              = x[j_coord_offset+DIM*3+YY];
            jz3              = x[j_coord_offset+DIM*3+ZZ];

            /* Calculate displacement vector */
            dx11             = ix1 - jx1;
            dy11             = iy1 - jy1;
            dz11             = iz1 - jz1;
            dx12             = ix1 - jx2;
            dy12             = iy1 - jy2;
            dz12             = iz1 - jz2;
            dx13             = ix1 - jx3;
            dy13             = iy1 - jy3;
            dz13             = iz1 - jz3;
            dx21             = ix2 - jx1;
            dy21             = iy2 - jy1;
            dz21             = iz2 - jz1;
            dx22             = ix2 - jx2;
            dy22             = iy2 - jy2;
            dz22             = iz2 - jz2;
            dx23             = ix2 - jx3;
            dy23             = iy2 - jy3;
            dz23             = iz2 - jz3;
            dx31             = ix3 - jx1;
            dy31             = iy3 - jy1;
            dz31             = iz3 - jz1;
            dx32             = ix3 - jx2;
            dy32             = iy3 - jy2;
            dz32             = iz3 - jz2;
            dx33             = ix3 - jx3;
            dy33             = iy3 - jy3;
            dz33             = iz3 - jz3;

            /* Calculate squared distance and things based on it */
            rsq11            = dx11*dx11+dy11*dy11+dz11*dz11;
            rsq12            = dx12*dx12+dy12*dy12+dz12*dz12;
            rsq13            = dx13*dx13+dy13*dy13+dz13*dz13;
            rsq21            = dx21*dx21+dy21*dy21+dz21*dz21;
            rsq22            = dx22*dx22+dy22*dy22+dz22*dz22;
            rsq23            = dx23*dx23+dy23*dy23+dz23*dz23;
            rsq31            = dx31*dx31+dy31*dy31+dz31*dz31;
            rsq32            = dx32*dx32+dy32*dy32+dz32*dz32;
            rsq33            = dx33*dx33+dy33*dy33+dz33*dz33;

            rinv11           = gmx_invsqrt(rsq11);
            rinv12           = gmx_invsqrt(rsq12);
            rinv13           = gmx_invsqrt(rsq13);
            rinv21           = gmx_invsqrt(rsq21);
            rinv22           = gmx_invsqrt(rsq22);
            rinv23           = gmx_invsqrt(rsq23);
            rinv31           = gmx_invsqrt(rsq31);
            rinv32           = gmx_invsqrt(rsq32);
            rinv33           = gmx_invsqrt(rsq33);

            rinvsq11         = rinv11*rinv11;
            rinvsq12         = rinv12*rinv12;
            rinvsq13         = rinv13*rinv13;
            rinvsq21         = rinv21*rinv21;
            rinvsq22         = rinv22*rinv22;
            rinvsq23         = rinv23*rinv23;
            rinvsq31         = rinv31*rinv31;
            rinvsq32         = rinv32*rinv32;
            rinvsq33         = rinv33*rinv33;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            felec            = qq11*(rinv11*rinvsq11-krf2);

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx11;
            ty               = fscal*dy11;
            tz               = fscal*dz11;

            /* Update vectorial force */
            fix1            += tx;
            fiy1            += ty;
            fiz1            += tz;
            f[j_coord_offset+DIM*1+XX] -= tx;
            f[j_coord_offset+DIM*1+YY] -= ty;
            f[j_coord_offset+DIM*1+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            felec            = qq12*(rinv12*rinvsq12-krf2);

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx12;
            ty               = fscal*dy12;
            tz               = fscal*dz12;

            /* Update vectorial force */
            fix1            += tx;
            fiy1            += ty;
            fiz1            += tz;
            f[j_coord_offset+DIM*2+XX] -= tx;
            f[j_coord_offset+DIM*2+YY] -= ty;
            f[j_coord_offset+DIM*2+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            felec            = qq13*(rinv13*rinvsq13-krf2);

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx13;
            ty               = fscal*dy13;
            tz               = fscal*dz13;

            /* Update vectorial force */
            fix1            += tx;
            fiy1            += ty;
            fiz1            += tz;
            f[j_coord_offset+DIM*3+XX] -= tx;
            f[j_coord_offset+DIM*3+YY] -= ty;
            f[j_coord_offset+DIM*3+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            felec            = qq21*(rinv21*rinvsq21-krf2);

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx21;
            ty               = fscal*dy21;
            tz               = fscal*dz21;

            /* Update vectorial force */
            fix2            += tx;
            fiy2            += ty;
            fiz2            += tz;
            f[j_coord_offset+DIM*1+XX] -= tx;
            f[j_coord_offset+DIM*1+YY] -= ty;
            f[j_coord_offset+DIM*1+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            felec            = qq22*(rinv22*rinvsq22-krf2);

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx22;
            ty               = fscal*dy22;
            tz               = fscal*dz22;

            /* Update vectorial force */
            fix2            += tx;
            fiy2            += ty;
            fiz2            += tz;
            f[j_coord_offset+DIM*2+XX] -= tx;
            f[j_coord_offset+DIM*2+YY] -= ty;
            f[j_coord_offset+DIM*2+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            felec            = qq23*(rinv23*rinvsq23-krf2);

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx23;
            ty               = fscal*dy23;
            tz               = fscal*dz23;

            /* Update vectorial force */
            fix2            += tx;
            fiy2            += ty;
            fiz2            += tz;
            f[j_coord_offset+DIM*3+XX] -= tx;
            f[j_coord_offset+DIM*3+YY] -= ty;
            f[j_coord_offset+DIM*3+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            felec            = qq31*(rinv31*rinvsq31-krf2);

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx31;
            ty               = fscal*dy31;
            tz               = fscal*dz31;

            /* Update vectorial force */
            fix3            += tx;
            fiy3            += ty;
            fiz3            += tz;
            f[j_coord_offset+DIM*1+XX] -= tx;
            f[j_coord_offset+DIM*1+YY] -= ty;
            f[j_coord_offset+DIM*1+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            felec            = qq32*(rinv32*rinvsq32-krf2);

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx32;
            ty               = fscal*dy32;
            tz               = fscal*dz32;

            /* Update vectorial force */
            fix3            += tx;
            fiy3            += ty;
            fiz3            += tz;
            f[j_coord_offset+DIM*2+XX] -= tx;
            f[j_coord_offset+DIM*2+YY] -= ty;
            f[j_coord_offset+DIM*2+ZZ] -= tz;

            /**************************
             * CALCULATE INTERACTIONS *
             **************************/

            /* REACTION-FIELD ELECTROSTATICS */
            felec            = qq33*(rinv33*rinvsq33-krf2);

            fscal            = felec;

            /* Calculate temporary vectorial force */
            tx               = fscal*dx33;
            ty               = fscal*dy33;
            tz               = fscal*dz33;

            /* Update vectorial force */
            fix3            += tx;
            fiy3            += ty;
            fiz3            += tz;
            f[j_coord_offset+DIM*3+XX] -= tx;
            f[j_coord_offset+DIM*3+YY] -= ty;
            f[j_coord_offset+DIM*3+ZZ] -= tz;

            /* Inner loop uses 234 flops */
        }
        /* End of innermost loop */

        tx = ty = tz = 0;
        f[i_coord_offset+DIM*1+XX] += fix1;
        f[i_coord_offset+DIM*1+YY] += fiy1;
        f[i_coord_offset+DIM*1+ZZ] += fiz1;
        tx                         += fix1;
        ty                         += fiy1;
        tz                         += fiz1;
        f[i_coord_offset+DIM*2+XX] += fix2;
        f[i_coord_offset+DIM*2+YY] += fiy2;
        f[i_coord_offset+DIM*2+ZZ] += fiz2;
        tx                         += fix2;
        ty                         += fiy2;
        tz                         += fiz2;
        f[i_coord_offset+DIM*3+XX] += fix3;
        f[i_coord_offset+DIM*3+YY] += fiy3;
        f[i_coord_offset+DIM*3+ZZ] += fiz3;
        tx                         += fix3;
        ty                         += fiy3;
        tz                         += fiz3;
        fshift[i_shift_offset+XX]  += tx;
        fshift[i_shift_offset+YY]  += ty;
        fshift[i_shift_offset+ZZ]  += tz;

        /* Increment number of inner iterations */
        inneriter                  += j_index_end - j_index_start;

        /* Outer loop uses 30 flops */
    }

    /* Increment number of outer iterations */
    outeriter        += nri;

    /* Update outer/inner flops */

    inc_nrnb(nrnb,eNR_NBKERNEL_ELEC_W4W4_F,outeriter*30 + inneriter*234);
}
