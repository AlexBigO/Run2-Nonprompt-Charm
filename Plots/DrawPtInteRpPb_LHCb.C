#include <iostream>

using namespace std;

void SetStyleHisto(TH1D *h);
void SetStyleHisto(TH1F *h);

const Double_t ptlimsmiddleJPsi[9] = {-4.25, -3.75, -3.25, -2.75, 1.75,
                                      2.25,  2.75,  3.25,  3.75};
Double_t yvaluncJPsi[9] = {1.1, 1.03, 0.97, 1, 0.84, 0.89, 0.8, 0.8, 0.82};
Double_t yuncJPsi[9] = {0.13, 0.11, 0.11, 0.14, 0.17, 0.09, 0.07, 0.07, 0.08};
const Double_t ptlimsmiddleBplus[2] = {-3., 3.};
Double_t yvaluncBplus[2] = {1., 0.78};
Double_t yuncBplus[2] = {0.1044031, 0.05385165};
const Double_t ptlimsmiddleALICEJPsi[1] = {-0.47};
Double_t yvaluncALICEJPsi[1] = {0.54};
Double_t yuncALICEJPsi[1] = {0.13};

void DrawPtInteRpPb_LHCb() {

  // prompt D0 RpPb

  Float_t JPsiBins[11] = {-4.5, -4., -3.5, -3., -2.5, 1.5,
                          2.,   2.5, 3.,   3.5, 4.};
  Double_t JPsiBinContent[10] = {1.1,  1.03, 0.97, 1,   -1.,
                                 0.84, 0.89, 0.8,  0.8, 0.82};
  Double_t JPsiBinError[10] = {0.13, 0.11, 0.11, 0.14, 0.,
                               0.17, 0.09, 0.07, 0.07, 0.08};
  TH1F *npJPsiRpPb = new TH1F("npJPsi", "npJPsi", 10, JPsiBins);
  for (int iPt = 0; iPt < 10; iPt++) {
    npJPsiRpPb->SetBinContent(iPt + 1, JPsiBinContent[iPt]);
    npJPsiRpPb->SetBinError(iPt + 1, JPsiBinError[iPt]);
  }

  Float_t BplusBins[4] = {-3.5, -2.5, 2.5, 3.5};
  Double_t BplusBinContent[3] = {1., -1., 0.78};
  Double_t BplusBinError[3] = {0.03, 0., 0.02};
  TH1F *BplusRpPb = new TH1F("BplusRpPb", "BplusRpPb", 3, BplusBins);
  for (int iPt = 0; iPt < 3; iPt++) {
    BplusRpPb->SetBinContent(iPt + 1, BplusBinContent[iPt]);
    BplusRpPb->SetBinError(iPt + 1, BplusBinError[iPt]);
  }

  //  TGraphAsymmErrors* gJPsiSystematics = new TGraphAsymmErrors(9,
  //  ptlimsmiddleJPsi, yvaluncJPsi); for (Int_t i = 0; i < 9; i++) {
  //    Double_t ptx = 0.2;
  //    gJPsiSystematics->SetPoint(i, ptlimsmiddleJPsi[i], yvaluncJPsi[i]);
  //    gJPsiSystematics->SetPointError(i, ptx, ptx, yuncJPsi[i], yuncJPsi[i]);
  //  }
  //
  //
  ////  cii = TColor::GetColor("#006600");
  //  gJPsiSystematics->SetFillStyle(1001);
  ////  gJPsiSystematics->SetFillStyle(0);
  ////  gJPsiSystematics->SetFillColor(kWhite);
  ////  gJPsiSystematics->SetFillColor(kGreen-9);
  //  gJPsiSystematics->SetFillColor(kTeal-9);
  ////  gJPsiSystematics->SetFillColor(kMagenta-10);
  //  gJPsiSystematics->SetLineWidth(3);
  ////  gJPsiSystematics->SetLineColor(kGreen-9);
  //  gJPsiSystematics->SetLineColor(kTeal-9);

  TGraphAsymmErrors *gBplusSystematics =
      new TGraphAsymmErrors(2, ptlimsmiddleBplus, yvaluncBplus);
  for (Int_t i = 0; i < 2; i++) {
    Double_t ptx = 0.2;
    gBplusSystematics->SetPoint(i, ptlimsmiddleBplus[i], yvaluncBplus[i]);
    gBplusSystematics->SetPointError(i, ptx, ptx, yuncBplus[i], yuncBplus[i]);
  }

  gBplusSystematics->SetFillStyle(0);
  gBplusSystematics->SetFillColor(kWhite);
  gBplusSystematics->SetLineWidth(3);
  //  gBplusSystematics->SetLineColor(kBlack);
  //  gBplusSystematics->SetLineColor(kRed+1);
  gBplusSystematics->SetLineColor(kViolet + 1);

  // ALICE J/Psi
  Float_t ALICEJPsiBins[2] = {-1.37, 0.43};
  Double_t ALICEJPsiBinContent[1] = {0.54};
  Double_t ALICEJPsiBinError[1] = {0.2};
  TH1F *ALICEJPsiRpPb =
      new TH1F("ALICEJPsiRpPb", "ALICEJPsiRpPb", 1, ALICEJPsiBins);
  for (int iPt = 0; iPt < 1; iPt++) {
    ALICEJPsiRpPb->SetBinContent(iPt + 1, ALICEJPsiBinContent[iPt]);
    ALICEJPsiRpPb->SetBinError(iPt + 1, ALICEJPsiBinError[iPt]);
  }

  TGraphAsymmErrors *gALICEJPsiSystematics =
      new TGraphAsymmErrors(1, ptlimsmiddleALICEJPsi, yvaluncALICEJPsi);
  for (Int_t i = 0; i < 1; i++) {
    Double_t ptx = 0.3;
    gALICEJPsiSystematics->SetPoint(i, ptlimsmiddleALICEJPsi[i],
                                    yvaluncALICEJPsi[i]);
    gALICEJPsiSystematics->SetPointError(i, ptx, ptx, yuncALICEJPsi[i],
                                         yuncALICEJPsi[i]);
  }

  gALICEJPsiSystematics->SetFillStyle(0);
  gALICEJPsiSystematics->SetFillColor(kWhite);
  gALICEJPsiSystematics->SetLineWidth(3);
  gALICEJPsiSystematics->SetLineColor(kOrange + 2);

  TGraphAsymmErrors *gALICEJPsiSystematicsExtr =
      new TGraphAsymmErrors(1, ptlimsmiddleALICEJPsi, yvaluncALICEJPsi);
  for (Int_t i = 0; i < 1; i++) {
    Double_t ptx = 0.3;
    gALICEJPsiSystematicsExtr->SetPoint(i, ptlimsmiddleALICEJPsi[i],
                                        yvaluncALICEJPsi[i]);
    gALICEJPsiSystematicsExtr->SetPointError(i, ptx, ptx, 0.02, 0.01);
  }

  gALICEJPsiSystematicsExtr->SetFillStyle(3001);
  gALICEJPsiSystematicsExtr->SetFillColor(kOrange + 2);
  gALICEJPsiSystematicsExtr->SetLineWidth(0);
  gALICEJPsiSystematicsExtr->SetMarkerSize(0);
  gALICEJPsiSystematicsExtr->SetLineColor(kOrange + 2);
  gALICEJPsiSystematicsExtr->SetMarkerColor(kOrange + 2);

  TH1D *hrefPrompt = new TH1D("hrefPrompt", "hrefPrompt", 20, -5, 5);
  hrefPrompt->SetTitle("");
  hrefPrompt->GetYaxis()->SetTitle("#it{R}_{pPb}");
  hrefPrompt->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  hrefPrompt->SetMinimum(0.01);
  hrefPrompt->SetMaximum(2.69);
  SetStyleHisto(hrefPrompt);
  hrefPrompt->SetLineWidth(1);
  hrefPrompt->GetYaxis()->SetTitleOffset(1.3);
  hrefPrompt->GetXaxis()->SetTitle("#it{y}");
  hrefPrompt->GetXaxis()->CenterTitle(true);
  hrefPrompt->GetXaxis()->SetNdivisions(505);
  //  hrefPrompt->GetXaxis()->SetRangeUser();

  // non-prompt D0 RpPb
  //  TH1F* hPtIntD0pPb = new TH1F("hPtIntD0pPb", "hPtIntD0pPb", 1, -0.96,
  //  0.04); hPtIntD0pPb->SetBinContent(1, 3988.5); hPtIntD0pPb->SetBinError(1,
  //  233.6);
  //
  //
  //  Double_t SystIntD0pPbSyst = 281.9;
  //  Double_t SystIntD0pPbExtraLow = 306.6;
  //  Double_t SystIntD0pPbExtraHigh = 199.6;
  //
  //  TH1F* hPtIntD0pp = new TH1F("hPtIntD0pp", "hPtIntD0pp", 1, -0.96, 0.04);
  //  hPtIntD0pp->SetBinContent(1, 18.4);
  //  hPtIntD0pp->SetBinError(1, 1.5);
  //
  //
  //  Double_t SystIntD0ppSyst = 1.6;
  //  Double_t SystIntD0ppExtraLow = 0.6;
  //  Double_t SystIntD0ppExtraHigh = 0.1;
  //
  //  TH1F* hPtIntD0RpPb = (TH1F*)hPtIntD0pPb->Clone("hPtIntD0RpPb");
  //  hPtIntD0RpPb->Divide(hPtIntD0pp);
  //  hPtIntD0RpPb->Scale(1./208.);

  //  Double_t SystIntD0RpPb = hPtIntD0RpPb->GetBinContent(1) *
  //  TMath::Sqrt(SystIntD0pPbSyst*SystIntD0pPbSyst/hPtIntD0pPb->GetBinContent(1)/hPtIntD0pPb->GetBinContent(1)
  //  +
  //  SystIntD0ppSyst*SystIntD0ppSyst/hPtIntD0pp->GetBinContent(1)/hPtIntD0pp->GetBinContent(1));
  //
  //  Double_t SystIntD0RpPbLowExtr = hPtIntD0RpPb->GetBinContent(1) *
  //  (SystIntD0pPbExtraLow/hPtIntD0pPb->GetBinContent(1) +
  //  SystIntD0ppExtraLow/hPtIntD0pp->GetBinContent(1));
  //
  //  Double_t SystIntD0RpPbHighExtr = hPtIntD0RpPb->GetBinContent(1) *
  //  (SystIntD0pPbExtraHigh/hPtIntD0pPb->GetBinContent(1) +
  //  SystIntD0ppExtraHigh/hPtIntD0pp->GetBinContent(1));

  //  Double_t gPtIntD0RpPbSystematicsMiddle[1] = {-0.46};
  //  Double_t yuncD0[1] = {0.};
  //    TGraphAsymmErrors* gPtIntD0RpPbSystematics = new TGraphAsymmErrors(1,
  //    gPtIntD0RpPbSystematicsMiddle, yuncD0); for (Int_t i = 0; i < 1; i++) {
  //      Double_t RpPbFD = hPtIntD0RpPb->GetBinContent(i+1);
  //      Double_t ptx = 0.4;
  //      gPtIntD0RpPbSystematics->SetPoint(i, -0.46, RpPbFD);
  //      gPtIntD0RpPbSystematics->SetPointError(i, ptx, ptx, SystIntD0RpPb,
  //      SystIntD0RpPb);
  //    }

  //  gPtIntD0RpPbSystematics->SetFillStyle(0);
  //  gPtIntD0RpPbSystematics->SetFillColor(kWhite);
  //  gPtIntD0RpPbSystematics->SetLineWidth(2);
  //  gPtIntD0RpPbSystematics->SetLineColor(kAzure+2);
  //
  //  Double_t gPtIntD0RpPbSystematicsExtra[1] = {-0.46};
  //  TGraphAsymmErrors* gPtIntD0RpPbSystematicsExtr = new TGraphAsymmErrors(1,
  //  gPtIntD0RpPbSystematicsExtra, yuncD0);
  //    for (Int_t i = 0; i < 1; i++) {
  //      Double_t RpPbFD = hPtIntD0RpPb->GetBinContent(i+1);
  //      Double_t ptx = 0.4;
  //      gPtIntD0RpPbSystematicsExtr->SetPoint(i, -0.46, RpPbFD);
  //      gPtIntD0RpPbSystematicsExtr->SetPointError(i, ptx, ptx,
  //      SystIntD0RpPbLowExtr, SystIntD0RpPbHighExtr);
  //    }
  //
  //  gPtIntD0RpPbSystematicsExtr->SetFillStyle(3001);
  //  gPtIntD0RpPbSystematicsExtr->SetFillColor(kAzure+2);
  //  gPtIntD0RpPbSystematicsExtr->SetLineWidth(2);
  //  gPtIntD0RpPbSystematicsExtr->SetLineColor(kAzure+2);

  TH1F *hPtIntD0pPbLHCb =
      new TH1F("hPtIntD0pPbLHCb", "hPtIntD0pPbLHCb", 1, -0.96, 0.04);
  hPtIntD0pPbLHCb->SetBinContent(1, 1791.27);
  hPtIntD0pPbLHCb->SetBinError(1, 83.1);

  Double_t SystIntD0pPbSystLHCb = 95.0;

  TH1F *hPtIntD0ppLHCb =
      new TH1F("hPtIntD0ppLHCb", "hPtIntD0ppLHCb", 1, -0.96, 0.04);
  hPtIntD0ppLHCb->SetBinContent(1, 9.26);
  hPtIntD0ppLHCb->SetBinError(1, 0.69);

  Double_t SystIntD0ppSystLHCb = 0.75;

  TH1F *hPtIntD0RpPbLHCb = (TH1F *)hPtIntD0pPbLHCb->Clone("hPtIntD0RpPbLHCb");
  hPtIntD0RpPbLHCb->Divide(hPtIntD0ppLHCb);
  hPtIntD0RpPbLHCb->Scale(1. / 208.);

  Double_t SystIntD0RpPbLHCb =
      hPtIntD0RpPbLHCb->GetBinContent(1) *
      TMath::Sqrt(SystIntD0pPbSystLHCb * SystIntD0pPbSystLHCb /
                      hPtIntD0pPbLHCb->GetBinContent(1) /
                      hPtIntD0pPbLHCb->GetBinContent(1) +
                  SystIntD0ppSystLHCb * SystIntD0ppSystLHCb /
                      hPtIntD0ppLHCb->GetBinContent(1) /
                      hPtIntD0ppLHCb->GetBinContent(1));

  Double_t gPtIntD0RpPbSystematicsMiddleLHCb[1] = {-0.46};
  Double_t yuncD0LHCb[1] = {0.};
  TGraphAsymmErrors *gPtIntD0RpPbSystematicsLHCb =
      new TGraphAsymmErrors(1, gPtIntD0RpPbSystematicsMiddleLHCb, yuncD0LHCb);
  for (Int_t i = 0; i < 1; i++) {
    Double_t RpPbFDLHCb = hPtIntD0RpPbLHCb->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    gPtIntD0RpPbSystematicsLHCb->SetPoint(i, -0.46, RpPbFDLHCb);
    gPtIntD0RpPbSystematicsLHCb->SetPointError(i, ptx, ptx, SystIntD0RpPbLHCb,
                                               SystIntD0RpPbLHCb);
  }

  gPtIntD0RpPbSystematicsLHCb->SetFillStyle(0);
  gPtIntD0RpPbSystematicsLHCb->SetFillColor(kWhite);
  gPtIntD0RpPbSystematicsLHCb->SetLineWidth(3);
  //  gPtIntD0RpPbSystematicsLHCb->SetLineColor(kAzure+2);
  gPtIntD0RpPbSystematicsLHCb->SetLineColor(kBlack);

  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 750, 750);
  gStyle->SetOptStat(0);
  c1->SetTickx();
  c1->SetTicky();
  c1->SetBottomMargin(0.13);
  c1->SetLeftMargin(0.17);
  c1->SetTopMargin(0.05);
  c1->SetRightMargin(0.03);
  c1->cd();
  hrefPrompt->Draw("");
  //  gJPsiSystematics->Draw("same2");

  // draw lines
  TLine *line = new TLine(-5, 1, 5, 1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  line = new TLine(-5, 1.159756, -4.5, 1.159756);

  Int_t ci;      // for color index setting
  TColor *color; // for color definition with alpha
  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-5, 0.9726364, -4.5, 0.9726364);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4.5, 1.189462, -4, 1.189462);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4.5, 1.009985, -4, 1.009985);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4.5, 1.009985, -4.5, 0.9726364);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4.5, 1.189462, -4.5, 1.159756);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4, 1.18205, -3.5, 1.18205);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4, 1.028814, -3.5, 1.028814);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4, 1.028814, -4, 1.009985);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4, 1.18205, -4, 1.189462);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3.5, 1.136548, -3, 1.136548);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3.5, 1.028574, -3, 1.028574);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3.5, 1.028574, -3.5, 1.028814);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3.5, 1.136548, -3.5, 1.18205);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3, 1.093588, -2.5, 1.093588);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3, 0.9972582, -2.5, 0.9972582);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3, 0.9972582, -3, 1.028574);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3, 1.093588, -3, 1.136548);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2.5, 1.054682, -2, 1.054682);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2.5, 0.9418059, -2, 0.9418059);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2.5, 0.9418059, -2.5, 0.9972582);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2.5, 1.054682, -2.5, 1.093588);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2, 1.032115, -1.5, 1.032115);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2, 0.8787846, -1.5, 0.8787846);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2, 0.8787846, -2, 0.9418059);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2, 1.032115, -2, 1.054682);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1.5, 1.020838, -1, 1.020838);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1.5, 0.8249466, -1, 0.8249466);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1.5, 0.8249466, -1.5, 0.8787846);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1.5, 1.020838, -1.5, 1.032115);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1, 1.01347, -0.5, 1.01347);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1, 0.783389, -0.5, 0.783389);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1, 0.783389, -1, 0.8249466);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1, 1.01347, -1, 1.020838);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-0.5, 1.007852, 0, 1.007852);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-0.5, 0.7524655, 0, 0.7524655);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-0.5, 0.7524655, -0.5, 0.783389);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-0.5, 1.007852, -0.5, 1.01347);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0, 1.003127, 0.5, 1.003127);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0, 0.7294283, 0.5, 0.7294283);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0, 0.7294283, 0, 0.7524655);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0, 1.003127, 0, 1.007852);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0.5, 0.9988697, 1, 0.9988697);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0.5, 0.7117993, 1, 0.7117993);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0.5, 0.7117993, 0.5, 0.7294283);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0.5, 0.9988697, 0.5, 1.003127);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1, 0.9950103, 1.5, 0.9950103);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1, 0.6978322, 1.5, 0.6978322);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1, 0.6978322, 1, 0.7117993);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1, 0.9950103, 1, 0.9988697);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1.5, 0.9914958, 2, 0.9914958);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1.5, 0.6863426, 2, 0.6863426);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1.5, 0.6863426, 1.5, 0.6978322);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1.5, 0.9914958, 1.5, 0.9950103);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2, 0.9881705, 2.5, 0.9881705);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2, 0.6764959, 2.5, 0.6764959);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2, 0.6764959, 2, 0.6863426);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2, 0.9881705, 2, 0.9914958);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2.5, 0.984998, 3, 0.984998);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2.5, 0.6678184, 3, 0.6678184);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2.5, 0.6678184, 2.5, 0.6764959);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2.5, 0.984998, 2.5, 0.9881705);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3, 0.9820374, 3.5, 0.9820374);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3, 0.6600608, 3.5, 0.6600608);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3, 0.6600608, 3, 0.6678184);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3, 0.9820374, 3, 0.984998);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3.5, 0.9792387, 4, 0.9792387);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3.5, 0.6529814, 4, 0.6529814);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3.5, 0.6529814, 3.5, 0.6600608);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3.5, 0.9792387, 3.5, 0.9820374);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4, 0.9765592, 4.5, 0.9765592);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4, 0.6464519, 4.5, 0.6464519);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4, 0.6464519, 4, 0.6529814);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4, 0.9765592, 4, 0.9792387);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4.5, 0.9740382, 5, 0.9740382);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4.5, 0.6404051, 5, 0.6404051);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4.5, 0.6404051, 4.5, 0.6464519);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4.5, 0.9740382, 4.5, 0.9765592);

  ci = TColor::GetColor("#ff0000");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-5, 1.205312, -4.5, 1.205312);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-5, 0.9284786, -4.5, 0.9284786);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4.5, 1.267125, -4, 1.267125);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4.5, 1.035915, -4, 1.035915);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4.5, 1.035915, -4.5, 0.9284786);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4.5, 1.267125, -4.5, 1.205312);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4, 1.245639, -3.5, 1.245639);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4, 1.075144, -3.5, 1.075144);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4, 1.075144, -4, 1.035915);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-4, 1.245639, -4, 1.267125);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3.5, 1.168033, -3, 1.168033);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3.5, 1.053898, -3, 1.053898);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3.5, 1.053898, -3.5, 1.075144);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3.5, 1.168033, -3.5, 1.245639);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3, 1.109898, -2.5, 1.109898);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3, 0.9754434, -2.5, 0.9754434);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3, 0.9754434, -3, 1.053898);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-3, 1.109898, -3, 1.168033);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2.5, 1.063002, -2, 1.063002);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2.5, 0.8884967, -2, 0.8884967);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2.5, 0.8884967, -2.5, 0.9754434);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2.5, 1.063002, -2.5, 1.109898);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2, 1.025654, -1.5, 1.025654);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2, 0.8178987, -1.5, 0.8178987);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2, 0.8178987, -2, 0.8884967);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-2, 1.025654, -2, 1.063002);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1.5, 0.9944976, -1, 0.9944976);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1.5, 0.7674757, -1, 0.7674757);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1.5, 0.7674757, -1.5, 0.8178987);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1.5, 0.9944976, -1.5, 1.025654);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1, 0.9685394, -0.5, 0.9685394);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1, 0.7328674, -0.5, 0.7328674);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1, 0.7328674, -1, 0.7674757);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-1, 0.9685394, -1, 0.9944976);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-0.5, 0.9469873, 0, 0.9469873);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-0.5, 0.7088543, 0, 0.7088543);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-0.5, 0.7088543, -0.5, 0.7328674);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(-0.5, 0.9469873, -0.5, 0.9685394);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0, 0.9289925, 0.5, 0.9289925);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0, 0.691371, 0.5, 0.691371);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0, 0.691371, 0, 0.7088543);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0, 0.9289925, 0, 0.9469873);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0.5, 0.9136944, 1, 0.9136944);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0.5, 0.6777298, 1, 0.6777298);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0.5, 0.6777298, 0.5, 0.691371);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(0.5, 0.9136944, 0.5, 0.9289925);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1, 0.9003735, 1.5, 0.9003735);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1, 0.6663484, 1.5, 0.6663484);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1, 0.6663484, 1, 0.6777298);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1, 0.9003735, 1, 0.9136944);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1.5, 0.8885169, 2, 0.8885169);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1.5, 0.6563205, 2, 0.6563205);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1.5, 0.6563205, 1.5, 0.6663484);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(1.5, 0.8885169, 1.5, 0.9003735);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2, 0.8777753, 2.5, 0.8777753);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2, 0.6471367, 2.5, 0.6471367);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2, 0.6471367, 2, 0.6563205);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2, 0.8777753, 2, 0.8885169);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2.5, 0.8679124, 3, 0.8679124);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2.5, 0.6385449, 3, 0.6385449);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2.5, 0.6385449, 2.5, 0.6471367);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(2.5, 0.8679124, 2.5, 0.8777753);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3, 0.8587724, 3.5, 0.8587724);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3, 0.6303724, 3.5, 0.6303724);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3, 0.6303724, 3, 0.6385449);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3, 0.8587724, 3, 0.8679124);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3.5, 0.8502358, 4, 0.8502358);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3.5, 0.622539, 4, 0.622539);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3.5, 0.622539, 3.5, 0.6303724);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(3.5, 0.8502358, 3.5, 0.8587724);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4, 0.8422792, 4.5, 0.8422792);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4, 0.6150139, 4.5, 0.6150139);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4, 0.6150139, 4, 0.622539);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4, 0.8422792, 4, 0.8502358);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4.5, 0.8349289, 5, 0.8349289);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4.5, 0.6077895, 5, 0.6077895);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4.5, 0.6077895, 4.5, 0.6150139);

  ci = TColor::GetColor("#0000ff");
  line->SetLineColor(ci);
  line->SetLineStyle(0);
  line->Draw();
  line = new TLine(4.5, 0.8349289, 4.5, 0.8422792);

  Double_t _fx3008[20] = {-4.75, -4.25, -3.75, -3.25, -2.75, -2.25, -1.75,
                          -1.25, -0.75, -0.25, 0.25,  0.75,  1.25,  1.75,
                          2.25,  2.75,  3.25,  3.75,  4.25,  4.75};
  Double_t _fy3008[20] = {1.057927,  1.090846,  1.100153,  1.083667,
                          1.051179,  1.014529,  0.9807463, 0.9523912,
                          0.9295936, 0.9115385, 0.8969634, 0.8848706,
                          0.8746091, 0.8657144, 0.8577895, 0.8506197,
                          0.8441252, 0.8381771, 0.8326678, 0.8276135};
  Double_t _felx3008[20] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                            0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                            0.25, 0.25, 0.25, 0.25, 0.25, 0.25};
  Double_t _fely3008[20] = {0.08529049, 0.08086105, 0.0713394, 0.05509307,
                            0.05392124, 0.07272262, 0.1019618, 0.1274446,
                            0.1462046,  0.159073,   0.1675351, 0.1730713,
                            0.1767769,  0.1793718,  0.1812936, 0.1828013,
                            0.1840644,  0.1851956,  0.1862158, 0.1872084};
  Double_t _fehx3008[20] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                            0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                            0.25, 0.25, 0.25, 0.25, 0.25, 0.25};
  Double_t _fehy3008[20] = {0.1018289,  0.09861629, 0.08189655, 0.05288164,
                            0.04240835, 0.04015333, 0.05136817, 0.06844641,
                            0.08387679, 0.09631313, 0.106164,   0.1139991,
                            0.1204012,  0.1257814,  0.130381,   0.1343783,
                            0.1379122,  0.1410616,  0.1438914,  0.1464247};
  TGraphAsymmErrors *grae = new TGraphAsymmErrors(
      20, _fx3008, _fy3008, _felx3008, _fehx3008, _fely3008, _fehy3008);
  grae->SetName("");
  grae->SetTitle("");

  ci = TColor::GetColor("#ff0000");
  grae->SetFillColor(ci);
  grae->SetFillStyle(3654);

  ci = TColor::GetColor("#ff0000");
  grae->SetLineColor(ci);
  grae->SetLineWidth(2);
  grae->SetMarkerStyle(20);

  TH1F *Graph_Graph3008 = new TH1F("Graph_Graph3008", "", 100, -6, 6);
  Graph_Graph3008->SetMinimum(0.5854994);
  Graph_Graph3008->SetMaximum(1.244368);
  Graph_Graph3008->SetDirectory(0);
  Graph_Graph3008->SetStats(0);
  Graph_Graph3008->SetLineWidth(3);
  Graph_Graph3008->SetMarkerStyle(20);
  Graph_Graph3008->GetXaxis()->SetNdivisions(505);
  Graph_Graph3008->GetXaxis()->SetLabelFont(132);
  Graph_Graph3008->GetXaxis()->SetLabelOffset(0.01);
  Graph_Graph3008->GetXaxis()->SetLabelSize(0.06);
  Graph_Graph3008->GetXaxis()->SetTitleSize(0.072);
  Graph_Graph3008->GetXaxis()->SetTitleOffset(0.95);
  Graph_Graph3008->GetXaxis()->SetTitleFont(132);
  Graph_Graph3008->GetYaxis()->SetLabelFont(132);
  Graph_Graph3008->GetYaxis()->SetLabelOffset(0.01);
  Graph_Graph3008->GetYaxis()->SetLabelSize(0.06);
  Graph_Graph3008->GetYaxis()->SetTitleSize(0.072);
  Graph_Graph3008->GetYaxis()->SetTitleOffset(0.9);
  Graph_Graph3008->GetYaxis()->SetTitleFont(132);
  Graph_Graph3008->GetZaxis()->SetLabelFont(132);
  Graph_Graph3008->GetZaxis()->SetLabelSize(0.06);
  Graph_Graph3008->GetZaxis()->SetTitleSize(0.072);
  Graph_Graph3008->GetZaxis()->SetTitleOffset(1.2);
  Graph_Graph3008->GetZaxis()->SetTitleFont(132);
  grae->SetHistogram(Graph_Graph3008);

  grae->Draw(",e2z");

  Double_t _fx3009[20] = {-4.75, -4.25, -3.75, -3.25, -2.75, -2.25, -1.75,
                          -1.25, -0.75, -0.25, 0.25,  0.75,  1.25,  1.75,
                          2.25,  2.75,  3.25,  3.75,  4.25,  4.75};
  Double_t _fy3009[20] = {1.058507,  1.140379,  1.153525,  1.117462,
                          1.059518,  0.9997073, 0.9477881, 0.9063306,
                          0.8742425, 0.8493319, 0.8295063, 0.8131908,
                          0.7992435, 0.7869503, 0.7758618, 0.7656981,
                          0.7562473, 0.747424,  0.7391417, 0.7314165};
  Double_t _felx3009[20] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                            0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                            0.25, 0.25, 0.25, 0.25, 0.25, 0.25};
  Double_t _fely3009[20] = {0.1300286,  0.104464,  0.07838074, 0.06356422,
                            0.08407505, 0.1112106, 0.1298893,  0.1388549,
                            0.1413751,  0.1404776, 0.1381354,  0.1354611,
                            0.1328951,  0.1306298, 0.128725,   0.1271533,
                            0.1258749,  0.124885,  0.1241279,  0.123627};
  Double_t _fehx3009[20] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                            0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                            0.25, 0.25, 0.25, 0.25, 0.25, 0.25};
  Double_t _fehy3009[20] = {0.1468046,  0.1267466,  0.09211422, 0.05057063,
                            0.05037912, 0.06329431, 0.07786601, 0.08816704,
                            0.09429691, 0.09765544, 0.0994862,  0.1005036,
                            0.1011301,  0.1015666,  0.1019135,  0.1022142,
                            0.1025252,  0.1028118,  0.1031375,  0.1035124};
  grae = new TGraphAsymmErrors(20, _fx3009, _fy3009, _felx3009, _fehx3009,
                               _fely3009, _fehy3009);
  grae->SetName("");
  grae->SetTitle("");

  ci = TColor::GetColor("#0000ff");
  grae->SetFillColor(ci);
  //     grae->SetFillStyle(3003);
  //     grae->SetFillStyle(3018);
  grae->SetFillStyle(3018);

  ci = TColor::GetColor("#0000ff");
  grae->SetLineColor(ci);
  grae->SetLineWidth(2);
  grae->SetMarkerStyle(20);

  TH1F *Graph_Graph3009 = new TH1F("Graph_Graph3009", "", 100, -6, 6);
  Graph_Graph3009->SetMinimum(0.5418559);
  Graph_Graph3009->SetMaximum(1.333059);
  Graph_Graph3009->SetDirectory(0);
  Graph_Graph3009->SetStats(0);
  Graph_Graph3009->SetLineWidth(3);
  Graph_Graph3009->SetMarkerStyle(20);
  Graph_Graph3009->GetXaxis()->SetNdivisions(505);
  Graph_Graph3009->GetXaxis()->SetLabelFont(132);
  Graph_Graph3009->GetXaxis()->SetLabelOffset(0.01);
  Graph_Graph3009->GetXaxis()->SetLabelSize(0.06);
  Graph_Graph3009->GetXaxis()->SetTitleSize(0.072);
  Graph_Graph3009->GetXaxis()->SetTitleOffset(0.95);
  Graph_Graph3009->GetXaxis()->SetTitleFont(132);
  Graph_Graph3009->GetYaxis()->SetLabelFont(132);
  Graph_Graph3009->GetYaxis()->SetLabelOffset(0.01);
  Graph_Graph3009->GetYaxis()->SetLabelSize(0.06);
  Graph_Graph3009->GetYaxis()->SetTitleSize(0.072);
  Graph_Graph3009->GetYaxis()->SetTitleOffset(0.9);
  Graph_Graph3009->GetYaxis()->SetTitleFont(132);
  Graph_Graph3009->GetZaxis()->SetLabelFont(132);
  Graph_Graph3009->GetZaxis()->SetLabelSize(0.06);
  Graph_Graph3009->GetZaxis()->SetTitleSize(0.072);
  Graph_Graph3009->GetZaxis()->SetTitleOffset(1.2);
  Graph_Graph3009->GetZaxis()->SetTitleFont(132);
  grae->SetHistogram(Graph_Graph3009);

  grae->Draw(",e2z");

  Double_t _fx3007[20] = {-4.75, -4.25, -3.75, -3.25, -2.75, -2.25, -1.75,
                          -1.25, -0.75, -0.25, 0.25,  0.75,  1.25,  1.75,
                          2.25,  2.75,  3.25,  3.75,  4.25,  4.75};
  Double_t _fy3007[20] = {1.088609,  1.126229,  1.135278,  1.109855,
                          1.06175,   1.007407,  0.9572993, 0.915485,
                          0.8822197, 0.8562116, 0.8355638, 0.8187584,
                          0.8047303, 0.7927435, 0.7822257, 0.7728413,
                          0.7644247, 0.7567923, 0.7498045, 0.7434512};
  Double_t _felx3007[20] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                            0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                            0.25, 0.25, 0.25, 0.25, 0.25, 0.25};
  Double_t _fely3007[20] = {0.09919654, 0.08844726, 0.06789779, 0.04310173,
                            0.06242828, 0.08700388, 0.1043509,  0.1168524,
                            0.1256461,  0.1313286,  0.1344911,  0.1359703,
                            0.1364384,  0.1363709,  0.1360571,  0.1356581,
                            0.1352756,  0.1349772,  0.1347552,  0.1346734};
  Double_t _fehx3007[20] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                            0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                            0.25, 0.25, 0.25, 0.25, 0.25, 0.25};
  Double_t _fehy3007[20] = {0.1041455,  0.09033128, 0.06535085, 0.04042193,
                            0.0407214,  0.04830556, 0.06690862, 0.07989918,
                            0.08885123, 0.09502154, 0.09942191, 0.1025856,
                            0.1049819,  0.1068842,  0.1084464,  0.1097623,
                            0.1109147,  0.1119373,  0.1128831,  0.1137536};
  grae = new TGraphAsymmErrors(20, _fx3007, _fy3007, _felx3007, _fehx3007,
                               _fely3007, _fehy3007);
  grae->SetName("");
  grae->SetTitle("");

  ci = 1184;
  color = new TColor(ci, 1, 0.6, 0.6, " ", 0.35);
  //  grae->SetFillColor(ci);
  grae->SetFillColor(kPink + 2);
  //  grae->SetFillStyle(3023);
  grae->SetFillStyle(3002);
  //  grae->SetOpacity(0.7);
  //  grae->SetFillStyle(3620);
  grae->SetLineColor(kMagenta - 10);
  //  grae->SetLineStyle(kPink+4);
  grae->SetLineWidth(2);
  grae->SetMarkerStyle(20);

  TH1F *Graph_Graph3007 = new TH1F("Graph_Graph3007", "", 100, -6, 6);
  Graph_Graph3007->SetMinimum(0.5479995);
  Graph_Graph3007->SetMaximum(1.277338);
  Graph_Graph3007->SetDirectory(0);
  Graph_Graph3007->SetStats(0);
  Graph_Graph3007->SetLineWidth(3);
  Graph_Graph3007->SetMarkerStyle(20);
  Graph_Graph3007->GetXaxis()->SetNdivisions(505);
  Graph_Graph3007->GetXaxis()->SetLabelFont(132);
  Graph_Graph3007->GetXaxis()->SetLabelOffset(0.01);
  Graph_Graph3007->GetXaxis()->SetLabelSize(0.06);
  Graph_Graph3007->GetXaxis()->SetTitleSize(0.072);
  Graph_Graph3007->GetXaxis()->SetTitleOffset(0.95);
  Graph_Graph3007->GetXaxis()->SetTitleFont(132);
  Graph_Graph3007->GetYaxis()->SetLabelFont(132);
  Graph_Graph3007->GetYaxis()->SetLabelOffset(0.01);
  Graph_Graph3007->GetYaxis()->SetLabelSize(0.06);
  Graph_Graph3007->GetYaxis()->SetTitleSize(0.072);
  Graph_Graph3007->GetYaxis()->SetTitleOffset(0.9);
  Graph_Graph3007->GetYaxis()->SetTitleFont(132);
  Graph_Graph3007->GetZaxis()->SetLabelFont(132);
  Graph_Graph3007->GetZaxis()->SetLabelSize(0.06);
  Graph_Graph3007->GetZaxis()->SetTitleSize(0.072);
  Graph_Graph3007->GetZaxis()->SetTitleOffset(1.2);
  Graph_Graph3007->GetZaxis()->SetTitleFont(132);
  grae->SetHistogram(Graph_Graph3007);

  grae->Draw(",e2z");

  SetStyleHisto(npJPsiRpPb);
  npJPsiRpPb->SetStats(0);
  //  npJPsiRpPb->SetLineColor(kMagenta+2);
  //  ci = TColor::GetColor("#006600");

  npJPsiRpPb->SetLineColor(kGreen + 2);
  npJPsiRpPb->SetLineWidth(3);
  //  npJPsiRpPb->SetMarkerColor(kMagenta+2);
  npJPsiRpPb->SetMarkerColor(kGreen + 2);
  npJPsiRpPb->SetMarkerStyle(21);

  SetStyleHisto(BplusRpPb);
  BplusRpPb->SetStats(0);
  //  BplusRpPb->SetLineColor(kBlack);
  //  BplusRpPb->SetLineColor(kRed+1);
  BplusRpPb->SetLineColor(kViolet + 1);
  BplusRpPb->SetLineWidth(3);
  //  BplusRpPb->SetMarkerColor(kBlack);
  //  BplusRpPb->SetMarkerColor(kRed+1);
  BplusRpPb->SetMarkerColor(kViolet + 1);
  BplusRpPb->SetMarkerStyle(21);

  //  SetStyleHisto(hPtIntD0RpPb);
  //  hPtIntD0RpPb->SetStats(0);
  //  hPtIntD0RpPb->SetLineColor(kAzure+2);
  //  hPtIntD0RpPb->SetMarkerColor(kAzure+2);
  //  hPtIntD0RpPb->SetMarkerStyle(20);

  SetStyleHisto(hPtIntD0RpPbLHCb);
  hPtIntD0RpPbLHCb->SetStats(0);
  //  hPtIntD0RpPbLHCb->SetLineColor(kAzure+2);
  //  hPtIntD0RpPbLHCb->SetMarkerColor(kAzure+2);
  hPtIntD0RpPbLHCb->SetLineColor(kBlack);
  hPtIntD0RpPbLHCb->SetLineWidth(3);
  hPtIntD0RpPbLHCb->SetMarkerColor(kBlack);
  hPtIntD0RpPbLHCb->SetMarkerStyle(20);

  SetStyleHisto(ALICEJPsiRpPb);
  ALICEJPsiRpPb->SetStats(0);
  //  hPtIntD0RpPbLHCb->SetLineColor(kAzure+2);
  //  hPtIntD0RpPbLHCb->SetMarkerColor(kAzure+2);
  ALICEJPsiRpPb->SetLineColor(kOrange + 2);
  ALICEJPsiRpPb->SetLineWidth(3);
  ALICEJPsiRpPb->SetMarkerColor(kOrange + 2);
  ALICEJPsiRpPb->SetMarkerStyle(20);

  TLatex info;
  info.SetNDC();
  info.SetTextFont(43);
  info.SetTextSize(30);
  info.DrawLatex(0.20, 0.89, "ALICE Preliminary");

  TLatex info2;
  info2.SetNDC();
  info2.SetTextFont(43);
  info2.SetTextSize(25);
  info2.DrawLatex(0.20, 0.84,
                  "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  info2.DrawLatex(0.25, 0.64, "#it{p}_{T} > 0");
  info2.DrawLatex(0.25, 0.75, "2 < #it{p}_{T} < 24 GeV/#it{c}");

  //  gJPsiSystematics->Draw("same2");
  npJPsiRpPb->Draw("e0 same");
  gBplusSystematics->Draw("same2");
  BplusRpPb->Draw("e0 same");
  //  gPtIntD0RpPbSystematics->Draw("same2");
  //  gPtIntD0RpPbSystematicsExtr->Draw("same2");
  //  hPtIntD0RpPb->Draw("e0 same");
  gPtIntD0RpPbSystematicsLHCb->Draw("same2");
  hPtIntD0RpPbLHCb->Draw("e0 same");
  gALICEJPsiSystematics->Draw("same2");
  gALICEJPsiSystematicsExtr->Draw("same2");
  ALICEJPsiRpPb->Draw("e0 same");

  TLegend *leg1 = new TLegend(0.19, 0.62, 0.32, 0.86);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetMargin(0.46);
  leg1->SetTextSize(25);
  leg1->SetTextFont(43);
  leg1->SetNColumns(1);
  leg1->AddEntry(hPtIntD0RpPbLHCb, "Non-prompt D^{0}", "pl");
  leg1->AddEntry(ALICEJPsiRpPb, "Non-prompt #it{J}/#it{#psi}", "pl");
  //  leg1->AddEntry(hPtIntD0RpPbLHCb, "Non-prompt D^{0}", "pl");
  //  leg->AddEntry(hPtIntD0RpPb, "0-24 GeV/#it{c} extrapolated", "pl");
  //  leg->AddEntry(gPtIntD0RpPbSystematicsExtr, "extr. unc.");
  leg1->Draw();

  TLatex infoLHCb;
  infoLHCb.SetNDC();
  infoLHCb.SetTextFont(43);
  infoLHCb.SetTextSize(27);
  infoLHCb.DrawLatex(0.56, 0.89, "LHCb");

  TLegend *legLHCb = new TLegend(0.55, 0.62, 0.68, 0.86);
  legLHCb->SetFillColor(0);
  legLHCb->SetFillStyle(0);
  legLHCb->SetBorderSize(0);
  legLHCb->SetMargin(0.46);
  legLHCb->SetTextSize(25);
  legLHCb->SetTextFont(43);
  legLHCb->SetNColumns(1);
  //  legLHCb->AddEntry(npJPsiRpPb, "Non-prompt #it{J}/#it{#psi}");
  legLHCb->AddEntry(BplusRpPb, "B^{+}");
  legLHCb->AddEntry(npJPsiRpPb, "Non-prompt #it{J}/#it{#psi}");
  legLHCb->Draw();

  TLatex infoLHCb2;
  infoLHCb2.SetNDC();
  infoLHCb2.SetTextFont(43);
  infoLHCb2.SetTextSize(25);
  //  infoLHCb2.DrawLatex(0.59, 0.89, "LHCb");
  infoLHCb2.DrawLatex(
      0.56, 0.84,
      "p#font[122]{-}Pb/Pb#font[122]{-}p, #sqrt{#it{s}_{NN}} = 8.16 TeV");
  infoLHCb2.DrawLatex(0.61, 0.64, "0 < #it{p}_{T} < 14 GeV/#it{c}");
  infoLHCb2.DrawLatex(0.61, 0.75, "2 < #it{p}_{T} < 20 GeV/#it{c}");

  TLatex inforef;
  inforef.SetNDC();
  inforef.SetTextFont(43);
  inforef.SetTextSize(22);
  inforef.DrawLatex(0.61, 0.6, "PLB 774 (2017) 159-178");
  inforef.DrawLatex(0.61, 0.71, "PRD 99 (2019) 052011");
  inforef.DrawLatex(0.25, 0.6, "EPJC 78 (2018) 466");

  //  TLatex models;
  //  models.SetNDC();
  //  models.SetTextFont(43);
  //  models.SetTextSize(25);
  //  models.DrawLatex(0.21, 0.31, "Models:");

  TLegend *legALICEJPsi = new TLegend(0.19, 0.55, 0.32, 0.6);
  legALICEJPsi->SetFillColor(0);
  legALICEJPsi->SetFillStyle(0);
  legALICEJPsi->SetBorderSize(0);
  legALICEJPsi->SetMargin(0.46);
  legALICEJPsi->SetTextSize(25);
  legALICEJPsi->SetTextFont(43);
  legALICEJPsi->SetNColumns(1);
  legALICEJPsi->AddEntry(gALICEJPsiSystematicsExtr, "extr. unc.", "F");
  legALICEJPsi->Draw();

  TGraphAsymmErrors *graph1 = new TGraphAsymmErrors(1);
  TGraphAsymmErrors *graph2 = new TGraphAsymmErrors(2);
  TGraphAsymmErrors *graph3 = new TGraphAsymmErrors(3);

  ci = TColor::GetColor("#ff0000");
  graph1->SetFillColor(ci);
  graph1->SetLineColor(ci);
  graph1->SetLineWidth(2);
  graph1->SetFillStyle(3654);

  ci = TColor::GetColor("#0000ff");
  graph2->SetFillColor(ci);
  graph2->SetLineColor(ci);
  graph2->SetLineWidth(2);
  //  graph2->SetFillStyle(3003);
  graph2->SetFillStyle(3018);

  ci = 1184;
  //  graph3->SetFillColor(ci);
  graph3->SetFillColor(kPink + 2);
  graph3->SetLineColor(kPink + 2);
  graph3->SetLineWidth(0);
  //  graph3->SetFillStyle(1001);
  graph3->SetFillStyle(3002);
  graph3->SetMarkerColor(kPink + 2);
  graph3->SetMarkerSize(0);

  TLegend *model = new TLegend(0.21, 0.17, 0.32, 0.3);
  model->SetFillColor(0);
  model->SetFillStyle(0);
  model->SetBorderSize(0);
  model->SetMargin(0.46);
  model->SetTextSize(25);
  model->SetTextFont(43);
  model->SetNColumns(1);
  model->AddEntry(graph1, "EPPS16", "F");
  model->AddEntry(graph2, "nCTEQ15", "F");
  model->AddEntry(graph3, "EPPS16*", "F");
  model->Draw();

  TLine *unit = new TLine(-5, 1, 5, 1);
  unit->SetLineStyle(3);
  unit->Draw();
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
