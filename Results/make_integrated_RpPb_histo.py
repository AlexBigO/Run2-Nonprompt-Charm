"""
file: make_integrated_RpPb_histo.py
brief: script to produce TH1 with integrated RpPb for non-prompt D0 and Dplus
usage: python3 make_integrated_RpPb_histo.py
author: Alexandre Bigot <alexandre.bigot@cern.ch>, Strasbourg University
"""

from ROOT import TH1F, TFile, TGraphErrors, TGraphAsymmErrors


ID_DZERO, ID_DPLUS = 0, 1

def main():
	"""
	Main function
	"""
	
	names = ["Dzero", "Dplus"]
	
	values = [1.04, 0.86]
	unc_stat = [0.11, 0.19]
	unc_syst = [0.12, 0.11]
	unc_extr_plus = [0.06, 0.03]
	unc_extr_minus = [0.11, 0.11]
	
	histos, graphs_syst, graphs_extr = [], [], []
	for name in names:
		histos.append(TH1F(f"hIntRpPb{name}", f"hIntRpPb{name}", 1, -0.96, 0.04))
	
		graphs_syst.append(TGraphErrors(1))
		graphs_syst[-1].SetName(f"gIntRpPbSystTotWoExtr{name}")

		graphs_extr.append(TGraphAsymmErrors(1))
		graphs_extr[-1].SetName(f"gIntRpPbSystExtr{name}")
	
	for i, (h, g_syst, g_extr) in enumerate(zip(histos, graphs_syst, graphs_extr)):
		h.SetBinContent(1, values[i])
		h.SetBinError(1, unc_stat[i])
		
		g_syst.SetPoint(0, 0.04-0.5, values[i])
		g_syst.SetPointError(0, 0.5, unc_syst[i])
		
		g_extr.SetPoint(0, 0.04-0.5, values[i])
		g_extr.SetPointError(0, 0.5, 0.5, unc_extr_minus[i], unc_extr_plus[i])
		
	outfile = TFile("integrated_RpPb_Nonprompt_Dzero_Dplus.root", "recreate")
	for (h, g_syst, g_extr) in zip(histos, graphs_syst, graphs_extr):
		h.Write()
		g_syst.Write()
		g_extr.Write()
	outfile.Close()
	
	
	

if __name__ == "__main__":
	main()
