'''
Script for the plots of D-meson mass fits
'''

import yaml
from ROOT import TFile, TCanvas, TLatex, TLegend # pylint: disable=import-error,no-name-in-module
from ROOT import kBlue, kRed, kBlack # pylint: disable=import-error,no-name-in-module
from StyleFormatter import SetGlobalStyle, SetObjectStyle

with open('config_input_files.yml', 'r') as ymlCfgFile:
    inputCfg = yaml.load(ymlCfgFile, yaml.FullLoader)

SetGlobalStyle(padleftmargin=0.14,padtopmargin=0.045, padbottommargin=0.125, titleoffsety=1.3, titleoffsetx=1., maxdigits=3)

# D+
nBinDplus = 0
inFileDplus = TFile.Open(inputCfg['prompt']['Dplus']['massfit'])
hRawYieldsDplus = inFileDplus.Get('hRawYields')
hSigmaDplus = inFileDplus.Get('hRawYieldsSigma')
hMeanDplus = inFileDplus.Get('hRawYieldsMean')
cMassDplus = inFileDplus.Get('cMass0')
hInvMassDplus = cMassDplus.GetListOfPrimitives().FindObject('fHistoInvMass')
fMassTotDplus = cMassDplus.GetListOfPrimitives().FindObject('funcmass')
fMassBkgDplus = cMassDplus.GetListOfPrimitives().FindObject('funcbkgrefit')
# hInvMassDplus = cMassDplus.GetPad(nBinDplus+1).GetListOfPrimitives().FindObject('fHistoInvMass')
# fMassTotDplus = cMassDplus.GetPad(nBinDplus+1).GetListOfPrimitives().FindObject('funcmass')
# fMassBkgDplus = cMassDplus.GetPad(nBinDplus+1).GetListOfPrimitives().FindObject('funcbkgrefit')
SetObjectStyle(hInvMassDplus, color=kBlack)
SetObjectStyle(fMassTotDplus, linewidth=3, linecolor=kBlue)
SetObjectStyle(fMassBkgDplus, linewidth=3, linecolor=kRed, linestyle=2)
fMassTotDplus.SetNpx(1000)
fMassBkgDplus.SetNpx(1000)

# Ds
nBinDs = 0
inFileDs = TFile.Open(inputCfg['prompt']['Ds']['massfit'])
hRawYieldsDs = inFileDs.Get('hRawYields')
hSigmaDs = inFileDs.Get('hRawYieldsSigma')
hMeanDs = inFileDs.Get('hRawYieldsMean')
cMassDs = inFileDs.Get('cMass')
hInvMassDs = cMassDs.GetPad(nBinDs+1).GetListOfPrimitives().FindObject('fHistoInvMass')
fMassTotDs = cMassDs.GetPad(nBinDs+1).GetListOfPrimitives().FindObject('funcmass')
fMassBkgDs = cMassDs.GetPad(nBinDs+1).GetListOfPrimitives().FindObject('funcbkgrefit')
fMassSecPeakDs = cMassDs.GetPad(nBinDs+1).GetListOfPrimitives().FindObject('fsecpeak')
SetObjectStyle(hInvMassDs, color=kBlack)
SetObjectStyle(fMassTotDs, linewidth=3, linecolor=kBlue)
SetObjectStyle(fMassBkgDs, linewidth=3, linecolor=kRed, linestyle=2)
fMassTotDs.SetNpx(1000)
fMassBkgDs.SetNpx(1000)

latALICE = TLatex()
latALICE.SetNDC()
latALICE.SetTextSize(26)
latALICE.SetTextFont(43)
# latALICE.SetTextSize(0.05)
# latALICE.SetTextFont(42)
latALICE.SetTextColor(kBlack)

latLabel = TLatex()
latLabel.SetNDC()
latLabel.SetTextSize(22)
latLabel.SetTextFont(43)
# latLabel.SetTextSize(0.04)
# latLabel.SetTextFont(42)
latLabel.SetTextColor(kBlack)

legend = TLegend(0.55, 0.75, 0.80, 0.85)
legend.SetBorderSize(0)
legend.SetFillStyle(0)
# legend.SetTextFont(42)
# legend.SetTextSize(0.04)
legend.SetTextFont(43)
legend.SetTextSize(22)
# legend.AddEntry(hInvMassDplus, 'Data', 'p')
legend.AddEntry(fMassTotDplus, 'Total fit function', 'l')
legend.AddEntry(fMassBkgDplus, 'Combinatorial', 'l')
strFrame = (f';#it{{M}}(pK#pi) (GeV/#it{{c}}^{{2}}); '
            f'Counts per {hInvMassDplus.GetBinWidth(nBinDplus+1)*1000:.0f} MeV/#it{{c}}^{{2}}'
           )
ptMin = hRawYieldsDplus.GetXaxis().GetBinLowEdge(nBinDplus+1)
ptMax = hRawYieldsDplus.GetXaxis().GetBinUpEdge(nBinDplus+1)
strSig = f'#it{{S}} = {hRawYieldsDplus.GetBinContent(nBinDplus+1):.0f} #pm {hRawYieldsDplus.GetBinError(1):.0f}'
strMu = (f'#mu = ({hMeanDplus.GetBinContent(nBinDplus+1)*1000:.0f} '
         f'#pm {hMeanDplus.GetBinError(nBinDplus+1)*1000:.0f}) MeV/#it{{c}}^{{2}}'
        )
strSigma = (f'#sigma = ({hSigmaDplus.GetBinContent(nBinDplus+1)*1000:.0f} '
            f'#pm {hSigmaDplus.GetBinError(nBinDplus+1)*1000:.0f}) MeV/#it{{c}}^{{2}}'
           )
cMassFitDplus = TCanvas('cMassFitDplus', '', 520, 500)
hFrameDplus = cMassFitDplus.DrawFrame(2.16, 24.5e+3, 2.41, 37.5e+3, strFrame)
hFrameDplus.GetYaxis().SetDecimals()
hInvMassDplus.Draw('same')
fMassBkgDplus.Draw('same')
fMassTotDplus.Draw('same')
legend.Draw("same")
latALICE.DrawLatex(0.19, 0.89, 'ALICE')
latLabel.DrawLatex(0.19, 0.82, 'p#font[122]{-}Pb, #sqrt{#it{s}} = 5.02 TeV')
latLabel.DrawLatex(0.19, 0.76, '#Lambda_{c}^{+} #rightarrow pK^{#font[122]{-}}#pi^{+}')
latLabel.DrawLatex(0.19, 0.70, f'{ptMin:.0f} < #it{{p}}_{{T}} < {ptMax:.0f} GeV/#it{{c}}')
latLabel.DrawLatex(0.57, 0.40, strMu)
latLabel.DrawLatex(0.57, 0.34, strSigma)
latLabel.DrawLatex(0.57, 0.28, strSig)
latLabel.SetTextSize(18)
latLabel.DrawLatex(0.19, 0.20, '#it{f}_{ non-prompt}^{ raw} = 0.630 #pm 0.056 (stat.) #pm 0.0504 (syst.)')
cMassFitDplus.Update()

strFrame = (f';#it{{M}}(KK#pi) (GeV/#it{{c}}^{{2}}); '
            f'Counts per {hInvMassDs.GetBinWidth(nBinDs+1)*1000:.0f} MeV/#it{{c}}^{{2}}')
ptMin = hRawYieldsDs.GetXaxis().GetBinLowEdge(nBinDs+1)
ptMax = hRawYieldsDs.GetXaxis().GetBinUpEdge(nBinDs+1)
strSig = f'#it{{S}} = {hRawYieldsDs.GetBinContent(nBinDs+1):.0f} #pm {hRawYieldsDs.GetBinError(nBinDs+1):.0f}'
strMu = (f'#mu = ({hMeanDs.GetBinContent(nBinDs+1)*1000:.0f} '
         f'#pm {hMeanDs.GetBinError(nBinDs+1)*1000:.0f}) MeV/#it{{c}}^{{2}}'
        )
strSigma = (f'#sigma = ({hSigmaDplus.GetBinContent(nBinDs+1)*1000:.0f} '
            f'#pm {hSigmaDplus.GetBinError(nBinDs+1)*1000:.0f}) MeV/#it{{c}}^{{2}}'
           )
cMassFitDs = TCanvas('cMassFitDs', '', 500, 500)
hFrameDs = cMassFitDs.DrawFrame(1.784, 0.1, 2.1, 110, strFrame)
hFrameDs.GetYaxis().SetDecimals()
hInvMassDs.Draw('same')
fMassBkgDs.Draw('same')
fMassTotDs.Draw('same')
latALICE.DrawLatex(0.19, 0.88, 'ALICE')
latLabel.DrawLatex(0.19, 0.83, 'pp, #sqrt{#it{s}} = 5.02 TeV')
latLabel.DrawLatex(0.19, 0.78, \
                   'D_{s}^{+} #rightarrow #phi#pi^{+} #rightarrow K^{+}K^{#font[122]{-}}#pi^{+} and charge conj.')
latLabel.DrawLatex(0.19, 0.73, f'{ptMin:.0f} < #it{{p}}_{{T}} < {ptMax:.0f} GeV/#it{{c}}')
latLabel.DrawLatex(0.19, 0.28, strSig)
latLabel.DrawLatex(0.19, 0.23, strMu)
latLabel.DrawLatex(0.19, 0.18, strSigma)
cMassFitDs.Update()

cMassFitDplus.SaveAs('../InvMassFitLc_prompt_pp5TeV.eps')
cMassFitDplus.SaveAs('../InvMassFitLc_prompt_pp5TeV.pdf')
cMassFitDplus.SaveAs('../InvMassFitLc_prompt_pp5TeV.png')
cMassFitDs.SaveAs('../figures/InvMassFitDs_prompt_pp5TeV.eps')

input('Press enter to exit')
