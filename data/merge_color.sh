#!/bin/bash
readonly QLANG=${LANG:0:5};

echo -e "\033[1;33mMerge quantities with user's language translation.\033[0m"
echo -e "\033[1;34mLocale = $QLANG\033[0m\n"
echo "#bin/bash" > temp.sh

rm merged/*.xml

for file in `ls quantities | grep xml`
do
	echo -e "\033[1;32mAdding\033[0m $file…"
	echo "xsltproc --stringparam trfile $file  --stringparam lang $QLANG -o merged/$file  merge.xslt quantities/$file" >> temp.sh
done

echo -e "\nMerging files…"
chmod a+rwx temp.sh
sh temp.sh
rm temp.sh

echo -e "\nDone."
