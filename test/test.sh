#!/usr/bin/env bash
if [ -z "$CXX" ]; then
	CXX="g++"
fi
mkdir -p "bin"
mkdir -p "obj"
make all
mkdir -p "output"
file_names=($(ls -d *.cpp))
exit_code=0
for i in "${!file_names[@]}"
do
	file_name="${file_names[i]}"
	short_name="${file_name%.*}"
	obj_path="bin/${short_name[0]}"
	output_path="output/${short_name}.temp"
	run_cmd="./${obj_path} > ${output_path}"
	echo $run_cmd
	eval $run_cmd
	standard_path="standard/${short_name}.result"
	result=$(diff -q "${output_path}" "${standard_path}")
	if [ "${#result}" -gt 0 ]; then
		exit_code=1
		echo -e "\033[1;31mERROR!!!\033[0m"
		echo "Actual:"
		IFS=$"\n"
		for line in $(cat "${output_path}")
		do
			echo $line
		done
		echo ""
		echo "Expect:"
		for line in $(cat "${standard_path}")
		do
			echo $line
		done
	else
		echo -e "\033[1;32mCorrect\033[0m"
	fi
	echo ""
done
if [ "${exit_code}" -ne 0 ]; then
	echo -e "\033[1;31mFailed\033[0m"
else
	echo -e "\033[1;32mSuccess\033[0m"
fi
exit $exit_code

