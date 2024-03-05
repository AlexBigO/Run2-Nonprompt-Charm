#include <iostream>
#include "TH1.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLatex.h"
#include "TLegend.h"

using namespace std;

void SetStyle();
void SetStyleHisto(TH1D *h);
void SetStyleHisto(TH1F *h);
void NormaliseHist1d(TH1 *h);

const Int_t colors[] = {kGreen+2, kBlue-4, kRed, kOrange+7};
const Int_t markers[] = {20, 21, 33, 34};
const Int_t npoints[] = {5, 3, 4, 4, 4, 4, 4};
const Int_t nPtBins = 3;
const Double_t ptlimsmiddle[4]={3,6,10,18};
const Int_t nPtBinsCoarse = 10;
Double_t ptlimsCoarse[nPtBinsCoarse+1] = {0,1,2,3,4,5,6,8,12,24};
Double_t ptbinwidthCoarse[nPtBinsCoarse] = {1,1,1,1,1,1,2,4,12};
const Double_t ptlimsmiddlePrompt[9] = {0.5,1.5,2.5,3.5,4.5,5.5,7,10,18};
Double_t yvaluncPrompt[9] = {0., 0., 0., 0., 0., 0., 0., 0., 0.};
Double_t xerrPrompt[9] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,0.25};

bool DrawAllPoints = false;

void makeCrossSection_pPb_NonPrompt_noFONLL_Lc(bool isPreliminary = kTRUE){
    
    TGaxis::SetMaxDigits(3);
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    
    TFile* promptFileHEP = new TFile("./HEPData-ins2593302-v1-Table_2.root", "read");
    TDirectoryFile *dir = (TDirectoryFile*)promptFileHEP->Get("Table 2");
    TH1F *hCroSecPromptD0 = (TH1F*)dir->Get("Hist1D_y1");
    TH1F *hCroSecPromptD0Stat = (TH1F*)dir->Get("Hist1D_y1_e1");
    TH1F *hCroSecPromptD0SystPlus = (TH1F*)dir->Get("Hist1D_y1_e2plus");
    TH1F *hCroSecPromptD0SystMinus = (TH1F*)dir->Get("Hist1D_y1_e2minus");
    
    TGraphAsymmErrors* gCroSecPromptD0Systematics = new TGraphAsymmErrors(9, ptlimsmiddlePrompt, yvaluncPrompt);
    for (Int_t i = 0; i < 9; i++) {
        Double_t Crosssection = hCroSecPromptD0->GetBinContent(i+1);
        Double_t ptx = ptlimsmiddlePrompt[i];
        Double_t errylow = -1. * hCroSecPromptD0SystMinus->GetBinContent(i+1);
        Double_t erryhigh = hCroSecPromptD0SystPlus->GetBinContent(i+1);
        Double_t errxlow = 0.25;
        Double_t errxhigh = 0.25;
        gCroSecPromptD0Systematics->SetPoint(i, ptlimsmiddlePrompt[i], Crosssection);
        gCroSecPromptD0Systematics->SetPointError(i, xerrPrompt[i], xerrPrompt[i], errylow, erryhigh);
    }
    
    //  gCroSecPromptD0Systematics->SetFillStyle(1001);
    gCroSecPromptD0Systematics->SetFillStyle(0);
    //  gCroSecPromptD0Systematics->SetFillColor(kRed-9);
    gCroSecPromptD0Systematics->SetFillColor(kWhite);
    gCroSecPromptD0Systematics->SetLineWidth(2);
    gCroSecPromptD0Systematics->SetLineColor(kRed-9);
    
    for(Int_t i = 0; i < 21; i++) {
        hCroSecPromptD0->SetBinError(i+1, hCroSecPromptD0Stat->GetBinContent(i+1));
    }
    hCroSecPromptD0->SetMarkerStyle(33);
    SetStyleHisto(hCroSecPromptD0);
    hCroSecPromptD0->SetMarkerSize(1.4);
    hCroSecPromptD0->SetMarkerColor(kRed+2);
    hCroSecPromptD0->SetLineColor(kRed+2);
    
    TFile* f[3];
    f[2] = TFile::Open ("NonPromptLcAverage_pPb5.02TeV.root", "READ");
    
    TH1F* hD0[4];
    //  TH1D *hD0D[4];
    //  TH1F* hSystHigh[4];
    //  TH1F* hSystLow[4];
    
    hD0[2] = (TH1F*)f[2]->Get("h1Average");
    // hD0[2]->Scale(1. / 0.03947);
    
    
    // Double_t SystTotal[4] = {0.178943, 0.165159, 0.170911, 0.213073};
    Double_t SystTotal[nPtBinsCoarse] = {76.95,7.008,0.873,0.0877};
    
    const Double_t yvalunc[4] = {0., 0., 0., 0.};
    /// Get Graph for total systematics on cross section
    TGraphAsymmErrors* gSigmaSystematics = new TGraphAsymmErrors(nPtBins+1, ptlimsmiddle,yvalunc);
    for (Int_t i = 0; i < nPtBins+1; i++) {
        Double_t Crosssection = hD0[2]->GetBinContent(i+1);
        Double_t ptx = ptlimsmiddle[i];
        // Double_t errylow = sqrt(SystTotal[i]*SystTotal[i]-0.05*0.05) * Crosssection;
        // Double_t erryhigh = sqrt(SystTotal[i]*SystTotal[i]-0.05*0.05) * Crosssection;
        Double_t errylow = SystTotal[i];
        Double_t erryhigh = SystTotal[i];
        // Double_t erryhigh = SystTotal[i] * Crosssection;
        Double_t errxlow = 0.45;
        Double_t errxhigh = 0.45;
        gSigmaSystematics->SetPoint(i, ptlimsmiddle[i], Crosssection);
        gSigmaSystematics->SetPointError(i, errxlow, errxhigh, errylow, erryhigh);
    }
    
    gSigmaSystematics->SetFillStyle(0);
    gSigmaSystematics->SetFillColor(kWhite);
    gSigmaSystematics->SetLineWidth(2);
    gSigmaSystematics->SetLineColor(kAzure+1);
    
    
    
    const Int_t nptlims = 9;
    const Int_t nptlimsExtra = 21;
    Float_t ptlims[nptlims+1] = {0,1,2,3,4,5,6,8,12,24};
    Float_t ptlimsExtral[22] = {0., 1., 1.5, 2., 2.5, 3., 3.5, 4., 4.5, 5., 5.5, 6., 6.5, 7., 7.5, 8., 9., 10., 12., 16., 24.,26};
    TH1D* href = new TH1D("href","href", nptlimsExtra, ptlimsExtral);
    href->GetYaxis()->SetTitle("d^{2}#sigma/(d#it{y} d#it{p}_{T}) (#mub GeV^{-1}#it{c})");
    href->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
    href->SetMinimum(0.051);
    href->SetMaximum(700000);
    SetStyleHisto(href);
    href->SetLineWidth(1);
    href->GetYaxis()->SetTitleOffset(1.3);
    
    
    TCanvas* c1 = new TCanvas("c1", "c1", 0, 0, 600, 750);
    gStyle->SetOptStat(0);
    TPad* p1 = new TPad("p1", "p1", 0., 0., 1, 1);
    p1->Draw();
    p1->cd();
    p1->SetTickx();
    p1->SetTicky();
    p1->SetLogy();
    p1->SetBottomMargin(0.13);
    p1->SetLeftMargin(0.17);
    p1->SetTopMargin(0.05);
    p1->SetRightMargin(0.03);
    href->Draw("AXIS");
    
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
    hD0[2]->SetLineColor(kAzure+2);
    hD0[2]->SetMarkerColor(kAzure+2);
    hD0[2]->SetMarkerSize(1.);
    hD0[2]->SetStats(0);
    // hD0[2]->SetLineColor(kRed);
    
    TLatex info;
    info.SetNDC();
    info.SetTextFont(43);
    info.SetTextSize(30);
    // info.DrawLatex(0.20, 0.89, "ALICE Preliminary");
    info.DrawLatex(0.20, 0.89, "ALICE");
    
    TLatex infos;
    infos.SetNDC();
    infos.SetTextFont(43);
    infos.SetTextSize(26);
    infos.DrawLatex(0.20, 0.84, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
    infos.DrawLatex(0.60, 0.89, "#font[122]{-}0.96 < #it{y}_{cms} < 0.04");
    
    TLatex inforef;
    inforef.SetNDC();
    inforef.SetTextFont(43);
    inforef.SetTextSize(22);
    // inforef.DrawLatex(0.59, 0.59, "JHEP 12 (2019) 092");
    inforef.DrawLatex(0.50, 0.59, " PRC 107 (2023) 6, 064901");
    
    //  info.DrawLatex(0.6, 0.85, "Non-Prompt D^{0}");//,
    //  info.DrawLatex(0.48, 0.7, "FONLL + PYTHIA8 Decayer");
    
    //  TLatex info5;
    //  info5.SetNDC();
    //  info5.SetTextFont(43);
    //  info5.SetTextSize(15);
    //  info5.DrawLatex(0.48, 0.66, "#it{f} (b #rightarrow B^{0}, b #rightarrow B^{+})_{LHCb}, BR (H_{b} #rightarrow D^{0}+X)_{PYTHIA 8}");//,
    //  info1.DrawLatex(0.5, 0.74-0.02, "average of");
    //info.DrawLatex(0.20, 0.70, "#Lambda_{c}^{+} #rightarrow pK^{0}_{S}");
    //  if (isPreliminary){
    //info.DrawLatex(0.28, 0.85, "ALICE");
    //info.DrawLatex(0.28, 0.85, "ALICE");
    //info.DrawLatex(0.22, 0.2-0.06, "Preliminary");
    //    }
    
    TLatex info2;
    info2.SetNDC();
    info2.SetTextFont(43);
    info2.SetTextSize(19);
    //  info2.DrawLatex(0.21, 0.19, "#pm3.7% lumi. unc. not shown");
    //  info2.DrawLatex(0.21, 0.22, "#pm0.76% BR unc. not shown");
    
    info2.DrawLatex(0.57, 0.45, "#pm 3.7% lumi. unc. not shown");
    info2.DrawLatex(0.57, 0.5, "#pm 5.0% BR unc. not shown");
    
    //  gPOWHEGB->Draw("e5ssame");
    //  gPOWHEGcentB->Draw("ezsame");
    gSigmaSystematics->Draw("same2");
    hD0[2]->Draw("e0 same");
    
    gCroSecPromptD0Systematics->Draw("same2");
    hCroSecPromptD0->Draw("e0 same");
    
    TLegend* leg = new TLegend(0.45, 0.6, 0.75, 0.75);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetMargin(0.46);
    leg->SetTextSize(25);
    leg->SetTextFont(43);
    leg->AddEntry(hD0[2], "Non-prompt #Lambda_{c}^{+}", "p");
    leg->AddEntry(hCroSecPromptD0, "Prompt #Lambda_{c}^{+}", "p");
    leg->Draw();

    c1->SaveAs("CrossSection_Np.pdf");
    c1->SaveAs("CrossSection_Np.png");
    c1->SaveAs("CrossSection_Np.eps");
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
  gStyle->SetLabelSize(0.055,"xyz");
  gStyle->SetLabelOffset(0.01,"y");
  gStyle->SetLabelOffset(0.01,"x");
  gStyle->SetLabelColor(kBlack,"xyz");
  //gStyle->SetTitleSize(0.055,"xyz");
  //gStyle->SetTitleOffset(1.5,"y");
  //gStyle->SetTitleOffset(1.15,"x");
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

void SetStyleHisto( TH1D *h){

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

void SetStyleHisto( TH1F *h){

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

void NormaliseHist1d(TH1 *h) {
	if(h) {
		// dN/dpt
		for(Int_t i = 1;i<=h->GetNbinsX();i++) {
			h->SetBinContent(i,h->GetBinContent(i) / (h->GetXaxis()->GetBinWidth(i)));
			//		hnew->SetBinError(i,hnew->GetBinContent(i)/(hnew->GetBinWidth(i) * TMath::Sqrt(hnew->GetBinContent(i)))); // may need to look at again
			h->SetBinError(i,h->GetBinError(i) / (h->GetXaxis()->GetBinWidth(i)));
		}
	}
	else {
		cout<<"can't normalise hist - not found"<<endl;
	}
}
