# Pre-Phaser
Cell-Cycle Phase Detector for scRNA-seq

## To run Recursive Feature Selection for coarse prediction
1. compile the cpp file: 

   g++ -std=c++11 Feature_Selection_Recursive.cpp -o Feature_Selection_Recursive

2. run the python script with the following arguments: prefix of the training dataset, desired k, maximum number of parallel jobs to launch(dependent on the system), output file

   python3 Feature_Selection_Recursive.py data/SC_df_z_train 10 500 data/recursive_selection_log&


## To run coarse classification and get accuracies and f1 scores
1. compile the cpp file:

   g++ -std=c++11 Generic_Evaluate_Selected_Features_On_Test.cpp -o Generic_Evaluate_Selected_Features_On_Test 

2. run the python script with the following arguments: prefix of the traing dataset, prefix of the test dataset, desired k, use_selection (yes/no), if yes, name of the file with genes to use

   python3 Generic_Evaluate_Selected_Features_On_Test.py data/SC_df_z_train data/SC_df_z_test 10 yes data/recursive_selection_sample_output

   python3 Generic_Evaluate_Selected_Features_On_Test.py data/SC_df_z_train data/SC_df_z_test 10 no 


## To run Recursive Feature Selection for precise prediction
1. compile the cpp file

   g++ -std=c++11 Precise_Feature_Selection_Recursive.cpp -o Precise_Feature_Selection_Recursive

2. run the python script with the following arguments: prefix of the training dataset, desired k, maximum number of parallel jobs to launch(dependent on the system), output file

   python3 Precise_Feature_Selection_Recursive.py data/microarray_leg_test 2 500 data/precise_recursive_selection_log&


## To run coarse classification and get accuracies and f1 scores
1. compile the cpp file:

   g++ -std=c++11 Precise_Evaluate_Selected_Features_On_Test.cpp -o Precise_Evaluate_Selected_Features_On_Test 

2. run the python script with the following arguments: prefix of the traing dataset, prefix of the test dataset, desired k, use_selection (yes/no), if yes, name of the file with genes to use

   python3 Precise_Evaluate_Selected_Features_On_Test.py data/microarray_leg_test data/SC_df_z_test 2 yes data/recursive_selection_precise_sample_output

   python3 Precise_Evaluate_Selected_Features_On_Test.py data/microarray_leg_test data/SC_df_z_test 2 no 


## Data Format: To generate your own data files
