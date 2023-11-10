#include <iostream>

using namespace std;

void SetStyleHisto(TH1D *h);
void SetStyleHisto(TH1F *h);

const Double_t ptlimsmiddleCMS[5] = {12.5, 17.5, 22.5, 27.5, 45.};
Double_t yvaluncCMS[5] = {0., 0., 0., 0., 0.};
const Double_t ptlimsmiddleFD[11] = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5,
                                     7.5, 9,   11,  14,  20};
Double_t yvaluncFD[11] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
const Double_t ptlimsmiddleRpPb[1] = {61.};
Double_t yvaluncRpPb[1] = {1.};
const Double_t ptlimsmiddleRpPbCMS[1] = {63.};
Double_t yvaluncRpPbCMS[1] = {1.};

void DrawRpPb_CMS_Logx() {

  // CMS

  TFile *CMSFile = new TFile("./CMS_HEPData-ins1390110-v1-root.root", "read");
  TDirectoryFile *CMSdir = (TDirectoryFile *)CMSFile->Get("Table 4");
  TH1F *CMSRpPb = (TH1F *)CMSdir->Get("Hist1D_y1");
  TH1F *CMSRpPbStat = (TH1F *)CMSdir->Get("Hist1D_y1_e1");
  TH1F *CMSRpPbSystData = (TH1F *)CMSdir->Get("Hist1D_y1_e2");
  TH1F *CMSRpPbSystFONLLPlus = (TH1F *)CMSdir->Get("Hist1D_y1_e3plus");
  TH1F *CMSRpPbSystFONLLMinus = (TH1F *)CMSdir->Get("Hist1D_y1_e3minus");

  int nPtBinsCMS = CMSRpPb->GetNbinsX();
  for (int iPt = 0; iPt < nPtBinsCMS; iPt++) {
    CMSRpPb->SetBinError(iPt + 1, CMSRpPbStat->GetBinContent(iPt + 1));
  }

  Double_t errxlowCMS[5] = {2., 2., 2., 2., 5.};
  Double_t errxhighCMS[5] = {2., 2., 2., 2., 5.};
  TGraphAsymmErrors *gRpPbCMSSystematics =
      new TGraphAsymmErrors(5, ptlimsmiddleCMS, yvaluncCMS);
  for (Int_t i = 0; i < 5; i++) {
    Double_t RpPbCMS = CMSRpPb->GetBinContent(i + 1);
    //    Double_t ptx = ptlimsmiddleCMS[i];
    Double_t errylow = CMSRpPbSystData->GetBinContent(i + 1);
    Double_t erryhigh = CMSRpPbSystData->GetBinContent(i + 1);
    //    Double_t errxlow = 0.25;
    //    Double_t errxhigh = 0.25;
    gRpPbCMSSystematics->SetPoint(i, ptlimsmiddleCMS[i], RpPbCMS);
    gRpPbCMSSystematics->SetPointError(i, errxlowCMS[i], errxhighCMS[i],
                                       errylow, erryhigh);
  }

  gRpPbCMSSystematics->SetFillStyle(0);
  gRpPbCMSSystematics->SetFillColor(kRed + 1);
  gRpPbCMSSystematics->SetLineWidth(2);
  gRpPbCMSSystematics->SetLineColor(kRed + 1);
  //  gRpPbCMSSystematics->SetLineStyle(9);
  gRpPbCMSSystematics->SetMarkerColor(kRed + 1);

  TGraphAsymmErrors *gRpPbCMSSystematicsFONLL =
      new TGraphAsymmErrors(5, ptlimsmiddleCMS, yvaluncCMS);
  for (Int_t i = 0; i < 5; i++) {
    Double_t RpPbCMS = CMSRpPb->GetBinContent(i + 1);
    Double_t ptx = ptlimsmiddleCMS[i];
    Double_t errylow = -1. * CMSRpPbSystFONLLMinus->GetBinContent(i + 1);
    Double_t erryhigh = CMSRpPbSystFONLLPlus->GetBinContent(i + 1);
    //    Double_t errxlow = 0.25;
    //    Double_t errxhigh = 0.25;
    gRpPbCMSSystematicsFONLL->SetPoint(i, ptlimsmiddleCMS[i], RpPbCMS);
    gRpPbCMSSystematicsFONLL->SetPointError(i, errxlowCMS[i], errxhighCMS[i],
                                            errylow, erryhigh);
  }

  //  gRpPbCMSSystematicsFONLL->SetFillStyle(3002);
  gRpPbCMSSystematicsFONLL->SetFillStyle(3004);
  gRpPbCMSSystematicsFONLL->SetFillColor(kRed - 7);
  gRpPbCMSSystematicsFONLL->SetLineWidth(0);
  gRpPbCMSSystematicsFONLL->SetLineStyle(3);
  gRpPbCMSSystematicsFONLL->SetLineColor(kRed - 7);
  gRpPbCMSSystematicsFONLL->SetMarkerColor(kRed - 7);

  const Int_t nptlimsExtra = 7;
  Float_t ptlimsExtral[nptlimsExtra + 1] = {0.8, 10., 15., 20.,
                                            25., 30., 60., 96.};

  TH1D *hrefCMS = new TH1D("hrefCMS", "hrefCMS", nptlimsExtra, ptlimsExtral);
  hrefCMS->SetTitle("");
  hrefCMS->GetYaxis()->SetTitle("#it{R}_{pPb}, #it{R}_{pPb}^{ FONLL}");
  hrefCMS->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  hrefCMS->SetMinimum(0.01);
  hrefCMS->SetMaximum(2.49);

  SetStyleHisto(hrefCMS);
  hrefCMS->SetLineWidth(1);
  hrefCMS->GetYaxis()->SetTitleOffset(1.1);
  hrefCMS->GetYaxis()->SetNdivisions(505);
  // non-prompt D0 RpPb

  TFile *pPbFile = new TFile("./CrossSection_D0_pPb5TeV_FD.root", "read");
  TH1F *hCroSecpPb = (TH1F *)pPbFile->Get("hCrossSection");
  //  TH1D* hCroSecpPbclone = (TH1D*)hCroSecpPb->Clone("hCroSecpPbclone");

  TFile *ppFile = new TFile("./HEPData-ins1848990-v1-root.root", "read");
  TDirectoryFile *dir = (TDirectoryFile *)ppFile->Get("Table 1");
  TH1F *hCroSecpp = (TH1F *)dir->Get("Hist1D_y1");
  TH1F *hCroSecppStat = (TH1F *)dir->Get("Hist1D_y1_e1");
  TH1F *hCroSecppSyst = (TH1F *)dir->Get("Hist1D_y1_e2");
  TH1F *hCroSecppSystBR = (TH1F *)dir->Get("Hist1D_y1_e3");
  TH1F *hCroSecppSystLumi = (TH1F *)dir->Get("Hist1D_y1_e4");

  TFile *corrFile = new TFile("./corrfactorFONLL_update_syst.root", "read");
  TH1F *factor = (TH1F *)corrFile->Get("hRatioDfromBOverBCentral");

  int nPtBinsFD = hCroSecpp->GetNbinsX();

  for (int iPt = 0; iPt < nPtBinsFD; iPt++) {
    hCroSecpp->SetBinError(iPt + 1, hCroSecppStat->GetBinContent(iPt + 1));
  }

  //  hCroSecpp->Draw();

  Double_t SystppNor[11];
  for (Int_t ibin = 0; ibin < 11; ibin++) {
    SystppNor[ibin] = hCroSecppSystLumi->GetBinContent(ibin + 1) /
                      hCroSecpp->GetBinContent(ibin + 1);
  }

  Double_t SystppAll[11];
  for (Int_t ibin = 0; ibin < 11; ibin++) {
    SystppAll[ibin] = hCroSecppSyst->GetBinContent(ibin + 1) /
                      hCroSecpp->GetBinContent(ibin + 1);
  }

  Double_t raw[11] = {0.03, 0.02, 0.01, 0.01, 0.01, 0.01,
                      0.01, 0.01, 0.02, 0.02, 0.03};
  Double_t sel[11] = {0.05, 0.03, 0.03, 0.03, 0.03, 0.03,
                      0.03, 0.04, 0.04, 0.04, 0.04};
  Double_t fr[11] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
                     0.01, 0.01, 0.01, 0.01, 0.02};
  Double_t gen[11] = {0.07, 0.05, 0.03, 0.02, 0.01, 0., 0., 0., 0., 0., 0.02};
  Double_t tra[11] = {0.02, 0.02, 0.02,  0.02, 0.02, 0.02,
                      0.02, 0.02, 0.025, 0.03, 0.03};
  Double_t br[11] = {0.03, 0.03, 0.03, 0.03, 0.03, 0.03,
                     0.03, 0.03, 0.03, 0.03, 0.03};
  Double_t nor[11] = {0.037, 0.037, 0.037, 0.037, 0.037, 0.037,
                      0.037, 0.037, 0.037, 0.037, 0.037};

  Double_t SystpPbAll[11];
  for (Int_t ibin = 0; ibin < 11; ibin++) {
    SystpPbAll[ibin] = TMath::Sqrt(
        raw[ibin] * raw[ibin] + sel[ibin] * sel[ibin] + fr[ibin] * fr[ibin] +
        gen[ibin] * gen[ibin] + tra[ibin] * tra[ibin]);
  }

  Double_t SystRpPbFD[11];
  for (Int_t ibin = 0; ibin < 11; ibin++) {
    SystRpPbFD[ibin] = TMath::Sqrt(SystpPbAll[ibin] * SystpPbAll[ibin] +
                                   SystppAll[ibin] * SystppAll[ibin]);
  }

  Double_t SystRpPbFDNor[11];
  for (Int_t ibin = 0; ibin < 11; ibin++) {
    SystRpPbFDNor[ibin] =
        TMath::Sqrt(nor[ibin] * nor[ibin] + SystppNor[ibin] * SystppNor[ibin]);
  }

  hCroSecpPb->Scale(1 / (0.0395 * 208));

  for (Int_t ibin = 0; ibin < 11; ibin++) {
    Double_t binContent = hCroSecpPb->GetBinContent(ibin + 1);
    Double_t binError = hCroSecpPb->GetBinError(ibin + 1);
    binContent = binContent / factor->GetBinContent(ibin + 1);
    binError = binError / factor->GetBinContent(ibin + 1);
    hCroSecpPb->SetBinContent(ibin + 1, binContent);
    hCroSecpPb->SetBinError(ibin + 1, binError);
  }
  //  hCroSecpPb->Draw();
  //  hCroSecpp->Draw("same");

  hCroSecpPb->Sumw2();
  hCroSecpp->Sumw2();
  TH1F *RpPbFDD0 = (TH1F *)hCroSecpPb->Clone("RpPbFDD0");

  RpPbFDD0->Divide(hCroSecpp);
  //  RpPbFDD0->Draw();

  Double_t errxlowALICE[11] = {0.17, 0.25, 0.3, 0.4, 0.4, 0.4,
                               0.4,  0.55, 0.7, 1.2, 2.2};
  Double_t errxhighALICE[11] = {0.17, 0.25, 0.3, 0.4, 0.4, 0.4,
                                0.4,  0.55, 0.7, 1.2, 2.2};
  TGraphAsymmErrors *gRpPbFDD0Systematics =
      new TGraphAsymmErrors(11, ptlimsmiddleFD, yvaluncFD);
  for (Int_t i = 0; i < 11; i++) {
    Double_t RpPbFD = RpPbFDD0->GetBinContent(i + 1);
    //    Double_t ptx = 0.4;
    Double_t errylow = SystRpPbFD[i] * RpPbFD;
    Double_t erryhigh = SystRpPbFD[i] * RpPbFD;
    //    Double_t errxlow = 0.25;
    //    Double_t errxhigh = 0.25;
    gRpPbFDD0Systematics->SetPoint(i, ptlimsmiddleFD[i], RpPbFD);
    gRpPbFDD0Systematics->SetPointError(i, errxlowALICE[i], errxlowALICE[i],
                                        errylow, erryhigh);
  }

  gRpPbFDD0Systematics->SetFillStyle(0);
  gRpPbFDD0Systematics->SetFillColor(kWhite);
  gRpPbFDD0Systematics->SetLineWidth(2);
  gRpPbFDD0Systematics->SetLineColor(kAzure + 2);

  const Int_t nptlims = 11;
  Float_t ptlims[nptlims + 1] = {1., 2., 3.,  4.,  5.,  6.,
                                 7., 8., 10., 12., 16., 24.};

  TH1D *hrefFD = new TH1D("hrefFD", "hrefFD", nptlims, ptlims);
  hrefFD->SetTitle("");
  hrefFD->GetYaxis()->SetTitle("#it{R}_{pPb}");
  hrefFD->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  hrefFD->SetMinimum(0.);
  hrefFD->SetMaximum(2.7);
  SetStyleHisto(hrefFD);
  hrefFD->SetLineWidth(1);
  hrefFD->GetYaxis()->SetTitleOffset(1.3);

  TGraphAsymmErrors *gNorSystematics =
      new TGraphAsymmErrors(1, ptlimsmiddleRpPb, yvaluncRpPb);
  for (Int_t i = 0; i < 1; i++) {
    //    Double_t RpPbFD = RpPbFDD0->GetBinContent(i+1);
    Double_t ptx = 2.5;
    //    Double_t errylow = SystRpPbFD[i] * RpPbFD;
    //    Double_t erryhigh = SystRpPbFD[i] * RpPbFD;
    //    Double_t errxlow = 0.25;
    //    Double_t errxhigh = 0.25;
    gNorSystematics->SetPoint(i, 72, 1.0);
    gNorSystematics->SetPointError(i, ptx, ptx, 0.0425, 0.0425);
  }

  gNorSystematics->SetFillStyle(1001);
  //  gNorSystematics->SetFillColor(kBlack);
  gNorSystematics->SetFillColor(kBlue - 8);
  gNorSystematics->SetLineWidth(2);
  gNorSystematics->SetLineColor(kBlue - 8);
  //  gNorSystematics->SetLineColor(kBlack);

  Double_t SystRpPbFDNorCMS[1] = {0.047};
  TGraphAsymmErrors *gNorSystematicsCMS =
      new TGraphAsymmErrors(1, ptlimsmiddleRpPbCMS, yvaluncRpPbCMS);
  for (Int_t i = 0; i < 1; i++) {
    //    Double_t RpPbFD = RpPbFDD0->GetBinContent(i+1);
    Double_t ptx = 2.9;
    //    Double_t errylow = SystRpPbFD[i] * RpPbFD;
    //    Double_t erryhigh = SystRpPbFD[i] * RpPbFD;
    //    Double_t errxlow = 0.25;
    //    Double_t errxhigh = 0.25;
    gNorSystematicsCMS->SetPoint(i, 78, 1.0);
    gNorSystematicsCMS->SetPointError(i, ptx, ptx, SystRpPbFDNorCMS[i],
                                      SystRpPbFDNorCMS[i]);
  }

  gNorSystematicsCMS->SetFillStyle(1001);
  //  gNorSystematicsCMS->SetFillColor(kGray);
  gNorSystematicsCMS->SetFillColor(kRed - 8);
  gNorSystematicsCMS->SetLineWidth(2);
  //  gNorSystematicsCMS->SetLineColor(kGray);
  gNorSystematicsCMS->SetLineColor(kRed - 8);
  //  gNorSystematicsCMS->SetMarkerColor(kGray);
  gNorSystematicsCMS->SetMarkerColor(kRed - 8);

  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 900, 750);
  gStyle->SetOptStat(0);
  c1->SetTickx();
  c1->SetTicky();
  c1->SetLogx();
  c1->SetBottomMargin(0.13);
  c1->SetLeftMargin(0.17);
  c1->SetTopMargin(0.05);
  c1->SetRightMargin(0.03);
  c1->cd();
  hrefCMS->Draw("");
  hrefFD->Draw("same");

  SetStyleHisto(CMSRpPb);
  CMSRpPb->SetStats(0);
  CMSRpPb->SetLineColor(kRed + 1);
  CMSRpPb->SetMarkerStyle(21);
  CMSRpPb->SetMarkerColor(kRed + 1);

  SetStyleHisto(RpPbFDD0);
  RpPbFDD0->SetStats(0);
  RpPbFDD0->SetLineColor(kAzure + 3);
  RpPbFDD0->SetMarkerColor(kAzure + 3);
  RpPbFDD0->SetMarkerStyle(20);

  TLatex info;
  info.SetNDC();
  info.SetTextFont(43);
  info.SetTextSize(30);
  info.DrawLatex(0.21, 0.89, "ALICE Preliminary");

  TLatex infopPb;
  infopPb.SetNDC();
  infopPb.SetTextFont(43);
  infopPb.SetTextSize(25);
  infopPb.DrawLatex(0.21, 0.84,
                    "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");

  TLatex infopPbb;
  infopPbb.SetNDC();
  infopPbb.SetTextFont(43);
  infopPbb.SetTextSize(25);
  infopPbb.DrawLatex(
      0.21, 0.78, "ALICE (#it{R}_{pPb})   #font[122]{-}0.96 < #it{y} < 0.04");
  //  infopPb.DrawLatex(0.45, 0.85, "-0.96 < y < 0.04");

  //  TLatex inforef;
  //  inforef.SetNDC();
  //  inforef.SetTextFont(43);
  //  inforef.SetTextSize(23);
  //  inforef.DrawLatex(0.21, 0.25, "[PRL 116, 032301 (2016)]");

  gRpPbCMSSystematicsFONLL->Draw("same2");
  gRpPbCMSSystematics->Draw("same2");
  CMSRpPb->Draw("e0 same");
  gRpPbFDD0Systematics->Draw("same2");
  RpPbFDD0->Draw("e0 same");
  gNorSystematics->Draw("same2");
  gNorSystematicsCMS->Draw("same2");
  //  hCroSecpPb->GetYaxis()->SetRangeUser(0., 1.8);
  //  hCroSecpPbclone->SetFillColor(17);
  //  hCroSecpPbclone->GetYaxis()->SetRangeUser(0., 1.8);
  //  hCroSecpPbclone->Draw("E2");
  //  hCroSecpPb->Draw("same");
  //  unit->Draw("same");
  // hCroSecpp->Draw("same");

  TLegend *leg = new TLegend(0.2, 0.68, 0.33, 0.76);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetMargin(0.46);
  leg->SetTextSize(25);
  leg->SetTextFont(43);
  leg->SetNColumns(1);
  leg->AddEntry(RpPbFDD0, "Non-prompt D^{0}", "pl");
  leg->AddEntry(gNorSystematics, "lumi. + BR syst.", "F");
  leg->Draw();

  TLatex infoCMS1;
  infoCMS1.SetNDC();
  infoCMS1.SetTextFont(43);
  infoCMS1.SetTextSize(26);
  infoCMS1.DrawLatex(0.21, 0.34, "CMS (#it{R}_{pPb}^{ FONLL})");

  TLatex infoCMS;
  infoCMS.SetNDC();
  infoCMS.SetTextFont(43);
  infoCMS.SetTextSize(25);
  //  infoCMS.DrawLatex(0.62, 0.85, "CMS");
  //  infoCMS.DrawLatex(0.65, 0.85, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02
  //  TeV");
  infoCMS.DrawLatex(0.4, 0.33, "|#it{y}| < 2.4");

  TLegend *legCMS = new TLegend(0.2, 0.17, 0.33, 0.32);
  legCMS->SetFillColor(0);
  legCMS->SetFillStyle(0);
  legCMS->SetBorderSize(0);
  legCMS->SetMargin(0.46);
  legCMS->SetTextSize(23);
  legCMS->SetTextFont(43);
  legCMS->SetNColumns(1);
  //  legCMS->AddEntry(CMSRpPb, "#it{R}_{#it{ p}+A}^{ FONLL}", "lp");
  legCMS->AddEntry(CMSRpPb, "B^{+}   PRL 116 (2016) 032301", "lp");
  legCMS->AddEntry(gRpPbCMSSystematicsFONLL, "FONLL pp ref. syst.", "lf");
  legCMS->AddEntry(gNorSystematicsCMS, "lumi. + BR syst.", "F");
  legCMS->Draw();

  TLegend *legCMS2 = new TLegend(0.61, 0.55, 0.74, 0.69);
  legCMS2->SetFillColor(0);
  legCMS2->SetFillStyle(0);
  legCMS2->SetBorderSize(0);
  legCMS2->SetMargin(0.46);
  legCMS2->SetTextSize(25);
  legCMS2->SetTextFont(43);
  legCMS2->SetNColumns(1);
  //  legCMS->AddEntry(CMSRpPb, "#it{R}_{#it{ p}+A}^{ FONLL}", "lp");
  //  legCMS->AddEntry(CMSRpPb, "B^{+}", "lp");
  //  legCMS2->AddEntry(gRpPbCMSSystematics, "Syst. #it{p} +Pb data", "F");
  //  legCMS2->AddEntry(gRpPbCMSSystematicsFONLL, "Syst. FONLL pp ref.", "lpf");
  //  legCMS2->AddEntry(gNorSystematicsCMS, "Syst. int. lumi + BR", "F");
  //  legCMS2->Draw();

  TLine *unit = new TLine(0, 1, 89, 1);
  unit->SetLineStyle(3);
  unit->Draw();

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
