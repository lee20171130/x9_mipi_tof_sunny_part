#!/bin/bash

use_mono()
{
    cp input_mono.bin input_RawData_all_0.bin
}

use_dual()
{
    cp input_dual.bin input_RawData_all_0.bin
}

choice=
echo -e "\n--------------choose input data mono or dual frequence-------
              *0) mono
               1) dual

           Please enter your choice[0]:\c"

read choice

case "$choice" in
     0 | "") echo "use mono frequence input data"
      use_mono
     ;; 

     1) echo "use dual frequence input data"
      use_dual
      ;;

     *) echo "nothing is done"
      ;;
esac
