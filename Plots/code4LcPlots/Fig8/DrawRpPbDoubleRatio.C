void SetStyleHisto(TH1D *h);
void SetStyleHisto(TH1F *h);
double calculateRatioErrorFromCorrelatedErrors(double a, double b, double sigmaA, double sigmaB, double rho);

int ALICETextSize = 32;
int infoTextSize = 28;

void DrawRpPbDoubleRatio()
{
    gStyle->SetNdivisions(505, "x");

    TFile *fileLcpp = new TFile("ptIntegralCrossSection/Lc/pp/LHCbNonPromptDzero_PtIntegr2-24_FONLLextrap.root");
    TFile *fileLcpPb = new TFile("ptIntegralCrossSection/Lc/pPb/LHCbNonPromptDzero_PtIntegr2-24_FONLLextrap.root");

    TFile *fileD0pp = new TFile("ptIntegralCrossSection/D0/pp/NonPromptDzero_PtIntegr2-24_FONLLextrap.root");
    TFile *fileD0pPb = new TFile("ptIntegralCrossSection/D0/pPb/LHCbNonPromptDzero_PtIntegr2-24_FONLLextrap.root");

    TH1F *h1pTIntLcpp = (TH1F *)fileLcpp->Get("hPtIntCrossSecStat");
    TH1F *h1pTIntLcpPb = (TH1F *)fileLcpPb->Get("hPtIntCrossSecStat");
    TH1F *h1pTIntLcpPbOverLcpp = (TH1F *)h1pTIntLcpPb->Clone("h1pTIntLcpPbOverLcpp");
    h1pTIntLcpPbOverLcpp->Divide(h1pTIntLcpPb, h1pTIntLcpp, 1, 208);

    TH1F *h1pTIntD0pp = (TH1F *)fileD0pp->Get("hPtIntCrossSecStat");
    TH1F *h1pTIntD0pPb = (TH1F *)fileD0pPb->Get("hPtIntCrossSecStat");
    TH1F *h1pTIntD0pPbOverD0pp = (TH1F *)h1pTIntD0pPb->Clone("h1pTIntD0pPbOverD0pp");
    h1pTIntD0pPbOverD0pp->Divide(h1pTIntD0pPb, h1pTIntD0pp, 1, 208);

    TH1F *h1pTIntLcOverD0pp = (TH1F *)h1pTIntLcpp->Clone("h1pTIntLcOverD0pp");
    h1pTIntLcOverD0pp->Divide(h1pTIntLcpp, h1pTIntD0pp, 1, 1);

    TH1F *h1pTIntLcOverD0pPb = (TH1F *)h1pTIntLcpPb->Clone("h1pTIntLcOverD0pPb");
    h1pTIntLcOverD0pPb->Divide(h1pTIntLcpPb, h1pTIntD0pPb, 1, 1);

    TH1F *h1pTIntRpPbDoubleRatio_temp = (TH1F *)h1pTIntLcOverD0pPb->Clone("h1pTIntRpPbDoubleRatio_temp");
    h1pTIntRpPbDoubleRatio_temp->Divide(h1pTIntLcOverD0pPb, h1pTIntLcOverD0pp, 1, 1);

    TH1F *h1pTIntRpPbDoubleRatio = new TH1F("h1pTIntRpPbDoubleRatio", "", 1, -0.96, 0.04);
    h1pTIntRpPbDoubleRatio->SetBinContent(1, h1pTIntRpPbDoubleRatio_temp->GetBinContent(1));
    h1pTIntRpPbDoubleRatio->SetBinError(1, h1pTIntRpPbDoubleRatio_temp->GetBinError(1));

    // TH1F *h1pTIntRpPbDoubleRatio = (TH1F *)h1pTIntLcpPbOverLcpp->Clone("h1pTIntRpPbDoubleRatio");
    // h1pTIntRpPbDoubleRatio->Divide(h1pTIntD0pPbOverD0pp);

    TCanvas *c1 = new TCanvas("c1", "c1", 750, 750);
    gStyle->SetOptStat(0);
    c1->SetTickx();
    c1->SetTicky();
    c1->SetBottomMargin(0.13);
    c1->SetLeftMargin(0.17);
    c1->SetTopMargin(0.05);
    c1->SetRightMargin(0.03);

    TGraphErrors *gPtIntCrossSecTrackingSystD0pp = (TGraphErrors *)fileD0pp->Get("gPtIntCrossSecTrackingSyst");
    TGraphErrors *gPtIntCrossSecFDSystD0pp = (TGraphErrors *)fileD0pp->Get("gPtIntCrossSecFDSyst");
    TGraphErrors *gPtIntCrossSecBRSystD0pp = (TGraphErrors *)fileD0pp->Get("gPtIntCrossSecBRSyst");
    TGraphErrors *gPtIntCrossSecLumiSystD0pp = (TGraphErrors *)fileD0pp->Get("gPtIntCrossSecLumiSyst");
    TGraphErrors *gPtIntCrossSecDataCorrSystD0pp = (TGraphErrors *)fileD0pp->Get("gPtIntCrossSecDataCorrSyst"); // tracking + FD + BDT eff + Pt shape

    TGraphErrors *gPtIntCrossSecTrackingSystD0pPb = (TGraphErrors *)fileD0pPb->Get("gPtIntCrossSecTrackingSyst");
    TGraphErrors *gPtIntCrossSecFDSystD0pPb = (TGraphErrors *)fileD0pPb->Get("gPtIntCrossSecFDSyst");
    TGraphErrors *gPtIntCrossSecBRSystD0pPb = (TGraphErrors *)fileD0pPb->Get("gPtIntCrossSecBRSyst");
    TGraphErrors *gPtIntCrossSecLumiSystD0pPb = (TGraphErrors *)fileD0pPb->Get("gPtIntCrossSecLumiSyst");
    TGraphErrors *gPtIntCrossSecDataCorrSystD0pPb = (TGraphErrors *)fileD0pPb->Get("gPtIntCrossSecDataCorrSyst"); // tracking + FD + BDT eff + Pt shape

    TGraphErrors *gPtIntCrossSecTrackingSystLcpp = (TGraphErrors *)fileLcpp->Get("gPtIntCrossSecTrackingSyst");
    TGraphErrors *gPtIntCrossSecFDSystLcpp = (TGraphErrors *)fileLcpp->Get("gPtIntCrossSecFDSyst");
    TGraphErrors *gPtIntCrossSecBRSystLcpp = (TGraphErrors *)fileLcpp->Get("gPtIntCrossSecBRSyst");
    TGraphErrors *gPtIntCrossSecLumiSystLcpp = (TGraphErrors *)fileLcpp->Get("gPtIntCrossSecLumiSyst");
    TGraphErrors *gPtIntCrossSecDataCorrSystLcpp = (TGraphErrors *)fileLcpp->Get("gPtIntCrossSecDataCorrSyst"); // tracking + FD + BDT eff + Pt shape

    TGraphErrors *gPtIntCrossSecTrackingSystLcpPb = (TGraphErrors *)fileLcpPb->Get("gPtIntCrossSecTrackingSyst");
    TGraphErrors *gPtIntCrossSecFDSystLcpPb = (TGraphErrors *)fileLcpPb->Get("gPtIntCrossSecFDSyst");
    TGraphErrors *gPtIntCrossSecBRSystLcpPb = (TGraphErrors *)fileLcpPb->Get("gPtIntCrossSecBRSyst");
    TGraphErrors *gPtIntCrossSecLumiSystLcpPb = (TGraphErrors *)fileLcpPb->Get("gPtIntCrossSecLumiSyst");
    TGraphErrors *gPtIntCrossSecDataCorrSystLcpPb = (TGraphErrors *)fileLcpPb->Get("gPtIntCrossSecDataCorrSyst"); // tracking + FD + BDT eff + Pt shape

    TGraphErrors *gPtIntCrossSecDataUncorrSystD0pp = (TGraphErrors *)fileD0pp->Get("gPtIntCrossSecDataUncorrSyst");   // raw yield
    TGraphErrors *gPtIntCrossSecDataUncorrSystD0pPb = (TGraphErrors *)fileD0pPb->Get("gPtIntCrossSecDataUncorrSyst"); // raw yield
    TGraphErrors *gPtIntCrossSecDataUncorrSystLcpp = (TGraphErrors *)fileLcpp->Get("gPtIntCrossSecDataUncorrSyst");   // raw yield
    TGraphErrors *gPtIntCrossSecDataUncorrSystLcpPb = (TGraphErrors *)fileLcpPb->Get("gPtIntCrossSecDataUncorrSyst"); // raw yield

    double *PtIntCrossSecTrackingSystD0pp = gPtIntCrossSecTrackingSystD0pp->GetEYhigh();
    double *PtIntCrossSecFDSystD0pp = gPtIntCrossSecFDSystD0pp->GetEYhigh();
    double *PtIntCrossSecBRSystD0pp = gPtIntCrossSecBRSystD0pp->GetEYhigh();
    double *PtIntCrossSecLumiSystD0pp = gPtIntCrossSecLumiSystD0pp->GetEYhigh();
    double *PtIntCrossSecDataCorrSystD0pp = gPtIntCrossSecDataCorrSystD0pp->GetEYhigh();

    double *PtIntCrossSecTrackingSystD0pPb = gPtIntCrossSecTrackingSystD0pPb->GetEYhigh();
    double *PtIntCrossSecFDSystD0pPb = gPtIntCrossSecFDSystD0pPb->GetEYhigh();
    double *PtIntCrossSecBRSystD0pPb = gPtIntCrossSecBRSystD0pPb->GetEYhigh();
    double *PtIntCrossSecLumiSystD0pPb = gPtIntCrossSecLumiSystD0pPb->GetEYhigh();
    double *PtIntCrossSecDataCorrSystD0pPb = gPtIntCrossSecDataCorrSystD0pPb->GetEYhigh();

    double *PtIntCrossSecTrackingSystLcpp = gPtIntCrossSecTrackingSystLcpp->GetEYhigh();
    double *PtIntCrossSecFDSystLcpp = gPtIntCrossSecFDSystLcpp->GetEYhigh();
    double *PtIntCrossSecBRSystLcpp = gPtIntCrossSecBRSystLcpp->GetEYhigh();
    double *PtIntCrossSecLumiSystLcpp = gPtIntCrossSecLumiSystLcpp->GetEYhigh();
    double *PtIntCrossSecDataCorrSystLcpp = gPtIntCrossSecDataCorrSystLcpp->GetEYhigh();

    double *PtIntCrossSecTrackingSystLcpPb = gPtIntCrossSecTrackingSystLcpPb->GetEYhigh();
    double *PtIntCrossSecFDSystLcpPb = gPtIntCrossSecFDSystLcpPb->GetEYhigh();
    double *PtIntCrossSecBRSystLcpPb = gPtIntCrossSecBRSystLcpPb->GetEYhigh();
    double *PtIntCrossSecLumiSystLcpPb = gPtIntCrossSecLumiSystLcpPb->GetEYhigh();
    double *PtIntCrossSecDataCorrSystLcpPb = gPtIntCrossSecDataCorrSystLcpPb->GetEYhigh();

    double *PtIntCrossSecDataUncorrSystD0pp = gPtIntCrossSecDataUncorrSystD0pp->GetEYhigh();
    double *PtIntCrossSecDataUncorrSystD0pPb = gPtIntCrossSecDataUncorrSystD0pPb->GetEYhigh();
    double *PtIntCrossSecDataUncorrSystLcpp = gPtIntCrossSecDataUncorrSystLcpp->GetEYhigh();
    double *PtIntCrossSecDataUncorrSystLcpPb = gPtIntCrossSecDataUncorrSystLcpPb->GetEYhigh();

    double PtIntCrossSecBDTAndPtShapeSystD0pp = sqrt(pow(PtIntCrossSecDataCorrSystD0pp[0], 2) - pow(PtIntCrossSecTrackingSystD0pp[0], 2) - pow(PtIntCrossSecFDSystD0pp[0], 2));
    double PtIntCrossSecBDTAndPtShapeSystD0pPb = sqrt(pow(PtIntCrossSecDataCorrSystD0pPb[0], 2) - pow(PtIntCrossSecTrackingSystD0pPb[0], 2) - pow(PtIntCrossSecFDSystD0pPb[0], 2));
    double PtIntCrossSecBDTAndPtShapeSystLcpp = sqrt(pow(PtIntCrossSecDataCorrSystLcpp[0], 2) - pow(PtIntCrossSecTrackingSystLcpp[0], 2) - pow(PtIntCrossSecFDSystLcpp[0], 2));
    double PtIntCrossSecBDTAndPtShapeSystLcpPb = sqrt(pow(PtIntCrossSecDataCorrSystLcpPb[0], 2) - pow(PtIntCrossSecTrackingSystLcpPb[0], 2) - pow(PtIntCrossSecFDSystLcpPb[0], 2));

    cout << "h1pTIntD0pp = " << h1pTIntD0pp->GetBinContent(1) << " +- stats: " << h1pTIntD0pp->GetBinError(1) << " +- tracking: " << PtIntCrossSecTrackingSystD0pp[0] << " +- Lumi: " << PtIntCrossSecLumiSystD0pp[0] << " +- FD: " << PtIntCrossSecFDSystD0pp[0] << " +- BR: " << PtIntCrossSecBRSystD0pp[0] << " +- raw yields: " << PtIntCrossSecDataUncorrSystD0pp[0] << " +- BDT: " << PtIntCrossSecBDTAndPtShapeSystD0pp << endl;
    cout << "h1pTIntD0pPb = " << h1pTIntD0pPb->GetBinContent(1) << " +- stats: " << h1pTIntD0pPb->GetBinError(1) << " +- tracking: " << PtIntCrossSecTrackingSystD0pPb[0] << " +- Lumi: " << PtIntCrossSecLumiSystD0pPb[0] << " +- FD: " << PtIntCrossSecFDSystD0pPb[0] << " +- BR: " << PtIntCrossSecBRSystD0pPb[0] << " +- raw yields: " << PtIntCrossSecDataUncorrSystD0pPb[0] << " +- BDT: " << PtIntCrossSecBDTAndPtShapeSystD0pPb << endl;
    cout << "h1pTIntLcpp = " << h1pTIntLcpp->GetBinContent(1) << " +- stats: " << h1pTIntLcpp->GetBinError(1) << " +- tracking: " << PtIntCrossSecTrackingSystLcpp[0] << " +- Lumi: " << PtIntCrossSecLumiSystLcpp[0] << " +- FD: " << PtIntCrossSecFDSystLcpp[0] << " +- BR: " << PtIntCrossSecBRSystLcpp[0] << " +- raw yields: " << PtIntCrossSecDataUncorrSystLcpp[0] << " +- BDT: " << PtIntCrossSecBDTAndPtShapeSystLcpp << endl;
    cout << "h1pTIntLcpPb = " << h1pTIntLcpPb->GetBinContent(1) << " +- stats: " << h1pTIntLcpPb->GetBinError(1) << " +- tracking: " << PtIntCrossSecTrackingSystLcpPb[0] << " +- Lumi: " << PtIntCrossSecLumiSystLcpPb[0] << " +- FD: " << PtIntCrossSecFDSystLcpPb[0] << " +- BR: " << PtIntCrossSecBRSystLcpPb[0] << " +- raw yields: " << PtIntCrossSecDataUncorrSystLcpPb[0] << " +- BDT: " << PtIntCrossSecBDTAndPtShapeSystLcpPb << endl;

    double PtIntLcOverD0ppCorr = sqrt(pow(calculateRatioErrorFromCorrelatedErrors(h1pTIntLcpp->GetBinContent(1), h1pTIntD0pp->GetBinContent(1), PtIntCrossSecTrackingSystLcpp[0], PtIntCrossSecTrackingSystD0pp[0], 1.0), 2) +
                                      pow(calculateRatioErrorFromCorrelatedErrors(h1pTIntLcpp->GetBinContent(1), h1pTIntD0pp->GetBinContent(1), PtIntCrossSecLumiSystLcpp[0], PtIntCrossSecLumiSystD0pp[0], 1.0), 2));
    double PtIntLcOverD0pPbCorr = sqrt(pow(calculateRatioErrorFromCorrelatedErrors(h1pTIntLcpPb->GetBinContent(1), h1pTIntD0pPb->GetBinContent(1), PtIntCrossSecTrackingSystLcpPb[0], PtIntCrossSecTrackingSystD0pPb[0], 1.0), 2) +
                                       pow(calculateRatioErrorFromCorrelatedErrors(h1pTIntLcpPb->GetBinContent(1), h1pTIntD0pPb->GetBinContent(1), PtIntCrossSecLumiSystLcpPb[0], PtIntCrossSecLumiSystD0pPb[0], 1.0), 2));

    double PtIntLcOverD0ppUncorr = sqrt(pow(calculateRatioErrorFromCorrelatedErrors(h1pTIntLcpp->GetBinContent(1), h1pTIntD0pp->GetBinContent(1), PtIntCrossSecDataUncorrSystLcpp[0], PtIntCrossSecDataUncorrSystD0pp[0], 0.0), 2) +
                                        pow(calculateRatioErrorFromCorrelatedErrors(h1pTIntLcpp->GetBinContent(1), h1pTIntD0pp->GetBinContent(1), PtIntCrossSecBRSystLcpp[0], PtIntCrossSecBRSystD0pp[0], 0.0), 2) +
                                        pow(calculateRatioErrorFromCorrelatedErrors(h1pTIntLcpp->GetBinContent(1), h1pTIntD0pp->GetBinContent(1), PtIntCrossSecFDSystLcpp[0], PtIntCrossSecFDSystD0pp[0], 0.0), 2) +
                                        pow(calculateRatioErrorFromCorrelatedErrors(h1pTIntLcpp->GetBinContent(1), h1pTIntD0pp->GetBinContent(1), PtIntCrossSecBDTAndPtShapeSystLcpp, PtIntCrossSecBDTAndPtShapeSystD0pp, 0.0), 2));
    double PtIntLcOverD0pPbUncorr = sqrt(pow(calculateRatioErrorFromCorrelatedErrors(h1pTIntLcpPb->GetBinContent(1), h1pTIntD0pPb->GetBinContent(1), PtIntCrossSecDataUncorrSystLcpPb[0], PtIntCrossSecDataUncorrSystD0pPb[0], 0.0), 2) +
                                         pow(calculateRatioErrorFromCorrelatedErrors(h1pTIntLcpPb->GetBinContent(1), h1pTIntD0pPb->GetBinContent(1), PtIntCrossSecBRSystLcpPb[0], PtIntCrossSecBRSystD0pPb[0], 0.0), 2) +
                                         pow(calculateRatioErrorFromCorrelatedErrors(h1pTIntLcpPb->GetBinContent(1), h1pTIntD0pPb->GetBinContent(1), PtIntCrossSecFDSystLcpPb[0], PtIntCrossSecFDSystD0pPb[0], 0.0), 2) +
                                         pow(calculateRatioErrorFromCorrelatedErrors(h1pTIntLcpPb->GetBinContent(1), h1pTIntD0pPb->GetBinContent(1), PtIntCrossSecBDTAndPtShapeSystLcpPb, PtIntCrossSecBDTAndPtShapeSystD0pPb, 0.0), 2));

    double PtIntLcOverD0ppTotalSyst = sqrt(pow(PtIntLcOverD0ppCorr, 2) + pow(PtIntLcOverD0ppUncorr, 2));
    double PtIntLcOverD0pPbTotalSyst = sqrt(pow(PtIntLcOverD0pPbCorr, 2) + pow(PtIntLcOverD0pPbUncorr, 2));

    double PtIntRpPbDoubleRatioDataTotalSyst = calculateRatioErrorFromCorrelatedErrors(h1pTIntLcOverD0pPb->GetBinContent(1), h1pTIntLcOverD0pp->GetBinContent(1), PtIntLcOverD0pPbTotalSyst, PtIntLcOverD0ppTotalSyst, 0.0);

    // double PtIntLcOverD0ppCorr = (PtIntCrossSecTrackingSystLcpp[0] + PtIntCrossSecLumiSystLcpp[0]) / h1pTIntLcpp->GetBinContent(1) + (PtIntCrossSecTrackingSystD0pp[0] + PtIntCrossSecLumiSystD0pp[0]) / h1pTIntD0pp->GetBinContent(1);
    // double PtIntLcOverD0pPbCorr = (PtIntCrossSecTrackingSystLcpPb[0] + PtIntCrossSecLumiSystLcpPb[0]) / h1pTIntLcpPb->GetBinContent(1) + (PtIntCrossSecTrackingSystD0pPb[0] + PtIntCrossSecLumiSystD0pPb[0]) / h1pTIntD0pPb->GetBinContent(1);
    // double PtIntLcOverD0ppUncorr = sqrt(pow(PtIntCrossSecDataUncorrSystLcpp[0] / h1pTIntLcpp->GetBinContent(1), 2) + pow(PtIntCrossSecBRSystLcpp[0] / h1pTIntLcpp->GetBinContent(1), 2) + pow(PtIntCrossSecFDSystLcpp[0] / h1pTIntLcpp->GetBinContent(1), 2) + pow(PtIntCrossSecBDTAndPtShapeSystLcpp / h1pTIntLcpp->GetBinContent(1), 2) + pow(PtIntCrossSecDataUncorrSystD0pp[0] / h1pTIntD0pp->GetBinContent(1), 2) + pow(PtIntCrossSecBRSystD0pp[0] / h1pTIntD0pp->GetBinContent(1), 2) + pow(PtIntCrossSecFDSystD0pp[0] / h1pTIntD0pp->GetBinContent(1), 2) + pow(PtIntCrossSecBDTAndPtShapeSystD0pp / h1pTIntD0pp->GetBinContent(1), 2));
    // double PtIntLcOverD0pPbUncorr = sqrt(pow(PtIntCrossSecDataUncorrSystLcpPb[0] / h1pTIntLcpPb->GetBinContent(1), 2) + pow(PtIntCrossSecBRSystLcpPb[0] / h1pTIntLcpPb->GetBinContent(1), 2) + pow(PtIntCrossSecFDSystLcpPb[0] / h1pTIntLcpPb->GetBinContent(1), 2) + pow(PtIntCrossSecBDTAndPtShapeSystLcpPb / h1pTIntLcpPb->GetBinContent(1), 2) + pow(PtIntCrossSecDataUncorrSystD0pPb[0] / h1pTIntD0pPb->GetBinContent(1), 2) + pow(PtIntCrossSecBRSystD0pPb[0] / h1pTIntD0pPb->GetBinContent(1), 2) + pow(PtIntCrossSecFDSystD0pPb[0] / h1pTIntD0pPb->GetBinContent(1), 2) + pow(PtIntCrossSecBDTAndPtShapeSystD0pPb / h1pTIntD0pPb->GetBinContent(1), 2));
    // double PtIntLcOverD0ppTotalSyst = h1pTIntLcOverD0pp->GetBinContent(1) * (PtIntLcOverD0ppCorr + PtIntLcOverD0ppUncorr);
    // double PtIntLcOverD0pPbTotalSyst = h1pTIntLcOverD0pPb->GetBinContent(1) * (PtIntLcOverD0pPbCorr + PtIntLcOverD0pPbUncorr);

    // double PtIntRpPbDoubleRatioDataTotalSyst = h1pTIntRpPbDoubleRatio->GetBinContent(1) * (sqrt(pow(PtIntLcOverD0ppTotalSyst / h1pTIntLcOverD0pp->GetBinContent(1), 2) + pow(PtIntLcOverD0pPbTotalSyst / h1pTIntLcOverD0pPb->GetBinContent(1), 2)));

    cout << "LcOverD0pp:" << h1pTIntLcOverD0pp->GetBinContent(1) << " +- " << h1pTIntLcOverD0pp->GetBinError(1) << " (stat) "
         << " +- " << PtIntLcOverD0ppTotalSyst << " (syst)" << endl;

    cout << "LcOverD0pPb:" << h1pTIntLcOverD0pPb->GetBinContent(1) << " +- " << h1pTIntLcOverD0pPb->GetBinError(1) << " (stat) "
         << " +- " << PtIntLcOverD0pPbTotalSyst << " (syst)" << endl;

    cout << "double ratio = " << h1pTIntRpPbDoubleRatio->GetBinContent(1) << " +- " << h1pTIntRpPbDoubleRatio->GetBinError(1) << endl;
    cout << "PtIntRpPbDoubleRatioDataTotalSyst = " << PtIntRpPbDoubleRatioDataTotalSyst << endl;

    TGraphAsymmErrors *gPtIntRpPbDoubleRatioData = new TGraphAsymmErrors(1);
    gPtIntRpPbDoubleRatioData->SetPoint(0, -0.96 + abs(-0.96 - 0.04) / 2, h1pTIntRpPbDoubleRatio->GetBinContent(1));
    gPtIntRpPbDoubleRatioData->SetPointError(0, 0.2, 0.2, PtIntRpPbDoubleRatioDataTotalSyst, PtIntRpPbDoubleRatioDataTotalSyst);

    // gPtIntRpPbDoubleRatioData->SetMarkerStyle(20);
    // gPtIntRpPbDoubleRatioData->SetMarkerSize(1.5);
    // gPtIntRpPbDoubleRatioData->SetMarkerColor(kBlack);
    // gPtIntRpPbDoubleRatioData->SetLineColor(kBlack);
    // gPtIntRpPbDoubleRatioData->SetLineWidth(1);
    // gPtIntRpPbDoubleRatioData->SetLineStyle(1);
    gPtIntRpPbDoubleRatioData->SetFillStyle(0);
    gPtIntRpPbDoubleRatioData->SetFillColor(kWhite);
    gPtIntRpPbDoubleRatioData->SetLineWidth(2);
    gPtIntRpPbDoubleRatioData->SetLineColor(kBlue);

    SetStyleHisto(h1pTIntRpPbDoubleRatio);
    h1pTIntRpPbDoubleRatio->SetStats(0);
    h1pTIntRpPbDoubleRatio->SetLineColor(kBlue);
    h1pTIntRpPbDoubleRatio->SetMarkerColor(kBlue);
    h1pTIntRpPbDoubleRatio->SetMarkerStyle(21);
    h1pTIntRpPbDoubleRatio->SetMarkerSize(2.0);

    TH1F *h1Ref = new TH1F("h1Ref", "", 10, -4.5, 4.5);
    // TH1F *h1Ref = (TH1F *)h1pTIntRpPbDoubleRatio->Clone("h1Ref");
    h1Ref->GetYaxis()->SetRangeUser(0.01, 2.99);
    h1Ref->GetYaxis()->SetTitle("#it{R}^{ Baryon / Meson}_{ pPb}");
    h1Ref->GetXaxis()->SetTitle("#it{y}_{cms}");
    SetStyleHisto(h1Ref);
    h1Ref->SetLineWidth(1);
    h1Ref->GetYaxis()->SetTitleOffset(1.3);
    c1->cd();
    // h1pTIntRpPbDoubleRatio->GetYaxis()->SetRangeUser(0.0, 2.0);
    h1Ref->Draw("");
    h1pTIntRpPbDoubleRatio->Draw("e0 same");
    gPtIntRpPbDoubleRatioData->Draw("same2");

    // LHCb
    Double_t _fx1005[2] = {
        -3,
        3};
    Double_t _fy1005[2] = {
        0.78,
        0.92};
    Double_t _fex1005[2] = {
        0.5,
        0.5};
    Double_t _fey1005[2] = {
        0.11,
        0.09};
    TGraphErrors *gre = new TGraphErrors(2, _fx1005, _fy1005, _fex1005, _fey1005);
    gre->SetName("");
    gre->SetTitle("");
    gre->SetFillStyle(1000);
    gre->SetLineColor(2);
    gre->SetLineWidth(3);
    gre->SetMarkerColor(2);
    gre->SetMarkerStyle(20);

    TH1F *Graph_Graph1005 = new TH1F("Graph_Graph1005", "", 100, -5, 5);
    Graph_Graph1005->SetMinimum(0);
    Graph_Graph1005->SetMaximum(2);
    Graph_Graph1005->SetDirectory(0);
    Graph_Graph1005->SetStats(0);
    Graph_Graph1005->SetLineWidth(3);
    Graph_Graph1005->SetMarkerStyle(20);
    Graph_Graph1005->GetXaxis()->SetTitle("#it{y}");
    Graph_Graph1005->GetXaxis()->SetNdivisions(505);
    Graph_Graph1005->GetXaxis()->SetLabelFont(132);
    Graph_Graph1005->GetXaxis()->SetLabelOffset(0.01);
    Graph_Graph1005->GetXaxis()->SetLabelSize(0.06);
    Graph_Graph1005->GetXaxis()->SetTitleSize(0.072);
    Graph_Graph1005->GetXaxis()->SetTitleOffset(0.95);
    Graph_Graph1005->GetXaxis()->SetTitleFont(132);
    Graph_Graph1005->GetYaxis()->SetTitle("#it{R}_{#it{p}Pb}^{#it{#Lambda}^{0}_{#it{b}}/#it{B}^{0}}");
    Graph_Graph1005->GetYaxis()->SetLabelFont(132);
    Graph_Graph1005->GetYaxis()->SetLabelOffset(0.01);
    Graph_Graph1005->GetYaxis()->SetLabelSize(0.06);
    Graph_Graph1005->GetYaxis()->SetTitleSize(0.072);
    Graph_Graph1005->GetYaxis()->SetTitleFont(132);
    Graph_Graph1005->GetZaxis()->SetLabelFont(132);
    Graph_Graph1005->GetZaxis()->SetLabelSize(0.06);
    Graph_Graph1005->GetZaxis()->SetTitleSize(0.072);
    Graph_Graph1005->GetZaxis()->SetTitleOffset(1.2);
    Graph_Graph1005->GetZaxis()->SetTitleFont(132);
    gre->SetHistogram(Graph_Graph1005);
    gre->SetMarkerSize(2.0);

    gre->Draw("pez same");

    Double_t _fx1006[2] = {
        -3,
        3};
    Double_t _fy1006[2] = {
        0.78,
        0.92};
    Double_t _fex1006[2] = {
        0.5,
        0.5};
    Double_t _fey1006[2] = {
        0.11,
        0.09};
    gre = new TGraphErrors(2, _fx1006, _fy1006, _fex1006, _fey1006);
    gre->SetName("");
    gre->SetTitle("");
    gre->SetFillStyle(1000);
    gre->SetLineColor(2);
    gre->SetLineWidth(3);
    gre->SetMarkerColor(2);
    gre->SetMarkerStyle(20);

    TH1F *Graph_Graph_Graph10051006 = new TH1F("Graph_Graph_Graph10051006", "", 100, -5, 5);
    Graph_Graph_Graph10051006->SetMinimum(0);
    Graph_Graph_Graph10051006->SetMaximum(2);
    Graph_Graph_Graph10051006->SetDirectory(0);
    Graph_Graph_Graph10051006->SetStats(0);
    Graph_Graph_Graph10051006->SetLineWidth(3);
    Graph_Graph_Graph10051006->SetMarkerStyle(20);
    Graph_Graph_Graph10051006->GetXaxis()->SetTitle("#it{y}");
    Graph_Graph_Graph10051006->GetXaxis()->SetNdivisions(505);
    Graph_Graph_Graph10051006->GetXaxis()->SetLabelFont(132);
    Graph_Graph_Graph10051006->GetXaxis()->SetLabelOffset(0.01);
    Graph_Graph_Graph10051006->GetXaxis()->SetLabelSize(0.06);
    Graph_Graph_Graph10051006->GetXaxis()->SetTitleSize(0.072);
    Graph_Graph_Graph10051006->GetXaxis()->SetTitleOffset(0.95);
    Graph_Graph_Graph10051006->GetXaxis()->SetTitleFont(132);
    Graph_Graph_Graph10051006->GetYaxis()->SetTitle("#it{R}_{#it{p}Pb}^{#it{#Lambda}^{0}_{#it{b}}/#it{B}^{0}}");
    Graph_Graph_Graph10051006->GetYaxis()->SetLabelFont(132);
    Graph_Graph_Graph10051006->GetYaxis()->SetLabelOffset(0.01);
    Graph_Graph_Graph10051006->GetYaxis()->SetLabelSize(0.06);
    Graph_Graph_Graph10051006->GetYaxis()->SetTitleSize(0.072);
    Graph_Graph_Graph10051006->GetYaxis()->SetTitleFont(132);
    Graph_Graph_Graph10051006->GetZaxis()->SetLabelFont(132);
    Graph_Graph_Graph10051006->GetZaxis()->SetLabelSize(0.06);
    Graph_Graph_Graph10051006->GetZaxis()->SetTitleSize(0.072);
    Graph_Graph_Graph10051006->GetZaxis()->SetTitleOffset(1.2);
    Graph_Graph_Graph10051006->GetZaxis()->SetTitleFont(132);
    gre->SetHistogram(Graph_Graph_Graph10051006);

    gre->Draw(",pez same");

    Double_t _fx1007[2] = {
        -3,
        3};
    Double_t _fy1007[2] = {
        0.78,
        0.92};
    Double_t _fex1007[2] = {
        0.2,
        0.2};
    Double_t _fey1007[2] = {
        0.117047,
        0.09486833};
    gre = new TGraphErrors(2, _fx1007, _fy1007, _fex1007, _fey1007);
    gre->SetName("");
    gre->SetTitle("");
    gre->SetFillStyle(0);
    gre->SetLineColor(2);
    gre->SetLineWidth(3);
    gre->SetMarkerColor(2);
    gre->SetMarkerStyle(20);

    TH1F *Graph_Graph1007 = new TH1F("Graph_Graph1007", "", 100, -3.84, 3.84);
    Graph_Graph1007->SetMinimum(0.6277615);
    Graph_Graph1007->SetMaximum(1.05006);
    Graph_Graph1007->SetDirectory(0);
    Graph_Graph1007->SetStats(0);
    Graph_Graph1007->SetLineWidth(3);
    Graph_Graph1007->SetMarkerStyle(20);
    Graph_Graph1007->GetXaxis()->SetNdivisions(505);
    Graph_Graph1007->GetXaxis()->SetLabelFont(132);
    Graph_Graph1007->GetXaxis()->SetLabelOffset(0.01);
    Graph_Graph1007->GetXaxis()->SetLabelSize(0.06);
    Graph_Graph1007->GetXaxis()->SetTitleSize(0.072);
    Graph_Graph1007->GetXaxis()->SetTitleOffset(0.95);
    Graph_Graph1007->GetXaxis()->SetTitleFont(132);
    Graph_Graph1007->GetYaxis()->SetLabelFont(132);
    Graph_Graph1007->GetYaxis()->SetLabelOffset(0.01);
    Graph_Graph1007->GetYaxis()->SetLabelSize(0.06);
    Graph_Graph1007->GetYaxis()->SetTitleSize(0.072);
    Graph_Graph1007->GetYaxis()->SetTitleOffset(0.9);
    Graph_Graph1007->GetYaxis()->SetTitleFont(132);
    Graph_Graph1007->GetZaxis()->SetLabelFont(132);
    Graph_Graph1007->GetZaxis()->SetLabelSize(0.06);
    Graph_Graph1007->GetZaxis()->SetTitleSize(0.072);
    Graph_Graph1007->GetZaxis()->SetTitleOffset(1.2);
    Graph_Graph1007->GetZaxis()->SetTitleFont(132);
    gre->SetHistogram(Graph_Graph1007);

    gre->Draw(",e2z same");
    // TLatex *tex = new TLatex(0.65, 0.25, "2 < #it{p}_{T} < 20 GeV/#it{c}");
    // tex->SetNDC();
    // tex->SetTextFont(132);
    // tex->SetLineWidth(2);
    // tex->Draw();
    // tex = new TLatex(0.2, 0.84, "LHCb");
    // tex->SetNDC();
    // tex->SetTextFont(132);
    // tex->SetTextSize(0.06);
    // tex->SetLineWidth(2);
    // tex->Draw();
    // tex = new TLatex(0.2, 0.77, "#sqrt{#it{s}_{NN}} = 8.16 TeV");
    // tex->SetNDC();
    // tex->SetTextFont(132);
    // tex->SetLineWidth(2);
    // tex->Draw();
    TLine *line = new TLine(-4.5, 1, 4.5, 1);
    line->SetLineStyle(2);
    line->SetLineWidth(2);
    line->Draw();
    // LHCb

    TLatex info2;
    info2.SetNDC();
    info2.SetTextFont(43);
    info2.SetTextSize(ALICETextSize);
    info2.DrawLatex(0.20, 0.89, "ALICE");
    info2.SetTextSize(infoTextSize);
    info2.DrawLatex(0.20, 0.83, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
    info2.DrawLatex(0.20, 0.77, "2 < #it{p}_{T} < 24 GeV/#it{c}");
    info2.SetTextSize(ALICETextSize);
    info2.DrawLatex(0.60, 0.89, "LHCb");
    info2.SetTextSize(infoTextSize);
    info2.DrawLatex(0.60, 0.83, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 8.16 TeV");
    info2.DrawLatex(0.60, 0.77, "2 < #it{p}_{T} < 20 GeV/#it{c}");

    TLegend *leg = new TLegend(0.20, 0.66, 0.3, 0.76);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetMargin(0.46);
    leg->SetTextSize(infoTextSize);
    leg->SetTextFont(43);
    leg->AddEntry(h1pTIntRpPbDoubleRatio, "Non-prompt #Lambda_{c}^{+} / D^{0}", "P");
    leg->Draw();

    TLegend *leg2 = new TLegend(0.60, 0.66, 0.71, 0.76);
    leg2->SetFillColor(0);
    leg2->SetFillStyle(0);
    leg2->SetBorderSize(0);
    leg2->SetMargin(0.46);
    leg2->SetTextSize(infoTextSize);
    leg2->SetTextFont(43);
    gre->SetMarkerSize(2.0);
    leg2->AddEntry(gre, "#Lambda^{0}_{b} / B^{0}", "p");
    leg2->Draw();

    c1->SaveAs("ptIntegralCrossSection/RpPbDoubleRatio.pdf");
    c1->SaveAs("ptIntegralCrossSection/RpPbDoubleRatio.png");
    c1->SaveAs("ptIntegralCrossSection/RpPbDoubleRatio.eps");

    TFile *fileOutput = new TFile("ptIntegralCrossSection/RpPbDoubleRatio.root", "recreate");
    fileOutput->cd();
    c1->Write();
    h1pTIntRpPbDoubleRatio->Write();
    gPtIntRpPbDoubleRatioData->Write();
    fileOutput->Close();
}

void SetStyleHisto(TH1D *h)
{

    h->SetLineColor(kBlack);
    h->SetLineWidth(2);
    h->GetYaxis()->SetLabelFont(42);
    h->GetYaxis()->SetTitleFont(42);
    h->GetYaxis()->SetTitleSize(0.06);
    h->GetYaxis()->SetTitleOffset(1);
    h->GetYaxis()->SetLabelSize(0.05);
    h->GetYaxis()->SetLabelOffset(0.01);
    h->GetYaxis()->SetDecimals(kTRUE);
    // h->GetYaxis()->SetNdivisions(507);
    h->GetXaxis()->SetTitleFont(42);
    h->GetXaxis()->SetLabelFont(42);
    h->GetXaxis()->SetTitleSize(0.06);
    h->GetXaxis()->SetTitleOffset(1.0);
    h->GetXaxis()->SetLabelSize(0.05);
    h->GetXaxis()->SetNdivisions(505);
}

void SetStyleHisto(TH1F *h)
{

    h->SetLineColor(kBlack);
    h->SetLineWidth(2);
    h->GetYaxis()->SetLabelFont(42);
    h->GetYaxis()->SetTitleFont(42);
    h->GetYaxis()->SetTitleSize(0.06);
    h->GetYaxis()->SetTitleOffset(1);
    h->GetYaxis()->SetLabelSize(0.05);
    h->GetYaxis()->SetLabelOffset(0.01);
    h->GetYaxis()->SetDecimals(kTRUE);
    // h->GetYaxis()->SetNdivisions(507);
    h->GetXaxis()->SetTitleFont(42);
    h->GetXaxis()->SetLabelFont(42);
    h->GetXaxis()->SetTitleSize(0.06);
    h->GetXaxis()->SetTitleOffset(1.0);
    h->GetXaxis()->SetLabelSize(0.05);
     h->GetXaxis()->SetNdivisions(505);
    // h->GetXaxis()->SetNdivisions(510);
}

double calculateRatioErrorFromCorrelatedErrors(double a, double b, double sigmaA, double sigmaB, double rho)
{
    double ratio = a / b;
    double sigmaRatio = ratio * sqrt(pow(sigmaA / a, 2) + pow(sigmaB / b, 2) - 2 * rho * sigmaA * sigmaB / (a * b));
    return sigmaRatio;
}