#include "TCanvas.h"
#include "TFile.h"
#include "TGaxis.h"
#include "TGraphAsymmErrors.h"
#include "TH1.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"
#include <iostream>

using namespace std;

void SetStyle();
void SetStyleHisto(TH1D *h);
void SetStyleHisto(TH1F *h);
void NormaliseHist1d(TH1 *h);

const Int_t colors[] = {kGreen + 2, kBlue - 4, kRed, kOrange + 7};
const Int_t markers[] = {20, 21, 33, 34};
const Int_t npoints[] = {5, 3, 4, 4, 4, 4, 4};
const Int_t nPtBins = 10;  // 11;
const Double_t ptlimsmiddle[nPtBins] = {2.5, 3.5, 4.5, 5.5, 6.5,
                                   7.5, 9,   11,  14,  20};
                                  //  {1.5, 2.5, 3.5, 4.5, 5.5, 6.5,
                                  //  7.5, 9,   11,  14,  20};
const Int_t nPtBinsCoarse = 10;
Double_t ptlimsCoarse[nPtBinsCoarse + 1] = {2., 3.,  4.,  5.,  6.,
                                            7., 8., 10., 12., 16., 24.};
Double_t ptbinwidthCoarse[nPtBinsCoarse] = {1., 1., 1., 1., 1.,
                                            1., 2., 2., 4., 8.};
const Double_t ptlimsmiddlePrompt[20] = {
    1.25, 1.75, 2.25, 2.75, 3.25, 3.75, 4.25, 4.75, 5.25, 5.75,
    6.25, 6.75, 7.25, 7.75, 8.5,  9.5,  11.,  14.,  20.,  30.};
    // {
    // 0.5,  1.25, 1.75, 2.25, 2.75, 3.25, 3.75, 4.25, 4.75, 5.25, 5.75,
    // 6.25, 6.75, 7.25, 7.75, 8.5,  9.5,  11.,  14.,  20.,  30.};
Double_t yvaluncPrompt[21] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
                              0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
Double_t xerrPrompt[21] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                           0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                           0.25, 0.25, 0.25, 0.45, 0.45, 0.45, 0.45};

bool DrawAllPoints = false;

enum Particles: uint8_t {
  kD0 = 0,
  kDplus,
  kLambdac
};

void makeCrossSection_pPb_NonPrompt_noFONLL_D0Dplus(bool isPreliminary = kTRUE, uint8_t particle = Particles::kDplus) {

  TGaxis::SetMaxDigits(3);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  TFile* promptFileHEP = nullptr;
  TDirectoryFile *dir = nullptr;
  TH1F *hCroSecPrompt = nullptr;
  TH1F *hCroSecPromptStat = nullptr;
  TH1F *hCroSecPromptSystPlus = nullptr;
  TH1F *hCroSecPromptSystMinus = nullptr;

  if (particle == kD0) {
    promptFileHEP = new TFile("./HEPData-ins1738950-v1-root.root", "read");
    dir = (TDirectoryFile *)promptFileHEP->Get("D0 pPb cross section, Figure 7 ");
  } else if (particle == kDplus) {
    promptFileHEP = new TFile("/home/abigot/AnalysisNonPromptDplus/HEPData_CrossSectionDplus_pPb_prompt.root", "read");
    dir = (TDirectoryFile *)promptFileHEP->Get("D+ pPb cross section, Figure 7 ");
  }
  hCroSecPrompt = (TH1F *)dir->Get("Hist1D_y1");
  hCroSecPromptStat = (TH1F *)dir->Get("Hist1D_y1_e1");
  hCroSecPromptSystPlus = (TH1F *)dir->Get("Hist1D_y1_e2plus");
  hCroSecPromptSystMinus = (TH1F *)dir->Get("Hist1D_y1_e2minus");

  TGraphAsymmErrors *gCroSecPromptD0Systematics =
      new TGraphAsymmErrors(20, ptlimsmiddlePrompt, yvaluncPrompt);
  for (Int_t i = 0; i < 20; i++) {
    Double_t Crosssection = hCroSecPrompt->GetBinContent(i + 1);
    Double_t ptx = ptlimsmiddlePrompt[i];
    Double_t errylow = -1. * hCroSecPromptSystMinus->GetBinContent(i + 1);
    Double_t erryhigh = hCroSecPromptSystPlus->GetBinContent(i + 1);
    Double_t errxlow = 0.25;
    Double_t errxhigh = 0.25;
    gCroSecPromptD0Systematics->SetPoint(i, ptlimsmiddlePrompt[i],
                                         Crosssection);
    gCroSecPromptD0Systematics->SetPointError(i, xerrPrompt[i], xerrPrompt[i],
                                              errylow, erryhigh);
  }

  //  gCroSecPromptD0Systematics->SetFillStyle(1001);
  gCroSecPromptD0Systematics->SetFillStyle(0);
  //  gCroSecPromptD0Systematics->SetFillColor(kRed-9);
  gCroSecPromptD0Systematics->SetFillColor(kWhite);
  gCroSecPromptD0Systematics->SetLineWidth(2);
  gCroSecPromptD0Systematics->SetLineColor(kRed - 9);

  for (Int_t i = 0; i < 21; i++) {
    hCroSecPrompt->SetBinError(i + 1,
                                 hCroSecPromptStat->GetBinContent(i + 1));
  }
  hCroSecPrompt->SetMarkerStyle(33);
  SetStyleHisto(hCroSecPrompt);
  hCroSecPrompt->SetMarkerSize(1);
  hCroSecPrompt->SetMarkerColor(kRed + 2);
  hCroSecPrompt->SetLineColor(kRed + 2);

  TFile *f[3];
  if (particle == kD0) {
    f[2] = TFile::Open("CrossSectionSystematics.root", "READ");
  } else if (particle == kDplus) {
    f[2] = TFile::Open("/home/abigot/AnalysisNonPromptDplus/Run2pPb5Tev/4_Analysis/5_CrossSection/wptweights_cent/cross_section_divided_by_BR.root", "READ");
  }

  TH1F *hD0[4];
  //  TH1D *hD0D[4];
  //  TH1F* hSystHigh[4];
  //  TH1F* hSystLow[4];

  if (particle == kD0) {
    hD0[2] = (TH1F *)f[2]->Get("hCrossSection");
    hD0[2]->Scale(1. / 0.03947);
  } else if (particle == kDplus) {
    hD0[2] = (TH1F *)f[2]->Get("hCorrYield");
    // already divided by BR in the input file
  }

  // For D0
  // Double_t SystRawYield[11] = {0.03, 0.02, 0.01, 0.01, 0.01, 0.01,
  //                              0.01, 0.01, 0.02, 0.02, 0.03};
  // Double_t SystBDTSelection[11] = {0.05, 0.03, 0.03, 0.03, 0.03, 0.03,
  //                                  0.03, 0.04, 0.04, 0.04, 0.04};
  // //  Double_t SystTrackingWOBudget[3] = {0.05, 0.05, 0.05};
  // //  Double_t SystMaterialBudget[3] = {0.02, 0.02, 0.02};
  // Double_t SystpTWeights[11] = {0.07, 0.05, 0.03, 0.02, 0.01, 0.,
  //                               0.,   0.,   0.,   0.,   0.02};
  // Double_t SystFeedDown[11] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
  //                              0.01, 0.01, 0.01, 0.01, 0.02};
  // Double_t SystTracking[11] = {0.02, 0.02, 0.02,  0.02, 0.02, 0.02,
  //                              0.02, 0.02, 0.025, 0.03, 0.03};
  // //  Double_t SystBR[11] = {0.0003, 0.0003, 0.0003, 0.0003, 0.0003, 0.0003,
  // //  0.0003, 0.0003, 0.0003, 0.0003, 0.0003}; Double_t SystLumi[11] = {0.037,
  // //  0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037};
  // Double_t SystTotal[11] = {0.};

  // const uint8_t nPtBins = 10;

  Double_t SystRawYield[nPtBins] = {0.06, 0.03, 0.03, 0.02, 0.02, 0.03, 0.02, 0.05, 0.03, 0.07};
  Double_t SystBDTSelection[nPtBins] = {0.06, 0.06, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03};
  //  Double_t SystTrackingWOBudget[3] = {0.05, 0.05, 0.05};
  //  Double_t SystMaterialBudget[3] = {0.02, 0.02, 0.02};
  Double_t SystpTWeights[nPtBins] = {0.01, 0.01, 0.01, 0.005, 0.005, 0.005, 0., 0., 0., 0.};
  Double_t SystFeedDown[nPtBins] = {0.02, 0.04, 0.02, 0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.06};
  Double_t SystTracking[nPtBins] = {0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.04, 0.04, 0.04};
  //  Double_t SystBR[11] = {0.0003, 0.0003, 0.0003, 0.0003, 0.0003, 0.0003,
  //  0.0003, 0.0003, 0.0003, 0.0003, 0.0003}; Double_t SystLumi[11] = {0.037,
  //  0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037};
  Double_t SystTotal[nPtBins] = {0.};

  for (Int_t i = 0; i < nPtBins; i++) {
    SystTotal[i] = TMath::Sqrt(SystRawYield[i] * SystRawYield[i] +
                               SystBDTSelection[i] * SystBDTSelection[i] +
                               SystpTWeights[i] * SystpTWeights[i] +
                               SystFeedDown[i] * SystFeedDown[i] +
                               SystTracking[i] * SystTracking[i]);
  }

  const Double_t yvalunc[nPtBins] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
  /// Get Graph for total systematics on cross section
  TGraphAsymmErrors *gSigmaSystematics =
      new TGraphAsymmErrors(nPtBins, ptlimsmiddle, yvalunc);
  for (Int_t i = 0; i < nPtBins; i++) {
    Double_t Crosssection = hD0[2]->GetBinContent(i + 1);
    Double_t ptx = ptlimsmiddle[i];
    Double_t errylow = SystTotal[i] * Crosssection;
    Double_t erryhigh = SystTotal[i] * Crosssection;
    Double_t errxlow = 0.45;
    Double_t errxhigh = 0.45;
    gSigmaSystematics->SetPoint(i, ptlimsmiddle[i], Crosssection);
    gSigmaSystematics->SetPointError(i, errxlow, errxhigh, errylow, erryhigh);
  }

  gSigmaSystematics->SetFillStyle(0);
  gSigmaSystematics->SetFillColor(kWhite);
  gSigmaSystematics->SetLineWidth(2);
  gSigmaSystematics->SetLineColor(kAzure + 1);

  const Int_t nptlims = nPtBins + 1; //12;
  const Int_t nptlimsExtra = 22;
  Float_t ptlims[nptlims + 1] = {2., 3.,  4.,  5.,  6.,
                                 7., 8., 10., 12., 16., 24.};
  Float_t ptlimsExtral[nptlimsExtra + 1] = {0.,  1.,  1.5, 2.,  2.5, 3.,  3.5, 4.,
                              4.5, 5.,  5.5, 6.,  6.5, 7.,  7.5, 8.,
                              9.,  10., 12., 16., 24., 36., 38.};
  TH1D *href = new TH1D("href", "href", nptlimsExtra, ptlimsExtral);
  href->GetYaxis()->SetTitle(
      "d^{2}#sigma/(d#it{y} d#it{p}_{T}) (#mub GeV^{-1}#it{c})");
  href->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  href->SetMinimum(0.02);
  href->SetMaximum(700000);
  SetStyleHisto(href);
  href->SetLineWidth(1);
  href->GetYaxis()->SetTitleOffset(1.3);

  TH1D *hrefRatio = (TH1D *)href->Clone("hrefRatio");
  hrefRatio->SetMinimum(0);
  hrefRatio->SetMaximum(1.4);
  hrefRatio->GetYaxis()->SetTitle("#Lambda_{c} / D^{0}");

  TH1D *hrefvfns = new TH1D("hrefvfns", "hrefvfns", nptlimsExtra, ptlimsExtral);
  hrefvfns->GetYaxis()->SetTitle(
      "d^{2}#sigma/d#it{y} d#it{p}_{T} (#mub #it{c}/GeV)");
  hrefvfns->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  hrefvfns->SetMinimum(0.05);
  hrefvfns->SetMaximum(400);
  SetStyleHisto(hrefvfns);
  hrefvfns->SetLineWidth(1);

  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 600, 750);
  gStyle->SetOptStat(0);
  TPad *p1 = new TPad("p1", "p1", 0., 0., 1, 1);
  p1->Draw();
  p1->cd();
  p1->SetTickx();
  p1->SetTicky();
  p1->SetLogy();
  p1->SetBottomMargin(0.13);
  p1->SetLeftMargin(0.17);
  p1->SetTopMargin(0.05);
  p1->SetRightMargin(0.03);
  //href->GetXaxis()->SetRangeUser(0, 36);
  href->Draw("");

  c1->cd();
  TPad *p2 = new TPad("p2", "p2", 0., 0.0, 1, 0.25);
  //  p2->Draw();
  p2->cd();
  p2->SetTickx();
  p2->SetTicky();
  p2->SetBottomMargin(0.4);
  p2->SetLeftMargin(0.17);
  p2->SetTopMargin(0.0);
  p2->SetRightMargin(0.03);
  //  p2->Draw();

  p1->cd();

  SetStyleHisto(hD0[2]);
  hD0[2]->SetMarkerStyle(20);
  hD0[2]->SetLineColor(kAzure + 2);
  hD0[2]->SetMarkerColor(kAzure + 2);
  hD0[2]->SetMarkerSize(0.8);
  hD0[2]->SetStats(0);
  // hD0[2]->SetLineColor(kRed);

  TLatex info;
  info.SetNDC();
  info.SetTextFont(43);
  info.SetTextSize(30);
  info.DrawLatex(0.20, 0.89, "ALICE Preliminary");

  TLatex infos;
  infos.SetNDC();
  infos.SetTextFont(43);
  infos.SetTextSize(25);
  infos.DrawLatex(0.20, 0.84,
                  "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  infos.DrawLatex(0.62, 0.89, "#font[122]{-}0.96 < #it{y}_{cms} < 0.04");

  TLatex inforef;
  inforef.SetNDC();
  inforef.SetTextFont(43);
  inforef.SetTextSize(22);
  inforef.DrawLatex(0.59, 0.59, "JHEP 12 (2019) 092");

  //  info.DrawLatex(0.6, 0.85, "Non-Prompt D^{0}");//,
  //  info.DrawLatex(0.48, 0.7, "FONLL + PYTHIA8 Decayer");

  //  TLatex info5;
  //  info5.SetNDC();
  //  info5.SetTextFont(43);
  //  info5.SetTextSize(15);
  //  info5.DrawLatex(0.48, 0.66, "#it{f} (b #rightarrow B^{0}, b #rightarrow
  //  B^{+})_{LHCb}, BR (H_{b} #rightarrow D^{0}+X)_{PYTHIA 8}");//,
  //  info1.DrawLatex(0.5, 0.74-0.02, "average of");
  // info.DrawLatex(0.20, 0.70, "#Lambda_{c}^{+} #rightarrow pK^{0}_{S}");
  //  if (isPreliminary){
  // info.DrawLatex(0.28, 0.85, "ALICE");
  // info.DrawLatex(0.28, 0.85, "ALICE");
  // info.DrawLatex(0.22, 0.2-0.06, "Preliminary");
  //    }

  TLatex info2;
  info2.SetNDC();
  info2.SetTextFont(43);
  info2.SetTextSize(20);
  //  info2.DrawLatex(0.21, 0.19, "#pm3.7% lumi. unc. not shown");
  //  info2.DrawLatex(0.21, 0.22, "#pm0.76% BR unc. not shown");

  info2.DrawLatex(0.54, 0.45, "#pm 3.7% lumi. unc. not shown");
  if (particle == kD0) {
    info2.DrawLatex(0.54, 0.5, "#pm 0.76% BR unc. not shown");
  } else if (particle == kDplus) {
    info2.DrawLatex(0.54, 0.5, "#pm 1.7% BR unc. not shown");
  }

  //  gPOWHEGB->Draw("e5ssame");
  //  gPOWHEGcentB->Draw("ezsame");
  gSigmaSystematics->Draw("same2");
  hD0[2]->Draw("e0 same");

  gCroSecPromptD0Systematics->Draw("same2");
  hCroSecPrompt->Draw("e0 same");

  TLegend *leg = new TLegend(0.45, 0.6, 0.75, 0.75);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetMargin(0.46);
  leg->SetTextSize(26);
  leg->SetTextFont(43);
  if (particle == kD0) {
    leg->AddEntry(hD0[2], "Non-prompt D^{0}", "pl");
    leg->AddEntry(hCroSecPrompt, "Prompt D^{0}", "pl");
  }  else if (particle == kDplus) {
    leg->AddEntry(hD0[2], "Non-prompt D^{+}", "pl");
    leg->AddEntry(hCroSecPrompt, "Prompt D^{+}", "pl");
  }
  leg->Draw();

  c1->SaveAs("./CrossSectionDplusPromptAndFD.pdf");
  c1->SaveAs("./CrossSectionDplusPromptAndFD.eps");
}

void SetStyle() {
  cout << "Setting style!" << endl;

  gStyle->Reset("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  gStyle->SetCanvasColor(10);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameLineWidth(1);
  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetPadColor(10);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetPadTopMargin(0.07);
  gStyle->SetPadRightMargin(0.07);
  gStyle->SetHistLineWidth(1);
  gStyle->SetHistLineColor(kRed);
  gStyle->SetFuncWidth(2);
  gStyle->SetFuncColor(kGreen);
  gStyle->SetLineWidth(2);
  gStyle->SetLabelSize(0.055, "xyz");
  gStyle->SetLabelOffset(0.01, "y");
  gStyle->SetLabelOffset(0.01, "x");
  gStyle->SetLabelColor(kBlack, "xyz");
  // gStyle->SetTitleSize(0.055,"xyz");
  // gStyle->SetTitleOffset(1.5,"y");
  // gStyle->SetTitleOffset(1.15,"x");
  gStyle->SetTitleFillColor(kWhite);
  gStyle->SetTextSizePixels(30);
  gStyle->SetTextFont(42);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);
  gStyle->SetLegendFont(42);
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(0.7);
  gStyle->SetMarkerColor(kBlack);
}

void SetStyleHisto(TH1D *h) {

  h->SetLineColor(kBlack);
  h->SetLineWidth(2);
  h->GetYaxis()->SetLabelFont(42);
  h->GetYaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleOffset(1);
  h->GetYaxis()->SetLabelSize(0.05);
  h->GetYaxis()->SetDecimals(kTRUE);
  // h->GetYaxis()->SetNdivisions(507);
  h->GetXaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetTitleOffset(1.0);
  h->GetXaxis()->SetLabelSize(0.05);
  h->GetXaxis()->SetNdivisions(510);
}

void SetStyleHisto(TH1F *h) {

  h->SetLineColor(kBlack);
  h->SetLineWidth(2);
  h->GetYaxis()->SetLabelFont(42);
  h->GetYaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleOffset(1);
  h->GetYaxis()->SetLabelSize(0.05);
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

void NormaliseHist1d(TH1 *h) {
  if (h) {
    // dN/dpt
    for (Int_t i = 1; i <= h->GetNbinsX(); i++) {
      h->SetBinContent(i,
                       h->GetBinContent(i) / (h->GetXaxis()->GetBinWidth(i)));
      //		hnew->SetBinError(i,hnew->GetBinContent(i)/(hnew->GetBinWidth(i)
      //* TMath::Sqrt(hnew->GetBinContent(i)))); // may need to look at again
      h->SetBinError(i, h->GetBinError(i) / (h->GetXaxis()->GetBinWidth(i)));
    }
  } else {
    cout << "can't normalise hist - not found" << endl;
  }
}
