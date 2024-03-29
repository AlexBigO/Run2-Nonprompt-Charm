#include <iostream>

using namespace std;

void SetStyleHisto(TH1D *h);
void SetStyleHisto(TH1F *h);

const Double_t ptlimsmiddlePrompt[8] = {0.5,1.5,2.5,3.5,4.5,5.5,7,10};
Double_t yvaluncPrompt[8] = {0.0};
const Double_t ptlimsmiddleFD[4]={3,6,10,18};
// Double_t yvaluncFD[4] = {0.269955,0.277465,0.227576,0.19715}; // myself
Double_t yvaluncFD[4] = {0.243497,0.25508,0.207956,0.197207}; // non-prompt merge in pp

const Double_t ptlimsmiddleRpPb[1]={26.};
Double_t yvaluncRpPb[1] = {1.};

int ALICETextSize = 26;
int infoTextSize = 22;
int legendTextSize = 18;

void DrawRpPb(){
  
//   // prompt RpPb
  
  TFile* promptD0File = new TFile("./HEPData-ins2593302-v1-Table_4.root", "read");
  TDirectoryFile *promptdir = (TDirectoryFile*)promptD0File->Get("Table 4");
  TH1F* promptRpPb = (TH1F*)promptdir->Get("Hist1D_y1");
  TH1F* promptRpPbStat = (TH1F*)promptdir->Get("Hist1D_y1_e1");
  TH1F* promptRpPbSystPlus = (TH1F*)promptdir->Get("Hist1D_y1_e2plus");
  TH1F* promptRpPbSystMinus = (TH1F*)promptdir->Get("Hist1D_y1_e2minus");
  TH1F* promptRpPbSystNor = (TH1F*)promptdir->Get("Hist1D_y1_e3");
  
  int nPtBinsPrompt = promptRpPb->GetNbinsX();
  for(int iPt = 0; iPt < nPtBinsPrompt; iPt++) {
    promptRpPb->SetBinError(iPt+1, promptRpPbStat->GetBinContent(iPt+1));
  }
  
  Double_t errxlowPrompt[8] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
  Double_t errxhighPrompt[8] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
  // Double_t errxlowPrompt[8] = {0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4};
  // Double_t errxhighPrompt[8] = {0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4};
  TGraphAsymmErrors* gRpPbPromptD0Systematics = new TGraphAsymmErrors(21, ptlimsmiddlePrompt, yvaluncPrompt);
  for (Int_t i = 0; i < 21; i++) {
    Double_t RpPbPrompt = promptRpPb->GetBinContent(i+1);
    Double_t ptx = ptlimsmiddlePrompt[i];
    Double_t errylow = -1. * promptRpPbSystMinus->GetBinContent(i+1);
    Double_t erryhigh = promptRpPbSystPlus->GetBinContent(i+1);
    gRpPbPromptD0Systematics->SetPoint(i, ptlimsmiddlePrompt[i], RpPbPrompt);
    gRpPbPromptD0Systematics->SetPointError(i, errxlowPrompt[i], errxhighPrompt[i], errylow, erryhigh);
  }

  gRpPbPromptD0Systematics->SetFillStyle(0);
  gRpPbPromptD0Systematics->SetFillColor(kWhite);
  gRpPbPromptD0Systematics->SetLineWidth(2);
  gRpPbPromptD0Systematics->SetLineColor(kRed+1);
  
  const Int_t nptlimsExtra = 9;
  Float_t ptlimsExtral[nptlimsExtra+1] = {0,1,2,3,4,5,6,8,12,26.5};
  
  TH1D* hrefPrompt = new TH1D("hrefPrompt","hrefPrompt", nptlimsExtra, ptlimsExtral);
  hrefPrompt->SetTitle("");
  hrefPrompt->GetYaxis()->SetTitle("#it{R}_{pPb}");
  hrefPrompt->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  hrefPrompt->SetMinimum(0.01);
  hrefPrompt->SetMaximum(2.7);
  SetStyleHisto(hrefPrompt);
  hrefPrompt->SetLineWidth(1);
  hrefPrompt->GetYaxis()->SetTitleOffset(1.3);
  
  // non-prompt D0 RpPb

  TFile *fRpPbFD = new TFile("./NonPrompt_RpPb_2_2.root", "read");

  TH1F* RpPbFDD0 = (TH1F*)fRpPbFD->Get("H_RpPb");
  
  TGraphAsymmErrors* gRpPbFDD0Systematics = new TGraphAsymmErrors(4, ptlimsmiddleFD, yvaluncFD);
  for (Int_t i = 0; i < 4; i++) {
   Double_t RpPbFD = RpPbFDD0->GetBinContent(i+1);
    Double_t ptx = 0.5;
    Double_t errylow = yvaluncFD[i]*RpPbFD;
    Double_t erryhigh = yvaluncFD[i]*RpPbFD;
    gRpPbFDD0Systematics->SetPoint(i, ptlimsmiddleFD[i], RpPbFD);
    gRpPbFDD0Systematics->SetPointError(i, ptx, ptx, errylow, erryhigh);
  }

  gRpPbFDD0Systematics->SetFillStyle(0);
  gRpPbFDD0Systematics->SetFillColor(kWhite);
  gRpPbFDD0Systematics->SetLineWidth(2);
  gRpPbFDD0Systematics->SetLineColor(kAzure+2);
  
  const Int_t nptlims = 4;
  Float_t ptlims[nptlims+1] = {2,4,8,12,26.5};
  
  TH1D* hrefFD = new TH1D("hrefFD","hrefFD", nptlims, ptlims);
  hrefFD->SetTitle("");
  hrefFD->GetYaxis()->SetTitle("#it{R}_{pPb}");
  hrefFD->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  hrefFD->SetMinimum(0.);
  hrefFD->SetMaximum(2.7);
  SetStyleHisto(hrefFD);
  hrefFD->SetLineWidth(1);
  hrefFD->GetYaxis()->SetTitleOffset(1.3);

  
  TGraphAsymmErrors* gNorSystematics = new TGraphAsymmErrors(1, ptlimsmiddleRpPb, yvaluncRpPb);
  for (Int_t i = 0; i < 1; i++) {
    Double_t ptx = 0.25;
    gNorSystematics->SetPoint(i, 26, 1.0);
    gNorSystematics->SetPointError(i, ptx, ptx, 0.037, 0.037);
  }

  gNorSystematics->SetFillStyle(1001);
  gNorSystematics->SetFillColor(kBlack);
  gNorSystematics->SetLineWidth(2);
  gNorSystematics->SetLineColor(kBlack);
  
  TCanvas* c1 = new TCanvas("c1", "c1", 0, 0, 520, 500);
  gStyle->SetOptStat(0);
  c1->SetTickx();
  c1->SetTicky();
  c1->SetBottomMargin(0.13);
  c1->SetLeftMargin(0.17);
  c1->SetTopMargin(0.05);
  c1->SetRightMargin(0.03);
  c1->cd();
  hrefPrompt->Draw("");
  hrefFD->Draw("same");
  // hrefFD->Draw("");
  
  SetStyleHisto(promptRpPb);
  promptRpPb->SetStats(0);
  promptRpPb->SetLineColor(kRed+1);
  promptRpPb->SetMarkerColor(kRed+1);
  promptRpPb->SetMarkerStyle(21);
  promptRpPb->SetMarkerSize(1.2);
  
  SetStyleHisto(RpPbFDD0);
  RpPbFDD0->SetStats(0);
  RpPbFDD0->SetLineColor(kAzure+2);
  RpPbFDD0->SetMarkerColor(kAzure+2);
  RpPbFDD0->SetMarkerStyle(20);
  RpPbFDD0->SetMarkerSize(1.2);
  
  TLine* unit = new TLine(0, 1, 39, 1);
  unit->SetLineStyle(3);
  unit->Draw();
  
  
  TLatex info;
  info.SetNDC();
  info.SetTextFont(43);
  info.SetTextSize(ALICETextSize);
  info.DrawLatex(0.20, 0.89, "ALICE");
  // info.DrawLatex(0.20, 0.89, "ALICE Preliminary");
  
  TLatex info2;
  info2.SetNDC();
  info2.SetTextFont(43);
  info2.SetTextSize(infoTextSize);
  info2.DrawLatex(0.20, 0.82, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  info2.SetTextSize(legendTextSize);
  info2.DrawLatex(0.65, 0.89, "#font[122]{-}0.96 < #it{y}_{cms} < 0.04");
  
  gRpPbPromptD0Systematics->Draw("same2");
  promptRpPb->Draw("e0 same");
  gRpPbFDD0Systematics->Draw("same2");
  RpPbFDD0->Draw("e0 same");
  gNorSystematics->Draw("same2");
    
  TLatex inforef;
  inforef.SetNDC();
  inforef.SetTextFont(43);
  inforef.SetTextSize(15);
  inforef.DrawLatex(0.60, 0.61, " PRC 107 (2023) 6, 064901");

  TLegend* leg = new TLegend(0.61, 0.65, 0.81, 0.8);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetMargin(0.46);
  leg->SetTextSize(legendTextSize);
  leg->SetTextFont(43);
  leg->AddEntry(RpPbFDD0, "Non-prompt #Lambda_{c}^{+}", "p");
  leg->AddEntry(promptRpPb, "Prompt #Lambda_{c}^{+}", "p");
  leg->Draw();

  c1->SaveAs("RpPbLc_promptFD.pdf");
  c1->SaveAs("RpPbLc_promptFD.png");
  c1->SaveAs("RpPbLc_promptFD.eps");

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
  h->GetYaxis()->SetDecimals(kTRUE);
  //h->GetYaxis()->SetNdivisions(507);
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
  h->GetYaxis()->SetDecimals(kTRUE);
  //h->GetYaxis()->SetNdivisions(507);
  h->GetXaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetTitleOffset(1.0);
  h->GetXaxis()->SetLabelSize(0.05);
//  h->GetXaxis()->SetNdivisions(505);
  h->GetXaxis()->SetNdivisions(510);
}
