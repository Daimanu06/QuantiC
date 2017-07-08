#!/bin/bash
readonly QLANG=${LANG:0:5};

echo "Merge quantities with user's language translation."
echo -e "Locale = $QLANG\n"
echo "#bin/bash" > temp.sh

rm merged/*.xml

for file in `ls quantities | grep xml`
do
	echo "Adding $file…"
	echo "xsltproc --stringparam trfile $file  --stringparam lang $QLANG -o merged/$file  merge.xslt quantities/$file" >> temp.sh
done

echo -e "\nMerging files…"
chmod a+rwx temp.sh
sh temp.sh
rm temp.sh

echo -e "\nDone."
