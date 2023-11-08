"""
file: plot.py
brief: Script to plot mean values and systematics (production cross section, nuclear modification factor)
usage: ???
author: Alexandre Bigot <alexandre.bigot@cern.ch>, Strasbourg University
"""

import argparse
import json
import sys

from ROOT import TCanvas, TFile, TLatex, TLegend, kAzure, kBlack, kFullCircle
sys.path.append('..')
from Utils.style_formatter import set_global_style, set_object_style


# pylint:disable=too-many-locals
def main(cfg):
    """
    Main function

    Parameters
    ------------------------------------------------
    - config: dictionary with config read from a json file
    """

    set_global_style(padleftmargin=0.12, padbottommargin=0.12, padtopmargin=0.05, titlesize=0.045, labelsize=0.04,
                     maxdigits=3)

    # load configuration
    name_infiles = cfg["input"]["name_files"]
    name_mean_objects = cfg["input"]["name_mean_objects"]
    name_syst_objects = cfg["input"]["name_syst_objects"]
    name_outfile = cfg["output"]["name_file"]

    # plot options
    width_canvas = cfg["plot_options"]["canvas"]["width"]
    height_canvas = cfg["plot_options"]["canvas"]["height"]
    title_xaxis = cfg["plot_options"]["canvas"]["title_xaxis"]
    title_yaxis = cfg["plot_options"]["canvas"]["title_yaxis"]
    title = ";" + title_xaxis + ";" + title_yaxis
    xlimits = cfg["plot_options"]["canvas"]["xlimits"]
    ylimits = cfg["plot_options"]["canvas"]["ylimits"]
    logx = cfg["plot_options"]["canvas"]["logx"]
    logy = cfg["plot_options"]["canvas"]["logy"]

    # define canvas
    c = TCanvas("c", "", width_canvas, height_canvas)
    c.DrawFrame(xlimits[0], ylimits[0], xlimits[-1], ylimits[-1], title)
    if logx:
        c.SetLogx()
    if logy:
        c.SetLogy()

    # define legend
    show_legend = cfg["plot_options"]["legend"]["show"]
    xlimits_legend = cfg["plot_options"]["legend"]["xlimits"]
    ylimits_legend = cfg["plot_options"]["legend"]["ylimits"]
    leg = TLegend(xlimits_legend[0], ylimits_legend[0], xlimits_legend[-1], ylimits_legend[-1])
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)
    leg.SetTextSize(cfg["plot_options"]["legend"]["size_text"])
    titles_legend = cfg["plot_options"]["legend"]["titles"]
    option_legend = cfg["plot_options"]["legend"]["options"]

    # import files
    files, mean_objects, syst_objects = [], [], []
    for i, (name_infile, name_mean_object, name_syst_object) in enumerate(
            zip(name_infiles, name_mean_objects, name_syst_objects)):
        files.append(TFile(name_infile))
        mean_objects.append(files[-1].Get(name_mean_object))
        syst_objects.append(files[-1].Get(name_syst_object))
        if show_legend:
            leg.AddEntry(mean_objects[-1], titles_legend[i], option_legend[i])

    # format style
    set_object_style(mean_objects[0], color=kAzure+4, markercolo=kAzure+4, markerstyle=kFullCircle)
    set_object_style(syst_objects[0], linecolor=kAzure+4, fillstyle=0)
    mean_objects[0].DrawCopy("psame")

    syst_objects[0].Draw("2")
    if show_legend:
        leg.Draw("same")

    # ALICE header
    latex = TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.04)
    latex.SetTextAlign(13)  # align at top
    latex.SetTextFont(42)
    entries_latex = cfg["plot_options"]["latex"]["entry"]
    x_top = cfg["plot_options"]["latex"]["x_top"]
    y_top = cfg["plot_options"]["latex"]["y_top"]
    for (x, y, entry) in zip(x_top, y_top, entries_latex):
        latex.DrawLatex(x, y, entry)

    # save canvas
    outfile = TFile(name_outfile, cfg["output"]["option_file"])
    c.Write()
    outfile.Close()

    for ext in cfg["output"]["extension"]:
        name_outcanvas = name_outfile.replace(".root", "."+ext)
        c.SaveAs(name_outcanvas)


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
