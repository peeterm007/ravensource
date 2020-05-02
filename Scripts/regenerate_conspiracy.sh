#!/bin/sh
#
# This script is not meant for users
# It is used by Ravenports developers to publish ravenports releases.

maintainer=marino
osname=$(uname -s)
if [ "$osname" = "SunOS" ]; then
myid=$(/usr/xpg4/bin/id -un)
else
myid=$(id -un)
fi
today=$(date "+%d %h %Y %H:%M")
message="Ravenports generated: ${today}"

if [ "${myid}" != "root" ]; then
   echo "Only root is allowed to regenerate ports (which requires using root-only ravenadm)"
   exit 1
fi

# Requires ravenadm v1.06 or later
CONSPIR=$(/raven/bin/ravenadm dev info D)

DPATH=$(dirname $0)
SCRIPTSDIR=$(cd ${DPATH} && pwd -P)
RAVENSRC=$(dirname ${SCRIPTSDIR})
PD_AWK=${SCRIPTSDIR}/miscellaneous/port_dates.awk
PD_FILE=${CONSPIR}/Mk/Misc/port_dates
CONVARS=${CONSPIR}/Mk/Misc/conspiracy_variants
TMPFULL=/tmp/port_dates
WARNING="Autogenerated -- Do not edit!"
PATTERN=RESERVED_WARNING
DATADIR=${SCRIPTSDIR}/Ravenports_Mk

for F in GID UID; do
   sed "s|${PATTERN}|${WARNING}|" ${DATADIR}/${F}.ravenports > ${CONSPIR}/Mk/Templates/${F}.ravenports
done
for F in information versions; do
   sed "s|${PATTERN}|${WARNING}|" ${DATADIR}/raven.${F}.mk > ${CONSPIR}/Mk/raven.${F}.mk
done
cp -RpP ${DATADIR}/raverreq   ${CONSPIR}/Mk/Misc/
cp -RpP ${DATADIR}/Keywords/* ${CONSPIR}/Mk/Keywords/
cp -RpP ${DATADIR}/Scripts/*  ${CONSPIR}/Mk/Scripts/
cp -RpP ${DATADIR}/Uses/*     ${CONSPIR}/Mk/Uses/

/raven/bin/ravenadm dev generate-conspiracy ${RAVENSRC}
if [ $? -ne 0 ]; then
   echo "Conspiracy generation failed --- aborting!"
   exit 1;
fi

/raven/bin/ravenadm dev generate-index

if [ $# -lt 1 -o "${1}" != "confirm" ]; then
   echo "add 'confirm' argument to regenerate (again) but with a commit this time"
   exit 0;
fi

(cd ${CONSPIR} && git add "." && git commit -m "${message}")
(cd ${CONSPIR} && git log --format="format:%ct" --name-only) | \
  awk -f ${PD_AWK} | sort > ${TMPFULL}
rm -f ${PD_FILE}
while read namebase timeS timeF
do
   grep -q " ${namebase} " ${CONVARS}
   if [ $? -eq 0 ]; then
      echo "${namebase} ${timeS} ${timeF}" >> ${PD_FILE}
   fi
done < ${TMPFULL}
rm -f ${TMPFULL}
(cd ${CONSPIR}/Mk && git add Misc)

chown -R ${maintainer} ${CONSPIR}
