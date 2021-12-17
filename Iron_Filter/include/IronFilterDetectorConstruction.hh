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
// $Id: IronFilterDetectorConstruction.hh $
//
/// \file IronFilterDetectorConstruction.hh
/// \brief Definition of the IronFilterDetectorConstruction class

#ifndef IronFilterDetectorConstruction_h
#define IronFilterDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4RotationMatrix.hh"

class G4VPhysicalVolume;
//for messenger
class IronFilterDetectorMessenger;
//
class IronFilterDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    IronFilterDetectorConstruction();
    virtual ~IronFilterDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();

    //for messenger
    void SetPolyHeight   (G4double);
    void SetFilterSpacing   (G4double);
    void SetMultiplierLeadRadius   (G4double);
    void SetModeratorAluminumRadius   (G4double);
    void SetMultiplierLeadHeightRear   (G4double);
    void SetFilterCellSpacing   (G4double);
    void SetModeratorTitaniumHeight   (G4double);
    void SetModeratorAluminumHeight   (G4double);
    void SetMultiplierLeadHeightFront   (G4double);
    void SetModeratorTitaniumRadius   (G4double);
    void SetTestX   (G4double);
    void SetTestY   (G4double);
    void SetTestZ   (G4double);
    ///


    // get methods
    //
    const G4VPhysicalVolume* GetboratedwaterPV() const;
    const G4VPhysicalVolume* GetcollimationholePV() const;
    const G4VPhysicalVolume* GetConcreteSupportPV() const;
    const G4VPhysicalVolume* GetInsulationPV() const;
    //const G4VPhysicalVolume* GetPhantomPV() const;
    //const G4VPhysicalVolume* GetPhantom2PV() const;
    //const G4VPhysicalVolume* GetPhantom3PV() const;
    //const G4VPhysicalVolume* GetPhantom4PV() const;
    ////const G4VPhysicalVolume* GetPhantom5PV() const;
    //const G4VPhysicalVolume* GetPhantom6PV() const;
    //const G4VPhysicalVolume* GetPhantom7PV() const;
    //const G4VPhysicalVolume* GetPhantom8PV() const;
    const G4VPhysicalVolume* GetLabFloorWallsolidPV() const;
    const G4VPhysicalVolume* Getlab70FloorWallsolidPV() const;
    const G4VPhysicalVolume* GetLab32FloorWallsolidPV() const;
    const G4VPhysicalVolume* Getlab66FloorWallsolidPV() const;
    const G4VPhysicalVolume* Getlab30FloorWallsolidPV() const;
    const G4VPhysicalVolume* Getlab28FloorWallsolidPV() const;
    const G4VPhysicalVolume* GetLabFloorExtendedsolidPV() const;
    const G4VPhysicalVolume* GetfrontglassdoorPV() const;
    const G4VPhysicalVolume* GetfrontdoorPV() const;
    const G4VPhysicalVolume* GetglasswindowPV() const;
    const G4VPhysicalVolume* GetreardoorPV() const;
    const G4VPhysicalVolume* GetTestSurfacesolidPV() const;
    const G4VPhysicalVolume* GetmultiplierleadPV() const;
    const G4VPhysicalVolume* GetmoderatoraluminumPV() const;
    //const G4VPhysicalVolume* GetshieldcapironPV() const;
    const G4VPhysicalVolume* GetmoderatortitaniumPV() const;
    const G4VPhysicalVolume* GetLeadaroundTiAndFPV() const;
    const G4VPhysicalVolume* GetinnerBPolyPV() const;
    //const G4VPhysicalVolume* GetTestCENTERPOINTPV() const;
    const G4VPhysicalVolume* GetfilterscandiumPV() const; //Test_LEFTSIDE
    const G4VPhysicalVolume* Getfilterscandium2PV() const;
    //const G4VPhysicalVolume* GetLiFsolidPV() const;


    //1st Detector type A
    const G4VPhysicalVolume* GetshieldingleadPV2() const;
    const G4VPhysicalVolume* GetfilteraluminumPV2() const;
    //const G4VPhysicalVolume* GetmoderatorironPV2() const;
    const G4VPhysicalVolume* GetshieldcapironPV2() const;
    const G4VPhysicalVolume* GetinnershieldPV2() const;
    const G4VPhysicalVolume* GetDTsolidPV2() const;
    const G4VPhysicalVolume* GetIronsolidPV2() const;


    //2nd Detector type A
    const G4VPhysicalVolume* GetshieldingleadPV() const;
    const G4VPhysicalVolume* GetfilteraluminumPV() const;
    //const G4VPhysicalVolume* GetmoderatorironPV() const;
    const G4VPhysicalVolume* GetshieldcapironPV() const;
    const G4VPhysicalVolume* GetinnershieldPV() const;
    const G4VPhysicalVolume* GetDTsolidPV() const;
    const G4VPhysicalVolume* GetIronsolidPV() const;

    //3rd Detector type A
    const G4VPhysicalVolume* GetshieldingleadPV3() const;
    const G4VPhysicalVolume* GetfilteraluminumPV3() const;
    //const G4VPhysicalVolume* GetmoderatorironPV3() const;
    const G4VPhysicalVolume* GetshieldcapironPV3() const;
    const G4VPhysicalVolume* GetinnershieldPV3() const;
    const G4VPhysicalVolume* GetDTsolidPV3() const;
    const G4VPhysicalVolume* GetIronsolidPV3() const;

    //4th Detector type B
    const G4VPhysicalVolume* GetshieldingleadPV1() const;
    const G4VPhysicalVolume* GetfilteraluminumPV1() const;
    //const G4VPhysicalVolume* GetmoderatorironPV1() const;
    const G4VPhysicalVolume* GetshieldcapironPV1() const;
    const G4VPhysicalVolume* GetDTsolidPV1() const;
    const G4VPhysicalVolume* GetIronsolidPV1() const;

    //5th Detector type B
    const G4VPhysicalVolume* GetshieldingleadPV1_5() const;
    const G4VPhysicalVolume* GetfilteraluminumPV1_5() const;
    //const G4VPhysicalVolume* GetmoderatorironPV1_5() const;
    const G4VPhysicalVolume* GetshieldcapironPV1_5() const;
    const G4VPhysicalVolume* GetDTsolidPV1_5() const;
    const G4VPhysicalVolume* GetIronsolidPV1_5() const;

    //6th Detector type B
    const G4VPhysicalVolume* GetshieldingleadPV1_6() const;
    const G4VPhysicalVolume* GetfilteraluminumPV1_6() const;
    //const G4VPhysicalVolume* GetmoderatorironPV1_6() const;
    const G4VPhysicalVolume* GetshieldcapironPV1_6() const;
    const G4VPhysicalVolume* GetDTsolidPV1_6() const;
    const G4VPhysicalVolume* GetIronsolidPV1_6() const;



    //for Messenger
    G4double GetPolyHeight() const    {return fPolyHeight;};
    G4double GetFilterSpacing() const    {return fFilterSpacing;};
    G4double GetMultiplierLeadRadius() const    {return fMultiplierLeadRadius;};
    G4double GetModeratorAluminumRadius() const    {return fModeratorAluminumRadius;};
    G4double GetMultiplierLeadHeightRear() const    {return fMultiplierLeadHeightRear;};
    G4double GetFilterCellSpacing() const    {return fFilterCellSpacing;};
    G4double GetModeratorTitaniumHeight() const    {return fModeratorTitaniumHeight;};
    G4double GetModeratorAluminumHeight() const    {return fModeratorAluminumHeight;};
    G4double GetMultiplierLeadHeightFront() const    {return fMultiplierLeadHeightFront;};
    G4double GetModeratorTitaniumRadius() const    {return fModeratorTitaniumRadius;};
    G4double GetTestX() const    {return ftestx;};
    G4double GetTestY() const    {return ftesty;};
    G4double GetTestZ() const    {return ftestz;};
    ///
  private:
    // methods

    //for messenger
    IronFilterDetectorMessenger* fDetectorMessenger;
    //


    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    G4VPhysicalVolume* boratedwater_PV;
    G4VPhysicalVolume* collimation_hole_PV;
    G4VPhysicalVolume* ConcreteSupport_PV;
    G4VPhysicalVolume* Insulation_PV;
    //G4VPhysicalVolume* Phantom_PV;
    //G4VPhysicalVolume* Phantom2_PV;
    //G4VPhysicalVolume* Phantom3_PV;
    //G4VPhysicalVolume* Phantom4_PV;
    ////G4VPhysicalVolume* Phantom5_PV;
    //G4VPhysicalVolume* Phantom6_PV;
    //G4VPhysicalVolume* Phantom7_PV;
    //G4VPhysicalVolume* Phantom8_PV;
    G4VPhysicalVolume* LabFloorWall_solid_PV;
    G4VPhysicalVolume* lab70FloorWall_solid_PV;
    G4VPhysicalVolume* lab66FloorWall_solid_PV;
    G4VPhysicalVolume* lab30FloorWall_solid_PV;
    G4VPhysicalVolume* lab28FloorWall_solid_PV;
    G4VPhysicalVolume* Lab32FloorWall_solid_PV;
    G4VPhysicalVolume* LabFloorExtended_solid_PV;
    G4VPhysicalVolume* frontglassdoor_PV;
    G4VPhysicalVolume* frontdoor_PV;
    G4VPhysicalVolume* glasswindow_PV;
    G4VPhysicalVolume* reardoor_PV;
    G4VPhysicalVolume* TestSurface_solid_PV;
    G4VPhysicalVolume* multiplier_lead_PV;
    G4VPhysicalVolume* moderator_aluminum_PV;
    G4VPhysicalVolume* moderator_titanium_PV;
    G4VPhysicalVolume* Lead_around_TiAndF_PV;
    //G4VPhysicalVolume* LiF_solid_PV;
    G4VPhysicalVolume* inner_BPoly_PV;
    G4VPhysicalVolume* Test_CENTERPOINT_PV;
    G4VPhysicalVolume* filter_scandium_PV;
    G4VPhysicalVolume* filter_scandium_2_PV;
    //G4VPhysicalVolume* shield_cap_iron_PV;


    //fridge
    G4VPhysicalVolume* DilutionUnit_PV;
    G4VPhysicalVolume* MixingPlate_PV;
    G4VPhysicalVolume* ColdPlate2_PV;
    G4VPhysicalVolume* ColdPlate1_PV;
    G4VPhysicalVolume* OneKPlate_PV;
    G4VPhysicalVolume* OneKShield_PV;
    G4VPhysicalVolume* DilutionChamber_PV;
    G4VPhysicalVolume* FourKPlate_PV;
    G4VPhysicalVolume* FourKShield_PV;
    G4VPhysicalVolume* SeventyKPlate_PV;
    G4VPhysicalVolume* SeventyKShield_PV;
    G4VPhysicalVolume* OVCShield_PV;

    //1st Detector type A
    G4VPhysicalVolume* shielding_lead_PV_2;
    G4VPhysicalVolume* filter_aluminum_PV_2;
    //G4VPhysicalVolume* moderator_iron_PV_2;
    G4VPhysicalVolume* shield_cap_iron_PV_2;
    G4VPhysicalVolume* inner_shield_PV_2;
    G4VPhysicalVolume* DT_solid_PV_2;
    G4VPhysicalVolume* Iron_solid_PV_2;

    //2nd Detector type A
    G4VPhysicalVolume* shielding_lead_PV;
    G4VPhysicalVolume* filter_aluminum_PV;
    //G4VPhysicalVolume* moderator_iron_PV;
    G4VPhysicalVolume* shield_cap_iron_PV;
    G4VPhysicalVolume* inner_shield_PV;
    G4VPhysicalVolume* DT_solid_PV;
    G4VPhysicalVolume* Iron_solid_PV;

    //3rd Detector type A
    G4VPhysicalVolume* shielding_lead_PV_3;
    G4VPhysicalVolume* filter_aluminum_PV_3;
    //G4VPhysicalVolume* moderator_iron_PV_3;
    G4VPhysicalVolume* shield_cap_iron_PV_3;
    G4VPhysicalVolume* inner_shield_PV_3;
    G4VPhysicalVolume* DT_solid_PV_3;
    G4VPhysicalVolume* Iron_solid_PV_3;

    //4th Detector type B
    G4VPhysicalVolume* shielding_lead_PV_1;
    G4VPhysicalVolume* filter_aluminum_PV_1;
    //G4VPhysicalVolume* moderator_iron_PV_1;
    G4VPhysicalVolume* shield_cap_iron_PV_1;
    G4VPhysicalVolume* DT_solid_PV_1;
    G4VPhysicalVolume* Iron_solid_PV_1;

    //5th Detector type B
    G4VPhysicalVolume* shielding_lead_PV_1_5;
    G4VPhysicalVolume* filter_aluminum_PV_1_5;
    //G4VPhysicalVolume* moderator_iron_PV_1_5;
    G4VPhysicalVolume* shield_cap_iron_PV_1_5;
    G4VPhysicalVolume* DT_solid_PV_1_5;
    G4VPhysicalVolume* Iron_solid_PV_1_5;

    //6th Detector type B
    G4VPhysicalVolume* shielding_lead_PV_1_6;
    G4VPhysicalVolume* filter_aluminum_PV_1_6;
    //G4VPhysicalVolume* moderator_iron_PV_1_6;
    G4VPhysicalVolume* shield_cap_iron_PV_1_6;
    G4VPhysicalVolume* DT_solid_PV_1_6;
    G4VPhysicalVolume* Iron_solid_PV_1_6;


    //for messenger, these are declared here but values are set in src file
    //constant parameters
    G4double delta;// 1.0cm parameter of catchment area
    G4double zeroRadius;
    G4double startAngle;
    G4double spanningAngle;
    G4double DD_Height;
    G4double RoomLength;


    //variables that you can vary using messenger
    G4double  fPolyHeight;
    G4double  fFilterSpacing;
    G4double  fMultiplierLeadRadius;
    G4double  fModeratorAluminumRadius;
    G4double  fMultiplierLeadHeightRear;
    G4double  fFilterCellSpacing;
    G4double  fModeratorTitaniumHeight;
    G4double  fModeratorAluminumHeight;
    G4double  fMultiplierLeadHeightFront;
    G4double  fModeratorTitaniumRadius;
    G4double  ftestx;
    G4double  ftesty;
    G4double  ftestz;

    //

    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

// inline functions

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetLabFloorWallsolidPV() const {
  return LabFloorWall_solid_PV;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::Getlab70FloorWallsolidPV() const {
  return lab70FloorWall_solid_PV;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::Getlab66FloorWallsolidPV() const {
  return lab66FloorWall_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::Getlab30FloorWallsolidPV() const {
  return lab30FloorWall_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::Getlab28FloorWallsolidPV() const {
  return lab28FloorWall_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetLab32FloorWallsolidPV() const {
  return Lab32FloorWall_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetLabFloorExtendedsolidPV() const {
  return LabFloorExtended_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfrontglassdoorPV() const {
  return frontglassdoor_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfrontdoorPV() const {
  return frontdoor_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetglasswindowPV() const {
  return glasswindow_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetreardoorPV() const {
  return reardoor_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetTestSurfacesolidPV() const {
  return TestSurface_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetboratedwaterPV() const {
  return boratedwater_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetinnerBPolyPV() const {
  return inner_BPoly_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmultiplierleadPV() const {
  return multiplier_lead_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatoraluminumPV() const {
  return moderator_aluminum_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatortitaniumPV() const {
  return moderator_titanium_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetLeadaroundTiAndFPV() const {
  return Lead_around_TiAndF_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilterscandiumPV() const {
  return filter_scandium_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::Getfilterscandium2PV() const {
  return filter_scandium_2_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetcollimationholePV() const {
  return collimation_hole_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetConcreteSupportPV() const {
  return ConcreteSupport_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetInsulationPV() const {
  return Insulation_PV;
}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetPhantomPV() const {
//  return Phantom_PV;
//}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetPhantom2PV() const {
//  return Phantom2_PV;
//}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetPhantom3PV() const {
//  return Phantom3_PV;
//}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetPhantom4PV() const {
//  return Phantom4_PV;
//}

////inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetPhantom5PV() const {
////  return Phantom5_PV;
////}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetPhantom6PV() const {
//  return Phantom6_PV;
//}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetPhantom7PV() const {
//  return Phantom7_PV;
//}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetPhantom8PV() const {
//  return Phantom8_PV;
//}

//teh surface at the center
//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetTestCENTERPOINTPV() const {
//  return Test_CENTERPOINT_PV;
//}

//the LiF layer to absorb the thermal neutrons
//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV() const {
//  return shield_cap_iron_PV;
//}




//Arrays of backing detector


//1st Detector type A

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV2() const {
  return shielding_lead_PV_2;
}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV2() const {
// return moderator_iron_PV_2;
//}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV2() const {
  return filter_aluminum_PV_2;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV2() const {
  return shield_cap_iron_PV_2;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV2() const {
  return DT_solid_PV_2;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV2() const {
  return Iron_solid_PV_2;
}

//2nd Detector type A
inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV() const {
  return shielding_lead_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV() const {
  return filter_aluminum_PV;
}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV() const {
// return moderator_iron_PV;
//}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV() const {
  return shield_cap_iron_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetinnershieldPV() const {
  return inner_shield_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV() const {
  return DT_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV() const {
  return Iron_solid_PV;
}

//3rd Detector type A

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV3() const {
  return shielding_lead_PV_3;
}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV3() const {
// return moderator_iron_PV_3;
//}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV3() const {
  return filter_aluminum_PV_3;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV3() const {
  return shield_cap_iron_PV_3;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV3() const {
  return DT_solid_PV_3;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV3() const {
  return Iron_solid_PV_3;
}

//4th Detector type B

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV1() const {
  return shielding_lead_PV_1;
}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV1() const {
// return moderator_iron_PV_1;
//}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV1() const {
  return filter_aluminum_PV_1;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV1() const {
  return shield_cap_iron_PV_1;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV1() const {
  return DT_solid_PV_1;
}



inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV1() const {
  return Iron_solid_PV_1;
}

//5th Detector type B

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV1_5() const {
  return shielding_lead_PV_1_5;
}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV1_5() const {
// return moderator_iron_PV_1_5;
//}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV1_5() const {
  return filter_aluminum_PV_1_5;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV1_5() const {
  return shield_cap_iron_PV_1_5;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV1_5() const {
  return DT_solid_PV_1_5;
}



inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV1_5() const {
  return Iron_solid_PV_1_5;
}


//6th Detector type B

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV1_6() const {
  return shielding_lead_PV_1_6;
}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV1_6() const {
// return moderator_iron_PV_1_6;
//}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV1_6() const {
  return filter_aluminum_PV_1_6;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV1_6() const {
  return shield_cap_iron_PV_1_6;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV1_6() const {
  return DT_solid_PV_1_6;
}



inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV1_6() const {
  return Iron_solid_PV_1_6;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



#endif
