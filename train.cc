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

int main(int argc, char** argv)
{

    //___________________________________________________________________________________________________________________________________________________________
    // Setting output file
    TString outfileName("TMVAoutput.root");
    TFile* outputFile = TFile::Open(outfileName,"RECREATE");

    //___________________________________________________________________________________________________________________________________________________________
    // Instantiating TMVA related items
    TMVA::Tools::Instance();
    TMVA::DataLoader* dataloader = new TMVA::DataLoader("dataset");
    // TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputFile, "V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;U;G,D:AnalysisType=Classification");
    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputFile, "V:!Silent:Color:DrawProgressBar:AnalysisType=Classification");

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
    dataloader->SetBackgroundWeightExpression("fabs(wgt*lepsf*btagsf)");

    // Loading signals
    dataloader->AddSignalTree(tree_SIG_4p5_train , 1.0 , TMVA::Types::kTraining);
    dataloader->AddSignalTree(tree_SIG_4p5_test  , 1.0 , TMVA::Types::kTesting);
    dataloader->SetSignalWeightExpression("fabs(wgt*lepsf*btagsf)");

    //___________________________________________________________________________________________________________________________________________________________
    // Input variables
    dataloader->AddVariable("mbb"         , 'F');
    dataloader->AddVariable("dphibb"      , 'F');
    dataloader->AddVariable("detabb"      , 'F');
    dataloader->AddVariable("drbb"        , 'F');
    dataloader->AddVariable("ptbb"        , 'F');
    dataloader->AddVariable("b0pt"        , 'F');
    dataloader->AddVariable("b1pt"        , 'F');
    dataloader->AddVariable("mjj"         , 'F');
    dataloader->AddVariable("detajj"      , 'F');
    dataloader->AddVariable("drjj"        , 'F');
    dataloader->AddVariable("ptjj"        , 'F');
    dataloader->AddVariable("j_lead_p"    , 'F');
    dataloader->AddVariable("j_sublead_p" , 'F');
    dataloader->AddVariable("mll"         , 'F');
    dataloader->AddVariable("dphill"      , 'F');
    dataloader->AddVariable("drll"        , 'F');
    dataloader->AddVariable("ptll"        , 'F');
    dataloader->AddVariable("l0pt"        , 'F');
    dataloader->AddVariable("l1pt"        , 'F');
    dataloader->AddVariable("met"         , 'F');
    dataloader->AddVariable("lt"          , 'F');
    dataloader->AddVariable("st"          , 'F');
    dataloader->AddVariable("mtvvh"       , 'F');

    //___________________________________________________________________________________________________________________________________________________________
    // Apply preselection
    TString cut = "";
    // cut += "(categ==1)";
    // cut += "*";
    cut += "(channel>=0)";
    cut += "*";
    cut += "(mjj>=500)";
    cut += "*";
    cut += "(fabs(detajj)>3)";
    cut += "*";
    cut += "(lt>=250)";
    dataloader->AddCut(cut, "Signal");
    dataloader->AddCut(cut, "Background");

    //___________________________________________________________________________________________________________________________________________________________
    // Run the code
    factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT","!H:!V:MaxDepth=5:NTrees=800:BoostType=RealAdaBoost:SeparationType=CrossEntropy:nCuts=-1:NodePurityLimit=0.99:UseYesNoLeaf=False:MinNodeSize=0.01%" );
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
