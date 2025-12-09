#/bin/bash

make ALG=kyber_ref KYBER_K = 2

nrfutil device program --firmware build/m33_kyber_ref.bin
python3 
