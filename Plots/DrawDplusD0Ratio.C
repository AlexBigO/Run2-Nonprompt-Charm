#include <iostream>

using namespace std;

void SetStyle();
void SetStyleHisto(TH1D *h);
void SetStyleHisto(TH1F *h);

enum Particles: uint8_t {
  kD0 = 0,
  kDplus,
  kLambdac
};

const uint8_t particle = Particles::kDplus;


// For D0
// uint8_t nPtBinsPrompts = 21;
// const Double_t ptlimsmiddlePrompt[21] = {
//     0.5,  1.25, 1.75, 2.25, 2.75, 3.25, 3.75, 4.25, 4.75, 5.25, 5.75,
//     6.25, 6.75, 7.25, 7.75, 8.5,  9.5,  11.,  14.,  20.,  30.};
// Double_t yvaluncPrompt[21] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
//                               0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
// const Double_t ptlimsmiddleFD[11] = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5,
//                                      7.5, 9,   11,  14,  20};
// Double_t yvaluncFD[11] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};

// For D+
uint8_t nPtBinsPrompts = 20;
const Double_t ptlimsmiddlePrompt[20] = {
    1.25, 1.75, 2.25, 2.75, 3.25, 3.75, 4.25, 4.75, 5.25, 5.75,
    6.25, 6.75, 7.25, 7.75, 8.5,  9.5,  11.,  14.,  20.,  30.};
Double_t yvaluncPrompt[20] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
                              0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
const Double_t ptlimsmiddleFD[10] = {2.5, 3.5, 4.5, 5.5, 6.5,
                                     7.5, 9,   11,  14,  20};
Double_t yvaluncFD[10] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};

const Double_t ptlimsmiddleRpPb[1] = {37.};
Double_t yvaluncRpPb[1] = {1.};

void DrawDplusD0Ratio() {

  // prompt D0 RpPb
  TGaxis::SetMaxDigits(3);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  TFile* promptFileHEP = nullptr;
  TDirectoryFile *promptdir = nullptr;

  if (particle == kD0) {
    promptFileHEP = new TFile("./HEPData-ins1738950-v1-root.root", "read");
    promptdir = (TDirectoryFile *)promptFileHEP->Get("RpPb D0, Figure 8");
  } else if (particle == kDplus) {
    promptFileHEP = new TFile("/home/abigot/AnalysisNonPromptDplus/HEPData-ins1738950-v1-D+_D0,_Figure_13.root", "read");
    promptdir = (TDirectoryFile *)promptFileHEP->Get("D+-D0, Figure 13");
  }

  TH1F *promptRpPb = (TH1F *)promptdir->Get("Hist1D_y1");
  TH1F *promptRpPbStat = (TH1F *)promptdir->Get("Hist1D_y1_e1");
  TH1F *promptRpPbSystPlus = (TH1F *)promptdir->Get("Hist1D_y1_e2plus");
  TH1F *promptRpPbSystMinus = (TH1F *)promptdir->Get("Hist1D_y1_e2minus");
  TH1F *promptRpPbSystNor = (TH1F *)promptdir->Get("Hist1D_y1_e3");

  int nPtBinsPrompt = promptRpPb->GetNbinsX();
  for (int iPt = 0; iPt < nPtBinsPrompt; iPt++) {
    promptRpPb->SetBinError(iPt + 1, promptRpPbStat->GetBinContent(iPt + 1));
  }
  // promptRpPb->GetXaxis()->SetRangeUser(0, 36);

  // D0
  // Double_t errxlowPrompt[21] = {0.4, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2,
  //                               0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2,
  //                               0.2, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4};
  // Double_t errxhighPrompt[21] = {0.4, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2,
  //                                0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2,
  //                                0.2, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4};

  // Dplus
  Double_t errxlowPrompt[20] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                           0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                           0.25, 0.25, 0.25, 0.25, 0.25, 0.25};
  Double_t errxhighPrompt[20] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                           0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                           0.25, 0.25, 0.25, 0.25, 0.25, 0.25};

  // D0
  // TGraphAsymmErrors *gRpPbPromptD0Systematics =
  //     new TGraphAsymmErrors(21, ptlimsmiddlePrompt, yvaluncPrompt);
  // for (Int_t i = 0; i < 21; i++) {

  TGraphAsymmErrors *gRpPbPromptD0Systematics =
      new TGraphAsymmErrors(20, ptlimsmiddlePrompt, yvaluncPrompt);
  for (Int_t i = 0; i < 20; i++) {
    Double_t RpPbPrompt = promptRpPb->GetBinContent(i + 1);
    Double_t ptx = ptlimsmiddlePrompt[i];
    Double_t errylow = -1. * promptRpPbSystMinus->GetBinContent(i + 1);
    Double_t erryhigh = promptRpPbSystPlus->GetBinContent(i + 1);
    Double_t errxlow = 0.25;
    Double_t errxhigh = 0.25;
    gRpPbPromptD0Systematics->SetPoint(i, ptlimsmiddlePrompt[i], RpPbPrompt);
    gRpPbPromptD0Systematics->SetPointError(
        i, errxlow, errxhigh, errylow, erryhigh);
  }

  gRpPbPromptD0Systematics->SetFillStyle(0);
  gRpPbPromptD0Systematics->SetFillColor(kWhite);
  gRpPbPromptD0Systematics->SetLineWidth(2);
  gRpPbPromptD0Systematics->SetLineColor(kRed - 7);

  const Int_t nptlimsExtra = 22;
  // const Int_t nptlimsExtra = 21;
  Float_t ptlimsExtral[nptlimsExtra + 1] = {
      0.,  1., 1.5, 2., 2.5, 3.,  3.5, 4.,  4.5, 5.,  5.5, 6.,
      6.5, 7., 7.5, 8., 9.,  10., 12., 16., 24., 36., 38.};

  // Float_t ptlimsExtral[nptlimsExtra + 1] = {
  //     1., 1.5, 2., 2.5, 3.,  3.5, 4.,  4.5, 5.,  5.5, 6.,
  //     6.5, 7., 7.5, 8., 9.,  10., 12., 16., 24., 36., 38.};

  TH1D *hrefPrompt =
      new TH1D("hrefPrompt", "hrefPrompt", nptlimsExtra, ptlimsExtral);
  hrefPrompt->SetTitle("");
  hrefPrompt->GetYaxis()->SetTitle("D^{+}/D^{0}");
  hrefPrompt->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  hrefPrompt->SetMinimum(0.105);
  hrefPrompt->SetMaximum(1.07);
  SetStyleHisto(hrefPrompt);
  hrefPrompt->SetLineWidth(1);
  // hrefPrompt->GetXaxis()->SetLimits(0, 35);
  // hrefPrompt->GetXaxis()->SetRangeUser(0, 36);
  hrefPrompt->GetYaxis()->SetTitleOffset(1.3);

  // non-prompt D0 RpPb

  

  // TFile *pPbFile = new TFile("./CrossSection_D0_pPb5TeV_FD.root", "read");
  // TH1F *hCroSecpPb = (TH1F *)pPbFile->Get("hCrossSection");
  // //  TH1D* hCroSecpPbclone = (TH1D*)hCroSecpPb->Clone("hCroSecpPbclone");

  // TFile *ppFile = new TFile("./HEPData-ins1848990-v1-root.root", "read");
  // TDirectoryFile *dir = (TDirectoryFile *)ppFile->Get("Table 1");
  // TH1F *hCroSecpp = (TH1F *)dir->Get("Hist1D_y1");
  // TH1F *hCroSecppStat = (TH1F *)dir->Get("Hist1D_y1_e1");
  // TH1F *hCroSecppSyst = (TH1F *)dir->Get("Hist1D_y1_e2");
  // TH1F *hCroSecppSystBR = (TH1F *)dir->Get("Hist1D_y1_e3");
  // TH1F *hCroSecppSystLumi = (TH1F *)dir->Get("Hist1D_y1_e4");

  // TFile *corrFile = new TFile("./corrfactorFONLL_update_syst.root", "read");
  // TH1F *factor = (TH1F *)corrFile->Get("hRatioDfromBOverBCentral");

  // int nPtBinsFD = hCroSecpp->GetNbinsX();

  // for (int iPt = 0; iPt < nPtBinsFD; iPt++) {
  //   hCroSecpp->SetBinError(iPt + 1, hCroSecppStat->GetBinContent(iPt + 1));
  // }

  // //  hCroSecpp->Draw();

  // Double_t SystppNor[11];
  // for (Int_t ibin = 0; ibin < 11; ibin++) {
  //   SystppNor[ibin] = hCroSecppSystLumi->GetBinContent(ibin + 1) /
  //                     hCroSecpp->GetBinContent(ibin + 1);
  // }

  // Double_t SystppAll[11];
  // for (Int_t ibin = 0; ibin < 11; ibin++) {
  //   SystppAll[ibin] = hCroSecppSyst->GetBinContent(ibin + 1) /
  //                     hCroSecpp->GetBinContent(ibin + 1);
  // }

  // Double_t raw[11] = {0.03, 0.02, 0.01, 0.01, 0.01, 0.01,
  //                     0.01, 0.01, 0.02, 0.02, 0.03};
  // Double_t sel[11] = {0.05, 0.03, 0.03, 0.03, 0.03, 0.03,
  //                     0.03, 0.04, 0.04, 0.04, 0.04};
  // Double_t fr[11] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
  //                    0.01, 0.01, 0.01, 0.01, 0.02};
  // Double_t gen[11] = {0.07, 0.05, 0.03, 0.02, 0.01, 0., 0., 0., 0., 0., 0.02};
  // Double_t tra[11] = {0.02, 0.02, 0.02,  0.02, 0.02, 0.02,
  //                     0.02, 0.02, 0.025, 0.03, 0.03};
  // Double_t br[11] = {0.03, 0.03, 0.03, 0.03, 0.03, 0.03,
  //                    0.03, 0.03, 0.03, 0.03, 0.03};
  // Double_t nor[11] = {0.037, 0.037, 0.037, 0.037, 0.037, 0.037,
  //                     0.037, 0.037, 0.037, 0.037, 0.037};

  // Double_t SystpPbAll[11];
  // for (Int_t ibin = 0; ibin < 11; ibin++) {
  //   SystpPbAll[ibin] = TMath::Sqrt(
  //       raw[ibin] * raw[ibin] + sel[ibin] * sel[ibin] + fr[ibin] * fr[ibin] +
  //       gen[ibin] * gen[ibin] + tra[ibin] * tra[ibin]);
  // }

  // Double_t SystRpPbFD[11];
  // for (Int_t ibin = 0; ibin < 11; ibin++) {
  //   SystRpPbFD[ibin] = TMath::Sqrt(SystpPbAll[ibin] * SystpPbAll[ibin] +
  //                                  SystppAll[ibin] * SystppAll[ibin]);
  // }

  // Double_t SystRpPbFDNor[11];
  // for (Int_t ibin = 0; ibin < 11; ibin++) {
  //   SystRpPbFDNor[ibin] =
  //       TMath::Sqrt(nor[ibin] * nor[ibin] + SystppNor[ibin] * SystppNor[ibin]);
  // }

  // hCroSecpPb->Scale(1 / (0.0395 * 208));

  // for (Int_t ibin = 0; ibin < 11; ibin++) {
  //   Double_t binContent = hCroSecpPb->GetBinContent(ibin + 1);
  //   Double_t binError = hCroSecpPb->GetBinError(ibin + 1);
  //   binContent = binContent / factor->GetBinContent(ibin + 1);
  //   binError = binError / factor->GetBinContent(ibin + 1);
  //   hCroSecpPb->SetBinContent(ibin + 1, binContent);
  //   hCroSecpPb->SetBinError(ibin + 1, binError);
  // }
  // //  hCroSecpPb->Draw();
  // //  hCroSecpp->Draw("same");

  // hCroSecpPb->Sumw2();
  // hCroSecpp->Sumw2();
  // TH1F *RpPbFDD0 = (TH1F *)hCroSecpPb->Clone("RpPbFDD0");

  // for (Int_t i = 0; i < 11; i++) {
  //   cout << "stat error cro sec FD: " << hCroSecpPb->GetBinError(i + 1) << endl;
  // }

  // For Dplus

  TFile *RpPbFile = new TFile("/home/abigot/AnalysisNonPromptDplus/Run2pPb5Tev/4_Analysis/5_CrossSection/comparisons/Ratio_Dplus_D0_FD_pPb_final.root", "read");
  TH1F *RpPbFDD0 = (TH1F *)RpPbFile->Get("hRatio");
  const uint8_t nPtBinsFD = 10; // RpPbFDD0->GetNbinsX();

  TGraphErrors *gRpPbFDD0Systematics = (TGraphErrors *)RpPbFile->Get("gRatioSystTot");
  // Double_t SystRpPbFD[11];
  // for (uint8_t ibin = 0; ibin < nPtBinsFD; ibin++) {
  //   SystRpPbFD[ibin] = gSystTot->GetErrorY(ibin);
  // }

  // TGraphErrors *gSystLumi = (TGraphErrors *)RpPbFile->Get("gRaaSystNorm");
  // auto systLumi = gSystLumi->GetErrorY(0);

  //  RpPbFDD0->Draw();

  // TGraphAsymmErrors *gRpPbFDD0Systematics =
  //     new TGraphAsymmErrors(nPtBinsFD, ptlimsmiddleFD, yvaluncFD);
  // for (Int_t i = 0; i < nPtBinsFD; i++) {
  //   Double_t RpPbFD = RpPbFDD0->GetBinContent(i + 1);
  //   Double_t ptx = 0.4;
  //   Double_t errylow = SystRpPbFD[i] * RpPbFD;
  //   Double_t erryhigh = SystRpPbFD[i] * RpPbFD;
  //   //    Double_t errxlow = 0.25;
  //   //    Double_t errxhigh = 0.25;
  //   gRpPbFDD0Systematics->SetPoint(i, ptlimsmiddleFD[i], RpPbFD);
  //   gRpPbFDD0Systematics->SetPointError(i, ptx, ptx, errylow, erryhigh);
  // }

  for (Int_t i = 0; i < nPtBinsFD; i++) {
    auto errY = gRpPbFDD0Systematics->GetErrorY(i);
    gRpPbFDD0Systematics->SetPointError(i, 0.25, errY);
  }


  gRpPbFDD0Systematics->SetFillStyle(0);
  gRpPbFDD0Systematics->SetFillColor(kWhite);
  gRpPbFDD0Systematics->SetLineWidth(2);
  gRpPbFDD0Systematics->SetLineColor(kAzure + 2);

  const Int_t nptlims = nPtBinsFD + 1;
  Float_t ptlims[nptlims + 1] = {1., 2., 3.,  4.,  5.,  6.,
                                 7., 8., 10., 12., 16., 24.};

  TH1D *hrefFD = new TH1D("hrefFD", "hrefFD", nptlims, ptlims);
  hrefFD->SetTitle("");
  hrefFD->GetYaxis()->SetTitle("D^{+}/D^{0}");
  hrefFD->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  // hrefFD->SetMinimum(0.1);
  hrefFD->SetMaximum(1.5);
  SetStyleHisto(hrefFD);
  hrefFD->SetLineWidth(1);
  // hrefFD->GetXaxis()->SetRangeUser(0, 36);
  hrefFD->GetYaxis()->SetTitleOffset(1.3);

  // TGraphAsymmErrors *gNorSystematics =
  //     new TGraphAsymmErrors(1, ptlimsmiddleRpPb, yvaluncRpPb);
  // for (Int_t i = 0; i < 1; i++) {
  //   //    Double_t RpPbFD = RpPbFDD0->GetBinContent(i+1);
  //   Double_t ptx = 0.4;
  //   //    Double_t errylow = SystRpPbFD[i] * RpPbFD;
  //   //    Double_t erryhigh = SystRpPbFD[i] * RpPbFD;
  //   //    Double_t errxlow = 0.25;
  //   //    Double_t errxhigh = 0.25;
  //   // gNorSystematics->SetPoint(i, 37, 1.0);
  //   // gNorSystematics->SetPointError(i, ptx, ptx, SystRpPbFDNor[i],
  //   //                                SystRpPbFDNor[i]);
  //   gNorSystematics->SetPointError(i, ptx, ptx, systLumi, systLumi);
  // }

  // gNorSystematics->SetFillStyle(1001);
  // gNorSystematics->SetFillColor(kBlack);
  // gNorSystematics->SetLineWidth(2);
  // gNorSystematics->SetLineColor(kBlack);
  //  for(int iPt = 0; iPt < nPtBins; iPt++) {
  //    double realerr = TMath::Sqrt((hCroSecpp->GetBinError(iPt+1) /
  //    hCroSecpp->GetBinContent(iPt+1)) * (hCroSecpp->GetBinError(iPt+1) /
  //    hCroSecpp->GetBinContent(iPt+1)) + (hCroSecpPb->GetBinError(iPt+1) /
  //    hCroSecpPb->GetBinContent(iPt+1)) * (hCroSecpPb->GetBinError(iPt+1) /
  //    hCroSecpPb->GetBinContent(iPt+1))); hCroSecpPb->SetBinError(iPt+1,
  //    realerr * hCroSecpPb->GetBinContent(iPt+1));
  //  }
  //
  //  for(int iPt = 0; iPt < nPtBins; iPt++) {
  //    double realerr = TMath::Sqrt((hCroSecppclone->GetBinError(iPt+1) /
  //    hCroSecppclone->GetBinContent(iPt+1)) *
  //    (hCroSecppclone->GetBinError(iPt+1) /
  //    hCroSecppclone->GetBinContent(iPt+1)) +
  //    (hCroSecpPbclone->GetBinError(iPt+1) /
  //    hCroSecpPbclone->GetBinContent(iPt+1)) *
  //    (hCroSecpPbclone->GetBinError(iPt+1) /
  //    hCroSecpPbclone->GetBinContent(iPt+1)));
  //    hCroSecpPbclone->SetBinError(iPt+1, realerr *
  //    hCroSecpPbclone->GetBinContent(iPt+1));
  //  }
  //  hCroSecpPb->Divide(hCroSecpp);
  //  hCroSecpPbclone->Divide(hCroSecppclone);

  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 750, 750);
  gStyle->SetOptStat(0);
  c1->SetTickx();
  c1->SetTicky();
  c1->SetBottomMargin(0.13);
  c1->SetLeftMargin(0.17);
  c1->SetTopMargin(0.05);
  c1->SetRightMargin(0.03);
  c1->cd();
  // hrefPrompt->GetXaxis()->SetRangeUser(0, 36);
  // hrefPrompt->SetMinimum(0.06);
  // hrefFD->GetXaxis()->SetRangeUser(0, 36);
  hrefPrompt->Draw("");
  hrefFD->Draw("same");

  SetStyleHisto(promptRpPb);
  promptRpPb->SetStats(0);
  promptRpPb->SetLineColor(kRed + 1);
  promptRpPb->SetMarkerColor(kRed + 1);
  promptRpPb->SetMarkerStyle(21);
  promptRpPb->SetMarkerSize(1.2);

  SetStyleHisto(RpPbFDD0);
  RpPbFDD0->SetStats(0);
  RpPbFDD0->SetLineColor(kAzure + 2);
  RpPbFDD0->SetMarkerColor(kAzure + 2);
  RpPbFDD0->SetMarkerStyle(20);
  RpPbFDD0->SetMarkerSize(1.2);

  TLatex info;
  info.SetNDC();
  info.SetTextFont(43);
  info.SetTextSize(33);
  info.DrawLatex(0.2, 0.89, "ALICE");
  info.SetTextSize(27);
  info.DrawLatex(0.2, 0.84, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  info.DrawLatex(0.66, 0.89, "-0.96 < #it{y}_{cms} < 0.04");
  info.SetTextSize(25);
  info.DrawLatex(0.21, 0.16, "#pm 1.9% BR unc. not shown");


  gRpPbPromptD0Systematics->Draw("same2");
  promptRpPb->Draw("e0 same");
  gRpPbFDD0Systematics->Draw("same2");
  RpPbFDD0->Draw("e0 same");
  // gNorSystematics->Draw("same2");

  //  hCroSecpPb->GetYaxis()->SetRangeUser(0., 1.8);
  //  hCroSecpPbclone->SetFillColor(17);
  //  hCroSecpPbclone->GetYaxis()->SetRangeUser(0., 1.8);
  //  hCroSecpPbclone->Draw("E2");
  //  hCroSecpPb->Draw("same");
  //  unit->Draw("same");
  // hCroSecpp->Draw("same");

  TLegend *leg = new TLegend(0.63, 0.65, 0.83, 0.8);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetMargin(0.46);
  leg->SetTextFont(43);
  leg->SetTextSize(28);
  leg->AddEntry(RpPbFDD0, "Non-prompt", "p");
  leg->AddEntry(promptRpPb, "Prompt", "p");
  leg->Draw();

  // TLine *unit = new TLine(0, 1, 38, 1);
  // unit->SetLineStyle(3);
  // unit->Draw();

  TLatex inforef;
  inforef.SetNDC();
  inforef.SetTextFont(43);
  inforef.SetTextSize(22);
  inforef.DrawLatex(0.66, 0.63, "JHEP 12 (2019) 092");

  // for (int i = 0; i < 11; i++) {
  //   //    cout << "rel stat unc pp :" <<
  //   //    hCroSecpp->GetBinError(i+1)/hCroSecpp->GetBinContent(i+1) << endl;
  //   cout << "rel stat unc pp :" << hCroSecpp->GetBinError(i + 1) << endl;
  //   cout << "content pp :" << hCroSecpp->GetBinContent(i + 1) << endl;
  //   //    cout << "rel stat unc pPb :" <<
  //   //    hCroSecpPb->GetBinError(i+1)/hCroSecpPb->GetBinContent(i+1) << endl;
  //   cout << "rel stat unc pPb :" << hCroSecpPb->GetBinError(i + 1) << endl;
  //   cout << "content pPb :" << hCroSecpPb->GetBinContent(i + 1) << endl;
  //   //    cout << "rel stat unc RpPb :" <<
  //   //    RpPbFDD0->GetBinError(i+1)/RpPbFDD0->GetBinContent(i+1) << endl;
  //   cout << "rel stat unc RpPb :" << RpPbFDD0->GetBinError(i + 1) << endl;
  //   cout << "content RpPb :" << RpPbFDD0->GetBinContent(i + 1) << endl;
  // }

  c1->SaveAs("./DplusD0Ratio.pdf");
  c1->SaveAs("./DplusD0Ratio.eps");
  c1->SaveAs("./DplusD0Ratio.png");
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
