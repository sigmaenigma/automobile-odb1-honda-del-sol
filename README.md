# OBD1 Data Reader for 1994 Honda Del Sol

This repository contains a proof-of-concept scripts designed to read OBD1 data from a 1994 Honda Del Sol. These scripts are not in a production state and should be used with caution.

## Description
The scripts read input from a specified GPIO pin on the Raspberry Pi or Arduino board, counts the number of blinks, and matches the count to a corresponding OBD1 code from a JSON file. The JSON file contains diagnostic trouble codes (DTCs) specific to the 1994 Honda Del Sol.
