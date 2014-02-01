bin/collateral-deacon
if [ $? -eq 0 ]
then
        feh -. --force-aliasing tmp/feh_tmp.ppm
        ppmtojpeg tmp/feh_tmp.ppm > tmp/feh_tmp.jpeg
        textme

        echo "Success."
else
        echo "Image generation failed." | mutt -s "Buddhabrot Notice" -- 4357573639@mms.att.net

        echo "Failure."
fi
