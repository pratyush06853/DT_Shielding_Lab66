//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: IronFilterDetectorConstruction.cc $
//
/// \file IronFilterDetectorConstruction.cc
/// \brief Implementation of the IronFilterDetectorConstruction class

#include "IronFilterDetectorConstruction.hh"
#include "IronFilterDetectorMessenger.hh"//pratyush
#include "G4Material.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4UnitsTable.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4Polycone.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4NeutronHPThermalScatteringNames.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4ios.hh"
#include "G4GeometryManager.hh"//pratyush
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include <TMath.h>

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterDetectorConstruction::IronFilterDetectorConstruction()
 : G4VUserDetectorConstruction(),
   LabFloorWall_solid_PV(0),
   LabFloorExtended_solid_PV(0),
   frontglassdoor_PV(0),
   frontdoor_PV(0),
   glasswindow_PV(0),
   reardoor_PV(0),
   lab66FloorWall_solid_PV(0),
   lab70FloorWall_solid_PV(0),
   Lab32FloorWall_solid_PV(0),
   lab30FloorWall_solid_PV(0),
   lab28FloorWall_solid_PV(0),
   TestSurface_solid_PV(0),
   boratedwater_PV(0),
   multiplier_lead_PV(0),
   moderator_aluminum_PV(0),
   moderator_titanium_PV(0),
   filter_scandium_PV(0),
   filter_scandium_2_PV(0),
   collimation_hole_PV(0),
   ConcreteSupport_PV(0),
   Left_Side_Bpoly_shield_PV(0),
   Right_Side_Bpoly_shield_PV(0),
   Up_Bpoly_shield_PV(0),
   //shield_cap_iron_PV(0),
   Lead_around_TiAndF_PV(0),
   Insulation_PV(0),
   DilutionUnit_PV(0),
   Phantom_PV(0),
   //Phantom2_PV(0),
   //Phantom3_PV(0),
   //Phantom4_PV(0),
   ////Phantom5_PV(0),
   //Phantom6_PV(0),
   //Phantom7_PV(0),
   //Phantom8_PV(0),
   inner_BPoly_PV(0),
   Test_CENTERPOINT_PV(0),
   //1st detector of type A
   shielding_lead_PV_2(0),
   filter_aluminum_PV_2(0),
   shield_cap_iron_PV_2(0),
   DT_solid_PV_2(0),
   Iron_solid_PV_2(0),
   //2nd detector of type A
   shielding_lead_PV(0),
   filter_aluminum_PV(0),
   shield_cap_iron_PV(0),
   DT_solid_PV(0),
   Iron_solid_PV(0),
   //3rd detector of type A
   shielding_lead_PV_3(0),
   filter_aluminum_PV_3(0),
   shield_cap_iron_PV_3(0),
   DT_solid_PV_3(0),
   Iron_solid_PV_3(0),
   //4th detector of type B
   shielding_lead_PV_1(0),
   filter_aluminum_PV_1(0),
   shield_cap_iron_PV_1(0),
   DT_solid_PV_1(0),
   Iron_solid_PV_1(0),
   //5th detector of type B
   shielding_lead_PV_1_5(0),
   filter_aluminum_PV_1_5(0),
   shield_cap_iron_PV_1_5(0),
   DT_solid_PV_1_5(0),
   Iron_solid_PV_1_5(0),
   //6th detector of type B
   shielding_lead_PV_1_6(0),
   filter_aluminum_PV_1_6(0),
   shield_cap_iron_PV_1_6(0),
   DT_solid_PV_1_6(0),
   Iron_solid_PV_1_6(0),
   ///////
   fCheckOverlaps(true)
{

  delta= 1.0*cm;// 1.0cm parameter of catchment area
  zeroRadius = 0.*cm;
  startAngle = 0.*deg;
  spanningAngle = 360.*deg;
  DD_Height = 20.0*cm;

  //for messenger, you vary these variables using the macro
  fMultiplierLeadHeightRear = 24.0*cm;//20.0*cm
  fMultiplierLeadHeightFront=  25.0*cm;//30.0*cm

  fModeratorAluminumHeight= 40.0*cm;//39.0*cm
  fModeratorTitaniumHeight= (7.0)*cm; //(34.0)*cm

  fMultiplierLeadRadius = 27.86*cm;//20.0*cm
  fModeratorAluminumRadius = 22.86*cm;//15.0*cm without Ti
  fModeratorTitaniumRadius = 22.86*cm;

  //fPolyHeight = 41.0*cm;//
  //fPolyHeight = 35.0*cm;//
  fPolyHeight = 28.0*cm;//this shouldn't change

  //fFilterCellSpacing= 50.0*cm;//5
  fFilterCellSpacing= 60.0*cm+26.0*cm;//50.0*cm+26.0*cm;

  ftestx = 0*m;
  ftesty = 0*m;
  ftestz = 0.0*m;



  fDetectorMessenger = new IronFilterDetectorMessenger(this);
  //
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterDetectorConstruction::~IronFilterDetectorConstruction()
{
  delete fDetectorMessenger;//Pratyush
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* IronFilterDetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterDetectorConstruction::DefineMaterials()
{
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;
  G4double density, fractionMass;
  G4String symbol, name;
  G4int nComponents, nAtoms;
  G4double temp;
  G4NistManager* NistMgr = G4NistManager::Instance();

  //G4Element* elBe = new G4Element(name = "Beryllium", symbol = "Be", z = 4.0, a = 9.012*g/mole);
  G4Element* elF = new G4Element(name= "Fluorine", symbol = "F", z = 9.0, a= 18.998403*g/mole); //pratyush
  G4Element* elLi6  = new G4Element(name = "Lithium", symbol = "Li", z = 3.0, a = 6.015*g/mole);
  //G4Element* elO  = new G4Element(name = "Oxygen", symbol = "O", z = 8.0, a = 15.999*g/mole);
  //G4Element* elCr  = new G4Element(name = "Chromium", symbol = "Cr", z = 24.0, a = 51.996*g/mole);
  //G4Element* elFe  = new G4Element(name = "Iron", symbol = "Fe", z = 26.0, a = 55.845*g/mole);
  //G4Element* elNi  = new G4Element(name = "Nickel", symbol = "Ni", z = 28.0, a = 58.693*g/mole);
  //G4Element* elMo  = new G4Element(name = "Molybdenum", symbol = "Mo", z = 42.0, a = 95.94*g/mole);
  G4Element* elAl  = new G4Element(name = "Aluminum", symbol = "Al", z = 13.0, a = 26.982*g/mole);
  //G4Element* elZn  = new G4Element(name = "zinc", symbol = "Zn", z = 30.0, a = 65.38*g/mole);
  G4Element* elS  = new G4Element(name = "sulphur", symbol = "S", z = 16.0, a = 32.065*g/mole);
  G4Element* elH  = new G4Element(name = "Hydrogen", symbol = "H", z = 1.0, a = 1.008*g/mole);
  G4Element* elC  = new G4Element(name = "Carbon", symbol = "C", z = 6.0, a = 12.011*g/mole);
  G4Element* elN = new G4Element("Nitrogen", symbol = "N",z = 7.,a = 14.01*g/mole);
  G4Element* elO = new G4Element("Oxygen", symbol = "O",z = 8.,a = 16.00*g/mole);

  G4Element* elNa = new G4Element("Sodium",symbol ="Na",z = 11.,a= 22.99*g/mole);

  G4Element* elMg = new G4Element("Magnesium",symbol ="Mg",z = 12.,a= 24.305*g/mole);

  G4Element* elP = new G4Element("Phosphorus",symbol ="P",z = 15.,a= 30.974*g/mole);

  G4Element* elCl = new G4Element("Chlorine",symbol ="Cl",z = 17.,a= 35.453*g/mole);

  G4Element* elK = new G4Element("Potassium",symbol ="K",z = 19.,a= 39.098*g/mole);

  G4Element* elCa = new G4Element("Calcium",symbol ="Ca",z = 20.,a= 40.08*g/mole);

  G4Element* elFe  = new G4Element("Iron",symbol ="Fe",z = 26.,a= 55.85*g/mole);

  G4Element* elZn = new G4Element("Zinc",symbol ="Zn",z = 30.,a= 65.38*g/mole);

  G4Element* elRb = new G4Element("Rb",symbol ="Rb",z = 37.,a= 85.47 *g/mole);

  G4Element* elSr = new G4Element("Sr",symbol ="Sr",z = 38.,a= 87.62 *g/mole);

  G4Element* elZr = new G4Element("Zr",symbol ="Zr",z = 40.,a= 91.22 *g/mole);

  G4Element* elPb = new G4Element("Lead",symbol ="Pb", z = 82.,a= 207.19 *g/mole);

  G4Element* elSi  = new G4Element("Silicon", symbol = "Si", z = 14.0, a = 28.085*g/mole);

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
  G4Element* elH  = new G4Element(name = "Hydrogen", symbol = "H", z = 1.0, a = 1.008*g/mole);
  G4Element* elC  = new G4Element(name = "Carbon", symbol = "C", z = 6.0, a = 12.011*g/mole);
  G4Element* elNa  = new G4Element(name = "Sodium", symbol = "Na", z = 11.0, a = 22.990*g/mole);
  G4Element* elSi  = new G4Element(name = "Silicon", symbol = "Si", z = 14.0, a = 28.085*g/mole);
  G4Element* elP  = new G4Element(name = "Phosphorus", symbol = "P", z = 15.0, a = 30.974*g/mole);
  G4Element* elK  = new G4Element(name = "Potassium", symbol = "K", z = 19.0, a = 39.098*g/mole);
  G4Element* elCa  = new G4Element(name = "Calcium", symbol = "Ca", z = 20.0, a = 40.078*g/mole);
  G4Element* elMn  = new G4Element(name = "Maganese", symbol = "Mn", z = 25.0, a = 54.938*g/mole);
  G4Element* elTi  = new G4Element(name = "Titanium", symbol = "Ti", z = 22.0, a = 47.867*g/mole);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
  //Vacuum
  new G4Material("galactic", z = 1.0, a = 1.01*g/mole, density = universe_mean_density, kStateGas, 2.73*kelvin, 3.e-18*pascal);


  //helium
  new G4Material("liquid_helium", z = 2., a = 4.00*g/mole, density = 0.145*g/cm3, kStateLiquid, temp = 3.*kelvin);


  // Lead
  new G4Material(name = "Pb", z = 82.0, a = 207.2*g/mole, density = 11.34*g/cm3);

  // Iron
  new G4Material("NatIron", z = 26.0, a = 55.845*g/mole, density = 7.874*g/cm3);


  // Iron
   new G4Material("NatScandium", z = 21.0, a = 44.95*g/mole, density = 2.985*g/cm3);

  // Titanium
  new G4Material("NatTi", z = 22.0, a = 47.867*g/mole, density = 4.507*g/cm3);


  //Copper
  new G4Material("NatCu", z =29.,  a =63.55*g/mole,density = 8.96 *g/cm3);

  //Aluminum
  new G4Material("NatAluminum", z = 13.0, a = 26.9815384*g/mole, density = 2.70*g/cm3, kStateSolid, 296*kelvin);


  //Manganese
  new G4Material("NatManganese", z = 25.0, a = 54.938*g/mole, density = 7.21*g/cm3);

  //Natural Boron
  //G4Material* NatB = new G4Material("NatB", z = 5.0, a = 10.811*g/mole, density = 2.37*g/cm3);
  G4Element* NatB=NistMgr->FindOrBuildElement("B");

  //Natural Carbon
  //G4Material* NatC = new G4Material("NatC", z = 6.0, a = 12.0107*g/mole, density = 1.95*g/cm3);
  G4Element* NatC=NistMgr->FindOrBuildElement("C");

  //Natural Hydrogen
  //G4Material* NatH = new G4Material("NatH", z = 1.0, a = 1.00784*g/mole, density = 0.0008999*g/cm3);
  G4Element* NatH=NistMgr->FindOrBuildElement("H");

  //Natural Oxygen
  //G4Material* NatO = new G4Material("NatO", z = 8.0, a = 15.999*g/mole, density = 0.001141*g/cm3);
  G4Element* NatO=NistMgr->FindOrBuildElement("O");

  //Natural Oxygen
  //G4Material* NatNa = new G4Material("NatNa", z = 11.0, a = 22.989*g/mole, density = 0.968*g/cm3);
  G4Element* NatNa=NistMgr->FindOrBuildElement("Na");

   //Natural Sulphur
   //G4Material* NatS = new G4Material("NatS", z = 16.0, a = 32.065*g/mole, density = 1.92*g/cm3);
   G4Element* NatS=NistMgr->FindOrBuildElement("S");

   //Ni60
   G4Material* Ni60 = new G4Material("Ni60", z = 28.0, a = 59.9307864*g/mole, density = 8.9*g/cm3);
   //Fe54
   G4Material* Fe54 = new G4Material("Fe54", z = 26.0, a = 	53.9396090*g/mole, density = 7.874*g/cm3);
   //Co
   G4Material* NatCo = new G4Material("NatCo", z = 27.0, a = 	58.933*g/mole, density = 8.86*g/cm3);

   G4Element *TS_H_P = new G4Element("TS_H_of_Polyethylene", "H", 1, 1.007*g/mole);
   G4Element *TS_H_W = new G4Element("TS_H_of_Water", "H", 1, 1.007*g/mole);

   G4Material* air = NistMgr->FindOrBuildMaterial("G4_AIR");
   //G4Material* concrete = NistMgr->FindOrBuildMaterial("G4_CONCRETE");

   //Water
   G4Material* water = new G4Material("water", density= 1.00 * g / cm3,nComponents= 2, kStateLiquid, 296*kelvin);
   water->AddElement(TS_H_W,2);//pratyush
   water->AddElement(elO,1);//pratyush

  //Lithium6_Fluoride
  //G4Material* Li6F = new G4Material("Li6F", density= 2.54 * g / cm3,nComponents= 2);
  //Li6F->AddElement(elLi6, 1); //pratyush
  //Li6F->AddElement(elF,1);   //pratyush

  //Aluminum Fluoride
  G4Material* AlF3 = new G4Material("AlF3", density= 3.10 * g / cm3,nComponents= 2); //pratyush
  AlF3->AddElement(elAl, 1);  //pratyush
  AlF3->AddElement(elF, 3);   //pratyush

  //Aluminum Fluoride
  G4Material* Borax = new G4Material("Borax", density= 0.76* g / cm3,nComponents= 4,kStateSolid, 296*kelvin); //pratyush
  Borax->AddElement(NatNa,12.06*perCent);//2
  Borax->AddElement(NatB,11.34*perCent);//4
  Borax->AddElement(NatH,5.29*perCent);//20
  Borax->AddElement(NatO,71.32*perCent);//17

  //Boric Acid https://www.convertunits.com/molarmass/Boric+Acid
  G4Material* boric_acid = new G4Material("boric_acid", density= 1.44* g / cm3,nComponents= 3,kStateSolid, 296*kelvin); //pratyush
  boric_acid->AddElement(NatH,4.890*perCent);//3
  boric_acid->AddElement(NatB,17.484*perCent);//1
  boric_acid->AddElement(NatO,77.626*perCent);//3

  //Borax_water_Mixture(5.8% solubity of borax https://omsi.edu/sites/all/FTP/files/kids/Borax-msds.pdf)
  //mixture of 5.5% Borax and 94.5% of Water
  G4Material* borax_water = new G4Material( "borax_water",density= 0.9868*g/cm3, nComponents= 2,kStateLiquid, 296*kelvin); //pratyush
  borax_water->AddMaterial( Borax, 5.5*perCent );  //pratyush
  borax_water->AddMaterial( water, 94.5*perCent ); //pratyush


  //Borax_BoricAcid_buffer(https://www.researchgate.net/publication/244069630_Preparation_of_highly_concentrated_aqueous_solution_of_sodium_borate)
  //mixture of 20g BoricAcid, 25g of Borax and 100g of water
  G4Material* borax_boricacid_buffer = new G4Material( "borax_boricacid_buffer",density= 1.019*g/cm3, nComponents= 3,kStateLiquid, 296*kelvin);
  borax_boricacid_buffer->AddMaterial( boric_acid, 13.7*perCent );//pratyush
  borax_boricacid_buffer->AddMaterial( Borax, 17.2*perCent );//pratyush
  borax_boricacid_buffer->AddMaterial( water, 69.1*perCent );//pratyush

  //Fluental
  //mixture of 40% Al and 60% of AlF_3
  //G4Material* fluental = new G4Material( "fluental",density= 2.94*g/cm3, nComponents= 2); //pratyush
  G4Material* fluental = new G4Material( "fluental",density= 2.50*g/cm3, nComponents= 2); //pratyush
  fluental->AddMaterial( AlF3, 60.*perCent );  //pratyush
  fluental->AddElement( elAl, fractionMass = 40.*perCent ); //pratyush

  // Titanium
  G4Isotope* Ti46 = new G4Isotope("Ti46", 22, 46, 45.9526316*g/mole);
  G4Isotope* Ti47 = new G4Isotope("Ti47", 22, 47, 46.9517631*g/mole);
  G4Isotope* Ti48 = new G4Isotope("Ti48", 22, 48, 47.9479463*g/mole);
  G4Isotope* Ti49 = new G4Isotope("Ti49", 22, 49, 48.9478700*g/mole);
  G4Isotope* Ti50 = new G4Isotope("Ti50", 22, 50, 49.9447912*g/mole);

  G4Element* NatTi = new G4Element("titanium_natural", "Ti",5);
  NatTi->AddIsotope(Ti46,8.25*perCent);
  NatTi->AddIsotope(Ti47,7.44*perCent);
  NatTi->AddIsotope(Ti48,73.72*perCent);
  NatTi->AddIsotope(Ti49,5.41*perCent);
  NatTi->AddIsotope(Ti50,5.18*perCent);

  G4Material* titanium = new G4Material("titanium", 4.507*g/cm3,1, kStateSolid, 296*kelvin);
  titanium->AddElement(NatTi, 1);



  //polyethyleneBorated
  //G4Material* boratedPoly = new G4Material( "boratedPoly", density=1.19*g/cm3, nComponents=3,kStateSolid, 296*kelvin);
  //G4Material* boratedPoly = new G4Material( "boratedPoly", density=0.95*g/cm3, nComponents=3,kStateSolid, 296*kelvin);

  //G4Material* boratedPoly = new G4Material( "boratedPoly", density=1.08*g/cm3, nComponents=3,kStateSolid, 296*kelvin);
  //https://www.shieldwerx.com/assets/SWX-201HD%202018.2.pdf
  //boratedPoly->AddElement( NatB, 5.*perCent );
  //boratedPoly->AddElement( NatC, 83.3*perCent );
  //boratedPoly->AddElement(TS_H_P, 11.7*perCent );

  //G4Material* boratedPoly = new G4Material( "boratedPoly", density=0.95*g/cm3, nComponents=3,kStateSolid, 296*kelvin);
  //boratedPoly->AddElement(NatB, 30.*perCent);
  //boratedPoly->AddElement(NatC, 61.37*perCent);
  //boratedPoly->AddElement(TS_H_P, 8.63*perCent);


  //boratedPoly->AddElement( NatB, 3.*perCent );
  //boratedPoly->AddElement( NatC, 82.576*perCent );
  //boratedPoly->AddElement(TS_H_P, 14.424*perCent );

  //from vivian communicated via whatsapp
  G4Material* boratedPoly = new G4Material("boratedPoly", density=1.05*g/cm3, nComponents=3,kStateSolid, 296*kelvin);
  boratedPoly->AddElement(NatB, 5*perCent);
  boratedPoly->AddElement(NatC, 81.55*perCent);
  boratedPoly->AddElement(TS_H_P, 13.45*perCent);

  //from vivian communicated via whatsapp
  //https://docs.google.com/spreadsheets/d/1W83GhE5Nq1R9f7KmCgBqi_Qkz0ilursgWs5V-Vmju8o/edit#gid=656123429
  G4Material* boratedPoly_15 = new G4Material("boratedPoly_15", density=1.15*g/cm3, nComponents=3,kStateSolid, 296*kelvin);
  boratedPoly_15->AddElement(NatB, 15*perCent);
  boratedPoly_15->AddElement(NatC, 73.38*perCent);
  boratedPoly_15->AddElement(TS_H_P, 11.62*perCent);

  // wood
  G4Material* wood = new G4Material("wood", density=0.9*g/cm3, nComponents=3);
  wood->AddElement(TS_H_P, 4);
  wood->AddElement(elO , 1);
  wood->AddElement(elC, 2);

  G4Material* quartz = new G4Material("quartz", density=2.200*g/cm3, nComponents=2);
  quartz->AddElement(elSi, 1);
  quartz->AddElement(elO , 2);

  // Polyethylene with boron at 3% - Has borated polyethylene any oxygen elements?
  //G4Material* boratedPoly = new G4Material("boratedPoly ", density=0.96*g/cm3, nComponents=3);
  //boratedPoly->AddElement(NatH,  14.424*perCent);
  //boratedPoly->AddElement(NatC,  82.576*perCent);
  //boratedPoly->AddElement(NatB,  3.00*perCent);


  G4Material*soft_tissue = new G4Material("soft_tissue",density= 0.9869*g/cm3,nComponents=9);
  soft_tissue->AddElement(elH,0.105);
  soft_tissue->AddElement(elC,0.256);
  soft_tissue->AddElement(elN,0.027);
  soft_tissue->AddElement(elO,0.602);
  soft_tissue->AddElement(elNa,0.001);
  soft_tissue->AddElement(elP,0.002);
  soft_tissue->AddElement(elS,0.003);
  soft_tissue->AddElement(elCl,0.002);
  soft_tissue->AddElement(elK,0.002);


  //soil
  G4Material*soil = new G4Material("soil",density= 1.50*g/cm3,nComponents=8);
  soil->AddElement(elH,0.021);
  soil->AddElement(elC,0.016);
  soil->AddElement(elO,0.577);
  soil->AddElement(elAl,0.050);
  soil->AddElement(elSi,0.271);
  soil->AddElement(elK,0.013);
  soil->AddElement(elCa,0.041);
  soil->AddElement(elFe,0.011);

  //G4Material*Pol= new G4Material("Pol",density= 0.96*g/cm3,nComponents=2);
  //Pol->AddElement(TS_H_P,  0.1486);
  //Pol->AddElement(elC,  0.8514);

  //LiI
  G4Isotope* Li6 = new G4Isotope("Li6", 3, 6, 6.01*g/mole);
  G4Isotope* Li7 = new G4Isotope("Li7", 3, 7, 7.01*g/mole);

  G4Element* Li6enriched = new G4Element("Lithium_enchried", "Li",2);
  Li6enriched->AddIsotope(Li6,97.0*perCent);
  Li6enriched->AddIsotope(Li7,3.0*perCent);

  G4Material* Li6F = new G4Material("Li6F", density= 2.64 * g / cm3,nComponents= 2, kStateSolid, 296*kelvin);
  Li6F->AddElement(Li6enriched, 1);
  Li6F->AddElement(elF,1);

  G4Material* ZnS = new G4Material("ZnS", density= 4.09 * g / cm3,nComponents= 2, kStateSolid, 296*kelvin);
  ZnS->AddElement(elZn, 1);
  ZnS->AddElement(elS,1);

  //Remeber HD has 1:2 LiF to ZnS concentration
  G4Material* ej_426_HD= new G4Material( "ej_426_HD", density=3.60*g/cm3, nComponents=2, kStateSolid, 296*kelvin);
  ej_426_HD->AddMaterial( Li6F, 33.3*perCent );   //1.026*g/cm3
  ej_426_HD->AddMaterial( ZnS, 66.7*perCent );


  //Polyethylene moderator
  G4Material*  polyethylene = new G4Material("polyethylene", density=0.94*g/cm3, nComponents=2,kStateSolid, 296*kelvin);
  polyethylene->AddElement(NatC, 1);
  polyethylene->AddElement(TS_H_P, 2);

  // Assuming PMMA -- see
  //	http://en.wikipedia.org/wiki/Poly(methyl_methacrylate)
  G4Material*  acrylic = new G4Material("acrylic", density= 1.17 * g/cm3, nComponents=3 ,kStateSolid, 296*kelvin);
  acrylic->AddElement(NatC, 5);
  acrylic->AddElement(elO, 2);
  acrylic->AddElement(TS_H_P, 8);




  //concrete
  G4Material*concrete = new G4Material("concrete",density= 2.3*g/cm3,nComponents=10);
  //G4Material*concrete = new G4Material("concrete",density= 4.81*g/cm3,nComponents=10);
  concrete->AddElement(elH,0.01);
  concrete->AddElement(elC,0.001);
  concrete->AddElement(elO,0.529107);
  concrete->AddElement(elNa,0.016);
  concrete->AddElement(elMg,0.002);
  concrete->AddElement(elAl,0.033872);
  concrete->AddElement(elSi,0.337021);
  concrete->AddElement(elK,0.013);
  concrete->AddElement(elCa,0.044);
  concrete->AddElement(elFe,0.014);


  //Pitts normal concrete used for base
  G4Material*baseconcrete = new G4Material("baseconcrete",density= 2.3*g/cm3,nComponents=11);
  //G4Material*concrete = new G4Material("concrete",density= 4.81*g/cm3,nComponents=10);
  baseconcrete->AddElement(elFe,0.111);
  baseconcrete->AddElement(elSi,0.0309);
  baseconcrete->AddElement(elAl,0.0055);
  baseconcrete->AddElement(elCa,0.2947);
  baseconcrete->AddElement(elMg,0.0144);
  baseconcrete->AddElement(elNa,0.0004);
  baseconcrete->AddElement(elK,0.001);
  baseconcrete->AddElement(elS,0.0018);
  baseconcrete->AddElement(elC,0.0742);
  baseconcrete->AddElement(elH,0.0058);
  baseconcrete->AddElement(elO,0.4603);

  //concrete
  //G4Material*concrete = new G4Material("concrete",density= 2.3*g/cm3,nComponents=10);
  G4Material*HDconcrete = new G4Material("HDconcrete",density= 4.81*g/cm3,nComponents=10);
  HDconcrete->AddElement(elH,0.01);
  HDconcrete->AddElement(elC,0.001);
  HDconcrete->AddElement(elO,0.529107);
  HDconcrete->AddElement(elNa,0.016);
  HDconcrete->AddElement(elMg,0.002);
  HDconcrete->AddElement(elAl,0.033872);
  HDconcrete->AddElement(elSi,0.337021);
  HDconcrete->AddElement(elK,0.013);
  HDconcrete->AddElement(elCa,0.044);
  HDconcrete->AddElement(elFe,0.014);




  //borated concrete
  G4Material* borated_concrete = new G4Material("borated_concrete",density= 2.32*g/cm3,nComponents=10);
  borated_concrete->AddElement(elH,0.96*perCent);
  borated_concrete->AddElement(elO,51.3*perCent);
  borated_concrete->AddElement(NatB,2.9*perCent);
  borated_concrete->AddElement(elC,5.36*perCent);
  borated_concrete->AddElement(elMg,0.42*perCent);
  borated_concrete->AddElement(elAl,0.79*perCent);
  borated_concrete->AddElement(elSi,15.7*perCent);
  borated_concrete->AddElement(elS,0.42*perCent);
  //borated_concrete->AddElement(elCa,23*perCent);//doesnot add up to 100
  borated_concrete->AddElement(elCa,21.65*perCent);
  borated_concrete->AddElement(elFe,0.50*perCent);


  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* IronFilterDetectorConstruction::DefineVolumes()
{

  // Get materials
  G4Material* Vacuum = G4Material::GetMaterial("galactic");
  G4Material* Iron = G4Material::GetMaterial("NatIron");
  G4Material* Scandium = G4Material::GetMaterial("NatScandium");
  //G4Material* ScandiumOxide = G4Material::GetMaterial("scandiumoxide");
  G4Material* Helium = G4Material::GetMaterial("liquid_helium");
  G4Material* Aluminum = G4Material::GetMaterial("NatAluminum");
  //G4Material* Titanium = G4Material::GetMaterial("NatTi");
  G4Material* Titanium = G4Material::GetMaterial("titanium");
  G4Material* Sulphur = G4Material::GetMaterial("NatS");
  G4Material* Copper= G4Material::GetMaterial("NatCu");
  G4Material* Fluental = G4Material::GetMaterial("fluental");
  G4Material* BoraxWater = G4Material::GetMaterial("borax_water");
  G4Material* BoraxBoricAcidBuffer = G4Material::GetMaterial("borax_boricacid_buffer");
  G4Material* Lithium6_Fluoride = G4Material::GetMaterial("Li6F");
  G4Material* Lead = G4Material::GetMaterial("Pb");
  G4Material* Manganese = G4Material::GetMaterial("NatManganese");
  G4Material* BoratedPoly = G4Material::GetMaterial("boratedPoly");
  G4Material* BoratedPoly_15 = G4Material::GetMaterial("boratedPoly_15");
  G4Material* Cobalt = G4Material::GetMaterial("NatCo");
  G4Material* Nickel60 = G4Material::GetMaterial("Ni60");
  G4Material* Iron54 = G4Material::GetMaterial("Fe54");
  G4Material*  Soft_Tissue=G4Material::GetMaterial("soft_tissue");
  G4Material*  Concrete = G4Material::GetMaterial("concrete");
  G4Material*  BaseConcrete = G4Material::GetMaterial("baseconcrete");
  G4Material*  HDConcrete = G4Material::GetMaterial("HDconcrete");
  G4Material*  Borated_Concrete = G4Material::GetMaterial("borated_concrete");
  G4Material*  Wood = G4Material::GetMaterial("wood");
  G4Material*  Quartz = G4Material::GetMaterial("quartz");
  G4Material*  Soil = G4Material::GetMaterial("soil");
  G4Material*  Polyethylene = G4Material::GetMaterial("polyethylene");
  G4Material* Water = G4Material::GetMaterial("water");
  G4Material* Air=G4Material::GetMaterial("air");
  G4Material* EJ4265HD = G4Material::GetMaterial("ej_426_HD");
  G4Material* Acrylic = G4Material::GetMaterial("acrylic");

  if ( ! Vacuum ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined.";
    G4Exception("IronFilterDetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }

//
//  calculate the Sizes of some derived units.
//
G4double Scandium_diameter_limited=3.5*cm;//3.5*cm;5*cm;
G4double Scandium_height_limited=30*cm;//30*cm;
//G4double Pb_radius = fSource_radius + 5.0*cm ;


G4double NeutronFilter_length = fMultiplierLeadHeightRear+fMultiplierLeadHeightFront+fModeratorAluminumHeight+fModeratorTitaniumHeight+fPolyHeight;


//G4double Water_rear_side = 20.0*cm ;
G4double Water_rear_side = 55.0*cm ;
//G4double Water_x = 200.0*cm;
G4double Water_x = 240.0*cm;
G4double Water_y = NeutronFilter_length+Water_rear_side;
//G4double Water_z = 200.0*cm;
G4double Water_z = 232.0*cm;

//G4double DT_Ti_T_location = 200.0*mm;//207.5*mm
G4double DT_Ti_T_location = fMultiplierLeadRadius;//207.5*mm
G4double Insulation_Thickness = 0*mm;//5*mm


G4double Water_cylindercal_can_radius = 152.7175*cm;
//G4double Water_cylindercal_can_radius_x = 120*cm;
G4double Water_cylindercal_can_radius_x = 20*cm+152.7175*cm;//152.7175*cm;
//G4double Water_cylindercal_can_radius_x = 152.7175*cm;
G4double Water_cylindercal_can_height = 114.3*cm;//115.8875*cm;
G4double ConcreteSupport_height = 90.47*cm; //80cm  90.0*cm


G4double Poly_a = 40.0*cm;
G4double hole_length = NeutronFilter_length-(fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)-fModeratorAluminumHeight-fModeratorTitaniumHeight;
//G4double hole_length = NeutronFilter_length-(fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)-fModeratorAluminumHeight-fModeratorTitaniumHeight;
//G4double colimator_length=26.0*cm;
//G4double colimator_length=30.0*cm;
G4double colimator_length=35.0*cm;

G4double Side_shield_thickness=20.0*cm;

G4double Titanium_shield_height= 5*cm ;
G4double Manganese_shield_height= 10*cm;

G4double lab68_wall_thickness = 25.0*cm ;
//distance from the outer egdes
G4double lab68_wall_x = 6.654*m ;
G4double lab68_wall_y = 9.35063*m ;
G4double lab68_wall_z = 5.636*m ;

G4double Pump_chase_y = 2.9*m ;

G4double lab68_frontdoor_glass_height = 2.9*m;
G4double lab68_frontdoor_glass_width = 2.2*m;

G4double lab68_frontdoor_wood_height = 2.3*m;
G4double lab68_frontdoor_wood_width = 1.5*m;

G4double lab68_glasswindow_height = 1.08*m;
G4double lab68_glasswindow_width = 0.57*m;

G4double lab68_reardoor_height = 2.3*m;
G4double lab68_reardoor_width = 0.91*m;

G4double lab68_frontdoor_x_coordinate = lab68_wall_x/2 -lab68_frontdoor_glass_width/2.0-1.2*m;
G4double lab68_reardoor_x_coordinate = -lab68_wall_x/2.0 +lab68_reardoor_width/2.0+2.613*m;

G4ThreeVector position_of_origin = {2.721*m, -2.703*m, 1.4547*m}; //with repect to the outer upper left corner of the room(Doug's corner)

G4ThreeVector xyposition_of_origin = {2.721*m, -2.703*m, 0};

G4double Phantom_Radius=0.4*m;
G4double Phantom_Height=2.0*m;
//G4double Phantom_Size=0.25*m;
G4double Phantom_Size=0.25*m/2.0;
G4double Li6F_thickness=1.0*cm;

//not needed

//Fridge
G4double SeventyKShield_Width = 0.2*cm;
G4double SeventyKShield_Radius = 18.95*cm;
G4double SeventyKShield_Height = 1.28*m;

G4double OVCShield_Width = 0.4*cm;
G4double OVCShield_Radius = 21.1*cm;
G4double OVCShield_Height = 1.5*m;

G4double FourKShield_Width = 0.2*cm;
G4double FourKShield_Radius = 17.2*cm;
G4double FourKShield_Height = 1.048*m;

G4double OneKShield_Width = 0.2*cm;
G4double OneKShield_Radius = 15.65*cm;
G4double OneKShield_Height = 0.881*m;

//G4double DilutionUnit_Radius = 10.0*cm;
G4double DilutionUnit_Radius = 3.0*cm;
G4double DilutionUnit_Height = 5.0*cm;

G4double DilutionChamber_Radius = DilutionUnit_Radius;//10.0*cm
G4double DilutionChamber_Height = DilutionUnit_Height + 5.3*cm;//15.3*cm
G4double DilutionChamber_Width = 2.0*mm;
G4double DilutionChamber_bottomplate_thick = 5*mm;
G4double DilutionChamber_upperplate_thick = 3*mm;

G4double SeventyKPlate_Radius = 20.0*cm;
G4double FourKPlate_Radius = 18.3*cm;
G4double OneKPlate_Radius = 16.7*cm;
G4double ColdPlate1_Radius = 15.0*cm;
G4double ColdPlate2_Radius = 15.0*cm;
G4double MixingPlate_Radius = 15.0*cm;

G4double SeventyKPlate_Thickness = 0.4*cm;
G4double FourKPlate_Thickness  = 0.4*cm;
G4double OneKPlate_Thickness  = 0.4*cm;
G4double ColdPlate1_Thickness  = 0.4*cm;
G4double ColdPlate2_Thickness  = 0.4*cm;
G4double MixingPlate_Thickness  = 0.5*cm;

G4double OVC_z = 10.3*cm;
G4double SeventyKPlate_z = 20.3*cm+ FourKPlate_Thickness/2.0 + SeventyKPlate_Thickness/2.0;
G4double FourKPlate_z  = 14.1*cm+ OneKPlate_Thickness/2.0 + FourKPlate_Thickness/2.0;
G4double OneKPlate_z  = 9.4*cm + ColdPlate1_Thickness/2.0 + OneKPlate_Thickness/2.0;
G4double ColdPlate1_z  = 9.6*cm + ColdPlate1_Thickness/2.0+ ColdPlate2_Thickness/2.0;
G4double ColdPlate2_z  = 16*cm + MixingPlate_Thickness/2.0+ ColdPlate2_Thickness/2.0;
//G4double MixingPlate_z  = 10.4*cm + MixingPlate_Thickness/2;
G4double MixingPlate_z  = 21.7*cm + MixingPlate_Thickness/2;


///backing Detector
G4double zeroRadius = 0.*cm;
G4double startAngle = 0.*deg;
G4double spanningAngle = 360.*deg;


G4double Front_Moderator_Thickness=1.5*cm; //changes this
G4double Back_Moderator_Thickness=1.5*cm;
G4double Inner_Radius =30.0*cm;
G4double Radial_thickness=10.0*cm;//10.0*cm;
G4double Mid_Acrylic_thickness=2.5*cm;//includes the thickness of two EJ426 layer
G4double EJ426_thickness=0.25*2*mm;
G4double BoratedPoly_thickness = 5.0*cm; //15


G4double shieldHeight =  Front_Moderator_Thickness+Mid_Acrylic_thickness+Back_Moderator_Thickness;


//
// Rotations
//

  G4RotationMatrix* NO_ROT = new G4RotationMatrix;

  G4RotationMatrix* turnAlongX = new G4RotationMatrix;
  turnAlongX->rotateX(90*deg);

  G4RotationMatrix* turnAlongXY = new G4RotationMatrix;
  turnAlongXY->rotateZ(90*deg);
  turnAlongXY->rotateZ(-100*deg);

  G4RotationMatrix* turnAlong = new G4RotationMatrix;
  turnAlong->rotateZ(10*deg);
  //turnAlong->rotateY(10*deg);

  G4RotationMatrix* turnAlong190 = new G4RotationMatrix;
  turnAlong190->rotateZ(190*deg);

  G4RotationMatrix* turnAlongZ = new G4RotationMatrix;
  turnAlongZ->rotateZ(90*deg);
  turnAlongZ->rotateZ(-90*deg);



//
// GEOMETRY
//

  // Start with a  vacuum layer. This will be the mother volume

  G4VSolid* vacuum_solid =new G4Box("vacuum_solid", 150.0*m, 150.0*m, 150.0*m);
  //G4VSolid* vacuum_solid =new G4Box("vacuum_solid", 15.0*m, 15.0*m, 15.0*m);
  G4LogicalVolume* vacuum_solid_LV = new G4LogicalVolume(vacuum_solid, Vacuum, "vacuum_solid");
  G4VPhysicalVolume* vacuum_solid_PV = new G4PVPlacement(NO_ROT,G4ThreeVector{0.,0.,0.}, vacuum_solid_LV, "Vacuum_solid", 0, false, 0, fCheckOverlaps);
  vacuum_solid_LV->SetVisAttributes(G4VisAttributes::Invisible);

/*
  //Lab_68 include ceiling
  G4VSolid* Main_2_S = new G4Box("Main_2_solid", lab68_wall_x/2.0, lab68_wall_y/2.0 , lab68_wall_z/2.0);
  //G4VSolid* hole_2_S = new G4Box("hole_2_solid", (lab68_wall_x-2*lab68_wall_thickness)/2.0, (lab68_wall_y-2*lab68_wall_thickness)/2.0, (lab68_wall_z-2*lab68_wall_thickness)/2.0);
  G4VSolid* hole_2_S = new G4Box("hole_2_solid", (lab68_wall_x-lab68_wall_thickness)/2.0, (lab68_wall_y-2*lab68_wall_thickness)/2.0, (lab68_wall_z-2*lab68_wall_thickness)/2.0);
  G4SubtractionSolid* LabFloorWall_solid_S= new G4SubtractionSolid("LabFloorWall_solid", Main_2_S, hole_2_S, NO_ROT, G4ThreeVector(0.,0., 0.));
  //G4SubtractionSolid* Main_2a_S= new G4SubtractionSolid("Main_2a_solid", Main_2_S, hole_2_S, NO_ROT, G4ThreeVector(0.,0., 0.));
  G4LogicalVolume* LabFloorWall_solid_LV = new G4LogicalVolume(LabFloorWall_solid_S, Concrete, "LabFloorWall_solid");
  LabFloorWall_solid_PV = new G4PVPlacement(turnAlong, G4ThreeVector{lab68_wall_x/2.0,-lab68_wall_y/2.0,lab68_wall_z/2.0}-position_of_origin, LabFloorWall_solid_LV, "LabFloorWall", vacuum_solid_LV, false, 0, fCheckOverlaps);
  LabFloorWall_solid_LV->SetVisAttributes(G4VisAttributes(G4Colour::Grey()));



  //Lab donot include ceiling
  //G4VSolid* LabFloorExtended_solid_S=  new G4Box("LabFloorExtended_solid", 15.0*m, 15.0*m , 15.0*m);
  //G4LogicalVolume* LabFloorExtended_solid_LV = new G4LogicalVolume(LabFloorExtended_solid_S, Soil, "LabFloorExtended_solid");
  //LabFloorExtended_solid_PV = new G4PVPlacement(turnAlong, G4ThreeVector{lab68_wall_x/2.0,-lab68_wall_y/2.0,lab68_wall_z/2.0}-position_of_origin-G4ThreeVector(0., 0., lab68_wall_z/2.0+15.0*m), LabFloorExtended_solid_LV, "LabFloor_extended", vacuum_solid_LV, false, 0, fCheckOverlaps);
  //LabFloorExtended_solid_LV->SetVisAttributes(G4VisAttributes(G4Colour::Brown()));
  //LabFloorExtended_solid_LV->SetVisAttributes(G4VisAttributes::Invisible);

  G4VSolid* frontglassdoor_S = new G4Box("frontglassdoor_solid", lab68_frontdoor_glass_width/2.0, lab68_wall_thickness/2.0, lab68_frontdoor_glass_height/2.0);
  //G4SubtractionSolid* Main_2b_S= new G4SubtractionSolid("Main_2b_solid", Main_2a_S, frontdoor_S, NO_ROT, G4ThreeVector(lab68_frontdoor_x_coordinate ,-lab68_wall_y/2.0, -(lab68_wall_z-2*lab68_wall_thickness-lab68_frontdoor_glass_height)/2.0));
  G4LogicalVolume* frontglassdoor_LV = new G4LogicalVolume(frontglassdoor_S, Quartz, "frontglassdoor");
  frontglassdoor_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(lab68_frontdoor_x_coordinate ,-(lab68_wall_y-lab68_wall_thickness)/2.0, -(lab68_wall_z-2*lab68_wall_thickness-lab68_frontdoor_glass_height)/2.0), frontglassdoor_LV, "Front Glass Door", LabFloorWall_solid_LV, false, 0, fCheckOverlaps);
  frontglassdoor_LV->SetVisAttributes(G4VisAttributes(G4Colour::Cyan()));


  G4VSolid* frontdoor_S = new G4Box("frontdoor_solid", lab68_frontdoor_wood_width/2.0, lab68_wall_thickness/2.0, lab68_frontdoor_wood_height/2.0);
  //G4SubtractionSolid* Main_2b_S= new G4SubtractionSolid("Main_2b_solid", Main_2a_S, frontdoor_S, NO_ROT, G4ThreeVector(lab68_frontdoor_x_coordinate ,-lab68_wall_y/2.0, -(lab68_wall_z-2*lab68_wall_thickness-lab68_frontdoor_glass_height)/2.0));
  G4LogicalVolume* frontdoor_LV = new G4LogicalVolume(frontdoor_S, Wood, "frontdoor");
  frontdoor_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(lab68_frontdoor_glass_width/2.0-lab68_frontdoor_wood_width/2.0 ,0, -lab68_frontdoor_glass_height/2.0+lab68_frontdoor_wood_height/2.0), frontdoor_LV, "Front Wood Door", frontglassdoor_LV, false, 0, fCheckOverlaps);
  frontdoor_LV->SetVisAttributes(G4VisAttributes(G4Colour::Brown()));


  G4VSolid* glasswindow_S = new G4Box("glasswindow_solid", lab68_glasswindow_width/2.0, lab68_wall_thickness/2.0, lab68_glasswindow_height/2.0);
  //G4SubtractionSolid* Main_2b_S= new G4SubtractionSolid("Main_2b_solid", Main_2a_S, frontdoor_S, NO_ROT, G4ThreeVector(lab68_frontdoor_x_coordinate ,-lab68_wall_y/2.0, -(lab68_wall_z-2*lab68_wall_thickness-lab68_frontdoor_glass_height)/2.0));
  G4LogicalVolume* glasswindow_LV = new G4LogicalVolume(glasswindow_S, Quartz, "glasswindow");
  glasswindow_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(lab68_frontdoor_wood_width/2.0-0.16*m-lab68_glasswindow_width/2.0, 0, -lab68_frontdoor_wood_height/2.0+1.11*m+lab68_glasswindow_height/2.0), glasswindow_LV, "Front Glass Window", frontdoor_LV, false, 0, fCheckOverlaps);
  glasswindow_LV->SetVisAttributes(G4VisAttributes(G4Colour::Cyan()));


  G4VSolid* reardoor_S = new G4Box("reardoor_solid", lab68_reardoor_width/2.0, lab68_wall_thickness/2.0, lab68_reardoor_height/2.0);
  //G4SubtractionSolid* LabFloorWall_solid_S= new G4SubtractionSolid("LabFloorWall_solid", Main_2b_S, reardoor_S, NO_ROT, G4ThreeVector(lab68_reardoor_x_coordinate ,lab68_wall_y/2.0, -(lab68_wall_z-2*lab68_wall_thickness-lab68_reardoor_height)/2.0));
  G4LogicalVolume* reardoor_LV = new G4LogicalVolume(reardoor_S, Wood, "reardoor");
  reardoor_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(lab68_reardoor_x_coordinate ,(lab68_wall_y-lab68_wall_thickness)/2.0, -(lab68_wall_z-2*lab68_wall_thickness-lab68_reardoor_height)/2.0), reardoor_LV, "Rear Wooden Door", LabFloorWall_solid_LV, false, 0, fCheckOverlaps);
  reardoor_LV->SetVisAttributes(G4VisAttributes(G4Colour::Brown()));

  //Lab_69 include ceiling
  G4ThreeVector position_lab66 = G4ThreeVector{-lab68_wall_x/2.0,-lab68_wall_y/2.0,lab68_wall_z/2.0}-position_of_origin
                                  +G4ThreeVector{0.0,TMath::Sin(TMath::DegToRad() * 10)*lab68_wall_x,0.0};
  lab70FloorWall_solid_PV = new G4PVPlacement(turnAlong, position_lab66, LabFloorWall_solid_LV, "lab66FloorWall", vacuum_solid_LV, false, 0, fCheckOverlaps);

  //Pump_chase_y
  //Lab_67 include ceiling
  G4ThreeVector position_lab70 = G4ThreeVector{3*lab68_wall_x/2.0,-lab68_wall_y/2.0,lab68_wall_z/2.0}-position_of_origin
                                  +G4ThreeVector{0.0,-TMath::Sin(TMath::DegToRad() * 10)*lab68_wall_x,0.0};
  lab70FloorWall_solid_PV = new G4PVPlacement(turnAlong, position_lab70, LabFloorWall_solid_LV, "lab70FloorWall", vacuum_solid_LV, false, 0, fCheckOverlaps);


  //Lab_30 include ceiling
  G4ThreeVector position_lab30 = G4ThreeVector{lab68_wall_x/2.0,lab68_wall_y/2.0+Pump_chase_y,lab68_wall_z/2.0}-position_of_origin
                                  +G4ThreeVector{TMath::Sin(TMath::DegToRad() * 10)*(lab68_wall_y+Pump_chase_y),0.0,0.0};
  lab30FloorWall_solid_PV = new G4PVPlacement(turnAlong190, position_lab30, LabFloorWall_solid_LV, "lab30FloorWall", vacuum_solid_LV, false, 0, fCheckOverlaps);

  //Lab_30 include ceiling
  G4ThreeVector position_lab28 = G4ThreeVector{3*lab68_wall_x/2.0,lab68_wall_y/2.0+Pump_chase_y,lab68_wall_z/2.0}-position_of_origin
                                  +G4ThreeVector{TMath::Sin(TMath::DegToRad() * 10)*(lab68_wall_y+Pump_chase_y),-TMath::Sin(TMath::DegToRad() * 10)*lab68_wall_x,0.0};
  lab28FloorWall_solid_PV = new G4PVPlacement(turnAlong190, position_lab28, LabFloorWall_solid_LV, "lab28FloorWall", vacuum_solid_LV, false, 0, fCheckOverlaps);

  //Lab_32 include ceiling
  G4ThreeVector position_lab32 = G4ThreeVector{-lab68_wall_x/2.0,lab68_wall_y/2.0+Pump_chase_y,lab68_wall_z/2.0}-position_of_origin
                                  +G4ThreeVector{TMath::Sin(TMath::DegToRad() * 10)*(lab68_wall_y+Pump_chase_y),TMath::Sin(TMath::DegToRad() * 10)*lab68_wall_x,0.0};
  Lab32FloorWall_solid_PV = new G4PVPlacement(turnAlong190, position_lab32, LabFloorWall_solid_LV, "Lab32FloorWall", vacuum_solid_LV, false, 0, fCheckOverlaps);



  ////G4LogicalVolume* LabFloorWall_solid_LV = new G4LogicalVolume(LabFloorWall_solid_S, Concrete, "LabFloorWall_solid");
  //LabFloorWall_solid_PV = new G4PVPlacement(turnAlong, G4ThreeVector{lab68_wall_x/2.0,-lab68_wall_y/2.0,lab68_wall_z/2.0}-position_of_origin, LabFloorWall_solid_LV, "OutSpacer", vacuum_solid_LV, false, 0, fCheckOverlaps);
  //LabFloorWall_solid_LV->SetVisAttributes(G4VisAttributes(G4Colour::Grey()));
  ////LabFloorWall_solid_LV->SetVisAttributes(G4VisAttributes::Invisible);



  /////out_neutron box  delta/2.0
  G4VSolid* Main_3_S = new G4Box("Main_3_solid", (Water_x+delta)/2.0, (Water_y+20.0*cm+colimator_length+delta)/2.0 , (Water_z+delta)/2.0);
  G4VSolid* hole_3_S = new G4Box("hole_3_solid", Water_x/2.0, (Water_y+20.0*cm+colimator_length+ Li6F_thickness)/2.0, Water_z/2.0);
  G4SubtractionSolid* TestSurface_solid_S= new G4SubtractionSolid("TestSurface_solid", Main_3_S, hole_3_S, NO_ROT, G4ThreeVector(0.,0., 0.));
  G4LogicalVolume* TestSurface_solid_LV = new G4LogicalVolume(TestSurface_solid_S, Vacuum, "TestSurface_solid");
  //TestSurface_solid_PV = new G4PVPlacement(turnAlongZ, G4ThreeVector(0., (fFilterCellSpacing-colimator_length)+(colimator_length+Water_y+20.0*cm)/2.0, 0), TestSurface_solid_LV, "TestSurface", vacuum_solid_LV, false, 0, fCheckOverlaps);
  //TestSurface_solid_LV->SetVisAttributes(G4VisAttributes(G4Colour::Grey()));
  //TestSurface_solid_LV->SetVisAttributes(G4VisAttributes::Invisible);



  //TestSurface_solid_LV->SetVisAttributes(G4VisAttributes::Invisible);


*/
  //layer of air at the bottom of the filter
  G4VSolid* Main_S = new G4Box("Main_solid", Water_cylindercal_can_radius_x/2.0 , (Water_cylindercal_can_radius)/2.0 , (Water_cylindercal_can_height)/2.0);
  //G4VSolid* hole_S = new G4Tubs("hole_solid", zeroRadius,fMultiplierLeadRadius, NeutronFilter_length/2.0, startAngle, spanningAngle);
  G4VSolid* hole_S = new G4Box("hole_solid", fMultiplierLeadRadius,fMultiplierLeadRadius, NeutronFilter_length/2.0);
  G4SubtractionSolid* boratedwater_S= new G4SubtractionSolid("boratedwater", Main_S, hole_S, turnAlongX, G4ThreeVector(0., -Water_cylindercal_can_radius/2.0+NeutronFilter_length/2.0, -(Water_cylindercal_can_height)/2.0 + DT_Ti_T_location + Insulation_Thickness));
  //G4SubtractionSolid* SecondMain_S= new G4SubtractionSolid("Second", Main_S, hole_S, turnAlongX, G4ThreeVector(0., -Water_cylindercal_can_radius/2.0+NeutronFilter_length/2.0, -(Water_cylindercal_can_height)/2.0 + DT_Ti_T_location + Insulation_Thickness));
  //G4VSolid* Secondhole_S = new G4Tubs("Secondhole_solid", zeroRadius, (2*Insulation_Thickness+34*mm)/2.0, (Water_cylindercal_can_height)/2.0, startAngle, spanningAngle);
  //G4SubtractionSolid* boratedwater_S= new G4SubtractionSolid("boratedwater", SecondMain_S, Secondhole_S, NO_ROT, G4ThreeVector(0., -Water_cylindercal_can_radius/2.0+NeutronFilter_length+(2*Insulation_Thickness+34*mm)/2.0,0.0));

  //G4LogicalVolume* boratedwater_LV = new G4LogicalVolume(boratedwater_S, Vacuum, "boratedwater");
  //G4LogicalVolume* boratedwater_LV = new G4LogicalVolume(boratedwater_S, BoraxBoricAcidBuffer, "boratedwater");
  //G4LogicalVolume* boratedwater_LV = new G4LogicalVolume(boratedwater_S, Concrete, "boratedwater");
  //G4LogicalVolume* boratedwater_LV = new G4LogicalVolume(boratedwater_S, BaseConcrete, "boratedwater");
  //G4LogicalVolume* boratedwater_LV = new G4LogicalVolume(boratedwater_S, HDConcrete, "boratedwater");
  //G4LogicalVolume* boratedwater_LV = new G4LogicalVolume(boratedwater_S, Water, "boratedwater");
  //G4LogicalVolume* boratedwater_LV = new G4LogicalVolume(boratedwater_S, BoratedPoly, "boratedwater");
  G4LogicalVolume* boratedwater_LV = new G4LogicalVolume(boratedwater_S, Polyethylene, "boratedwater");
  boratedwater_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., fFilterCellSpacing+ Water_cylindercal_can_radius/2.0, (Water_cylindercal_can_height)/2.0 - DT_Ti_T_location - Insulation_Thickness), boratedwater_LV, "BoratedWater", vacuum_solid_LV, false, 0, fCheckOverlaps);
  ////boratedwater_PV = new G4PVPlacement(turnAlongZ, G4ThreeVector(0., fFilterCellSpacing+Water_y/2.0, 0), boratedwater_LV, "BoratedWater", vacuum_solid_LV, false, 0, fCheckOverlaps);
  boratedwater_LV->SetVisAttributes(G4VisAttributes(G4Colour::Cyan()));

  //Extra layer of borated poly on the Top
  G4double Up_BpolyThickness=30.0*cm;
  G4VSolid* Up_Bpoly_shield_S = new G4Box("Up_Bpoly_shield", Water_cylindercal_can_radius_x/2.0+Side_shield_thickness , (Water_cylindercal_can_radius)/2.0 ,(Up_BpolyThickness)/2.0);
  //G4LogicalVolume* Up_Bpoly_shield_LV = new G4LogicalVolume(Up_Bpoly_shield_S, Polyethylene, "Up_Bpoly_shield");
  G4LogicalVolume* Up_Bpoly_shield_LV = new G4LogicalVolume(Up_Bpoly_shield_S, BoratedPoly_15, "Up_Bpoly_shield");
  Up_Bpoly_shield_LV->SetVisAttributes(G4VisAttributes(G4Colour::Magenta()));
  Up_Bpoly_shield_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., fFilterCellSpacing+ Water_cylindercal_can_radius/2.0, (Water_cylindercal_can_height)/2.0 - DT_Ti_T_location - Insulation_Thickness+(Water_cylindercal_can_height)/2.0+(Up_BpolyThickness)/2.0), Up_Bpoly_shield_LV, "Up_Bpoly_shield_left", vacuum_solid_LV, false, 0, fCheckOverlaps);


  //Extra layer of borated poly on the sides of the tanks
  G4VSolid* Side_Bpoly_shield_S = new G4Box("Side_Bpoly_shield", Side_shield_thickness/2.0, (Water_cylindercal_can_radius)/2.0,(Water_cylindercal_can_height+ConcreteSupport_height)/2.0);
  //G4LogicalVolume* Side_Bpoly_shield_LV = new G4LogicalVolume(Side_Bpoly_shield_S, Polyethylene, "Side_Bpoly_shield");
  G4LogicalVolume* Side_Bpoly_shield_LV = new G4LogicalVolume(Side_Bpoly_shield_S, BoratedPoly_15, "Side_Bpoly_shield");
  //leftSide
  Left_Side_Bpoly_shield_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(Water_cylindercal_can_radius_x/2.0+Side_shield_thickness/2.0, fFilterCellSpacing+ Water_cylindercal_can_radius/2.0, (Water_cylindercal_can_height-ConcreteSupport_height)/2 - DT_Ti_T_location - Insulation_Thickness), Side_Bpoly_shield_LV, "Side_Bpoly_shield_left", vacuum_solid_LV, false, 0, fCheckOverlaps);

  ///rightside
  Right_Side_Bpoly_shield_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(-Water_cylindercal_can_radius_x/2.0-Side_shield_thickness/2.0, fFilterCellSpacing+ Water_cylindercal_can_radius/2.0, (Water_cylindercal_can_height-ConcreteSupport_height)/2 - DT_Ti_T_location - Insulation_Thickness), Side_Bpoly_shield_LV, "Side_Bpoly_shield_right", vacuum_solid_LV, false, 0, fCheckOverlaps);

  Side_Bpoly_shield_LV->SetVisAttributes(G4VisAttributes(G4Colour::Magenta()));


  //G4VSolid* Main_S_1 = new G4Box("Main_solid_1", Water_cylindercal_can_radius_x/2.0 , (Water_cylindercal_can_radius)/2.0 , (Water_cylindercal_can_height)/2.0);
  //G4VSolid* hole_S_1 = new G4Box("hole_solid_1", 1.5*fMultiplierLeadRadius , NeutronFilter_length/2.0 , (Water_cylindercal_can_height)/2.0);
  ////G4VSolid* hole_S_1 = new G4Tubs("hole_solid_1", zeroRadius,fMultiplierLeadRadius, NeutronFilter_length/2.0, startAngle, spanningAngle);
  //G4SubtractionSolid* Concrete_S= new G4SubtractionSolid("boratedwater_2", Main_S_1, hole_S_1, NO_ROT, G4ThreeVector(0., -Water_cylindercal_can_radius/2.0+NeutronFilter_length/2.0, 0.0));
  ////G4LogicalVolume* Concrete_LV = new G4LogicalVolume(Concrete_S, Vacuum, "Concrete_shielding");
  ////G4LogicalVolume* Concrete_LV = new G4LogicalVolume(Concrete_S, BoraxBoricAcidBuffer, "Concrete_shielding");
  //G4LogicalVolume* Concrete_LV = new G4LogicalVolume(Concrete_S, Concrete, "Concrete_shielding");
  ////G4LogicalVolume* Concrete_LV = new G4LogicalVolume(Concrete_S, BoratedPoly, "boratedwater");
  //new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0, 0), Concrete_LV, "Concrete", boratedwater_LV, false, 0, fCheckOverlaps);
  //Concrete_LV->SetVisAttributes(G4VisAttributes(G4Colour::Green()));

  //Insulation
  //G4VSolid* Insulation_S = new G4Tubs("Insulation", zeroRadius, (2*Insulation_Thickness+34*mm)/2.0, (Water_cylindercal_can_height)/2.0, startAngle, spanningAngle);
  //G4LogicalVolume* Insulation_LV = new G4LogicalVolume(Insulation_S, Polyethylene, "Insulation");
  //Insulation_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., fFilterCellSpacing+NeutronFilter_length+(2*Insulation_Thickness+34*mm)/2.0, (Water_cylindercal_can_height)/2.0 - DT_Ti_T_location - Insulation_Thickness), Insulation_LV, "Insulation", vacuum_solid_LV, false, 0, fCheckOverlaps);
  //Insulation_LV->SetVisAttributes(G4VisAttributes(G4Colour::Yellow()));



  G4double ExtraBoratedpoly_thickness =20*cm;
  //BPoly inside boarted water sheild
  G4VSolid* Main6_S = new G4Box("Main6_solid", Water_cylindercal_can_radius_x/2.0 , (ExtraBoratedpoly_thickness)/2.0 , (Water_cylindercal_can_height)/2.0);
  //G4VSolid* hole6_S = new G4Tubs("hole6_solid", zeroRadius,fMultiplierLeadRadius, (ExtraBoratedpoly_thickness)/2.0, startAngle, spanningAngle);
  G4VSolid* hole6_S = new G4Box("hole6_solid", fMultiplierLeadRadius,fMultiplierLeadRadius, (ExtraBoratedpoly_thickness)/2.0);
  G4SubtractionSolid* ExtraBoratedpoly_S= new G4SubtractionSolid("ExtraBoratedpoly", Main6_S, hole6_S, turnAlongX, G4ThreeVector(0., 0, -(Water_cylindercal_can_height)/2.0 + DT_Ti_T_location + Insulation_Thickness));
  ////G4LogicalVolume* ExtraBoratedpoly_LV = new G4LogicalVolume(ExtraBoratedpoly_S, Vacuum, "ExtraBoratedpoly");
  ////G4LogicalVolume* ExtraBoratedpoly_LV = new G4LogicalVolume(ExtraBoratedpoly_S, BoraxBoricAcidBuffer, "ExtraBoratedpoly");
  ////G4LogicalVolume* ExtraBoratedpoly_LV = new G4LogicalVolume(ExtraBoratedpoly_S, Concrete, "ExtraBoratedpoly");
  G4LogicalVolume* ExtraBoratedpoly_LV = new G4LogicalVolume(ExtraBoratedpoly_S, BoratedPoly, "ExtraBoratedpoly");
  ////G4LogicalVolume* ExtraBoratedpoly_LV = new G4LogicalVolume(ExtraBoratedpoly_S, BoratedPoly, "ExtraBoratedpoly");
  ////ExtraBoratedpoly_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0.,  Water_cylindercal_can_radius/2.0, (Water_cylindercal_can_height)/2.0 - DT_Ti_T_location - Insulation_Thickness), ExtraBoratedpoly_LV, "ExtraBoratedpoly", boratedwater_LV, false, 0, fCheckOverlaps);
  new G4PVPlacement(NO_ROT, G4ThreeVector(0.,  -Water_cylindercal_can_radius/2.0+ExtraBoratedpoly_thickness/2.0, 0 ), ExtraBoratedpoly_LV, "ExtraBoratedpoly", boratedwater_LV, false, 0, fCheckOverlaps);
  ExtraBoratedpoly_LV->SetVisAttributes(G4VisAttributes(G4Colour::Yellow()));



  //BPoly inside boarted water sheild
  G4double Concrete_can_x=( 120.0 + (fMultiplierLeadRadius/10 - 15.0)*2 )*cm;
  G4double Concrete_can_z=( 80.0 + (fMultiplierLeadRadius/10 - 15.0)*2 )*cm;
  //G4double Concrete_can_x= 120.0 *cm;
  //G4double Concrete_can_z= 90.0 *cm;
  G4double Concrete_can_x_thickness=30.0*cm;
  G4double Concrete_can_z_thickness=15.0*cm;//15.0*cm

  G4VSolid* Main70_S = new G4Box("Main70_solid", Concrete_can_x/2.0 , (Water_cylindercal_can_radius)/2.0-(ExtraBoratedpoly_thickness)/2.0 , (Concrete_can_z)/2.0);
  G4VSolid* hole70_S = new G4Box("hole70_solid", Concrete_can_x/2.0-Concrete_can_x_thickness , (Water_cylindercal_can_radius)/2.0-(ExtraBoratedpoly_thickness)/2.0 , (Concrete_can_z)/2.0-Concrete_can_z_thickness);
  G4SubtractionSolid* ShellConcrete_S= new G4SubtractionSolid("ShellBoratedpoly", Main70_S, hole70_S, NO_ROT, G4ThreeVector(0., 0, -15.0*cm));

  G4LogicalVolume* ShellConcrete_LV = new G4LogicalVolume(ShellConcrete_S, BaseConcrete, "ShellConcrete");
  //G4LogicalVolume* ShellConcrete_LV = new G4LogicalVolume(ShellConcrete_S, HDConcrete, "ShellConcrete");
  new G4PVPlacement(NO_ROT, G4ThreeVector(0, (ExtraBoratedpoly_thickness)/2.0, -Water_cylindercal_can_height/2.0+ (Concrete_can_z)/2.0), ShellConcrete_LV, "ShellConcrete", boratedwater_LV, false, 0, fCheckOverlaps);
  //ShellConcrete_LV->SetVisAttributes(G4VisAttributes(G4Colour::Magenta()));


  //G4VSolid* ConcreteSupport_S = new G4Box("ConcreteSupport", Water_cylindercal_can_radius_x/2.0 , (Water_cylindercal_can_radius)/2.0 , (ConcreteSupport_height)/2.0);
  G4VSolid* ConcreteSupport_S = new G4Box("ConcreteSupport", Concrete_can_x/2.0 , (Water_cylindercal_can_radius)/2.0-(ExtraBoratedpoly_thickness)/2.0 , (ConcreteSupport_height)/2.0);
  //G4LogicalVolume* ConcreteSupport_LV = new G4LogicalVolume(ConcreteSupport_S, HDConcrete , "ConcreteSupport");
  G4LogicalVolume* ConcreteSupport_LV = new G4LogicalVolume(ConcreteSupport_S, BaseConcrete , "ConcreteSupport");
  //G4LogicalVolume* ConcreteSupport_LV = new G4LogicalVolume(ConcreteSupport_S, Concrete, "ConcreteSupport");
  //G4LogicalVolume* ConcreteSupport_LV = new G4LogicalVolume(ConcreteSupport_S, BoraxBoricAcidBuffer, "ConcreteSupport");
  //G4LogicalVolume* ConcreteSupport_LV = new G4LogicalVolume(ConcreteSupport_S, Borated_Concrete, "ConcreteSupport");
  ConcreteSupport_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., fFilterCellSpacing+Water_cylindercal_can_radius/2.0+(ExtraBoratedpoly_thickness/2.0), -(DT_Ti_T_location+Insulation_Thickness)-ConcreteSupport_height/2.0), ConcreteSupport_LV, "ConcreteSupport", vacuum_solid_LV, false, 0, fCheckOverlaps);
  //ConcreteSupport_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., fFilterCellSpacing+Water_cylindercal_can_radius/2.0, -(DT_Ti_T_location+Insulation_Thickness)-ConcreteSupport_height/2.0), ConcreteSupport_LV, "ConcreteSupport", vacuum_solid_LV, false, 0, fCheckOverlaps);
  //ConcreteSupport_LV->SetVisAttributes(G4VisAttributes(G4Colour::Grey()));
  //ConcreteSupport_LV->SetVisAttributes(G4VisAttributes(G4Colour::Cyan()));


  //Poly in base concrete
  G4VSolid* Main71_S = new G4Box("Main71_solid", Water_cylindercal_can_radius_x/2.0 , (Water_cylindercal_can_radius)/2.0-(ExtraBoratedpoly_thickness)/2.0 , (ConcreteSupport_height)/2.0);
  //G4VSolid* Hole71_S = new G4Box("Hole71_solid", Concrete_can_x/2.0 , (Water_cylindercal_can_radius)/2.0-(ExtraBoratedpoly_thickness)/2.0 , (ConcreteSupport_height)/2.0);
  //G4SubtractionSolid* PolyAround_ConcreteSupport_S= new G4SubtractionSolid("PolyAround_ConcreteSupport_", Main71_S, Hole71_S, NO_ROT, G4ThreeVector(0., (ExtraBoratedpoly_thickness)/2.0, 0));
  G4VSolid* Hole71_S = new G4Box("Hole71_solid", Concrete_can_x/2.0 , (Water_cylindercal_can_radius)/2.0-(ExtraBoratedpoly_thickness)/2.0 , (ConcreteSupport_height)/2.0);
  G4SubtractionSolid* PolyAround_ConcreteSupport_S= new G4SubtractionSolid("PolyAround_ConcreteSupport_", Main71_S, Hole71_S, NO_ROT, G4ThreeVector(0.,0, 0));
  G4LogicalVolume* PolyAround_ConcreteSupport_LV = new G4LogicalVolume(PolyAround_ConcreteSupport_S,Polyethylene , "PolyAround_ConcreteSupport");
  //G4LogicalVolume* PolyAround_ConcreteSupport_LV = new G4LogicalVolume(PolyAround_ConcreteSupport_S, BoratedPoly , "PolyAround_ConcreteSupport");
  new G4PVPlacement(NO_ROT, G4ThreeVector(0., fFilterCellSpacing+Water_cylindercal_can_radius/2.0+(ExtraBoratedpoly_thickness/2.0), -(DT_Ti_T_location+Insulation_Thickness)-ConcreteSupport_height/2.0), PolyAround_ConcreteSupport_LV, "PolyAround_ConcreteSupport", vacuum_solid_LV, false, 0, fCheckOverlaps);
  //PolyAround_ConcreteSupport_LV->SetVisAttributes(G4VisAttributes(G4Colour::Magenta()));

  //borated Poly in front at the concrete
  G4VSolid* BoratedPolyInFrontConcrete_S = new G4Box("BoratedPolyInFrontConcrete", Water_cylindercal_can_radius_x/2.0 ,ExtraBoratedpoly_thickness/2.0 , (ConcreteSupport_height)/2.0);
  G4LogicalVolume* BoratedPolyInFrontConcrete_LV = new G4LogicalVolume(BoratedPolyInFrontConcrete_S, BoratedPoly , "BoratedPolyInFrontConcrete");
  new G4PVPlacement(NO_ROT, G4ThreeVector(0., fFilterCellSpacing+ExtraBoratedpoly_thickness/2.0, -(DT_Ti_T_location+Insulation_Thickness)-ConcreteSupport_height/2.0), BoratedPolyInFrontConcrete_LV, "BoratedPolyInFrontConcrete", vacuum_solid_LV, false, 0, fCheckOverlaps);
  BoratedPolyInFrontConcrete_LV->SetVisAttributes(G4VisAttributes(G4Colour::Yellow()));

  //Insulation but this is actually a surface to see the neutrons coming out of the concrete and borated water
  G4VSolid* Insulation_S = new G4Box("Insulation", Water_cylindercal_can_radius_x/2.0+ Side_shield_thickness +500.0*cm, delta/2.0, (Water_cylindercal_can_height+ConcreteSupport_height+600*cm)/2.);
  //G4VSolid* MainInsulation_S = new G4Box("MainInsulation", Water_cylindercal_can_radius_x/2.0+ Side_shield_thickness +30.0*cm+delta, (Water_cylindercal_can_radius+colimator_length)/2.0+delta, (Water_cylindercal_can_height+ConcreteSupport_height+Up_BpolyThickness)/2.0+delta);
  //G4VSolid* HoleInsulation_S = new G4Box("HoleInsulation", Water_cylindercal_can_radius_x/2.0+ Side_shield_thickness +30.0*cm, (Water_cylindercal_can_radius+colimator_length)/2.0, (Water_cylindercal_can_height+ConcreteSupport_height+Up_BpolyThickness)/2.0);
  //G4SubtractionSolid* Insulation_S= new G4SubtractionSolid("Insulation", MainInsulation_S, HoleInsulation_S, NO_ROT, G4ThreeVector(0., 0, 0));
  G4LogicalVolume* Insulation_LV = new G4LogicalVolume(Insulation_S, Vacuum, "Insulation");
  Insulation_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., fFilterCellSpacing-colimator_length-3*delta/2.0, (Water_cylindercal_can_height-ConcreteSupport_height+100*cm)/2 - DT_Ti_T_location - Insulation_Thickness), Insulation_LV, "Insulation", vacuum_solid_LV, false, 0, fCheckOverlaps);
  ////Insulation_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., fFilterCellSpacing+Water_cylindercal_can_radius/2.0-colimator_length/2.0, (Water_cylindercal_can_height-ConcreteSupport_height+Up_BpolyThickness)/2 - DT_Ti_T_location - Insulation_Thickness), Insulation_LV, "Insulation", vacuum_solid_LV, false, 0, fCheckOverlaps);
  Insulation_LV->SetVisAttributes(G4VisAttributes(G4Colour::Green()));




  // Poly need to change
  //G4VSolid* Main_1_S = new G4Box("Main_1_solid", Water_cylindercal_can_radius_x/2.0, (Water_cylindercal_can_height+ConcreteSupport_height)/2.,colimator_length/2.0);
  G4VSolid* Main_1_S = new G4Box("Main_1_solid", Water_cylindercal_can_radius_x/2.0+ Side_shield_thickness +30.0*cm, (Water_cylindercal_can_height+ConcreteSupport_height)/2.,colimator_length/2.0);  //G4VSolid* Main_1_S = new G4Tubs("Main_1_solid", zeroRadius,fMultiplierLeadRadius, colimator_length/2.0, startAngle, spanningAngle);
  G4VSolid* hole_1_S = new G4Tubs("hole_1_solid", 0 , Scandium_diameter_limited/2.0, colimator_length/2.0,startAngle, spanningAngle);
  //G4SubtractionSolid* Main_12_S= new G4SubtractionSolid("Main_12_solid", Main_1_S, hole_1_S, NO_ROT, G4ThreeVector(0, -Scandium_diameter_limited/2.0, 0));
  //G4SubtractionSolid* collimation_hole_S= new G4SubtractionSolid("collimation_hole_solid", Main_12_S, hole_1_S, NO_ROT, G4ThreeVector(0, Scandium_diameter_limited/2.0, 0));
    G4SubtractionSolid* collimation_hole_S= new G4SubtractionSolid("inner_BPoly_solid", Main_1_S, hole_1_S, NO_ROT, G4ThreeVector(0., (Water_cylindercal_can_height-ConcreteSupport_height)/2 - DT_Ti_T_location - Insulation_Thickness, 0));
  //G4VSolid* collimation_hole_S = new G4Tubs("collimation_hole", zeroRadius, Scandium_diameter_limited/2.0, hole_length/2.0, startAngle, spanningAngle);
  //G4LogicalVolume* collimation_hole_LV = new G4LogicalVolume(collimation_hole_S, BoratedPoly, "collimation_hole");
  G4LogicalVolume* collimation_hole_LV = new G4LogicalVolume(collimation_hole_S, BoratedPoly_15, "collimation_hole");
  //G4LogicalVolume* collimation_hole_LV = new G4LogicalVolume(collimation_hole_S, Polyethylene, "collimation_hole");
  //collimation_hole_PV = new G4PVPlacement(turnAlongX, G4ThreeVector(0., fFilterCellSpacing-colimator_length/2.0, 0), collimation_hole_LV, "collimation_hole", vacuum_solid_LV, false, 0, fCheckOverlaps);
  collimation_hole_PV = new G4PVPlacement(turnAlongX, G4ThreeVector(0., fFilterCellSpacing-colimator_length/2.0, (Water_cylindercal_can_height-ConcreteSupport_height)/2 - DT_Ti_T_location - Insulation_Thickness), collimation_hole_LV, "collimation_hole", vacuum_solid_LV, false, 0, fCheckOverlaps);
  collimation_hole_LV->SetVisAttributes(G4VisAttributes(G4Colour::Magenta()));


  //Water near the sides
  //G4VSolid* Main_1_S = new G4Box("Main_1_solid", Water_cylindercal_can_radius_x/2.0, (Water_cylindercal_can_height+ConcreteSupport_height)/2.,colimator_length/2.0);
  G4VSolid* Water_1_S = new G4Box("Water_1_solid", Water_cylindercal_can_radius_x/2.0+ Side_shield_thickness +30.0*cm, (Water_cylindercal_can_height+ConcreteSupport_height)/2., 2*colimator_length);
  G4VSolid* Waterhole_1_S = new G4Box("Waterhole_1_solid", Water_cylindercal_can_radius_x/2.0+ Side_shield_thickness, (Water_cylindercal_can_height+ConcreteSupport_height)/2., 2*colimator_length);
  G4SubtractionSolid* ExtraWater_hole_S= new G4SubtractionSolid("inner_BPoly_solid", Water_1_S, Waterhole_1_S, NO_ROT, G4ThreeVector(0.,0, 0));
  G4LogicalVolume* ExtraWater_hole_LV = new G4LogicalVolume(ExtraWater_hole_S, Water, "ExtraWater_hole");
  new G4PVPlacement(turnAlongX, G4ThreeVector(0., fFilterCellSpacing+2*colimator_length, (Water_cylindercal_can_height-ConcreteSupport_height)/2 - DT_Ti_T_location - Insulation_Thickness), ExtraWater_hole_LV, "ExtraWater", vacuum_solid_LV, false, 0, fCheckOverlaps);
  //ExtraWater_hole_LV->SetVisAttributes(G4VisAttributes(G4Colour::Cyan()));



  //moderator in made of of Borated Poly surrounds Sc
  //G4VSolid* MainShield_1_S = new G4Tubs("MainShield_1_solid", zeroRadius,fMultiplierLeadRadius, NeutronFilter_length/2.0, startAngle, spanningAngle);
  G4VSolid* MainShield_1_S = new G4Box("MainShield_1_solid", fMultiplierLeadRadius,fMultiplierLeadRadius, NeutronFilter_length/2.0);
  G4VSolid* holeShield_1_S = new G4Tubs("holeShield_1_solid", 0 , Scandium_diameter_limited/2.0, hole_length/2.0,startAngle, spanningAngle);
  G4SubtractionSolid* inner_BPoly_S= new G4SubtractionSolid("inner_BPoly_solid", MainShield_1_S, holeShield_1_S, NO_ROT, G4ThreeVector(0., 0, -NeutronFilter_length/2.0+hole_length/2.0));
  //G4VSolid* inner_BPoly_S= new G4Box("Main_1_solid", Poly_a/2.0 , Poly_a/2.0, NeutronFilter_length/2.0);
  //G4VSolid* inner_BPoly_S= new G4Tubs("Main_1_solid", zeroRadius,fMultiplierLeadRadius, NeutronFilter_length/2.0, startAngle, spanningAngle);
  //G4LogicalVolume *inner_BPoly_LV = new G4LogicalVolume(inner_BPoly_S, BoratedPoly,"inner_BPoly" );
  //G4LogicalVolume *inner_BPoly_LV = new G4LogicalVolume(inner_BPoly_S, Polyethylene,"inner_BPoly" );
  //G4LogicalVolume *inner_BPoly_LV = new G4LogicalVolume(inner_BPoly_S, BaseConcrete,"inner_BPoly" );
  G4LogicalVolume *inner_BPoly_LV = new G4LogicalVolume(inner_BPoly_S, BoratedPoly_15,"inner_BPoly" );
  inner_BPoly_PV = new G4PVPlacement( turnAlongX, G4ThreeVector(0., fFilterCellSpacing+NeutronFilter_length/2.0, 0.), inner_BPoly_LV, "inner_BPoly", vacuum_solid_LV, false, 0, fCheckOverlaps);
  inner_BPoly_LV->SetVisAttributes(G4VisAttributes(G4Colour::Yellow()));

  //concrete just aound the bpoly that surrounds the scandium
  //G4VSolid* PolyUnderFilter_S = new G4Box("PolyUnderFilter", (Concrete_can_x/2.0-30*cm) , (Water_cylindercal_can_radius)/2.0-(ExtraBoratedpoly_thickness)/2.0 , (15.0*cm)/2.0);
  //G4LogicalVolume* PolyUnderFilter_LV = new G4LogicalVolume(PolyUnderFilter_S, Polyethylene , "PolyUnderFilter");
  G4VSolid* MainConcreteBlock_S = new G4Box("MainConcreteBlock", fMultiplierLeadRadius,fMultiplierLeadRadius , (fPolyHeight-Titanium_shield_height-Manganese_shield_height)/2.0);
  G4VSolid* MainConcreteBlockHole_S = new G4Box("MainConcreteBlockHole", 12.0*cm, 12.0*cm , (fPolyHeight-Titanium_shield_height-Manganese_shield_height)/2.0);
  G4SubtractionSolid* ConcreteAroundSc_S= new G4SubtractionSolid("ConcreteAroundSc", MainConcreteBlock_S, MainConcreteBlockHole_S, NO_ROT, G4ThreeVector(0., 0, 0));
  G4LogicalVolume* ConcreteAroundSc_LV = new G4LogicalVolume(ConcreteAroundSc_S, BaseConcrete , "ConcreteAroundSc");
  new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0, NeutronFilter_length/2.0-(fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)-fModeratorAluminumHeight-fModeratorTitaniumHeight-Titanium_shield_height-Manganese_shield_height-(fPolyHeight-Titanium_shield_height-Manganese_shield_height)/2.0), ConcreteAroundSc_LV, "PolyUnderFilter", inner_BPoly_LV, false, 0, fCheckOverlaps);
  ConcreteAroundSc_LV->SetVisAttributes(G4VisAttributes(G4Colour::Cyan()));




  //extra shield layer of Ti
  G4VSolid* Titanium_shield_S_main = new G4Box("Titanium_Main", fModeratorAluminumRadius, fModeratorAluminumRadius,(Titanium_shield_height)/2.0);
  G4VSolid* Titanium_shield_S_hole = new G4Tubs("Titanium_Hole", zeroRadius, Scandium_diameter_limited/2.0,(Titanium_shield_height)/2.0, startAngle, spanningAngle);
  G4SubtractionSolid* Titanium_shield_S = new G4SubtractionSolid("Titanium_shield", Titanium_shield_S_main, Titanium_shield_S_hole , NO_ROT, G4ThreeVector(0., 0, 0));
  //G4VSolid* Titanium_shield_S = new G4Tubs("Titanium_shield", Scandium_diameter_limited/2.0, fModeratorAluminumRadius , (Titanium_shield_height)/2.0, startAngle, spanningAngle);
  G4LogicalVolume* Titanium_shield_LV = new G4LogicalVolume(Titanium_shield_S, Titanium, "Titanium_shield");
  Titanium_shield_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0,0,NeutronFilter_length/2.0-(fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)-fModeratorAluminumHeight-fModeratorTitaniumHeight-Titanium_shield_height/2.0), Titanium_shield_LV, "Ti_shield", inner_BPoly_LV, false, 0, fCheckOverlaps);
  Titanium_shield_LV->SetVisAttributes(G4VisAttributes(G4Colour::Green()));

  //extra shield layer of Mn
  G4VSolid* Manganese_shield_S_main = new G4Box("Maganese_Main", fModeratorAluminumRadius, fModeratorAluminumRadius,(Manganese_shield_height)/2.0);
  G4VSolid* Manganese_shield_S_hole = new G4Tubs("Maganese_Hole", zeroRadius, Scandium_diameter_limited/2.0,(Manganese_shield_height)/2.0, startAngle, spanningAngle);
  G4SubtractionSolid* Manganese_shield_S = new G4SubtractionSolid("Manganese_shield", Manganese_shield_S_main, Manganese_shield_S_hole, NO_ROT, G4ThreeVector(0., 0, 0));
  //G4VSolid* Manganese_shield_S = new G4Tubs("Manganese_shield", Scandium_diameter_limited/2.0, fModeratorAluminumRadius , (Manganese_shield_height)/2.0, startAngle, spanningAngle);
  G4LogicalVolume* Manganese_shield_LV = new G4LogicalVolume(Manganese_shield_S, Titanium, "Manganese_shield");
  //G4LogicalVolume* Manganese_shield_LV = new G4LogicalVolume(Manganese_shield_S, Manganese, "Manganese_shield");
  Manganese_shield_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0,0,NeutronFilter_length/2.0-(fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)-fModeratorAluminumHeight-fModeratorTitaniumHeight-Titanium_shield_height-Manganese_shield_height/2.0), Manganese_shield_LV, "Mn_shield", inner_BPoly_LV, false, 0, fCheckOverlaps);
  Manganese_shield_LV->SetVisAttributes(G4VisAttributes(G4Colour::Cyan()));



  //lead in the form of cylinder as outer shield
  //G4VSolid* multiplier_lead_S = new G4Tubs("multiplier_lead", zeroRadius, fMultiplierLeadRadius , (fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)/2.0, startAngle, spanningAngle);
  G4VSolid* multiplier_lead_S = new G4Box("multiplier_lead", fMultiplierLeadRadius, fMultiplierLeadRadius , (fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)/2.0);
  G4LogicalVolume* multiplier_lead_LV = new G4LogicalVolume(multiplier_lead_S, Lead, "multiplier_lead");
  multiplier_lead_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0.,NeutronFilter_length/2.0-(fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)/2.0), multiplier_lead_LV, "Pb_shield", inner_BPoly_LV, false, 0, fCheckOverlaps);
  multiplier_lead_LV->SetVisAttributes(G4VisAttributes(G4Colour::Blue()));


  //Fluental (Aluminum) as the first moderator
  //G4VSolid* moderator_aluminum_S = new G4Tubs("moderator_aluminum", zeroRadius, fModeratorAluminumRadius, (fModeratorAluminumHeight /2.0), startAngle, spanningAngle);
  G4VSolid* moderator_aluminum_S = new G4Box("moderator_aluminum", fModeratorAluminumRadius, fModeratorAluminumRadius, (fModeratorAluminumHeight /2.0));
  G4LogicalVolume* moderator_aluminum_LV = new G4LogicalVolume(moderator_aluminum_S, Fluental, "moderator_aluminum");
  moderator_aluminum_PV =new G4PVPlacement(NO_ROT, G4ThreeVector(0,0,NeutronFilter_length/2.0-(fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)-fModeratorAluminumHeight /2.0),moderator_aluminum_LV, "Fluental_Moderator", inner_BPoly_LV, false, 0, fCheckOverlaps);
  moderator_aluminum_LV->SetVisAttributes(G4VisAttributes(G4Colour::Grey()));

  //Titanium as a secondary moderator in the form of cylinder
  //G4VSolid* moderator_titanium_S = new G4Tubs( "moderator_titanium", zeroRadius, fModeratorTitaniumRadius,(fModeratorTitaniumHeight/2.0), startAngle, spanningAngle);
  G4VSolid* moderator_titanium_S = new G4Box( "moderator_titanium", fModeratorTitaniumRadius, fModeratorTitaniumRadius,(fModeratorTitaniumHeight/2.0));
  G4LogicalVolume* moderator_titanium_LV = new G4LogicalVolume( moderator_titanium_S, Titanium, "moderator_titanium" );//to check with fluental
  moderator_titanium_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,NeutronFilter_length/2.0-(fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)-fModeratorAluminumHeight-fModeratorTitaniumHeight/2.0),moderator_titanium_LV, "Moderator_titanium",inner_BPoly_LV, false, 0, fCheckOverlaps);
  moderator_titanium_LV->SetVisAttributes(G4VisAttributes(G4Colour::Green()));

  //Lead cylinder surrounding the Titanium and Fluental
  //G4VSolid* Lead_around_TiAndF_S = new G4Tubs("Lead Reflector", fModeratorAluminumRadius, fMultiplierLeadRadius,(fModeratorAluminumHeight+fModeratorTitaniumHeight)/2.0, startAngle, spanningAngle);
  G4VSolid* Lead_around_TiAndF_S_main = new G4Box("Lead Reflector", fMultiplierLeadRadius, fMultiplierLeadRadius,(fModeratorAluminumHeight+fModeratorTitaniumHeight+Titanium_shield_height+Manganese_shield_height)/2.0);
  G4VSolid* Lead_around_TiAndF_S_hole = new G4Box("Lead Reflector_hole", fModeratorAluminumRadius, fModeratorAluminumRadius,(fModeratorAluminumHeight+fModeratorTitaniumHeight+Titanium_shield_height+Manganese_shield_height)/2.0);
  G4SubtractionSolid* Lead_around_TiAndF_S= new G4SubtractionSolid("inner_BPoly_solid", Lead_around_TiAndF_S_main, Lead_around_TiAndF_S_hole, NO_ROT, G4ThreeVector(0., 0, 0));
  G4LogicalVolume* Lead_around_TiAndF_LV = new G4LogicalVolume(Lead_around_TiAndF_S, Lead, "reflector_Lead" );//to check with fluental
  //Lead_around_TiAndF_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,NeutronFilter_length/2.0-(fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)-(fModeratorAluminumHeight+fModeratorTitaniumHeight)/2.0),Lead_around_TiAndF_LV, "Reflector_lead",inner_BPoly_LV, false, 0, fCheckOverlaps);
  //Lead_around_TiAndF_LV->SetVisAttributes(G4VisAttributes(G4Colour::Blue()));

  //Scandium as a the final filter
  G4VSolid* filter_scandium_S = new G4Tubs("filter_scandium", zeroRadius,  Scandium_diameter_limited/2.0,(Scandium_height_limited/2.0), startAngle, spanningAngle);
  //G4LogicalVolume *filter_scandium_LV = new G4LogicalVolume(filter_scandium_S, Scandium,"filter_scandium" );
  G4LogicalVolume *filter_scandium_LV = new G4LogicalVolume(filter_scandium_S, BoratedPoly_15,"filter_scandium" );
  filter_scandium_PV = new G4PVPlacement( turnAlongX, G4ThreeVector(0,fFilterCellSpacing+NeutronFilter_length-(fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)-fModeratorAluminumHeight-fModeratorTitaniumHeight-Scandium_height_limited/2.0,0), filter_scandium_LV, "Filter_scandium",vacuum_solid_LV,false, 0, fCheckOverlaps);
  ////filter_scandium_PV = new G4PVPlacement( turnAlongX, G4ThreeVector(0, fFilterCellSpacing-colimator_length+Scandium_height_limited/2.0, Scandium_diameter_limited/2.0), filter_scandium_LV, "Filter_scandium",vacuum_solid_LV,false, 0, fCheckOverlaps);
  /////filter_scandium_2_PV = new G4PVPlacement( turnAlongX, G4ThreeVector(0, fFilterCellSpacing-colimator_length+Scandium_height_limited/2.0, -Scandium_diameter_limited/2.0), filter_scandium_LV, "Filter_scandium_2",vacuum_solid_LV,false, 0, fCheckOverlaps);
  filter_scandium_LV->SetVisAttributes(G4VisAttributes(G4Colour::Red()));





  //LiF Layer
  ////G4VSolid* shield_cap_iron_S = new G4Box("Shield_cap_iron", Poly_a/2.0 , Poly_a/2.0,(Li6F_thickness/2.0));
  //G4VSolid* shield_cap_iron_S = new G4Tubs("Shield_cap_iron", zeroRadius,fMultiplierLeadRadius,(Li6F_thickness/2.0), startAngle, spanningAngle);
  //G4LogicalVolume *shield_cap_iron_LV = new G4LogicalVolume(shield_cap_iron_S, Lithium6_Fluoride,"shield_cap_iron_S" );
  //shield_cap_iron_PV = new G4PVPlacement( turnAlongX, G4ThreeVector(0., fFilterCellSpacing-colimator_length-(Li6F_thickness/2.0), 0),shield_cap_iron_LV, "LiF_layer", vacuum_solid_LV, false, 0, fCheckOverlaps );
  //shield_cap_iron_LV->SetVisAttributes(G4VisAttributes(G4Colour::Red()));

  //At the center
  //G4VSolid* Test_CENTERPOINT_S = new G4Box("Test_CENTERPOINT_solid", Water_x/2.0, delta/2.0, Water_z/2.0);
  G4VSolid* Test_CENTERPOINT_S = new G4Tubs("Test_CENTERPOINT_solid", zeroRadius, fMultiplierLeadRadius, delta/2.0, startAngle, spanningAngle);
  G4LogicalVolume *Test_CENTERPOINT_LV = new G4LogicalVolume(Test_CENTERPOINT_S, Vacuum,"Test_CENTERPOINT" );
  //Test_CENTERPOINT_PV = new G4PVPlacement(turnAlongX, G4ThreeVector(0., 0., 0.), Test_CENTERPOINT_LV, "Test_CENTERPOINT", vacuum_solid_LV, false, 0, fCheckOverlaps);
  //Test_CENTERPOINT_LV->SetVisAttributes(G4VisAttributes(G4Colour::Yellow()));

  //G4ThreeVector Origin_DT=G4ThreeVector(0., fFilterCellSpacing+NeutronFilter_length/2.0, 0.)
  //                +G4ThreeVector(0., NeutronFilter_length/2.0-(fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)/2.0,0.);

  G4ThreeVector Origin_DT=G4ThreeVector(0., fFilterCellSpacing+NeutronFilter_length+(Insulation_Thickness+34.0*mm)/2.0, 0.);

  G4double assymetric_factor_positivey=Water_rear_side+fMultiplierLeadHeightRear;
  G4double assymetric_factor_negativey=NeutronFilter_length-fMultiplierLeadHeightRear;

  G4ThreeVector Phantom_Placement=  Origin_DT + G4ThreeVector(ftestx, ftesty, ftestz);
  //G4ThreeVector Phantom_Placement=  Origin_DT + G4ThreeVector(ftestx+Water_x/2.0, 0, ftestz);
  ////G4ThreeVector Phantom_Placement_2= Origin_DT + G4ThreeVector(-ftestx, -ftesty, 0);
  //G4ThreeVector Phantom_Placement_2= Origin_DT + G4ThreeVector(-ftestx-Water_x/2.0, 0, ftestz);
  ////G4ThreeVector Phantom_Placement_3= Origin_DT + G4ThreeVector(ftestx, -ftesty, 0);
  //G4ThreeVector Phantom_Placement_3= Origin_DT + G4ThreeVector(0, -ftesty-assymetric_factor_negativey, ftestz);
  ////G4ThreeVector Phantom_Placement_4= Origin_DT + G4ThreeVector(-ftestx, ftesty, 0);
  //G4ThreeVector Phantom_Placement_4= Origin_DT + G4ThreeVector(0, ftesty+assymetric_factor_positivey, ftestz);
  ////G4ThreeVector Phantom_Placement_5= G4ThreeVector(lab68_wall_x/2.0,-lab68_wall_y/2.0, 0) - xyposition_of_origin;
  //G4ThreeVector Phantom_Placement_5= Origin_DT + G4ThreeVector(ftestx+Water_x/2.0, ftesty+assymetric_factor_positivey, ftestz);
  //G4ThreeVector Phantom_Placement_6= Origin_DT + G4ThreeVector(-ftestx-Water_x/2.0, ftesty+assymetric_factor_positivey, ftestz);
  //G4ThreeVector Phantom_Placement_7= Origin_DT + G4ThreeVector(ftestx+Water_x/2.0, -ftesty-assymetric_factor_negativey, ftestz);
  //G4ThreeVector Phantom_Placement_8= Origin_DT + G4ThreeVector(-ftestx-Water_x/2.0, -ftesty-assymetric_factor_negativey, ftestz);

  // Poly need to change
  //G4VSolid* Phantom_S = new G4Tubs("Phantom", zeroRadius, Phantom_Radius/2.0, Phantom_Height/2.0, startAngle, spanningAngle);
  //G4VSolid* Phantom_S = new G4Box("Phantom",Phantom_Size/2.0, Phantom_Size/2.0, Phantom_Size/2.0-delta);
  G4VSolid* Phantom_S = new G4Sphere("Phantom", zeroRadius,Phantom_Size, startAngle, spanningAngle, startAngle, spanningAngle);
  //G4LogicalVolume* Phantom_LV = new G4LogicalVolume(Phantom_S, Air, "Phantom");
  //G4LogicalVolume* Phantom_LV = new G4LogicalVolume(Phantom_S, Soft_Tissue, "Phantom");
  G4LogicalVolume* Phantom_LV = new G4LogicalVolume(Phantom_S, Vacuum, "Phantom");
  //Phantom_PV = new G4PVPlacement(NO_ROT, Phantom_Placement, Phantom_LV, "Phantom", vacuum_solid_LV, false, 0, fCheckOverlaps);

  //Phantom2_PV = new G4PVPlacement(NO_ROT, Phantom_Placement_2, Phantom_LV, "Phantom2", vacuum_solid_LV, false, 0, fCheckOverlaps);

  //Phantom3_PV = new G4PVPlacement(NO_ROT, Phantom_Placement_3, Phantom_LV, "Phantom3", vacuum_solid_LV, false, 0, fCheckOverlaps);

  //Phantom4_PV = new G4PVPlacement(NO_ROT, Phantom_Placement_4, Phantom_LV, "Phantom4", vacuum_solid_LV, false, 0, fCheckOverlaps);

  ////Phantom5_PV = new G4PVPlacement(NO_ROT, Phantom_Placement_5, Phantom_LV, "Phantom5", vacuum_solid_LV, false, 0, fCheckOverlaps);

  //Phantom6_PV = new G4PVPlacement(NO_ROT, Phantom_Placement_6, Phantom_LV, "Phantom6", vacuum_solid_LV, false, 0, fCheckOverlaps);

  //Phantom7_PV = new G4PVPlacement(NO_ROT, Phantom_Placement_7, Phantom_LV, "Phantom7", vacuum_solid_LV, false, 0, fCheckOverlaps);

  //Phantom8_PV = new G4PVPlacement(NO_ROT, Phantom_Placement_8, Phantom_LV, "Phantom8", vacuum_solid_LV, false, 0, fCheckOverlaps);



  Phantom_LV->SetVisAttributes(G4VisAttributes(G4Colour::Green()));
  //Phantom_LV->SetVisAttributes(G4VisAttributes::Invisible);


  //Lab donot include ceiling
  G4double soil_width=2*m;
  //G4VSolid* LabFloorExtended_solid_S=  new G4Box("LabFloorExtended_solid", 25.0*m, 25.0*m , 15.0*m);
  G4VSolid* LabFloorExtended_solid_S=  new G4Box("LabFloorExtended_solid", 20.0*m, 20.0*m , soil_width/2.0);
  //G4SubtractionSolid* Main_2a_S= new G4SubtractionSolid("Main_2a_solid", Main_2_S, hole_2_S, NO_ROT, G4ThreeVector(0.,0., 0.));
  G4LogicalVolume* LabFloorExtended_solid_LV = new G4LogicalVolume(LabFloorExtended_solid_S, Soil, "LabFloorExtended_solid");
  ////G4LogicalVolume* LabFloorExtended_solid_LV = new G4LogicalVolume(LabFloorExtended_solid_S, Vacuum, "LabFloorExtended_solid");
  //LabFloorExtended_solid_PV = new G4PVPlacement(turnAlong, G4ThreeVector{lab68_wall_x/2.0,-lab68_wall_y/2.0,lab68_wall_z/2.0}-position_of_origin-G4ThreeVector(0., 0., lab68_wall_z/2.0+soil_width/2.0), LabFloorExtended_solid_LV, "LabFloor_extended", vacuum_solid_LV, false, 0, fCheckOverlaps);
  LabFloorExtended_solid_LV->SetVisAttributes(G4VisAttributes(G4Colour::Brown()));
  ///LabFloorExtended_solid_LV->SetVisAttributes(G4VisAttributes::Invisible);

  //DilutionUnit contains superfluid Helium
  //G4VSolid* DilutionUnit_S = new G4Tubs( "DilutionUnit", zeroRadius, DilutionUnit_Radius, (DilutionUnit_Height /2.0), startAngle, spanningAngle);
  //G4LogicalVolume *DilutionUnit_LV = new G4LogicalVolume( DilutionUnit_S, Helium, "DilutionUnit" );
  ////G4LogicalVolume *DilutionUnit_LV = new G4LogicalVolume( DilutionUnit_S, Germanium, "DilutionUnit" );
  //DilutionUnit_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,0),DilutionUnit_LV, "helium", vacuum_solid_LV, false, 0, fCheckOverlaps);
  //DilutionUnit_LV->SetVisAttributes(G4VisAttributes(G4Colour::Green()));


  //G4VSolid* Boundary_S=  new G4Box("Boundary", 0.3*m, 5.0*m , 5.0*m);
  //G4VSolid* Boundary_S = new G4Tubs("Boundary", zeroRadius, fMultiplierLeadRadius , 1.0*cm, startAngle, spanningAngle);
  //G4LogicalVolume* Boundary_LV = new G4LogicalVolume(Boundary_S, Soil, "Boundary");
  //G4LogicalVolume* Boundary_LV = new G4LogicalVolume(Boundary_S, Vacuum, "Boundary");
  //new G4PVPlacement(turnAlongX, G4ThreeVector(0, 0, 0), Boundary_LV, "LabFloor_extended", vacuum_solid_LV, false, 0, fCheckOverlaps);
  //Boundary_LV->SetVisAttributes(G4VisAttributes(G4Colour::Brown()));

  // Always return the physical World


  ///Lab Ends///////////
  ////////////////////////////******************///////////////////////////////////////////


  ////Fridge_Begins///////
  ///////////////////////////*******************///////////////////////////////////////////
  /*
  //DilutionUnit contains superfluid Helium
  G4VSolid* DilutionUnit_S = new G4Tubs( "DilutionUnit", zeroRadius, DilutionUnit_Radius, (DilutionUnit_Height /2.0), startAngle, spanningAngle);
  G4LogicalVolume *DilutionUnit_LV = new G4LogicalVolume( DilutionUnit_S, Helium, "DilutionUnit" );
  //G4LogicalVolume *DilutionUnit_LV = new G4LogicalVolume( DilutionUnit_S, Germanium, "DilutionUnit" );
  DilutionUnit_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,0),DilutionUnit_LV, "helium", vacuum_solid_LV, false, 0, fCheckOverlaps);
  DilutionUnit_LV->SetVisAttributes(G4VisAttributes(G4Colour::Green()));


  //Dilution Chamber that holds the superfluid Helium
  G4double nedges[7]=  {-DilutionUnit_Height /2.0-DilutionChamber_bottomplate_thick,
                           -(DilutionUnit_Height /2.0),-(DilutionUnit_Height /2.0),
                           0.0,
                           DilutionChamber_Height-DilutionUnit_Height/2.0, DilutionChamber_Height-DilutionUnit_Height/2.0,
                           DilutionChamber_Height-DilutionUnit_Height/2.0+DilutionChamber_upperplate_thick};
  G4double innerradius[7]= {0.0, 0.0, DilutionChamber_Radius ,DilutionChamber_Radius ,  DilutionChamber_Radius, 0.0, 0.0 };
  G4double outerradius[7]= {DilutionChamber_Radius+DilutionChamber_Width, DilutionChamber_Radius+DilutionChamber_Width, DilutionChamber_Radius+DilutionChamber_Width,
    DilutionChamber_Radius+DilutionChamber_Width, DilutionChamber_Radius+DilutionChamber_Width, DilutionChamber_Radius+DilutionChamber_Width
  , DilutionChamber_Radius+DilutionChamber_Width};

  G4ThreeVector position_DilutionChamber = G4ThreeVector(0, 0, 0);

  G4Polycone* DilutionChamber_S = new G4Polycone("DilutionChamber", startAngle, spanningAngle, 7, nedges, innerradius, outerradius);
  G4LogicalVolume*  DilutionChamber_LV= new G4LogicalVolume(DilutionChamber_S, Copper, "DilutionChamber");
  DilutionChamber_PV = new G4PVPlacement(NO_ROT, position_DilutionChamber , DilutionChamber_LV, "DilutionChamber", vacuum_solid_LV, false, 0, fCheckOverlaps);
  DilutionChamber_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));



  //MixingPlate
  G4VSolid* MixingPlate_S = new G4Tubs( "MixingPlate", zeroRadius, MixingPlate_Radius, (MixingPlate_Thickness /2.0), startAngle, spanningAngle);
  G4LogicalVolume *MixingPlate_LV = new G4LogicalVolume( MixingPlate_S, Copper, "MixingPlate" );
  MixingPlate_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0, 0, MixingPlate_z),MixingPlate_LV, "MixingPlate", vacuum_solid_LV, false, 0, fCheckOverlaps);
  MixingPlate_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));

  //ColdPlate2
  G4VSolid* ColdPlate2_S = new G4Tubs( "ColdPlate2", zeroRadius, ColdPlate2_Radius, (ColdPlate2_Thickness /2.0), startAngle, spanningAngle);
  G4LogicalVolume *ColdPlate2_LV = new G4LogicalVolume( ColdPlate2_S, Copper, "ColdPlate2" );
  ColdPlate2_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z),ColdPlate2_LV, "ColdPlate2", vacuum_solid_LV, false, 0, fCheckOverlaps);
  ColdPlate2_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));

  //ColdPlate1
  G4VSolid* ColdPlate1_S = new G4Tubs( "ColdPlate1", zeroRadius, ColdPlate1_Radius, (ColdPlate1_Thickness /2.0), startAngle, spanningAngle);
  G4LogicalVolume *ColdPlate1_LV = new G4LogicalVolume( ColdPlate1_S, Copper, "ColdPlate1" );
  ColdPlate1_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z),ColdPlate1_LV, "ColdPlate1", vacuum_solid_LV, false, 0, fCheckOverlaps);
  ColdPlate1_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));

  //OneKPlate
  G4VSolid* OneKPlate_S = new G4Tubs( "OneKPlate", zeroRadius, OneKPlate_Radius, (OneKPlate_Thickness /2.0), startAngle, spanningAngle);
  G4LogicalVolume *OneKPlate_LV = new G4LogicalVolume( OneKPlate_S, Copper, "OneKPlate" );
  OneKPlate_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z),OneKPlate_LV, "OneKPlate", vacuum_solid_LV, false, 0, fCheckOverlaps);
  OneKPlate_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));

  G4double z[4]=  {-OneKShield_Width, 0.0, 0.0, OneKShield_Height};
  G4double ri[4]= {0.0, 0.0, OneKShield_Radius ,  OneKShield_Radius };
  G4double ro[4]= {OneKShield_Radius+OneKShield_Width, OneKShield_Radius+OneKShield_Width, OneKShield_Radius+OneKShield_Width, OneKShield_Radius+OneKShield_Width};
  G4ThreeVector position_OneKShield = G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z) + G4ThreeVector(0, 0, -OneKPlate_Thickness/2-OneKShield_Height);

  G4Polycone* OneKShield_S = new G4Polycone("OneKShield", startAngle, spanningAngle, 4, z, ri, ro);
  G4LogicalVolume*  OneKShield_LV= new G4LogicalVolume(OneKShield_S, Copper, "OneKShield");
  //G4LogicalVolume*  OneKShield_LV= new G4LogicalVolume(OneKShield_S, Aluminum, "OneKShield");
  OneKShield_PV = new G4PVPlacement(NO_ROT, position_OneKShield , OneKShield_LV, "OneKShield", vacuum_solid_LV, false, 0, fCheckOverlaps);
  OneKShield_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));

  //FourKPlate
  G4VSolid* FourKPlate_S = new G4Tubs( "FourKPlate", zeroRadius, FourKPlate_Radius, (FourKPlate_Thickness/2.0), startAngle, spanningAngle);
  G4LogicalVolume *FourKPlate_LV = new G4LogicalVolume( FourKPlate_S, Copper, "FourKPlate" );
  FourKPlate_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z+FourKPlate_z),FourKPlate_LV, "FourKPlate", vacuum_solid_LV, false, 0, fCheckOverlaps);
  FourKPlate_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));


  G4double z1[4]=  {-FourKShield_Width, 0.0, 0.0, FourKShield_Height};
  G4double ri1[4]= {0.0, 0.0, FourKShield_Radius ,  FourKShield_Radius };
  G4double ro1[4]= {FourKShield_Radius+FourKShield_Width, FourKShield_Radius+FourKShield_Width, FourKShield_Radius+FourKShield_Width, FourKShield_Radius+FourKShield_Width};
  G4ThreeVector position_FourKShield = G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z+FourKPlate_z) + G4ThreeVector(0, 0, -FourKPlate_Thickness/2-FourKShield_Height);

  G4Polycone* FourKShield_S = new G4Polycone("FourKShield", startAngle, spanningAngle, 4, z1, ri1, ro1);
  G4LogicalVolume*  FourKShield_LV= new G4LogicalVolume(FourKShield_S, Copper, "FourKShield");
  //G4LogicalVolume*  FourKShield_LV= new G4LogicalVolume(FourKShield_S, Aluminum, "FourKShield");
  FourKShield_PV = new G4PVPlacement(NO_ROT, position_FourKShield , FourKShield_LV, "FourKShield", vacuum_solid_LV, false, 0, fCheckOverlaps);
  FourKShield_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));


  //SeventyKPlate
  G4VSolid* SeventyKPlate_S = new G4Tubs( "SeventyKPlate", zeroRadius, SeventyKPlate_Radius, (SeventyKPlate_Thickness /2.0), startAngle, spanningAngle);
  G4LogicalVolume *SeventyKPlate_LV = new G4LogicalVolume( SeventyKPlate_S, Copper, "SeventyKPlate" );
  SeventyKPlate_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z+FourKPlate_z+SeventyKPlate_z),SeventyKPlate_LV, "SeventyKPlate", vacuum_solid_LV, false, 0, fCheckOverlaps);
  SeventyKPlate_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));


  G4double z2[4]=  {-SeventyKShield_Width, 0.0, 0.0, SeventyKShield_Height};
  G4double ri2[4]= {0.0, 0.0, SeventyKShield_Radius ,  SeventyKShield_Radius };
  G4double ro2[4]= {SeventyKShield_Radius+SeventyKShield_Width, SeventyKShield_Radius+SeventyKShield_Width, SeventyKShield_Radius+SeventyKShield_Width, SeventyKShield_Radius+SeventyKShield_Width};
  G4ThreeVector position_SeventyKShield = G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z+FourKPlate_z+SeventyKPlate_z) + G4ThreeVector(0, 0, -SeventyKPlate_Thickness/2-SeventyKShield_Height);

  G4Polycone* SeventyKShield_S = new G4Polycone("SeventyKShield", startAngle, spanningAngle, 4, z2, ri2, ro2);
  G4LogicalVolume*  SeventyKShield_LV= new G4LogicalVolume(SeventyKShield_S, Copper, "SeventyKShield");
  //G4LogicalVolume*  SeventyKShield_LV= new G4LogicalVolume(SeventyKShield_S, Aluminum, "SeventyKShield");
  SeventyKShield_PV = new G4PVPlacement(NO_ROT, position_SeventyKShield , SeventyKShield_LV, "SeventyKShield", vacuum_solid_LV, false, 0, fCheckOverlaps);
  SeventyKShield_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));;


  //OVC
  G4double z3[4]=  {-OVCShield_Width, 0.0, 0.0, OVCShield_Height};
  G4double ri3[4]= {0.0, 0.0, OVCShield_Radius ,  OVCShield_Radius };
  G4double ro3[4]= {OVCShield_Radius+OVCShield_Width, OVCShield_Radius+OVCShield_Width, OVCShield_Radius+OVCShield_Width, OVCShield_Radius+OVCShield_Width};
  G4ThreeVector position_OVCShield = G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z+FourKPlate_z+SeventyKPlate_z+OVC_z) + G4ThreeVector(0, 0,-OVCShield_Height);

  G4Polycone* OVCShield_S = new G4Polycone("OVCShield", startAngle, spanningAngle, 4, z3, ri3, ro3);
  G4LogicalVolume*  OVCShield_LV= new G4LogicalVolume(OVCShield_S, Aluminum, "OVCShield");
  OVCShield_PV = new G4PVPlacement(NO_ROT, position_OVCShield , OVCShield_LV, "OVCShield", vacuum_solid_LV, false, 0, fCheckOverlaps);
  OVCShield_LV->SetVisAttributes(G4VisAttributes(G4Colour(G4Colour::Cyan())));
  OVCShield_LV->SetVisAttributes(G4VisAttributes::Invisible);

  ///////////////***********************////////////////////////
 ////***********Fridge Ends***********//////////////


 /////**********Backing Detector Array begins**********////////////
 /*
 //Second detector
 G4double second_detector_z =  70.0*cm;
//Front Polyethylene layer, front is in -ve z axis
G4VSolid* shielding_lead_S = new G4Tubs("shielding_lead", Inner_Radius, Inner_Radius+ Radial_thickness,(Front_Moderator_Thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume* shielding_lead_LV = new G4LogicalVolume(shielding_lead_S, Polyethylene, "shielding_lead_solid");
shielding_lead_PV = new G4PVPlacement(turnAlongX, G4ThreeVector(0., -(second_detector_z-(shieldHeight-Front_Moderator_Thickness)/2.0), 0.), shielding_lead_LV, "2ndTitanium_Reflector_A", vacuum_solid_LV, false, 0, fCheckOverlaps);


//Back Borated-Polyethylene layer, is in +ve z axis to capture the rest neutrons
//G4VSolid* moderator_iron_S = new G4Tubs( "moderator_iron", Inner_Radius, Inner_Radius+ Radial_thickness,(BoratedPoly_thickness/2.0), startAngle, spanningAngle);
//G4LogicalVolume *moderator_iron_LV = new G4LogicalVolume( moderator_iron_S, PolBor10pc, "moderator_iron" );
//moderator_iron_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,second_detector_z+(shieldHeight+BoratedPoly_thickness)/2.0),moderator_iron_LV, "Borated_Capturer", vacuum_solid_LV, false, 0, fCheckOverlaps);

//Back Polyethylene layer, back is in +ve z axis
G4VSolid* Iron_solid_S = new G4Tubs("Iron_solid", Inner_Radius, Inner_Radius+ Radial_thickness,(Back_Moderator_Thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume *Iron_solid_LV = new G4LogicalVolume(Iron_solid_S, Polyethylene,"Iron_solid" );
Iron_solid_PV = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(second_detector_z+(shieldHeight-Back_Moderator_Thickness)/2.0),0), Iron_solid_LV, "2nd_SiPM_A",vacuum_solid_LV,false, 0, fCheckOverlaps);

//Acrylic in the middle
G4VSolid* DT_solid_S = new G4Tubs("DT_solid", Inner_Radius, Inner_Radius+ Radial_thickness,(Mid_Acrylic_thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume *DT_solid_LV = new G4LogicalVolume(DT_solid_S, Acrylic,"DT_solid" );
DT_solid_PV = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(second_detector_z+(shieldHeight-2*Back_Moderator_Thickness-Mid_Acrylic_thickness)/2.0),0), DT_solid_LV, "2nd_Scintillator_A",  vacuum_solid_LV, false, 0, fCheckOverlaps);



//Front EJ426, placed in Acrylic as its Mother Volume, Front is -ve z axis
G4VSolid* filter_aluminum_S = new G4Tubs("filter_aluminum_solid", Inner_Radius, Inner_Radius+ Radial_thickness,(EJ426_thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume* filter_aluminum_LV = new G4LogicalVolume(filter_aluminum_S, EJ4265HD , "filter_aluminum_solid");
filter_aluminum_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(Mid_Acrylic_thickness-EJ426_thickness)/2.0), filter_aluminum_LV, "2nd_Leadlayer_A", DT_solid_LV, false, 0, fCheckOverlaps);


//Back EJ426, placed in Acrylic as its Mother Volume, Back is +ve z axis
G4VSolid* shield_cap_iron_S = new G4Tubs("Shield_cap_iron", Inner_Radius, Inner_Radius+ Radial_thickness,(EJ426_thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume *shield_cap_iron_LV = new G4LogicalVolume(shield_cap_iron_S, EJ4265HD,"shield_cap" );
shield_cap_iron_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(Mid_Acrylic_thickness-EJ426_thickness)/2.0), shield_cap_iron_LV, "2nd_FeCap_A", DT_solid_LV, false, 0, fCheckOverlaps );


//First detector, distance between the helium Cell and the Detector is given
G4double first_detector_z =  30.0*cm;//45.0*cm
shielding_lead_PV_2 = new G4PVPlacement(turnAlongX, G4ThreeVector(0., -(first_detector_z-(shieldHeight-Front_Moderator_Thickness)/2.0), 0.), shielding_lead_LV, "1stTitanium_Reflector_A", vacuum_solid_LV, false, 0, fCheckOverlaps);
Iron_solid_PV_2 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(first_detector_z+(shieldHeight-Back_Moderator_Thickness)/2.0),0), Iron_solid_LV, "1st_SiPM_A",vacuum_solid_LV,false, 0, fCheckOverlaps);

G4LogicalVolume *DT_solid_LV_2 = new G4LogicalVolume(DT_solid_S, Acrylic,"DT_solid" );
DT_solid_PV_2 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(first_detector_z+(shieldHeight-2*Back_Moderator_Thickness-Mid_Acrylic_thickness)/2.0),0), DT_solid_LV_2, "1st_Scintillator_A",  vacuum_solid_LV, false, 0, fCheckOverlaps);

filter_aluminum_PV_2 = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(Mid_Acrylic_thickness-EJ426_thickness)/2.0), filter_aluminum_LV, "1st_Leadlayer_A", DT_solid_LV_2, false, 0, fCheckOverlaps);
shield_cap_iron_PV_2 = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(Mid_Acrylic_thickness-EJ426_thickness)/2.0), shield_cap_iron_LV, "1st_FeCap_A", DT_solid_LV_2, false, 0, fCheckOverlaps );

//third detector, distance between the helium Cell and the Detector is given
G4double third_detector_z =  120.0*cm;
shielding_lead_PV_3 = new G4PVPlacement(turnAlongX, G4ThreeVector(0., -(third_detector_z-(shieldHeight-Front_Moderator_Thickness)/2.0), 0.), shielding_lead_LV, "3rdTitanium_Reflector_A", vacuum_solid_LV, false, 0, fCheckOverlaps);
Iron_solid_PV_3 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(third_detector_z+(shieldHeight-Back_Moderator_Thickness)/2.0),0), Iron_solid_LV, "3rd_SiPM_A",vacuum_solid_LV,false, 0, fCheckOverlaps);

G4LogicalVolume *DT_solid_LV_3 = new G4LogicalVolume(DT_solid_S, Acrylic,"DT_solid" );
DT_solid_PV_3 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(third_detector_z+(shieldHeight-2*Back_Moderator_Thickness-Mid_Acrylic_thickness)/2.0),0), DT_solid_LV_3, "3rd_Scintillator_A",  vacuum_solid_LV, false, 0, fCheckOverlaps);

filter_aluminum_PV_3 = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(Mid_Acrylic_thickness-EJ426_thickness)/2.0), filter_aluminum_LV, "3rd_Leadlayer_A", DT_solid_LV_3, false, 0, fCheckOverlaps);
shield_cap_iron_PV_3 = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(Mid_Acrylic_thickness-EJ426_thickness)/2.0), shield_cap_iron_LV, "3rd_FeCap_A", DT_solid_LV_3, false, 0, fCheckOverlaps );



//fourth Detector, distance between the helium Cell and the Detector is given


G4double fourth_detector_z = 150.0*cm+shieldHeight/2.0;
//G4double fourth_detector_z = 20.0*cm+shieldHeight/2.0;

//Front Polyethylene layer, front is in -ve z axis
G4VSolid* shielding_lead_S_1 = new G4Tubs("shielding_lead_1", Inner_Radius-10.0*cm, Inner_Radius+ Radial_thickness-10.0*cm,(Front_Moderator_Thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume* shielding_lead_LV_1 = new G4LogicalVolume(shielding_lead_S_1, Polyethylene, "shielding_lead_solid_1");
shielding_lead_PV_1 = new G4PVPlacement(turnAlongX, G4ThreeVector(0., -(fourth_detector_z-(shieldHeight-Front_Moderator_Thickness)/2.0), 0.), shielding_lead_LV_1, "4th_Titanium_Reflector_B", vacuum_solid_LV, false, 0, fCheckOverlaps);



//Back Polyethylene layer, back is in +ve z axis
G4VSolid* Iron_solid_S_1 = new G4Tubs("Iron_solid_1", Inner_Radius-10.0*cm, Inner_Radius+ Radial_thickness-10.0*cm,(Back_Moderator_Thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume *Iron_solid_LV_1 = new G4LogicalVolume(Iron_solid_S_1, Polyethylene,"Iron_solid_1" );
Iron_solid_PV_1= new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(fourth_detector_z+(shieldHeight-Back_Moderator_Thickness)/2.0),0), Iron_solid_LV_1, "4th_SiPM_B",vacuum_solid_LV,false, 0, fCheckOverlaps);

//Acrylic in the middle
G4VSolid* DT_solid_S_1 = new G4Tubs("DT_solid_1", Inner_Radius-10.0*cm, Inner_Radius+ Radial_thickness-10.0*cm,(Mid_Acrylic_thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume *DT_solid_LV_1 = new G4LogicalVolume(DT_solid_S_1, Acrylic,"DT_solid_1" );
DT_solid_PV_1 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(fourth_detector_z+(shieldHeight-2*Back_Moderator_Thickness-Mid_Acrylic_thickness)/2.0),0), DT_solid_LV_1, "4th_Scintillator_B",  vacuum_solid_LV, false, 0, fCheckOverlaps);



//Front EJ426, placed in Acrylic as its Mother Volume, Front is -ve z axis
G4VSolid* filter_aluminum_S_1 = new G4Tubs("filter_aluminum_solid_1", Inner_Radius-10.0*cm, Inner_Radius+ Radial_thickness-10.0*cm,(EJ426_thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume* filter_aluminum_LV_1 = new G4LogicalVolume(filter_aluminum_S_1, EJ4265HD , "filter_aluminum_solid_1");
filter_aluminum_PV_1 = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(Mid_Acrylic_thickness-EJ426_thickness)/2.0), filter_aluminum_LV_1, "4th_Leadlayer_B", DT_solid_LV_1, false, 0, fCheckOverlaps);


//Back EJ426, placed in Acrylic as its Mother Volume, Back is +ve z axis
G4VSolid* shield_cap_iron_S_1 = new G4Tubs("Shield_cap_iron_1", Inner_Radius-10.0*cm, Inner_Radius+ Radial_thickness-10.0*cm,(EJ426_thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume *shield_cap_iron_LV_1 = new G4LogicalVolume(shield_cap_iron_S_1, EJ4265HD,"shield_cap_1" );
shield_cap_iron_PV_1 = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(Mid_Acrylic_thickness-EJ426_thickness)/2.0), shield_cap_iron_LV_1, "4th_FeCap_B", DT_solid_LV_1, false, 0, fCheckOverlaps );

//fifth Detector, distance between the helium Cell and the Detector is given
G4double fifth_detector_z = 250.0*cm+shieldHeight/2.0;

shielding_lead_PV_1_5 = new G4PVPlacement(turnAlongX, G4ThreeVector(0., -(fifth_detector_z-(shieldHeight-Front_Moderator_Thickness)/2.0), 0.), shielding_lead_LV_1, "5th_Titanium_Reflector_B", vacuum_solid_LV, false, 0, fCheckOverlaps);
Iron_solid_PV_1_5= new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(fifth_detector_z+(shieldHeight-Back_Moderator_Thickness)/2.0),0), Iron_solid_LV_1, "5th_SiPM_B",vacuum_solid_LV,false, 0, fCheckOverlaps);
G4LogicalVolume *DT_solid_LV_1_5 = new G4LogicalVolume(DT_solid_S_1, Acrylic,"DT_solid_1" );
DT_solid_PV_1_5 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(fifth_detector_z+(shieldHeight-2*Back_Moderator_Thickness-Mid_Acrylic_thickness)/2.0),0), DT_solid_LV_1_5, "5th_Scintillator_B",  vacuum_solid_LV, false, 0, fCheckOverlaps);
filter_aluminum_PV_1_5 = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(Mid_Acrylic_thickness-EJ426_thickness)/2.0), filter_aluminum_LV_1, "5th_Leadlayer_B", DT_solid_LV_1_5, false, 0, fCheckOverlaps);
shield_cap_iron_PV_1_5 = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(Mid_Acrylic_thickness-EJ426_thickness)/2.0), shield_cap_iron_LV_1, "5th_FeCap_B", DT_solid_LV_1_5, false, 0, fCheckOverlaps );

//sixth Detector, distance between the helium Cell and the Detector is given
G4double sixth_detector_z = 400.0*cm+shieldHeight/2.0;

shielding_lead_PV_1_6 = new G4PVPlacement(turnAlongX, G4ThreeVector(0., -(sixth_detector_z-(shieldHeight-Front_Moderator_Thickness)/2.0), 0.), shielding_lead_LV_1, "6th_Titanium_Reflector_B", vacuum_solid_LV, false, 0, fCheckOverlaps);
Iron_solid_PV_1_6= new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(sixth_detector_z+(shieldHeight-Back_Moderator_Thickness)/2.0),0), Iron_solid_LV_1, "6th_SiPM_B",vacuum_solid_LV,false, 0, fCheckOverlaps);
G4LogicalVolume *DT_solid_LV_1_6 = new G4LogicalVolume(DT_solid_S_1, Acrylic,"DT_solid_1" );
DT_solid_PV_1_6 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(sixth_detector_z+(shieldHeight-2*Back_Moderator_Thickness-Mid_Acrylic_thickness)/2.0),0), DT_solid_LV_1_6, "6th_Scintillator_B",  vacuum_solid_LV, false, 0, fCheckOverlaps);
filter_aluminum_PV_1_6 = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(Mid_Acrylic_thickness-EJ426_thickness)/2.0), filter_aluminum_LV_1, "6th_Leadlayer_B", DT_solid_LV_1_6, false, 0, fCheckOverlaps);
shield_cap_iron_PV_1_6 = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(Mid_Acrylic_thickness-EJ426_thickness)/2.0), shield_cap_iron_LV_1, "6th_FeCap_B", DT_solid_LV_1_6, false, 0, fCheckOverlaps );

//////**********Backing Detector array ends***********////////////////


  return vacuum_solid_PV;
}


//method SetPolyHeight is defined here
void IronFilterDetectorConstruction::SetPolyHeight(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfPolyHeight: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fPolyHeight = ival;
}


//method SetFilterSpacing is defined here
void IronFilterDetectorConstruction::SetFilterSpacing(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfFilterSpacing: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fFilterSpacing = ival;
}

//method SetMultiplierLeadRadius is defined here
void IronFilterDetectorConstruction::SetMultiplierLeadRadius(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfMultiplierLeadRadius: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fMultiplierLeadRadius = ival;
}
//method SetModeratorAluminumRadius is defined here
void IronFilterDetectorConstruction::SetModeratorAluminumRadius(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfModeratorAluminumRadius: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fModeratorAluminumRadius = ival;
}
//method SetMultiplierLeadHeightRear is defined here
void IronFilterDetectorConstruction::SetMultiplierLeadHeightRear(G4double ival)
{
  if (ival < 0)
    { G4cout << "\n --->warning from SetfMultiplierLeadHeightRear: "
             << ival << " must be at least 0. Command refused" << G4endl;
      return;
    }
  fMultiplierLeadHeightRear = ival;
}
//method SetFilterCellSpacing is defined here
void IronFilterDetectorConstruction::SetFilterCellSpacing(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfFilterCellSpacing: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fFilterCellSpacing = ival;
}
//method SetModeratorTitaniumHeight is defined here
void IronFilterDetectorConstruction::SetModeratorTitaniumHeight(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfModeratorTitaniumHeight: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fModeratorTitaniumHeight = ival;
}
//method SetModeratorAluminumHeight is defined here
void IronFilterDetectorConstruction::SetModeratorAluminumHeight(G4double ival)
{
  if (ival < 1)
   { G4cout << "\n --->warning from SetfModeratorAluminumHeight: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fModeratorAluminumHeight = ival;
}
//method SetMultiplierLeadHeightFront is defined here
void IronFilterDetectorConstruction::SetMultiplierLeadHeightFront(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfMultiplierLeadHeightFront: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fMultiplierLeadHeightFront = ival;
}
//method SetModeratorTitaniumRadius is defined here
void IronFilterDetectorConstruction::SetModeratorTitaniumRadius(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfModeratorTitaniumRadius: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fModeratorTitaniumRadius = ival;
}

void IronFilterDetectorConstruction::SetTestX(G4double ival)
{
  ftestx = ival;
}

void IronFilterDetectorConstruction::SetTestY(G4double ival)
{
  ftesty = ival;
}

void IronFilterDetectorConstruction::SetTestZ(G4double ival)
{
  ftestz = ival;
}
