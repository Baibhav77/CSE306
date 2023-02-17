The following are the procedures our CSV program makes  after reading data from a CSV file (file), processing the data, and producing results based on command-line options.

Procedure:

i)First compile code with command “gcc main.c -o csv”

ii) use your command line interface (CLI) to type the commands and get the desired output.

iii) Always remember to specify “./csv” as it is required for the code to run.

iv) Use the following command-line arguments to produce specific results:

 a)  "-h" as input allows users to use field name as field value .
      For Eg. “./csv -min 0 05020004-eng.csv” can be refer as “./csv -h -min "Ref_Date" 05020004-eng.csv” using “ -h”
 b)  use “-f” as input to find the number of fields in the csv file 
 c) use “-r” as input to find the number of rows in the csv file 
 d) Use “-max [[FIELD]]”  to Display the maximum value in the indicated field of the data records
 e) Use “-min [[FIELD]]”  to Display the minimum value in the indicated field of the data records
 f) Use “-means” to display the mean value of the field. It only works if there is a number only in the field.

dd

