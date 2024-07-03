# HEP data preparation

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