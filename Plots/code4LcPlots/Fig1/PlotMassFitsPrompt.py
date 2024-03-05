'''
Script for the plots of D-meson mass fits
'''

import yaml
from ROOT import TFile, TCanvas, TLatex, TLegend # pylint: disable=import-error,no-name-in-module
from ROOT import kBlue, kRed, kBlack # pylint: disable=import-error,no-name-in-module
from StyleFormatter import SetGlobalStyle, SetObjectStyle

with open('config_input_files.yml', 'r') as ymlCfgFile:
    inputCfg = yaml.load(ymlCfgFile, yaml.FullLoader)

# SetGlobalStyle(padleftmargin=0.14, padbottommargin=0.125, titleoffsety=1.3, titleoffsetx=1., maxdigits=3)
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

legend = TLegend(0.18, 0.52, 0.38, 0.67)
legend.SetBorderSize(0)
legend.SetFillStyle(0)
# legend.SetTextFont(42)
# legend.SetTextSize(0.04)
legend.SetTextFont(43)
legend.SetTextSize(18)
# legend.AddEntry(hInvMassDplus, 'Data', 'p')
legend.AddEntry(fMassTotDplus, 'Total fit function', 'l')
legend.AddEntry(fMassBkgDplus, '#splitline{Combinatorial}{background}', 'l')
strFrame = (f';#it{{M}}(pK#pi) (GeV/#it{{c}}^{{2}}); '
            f'Counts per {hInvMassDplus.GetBinWidth(nBinDplus+1)*1000:.0f} MeV/#it{{c}}^{{2}}'
           )
ptMin = hRawYieldsDplus.GetXaxis().GetBinLowEdge(nBinDplus+1)
ptMax = hRawYieldsDplus.GetXaxis().GetBinUpEdge(nBinDplus+1)
strSig = f'#it{{S}} = {hRawYieldsDplus.GetBinContent(nBinDplus+1):.0f} #pm {hRawYieldsDplus.GetBinError(1):.0f}'
strMu = (f'#mu = ({hMeanDplus.GetBinContent(nBinDplus+1)*1000:.0f} '
         f'#pm {hMeanDplus.GetBinError(nBinDplus+1)*1000:.0f}) MeV/#it{{c}}^{{2}}'
        )
strSigma = (f'#sigma = {hSigmaDplus.GetBinContent(nBinDplus+1)*1000:.0f} '
            f'MeV/#it{{c}}^{{2}}'
           )
# strSigma = (f'#sigma = ({hSigmaDplus.GetBinContent(nBinDplus+1)*1000:.0f} '
#             f'#pm {hSigmaDplus.GetBinError(nBinDplus+1)*1000:.0f}) MeV/#it{{c}}^{{2}}'
#            )
cMassFitDplus = TCanvas('cMassFitDplus', '', 520, 500)
hFrameDplus = cMassFitDplus.DrawFrame(2.16, 24.5e+3, 2.41, 37.5e+3, strFrame)
hFrameDplus.GetYaxis().SetDecimals()
hInvMassDplus.Draw('same')
fMassBkgDplus.Draw('same')
fMassTotDplus.Draw('same')
legend.Draw("same")
latALICE.DrawLatex(0.19, 0.89, 'ALICE')
latLabel.DrawLatex(0.19, 0.82, 'p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV')
latLabel.SetTextSize(18)
latLabel.DrawLatex(0.19, 0.76, '#Lambda_{c}^{+} #rightarrow pK^{#font[122]{-}}#pi^{+} and charge conj.')
latLabel.DrawLatex(0.19, 0.70, f'{ptMin:.0f} < #it{{p}}_{{T}} < {ptMax:.0f} GeV/#it{{c}}')
latLabel.DrawLatex(0.65, 0.89, '#font[122]{-}0.96 < #it{y}_{cms} < 0.04')
latLabel.DrawLatex(0.55, 0.40, strMu)
latLabel.DrawLatex(0.55, 0.34, strSigma)
latLabel.DrawLatex(0.55, 0.28, strSig)
latLabel.SetTextSize(18)
latLabel.DrawLatex(0.18, 0.16, '#it{f}_{ non-prompt}^{ raw} = 0.630 #pm 0.056 (stat.) #pm 0.050 (syst.)')
cMassFitDplus.Update()

cMassFitDplus.SaveAs('../pKpi/InvMassFitLc_pkpi_4_8.eps')
cMassFitDplus.SaveAs('../pKpi/InvMassFitLc_pkpi_4_8.pdf')
cMassFitDplus.SaveAs('../pKpi/InvMassFitLc_pkpi_4_8.png')

input('Press enter to exit')
