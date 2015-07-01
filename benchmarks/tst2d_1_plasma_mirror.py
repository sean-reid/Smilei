# ----------------------------------------------------------------------------------------
# 					SIMULATION PARAMETERS FOR THE PIC-CODE SMILEI
# ----------------------------------------------------------------------------------------
#
# Remember: never override the following names:
#           SmileiComponent, Species, Laser, Collisions, DiagProbe, DiagParticles,
#           DiagScalar, DiagPhase or ExtField
#
import math

l0 = 2.*math.pi			# laser wavelength
t0 = l0					# optical cycle
Lsim = [20.*l0,50.*l0]	# length of the simulation
Tsim = 50.*t0			# duration of the simulation
resx = 20.				# nb of cells in on laser wavelength
rest = 30.				# time of timestep in one optical cycle 


# dim: Geometry of the simulation
#      1d3v = cartesian grid with 1d in space + 3d in velocity
#      2d3v = cartesian grid with 2d in space + 3d in velocity
#      3d3v = cartesian grid with 3d in space + 3d in velocity
#      2drz = cylindrical (r,z) grid with 3d3v particles
#
dim = '2d3v'

# order of interpolation
#
interpolation_order = 2 

# SIMULATION BOX : for all space directions (use vector)
# cell_length: length of the cell
# sim_length: length of the simulation in units of the normalization wavelength 
#
cell_length = [l0/resx,l0/resx]
sim_length  = Lsim

# SIMULATION TIME
# timestep: duration of the timestep
# sim_time: duration of the simulation in units of the normalization period 
#
timestep = t0/rest
sim_time = Tsim
 
# ELECTROMAGNETIC BOUNDARY CONDITIONS
# bc_em_type_x/y/z : boundary conditions used for EM fields 
#                    periodic = periodic BC (using MPI topology)
#                    silver-muller = injecting/absorbing BC
#                    reflective = consider the ghost-cells as a perfect conductor
#
bc_em_type_x = ['silver-muller']
bc_em_type_y = ['silver-muller']

# RANDOM seed 
# this is used to randomize the random number generator
random_seed = 0

# ----------------
# LASER PROPERTIES
# ----------------
#
# for each laser define:
# a0: maximum amplitude of the laser electric field (in units of the normalization field)
# angle: angle (in degree) at which the laser enters the simulation box
# delta: polarization parameter, (0:y) (1:z) (0.707106781:circ)
# time_profile: string defining the time profile
# double_params: vector of real parameters used by the different time-profiles
#
Laser(
	boxSide = 'west',
	a0=0.1,
	focus=[10.*l0, 25.0*l0],
	angle=20.0, 
	delta=0.0,              
	time_profile = 'sin2',
	double_params = 5.*t0,
	transv_profile = 'focused',
	double_params_transv = 5.0*l0
)

# DEFINE ALL SPECIES
# species_type       = string, given name to the species (e.g. ion, electron, positron, test ...)
# initPosition_type  = string, "regular" or "random"
# initMomentum_type  = string "cold", "maxwell-juettner" or "rectangular"
# n_part_per_cell    = integer, number of particles/cell
# c_part_max         = float, factor on the memory reserved for the total number of particles
# mass               = float, particle mass in units of the electron mass
# dynamics_type      = string, type of species dynamics = "norm" or "rrLL"
# time_frozen        = float, time during which particles are frozen in units of the normalization time
# radiating          = boolean, if true, incoherent radiation calculated using the Larmor formula 
# charge             = float or function, particle charge in units of the electron charge
# charge_density     = float or function, species charge density in units of the "critical" density
#     or nb_density for number density
# mean_velocity      = list of floats or functions, mean velocity in units of the speed of light
# temperature        = list of floats or functions, temperature in units of m_e c^2
# Predefined functions: constant, trapezoidal, gaussian, polygonal, cosine
#
Species(
	species_type = 'ion',
	initPosition_type = 'random',
	initMomentum_type = 'cold',
	ionization_model = 'none',
	n_part_per_cell = 5,
	c_part_max = 1.0,
	mass = 1836.0,
	charge = 1.0,
	nb_density = trapezoidal(2.0,xvacuum=10.*l0,xplateau=4.*l0),
	time_frozen = Tsim,
	bc_part_type_west  = 'refl',
	bc_part_type_east  = 'refl',
	bc_part_type_south = 'none',
	bc_part_type_north = 'none'
)
Species(
	species_type = 'eon',
	initPosition_type = 'random',
	initMomentum_type = 'cold',
	ionization_model = 'none',
	n_part_per_cell = 5,
	c_part_max = 1.0,
	mass = 1.0,
	charge = -1.0,
	nb_density = trapezoidal(2.0,xvacuum=10.*l0,xplateau=4.*l0),
	time_frozen = 0.,
	bc_part_type_west  = 'refl',
	bc_part_type_east  = 'refl',
	bc_part_type_south = 'none',
	bc_part_type_north = 'none'
)

# ---------------------
# DIAGNOSTIC PARAMETERS
# ---------------------

# print_every (on screen text output) 
# print_every = 60


# DIAG ON SCALARS
# every = number of time-steps between each output
#
DiagScalar(every=5)
fieldDump_every = 15
fieldsToDump = ('Ex','Ey','Rho_eon')

