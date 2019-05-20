# Pre-Phaser
Cell-Cycle Phase Detector for scRNA-seq

## To run Recursive Feature Selection
1. compile the cpp file: 

   g++ -std=c++11 Feature_Selection_Recursive.cpp -o Feature_Selection_Recursive

2. run the python script with the following arguments: prefix of the training dataset, desired k, maximum number of parallel jobs to launch(dependent on the system)

   python3 Feature_Selection_Recursive.py data/SC_df_z_train 10 500 > recursive_selection_log&



## To generate your own data files
