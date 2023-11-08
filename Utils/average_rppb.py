"""
file: average_rppb.py
brief: Script to average RpPb results from D0 and D+
usage: python3 average_rppb.py
author: Alexandre Bigot <alexandre.bigot@cern.ch>, Strasbourg University
"""

import numpy as np
from ROOT import TFile
from style_formatter import set_global_style
from uncertainty_handler import UncertaintyPropagator, graph_errors

ID0 = 0
ID1 = 1

kHisto, kGraph = 0, 1

TYPE_INPUT_SYST = [kGraph, kHisto]

name_fully_correlated_systematics = [
    ["TrEff", "Norm"],
    ["Tracking, Lumi"]]

name_relative_systematics = [
    ["Norm"],
    ["Lumi"]
]

name_syst_not_included_in_tot = [
    ["Norm"],
    ["Lumi"]
]


def main():
    """
    Main function
    """

    set_global_style(padleftmargin=0.14, padbottommargin=0.12, titlesize=0.045, labelsize=0.04,
                     maxdigits=3, linewidth=1)

    name_infiles = ["../Results/Dplus/RpPb_Dplus_Nonprompt.root",
                    "../Results/D0/outputRpPb_Rebin_SeparateSyst.root "]

    name_outfile = "../Results/RpPb_D0_Dplus_Nonprompt_Weighted_Average.root"

    name_histos = ["hRpPb", "RpPbFDD0"]

    name_ingraphs = [
        ["gRaaSystYieldExtr", "gRaaSystSelEff", "gRaaSystTrEff", "gRaaSystPtShape", "gRaaSystFD", "gRaaSystNorm"],
        ["SystRpPbRawyieldAbs", "SystRpPbSelectionAbs", "SystRpPbTrackingAbs", "SystRpPbPtShapeAbs",
         "SystRpPbFractionAbs", "SystRpPbLumi"]]

    name_outgraphs = ["gRpPbSystYieldExtr", "gRpPbSystSelEff", "gRpPbSystTrEff", "gRpPbSystPtShape",
                      "gRpPbSystFD", "gRpPbSystNorm", "gRpPbSystTotWoNorm"]

    title_axis = ";#it{p}_{T} (GeV/#it{c}); R_{pPb}"
    g_syst = {}
    for name in name_outgraphs:
        g_syst[name] = graph_errors(name, title_axis)

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

        i_point = i_pt
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
                zip(name_ingraphs[0], name_ingraphs[1], name_outgraphs[:-1])):

            graph0 = files[0].Get(name_ingraph0)
            graph1 = files[1].Get(name_ingraph1)
            n_points = graph0.GetN()  # graph0 is a TGraphErrors here
            if i_pt > 0 and n_points == 1:
                i_point = 0
            if i == 0:
                xtot, err_xtot = graph0.GetPointX(i_point), graph0.GetErrorX(i_point)  # ID0 is a graph               

            if TYPE_INPUT_SYST[ID0] == kGraph:
                y0, err_y0 = graph0.GetPointY(i_point), graph0.GetErrorY(i_point)
            else:
                y0, err_y0 = graph0.GetBinContent(i_point+1), graph0.GetBinError(i_point+1)
            if TYPE_INPUT_SYST[ID1] == kGraph:
                y1, err_y1 = graph1.GetPointX(i_point), graph1.GetErrorY(i_point)
            else:
                y1, err_y1 = graph1.GetBinContent(i_point+1), graph1.GetBinError(i_point+1)

            if err_y0 * err_y1 == 0:
                y = y0
                err_y = 0
            else:
                if any(name_syst in name_ingraph0 for name_syst in name_relative_systematics[ID0]):
                    err_y0 *= ytot
                if any(name_syst in name_ingraph1 for name_syst in name_relative_systematics[ID1]):
                    err_y1 *= ytot
                coefs = [(y0 / err_y0)**2, (y1 / err_y1)**2]

                correlation = [0]
                if any(name_syst in name_ingraph0 for name_syst in name_fully_correlated_systematics[ID0]):
                    correlation = [1]

                propagator = UncertaintyPropagator([y0, y1], [err_y0, err_y1], correlation, name_func, coefs)

                err_y = propagator.get_std_dev()

                if not any(name_syst in name_ingraph0 for name_syst in name_syst_not_included_in_tot[ID0]):
                    err2_ytot += err_y**2

            if i_pt == 0 and n_points == 1:
                print("hello")
                g_syst[name_outgraph].SetPoint(i_pt, xtot, 1.)
                g_syst[name_outgraph].SetPointError(i_pt, err_xtot, err_y / ytot)
            elif n_points > 1:
                g_syst[name_outgraph].SetPoint(i_pt, xtot, ytot)
                g_syst[name_outgraph].SetPointError(i_pt, err_xtot, err_y)

        for name_outgraph in name_outgraphs:
            if "Tot" not in name_outgraph:
                continue
            g_syst[name_outgraph].SetPoint(i_pt, xtot, ytot)
            g_syst[name_outgraph].SetPointError(i_pt, err_xtot, np.sqrt(err2_ytot))

    outfile = TFile(name_outfile, "recreate")

    htot.Write()
    for _, graph in g_syst.items():
        graph.Write()

    outfile.Close()


if __name__ == "__main__":
    main()
