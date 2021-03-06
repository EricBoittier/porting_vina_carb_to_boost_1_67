#ifdef __cplusplus
extern "C" {
#endif
/** \file molecules.h
\brief  Header file for molecule structures 

File begun May 2007 by Lachele Foley and modified continually ever since
	by Lachele Foley and others, including Mike Tessier. */

#if !defined(GLYLIB_MOLECULES)
#define GLYLIB_MOLECULES
#include <geometries.h>
#include <parameter_sets.h>

/** \addtogroup MAIN_STRUCTURES
 * @{
 */
extern char *ATYPESFILE,*RTYPESFILE,*MTYPESFILE; /**< locations of type databases, */
	/* to be set internally by programs, but globally visible */

typedef struct {
	int i; /**< general index */
	int m; /**< molecule index */
	int r; /**< residue index */
	int a; /**< atom index */
} molindex; /**< Index to describe position in a molecule */
typedef struct {
	int i; /**< general index */
	int E; /**< ensemble index */
	int A; /**< assembly index */
	int m; /**< molecule index */
	int r; /**< residue index */
	int a; /**< atom index */
} ensindex; /**< Index to describe position in an ensemble */
typedef struct {
	int nP; /**< number of positions */
	molindex *P; /**< the nP relevant positions */
	double s; /**< size (e.g., total length of chain) */
} molindex_set; /**< Structure holding molecule indices (for rings and such) */

/* 
Structures for making selections.
*/
typedef struct { 
	int na, *ai; ///< na atom indices and the na indices 
} residue_tree_index; ///< for storing indices within a structure like E[ei].m[mi].r[ri].a[ai].i
typedef struct { 
	int nr, *ri; ///< nr residue indices and the nr indices
	residue_tree_index *r; ///< nr residue_tree_index structures
} molecule_tree_index; ///< for storing indices within a structure like E[ei].m[mi].r[ri].a[ai].i
typedef struct { 
	int nm, *mi; ///< nm molecule indices and the nm indices
	molecule_tree_index *m; ///< nm molecule_tree_index structures
} ensemble_tree_index; ///< for storing indices within a structure like E[ei].m[mi].r[ri].a[ai].i
typedef struct {
	int posneg; ///< Is this a positive (1), negative (-1) or brand new (0) selection set?
	int nmN,nmi,nmn,*mn,*mi; ///< # of molecule names, numbers & indicies, nmn numbers and nmi indices
	char **mN; ///< nmN names
	int nrN,nri,nrn,*rn,*ri; ///< # of residue names, numbers & indicies, nrn numbers and nri indices
	char **rN; ///< nrN names
	int naN,nai,nan,*an,*ai; ///< # of atom names, numbers & indicies, nan numbers and nai indices
	char **aN; ///< naN names
} moiety_selection; 


typedef struct { 
	ensindex s; ///< "source" -- index to first atom in bond
	ensindex t; ///< "target" -- index to the other atom in the bond
	double o; ///< order of bond
	bond_type *typ; ///< pointer to type of bond
	int i; ///< index -- for example as alternative to *typ
	char *D; ///< free-form description
} bond; ///< a generic bond structure for connections of any type
typedef struct {
	int n; // number of bonds
	bond *b; // n of these
} bondset; // set of consecutive bonds
typedef struct {
	molindex s; ///< source atom in the bond
	molindex t; ///< target atom in the bond
	double o; ///< order 
	bond_type *typ; ///< pointer to type of bond
	int i; ///< index -- for example as alternative to *typ
	char *D; ///< free-form description
} molbond; ///< a bond within a molecule
typedef struct {
	int n;  // number of these
	molbond *b; // n of them
	char *D; // free-form description
} molbondset; // set of consecutive molbonds

typedef struct {
	double d; /**< a distance, =-1 if these values not set */
	double a; /**< a relevant angle */
	double t; /**< a reference torsion angle (sets chirality at a node) */
} position_set; /**< structure for info about a particular atom in terms of internal coordinates */
typedef struct {
	char isorigin; /**< Y if yes, N if no */
	ensindex ID; /**< whoami? -- here, i gives location in rT. */
	int nmbi; /**< number incoming bonds */
	molbond **mbi; /**< nmbi incoming bonds */
	int nmbo; /**< number outgoing bonds */
	molbond **mbo; /**< outgoing bonds */
	int nOV; /**< number of open valences */
	ensindex **OV; /**< nOV open valences */
} residue_node;
typedef struct {
	char isorigin; /**< Y if yes, N if no */
	ensindex ID; /**< whoami? -- here, i gives location in aT (or rT etc.) */
	int ni; /**< number incoming bonds */
	ensindex **i; /**< ni atoms making incoming bonds -- i gives locations in aT */
	int no; /**< number outgoing bonds */
	ensindex **o; /**< no atoms making outgoing bonds -- i gives locations in aT */
	int nOV; /**< number of open valences */
	ensindex **OV; /**< nOV open valences */
	int nEC; /**< number of extra coordinates (e.g., lone pairs) defined */
	ensindex **EC; /** nEC extra coordinates */
	int nps; /**< total number of position sets */
	ensindex *psi; /**< nps chirality ordered indices; others point into here if defined */
	position_set *ps; /**< nps chirality ordered positions */
	ensindex *tref; /**< grandparent atom to set torsion -- i gives location in aT */
	double tors; /**< torsion to set with respect to grandparent */
} atom_node; /**< for non-redundant bonding descriptions. See documentation. */


typedef struct {
	molindex a,b,c; // three atoms in the angle
	double ang; // the angle
	angle_type *typ; // pointer to type of angle
	char *D;// free-form descriptor
	int i; // index -- for example as alternative to *typ
} angle_index; // index to atoms in an angle
typedef struct {
	molindex a,b,c,d; // four atoms defining the torsion
	double ang; // the angle
	torsion_type *typ; // pointer to type of torsion
	char *D;// free-form descriptor
	int i; // index -- for example as alternative to *typ
} torsion_index; // index to atoms in an angle

/********** structure atom *************/
typedef struct {
	int n; ///< atom number or other identifying index
	char *N; ///< atom name 
	char *T; ///< atom type name
	char *D; ///< free-form description
	char *E; ///< atom element
	double m; ///< atom mass -- units defined per program needs
	int t; ///< type number -- must correspond to assignments of "atype" (see)
	atype *typ; ///< pointer to atype structure
	molindex moli; ///< the molecule index for this atom (address)
	int nb; ///< number of bonds within this residue (deprecated, soon to go away)
	bond *b; ///< bond structures (nb of these)
	int nmb; ///< number of bonds to other residues or molecules
	molbond *mb; ///< nmb of these (pointers to the structures)
	int mTi; ///< Index into the molecule's connection tree for this atom (m.aT)
	int rTi; ///< Index into the residue's connection tree for this atom (r.aT) 
	coord_3D x; ///< atom's main coordinates 
	coord_3D xv; ///< atom's main velocity
	int nalt; ///< number of alternate coordinate sets
	coord_3D *xa; ///< nalt of alternate coords
	int nxva; ///< number of alternate velocities defined
	coord_3D *xva; ///< nxva alternate velocities
	int nvec; ///< number of vector sets
	vectormag_3D *v; ///< vector sets
	int nch; ///< number of charges
	double *ch; ///< nch charges for this atom
	int ni; ///< number of other indices
	int *i; ///< other indices, as needed (ni of these)
	int nd; ///< number of double-precision parameters
	double *d; ///< other parameters, as needed (nd of these) 
	int nensi; ///< number of ensemble indices
	ensindex *ensi; ///< list of ensemble indices
	char *sres; ///< name of some other/original residue to which this atom belongs
	int nOD; ///< number of other descriptors
	char **OD; ///< the nOD descriptors
	int nVP; ///< number of void structures
	char *cID; ///< chain identifier
	void *VP; ///< nVP of these, whatever they may be
} atom; ///< an actual atom in a residue/molecule

/********** structure residue *************/
typedef struct {
	int n; ///< residue number given in input file
	char *cID; /**< Chain identifier */
	char *IC; ///< insertion code
	char *N; ///< residue name 
	char *T; ///< residue type
	char *D; ///< free-form description for residue
	int t; ///< type number
	rtype *typ; ///< pointer to rtype structure
	molindex moli; ///< the molecule index for this residue (address -- set .a to -1 or 0) 
	int na; ///< number of atoms in residue
	atom *a; ///< atom structures (na of these)
	atom_node *aT; ///< na of these (one per atom)
	double m; ///< molecular weight
	coord_3D COM; ///< center of mass for residue
	int nrb; ///< number of bonds between residues
	molbond *rb; ///< nrb of these descriptions of bonds 
	int mTi; ///< Index into the molecule's connection tree for this residue (m.rT)
	int nbs; ///< number of bond sets 
	molbondset *bs; ///< (consecutive bonds, use these for plotting, etc.)
	int nring; ///< number of simple rings (no cage structures, etc.)
	molindex_set *ring; ///< molecule indices for the nring rings
//	int nrbs; ///< number of ring bondsets defined
//	molbondset *rbs; ///< bondsets for rings
	int nrc; // number of ring/reference coordinate sets defined
	coord_3D *rc; ///< coordinates for ring/reference centers
	int nrp; ///< number of ring planes defined
	plane *rp; ///< equations for average/approximate/exact/etc. ring planes (where useful)
	// need something for more complex structures eventually
	int ni; ///< number of other indices
	int *i; ///< other indices, as needed (ni of these)
	int nd; ///< number of double-precision parameters
	double *d; ///< other parameters, as needed (nd of these)
	int nensi; ///< number of ensemble indices
	ensindex *ensi; ///< list of ensemble indices
	char *altname; ///< name of some other/original name for this residue 
	int nOD; ///< number of other descriptors
	char **OD; ///< the nOD descriptors
	int nVP; ///< number of void structures
	void *VP; ///< nVP of these, whatever they may be
} residue; ///< an actual residue in a molecule

/********** structure molecule *************/
typedef struct {
	int n; ///< molecule number given in an input file
	int i; ///< index
	char *Des; ///< Chain or other designation
	char *N; ///< free-form name for molecule
	char *T; ///< free-form type for molecule
	char *D; ///< free-form description for residue
	double m; ///< molecular weight
	char *cID; /**< Chain identifier */
	int mi; ///< number corresponding to the index in the parent ensemble
	int Ei; ///< number corresponding to parent ensemble
	int t; ///< type number
	mtype *typ; ///< pointer to atype structure
	coord_3D COM; ///< center of mass for molecule
	int na; ///< total number of atoms in molecule
	atom **a; ///< na of these, but should point into residues
	atom_node *aT; ///< nat of these
	int nr; ///< number of residues
        residue *r; ///< pointers to residues
	residue_node *rT; ///< nr of these residue-level connection trees
	int nrbs; ///< number of sets of bonds between residues (for example, linear chains)
	molbondset *rbs; ///< nrbs of these sets
	int nrc; ///< number of additional reference (ring centers, for example)
	coord_3D *rc; ///< nrc of these
	int nBOX; ///< Number of box_info structures defined
	boxinfo *BOX; ///< The nBOX structures
	//coord_3D boxl,boxh; // box dimensions
	int noi; ///< number of other indices
	int *oi; ///< other indices, as needed (ni of these)
	int nd; ///< number of double-precision parameters
	double *d; ///< other parameters, as needed (nd of these)
	int nensi; ///< number of ensemble indices
	ensindex *ensi; ///< list of ensemble indices
	int nOD; ///< number of other descriptors
	char **OD; ///< the nOD descriptors
	int nVP; ///< number of void structures
	void *VP; ///< nVP of these, whatever they may be
} molecule;

/********** structure dockinfo *************/
typedef struct{
	int i; ///< index
	int n; ///< number of docked structures represented
	int numClusters;
	int *clusterRank;
	coord_3D RC, *TR; ///< reference coordinate ; translation for docked structure
        vectormag_3D *Q, *QN, *QN0; ///< Quaternion x,y,z,w ; Quaternion nx,ny,nz,angle
	///< NOTE!! do -not- use typical vectormag_3D functions on these structures
	int nTors; ///< Number of Torsions 
	double *Tors; ///< nTors torsions
	double *eFEB; ///< Estimated Free Energy of Binding, kcal/mol [=(1)+(3)]
	double *eKi, *Tmp; ///< Estimated Inhibition Constant, Ki & temperature, Kelvin
	double *fDE; ///< Final Docked Energy, kcal/mol [=(1)+(2)] or [=(1)+(2)+(3)-(4)]
	double *fIE; ///< (1) Final Intermolecular Energy   
	double *fIEL; ///< (2) Final Internal Energy of Ligand 
	double *TFE; ///< (3) Torsional Free Energy          
	double *USE; ///< (4) Unbound System's Energy <Autodock 4.0 only>
	int nDIH; ///< number of dihedrals
	double *DIH; ///< the dihedrals
	char *D; ///<Free-form descriptor for the set
	char *DOCK_PROGRAM; ///<The docking program used, if known and relevant
	char *VERSION; ///<The version, or similar indentifier, of the above program
	molecule M; ///< to hold molecule info about the initial/docked structures
} dockinfo;

/********** structure assembly *************/
typedef struct { 
	int i; ///< index
	char *N; ///< name
	char *T; ///< type
	char *D; ///< description (free-form) (was *desc)
	double mass; ///< mass of assembly
	double TIME; ///< current/initial/reference time in the simulation
	coord_3D COM; ///< center of mass 
	int nm; ///< number of molecule structures
	molecule **m; ///< nm of these
	atom_node *mT; ///< nm of these
	//int nmb; // number of bonds/connections between molecules (H-bonds, for example)
	//molbond *mb; // nmb of these descriptions of connection 
	int nr; ///< number of residues
	residue **r; ///< nr of these -- probably best to point into molecules...
	residue_node *rT; ///< nr of these
	int na; ///< number of atoms
	atom **a; ///< na of these -- probably best to point into mol/res combos
	//int naT; ///< naT connection trees defined. // WHY naT???
	atom_node *aT; ///< na of these
	int nb; ///< total number of bonds
	molbond *b; ///< the bonds
	int nANG; ///< # of angles
	angle_index *ANG; ///< nANG of these
	int nTOR; ///< # of torsions
	torsion_index *TOR; ///< nTOR of these
	int nPRM; ///< number of parameter sets
	parameter_set **PRM; ///< pointers to parameter sets
	int nmbs; ///< number of sets of connections between molecules 
	molbondset *mbs; ///< nmbs of these sets
	int nBOX; ///< Number of box_info structures defined
	boxinfo *BOX; ///< The nBOX structures
	//coord_3D boxl,boxh; // simple box dimensions (limits low & high or just use one for size)
	//double boxang; // coord_3D is x, y and z -- angle (probably between XY and YZ planes in degrees, maybe).  
	//char *boxtype; // type of simple box (cubic, trapezoidal, etc.)
	int nOD; ///< number of other descriptors
	char **OD; ///< the nOD descriptors
	int nensi; ///< number of ensemble indices
	ensindex *ensi; ///< list of ensemble indices
	int nVP; ///< number of void pointers
	void *VP; ///< void pointers
} assembly;///< structure for groups of molecules within a larger structure

/********** structure ensemble *************/
typedef struct { 
	int i; ///< index
	char *N; ///< name
	char *T; ///< type
	char *D; ///< free-form descriptor
	double mass; ///< mass of ensemble
	coord_3D COM; ///< center of mass 
	int nm; ///< number of molecule structures
	molecule *m; ///< nm of these
	int nA; ///< number of assembly structures 
	assembly **A; ///< nA of these
	int nBOX; ///< Number of box_info structures defined
	boxinfo *BOX; ///< The nBOX structures
	//coord_3D boxl,boxh; // box dimensions
	int nPRM; ///< number of parameter sets
	parameter_set **PRM; ///< pointer to parameter sets
	int nOD; ///< number of other descriptors
	char **OD; ///< the nOD descriptors
	int nensi; ///< number of ensemble indices
	ensindex *ensi; ///< list of ensemble indices
	int nVP; ///< number of void pointers
	void *VP; ///< void pointers
} ensemble;///< structure for an entire system of molecules
/** @}*/

/*int NUMAT;  trying a move to PDB.h, which is where this belongs.  Would like to get rid of it soon */

/** \addtogroup DEBUGGING
 * @{
 */
/* The following is a set of functions intended primarily to facilitate 
debugging.  But, they could easily be used for verbose data output within
the program.  They all follow the same basic format:

print_X(X *x, int level)

where 	X = one of the structures defined above (e.g., molecule, residue, 
		bondset, atom, bond, atype, plane, vectormag_3D, coord_3D).
	*x = pointer to your structure
	level = the depth to print.  This is only available on structures 
		likely to contain arrays of other structures.  level=0 only
		prints the top-level information.  level=1 prints one level 
		down of other structures, lists, etc. level=2 prints two 
		levels down, etc.   The value of level can be larger than 
		the depth available -- the function will stop when it runs
		out of structures to print.  
*/
void print_molecule(molecule*,int),print_residue(residue*,int);
void print_bondset(bondset*,int),print_atom(atom*,int),print_bond(bond*);
void print_atype(atype*,int),print_plane(plane*);
void print_vectormag_3D(vectormag_3D*),print_coord_3D(coord_3D*);
//
void dprint_molecule(molecule*,int),dprint_residue(residue*,int);
void dprint_bondset(bondset*,int);
void dprint_molbondset(molbondset*,int);
void dprint_atom(atom*,int),dprint_bond(bond*),dprint_molbond(molbond *mb);
void dprint_atype(atype*,int),dprint_plane(plane*);
void dprint_vectormag_3D(vectormag_3D*),dprint_coord_3D(coord_3D*);
//
void dXprint_molecule(molecule*,int),dXprint_residue(residue*,int);
void dXprint_bondset(bondset*,int),dXprint_atom(atom*,int),dXprint_bond(bond*);
void dXprint_molbondset(molbondset*,int),dXprint_molbond(molbond *mb);
void dXprint_atype(atype*,int),dXprint_plane(plane*);
void dXprint_vectormag_3D(vectormag_3D*),dXprint_coord_3D(coord_3D*);
/** @}*/


/** \defgroup GEOMETRY Geometric Manipulations and Calculations

For functions that perform geometric manipulations or calculations on
the chemical structures (e.g. assembly, molecule, etc.), it is often 
necessary to indicate which set of coordinates are to be used for the 
calculation.  In most cases, it is also possible to perform the calculation
on coordinates in one location, but leave those untouched and save the
results to another location.  The same applies to velocities and vectors.

Special variable names and meanings:  

	xs, vs, xvs:	
		These are the source data on which to base the calculation.

	xd, vd, xvd: 	
		These are the locations to which changed data should be stored.
		Note that this location can typically be the same as the source.

	xt, vt, xvt:	
		In these cases, two sets of coordinates are being compared to

The variables above can take on the following values:

	-1
		This tells the function to use the main coordinate set.  
		That is, use atom.x or atom.xv.  This value is not relevant
		to vectors, where there is not a "main" vector.

	0, 1, 2, ...
		A number greater than or equal to zero indicates the location
		in an array.  These values apply to atom.xa[i], atom.xva[i]
		and atom.v[i].

	-2
		This is not available in all functions.  It indicates that 
		the entire array should be used.  This applies to atom.xa[i], 
		atom.xva[i] and atom.v[i].

	-3
		This is not available in all functions.  It indicates that 
		the main coordinates and the entire corresponding array should 
		be used.  This applies to { atom.x + atom.xa[i] } and to 
		{ atom.xv and atom.xva[i] }.  It does not apply to atom.v[i].

Information about vectors:

	All of the functions that involve vectors will set the magnitude 
	of the resulting vector without relying on the entry in the input 
	vector.  So, for example, there is no need to get_magnitude 
	before normalizing or multiplying by a scalar.

	This also means that the vector manipulation functions here are 
	inefficient in that they recalculate the magnitude every time they 
	are called.  If you are doing many vector manipulations in which 
	the magnitude is not relevant, you might consider making a similar 
	set that does not recalculate the magnitude.
*/
/** \addtogroup GEOMETRY
 * @{
 */
void translate_residue_by_XYZ(residue *r,int xs,int xd,coord_3D); 
void translate_molecule_by_XYZ(molecule *m,int xs,int xd,coord_3D); 
void translate_ensemble_by_XYZ(ensemble *e,int xs,int xd,coord_3D); 
void translate_zero_to_coord_M(molecule *m,int xs,int xd,coord_3D); 
coord_3D **atoms_to_coord_list(atom **atoms, int num_atoms); 
/** This function rotates the coordinate list such that the
vector given by vectormag_3D points along the Z (Y, X, other) axis.
The orientation of the orthogonal axes is arbitrary. */
void rotate_vector_to_Z_M(molecule* m,int xs,int xd,int vs,int vd,vectormag_3D vec); 
	// The four integers are:
	// int#1 location of source coordinates (-1=x, 0,1,2,etc=xa[xs]
	// int#2 location of rotated coordinates (-1=x, 0,1,2,etc=xa[xs]
	// int#3 location of source vectors (-1=do not calc, 0,1,2,etc=v[xs]
	// int#4 location of rotated vectors (-1=do not calc, 0,1,2,etc=v[xs]
void normalize_molecule_vectors(molecule *m,int vs,int vd);
void normalize_ensemble_vectors(ensemble *e,int vs,int vd);
	// int #1 -- location of source vector
	// int #2 -- where to write vectors normalized to one (made unit vectors) 
void shift_molecule_atoms_by_vector_scale(molecule *m,int xs,int xd,int vr, double scale);
vectormag_3D get_molecule_point_charge_dipole(molecule *m,int xs,int chgsrc, atype *AT);

void rollMolecule(molecule* m,double rad); //Rotates about x-axis using radians
void pitchMolecule(molecule* m,double rad);//Rotates about y-axis using radians
void yawMolecule(molecule* m,double rad);  //Rotates about z-axis using radians
void rollAssembly(assembly* a,double rad); //Rotates about x-axis using radians
void pitchAssembly(assembly* a,double rad);//Rotates about y-axis using radians
void yawAssembly(assembly* a,double rad);  //Rotates about z-axis using radians

/** This function will return the distance from a point pt to a plane pt.  If
absl is set to 0, it returns a signed distance ("above" or "below").  If set
to 1, it returns the absolute value.*/
double get_distance_from_point_to_plane(plane p, coord_3D pt, int absl); 
double get_angle_between_plane_and_vector(plane p, coord_3D pt1, coord_3D pt2);
/** @}*/

/** \addtogroup ANALYSIS
 * @{
 */
// int#1 is xs, the location of the source coords
void set_residue_COM(residue *r,atype *ATYPE,int xs);
void set_molecule_COM(molecule *m,atype *ATYPE,int xs);
void set_assembly_molecule_COM(assembly *a,atype *ATYPE,int xs);
void set_ensemble_COM(ensemble *e,atype *ATYPE,int xs);
coord_3D get_residue_COM(residue *r,atype *ATYPE,int xs);
coord_3D get_molecule_COM(molecule *m,atype *ATYPE,int xs);
coord_3D get_assembly_molecule_COM(assembly *a,atype *ATYPE,int xs);
coord_3D get_ensemble_COM(ensemble *e,atype *ATYPE,int xs);
// RMS between coordinate sets xs and xt
double get_alt_rms_res(residue *r, int xs, int xt); // per residue
double get_alt_rms_mol(molecule *m, int xs, int xt); // per molecule

void find_vdw_clashes_pairwize_between_Assemblies(assembly *A, int xsA, assembly *B, int xsB);
/** @}*/

/** \addtogroup INDEX_UTILS
 * @{
 */
ensindex copy_moli_to_ensi(molindex moli);
char is_consistent_ensi_moli(ensindex ensi, molindex moli);
char is_consistent_moli_moli(molindex mone, molindex mtwo);
char is_consistent_molbond_molbond(molbond mb1, molbond mb2);
char is_consistent_molbond_molbond_inverse(molbond mb1, molbond mb2);
char is_consistent_ensi_ensi(ensindex eone, ensindex etwo);
void set_ensemble_molindexes(ensemble *E);
void set_assembly_molindexes(assembly *A);
void set_molecule_molindexes(molecule *m, int mi);
void set_residue_molindexes(residue *r, int mi, int ri);
/*
Find atoms/residues named N -- searches for a.N or r.N
*/
molindex_set find_residue_atoms_by_N(residue *r, const char *name); /**< searches for a.N */
molindex_set find_molecule_atoms_by_N(molecule *m, const char *name); /**< searches for a.N */
molindex_set find_molecule_residues_by_N(molecule *m, const char *name); /**< searches for r.N */
molindex_set find_assembly_top_level_atoms_by_N(assembly *a, const char *name); /**< searches for a.N, saves i in A.a[i] to moli.i */
/*
Find atoms/residues numbered n -- searches for a.n or r.n
*/
molindex_set find_residue_atoms_by_n(residue *r, int number); /**< searches for a.n */
molindex_set find_molecule_atoms_by_n(molecule *m, int number); /**< searches for a.n */
molindex_set find_molecule_residues_by_n(molecule *m, int number); /**< searches for r.n */
molindex_set find_assembly_top_level_atoms_by_n(assembly *a, int number); /**< searches for a.n, saves i in A.a[i] to moli.i */
/** @}*/


/** \addtogroup BONDING
 * @{
 */
void set_molecule_atom_nodes_from_bonds(molecule *m);
int follow_molecule_atom_nodes_from_bonds(molecule *m, int iTree, atom *a);
void set_molecule_residue_molbonds(molecule *m);
void set_residue_atom_nodes_from_bonds(residue *r);
int follow_residue_atom_nodes_from_bonds(residue *r, int iTree, atom *a);
void set_molecule_residue_nodes_from_bonds(molecule *m);
int follow_molecule_residue_nodes_from_bonds(molecule *m, int iTree, residue *r);

void set_nbonds_for_atoms_in_assembly(assembly *A);
/** @}*/


/** \addtogroup INITIALIZATION
 * @{
 */
atype *ATYPE_init(); // initialize atom types -- for a few old programs only

void initialize_atype(atype *at);
void initialize_rtype(rtype *rt);
void initialize_mtype(mtype *mt);
void initialize_types(types *t);
void initialize_molindex(molindex *mi);
void initialize_ensindex(ensindex *ei);
void initialize_bond(bond *b);
void initialize_bondset(bondset *bs);
void initialize_molbond(molbond *mb);
void initialize_molbondset(molbondset *mbs);
void initialize_atom(atom *a);
void initialize_residue(residue *r);
void initialize_molecule(molecule *m);
void initialize_dockinfo(dockinfo *di);
void initialize_assembly(assembly *A);
void initialize_ensemble(ensemble *E);
/** @}*/


/** \addtogroup MEMORY_MANAGEMENT
 * @{
 */
/* Functions that recursively free memory in themselves, with the exception of parameters */
void deallocateBondType(bond_type *btp);
void deallocateMolbond(molbond *mlb);
/*
void deallocateAtomNode(atom_node *an);
void deallocateResidueNode(residue_node *rn);
*/
void deallocateBond(bond *bnd);
void deallocateBondset(bondset *bst);
void deallocateAtom(atom *atm);
void deallocateResidue(residue *res);
void deallocateMolecule(molecule *mol);
/** @}*/

/** \addtogroup STRUCTURE_UTILS
 * @{
 */
void set_atom_element_best_guess(atom *a);
void add_assembly_to_ensemble(
        assembly *A, ///< pointer to the assembly being added (SEE DOCS)
        ensemble *E ///< pointer to the ensemble being grown
        );
/** @}*/

#endif
#ifdef __cplusplus
}
#endif
