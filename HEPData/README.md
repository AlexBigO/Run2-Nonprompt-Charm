# HEP data preparation

## hepdata_lib version
Careful (!), one should use a modified version of *hepdata_lib* allowing to define relative uncertainties directly via Uncertainty class attribute so that our script works:
```
cd $HOME
git clone -b dev git@github.com:AlexBigO/hepdata_lib.git
pip install -e $HOME/hepdata_lib
```

## Command line
Run the command line
```
python3 produce_hep_data_files.py config_preparation.yml
```
to produce HEP data.

### Configuration
The configuration is embedded


## Validation checks
For a validation of the output:
```
#pip install --user hepdata-validator
hepdata-validate -d test_submission
```

## HEP Sandbox
Go to the [HEPSandbox](https://www.hepdata.net/record/sandbox) web page and upload the `submission.tar.gz` (output of the HEP data production script).

The latest result is [here](https://www.hepdata.net/record/sandbox/1724322379).
