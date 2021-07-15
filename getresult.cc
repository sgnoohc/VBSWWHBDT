#include <TROOT.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TFile.h>
#include <TH1D.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TChain.h>
#include <TDirectoryFile.h>
#include <stdlib.h>

using namespace std;

//int main(){
int main(int argc, char** argv)
{

    if(argc != 3){
        cout<<"usage  :  ./xxx        signal yield       bkg yield"<<endl;
        return 0;
    }
    double sig_yield = atof(argv[1]);
    double bkg_yield = atof(argv[2]);
    //cout<<sig_yield<<"   "<<bkg_yield<<endl;
    TFile *file = new TFile("TMVAoutput.root");

    TDirectoryFile *DirFileA = (TDirectoryFile *)file->Get("dataset");
    TDirectoryFile *DirFileB = (TDirectoryFile *)DirFileA->Get("Method_BDT");
    TDirectoryFile *DirFileC = (TDirectoryFile *)DirFileB->Get("BDT");

    ofstream outputfile;
    outputfile.open("table.txt",ios::out);

    TH1D *plot_MVA_BDT_S = (TH1D *)DirFileC->Get("MVA_BDT_S");
    TH1D *plot_MVA_BDT_B = (TH1D *)DirFileC->Get("MVA_BDT_B");
    TH1D *plot_MVA_BDT_S_high = (TH1D *)DirFileC->Get("MVA_BDT_S_high");
    TH1D *plot_MVA_BDT_B_high = (TH1D *)DirFileC->Get("MVA_BDT_B_high");
    TH1D *plot_MVA_BDT_effS = (TH1D *)DirFileC->Get("MVA_BDT_effS");
    TH1D *plot_MVA_BDT_effB = (TH1D *)DirFileC->Get("MVA_BDT_effB");
    TH1D *plot_MVA_BDT_effBvsS = (TH1D *)DirFileC->Get("MVA_BDT_effBvsS");
    TH1D *plot_MVA_BDT_rejBvsS = (TH1D *)DirFileC->Get("MVA_BDT_rejBvsS");
    TH1D *plot_MVA_BDT_invBeffvsSeff = (TH1D *)DirFileC->Get("MVA_BDT_invBeffvsSeff");
    TH1D *plot_MVA_BDT_Train_S = (TH1D *)DirFileC->Get("MVA_BDT_Train_S");
    TH1D *plot_MVA_BDT_Train_B = (TH1D *)DirFileC->Get("MVA_BDT_Train_B");
    TH1D *plot_MVA_BDT_trainingEffS = (TH1D *)DirFileC->Get("MVA_BDT_trainingEffS");
    TH1D *plot_MVA_BDT_trainingEffB = (TH1D *)DirFileC->Get("MVA_BDT_trainingEffB");
    TH1D *plot_MVA_BDT_trainingEffBvsS = (TH1D *)DirFileC->Get("MVA_BDT_trainingEffBvsS");
    TH1D *plot_MVA_BDT_trainingRejBvsS = (TH1D *)DirFileC->Get("MVA_BDT_trainingRejBvsS");

    int nbins = plot_MVA_BDT_S_high->GetNbinsX();

    TH1D *plot_SIG_BDT_response = new TH1D(*plot_MVA_BDT_S_high);
    TH1D *plot_BKG_BDT_response = new TH1D(*plot_MVA_BDT_B_high);

    plot_SIG_BDT_response->Sumw2();
    plot_BKG_BDT_response->Sumw2();

    plot_SIG_BDT_response->Rebin(50);
    plot_BKG_BDT_response->Rebin(50);

    plot_SIG_BDT_response->Scale(2*sig_yield/(double)(nbins));
    plot_BKG_BDT_response->Scale(2*bkg_yield/(double)(nbins));

    TH1D *plot_BKG_BDT_SUM_response = new TH1D(*plot_SIG_BDT_response);
    TH1D *plot_SIG_BDT_SUM_response = new TH1D(*plot_SIG_BDT_response);

    for(int ii = 0 ; ii < plot_BKG_BDT_response->GetXaxis()->GetNbins() ; ii++){
        double bkgcontent = 0;
        double bkgerror = 0;
        double sigcontent = 0;
        double sigerror = 0;
        for(int jj = ii ; jj < plot_BKG_BDT_response->GetXaxis()->GetNbins() ; jj ++){
            double err;
            double con;
            con = plot_BKG_BDT_response->GetBinContent(jj + 1);
            err = plot_BKG_BDT_response->GetBinError(jj + 1);
            bkgcontent += con;
            bkgerror += (err * err);
            con = plot_SIG_BDT_response->GetBinContent(jj + 1);
            err = plot_SIG_BDT_response->GetBinError(jj + 1);
            sigcontent += con;
            sigerror += (err * err);
        }
        bkgerror = sqrt(bkgerror);
        sigerror = sqrt(sigerror);
        plot_BKG_BDT_SUM_response->SetBinContent(ii+1,bkgcontent);
        plot_BKG_BDT_SUM_response->SetBinError(ii+1,bkgerror);
        plot_SIG_BDT_SUM_response->SetBinContent(ii+1,sigcontent);
        plot_SIG_BDT_SUM_response->SetBinError(ii+1,sigerror);
    }

    for(int ii = 0 ; ii < plot_BKG_BDT_SUM_response->GetXaxis()->GetNbins() ; ii++){
        outputfile<<plot_BKG_BDT_SUM_response->GetBinContent(ii + 1)<<" , ";
    }
    outputfile<<endl<<endl;

    for(int ii = 0 ; ii < plot_SIG_BDT_SUM_response->GetXaxis()->GetNbins() ; ii++){
        outputfile<<plot_SIG_BDT_SUM_response->GetBinContent(ii + 1)<<" , ";
    }
    outputfile<<endl<<endl;

    for(int ii = 0 ; ii < plot_BKG_BDT_SUM_response->GetXaxis()->GetNbins() ; ii++){
        outputfile<<0.58 * sqrt(plot_BKG_BDT_SUM_response->GetBinContent(ii + 1))<<" , ";
    }
    outputfile<<endl<<endl;


    return 1;
}
