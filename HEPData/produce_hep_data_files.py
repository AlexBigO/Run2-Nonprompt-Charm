"""
file: produce_hep_data_files.py
brief: script for production of HEPData
usage: python3 produce_hep_data_files.py CONFIG
author: Alexandre Bigot <alexandre.bigot@cern.ch>, Strasbourg University
"""
import argparse
# pylint: disable=anomalous-backslash-in-string
import collections

import yaml
from hepdata_lib import (RootFileReader, Submission, Table, Uncertainty,
                         Variable)
from yaml.representer import Representer

yaml.add_representer(collections.defaultdict, Representer.represent_dict)


# pylint: disable=too-many-locals
def make_table(cfg):
    """
    Helper method to make and configure a Table instance

    Parameter
    -----------------
    - cfg: dictionary with config for the wanted Table

    Returns
    -----------------
    - table: configured Table instance
    """

    table_number = cfg["table_number"]
    figure_number_in_article = cfg["figure_number_in_article"]

    name_infile = cfg["input"]["file"]
    name_hist = cfg["input"]["hist"]
    name_graph = cfg["input"]["graph"]
    symbol = cfg["input"]["symbol"]
    position_panel = cfg["input"]["position_panel"]

    file_reader = RootFileReader(name_infile)
    data_stat = file_reader.read_hist_1d(name_hist)
    data_syst = file_reader.read_graph(name_graph)

    table = Table(f"Table {table_number}")
    table.location = f"Data from Figure {figure_number_in_article}, {position_panel} panel ({symbol})"
    table.description = cfg["description"]
    table.keywords["observables"] = [cfg["keywords"]["observables"]]
    if cfg["keywords"]["phrases"] is not None:
        table.keywords["phrases"] = cfg["keywords"]["phrases"]
    table.keywords["reactions"] = cfg["keywords"]["reactions"]
    table.keywords["cmenergies"] = [cfg["keywords"]["cmenergies"]]

    x_variable = Variable(cfg["variables"]["x_axis"]["name"],
                          is_independent=True,
                          is_binned=True,
                          units=cfg["variables"]["x_axis"]["units"],
                          values=data_stat["x_edges"])
    data = Variable(cfg["variables"]["data"]["name"],
                    is_independent=False,
                    is_binned=False,
                    units=cfg["variables"]["data"]["units"],
                    values=data_stat["y"])
    for reaction in cfg["qualifier"]["reaction"]:
        data.add_qualifier("REACTION", reaction)
    data.add_qualifier("SQRT(S)/NUCLEON", cfg["qualifier"]["energy"], "GEV")
    data.add_qualifier("YRAP", f"{cfg['qualifier']['rapidity'][0]} TO {cfg['qualifier']['rapidity'][1]}")

    # statistical uncertainties
    data_stat_unc = Uncertainty("stat", is_symmetric=True)
    data_stat_unc.values = data_stat['dy']
    # add statistical uncertainties to data Variable instance
    data.add_uncertainty(data_stat_unc)

    # systematic uncertainties
    data_syst_unc = Uncertainty("sys", is_symmetric=False)
    try:
        data_syst_unc.values = data_syst["dy"]
    except TypeError:
        data_syst_unc.is_symmetric = True
        data_syst_unc.values = data_syst["dy"]
    # add systematic uncertainties to data Variable instance
    data.add_uncertainty(data_syst_unc)

    if cfg["systematics"]["br"] is not None:
        br_syst_unc = Uncertainty("sys, uncertainty on branching ratio", is_symmetric=True, is_relative=True)
        br_syst_unc.values = [
            cfg["systematics"]["br"]["unc"] / cfg["systematics"]["br"]["value"] * 100] * len(data_stat["y"])
        data.add_uncertainty(br_syst_unc)

    if cfg["systematics"]["lumi"] is not None:
        lumi_syst_unc = Uncertainty("sys, uncertainty on luminosity", is_symmetric=True, is_relative=True)
        lumi_syst_unc.values = [cfg["systematics"]["lumi"] * 100] * len(data_stat["y"])
        data.add_uncertainty(lumi_syst_unc)
        
    if cfg["systematics"]["extrapolation"] is not None:
    		extr_syst_unc = Uncertainty("sys, uncertainty on extrapolation", is_symmetric=False)
    		extr_syst_unc.values = [ cfg["systematics"]["extrapolation"] ] * len(data_stat["y"])
    		data.add_uncertainty(extr_syst_unc)

    # add variables to Table instance
    table.add_variable(x_variable)
    table.add_variable(data)

    return table


def main(cfg_input):
    """
    Main method

    Parameters
    -----------------
    - config: dictionary with config read from a yaml file
    """

    name_tables = []
    for key in cfg_input:
        if "Table" in key:
            name_tables.append(key)

    # create Submission instance
    submission = Submission()
    submission.read_abstract(cfg_input["abstract_file"])
    submission.get_license()

    print("Producing HEP data: ...", end="\r")
    for name_table in name_tables:
        submission.add_table(make_table(cfg_input[name_table]))

    # produce output files
    submission.create_files("./test_submission")
    print("Producing HEP data: Done!")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Arguments")
    parser.add_argument("config", metavar="text", default="config.yml", help="config file name for ml")
    args = parser.parse_args()

    print("Loading configuration: ...", end="\r")
    with open(args.config, "r", encoding="utf-8") as yml_cfg:
        configuration = yaml.load(yml_cfg, yaml.FullLoader)
    print("Loading configuration: Done!")

    main(configuration)
