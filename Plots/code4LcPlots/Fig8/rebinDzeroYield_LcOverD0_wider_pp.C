#include <iostream>
using namespace std;

// Double_t ptbin[7] = {2, 3, 4, 5, 6, 8, 12};   // ptbins to be rebinned into
Double_t ptbins[5] = {2, 4, 8, 12, 24};
TH1D *rebinHist(TH1D *h);
Double_t MEAN2(Double_t A, Double_t B);

const Double_t ptlimsmiddlePrompt[5] = {3., 5., 7., 10., 18.};
Double_t yvaluncPrompt[5] = {0., 0., 0., 0., 0.};
// const Double_t ptlimsmiddlePrompt01[1] = {0.5};
// Double_t yvaluncPrompt01[1] = {0.};
const Double_t ptlimsmiddleFD[4] = {3., 6., 10., 18.};
Double_t yvaluncFD[4] = {0., 0., 0., 0.};

void SetStyleHisto(TH1D *h);
void SetStyleHisto(TH1F *h);


int ALICETextSize = 32;
int infoTextSize = 28;

void rebinDzeroYield_LcOverD0_wider_pp()
{

  // gStyle->SetNdivisions(505, "xyz");

  TFile *promptLcFile = new TFile("./HEPData-ins2686623-v1-root.root", "read");
  TDirectoryFile *promptdir = (TDirectoryFile *)promptLcFile->Get("Figure 5 non-prompt Lc over non-prompt D0 pp 13 TeV");
  TH1F *promptLc = (TH1F *)promptdir->Get("Hist1D_y1");
  TH1F *promptLcStat = (TH1F *)promptdir->Get("Hist1D_y1_e1");
  TH1F *promptLcSyst = (TH1F *)promptdir->Get("Hist1D_y1_e2");

  int nPtBinsPrompt = promptLc->GetNbinsX();
  for (int iPt = 0; iPt < nPtBinsPrompt; iPt++)
  {
    promptLc->SetBinError(iPt + 1, promptLcStat->GetBinContent(iPt + 1));
  }

  //  Float_t ptlimsLc01[2] = {0., 1.};
  //  TH1D* PromptLc01 = new TH1D("PromptLc01","PromptLc01", 1, ptlimsLc01);
  //  PromptLc01->SetBinContent(1, 0.34317705);
  //  PromptLc01->SetBinError(1, 0.09);

  //  TGraphAsymmErrors* gPromptLcSystematics01 = new TGraphAsymmErrors(1, ptlimsmiddlePrompt01, yvaluncPrompt01);
  //  for (Int_t i = 0; i < 1; i++) {
  //    Double_t PromptValue = PromptLc01->GetBinContent(i+1);
  //    Double_t ptx = 0.3;
  //    Double_t errylow = 0.05;
  //    Double_t erryhigh = 0.05;
  ////    Double_t errxlow = 0.23;
  ////    Double_t errxhigh = 0.23;
  //    gPromptLcSystematics01->SetPoint(i, ptlimsmiddlePrompt01[i], PromptValue);
  //    gPromptLcSystematics01->SetPointError(i, ptx, ptx, errylow, erryhigh);
  //  }

  //  gPromptLcSystematics01->SetFillStyle(0);
  //  gPromptLcSystematics01->SetFillColor(kRed+1);
  //  gPromptLcSystematics01->SetLineWidth(2);
  //  gPromptLcSystematics01->SetLineColor(kRed+1);

  const Int_t nptlimsExtra = 7;
  Float_t ptlimsExtral[nptlimsExtra + 1] = {0., 2., 4., 6., 8., 12., 24., 26.};

  TH1D *hrefPrompt = new TH1D("hrefPrompt", "hrefPrompt", nptlimsExtra, ptlimsExtral);
  hrefPrompt->SetTitle("");
  hrefPrompt->GetYaxis()->SetTitle("Baryon / Meson");
  // hrefPrompt->GetYaxis()->SetTitle("Non-prompt #Lambda_{c}^{+}/D^{0}");
  hrefPrompt->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  hrefPrompt->SetMinimum(0.01);
  hrefPrompt->SetMaximum(2.99);
  // hrefPrompt->SetMaximum(1.79);
  SetStyleHisto(hrefPrompt);
  hrefPrompt->GetYaxis()->SetTitleSize(0.05);
  hrefPrompt->SetLineWidth(1);
  hrefPrompt->GetYaxis()->SetTitleOffset(1.3);

  //  Double_t errxlowPrompt[8] = {};
  //  Double_t errxhighPrompt[8] = {};
  TGraphAsymmErrors *gPromptLcSystematics = new TGraphAsymmErrors(5, ptlimsmiddlePrompt, yvaluncPrompt);
  for (Int_t i = 0; i < 5; i++)
  {
    Double_t PromptValue = promptLc->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    Double_t errylow = promptLcSyst->GetBinContent(i + 1);
    Double_t erryhigh = promptLcSyst->GetBinContent(i + 1);
    //    Double_t errxlow = 0.23;
    //    Double_t errxhigh = 0.23;
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
    //    Double_t errxlow = 0.23;
    //    Double_t errxhigh = 0.23;
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
  hrefFD->GetYaxis()->SetTitle("Baryon / Meson");
  // hrefFD->GetYaxis()->SetTitle("Non-prompt #Lambda_{c}^{+}/D^{0}");
  hrefFD->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  //  hrefFD->SetMinimum(0.);
  //  hrefFD->SetMaximum(2.7);
  SetStyleHisto(hrefFD);
  hrefFD->GetYaxis()->SetTitleSize(0.05);
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
  TFile *inputFileLbOverBLHCb = new TFile("./LambdaBOverB_pp13TeV.root", "read");
  TH1D *hLbOverBLHCb = (TH1D *)inputFileLbOverBLHCb->Get("result__3");
  TGraphAsymmErrors *grae = (TGraphAsymmErrors *)inputFileLbOverBLHCb->Get("Graph5");
  grae->SetName("Graph5");
  grae->SetTitle("Graph");
  grae->SetFillStyle(0);

  // ci = TColor::GetColor("#0000ff");
  // grae->SetLineColor(ci);
  // grae->SetLineWidth(2);

  // ci = TColor::GetColor("#0000ff");
  // grae->SetMarkerColor(ci);
  // grae->SetMarkerStyle(20);

  TH1F *Graph_Graph53001 = new TH1F("Graph_Graph53001", "Graph", 100, -110001.8, 10032.02);
  Graph_Graph53001->SetMinimum(-0.05530028);
  Graph_Graph53001->SetMaximum(0.608303);
  Graph_Graph53001->SetDirectory(0);
  Graph_Graph53001->SetStats(0);
  Graph_Graph53001->SetLineWidth(2);
  Graph_Graph53001->SetMarkerStyle(20);
  Graph_Graph53001->GetXaxis()->SetNdivisions(505);
  Graph_Graph53001->GetXaxis()->SetLabelFont(132);
  Graph_Graph53001->GetXaxis()->SetLabelOffset(0.01);
  Graph_Graph53001->GetXaxis()->SetLabelSize(0.06);
  Graph_Graph53001->GetXaxis()->SetTitleSize(0.072);
  Graph_Graph53001->GetXaxis()->SetTitleOffset(0.95);
  Graph_Graph53001->GetXaxis()->SetTitleFont(132);
  Graph_Graph53001->GetYaxis()->SetLabelFont(132);
  Graph_Graph53001->GetYaxis()->SetLabelOffset(0.01);
  Graph_Graph53001->GetYaxis()->SetLabelSize(0.06);
  Graph_Graph53001->GetYaxis()->SetTitleSize(0.072);
  Graph_Graph53001->GetYaxis()->SetTitleOffset(0.95);
  Graph_Graph53001->GetYaxis()->SetTitleFont(132);
  Graph_Graph53001->GetZaxis()->SetLabelFont(132);
  Graph_Graph53001->GetZaxis()->SetLabelSize(0.06);
  Graph_Graph53001->GetZaxis()->SetTitleSize(0.072);
  Graph_Graph53001->GetZaxis()->SetTitleOffset(1.2);
  Graph_Graph53001->GetZaxis()->SetTitleFont(132);
  grae->SetHistogram(Graph_Graph53001);

  SetStyleHisto(hLbOverBLHCb);
  hLbOverBLHCb->GetYaxis()->SetTitleSize(0.05);
  hLbOverBLHCb->SetLineWidth(2);
  hLbOverBLHCb->SetMarkerColor(kGreen + 1);
  hLbOverBLHCb->SetLineColor(kGreen + 1);
  hLbOverBLHCb->SetMarkerStyle(24);
  hLbOverBLHCb->SetMarkerSize(2);
  hLbOverBLHCb->Draw("Esame");

  grae->SetMarkerColor(kGreen + 1);
  grae->SetLineColor(kGreen + 1);
  grae->SetMarkerStyle(24);
  grae->Draw("e2z");

  TLatex infoLHCb;
  infoLHCb.SetNDC();
  infoLHCb.SetTextFont(43);
  infoLHCb.SetTextSize(ALICETextSize);
  //    infoLHCb.DrawLatex(0.6, 0.89, "LHCb");
  infoLHCb.DrawLatex(0.65, 0.89, "LHCb");
  infoLHCb.DrawLatex(0.23, 0.89, "ALICE");

  TLatex infosLHCb;
  infosLHCb.SetNDC();
  infosLHCb.SetTextFont(43);
  infosLHCb.SetTextSize(infoTextSize);
  infosLHCb.DrawLatex(0.65, 0.84, "pp, #sqrt{#it{s}} = 13 TeV");
  infosLHCb.DrawLatex(0.65, 0.79, "2 < #it{y}_{cms} < 4.5");

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

  TLatex infos;
  infos.SetNDC();
  infos.SetTextFont(43);
  infos.SetTextSize(infoTextSize);
  infos.DrawLatex(0.23, 0.84, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  infos.DrawLatex(0.23, 0.79, "#font[122]{-}0.96 < #it{y}_{cms} < 0.04");
  infos.DrawLatex(0.23, 0.66, "pp, #sqrt{#it{s}} = 13 TeV");
  infos.DrawLatex(0.23, 0.61, "#font[122]{-}0.5 < #it{y}_{cms} < 0.5");
  // infos.DrawLatex(0.36, 0.89, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  // infos.DrawLatex(0.36, 0.78, "pp, #sqrt{#it{s}} = 13 TeV");
  //  infos.DrawLatex(0.23, 0.78, "#font[122]{-}0.96 < #it{y}_{cms} < 0.04");

  TLatex inforef;
  inforef.SetNDC();
  inforef.SetTextFont(43);
  inforef.SetTextSize(infoTextSize);
  // inforef.DrawLatex(0.5, 0.68, "PRD 108 (2023) 112003");
  //  inforef.DrawLatex(0.62, 0.555, "arXiv:2211.14032");

  gPromptLcSystematics->Draw("same2");
  promptLc->Draw("e0 same");
  //  gPromptLcSystematics01->Draw("same2");
  //  PromptLc01->Draw("e0 same");
  gFDSystematics->Draw("same2");
  hLcOverD0->Draw("e0 same");
  //  gNorSystematics->Draw("same2");

  TLegend *legLHCb = new TLegend(0.23, 0.71, 0.33, 0.79);
  legLHCb->SetFillColor(0);
  legLHCb->SetFillStyle(0);
  legLHCb->SetBorderSize(0);
  legLHCb->SetMargin(0.46);
  legLHCb->SetTextSize(infoTextSize);
  legLHCb->SetTextFont(43);
  legLHCb->AddEntry(hLcOverD0, "Non-prompt #Lambda_{c}^{+} / D^{0}", "p");
  legLHCb->Draw("same");

  TLegend *legLHCb2 = new TLegend(0.23, 0.53, 0.33, 0.61);
  legLHCb2->SetFillColor(0);
  legLHCb2->SetFillStyle(0);
  legLHCb2->SetBorderSize(0);
  legLHCb2->SetMargin(0.46);
  legLHCb2->SetTextSize(infoTextSize);
  legLHCb2->SetTextFont(43);
  legLHCb2->AddEntry(promptLc, "Non-prompt #Lambda_{c}^{+} / D^{0}", "p");
  legLHCb2->Draw("same");

  TLegend *legLHCb3 = new TLegend(0.65, 0.70, 0.75, 0.78);
  legLHCb3->SetFillColor(0);
  legLHCb3->SetFillStyle(0);
  legLHCb3->SetBorderSize(0);
  legLHCb3->SetMargin(0.46);
  legLHCb3->SetTextSize(infoTextSize);
  legLHCb3->SetTextFont(43);
  legLHCb3->AddEntry(hLbOverBLHCb, "#Lambda_{b}^{0} / B^{0}", "p");
  legLHCb3->Draw("same");

  c1->SaveAs("NonPromptLcD0Ratio_pp_vs_pPb.pdf");
  c1->SaveAs("NonPromptLcD0Ratio_pp_vs_pPb.eps");
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
