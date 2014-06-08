#!/bin/bash

PARAM1=$1
PARAM2=$2

function no_title() {
    echo "No title provided."
    exit 1
}

if [[ "$PARAM1" = "" ]] ; then
    # Missing parameter.
    no_title
else
    if [[ "$PARAM1" == "-d" ]] ; then
        # Post will be draft.
        if [[ "$PARAM2" == "" ]] ; then
            # Missing Title
            no_title
        else
            # Param2 is Title, and it's a draft.
            DRAFT="yes"
            TITLE=$PARAM2
        fi
    else
        # Param1 is Title, and it's not a draft.
        DRAFT="no"
        TITLE=$PARAM1
    fi
fi

DATE=$(date '+%Y-%m-%d')    

if [[ "$DRAFT" == "yes" ]] ; then
    FOLDER=_drafts
else
    FOLDER=_posts
fi

TIME=$(date '+%H:%M')

LOWERTITLE=${TITLE,,}
DASHTITLE=${LOWERTITLE// /-}

FILENAME=$DATE"-"$DASHTITLE".markdown"

pushd . &> /dev/null
cd $FOLDER

echo "---" > $FILENAME
echo "layout: post" >> $FILENAME
echo "title: \"$TITLE\"" >> $FILENAME
echo "date:   $DATE $TIME" >> $FILENAME
echo "---" >> $FILENAME
echo "" >> $FILENAME

popd &> /dev/null
