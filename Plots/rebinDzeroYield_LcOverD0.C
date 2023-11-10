#include <iostream>
using namespace std;

// Double_t ptbin[7] = {2, 3, 4, 5, 6, 8, 12};   // ptbins to be rebinned into
Double_t ptbins[4] = {2, 4, 8, 12};
TH1D *rebinHist(TH1D *h);
Double_t MEAN2(Double_t A, Double_t B);

const Double_t ptlimsmiddlePrompt[8] = {1.5, 2.5, 3.5, 4.5, 5.5, 7., 10., 18.};
Double_t yvaluncPrompt[8] = {0., 0., 0., 0., 0., 0., 0., 0.};
const Double_t ptlimsmiddlePrompt01[1] = {0.5};
Double_t yvaluncPrompt01[1] = {0.};
const Double_t ptlimsmiddleFD[3] = {3., 6., 10.};
Double_t yvaluncFD[3] = {0., 0., 0.};

void SetStyleHisto(TH1D *h);
void SetStyleHisto(TH1F *h);

void rebinDzeroYield_LcOverD0() {
  TFile *promptLcFile =
      new TFile("./PromptLc_HEPData-ins1829739-v1-root.root", "read");
  TDirectoryFile *promptdir = (TDirectoryFile *)promptLcFile->Get("Table 5");
  TH1F *promptLc = (TH1F *)promptdir->Get("Hist1D_y1");
  TH1F *promptLcStat = (TH1F *)promptdir->Get("Hist1D_y1_e1");
  TH1F *promptLcSystPlus = (TH1F *)promptdir->Get("Hist1D_y1_e2plus");
  TH1F *promptLcMinus = (TH1F *)promptdir->Get("Hist1D_y1_e2minus");

  int nPtBinsPrompt = promptLc->GetNbinsX();
  for (int iPt = 0; iPt < nPtBinsPrompt; iPt++) {
    promptLc->SetBinError(iPt + 1, promptLcStat->GetBinContent(iPt + 1));
  }

  Float_t ptlimsLc01[2] = {0., 1.};
  TH1D *PromptLc01 = new TH1D("PromptLc01", "PromptLc01", 1, ptlimsLc01);
  PromptLc01->SetBinContent(1, 0.34317705);
  PromptLc01->SetBinError(1, 0.09);

  TGraphAsymmErrors *gPromptLcSystematics01 =
      new TGraphAsymmErrors(1, ptlimsmiddlePrompt01, yvaluncPrompt01);
  for (Int_t i = 0; i < 1; i++) {
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
  Float_t ptlimsExtral[nptlimsExtra + 1] = {0., 1., 2.,  3.,  4., 5.,
                                            6., 8., 12., 24., 26.};

  TH1D *hrefPrompt =
      new TH1D("hrefPrompt", "hrefPrompt", nptlimsExtra, ptlimsExtral);
  hrefPrompt->SetTitle("");
  hrefPrompt->GetYaxis()->SetTitle("#Lambda_{c}^{+}/D^{0}");
  hrefPrompt->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  hrefPrompt->SetMinimum(0.01);
  hrefPrompt->SetMaximum(1.5);
  SetStyleHisto(hrefPrompt);
  hrefPrompt->SetLineWidth(1);
  hrefPrompt->GetYaxis()->SetTitleOffset(1.3);

  //  Double_t errxlowPrompt[8] = {};
  //  Double_t errxhighPrompt[8] = {};
  TGraphAsymmErrors *gPromptLcSystematics =
      new TGraphAsymmErrors(8, ptlimsmiddlePrompt, yvaluncPrompt);
  for (Int_t i = 0; i < 8; i++) {
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

  TFile *inputFileLc = new TFile("./CrossSectionLc2pK0s.root", "read");
  TH1D *hCroSecLc = (TH1D *)inputFileLc->Get("hCrossSection");
  //  TH1D* hCroSecLcClone = (TH1D*)hCroSecLc->Clone("hCroSecLcClone");

  Double_t SystRawYield[3] = {0.1, 0.09, 0.09};
  Double_t SystBDTSelection[3] = {0.07, 0.07, 0.07};
  Double_t SystTrackingWOBudget[3] = {0.05, 0.05, 0.05};
  Double_t SystMaterialBudget[3] = {0.02, 0.02, 0.02};
  Double_t SystpTWeights[3] = {0.1, 0.1, 0.1};
  Double_t SystFeedDown[3] = {0.1, 0.1, 0.1};
  Double_t SystBR[3] = {0.05, 0.05, 0.05};
  Double_t SystNor[3] = {0.037, 0.037, 0.037};

  //  Double_t SystTotal[3] = {0.};
  Double_t SystLcCorrAbs[3] = {0.};
  Double_t SystLcUnCorrAbs[3] = {0.};
  for (Int_t i = 0; i < 3; i++) {
    SystLcCorrAbs[i] =
        TMath::Sqrt(SystTrackingWOBudget[i] * SystTrackingWOBudget[i] +
                    SystMaterialBudget[i] * SystMaterialBudget[i] +
                    SystNor[i] * SystNor[i]);
    SystLcCorrAbs[i] = SystLcCorrAbs[i] * hCroSecLc->GetBinContent(i + 1);
  }

  for (Int_t i = 0; i < 3; i++) {
    SystLcUnCorrAbs[i] =
        TMath::Sqrt(SystRawYield[i] * SystRawYield[i] +
                    SystBDTSelection[i] * SystBDTSelection[i] +
                    SystpTWeights[i] * SystpTWeights[i] +
                    SystFeedDown[i] * SystFeedDown[i] + SystBR[i] * SystBR[i]);
    SystLcUnCorrAbs[i] = SystLcUnCorrAbs[i] * hCroSecLc->GetBinContent(i + 1);
  }

  TFile *inputFileD0 = new TFile("./CrossSectionSystematics.root", "read");
  TH1D *hCroSecD0 = (TH1D *)inputFileD0->Get("hCrossSection");
  //  TH1D* hCroSecD0Clone = (TH1D*)hCroSecD0->Clone("hCroSecD0Clone");
  hCroSecD0->Scale(1. / 0.0395);

  Double_t raw[11] = {0.03, 0.02, 0.01, 0.01, 0.01, 0.01,
                      0.01, 0.01, 0.02, 0.02, 0.03};
  Double_t sel[11] = {0.05, 0.03, 0.03, 0.03, 0.03, 0.03,
                      0.03, 0.04, 0.04, 0.04, 0.04};
  Double_t fr[11] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
                     0.01, 0.01, 0.01, 0.01, 0.02};
  Double_t gen[11] = {0.07, 0.05, 0.03, 0.02, 0.01, 0., 0., 0., 0., 0., 0.02};
  Double_t tra[11] = {0.02, 0.02, 0.02,  0.02, 0.02, 0.02,
                      0.02, 0.02, 0.025, 0.03, 0.03};
  Double_t br[11] = {0.0003, 0.0003, 0.0003, 0.0003, 0.0003, 0.0003,
                     0.0003, 0.0003, 0.0003, 0.0003, 0.0003};
  Double_t nor[11] = {0.037, 0.037, 0.037, 0.037, 0.037, 0.037,
                      0.037, 0.037, 0.037, 0.037, 0.037};

  Double_t SystD0CorrAbs[11];
  Double_t SystD0UnCorrAbs[11];
  for (Int_t i = 0; i < 11; i++) {
    SystD0CorrAbs[i] =
        TMath::Sqrt(tra[i] * tra[i] + nor[i] * nor[i] + sel[i] * sel[i] +
                    fr[i] * fr[i] + gen[i] * gen[i] + br[i] * br[i]);
    SystD0CorrAbs[i] = SystD0CorrAbs[i] * hCroSecD0->GetBinContent(i + 1);
  }

  for (Int_t i = 0; i < 11; i++) {
    SystD0UnCorrAbs[i] = TMath::Sqrt(raw[i] * raw[i]);
    SystD0UnCorrAbs[i] = SystD0UnCorrAbs[i] * hCroSecD0->GetBinContent(i + 1);
  }

  TH1D *hCroSecD0Rebin = rebinHist(hCroSecD0);

  Double_t SystD0CorrRebinAbs[3];
  Double_t SystD0UnCorrRebinAbs[3];

  SystD0UnCorrRebinAbs[0] =
      TMath::Sqrt(SystD0UnCorrAbs[1] * SystD0UnCorrAbs[1] * 1 * 1 / 2 / 2);
  SystD0UnCorrRebinAbs[0] =
      TMath::Sqrt(SystD0UnCorrRebinAbs[0] * SystD0UnCorrRebinAbs[0] +
                  SystD0UnCorrAbs[2] * SystD0UnCorrAbs[2] * 1 * 1 / 2 / 2);

  SystD0UnCorrRebinAbs[1] =
      TMath::Sqrt(SystD0UnCorrAbs[3] * SystD0UnCorrAbs[3] * 1 * 1 / 4 / 4);
  SystD0UnCorrRebinAbs[1] =
      TMath::Sqrt(SystD0UnCorrRebinAbs[1] * SystD0UnCorrRebinAbs[1] +
                  SystD0UnCorrAbs[4] * SystD0UnCorrAbs[4] * 1 * 1 / 4 / 4);
  SystD0UnCorrRebinAbs[1] =
      TMath::Sqrt(SystD0UnCorrRebinAbs[1] * SystD0UnCorrRebinAbs[1] +
                  SystD0UnCorrAbs[5] * SystD0UnCorrAbs[5] * 1 * 1 / 4 / 4);
  SystD0UnCorrRebinAbs[1] =
      TMath::Sqrt(SystD0UnCorrRebinAbs[1] * SystD0UnCorrRebinAbs[1] +
                  SystD0UnCorrAbs[6] * SystD0UnCorrAbs[6] * 1 * 1 / 4 / 4);

  SystD0UnCorrRebinAbs[2] =
      TMath::Sqrt(SystD0UnCorrAbs[7] * SystD0UnCorrAbs[7] * 2 * 2 / 4 / 4);
  SystD0UnCorrRebinAbs[2] =
      TMath::Sqrt(SystD0UnCorrRebinAbs[2] * SystD0UnCorrRebinAbs[2] +
                  SystD0UnCorrAbs[8] * SystD0UnCorrAbs[8] * 2 * 2 / 4 / 4);

  SystD0CorrRebinAbs[0] = SystD0UnCorrAbs[1] * 1 / 2;
  SystD0CorrRebinAbs[0] = SystD0CorrRebinAbs[0] + SystD0CorrAbs[2] * 1 / 2;

  SystD0CorrRebinAbs[1] = SystD0UnCorrAbs[3] * 1 / 4;
  SystD0CorrRebinAbs[1] = SystD0CorrRebinAbs[1] + SystD0CorrAbs[4] * 1 / 4;
  SystD0CorrRebinAbs[1] = SystD0CorrRebinAbs[1] + SystD0CorrAbs[5] * 1 / 4;
  SystD0CorrRebinAbs[1] = SystD0CorrRebinAbs[1] + SystD0CorrAbs[6] * 1 / 4;

  SystD0CorrRebinAbs[2] = SystD0UnCorrAbs[7] * 2 / 4;
  SystD0CorrRebinAbs[2] = SystD0CorrRebinAbs[2] + SystD0CorrAbs[8] * 2 / 4;

  TH1D *hLcOverD0 = (TH1D *)hCroSecLc->Clone("hLcOverD0");
  hLcOverD0->Divide(hCroSecD0Rebin);

  Double_t SystLcOverCorrAbs[3];
  Double_t SystLcOverD0UnCorrAbs[3];
  Double_t SystLcOverD0TotalAbs[3];

  SystLcOverCorrAbs[0] = SystD0CorrRebinAbs[0] + SystLcCorrAbs[0];
  SystLcOverCorrAbs[0] =
      SystLcOverCorrAbs[0] / hCroSecD0Rebin->GetBinContent(1);

  SystLcOverCorrAbs[1] = SystD0CorrRebinAbs[1] + SystLcCorrAbs[1];
  SystLcOverCorrAbs[1] =
      SystLcOverCorrAbs[1] / hCroSecD0Rebin->GetBinContent(2);

  SystLcOverCorrAbs[2] = SystD0CorrRebinAbs[2] + SystLcCorrAbs[2];
  SystLcOverCorrAbs[2] =
      SystLcOverCorrAbs[2] / hCroSecD0Rebin->GetBinContent(3);

  SystLcOverD0UnCorrAbs[0] =
      TMath::Sqrt(SystD0UnCorrRebinAbs[0] * SystD0UnCorrRebinAbs[0] +
                  SystLcUnCorrAbs[0] * SystLcUnCorrAbs[0]);
  SystLcOverD0UnCorrAbs[0] =
      SystLcOverD0UnCorrAbs[0] / hCroSecD0Rebin->GetBinContent(1);

  SystLcOverD0UnCorrAbs[1] =
      TMath::Sqrt(SystD0UnCorrRebinAbs[1] * SystD0UnCorrRebinAbs[1] +
                  SystLcUnCorrAbs[1] * SystLcUnCorrAbs[1]);
  SystLcOverD0UnCorrAbs[1] =
      SystLcOverD0UnCorrAbs[1] / hCroSecD0Rebin->GetBinContent(2);

  SystLcOverD0UnCorrAbs[2] =
      TMath::Sqrt(SystD0UnCorrRebinAbs[2] * SystD0UnCorrRebinAbs[2] +
                  SystLcUnCorrAbs[2] * SystLcUnCorrAbs[2]);
  SystLcOverD0UnCorrAbs[2] =
      SystLcOverD0UnCorrAbs[2] / hCroSecD0Rebin->GetBinContent(3);

  SystLcOverD0TotalAbs[0] =
      TMath::Sqrt(SystLcOverD0UnCorrAbs[0] * SystLcOverD0UnCorrAbs[0] +
                  SystLcOverCorrAbs[0] * SystLcOverCorrAbs[0]);

  SystLcOverD0TotalAbs[1] =
      TMath::Sqrt(SystLcOverD0UnCorrAbs[1] * SystLcOverD0UnCorrAbs[1] +
                  SystLcOverCorrAbs[1] * SystLcOverCorrAbs[1]);

  SystLcOverD0TotalAbs[2] =
      TMath::Sqrt(SystLcOverD0UnCorrAbs[2] * SystLcOverD0UnCorrAbs[2] +
                  SystLcOverCorrAbs[2] * SystLcOverCorrAbs[2]);
  //
  //	TH1D* hCroSecD0Rebin = rebinHist(hCroSecD0);
  //  hCroSecD0Rebin->SetName("hCroSecD0Rebin");
  //  hCroSecD0Rebin->SetTitle("Cross Section D0 Rebin");
  //
  //  hCroSecLc->SetName("hCroSecLc");
  //  hCroSecLc->SetTitle("Cross Section Lc");
  //  hCroSecLc->GetYaxis()->SetTitle("#Lambda_{c}^{+}/D^{0}");
  //
  //  hCroSecD0Rebin->Scale(1. / 0.0395);
  //  hCroSecLc->Divide(hCroSecD0Rebin);
  //  hCroSecD0Clone->Scale(1. / 0.0395);
  ////  hCroSecD0Rebin->Draw();
  ////  hCroSecLc->Draw();
  //
  //  Double_t raw[11] = {0.03, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02,
  //  0.02, 0.03}; Double_t sel[11] = {0.05, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03,
  //  0.04, 0.04, 0.04, 0.04}; Double_t fr[11]  = {0.01, 0.01, 0.01, 0.01, 0.01,
  //  0.01, 0.01, 0.01, 0.01, 0.01, 0.02}; Double_t gen[11] = {0.07, 0.05, 0.03,
  //  0.02, 0.01, 0., 0., 0., 0., 0., 0.02}; Double_t tra[11] = {0.02, 0.02,
  //  0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.025, 0.03, 0.03}; Double_t br[11] =
  //  {0.0003, 0.0003, 0.0003, 0.0003, 0.0003, 0.0003, 0.0003, 0.0003, 0.0003,
  //  0.0003, 0.0003}; Double_t nor[11] = {0.037, 0.037, 0.037, 0.037, 0.037,
  //  0.037, 0.037, 0.037, 0.037, 0.037, 0.037};
  //
  //  Double_t SystpPbAll[11];
  //  Double_t SystpPbUnCorr[11];
  //  Double_t SystpPbCorr[11];
  //
  ////  SystpPbUnCorr[0] =
  ////  SystpPbUnCorr[1] =
  ////  SystpPbUnCorr[2] =
  //
  ////  for(Int_t ibin = 0;ibin < 11; ibin++) {
  ////    Double_t SystpPbUnCorrRel = TMath::Sqrt(raw[ibin]*raw[ibin]+
  ///sel[ibin]*sel[ibin] +fr[ibin]*fr[ibin] +gen[ibin]*gen[ibin] +
  ///br[ibin]*br[ibin]); /    SystpPbUnCorr[0] += SystpPbUnCorrRel *
  ///hCroSecD0->GetBinContent(ibin+1); /    SystpPbUnCorr[0] = TMath::Sqrt(); /
  ///}
  //  for(Int_t ibin = 0;ibin < 11; ibin++) {
  //    SystpPbUnCorr[ibin] = TMath::Sqrt(raw[ibin]*raw[ibin]+
  //    sel[ibin]*sel[ibin] +fr[ibin]*fr[ibin] +gen[ibin]*gen[ibin] +
  //    br[ibin]*br[ibin]); SystpPbUnCorr[ibin] = SystpPbUnCorr[ibin] *
  //    hCroSecD0->GetBinContent(ibin+1);
  //  }
  //
  //  for(Int_t ibin = 0;ibin < 11; ibin++) {
  //    SystpPbCorr[ibin] = tra[ibin] * hCroSecD0->GetBinContent(ibin+1);
  //  }
  //
  //  // calculate rebinned syst
  //  Double_t SystpPbUnCorrRebin[3] = {0., 0., 0.};
  //  Double_t SystpPbCorrRebin[3] = {0., 0., 0.};
  //  Double_t SystpPbAllRebin[3] = {0., 0., 0.};
  //
  //  for(Int_t i = 1; i < 2; i++) {
  //    SystpPbUnCorrRebin[0] = TMath::Sqrt(SystpPbUnCorrRebin[0] *
  //    SystpPbUnCorrRebin[0] + SystpPbUnCorr[i] * SystpPbUnCorr[i] * 1. * 1.
  //    / 2. / 2.);
  //  }
  //
  //  for(Int_t i = 3; i < 6; i++) {
  //    SystpPbUnCorrRebin[1] = TMath::Sqrt(SystpPbUnCorrRebin[1] *
  //    SystpPbUnCorrRebin[1] + SystpPbUnCorr[i] * SystpPbUnCorr[i] * 1. * 1.
  //    / 4. / 4.);
  //  }
  //
  //  for(Int_t i = 7; i < 8; i++) {
  //    SystpPbUnCorrRebin[2] = TMath::Sqrt(SystpPbUnCorrRebin[2] *
  //    SystpPbUnCorrRebin[2] + SystpPbUnCorr[i] * SystpPbUnCorr[i] * 2. * 2.
  //    / 4. / 4.);
  //  }
  //
  //  for(Int_t i = 1; i < 2; i++) {
  //    SystpPbCorrRebin[0] = SystpPbUnCorrRebin[0] + SystpPbCorr[i] * 1. / 2.;
  //  }
  //
  //  for(Int_t i = 3; i < 6; i++) {
  //    SystpPbCorrRebin[1] = SystpPbUnCorrRebin[1] + SystpPbCorr[i] * 1. / 4.;
  //  }
  //
  //  for(Int_t i = 7; i < 8; i++) {
  //    SystpPbCorrRebin[2] = SystpPbUnCorrRebin[2] + SystpPbCorr[i] * 2. / 4.;
  //  }
  //
  //  for(Int_t i = 0; i < 2; i++) {
  //    SystpPbAllRebin[i] = TMath::Sqrt(SystpPbUnCorrRebin[i] *
  //    SystpPbUnCorrRebin[i] + SystpPbCorr[i] * SystpPbCorr[i]);
  //  }
  //
  //  TH1D* hCroSecD0CloneRebin = rebinHist(hCroSecD0Clone);  // for syst unc
  //  calculation (abs) for(Int_t i = 0; i < 3; i++) {
  //    hCroSecD0CloneRebin->SetBinError(i+1, SystpPbAllRebin[i]);
  //  }
  ////  hCroSecD0CloneRebin->Scale(1. / 0.0395);
  //
  //  Double_t SystpPbUnCorrRebinRel[3] = {0., 0., 0.};
  //  Double_t SystpPbCorrRebinRel[3] = {0., 0., 0.};
  //  for(Int_t i = 0; i < 3; i++) {
  //    SystpPbUnCorrRebinRel[i] = SystpPbUnCorrRebin[i] *
  //    hCroSecD0CloneRebin->GetBinContent(i+1); SystpPbCorrRebinRel[i] =
  //    SystpPbCorrRebin[i] * hCroSecD0CloneRebin->GetBinContent(i+1);
  //  }
  //
  //
  //
  //  Double_t LcOverDzeroSystUncorr[3];
  //  for(Int_t i = 0; i < 3; i++) {
  //    LcOverDzeroSystUncorr[i] = TMath::Sqrt(SystUncorr[i] * SystUncorr[i] +
  //    SystpPbUnCorrRebinRel[i] * SystpPbUnCorrRebinRel[i]);
  //    LcOverDzeroSystUncorr[i] = LcOverDzeroSystUncorr[i] *
  //    hCroSecLc->GetBinContent(i+1);
  //  }
  //
  //  Double_t LcOverDzeroSystCorr[3];
  //  for(Int_t i = 0; i < 3; i++) {
  //    LcOverDzeroSystCorr[i] = (SystTracking[i] + SystpPbCorrRebin[i]) /
  //    hCroSecD0Clone->GetBinContent(i+1); LcOverDzeroSystCorr[i] =
  //    LcOverDzeroSystCorr[i] / hCroSecLc->GetBinContent(i+1);
  //  }
  //
  //  Double_t LcOverDzeroSystAll[3];
  //  for(Int_t i = 0; i < 3; i++) {
  //    LcOverDzeroSystAll[i] = TMath::Sqrt(LcOverDzeroSystUncorr[i] *
  //    LcOverDzeroSystUncorr[i] + LcOverDzeroSystCorr[i] *
  //    LcOverDzeroSystCorr[i]); LcOverDzeroSystAll[i] = LcOverDzeroSystAll[i] *
  //    hCroSecLc->GetBinContent(i+1);
  //  }
  //
  //
  TGraphAsymmErrors *gFDSystematics =
      new TGraphAsymmErrors(3, ptlimsmiddleFD, yvaluncFD);
  for (Int_t i = 0; i < 3; i++) {
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

  const Int_t nptlims = 3;
  Float_t ptlims[nptlims + 1] = {2., 4., 8., 12.};

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
  hrefPrompt->Draw("");
  hrefFD->Draw("same");

  SetStyleHisto(promptLc);
  promptLc->SetStats(0);
  promptLc->SetLineColor(kRed + 1);
  promptLc->SetMarkerColor(kRed + 1);
  promptLc->SetMarkerStyle(21);

  SetStyleHisto(hLcOverD0);
  hLcOverD0->SetStats(0);
  hLcOverD0->SetLineColor(kAzure + 2);
  hLcOverD0->SetMarkerColor(kAzure + 2);
  hLcOverD0->SetMarkerStyle(20);

  SetStyleHisto(PromptLc01);
  PromptLc01->SetStats(0);
  PromptLc01->SetLineColor(kRed + 1);
  PromptLc01->SetMarkerColor(kRed + 1);
  PromptLc01->SetMarkerStyle(21);

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
  infos.DrawLatex(0.7, 0.89, "#font[122]{-}0.96 < #it{y} < 0.04");

  TLatex inforef;
  inforef.SetNDC();
  inforef.SetTextFont(43);
  inforef.SetTextSize(23);
  inforef.DrawLatex(0.62, 0.59, "PRL 127 (2021) 202301");
  inforef.DrawLatex(0.62, 0.555, "arXiv:2211.14032");

  gPromptLcSystematics->Draw("same2");
  promptLc->Draw("e0 same");
  gPromptLcSystematics01->Draw("same2");
  PromptLc01->Draw("e0 same");
  gFDSystematics->Draw("same2");
  hLcOverD0->Draw("e0 same");
  //  gNorSystematics->Draw("same2");

  TLegend *leg = new TLegend(0.51, 0.6, 0.75, 0.75);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetMargin(0.46);
  leg->SetTextSize(25);
  leg->SetTextFont(43);
  leg->AddEntry(hLcOverD0, "Non-prompt #Lambda_{c}^{+}/D^{0}", "pl");
  leg->AddEntry(promptLc, "Prompt #Lambda_{c}^{+}/D^{0}", "pl");
  leg->Draw();
}

TH1D *rebinHist(TH1D *h) {
  TH1D *h_rebin = new TH1D("h_rebin", "h_rebin", 3, ptbins);
  for (Int_t i = 1; i <= h_rebin->GetNbinsX(); i++) {
    Double_t binw = h_rebin->GetBinWidth(i);
    for (Int_t j = 1; j <= h->GetNbinsX(); j++) {
      Double_t binw0 = h->GetBinWidth(j);
      if (h->GetBinCenter(j) > h_rebin->GetBinLowEdge(i) &&
          h->GetBinCenter(j) <= h_rebin->GetBinLowEdge(i + 1)) {
        Double_t binc = h_rebin->GetBinContent(i);
        Double_t binc0 = h->GetBinContent(j);
        Double_t bine = h_rebin->GetBinError(i);
        Double_t bine0 = h->GetBinError(j);
        //				h_rebin->SetBinContent(i, binc + binw0 / binw
        //* binc0);
        h_rebin->SetBinContent(i, binc + binc0 * binw0 / binw);
        h_rebin->SetBinError(
            i, TMath::Sqrt(bine * bine +
                           bine0 * bine0 * binw0 * binw0 / binw / binw));
      }
    }
  }
  h_rebin->SetLineColor(h->GetLineColor());
  h_rebin->SetLineWidth(h->GetLineWidth());
  h_rebin->SetMarkerStyle(h->GetMarkerStyle());
  h_rebin->SetMarkerColor(h->GetMarkerColor());
  return h_rebin;
}

Double_t MEAN2(Double_t A, Double_t B) { return TMath::Sqrt(A * A + B * B); }

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
