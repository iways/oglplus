#!/bin/bash
# Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cd $(dirname $0)/../
build_dir=${PWD}/_build
label="http://oglplus.org/"
width=852
height=480
example="${1%.cpp}"
#
rootdir="$(dirname $0)/.."
tmpdir=$(mktemp -d)
mkdir -p ${tmpdir}
#
prefix="${tmpdir}/oglplus-$(basename ${example})"
labelfile=${tmpdir}/label.png
logofile=${tmpdir}/logo.png
#
filelist=${tmpdir}/filelist
rm -f ${filelist}
mkfifo ${filelist}

# make the label
convert \
	-size $[${width}/2]x28 xc:none \
	-background none \
	-pointsize 28 \
	-gravity center \
	-stroke black \
	-strokewidth 8 \
	-annotate 0 "${label}" \
	-blur 0x4 \
	-shadow ${width}x7+2+2 \
	+repage \
	-stroke none \
	-strokewidth 1 \
	-fill white \
	-annotate 0 "${label}" \
	${labelfile}

# make the logo
convert \
	-size 144x144 xc:none \
	-background none \
	-gravity center \
	-stroke black \
	-fill black \
	-draw 'circle 72,72, 72,144' \
	-blur 2x2 \
	-shadow ${width}x7 \
	+repage \
	"${rootdir}/doc/logo/oglplus_circular.png" \
	-composite \
	-adaptive-resize 72x72 \
	-border 16x0 \
	"${logofile}"


if [ "${example}" == "" ]
then echo "No example specified" && exit 1
fi

if [ ! -f "${build_dir}/${example}" ]
then echo "Unable to find built example '${example}' in '${PWD}'" && exit 1
fi
#
function convert_single_frame()
{
	convert \
		-size ${width}x${height} \
		-depth 8 \
		${1} \
		-flip \
		-alpha Off \
		-gravity SouthEast \
		${labelfile} \
		-composite \
		-gravity SouthEast \
		${logofile} \
		-composite \
		-quality 100 \
		${1%.rgba}.jpeg
	if [ $? -ne 0 ]
	then
		frame_no=$(echo ${1} | sed "s/${prefix////\\/}-0*\([0-9]\+\).*/\1/")
		prev_frame_no=$[${frame_no}-1]
		prev_frame=$(printf "${prefix}-%06d.jpeg" ${prev_frame_no})
		cp ${prev_frame} ${1%.rgba}.jpeg
	fi
	rm -f ${1}
}
#
let frameno=0
# start the example
(
xkill &
xkill_pid=$!
cd ${build_dir}
echo "${prefix}-" > ${filelist} &
nice -19 ${build_dir}/${example} --frame-dump ${prefix}- < ${filelist} |
while read framepath
do
	echo "${framepath}"
	convert_single_frame "${framepath}" > /dev/null
done > ${filelist}
)
kill -INT ${xkill_pid}

for job in $(jobs -p)
do wait ${job}
done

avconv -y -f image2 -i "${prefix}-%06d.jpeg" -r 25 -vcodec mpeg4 -b 8000k ${prefix}.avi
mv ${prefix}.avi .
rm -rf ${tmpdir}
