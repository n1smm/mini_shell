#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
NC='\033[0m'

infile=$1
#limit=$2
limit=$(echo "$2" | tr -cd '[:print:]')
firstComm=$3
outfile=${!#}
newInFile="${infile}.tmp"
newOutFile="${outfile}.tmp"
myErrFile="${infile}.err"
origErrFile="${outfile}.err"
touch $newOutFile 
touch $newInFile
orig_args=("$@")
shift

args=("$@")   #"${@:1:$#-1}"
len=${#args[@]}
COMMAND="./pipex_bonus"

	###printing output of pipex ###
your_output="$($COMMAND $infile "$@" 2> "$myErrFile")"
echo -e "${GREEN}your output:${NC}"
cat ${!#}
echo -e ""
echo -e "${RED}your std_err:${NC}"
cat "$myErrFile"
if [ -s "$myErrFile" ];then
	echo -e ""
else
	echo -e "${YELLOW}there is no error message${NC}\n"
fi

	###printing output of terminal commands ###
if [ "$infile" = "here_doc" ]; then
	hereDoc=true
	args=("${args[@]:2}")
	len=${#args[@]}
else
	hereDoc=false
fi
pipeline=()
for ((i=0; i<$len-2; i++)); do
  pipeline+=("${args[$i]}" "|")
done
pipeline+=("${args[$i]}")

if [ "$hereDoc" = true ]; then
	eval "$firstComm << $limit" | eval "${pipeline[@]} >> $newOutFile" 2> "$origErrFile" # 2>/dev/null
else
	eval "< "$infile" ${pipeline[@]} > "$newOutFile" 2> "$origErrFile"" 2>/dev/null
fi

echo -e "${GREEN}original output:${NC}"
cat "$newOutFile"
echo -e ""
echo -e "${RED}original err_out:${NC}"
cat "$origErrFile"
if [ -s "$myErrFile" ];then
	echo -e ""
else
	echo -e "${YELLOW}there is no error message${NC}\n"
fi
#< "$infile" $1 | $2 > "$newOutFile"
#cat "$newOutFile"

	###diff check###
echo -e ""
diff $newOutFile $outfile > result
if [ -s result ]; then
	echo -e "${CYAN} diff result:"
	cat result
	echo "${NC}"
else
	echo -e " \033[7m CONGRATS: pipex and shell Std_out are the same"
	if [ -s "$myErrFile" ] || [ -s "$origErrFile" ]; then
		echo -e "${RED} But ... There is an error recorded in std_err${NC}"
	fi
fi

### removing temp files ###
rm -f $result
rm -f $newOutFile
rm -f $newInFile
rm -f $outfile
rm -f $myErrFile
rm -f $origErrFile




