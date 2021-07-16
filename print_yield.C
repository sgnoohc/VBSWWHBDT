
void print_yield(TString process)
{
    TFile* file_all = TFile::Open(Form("output/%s_variable.root", process.Data()));
    TTree* tree_all = (TTree*) file_all->Get("tree");
    TFile* file_test = TFile::Open(Form("output/%s_variable_test.root", process.Data()));
    TTree* tree_test = (TTree*) file_test->Get("tree");

    // Get histograms
    tree_all->Draw("0>>htemp0(1,0,1)", "(mjj>500)*(fabs(detajj)>3)*(channel>=0)*(event_weight)*(lt>=250)");
    TH1F* htemp_all = (TH1F*) gDirectory->Get("htemp0");
    float yield_all = htemp_all->Integral();
    tree_test->Draw("0>>htemp0(1,0,1)", "(mjj>500)*(fabs(detajj)>3)*(channel>=0)*(event_weight)*(lt>=250)");
    TH1F* htemp_test = (TH1F*) gDirectory->Get("htemp0");
    float yield_test = htemp_test->Integral();

    // Print
    float xsec_sf = yield_all/yield_test;
    std::cout << process.Data()  << " : " << xsec_sf << std::endl;;
}

void print_yield()
{

    std::vector<TString> procs = {"bosons", "raretop", "tt1l", "tt2l", "tt1lpowheg", "tt2lpowheg", "ttw", "ttz", "vbshww_c2v_4p5"};

    for (auto& proc : procs)
    {
        // Print yields
        print_yield(proc.Data());
    }
}
