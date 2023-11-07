"""
file: analysis_utils.py
brief: Module with utils for analysis
author: Alexandre Bigot <alexandre.bigot@cern.ch>, Strasbourg University
"""

import numpy as np
from ROOT import TH1F


# pylint:disable=too-many-locals,too-many-branches
def compute_ratio_diff_bins(h_num, h_denom, opt_unc=''):
    '''
    Method to compute ratio between histograms with different bins (but compatible)

    Parameters
    ----------
    - h_num: histogram for numerator
    - h_denom: histogram for denominator
    - opt_unc: uncertainty option as in ROOT.TH1.Divide

    Returns
    ----------
    - h_ratio: ratio histogram
    '''

    pt_min_num = h_num.GetBinLowEdge(1)
    pt_max_num = h_num.GetXaxis().GetBinUpEdge(h_num.GetNbinsX())
    pt_min_denom = h_denom.GetBinLowEdge(1)
    pt_max_denom = h_denom.GetXaxis().GetBinUpEdge(h_denom.GetNbinsX())
    if pt_min_num < pt_min_denom:
        pt_min = pt_min_denom
    else:
        pt_min = pt_min_num
    if pt_max_num > pt_max_denom:
        pt_max = pt_max_denom
    else:
        pt_max = pt_max_num

    if h_num.GetNbinsX() < h_denom.GetNbinsX():
        if np.array(h_num.GetXaxis().GetXbins(), 'd').any():  # variable binning
            pt_lims_ratio = np.array(h_num.GetXaxis().GetXbins(), 'd')
        else:  # constant binning
            width_bin = h_num.GetBinWidth(1)
            pt_lims_ratio = np.array([pt_min_denom + i_bin * width_bin for i_bin in range(h_num.GetNbinsX()+1)], 'd')
    else:
        if np.array(h_denom.GetXaxis().GetXbins(), 'd').any():  # variable binning
            pt_lims_ratio = np.array(h_denom.GetXaxis().GetXbins(), 'd')
        else:  # constant binning
            width_bin = h_denom.GetBinWidth(1)
            pt_lims_ratio = np.array([pt_min_denom + i_bin * width_bin for i_bin in range(h_denom.GetNbinsX()+1)], 'd')
    pt_lims_ratio = pt_lims_ratio[(pt_lims_ratio >= pt_min) & (pt_lims_ratio <= pt_max)]
    n_pt_bins = len(pt_lims_ratio) - 1

    h_ratio = TH1F('hRatio', f';{h_num.GetXaxis().GetTitle()};ratio', n_pt_bins, pt_lims_ratio)
    h_num_reb = TH1F('hNumReb', '', n_pt_bins, pt_lims_ratio)
    h_denom_reb = TH1F('hDenomReb', '', n_pt_bins, pt_lims_ratio)

    for i_pt_ratio in range(1, h_ratio.GetNbinsX()+1):
        delta_pt = pt_lims_ratio[i_pt_ratio]-pt_lims_ratio[i_pt_ratio-1]
        num, unc_num, den, unc_denom = (0 for _ in range(4))
        for i_pt_num in range(1, h_num.GetNbinsX()+1):
            if h_num.GetBinLowEdge(i_pt_num) >= pt_lims_ratio[i_pt_ratio-1] and \
                    h_num.GetXaxis().GetBinUpEdge(i_pt_num) <= pt_lims_ratio[i_pt_ratio]:
                num += h_num.GetBinContent(i_pt_num) * h_num.GetBinWidth(i_pt_num)
                unc_num += h_num.GetBinError(i_pt_num)**2 * h_num.GetBinWidth(i_pt_num)**2  # considered uncorrelated
        h_num_reb.SetBinContent(i_pt_ratio, num/delta_pt)
        h_num_reb.SetBinError(i_pt_ratio, np.sqrt(unc_num)/delta_pt)
        for i_pt_denom in range(1, h_denom.GetNbinsX()+1):
            if h_denom.GetBinLowEdge(i_pt_denom) >= pt_lims_ratio[i_pt_ratio-1] and \
                    h_denom.GetXaxis().GetBinUpEdge(i_pt_denom) <= pt_lims_ratio[i_pt_ratio]:
                den += h_denom.GetBinContent(i_pt_denom) * h_denom.GetBinWidth(i_pt_denom)
                # considered uncorrelated
                unc_denom += h_denom.GetBinError(i_pt_denom)**2 * h_denom.GetBinWidth(i_pt_denom)**2
        h_denom_reb.SetBinContent(i_pt_ratio, den/delta_pt)
        h_denom_reb.SetBinError(i_pt_ratio, np.sqrt(unc_denom)/delta_pt)

    h_ratio.Divide(h_num_reb, h_denom_reb, 1., 1., opt_unc)

    return h_ratio
