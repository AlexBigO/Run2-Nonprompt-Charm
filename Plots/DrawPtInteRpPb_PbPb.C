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

void DrawPtInteRpPb_PbPb() {

  // prompt D0 RpPb

  //  Float_t JPsiBins[11] = {-4.5, -4., -3.5, -3.,
  //  -2.5, 1.5, 2., 2.5, 3., 3.5, 4.}; Double_t JPsiBinContent[10] =
  //  {1.1, 1.03, 0.97, 1, -1., 0.84, 0.89, 0.8, 0.8, 0.82}; Double_t
  //  JPsiBinError[10] = {0.13, 0.11, 0.11, 0.14, 0., 0.17, 0.09, 0.07, 0.07,
  //  0.08}; TH1F* npJPsiRpPb = new TH1F("npJPsi", "npJPsi", 10, JPsiBins);
  //  for(int iPt = 0; iPt < 10; iPt++) {
  //    npJPsiRpPb->SetBinContent(iPt+1, JPsiBinContent[iPt]);
  //    npJPsiRpPb->SetBinError(iPt+1, JPsiBinError[iPt]);
  //  }
  //
  //  Float_t BplusBins[4] = {-3.5, -2.5, 2.5, 3.5};
  //  Double_t BplusBinContent[3] = {1., -1., 0.78};
  //  Double_t BplusBinError[3] = {0.03, 0., 0.02};
  //  TH1F* BplusRpPb = new TH1F("BplusRpPb", "BplusRpPb", 3, BplusBins);
  //  for(int iPt = 0; iPt < 3; iPt++) {
  //    BplusRpPb->SetBinContent(iPt+1, BplusBinContent[iPt]);
  //    BplusRpPb->SetBinError(iPt+1, BplusBinError[iPt]);
  //  }
  //
  //  TGraphAsymmErrors* gJPsiSystematics = new TGraphAsymmErrors(9,
  //  ptlimsmiddleJPsi, yvaluncJPsi); for (Int_t i = 0; i < 9; i++) {
  //    Double_t ptx = 0.2;
  //    gJPsiSystematics->SetPoint(i, ptlimsmiddleJPsi[i], yvaluncJPsi[i]);
  //    gJPsiSystematics->SetPointError(i, ptx, ptx, yuncJPsi[i], yuncJPsi[i]);
  //  }
  //
  //  gJPsiSystematics->SetFillStyle(1001);
  //  gJPsiSystematics->SetFillColor(kGreen-10);
  //  gJPsiSystematics->SetLineWidth(2);
  //  gJPsiSystematics->SetLineColor(kGreen-10);
  //
  //  TGraphAsymmErrors* gBplusSystematics = new TGraphAsymmErrors(2,
  //  ptlimsmiddleBplus, yvaluncBplus); for (Int_t i = 0; i < 2; i++) {
  //    Double_t ptx = 0.2;
  //    gBplusSystematics->SetPoint(i, ptlimsmiddleBplus[i], yvaluncBplus[i]);
  //    gBplusSystematics->SetPointError(i, ptx, ptx, yuncBplus[i],
  //    yuncBplus[i]);
  //  }
  //
  //  gBplusSystematics->SetFillStyle(0);
  //  gBplusSystematics->SetFillColor(kWhite);
  //  gBplusSystematics->SetLineWidth(2);
  //  gBplusSystematics->SetLineColor(kBlack);
  //
  //  const Int_t nptlimsExtra = 22;
  //  Float_t ptlimsExtral[nptlimsExtra+1] =
  //  {0., 1., 1.5, 2., 2.5, 3., 3.5, 4., 4.5, 5., 5.5, 6., 6.5, 7., 7.5, 8., 9.,
  //  10., 12., 16., 24., 36., 38.};
  //
  TH1D *hrefPrompt = new TH1D("hrefPrompt", "hrefPrompt", 3, 0, 3);
  hrefPrompt->SetTitle("");
  hrefPrompt->GetYaxis()->SetTitle("Nuclear modification factor");
  hrefPrompt->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  hrefPrompt->SetMinimum(0.41);
  hrefPrompt->SetMaximum(2.19);
  SetStyleHisto(hrefPrompt);
  hrefPrompt->SetLineWidth(1);
  hrefPrompt->GetYaxis()->SetTitleOffset(1.3);
  hrefPrompt->GetXaxis()->SetTitle("");
  hrefPrompt->GetXaxis()->SetBinLabel(1,
                                      "p#font[122]{-}Pb, 0#font[122]{-}100%");
  hrefPrompt->GetXaxis()->SetBinLabel(2,
                                      "Pb#font[122]{-}Pb, 30#font[122]{-}50%");
  hrefPrompt->GetXaxis()->SetBinLabel(3,
                                      "Pb#font[122]{-}Pb, 0#font[122]{-}10%");

  // Prompt RPbPb
  TH1F *hPtIntD0PbPb3050 =
      new TH1F("hPtIntD0PbPb3050", "hPtIntD0PbPb3050", 1, 1, 2);
  hPtIntD0PbPb3050->SetBinContent(1, 0.774596);
  hPtIntD0PbPb3050->SetBinError(1, 0.069333);

  Double_t ptlimsmiddlePbPb3050[1] = {1.5};
  Double_t yuncPbPb3050[1] = {0.};
  TGraphAsymmErrors *gPtIntD0RPbPbSystematics3050 =
      new TGraphAsymmErrors(1, ptlimsmiddlePbPb3050, yuncPbPb3050);
  for (Int_t i = 0; i < 1; i++) {
    Double_t RpPbFD = hPtIntD0PbPb3050->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    gPtIntD0RPbPbSystematics3050->SetPoint(i, 1.5, RpPbFD);
    gPtIntD0RPbPbSystematics3050->SetPointError(i, ptx, ptx, 0.119790,
                                                0.116672);
  }

  gPtIntD0RPbPbSystematics3050->SetFillStyle(0);
  gPtIntD0RPbPbSystematics3050->SetFillColor(kWhite);
  gPtIntD0RPbPbSystematics3050->SetLineWidth(2);
  gPtIntD0RPbPbSystematics3050->SetLineColor(kRed + 1);

  TH1F *hPtIntD0PbPb010 =
      new TH1F("hPtIntD0PbPb010", "hPtIntD0PbPb010", 1, 2, 3);
  hPtIntD0PbPb010->SetBinContent(1, 0.689416);
  hPtIntD0PbPb010->SetBinError(1, 0.053928);

  Double_t ptlimsmiddlePbPb010[1] = {2.5};
  Double_t yuncPbPb010[1] = {0.};
  TGraphAsymmErrors *gPtIntD0RPbPbSystematics010 =
      new TGraphAsymmErrors(1, ptlimsmiddlePbPb010, yuncPbPb010);
  for (Int_t i = 0; i < 1; i++) {
    Double_t RpPbFD = hPtIntD0PbPb010->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    gPtIntD0RPbPbSystematics010->SetPoint(i, 2.5, RpPbFD);
    gPtIntD0RPbPbSystematics010->SetPointError(i, ptx, ptx, 0.106183, 0.104013);
  }

  gPtIntD0RPbPbSystematics010->SetFillStyle(0);
  gPtIntD0RPbPbSystematics010->SetFillColor(kWhite);
  gPtIntD0RPbPbSystematics010->SetLineWidth(2);
  gPtIntD0RPbPbSystematics010->SetLineColor(kRed + 1);

  TH1F *hPtIntD0PbPb3050np =
      new TH1F("hPtIntD0PbPb3050np", "hPtIntD0PbPb3050np", 1, 1, 2);
  hPtIntD0PbPb3050np->SetBinContent(1, 1.10);
  hPtIntD0PbPb3050np->SetBinError(1, 0.12);

  Double_t ptlimsmiddlePbPb3050np[1] = {1.5};
  Double_t yuncPbPb3050np[1] = {0.};
  TGraphAsymmErrors *gPtIntD0RPbPbSystematics3050np =
      new TGraphAsymmErrors(1, ptlimsmiddlePbPb3050np, yuncPbPb3050np);
  for (Int_t i = 0; i < 1; i++) {
    Double_t RpPbFD = hPtIntD0PbPb3050np->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    gPtIntD0RPbPbSystematics3050np->SetPoint(i, 1.5, RpPbFD);
    gPtIntD0RPbPbSystematics3050np->SetPointError(i, ptx, ptx, 0.15, 0.15);
  }

  gPtIntD0RPbPbSystematics3050np->SetFillStyle(0);
  gPtIntD0RPbPbSystematics3050np->SetFillColor(kWhite);
  gPtIntD0RPbPbSystematics3050np->SetLineWidth(2);
  gPtIntD0RPbPbSystematics3050np->SetLineColor(kGreen + 3);

  Double_t PtIntD0RPbPbSystematicsExtra3050np[1] = {0.5};
  //  Double_t yuncD0[1] = {0.};
  TGraphAsymmErrors *gPtIntD0RPbPbSystematicsExtr3050np = new TGraphAsymmErrors(
      1, PtIntD0RPbPbSystematicsExtra3050np, yuncPbPb3050np);
  for (Int_t i = 0; i < 1; i++) {
    Double_t RpPbFD = hPtIntD0PbPb3050np->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    gPtIntD0RPbPbSystematicsExtr3050np->SetPoint(i, 1.5, RpPbFD);
    gPtIntD0RPbPbSystematicsExtr3050np->SetPointError(i, ptx, ptx, 0.09, 0.08);
  }

  gPtIntD0RPbPbSystematicsExtr3050np->SetFillStyle(3004);
  //  gPtIntD0RPbPbSystematicsExtr3050np->SetFillStyle(3002);
  gPtIntD0RPbPbSystematicsExtr3050np->SetFillColor(kGreen + 3);
  gPtIntD0RPbPbSystematicsExtr3050np->SetLineWidth(2);
  gPtIntD0RPbPbSystematicsExtr3050np->SetLineColor(kGreen + 3);

  TH1F *hPtIntD0PbPb010np =
      new TH1F("hPtIntD0PbPb010np", "hPtIntD0PbPb010np", 1, 2, 3);
  hPtIntD0PbPb010np->SetBinContent(1, 1.00);
  hPtIntD0PbPb010np->SetBinError(1, 0.1);

  Double_t ptlimsmiddlePbPb010np[1] = {2.5};
  Double_t yuncPbPb010np[1] = {0.};
  TGraphAsymmErrors *gPtIntD0RPbPbSystematics010np =
      new TGraphAsymmErrors(1, ptlimsmiddlePbPb010np, yuncPbPb010np);
  for (Int_t i = 0; i < 1; i++) {
    Double_t RpPbFD = hPtIntD0PbPb010np->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    gPtIntD0RPbPbSystematics010np->SetPoint(i, 2.5, RpPbFD);
    gPtIntD0RPbPbSystematics010np->SetPointError(i, ptx, ptx, 0.13, 0.13);
  }

  gPtIntD0RPbPbSystematics010np->SetFillStyle(0);
  gPtIntD0RPbPbSystematics010np->SetFillColor(kWhite);
  gPtIntD0RPbPbSystematics010np->SetLineWidth(2);
  gPtIntD0RPbPbSystematics010np->SetLineColor(kGreen + 3);

  Double_t PtIntD0RPbPbSystematicsExtra010np[1] = {0.5};
  //  Double_t yuncD0[1] = {0.};
  TGraphAsymmErrors *gPtIntD0RPbPbSystematicsExtr010np = new TGraphAsymmErrors(
      1, PtIntD0RPbPbSystematicsExtra010np, yuncPbPb010np);
  for (Int_t i = 0; i < 1; i++) {
    Double_t RpPbFD = hPtIntD0PbPb010np->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    gPtIntD0RPbPbSystematicsExtr010np->SetPoint(i, 2.5, RpPbFD);
    gPtIntD0RPbPbSystematicsExtr010np->SetPointError(i, ptx, ptx, 0.09, 0.08);
  }

  gPtIntD0RPbPbSystematicsExtr010np->SetFillStyle(3004);
  //  gPtIntD0RPbPbSystematicsExtr010np->SetFillStyle(3002);
  gPtIntD0RPbPbSystematicsExtr010np->SetFillColor(kGreen + 3);
  gPtIntD0RPbPbSystematicsExtr010np->SetLineWidth(0);
  gPtIntD0RPbPbSystematicsExtr010np->SetLineColor(kGreen + 3);
  gPtIntD0RPbPbSystematicsExtr010np->SetMarkerSize(0);

  TH1F *hPtIntD0pPbPrompt =
      new TH1F("hPtIntD0pPbPrompt", "hPtIntD0pPbPrompt", 1, 0, 1);
  hPtIntD0pPbPrompt->SetBinContent(1, 0.96);
  hPtIntD0pPbPrompt->SetBinError(1, 0.05);

  Double_t ptlimsmiddlepPbPrompt[1] = {0.5};
  Double_t yuncpPbPrompt[1] = {0.};
  TGraphAsymmErrors *gPtIntD0RpPbSystematicsPrompt =
      new TGraphAsymmErrors(1, ptlimsmiddlepPbPrompt, yuncPbPb010);
  for (Int_t i = 0; i < 1; i++) {
    Double_t RpPbFD = hPtIntD0pPbPrompt->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    gPtIntD0RpPbSystematicsPrompt->SetPoint(i, 0.5, RpPbFD);
    gPtIntD0RpPbSystematicsPrompt->SetPointError(i, ptx, ptx, 0.07, 0.07);
  }

  gPtIntD0RpPbSystematicsPrompt->SetFillStyle(0);
  gPtIntD0RpPbSystematicsPrompt->SetFillColor(kWhite);
  gPtIntD0RpPbSystematicsPrompt->SetLineWidth(2);
  gPtIntD0RpPbSystematicsPrompt->SetLineColor(kRed + 1);

  // non-prompt D0 RpPb
  TH1F *hPtIntD0pPb = new TH1F("hPtIntD0pPb", "hPtIntD0pPb", 1, 0, 1);
  //  hPtIntD0pPb->SetBinContent(1, 3911.2188);
  hPtIntD0pPb->SetBinContent(1, 3988.5);
  //  hPtIntD0pPb->SetBinError(1, 229.08);
  hPtIntD0pPb->SetBinError(1, 233.6);

  //  Double_t SystIntD0pPbCorr = 78.57;
  //  Double_t SystIntD0pPbUnCorr = 173.52;
  Double_t SystIntD0pPbSyst = 281.9;
  //  Double_t SystIntD0pPbExtraLow = 73.18;
  Double_t SystIntD0pPbExtraLow = 306.6;
  //  Double_t SystIntD0pPbExtraHigh = 120.55;
  Double_t SystIntD0pPbExtraHigh = 199.6;

  TH1F *hPtIntD0pp = new TH1F("hPtIntD0pp", "hPtIntD0pp", 1, 0, 1);
  hPtIntD0pp->SetBinContent(1, 18.08);
  //  hPtIntD0pp->SetBinError(1, 1.47);
  hPtIntD0pp->SetBinError(1, 1.5);

  //  Double_t SystIntD0ppCorr = 1.53;
  //  Double_t SystIntD0ppUnCorr = 0.53;
  Double_t SystIntD0ppSyst = 1.6;
  //  Double_t SystIntD0ppExtraLow = 0.34;
  Double_t SystIntD0ppExtraLow = 0.6;
  //  Double_t SystIntD0ppExtraHigh = 0.07;
  Double_t SystIntD0ppExtraHigh = 0.1;

  TH1F *hPtIntD0RpPb = (TH1F *)hPtIntD0pPb->Clone("hPtIntD0RpPb");
  hPtIntD0RpPb->Divide(hPtIntD0pp);
  hPtIntD0RpPb->Scale(1. / 208.);

  //  Double_t SystIntD0RpPbCorr = (SystIntD0pPbCorr + SystIntD0pPbCorr) /
  //  hPtIntD0pp->GetBinContent(1); Double_t SystIntD0RpPbUnCorr =
  //  TMath::Sqrt(SystIntD0pPbUnCorr*SystIntD0pPbUnCorr +
  //  SystIntD0ppUnCorr*SystIntD0ppUnCorr) / hPtIntD0pp->GetBinContent(1);
  //  Double_t SystIntD0RpPbLow =
  //  TMath::Sqrt(SystIntD0pPbExtraLow*SystIntD0pPbExtraLow +
  //  SystIntD0ppExtraLow*SystIntD0ppExtraLow) / hPtIntD0pp->GetBinContent(1);
  //  Double_t SystIntD0RpPbHigh =
  //  TMath::Sqrt(SystIntD0pPbExtraHigh*SystIntD0pPbExtraHigh +
  //  SystIntD0ppExtraHigh*SystIntD0ppExtraHigh) / hPtIntD0pp->GetBinContent(1);
  //  Double_t SystIntD0RpPbTotalLow =
  //  TMath::Sqrt(SystIntD0RpPbCorr*SystIntD0RpPbCorr +
  //  SystIntD0RpPbUnCorr*SystIntD0RpPbUnCorr +
  //  SystIntD0RpPbLow*SystIntD0RpPbLow) / 208.; Double_t SystIntD0RpPbTotalHigh
  //  = TMath::Sqrt(SystIntD0RpPbCorr*SystIntD0RpPbCorr +
  //  SystIntD0RpPbUnCorr*SystIntD0RpPbUnCorr +
  //  SystIntD0RpPbHigh*SystIntD0RpPbHigh) / 208.;
  Double_t SystIntD0RpPb = hPtIntD0RpPb->GetBinContent(1) *
                           TMath::Sqrt(SystIntD0pPbSyst * SystIntD0pPbSyst /
                                           hPtIntD0pPb->GetBinContent(1) /
                                           hPtIntD0pPb->GetBinContent(1) +
                                       SystIntD0ppSyst * SystIntD0ppSyst /
                                           hPtIntD0pp->GetBinContent(1) /
                                           hPtIntD0pp->GetBinContent(1));

  Double_t SystIntD0RpPbLowExtr =
      hPtIntD0RpPb->GetBinContent(1) *
      (SystIntD0pPbExtraLow / hPtIntD0pPb->GetBinContent(1) +
       SystIntD0ppExtraLow / hPtIntD0pp->GetBinContent(1));

  Double_t SystIntD0RpPbHighExtr =
      hPtIntD0RpPb->GetBinContent(1) *
      (SystIntD0pPbExtraHigh / hPtIntD0pPb->GetBinContent(1) +
       SystIntD0ppExtraHigh / hPtIntD0pp->GetBinContent(1));

  Double_t gPtIntD0RpPbSystematicsMiddle[1] = {0.5};
  Double_t yuncD0[1] = {0.};
  TGraphAsymmErrors *gPtIntD0RpPbSystematics =
      new TGraphAsymmErrors(1, gPtIntD0RpPbSystematicsMiddle, yuncD0);
  for (Int_t i = 0; i < 1; i++) {
    Double_t RpPbFD = hPtIntD0RpPb->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    gPtIntD0RpPbSystematics->SetPoint(i, 0.5, RpPbFD);
    gPtIntD0RpPbSystematics->SetPointError(i, ptx, ptx, SystIntD0RpPb,
                                           SystIntD0RpPb);
  }

  gPtIntD0RpPbSystematics->SetFillStyle(0);
  gPtIntD0RpPbSystematics->SetFillColor(kWhite);
  gPtIntD0RpPbSystematics->SetLineWidth(2);
  gPtIntD0RpPbSystematics->SetLineColor(kAzure + 2);

  Double_t gPtIntD0RpPbSystematicsExtra[1] = {0.5};
  //  Double_t yuncD0[1] = {0.};
  TGraphAsymmErrors *gPtIntD0RpPbSystematicsExtr =
      new TGraphAsymmErrors(1, gPtIntD0RpPbSystematicsExtra, yuncD0);
  for (Int_t i = 0; i < 1; i++) {
    Double_t RpPbFD = hPtIntD0RpPb->GetBinContent(i + 1);
    Double_t ptx = 0.3;
    gPtIntD0RpPbSystematicsExtr->SetPoint(i, 0.5, RpPbFD);
    gPtIntD0RpPbSystematicsExtr->SetPointError(
        i, ptx, ptx, SystIntD0RpPbLowExtr, SystIntD0RpPbHighExtr);
  }

  gPtIntD0RpPbSystematicsExtr->SetFillStyle(3004);
  //  gPtIntD0RpPbSystematicsExtr->SetFillStyle(3002);
  gPtIntD0RpPbSystematicsExtr->SetFillColor(kAzure + 2);
  gPtIntD0RpPbSystematicsExtr->SetLineWidth(0);
  gPtIntD0RpPbSystematicsExtr->SetLineStyle(3);
  gPtIntD0RpPbSystematicsExtr->SetLineColor(kAzure + 2);
  gPtIntD0RpPbSystematicsExtr->SetMarkerColor(kAzure + 2);
  gPtIntD0RpPbSystematicsExtr->SetMarkerSize(0);
  //  gPtIntD0RpPbSystematicsExtr->SetMarkerColor(kWhite);

  //  TH1F* hPtIntD0pPbLHCb = new TH1F("hPtIntD0pPbLHCb", "hPtIntD0pPbLHCb", 1,
  //  -0.96, 0.04); hPtIntD0pPbLHCb->SetBinContent(1, 1791.27);
  //  hPtIntD0pPbLHCb->SetBinError(1, 83.1);
  //
  //  Double_t SystIntD0pPbCorrLHCb = 36.1;
  //  Double_t SystIntD0pPbUnCorrLHCb = 65.16;
  ////  Double_t SystIntD0pPbExtraLowLHCb = 73.18;
  ////  Double_t SystIntD0pPbExtraHighLHCb = 16.16;
  //
  //  TH1F* hPtIntD0ppLHCb = new TH1F("hPtIntD0ppLHCb", "hPtIntD0ppLHCb", 1,
  //  -0.96, 0.04); hPtIntD0ppLHCb->SetBinContent(1, 9.26);
  //  hPtIntD0ppLHCb->SetBinError(1, 0.69);
  //
  //  Double_t SystIntD0ppCorrLHCb = 0.67;
  //  Double_t SystIntD0ppUnCorrLHCb = 0.29;
  ////  Double_t SystIntD0ppExtraLow = 0.34;
  ////  Double_t SystIntD0ppExtraHigh = 0.07;
  //
  //  TH1F* hPtIntD0RpPbLHCb =
  //  (TH1F*)hPtIntD0pPbLHCb->Clone("hPtIntD0RpPbLHCb");
  //  hPtIntD0RpPbLHCb->Divide(hPtIntD0ppLHCb);
  //  hPtIntD0RpPbLHCb->Scale(1./208.);
  //
  //  Double_t SystIntD0RpPbCorrLHCb = (SystIntD0pPbCorrLHCb +
  //  SystIntD0pPbCorrLHCb) / hPtIntD0ppLHCb->GetBinContent(1); Double_t
  //  SystIntD0RpPbUnCorrLHCb =
  //  TMath::Sqrt(SystIntD0pPbUnCorrLHCb*SystIntD0pPbUnCorrLHCb +
  //  SystIntD0ppUnCorrLHCb*SystIntD0ppUnCorrLHCb) /
  //  hPtIntD0ppLHCb->GetBinContent(1); Double_t SystIntD0RpPbTotalLHCb =
  //  TMath::Sqrt(SystIntD0RpPbCorrLHCb*SystIntD0RpPbCorrLHCb +
  //  SystIntD0RpPbUnCorrLHCb*SystIntD0RpPbUnCorrLHCb) / 208.;
  //
  //  Double_t gPtIntD0RpPbSystematicsMiddleLHCb[1] = {-0.46};
  //  Double_t yuncD0LHCb[1] = {0.};
  //    TGraphAsymmErrors* gPtIntD0RpPbSystematicsLHCb = new
  //    TGraphAsymmErrors(1, gPtIntD0RpPbSystematicsMiddleLHCb, yuncD0LHCb); for
  //    (Int_t i = 0; i < 1; i++) {
  //      Double_t RpPbFDLHCb = hPtIntD0RpPbLHCb->GetBinContent(i+1);
  //      Double_t ptx = 0.4;
  //      gPtIntD0RpPbSystematicsLHCb->SetPoint(i, -0.46, RpPbFDLHCb);
  //      gPtIntD0RpPbSystematicsLHCb->SetPointError(i, ptx, ptx,
  //      SystIntD0RpPbTotalLHCb, SystIntD0RpPbTotalLHCb);
  //    }
  //
  //  gPtIntD0RpPbSystematicsLHCb->SetFillStyle(0);
  //  gPtIntD0RpPbSystematicsLHCb->SetFillColor(kWhite);
  //  gPtIntD0RpPbSystematicsLHCb->SetLineWidth(2);
  //  gPtIntD0RpPbSystematicsLHCb->SetLineColor(kRed+1);
  //

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
  //  hrefFD->Draw("same");

  //  SetStyleHisto(npJPsiRpPb);
  //  npJPsiRpPb->SetStats(0);
  //  npJPsiRpPb->SetLineColor(kGreen+2);
  //  npJPsiRpPb->SetMarkerColor(kGreen+2);
  //  npJPsiRpPb->SetMarkerStyle(24);

  //  SetStyleHisto(BplusRpPb);
  //  BplusRpPb->SetStats(0);
  //  BplusRpPb->SetLineColor(kBlack);
  //  BplusRpPb->SetMarkerColor(kBlack);
  //  BplusRpPb->SetMarkerStyle(21);

  SetStyleHisto(hPtIntD0RpPb);
  hPtIntD0RpPb->SetStats(0);
  hPtIntD0RpPb->SetLineColor(kAzure + 2);
  hPtIntD0RpPb->SetMarkerColor(kAzure + 2);
  hPtIntD0RpPb->SetMarkerStyle(20);

  SetStyleHisto(hPtIntD0PbPb3050);
  hPtIntD0PbPb3050->SetStats(0);
  hPtIntD0PbPb3050->SetLineColor(kRed + 1);
  hPtIntD0PbPb3050->SetLineWidth(2);
  hPtIntD0PbPb3050->SetMarkerColor(kRed + 1);
  hPtIntD0PbPb3050->SetMarkerStyle(21);
  hPtIntD0PbPb3050->SetMarkerSize(1);
  hPtIntD0PbPb3050->GetXaxis()->SetLabelOffset(5);
  hPtIntD0PbPb3050->GetXaxis()->SetBinLabel(1,
                                            "#font[122]{-}0.96 < #it{y} <0.04");

  SetStyleHisto(hPtIntD0PbPb010);
  hPtIntD0PbPb010->SetStats(0);
  hPtIntD0PbPb010->SetLineColor(kRed + 1);
  hPtIntD0PbPb010->SetLineWidth(2);
  hPtIntD0PbPb010->SetMarkerColor(kRed + 1);
  hPtIntD0PbPb010->SetMarkerStyle(21);
  hPtIntD0PbPb010->SetMarkerSize(1);

  SetStyleHisto(hPtIntD0PbPb3050np);
  hPtIntD0PbPb3050np->SetStats(0);
  hPtIntD0PbPb3050np->SetLineColor(kGreen + 3);
  hPtIntD0PbPb3050np->SetLineWidth(2);
  hPtIntD0PbPb3050np->SetMarkerColor(kGreen + 3);
  hPtIntD0PbPb3050np->SetMarkerStyle(21);
  hPtIntD0PbPb3050np->SetMarkerSize(1);
  hPtIntD0PbPb3050np->GetXaxis()->SetLabelOffset(5);
  hPtIntD0PbPb3050np->GetXaxis()->SetBinLabel(
      1, "#font[122]{-}0.96 < #it{y} <0.04");

  SetStyleHisto(hPtIntD0PbPb010np);
  hPtIntD0PbPb010np->SetStats(0);
  hPtIntD0PbPb010np->SetLineColor(kGreen + 3);
  hPtIntD0PbPb010np->SetLineWidth(2);
  hPtIntD0PbPb010np->SetMarkerColor(kGreen + 3);
  hPtIntD0PbPb010np->SetMarkerStyle(21);
  hPtIntD0PbPb010np->SetMarkerSize(1);

  SetStyleHisto(hPtIntD0pPbPrompt);
  hPtIntD0pPbPrompt->SetStats(0);
  hPtIntD0pPbPrompt->SetLineColor(kRed + 1);
  hPtIntD0pPbPrompt->SetLineWidth(2);
  hPtIntD0pPbPrompt->SetMarkerColor(kRed + 1);
  hPtIntD0pPbPrompt->SetMarkerStyle(20);

  //  SetStyleHisto(hPtIntD0RpPbLHCb);
  //  hPtIntD0RpPbLHCb->SetStats(0);
  //  hPtIntD0RpPbLHCb->SetLineColor(kRed+1);
  //  hPtIntD0RpPbLHCb->SetMarkerColor(kRed+1);
  //  hPtIntD0RpPbLHCb->SetMarkerStyle(20);
  TLine *unit = new TLine(0, 1, 3, 1);
  unit->SetLineStyle(3);
  unit->Draw();

  TLatex info;
  info.SetNDC();
  info.SetTextFont(43);
  info.SetTextSize(30);
  info.DrawLatex(0.20, 0.89, "ALICE Preliminary");

  TLatex infocontent;
  infocontent.SetNDC();
  infocontent.SetTextFont(43);
  infocontent.SetTextSize(25);
  //  infoPbPb.DrawLatex(0.60, 0.9, "ALICE Preliminary");
  infocontent.DrawLatex(0.20, 0.83,
                        "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  infocontent.DrawLatex(0.60, 0.83,
                        "Pb#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");

  TLatex infoy;
  infoy.SetNDC();
  infoy.SetTextFont(43);
  infoy.SetTextSize(25);
  infoy.DrawLatex(0.2, 0.06, "#font[122]{-}0.96 < #it{y} < 0.04");
  infoy.DrawLatex(0.51, 0.06, "|#it{y}| < 0.5");
  infoy.DrawLatex(0.78, 0.06, "|#it{y}| < 0.5");
  //  info.DrawLatex(0.20, 0.78, "Non-prompt D^{0}");

  //  gJPsiSystematics->Draw("same2");
  //  npJPsiRpPb->Draw("e0 same");
  //  gBplusSystematics->Draw("same2");
  //  BplusRpPb->Draw("e0 same");
  //  gNorSystematics->Draw("same2");
  gPtIntD0RpPbSystematics->Draw("same2");
  gPtIntD0RpPbSystematicsExtr->Draw("same2");
  hPtIntD0RpPb->Draw("e0 same");
  gPtIntD0RPbPbSystematics3050->Draw("same2");
  hPtIntD0PbPb3050->Draw("e0 same");
  gPtIntD0RPbPbSystematics010->Draw("same2");
  gPtIntD0RPbPbSystematicsExtr010np->Draw("same2");
  hPtIntD0PbPb010->Draw("e0 same");
  gPtIntD0RpPbSystematicsPrompt->Draw("same2");
  hPtIntD0pPbPrompt->Draw("e0 same");
  gPtIntD0RPbPbSystematics3050np->Draw("same2");
  gPtIntD0RPbPbSystematicsExtr3050np->Draw("same2");
  hPtIntD0PbPb3050np->Draw("e0 same");
  gPtIntD0RPbPbSystematics010np->Draw("same2");
  hPtIntD0PbPb010np->Draw("e0 same");

  //  gPtIntD0RpPbSystematicsLHCb->Draw("same2");
  //  hPtIntD0RpPbLHCb->Draw("e0 same");

  TLegend *legpPb = new TLegend(0.19, 0.58, 0.35, 0.82);
  legpPb->SetFillColor(0);
  legpPb->SetFillStyle(0);
  legpPb->SetBorderSize(0);
  legpPb->SetMargin(0.46);
  legpPb->SetTextSize(20);
  legpPb->SetTextFont(43);
  legpPb->SetNColumns(1);
  //  leg->AddEntry(hPtIntD0RpPbLHCb, "2-24 GeV/#it{c}", "pl");
  legpPb->AddEntry(hPtIntD0pPbPrompt, "Prompt D^{0}", "pl");
  legpPb->AddEntry(hPtIntD0RpPb, "Non-prompt D^{0}", "pl");
  legpPb->AddEntry(gPtIntD0RpPbSystematicsExtr, "extr. unc.", "F");

  //  legpPb->AddEntry(hPtIntD0PbPb3050np, "Non-prompt D^{0} in Pb-Pb", "pl");
  //  legpPb->AddEntry(hPtIntD0PbPb3050, "Prompt D^{0} in Pb-Pb", "pl");
  legpPb->Draw();

  TLegend *legPbPb = new TLegend(0.6, 0.58, 0.75, 0.82);
  legPbPb->SetFillColor(0);
  legPbPb->SetFillStyle(0);
  legPbPb->SetBorderSize(0);
  legPbPb->SetMargin(0.46);
  legPbPb->SetTextSize(20);
  legPbPb->SetTextFont(43);
  legPbPb->SetNColumns(1);
  //  leg->AddEntry(hPtIntD0RpPbLHCb, "2-24 GeV/#it{c}", "pl");
  //  legPbPb->AddEntry(hPtIntD0RpPb, "Non-prompt D^{0} in p-Pb", "pl");
  //  legPbPb->AddEntry(gPtIntD0RpPbSystematicsExtr, "extr. unc. for non-prompt
  //  D^{0} in p-Pb"); legPbPb->AddEntry(hPtIntD0pPbPrompt, "Prompt D^{0} in
  //  p-Pb", "pl");
  legPbPb->AddEntry(hPtIntD0PbPb3050, "Prompt D^{0}", "pl");
  legPbPb->AddEntry(hPtIntD0PbPb3050np, "Non-prompt D^{0}", "pl");
  legPbPb->AddEntry(gPtIntD0RPbPbSystematicsExtr010np, "extr. unc.", "F");

  legPbPb->Draw();

  TLatex inforef;
  inforef.SetNDC();
  inforef.SetTextFont(43);
  inforef.SetTextSize(19);
  inforef.DrawLatex(0.26, 0.74, "JHEP 12 (2019) 92");
  inforef.DrawLatex(0.67, 0.66, "JHEP 12 (2022) 126");
  inforef.DrawLatex(0.67, 0.74, "JHEP 01 (2022) 174");

  //  TLatex infoLHCb;
  //  infoLHCb.SetNDC();
  //  infoLHCb.SetTextFont(43);
  //  infoLHCb.SetTextSize(25);
  //  infoLHCb.DrawLatex(0.59, 0.9, "LHCb");
  //  infoLHCb.DrawLatex(0.59, 0.85, "#it{p} Pb/Pb#it{p}, #sqrt{#it{s}_{NN}}
  //  = 8.16 TeV"); infoLHCb.DrawLatex(0.59, 0.8, "2 < #it{p}_{T} < 20
  //  GeV/#it{c}");

  //  TLegend* legLHCb = new TLegend(0.63, 0.65, 0.81, 0.77);
  //  legLHCb->SetFillColor(0);
  //  legLHCb->SetFillStyle(0);
  //  legLHCb->SetBorderSize(0);
  //  legLHCb->SetMargin(0.46);
  //  legLHCb->SetTextSize(25);
  //  legLHCb->SetTextFont(43);
  //  legLHCb->SetNColumns(1);
  //  legLHCb->AddEntry(BplusRpPb, "B^{+}");
  //  legLHCb->AddEntry(npJPsiRpPb, "Non-prompt #it{J} / #Psi");
  ////  legLHCb->AddEntry(gRpPbCMSSystematicsFONLL, "Syst. FONLL pp ref.");
  ////  legLHCb->AddEntry(gNorSystematicsCMS, "Syst. int. lumi");
  //  legLHCb->Draw();

  //  TLine* unit = new TLine(0, 1, 3, 1);
  //  unit->SetLineStyle(3);
  //  unit->Draw();

  //  for(int i = 0; i < 11; i++){
  ////    cout << "rel stat unc pp :" <<
  ///hCroSecpp->GetBinError(i+1)/hCroSecpp->GetBinContent(i+1) << endl;
  //    cout << "rel stat unc pp :" <<  hCroSecpp->GetBinError(i+1) << endl;
  //    cout << "content pp :" <<  hCroSecpp->GetBinContent(i+1) << endl;
  ////    cout << "rel stat unc pPb :" <<
  ///hCroSecpPb->GetBinError(i+1)/hCroSecpPb->GetBinContent(i+1) << endl;
  //    cout << "rel stat unc pPb :" << hCroSecpPb->GetBinError(i+1) << endl;
  //    cout << "content pPb :" << hCroSecpPb->GetBinContent(i+1) << endl;
  ////    cout << "rel stat unc RpPb :" <<
  ///RpPbFDD0->GetBinError(i+1)/RpPbFDD0->GetBinContent(i+1) << endl;
  //    cout << "rel stat unc RpPb :" << RpPbFDD0->GetBinError(i+1) << endl;
  //    cout << "content RpPb :" << RpPbFDD0->GetBinContent(i+1) << endl;
  //  }
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
