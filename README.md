# Image Filter Dataflow
C++ image processing framework with various pre-constructed filters. Based on dataflow architecture principles.
Currently only works with PNM files, but you can use this tool along side the many available conversion tools.

## Installation
run `make` from root directory

## Running
call executable with names of source and destination file.
example:
```
$ bin/proj test/test_input.pnm output_file.pnm
```
this will create a file called output_file.pnm that will contain the processes image
