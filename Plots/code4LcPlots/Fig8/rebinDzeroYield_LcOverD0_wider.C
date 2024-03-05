#include <iostream>
using namespace std;

// Double_t ptbin[7] = {2, 3, 4, 5, 6, 8, 12};   // ptbins to be rebinned into
Double_t ptbins[5] = {2, 4, 8, 12, 24};
TH1D *rebinHist(TH1D *h);
Double_t MEAN2(Double_t A, Double_t B);

const Double_t ptlimsmiddlePrompt[8] = {1.5, 2.5, 3.5, 4.5, 5.5, 7., 10., 18.};
Double_t yvaluncPrompt[8] = {0., 0., 0., 0., 0., 0., 0., 0.};
const Double_t ptlimsmiddlePrompt01[1] = {0.5};
Double_t yvaluncPrompt01[1] = {0.};
const Double_t ptlimsmiddleFD[4] = {3., 6., 10., 18.};
Double_t yvaluncFD[4] = {0., 0., 0., 0.};

void SetStyleHisto(TH1D *h);
void SetStyleHisto(TH1F *h);

int ALICETextSize = 32;
int infoTextSize = 28;

void rebinDzeroYield_LcOverD0_wider()
{
  // gStyle->SetNdivisions(505, "y");

  TFile *promptLcFile = new TFile("./PromptLc_HEPData-ins1829739-v1-root.root", "read");
  TDirectoryFile *promptdir = (TDirectoryFile *)promptLcFile->Get("Table 5");
  TH1F *promptLc = (TH1F *)promptdir->Get("Hist1D_y1");
  TH1F *promptLcStat = (TH1F *)promptdir->Get("Hist1D_y1_e1");
  TH1F *promptLcSystPlus = (TH1F *)promptdir->Get("Hist1D_y1_e2plus");
  TH1F *promptLcMinus = (TH1F *)promptdir->Get("Hist1D_y1_e2minus");

  int nPtBinsPrompt = promptLc->GetNbinsX();
  for (int iPt = 0; iPt < nPtBinsPrompt; iPt++)
  {
    promptLc->SetBinError(iPt + 1, promptLcStat->GetBinContent(iPt + 1));
  }

  Float_t ptlimsLc01[2] = {0., 1.};
  TH1D *PromptLc01 = new TH1D("PromptLc01", "PromptLc01", 1, ptlimsLc01);
  PromptLc01->SetBinContent(1, 0.34317705);
  PromptLc01->SetBinError(1, 0.09);

  TGraphAsymmErrors *gPromptLcSystematics01 = new TGraphAsymmErrors(1, ptlimsmiddlePrompt01, yvaluncPrompt01);
  for (Int_t i = 0; i < 1; i++)
  {
    Double_t PromptValue = PromptLc01->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    Double_t errylow = 0.05;
    Double_t erryhigh = 0.05;
    //    Double_t errxlow = 0.25;
    //    Double_t errxhigh = 0.25;
    gPromptLcSystematics01->SetPoint(i, ptlimsmiddlePrompt01[i], PromptValue);
    gPromptLcSystematics01->SetPointError(i, ptx, ptx, errylow, erryhigh);
  }

  gPromptLcSystematics01->SetFillStyle(0);
  gPromptLcSystematics01->SetFillColor(kRed + 1);
  gPromptLcSystematics01->SetLineWidth(2);
  gPromptLcSystematics01->SetLineColor(kRed + 1);

  const Int_t nptlimsExtra = 10;
  Float_t ptlimsExtral[nptlimsExtra + 1] = {0., 1., 2., 3., 4., 5., 6., 8., 12., 24., 26.};

  TH1D *hrefPrompt = new TH1D("hrefPrompt", "hrefPrompt", nptlimsExtra, ptlimsExtral);
  hrefPrompt->SetTitle("");
  hrefPrompt->GetYaxis()->SetTitle("Baryon / Meson");
  // hrefPrompt->GetYaxis()->SetTitle("#Lambda_{c}^{+}/D^{0}");
  hrefPrompt->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  hrefPrompt->SetMinimum(0.01);
  hrefPrompt->SetMaximum(2.99);
  SetStyleHisto(hrefPrompt);
  hrefPrompt->GetYaxis()->SetTitleSize(0.05);
  hrefPrompt->SetLineWidth(1);
  hrefPrompt->GetYaxis()->SetTitleOffset(1.3);

  //  Double_t errxlowPrompt[8] = {};
  //  Double_t errxhighPrompt[8] = {};
  TGraphAsymmErrors *gPromptLcSystematics = new TGraphAsymmErrors(8, ptlimsmiddlePrompt, yvaluncPrompt);
  for (Int_t i = 0; i < 8; i++)
  {
    Double_t PromptValue = promptLc->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    Double_t errylow = -1. * promptLcMinus->GetBinContent(i + 1);
    Double_t erryhigh = promptLcSystPlus->GetBinContent(i + 1);
    //    Double_t errxlow = 0.25;
    //    Double_t errxhigh = 0.25;
    gPromptLcSystematics->SetPoint(i, ptlimsmiddlePrompt[i], PromptValue);
    gPromptLcSystematics->SetPointError(i, ptx, ptx, errylow, erryhigh);
  }

  gPromptLcSystematics->SetFillStyle(0);
  gPromptLcSystematics->SetFillColor(kRed + 1);
  gPromptLcSystematics->SetLineWidth(2);
  gPromptLcSystematics->SetLineColor(kRed + 1);

  // input file data result

  //  TFile* inputFileLc = new TFile("./CrossSectionLc2pK0s.root", "read");
  //  TH1D* hCroSecLc = (TH1D*)inputFileLc->Get("hCrossSection");

  TFile *inputFileLc = new TFile("./NonPromptLcAverage_pPb5.02TeV.root", "read");
  TH1D *hCroSecLc = (TH1D *)inputFileLc->Get("h1Average");

  // systematics from Annalena
  //  Double_t SystRawYield[3] = {0.1, 0.09, 0.09};
  //  Double_t SystBDTSelection[3] = {0.07, 0.07, 0.07};
  //  Double_t SystTrackingWOBudget[3] = {0.05, 0.05, 0.05};
  //  Double_t SystMaterialBudget[3] = {0.02, 0.02, 0.02};
  //  Double_t SystpTWeights[3] = {0.1, 0.1, 0.1};
  //  Double_t SystFeedDown[3] = {0.1, 0.1, 0.1};
  //  Double_t SystBR[3] = {0.05, 0.05, 0.05};
  //  Double_t SystNor[3] = {0.037, 0.037, 0.037};

  // systematics from Pengzhong
  Double_t SystRawYield[4] = {0.0586, 0.0553, 0.0563, 0.15};
  Double_t SystBDTSelection[4] = {0.0547, 0.0568, 0.0607, 0.08};
  Double_t SystTrackingWOBudget[4] = {0.0557, 0.0563, 0.0572, 0.08};
  Double_t SystMaterialBudget[4] = {0.02, 0.02, 0.02, 0.02};
  Double_t SystpTWeights[4] = {0.0357, 0.0146, 0.0, 0.0};
  Double_t SystFeedDown[4] = {0.0714, 0.0732, 0.0771, 0.15};
  Double_t SystBR[4] = {0.0428, 0.0392, 0.040, 0.05};
  Double_t SystNor[4] = {0.037, 0.037, 0.037};

  //    Double_t SystRawYield_pPb[nPtBinsCoarse] = {0.0586,0.0553,0.0563,0.15};
  //        Double_t SystBDTSEl_pPb[nPtBinsCoarse] = {0.0547,0.0568,0.0607,0.08};
  //        Double_t SystTrackWOBudget_pPb[nPtBinsCoarse] = {0.0557,0.0563,0.0572,0.8};
  //        Double_t SystMaterialBudget_pPb[nPtBinsCoarse] = {0.02, 0.02, 0.02,0.02};
  //        Double_t SystPID_pPb[nPtBinsCoarse] = {0.};
  //        Double_t SystBR_pPb[nPtBinsCoarse] = {0.0428,0.0392,0.040,0.05};
  //        Double_t SystPtShape_pPb[nPtBinsCoarse] = {0.0357,0.0146,0.0,0.0};
  //        Double_t SystFD_pPb[nPtBinsCoarse] = {0.0714,0.0732,0.0771,0.15};
  //        Double_t SystTrack_pPb[nPtBinsCoarse] = {0.0557,0.0563,0.0572,0.06};

  //  Double_t SystTotal[3] = {0.};
  Double_t SystLcCorrAbs[4] = {0.};
  Double_t SystLcUnCorrAbs[4] = {0.};
  for (Int_t i = 0; i < 4; i++)
  {
    SystLcCorrAbs[i] = TMath::Sqrt(SystTrackingWOBudget[i] * SystTrackingWOBudget[i] + SystMaterialBudget[i] * SystMaterialBudget[i] + SystNor[i] * SystNor[i]);
    SystLcCorrAbs[i] = SystLcCorrAbs[i] * hCroSecLc->GetBinContent(i + 1);
  }

  for (Int_t i = 0; i < 4; i++)
  {
    SystLcUnCorrAbs[i] = TMath::Sqrt(SystRawYield[i] * SystRawYield[i] + SystBDTSelection[i] * SystBDTSelection[i] + SystpTWeights[i] * SystpTWeights[i] + SystFeedDown[i] * SystFeedDown[i] + SystBR[i] * SystBR[i]);
    SystLcUnCorrAbs[i] = SystLcUnCorrAbs[i] * hCroSecLc->GetBinContent(i + 1);
  }

  TFile *inputFileD0 = new TFile("./CrossSectionSystematics.root", "read");
  TH1D *hCroSecD0 = (TH1D *)inputFileD0->Get("hCrossSection");
  hCroSecD0->Scale(1. / 0.0395);

  Double_t raw[11] = {0.03, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.02, 0.03};
  Double_t sel[11] = {0.05, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.04, 0.04, 0.04};
  Double_t fr[11] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02};
  Double_t gen[11] = {0.07, 0.05, 0.03, 0.02, 0.01, 0., 0., 0., 0., 0., 0.02};
  Double_t tra[11] = {0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.025, 0.03, 0.03};
  Double_t br[11] = {0.0003, 0.0003, 0.0003, 0.0003, 0.0003, 0.0003, 0.0003, 0.0003, 0.0003, 0.0003, 0.0003};
  Double_t nor[11] = {0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037};

  Double_t SystD0CorrAbs[11];
  Double_t SystD0UnCorrAbs[11];
  for (Int_t i = 0; i < 11; i++)
  {
    SystD0CorrAbs[i] = TMath::Sqrt(tra[i] * tra[i] + nor[i] * nor[i] + sel[i] * sel[i] + fr[i] * fr[i] + gen[i] * gen[i] + br[i] * br[i]);
    SystD0CorrAbs[i] = SystD0CorrAbs[i] * hCroSecD0->GetBinContent(i + 1);
  }

  for (Int_t i = 0; i < 11; i++)
  {
    SystD0UnCorrAbs[i] = TMath::Sqrt(raw[i] * raw[i]);
    SystD0UnCorrAbs[i] = SystD0UnCorrAbs[i] * hCroSecD0->GetBinContent(i + 1);
  }

  TH1D *hCroSecD0Rebin = rebinHist(hCroSecD0);

  Double_t SystD0CorrRebinAbs[4];
  Double_t SystD0UnCorrRebinAbs[4];

  SystD0UnCorrRebinAbs[0] = TMath::Sqrt(SystD0UnCorrAbs[1] * SystD0UnCorrAbs[1] * 1 * 1 / 2 / 2);
  SystD0UnCorrRebinAbs[0] = TMath::Sqrt(SystD0UnCorrRebinAbs[0] * SystD0UnCorrRebinAbs[0] + SystD0UnCorrAbs[2] * SystD0UnCorrAbs[2] * 1 * 1 / 2 / 2);

  SystD0UnCorrRebinAbs[1] = TMath::Sqrt(SystD0UnCorrAbs[3] * SystD0UnCorrAbs[3] * 1 * 1 / 4 / 4);
  SystD0UnCorrRebinAbs[1] = TMath::Sqrt(SystD0UnCorrRebinAbs[1] * SystD0UnCorrRebinAbs[1] + SystD0UnCorrAbs[4] * SystD0UnCorrAbs[4] * 1 * 1 / 4 / 4);
  SystD0UnCorrRebinAbs[1] = TMath::Sqrt(SystD0UnCorrRebinAbs[1] * SystD0UnCorrRebinAbs[1] + SystD0UnCorrAbs[5] * SystD0UnCorrAbs[5] * 1 * 1 / 4 / 4);
  SystD0UnCorrRebinAbs[1] = TMath::Sqrt(SystD0UnCorrRebinAbs[1] * SystD0UnCorrRebinAbs[1] + SystD0UnCorrAbs[6] * SystD0UnCorrAbs[6] * 1 * 1 / 4 / 4);

  SystD0UnCorrRebinAbs[2] = TMath::Sqrt(SystD0UnCorrAbs[7] * SystD0UnCorrAbs[7] * 2 * 2 / 4 / 4);
  SystD0UnCorrRebinAbs[2] = TMath::Sqrt(SystD0UnCorrRebinAbs[2] * SystD0UnCorrRebinAbs[2] + SystD0UnCorrAbs[8] * SystD0UnCorrAbs[8] * 2 * 2 / 4 / 4);

  SystD0UnCorrRebinAbs[3] = TMath::Sqrt(SystD0UnCorrAbs[9] * SystD0UnCorrAbs[9] * 2 * 2 / 4 / 4);
  SystD0UnCorrRebinAbs[3] = TMath::Sqrt(SystD0UnCorrRebinAbs[3] * SystD0UnCorrRebinAbs[3] + SystD0UnCorrAbs[10] * SystD0UnCorrAbs[10] * 2 * 2 / 4 / 4);

  SystD0CorrRebinAbs[0] = SystD0UnCorrAbs[1] * 1 / 2;
  SystD0CorrRebinAbs[0] = SystD0CorrRebinAbs[0] + SystD0CorrAbs[2] * 1 / 2;

  SystD0CorrRebinAbs[1] = SystD0UnCorrAbs[3] * 1 / 4;
  SystD0CorrRebinAbs[1] = SystD0CorrRebinAbs[1] + SystD0CorrAbs[4] * 1 / 4;
  SystD0CorrRebinAbs[1] = SystD0CorrRebinAbs[1] + SystD0CorrAbs[5] * 1 / 4;
  SystD0CorrRebinAbs[1] = SystD0CorrRebinAbs[1] + SystD0CorrAbs[6] * 1 / 4;

  SystD0CorrRebinAbs[2] = SystD0UnCorrAbs[7] * 2 / 4;
  SystD0CorrRebinAbs[2] = SystD0CorrRebinAbs[2] + SystD0CorrAbs[8] * 2 / 4;

  SystD0CorrRebinAbs[3] = SystD0UnCorrAbs[9] * 2 / 4;
  SystD0CorrRebinAbs[3] = SystD0CorrRebinAbs[3] + SystD0CorrAbs[10] * 2 / 4;

  TH1D *hLcOverD0 = (TH1D *)hCroSecLc->Clone("hLcOverD0");
  hLcOverD0->Divide(hCroSecD0Rebin);

  Double_t SystLcOverCorrAbs[4];
  Double_t SystLcOverD0UnCorrAbs[4];
  Double_t SystLcOverD0TotalAbs[4];

  SystLcOverCorrAbs[0] = SystD0CorrRebinAbs[0] + SystLcCorrAbs[0];
  SystLcOverCorrAbs[0] = SystLcOverCorrAbs[0] / hCroSecD0Rebin->GetBinContent(1);

  SystLcOverCorrAbs[1] = SystD0CorrRebinAbs[1] + SystLcCorrAbs[1];
  SystLcOverCorrAbs[1] = SystLcOverCorrAbs[1] / hCroSecD0Rebin->GetBinContent(2);

  SystLcOverCorrAbs[2] = SystD0CorrRebinAbs[2] + SystLcCorrAbs[2];
  SystLcOverCorrAbs[2] = SystLcOverCorrAbs[2] / hCroSecD0Rebin->GetBinContent(3);

  SystLcOverCorrAbs[3] = SystD0CorrRebinAbs[3] + SystLcCorrAbs[3];
  SystLcOverCorrAbs[3] = SystLcOverCorrAbs[3] / hCroSecD0Rebin->GetBinContent(4);

  SystLcOverD0UnCorrAbs[0] = TMath::Sqrt(SystD0UnCorrRebinAbs[0] * SystD0UnCorrRebinAbs[0] + SystLcUnCorrAbs[0] * SystLcUnCorrAbs[0]);
  SystLcOverD0UnCorrAbs[0] = SystLcOverD0UnCorrAbs[0] / hCroSecD0Rebin->GetBinContent(1);

  SystLcOverD0UnCorrAbs[1] = TMath::Sqrt(SystD0UnCorrRebinAbs[1] * SystD0UnCorrRebinAbs[1] + SystLcUnCorrAbs[1] * SystLcUnCorrAbs[1]);
  SystLcOverD0UnCorrAbs[1] = SystLcOverD0UnCorrAbs[1] / hCroSecD0Rebin->GetBinContent(2);

  SystLcOverD0UnCorrAbs[2] = TMath::Sqrt(SystD0UnCorrRebinAbs[2] * SystD0UnCorrRebinAbs[2] + SystLcUnCorrAbs[2] * SystLcUnCorrAbs[2]);
  SystLcOverD0UnCorrAbs[2] = SystLcOverD0UnCorrAbs[2] / hCroSecD0Rebin->GetBinContent(3);

  SystLcOverD0UnCorrAbs[3] = TMath::Sqrt(SystD0UnCorrRebinAbs[3] * SystD0UnCorrRebinAbs[3] + SystLcUnCorrAbs[3] * SystLcUnCorrAbs[3]);
  SystLcOverD0UnCorrAbs[3] = SystLcOverD0UnCorrAbs[3] / hCroSecD0Rebin->GetBinContent(4);

  SystLcOverD0TotalAbs[0] = TMath::Sqrt(SystLcOverD0UnCorrAbs[0] * SystLcOverD0UnCorrAbs[0] + SystLcOverCorrAbs[0] * SystLcOverCorrAbs[0]);

  SystLcOverD0TotalAbs[1] = TMath::Sqrt(SystLcOverD0UnCorrAbs[1] * SystLcOverD0UnCorrAbs[1] + SystLcOverCorrAbs[1] * SystLcOverCorrAbs[1]);

  SystLcOverD0TotalAbs[2] = TMath::Sqrt(SystLcOverD0UnCorrAbs[2] * SystLcOverD0UnCorrAbs[2] + SystLcOverCorrAbs[2] * SystLcOverCorrAbs[2]);

  SystLcOverD0TotalAbs[3] = TMath::Sqrt(SystLcOverD0UnCorrAbs[3] * SystLcOverD0UnCorrAbs[3] + SystLcOverCorrAbs[3] * SystLcOverCorrAbs[3]);

  TGraphAsymmErrors *gFDSystematics = new TGraphAsymmErrors(4, ptlimsmiddleFD, yvaluncFD);
  for (Int_t i = 0; i < 4; i++)
  {
    Double_t FDValue = hLcOverD0->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    Double_t errylow = SystLcOverD0TotalAbs[i];
    Double_t erryhigh = SystLcOverD0TotalAbs[i];
    //    Double_t errxlow = 0.25;
    //    Double_t errxhigh = 0.25;
    gFDSystematics->SetPoint(i, ptlimsmiddleFD[i], FDValue);
    gFDSystematics->SetPointError(i, ptx, ptx, errylow, erryhigh);
  }

  gFDSystematics->SetFillStyle(0);
  gFDSystematics->SetFillColor(kWhite);
  gFDSystematics->SetLineWidth(2);
  gFDSystematics->SetLineColor(kAzure + 2);

  const Int_t nptlims = 4;
  Float_t ptlims[nptlims + 1] = {2., 4., 8., 12., 24.};

  TH1D *hrefFD = new TH1D("hrefFD", "hrefFD", nptlims, ptlims);
  hrefFD->SetTitle("");
  hrefFD->GetYaxis()->SetTitle("#Lambda_{c}^{+}/D^{0}");
  hrefFD->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  //  hrefFD->SetMinimum(0.);
  //  hrefFD->SetMaximum(2.7);
  SetStyleHisto(hrefFD);
  hrefFD->SetLineWidth(1);
  hrefFD->GetYaxis()->SetTitleOffset(1.3);

  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 750, 750);
  gStyle->SetOptStat(0);
  c1->SetTickx();
  c1->SetTicky();
  c1->SetBottomMargin(0.13);
  c1->SetLeftMargin(0.17);
  c1->SetTopMargin(0.05);
  c1->SetRightMargin(0.03);
  c1->cd();

  hrefPrompt->Draw();
  hrefFD->Draw("same");

  //*******************************************************************************

  Double_t _fx1002[4] = {
      3,
      5.5,
      9.5,
      16};
  Double_t _fy1002[4] = {
      0.43,
      0.48,
      0.31,
      0.2};
  Double_t _fex1002[4] = {
      1,
      1.5,
      2.5,
      4};
  Double_t _fey1002[4] = {
      0.08256,
      0.05712,
      0.04247,
      0.0512};
  TGraphErrors *gre = new TGraphErrors(4, _fx1002, _fy1002, _fex1002, _fey1002);
  gre->SetName("");
  gre->SetTitle("");
  gre->SetFillStyle(1000);
  gre->SetLineColor(kGreen + 1);
  gre->SetMarkerColor(kGreen + 1);
  gre->SetLineWidth(2);
  gre->SetMarkerStyle(24);
  gre->SetMarkerSize(2.0);


  TH1F *Graph_Graph1002 = new TH1F("Graph_Graph1002", "", 100, 0.2, 21.8);
  Graph_Graph1002->SetStats(0);
  Graph_Graph1002->SetLineWidth(2);
  Graph_Graph1002->SetMarkerStyle(20);
  gre->SetHistogram(Graph_Graph1002);
  

  gre->Draw(",pez");

  ////
  Double_t _fx1004[4] = {
      3,
      5.5,
      9.5,
      16};
  Double_t _fy1004[4] = {
      0.43,
      0.48,
      0.31,
      0.2};
  Double_t _fex1004[4] = {
      0.2,
      0.2,
      0.2,
      0.2};
  Double_t _fey1004[4] = {
      0.09922477,
      0.08010393,
      0.05584992,
      0.05654591};
  //    TGraphErrors *gre = new TGraphErrors(4,_fx1001,_fy1001,_fex1001,_fey1001);
  gre = new TGraphErrors(4, _fx1004, _fy1004, _fex1004, _fey1004);
  gre->SetName("");
  gre->SetTitle("");
  gre->SetFillStyle(0);
  gre->SetLineColor(kGreen + 1);
  gre->SetMarkerColor(kGreen + 1);
  gre->SetLineWidth(2);
  gre->SetMarkerStyle(24);
  gre->SetMarkerSize(2.0);

  TH1F *Graph_Graph1004 = new TH1F("Graph_Graph1004", "", 100, 1.46, 17.54);
  Graph_Graph1004->SetStats(0);
  Graph_Graph1004->SetLineWidth(2);
  Graph_Graph1004->SetMarkerStyle(20);
  gre->SetHistogram(Graph_Graph1004);
  gre->SetMarkerSize(2.0);

  gre->Draw(",e2z");

  TLatex infoLHCb;
  infoLHCb.SetNDC();
  infoLHCb.SetTextFont(43);
  infoLHCb.SetTextSize(ALICETextSize);
  infoLHCb.DrawLatex(0.6, 0.89, "LHCb");
  infoLHCb.DrawLatex(0.20, 0.89, "ALICE");

  TLatex infosLHCb;
  infosLHCb.SetNDC();
  infosLHCb.SetTextFont(43);
  infosLHCb.SetTextSize(infoTextSize);
  infosLHCb.DrawLatex(0.6, 0.84, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 8.16 TeV");
  infosLHCb.DrawLatex(0.6, 0.78, "2.5 < #it{y}_{cms} < 3.5");
  //***********************************************************************************

  SetStyleHisto(promptLc);
  promptLc->SetStats(0);
  promptLc->SetLineColor(kRed + 1);
  promptLc->SetMarkerColor(kRed + 1);
  promptLc->SetMarkerStyle(21);
  promptLc->SetMarkerSize(2);

  SetStyleHisto(hLcOverD0);
  hLcOverD0->SetStats(0);
  hLcOverD0->SetLineColor(kAzure + 2);
  hLcOverD0->SetMarkerColor(kAzure + 2);
  hLcOverD0->SetMarkerStyle(20);
  hLcOverD0->SetMarkerSize(2);

  SetStyleHisto(PromptLc01);
  PromptLc01->SetStats(0);
  PromptLc01->SetLineColor(kRed + 1);
  PromptLc01->SetMarkerColor(kRed + 1);
  PromptLc01->SetMarkerStyle(21);
  PromptLc01->SetMarkerSize(2);

  TLatex infos;
  infos.SetNDC();
  infos.SetTextFont(43);
  infos.SetTextSize(infoTextSize);
  infos.DrawLatex(0.20, 0.84, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  infos.DrawLatex(0.20, 0.78, "#font[122]{-}0.96 < #it{y}_{cms} < 0.04");

  TLatex inforef;
  inforef.SetNDC();
  inforef.SetTextFont(43);
  inforef.SetTextSize(infoTextSize);
  //  inforef.DrawLatex(0.62, 0.59, "PRL 127 (2021) 202301");
  //  inforef.DrawLatex(0.62, 0.555, "arXiv:2211.14032");

  gPromptLcSystematics->Draw("same2");
  promptLc->Draw("e0 same");
  gPromptLcSystematics01->Draw("same2");
  PromptLc01->Draw("e0 same");
  gFDSystematics->Draw("same2");
  hLcOverD0->Draw("e0 same");
  //  gNorSystematics->Draw("same2");

  TLegend *legLHCb = new TLegend(0.20, 0.6, 0.30, 0.75);
  legLHCb->SetFillColor(0);
  legLHCb->SetFillStyle(0);
  legLHCb->SetBorderSize(0);
  legLHCb->SetMargin(0.46);
  legLHCb->SetTextSize(infoTextSize);
  legLHCb->SetTextFont(43);
  legLHCb->AddEntry(hLcOverD0, "Non-prompt #Lambda_{c}^{+} / D^{0}", "p");
  legLHCb->AddEntry(promptLc, "Prompt #Lambda_{c}^{+} / D^{0}", "p");
  legLHCb->Draw("same");

  TLegend *legLHCb2 = new TLegend(0.60, 0.67, 0.70, 0.75);
  legLHCb2->SetFillColor(0);
  legLHCb2->SetFillStyle(0);
  legLHCb2->SetBorderSize(0);
  legLHCb2->SetMargin(0.46);
  legLHCb2->SetTextSize(infoTextSize);
  legLHCb2->SetTextFont(43);
  // gre->SetMarkerSize(2.0);
  legLHCb2->AddEntry(gre, "#Lambda_{b}^{0} / B^{0}", "p");
  legLHCb2->Draw("same");

  c1->SaveAs("LcOverD0LHCbPaper.pdf");
  c1->SaveAs("LcOverD0LHCbPaper.eps");
}

TH1D *rebinHist(TH1D *h)
{
  TH1D *h_rebin = new TH1D("h_rebin", "h_rebin", 4, ptbins);
  for (Int_t i = 1; i <= h_rebin->GetNbinsX(); i++)
  {
    Double_t binw = h_rebin->GetBinWidth(i);
    for (Int_t j = 1; j <= h->GetNbinsX(); j++)
    {
      Double_t binw0 = h->GetBinWidth(j);
      if (h->GetBinCenter(j) > h_rebin->GetBinLowEdge(i) && h->GetBinCenter(j) <= h_rebin->GetBinLowEdge(i + 1))
      {
        Double_t binc = h_rebin->GetBinContent(i);
        Double_t binc0 = h->GetBinContent(j);
        Double_t bine = h_rebin->GetBinError(i);
        Double_t bine0 = h->GetBinError(j);
        h_rebin->SetBinContent(i, binc + binc0 * binw0 / binw);
        h_rebin->SetBinError(i, TMath::Sqrt(bine * bine + bine0 * bine0 * binw0 * binw0 / binw / binw));
      }
    }
  }
  h_rebin->SetLineColor(h->GetLineColor());
  h_rebin->SetLineWidth(h->GetLineWidth());
  h_rebin->SetMarkerStyle(h->GetMarkerStyle());
  h_rebin->SetMarkerColor(h->GetMarkerColor());
  return h_rebin;
}

Double_t MEAN2(Double_t A, Double_t B)
{
  return TMath::Sqrt(A * A + B * B);
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
  h->GetXaxis()->SetNdivisions(510);
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
  //  h->GetXaxis()->SetNdivisions(505);
  h->GetXaxis()->SetNdivisions(510);
}
