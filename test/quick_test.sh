#!/bin/bash
../bin/proj test_input.pnm real_output.pnm
if diff real_output.pnm test_output.pnm; then
	echo File Match Success
else
	echo File Match Fail
fi
if diff ../log/checksum test_checksum; then
	echo Checksum Match Success
else
	echo Checksum Match Fail
fi
rm ../log/checksum
rm ../log/log_file
rm real_output.pnm
