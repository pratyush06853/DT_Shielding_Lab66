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
// $Id: IronFilterSteppingAction.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file IronFilterSteppingAction.cc
/// \brief Implementation of the IronFilterSteppingAction class

#include "IronFilterSteppingAction.hh"
#include "IronFilterEventAction.hh"
#include "IronFilterDetectorConstruction.hh"
#include "IronFilterAnalysis.hh"

#include "G4Neutron.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterSteppingAction::IronFilterSteppingAction(
                      const IronFilterDetectorConstruction* detectorConstruction,
                      IronFilterEventAction* eventAction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterSteppingAction::~IronFilterSteppingAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterSteppingAction::UserSteppingAction(const G4Step* step)
{
// Collect energy and number of scatters step by step

  G4StepPoint* preStep = step->GetPreStepPoint();
  G4StepPoint* postStep = step->GetPostStepPoint();

  G4Track* track = step->GetTrack();

  // get volume of the current step
  const G4VPhysicalVolume* volume = postStep->GetTouchableHandle()->GetVolume();
  //const G4ParticleDefinition* particle = track->GetDefinition();
  const G4String processName = postStep->GetProcessDefinedStep()->GetProcessName();
  //G4double energy = postStep->GetKineticEnergy();

//if ( (volume == fDetConstruction->GetboratedwatersolidPV() && processName == "Transportation" ))
//{
        // Produce code for which direction particle left GetboratedwatersolidPV()
        G4int test_volumeID;
        G4int flag=0;

        //for calibration studies part one
        //if(volume == fDetConstruction->GetTestCENTERPOINTPV()){
        //  test_volumeID = 0;
        //  flag=1;
        // }

        //else if(volume == fDetConstruction->GetInsulationPV()){
        if(volume == fDetConstruction->GetInsulationPV()){
          test_volumeID = 8;
          flag=1;
        }

        //For Safety Studies
        //if(volume == fDetConstruction->GetPhantomPV()){
        //  test_volumeID = 8;
        //  flag=1;
        //}

        //for ambient n-capture Studies
        //1st detector
        //if(volume == fDetConstruction->GetfilteraluminumPV2()){
        //  test_volumeID = 8;
        //  flag=1;
        // }
        //1st detector
        //else if(volume == fDetConstruction->GetshieldcapironPV2()){
        //  test_volumeID = 8;
        //  flag=1;
        //}
        //2nd detector
        //else if(volume == fDetConstruction->GetfilteraluminumPV()){
        //  test_volumeID = 8;
        //  flag=1;
        //}
        //2nd detector
        //else if(volume == fDetConstruction->GetshieldcapironPV()){
        //  test_volumeID = 8;
        //  flag=1;
        //}
        //3rd detector
        //else if(volume == fDetConstruction->GetfilteraluminumPV3()){
        //  test_volumeID = 8;
        //  flag=1;
        //}
        //3rd detector
        //else if(volume == fDetConstruction->GetshieldcapironPV3()){
        //  test_volumeID = 8;
        //  flag=1;
        //}
        //4th Detector
        //else if(volume == fDetConstruction->GetfilteraluminumPV1()){
        //  test_volumeID = 8;
        //  flag=1;
        //}
        //4th Detector
        //else if(volume == fDetConstruction->GetshieldcapironPV1()){
        //  test_volumeID = 8;
        //  flag=1;
        //}
        //5th detector
        //else if(volume == fDetConstruction->GetfilteraluminumPV1_5()){
        //  test_volumeID = 8;
        //  flag=1;
        //}
        //5th detector
        //else if(volume == fDetConstruction->GetshieldcapironPV1_5()){
        //  test_volumeID = 8;
        //  flag=1;
        //}
        //6th detector
        //else if(volume == fDetConstruction->GetfilteraluminumPV1_6()){
        //  test_volumeID = 8;
        //  flag=1;
        //}
        //6th detector
        //else if(volume == fDetConstruction->GetshieldcapironPV1_6()){
        //  test_volumeID = 8;
        //  flag=1;
        //}



        //For Safety Studies
        //else if(volume == fDetConstruction->GetPhantomPV()){
        //  test_volumeID = 8;
        //  flag=0;
        //}


        //else if(volume == fDetConstruction->GetPhantom2PV()){
        //  test_volumeID = 9;
        //  flag=1;
        // }
        //else if(volume == fDetConstruction->GetPhantom3PV()){
        //  test_volumeID = 10;
        //  flag=1;
        //}
        //else if(volume == fDetConstruction->GetPhantom4PV()){
        //  test_volumeID = 11;
        //  flag=1;
        //}
        ////else if(volume == fDetConstruction->GetPhantom5PV()){
        ////  test_volumeID = 12;
        ////  flag=0;
        ////}
        //else if(volume == fDetConstruction->GetPhantom6PV()){
        //  test_volumeID = 13;
        //  flag=1;
        //}
        //else if(volume == fDetConstruction->GetPhantom7PV()){
        //  test_volumeID = 14;
        //  flag=1;
        //}
        //else if(volume == fDetConstruction->GetPhantom8PV()){
        //  test_volumeID = 15;
        //  flag=1;
        //}
        else {
          test_volumeID =10;
          flag=0;
        }

        //way to kill particle less than a predefined energy to speed up thre simulation.
        //G4int flag=1;

        //if(energy*1000 < 1 ){
        //    track->SetTrackStatus(fStopAndKill);
        //    flag = 0;
          //cout<<"Track is killed as the energy of the particle is than 1 KeV"<<endl;
        //  }
        if(flag){
               // get analysis manager
               G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
               G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
               G4double energy = postStep->GetKineticEnergy();
               G4double edep = step->GetTotalEnergyDeposit();
               G4int trackID = track->GetTrackID();
               G4int stepID = track->GetCurrentStepNumber();
               G4String particle_name = track->GetParticleDefinition()->GetParticleName();
               G4int particle_ID = track->GetParticleDefinition()->GetPDGEncoding();

               // TODO: turn this into a tree that gets filled 2112 neutrons
              //if( (particle_ID == 2112 || particle_ID == 22) ){
              if( (particle_ID == 2112) ){
              //if(  (processName  == "hIoni" && particle_name  == "triton") ){
                   //G4cout<<eventID<<"     "<<trackID<<"      "<<particle_ID<<"      "<<energy<<G4endl;
                   //analysisManager->FillNtupleDColumn(0, edep);
                   analysisManager->FillNtupleDColumn(0, energy);
                   analysisManager->FillNtupleDColumn(1, track->GetPosition().x());
                   analysisManager->FillNtupleDColumn(2, track->GetPosition().y());
                   analysisManager->FillNtupleDColumn(3, track->GetPosition().z());
                   analysisManager->FillNtupleDColumn(4, track->GetGlobalTime());
                   analysisManager->FillNtupleDColumn(5, track->GetMomentumDirection().x());
                   analysisManager->FillNtupleDColumn(6, track->GetMomentumDirection().y());
                   analysisManager->FillNtupleDColumn(7, track->GetMomentumDirection().z());
                   analysisManager->FillNtupleIColumn(8, test_volumeID);
                   analysisManager->FillNtupleIColumn(9, particle_ID);
                   analysisManager->FillNtupleIColumn(10, eventID);
                   analysisManager->FillNtupleIColumn(11, trackID);
                   analysisManager->FillNtupleIColumn(12, stepID);
                   analysisManager->AddNtupleRow();
               } //close if statement

         }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
