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
const Int_t nPtBins = 11;
const Double_t ptlimsmiddle[11] = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5,
                                   7.5, 9,   11,  14,  20};
const Int_t nPtBinsCoarse = 11;
Double_t ptlimsCoarse[nPtBinsCoarse + 1] = {1., 2., 3.,  4.,  5.,  6.,
                                            7., 8., 10., 12., 16., 24.};
Double_t ptbinwidthCoarse[nPtBinsCoarse] = {1., 1., 1., 1., 1., 1.,
                                            1., 2., 2., 4., 8.};
const Double_t ptlimsmiddlePrompt[21] = {
    0.5,  1.25, 1.75, 2.25, 2.75, 3.25, 3.75, 4.25, 4.75, 5.25, 5.75,
    6.25, 6.75, 7.25, 7.75, 8.5,  9.5,  11.,  14.,  20.,  30.};
Double_t yvaluncPrompt[21] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
                              0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};

bool DrawAllPoints = false;

void DrawCutVarFit(bool isPreliminary = kTRUE) {

  //  TGaxis::SetMaxDigits(3);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  TFile *CutVarFile =
      new TFile("/Users/jon/alice/DmesonAnalysis_new-mod/CutVariation/"
                "centralFD_weightptcent_newcentral/"
                "CutVary_FD_centralFD_weightptcent_newcentral.root",
                "read");
  TH1F *hRawYieldsVsCutPt_pT3_4 =
      (TH1F *)CutVarFile->Get("hRawYieldsVsCutPt_pT3_4");
  TH1F *hRawYieldPromptVsCut_pT3_4 =
      (TH1F *)CutVarFile->Get("hRawYieldPromptVsCut_pT3_4");
  TH1F *hRawYieldFDVsCut_pT3_4 =
      (TH1F *)CutVarFile->Get("hRawYieldFDVsCut_pT3_4");
  TH1F *hRawYieldsVsCutReSum_pT3_4 =
      (TH1F *)CutVarFile->Get("hRawYieldsVsCutReSum_pT3_4");

  SetStyleHisto(hRawYieldsVsCutPt_pT3_4);
  SetStyleHisto(hRawYieldPromptVsCut_pT3_4);
  SetStyleHisto(hRawYieldFDVsCut_pT3_4);
  SetStyleHisto(hRawYieldsVsCutReSum_pT3_4);

  hRawYieldsVsCutPt_pT3_4->SetMarkerStyle(20);
  hRawYieldsVsCutPt_pT3_4->SetMarkerSize(1);
  hRawYieldsVsCutPt_pT3_4->SetMarkerColor(kBlack);
  hRawYieldsVsCutPt_pT3_4->SetLineColor(kBlack);

  hRawYieldPromptVsCut_pT3_4->SetMarkerStyle(33);
  hRawYieldPromptVsCut_pT3_4->SetMarkerSize(1);
  hRawYieldPromptVsCut_pT3_4->SetMarkerColor(kRed + 1);
  hRawYieldPromptVsCut_pT3_4->SetLineColor(kRed + 1);

  hRawYieldFDVsCut_pT3_4->SetMarkerStyle(33);
  hRawYieldFDVsCut_pT3_4->SetMarkerSize(1);
  hRawYieldFDVsCut_pT3_4->SetMarkerColor(kAzure + 4);
  hRawYieldFDVsCut_pT3_4->SetLineColor(kAzure + 4);

  hRawYieldsVsCutReSum_pT3_4->SetMarkerStyle(33);
  hRawYieldsVsCutReSum_pT3_4->SetMarkerSize(1);
  hRawYieldsVsCutReSum_pT3_4->SetMarkerColor(kGreen + 2);
  hRawYieldsVsCutReSum_pT3_4->SetLineColor(kGreen + 2);

  hRawYieldsVsCutPt_pT3_4->GetYaxis()->SetTitle("Raw yield");
  hRawYieldsVsCutPt_pT3_4->GetYaxis()->SetMaxDigits(3);
  hRawYieldsVsCutPt_pT3_4->GetXaxis()->SetTitle("ML based selection");
  hRawYieldsVsCutPt_pT3_4->SetMinimum(0.1);
  hRawYieldsVsCutPt_pT3_4->SetMaximum(12000);
  hRawYieldsVsCutPt_pT3_4->SetLineWidth(2);
  hRawYieldsVsCutPt_pT3_4->GetYaxis()->SetTitleOffset(1.);

  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 750, 750);
  gStyle->SetOptStat(0);
  c1->SetTickx();
  c1->SetTicky();
  c1->SetBottomMargin(0.13);
  c1->SetLeftMargin(0.17);
  c1->SetTopMargin(0.06);
  c1->SetRightMargin(0.03);
  c1->cd();

  hRawYieldsVsCutPt_pT3_4->Draw();
  hRawYieldPromptVsCut_pT3_4->Draw("HISTsame");
  hRawYieldPromptVsCut_pT3_4->SetFillStyle(3154);
  hRawYieldPromptVsCut_pT3_4->SetFillColor(kRed + 1);
  hRawYieldFDVsCut_pT3_4->Draw("HISTsame");
  hRawYieldFDVsCut_pT3_4->SetFillStyle(3145);
  hRawYieldFDVsCut_pT3_4->SetFillColor(kAzure + 4);
  hRawYieldsVsCutReSum_pT3_4->Draw("HISTsame");
  //  info.DrawLatex(0.65, 0.85, "-0.96 < #it{y} < 0.04");

  //  TLatex inforef;
  //  inforef.SetNDC();
  //  inforef.SetTextFont(43);
  //  inforef.SetTextSize(22);
  //  inforef.DrawLatex(0.59, 0.59, "JHEP 12 (2019) 092");

  //  info.DrawLatex(0.6, 0.85, "Non-Prompt D^{0}");//,
  //  info.DrawLatex(0.48, 0.7, "FONLL + PYTHIA8 Decayer");

  TLatex info;
  info.SetNDC();
  info.SetTextFont(43);
  info.SetTextSize(30);
  info.DrawLatex(0.20, 0.88, "ALICE Preliminary");

  TLatex infos;
  infos.SetNDC();
  infos.SetTextFont(43);
  infos.SetTextSize(25);
  infos.DrawLatex(0.20, 0.83,
                  "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  infos.DrawLatex(0.7, 0.88, "#font[122]{-}0.96 < #it{y} < 0.04");

  TLatex infoPt;
  infoPt.SetNDC();
  infoPt.SetTextFont(43);
  infoPt.SetTextSize(30);
  infoPt.DrawLatex(0.55, 0.72, "3 < #it{p}_{T} < 4 GeV/#it{c}");

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

  //  TLatex info2;
  //  info2.SetNDC();
  //  info2.SetTextFont(43);
  //  info2.SetTextSize(15);
  //  info2.DrawLatex(0.21, 0.17, "#pm 3.7% lumi. unc. not shown");
  //  info2.DrawLatex(0.21, 0.22, "#pm 0.76% BR unc. not shown");

  TLegend *leg = new TLegend(0.55, 0.5, 0.7, 0.7);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetMargin(0.46);
  leg->SetTextSize(28);
  leg->SetTextFont(43);
  leg->AddEntry(hRawYieldsVsCutPt_pT3_4, "Data", "p");
  leg->AddEntry(hRawYieldPromptVsCut_pT3_4, "Prompt D^{0}", "F");
  leg->AddEntry(hRawYieldFDVsCut_pT3_4, "Non-prompt D^{0}", "F");
  leg->AddEntry(hRawYieldsVsCutReSum_pT3_4, "Total", "l");
  leg->Draw();
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
