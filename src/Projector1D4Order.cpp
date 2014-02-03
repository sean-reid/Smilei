#include "Projector1D4Order.h"
#include "ElectroMagn.h"
#include "Field1D.h"
#include "Particle.h"
#include "Tools.h"
#include "SmileiMPI_Cart1D.h"

#include <iostream>
#include <cmath>

using namespace std;


// ---------------------------------------------------------------------------------------------------------------------
// Constructor for Projector1D4Order
// ---------------------------------------------------------------------------------------------------------------------
Projector1D4Order::Projector1D4Order (PicParams* params, SmileiMPI* smpi) : Projector1D(params, smpi)
{
	SmileiMPI_Cart1D* smpi1D = static_cast<SmileiMPI_Cart1D*>(smpi);

	dx_inv_  = 1.0/params->cell_length[0];
	dx_ov_dt = params->cell_length[0] / params->timestep;
    
    //double defined for use in coefficients
    dble_1_ov_384 = 1.0/384.0;
    dble_1_ov_48 = 1.0/48.0;
    dble_1_ov_16 = 1.0/16.0;
    dble_1_ov_12 = 1.0/12.0;
    dble_1_ov_24 = 1.0/24.0;
    dble_19_ov_96 = 19.0/96.0;
    dble_11_ov_24 = 11.0/24.0;
    dble_1_ov_4 = 1.0/4.0;
    dble_1_ov_6 = 1.0/6.0;
    dble_115_ov_192 = 115.0/192.0;
    dble_5_ov_8 = 5.0/8.0;

	index_domain_begin = smpi1D->getCellStartingGlobalIndex(0); 

	DEBUG("cell_length "<< params->cell_length[0]);

}

Projector1D4Order::~Projector1D4Order()
{
}

// ---------------------------------------------------------------------------------------------------------------------
// 2nd order projection in 1d3v simulations
// ---------------------------------------------------------------------------------------------------------------------
void Projector1D4Order::operator() (double* Jx, double* Jy, double* Jz, Particle* part, double gf, unsigned int bin, unsigned int b_dim0)
{
/*
	// Declare local variables
    unsigned int ipo, ip, iloc;
    int ip_m_ipo;
    double charge_weight = (double)(part->charge())*part->weight();
    double xjn, xj_m_xipo, xj_m_xipo2, xj_m_xip, xj_m_xip2;
    double crx_p = charge_weight*dx_ov_dt;                // current density for particle moving in the x-direction
    double cry_p = charge_weight*part->momentum(1)/gf;    // current density in the y-direction of the macroparticle
    double crz_p = charge_weight*part->momentum(2)/gf;    // current density allow the y-direction of the macroparticle
    //double rho_p = part->weight();                         // charge density for the macroparticle
    double S0[5], S1[5], Wl[5], Wt[5], Jx_p[5];            // arrays used for the Esirkepov projection method
    
    // Initialize variables
    for (unsigned int i=0; i<5; i++){
        S0[i]=0.; S1[i]=0.; Wl[i]=0.; Wt[i]=0.; Jx_p[i]=0.;
    }//i

    
	// Locate particle old position on the primal grid
	xjn        = part->position_old(0) * dx_inv_;
	ipo        = round(xjn);                          // index of the central node
	xj_m_xipo  = xjn - (double)ipo;                   // normalized distance to the nearest grid point
	xj_m_xipo2 = xj_m_xipo*xj_m_xipo;                 // square of the normalized distance to the nearest grid point
	//cout << "old coords = " << part->position_old(0);

	// Locate particle new position on the primal grid
	xjn       = part->position(0) * dx_inv_;
	ip        = round(xjn);                           // index of the central node
	xj_m_xip  = xjn - (double)ip;                     // normalized distance to the nearest grid point
	xj_m_xip2 = xj_m_xip*xj_m_xip;                    // square of the normalized distance to the nearest grid point

    
	// coefficients 2nd order interpolation on 3 nodes
	S0[1] = 0.5 * (xj_m_xipo2-xj_m_xipo+0.25);
	S0[2] = (0.75-xj_m_xipo2);
	S0[3] = 0.5 * (xj_m_xipo2+xj_m_xipo+0.25);
 
	// coefficients 2nd order interpolation on 3 nodes
	ip_m_ipo = ip-ipo;
	S1[ip_m_ipo+1] = 0.5 * (xj_m_xip2-xj_m_xip+0.25);
	S1[ip_m_ipo+2] = (0.75-xj_m_xip2);
	S1[ip_m_ipo+3] = 0.5 * (xj_m_xip2+xj_m_xip+0.25);
    
    // coefficients used in the Esirkepov method
    for (unsigned int i=0; i<5; i++){
        Wl[i] = S0[i] - S1[i];           // for longitudinal current (x)
        Wt[i] = 0.5 * (S0[i] + S1[i]);   // for transverse currents (y,z)
    }//i
    
    // local current created by the particle
    // calculate using the charge conservation equation
    for (unsigned int i=1; i<5; i++){
        Jx_p[i] = Jx_p[i-1] + crx_p * Wl[i-1];
    }

	ipo -= index_domain_begin + bin ;
	//cout << "\tcoords = " << part->position(0) << "\tglobal index = " << ip;
	//ip  -= index_domain_begin;
	//cout << "\tlocal index = " << ip << endl;

	// 2nd order projection for the total currents & charge density
	// At the 2nd order, oversize = 2.
	for (unsigned int i=0; i<5; i++) {
		iloc = i + ipo - 2;
		Jx[iloc] += Jx_p[i];
		Jy[iloc] += cry_p * Wt[i];
		Jz[iloc] += crz_p * Wt[i];
        //(*rho)(iloc)  += rho_p * S1[i];
	}//i
*/
    
}//END Projector1D4Order

// ---------------------------------------------------------------------------------------------------------------------
// 2nd order projection in 1d3v simulations
// ---------------------------------------------------------------------------------------------------------------------
void Projector1D4Order::operator() (ElectroMagn* EMfields, Particle* part, double gf)
{
/*
	Field1D* Jx1D  = static_cast<Field1D*>(EMfields->Jx_);
	Field1D* Jy1D  = static_cast<Field1D*>(EMfields->Jy_);
	Field1D* Jz1D  = static_cast<Field1D*>(EMfields->Jz_);

	// Declare local variables
    int unsigned ipo, ip, iloc;
    int ip_m_ipo;
    double charge_weight = (double)(part->charge())*part->weight();
    double xjn, xj_m_xipo, xj_m_xipo2, xj_m_xip, xj_m_xip2;
    double crx_p = charge_weight*dx_ov_dt;                // current density for particle moving in the x-direction
    double cry_p = charge_weight*part->momentum(1)/gf;    // current density in the y-direction of the macroparticle
    double crz_p = charge_weight*part->momentum(2)/gf;    // current density allow the y-direction of the macroparticle
    //double rho_p = part->weight();                         // charge density for the macroparticle
    double S0[5], S1[5], Wl[5], Wt[5], Jx_p[5];            // arrays used for the Esirkepov projection method
    
    // Initialize variables
    for (unsigned int i=0; i<5; i++){
        S0[i]=0.; S1[i]=0.; Wl[i]=0.; Wt[i]=0.; Jx_p[i]=0.;
    }//i

    
	// Locate particle old position on the primal grid
	xjn        = part->position_old(0) * dx_inv_;
	ipo        = round(xjn);                          // index of the central node
	xj_m_xipo  = xjn - (double)ipo;                   // normalized distance to the nearest grid point
	xj_m_xipo2 = xj_m_xipo*xj_m_xipo;                 // square of the normalized distance to the nearest grid point
	//cout << "old coords = " << part->position_old(0);

	// Locate particle new position on the primal grid
	xjn       = part->position(0) * dx_inv_;
	ip        = round(xjn);                           // index of the central node
	xj_m_xip  = xjn - (double)ip;                     // normalized distance to the nearest grid point
	xj_m_xip2 = xj_m_xip*xj_m_xip;                    // square of the normalized distance to the nearest grid point

    
	// coefficients 2nd order interpolation on 3 nodes
	S0[1] = 0.5 * (xj_m_xipo2-xj_m_xipo+0.25);
	S0[2] = (0.75-xj_m_xipo2);
	S0[3] = 0.5 * (xj_m_xipo2+xj_m_xipo+0.25);
 
	// coefficients 2nd order interpolation on 3 nodes
	ip_m_ipo = ip-ipo;
	S1[ip_m_ipo+1] = 0.5 * (xj_m_xip2-xj_m_xip+0.25);
	S1[ip_m_ipo+2] = (0.75-xj_m_xip2);
	S1[ip_m_ipo+3] = 0.5 * (xj_m_xip2+xj_m_xip+0.25);
    
    // coefficients used in the Esirkepov method
    for (unsigned int i=0; i<5; i++){
        Wl[i] = S0[i] - S1[i];           // for longitudinal current (x)
        Wt[i] = 0.5 * (S0[i] + S1[i]);   // for transverse currents (y,z)
    }//i
    
    // local current created by the particle
    // calculate using the charge conservation equation
    for (unsigned int i=1; i<5; i++){
        Jx_p[i] = Jx_p[i-1] + crx_p * Wl[i-1];
    }

	ipo -= index_domain_begin;
	//cout << "\tcoords = " << part->position(0) << "\tglobal index = " << ip;
	ip  -= index_domain_begin;
	//cout << "\tlocal index = " << ip << endl;

	// 2nd order projection for the total currents & charge density
	for (unsigned int i=0; i<5; i++) {
		iloc = i+ipo-2;
		//#pragma omp atomic
		(*Jx1D)(iloc) += Jx_p[i];
		//#pragma omp atomic
		(*Jy1D)(iloc) += cry_p * Wt[i];
		//#pragma omp atomic
		(*Jz1D)(iloc) += crz_p * Wt[i];
        //(*rho)(iloc)  += rho_p * S1[i];
	}//i

*/
}//END Projector1D4Order

// ---------------------------------------------------------------------------------------------------------------------
// 4th order projection in 1d3v simulations
// ---------------------------------------------------------------------------------------------------------------------
void Projector1D4Order::operator() (Field* Jx, Field* Jy, Field* Jz, Field* rho, Particle* part, double gf)
{
	Field1D* Jx1D  = static_cast<Field1D*>(Jx);
	Field1D* Jy1D  = static_cast<Field1D*>(Jy);
	Field1D* Jz1D  = static_cast<Field1D*>(Jz);
    Field1D* rho1D = static_cast<Field1D*>(rho);
    
	// Declare local variables
    int unsigned ipo, ip, iloc;
    int ip_m_ipo;
    double charge_weight = (double)(part->charge())*part->weight();
    double xjn, xj_m_xipo, xj_m_xipo2, xj_m_xipo3, xj_m_xipo4, xj_m_xip, xj_m_xip2, xj_m_xip3, xj_m_xip4;
    double crx_p = charge_weight*dx_ov_dt;                // current density for particle moving in the x-direction
    double cry_p = charge_weight*part->momentum(1)/gf;    // current density in the y-direction of the macroparticle
    double crz_p = charge_weight*part->momentum(2)/gf;    // current density allow the y-direction of the macroparticle
    double S0[7], S1[7], Wl[7], Wt[7], Jx_p[7];           // arrays used for the Esirkepov projection method
    
    // Initialize variables
    for (unsigned int i=0; i<7; i++){
        S0[i]=0.; S1[i]=0.; Wl[i]=0.; Wt[i]=0.; Jx_p[i]=0.;
    }//i
    
    
	// Locate particle old position on the primal grid
	xjn        = part->position_old(0) * dx_inv_;
	ipo        = round(xjn);                          // index of the central node
	xj_m_xipo  = xjn - (double)ipo;                   // normalized distance to the nearest grid point
	xj_m_xipo2 = xj_m_xipo  * xj_m_xipo;              // square of the normalized distance to the nearest grid point
	xj_m_xipo3 = xj_m_xipo2 * xj_m_xipo;              // cube of the normalized distance to the nearest grid point
    xj_m_xipo4 = xj_m_xipo3 * xj_m_xipo;              // 4th power of the normalized distance to the nearest grid point
    
	// Locate particle new position on the primal grid
	xjn       = part->position(0) * dx_inv_;
	ip        = round(xjn);                           // index of the central node
	xj_m_xip  = xjn - (double)ip;                     // normalized distance to the nearest grid point
	xj_m_xip2 = xj_m_xip  * xj_m_xip;                 // square of the normalized distance to the nearest grid point
	xj_m_xip3 = xj_m_xip2 * xj_m_xip;                 // cube of the normalized distance to the nearest grid point
    xj_m_xip4 = xj_m_xip3 * xj_m_xip;                 // 4th power of the normalized distance to the nearest grid point
    
    
	// coefficients 4th order interpolation on 5 nodes
	   
    S0[1] = dble_1_ov_384   - dble_1_ov_48  * xj_m_xipo  + dble_1_ov_16 * xj_m_xipo2 - dble_1_ov_12 * xj_m_xipo3 + dble_1_ov_24 * xj_m_xipo4;
	S0[2] = dble_19_ov_96   - dble_11_ov_24 * xj_m_xipo  + dble_1_ov_4 * xj_m_xipo2  + dble_1_ov_6  * xj_m_xipo3 - dble_1_ov_6  * xj_m_xipo4;
	S0[3] = dble_115_ov_192 - dble_5_ov_8   * xj_m_xipo2 + dble_1_ov_4 * xj_m_xipo4;
    S0[4] = dble_19_ov_96   + dble_11_ov_24 * xj_m_xipo  + dble_1_ov_4 * xj_m_xipo2  - dble_1_ov_6  * xj_m_xipo3 - dble_1_ov_6  * xj_m_xipo4;
    S0[5] = dble_1_ov_384   + dble_1_ov_48  * xj_m_xipo  + dble_1_ov_16 * xj_m_xipo2 + dble_1_ov_12 * xj_m_xipo3 + dble_1_ov_24 * xj_m_xipo4;
    
	// coefficients 2nd order interpolation on 5 nodes
	ip_m_ipo = ip-ipo;
    
    S1[ip_m_ipo+1] = dble_1_ov_384   - dble_1_ov_48  * xj_m_xip  + dble_1_ov_16 * xj_m_xip2 - dble_1_ov_12 * xj_m_xip3 + dble_1_ov_24 * xj_m_xip4;
	S1[ip_m_ipo+2] = dble_19_ov_96   - dble_11_ov_24 * xj_m_xip  + dble_1_ov_4 * xj_m_xip2  + dble_1_ov_6  * xj_m_xip3 - dble_1_ov_6  * xj_m_xip4;
	S1[ip_m_ipo+3] = dble_115_ov_192 - dble_5_ov_8   * xj_m_xip2 + dble_1_ov_4 * xj_m_xip4;
    S1[ip_m_ipo+4] = dble_19_ov_96   + dble_11_ov_24 * xj_m_xip  + dble_1_ov_4 * xj_m_xip2  - dble_1_ov_6  * xj_m_xip3 - dble_1_ov_6  * xj_m_xip4;
    S1[ip_m_ipo+5] = dble_1_ov_384   + dble_1_ov_48  * xj_m_xip  + dble_1_ov_16 * xj_m_xip2 + dble_1_ov_12 * xj_m_xip3 + dble_1_ov_24 * xj_m_xip4;

    // coefficients used in the Esirkepov method
    for (unsigned int i=0; i<7; i++){
        Wl[i] = S0[i] - S1[i];           // for longitudinal current (x)
        Wt[i] = 0.5 * (S0[i] + S1[i]);   // for transverse currents (y,z)
    }//i
    
    // local current created by the particle
    // calculate using the charge conservation equation
    for (unsigned int i=1; i<7; i++){
        Jx_p[i] = Jx_p[i-1] + crx_p * Wl[i-1];
    }
    
	ipo -= index_domain_begin;
	//cout << "\tcoords = " << part->position(0) << "\tglobal index = " << ip;
	ip  -= index_domain_begin;
	//cout << "\tlocal index = " << ip << endl;
    
	// 2nd order projection for the currents
	for (unsigned int i=0; i<7; i++) {
		iloc = i+ipo-3;
		//#pragma omp atomic
		(*Jx1D)(iloc) += Jx_p[i];
		//#pragma omp atomic
		(*Jy1D)(iloc) += cry_p * Wt[i];
		//#pragma omp atomic
		(*Jz1D)(iloc) += crz_p * Wt[i];
        //#pragma omp atomic
        (*rho1D)(iloc)  += charge_weight * S1[i];
	}//i
    
}//END Projector1D4Order


void Projector1D4Order::operator() (Field* rho, Particle* part)
{
/*
	Field1D* rho1D  = static_cast<Field1D*>(rho);
	
    
	//Declaration of local variables
	int i;
	double xjn,xjmxi,xjmxi2;
	double rho_j = part->charge()*part->weight();  // charge density of the macro-particle
    

	//Locate particle on the grid
	xjn    = part->position(0) * dx_inv_;  // normalized distance to the first node
	i      = round(xjn);                   // index of the central node
	xjmxi  = xjn - (double)i;              // normalized distance to the nearest grid point
	xjmxi2 = xjmxi*xjmxi;                  // square of the normalized distance to the nearest grid point

	//cout << "Pos = " << part->position(0) << " - i global = " << i << " - i local = " << i-index_domain_begin <<endl;

	i -= index_domain_begin;
	
	// 2nd order projection for the total density
	//#pragma omp atomic
	(*rho1D)( i-1)  += 0.5 * (xjmxi2-xjmxi+0.25) * rho_j;
	//#pragma omp atomic
	(*rho1D)( i  )  += (0.75-xjmxi2)             * rho_j ;
	//#pragma omp atomic
	(*rho1D)( i+1)  += 0.5 * (xjmxi2+xjmxi+0.25) * rho_j;
*/
}
