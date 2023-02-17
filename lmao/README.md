

## How To Use

To clone and run this application, you'll need [Git](https://git-scm.com). 
You then use the command git clone.

The following are the procedures our CSV program makes  after reading data from a CSV file (file), processing the data, and producing results based on command-line options.



```bash
# Clone this repository
$ git clone git@github.com:Baibhav77/CSE306.git

$ cd lmao

$ ./csv 
```


 ## Procedure

First compile code with command 
```bash
gcc main.c -o csv
```

Use your command line interface (CLI) to type the commands and get the desired output. Always remember to specify “./csv” as it is required for the code to run as environment setup.

Use "-h" as input allows users to use field name as field value .

Use “-f” as input to find the number of fields in the csv file.

Use “-r” as input to find the number of rows in the csv file .

Use “-max [FIELD]”  to Display the maximum value in the indicated field of the data records.

Use “-min [FIELD]”  to Display the minimum value in the indicated field of the data records.

Use “-means” to display the mean value of the field. It only works if there is a number only in the field.

Use “-records FIELD VALUE” as input to display the row that contain the indicated value in that indicated field

```bash
For Eg. “./csv -min 0 05020004-eng.csv” can be refer as “./csv -h -min "Ref_Date" 05020004-eng.csv” using “ -h”
```




