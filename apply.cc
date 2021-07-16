#include "rooutil.h"
#include "VBS.h"

int main(int argc, char** argv)
{

    //___________________________________________________________________________________________________________________________________________________________
    // Argument parsing
    if (argc != 3)
    {
        std::cout << "Usage:" << std::endl;
        std::cout << ""<< std::endl;
        std::cout << "   ./apply PROCESS TREENAME"<< std::endl;
        std::cout << ""<< std::endl;
        std::cout << "      PROCESS         Process of the sample (e.g. bosons, tt1l, tt2l, tt1lpowheg, tt2lpowheg, etc.)"<< std::endl;
        std::cout << "      TREENAME        Name of the ttree     (e.g. variable, variable_train, variable_test)"<< std::endl;
        std::cout << ""<< std::endl;
        return 1;
    }
    TString process = argv[1];
    TString treename = argv[2];

    //___________________________________________________________________________________________________________________________________________________________
    // Output file
    TFile* ofile = new TFile(Form("output/%s_%s.root", process.Data(), treename.Data()), "recreate");

    //___________________________________________________________________________________________________________________________________________________________
    // Reading inputs
    TString ntuple_tag = "v70_SS_20210715";
    TString filepath = Form("/home/users/phchang/public_html/analysis/hwh/VBSHWWBabyLooper__/hadds/%s/createMini_Run2/%s.root", ntuple_tag.Data(), process.Data());
    TChain* input_chain = RooUtil::FileUtil::createTChain(treename, filepath);

    RooUtil::Looper<VBS> looper;

    looper.init(input_chain, &vbs, -1 /* -1 means loop over all events*/);

    RooUtil::TTreeX tx("tree", "tree");

    tx.createBranch<float>("mbb"         );
    tx.createBranch<float>("dphibb"      );
    tx.createBranch<float>("detabb"      );
    tx.createBranch<float>("drbb"        );
    tx.createBranch<float>("ptbb"        );
    tx.createBranch<float>("b0pt"        );
    tx.createBranch<float>("b1pt"        );
    tx.createBranch<float>("mjj"         );
    tx.createBranch<float>("detajj"      );
    tx.createBranch<float>("drjj"        );
    tx.createBranch<float>("ptjj"        );
    tx.createBranch<float>("j_lead_p"    );
    tx.createBranch<float>("j_sublead_p" );
    tx.createBranch<float>("mll"         );
    tx.createBranch<float>("dphill"      );
    tx.createBranch<float>("drll"        );
    tx.createBranch<float>("ptll"        );
    tx.createBranch<float>("l0pt"        );
    tx.createBranch<float>("l1pt"        );
    tx.createBranch<float>("met"         );
    tx.createBranch<float>("lt"          );
    tx.createBranch<float>("st"          );
    tx.createBranch<float>("mtvvh"       );
    tx.createBranch<float>("event_weight");
    tx.createBranch<float>("BDTscore"    );
    tx.createBranch<int>  ("categ"       );
    tx.createBranch<int>  ("channel"     );

    RooUtil::TMVAUtil::ReaderX readerX("BDT", "dataset/weights/TMVAClassification_BDT.weights.xml");

    // Xsection SF from (test events) -> (train + test events)
    //___________________________________________________________________________________________________________________________________________________________
    // bosons : 1.62521
    // raretop : 1.97812
    // tt1l : 2.02885
    // tt2l : 2.0113
    // tt1lpowheg : 1.95004
    // tt2lpowheg : 1.93316
    // ttw : 1.98607
    // ttz : 1.86443
    // vbshww_c2v_4p5 : 1.99914
    float xsec_sf = 1.;
    if (treename.Contains("_test"))
    {
        if (process.EqualTo("bosons")) xsec_sf = 1.62521;
        if (process.EqualTo("raretop")) xsec_sf = 1.97812;
        if (process.EqualTo("ttw")) xsec_sf = 1.98607;
        if (process.EqualTo("ttz")) xsec_sf = 1.86443;
        if (process.EqualTo("vbshww_c2v_4p5")) xsec_sf = 1.99914;
    }

    // Xsection SF from (test events) -> (train + test events) (with LT >= 250)
    //___________________________________________________________________________________________________________________________________________________________
    // bosons : 1.82449
    // raretop : 1.88327
    // tt1l : 1.92888
    // tt2l : 2.13472
    // tt1lpowheg : 1.80935
    // tt2lpowheg : 1.857
    // ttw : 2.00553
    // ttz : 2.12104
    // vbshww_c2v_4p5 : 1.99984

    //___________________________________________________________________________________________________________________________________________________________
    // Event Loop
    while (looper.nextEvent())
    {

        tx.setBranch<float>("mbb"          , vbs.mbb());
        tx.setBranch<float>("dphibb"       , vbs.dphibb());
        tx.setBranch<float>("detabb"       , vbs.detabb());
        tx.setBranch<float>("drbb"         , vbs.drbb());
        tx.setBranch<float>("ptbb"         , vbs.ptbb());
        tx.setBranch<float>("b0pt"         , vbs.b0pt());
        tx.setBranch<float>("b1pt"         , vbs.b1pt());
        tx.setBranch<float>("mjj"          , vbs.mjj());
        tx.setBranch<float>("detajj"       , vbs.detajj());
        tx.setBranch<float>("drjj"         , vbs.drjj());
        tx.setBranch<float>("ptjj"         , vbs.ptjj());
        tx.setBranch<float>("j_lead_p"     , vbs.j_lead_p());
        tx.setBranch<float>("j_sublead_p"  , vbs.j_sublead_p());
        tx.setBranch<float>("mll"          , vbs.mll());
        tx.setBranch<float>("dphill"       , vbs.dphill());
        tx.setBranch<float>("drll"         , vbs.drll());
        tx.setBranch<float>("ptll"         , vbs.ptll());
        tx.setBranch<float>("l0pt"         , vbs.l0pt());
        tx.setBranch<float>("l1pt"         , vbs.l1pt());
        tx.setBranch<float>("met"          , vbs.met());
        tx.setBranch<float>("lt"           , vbs.lt());
        tx.setBranch<float>("st"           , vbs.st());
        tx.setBranch<float>("mtvvh"        , vbs.mtvvh());
        tx.setBranch<float>("event_weight" , vbs.wgt() * vbs.lepsf() * vbs.btagsf() * xsec_sf);
        tx.setBranch<float>("BDTscore"     , readerX.eval(tx));
        tx.setBranch<int>("categ"          , vbs.categ());
        tx.setBranch<int>("channel"        , vbs.channel());

        tx.fill();
    }

    ofile->cd();
    tx.write();

    return 0;

}
