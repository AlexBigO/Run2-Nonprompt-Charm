"""
file: average_rppb.py
brief: Script to average RpPb results from D0 and D+
usage: python3 average_rppb.py
author: Alexandre Bigot <alexandre.bigot@cern.ch>, Strasbourg University
"""

import numpy as np
from ROOT import TFile, TGraphErrors
from style_formatter import set_global_style
from uncertainty_handler import UncertaintyPropagator


def main():
    """
    Main function
    """

    set_global_style(padleftmargin=0.14, padbottommargin=0.12, titlesize=0.045, labelsize=0.04,
                     maxdigits=3, linewidth=1)

    name_infiles = ["../Results/Dplus/RpPb_Dplus_Nonprompt.root",
                    "../Results/D0/RpPb_D0_Nonprompt_with_Dplus_binning.root"]

    name_outfile = "../Results/RpPb_D0_Dplus_Nonprompt_Weighted_Average.root"

    name_histos = ["hRpPb", "RpPbFDD0"]

    name_ingraphs = [
        ["gRaaSystYieldExtr", "gRaaSystSelEff", "gRaaSystTrEff", "gRaaSystPIDEff", "gRaaSystPtShape", "gRaaSystFD",
         "gRaaSystNorm", "gRaaSystTot"],
        ["gRaaSystYieldExtr", "gRaaSystSelEff", "gRaaSystTrEff", "gRaaSystPIDEff", "gRaaSystPtShape", "gRaaSystFD",
         "gRaaSystNorm", "gRaaSystTot"]]

    name_outgraphs = ["gRpPbSystYieldExtr", "gRpPbSystSelEff", "gRpPbSystTrEff", "gRpPbSystPIDEff", "gRpPbSystPtShape",
                      "gRpPbSystFD", "gRpPbSystNorm", "gRpPbSystTotWoNorm"]

    title_axis = ";#it{p}_{T} (GeV/#it{c}); R_{pPb}"
    g_syst = {}
    for name in name_outgraphs:
        g_syst[name] = TGraphErrors(1)
        g_syst[name].SetName(name)
        g_syst[name].SetTitle(title_axis)

    files, histos = [], []
    for (name_infile, name_histo) in zip(name_infiles, name_histos):
        files.append(TFile.Open(name_infile))
        histos.append(files[-1].Get(name_histo))

    # perform weighted average of histograms
    name_func = "weighted_sum"

    htot = histos[0].Clone()
    htot.SetTitle(title_axis)

    n_bins = htot.GetXaxis().GetNbins()

    for i_pt in range(n_bins):

        values, errors, coefs = [], [], []

        for histo in histos:
            values.append(histo.GetBinContent(i_pt+1))
            errors.append(histo.GetBinError(i_pt+1))
            coefs.append((values[-1] / errors[-1])**2)

        unc_statistical = UncertaintyPropagator(values, errors, None, name_func, coefs)

        ytot = unc_statistical.get_mean()
        htot.SetBinContent(i_pt+1, ytot)
        htot.SetBinError(i_pt+1, unc_statistical.get_std_dev())

        xtot, err_xtot = 0, 0
        err2_ytot = 0
        for i, (name_ingraph0, name_ingraph1, name_outgraph) in enumerate(
                zip(name_ingraphs[0][:-1], name_ingraphs[1][:-1], name_outgraphs[:-1])):
            if "Norm" in name_ingraph0 and i_pt > 0:
                continue
            graph0 = files[0].Get(name_ingraph0)
            graph1 = files[1].Get(name_ingraph1)
            if i == 0:
                xtot, err_xtot = graph0.GetPointX(i_pt), graph0.GetErrorX(i_pt)

            y0, err_y0 = graph0.GetPointY(i_pt), graph0.GetErrorY(i_pt)
            y1, err_y1 = graph1.GetPointX(i_pt), graph1.GetErrorY(i_pt)

            if err_y0 * err_y1 == 0:
                y = y0
                err_y = 0
            else:
                coefs = [(y0 / err_y0)**2, (y1 / err_y1)**2]
                correlation = [0]
                is_sigma_rel = False
                if "TrEff" in name_ingraph0:
                    correlation = [1]
                if "Norm" in name_ingraph0:
                    correlation = [1]
                    is_sigma_rel = True

                propagator = UncertaintyPropagator([y0, y1], [err_y0, err_y1], correlation, name_func, coefs,
                                                   is_sigma_rel)

                err_y = propagator.get_std_dev()

                if "Norm" not in name_ingraph0:  # we do not include Norm systematics
                    err2_ytot += err_y**2

            if "Norm" not in name_ingraph0:
                g_syst[name_outgraph].SetPoint(i_pt, xtot, ytot)
                g_syst[name_outgraph].SetPointError(i_pt, err_xtot, err_y)
            else:
                g_syst[name_outgraph].SetPoint(i_pt, xtot, 1.)
                g_syst[name_outgraph].SetPointError(i_pt, err_xtot, err_y)

        for name_outgraph in [name_outgraphs[-1]]:
            g_syst[name_outgraph].SetPoint(i_pt, xtot, ytot)
            g_syst[name_outgraph].SetPointError(i_pt, err_xtot, np.sqrt(err2_ytot))

    outfile = TFile(name_outfile, "recreate")

    htot.Write()
    for _, graph in g_syst.items():
        graph.Write()

    outfile.Close()


if __name__ == "__main__":
    main()
