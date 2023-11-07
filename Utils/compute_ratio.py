"""
file: compute_ratio.py
brief: Script to compute ratio of prodcution cross sections
usage: python3 compute_ratio.py config_compute_ratio.json
author: Alexandre Bigot <alexandre.bigot@cern.ch>, Strasbourg University
"""

import argparse
import numpy as np
import json
import sys

from ROOT import TFile
from style_formatter import set_global_style
from uncertainty_handler import UncertaintyPropagator, graph_errors
from analysis_utils import compute_ratio_diff_bins

ID_NUM = 0
ID_DENOM = 1

LABEL_TOTAL_SYST = "Tot"
LABEL_BR_SYST = "BR"

NAME_FUNC = "weighted_product"  # name of function for uncertainty propagation
COEFS = [+1, -1]  # ratio of num / denom


def log_removed_points(n_points_removed, name_graph_num, name_graph_denom, flag=0):
    """
    Helper method to print log message when removing points from TGraphErros with incompatible x axis

    Parameters
    ------------------------------------------------
    n_points_removed: int
        Number of points removed

    name_graph_num: str
        Name of graph in numerator

    name_graph_denom: str
        Name of graph in denominator

    flag: int
        Flag to distinguish cases
    """

    if flag == 0:
        if n_points_removed == 1:
            print(f"\033[93mWARNING: different number of points in TGraphErrors. {n_points_removed} point removed to "
                  f"match {name_graph_num} (numerator) and {name_graph_denom} (denominator) x ranges.\n\033[0m")
        elif n_points_removed > 1:
            print(f"\033[93mWARNING: different number of points in TGraphErrors. {n_points_removed} points removed to "
                  f"match {name_graph_num} (numerator) "
                  f"and {name_graph_denom} (denominator) x ranges.\n\033[0m")
    elif flag == 1:
        print(f"\033[93mWARNING: {name_graph_num} (numerator) contains a single point. "
              f"We only keep the first point in {name_graph_denom} (denominator).\n\033[0m")
    else:
        print(f"\033[93mWARNING: {name_graph_denom} (denominator) contains a single point. "
              f"We only keep the first point in {name_graph_num} (numerator).\n\033[0m")


# pylint:disable=too-many-locals
def check_graph_errors_x_range_compatibility(graphs_num, graphs_denom, name_relative_systematics):
    """
    Helper method ...

    Parameters
    ------------------------------------------------
    graphs_num: list
        List of TGraphErrors in numerator

    graphs_denom: list
        List of TGraphErrors in denominator

    Outputs
    ------------------------------------------------
    name_relative_systematics: list
        Updated list of graph names containing relative systematics
    """

    for (graph_num, graph_denom) in zip(graphs_num, graphs_denom):
        n_num = graph_num.GetN()
        n_denom = graph_denom.GetN()
        n_points_removed = 0
        if n_num != n_denom:
            if n_num == 1:
                log_removed_points(n_points_removed, graph_num.GetName(), graph_denom.GetName(), 1)
                x, err_x = graph_num.GetPointX(0), graph_num.GetErrorX(0)
                y, err_y = graph_denom.GetPointY(0), graph_denom.GetErrorY(0)
                for _ in range(n_denom):
                    graph_denom.RemovePoint(0)
                graph_denom.SetPoint(0, x, graph_num.GetPointY(0))
                graph_denom.SetPointError(0, err_x, err_y / y)
                name_relative_systematics[ID_DENOM].append(graph_denom.GetName())
                continue
            if n_denom == 1:
                log_removed_points(n_points_removed, graph_num.GetName(), graph_denom.GetName(), 2)
                x, err_x = graph_denom.GetPointX(0), graph_denom.GetErrorX(0)
                y, err_y = graph_num.GetPointY(0), graph_num.GetErrorY(0)
                for _ in range(n_num):
                    graph_num.RemovePoint(0)
                graph_num.SetPoint(0, x, graph_denom.GetPointY(0))
                graph_num.SetPointError(0, err_x, err_y / y)
                name_relative_systematics[ID_NUM].append(graph_num.GetName())
                continue
            remove_points = True
            while remove_points:
                xmin_num, xmax_num = graph_num.GetPointX(0), graph_num.GetPointX(n_num-1)
                xmin_denom, xmax_denom = graph_denom.GetPointX(0), graph_denom.GetPointX(n_denom-1)

                if xmin_num < xmin_denom:
                    graph_num.RemovePoint(0)
                elif xmin_num > xmin_denom:
                    graph_denom.RemovePoint(0)

                if xmax_num > xmax_denom:
                    graph_num.RemovePoint(n_num-1)
                elif xmax_num < xmax_denom:
                    graph_denom.RemovePoint(n_denom-1)

                n_points_removed += 1
                if graph_num.GetN() == graph_denom.GetN():
                    remove_points = False
        log_removed_points(n_points_removed, graph_num.GetName(), graph_denom.GetName())

    return name_relative_systematics


# pylint:disable=too-many-locals,too-many-branches,too-many-statements
def main(cfg):
    """
    Main function

    Parameters
    ------------------------------------------------
    - config: dictionary with config read from a json file
    """

    set_global_style(padleftmargin=0.14, padbottommargin=0.12, titlesize=0.045, labelsize=0.04,
                     maxdigits=3, linewidth=1)

    # load configuration
    name_infiles = cfg["input"]["name_files"]
    name_histos = cfg["input"]["name_histos"]
    name_graph_errors = cfg["input"]["name_graph_errors"]
    # name_graph_errors_denom = cfg["input"]["name_graph_errors_denom"]
    name_outfile = cfg["output"]["name_file"]

    name_outhisto = cfg["output"]["histo"]["name"]
    title_outhisto = cfg["output"]["histo"]["title"]
    name_outgraphs = cfg["output"]["graph_errors"]["names"]
    title_outgraph = cfg["output"]["graph_errors"]["title"]

    name_fully_correlated_systematics = cfg["systematics"]["fully_correlated"]
    name_relative_systematics = cfg["systematics"]["relative"]
    name_syst_not_included_in_tot = cfg["systematics"]["not_included_in_tot"]

    # load input
    histos, graphs_num, graphs_denom = [], [], []
    for i, (name_infile, name_histo, name_graphs) in enumerate(zip(
            name_infiles, name_histos, name_graph_errors)):
        infile = TFile(name_infile)
        histos.append(infile.Get(name_histo))
        histos[-1].SetDirectory(0)
        for name_graph in name_graphs:
            if i == ID_NUM:  # numerator
                graphs_num.append(infile.Get(name_graph))
            else:  # denominator
                graphs_denom.append(infile.Get(name_graph))

    # safety
    if len(graphs_num) != len(graphs_denom):
        print("\033[91mERROR: different number of TGraphErrors in numerator and denominator!\033[0m")
        sys.exit(0)

    # check if there is already a graph for BR systematics in numerator, add it if not there
    if not any("BR" in name for name in name_graph_errors[ID_NUM]):
        g_br = graph_errors("RelSystBR", title_outgraph)
        g_br.SetPoint(0, 0.5, 1)
        g_br.SetPointError(0, 0.3, cfg["input"]["cross_section"]["branching_ratios_syst"][ID_NUM])
        graphs_num.append(g_br)
        name_relative_systematics[ID_NUM].append(LABEL_BR_SYST)
    # check if there is already a graph for BR systematics in denominator, add it if not there
    if not any("BR" in name for name in name_graph_errors[ID_DENOM]):
        g_br = graph_errors("RelSyst"+LABEL_BR_SYST, title_outgraph)
        g_br.SetPoint(0, 0.5, 1)
        g_br.SetPointError(0, 0.3, cfg["input"]["cross_section"]["branching_ratios_syst"][ID_DENOM])
        graphs_denom.append(g_br)
        name_relative_systematics[ID_DENOM].append(LABEL_BR_SYST)

    name_outgraphs.append(cfg["output"]["graph_errors"]["name_branching_ratio"])

    name_relative_systematics = check_graph_errors_x_range_compatibility(
        graphs_num, graphs_denom, name_relative_systematics)

    # if sigma x BR is in input
    if cfg["input"]["cross_section"]["contains_branching_ratio"]:
        branching_ratios = cfg["input"]["cross_section"]["branching_ratios"]

        for histo, br in zip(histos, branching_ratios):
            histo.Scale(1./br)
        for (graph_num, graph_denom) in zip(graphs_num, graphs_denom):
            if not any(name_syst in graph_num.GetName() for name_syst in name_relative_systematics[ID_NUM]):
                graph_num.Scale(1./branching_ratios[ID_NUM])
            if not any(name_syst in graph_denom.GetName() for name_syst in name_relative_systematics[ID_DENOM]):
                graph_denom.Scale(1./branching_ratios[ID_DENOM])

    # define output quantities
    h_ratio = compute_ratio_diff_bins(histos[ID_NUM], histos[ID_DENOM])
    h_ratio.SetName(name_outhisto)
    h_ratio.SetTitle(title_outhisto)

    g_ratios = []
    for name_outgraph in name_outgraphs:
        g_ratio = graph_errors(name_outgraph, title_outgraph)
        g_ratios.append(g_ratio)

    g_ratios.append(graph_errors("gRatioSyst"+LABEL_TOTAL_SYST+"Wo"+"".join(name_syst_not_included_in_tot),
                                 title_outgraph))

    for i_pt in range(h_ratio.GetXaxis().GetNbins()):
        i_point = i_pt
        y_ratio = h_ratio.GetBinContent(i_pt+1)
        x_ratio, err_x_ratio = 0, 0
        err2_y_tot = 0
        for i_graph, (graph_num, graph_denom) in enumerate(zip(graphs_num, graphs_denom)):
            name_graph = graph_num.GetName()
            n_points = graph_num.GetN()
            if LABEL_TOTAL_SYST in name_graph:
                continue
            if i_pt > 0 and n_points == 1:
                i_point = 0

            # retrieve x axis information (once per pT bin)
            if i_graph == 0:
                x_ratio, err_x_ratio = graph_num.GetPointX(i_point), graph_num.GetErrorX(i_point)

            y_num, err_y_num = graph_num.GetPointY(i_point), graph_num.GetErrorY(i_point)
            y_denom, err_y_denom = graph_denom.GetPointY(i_point), graph_denom.GetErrorY(i_point)

            correlation = [0]

            if any(name_syst in name_graph for name_syst in name_fully_correlated_systematics):
                correlation = [1]
            # make uncertainties absolute if relative
            if any(name_syst in name_graph for name_syst in name_relative_systematics[ID_NUM]):
                err_y_num *= y_ratio
            if any(name_syst in graph_denom.GetName() for name_syst in name_relative_systematics[ID_DENOM]):
                err_y_denom *= y_ratio

            # propagate uncertainties
            propagator = UncertaintyPropagator(
                [y_num, y_denom],
                [err_y_num, err_y_denom],
                correlation,
                NAME_FUNC,
                COEFS)

            err_y_ratio = propagator.get_std_dev()

            # do not include the chosen systematics in the total count
            if not any(name_syst in name_graph for name_syst in name_syst_not_included_in_tot):
                err2_y_tot += err_y_ratio**2

            if i_pt == 0 and n_points == 1:
                g_ratios[i_graph].SetPoint(i_pt, x_ratio, 1.)
                g_ratios[i_graph].SetPointError(i_pt, err_x_ratio, err_y_ratio / y_ratio)
            elif n_points > 1:
                g_ratios[i_graph].SetPoint(i_pt, x_ratio, y_ratio)
                g_ratios[i_graph].SetPointError(i_pt, err_x_ratio, err_y_ratio)

        for graph in g_ratios:
            if LABEL_TOTAL_SYST not in graph.GetName():
                continue
            graph.SetPoint(i_pt, x_ratio, y_ratio)
            graph.SetPointError(i_pt, err_x_ratio, np.sqrt(err2_y_tot))

    outfile = TFile(name_outfile, cfg["output"]["option_file"])
    h_ratio.Write()
    for graph in g_ratios:
        graph.Write()
    outfile.Close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Arguments")
    parser.add_argument(
        "config",
        metavar="text",
        default="config_cutvar_example.json",
        help="JSON config file",
    )
    args = parser.parse_args()

    with open(args.config, encoding="utf8") as file:
        config = json.load(file)

    main(config)
