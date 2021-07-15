#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"

int main()
{

    //___________________________________________________________________________________________________________________________________________________________
    // Setting output file
    TString outfileName("TMVAoutput.root");
    TFile* outputFile = TFile::Open(outfileName,"RECREATE");

    //___________________________________________________________________________________________________________________________________________________________
    // Instantiating TMVA related items
    TMVA::Tools::Instance();
    TMVA::DataLoader* dataloader = new TMVA::DataLoader("dataset");
    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");

    //___________________________________________________________________________________________________________________________________________________________
    // Reading inputs
    TString ntuple_tag = "v70_SS_20210715";

    // Reading backgrounds
    TFile *input_BKG_bosons     = TFile::Open(Form("/home/users/phchang/public_html/analysis/hwh/VBSHWWBabyLooper__/hadds/%s/createMini_Run2/bosons.root"         , ntuple_tag.Data()));
    TFile *input_BKG_tt1l       = TFile::Open(Form("/home/users/phchang/public_html/analysis/hwh/VBSHWWBabyLooper__/hadds/%s/createMini_Run2/tt1l.root"           , ntuple_tag.Data()));
    TFile *input_BKG_tt2l       = TFile::Open(Form("/home/users/phchang/public_html/analysis/hwh/VBSHWWBabyLooper__/hadds/%s/createMini_Run2/tt2l.root"           , ntuple_tag.Data()));
    TFile *input_BKG_raretop    = TFile::Open(Form("/home/users/phchang/public_html/analysis/hwh/VBSHWWBabyLooper__/hadds/%s/createMini_Run2/raretop.root"        , ntuple_tag.Data()));
    TFile *input_BKG_ttw        = TFile::Open(Form("/home/users/phchang/public_html/analysis/hwh/VBSHWWBabyLooper__/hadds/%s/createMini_Run2/ttw.root"            , ntuple_tag.Data()));
    TFile *input_BKG_ttz        = TFile::Open(Form("/home/users/phchang/public_html/analysis/hwh/VBSHWWBabyLooper__/hadds/%s/createMini_Run2/ttz.root"            , ntuple_tag.Data()));
    TFile *input_BKG_tt1lpowheg = TFile::Open(Form("/home/users/phchang/public_html/analysis/hwh/VBSHWWBabyLooper__/hadds/%s/createMini_Run2/tt1lpowheg.root"     , ntuple_tag.Data()));
    TFile *input_BKG_tt2lpowheg = TFile::Open(Form("/home/users/phchang/public_html/analysis/hwh/VBSHWWBabyLooper__/hadds/%s/createMini_Run2/tt2lpowheg.root"     , ntuple_tag.Data()));
    TTree *tree_BKG_bosons_train  = (TTree*)input_BKG_bosons     -> Get("variable_train");
    TTree *tree_BKG_bosons_test   = (TTree*)input_BKG_bosons     -> Get("variable_test");
    TTree *tree_BKG_tt1l_train    = (TTree*)input_BKG_tt1l       -> Get("variable");
    TTree *tree_BKG_tt1l_test     = (TTree*)input_BKG_tt1lpowheg -> Get("variable");
    TTree *tree_BKG_tt2l_train    = (TTree*)input_BKG_tt2l       -> Get("variable");
    TTree *tree_BKG_tt2l_test     = (TTree*)input_BKG_tt2lpowheg -> Get("variable");
    TTree *tree_BKG_raretop_train = (TTree*)input_BKG_raretop    -> Get("variable_train");
    TTree *tree_BKG_raretop_test  = (TTree*)input_BKG_raretop    -> Get("variable_test");
    TTree *tree_BKG_ttw_train     = (TTree*)input_BKG_ttw        -> Get("variable_train");
    TTree *tree_BKG_ttw_test      = (TTree*)input_BKG_ttw        -> Get("variable_test");
    TTree *tree_BKG_ttz_train     = (TTree*)input_BKG_ttz        -> Get("variable_train");
    TTree *tree_BKG_ttz_test      = (TTree*)input_BKG_ttz        -> Get("variable_test");

    // Reaidng signals
    TFile *input_SIG_4p5        = TFile::Open(Form("/home/users/phchang/public_html/analysis/hwh/VBSHWWBabyLooper__/hadds/%s/createMini_Run2/vbshww_c2v_4p5.root" , ntuple_tag.Data()));
    TTree *tree_SIG_4p5_train     = (TTree*)input_SIG_4p5        -> Get("variable_train");
    TTree *tree_SIG_4p5_test      = (TTree*)input_SIG_4p5        -> Get("variable_test");

    // Loading backgrounds
    dataloader->AddBackgroundTree(tree_BKG_bosons_train  , 1.0 , TMVA::Types::kTraining);
    dataloader->AddBackgroundTree(tree_BKG_bosons_test   , 1.0 , TMVA::Types::kTesting);
    dataloader->AddBackgroundTree(tree_BKG_tt1l_train    , 1.0 , TMVA::Types::kTraining);
    dataloader->AddBackgroundTree(tree_BKG_tt1l_test     , 1.0 , TMVA::Types::kTesting);
    dataloader->AddBackgroundTree(tree_BKG_tt2l_train    , 1.0 , TMVA::Types::kTraining);
    dataloader->AddBackgroundTree(tree_BKG_tt2l_test     , 1.0 , TMVA::Types::kTesting);
    dataloader->AddBackgroundTree(tree_BKG_raretop_train , 1.0 , TMVA::Types::kTraining);
    dataloader->AddBackgroundTree(tree_BKG_raretop_test  , 1.0 , TMVA::Types::kTesting);
    dataloader->AddBackgroundTree(tree_BKG_ttw_train     , 1.0 , TMVA::Types::kTraining);
    dataloader->AddBackgroundTree(tree_BKG_ttw_test      , 1.0 , TMVA::Types::kTesting);
    dataloader->AddBackgroundTree(tree_BKG_ttz_train     , 1.0 , TMVA::Types::kTraining);
    dataloader->AddBackgroundTree(tree_BKG_ttz_test      , 1.0 , TMVA::Types::kTesting);
    dataloader->SetBackgroundWeightExpression("wgt*lepsf*btagsf");

    // Loading signals
    dataloader->AddSignalTree(tree_SIG_4p5_train , 1.0 , TMVA::Types::kTraining);
    dataloader->AddSignalTree(tree_SIG_4p5_test  , 1.0 , TMVA::Types::kTesting);
    dataloader->SetSignalWeightExpression("wgt*lepsf*btagsf");

    //___________________________________________________________________________________________________________________________________________________________
    // Input variables
    dataloader->AddVariable("met",'F');
    dataloader->AddVariable("l0pt",'F');
    dataloader->AddVariable("l1pt",'F');
    dataloader->AddVariable("ptbb",'F');
    dataloader->AddVariable("mjj",'F');
    dataloader->AddVariable("detajj",'F');
    dataloader->AddVariable("j_lead_p",'F');
    dataloader->AddVariable("j_sublead_p",'F');
    dataloader->AddVariable("st",'F');
    // dataloader->AddVariable("btagchannel",'I');
    // dataloader->AddVariable("lt",'F');
    // dataloader->AddVariable("categ",'I');
    // dataloader->AddVariable("firbjetscore",'F');
    // dataloader->AddSpectator("spec := var1","Spectator","units",'F');
    // dataloader->AddVariable("lepton1pt",'F');
    // dataloader->AddVariable("lepton2pt",'F');
    // dataloader->AddVariable("lepton1reliso",'F');
    // dataloader->AddVariable("lepton2reliso",'F');
    // dataloader->AddVariable("bjetscoretype := bjetscoretype",'I');
    // dataloader->AddVariable("dibjetmass",'F');
    // dataloader->AddVariable("bjet1eta",'F');
    // dataloader->AddVariable("bjet2eta",'F');
    // dataloader->AddVariable("dibjetdeltaR",'F');
    // dataloader->AddVariable("dibjetdeta",'F');
    // dataloader->AddVariable("dibjetdphi",'F');
    // dataloader->AddVariable("leadingvbfjetp",'F');
    // dataloader->AddVariable("subleadvbfjetp",'F');
    // dataloader->AddVariable("divbfjetmass",'F');
    // dataloader->AddVariable("divbfjetdeta",'F');
    // dataloader->AddVariable("divbfjetdphi",'F');
    // dataloader->AddVariable("vbfjet1eta",'F');
    // dataloader->AddVariable("vbfjet2eta",'F');
    // dataloader->AddVariable("vbfjet1Pt",'F');
    // dataloader->AddVariable("vbfjet2Pt",'F');
    // dataloader->AddVariable("divbfjetPt",'F');
    // dataloader->AddVariable("divbfjetdeltaR",'F');
    // dataloader->AddVariable("btagregion",'I');
    // dataloader->AddVariable("lepregion",'I');
    // dataloader->AddVariable("eventtype",'F');

    //___________________________________________________________________________________________________________________________________________________________
    // Apply preselection
    TCut mycut1 = "leadlepID == -11";
    TCut mycut2 = "subllepID != -15";
    TCut mycut3 = "mjj > 500";
    TCut mycut4 = "fabs(detajj) > 3";
    TCut mycut5 = "mbb < 150";
    TCut mycuts = mycut1 && mycut2 && mycut3 && mycut4 && mycut5;
    TCut mycutb = mycuts;
    dataloader->AddCut(mycuts, "Signal");
    dataloader->AddCut(mycutb, "Background");

    //___________________________________________________________________________________________________________________________________________________________
    // Run the code
    factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT","!H:!V:NTrees=800:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );
    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();


    //___________________________________________________________________________________________________________________________________________________________
    // Done!
    outputFile->Close();

    std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
    std::cout << "==> TMVAClassification is done!" << std::endl;

    return 0;

}
